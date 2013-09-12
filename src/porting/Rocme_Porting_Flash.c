/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_flash.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/
#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "signal.h"
#include <stdarg.h>
#include <math.h>
#include <memory.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <dirent.h>
#include <utime.h>
#include <ctype.h>

#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/if.h> 
#include <net/if_arp.h> 
#include <net/route.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h> 
#include <net/if_arp.h> 

#include "flash_drv.h"
#include "porter_rocme.h"

static char* rocme_data_path ="/flashfile/d/rocme.dat";
static char* rocme_iframe0_data= "/flashfile/d/romeiframe0.dat";
static char* rocme_iframe1_data ="/flashfile/d/romeiframe1.dat";
static char* rocme_boot_logo    = "/flashfile/d/appdata_logo_upd.dat";

#define rocme_size 0x90000
#define ROCME_LOGO_ADDR 0xe00000
#define ROCME_LOGO_FLASH_SIZE	0x100000

/**************************************************************************
��������: 
            rocme_porting_flash_init
����˵��: 
            flash�洢�豸��ʼ�����м����������ʱ���ô˺��������������м��
        ֮ǰ�������Ѿ�������flash�豸�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
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
INT32_T rocme_porting_flash_init(void)
{
ROCME_TEST_PRINT
	#if 0
	FILE *fp = NULL;
	fp = fopen(rocme_data_path, "rb");
	if (fp)
	{
		fread(rocme_buffer, 1, rocme_size, fp);
		fclose(fp);
		ROCME_PRINTF(ROCME_LOG_INFO,"[rocme_porting_flash_init] open file \"%s\" ok \r\n", rocme_data_path);
		return ROC_OK;
	}
	else
	{
		fp = fopen(rocme_data_path, "a+");
		if(fp)
		{
			memset(rocme_buffer,0xff,rocme_size);
			fwrite(rocme_buffer, 1, rocme_size, fp);
			fflush(fp);
			fsync((int)fp);
			fclose(fp);
			return ROC_OK;
		}
		
	}
	
	ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_flash_init] open file \"%s\" failed \r\n", rocme_data_path);
	return ROC_ERR;
	#endif
	INT32_T errCode;
    FILE *flashfile;
    INT32_T i =0;
    
    errCode = access(rocme_data_path, F_OK);
    if(errCode != 0)
    {
        UINT8_T x = 0xff;
        flashfile = fopen(rocme_data_path, "wb");
        if(flashfile==NULL)
        {
            ROCME_PRINTF(ROCME_LOG_ERROR," open file failed!!!--+--\n");
            return (-1);
        }

        fseek( flashfile, rocme_size-1, SEEK_SET );
        fwrite( &x, 1, 1, flashfile );
        fclose(flashfile);
    }
    else
    {
        ROCME_PRINTF(ROCME_LOG_INFO,"flash file exist. OK\n");
    }
	return 0;
}

/**************************************************************************
��������: 
            rocme_porting_flash_info
����˵��: 
            ���flash�洢�ռ����ʼ��ַ��������ÿ��ĳ��ȣ������RocME�м��
        ���ֵ�flash memoryÿ����ʳߴ���32k/64k/128k/256kBytes����flash����С
        �ռ䲻��С��512k��
����˵����
    ���������
            ��
    ���������
            [ *addr       ] : ������м����flash����ʼ��ַͷָ��
            [ num_of_sect ] : ������м����flash���ܿ���
            [ sect_size   ] : ������м����flash��ÿ��Ĵ�С
��    �أ� 
    �ɹ� : 0            ( flash������Ϣ��ȡ�ɹ� )
    ʧ�� : -1 �� ������ ( flash������Ϣ��ȡʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_flash_info(UINT8_T **addr, INT32_T *num_of_sect,  INT32_T *sect_size)
{
ROCME_TEST_PRINT
	*addr = 1;
	*num_of_sect = 9;
	*sect_size = 0x10000;
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_flash_read
����˵��: 
            ��ָ����flash�洢�ռ��ָ����ַ��ȡ���ݵ�ָ�������ݻ������С�
����˵����
    ���������
            [ flash_addr  ] : �м����ȡflash��Ŀ���ַ
            [ *buff_addr  ] : ��ȡ���ݵĴ洢������ͷָ��
            [ nbytes      ] : ��Ҫ��ȡ�ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : >=0����ֵ    ( ʵ�ʶ�ȡ�����ݳ��� )
    ʧ�� : -1 �� ������ ( ��ȡflash����ʧ��  )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_flash_read(UINT32_T flash_addr, UINT8_T *buff_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
	#if 0
	if((flash_addr<rocme_buffer)||((flash_addr+nbytes)>(rocme_buffer+rocme_size) ))
	{
		return ROC_ERR;
	}
	memcpy(buff_addr,flash_addr,nbytes);
	
	return nbytes;
	#endif
	INT32_T error;
    FILE *flashfile;

    flash_addr -= 1;
    if( ((flash_addr+nbytes) > rocme_size)	|| (buff_addr == NULL) )
    {
        return (-1);
    }
	
    flashfile = fopen(rocme_data_path, "rb");
    if(flashfile==NULL)
    {
        return (-1);
    }

    error = fseek(flashfile, flash_addr, SEEK_SET);
    if(error!=0)
    {
        fclose(flashfile);
        return (-1);
    }

    nbytes = fread(buff_addr, 1, nbytes, flashfile);
    if( nbytes == -1)
    {
        fclose(flashfile);
        return (-1);
    }

    fclose(flashfile);

    return nbytes;
	
}

/**************************************************************************
��������: 
            rocme_porting_flash_burn
����˵��: 
            ��ָ��������д�뵽ָ����flash�洢���У�ʵ��Ϊͬ����ʽд�롣
����˵����
    ���������
            [ flash_addr  ] : �м��д��flash��Ŀ���ַ
            [ *buff_addr  ] : д�����ݵĴ洢������ͷָ��
            [ nbytes      ] : ��Ҫд��ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : >=0����ֵ    ( ʵ��д������ݳ��� )
    ʧ�� : -1 �� ������ ( д��flash����ʧ��  )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_flash_burn(UINT32_T flash_addr, const UINT8_T *buff_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
	#if 0
	FILE *fp = NULL;
	
	if((flash_addr<rocme_buffer)||((flash_addr+nbytes)>(rocme_buffer+rocme_size) ))
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[ipanel_porting_nvram_burn] params err \r\n");
		return ROC_ERR;
	}
	memcpy(flash_addr,buff_addr,nbytes);
	
	fp = fopen(rocme_data_path, "r+b");
	if(fp)
	{
		fwrite(rocme_buffer, 1, rocme_size, fp);
		fflush(fp);
		fsync((int)fp);
		fclose(fp);
		return nbytes;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[ipanel_porting_nvram_burn] open file \"%s\" failed \r\n", rocme_data_path);
		return ROC_ERR;
	}
	#endif
	INT32_T error;

    flash_addr -= 1;
    if( ((flash_addr+nbytes) > rocme_size)	|| (buff_addr == NULL) )
    {
        return (-1);
    }

    FILE *flashfile;

    flashfile = fopen(rocme_data_path, "rb+");
    if(flashfile==NULL)
    {
        return (-1);
    }
	
    error = fseek(flashfile, flash_addr, SEEK_SET);
    if(error!=0)
    {
        fclose(flashfile);
        return (-1);
    }

    nbytes = fwrite(buff_addr, 1, nbytes, flashfile);
    if(nbytes == -1)
    {
        fclose(flashfile);
        return (-1);
    }

    fclose(flashfile);
    return nbytes;
}

/**************************************************************************
��������: 
            rocme_porting_flash_status
����˵��: 
            �жϵ�ǰflash��д��״̬���˺���Ŀǰ����Ҫ�󣬿���ʵ��Ϊ�գ�ֱ�ӷ�
        ���Ѿ�д�ɹ�( 1 )���ɡ�
����˵����
    ���������
            [ flash_addr  ] : �м��д��flash��Ŀ���ַ
            [ nbytes      ] : д��ĳ���
    ���������
            ��
��    �أ� 
    ����д :  0
    д�ɹ� :  1
    дʧ�� : -1 
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_flash_status(UINT32_T flash_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
	return 1;
}

/**************************************************************************
��������: 
            rocme_porting_flash_erase
����˵��: 
            ����ָ��flash�洢�ռ��е����ݡ�
����˵����
    ���������
            [ flash_addr  ] : �м����Ҫ����flash��Ŀ���ַ
            [ nbytes      ] : �����ĳ���
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( flash�����ɹ� )
    ʧ�� : -1 �� ������ ( flash����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_flash_erase(UINT32_T flash_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
#if 0
	FILE *fp = NULL;
	
	if((flash_addr<rocme_buffer)||((flash_addr+nbytes)>(rocme_buffer+rocme_size) ))
	{
		return ROC_ERR;
	}
	memset(flash_addr,0xff,nbytes);
	
	fp = fopen(rocme_data_path, "r+b");
	if(fp)
	{
		fwrite(rocme_buffer, 1, rocme_size, fp);
		fflush(fp);
		fsync((int)fp);
		fclose(fp);
		return ROC_OK;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[ipanel_porting_nvram_burn] open file \"%s\" failed \r\n", rocme_data_path);
		return ROC_ERR;
	}
#endif
	INT32_T error;
	FILE *flashfile;
	INT32_T i = 0;

	flash_addr -= 1;
    if( (flash_addr+nbytes) > rocme_size)
    {
        return (-1);
    }	 

	flashfile = fopen(rocme_data_path, "rb+");
	if(flashfile==NULL)
	{
		return (-1);
	}

	error = fseek(flashfile, flash_addr, SEEK_SET);
	if(error!=0)
	{
		fclose(flashfile);
		return (-1);
	}

	for( i=0; i<nbytes; i++ )
	{
		UINT8_T x = 0xff;
		nbytes = fwrite(&x, 1, 1, flashfile);
		if(nbytes == -1)
		{
			fclose(flashfile);
			return (-1);
		}
	}

	fclose(flashfile);
	return 0;

}

/**************************************************************************
��������: 
            rocme_porting_get_iframe_data
����˵��: 
            ȡ��ָ��ID��I֡���ݣ�Ŀǰ�м��Ҫ����2��Ĭ��I֡��Iframe_idΪ0ʱ��
        ������Ĭ�ϱ���֡��Iframe_idΪ1ʱ��������Ƶ��Ŀ����֡��ÿ��I֡��С
        ���ɳ���64Kb��
����˵����
    ���������
            [ Iframe_id     ] : I֡���
            [ *pdata        ] : �洢I֡buff��ͷָ��
            [ container_len ] : �洢I֡buff����󳤶ȣ�ĿǰRocME�м��������
                            Ϊ65536�ֽ�(64Kb)��С��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ȡI֡���ݳɹ� )
    ʧ�� : -1 �� ������ ( ��ȡI֡����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_iframe_data(UINT32_T Iframe_id,const UINT8_T *pdata,const UINT32_T container_len)
{
ROCME_TEST_PRINT
	FILE *fp = NULL;
	if(Iframe_id ==1)
	{
		fp = fopen(rocme_iframe1_data, "rb");
		if(fp)
		{
			fread(pdata, 1, container_len, fp);
			fclose(fp);
			return ROC_OK;
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_get_iframe1_data] open file \"%s\" failed \r\n", rocme_iframe0_data);
			return ROC_ERR;
		}
	}
	else if(Iframe_id ==0)
	{
		fp = fopen(rocme_iframe0_data, "rb");
		if(fp)
		{
			fread(pdata, 1, container_len, fp);
			fclose(fp);
			return ROC_OK;
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_get_iframe0_data] open file \"%s\" failed \r\n", rocme_iframe1_data);
			return ROC_ERR;
		}
	}
}

/**************************************************************************
��������: 
            rocme_porting_save_Iframe
����˵��: 
            ����I֡����Ӧ��I֡�洢�ռ䡣
����˵����
    ���������
            [ Iframe_id     ] : I֡���
            [ *pdata        ] : �洢I֡buff��ͷָ��
            [ container_len ] : I֡buff�ĳ��ȣ�ĿǰRocME�м�����������Ϊ
                            65536�ֽ�(64Kb)��С��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����I֡���ݳɹ� )
    ʧ�� : -1 �� ������ ( ����I֡����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_save_Iframe(UINT32_T Iframe_id,const UINT8_T *pdata,const UINT32_T len)
{
ROCME_TEST_PRINT
	FILE *fp = NULL;
	if(Iframe_id ==1)
	{
		fp = fopen(rocme_iframe0_data, "r+b");
		if(fp)
		{
			fwrite(pdata, 1, len, fp);
			fflush(fp);
			fsync((int)fp);
			fclose(fp);
			return ROC_OK;
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_get_iframe1_data] open file \"%s\" failed \r\n", rocme_iframe0_data);
			return ROC_ERR;
		}
	}
	else if(Iframe_id ==0)
	{
		fp = fopen(rocme_iframe1_data, "r+b");
		if(fp)
		{
			fwrite(pdata, 1, len, fp);
			fflush(fp);
			fsync((int)fp);
			fclose(fp);
			return ROC_OK;
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_get_iframe0_data] open file \"%s\" failed \r\n", rocme_iframe1_data);
			return ROC_ERR;
		}
	}
}

/**************************************************************************
��������: 
            rocme_porting_flash_save_boot_pic
����˵��: 
            ���濪��ͼƬ����Ӧ��flash�ռ䡣
����˵����
    ���������
            [ type          ] : �ļ����淽����0Ϊ�ڴ淽ʽ��1Ϊ�ļ���ʽ��
            [ *data_ptr     ] : ͼƬ�ڴ��ַ���ߴ洢·��
            [ data_len      ] : ͼƬ��С
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �������ݳɹ� )
    ʧ�� : -1 �� ������ ( ��������ʧ�� )
ע�⣺
    ������ͼƬ����Ҫ������Ϣ10602.
**************************************************************************/
INT32_T rocme_porting_flash_save_boot_pic(UINT8_T type, const CHAR_T *data_ptr, const UINT32_T data_len)
{
ROCME_TEST_PRINT
    FILE* fp = NULL;
    SysNetworkEvent_t stEvent;
    if((type < 0) || (type > 1))
    {
        return -1;
    }
	if(type == 0)
	{
		TDRV_FLASH_EraseEx(ROCME_LOGO_ADDR,ROCME_LOGO_FLASH_SIZE);
		TDRV_FLASH_Write(ROCME_LOGO_ADDR, data_len, data_ptr);
	}
	else
	{
		fp = fopen(data_ptr, "wb");
	    if(fp)
	    {
			unsigned char *p =NULL;
			p = rocme_porting_malloc(data_len);
			if(p==NULL)
			{
				return -1;
			}
			memset(p,0xff,data_len);
			
			fread(p,1,data_len,fp);
			TDRV_FLASH_EraseEx(ROCME_LOGO_ADDR,ROCME_LOGO_FLASH_SIZE);
			TDRV_FLASH_Write(ROCME_LOGO_ADDR, data_len, p);

	    }
	    else
	    {
	        return -1;
	    }
	}
    /*��Ҫ������Ϣ10602*/
    stEvent.msgType = ROC_SYSEVENT_TYPE;
    stEvent.msg = 10602;
    stEvent.modifiers[0] = 0;
    network_event_cbk(0, &stEvent, sizeof(stEvent));
    
    return 0;

}

/**************************************************************************
��������: 
            rocme_porting_flash_set_boot_tag
����˵��: 
            ��һ����ʶд������С�
����˵����
    ���������
            [ index         ] : �ñ�ʶָ����ʱ��2������Ӧ�ã�1��A��Ӧ�ã�0��Ĭ��Ӧ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������óɹ� )
    ʧ�� : -1 �� ������ ( �������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_flash_set_boot_tag(UINT32_T index)
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}

