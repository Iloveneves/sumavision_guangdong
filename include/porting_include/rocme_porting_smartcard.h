/*******************************************************************************
File name   : rocme_porting_smartcard.h

Author      : XXX

Description : The poriting interface & macro definition for SMC module.

Copyright (C) BeiJing SUMAVision, Inc., 2009 .All rights reserved.

History     :
        2009.12.20          Created
        2010.01.11          Add sc event callback register
*******************************************************************************/
#ifndef _ROCME_PORTING_SMARTCARD_H_
#define _ROCME_PORTING_SMARTCARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"

/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/
/*ROCME智能卡事件定义*/
typedef enum Roc_ScEvt_e
{
    ROC_SC_REMOVE       = 0x0,   /*拔出智能卡事件*/
    ROC_SC_INSERT       = 0x1,   /*插入智能卡事件*/
    ROC_SC_RESET_FAULT  = 0x2    /*智能卡插入，但复位无效*/
} Roc_ScEvt_t;

typedef void (*rocme_porting_sc_callback) ( void *param, Roc_ScEvt_t event);

typedef struct Roc_Sc_RegParam_s
{
    rocme_porting_sc_callback    callback;   /*回调函数*/
    void                         *cb_param;  /*回调函数的私有参数*/
}Roc_Sc_RegParam_t;


/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/

/***************************************************************************
功能说明：
     初始化智能卡

参数说明：
    输入参数： 空
    输出参数： 无

返    回： 
    成功 : 0            (初始化成功)
    失败 : -1 或 错误码 (初始化失败)

参考实现：
    rocme_smartcard.c
***************************************************************************/
INT32_T rocme_porting_smartcard_init(void);


/***************************************************************************
功能说明：
        卸载(关闭)智能卡。

参数说明：
    输入参数： 空
    输出参数： 无

返    回： 
    成功 : 0            (卸载成功)
    失败 : -1 或 错误码 (卸载失败)

参考实现：
    rocme_smartcard.c
***************************************************************************/
INT32_T rocme_porting_smartcard_term(void);


/***************************************************************************
功能说明：
        智能卡复位

参数说明：
    输入参数： 空
    输出参数： 无

返    回： 
    成功 : 0            ( )
    失败 : -1 或 错误码 ( )

参考实现：
    rocme_smartcard.c
***************************************************************************/
INT32_T rocme_porting_smartcard_reset(UINT8_T * pbyATR, UINT8_T * pbyLen);


/***************************************************************************
功能说明：
        与智能卡通信,按照ISO-7816为规范

参数说明：
    输入参数： 
        pLen:        输入:指令字节长度(单位:字节);
                     输出:应答内容长度(单位:字节) 
        
        byszCommand: 指令,通常头5个字节格式为:CLS INS P1 P2 P3;   

        byszReply:   输入:已分配的应答内容空间,空间长度为256 字节
                     输出:智能卡应答内容

    输出参数： 无

返    回： 
    成功 : 0            ( )
    失败 : -1 或 错误码 ( )

参考实现：
    rocme_smartcard.c
***************************************************************************/
INT32_T rocme_porting_smartcard_transfer(INT32_T * pLen, const CHAR_T * byszCommand, CHAR_T * byszReply);


/***************************************************************************
功能说明：
        查询智能卡状态

参数说明：
    输入参数： 空
    输出参数： 无

返    回： 
    0    ----未插卡
    1    ----已插卡(已复位,可通信状态)
    其他 ----查询失败

参考实现：
    rocme_smartcard.c
***************************************************************************/
INT32_T rocme_porting_smartcard_state(void);


/***************************************************************************
功能说明：
    注册一个智能卡事件回调函数。
    当发生智能卡事件时，底层需要调用注册了的回调函数来通知中间件

参数说明：
    输入参数：
            param:参见Roc_Sc_RegParam_t数据结构定义

    输出参数： 
            handle:注册成功则输出handle，当中间取消注册时就依赖于此handle

返    回： 
    0    ----成功
    -1   ----失败

参考实现：
    rocme_smartcard.c
***************************************************************************/
UINT32_T rocme_porting_smartcard_register(Roc_Sc_RegParam_t param, UINT32_T *handle);


/***************************************************************************
函数名:
    rocme_porting_smartcard_unregister()

功能说明：
    取消一个智能卡事件回调函数的注册

参数说明：
    输入参数：
            [   handle] 注册成功时输出的handle

    输出参数： 
            无

返    回： 
    0    ----成功
    -1   ----失败

参考实现：
    rocme_smartcard.c
***************************************************************************/
INT32_T rocme_porting_smartcard_unregister(UINT32_T handle);

#ifdef __cplusplus
}
#endif

#endif
