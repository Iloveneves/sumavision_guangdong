//------------------------------------------------------------------------
// 
// 文件名称：flash_drv.c
// 
// 摘    要：flash driver 
// 
// 当前版本：x.x
//
// 作    者：jianghaiqi
//
// 创建日期：2008年6月5日
//
// 说    明: FLASH驱动层封装
//------------------------------------------------------------------------

#ifndef _EMLUATOR_PC

#include "hi_unf_ecs.h"
#include "hi_os.h"


extern int flash_init();
extern void flash_exit();
extern int flash_erase(unsigned int uAddr, unsigned int uSize);
extern int flash_read(unsigned int addr, char *buf, unsigned int size );
extern int flash_write(unsigned int addr, char *buf, unsigned int size );
extern int flash_write_ex(unsigned int addr, char *buf, unsigned int size );


//------------------------------------------------------------------------
// 初始化Flash驱动(TRUE/FLASE)
//------------------------------------------------------------------------
int TDRV_FLASH_Initialize(void)
{
	return (0 == flash_init());
}

//------------------------------------------------------------------------
// 释放Flash驱动(TRUE/FLASE)
//------------------------------------------------------------------------
int TDRV_FLASH_Finalize(void)
{
	flash_exit();
 	return TRUE;
}

//------------------------------------------------------------------------
// 擦写指定位置的扇区
//------------------------------------------------------------------------
//  uAddr 扇区首地址
// 返回 操作是否成功(TRUE/FLASE)
//------------------------------------------------------------------------
int TDRV_FLASH_EraseEx(unsigned int uAddr, int uSize)
{
	return ( 0 == flash_erase(uAddr, uSize) );
}

int TDRV_FLASH_Erase(unsigned int uAddr)
{
	return TDRV_FLASH_EraseEx(uAddr, 0x20000);
}

//------------------------------------------------------------------------
// 从Flash读取数据
//------------------------------------------------------------------------
// uAddr Flash地址
// uSize 缓冲大小
// pBuffer 读缓冲
// 返回 读到的字节数
//------------------------------------------------------------------------
int TDRV_FLASH_Read(unsigned int uAddr, unsigned int uSize, unsigned char * pBuffer)
{
	return flash_read( uAddr, (char *)pBuffer, uSize ); 
}

//------------------------------------------------------------------------
// 向Flash写数据
//------------------------------------------------------------------------
// uAddr Flash地址
// pData 待写数据
// uSize 数据大小
// 返回 成功写进的大小
//------------------------------------------------------------------------
int TDRV_FLASH_Write(unsigned int uAddr, unsigned int uSize, unsigned char * pData)
{
	return flash_write(uAddr, (char *)pData, uSize);
}

int TDRV_FLASH_WriteEx(unsigned int uAddr, unsigned int uSize, unsigned char * pData)
{
	return flash_write_ex(uAddr, (char *)pData, uSize);
}



int TDRV_FLASH_Flush()
{
	return TRUE;
}


static int g_nI2cPort = 1;
static int g_bI2cInited = FALSE;
static int CheckI2cInited(void)
{
	if( g_bI2cInited )
	{
		return TRUE;
	}

	HI_UNF_I2C_Open();
	g_bI2cInited = TRUE;

	return TRUE;
}


int TDRV_I2C_Read(unsigned char bDeviceAddr, unsigned char bSubDeviceAddr ,
				   unsigned char* pData, unsigned char nCount)
{
	if( !CheckI2cInited() )
	{
		return FALSE;
	}

	int ret;

	ret = HI_UNF_I2C_Read(g_nI2cPort, bDeviceAddr, (unsigned int)bSubDeviceAddr, 1, pData, (unsigned int)nCount);
	if( HI_SUCCESS != ret )
	{
		return FALSE;
	}
	
	return TRUE;	
}


int TDRV_I2C_Write(unsigned char bDeviceAddr, unsigned char bSubDeviceAddr ,
					unsigned char* pData, unsigned char nCount)
{
	if( !CheckI2cInited() )
	{
		return FALSE;
	}

	int ret;

	ret = HI_UNF_I2C_Write(g_nI2cPort, bDeviceAddr, (unsigned int)bSubDeviceAddr, 1, pData, (unsigned int)nCount);
	if( HI_SUCCESS != ret )
	{
		return FALSE;
	}
	
	return TRUE;	
}


int TDRV_I2C_Read_OneAddr(	unsigned char bDeviceAddr ,
							unsigned char* pData, unsigned char nCount)
{
	if( !CheckI2cInited() )
	{
		return FALSE;
	}

	int ret;

	ret = HI_UNF_I2C_Read(g_nI2cPort, bDeviceAddr, 0, 0, pData, (unsigned int)nCount);
	if( HI_SUCCESS != ret )
	{
		return FALSE;
	}
	
	return TRUE;	
}


int TDRV_I2C_Write_OneAddr(unsigned char bDeviceAddr ,
							unsigned char* pData, unsigned char nCount)
{
	if( !CheckI2cInited() )
	{
		return FALSE;
	}

	int ret;

	ret = HI_UNF_I2C_Write(g_nI2cPort, bDeviceAddr, 0, 0, pData, (unsigned int)nCount);
	if( HI_SUCCESS != ret )
	{
		return FALSE;
	}
	
	return TRUE;	
}


#endif	//_EMLUATOR_PC


