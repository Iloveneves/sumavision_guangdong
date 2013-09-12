/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_errno.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <fcntl.h>

#include "hi_unf_ecs.h"//eeprom header
#include "hi_unf_disp.h"
#include "hi_type.h"

#include "flash_drv.h"

#include "porter_rocme.h"


#define POLYNOMIAL				0x04c11db7L
#define LOADER_INFO_BASIC_ADDR 		0x00200000
#define LOADER_INFO_BACKUP_ADDR 	0x00300000
/******************************************************************************
 *                                 局部变量                                   *
 ******************************************************************************/
static roc_stb_info_t* g_SystemInfo = NULL;
static LOADER_DB_INFO_S  g_StbLoaderInfo;
static unsigned long g_CRCTable[256];

static pthread_mutex_t  loader_mutex;
/******************************************************************************
 *                                 局部函数声明                               *
 ******************************************************************************/
static void
print_data( unsigned char* data, int len );

static int
convert_ascii( HI_U8* strAscii , HI_U64* u64Res , int len);

//static void
//print_descriptor( HZTY_Download_Descriptor_t  *pNIT );

static int
check_data(char* buff_1, char* buff_2, int test_len );

static void 
print_eeprom_data( roc_upd_info_t* eeprom_data );

static unsigned long
crc_32( char* buf, int len );

static 
void init_loader_mutex();

static void GenCrcTable();
/******************************************************************************
 *                                 全局函数声明                               *
 ******************************************************************************/
 
void get_system_info(roc_stb_info_t *pSystemInfo );
HI_S32 HI_LOADER_ReadLoaderInfo( LOADER_DB_INFO_S* info );
HI_S32 HI_LOADER_WriteLoaderInfo( LOADER_DB_INFO_S* info );
int WriteLoaderParam(roc_upd_info_t *param);

/*****************************************************************************
功能说明: 
    设置机顶盒信息

参数说明:
    输出参数:
        [info ] 机顶盒信息
        typedef struct roc_stb_info {
            UINT32_T swv; //软件版本号  
            UINT32_T hwv; //硬件版本号  
            UINT32_T serial; //机顶盒序列号
        }roc_stb_info_t;
        该信息在机顶盒出厂时应该保持到flash中，
        当loader升级成功后更新该信息

返    回:
    失败: 非0              
    成功:  0
*****************************************************************************/
UINT32_T rocme_porting_get_stbinfo( roc_stb_info_t *info )
{
	ROCME_TEST_PRINT
	 if (info == NULL)
    {
    	printf("sysInfo");
        return ROC_ERR;
    }

    get_system_info(info);

	return ROC_OK;
}


/*****************************************************************************
功能说明: 
    设置机顶盒升级信息

参数说明:
    输入参数:
        [info ] 机顶盒升级信息
        typedef struct roc_upd_info
        {
            UINT8_T  flag;         //升级标志 
            UINT16_T download_pid; //下载的pid
            UINT8_T  modulation;   //调制方式 
            UINT32_T symbol_rate;  //符号率   
            UINT32_T frequency;    //频点    
        }roc_upd_info_t;

        loader启动时检查升级标志 
        当升级标志为ROC_UPD_ASK时，则启动升级
        升级成功后将该标志置为ROC_UPD_NO

返    回:
    失败: 非0              
    成功:  0
*****************************************************************************/
UINT32_T rocme_porting_set_updinfo( roc_upd_info_t *info )
{
	ROCME_TEST_PRINT
	if(NULL == info)
	{
		printf("info is null\n");

		return ROC_ERR;
	}

	WriteLoaderParam(info);

	return ROC_OK;
}


int convert_ascii( HI_U8* strAscii , HI_U64* u64Res , int len)
{
	ROCME_TEST_PRINT
    int     i = 0 ;
    HI_U8   u8data  = 0 ;
    HI_U64  u64data = 0 ;

    if( (!strAscii) || (!u64Res) || (len > 16) )
    {
        return  -1;
    }

    for(i = 0 ; i < len ; i++)
    {
        u8data = 0 ;
        if( (strAscii[i] >= '0') && (strAscii[i] <= '9') )
        {
            u8data = strAscii[i] - '0' ;    
        }   
        else if( (strAscii[i] >= 'a') && (strAscii[i] <= 'f') )
        {
            u8data = strAscii[i] - 'a'+ 10 ;
        }
        else if( (strAscii[i] >= 'A') && (strAscii[i] <= 'F') )
        {
            u8data  = strAscii[i] - 'A'+ 10 ;
        }
		else if(strAscii[i] == 0)
		{
			break;
		}
		else
		{
			continue;
		}

        u64data = ( u64data << 4 ) | u8data ;
    }

    *u64Res =  u64data ;

    return  0;
}

void init_loader_mutex()
{
	ROCME_TEST_PRINT
	static int inited=0;
	if(inited)
	{
		return;
	}
	
	if( pthread_mutex_init( &loader_mutex , NULL ) )
	{
		return;
	}

	inited = 1;
	return;
}

unsigned long UpdateCrc(unsigned long crc_accum, void *pBuffer,
                             int data_blk_size)
 /* update the CRC on the data block one byte at a time */ 
{ 
	ROCME_TEST_PRINT
	register int i, j;
	char* data_blk_ptr = (char*)pBuffer;
	GenCrcTable();
	for ( j = 0;  j < data_blk_size;  j++ )
	{ 
		i = ( (int) ( crc_accum >> 24) ^ *data_blk_ptr++ ) & 0xff;
		crc_accum = ( crc_accum << 8 ) ^ g_CRCTable[i];
	}
	return crc_accum; 
}

static void GenCrcTable()
{ 
	ROCME_TEST_PRINT
	register int i, j;  
	register unsigned long crc_accum;
	for ( i = 0;  i < 256;  i++ )
	{
		crc_accum = ( (unsigned long) i << 24 );
		for ( j = 0;  j < 8;  j++ )
		{
			if ( crc_accum & 0x80000000L )
			{
				crc_accum = ( crc_accum << 1 ) ^ POLYNOMIAL;
			}
			else
			{
				crc_accum = ( crc_accum << 1 );
			}
		}
		g_CRCTable[i] = crc_accum; 
	}
	return; 
}

/******************************************************************************
 *                                 外部函数                                   *
 ******************************************************************************/
void get_system_info(roc_stb_info_t *pSystemInfo )
{
	ROCME_TEST_PRINT
	HI_U64	u64Data = 0 ;
	UINT8_T temp[6];
	UINT8_T CardIDval[50];
	char softversion[16] = {0};
	INT32_T ret=0;
	int  len = 0;
	
	if( NULL == g_SystemInfo )
	{
		LOADER_DB_INFO_S stLoaderInfo;
		memset(&stLoaderInfo, 0, sizeof(LOADER_DB_INFO_S));
		HI_LOADER_ReadLoaderInfo(&stLoaderInfo);

		g_SystemInfo = (roc_stb_info_t*)malloc(sizeof(roc_stb_info_t));

		if(NULL == g_SystemInfo)
		{
			return;
		}

		memset(g_SystemInfo, 0, sizeof(roc_stb_info_t));

		
		rocme_porting_get_product_serial(temp);
		g_SystemInfo->stb_serial_no = (temp[2]<<24) +(temp[3]<<16) + (temp[4]<<8) + temp[5];/*取mac地址的后四位作为stbid*/

		g_SystemInfo->major_sw_ver= stLoaderInfo.nSoftwareVersion/0x10000;
		g_SystemInfo->minor_sw_ver = stLoaderInfo.nSoftwareVersion%0x10000;
		
		g_SystemInfo->major_hw_ver=  stLoaderInfo.nHardwareVersion/0x10000;
		g_SystemInfo->minor_hw_ver=  stLoaderInfo.nHardwareVersion%0x10000;

		g_SystemInfo->manu_code= stLoaderInfo.nManufacturer; 

		memcpy(&g_StbLoaderInfo,&stLoaderInfo,sizeof(LOADER_DB_INFO_S));

	}
	
	*pSystemInfo = *g_SystemInfo;
	return;
}

/*write information to flash or eeprom*/
int WriteLoaderParam(roc_upd_info_t *param)
{
	ROCME_TEST_PRINT
    HI_S32 s32Ret = HI_FAILURE;

    g_StbLoaderInfo.bFlag = LOADER_PROGRESS_FLAG;
    g_StbLoaderInfo.bCallMainProgram = CALL_LOADER;
    g_StbLoaderInfo.nFrequency = param->frequency;
    g_StbLoaderInfo.nSymbolRate = param->symbol_rate;
    g_StbLoaderInfo.bQamSize = param->modulation-1;
    g_StbLoaderInfo.nPID = param->download_pid;


    init_loader_mutex();
    pthread_mutex_lock(&loader_mutex);
    s32Ret = HI_LOADER_WriteLoaderInfo(&g_StbLoaderInfo);
	
    pthread_mutex_unlock(&loader_mutex);

    if( HI_SUCCESS != s32Ret )
    {
        printf( "HI_LOADER_WriteLoaderInfo return FAIL\n"); 
    }
    return HI_SUCCESS;
}



HI_S32 HI_LOADER_ReadLoaderInfo( LOADER_DB_INFO_S* info )
{
	ROCME_TEST_PRINT
	HI_U32 crc = 0;
	int fd = -1; 
	char *pbuf = NULL;
	int i=0;
	LOADER_DB_INFO_S loader_s={0};
	char *pBuf_tmp = NULL;
	if (NULL == info)
	{
		return HI_FAILURE;
	}
	pbuf = (char *)malloc(0x20000);
	if(!pbuf)
		return ROC_ERR;

	memset((char *)info,0x00,sizeof(LOADER_DB_INFO_S));
	if(HI_FAILURE == TDRV_FLASH_Read(LOADER_INFO_BASIC_ADDR,0x20000,pbuf))
	{
		printf("flash_read main loader fail %s ;%d\n",__FUNCTION__,__LINE__);
		goto read_loader_back;
	}
	pBuf_tmp = pbuf;
	memcpy((char*)info, pbuf, sizeof(LOADER_DB_INFO_S));
	crc = UpdateCrc(0xffffffff,(void *)info, (sizeof(LOADER_DB_INFO_S) - sizeof(HI_U32)));
	if( crc == info->nCRC && LOADER_PROGRESS_FLAG == info->bFlag)
	{
		printf("flash_read main loader ok %s ;%d\n",__FUNCTION__,__LINE__);
		return HI_SUCCESS;
	}

read_loader_back:
// read loader_info backup;==========================================================	
	if(HI_FAILURE == TDRV_FLASH_Read(LOADER_INFO_BACKUP_ADDR,0x20000,pbuf))
	{
		printf("flash_read backup loader fail %s ;%d\n",__FUNCTION__,__LINE__);
		free(pbuf);
		return HI_FAILURE;
	}

	memcpy((char*)info, pbuf, sizeof(LOADER_DB_INFO_S));
	crc = UpdateCrc(0xffffffff,(void *)info, (sizeof(LOADER_DB_INFO_S) - sizeof(HI_U32)));
	if( crc == info->nCRC && LOADER_PROGRESS_FLAG == info->bFlag)
	{
		printf("flash_read backup loader ok %s ;%d\n",__FUNCTION__,__LINE__);
		free(pbuf);
		return HI_SUCCESS;
	}

//* 主副分区都不正确, 采用默认配置更新主分区 */
	printf( "Use default loader settings\n");
	memset(info, 0x00, sizeof(LOADER_DB_INFO_S));
	info->bFlag   = LOADER_PROGRESS_FLAG;
	info->nFrequency  = 299;
	info->bQamSize = 2;
	info->nPID = 2304;
	info->nSymbolRate = 6875;
	info->nSoftwareVersion = 0xf0001;
	info->nHardwareVersion = 0x0201;
	info->nReleaseDate = 1;
	free(pbuf);
	return HI_SUCCESS;
}

HI_S32 HI_LOADER_WriteLoaderInfo(LOADER_DB_INFO_S* info)
{
	ROCME_TEST_PRINT
    /* 拷贝主分区到备份分区 */
  	//LOADER_DB_INFO_S basicInfo=*((LOADER_DB_INFO_S *)info);
    HI_U32 u32CheckSum = 0;
    HI_S32 i = 0;
    HI_U32 param[2];
    HI_U32 crc = 0;
	int fd = -1;
	char *pBuf = NULL;
	char *pBuf_tmp = NULL;
	if( NULL == info )
	{
		printf( "Input Param Invalid\n");
		return HI_FAILURE;
	}
	/* 检查输入参数的合法性 */
	info->bFlag = LOADER_PROGRESS_FLAG;
	info->nCRC = UpdateCrc(0xffffffff,(void *)info, (sizeof(LOADER_DB_INFO_S) - sizeof(HI_U32)));
	pBuf =(char*)malloc(0x20000);
	if( !pBuf )
	{
		return HI_FAILURE;
	}
	//write main loader info addr 0x200000--0x300000=======
	
	if( HI_FAILURE == TDRV_FLASH_EraseEx(LOADER_INFO_BASIC_ADDR,0x20000) )
	{
		printf("\r\flash_erase failed at addr 0x200000\r\n");
		goto write_loader_info;
	}
	memset(pBuf, 0x00, 0x20000);
	memcpy(pBuf, (char*)info, sizeof(LOADER_DB_INFO_S));


	if(HI_FAILURE ==  TDRV_FLASH_Write(LOADER_INFO_BASIC_ADDR, 0x20000, pBuf) )
	{
		printf("\r\flash_write(%d, ) failed\r\n", sizeof(LOADER_DB_INFO_S) );
	}



write_loader_info:
	//	write backup loader info addr 0x300000--0x400000=======
	if( HI_FAILURE == TDRV_FLASH_EraseEx(LOADER_INFO_BACKUP_ADDR, 0x20000) )
	{
		printf("\r\flash_erase failed at addr 0x200000\r\n");
		free(pBuf);
		return HI_FAILURE;
	}

	memset(pBuf, 0x00, 0x20000);

	memcpy(pBuf, (char*)info, sizeof(LOADER_DB_INFO_S));
	if(HI_FAILURE ==  TDRV_FLASH_Write(LOADER_INFO_BACKUP_ADDR, 0x20000, pBuf) )
	{
		printf("\r\flash_write(%d, ) failed\r\n", sizeof(LOADER_DB_INFO_S) );
	}

	free(pBuf);
	return HI_SUCCESS;
		
}


