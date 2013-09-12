/*******************************************************************************
 *             Copyright 2009 - 2010, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: hi_udisk.c
 * Description: USB Disk Management Module
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 * main1     2009-05-12   raojun
 * main2     2009-11-12   z42136                  spec update
 ******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/vfs.h>
#include <sys/statfs.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "linux_list.h"
#include "hi_udisk.h"
#include "scsiexe.h"

//#define DEBUG_POS printf("%s : %d\n", __FUNCTION__, __LINE__)

static HI_CHAR *m_UDisk_Root = HI_NULL;
static HI_CHAR *m_UDisk_Name = HI_NULL;     /*存放盘名，例如: sdb */
static HI_CHAR aszVfatPara[50];
#define UDISK_USB_DEV_ROOT  "/dev"
#define UDISK_USB_DEV_PATH_PART "/dev/sd%d%d"
#define UDISK_USB_DEV_PATH_HOST "/dev/scsi/host%d"

#define MKDIR_DEV_DISK(Path, host) sprintf(Path, m_UDisk_Root, host)
#define MKDIR_MNT_DISK(Path) sprintf(Path, "%s/%s", m_UDisk_Root,m_UDisk_Name)

//#define MKDIR_DEV_PART(Path, host, partid) sprintf(Path, UDISK_USB_DEV_PATH_PART, host, partid)
//#define MKDIR_MNT_PART(Path, host, partid) sprintf(Path, "%s/udisk%d/partition%d", m_UDisk_Root, host, partid)
#define MKDIR_DEV_PART2(Path, diskdevpath, partid) sprintf(Path, "%s%d", diskdevpath, partid)
#define MKDIR_MNT_PART2(Path, diskmntpath, partid) sprintf(Path, "%s/%s%d", diskmntpath,m_UDisk_Name,partid)

// 系统默认值
#define MAX_UDISK_DISKNUM_DEFAULT   32
#define MAX_UDISK_PARTNUM_DEFAULT   32

/*  分区数据插表时按分区号排序  */
//#define SORT_PART_NUM 

typedef struct
{
    struct list_head part_node;

    // for full report
    HI_BOOL bFullReport;
    HI_U64 u64WaterLine;

    HI_UDISK_PARTITIONINFO_S PartInfo;
}UDISK_PartNode_S;

typedef struct
{
    struct list_head disk_node;

    HI_UDISK_DISKINFO_S DiskInfo;
    HI_U32 host;

    struct list_head part_list_head;
}UDISK_DiskNode_S;

LIST_HEAD(m_UDisk_DiskListHead);

typedef struct
{
    struct list_head file_node;
    HI_UDISK_FILEINFO_S FileInfo;
}UDISK_FileNode_S;


pthread_mutex_t m_UDisk_mutex;
#define UDISK_Lock()    pthread_mutex_lock(&m_UDisk_mutex)
#define UDISK_UnLock()  pthread_mutex_unlock(&m_UDisk_mutex)

typedef struct
{
    HI_UDISK_EVENT_CALLBACK cb[HI_UDISK_EVENT_BUTT];
    HI_VOID * pPrivate[HI_UDISK_EVENT_BUTT];
}UDISK_Event_S;

UDISK_Event_S m_UDisk_Event;

HI_S32 UDISK_StatFs(HI_CHAR * pMnt, HI_U64 *pu64TotalSize, HI_U64 *pu64AvailSize)
{
    HI_S32 ret;
    struct statfs fs_stat;
    ret = statfs(pMnt, &fs_stat);
    if (ret != 0 )
    {
        perror("statfs");
        return HI_FAILURE;
    }

    *pu64TotalSize = (HI_U64)fs_stat.f_blocks * (HI_U64)fs_stat.f_bsize;
    *pu64AvailSize = (HI_U64)fs_stat.f_bavail * (HI_U64)fs_stat.f_bsize;

    return HI_SUCCESS;
}

HI_S32 UDISK_StatDisk(HI_CHAR * pDiskDev, HI_CHAR * pszVendor, HI_CHAR * pszModel)
{
	struct sg_io_hdr * p_hdr = init_io_hdr();
    unsigned char sense_buffer[SENSE_LEN];
    unsigned char data_buffer[BLOCK_LEN*256];
    int evpd=0, page_code=0;
    unsigned char * buffer;

	set_xfer_data(p_hdr, data_buffer, BLOCK_LEN*256);
	set_sense_data(p_hdr, sense_buffer, SENSE_LEN);

	int status = 0;

	int fd = open(pDiskDev, O_RDWR);
	if(fd <= 0)
	{
		printf("failed to open sg file %s\n", pDiskDev);
		destroy_io_hdr(p_hdr);
	    return HI_FAILURE;
	}

	status = execute_Inquiry(fd, page_code, evpd, p_hdr);
	if (status!=0)
	{
	    close(fd);
	    destroy_io_hdr(p_hdr);
	    return HI_FAILURE;
	}

    // get vendor : 8-15
    buffer = p_hdr->dxferp;
    memcpy(pszVendor, buffer+8, 8);
    pszVendor[9] = '\0';

    // get model : 16-31
    buffer = p_hdr->dxferp;
    memcpy(pszModel, buffer+16, 16);
    pszModel[17] = '\0';

	close(fd);
	destroy_io_hdr(p_hdr);
    return HI_SUCCESS;
}

HI_VOID UDISK_EventCallback(HI_UDISK_EVENT_E enEvent, HI_VOID * param)
{
    if(m_UDisk_Event.cb[enEvent])
    {
        m_UDisk_Event.cb[enEvent](enEvent, param, m_UDisk_Event.pPrivate[enEvent]);
    }
}

HI_S32 UDISK_Mount(const char * source, const char * target, const char *fs, HI_UDISK_FSTYPE_E * fs_mnt)
{
    HI_S32 ret;

    // 指定格式加载
    if(fs != NULL)
    {
        if (!strcmp(fs, "vfat")) 
        {
            ret = mount(source, target, "vfat", 0, aszVfatPara/*"iocharset=utf8,codepage=936"aszVfatPara*/);
        }
        else
        {
            ret = mount(source, target, fs, 0, NULL);
        }
        if(ret < 0)
        {
            perror("mount");
            printf("<ERROR>mount %s on %s type %s failed!\n", source, target, fs);
        }
        return ret;
    }

    // 未指定格式，自动判断格式，并加载
    if(UDISK_Mount(source, target, "vfat", NULL) >= 0)
    {
        *fs_mnt = HI_UDISK_FSTYPE_FAT32;
        return HI_SUCCESS;
    }

    // ext3分区，使用ext2和ext3有可能都可以加载成功。因此优先使用ext3加载。
    if(UDISK_Mount(source, target, "ext3", NULL) >= 0)
    {
        *fs_mnt = HI_UDISK_FSTYPE_EXT3;
        return HI_SUCCESS;
    }

    if(UDISK_Mount(source, target, "ext2", NULL) >= 0)
    {
        *fs_mnt = HI_UDISK_FSTYPE_EXT2;
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 UDISK_Umount(const char * target)
{
    HI_S32 ret;

    /* 2: MNT_DETACH:
    ** Perform a lazy unmount: make the mount point unavailable for new accesses,
    ** and actually perform the unmount when the mount point ceases  to be busy. */
    ret = umount2(target, 2);
    if(ret < 0)
    {
        perror("umount");
        printf("<ERROR>umount %s failed!\n", target);
    }

    return ret;
}

HI_S32 UDISK_GetDiskIndexByDevPath(HI_CHAR * pDevPath, HI_U32 * pu32DiskIndex)
{
    HI_U32 disk_index;
    UDISK_DiskNode_S * pos_disk;

    UDISK_Lock();

    disk_index = 0;
    list_for_each_entry(pos_disk, &m_UDisk_DiskListHead, disk_node)
    {
        if(strcmp(pDevPath, pos_disk->DiskInfo.szDevPath) == 0)
        {
            // disk found!
            *pu32DiskIndex = disk_index;

            UDISK_UnLock();
            return HI_SUCCESS;
        }

        disk_index++;
    }

    // disk not exist!
    UDISK_UnLock();
    return HI_FAILURE;
}

HI_S32 UDISK_GetPartIndexByDevPath(HI_CHAR * pDevPath, HI_U32 * pu32DiskIndex, HI_U32 * pu32PartIndex)
{
    HI_U32 disk_index, part_index;
    UDISK_DiskNode_S * pos_disk;
    UDISK_PartNode_S * pos_part;

    UDISK_Lock();

    // 找disk
    disk_index=0;
    list_for_each_entry(pos_disk, &m_UDisk_DiskListHead, disk_node)
    {
        part_index=0;
        list_for_each_entry(pos_part, &(pos_disk->part_list_head), part_node)
        {
            if(strcmp(pDevPath, pos_part->PartInfo.szDevPath) == 0)
            {
                // partition found
                *pu32DiskIndex = disk_index;
                *pu32PartIndex = part_index;

                UDISK_UnLock();
                return HI_SUCCESS;
            }
            part_index++;
        }
        disk_index++;
    }

    // partition not exist!
    UDISK_UnLock();
    return HI_FAILURE;
}

HI_VOID UDISK_AttachPart(UDISK_DiskNode_S * pDiskNode)
{
    HI_S32 s32Ret = 0;
    HI_S32 s32MntPartFailTimes = 0;
    DIR *dir = NULL;
    struct dirent* pEntry = NULL;
    HI_U32 u32DevPathLen = 0;
    HI_U32 u32DevAllPathLen = 0;

    HI_BOOL bListEmpty = HI_FALSE;
    HI_BOOL bIsExistPart = HI_FALSE;  /*  只有盘没有分区;例如:只存在 sdb,不存在sdb1  */
    HI_U32 u32PartId = 1;
    HI_U32 u32CurPartId = 1;
    HI_U32 u32NextPartId = 1;

    UDISK_PartNode_S * pPartNode = HI_NULL;
    UDISK_PartNode_S * pCurpart = HI_NULL;
    UDISK_PartNode_S * pNextPart = HI_NULL;

    HI_UDISK_PARTITIONINFO_S * pPart;

    HI_CHAR szPartDevPath[MAX_UDISK_NAME_LEN] = "";
    HI_CHAR szPartMntPath[MAX_UDISK_NAME_LEN] = "";

    HI_UDISK_EVENT_PARAM_MOUNT_S param;

    u32DevPathLen = strlen(m_UDisk_Name);
    u32DevAllPathLen =  strlen(pDiskNode->DiskInfo.szDevPath);   /*  "/dev/sdb" 的长度  */
    dir = opendir(UDISK_USB_DEV_ROOT);
    while (NULL != (pEntry = readdir(dir)))
    {
        if ((strlen(pEntry->d_name) != u32DevPathLen )
                && (0 == strncmp(pEntry->d_name, m_UDisk_Name, u32DevPathLen)))
        {
            bIsExistPart = HI_TRUE;

            //找到
            sscanf(pEntry->d_name+u32DevPathLen, "%d", &u32PartId);
            printf("############## d_name = %s \n", pEntry->d_name);

            MKDIR_DEV_PART2(szPartDevPath, pDiskNode->DiskInfo.szDevPath, u32PartId);
            MKDIR_MNT_PART2(szPartMntPath, pDiskNode->DiskInfo.szMntPath, u32PartId);

            s32Ret = mkdir(szPartMntPath, 0777);
            if (s32Ret < 0)
            {
                perror("mkdir");
                printf("<ERROR>make usb disk dir :%s error\r\n", szPartMntPath);

                if(errno == EEXIST)
                {
                    // should not go here! continue ignore error
                    printf("<FATAL ERROR>%s should not exist!\n", szPartMntPath);
                }
            }

            pPartNode = (UDISK_PartNode_S *)malloc(sizeof(UDISK_PartNode_S));
            if(pPartNode == HI_NULL)
            {
                rmdir(szPartMntPath);
                s32MntPartFailTimes += 1;
                break;
            }

            pPartNode->bFullReport = HI_FALSE;
            pPartNode->u64WaterLine = 0;

            pPart = &pPartNode->PartInfo;

            pPart->bMounted = HI_FALSE;
            strcpy(pPart->szDevPath, szPartDevPath);
            strcpy(pPart->szMntPath, szPartMntPath);

            if(UDISK_Mount(szPartDevPath, szPartMntPath, HI_NULL, &pPart->enFSType) >= 0)
            {
                UDISK_StatFs(szPartMntPath, &pPart->u64TotalSize, &pPart->u64AvailSize);
                pPart->bMounted = HI_TRUE;
            }
            else
            {
                s32MntPartFailTimes += 1;
            }
            // 将part节点加入链表
            UDISK_Lock();
            
#ifdef SORT_PART_NUM
            bListEmpty = list_empty(&pDiskNode->part_list_head);
            if (bListEmpty)
            {
                list_add_tail(&pPartNode->part_node, &pDiskNode->part_list_head);
            }
            else
            {
                list_for_each_entry(pCurpart, &(pDiskNode->part_list_head), part_node)
                {
                    sscanf(pCurpart->PartInfo.szDevPath+u32DevAllPathLen, "%d", &u32CurPartId);
                    pNextPart = list_entry(pCurpart->part_node.next, UDISK_PartNode_S, part_node);

                    /*是否在链表尾*/
                    if(&pNextPart->part_node == &(pDiskNode->part_list_head))
                    {
                        /*按分区号数字大小顺序插表*/
                        if (u32PartId > u32CurPartId)
                        {
                            list_add(&pPartNode->part_node,&pCurpart->part_node);
                            break;
                        }
                        else
                        {
                            list_add_tail(&pPartNode->part_node,&pCurpart->part_node);
                            break;
                        }
                    }
                    else
                    {
                        sscanf(pNextPart->PartInfo.szDevPath+u32DevAllPathLen, "%d", &u32NextPartId);
                        if (u32PartId>u32CurPartId && u32PartId>u32NextPartId)
                        {
                            continue;
                        }
                        else if (u32PartId>u32CurPartId && u32PartId<u32NextPartId)
                        {
                            list_add(&pPartNode->part_node,&pCurpart->part_node);
                            break;
                        }
                        else
                        {
                            list_add_tail(&pPartNode->part_node,&pCurpart->part_node);
                            break;
                        }
                   }
                }
            }
#else
            // 将part节点加入链表
            list_add_tail(&pPartNode->part_node, &pDiskNode->part_list_head);
#endif            
            UDISK_UnLock();
            /* 事件回调 */ 
            UDISK_GetPartIndexByDevPath(pPart->szDevPath, &param.u32DiskIndex, &param.u32PartitionIndex);
            if(HI_TRUE == pPart->bMounted)
            {
                UDISK_EventCallback(HI_UDISK_EVENT_MOUNTED, &param);
            }
        }        
    }

    /*  当没有分区时;例如:只存在 sdb,不存在sdb1  */
    if(HI_FALSE == bIsExistPart)  
    {
        pPartNode = (UDISK_PartNode_S *)malloc(sizeof(UDISK_PartNode_S));
        if(pPartNode == HI_NULL)
        {
            return;
        }
        pPartNode->bFullReport = HI_FALSE;
        pPartNode->u64WaterLine = 0;

        pPart = &pPartNode->PartInfo;
        pPart->bMounted = HI_FALSE;

        strcpy(pPart->szDevPath, pDiskNode->DiskInfo.szDevPath);
        strcpy(pPart->szMntPath, pDiskNode->DiskInfo.szMntPath);

        if(UDISK_Mount(pPart->szDevPath, pPart->szMntPath, HI_NULL, &pPart->enFSType) >= 0)
        {
            UDISK_StatFs(pPart->szMntPath, &pPart->u64TotalSize, &pPart->u64AvailSize);
            pPart->bMounted = HI_TRUE;
        }
        else
        {
            s32MntPartFailTimes += 1;
        }
        // 将part节点加入链表
        UDISK_Lock();
        list_add_tail(&pPartNode->part_node, &pDiskNode->part_list_head);
        UDISK_UnLock();
        
        // 事件回调
        UDISK_GetPartIndexByDevPath(pPart->szDevPath, &param.u32DiskIndex, &param.u32PartitionIndex);
        if(HI_TRUE == pPart->bMounted)
        {
            UDISK_EventCallback(HI_UDISK_EVENT_MOUNTED, &param);
        }
    }

    /* 所有分区挂载成功  */
    if(0 == s32MntPartFailTimes)
    {
        UDISK_EventCallback(HI_UDISK_EVENT_ALLPARTMOUNTED, &param);
    }
#if 0
    /** 如果检测不到part,则再检测是否存在disk */
    dir = opendir(UDISK_USB_DEV_ROOT);
    if (HI_FAILURE == s32Ret)
    {
        while (NULL != (pEntry = readdir(dir)))
        {
            if (0 != strncmp(pEntry->d_name, m_UDisk_Name, u32DevPathLen))
            {
                continue ;
            }

            sprintf(szPartDevPath, "%s", pDiskNode->DiskInfo.szDevPath);
            u32PartId = 1;

            MKDIR_MNT_PART2(szPartMntPath, pDiskNode->DiskInfo.szMntPath, u32PartId);

            s32Ret = mkdir(szPartMntPath, 0777);
            if (s32Ret < 0)
            {
                perror("mkdir");
                printf("<ERROR>make usb disk dir :%s error\r\n", szPartMntPath);

                if(errno == EEXIST)
                {
                    // should not go here! continue ignore error
                    printf("<FATAL ERROR>%s should not exist!\n", szPartMntPath);
                }
            }

            pPartNode = (UDISK_PartNode_S *)malloc(sizeof(UDISK_PartNode_S));
            if(pPartNode == HI_NULL)
            {
                break;
            }

            pPartNode->bFullReport = HI_FALSE;
            pPartNode->u64WaterLine = 0;

            pPart = &pPartNode->PartInfo;

            pPart->bMounted = HI_FALSE;
            strcpy(pPart->szDevPath, szPartDevPath);
            strcpy(pPart->szMntPath, szPartMntPath);

            if(UDISK_Mount(szPartDevPath, szPartMntPath, HI_NULL, &pPart->enFSType) >= 0)
            {
                UDISK_StatFs(szPartMntPath, &pPart->u64TotalSize, &pPart->u64AvailSize);
                pPart->bMounted = HI_TRUE;
            }

            // 将part节点加入链表
            UDISK_Lock();
            list_add_tail(&pPartNode->part_node, &pDiskNode->part_list_head);
            UDISK_UnLock();

            // 事件回调
            UDISK_GetPartIndexByDevPath(pPart->szDevPath, &param.u32DiskIndex, &param.u32PartitionIndex);
            UDISK_EventCallback(HI_UDISK_EVENT_MOUNTED, &param);
        }
    }
#endif
    closedir(dir);
    return;
}

static UDISK_DiskNode_S * UDISK_FindDisk(HI_CHAR * pDevPath)
{
    UDISK_DiskNode_S * pos;

    UDISK_Lock();
    list_for_each_entry(pos, &m_UDisk_DiskListHead, disk_node)
    {
        if (strcmp(pDevPath, pos->DiskInfo.szDevPath) == 0)
        {
            UDISK_UnLock();
            return pos;
        }
    }

    UDISK_UnLock();
    return HI_NULL;
}

static HI_VOID UDISK_UMountDisk(HI_CHAR * pDiskMntPath)
{
    DIR *dir = NULL;
    struct dirent* pEntry = NULL;

    HI_CHAR szPartMntPath[MAX_UDISK_NAME_LEN] = "";

    dir = opendir(pDiskMntPath);
    while (NULL != (pEntry = readdir(dir)))
    {
        if ( (0 == strcmp(pEntry->d_name, "."))
           ||(0 == strcmp(pEntry->d_name, "..")))
        {
            continue ;
        }

        sprintf(szPartMntPath, "%s/%s", pDiskMntPath, pEntry->d_name);
        UDISK_Umount(szPartMntPath);
        rmdir(szPartMntPath);
    }
    closedir(dir);
}

static HI_VOID UDISK_UMountDisks(HI_CHAR * root)
{
    DIR *dir = NULL;
    struct dirent* pEntry = NULL;
    HI_CHAR szDiskMntPath[MAX_UDISK_NAME_LEN] = "";

    dir = opendir(root);
    if(dir == NULL)
    {
        printf("<ERROR>make sure %s is an valid directory\n", root);
        return ;
    }

    while (NULL != (pEntry = readdir(dir)))
    {
        if ( (0 == strcmp(pEntry->d_name, ".")) || (0 == strcmp(pEntry->d_name, "..")))
        {
            continue ;
        }

        sprintf(szDiskMntPath, "%s/%s", root, pEntry->d_name);
        UDISK_UMountDisk(szDiskMntPath);
        rmdir(szDiskMntPath);
    }

    closedir(dir);
}


static HI_VOID UDISK_AttachDisk(HI_CHAR * pDevPath)
{
    HI_S32 s32Ret = 0;

    HI_CHAR szDiskDevPath[MAX_UDISK_NAME_LEN] = "";
    HI_CHAR szDiskMntPath[MAX_UDISK_NAME_LEN] = "";
    HI_CHAR szTemp[MAX_UDISK_NAME_LEN] = "";

    UDISK_DiskNode_S * pDiskNode = HI_NULL;
    HI_UDISK_DISKINFO_S * pDisk;

    HI_UDISK_EVENT_PARAM_PLUG_S param;

    // 检查设备是否已经加载，如果已经加载则不做任何处理
    pDiskNode = UDISK_FindDisk(pDevPath);
    if( pDiskNode != HI_NULL )
    {
        UDISK_Lock();
        pDiskNode->DiskInfo.bPlugIn = HI_TRUE;
        UDISK_UnLock();
        return;
    }

    MKDIR_MNT_DISK(szDiskMntPath);

    // 判断mount的目的目录是否存在。没有则创建之；有则存在异常
    s32Ret = mkdir(szDiskMntPath, 0777);
    if(s32Ret < 0)
    {
        if(errno == EEXIST)
        {
            // 目录已经存在，表示上次程序已经加载了，但退出时没有卸载
            // 卸载后, 在后面的过程中重新加载
            UDISK_UMountDisk(szDiskMntPath);
        }
        else
        {
            // should not go here!!
            perror("mkdir");
            printf("<ERROR>make usb disk dir :%s error\r\n", szDiskMntPath);
        }
    }

    // 创建新的Disk节点
    pDiskNode = (UDISK_DiskNode_S *)malloc(sizeof(UDISK_DiskNode_S));
    if(pDiskNode == HI_NULL)
    {
        return;
    }

    // 给Disk节点赋值
    pDisk = &pDiskNode->DiskInfo;

    strcpy(pDisk->szDevPath,pDevPath);
    printf("pDisk->szDevPath:%s \r\n", pDisk->szDevPath);
    strcpy(pDisk->szMntPath, szDiskMntPath);

    // get disk informations
    //pDisk->u32Port = 0;
    //pDisk->u64Size = 0;
    //sprintf(szTemp, "%s", pDisk->szDevPath);
    UDISK_StatDisk(pDisk->szDevPath, pDisk->szVendor, pDisk->szModel);

    INIT_LIST_HEAD(&pDiskNode->part_list_head);

    // 将Disk节点加入到链表
    UDISK_Lock();
    list_add_tail(&(pDiskNode->disk_node), &m_UDisk_DiskListHead);
    pDiskNode->DiskInfo.bPlugIn = HI_TRUE;
    UDISK_UnLock();

    // plugin 事件回调
    UDISK_GetDiskIndexByDevPath(pDisk->szDevPath, &param.u32DiskIndex);
    UDISK_EventCallback(HI_UDISK_EVENT_PLUGIN, &param);
    
    // 加载磁盘下所有的分区
    UDISK_AttachPart(pDiskNode);
}

static HI_VOID UDISK_DetachDisk(HI_CHAR * pDevPath)
{
    HI_S32 s32Ret;
    HI_U32 u32CheckUdiskTimes = 3;

    UDISK_DiskNode_S * pDiskNode = HI_NULL;
    UDISK_PartNode_S * pPartNode, * n;

    HI_UDISK_EVENT_PARAM_PLUG_S  param_plg;
    HI_UDISK_EVENT_PARAM_MOUNT_S param_mnt;

    // 找到对应的disk/part节点，删除之
    pDiskNode = UDISK_FindDisk(pDevPath);
    if(pDiskNode == HI_NULL)
    {
        // 没有找到对应的disk节点
        return ;
    }

    UDISK_Lock();
    list_for_each_entry_safe(pPartNode, n, &(pDiskNode->part_list_head), part_node)
    {
        // 如果已经加载，则卸载
        
        if(pPartNode->PartInfo.bMounted == HI_TRUE)
        {
            
            while (u32CheckUdiskTimes > 0)
            {
                
                sleep(1);
                s32Ret = UDISK_Umount(pPartNode->PartInfo.szMntPath);
                if (HI_SUCCESS == s32Ret)
                {
                    break;
                }
                u32CheckUdiskTimes--;
                
            }            
            // umounted 事件回调
            UDISK_GetPartIndexByDevPath(pPartNode->PartInfo.szDevPath, &param_mnt.u32DiskIndex, &param_mnt.u32PartitionIndex);
            UDISK_EventCallback(HI_UDISK_EVENT_UMOUNTED, &param_mnt);
        }

        /*  删除mount路径  */
        rmdir(pPartNode->PartInfo.szMntPath);

        // 从分区链表中删除该分区
        list_del(&pPartNode->part_node);
        
        free(pPartNode);
    }

    // plugout事件回调
    UDISK_GetDiskIndexByDevPath(pDiskNode->DiskInfo.szDevPath, &param_plg.u32DiskIndex);    
    UDISK_EventCallback(HI_UDISK_EVENT_PLUGOUT, &param_plg);

    // 删除disk目录
    rmdir(pDiskNode->DiskInfo.szMntPath);

    // 从磁盘链表中删除该磁盘
    list_del(&pDiskNode->disk_node);
    
    free(pDiskNode);

    UDISK_UnLock();
}

HI_VOID UDISK_ShowDiskInfo(HI_UDISK_DISKINFO_S * pDiskInfo)
{
    printf("======== disk info ================\n");
    //printf("port    = %d\n",    pDiskInfo->u32Port);
    printf("total size    = %lld\n",  pDiskInfo->u64TotalSize);
    printf("Free size    = %lld\n",  pDiskInfo->u64AvailSize);
    printf("Vendor  = %s\n",    pDiskInfo->szVendor);
    printf("Model   = %s\n",    pDiskInfo->szModel);
    printf("devpath = %s\n",    pDiskInfo->szDevPath);
    printf("mntpath = %s\n",    pDiskInfo->szMntPath);
    printf("===================================\n");
}

HI_VOID UDISK_ShowPartInfo(HI_UDISK_PARTITIONINFO_S * pPartInfo)
{
    printf("======== part info ================\n");
    printf("bMounted = %s\n",   (pPartInfo->bMounted==HI_TRUE)?"YES":"NO");
    printf("FS       = %d\n",   pPartInfo->enFSType);
    printf("size     = %lld\n", pPartInfo->u64TotalSize);
    printf("avail    = %lld\n", pPartInfo->u64AvailSize);
    printf("devpath  = %s\n",   pPartInfo->szDevPath);
    printf("mntpath  = %s\n",   pPartInfo->szMntPath);
    printf("===================================\n");

}

HI_VOID UDISK_ShowFileList(HI_UDISK_FILELIST_S * pFileList)
{
    HI_U32 i;

    printf("HI_UDISK_FILE_ShowFileList: total files = %d\n", pFileList->u32FileNum);
    for(i=0; i<pFileList->u32FileNum; i++)
    {
        printf("%d\t: type=%d, name = %s, full = %s\n",
                pFileList->ppFileList[i]->u32Index,
                pFileList->ppFileList[i]->u32Type,
                pFileList->ppFileList[i]->pszShortName,
                pFileList->ppFileList[i]->pszFullName);
    }

    return;
}

HI_VOID UDISK_CheckDiskPlugInOut(HI_VOID)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_BOOL bCheckDisk = HI_FALSE;
    DIR *dir = NULL;
    struct dirent* pEntry = NULL;
    HI_CHAR szDiskDevPath[MAX_UDISK_NAME_LEN] = "";
    HI_S32 s32NameLen = 0;   /*  磁盘或分区的名字长度  */
    HI_S32 s32Num = 0;      /*  循环变量  */
    HI_BOOL bFilter = HI_FALSE;   /*  过滤带数字的分区  */
    
    UDISK_DiskNode_S *pDiskPos = HI_NULL;
    UDISK_DiskNode_S *n = HI_NULL;
    
    /* 磁盘插入标志先置假，判断磁盘是否有拔出和插入动作 */
    UDISK_Lock();
    list_for_each_entry(pDiskPos, &m_UDisk_DiskListHead, disk_node)
    {
        pDiskPos->DiskInfo.bPlugIn = HI_FALSE;
    }
    UDISK_UnLock();
    
    dir = opendir(UDISK_USB_DEV_ROOT);
    if (NULL == dir)
    {
        printf("can't open directory %s !\r\n", UDISK_USB_DEV_ROOT);
        return;
    }
    while (NULL != (pEntry = readdir(dir)))
    {
        /*  找到 sd 打头的盘  */        
        s32NameLen = strlen(pEntry->d_name);        
        if ( pEntry->d_name[0]=='s' && pEntry->d_name[1]=='d' && s32NameLen>=3 )
        {
            /*  过滤带数字的分区，如:sdb1  */
            for( s32Num=3; s32Num<s32NameLen; s32Num++ )
            {
                if( isdigit(pEntry->d_name[s32Num]) )
                {
                    bFilter = HI_TRUE;
                    break;
                }
            }
            if( HI_TRUE == bFilter )
            {
                bFilter = HI_FALSE;
                continue;
            }

            m_UDisk_Name = (HI_CHAR *)malloc(strlen(pEntry->d_name)+1);
             if ( NULL == m_UDisk_Name )
            {
                printf("no mem for name!\n");
                continue;
            }
            strcpy(m_UDisk_Name, pEntry->d_name);
            sprintf(szDiskDevPath,"%s/%s",UDISK_USB_DEV_ROOT,m_UDisk_Name);
            
            s32Ret = access(szDiskDevPath, F_OK);
            if (HI_SUCCESS == s32Ret)
            {
                bCheckDisk = HI_TRUE;
				printf("111111111111111111111111\n");
                UDISK_AttachDisk(szDiskDevPath);
            }
            else
            {
				printf("44444444444444444444444444\n");
                UDISK_DetachDisk(szDiskDevPath);
                perror("access");
            }
            
            if(HI_NULL != m_UDisk_Name)
            {
                free(m_UDisk_Name);
                m_UDisk_Name = HI_NULL;
            }
        }
    }

    /* 从链表中删除已经被拔出的磁盘 */ 
    UDISK_Lock();
    list_for_each_entry_safe(pDiskPos, n, &m_UDisk_DiskListHead, disk_node)
    {
        if(HI_FALSE == pDiskPos->DiskInfo.bPlugIn)
        {
            printf("detach %s\n",pDiskPos->DiskInfo.szDevPath);
            UDISK_DetachDisk(pDiskPos->DiskInfo.szDevPath);
        }
    }    
    UDISK_UnLock();
    closedir(dir);
    return ;
}

HI_VOID UDISK_CheckPartitionFull(HI_VOID)
{
    HI_U32 disk_index, part_index;
    UDISK_DiskNode_S * pDiskNode;
    UDISK_PartNode_S * pPartNode;
    HI_U64 u64TotalSize, u64AvailSize;
    HI_UDISK_EVENT_PARAM_FULL_S param;

    UDISK_Lock();

    // 找disk
    disk_index = 0;
    list_for_each_entry(pDiskNode, &m_UDisk_DiskListHead, disk_node)
    {
        // disk found, 找partition
        part_index = 0;
        list_for_each_entry(pPartNode, &(pDiskNode->part_list_head), part_node)
        {
            if(pPartNode->bFullReport == HI_TRUE)
            {
                if(UDISK_StatFs(pPartNode->PartInfo.szMntPath, &u64TotalSize, &u64AvailSize) == HI_SUCCESS)
                {
                    if(u64AvailSize <= pPartNode->u64WaterLine)
                    {
                        // 发送FULL事件
                        param.u32DiskIndex = disk_index;
                        param.u32PartitionIndex = part_index;

                        // 用户函数回调中，有可能会调用UDISK的接口引起死锁
                        UDISK_EventCallback(HI_UDISK_EVENT_FULL, &param);
                    }
                }
            }
            part_index++;
        }
        disk_index++;
    }

    // partition not exist!
    UDISK_UnLock();
}

/* filter包含指定的扩展名，则返回HI_SUCCESS，否则返回HI_FAILURE */
HI_S32 UDISK_CheckFILTER(HI_S8 *filename,
            HI_UDISK_FILTER_E eFilterType,
            HI_CHAR * filter)
{
    HI_CHAR *pSuffix = NULL;
    HI_U32 SuffixLen;
    HI_CHAR *pSuffixFlt = NULL;

    // filter 包含通配符".*"
    if(strcmp(filter, ".*") == 0)
    {
        return HI_SUCCESS;
    }

    pSuffix = strrchr((char*)filename, '.');
    if (NULL == pSuffix)
    {
        return HI_FAILURE;
    }
    SuffixLen = strlen(pSuffix);

    /* 遍历flt中所有的suffix */
    while(1)
    {
        if(pSuffixFlt == NULL)
        {
            // 第一个flt
            pSuffixFlt = strchr(filter, '.');
        }
        else
        {
            // 后面的flt
            pSuffixFlt = strchr(pSuffixFlt+1, '.');
        }

        /* 最后一个flt已经处理了 */
        if(pSuffixFlt == NULL)
        {
            return HI_FAILURE;
        }

        if(eFilterType & HI_UDISK_FLT_CASECARE)
        {
            // 比较时，考虑大小写差异
            if(strncmp(pSuffixFlt, pSuffix, SuffixLen) == 0)
            {
                return HI_SUCCESS;
            }
        }
        else
        {
            // 比较时，忽略大小写差异
            if(strncasecmp(pSuffixFlt, pSuffix, SuffixLen) == 0)
            {
                return HI_SUCCESS;
            }
        }
    }

    return HI_FAILURE;
}

HI_S32 UDISK_AddFileToList(
    HI_CHAR *pathname,
    HI_CHAR *filename,
    HI_UDISK_FILELIST_S * pFileList)
{
    HI_UDISK_FILEINFO_S *pNewFile = NULL;
    struct stat buf;
    HI_CHAR *pos = NULL;

    // 增加一个指向FILEINFO_S结构体指针的内存
    //*(pFileList->ppFileList) = (HI_UDISK_FILEINFO_S *)realloc(*(pFileList->ppFileList), sizeof(HI_UDISK_FILEINFO_S *)*(pFileList->u32FileNum));

    pNewFile = (HI_UDISK_FILEINFO_S *)malloc(sizeof(HI_UDISK_FILEINFO_S));
    if ( NULL == pNewFile )
    {
        printf("no mem for new file node!\n");
        return HI_UDISK_ERR_NOMEM;
    }

    pNewFile->u32Index = pFileList->u32FileNum;
    pNewFile->u32Size = 0;
    pNewFile->u32CTime = 0;
    pNewFile->pszShortName = malloc(strlen(filename) + 1);
    pNewFile->pszFullName = malloc(strlen(pathname) + strlen("/") + strlen(filename) + 1);
    if (   NULL == pNewFile->pszShortName
        || NULL == pNewFile->pszFullName )
    {
        free(pNewFile);
        printf("no mem for new file name string!\n");
        return HI_UDISK_ERR_NOMEM;
    }

    strcpy(pNewFile->pszShortName, filename);

    if (0 == strcmp(filename, "."))
    {
        pNewFile->u32Type = 0;
        strcpy(pNewFile->pszFullName, pathname);
    }
    else if (0 == strcmp(filename, ".."))
    {
        pNewFile->u32Type = 0;
        strcpy(pNewFile->pszFullName, pathname);
        if (0 == strcmp(pNewFile->pszFullName, m_UDisk_Root))
        {
            /*Reach USB Disk Root Dir, Enter Upper Layer Dir is forbidden*/
        }
        else if (0 == strcmp(pNewFile->pszFullName, "/"))
        {
            /*Already Linux Root Dir*/
        }
        else
        {
            pos = strrchr(pNewFile->pszFullName, (int)'/');
            if (NULL == pos)
            {
                /*UnHandled Path Name*/
            }
            else if (pos == pNewFile->pszFullName)
            {
                /*Reach Linux Root Dir*/
                *(pos+1) = '\0';
            }
            else
            {
                *pos = '\0';
            }
        }
    }
    else
    {
        strcpy(pNewFile->pszFullName, pathname);
        strcat(pNewFile->pszFullName, "/");
        strcat(pNewFile->pszFullName, filename);

        if (lstat(pNewFile->pszFullName, &buf) < 0)
        {
            printf("<WARNING>%s, %d : lstat failed\r\n", __FUNCTION__, __LINE__);
        }
        else
        {
            if (S_ISDIR(buf.st_mode))
            {
                pNewFile->u32Type = 0;
            }
            else
            {
                pNewFile->u32Type = 1;
            }
        }
    }

    /*y00107738 add*/
    if (!stat(pNewFile->pszFullName, &buf))
    {
        pNewFile->u32Size = buf.st_size;
        pNewFile->u32CTime = buf.st_ctime;
    }

    pFileList->ppFileList[pFileList->u32FileNum] = pNewFile;
    pFileList->u32FileNum++;

    return HI_SUCCESS;
}

HI_S32 UDISK_ScanDir(
            HI_CHAR *pszDir,
            HI_UDISK_SCAN_S * pScanOpt,
            HI_UDISK_FILELIST_S * pFileList)
{
    HI_S8 subFilePath[MAX_UDISK_NAME_LEN] = {0};
    HI_S32 subFilePathLen = 0;
    DIR *dir = NULL;
    struct stat64 fileStruct;
    struct dirent* pEntry = NULL;

    dir = opendir(pszDir);
    if (NULL == dir)
    {
        return HI_UDISK_ERR_NOTEXIST;
    }

    while (NULL != (pEntry = readdir(dir)))
    {
        /* "." */
        if(0 == strcmp(pEntry->d_name, "."))
        {
            if(pScanOpt->enFilterType & HI_UDISK_FLT_CURDIR)
            {
                UDISK_AddFileToList(pszDir, pEntry->d_name, pFileList);
            }
        }
        else if(0 == strcmp(pEntry->d_name, ".."))
        {
            if(pScanOpt->enFilterType & HI_UDISK_FLT_UPDIR)
            {
                UDISK_AddFileToList(pszDir, pEntry->d_name, pFileList);
            }
        }
        else
        {
            subFilePathLen = strlen(pszDir) + strlen("/") + strlen(pEntry->d_name) + 1;
            if (MAX_UDISK_NAME_LEN < subFilePathLen)
            {
                printf("<WARNING>%s, %d : path length (%d) is too long\r\n",
                        __FUNCTION__, __LINE__, subFilePathLen);
                continue;
            }
            memset(subFilePath, 0x0, MAX_UDISK_NAME_LEN);
            strcpy(subFilePath, pszDir);
            strcat(subFilePath,"/");
            strcat(subFilePath,pEntry->d_name);

            int ret = lstat64(subFilePath, &fileStruct);
            if ( ret < 0)
            {
                perror("lstat: ");
                printf("subFilePath=%s, ret = %d\r\n",subFilePath, ret);
                printf("<WARNING>%s, %d : lstat failed\r\n",
                        __FUNCTION__, __LINE__);
                break;
            }

            if (S_ISDIR(fileStruct.st_mode))
            {
                if(pScanOpt->enFilterType & HI_UDISK_FLT_SUBDIR)
                {
                    UDISK_AddFileToList(pszDir, pEntry->d_name, pFileList);
                }

                if (HI_TRUE == pScanOpt->bRecursive)
                {
                    UDISK_ScanDir(subFilePath, pScanOpt, pFileList);
                }
            }
            else
            {
                /* 文件过滤 */
                if(HI_SUCCESS == UDISK_CheckFILTER(pEntry->d_name, pScanOpt->enFilterType, pScanOpt->pFileFilter))
                {
                    UDISK_AddFileToList(pszDir, pEntry->d_name, pFileList);
                }
            }
        }
    }
    closedir(dir);

    return HI_SUCCESS;
}

static HI_BOOL m_UDisk_NotifyQuit = HI_FALSE;
static pthread_t m_Udisk_CheckThread = HI_NULL;

HI_VOID * UDISK_CheckThread(HI_VOID * args)
{
    while(m_UDisk_NotifyQuit != HI_TRUE)
    {
        // 检测是否有DISK插入/拔出
        UDISK_CheckDiskPlugInOut();

        // 检测分区是否满
        UDISK_CheckPartitionFull();

        // 每轮检测之后睡眠一下
        sleep(1);
    }

    return HI_NULL;
}

HI_S32 HI_UDISK_Init(const HI_CHAR * pUdiskRoot)
{
    DIR * dir = NULL;
    struct dirent* pEntry = NULL;
    pthread_mutexattr_t mutex_attr;

    if(pUdiskRoot == HI_NULL)
    {
        printf("<ERROR>udisk root can't be NULL\n");
        return HI_FAILURE;
    }

    // umount 1:  disks & parts
    UDISK_UMountDisks((HI_CHAR *)pUdiskRoot);

    // umount 2: root
    UDISK_Umount(pUdiskRoot);

    // pDiskRoot指向的目录是否存在
    dir = opendir(pUdiskRoot);
    if(dir == NULL)
    {
        perror("opendir");
        printf("%s not exist, so make it!\n", pUdiskRoot);

        if(mkdir(pUdiskRoot, 0777) < 0)
        {
            perror("mkdir");
            printf("<ERROR>make dir %s error\r\n", pUdiskRoot);
            return HI_FAILURE;
        }
        dir = opendir(pUdiskRoot);
    }

    // pDiskRoot指向的目录是否为空
    while (NULL != (pEntry = readdir(dir)))
    {
        if ( (0 == strcmp(pEntry->d_name, ".")) || (0 == strcmp(pEntry->d_name, "..")))
        {
            continue ;
        }

        // 目录不为空
        printf("<ERROR>%s is not empty!\n", pUdiskRoot);
        closedir(dir);
        return HI_FAILURE;
    }

    closedir(dir);

    // 挂载pUdiskRoot到tmpfs
    if(UDISK_Mount("nodev", pUdiskRoot, "tmpfs", NULL) < 0)
    {
        return HI_FAILURE;
    }

    // 初始化内部数据变量
    m_UDisk_Root = (HI_CHAR *)malloc(strlen(pUdiskRoot) + 1);
    strcpy(m_UDisk_Root, pUdiskRoot);

    bzero(&m_UDisk_Event, sizeof(m_UDisk_Event));

    // 初始化内部互斥变量和信号锁资源
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE_NP);
    if (0 != pthread_mutex_init(&m_UDisk_mutex, &mutex_attr ))
    {
        printf("<ERROR>UDISK check mutex created failed\r\n");
        return HI_FAILURE;
    }

    // 创建事件检测线程
    m_UDisk_NotifyQuit = HI_FALSE;
    if (0 != pthread_create(&m_Udisk_CheckThread, NULL, UDISK_CheckThread, NULL))
    {
        printf("<ERROR>UDISK check thread created failed\r\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UDISK_Deinit(HI_VOID)
{
    // 通知检测线程退出
    m_UDisk_NotifyQuit = HI_TRUE;

    // 等待检测线程完全退出
    if (HI_NULL != m_Udisk_CheckThread)
    {
        pthread_join(m_Udisk_CheckThread, NULL);
        m_Udisk_CheckThread = HI_NULL;
    }

    UDISK_Umount(m_UDisk_Root);
    if (HI_NULL != m_UDisk_Root)
    {
        free(m_UDisk_Root);
        m_UDisk_Root = HI_NULL;
    }

    pthread_mutex_destroy(&m_UDisk_mutex);
    //sem_destroy(&m_UDisk_sem);

    return HI_SUCCESS;
}

HI_CHAR * HI_UDISK_GetRoot(HI_VOID)
{
    return m_UDisk_Root;
}

HI_S32 HI_UDISK_GetDiskNum(HI_U32 * pu32DiskNum)
{
    HI_U32 u32DiskNum = 0;
    struct list_head * pos;

    UDISK_Lock();
    list_for_each(pos, &m_UDisk_DiskListHead)
    {
        u32DiskNum++;
    }
    UDISK_UnLock();

    *pu32DiskNum = u32DiskNum;
    return HI_SUCCESS;
}

HI_S32 HI_UDISK_GetDiskInfo(HI_U32 u32DiskIndex, HI_UDISK_DISKINFO_S * pDiskInfo)
{
    HI_U32 disk_index = 0;
    UDISK_DiskNode_S * pos_disk;
    UDISK_PartNode_S * pos_part;
    HI_U64 u64TotalSize = 0;
    HI_U64 u64AvailSize = 0;

    UDISK_Lock();
	

    list_for_each_entry(pos_disk, &m_UDisk_DiskListHead, disk_node)
    {
		printf("555555555555555555555555555555 the diskindex = %d\n",u32DiskIndex);
        if(++disk_index == u32DiskIndex)
        {
            list_for_each_entry(pos_part, &(pos_disk->part_list_head), part_node)
            {
                u64TotalSize += pos_part->PartInfo.u64TotalSize;
                u64AvailSize += pos_part->PartInfo.u64AvailSize;
            }
            // disk found!
            memcpy(pDiskInfo, &pos_disk->DiskInfo, sizeof(HI_UDISK_DISKINFO_S));
            pDiskInfo->u64TotalSize = u64TotalSize;
            pDiskInfo->u64AvailSize = u64AvailSize;
            UDISK_UnLock();
            return HI_SUCCESS;
        }
    }

    // disk not exist!
    UDISK_UnLock();
    return HI_FAILURE;
}

HI_S32 HI_UDISK_GetPartitionNum(HI_U32 u32DiskIndex, HI_U32 * pu32PartitionNum)
{
    HI_U32 disk_index, part_index;
    UDISK_DiskNode_S * pDiskNode;
    HI_UDISK_DISKINFO_S * pDiskInfo = HI_NULL;;
    struct list_head * tmp;

    UDISK_Lock();

    // 找disk
    disk_index = 0;
    list_for_each_entry(pDiskNode, &m_UDisk_DiskListHead, disk_node)
    {
        if(++disk_index == u32DiskIndex)
        {
            pDiskInfo = &(pDiskNode->DiskInfo);
            break;
        }
    }

    if(pDiskInfo == HI_NULL)
    {
        // disk not exist!
        UDISK_UnLock();
        return HI_UDISK_ERR_NOTEXIST;
    }

    // disk found
    part_index = 0;
    list_for_each(tmp, &(pDiskNode->part_list_head))
    {
        part_index++;
    }

    *pu32PartitionNum = part_index;

    UDISK_UnLock();
    return HI_SUCCESS;
}

HI_S32 HI_UDISK_GetPartitionInfo(HI_U32 u32DiskIndex, HI_U32 u32PartitionIndex, HI_UDISK_PARTITIONINFO_S * pPartitionInfo)
{
    HI_U32 disk_index, part_index;
    UDISK_DiskNode_S * pDiskNode;
    HI_UDISK_DISKINFO_S * pDiskInfo = HI_NULL;;
    UDISK_PartNode_S * pPartNode;

    UDISK_Lock();

    // 找disk
    disk_index = 0;
    list_for_each_entry(pDiskNode, &m_UDisk_DiskListHead, disk_node)
    {
        if(++disk_index == u32DiskIndex)
        {
            pDiskInfo = &(pDiskNode->DiskInfo);
            break;
        }
    }

    if(pDiskInfo == HI_NULL)
    {
        // disk not exist!
        UDISK_UnLock();
        return HI_UDISK_ERR_NOTEXIST;
    }

    // disk found
    part_index = 0;
    list_for_each_entry(pPartNode, &(pDiskNode->part_list_head), part_node)
    {
        if(part_index++ == u32PartitionIndex)
        {
            // partition found
            memcpy(pPartitionInfo, &pPartNode->PartInfo, sizeof(HI_UDISK_PARTITIONINFO_S));
            UDISK_StatFs(pPartitionInfo->szMntPath, &pPartitionInfo->u64TotalSize, &pPartitionInfo->u64AvailSize);
            UDISK_UnLock();
            return HI_SUCCESS;
        }
    }

    // partition not exist!
    UDISK_UnLock();
    return HI_FAILURE;
}

HI_S32 HI_UDISK_FormatPartition(HI_U32 u32DiskIndex, HI_U32 u32PartitionIndex, HI_UDISK_FSTYPE_E enFSType)
{
    HI_UDISK_PARTITIONINFO_S PartInfo;

    if(HI_UDISK_GetPartitionInfo(u32DiskIndex, u32PartitionIndex, &PartInfo) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    // TODO: 调用系统函数进行格式化

    printf("%s not support now!\n", __FUNCTION__);
    return HI_FAILURE;
}

/* filelist是动态生成的，不需要加锁 */
HI_S32 HI_UDISK_GetFileList(
            HI_CHAR *pszDir,
            HI_UDISK_SCAN_S * pScanOpt,
            HI_UDISK_FILELIST_S * pFileList)
{
    HI_S32 ret;

    if( (pszDir == HI_NULL)
      ||(pScanOpt == HI_NULL)
      ||(pFileList == HI_NULL) )
    {
        return HI_UDISK_ERR_NULL;
    }

    // 一次性分配10240个文件节点。
    // 后续改为在realloc方式。
    pFileList->ppFileList = malloc(sizeof(HI_UDISK_FILEINFO_S *) * 10240);
    bzero(pFileList->ppFileList, sizeof(HI_UDISK_FILEINFO_S *) * 10240);
    pFileList->u32FileNum = 0;

    ret = UDISK_ScanDir(pszDir, pScanOpt, pFileList);

    if(ret != HI_SUCCESS)
    {
        HI_UDISK_FreeFileList(pFileList);
    }

    return ret;
}

HI_S32 HI_UDISK_FreeFileList(HI_UDISK_FILELIST_S * pFileList)
{
    HI_U32 i;

    for(i=0; i<pFileList->u32FileNum; i++)
    {
        free(pFileList->ppFileList[i]);
        pFileList->ppFileList[i] = NULL;
    }

    free(pFileList->ppFileList);
    pFileList->ppFileList = NULL;

    pFileList->u32FileNum = 0;

    return HI_SUCCESS;
}

HI_S32 HI_UDISK_RegisterEventCallback(
        HI_UDISK_EVENT_E enEvent,
        HI_UDISK_EVENT_CALLBACK pCallbackFunc,
        HI_VOID * pPrivate)
{
    if(enEvent >= HI_UDISK_EVENT_BUTT)
    {
        return HI_UDISK_ERR_INVALIDPARA;
    }

    UDISK_Lock();
    m_UDisk_Event.cb[enEvent] = pCallbackFunc;
    m_UDisk_Event.pPrivate[enEvent] = pPrivate;
    UDISK_UnLock();

    return HI_SUCCESS;
}

HI_S32 HI_UDISK_UnRegisterEventCallback(HI_UDISK_EVENT_E enEvent)
{
    if(enEvent >= HI_UDISK_EVENT_BUTT)
    {
        return HI_UDISK_ERR_INVALIDPARA;
    }

    UDISK_Lock();
    m_UDisk_Event.cb[enEvent] = HI_NULL;
    m_UDisk_Event.pPrivate[enEvent] = HI_NULL;
    UDISK_UnLock();

    return HI_SUCCESS;
}

HI_S32 HI_UDISK_SetFullReport(HI_U32 u32DiskIndex, HI_U32 u32PartitionIndex, HI_BOOL bReport, HI_U64 u64WaterLine)
{
    HI_U32 disk_index, part_index;
    UDISK_DiskNode_S * pDiskNode;
    HI_UDISK_DISKINFO_S * pDiskInfo = HI_NULL;;
    UDISK_PartNode_S * pPartNode;

    UDISK_Lock();

    // 找disk
    disk_index = 0;
    list_for_each_entry(pDiskNode, &m_UDisk_DiskListHead, disk_node)
    {
        if(disk_index++ == u32DiskIndex)
        {
            pDiskInfo = &(pDiskNode->DiskInfo);
            break;
        }
    }

    if(pDiskInfo == HI_NULL)
    {
        // disk not exist!
        UDISK_UnLock();
        return HI_FAILURE;
    }

    // disk found, 找partition
    part_index = 0;
    list_for_each_entry(pPartNode, &(pDiskNode->part_list_head), part_node)
    {
        if(part_index++ == u32PartitionIndex)
        {
            // partition found
            pPartNode->bFullReport = bReport;
            pPartNode->u64WaterLine = u64WaterLine;

            UDISK_UnLock();
            return HI_SUCCESS;
        }
    }

    // partition not exist!
    UDISK_UnLock();
    return HI_FAILURE;
}

HI_VOID HI_UDISK_VfatParaSet(HI_BOOL bLinuxVfatType)
{
    if(bLinuxVfatType == HI_FALSE)
    {
        strcpy(aszVfatPara, "iocharset=cp936,codepage=936");
    }
    else
    {
        strcpy(aszVfatPara, "codepage=936");
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

