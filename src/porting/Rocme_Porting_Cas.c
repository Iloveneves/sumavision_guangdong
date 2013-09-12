/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_cas.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/

#include "porter_rocme.h"


/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_ca_get_data_info(UINT32_T *addr, UINT32_T *length)
{
ROCME_TEST_PRINT
	
}


/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_CASInit(void)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetCASProviderID( ROC_CAS_PROVIDER_e *provider )
{
	ROCME_TEST_PRINT

}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetCASProviderName(CHAR_T * name)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetCASVer(CHAR_T *strVersion)
{
	ROCME_TEST_PRINT

}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetCardID(CHAR_T *strCardID)
{
	ROCME_TEST_PRINT

}

/***************************************************************
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
***************************************************************/
ROC_BOOL rocme_porting_CASIDVerify(const UINT16_T wCaSystemID)
{
	ROCME_TEST_PRINT

}

/***************************************************************
函数名称:
    rocme_porting_SetCurEcmInfos

功能说明:
    用户转换频道的时候调用这个函数，
    设置当前正在收看的节目的详细信息。
    
    当用户换频道时，中间件需要调用此porting接口，
    将当前节目的原始信息及ECM PID通过机顶盒传递给CAS模块，
    CAS模块会根据当前频道的信息处理与当前频道相关的操作，
    如果当前频道为不加扰的频道，则需要将ECM的PID设为0。
    
    解析pmt表中的ca描述符时，使用rocme_porting_CASIDVerify()验证描述符是否对应当前CA，对应的信息保存下来供这里切台使用。

参数说明:
    输入参数:
      ServiceNetInfo:   要收看的节目对应的net id, ts id, service id等关联信息
      componentCount:   compEcmInfos指向Roc_ComponentEcmInfo结构体的个数
      pCompEcmInfos:    设置要收看节目的pid信息。
    输出参数:
            无。
***************************************************************/
void rocme_porting_SetCurEcmInfos(Roc_NetID_Serv ServiceNetInfo,UINT32_T componentCount, const Roc_ComponentEcmInfo* pCompEcmInfos)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
void rocme_porting_SetEmmInfo(INT32_T nEmmCount,const Roc_ComponentEmmInfo *EmmInfo)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
void rocme_porting_ServiceChangeNotify(void)
{
	ROCME_TEST_PRINT
}

/***************************************************************
函数名称:
    rocme_porting_ServiceStopNotify

功能说明: 
    中间件调用此函数通知CA模块当前播放的节目停止播放
    
参数说明:
    无

返    回:
    无
***************************************************************/
void rocme_porting_ServiceStopNotify(void)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_IsPinLocked(INT32_T * pState)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_IsPinPass(INT32_T * pState)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_ChangePin(UINT8_T type, UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T* pbysNewPin, UINT8_T byNewPinLen)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetRating(UINT8_T* pbyRating)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_SetRating(UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T byRating)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetWorkTime(UINT16_T * pwStartTime, UINT16_T * pwEndTime)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_SetWorkTime(UINT8_T* pbysPin, UINT8_T byPinLen, UINT16_T wStartTime, UINT16_T wEndTime)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetOperatorInfo(UINT16_T wTVSID,UINT8_T * pbyCount,Roc_OperatorInfo * pOperatorInfo)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetServiceEntitles(UINT16_T wTVSID,UINT16_T *pEntitleCount,Roc_ServiceEntitle* psEntitles)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
void rocme_porting_ChangeLanguage(UINT8_T byLanguage)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetEmailCount(UINT16_T * pEmailCount, UINT16_T * pNewEmailCount)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetEmailHead(UINT16_T * pEmailCount, Roc_EmailInfo * pEmail)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetEmailContent(UINT32_T tVersion, Roc_EmailContent * pEmail)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_DelEmail(UINT32_T tVersion)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_CheckNewEmail(void)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetBookIpps(UINT16_T wTVSID, UINT8_T * pbyCount, Roc_CAIpp * pIpps)
{
	ROCME_TEST_PRINT
}

/***************************************************************
函数名称:
    rocme_porting_GetInquireIpp

功能说明:
    得到获取即时弹出的IPP节目信息
    
参数说明:
    [ *pIpp ]: 即时弹出的ippv节目信息

返    回:
    成功: 0
    失败: 其他,参考省网错误码定义
***************************************************************/
INT32_T rocme_porting_GetInquireIpp(Roc_CAIpp * pIpp)
{
	ROCME_TEST_PRINT
}

/***************************************************************
函数名称:
    rocme_porting_CancelInquireIpp

功能说明:
    当用户不购买IPP产品,上层应用退出IPP购买提示框时
    调用此函数通知CA。
    
参数说明:
    无

返    回:
    无
***************************************************************/
void rocme_porting_CancelInquireIpp()
{
	ROCME_TEST_PRINT
}


/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_BookIpp(UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T PriceType)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetViewedIpps(UINT32_T * pbyCount, Roc_CAViewedIpp * pIpps)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetMoneyInfo(UINT16_T wTVSID, UINT8_T* pbyCount, Roc_TVSSlotInfo * pSlotInfos)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
void rocme_porting_SendNITToCA( UINT8_T *sec, UINT32_T len )
{
	ROCME_TEST_PRINT
}
/***************************************************************
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
***************************************************************/
#if 0
INT32_T rocme_porting_ca_send_msg(UINT32_T type, UINT8_T *data, UINT32_T dataLen)
{
}
#endif

