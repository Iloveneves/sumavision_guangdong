/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_flash.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
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
函数名称: 
            rocme_porting_flash_init
功能说明: 
            flash存储设备初始化，中间件会在启动时调用此函数，若在启动中间件
        之前机顶盒已经做好了flash设备的初始化，此函数可以实现为空，直接返回0。
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
函数名称: 
            rocme_porting_flash_info
功能说明: 
            获得flash存储空间的起始地址、块数和每块的长度，建议给RocME中间件
        划分的flash memory每块合适尺寸是32k/64k/128k/256kBytes。但flash的最小
        空间不得小于512k。
参数说明：
    输入参数：
            无
    输出参数：
            [ *addr       ] : 分配给中间件的flash的起始地址头指针
            [ num_of_sect ] : 分配给中间件的flash的总块数
            [ sect_size   ] : 分配给中间件的flash的每块的大小
返    回： 
    成功 : 0            ( flash基本信息获取成功 )
    失败 : -1 或 错误码 ( flash基本信息获取失败 )
修改记录：
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
函数名称: 
            rocme_porting_flash_read
功能说明: 
            从指定的flash存储空间的指定地址读取数据到指定的数据缓冲区中。
参数说明：
    输入参数：
            [ flash_addr  ] : 中间件读取flash的目标地址
            [ *buff_addr  ] : 读取数据的存储缓冲区头指针
            [ nbytes      ] : 需要读取的长度
    输出参数：
            无
返    回： 
    成功 : >=0的数值    ( 实际读取的数据长度 )
    失败 : -1 或 错误码 ( 读取flash内容失败  )
修改记录：
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
函数名称: 
            rocme_porting_flash_burn
功能说明: 
            将指定的数据写入到指定的flash存储区中，实现为同步方式写入。
参数说明：
    输入参数：
            [ flash_addr  ] : 中间件写入flash的目标地址
            [ *buff_addr  ] : 写入数据的存储缓冲区头指针
            [ nbytes      ] : 需要写入的长度
    输出参数：
            无
返    回： 
    成功 : >=0的数值    ( 实际写入的数据长度 )
    失败 : -1 或 错误码 ( 写入flash内容失败  )
修改记录：
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
函数名称: 
            rocme_porting_flash_status
功能说明: 
            判断当前flash的写入状态，此函数目前不做要求，可以实现为空，直接返
        回已经写成功( 1 )即可。
参数说明：
    输入参数：
            [ flash_addr  ] : 中间件写入flash的目标地址
            [ nbytes      ] : 写入的长度
    输出参数：
            无
返    回： 
    正在写 :  0
    写成功 :  1
    写失败 : -1 
修改记录：
**************************************************************************/
INT32_T rocme_porting_flash_status(UINT32_T flash_addr, INT32_T nbytes)
{
ROCME_TEST_PRINT
	return 1;
}

/**************************************************************************
函数名称: 
            rocme_porting_flash_erase
功能说明: 
            擦除指定flash存储空间中的数据。
参数说明：
    输入参数：
            [ flash_addr  ] : 中间件需要擦除flash的目标地址
            [ nbytes      ] : 擦除的长度
    输出参数：
            无
返    回： 
    成功 : 0            ( flash擦除成功 )
    失败 : -1 或 错误码 ( flash擦除失败 )
修改记录：
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
函数名称: 
            rocme_porting_get_iframe_data
功能说明: 
            取得指定ID的I帧数据，目前中间件要求有2幅默认I帧，Iframe_id为0时，
        代表开机默认背景帧，Iframe_id为1时，代表音频节目背景帧，每幅I帧大小
        不可超过64Kb。
参数说明：
    输入参数：
            [ Iframe_id     ] : I帧编号
            [ *pdata        ] : 存储I帧buff的头指针
            [ container_len ] : 存储I帧buff的最大长度，目前RocME中间件定义其
                            为65536字节(64Kb)大小。
    输出参数：
            无
返    回： 
    成功 : 0            ( 获取I帧数据成功 )
    失败 : -1 或 错误码 ( 获取I帧数据失败 )
修改记录：
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
函数名称: 
            rocme_porting_save_Iframe
功能说明: 
            保存I帧到对应的I帧存储空间。
参数说明：
    输入参数：
            [ Iframe_id     ] : I帧编号
            [ *pdata        ] : 存储I帧buff的头指针
            [ container_len ] : I帧buff的长度，目前RocME中间件定义其最大为
                            65536字节(64Kb)大小。
    输出参数：
            无
返    回： 
    成功 : 0            ( 保存I帧数据成功 )
    失败 : -1 或 错误码 ( 保存I帧数据失败 )
修改记录：
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
函数名称: 
            rocme_porting_flash_save_boot_pic
功能说明: 
            保存开机图片到对应的flash空间。
参数说明：
    输入参数：
            [ type          ] : 文件保存方法，0为内存方式，1为文件方式。
            [ *data_ptr     ] : 图片内存地址或者存储路径
            [ data_len      ] : 图片大小
    输出参数：
            无
返    回： 
    成功 : 0            ( 保存数据成功 )
    失败 : -1 或 错误码 ( 保存数据失败 )
注意：
    保存完图片后，需要发送消息10602.
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
    /*需要发送消息10602*/
    stEvent.msgType = ROC_SYSEVENT_TYPE;
    stEvent.msg = 10602;
    stEvent.modifiers[0] = 0;
    network_event_cbk(0, &stEvent, sizeof(stEvent));
    
    return 0;

}

/**************************************************************************
函数名称: 
            rocme_porting_flash_set_boot_tag
功能说明: 
            将一个标识写入机顶盒。
参数说明：
    输入参数：
            [ index         ] : 该标识指定在时段2是运行应用，1是A类应用，0是默认应用
    输出参数：
            无
返    回： 
    成功 : 0            ( 标记设置成功 )
    失败 : -1 或 错误码 ( 标记设置失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_flash_set_boot_tag(UINT32_T index)
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}

