//------------------------------------------------------------------------
// 
// �ļ����ƣ�flash_drv.c
// 
// ժ    Ҫ��flash driver 
// 
// ��ǰ�汾��x.x
//
// ��    �ߣ�jianghaiqi
//
// �������ڣ�2008��6��5��
//
// ˵    ��: FLASH�������װ
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
// ��ʼ��Flash����(TRUE/FLASE)
//------------------------------------------------------------------------
int TDRV_FLASH_Initialize(void)
{
	return (0 == flash_init());
}

//------------------------------------------------------------------------
// �ͷ�Flash����(TRUE/FLASE)
//------------------------------------------------------------------------
int TDRV_FLASH_Finalize(void)
{
	flash_exit();
 	return TRUE;
}

//------------------------------------------------------------------------
// ��дָ��λ�õ�����
//------------------------------------------------------------------------
//  uAddr �����׵�ַ
// ���� �����Ƿ�ɹ�(TRUE/FLASE)
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
// ��Flash��ȡ����
//------------------------------------------------------------------------
// uAddr Flash��ַ
// uSize �����С
// pBuffer ������
// ���� �������ֽ���
//------------------------------------------------------------------------
int TDRV_FLASH_Read(unsigned int uAddr, unsigned int uSize, unsigned char * pBuffer)
{
	return flash_read( uAddr, (char *)pBuffer, uSize ); 
}

//------------------------------------------------------------------------
// ��Flashд����
//------------------------------------------------------------------------
// uAddr Flash��ַ
// pData ��д����
// uSize ���ݴ�С
// ���� �ɹ�д���Ĵ�С
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


