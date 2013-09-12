/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_base.c
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
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
����˵��: 
    �����ڴ�ռ�

����˵��:
    �������:
        [size] Ҫ������ڴ�ռ�Ĵ�С

��    ��:
    ʧ��: NULL              
    �ɹ�: �ڴ�ָ��						
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
����˵��: 
    ��ptr����Ĵ���ռ�ı�Ϊ�����Ĵ�Сsize��size���Դ��ڻ�С��ԭ�ߴ硣

����˵��:
    �������:
        [ptr ] Ҫ�ı���ڴ�ռ�ĵ�ַ
        [size] Ҫ������ڴ�ռ�Ĵ�С

��    ��:
    ʧ��: NULL              
    �ɹ�: �ڴ�ָ��	
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
����˵��: 
    �ͷ��ڴ�

����˵��:
    �������:
        [ptr] ָ����ǰ��rocme_porting_malloc��rocme_porting_realloc�����ص��ڴ�ָ��

��    ��:
    ��	
*****************************************************************************/
void rocme_porting_free(void* ptr)
{
//ROCME_TEST_PRINT
	free(ptr);
	return;
}


/*****************************************************************************
����˵��: 
    ��ʽ���������

����˵��:
    �������:
        [fmt] Ҫ��ʽ���������

��    ��:
    ʧ��: -1              
    �ɹ�: ������ֽ���				
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
����˵��: 
    ��ȡ�Ի��������������ĺ�����

����˵��:
    ��

��    ��:
    ʧ��: -1              
    �ɹ�: �Ի��������������ĺ�����					
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
����˵��: 
    ��������������״̬

����˵��:
    ��

��    ��:
    ʧ��: -1              
    �ɹ�:  0					
*****************************************************************************/
INT32_T rocme_porting_standby(void)
{
ROCME_TEST_PRINT
	exit(254);
	return 0;
}


/*****************************************************************************
����˵��: 
    ��û����д���״̬

����˵��:
    ��

��    ��:
    1: ֧�������   --��ʱ���Ե���rocme_porting_standby���������״̬
    0: ��֧�ּٴ��� --��ʱ���м�����ƽ���ٴ���״̬					
*****************************************************************************/
INT32_T rocme_porting_standby_mode(void)
{
ROCME_TEST_PRINT
	return 1;
}


/*****************************************************************************
����˵��: 
    �������������� 

����˵��:
    ��

��    ��:
    ʧ��: -1              
    �ɹ�:  0					
*****************************************************************************/
INT32_T rocme_porting_reset_system(void)
{
ROCME_TEST_PRINT
	system("reboot");
	return 0;

}


