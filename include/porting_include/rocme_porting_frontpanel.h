/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_frontpanel.h

Author      : DSM

Description : The poriting interface & macro definition for FRONTPANEL module.

History     :
              2009.12.20          Created         Jason
              2010.01.10          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTING_FRONTPANEL_H_
#define _ROCME_PORTING_FRONTPANEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/

/**************************************************************************
函数名称: 
            rocme_porting_frontpanel_init
功能说明: 
            前面板设备初始化，中间件会在启动时调用此函数，若在启动中间件
        之前机顶盒已经做好了前面板相关的初始化，此函数可以实现为空，直接返回0。
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
INT32_T rocme_porting_frontpanel_init(void);

/**************************************************************************
函数名称: 
            rocme_porting_frontpanel_show_string
功能说明: 
            前面板显示字符串功能，要求至少提供显示4个字符，至少支持如下字符:
       " 0 1 2 3 4 5 6 7 8 9 A E F L N O P S T U V a d g i l n o r t u v "。
参数说明：
    输入参数：
            [ *pBuf   ] : 字符串头指针
            [ len     ] : 字符串长度，最大不会超过4
    输出参数：
            无
返    回： 
    成功 : 0            ( 显示字符串成功 )
    失败 : -1 或 错误码 ( 显示字符串失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_string(CHAR_T *pBuf,UINT32_T len);

/**************************************************************************
函数名称: 
            rocme_porting_frontpanel_show_2point
功能说明: 
            前面板上显示时间分隔符( : )功能。
参数说明：
    输入参数：
            [ is_show   ] : 是否显示时间分隔符标识
                            ROC_TRUE   -  显示
                            ROC_FALSE  -  不显示
    输出参数：
            无
返    回： 
    成功 : 0            ( 显示时间分隔符成功 )
    失败 : -1 或 错误码 ( 显示时间分隔符失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_2point(ROC_BOOL is_show);

/**************************************************************************
函数名称: 
            rocme_porting_frontpanel_show_led
功能说明: 
            前面板LED灯控制功能，索引0代表tuner锁定指示灯，1代表电源指示灯。
参数说明：
    输入参数：
            [ len_index   ] : LED灯索引号，0代表tuner锁定指示灯，1代表电源指示灯
            [ on_off      ] : 是否显示LED灯标识
                              ROC_TRUE   -  显示
                              ROC_FALSE  -  不显示                        
    输出参数：
            无
返    回： 
    成功 : 0            ( 显示时间分隔符成功 )
    失败 : -1 或 错误码 ( 显示时间分隔符失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_led(UINT8_T len_index,ROC_BOOL on_off);

/**************************************************************************
函数名称: 
            rocme_porting_frontpanel_show_time
功能说明: 
            前面板显示时间功能，要求根据传入的开始时间，前面板开始显示时间，
        直至再次调用此函数关闭，显示时间期间前面板不必响应其他字符串请求。
        例如若要求开始显示时间为18:20，则on_off = ROC_TRUE,*time24h = "1820"，
        当显示时间成功开始后，前面板应显示"18:20"，并且按照/分钟的频率进行刷
        新，逐次显示"18:21"、"18:22"... ... ，当需要结束时间显示时，传入参数
        on_off = ROC_FALSE,*time24h = NULL或任意，此时前面板需要将显示清空。
参数说明：
    输入参数：
            [ on_off      ] : 是否显示时间标识，只有当ROC_TRUE时，参数*time24h
                          才起作用。
                              ROC_TRUE   -  显示
                              ROC_FALSE  -  不显示                               
            [ *time24h    ] : 时间字符串头指针，当on_off=ROC_TRUE时有效
    输出参数：
            无
返    回： 
    成功 : 0            ( 开启/关闭时间显示成功 )
    失败 : -1 或 错误码 ( 开启/关闭时间显示失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_time(ROC_BOOL on_off,CHAR_T *time24h);


#ifdef __cplusplus
}
#endif

#endif
