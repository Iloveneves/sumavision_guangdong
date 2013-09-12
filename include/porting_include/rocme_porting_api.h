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
功能说明: 
    显示机顶盒厂商私有信息
    
    机顶盒用此函数通知中间件显示其私有数据信息，
    主要应用于机顶盒厂商生产测试用
    
参数说明: 
    输入参数:
        [ *Info ] : 机顶盒厂商要显示的信息。
        此接口只有在全屏播放视音频情况下调用有效。    
*****************************************************************************/
void rocme_porting_api_ShowManufactureInfo(const CHAR_T* Info,UINT32_T len);


/*****************************************************************************
函数名:
    rocme_porting_get_currenttime
功能说明: 
    机顶盒调用此函数获取当前时间。
参数说明:
    输出参数:
        [*time ] 当前时间,参考rocme_time_t结构
返    回:
    成功: 0
    失败: 其它值
备注:
    中间件实现此函数供机顶盒调用。
*/
INT32_T rocme_porting_api_get_currenttime(rocme_time_t *ptime);


#ifdef __cplusplus
}
#endif

#endif
