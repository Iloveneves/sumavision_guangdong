/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_smartcard.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/


#include <pthread.h>

#include <string.h>
#include <stdio.h>

#include "hi_unf_ecs.h"

#include "porter_rocme.h"



enum
{
	ACTION_CARDIN,
	ACTION_CARDOUT,
	ACTION_CARDERR,
	ACTION_NONE,
};

enum
{
	CLA_OFFSET = 0,
	INS_OFFSET,
	P1_OFFSET,
	P2_OFFSET,
	P3_OFFSET,
	CMD_HEADER,
	MAX_LENGTH = 256,
};

typedef void (*ScCallback)(ROC_BOOL sc_act);


typedef struct 
{
	rocme_porting_sc_callback backfunc;
	void *param;
}SDrvSciInfo;

static SDrvSciInfo g_DrvSciInfo;
pthread_t s_SciThread;




/******************************************************************************************************\
func
******************************************************************************************************/
void SciProcessFunc( void *param )
{
	ROCME_TEST_PRINT
	HI_UNF_SCI_PORT_E u8SCIPort = HI_UNF_SCI_PORT0;//(HI_UNF_SCI_PORT_E)deviceNum
	HI_UNF_SCI_STATUS_E u32SCILastStatus = HI_UNF_SCI_STATUS_NOCARD;//0xffffffff(修改为无卡)2011-03-15
	HI_UNF_SCI_STATUS_E u32SCIStatus;
	ROC_BOOL bStatus = ROC_FALSE;
	ROC_BOOL	g_SciStatus = ROC_FALSE;
	ROC_BOOL bCardAct = ACTION_NONE;
	
	while(1)
	{

		if( HI_SUCCESS != HI_UNF_SCI_GetCardStatus(u8SCIPort, &u32SCIStatus) )
		{
			rocme_porting_task_sleep(200);
			continue;
		}

		if( u32SCILastStatus == u32SCIStatus )
		{
			rocme_porting_task_sleep(100);
			continue;
		}

		if( u32SCIStatus <= HI_UNF_SCI_STATUS_NOCARD )
		{
			// 无卡
			bStatus = ROC_FALSE;
		}
		else if(u32SCIStatus == HI_UNF_SCI_STATUS_INACTIVECARD)
		{
			bStatus =ACTION_CARDERR;
		}
		else
		{
			// 有卡
			bStatus = ROC_ERR;
		}

		if( bStatus != g_SciStatus )//有插拔卡的动作
		{
			g_SciStatus = bStatus;
			if( bStatus )
			{
				bCardAct = ACTION_CARDIN;//卡插入
			}
			else
			{
				bCardAct = ACTION_CARDOUT;//卡拔出
			}
		}
		else
		{
			bCardAct = ACTION_NONE;//无插拔卡的动作
		}

		switch( bCardAct )
		{
			case ACTION_CARDIN:
			case ACTION_CARDOUT:
			case ACTION_CARDERR:
				if(g_DrvSciInfo.backfunc != NULL)
				{
					g_DrvSciInfo.backfunc(g_DrvSciInfo.param,bCardAct);
				}
				break;
			default:
				break;
		}

		u32SCILastStatus = u32SCIStatus;

		rocme_porting_task_sleep(100);
	}

}


/******************************************************************************************************\
func
******************************************************************************************************/


ROC_BOOL ProcessProcedureBytes(const HI_UNF_SCI_PORT_E u8SCIPort, HI_U8 u8Ins, HI_U32* pu32TransNum, HI_U8* pu8SWBuffer)
{
	ROCME_TEST_PRINT
	HI_U32 nTransNum = 0, nLen = 0;
	HI_U8 bBuf;
	do 
	{		
		if( HI_SUCCESS != HI_UNF_SCI_Receive(u8SCIPort, &bBuf, 1, &nLen, 2000) || (1 != nLen) )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_Receive() failed. nLen = %d\n", __LINE__, __FUNCTION__, nLen);
			return ROC_ERR;
		}

		if( bBuf == 0x60 )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: Receive again.\n", __LINE__, __FUNCTION__);
			continue;
		}

		if( ((bBuf & 0xf0) == 0x60) || ((bBuf & 0xf0) == 0x90) )
		{
			pu8SWBuffer[0] = bBuf;

			if( HI_SUCCESS != HI_UNF_SCI_Receive(u8SCIPort, &bBuf, 1, &nLen, 2000) || (1 != nLen) )
			{
				ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_Receive() failed. nLen = %d\n", __LINE__, __FUNCTION__, nLen);
				return ROC_ERR;
			}

			*pu32TransNum = 0;
			pu8SWBuffer[1] = bBuf;
			return ROC_OK;
		}

		if( (bBuf ^ u8Ins) == 0 )
		{
			nTransNum = *pu32TransNum;
		}
		else
		if( (bBuf ^ u8Ins) == 0xff )
		{
			nTransNum = (*pu32TransNum == 0) ? 0 : 1;
		}
		else
		if( (bBuf ^ u8Ins) == 0x01 )
		{
			nTransNum = *pu32TransNum;
		}
		else
		if( (bBuf ^ u8Ins) == 0xfe )
		{
			nTransNum = (*pu32TransNum == 0) ? 0 : 1;
		}
		else
		{
			return ROC_ERR;
		}
	} while( 0 == nTransNum );
	
    *pu32TransNum = nTransNum;

    return ROC_OK;
}

/******************************************************************************************************\
func
******************************************************************************************************/


ROC_BOOL SciTransferT0(const HI_UNF_SCI_PORT_E u8SCIPort,
				   const HI_U8* pu8Command,
				   HI_U32 u32CommandLen, 
				   HI_U8* pu8Reply,
				   HI_U32* pu32ReplyLen)
{
	ROCME_TEST_PRINT
	if( (HI_UNF_SCI_PORT0 != u8SCIPort) && (HI_UNF_SCI_PORT1 != u8SCIPort) )
	{
		return ROC_ERR;
	}

	if( !pu8Command )
	{
		return ROC_ERR;
	}

	if( (0xff == pu8Command[CLA_OFFSET]) ||
		(0x60 == (pu8Command[INS_OFFSET] & 0xf0)) ||
		(0x90 == (pu8Command[INS_OFFSET] & 0xf0)) )
	{
		return ROC_ERR;
	}

	ROC_BOOL bWrite = ROC_TRUE;
	HI_U8 bIns;
	HI_S32 nTrans, nNextTrans, nActLen;
	
	nTrans = pu8Command[P3_OFFSET];
	if( u32CommandLen > CMD_HEADER )
	{
		bWrite = ROC_TRUE;
	}
	else
	{
		bWrite = ROC_FALSE;
		if( nTrans == 0 )
		{
			nTrans = 256;
		}
	}

	bIns = pu8Command[INS_OFFSET];
	nTrans += CMD_HEADER;
	nNextTrans = CMD_HEADER;
	*pu32ReplyLen = 0;

	HI_U8 szSwBuf[2];
	HI_U8 szBuf[MAX_LENGTH];

	do 
	{
		if( HI_SUCCESS != HI_UNF_SCI_Send(u8SCIPort, (HI_U8*)pu8Command, nNextTrans, &nNextTrans, 2000) )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_Send() failed.\n", __LINE__, __FUNCTION__);
			return ROC_ERR;
		}

		pu8Command += nNextTrans;
		nTrans -= nNextTrans;
		nNextTrans = nTrans;

		if( !ProcessProcedureBytes(u8SCIPort, bIns, &nNextTrans, szSwBuf) )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: ProcessProcedureBytes() failed.\n", __LINE__, __FUNCTION__);
			return ROC_ERR;
		}

		if( 0 == nNextTrans )
		{
			memcpy(pu8Reply, szSwBuf, 2);
			*pu32ReplyLen = 2;
			return ROC_OK;
		}
	} while( bWrite );

	do
	{
	
		if( HI_SUCCESS != HI_UNF_SCI_Receive(u8SCIPort, szBuf, nNextTrans, &nActLen, 2000) )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_Receive() failed.\n", __LINE__, __FUNCTION__);
			return ROC_ERR;
		}

		memcpy( (pu8Reply + *pu32ReplyLen), szBuf, nActLen );
		*pu32ReplyLen += nActLen;

		nTrans -= nNextTrans;
		nNextTrans = nTrans;

		if( !ProcessProcedureBytes(u8SCIPort, bIns, &nNextTrans, szSwBuf) )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: ProcessProcedureBytes() failed.\n", __LINE__, __FUNCTION__);
			return ROC_ERR;
		}

		if( 0 == nNextTrans )
		{
			if( 0 == nTrans )
			{
				memcpy( (pu8Reply + *pu32ReplyLen), szSwBuf, 2 );
				*pu32ReplyLen += 2;
				return ROC_OK;
			}
			else
			{
				ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: failed.\n", __LINE__, __FUNCTION__);
				return ROC_ERR;
			}
		}
	} while( nTrans > 0 );

	return ROC_OK;
}

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
INT32_T rocme_porting_smartcard_init(void)
{
	ROCME_TEST_PRINT

	HI_S32 ret = HI_FAILURE;

	
	HI_UNF_SCI_PORT_E bPort = HI_UNF_SCI_PORT0;
	HI_UNF_SCI_CLK_MODE_E enClkMode = HI_UNF_SCI_CLK_MODE_OD;
	HI_UNF_SCI_LEVEL_E nVccEn = HI_UNF_SCI_LEVEL_LOW;
	HI_UNF_SCI_LEVEL_E nDetect = HI_UNF_SCI_LEVEL_HIGH;
	HI_U32 nFreq = 3570;
	HI_UNF_SCI_PROTOCOL_E protocol = HI_UNF_SCI_PROTOCOL_T0;

	ret = HI_UNF_SCI_Init();
	if( HI_SUCCESS != ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_Init() failed, ret = 0x%08x.\n", __LINE__, __FUNCTION__, ret);
		return ROC_ERR;
	}

	ret = HI_UNF_SCI_Open(bPort, protocol, nFreq);
	if( HI_SUCCESS != ret )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_Open() failed.\n", __LINE__, __FUNCTION__);
		return ROC_ERR;
	}

	// 设置时钟工作模式
	ret = HI_UNF_SCI_ConfigClkMode(bPort, enClkMode);
	if( HI_SUCCESS != ret )
	{
		HI_UNF_SCI_Close(bPort);
		ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_ConfigClkMode() failed.\n", __LINE__, __FUNCTION__);
		return ROC_ERR;
	}

	// 设置检测方式
	ret = HI_UNF_SCI_ConfigVccEn(bPort, nVccEn);
	if( HI_SUCCESS != ret )
	{
		HI_UNF_SCI_Close(bPort);
		ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_ConfigVccEn() failed.\n", __LINE__, __FUNCTION__);
		return ROC_ERR;
	}

	ret = HI_UNF_SCI_ConfigDetect(bPort, nDetect);
	if( HI_SUCCESS != ret )
	{
		HI_UNF_SCI_Close(bPort);
		ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_ConfigDetect() failed.\n", __LINE__, __FUNCTION__);
		return ROC_ERR;
	}

	g_DrvSciInfo.backfunc = NULL;
	g_DrvSciInfo.param = NULL;
	if(pthread_create(&s_SciThread, NULL, &SciProcessFunc, NULL) != HI_SUCCESS)//bPort
	{
		HI_UNF_SCI_Close(bPort);
		ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: TDRV_CreateThread() failed.\n", __LINE__, __FUNCTION__);
		return ROC_ERR;
	}

	return ROC_OK;
}


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
INT32_T rocme_porting_smartcard_term(void)
{
	HI_S32 s32Ret = 0;

	s32Ret = pthread_join(s_SciThread, NULL);
	if(HI_SUCCESS != s32Ret)
	{
		return ROC_ERR;
	}

	s32Ret = HI_UNF_SCI_Close(0);
	if(HI_SUCCESS != s32Ret)
	{
		return ROC_ERR;
	}

	s32Ret = HI_UNF_SCI_DeInit();
	if(HI_SUCCESS != s32Ret)
	{
	    return ROC_ERR;
	}

	return ROC_OK;

}


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
INT32_T rocme_porting_smartcard_reset(UINT8_T * pbyATR, UINT8_T * pbyLen)
{
	ROCME_TEST_PRINT
	HI_UNF_SCI_PORT_E bPort = HI_UNF_SCI_PORT0;

	DOFUNC_RETURN(HI_UNF_SCI_ResetCard(bPort, HI_TRUE));
	DOFUNC_RETURN(HI_UNF_SCI_GetATR(bPort, (HI_U8*)pbyATR, 255, (HI_U8*)pbyLen));

	return ROC_OK;
}


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
INT32_T rocme_porting_smartcard_transfer(INT32_T * pLen, const CHAR_T * byszCommand, CHAR_T * byszReply)
{
	ROCME_TEST_PRINT
	HI_S32 ret = HI_FAILURE;
	HI_U32 card_status;
	HI_UNF_SCI_PORT_E bPort = HI_UNF_SCI_PORT0;


	ret = HI_UNF_SCI_GetCardStatus(bPort, &card_status);
	if(ret != HI_SUCCESS)
	{
		return ROC_ERR;
	}
	
	
	if(card_status==HI_UNF_SCI_STATUS_NOCARD) 
	{
		return ROC_ERR;
	}

	HI_U8* pu8Reply;
	HI_U32* pu32ReplyLen;
	
	if(SciTransferT0( (const HI_UNF_SCI_PORT_E)bPort,
						(const HI_U8*)byszCommand,
						(HI_U32)*pLen,
						pu8Reply,
						pu32ReplyLen) != ROC_ERR)
	{
		*pLen = *pu32ReplyLen;
		memcpy(byszReply,pu8Reply,*pu32ReplyLen);
		return ROC_OK;
	}
	else
	{
		return ROC_ERR;
	}


}



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
INT32_T rocme_porting_smartcard_state(void)
{

	ROCME_TEST_PRINT

	HI_UNF_SCI_STATUS_E enStatus;
	HI_UNF_SCI_PORT_E bPort = HI_UNF_SCI_PORT0;
	if( HI_SUCCESS != HI_UNF_SCI_GetCardStatus(bPort, &enStatus) )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[%d %s]: HI_UNF_SCI_GetCardStatus() failed.\n", __LINE__, __FUNCTION__);
		return ROC_ERR;
	}
	switch(enStatus)
	{
		case HI_UNF_SCI_STATUS_NOCARD:
			return 0;
		case HI_UNF_SCI_STATUS_READY:
			return 1;
		default:
			return ROC_ERR;
	}
}


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
UINT32_T rocme_porting_smartcard_register(Roc_Sc_RegParam_t param, UINT32_T *handle)
{
	ROCME_TEST_PRINT
	g_DrvSciInfo.backfunc = param.callback;
	g_DrvSciInfo.param = param.cb_param;

	return ROC_OK;
}


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
INT32_T rocme_porting_smartcard_unregister(UINT32_T handle)
{
	ROCME_TEST_PRINT
	g_DrvSciInfo.backfunc = NULL;
	g_DrvSciInfo.param = NULL;
	return ROC_OK;
}



