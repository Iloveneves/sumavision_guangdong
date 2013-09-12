/******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_cas.h

Author      : 

Description : The poriting interface & macro definition for CAS module.
              此头文件包含3部分内容:
              1. 常量、结构体定义
              2. 要求机顶盒（实际是CAS厂商的CA模块，经机顶盒中转）提供的接口，
                 中间件根据自己的界面和流程进行调用
              3. 中间件实现的接口，供机顶盒（实际是CAS厂商的CA模块，经机顶盒
                 中转）调用

              对INT32_T类型返回值，如无特别说明，0表示成功，其他表示错误号。
              广东项目返回的错误号请参考省网规范中相关定义。
              
History     :
              2010.01.26          Created         
              2010.06.08          modify EMM&ECM API
              2011.02.10          modify for guangdong
*******************************************************************************/

#ifndef _ROCME_PORTING_CAS_H_2010_01_26_
#define _ROCME_PORTING_CAS_H_2010_01_26_


#include "rocme_porting_typedef.h"
#include "rocme_porting_event.h"

/*++++++++++++++++++++++++++++    常量定义    ++++++++++++++++++++++++++++*/

/* 最大限制常量 */
#define ROC_CAS_MAX_WALLET_COUNT                  4     /* 每个运营商最多钱包数*/
#define ROC_CAS_MAX_TVS_COUNT                     5     /* 最大运营商个数 */
#define ROC_CAS_MAX_ENTITLE_COUNT               300     /* 最大授权记录个数 */
#define ROC_CAS_MAXLEN_PRODUCT_NAME              21     /* 最长的产品名称,最多20个字符+\0 */
#define ROC_CAS_MAXLEN_SERVICE_NAME              21     /* 最长的业务名称,最多20个字符+\0 */
#define ROC_CAS_MAXLEN_TVSINFO                   33     /* 运营商信息长度,包括\0*/
#define ROC_CAS_MAXLEN_CARDID                    21     /* 最大智能卡号,最多20个字符+\0 */
#define ROC_CAS_MAXLEN_PROVIDERNAME              21     /* 最大CA厂商名称,最多20个字符+\0 */
#define ROC_CAS_MAXLEN_VERSION                   21     /* 最长版本号,最多20个字符+\0 */
#define ROC_CAS_MAXLEN_IPP                      250     /* 最大IPP节目个数 */
#define ROC_CAS_MAXLEN_EMAIL_TITLE               21     /* 最长邮件标题,20个字符+\0*/
#define ROC_CAS_MAXLEN_EMAIL_CONTENT           3073     /* 最长邮件内容,3072个字符+\0*/
#define ROC_CAS_MAXLEN_EMAIL_SEND_NAME           11     /* 最大邮件发送者名称,10个字符+\0*/

/* INT32_T类型返回值的错误号定义 */
#define ROC_CAS_OK                                0    /* 成功 */
#define ROC_CAS_UNIMPL_INF                       -1    /* 未实现的接口 */

/* 语言类型，rocme_porting_ChangeLanguage使用 */
#define ROC_CAS_LANG_CHN_SIM                   1    /* 简体中文(默认) */
#define ROC_CAS_LANG_ENG                       2    /* 英文 */

/*CA提供商*/
typedef enum ROC_CAS_PROVIDER
{
    ROC_CAS_SUMAVISION      = 0x00,     /* 数码视讯     */
    ROC_CAS_NDS             = 0x01,     /* NDS          */
    ROC_CAS_IRDETO          = 0x02,     /* Irdeto       */
    ROC_CAS_CONAX           = 0x03,     /* CONAX        */
    ROC_CAS_NAGRAVISION     = 0x04,     /* Nagravision  */
    ROC_CAS_VIACESS         = 0x05,     /* Viacess      */
    ROC_CAS_NOVEL           = 0x06,     /* 永新视博     */
    ROC_CAS_DVN             = 0x07,     /* 天柏         */
    ROC_CAS_CTI             = 0x08,     /* 算通         */
    ROC_CAS_RESERVE0,
    ROC_CAS_RESERVE1
}ROC_CAS_PROVIDER_e;

typedef enum ROC_CA_EVENT
{
    ROC_CA_EVENT_IPP                = 11701,
    ROC_CA_EVENT_HIDE_PROMPT_MSG    = 11702,
    ROC_CA_EVENT_RESERVE    
}ROC_CA_EVENT_e;


/*++++++++++++++++++++++++++++    结构体定义    ++++++++++++++++++++++++++++*/


/* 运营商信息 */
typedef struct _Roc_OperatorInfo{
    UINT16_T m_wTVSID;                              /* 运营商的外部编号 */
    INT8_T   m_szTVSName[ROC_CAS_MAXLEN_TVSINFO];   /* 运营商名称或其他信息,CA不支持此项则m_szTVSName[0]=0*/
    UINT8_T  m_byServiceStatus;                     /* 运营商对此卡的服务状态，0正常工作，1限制工作 */
}Roc_OperatorInfo;

/* 授权信息 */
typedef struct _Roc_ServiceEntitle{
    UINT16_T    m_wProductID;                       /* 产品号 */
    UINT32_T    m_tStartTime;                       /* 开始时间 */
    UINT32_T    m_tEndTime;                         /* 结束时间，有些cas没有，有些运营商要求不显示 */
    INT8_T      m_ProductName[ROC_CAS_MAXLEN_PRODUCT_NAME];                  /* 产品名称。没有则将m_ProductName[0]赋值为0*/
}Roc_ServiceEntitle;/*普通产品授权*/


/* mail 头信息 */
typedef struct _Roc_EmailInfo{
    UINT32_T    m_dwVersion;                                    /* 邮件标识 */
    INT8_T      m_szSenderName[ROC_CAS_MAXLEN_EMAIL_SEND_NAME]; /* 发送者姓名。若CA没有此结构,则填为运营商ID*/
    UINT8_T     m_Status;                                       /* 邮件的状态，0未读邮件， 1已读邮件 */
    INT8_T      m_szTitle[ROC_CAS_MAXLEN_EMAIL_TITLE];          /* 邮件短内容，带'\0'的字符串，从邮件内容开头截取一部分 */
    UINT16_T    m_wImportance;                                  /* 重要性。0普通,1重要。若CA没有此结构则都置为普通 */
    UINT32_T    m_dwCreateTime;                                 /* 邮件发送时间,time_t格式*/
}Roc_EmailInfo;

/* mail 信息 */
typedef struct _Roc_EmailContent{
    INT8_T      m_szEmail[ROC_CAS_MAXLEN_EMAIL_CONTENT];    /* 邮件内容，带'\0'的字符串 兼容其他CA厂商,最大支持(ROC_CAS_MAXLEN_EMAIL_CONTENT)3073个字节的邮件*/
}Roc_EmailContent;

/* 设置ecm pid结构 */
typedef struct _Roc_ServiceInfo{
    UINT16_T    m_wEcmPid;                          /* 节目相应控制信息的PID。数码视讯只需要这个成员，其他成员值任意。永新同方需要其他成员值。 */                               
    UINT8_T     m_byServiceNum;                     /* 当前PID下的节目个数 */
    UINT16_T    m_wServiceID[4];                    /* 当前PID下的节目ID列表 */       
}Roc_ServiceInfo;

/* 设置ecm pid, 组件pid等信息 */
typedef struct _Roc_ComponentEcmInfo
{
    UINT16_T            component_pid;          /*组件PID*/
    UINT8_T             component_type;         /*组件类型，比如mpeg1、mpeg2、h.264视频，mpeg1第3层（mp3）、ac3音频，数据广播，私有类型等等*/
    UINT16_T            ca_system_id;           /*CA系统标识符,必须通过CA校验,不加密时传0*/
    UINT16_T            ecm_pid;                /*音\视频的ECM PID,不加密时传0*/
    UINT8_T             ca_private_data_len;    /*CA描述符内的私有数据长度,音\视频不加密时为0*/
    UINT8_T             *ca_private_data;       /*CA描述符内的私有数据,音\视频不加密时为NULL*/
}Roc_ComponentEcmInfo;

/* 设置ecm pid, 组件pid等信息 */
typedef struct _Roc_ComponentEmmInfo
{
    UINT16_T            ca_system_id;       /*CA系统标识符,必须通过CA校验*/
    UINT16_T            emm_pid;            /*Emm PID*/
    UINT8_T             ca_private_data_len;/*CA描述符内的私有数据长度,没有私有数据时传0*/
    UINT8_T             *ca_private_data;   /*CA描述符内的私有数据*/
}Roc_ComponentEmmInfo;


/* ipp相关数据结构 */
typedef struct _Roc_CAIpp{
    UINT16_T    m_wTVSID;                           /* 运营商编号 */
    UINT16_T    m_wProdID;                          /* 产品ID */
    UINT8_T     m_bySlotID;                         /* 钱包ID */
    INT8_T      m_szProdName[ROC_CAS_MAXLEN_PRODUCT_NAME];      /* 产品名称 */
    UINT32_T    m_tStartTime;                       /* 开始时间，time_t格式 */
    UINT32_T    m_tEndTime;                         /* 结束时间, time_t格式 */
    UINT16_T    m_wCurTppTapPrice;                  /* 当前的不回传、能录像价格(分)，价格类型值为0 */
    UINT16_T    m_wCurTppNoTapPrice;                /* 当前的不回传、不可录像价格(分)，价格类型值为1 */
    UINT16_T    m_wCurCppTapPrice;                  /* 当前的要回传、能录像价格(分)，价格类型值为2 */
    UINT16_T    m_wCurCppNoTapPrice;                /* 当前的要回传、不可录像价格(分)，价格类型值为3 */
    UINT8_T     m_byIppStatus;                      /* Ipp产品状态:低4位代表:0--IPPT类型;1--IPPV; 高4位代表:0--未订购;1--已订购*/
}Roc_CAIpp;

typedef struct _Roc_CAViewedIpp{
    UINT16_T    m_wTVSID;                           /* 运营商编号 */
    INT8_T      m_szProdName[ROC_CAS_MAXLEN_PRODUCT_NAME];   /* 产品名称。数码视讯有，永新同方无。 */
    UINT32_T    m_tStartTime;                       /* 开始时间，time_t格式。 */
    UINT32_T    m_tEndTime;                         /* 持续秒数 */
    UINT16_T    m_wBookedPrice;                     /* 预订价格*/
    UINT8_T     m_byBookedPriceType;                /* 预订价格类型:0:TppTap;1:TppNoTap;2:CppTap;3:CppNoTap; */
}Roc_CAViewedIpp;

typedef struct _Roc_TVSSlotInfo{
    UINT32_T m_dwBalance;            /* 已花费,单位:分 */
    UINT32_T m_dwRemainder;          /* 剩余,单位:分   */
    UINT16_T m_wSlotID;              /* 钱包ID，超过0xff表示此项无效不必显示，TF的给有效值，数码视讯的给无效值 */
}Roc_TVSSlotInfo;

/*----------------- 应急广播（强制切台）相关数据结构 --------------*/

/*
频率和符号率bcd编码方式举例:
    若频率为355000KHz，即355.0000MHz，则对应的m_dwFrequency的值应为0x03550000；
    若符号率为6875KHz，即6.8750MHz，则对应的m_symbol_rate的值应为0x00068750。

调制方式取值:
        0               Reserved
        1               QAM16
        2               QAM32
        3               QAM64
        4               QAM128
        5               QAM256
        6～255  Reserved
*/
typedef struct _Roc_Freq_Serv{
    UINT8_T     m_Modulation;           /* 调制方式 */
    UINT32_T    m_dwFrequency;          /* 频率，BCD码 */
    UINT32_T    m_symbol_rate;          /* 符号率，BCD码 */
    UINT16_T    m_wServiceID;           /* service id */
}Roc_Freq_Serv;

typedef struct _Roc_NetID_Serv{
    UINT16_T    m_wOriNetID;            /* 原始网络ID */
    UINT16_T    m_wTSID;                /* TSID */
    UINT16_T    m_wServiceID;           /* service id */
}Roc_NetID_Serv;

/*+++++++++++++++++++++以下为集成数码视讯CA时,机顶盒厂商需要实现的函数+++++++++++++++++++++++++++++*/
/*
函数名称:
    rocme_porting_ca_get_data_info

功能说明: 
    取得CA在FLASH中存储空间的地址和大小

参数说明:
    输入参数:
            无
    输出参数:
            [ addr   ] : CA在FLASH中存储空间的地址
            [ length ] : CA在FLASH中存储空间的大小

返    回: 
    成功: 0          
    失败: -1

备注:
    如果使用数码视讯CA，需实现此接口。如果使用其他厂商，此接口直接返回0；

修改记录:
*/
INT32_T rocme_porting_ca_get_data_info(UINT32_T *addr, UINT32_T *length);

/*++++++++++++++++++++++以上为集成数码视讯CA时,机顶盒厂商需要实现的函数+++++++++++++++++++++++++++*/






/*++++++++++++++++++++以下为集成非数码视讯CA时,机顶盒厂商需要实现的函数+++++++++++++++++++++++++++*/

/*
函数名称:
    rocme_porting_CASInit

功能说明:
    中间件启动的时候调用，对CAS模块初始化

参数说明:
    输入参数:
            无。
    输出参数:
            无。
返    回:
    成功: 0
    失败: -1
*/
INT32_T rocme_porting_CASInit(void);

/*
函数名称:
    rocme_porting_GetCASProvider

功能说明:
    获取cas的提供商

参数说明:
    输入参数:
            无。
    输出参数:
            [ *provider ]: cas提供商的枚举

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetCASProviderID( ROC_CAS_PROVIDER_e *provider );

/*
函数名称:
    rocme_porting_GetCASProvider

功能说明:
    获取cas的提供商的全称

参数说明:
    输出参数:
            [ *name ]: cas提供商的全称,最多21个字节,包含结束符

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetCASProviderName(CHAR_T * name);

/*
函数名称:
    rocme_porting_GetCASVer

功能说明:
    中间件获得CA模块的版本

参数说明: 
    输入参数:
            无。
    输出参数:
            [ *strVersion   ]: 输出版本号,最大21(ROC_CAS_MAXLEN_PROVIDERNAME)个字符,包含结束符

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetCASVer(CHAR_T *strVersion);

/*
函数名称:
    rocme_porting_GetCardID

功能说明: 
    获得智能卡内部ID。
    
参数说明: 
    输入参数:
            无。
    输出参数:
            [ *strCardID]: 输出智能卡内部ID,以'\0'结束的字符串，最大长度21(ROC_CAS_MAXLEN_VERSION)。

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetCardID(CHAR_T *strCardID);

/*
函数名称:
    rocme_porting_CASIDVerify

功能说明: 
    中间件获得CASID后调用该接口判断CASID是否有效，如果有效则返回ROC_TRUE，否则返回ROC_FALSE
    
参数说明:
    输入参数:
            wCaSystemID: 分析SI/PSI信息（pmt/cat表中的ca描述符）获得的CASID
    输出参数:
            无。

返    回:
    ROC_TRUE:   CASID有效
    ROC_FALSE:  CASID无效
*/
ROC_BOOL rocme_porting_CASIDVerify(const UINT16_T wCaSystemID);

/*
函数名称:
    rocme_porting_SetCurEcmInfos

功能说明:
    中间件调用此接口添加或者删减ECM。
    机顶盒需要保存设置的ECM链表。
    如果传入的component_pid对应的ecm pid不为0表示添加一个ecm关联，
    如果传入的component_pid对应的ecm pid为0表示删除一个ecm关联，
    机顶盒必须维护已经设置过的ecm记录。
    
    解析pmt表中的ca描述符时，使用rocme_porting_CASIDVerify()验证描述符是否对应当前CA，对应的信息保存下来供这里切台使用。

参数说明:
    输入参数:
      ServiceNetInfo:   要收看的节目对应的net id, ts id, service id等关联信息
      componentCount:   compEcmInfos指向Roc_ComponentEcmInfo结构体的个数
      pCompEcmInfos:    设置要收看节目的pid信息。
    输出参数:
            无。
*/
void rocme_porting_SetCurEcmInfos(Roc_NetID_Serv ServiceNetInfo,UINT32_T componentCount, const Roc_ComponentEcmInfo* pCompEcmInfos);

/*
函数名称:
    rocme_porting_SetEmmInfo

功能说明: 
    设置EMMPID，CAS模块将根据设置的EMMPID信息进行EMM数据接收处理。

    中间件收到CAT表后，调用此函数，将EMM PID送下去，这样CA程序就可以根据此PID收取
    私有表，更新用户卡里的授权及为用户提供增值服务。
    当设置EMM的PID为0时，表示通知CA模块停止收取EMM。
    
参数说明: 
    输入参数:
            [ *EmmInfo  ]: EMM信息，参考Roc_ComponentEmmInfo结构定义。 
            [ nEmmCount ]: EmmPid的个数，目前只支持nEmmCount＝1
    输出参数:
            无。
备    注:
    中间件会调用rocme_porting_CASIDVerify()验证ca system id，通过验证后才把对应的EMM传给机顶盒
*/
void rocme_porting_SetEmmInfo(INT32_T nEmmCount,const Roc_ComponentEmmInfo *EmmInfo);

/*
函数名称:
    rocme_porting_ServiceChangeNotify

功能说明: 
    中间件调用此函数通知CA模块节目有改变
    
参数说明:
    输入参数:
            void
    输出参数:
            无

返    回:
    无
*/
void rocme_porting_ServiceChangeNotify(void);

/*
函数名称:
    rocme_porting_ServiceStopNotify

功能说明: 
    中间件调用此函数通知CA模块当前播放的节目停止播放
    
参数说明:
    无

返    回:
    无
*/
void rocme_porting_ServiceStopNotify(void);

/*
函数名称:
    rocme_porting_IsPinLocked

功能说明: 
    判断卡是否被锁住。
    
参数说明: 
    输入参数:
            无。
    输出参数:
            [ *pState ]: 输出参数，1表示锁住了，0表示未锁住, -1表示不支持此功能。
返    回:
    成功: 0
    失败: 其他,参考省网错误码定义

备    注:
    不支持PIN码锁定状态检查功能时,将*pState赋值为-1,并且返回0
*/
INT32_T rocme_porting_IsPinLocked(INT32_T * pState);

/*
函数名称:
    rocme_porting_IsPinPass

功能说明: 
    判断用户是否通过pin码验证。

参数说明: 
    输入参数:
            无。

    输出参数:
            [ *pState ]: 1--表示通过了；0--表示没有; (-1)表示不支持此功能。

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义

备注:
    不支持此功能时,将*pState赋值为-1,并且返回0
*/
INT32_T rocme_porting_IsPinPass(INT32_T * pState);

/*
函数名称:
    rocme_porting_ChangePin

功能说明: 
    修改智能卡的PIN码。
    
参数说明:  
    输入参数:
            [ type        ]: PIN码类型,0为父母控制PIN（如设置观看时间和级别）；1为钱包管理PIN(即IPP购买时输入的PIN)。
            [ *pbysPin    ]: PIN码
            [ byPinLen    ]: PIN码长度
            [ *pbysNewPin ]: 新PIN码
            [ byNewPinLen ]: 新PIN码的长度
    输出参数:
            无
返    回:
    成功: 0
    失败: 其他,参考省网错误码定义

备注:
    中间件传递的PIN码都是ASCII码。
    如果密码是:12345678,
    中间件传递的pbysPin[8]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38}
*/
INT32_T rocme_porting_ChangePin(UINT8_T type, UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T* pbysNewPin, UINT8_T byNewPinLen);

/*
函数名称:
    rocme_porting_GetRating

功能说明: 
    获得智能卡目前最高观看级别
    观看级别为3~18，共15级。初始值为18，即可以观看所有级别的节目。
    
参数说明:  
    输入参数:
            无
    输出参数:
            [ *pbyRating]: 输出观看级别

返    回:
    0:      成功
    (-1):   CA不支持此功能:     
    其他:   失败,具体参考省网错误码定义
*/
INT32_T rocme_porting_GetRating(UINT8_T* pbyRating);

/*
函数名称:
    rocme_porting_SetRating

功能说明: 
    设置智能卡观看级别。
    
参数说明:  
    输入参数:
            [ *pbysPin  ]: PIN码
            [ byPinLen  ]: PIN码长度
            [ byRating  ]:要设置的新的观看级别
    输出参数:
            无
返    回:
    0:      成功
    (-1):   CA不支持此功能:     
    其他:   失败,具体参考省网错误码定义

备    注:
    此时PIN码必须是父母控制的PIN码

备注:
    中间件传递的PIN码都是ASCII码。
    如果密码是:12345678,
    中间件传递的pbysPin[8]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38}
*/
INT32_T rocme_porting_SetRating(UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T byRating);

/*
函数名称:
    rocme_porting_GetWorkTime

功能说明: 
    获得智能卡当前设置的工作时间段
    工作时段初始值为00:00~23:59，即全天都能收看。
    
参数说明: 
    输入参数:
            无
    输出参数:
            [ *pwStartTime ]: 开始工作的时间，高字节表示小时，低字节表示分钟
            [ *pwEndTime   ]: 结束工作的时间，格式同上
返    回:
    0:      成功
    (-1):   CA不支持此功能:     
    其他:   失败,具体参考省网错误码定义
*/
INT32_T rocme_porting_GetWorkTime(UINT16_T * pwStartTime, UINT16_T * pwEndTime);

/*
函数名称:
    rocme_porting_SetWorkTime

功能说明: 
    设置智能卡工作时段
    
参数说明: 
    输入参数:
            [ *pbysPin   ]: PIN码
            [ byPinLen   ]: PIN码长度
            [ wStartTime ]: 开始工作的时间，高字节表示小时，低字节表示分钟
            [ wEndTime   ]: 结束工作的时间，格式同上
    输出参数:
            无

返    回:
    0:      成功
    (-1):   CA不支持此功能:     
    其他:   失败,具体参考省网错误码定义

备    注:
    此时PIN码必须是父母控制的PIN码


备注:
    中间件传递的PIN码都是ASCII码。
    如果密码是:12345678,
    中间件传递的pbysPin[8]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38}
*/
INT32_T rocme_porting_SetWorkTime(UINT8_T* pbysPin, UINT8_T byPinLen, UINT16_T wStartTime, UINT16_T wEndTime);

/*
函数名称:
    rocme_porting_GetOperatorInfo

功能说明: 
    获得CAS运营商信息
    
参数说明:  
    输入参数:
            [ wTVSID         ]: CAS运营商的ID  如果是0xFFFF 则返回所有的运营商信息
            [ *pbyCount      ]: 数组的长度
    输出参数:
            [ *pOperatorInfo ]: 输出运营商信息
            [ *pbyCount      ]: 实际输出运营商信息的个数

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetOperatorInfo(UINT16_T wTVSID,UINT8_T * pbyCount,Roc_OperatorInfo * pOperatorInfo);

/*
函数名称:
    rocme_porting_GetServiceEntitles

功能说明: 
    获得普通授权节目购买的情况，用于在界面上显示。
    
参数说明: 
    输入参数:
            [ wTVSID         ]: 运营商的内部编号。
            [ *pEntitleCount ]: psEntitles指向空间的最大Roc_ServiceEntitle个数
    输出参数:
            [ *pEntitleCount ]: psEntitles中实际获得的Roc_ServiceEntitle个数
            [ *psEntitles    ]: 输出授权

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetServiceEntitles(UINT16_T wTVSID,UINT16_T *pEntitleCount,Roc_ServiceEntitle* psEntitles);

/*
函数名称:
    rocme_porting_ChangeLanguage

功能说明:
    切换提示语言，机顶盒CA模块初始化后调用。
    默认使用中文。当用户切换语言后,中间件调用此函数通知CA模块

参数说明: 
    输入参数:
            [ byLanguage ]: 语言类型
                            ROC_CAS_LANG_CHN_SIM  简体中文(默认)
                            ROC_CAS_LANG_ENG      英文
    输出参数:
            无

返    回:
    无
*/
void rocme_porting_ChangeLanguage(UINT8_T byLanguage);

/*
函数名称:
    rocme_porting_GetEmailCount

功能说明: 
    获取E-mail个数
    
参数说明: 
    输入参数:
            无
    输出参数:
            [ *pEmailCount    ]: 已有E-mail总个数。
            [ *pNewEmailCount ]: 对于数码视讯CAS，是未读过的E-mail个数，对于永新同方CAS，是剩余可用空间个数
返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetEmailCount(UINT16_T * pEmailCount, UINT16_T * pNewEmailCount);

/*
函数名称:
    rocme_porting_GetEmailHead

功能说明:
    获取多个E-mail简要信息
    
参数说明: 
    输入参数:
            [ *pEmailCount ]: pEmail最多可存Roc_EmailInfo的总个数
    输出参数:
            [ *pEmailCount ]: 取到的pEmail中Roc_EmailInfo的总个数。
            [ *pEmail      ]: 取到的E-mail简要信息。
返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetEmailHead(UINT16_T * pEmailCount, Roc_EmailInfo * pEmail);

/*
函数名称:
    rocme_porting_GetEmailContent

功能说明: 
    获取一个E-mail的内容
    
参数说明: 
    输入参数:
            [ tVersion  ]: E-mail版本。
    输出参数:
            [ *pEmail   ]: 获取的E-mail结构。
返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetEmailContent(UINT32_T tVersion, Roc_EmailContent * pEmail);

/*
函数名称;
    rocme_porting_DelEmail

功能说明: 
    删除指定E-mail。
    
参数说明:
    输入参数:
            [ tVersion  ]: E-mail版本。如果为-1，表示删除邮箱中所有email，否则，为具体的id。
返    回
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_DelEmail(UINT32_T tVersion);

/*
函数名称:
    rocme_porting_CheckNewEmail

功能说明: 
    中间件查询是否有新邮件，会在开机启动时进行主动的查询
    
参数说明:
    无

返    回
    成功: 1                         有新的邮件
          0                         没有新的邮件
    失败: 其他
*/
INT32_T rocme_porting_CheckNewEmail(void);

/*
函数名称:
    rocme_porting_GetBookIpps

功能说明:
    得到可预定或者已经预定的IPP节目列表
    
参数说明:
    输入参数:
        [ wTVSID    ]: 运营商ID
        [ *pbyCount ]: pIpps可容纳的IPP结构的个数
    输出参数:
        [ *pbyCount ]: 已获取的IPP节目个数
        [ *pIpp     ]: IPP节目信息

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetBookIpps(UINT16_T wTVSID, UINT8_T * pbyCount, Roc_CAIpp * pIpps);

/*
函数名称:
    rocme_porting_GetInquireIpp

功能说明:
    得到获取即时弹出的IPP节目信息
    
参数说明:
    [ *pIpp ]: 即时弹出的ippv节目信息

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetInquireIpp(Roc_CAIpp * pIpp);

/*
函数名称:
    rocme_porting_CancelInquireIpp

功能说明:
    当用户不购买IPP产品,上层应用退出IPP购买提示框时
    调用此函数通知CA。
    
参数说明:
    无

返    回:
    无
*/
void rocme_porting_CancelInquireIpp();


/*
函数名称:
    rocme_porting_BookIpp

功能说明:
    预订Ipp节目
    
参数说明:
    输入参数:
            [ *pbysPin  ]: PIN码
            [ byPinLen  ]: PIN码长度
            [ PriceType ]: 要预定并确认购买的ipp节目的价格类型
    输出参数:
            无

返    回:
    0:      成功
    其他:   参考广东省网错误码定义                    

备注:
    中间件传递的PIN码都是ASCII码。
    如果密码是:12345678,
    中间件传递的pbysPin[8]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38}
*/
INT32_T rocme_porting_BookIpp(UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T PriceType);

/*
函数功能:
    rocme_porting_GetViewedIpps

功能说明:
    得到已观看的Ipp节目。
    
参数说明:
    输入参数:
            [ *pbyCount ]: pIpps指向的数组可容纳节目个数
    输出参数:
            [ *pbyCount ]: pIpps中得到的已观看节目信息个数。
            [ *pIpps    ]: 已观看的ippv节目信息
返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetViewedIpps(UINT32_T * pbyCount, Roc_CAViewedIpp * pIpps);

/*
函数名称:
    rocme_porting_GetMoneyInfo

功能说明:
    得到某个运营商的已花费钱数，剩余钱数。
    
参数说明:
    输入参数:
            [ wTVSID       ]: 运营商的内部编号。
            [ *pbyCount    ]: pSlotInfos指向的数组可容纳钱包信息个数
    输出参数:
            [ *pbyCount    ]: pSlotInfos中得到的钱包信息个数
            [ *pSlotInfos  ]: 输出钱包信息

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
*/
INT32_T rocme_porting_GetMoneyInfo(UINT16_T wTVSID, UINT8_T* pbyCount, Roc_TVSSlotInfo * pSlotInfos); 

/*
函数名称:
    rocme_porting_SendNITToCA

功能说明: 
    中间件收到NIT表的section后,调用此函数将数据给CA
    
参数说明:
    输入参数:
            [ sec    ]: nit section 缓冲区
            [ len    ]: nit section 缓冲区的大小
    输出参数:
            无

返    回:
    无

备    注:
    该函数不能阻塞。
    若CA无此需求,将函数置空即可。
*/
void rocme_porting_SendNITToCA( UINT8_T *sec, UINT32_T len );
/*++++++++++++++++++++以上为集成非数码视讯CA时,机顶盒厂商需要实现的函数+++++++++++++++++++++++++++*/



/*++++++++++++++++++++以下为集成非数码视讯CA时,中间件提供给机顶盒厂商调用的函数+++++++++++++++++++*/
/*
函数:
    rocme_porting_ca_send_msg

功能:
    机顶盒向中间件发送CA消息

参数:
    type:参考广东省网规范中的"消息代码"中关于CA部分的定义.
    data:不为0时,为消息内容
    dataLen:data不为0时,为附属内容的数据长度

返    回:
    0    --  成功
    其他 --  失败

备    注:
    当CA需要与上层应用交互时,使用此函数
*/
//INT32_T rocme_porting_ca_send_msg(UINT32_T type, UINT8_T *data, UINT32_T dataLen);
/*++++++++++++++++++++以上为集成非数码视讯CA时,中间件提供给机顶盒厂商调用的函数+++++++++++++++++++*/

//#define rocme_porting_ca_send_msg


#endif

