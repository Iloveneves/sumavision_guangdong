/*****************************************************************************
File name   : rocme_porting_base.h

Author		: XXX			

Description : The poriting interface & macro definition for BASE module.
	          
Copyright (C) BeiJing SUMAVision, Inc., 2009 .All rights reserved.

History		:
				2009.12.20  		Created 					
*****************************************************************************/
#ifndef _ROCME_PORTING_BASE_H_
#define _ROCME_PORTING_BASE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"

//#define rocme_porting_dprintf(fmt, ...)   printf(fmt, ...)

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
void *rocme_porting_malloc(const INT32_T size);


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
void *rocme_porting_realloc(void * ptr, const INT32_T size);


/*****************************************************************************
����˵��: 
    �ͷ��ڴ�

����˵��:
    �������:
        [ptr] ָ����ǰ��rocme_porting_malloc��rocme_porting_realloc�����ص��ڴ�ָ��

��    ��:
    ��	
*****************************************************************************/
void rocme_porting_free(void* ptr);


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
INT32_T rocme_porting_dprintf(const CHAR_T* fmt, ...);


/*****************************************************************************
����˵��: 
    ��ȡ�Ի��������������ĺ�����

����˵��:
    ��

��    ��:
    ʧ��: -1              
    �ɹ�: �Ի��������������ĺ�����					
*****************************************************************************/
UINT32_T rocme_porting_time_ms(void);


/*****************************************************************************
����˵��: 
    ��������������״̬

����˵��:
    ��

��    ��:
    ʧ��: -1              
    �ɹ�:  0					
*****************************************************************************/
INT32_T rocme_porting_standby(void);


/*****************************************************************************
����˵��: 
    ��û����д���״̬

����˵��:
    ��

��    ��:
    1: ֧�������   --��ʱ���Ե���rocme_porting_standby���������״̬
    0: ��֧�ּٴ��� --��ʱ���м�����ƽ���ٴ���״̬					
*****************************************************************************/
INT32_T rocme_porting_standby_mode(void);


/*****************************************************************************
����˵��: 
    �������������� 

����˵��:
    ��

��    ��:
    ʧ��: -1              
    �ɹ�:  0					
*****************************************************************************/
INT32_T rocme_porting_reset_system(void);


#ifdef __cplusplus
}
#endif

#endif