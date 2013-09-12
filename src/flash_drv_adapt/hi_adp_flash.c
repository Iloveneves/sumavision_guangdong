
#ifndef _EMLUATOR_PC

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "hi_debug.h"
#include "nand_raw.h"
#include "hi_adp_flash.h"

static HI_Flash_InterInfo_S gFlashInfo[MAX_HANDLE];
static HI_Flash_PartInfo_S gPartInfo[MAX_PARTS];
static HI_BOOL gInitFlag = HI_FALSE;
static pthread_mutex_t gFlashMutex;

#define CHECK_FLASH_INIT(hFlash) \
    do \
    { \
        if (!gInitFlag) \
        { \
            HI_ERR_FLASH("NOT init yet!\n"); \
            return HI_FAILURE; \
        } \
        if (INVALID_FD == gFlashInfo[hFlash].fd) \
        { \
            return HI_FAILURE; \
        } \
    } while (0)

#define CHECK_ADDR_LEN_VALID(Address, Len, LimitLeng) \
    do \
    { \
        if ((Address >= LimitLeng) || ((Address + Len) > LimitLeng)) \
        { \
            HI_ERR_FLASH("startaddr(0x%llX) + Len(0x%x) or startaddr should be smaller than partsize(0x%llX)\n", Address, Len, LimitLeng); \
            pthread_mutex_unlock(&gFlashMutex); \
            return HI_FAILURE; \
        } \
    } while (0)

static char* skip_space(char* line)
{
    char* p = line;
    while (*p == ' ' || *p == '\t')
    {
        p++;
    }
    return p;
}

static char* skip_word(char* line)
{
    char* p = line;
    while (*p != '\t' && *p != ' ' && *p != '\n' && *p != 0)
    {
        p++;
    }
    return p;
}

static char* get_word(char* line, char* value)
{
    char* p = line;
    p = skip_space(p);
    while (*p != '\t' && *p != ' ' && *p != '\n' && *p != 0)
    {
        *value++ = *p++;
    }
    *value = 0;
    return p;
}

static HI_S32 Flash_Init(HI_VOID)
{
	HI_CHAR line[512];	
	FILE* fp = HI_NULL;
	HI_U32 i = 0;
	HI_U64 u64StartAddr = 0;

	for(i=0; i< MAX_PARTS; i++)
	{
	    gPartInfo[i].StartAddr= 0; 
	    gPartInfo[i].PartSize= 0; 
	    gPartInfo[i].BlockSize = 0;
	    memset(gPartInfo[i].DevName, '\0', FLASH_NAME_LEN);
	    memset(gPartInfo[i].PartName, '\0', FLASH_NAME_LEN);
	}

	for(i=0; i< MAX_HANDLE; i++)
	{
	    gFlashInfo[i].fd = INVALID_FD;
	    gFlashInfo[i].OpenAddr = 0;
	    gFlashInfo[i].OpenLeng= 0;
        gFlashInfo[i].pPartInfo = NULL;   
	}

    fp = fopen("/proc/mtd", "r");
    if (fp)
 	{
 		fgets(line, sizeof(line), fp); //skip first line
		HI_INFO_FLASH(" DevName\t  PartSize\tBlockSize   PartName    Startaddr\n");

	    for(i=0; fgets(line, sizeof(line), fp) != 0; i++)
	    {
	        int  u32Success = 0;
			char argv[4][32];
			char *p;
			p = line;

		    p = skip_space(p);
		    p = skip_word(p);
            p = get_word(p, argv[1]);
            p = get_word(p, argv[2]);
            p = get_word(p, argv[3]);

			gPartInfo[i].PartSize = strtol(argv[1],NULL, 16); //partion size
			gPartInfo[i].BlockSize = strtol(argv[2], NULL,16); //erase size
	        strncpy(gPartInfo[i].PartName, (argv[3]+1), (strlen(argv[3])-2));
			sprintf(gPartInfo[i].DevName, "/dev/mtd%d", i);

            u64StartAddr = nand_raw_get_start_addr(gPartInfo[i].DevName, gPartInfo[i].BlockSize, &u32Success);
            if (!u32Success)
            {
                HI_ERR_FLASH("get \"%s\" startaddr fail!!!!!!\n", gPartInfo[i].DevName);
                //return HI_FAILURE;
            }
            gPartInfo[i].StartAddr = u64StartAddr;
			
			HI_INFO_FLASH(" %s,  0x%llx,\t0x%x,    %s,\t0x%llx\n", gPartInfo[i].DevName, gPartInfo[i].PartSize, \
			    gPartInfo[i].BlockSize, gPartInfo[i].PartName, gPartInfo[i].StartAddr);
	    }
    }
    else
    {
        HI_ERR_FLASH("open /proc/mtd file failure!\n");
		return HI_FAILURE;
    }

    if (fclose(fp))
    {
        return HI_FAILURE;
    }
	return HI_SUCCESS;
}

HI_HANDLE HI_Flash_Open(HI_FLASH_TYPE_E enFlashType, HI_CHAR *pPartitionName, HI_U64 u64Address, HI_U64 u64Len)
{
    HI_CHAR DevName[FLASH_NAME_LEN] = {0};
    HI_U32  hPart = 0;
	HI_U32  hFlash = 0;
	HI_U32  i;
	HI_S32  fd = INVALID_FD;
	HI_U64  TotalSize = 0;
    HI_U32  PageSize = 0;
    HI_U32  BlockSize = 0;
    HI_U32  OobSize = 0;
    HI_U32  BlockShift = 0;

	HI_INFO_FLASH("FlashType=%d, PartitionName=%s, Address=0x%llx, Len=0x%llx\n", enFlashType, pPartitionName, u64Address, u64Len);
	
    if (!gInitFlag)
    {
        gInitFlag = HI_TRUE;
        pthread_mutex_init(&gFlashMutex, NULL); 
        
        if (nand_raw_init() || Flash_Init())
        {
            gInitFlag = HI_FALSE;    
            return INVALID_FD;
        }
    }
    
    pthread_mutex_lock(&gFlashMutex);
    
    if (pPartitionName == NULL)
    {
        nand_raw_get_info((unsigned long long *)&TotalSize, (unsigned long *)&PageSize, (unsigned long *)&BlockSize, 
            (unsigned long *)&OobSize, (unsigned long *)&BlockShift);
        if ((int)(u64Address % BlockSize) || (int)(u64Len % BlockSize))
        {
            HI_ERR_FLASH("Open Address(%#llx) and Len(%#llx) should be align with BlockSize(0x%lX)!\n", u64Address, u64Len, BlockSize);
            pthread_mutex_unlock(&gFlashMutex);
            return INVALID_FD;
        } 
        
        for(i=0; i<MAX_HANDLE; i++) //find one address in array(gFlashInfo)
    	{
            if(INVALID_FD == gFlashInfo[i].fd)
    		{
    			break;
    		}	
    	}   
    	if (MAX_HANDLE == i)
    	{
            HI_ERR_FLASH("flash array full!\n");
            pthread_mutex_unlock(&gFlashMutex);
            return INVALID_FD;
    	}
    	hFlash = i;          	

        gFlashInfo[hFlash].fd = SPAN_PART_HANDLE + i;
        gFlashInfo[hFlash].OpenAddr = u64Address;
        gFlashInfo[hFlash].OpenLeng= u64Len;
        gFlashInfo[hFlash].pPartInfo = NULL;
        HI_INFO_FLASH("fd = %d\n", gFlashInfo[hFlash].fd); 
        HI_INFO_FLASH("end.\n");
        pthread_mutex_unlock(&gFlashMutex);
        
        return hFlash;
    }
    else
    {
        for(i=0; i<MAX_PARTS; i++) 
    	{
    	    if(!strcmp(gPartInfo[i].DevName, pPartitionName)) //eg: "/dev/mtd* "
    	    {
                break;
    	    }
    		if(!strcmp(gPartInfo[i].PartName, pPartitionName))
    		{
    			break;
    		}		
    	}    	
    	if (MAX_PARTS == i)
        {
            HI_ERR_FLASH("can not find a right flash part!\n");
            pthread_mutex_unlock(&gFlashMutex);
            return INVALID_FD;
        }
        strcpy(DevName, gPartInfo[i].DevName);
        hPart = i;
        
		for(i=0; i<MAX_HANDLE; i++) //find one address in array(gFlashInfo)
    	{
            if(INVALID_FD == gFlashInfo[i].fd)
    		{
    			break;
    		}	
    	}   
    	if (MAX_HANDLE == i)
    	{
            HI_ERR_FLASH("flash array full!\n");
            pthread_mutex_unlock(&gFlashMutex);
            return INVALID_FD;
    	}        	
        hFlash = i;
                                    
        for(i=0; i<MAX_HANDLE; i++) // if the partition open, return index of array(gFlashInfo)
    	{
    	    if((HI_NULL != gFlashInfo[i].pPartInfo) && (!strcmp(gFlashInfo[i].pPartInfo->DevName, DevName)))
    		{
    		    if (INVALID_FD != gFlashInfo[i].fd)
    		    {
    		        HI_INFO_FLASH("fd = %d, DevName =\"%s\"(%s)\n", gFlashInfo[i].fd, gFlashInfo[i].pPartInfo->DevName, gFlashInfo[i].pPartInfo->PartName);
                    pthread_mutex_unlock(&gFlashMutex);
    		        return i;
    		    }	
    		}	
    	}

    	fd = open(DevName, O_RDWR);
    	if((fd < 0) || (fd >= SPAN_PART_HANDLE))
    	{
    		HI_ERR_FLASH("Open %s flash partition failure!\n", DevName);
    		pthread_mutex_unlock(&gFlashMutex);
    		return INVALID_FD;
    	}
        gFlashInfo[hFlash].fd = fd;
        //gFlashInfo[hFlash].OpenAddr = 0;
        gFlashInfo[hFlash].OpenLeng= 0;
        gFlashInfo[hFlash].pPartInfo = &gPartInfo[hPart];
        gFlashInfo[hFlash].OpenAddr = gFlashInfo[hFlash].pPartInfo->StartAddr;
        HI_INFO_FLASH("fd = %d, DevName =\"%s\"(%s)\n", gFlashInfo[hFlash].fd, gFlashInfo[hFlash].pPartInfo->DevName, gFlashInfo[hFlash].pPartInfo->PartName);           
    }

    HI_INFO_FLASH("end.\n");
    pthread_mutex_unlock(&gFlashMutex);
    return hFlash;
}


HI_S32 HI_Flash_Close(HI_HANDLE hFlash)
{
    HI_Flash_PartInfo_S *pPartInfo;
    pPartInfo = gFlashInfo[hFlash].pPartInfo;
    HI_U32 i;
    HI_S32 ret;

    CHECK_FLASH_INIT(hFlash);

    pthread_mutex_lock(&gFlashMutex);
    HI_INFO_FLASH("fd = %d\n", gFlashInfo[hFlash].fd);

    if (SPAN_PART_HANDLE <= gFlashInfo[hFlash].fd)
    {
        gFlashInfo[hFlash].fd = INVALID_FD;
        gFlashInfo[hFlash].OpenAddr = 0;
        gFlashInfo[hFlash].OpenLeng= 0;
        gFlashInfo[hFlash].pPartInfo = NULL;
    }
    else
    {
        ret = close(gFlashInfo[hFlash].fd);
        if(0 != ret)
        {
            HI_ERR_FLASH("Close %s flash partition failure %d!\n", gFlashInfo[hFlash].pPartInfo->DevName, ret);
            pthread_mutex_unlock(&gFlashMutex);
            return HI_FAILURE;
        }
        gFlashInfo[hFlash].fd = INVALID_FD;
        gFlashInfo[hFlash].OpenAddr = 0;
        gFlashInfo[hFlash].OpenLeng= 0;
        gFlashInfo[hFlash].pPartInfo = NULL;
    }
    
    for(i=0; i< MAX_HANDLE; i++)
	{
	    if (INVALID_FD != gFlashInfo[i].fd)
	    {
            break;
	    }           
	}
	
	if (MAX_HANDLE == i)
	{
        nand_raw_destroy();
        gInitFlag = HI_FALSE;
	}

	HI_INFO_FLASH("end.\n");
	pthread_mutex_unlock(&gFlashMutex);
	
    return HI_SUCCESS;
}

HI_S32 HI_Flash_Erase(HI_HANDLE hFlash, HI_U64 u64Address, HI_U64 u64Len)
{
    HI_U64 StartAddr = 0;
    HI_U64 LimitLeng = 0;
    
    HI_U64 TotalSize = 0;
    HI_U32 PageSize = 0;
    HI_U32 BlockSize = 0;
    HI_U32 OobSize = 0;
    HI_U32 BlockShift = 0;
    int index = 0;   
    HI_S32 ret;

    CHECK_FLASH_INIT(hFlash);
    
    pthread_mutex_lock(&gFlashMutex);

    if (SPAN_PART_HANDLE <= gFlashInfo[hFlash].fd)
    {
        StartAddr = gFlashInfo[hFlash].OpenAddr;
        LimitLeng = gFlashInfo[hFlash].OpenLeng;
    }
    else
    {
        StartAddr = gFlashInfo[hFlash].pPartInfo->StartAddr;
        LimitLeng = gFlashInfo[hFlash].pPartInfo->PartSize;
    }
    CHECK_ADDR_LEN_VALID(u64Address, u64Len, LimitLeng);

    nand_raw_get_info((unsigned long long *)&TotalSize, (unsigned long *)&PageSize, (unsigned long *)&BlockSize, 
        (unsigned long *)&OobSize, (unsigned long *)&BlockShift);
    index = (int)(u64Address >> BlockShift);
    ret = nand_raw_get_physical_index(StartAddr, &index, BlockSize); 
    if (0 != ret)
    {
        printf("logical addr change to physical addr error!\n");
        pthread_mutex_unlock(&gFlashMutex);    
        return ret;
    }
    StartAddr += (unsigned long long)(index << BlockShift);
    StartAddr += (u64Address % BlockSize);
    
    HI_INFO_FLASH("HANDLE=%d, Address=0x%llx, Len=0x%llx\n", hFlash, StartAddr, u64Len); 
    
    ret = nand_raw_erase(gFlashInfo[hFlash].fd, (unsigned long long)StartAddr, u64Len, gFlashInfo[hFlash].OpenAddr, LimitLeng);
    HI_INFO_FLASH("end.\n");
    pthread_mutex_unlock(&gFlashMutex);
    
    return ret;
}

HI_S32 HI_Flash_Read(HI_HANDLE hFlash, HI_U64 u64Address, HI_U8 *pBuf, HI_U32 u32Len, HI_U32 u32Flags)
{
    HI_U64 StartAddr = 0;
    HI_U64 LimitLeng = 0;

    HI_U64 TotalSize = 0;
    HI_U32 PageSize = 0;
    HI_U32 BlockSize = 0;
    HI_U32 OobSize = 0;
    HI_U32 BlockShift = 0;
    int index = 0; 
    
    HI_S32 ret, wtihoob;
    
    CHECK_FLASH_INIT(hFlash);
    if (NULL == pBuf)
    {
        return HI_FAILURE;
    }

    pthread_mutex_lock(&gFlashMutex);

    if (SPAN_PART_HANDLE <= gFlashInfo[hFlash].fd)
    {
        StartAddr = gFlashInfo[hFlash].OpenAddr;
        LimitLeng = gFlashInfo[hFlash].OpenLeng;        
    }
    else
    {
        StartAddr = gFlashInfo[hFlash].pPartInfo->StartAddr;        
        LimitLeng = gFlashInfo[hFlash].pPartInfo->PartSize;
    }
    CHECK_ADDR_LEN_VALID(u64Address, u32Len, LimitLeng);

    nand_raw_get_info((unsigned long long *)&TotalSize, (unsigned long *)&PageSize, (unsigned long *)&BlockSize, 
        (unsigned long *)&OobSize, (unsigned long *)&BlockShift);
    index = (int)(u64Address >> BlockShift);
    ret = nand_raw_get_physical_index(StartAddr, &index, BlockSize); 
    if (0 != ret)
    {
        printf("logical addr change to physical addr error!\n");
        pthread_mutex_unlock(&gFlashMutex);    
        return ret;
    }
    StartAddr += (unsigned long long)(index << BlockShift);
    StartAddr += (u64Address % BlockSize);
    
    HI_INFO_FLASH("HANDLE=%d, Address=0x%llx, Len=0x%x, Flag=%d\n", hFlash, StartAddr, u32Len, u32Flags);

    if (HI_FLASH_RW_FLAG_WITH_OOB == (u32Flags & HI_FLASH_RW_FLAG_WITH_OOB))
    {
        wtihoob = 1;
    }
    else
    {
        wtihoob = 0;
    }
    
    ret = nand_raw_read(gFlashInfo[hFlash].fd, (unsigned long long *)&StartAddr, pBuf, u32Len, gFlashInfo[hFlash].OpenAddr, LimitLeng, wtihoob, 1);
    HI_INFO_FLASH("totalread =0x%x, end.\n", ret);
    pthread_mutex_unlock(&gFlashMutex);
    
    return ret;    
}


HI_S32 HI_Flash_Write(HI_HANDLE hFlash, HI_U64 u64Address, HI_U8 *pBuf, HI_U32 u32Len, HI_U32 u32Flags)
{
    HI_U64 StartAddr = 0;
    HI_U64 LimitLeng = 0;
    HI_S32 ret, wtihoob, erase;
    
    HI_U64 TotalSize = 0;
    HI_U32 PageSize = 0;
    HI_U32 BlockSize = 0;
    HI_U32 OobSize = 0;
    HI_U32 BlockShift = 0;
    int index = 0;
    
    HI_U32 u32EraseLen = 0;
    HI_U32 BlockSize_new = 0;    

    CHECK_FLASH_INIT(hFlash);
    if (NULL == pBuf)
    {
        return HI_FAILURE;
    }

    pthread_mutex_lock(&gFlashMutex);  

    if (SPAN_PART_HANDLE <= gFlashInfo[hFlash].fd)
    {
        StartAddr = gFlashInfo[hFlash].OpenAddr;
        LimitLeng = gFlashInfo[hFlash].OpenLeng;
    }
    else
    {
        StartAddr = gFlashInfo[hFlash].pPartInfo->StartAddr;
        LimitLeng = gFlashInfo[hFlash].pPartInfo->PartSize;
    }
    CHECK_ADDR_LEN_VALID(u64Address, u32Len, LimitLeng);

    nand_raw_get_info((unsigned long long *)&TotalSize, (unsigned long *)&PageSize, (unsigned long *)&BlockSize, 
        (unsigned long *)&OobSize, (unsigned long *)&BlockShift);
    index = (int)(u64Address >> BlockShift);
    ret = nand_raw_get_physical_index(StartAddr, &index, BlockSize); 
    if (0 != ret)
    {
        printf("logical addr change to physical addr error!\n");
        pthread_mutex_unlock(&gFlashMutex);    
        return ret;
    }
    StartAddr += (unsigned long long)(index << BlockShift);
    StartAddr += (u64Address % BlockSize);
    HI_INFO_FLASH("HANDLE=%d, Address=0x%llx, Len=0x%x, Flag=%d\n", hFlash, StartAddr, u32Len, u32Flags);

    if (HI_FLASH_RW_FLAG_ERASE_FIRST == (u32Flags & HI_FLASH_RW_FLAG_ERASE_FIRST))
    {
        erase = 1;
    }
    else
    {
        erase = 0;
    }
    
    if (HI_FLASH_RW_FLAG_WITH_OOB == (u32Flags & HI_FLASH_RW_FLAG_WITH_OOB))
    {
        BlockSize_new = BlockSize + OobSize * (BlockSize / PageSize);
        wtihoob = 1;
    }
    else
    {
        BlockSize_new = BlockSize;
        wtihoob = 0;
    }

    if (erase)
    {
        u32EraseLen = u32Len / BlockSize_new;
        if (u32Len % BlockSize_new)
        {
            u32EraseLen += 1;
        }
        u32EraseLen = u32EraseLen * BlockSize;
        //printf("> %s: [%d], u32EraseLen=%#x\n", __FUNCTION__, __LINE__, u32EraseLen);
        
        ret = nand_raw_erase(gFlashInfo[hFlash].fd, (unsigned long long)StartAddr, (unsigned long long)u32EraseLen, gFlashInfo[hFlash].OpenAddr, LimitLeng);
        if (HI_SUCCESS != ret)
        {
            if (HI_FLASH_END_DUETO_BADBLOCK != ret)
            {
                HI_ERR_FLASH("earse fail!\n");
                return ret;
            }
        }
    }
 
    ret = nand_raw_write(gFlashInfo[hFlash].fd, (unsigned long long *)&StartAddr, pBuf, u32Len, gFlashInfo[hFlash].OpenAddr, LimitLeng, wtihoob);
    HI_INFO_FLASH("totalwrite =0x%x, end.\n", ret);
    pthread_mutex_unlock(&gFlashMutex);
    
    return ret;    
}

HI_S32 HI_Flash_GetInfo(HI_HANDLE hFlash, HI_Flash_InterInfo_S *pFlashInfo)
{
    HI_U64 TotalSize = 0;
    HI_U32 PageSize = 0;
    HI_U32 BlockSize = 0;
    HI_U32 OobSize = 0;
    HI_U32 BlockShift = 0;

    CHECK_FLASH_INIT(hFlash);
    if(NULL == pFlashInfo)
    {
        return HI_FAILURE;
    }

    nand_raw_get_info((unsigned long long *)&TotalSize, (unsigned long *)&PageSize, (unsigned long *)&BlockSize, 
    (unsigned long *)&OobSize, (unsigned long *)&BlockShift);
    pFlashInfo->TotalSize = TotalSize;
    
    if (SPAN_PART_HANDLE <= gFlashInfo[hFlash].fd)
    {
        pFlashInfo->PartSize = gFlashInfo[hFlash].OpenLeng;
    }
    else
    {
        pFlashInfo->PartSize = gFlashInfo[hFlash].pPartInfo->PartSize;
    }
    pFlashInfo->BlockSize = BlockSize;
    pFlashInfo->PageSize  = PageSize;
    pFlashInfo->OobSize   = OobSize;
    pFlashInfo->fd = gFlashInfo[hFlash].fd;
    
	return HI_SUCCESS;
}


int flash_init()
{
    if (!gInitFlag)
    {
        gInitFlag = HI_TRUE;
        pthread_mutex_init(&gFlashMutex, NULL); 
        
        if (nand_raw_init() || Flash_Init())
        {
            gInitFlag = HI_FALSE;    
            return HI_FAILURE;
        }
    }

	return HI_SUCCESS;
}


void flash_exit()
{
	pthread_mutex_lock(&gFlashMutex);
	nand_raw_destroy();
	pthread_mutex_unlock(&gFlashMutex);
	pthread_mutex_destroy(&gFlashMutex);
	gInitFlag = HI_FALSE;
}


int flash_erase(unsigned int uAddr, unsigned int uSize)
{
	HI_U64 u64Addr = uAddr;
	HI_U64 u64Len = uSize;
	HI_HANDLE fd = INVALID_FD;
	HI_S32 ret;
	int i;

//	printf("flash erase: %0#x, %0#x\r\n", uAddr, uSize);

	for( i = 0; i < MAX_PARTS; i++ )
	{
		if( u64Addr >= gPartInfo[i].StartAddr &&
			u64Addr < gPartInfo[i].StartAddr + gPartInfo[i].PartSize )
		{
			u64Addr -= gPartInfo[i].StartAddr;
			break;
		}
	}

	if( i >= MAX_PARTS )
	{
		printf("flash erase: i = %d\r\n", i);
		return HI_FAILURE;
	}

	fd = HI_Flash_Open(HI_FLASH_TYPE_NAND_0, gPartInfo[i].DevName, u64Addr, u64Len);
	if( INVALID_FD == fd )
	{
		printf("flash erase: open failed.\r\n");
		return HI_FAILURE;
	}

	ret = HI_Flash_Erase(fd, u64Addr, u64Len);
	if( HI_SUCCESS != ret && HI_FLASH_END_DUETO_BADBLOCK != ret )
	{
		printf("flash erase: erase failed.\r\n");
//		HI_Flash_Close(fd);
//		return HI_FAILURE;
	}

	ret = HI_Flash_Close(fd);
	if( HI_SUCCESS != ret )
	{
		printf("flash erase: close failed.\r\n");
		return HI_FAILURE;
	}

//	printf("flash erase: success.\r\n");

	return HI_SUCCESS;
}


int flash_read(unsigned int addr, char *buf, unsigned int size )
{
	HI_U64 u64Addr = addr;
	HI_U64 u64Len = size;
	HI_HANDLE fd = INVALID_FD;
	HI_S32 ret;
	int len = 0;
	int i;

	printf("flash read : %0#x, %0#x\r\n", addr, size);
	
	for( i = 0; i < MAX_PARTS; i++ )
	{
		if( u64Addr >= gPartInfo[i].StartAddr &&
			u64Addr < gPartInfo[i].StartAddr + gPartInfo[i].PartSize )
		{
			u64Addr -= gPartInfo[i].StartAddr;
			break;
		}
	}
	
	if( i >= MAX_PARTS )
	{
		printf("flash read : i = %d\r\n", i);
		return 0;
	}
	
	fd = HI_Flash_Open(HI_FLASH_TYPE_NAND_0, gPartInfo[i].DevName, u64Addr, u64Len);
	if( INVALID_FD == fd )
	{
		printf("flash read : open failed.\r\n");
		return HI_FAILURE;
	}

	ret = HI_Flash_Read(fd, u64Addr, (HI_U8*)buf, size, HI_FLASH_RW_FLAG_RAW);
	if( ret < 0 && HI_FLASH_END_DUETO_BADBLOCK != ret )
	{
		printf("flash read : read failed.\r\n");
//		HI_Flash_Close(fd);
//		return HI_FAILURE;
	}
	
	len = ret;

	ret = HI_Flash_Close(fd);
	if( HI_SUCCESS != ret )
	{
		printf("flash read : close failed.\r\n");
		return HI_FAILURE;
	}

	printf("flash read : success.\r\n");
	
	return len;
}


int flash_write(unsigned int addr, char *buf, unsigned int size )
{
	HI_U64 u64Addr = addr;
	HI_U64 u64Len = size;
	HI_HANDLE fd = INVALID_FD;
	HI_S32 ret;
	int len = 0;
	int i;
	
	printf("flash write: %0#x, %0#x, u64Addr: 0x%08x%08x\r\n", addr, size, (HI_U32)(u64Addr>>32), (HI_U32)u64Addr);
	for( i = 0; i < MAX_PARTS; i++ )
	{
		if( u64Addr >= gPartInfo[i].StartAddr &&
			u64Addr < gPartInfo[i].StartAddr + gPartInfo[i].PartSize )
		{
			u64Addr -= gPartInfo[i].StartAddr;
			break;
		}
	}
	
	if( i >= MAX_PARTS )
	{
		printf("flash write: i = %d\r\n", i);
		return 0;
	}
	
//	printf("name: %s, %08x%08x(%0#x), %08x%08x(%0#x)\r\n", gPartInfo[i].DevName, (HI_U32)(u64Addr>>32), (HI_U32)u64Addr, addr, (HI_U32)(u64Len>>32), (HI_U32)u64Len, size);
	fd = HI_Flash_Open(HI_FLASH_TYPE_NAND_0, gPartInfo[i].DevName, u64Addr, u64Len);
	if( INVALID_FD == fd )
	{
		printf("flash write: open failed.\r\n");
		return HI_FAILURE;
	}
	
	ret = HI_Flash_Write(fd, u64Addr, (HI_U8*)buf, size, HI_FLASH_RW_FLAG_RAW);
	if( ret < 0 && HI_FLASH_END_DUETO_BADBLOCK != ret )
	{
		printf("flash write: write failed.\r\n");
//		HI_Flash_Close(fd);
//		return HI_FAILURE;
	}
	
	len = ret;
	
	ret = HI_Flash_Close(fd);
	if( HI_SUCCESS != ret )
	{
		printf("flash write: close failed.\r\n");
		return HI_FAILURE;
	}
	
	printf("flash write: success.\r\n");
	return len;
}


int flash_write_ex(unsigned int addr, char *buf, unsigned int size )
{
	HI_U64 u64Addr = addr;
	HI_U64 u64Len = size;
	HI_HANDLE fd = INVALID_FD;
	HI_S32 ret;
	int len = 0;
	int i;
	
	printf("flash write: %0#x, %0#x\r\n", addr, size);
	for( i = 0; i < MAX_PARTS; i++ )
	{
		if( u64Addr >= gPartInfo[i].StartAddr &&
			u64Addr < gPartInfo[i].StartAddr + gPartInfo[i].PartSize )
		{
			u64Addr -= gPartInfo[i].StartAddr;
			break;
		}
	}
	
	if( i >= MAX_PARTS )
	{
		printf("flash write: i = %d\r\n", i);
		return 0;
	}
	
	fd = HI_Flash_Open(HI_FLASH_TYPE_NAND_0, gPartInfo[i].DevName, u64Addr, u64Len);
	if( INVALID_FD == fd )
	{
		printf("flash write: open failed.\r\n");
		return HI_FAILURE;
	}
	
	ret = HI_Flash_Write(fd, u64Addr, (HI_U8*)buf, size, HI_FLASH_RW_FLAG_WITH_OOB);
	if( ret < 0 && HI_FLASH_END_DUETO_BADBLOCK != ret )
	{
		printf("flash write: write failed.\r\n");
//		HI_Flash_Close(fd);
//		return HI_FAILURE;
	}
	
	len = ret;
	
	ret = HI_Flash_Close(fd);
	if( HI_SUCCESS != ret )
	{
		printf("flash write: close failed.\r\n");
		return HI_FAILURE;
	}
	
	printf("flash write: success.\r\n");
	return len;
}



#endif 
