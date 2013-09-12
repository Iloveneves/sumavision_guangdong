
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include <sys/vfs.h>
#include <linux/fs.h>
#include <mntent.h>
#include <semaphore.h>

#include "hi_type.h"
#include "hi_udisk.h"

#include "porter_rocme.h"


#define UDISK_MAX_STORAGE_NUM        (26-2)
#define UDISK_MAX_PARTITION_NUM        (26-2)
#define UDISK_INVALID_PARTITION_NAME   'A'

#define FOMAT_PREFIX "mkfs."
#define CHAR_SPACE " "
#define EXTOP " -q "

/******************struct***********************/
#if 0
typedef struct hiUDISK_STORAGE_INFO_T
{
    HI_BOOL bMounted;
    HI_U32 u32StorageNum;
    HI_U32 u32StorageName[64];	
} UDISK_STORAGE_INFO_S;
#endif
typedef struct
{
    HI_BOOL bUse;
    HI_U32 u32DiskNum;
    HI_U32 u32PartitionNum;	
    HI_CHAR szPartitionLogic;
	UINT32_T u32Start;
    HI_CHAR aszPartitionPath[MAX_UDISK_NAME_LEN];
} UDISK_PARTITION_INFO_S;

/*****************variable***********************/
static pthread_mutex_t s_partition_info_mutex;
static UDISK_PARTITION_INFO_S s_astPartition_info[UDISK_MAX_STORAGE_NUM];
static HI_U32 s_u32DiskCount = 0;
static HI_U32 nPartionNumber = 0;



/*****************function********************/
HI_S32 udisk_get_storagenum_by_name(HI_U8 *pStorageName, HI_U32 *pu32StorageNum)
{
    HI_U32 i = 0;
    


	if (strncmp(s_astPartition_info[i].aszPartitionPath, pStorageName, 64>sizeof(pStorageName)?sizeof(pStorageName):64) == 0)
	{
	    *pu32StorageNum = i+1;
	    return HI_SUCCESS;
	}
   


    return HI_FAILURE;
}

HI_VOID udisk_storage_mount()
{
	ROCME_TEST_PRINT
    HI_U32 j = 0;
    HI_S32 s32Ret = 0;
    HI_U32 u32DiskNum = 0;
    HI_U32 u32PartitionNum = 0;
    HI_UDISK_DISKINFO_S DiskInfo;
    

    s32Ret = HI_UDISK_GetDiskNum(&u32DiskNum);
    if (HI_SUCCESS != s32Ret) 
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"[udisk_storage_mount] udisk_storage_mount( T) failed! ret is %08x\r\n", s32Ret);
        u32DiskNum = 0;
    }

    s_u32DiskCount = u32DiskNum;
	printf("****************u32DiskNum is %d\r\n",u32DiskNum);
	for(j = 0; j < u32DiskNum; j++)
    {
        HI_UDISK_GetDiskInfo(j, &DiskInfo);
        {
            printf("%s\n", DiskInfo.szVendor);
            printf("%s\n", DiskInfo.szModel);
            printf("%s\n", DiskInfo.szDevPath);
            printf("%s\n", DiskInfo.szMntPath);
        }
        
        s_astPartition_info[j].bUse= HI_TRUE;
        s_astPartition_info[j].u32DiskNum= j;
        memset(s_astPartition_info[j].aszPartitionPath, 0, 64);
        //snprintf(s_astStorage_info[j].u32StorageName, 64, "udisk%d", j);
        snprintf(s_astPartition_info[j].aszPartitionPath, 64, DiskInfo.szMntPath);
        printf("%s\n", s_astPartition_info[j].aszPartitionPath);
        
    }
}

HI_VOID udisk_storage_info_init()
{
	HI_U32 i = 0;
	HI_U32 j = 0;
	HI_U32 k = 0;
	HI_S32 s32Ret = 0;
	HI_U32 u32DiskNum = 0;
	HI_U32 u32PartitionNum = 0;
	pthread_mutex_lock(&s_partition_info_mutex);
	
	for (i = 0; i < UDISK_MAX_PARTITION_NUM; i++)
	{
		s_astPartition_info[i].bUse = HI_FALSE;
		s_astPartition_info[i].szPartitionLogic = 'C'+i;
		memset(s_astPartition_info[i].aszPartitionPath, 0, UDISK_MAX_PARTITION_NUM);
		/*由于插拔不稳定，防止进入系统/root/__在初始化得时候将所有分区设成/tmp/disk/sda*/
		//memcpy(s_astPartition_info[i].aszPartitionPath,"/tmp/disk/sda",MAX_UDISK_NAME_LEN);
	}
	#if 0
	s32Ret = HI_UDISK_GetDiskNum(&u32DiskNum);
	printf("HI_UDISK_GetDiskNum %d\n",u32DiskNum);
	if (HI_SUCCESS != s32Ret) 
	{
		u32DiskNum = 0;
	}
	
	i=0;
	for(j=0;j<u32DiskNum;j++)
	{	
		s32Ret = HI_UDISK_GetPartitionNum(j+1, &u32PartitionNum);
		u32PartitionNum++;
		printf("HI_UDISK_GetPartitionNum %d____ret_value__%d\n",u32PartitionNum,s32Ret);
		if (HI_SUCCESS != s32Ret)
		{
			u32PartitionNum = 0;
		}
		if (0==u32PartitionNum)
		{
			char sys_cmd[128]="";
			printf("mount got here ________________....\n");
			sprintf(sys_cmd,"mount -v /dev/sda  /tmp/disk");
			system(sys_cmd);
			sleep(1);
			memcpy(s_astPartition_info[i].aszPartitionPath,"/tmp/disk",MAX_UDISK_NAME_LEN);
		}
		for(k=0;k<u32PartitionNum;k++) 
		{
			HI_UDISK_PARTITIONINFO_S PartitionInfo;
			if(i >= UDISK_MAX_PARTITION_NUM) 
			{
				break;
			}
			s32Ret = HI_UDISK_GetPartitionInfo(j, k, &PartitionInfo);
	//		printf("HI_UDISK_GetPartitionInfo___k_%d,___s32Ret__%d\n"
	//			   "HI_UDISK_GetPartitionInfo___PartitionInfo.enFSType_%d\n"
	//			,k,s32Ret,PartitionInfo.enFSType);
			if (HI_SUCCESS != s32Ret )//|| PartitionInfo.enFSType != HI_UDISK_FSTYPE_FAT32)
			{
				i++;
				continue;
			}
			s_astPartition_info[i].u32DiskNum = j+1;
			s_astPartition_info[i].u32PartitionNum= k+1;
			if(0 == i)
				s_astPartition_info[i].u32Start = 0;
			else 
				s_astPartition_info[i].u32Start =(UINT32_T)PartitionInfo.u64TotalSize/1024 + s_astPartition_info[i-1].u32Start + 10;
	//		printf("pstStorageInfo->start_________________%d___ii__%d\n",s_astPartition_info[i].u32Start,i);
			memcpy(s_astPartition_info[i].aszPartitionPath,PartitionInfo.szMntPath,MAX_UDISK_NAME_LEN);
			printf("[udisk_partition_info_init] %c:%d:%d:%s\n"		//HISI_DBG
					,s_astPartition_info[i].szPartitionLogic
					,s_astPartition_info[i].u32DiskNum
					,s_astPartition_info[i].u32PartitionNum
					,s_astPartition_info[i].aszPartitionPath);
			i++;
		}
	}
#endif
	pthread_mutex_unlock(&s_partition_info_mutex);

	return;
}


HI_VOID udisk_notify_callback(HI_UDISK_EVENT_E enEvent, HI_VOID * pParam, HI_VOID * pPrivate)
{

    //pthread_mutex_lock(&s_storage_info_mutex);

    switch (enEvent)
    {
        case HI_UDISK_EVENT_PLUGIN:
            udisk_storage_info_init();
            break;
        case HI_UDISK_EVENT_MOUNTED:
			udisk_storage_info_init();

            break;
        case HI_UDISK_EVENT_UMOUNTED:
			udisk_storage_info_init();

            break;
        case HI_UDISK_EVENT_PLUGOUT:
			udisk_storage_info_init();


            break;
        case HI_UDISK_EVENT_FULL:
			udisk_storage_info_init();
            break;
        default:
            break;
    }
    //pthread_mutex_unlock(&s_storage_info_mutex);

}


HI_S32 rocme_porting_udisk_init()
{
	ROCME_TEST_PRINT
		
    HI_U32 ret = HI_SUCCESS;

    pthread_mutex_init(&s_partition_info_mutex, NULL);

    HI_UDISK_VfatParaSet(HI_FALSE);
	system("umount  -f  /tmp/disk");	
	system(1);
    ret= HI_UDISK_Init("/tmp/disk");

    if (ret != HI_SUCCESS )
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_udisk_init] rocme_porting_udisk_init( T) failed! ret is %08x\r\n", ret);
        printf("HI_UDISK_Init fail \n");
        return ret;
    }
/*	
	char sys_cmd[128]="";
	sprintf(sys_cmd,"mount -v /dev/sda	/tmp/disk");
	system(sys_cmd);
	sleep(1);
*/
    udisk_storage_info_init();
    HI_UDISK_RegisterEventCallback(HI_UDISK_EVENT_PLUGIN,udisk_notify_callback,NULL);
    HI_UDISK_RegisterEventCallback(HI_UDISK_EVENT_PLUGOUT,udisk_notify_callback,NULL);
    HI_UDISK_RegisterEventCallback(HI_UDISK_EVENT_MOUNTED,udisk_notify_callback,NULL);
    HI_UDISK_RegisterEventCallback(HI_UDISK_EVENT_UMOUNTED,udisk_notify_callback,NULL);
    HI_UDISK_RegisterEventCallback(HI_UDISK_EVENT_FULL,udisk_notify_callback,NULL);

    return ret;
}

HI_S32 rocme_porting_udisk_deinit()
{
    HI_S32 s32Ret = 0;

    s32Ret = HI_UDISK_Deinit();
    udisk_storage_info_init();
    pthread_mutex_destroy(&s_partition_info_mutex);

    return s32Ret;
}

/*
功能: 获取存储设备的个数
参数：
	无
返回值：设备个数
备注：
*/
UINT32_T rocme_porting_get_storage_num(void)
{
	ROCME_TEST_PRINT
	HI_U32 num;
	HI_UDISK_GetDiskNum(&num);
	printf("the storage num = %d\n",num);
	return num;
}

/*
功能: 获取某个存储设备的分区个数
参数：
	storageName:  设备名称
返回值：该设备的分区个数
备注：
*/
UINT32_T rocme_porting_get_partition_num(CHAR_T* storageName)
{

ROCME_TEST_PRINT
	printf("the storagename =%s\n",storageName);
	
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32StorageNum = 0;
    HI_U32 u32PartitionNum = 0;
    HI_U32 i = 0;
    HI_U32 u32Return = 0;
    
    pthread_mutex_lock(&s_partition_info_mutex);
    do
    {
        s32Ret = udisk_get_storagenum_by_name(storageName, &u32StorageNum);
        if (HI_SUCCESS != s32Ret)
        {
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_get_partition_num] udisk_get_storagenum_by_name( T) failed! ret is %08x\r\n", s32Ret);
            u32Return = 0;
            break;
        }
        printf("the storagenum = %d\n",u32StorageNum);
        /*获取指定storagePartNum  的信息*/
        s32Ret = HI_UDISK_GetPartitionNum(u32StorageNum, &u32PartitionNum);
        if (HI_SUCCESS != s32Ret)
        {
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_get_partition_num] HI_UDISK_GetPartitionNum( T) failed! ret is %08x\r\n", s32Ret);
            u32Return = 0;
            break;
        }
		printf("the rocme_porting_get_partition_num = %d\n",u32PartitionNum);
        u32Return = u32PartitionNum;
    }while (0);
    
    pthread_mutex_unlock(&s_partition_info_mutex);
    return u32Return;	
}

/*
功能：获取存储设备的分区信息（名称、大小，空闲，访问路径、
分区类型），具体信息参见RocStorageInfo_t
参数：
    storagePartInfo，存储设备的分区信息结构体指针，用于获取存储设备的
    分区信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_storage_partition_infos(CHAR_T* storageName, 
	  												RocStoragePartitionInfo_t* storagePartInfo, 
	                                				UINT32_T* storagePartNum)
{
	ROCME_TEST_PRINT
		
    HI_U32 u32StorageNum = 0;
    HI_UDISK_PARTITIONINFO_S PartitionInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0;

    if ((storageName == NULL) || (storagePartInfo == NULL) || (storagePartNum == NULL))
    {
        return -1;
    }

    
    pthread_mutex_lock(&s_partition_info_mutex);
    do
    {
        s32Ret = udisk_get_storagenum_by_name(storageName, &u32StorageNum);
        if (HI_SUCCESS != s32Ret)
        {		
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_get_storage_partition_infos] udisk_get_storagenum_by_name( T) failed! ret is %08x\r\n", s32Ret);
            s32Ret = -1;
            break;
        }
      printf("[rocme_porting_get_storage_partition_infos]the storagePartNum =%d\n",*storagePartNum);
        /*获取指定storagePartNum  的信息*/
        s32Ret = HI_UDISK_GetPartitionInfo(u32StorageNum, *storagePartNum - 1, &PartitionInfo);
        if (HI_SUCCESS != s32Ret)
        {
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_get_storage_partition_infos] rocme_porting_get_storage_partition_infos( T) failed! ret is %08x\r\n", s32Ret);
            s32Ret = -1;
            break;
        }

        //if (PartitionInfo.bMounted)
        {
            //snprintf(storagePartInfo->name, 64, "%s", s_astStorage_info[i].u32StorageName, 'C'+*storagePartNum);
            snprintf(storagePartInfo->name, 64, "%s", PartitionInfo.szMntPath);
            printf("storagePartInfo->name: %s\n", storagePartInfo->name);
            storagePartInfo->size = PartitionInfo.u64TotalSize/1024/1024;
            storagePartInfo->freeSize = PartitionInfo.u64AvailSize/1024/1024;
            memcpy(storagePartInfo->path, PartitionInfo.szMntPath, 128);

            switch(PartitionInfo.enFSType)
            {
                case HI_UDISK_FSTYPE_FAT:
                    memcpy(storagePartInfo->fsType, "fat16", strlen("fat16")+1);
                    break;
                case HI_UDISK_FSTYPE_FAT32:
                    memcpy(storagePartInfo->fsType, "fat32", strlen("fat32")+1);
                    break;
                case HI_UDISK_FSTYPE_NTFS:
                    memcpy(storagePartInfo->fsType, "ntfs", strlen("ntfs")+1);
                    break;
                case HI_UDISK_FSTYPE_EXT2:
                    memcpy(storagePartInfo->fsType, "ext2", strlen("ext2")+1);
                    break;
                case HI_UDISK_FSTYPE_EXT3:
                    memcpy(storagePartInfo->fsType, "ext3", strlen("ext3")+1);
                    break;
                default:
                    memcpy(storagePartInfo->fsType, "ext3", strlen("ext3")+1);
                    break;

            }
        }
        s32Ret = 0;
    }while (0);
    
    pthread_mutex_unlock(&s_partition_info_mutex);
    return s32Ret;
}

/*
功能：获取存储设备信息(名称、大小，空闲，分区)，
                具体信息参见RocStorageInfo_t
参数：
    storageInfo，存储设备信息结构体指针，用于获取存储设备信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_storage_infos(RocStorageInfo_t* storageInfo, UINT32_T* storageNum)
{
	ROCME_TEST_PRINT

	HI_UDISK_DISKINFO_S DiskInfo;
    HI_UDISK_PARTITIONINFO_S PartitionInfo;
    HI_U32 u32PartitionNum = 0;
    HI_U32 u32Size = 0;
    HI_U32 u32FreeSize = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0;
    HI_U32 u32LocalStorageNum = 0;

    //STORAGE_PRINT("[rocme_porting_get_storage_infos]storageInfo = %x, storageNum = %d\n", storageInfo, *storageNum);
    if (storageNum == NULL)
    {
        return -1;
    }

    u32LocalStorageNum = *storageNum;
	printf("2222222222222,the storageNum =%d\n",u32LocalStorageNum);

    pthread_mutex_lock(&s_partition_info_mutex);
    
    do
    {
        memset(&DiskInfo, 0, sizeof(HI_UDISK_DISKINFO_S));
        memset(&PartitionInfo, 0, sizeof(HI_UDISK_PARTITIONINFO_S));
        s32Ret = HI_UDISK_GetDiskInfo(u32LocalStorageNum, &DiskInfo);
        if (HI_SUCCESS != s32Ret)
        {
			printf("3333333333333333\n");
            //pthread_mutex_unlock(&s_storage_info_mutex);
            s32Ret = -1;
            break;
        }
		
		
        s32Ret = HI_UDISK_GetPartitionNum(u32LocalStorageNum, &u32PartitionNum);
		
        if (HI_SUCCESS != s32Ret)
        {
            //pthread_mutex_unlock(&s_storage_info_mutex);
            printf("HI_UDISK_GetDiskInfo error");
            s32Ret = -1;
            break;
        }
        printf("the partion num = %d\n",u32PartitionNum); 
        for(i = 0; i < u32PartitionNum; i++)
        {
            HI_UDISK_GetPartitionInfo(u32LocalStorageNum, i, &PartitionInfo);
            u32Size += PartitionInfo.u64TotalSize;
            u32FreeSize += PartitionInfo.u64AvailSize;
        }
		
		memcpy(s_astPartition_info[u32LocalStorageNum-1].aszPartitionPath,PartitionInfo.szMntPath,MAX_UDISK_NAME_LEN);
		memcpy(storageInfo->name, 
                    s_astPartition_info[u32LocalStorageNum-1].aszPartitionPath, 
                    64>sizeof(s_astPartition_info[u32LocalStorageNum-1].aszPartitionPath)?sizeof(s_astPartition_info[u32LocalStorageNum-1].aszPartitionPath):64);

        storageInfo->size = u32Size/1024/1024;
        storageInfo->freeSize = u32FreeSize/1024/1024;
		printf("the usb size =%d,the usb free size =%d\n",storageInfo->size,storageInfo->freeSize);
        s32Ret = 0;
    }while (0);

    pthread_mutex_unlock(&s_partition_info_mutex);
    return s32Ret;
}



/*
功能：卸载设备
参数：storageName：字符串，设备名称
返回值：数值型，1表示卸载成功，0表示卸载失败
备注：
*/
INT32_T rocme_porting_uninstall_storage(CHAR_T* storageName)
{
	ROCME_TEST_PRINT

	HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0;
    HI_U32 u32StorageNum = 0;
    HI_U32 u32PartitionNum = 0;
    HI_UDISK_PARTITIONINFO_S PartitionInfo;
    HI_U8 au8Command[256] = {0};

    if (HI_NULL == storageName)
    {
       printf("storageName == NULL\n");
    }
        
    pthread_mutex_lock(&s_partition_info_mutex);

    do
    {
        s32Ret = udisk_get_storagenum_by_name(storageName, &u32StorageNum);
        if (HI_SUCCESS != s32Ret)
        {
            s32Ret = 0;
            break;
        }
      
        s32Ret = HI_UDISK_GetPartitionNum(u32StorageNum, &u32PartitionNum);
        if (HI_SUCCESS != s32Ret)
        {
            s32Ret = 0;
            break;
        }
        
        for(i = 0; i < u32PartitionNum; i++)
        {
            memset(&PartitionInfo, 0, sizeof(PartitionInfo));
            HI_UDISK_GetPartitionInfo(u32StorageNum, i,  &PartitionInfo);
            
            memset(au8Command, 0, sizeof(au8Command));
            sprintf(au8Command, "umount %s",PartitionInfo.szMntPath);
            //STORAGE_PRINT("[rocme_porting_uninstall_storage]Command = %s\n", au8Command);
            if (system(au8Command) < 0)
            {
                printf("umount failed\n");
            }
            else
            {
                s_astPartition_info[i].bUse= HI_FALSE;
                s_astPartition_info[i].u32DiskNum= i;
                memset(s_astPartition_info[i].aszPartitionPath, 0, 64);
            }
        }
        s32Ret = 1;
    }while (0);
    
    pthread_mutex_unlock(&s_partition_info_mutex);
    return s32Ret;
}


/*
功能：格式化设备
参数：storageName：字符串，设备名称
返回值：数值型，1表示格式化成功，0表示格式化失败
备注：
*/
INT32_T rocme_porting_format_storage(CHAR_T* storageName, RocStorageFSType_E eFormatType)
{
	ROCME_TEST_PRINT

	HI_U32 i = 0;
    HI_U32 u32StorageNum = 0;
    HI_U32 u32PartitionNum = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UDISK_FSTYPE_E enFSType = HI_UDISK_FSTYPE_BUT;
    HI_UDISK_PARTITIONINFO_S PartitionInfo;
    HI_U8 au8Command[256] = {0};
    HI_U8 au8Fstype[16] = {0};

    pthread_mutex_lock(&s_partition_info_mutex);

    do
    {    
        s32Ret = udisk_get_storagenum_by_name(storageName, &u32StorageNum);
        if (HI_SUCCESS != s32Ret)
        {
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_format_storage] rocme_porting_format_storage( T) failed! ret is %08x\r\n", s32Ret);
            s32Ret = 0;
            break;
        }
        
        /*获取指定storagePartNum  的信息*/
        s32Ret = HI_UDISK_GetPartitionNum(u32StorageNum, &u32PartitionNum);
        if (HI_SUCCESS != s32Ret)
        {
            s32Ret = 0;
            break;
        }

        memset(au8Fstype, 0, sizeof(au8Fstype));
        switch (eFormatType)
        {
            case EM_FS_VFAT:
    	      strcpy(au8Fstype, "vfat");
                break;
            case EM_FS_EXT2:
    	      strcpy(au8Fstype, "ext2");
                break;
            case EM_FS_EXT3:
    	      strcpy(au8Fstype, "ext3");
                break;
            case EM_FS_UNKOWN:
            default:
    	      strcpy(au8Fstype, "vfat");
                break;
        }

        for(i = 0; i < u32PartitionNum; i++)
        {
            memset(&PartitionInfo, 0, sizeof(PartitionInfo));
            HI_UDISK_GetPartitionInfo(u32StorageNum, i,  &PartitionInfo);
          //  STORAGE_PRINT("szMntPath:%s\n", PartitionInfo.szMntPath);
          //  STORAGE_PRINT("szDevPath:%s\n", PartitionInfo.szDevPath);
#if 1
            memset(au8Command, 0, sizeof(au8Command));
            sprintf(au8Command, "umount %s",PartitionInfo.szMntPath);
            //if (umount(PartitionInfo.szDevPath) < 0)
            if (system(au8Command) < 0)
            {
               // STORAGE_PRINT("umount failed\n");
                continue;
            }
#endif
            memset(au8Command, 0, sizeof(au8Command));
            switch (eFormatType)
            {
                case EM_FS_VFAT:
                        sprintf(au8Command, "%s%s%s%s", FOMAT_PREFIX, au8Fstype, CHAR_SPACE, PartitionInfo.szDevPath);
                        break;
                case EM_FS_EXT2:
                case EM_FS_EXT3:
            	       sprintf(au8Command, "%s%s%s%s%s", FOMAT_PREFIX, au8Fstype, CHAR_SPACE, PartitionInfo.szDevPath, EXTOP);
                        break;
                case EM_FS_UNKOWN:
                default:
                        sprintf(au8Command, "%s%s%s%s", FOMAT_PREFIX, au8Fstype, CHAR_SPACE, PartitionInfo.szDevPath);
                        break;
            }
           // STORAGE_PRINT("[rocme_porting_format_storage]Command = %s\n", au8Command);
            
            if (system(au8Command) < 0)
            {
                	//STORAGE_PRINT("format failed\n" );
            }
        }
        s32Ret = 1;
    }while (0);
    
    pthread_mutex_unlock(&s_partition_info_mutex);
    return s32Ret;
}

 

