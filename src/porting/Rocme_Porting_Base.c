/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_base.c
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/
#include "hi_type.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/time.h>


#include "porter_rocme.h"



#define ROCME_PORTING_DEBUG  1
unsigned long g_RocmeStartTime = 0;

/*****************************************************************************
功能说明: 
    分配内存空间

参数说明:
    输入参数:
        [size] 要分配的内存空间的大小

返    回:
    失败: NULL              
    成功: 内存指针						
*****************************************************************************/
void *rocme_porting_malloc(const INT32_T size)
{
//ROCME_TEST_PRINT
    void *pointer = NULL;


    pointer = (void *)calloc(1,size);

    if (pointer)
    {      
       // ROCME_PRINTF(ROCME_LOG_INFO,"[rocme_porting_malloc]malloc ok, memsize=0x%x.\n", size);
        
    }
    else
    {
        ROCME_PRINTF(ROCME_LOG_ERROR,"[rocme_porting_malloc]malloc fail, memsize=0x%x.\n", size);
    }

    return pointer;
}

/*****************************************************************************
功能说明: 
    将ptr对象的储存空间改变为给定的大小size，size可以大于或小于原尺寸。

参数说明:
    输入参数:
        [ptr ] 要改变的内存空间的地址
        [size] 要分配的内存空间的大小

返    回:
    失败: NULL              
    成功: 内存指针	
*****************************************************************************/
void *rocme_porting_realloc(void * ptr, const INT32_T size)
{
//ROCME_TEST_PRINT
	ptr=realloc(ptr,size);
	
	if(ptr)
		return ptr;
	else
		return NULL;
	
}


/*****************************************************************************
功能说明: 
    释放内存

参数说明:
    输入参数:
        [ptr] 指向先前由rocme_porting_malloc、rocme_porting_realloc所返回的内存指针

返    回:
    无	
*****************************************************************************/
void rocme_porting_free(void* ptr)
{
//ROCME_TEST_PRINT
	free(ptr);
	return;
}


/*****************************************************************************
功能说明: 
    格式化输出数据

参数说明:
    输入参数:
        [fmt] 要格式化输出数据

返    回:
    失败: -1              
    成功: 输出的字节数				
*****************************************************************************/

INT32_T rocme_porting_dprintf(const CHAR_T* fmt, ...)
{

	HI_S32 ret = 0;

	if (ROCME_PORTING_DEBUG)
	{

		va_list args;
		va_start(args,fmt);
		ret = vprintf(fmt,args);
		va_end(args);
		fflush(stdout);

	}

	return ret;

}




/*****************************************************************************
功能说明: 
    获取自机顶盒启动以来的毫秒数

参数说明:
    无

返    回:
    失败: -1              
    成功: 自机顶盒启动以来的毫秒数					
*****************************************************************************/
UINT32_T rocme_porting_time_ms(void)
{
//ROCME_TEST_PRINT
	struct timeval	 tm;
	struct timezone tz;


	if(0 != gettimeofday( &tm, &tz ))
	{
		return -1;
	}
	return tm.tv_sec * 1000 + tm.tv_usec / 1000;
}


/*****************************************************************************
功能说明: 
    进入机顶盒真待机状态

参数说明:
    无

返    回:
    失败: -1              
    成功:  0					
*****************************************************************************/
INT32_T rocme_porting_standby(void)
{
ROCME_TEST_PRINT
	exit(254);
	return 0;
}


/*****************************************************************************
功能说明: 
    获得机顶盒待机状态

参数说明:
    无

返    回:
    1: 支持真待机   --此时可以调用rocme_porting_standby进入真待机状态
    0: 不支持假待机 --此时由中间件控制进入假待机状态					
*****************************************************************************/
INT32_T rocme_porting_standby_mode(void)
{
ROCME_TEST_PRINT
	return 1;
}


/*****************************************************************************
功能说明: 
    重新启动机顶盒 

参数说明:
    无

返    回:
    失败: -1              
    成功:  0					
*****************************************************************************/
INT32_T rocme_porting_reset_system(void)
{
ROCME_TEST_PRINT
	system("reboot");
	return 0;

}


