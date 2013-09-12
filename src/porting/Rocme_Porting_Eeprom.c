/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_eeprom.cpp
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
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

#include "porter_rocme.h"




#define  rocme_eep_size  (1024*64)
unsigned char rocme_buffer[rocme_eep_size];
#define ROCME_FAILURE (-1)


static char* rocme_eep_data_path ="/flashfile/d/eep.dat";



/**************************************************************************
函数名称: 
            rocme_porting_eeprom_init
功能说明: 
            eeprom存储设备初始化，中间件会在启动时调用此函数，若在启动中间件
        之前机顶盒已经做好了eeprom设备的初始化，此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            void
    输出参数：
            无
返    回： 
    成功 : 0            ( 初始化成功 )
    失败 : -1 或 错误码 ( 初始化失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_init(void)
	{
	ROCME_TEST_PRINT
#if 0
		FILE *fp = NULL;
		fp = fopen(rocme_eep_data_path, "rb");
		if (fp)
		{
			fread(rocme_buffer, 1, rocme_eep_size, fp);
			fclose(fp);
			ROCME_PRINTF(ROCME_LOG_INFO,"[rocme_porting_flash_init] open file \"%s\" ok\r\n", rocme_eep_data_path);
			return ROC_OK;
		}
		else
		{
			fp = fopen(rocme_eep_data_path, "a+");
			if(fp)
			{
				memset(rocme_buffer,0xff,rocme_eep_size);
				fwrite(rocme_buffer, 1, rocme_eep_size, fp);
				fflush(fp);
				fsync((int)fp);
				fclose(fp);
				return ROC_OK;
			}
			
		}
		
		ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_flash_init] open file \"%s\" failed \r\n", rocme_eep_data_path);
		return ROC_ERR;
#endif

	INT32_T errCode;
    FILE *flashfile;
    UINT8_T buf[1024];
    INT32_T i =0;

    errCode = access(rocme_eep_data_path, F_OK);
    if(errCode != 0)
    {
        flashfile = fopen(rocme_eep_data_path, "wb");
        if(flashfile==NULL)
        {
            printf("--+--rocme_porting_nvram_read()**ERROR**, open file failed!!!--+--\n");
            return (-1);
        }
               
        memset( buf, 0xff, 1024);

        for( i=0; i<64; i++ )
        {
            if( 1024 != fwrite( buf, 1, 1024, flashfile) )
            {
                printf( "[%s] fwrite error !!!\n", __func__ );
            }
        }
		
        fclose( flashfile );
    }
    else
    {
        printf("e2p file exist. OK\n");
    }

    return 0;
	}


/**************************************************************************
函数名称: 
            rocme_porting_eeprom_info
功能说明: 
            获得eeprom存储空间的起始地址、块数和每块的长度，eeprom的最小
        空间不得小于1k。
参数说明：
    输入参数：
            无
    输出参数：
            [ *eep_addr   ] : 分配给中间件的eeprom的起始地址头指针
            [ num_of_sect ] : 分配给中间件的eeprom的总块数
            [ sect_size   ] : 分配给中间件的eeprom的每块的大小
返    回： 
    成功 : 0            ( eeprom基本信息获取成功 )
    失败 : -1 或 错误码 ( eeprom基本信息获取失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_info(UINT8_T **eep_addr, INT32_T *num_of_sect,  INT32_T *sect_size)
{
	ROCME_TEST_PRINT
	*eep_addr = 0;
	*num_of_sect = 1;
	*sect_size = rocme_eep_size;
	return ROC_OK;
}

/**************************************************************************
函数名称: 
            rocme_porting_eeprom_read
功能说明: 
            从指定的eeprom存储空间的指定地址读取数据到指定的数据缓冲区中。
参数说明：
    输入参数：
            [ eep_addr    ] : 中间件读取eeprom的目标地址
            [ *buff_addr  ] : 读取数据的存储缓冲区头指针
            [ nbytes      ] : 需要读取的长度
    输出参数：
            无
返    回： 
    成功 : >=0的数值    ( 实际读取的数据长度  )
    失败 : -1 或 错误码 ( 读取eeprom内容失败  )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_read(UINT32_T eep_addr, UINT8_T *buff_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
#if 0
	if((eep_addr<rocme_buffer)||((eep_addr+nbytes)>(rocme_buffer+rocme_eep_size) ))
	{
		return ROC_ERR;
	}
	memcpy(buff_addr,eep_addr,nbytes);
	
	return nbytes;
#endif

	INT32_T error;
    INT32_T i = 0;
    FILE *flashfile;
    
    printf( "in [%s] addr=0x%x size=%d\n", __func__, eep_addr, nbytes );
    flashfile = fopen(rocme_eep_data_path, "rb");
    if(flashfile==NULL)
    {
        printf("--+--rocme_porting_eeprom_read, open file failed!!!--+--\n");
        return (ROCME_FAILURE);
    }

    error = fseek(flashfile, eep_addr, SEEK_SET);
    if(error!=0)
    {
        printf("--+--rocme_porting_eeprom_read, fseek file failed!!!--+--\n");
        fclose(flashfile);
        return (ROCME_FAILURE);
    }

    nbytes = fread(buff_addr, 1, nbytes, flashfile);
    if( nbytes == -1)
    {
        printf("--+--rocme_porting_eeprom_read, fread file failed!!!--+--\n");
        fclose(flashfile);
        return (ROCME_FAILURE);
    }

    fclose(flashfile);
}



/**************************************************************************
函数名称: 
            rocme_porting_eeprom_burn
功能说明: 
            将指定的数据写入到指定的eeprom存储区中，实现为同步方式写入。
参数说明：
    输入参数：
            [ eep_addr    ] : 中间件写入flash的目标地址
            [ *buff_addr  ] : 写入数据的存储缓冲区头指针
            [ nbytes      ] : 需要写入的长度
    输出参数：
            无
返    回： 
    成功 : >=0的数值    ( 实际写入的数据长度 )
    失败 : -1 或 错误码 ( 写入eeprom内容失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_burn(UINT32_T eep_addr, const INT8_T *buff_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
#if 0
	FILE *fp = NULL;
	if((eep_addr<rocme_buffer)||((eep_addr+nbytes)>(rocme_buffer+rocme_eep_size) ))
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_eeprom_burn] params err \r\n");
		return ROC_ERR;
	}
	memcpy(eep_addr,buff_addr,nbytes);
	
	fp = fopen(rocme_eep_data_path, "r+b");
	if(fp)
	{
		
		fwrite(rocme_buffer, 1, rocme_eep_size, fp);
		fflush(fp);
		fsync((int)fp);
		fclose(fp);
		return nbytes;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_eeprom_burn] open file \"%s\" failed \r\n", rocme_eep_data_path);
		return ROC_ERR;
	}
#endif
	INT32_T error;
    INT32_T i = 0;
    FILE *flashfile;

    if( (eep_addr+nbytes) > rocme_buffer || buff_addr == NULL )
    {
        printf("--+--rocme_porting_eeprom_burn, param error!!!--+--\n");
        return -1;
    }
    
    flashfile = fopen(rocme_eep_data_path, "rb+");
    if(flashfile==NULL)
    {
        printf("--+--rocme_porting_eeprom_burn, open file failed!!!--+--\n");
        return (ROCME_FAILURE);
    }
	
    error = fseek(flashfile, eep_addr, SEEK_SET);
    if(error!=0)
    {
        printf("--+--rocme_porting_eeprom_burn, fseek file failed!!!--+--\n");
        fclose(flashfile);
        return (ROCME_FAILURE);
    }

    nbytes = fwrite(buff_addr, 1, nbytes, flashfile);
    if(nbytes == -1)
    {
        printf("--+--rocme_porting_eeprom_burn, fwrite file failed!!!--+--\n");
        fclose(flashfile);
        return (ROCME_FAILURE);
    }

    fclose(flashfile);

    return nbytes;
}



/**************************************************************************
函数名称: 
            rocme_porting_eeprom_status
功能说明: 
            判断当前eeprom的写入状态，此函数目前不做要求，可以实现为空，直接返
        回已经写成功( 1 )即可。
参数说明：
    输入参数：
            [ eep_addr    ] : 中间件写入eeprom的目标地址
            [ nbytes      ] : 写入的长度
    输出参数：
            无
返    回： 
    正在写 :  0
    写成功 :  1
    写失败 : -1 
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_status(UINT32_T eep_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
	return 1;
}


/**************************************************************************
函数名称: 
            rocme_porting_eeprom_erase
功能说明: 
            擦除指定eeprom存储空间中的数据。
参数说明：
    输入参数：
            [ eep_addr    ] : 中间件需要擦除eeprom的目标地址
            [ nbytes      ] : 擦除的长度
    输出参数：
            无
返    回： 
    成功 : 0            ( eeprom擦除成功 )
    失败 : -1 或 错误码 ( eeprom擦除失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_erase(UINT32_T eep_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
#if 0
	FILE *fp = NULL;
	
	if((eep_addr<rocme_buffer)||((eep_addr+nbytes)>(rocme_buffer+rocme_eep_size) ))
	{
		return ROC_ERR;
	}
	memset(eep_addr,0xff,nbytes);
	
	fp = fopen(rocme_eep_data_path, "r+b");
	if(fp)
	{
		fwrite(rocme_buffer, 1, rocme_eep_size, fp);
		fflush(fp);
		fsync((int)fp);
		fclose(fp);
		return ROC_OK;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_eeprom_erase] open file \"%s\" failed \r\n", rocme_eep_data_path);
		return ROC_ERR;
	}
#endif

	INT32_T error;
    UINT32_T i =0;
    FILE *flashfile;

    printf( "[%s] eep_addr=%d nbytes=%d\n", __func__, eep_addr, nbytes );

    if( (eep_addr+nbytes) > rocme_buffer )
    {
        printf("--+--rocme_porting_eeprom_burn, param error!!!--+--\n");
        return -1;
    }
    
    flashfile = fopen(rocme_eep_data_path, "rb+");
    if(flashfile==NULL)
    {
        printf("--+--rocme_porting_eeprom_burn, open file failed!!!--+--\n");
        return (ROCME_FAILURE);
    }
	
    error = fseek(flashfile, eep_addr, SEEK_SET);
    if(error!=0)
    {
        printf("--+--rocme_porting_eeprom_burn, fseek file failed!!!--+--\n");
        fclose(flashfile);
        return (ROCME_FAILURE);
    }

    for( i=0; i<nbytes; i++ )
    {
        UINT8_T x=0xff;
        
        if(1 != fwrite( &x, 1, 1, flashfile))
        {
            printf("--+--rocme_porting_eeprom_burn, fwrite file failed!!!--+--\n");
        }
    }

    fclose(flashfile);
    return 0;
}

