/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_eeprom.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
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
��������: 
            rocme_porting_eeprom_init
����˵��: 
            eeprom�洢�豸��ʼ�����м����������ʱ���ô˺��������������м��
        ֮ǰ�������Ѿ�������eeprom�豸�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            void
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʼ���ɹ� )
    ʧ�� : -1 �� ������ ( ��ʼ��ʧ�� )
�޸ļ�¼��
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
��������: 
            rocme_porting_eeprom_info
����˵��: 
            ���eeprom�洢�ռ����ʼ��ַ��������ÿ��ĳ��ȣ�eeprom����С
        �ռ䲻��С��1k��
����˵����
    ���������
            ��
    ���������
            [ *eep_addr   ] : ������м����eeprom����ʼ��ַͷָ��
            [ num_of_sect ] : ������м����eeprom���ܿ���
            [ sect_size   ] : ������м����eeprom��ÿ��Ĵ�С
��    �أ� 
    �ɹ� : 0            ( eeprom������Ϣ��ȡ�ɹ� )
    ʧ�� : -1 �� ������ ( eeprom������Ϣ��ȡʧ�� )
�޸ļ�¼��
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
��������: 
            rocme_porting_eeprom_read
����˵��: 
            ��ָ����eeprom�洢�ռ��ָ����ַ��ȡ���ݵ�ָ�������ݻ������С�
����˵����
    ���������
            [ eep_addr    ] : �м����ȡeeprom��Ŀ���ַ
            [ *buff_addr  ] : ��ȡ���ݵĴ洢������ͷָ��
            [ nbytes      ] : ��Ҫ��ȡ�ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : >=0����ֵ    ( ʵ�ʶ�ȡ�����ݳ���  )
    ʧ�� : -1 �� ������ ( ��ȡeeprom����ʧ��  )
�޸ļ�¼��
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
��������: 
            rocme_porting_eeprom_burn
����˵��: 
            ��ָ��������д�뵽ָ����eeprom�洢���У�ʵ��Ϊͬ����ʽд�롣
����˵����
    ���������
            [ eep_addr    ] : �м��д��flash��Ŀ���ַ
            [ *buff_addr  ] : д�����ݵĴ洢������ͷָ��
            [ nbytes      ] : ��Ҫд��ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : >=0����ֵ    ( ʵ��д������ݳ��� )
    ʧ�� : -1 �� ������ ( д��eeprom����ʧ�� )
�޸ļ�¼��
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
��������: 
            rocme_porting_eeprom_status
����˵��: 
            �жϵ�ǰeeprom��д��״̬���˺���Ŀǰ����Ҫ�󣬿���ʵ��Ϊ�գ�ֱ�ӷ�
        ���Ѿ�д�ɹ�( 1 )���ɡ�
����˵����
    ���������
            [ eep_addr    ] : �м��д��eeprom��Ŀ���ַ
            [ nbytes      ] : д��ĳ���
    ���������
            ��
��    �أ� 
    ����д :  0
    д�ɹ� :  1
    дʧ�� : -1 
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_eeprom_status(UINT32_T eep_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
	return 1;
}


/**************************************************************************
��������: 
            rocme_porting_eeprom_erase
����˵��: 
            ����ָ��eeprom�洢�ռ��е����ݡ�
����˵����
    ���������
            [ eep_addr    ] : �м����Ҫ����eeprom��Ŀ���ַ
            [ nbytes      ] : �����ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( eeprom�����ɹ� )
    ʧ�� : -1 �� ������ ( eeprom����ʧ�� )
�޸ļ�¼��
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

