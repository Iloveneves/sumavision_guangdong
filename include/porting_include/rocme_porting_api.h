/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_api.h

Author      : DSM

Description : The porting APIs called by manufactor implement by SUMA.

History     :
              2009.12.20          Created         Jason

*******************************************************************************/
#ifndef _SMSX_ROCME_PORTING_API_H_
#define _SMSX_ROCME_PORTING_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"

typedef struct _rocme_time_t{
    INT32_T tm_sec;     /* seconds after the minute - [0,59] */
    INT32_T tm_min;     /* minutes after the hour - [0,59] */
    INT32_T tm_hour;    /* hours since midnight - [0,23] */
    INT32_T tm_mday;    /* day of the month - [1,31] */
    INT32_T tm_mon;     /* months since January - [0,11] */
    INT32_T tm_year;    /* years since 1900 */
}rocme_time_t;

/*****************************************************************************
����˵��: 
    ��ʾ�����г���˽����Ϣ
    
    �������ô˺���֪ͨ�м����ʾ��˽��������Ϣ��
    ��ҪӦ���ڻ����г�������������
    
����˵��: 
    �������:
        [ *Info ] : �����г���Ҫ��ʾ����Ϣ��
        �˽ӿ�ֻ����ȫ����������Ƶ����µ�����Ч��    
*****************************************************************************/
void rocme_porting_api_ShowManufactureInfo(const CHAR_T* Info,UINT32_T len);


/*****************************************************************************
������:
    rocme_porting_get_currenttime
����˵��: 
    �����е��ô˺�����ȡ��ǰʱ�䡣
����˵��:
    �������:
        [*time ] ��ǰʱ��,�ο�rocme_time_t�ṹ
��    ��:
    �ɹ�: 0
    ʧ��: ����ֵ
��ע:
    �м��ʵ�ִ˺����������е��á�
*/
INT32_T rocme_porting_api_get_currenttime(rocme_time_t *ptime);


#ifdef __cplusplus
}
#endif

#endif
