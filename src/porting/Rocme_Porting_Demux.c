/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_demux.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/


#include "hi_unf_demux.h"

#include "porter_rocme.h"



#if 0
#define ROCME_DMX_FILTER_DEPTH          	(16)
#define ROCME_DMX_FILTER_NUM			(48)
#define ROCME_DMX_CHANNEL_NUM		(48)
#define ROCME_DMX_SEC_NUM			(32)
#define ROCME_DMX_SEC_MAXLEN			(4096)	

/* 通道：一级过滤器 */
typedef struct 
{
	HI_BOOL 	bUsed; 				/* 是否被占用 */
	HI_BOOL		bRun;				/* 是否上报数据*/

	HI_U32  		u32Pid;	 			/* 通道PID */
	HI_S32  		hChanHandle;		/* 通道号 */
	HI_S32		poolsize;
	
	HI_U32  		u32DemuxId;		/* PORT号 */

	Roc_Slot_Type_e eType;  /* 通道类型 */

	HI_UNF_DMX_DATA_S stDataBuf;
} ROCME_DMX_CHANNEL_ATTR_S;

/* 二级过滤器 */
typedef struct 
{
   
	HI_BOOL 	bUsed;  				/* 是否被占用 */
	HI_BOOL 	bRun;				/* 是否上报数据*/
	
	HI_HANDLE 	hFilterHandle;		/* 过滤器序号 */
	HI_HANDLE	hChanIndex;		/* 通道号INDEX */

	HI_S32 s32Wide;
	Roc_Filter_Type_e	eType;//过滤器类型
	
	HI_U8 au8Coef[ROCME_DMX_FILTER_DEPTH];
	HI_U8 au8Mask[ROCME_DMX_FILTER_DEPTH];
	HI_U8 au8Excl[ROCME_DMX_FILTER_DEPTH];
	
} ROCME_DMX_FILTER_ATTR_S;

static HI_BOOL 	rocme_dmx_init = HI_FALSE;
static UINT32_T g_hDemuxMutex = 0;



static HI_U8	u8chanenable[ROCME_DMX_CHANNEL_NUM];
static HI_U8	u8filterenable[ROCME_DMX_FILTER_NUM];


static ROCME_DMX_CHANNEL_ATTR_S 	rocme_channel[ROCME_DMX_CHANNEL_NUM];
static ROCME_DMX_FILTER_ATTR_S		Rocme_filter[ROCME_DMX_FILTER_NUM];



/***************************************************************************************

!!!!!!!!该文件中很多接口不能通过调用中间层软件实现，而且可能与驱动层的功能实现有冲突
*****************************************************************************************/

static HI_UNF_DMX_CHAN_TYPE_E DemuxGetChannelType(const Roc_Slot_Type_e slot_type)
{
	HI_UNF_DMX_CHAN_TYPE_E eChannelType = HI_UNF_DMX_CHAN_TYPE_BUTT;
	
	switch (slot_type)
	{
		case ROC_SLOT_TYPE_SECTION:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_SEC;
			break;

		case ROC_SLOT_TYPE_PES:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_PES;
			break;
			
		case ROC_SLOT_TYPE_RAW:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_POST;
			break;

		default:
			break;	
	}

	return eChannelType;
}

/**************************************************************************
函数名称: 
            rocme_porting_demux_init
功能说明: 
            DEMUX功能初始化，中间件会在启动时调用此函数，若在启动中间件之前
        机顶盒已经做好了DEMUX的初始化，此函数可以实现为空，直接返回0。
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
INT32_T rocme_porting_demux_init(void)
{
ROCME_TEST_PRINT
	HI_S32 i;
	
	//打开解复用设备。
	CHK_RETURN( (HI_FALSE ==  rocme_dmx_init)  , HI_SUCCESS );

	/* 先初始化DVB TS 通路 */
	DOFUNC_RETURN( HI_UNF_DMX_Init() );
	DOFUNC_RETURN( HI_UNF_DMX_AttachTSPort(HI_UNF_DMX_ID_0_PLAY , HI_UNF_DMX_PORT_0_TUNER ) );
printf("1111111111111111111111111111\r\n");
	if (g_hDemuxMutex == 0)
	{
		g_hDemuxMutex  = rocme_porting_mutex_create(ROC_MUTEX_RECURSIVE_NP);
		if (g_hDemuxMutex == 0)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"mutex create failed\n");
			return ROC_ERR;
		}
	}


	for (i = 0; i< ROCME_DMX_CHANNEL_NUM; i++)
	{
		memset(&rocme_channel[i], 0x0, sizeof(ROCME_DMX_CHANNEL_ATTR_S));
		
		rocme_channel[i].bUsed = HI_FALSE;
		rocme_channel[i].bRun = HI_FALSE;
		rocme_channel[i].hChanHandle= 0xffffffff;
		rocme_channel[i].u32Pid = 0xffffffff;

		u8chanenable[i] = 0;
		
	}

	for (i = 0; i< ROCME_DMX_FILTER_NUM; i++)
	{
		memset(&Rocme_filter[i], 0x0, sizeof(ROCME_DMX_FILTER_ATTR_S));

		Rocme_filter[i].bUsed = HI_FALSE;
		Rocme_filter[i].bRun = HI_FALSE;
		Rocme_filter[i].hChanIndex = 0xffffffff;
		Rocme_filter[i].hFilterHandle = 0xffffffff;

		u8filterenable[i] = 0;
	}



	rocme_dmx_init = HI_TRUE;

	rocme_porting_task_sleep(10);
	
	return ROC_OK;


}

/**************************************************************************
函数名称: 
            rocme_porting_demux_term
功能说明: 
            卸载DEMUX功能。目前此函数可以实现为空。
参数说明：
    输入参数：
            void
    输出参数：
            无
返    回： 
    成功 : 0            ( 卸载成功 )
    失败 : -1 或 错误码 ( 卸载失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_demux_term(void)
{

	ROCME_TEST_PRINT
	CHK_RETURN( (HI_TRUE ==  rocme_dmx_init)  , HI_SUCCESS );
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

	DOFUNC_RETURN( HI_UNF_DMX_DetachTSPort( HI_UNF_DMX_ID_0_PLAY) );
	HI_UNF_DMX_DeInit() ;

	rocme_porting_mutex_unlock(g_hDemuxMutex);


	rocme_porting_mutex_destroy(g_hDemuxMutex);
	g_hDemuxMutex = 0;

	rocme_dmx_init = HI_FALSE;

	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_slot_query_PID
功能说明: 
            指定数据通道上，查询一个PID是否已经被某个slot(包括中间件使用的
        slot和中间件之外的slot)占用，若平台不支持slot的PID设定不能重复，此
        功能必须实现。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ pid           ] : 需要查询的PID值
    输出参数：
            
返    回： 
    此PID未被占用 :  0
    此PID已被占用 : -1
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_query_PID(const INT32_T channel_index,const UINT16_T pid)
{
ROCME_TEST_PRINT
	UINT32_T i;
	for(i=0;i<ROCME_DMX_CHANNEL_NUM;i++)
	{
		if((rocme_channel[i].bUsed == HI_TRUE)&&(rocme_channel[i].u32Pid == pid))
		{
			break;
		}
	}
	if(i>= ROCME_DMX_CHANNEL_NUM)
	{
		return ROC_OK;
	}
	else
	{
		return ROC_ERR;
	}
}


/**************************************************************************
函数名称: 
            rocme_porting_slot_alloc
功能说明: 
            在指定的数据通道上申请分配一个slot(指定slot的类型、buff的大小)，
        若成功申请到slot，返回一个slot的控制ID，中间件获得对此slot的控制权，
        即通过此ID对此slot设备进行修改、启动、释放等具体操作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ slot_type     ] : slot的类型，具体如下:
                                ROC_SLOT_TYPE_NULL     -  used with inject carousel 
                            packet only flag
                                ROC_SLOT_TYPE_SECTION  -  for section data - Signal 
                            every section
                                ROC_SLOT_TYPE_PES      -  signal every complete PES
                            packet except when signal_on_every_transport_packet is 
                            supplied as a flag
                                ROC_SLOT_TYPE_RAW      -  Raw transport packets, si-
                            -gnalled every packet
                                ROC_SLOT_TYPE_PCR      -  specifies that the data c-
                            -ollected on this slot is collected for PCR gathering purposes
                                ROC_SLOT_TYPE_RESERVE  -  扩展保留
             [ buff_size    ] : 需要开辟的slot使用的buff的大小，中间件除特殊情况外，
                            会申请64KB。
    输出参数：
            无
返    回： 
    成功 : 申请到的slot控制ID ( 申请成功 )
    失败 : -1 或 错误码       ( 申请失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_alloc(const INT32_T channel_index,const Roc_Slot_Type_e slot_type,const INT32_T buff_size)
{
ROCME_TEST_PRINT
	UINT32_T ret = 0;
	INT32_T i;
	HI_UNF_DMX_CHAN_ATTR_S stChAttr;
			
	for (i = 0; i<	ROCME_DMX_CHANNEL_NUM; i++)
	{
		if (rocme_channel[i].bUsed == HI_FALSE)
		{


			rocme_channel[i].poolsize = buff_size;
			rocme_channel[i].eType = slot_type;
			rocme_channel[i].u32DemuxId = HI_UNF_DMX_ID_0_PLAY;

			break;
		}
	}

	if (i>= ROCME_DMX_CHANNEL_NUM) //IPANEL_DMX_CHANNEL_NUM
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "rocme_porting_slot_alloc failed. no slot %x\n");
		return ROC_ERR;
	}

	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[i];

	rocme_porting_mutex_lock(g_hDemuxMutex);

	ret = HI_UNF_DMX_GetChannelDefaultAttr(&stChAttr);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_GetChannelDefaultAttr failed. ret = %x\n", ret);
		return ROC_ERR;
	}
	
	stChAttr.enChannelType = DemuxGetChannelType(slot_type);
	if (stChAttr.enChannelType == HI_UNF_DMX_CHAN_TYPE_SEC)
	{
		stChAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_DISCARD; 
	}
	else
	{
		stChAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_FORBID; 
	}
	stChAttr.enOutputMode = HI_UNF_DMX_CHAN_OUTPUT_MODE_PLAY;
	stChAttr.u32BufSize = buff_size;

	
	ret = HI_UNF_DMX_CreateChannel((HI_U32)pChannel->u32DemuxId, &stChAttr, (HI_HANDLE*)(&pChannel->hChanHandle));
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CreateChannel failed. ret = %x\n", ret);
		return ROC_ERR;
	}
		
	rocme_channel[i].bUsed = HI_TRUE;
	rocme_porting_mutex_unlock(g_hDemuxMutex);
	return( i);
}

/**************************************************************************
函数名称: 
            rocme_porting_slot_modify
功能说明: 
            根据slot_ID，修改相应的slot设备的一级过滤条件(即具体PID值)。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ pid        ] : 需要设置的一级过滤条件值
    输出参数：
            无
返    回： 
    成功 : 0            ( 修改slot一级过滤条件成功 )
    失败 : -1 或 错误码 ( 修改slot一级过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_modify(const INT32_T slot_ID,const UINT16_T pid)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
	HI_S8  i, j;
	HI_UNF_DMX_CHAN_ATTR_S stChAttr;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];

	if(pid == pChannel->u32Pid)
	{
		ROCME_PRINTF(ROCME_LOG_INFO, "same pid , %d to %d .\n", pid , pChannel->u32Pid);
		return ROC_OK;
	}
	if(rocme_porting_slot_query_PID(slot_ID,pid)==ROC_ERR)
	{
		
		ROCME_PRINTF(ROCME_LOG_ERROR, "the pid is used\n");
		return ROC_ERR;
	}

	if(pChannel->hChanHandle != 0xffffffff)
	{
		rocme_porting_mutex_lock(g_hDemuxMutex);
		//先关闭通道
		HI_UNF_DMX_CHAN_STATUS_S status;
		ret = HI_UNF_DMX_GetChannelStatus(pChannel->hChanHandle, &status);
		if( ret != HI_SUCCESS)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CloseChannel failed. channel %x (%x) , ret = %x\n", 
				slot_ID, pChannel->hChanHandle, ret);
			
			status.enChanStatus = HI_UNF_DMX_CHAN_PLAY_EN;
		}
		
		if(status.enChanStatus != HI_UNF_DMX_CHAN_CLOSE)
		{
			ret = HI_UNF_DMX_CloseChannel(pChannel->hChanHandle);
			if( HI_SUCCESS != ret )
			{
				ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CloseChannel failed. channel %x (%x) , ret = %x\n", 
					slot_ID, pChannel->hChanHandle, ret);
			}
		}
		
		//设置pid
		ret = HI_UNF_DMX_SetChannelPID(pChannel->hChanHandle, pid);
		if( HI_SUCCESS != ret )
		{
			rocme_porting_mutex_unlock(g_hDemuxMutex);
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_SetChannelPID failed. channel %x (%x), pid %d , ret = %x\n", 
				slot_ID, pChannel->hChanHandle, pid, ret);
			return ROC_ERR;
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_INFO, "HI_UNF_DMX_SetChannelPID succes, channel %x (%x) , pid %d  .\n", 
				slot_ID, pChannel->hChanHandle, pid);
		}
		
		pChannel->u32Pid= pid;	
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		return ROC_OK;

	}
	else
	{
		
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel handle err\r\n");
		return ROC_ERR;
	}
		

}
/**************************************************************************
函数名称: 
            rocme_porting_slot_clear
功能说明: 
            根据slot_ID，清除其设置的一级过滤条件(即具体的PID值)。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 清除slot过滤条件成功 )
    失败 : -1 或 错误码 ( 清除slot过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_clear(const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
	HI_S8  i, j;
	HI_UNF_DMX_CHAN_ATTR_S stChAttr;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];


	rocme_porting_mutex_lock(g_hDemuxMutex);

	pChannel->u32Pid= 0x1fff;
	HI_UNF_DMX_CloseChannel(pChannel->hChanHandle);
	ret = HI_UNF_DMX_SetChannelPID(pChannel->hChanHandle, pChannel->u32Pid);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_SetChannelPID failed. channel %x (%x), pid %d , ret = %x\n", 
			slot_ID, pChannel->hChanHandle, pChannel->u32Pid, ret);
		return ROC_ERR;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_INFO, "HI_UNF_DMX_SetChannelPID succes, channel %x (%x) , pid %d  .\n", 
			slot_ID, pChannel->hChanHandle, pChannel->u32Pid);
	}

	rocme_porting_mutex_unlock(g_hDemuxMutex);	
	return ROC_OK;


}


/**************************************************************************
函数名称: 
            rocme_porting_slot_start
功能说明: 
            启动一个slot设备开始过滤数据，如果底层平台的slot设备无此设置的实现，
        则此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 启动slot设备成功 )
    失败 : -1 或 错误码 ( 启动slot设备失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_start(const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
	HI_UNF_DMX_CHAN_STATUS_S status;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];

	ret = HI_UNF_DMX_GetChannelStatus(pChannel->hChanHandle, &status);
	if( ret != HI_SUCCESS)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CloseChannel failed. channel %x (%x) , ret = %x\n", 
			slot_ID, pChannel->hChanHandle, ret);
	
		status.enChanStatus = HI_UNF_DMX_CHAN_CLOSE;
	}
	
	if(status.enChanStatus == HI_UNF_DMX_CHAN_CLOSE)
	{
		ret = HI_UNF_DMX_OpenChannel((HI_U32)pChannel->hChanHandle);
		if( HI_SUCCESS != ret )
		{
			rocme_porting_mutex_unlock(g_hDemuxMutex);
			ROCME_PRINTF(ROCME_LOG_ERROR,"HI_UNF_DMX_OpenChannel failed. channel %x (%x), ret = %x\n", 
				slot_ID, pChannel->hChanHandle, ret);
			return ROC_ERR;
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_INFO, "HI_UNF_DMX_OpenChannel success. channel %x (%x) \n", 
				slot_ID, pChannel->hChanHandle);
		}
	}
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_slot_stop
功能说明: 
            停止一个slot设备过滤数据，如果底层平台的slot设备无此设置的实现，
        则此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 停止slot设备成功 )
    失败 : -1 或 错误码 ( 停止slot设备失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_stop(const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];
	
	ret = HI_UNF_DMX_CloseChannel((HI_U32)pChannel->hChanHandle);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CloseChannel failed. channel %x (%x) , ret = %x\n", 
			slot_ID, pChannel->hChanHandle, ret);
		return ROC_ERR;
	}
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_slot_free
功能说明: 
            释放掉对一个指定slot的控制权。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 释放成功 )
    失败 : -1 或 错误码 ( 释放失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_free(const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
#if 1
	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];

	rocme_porting_mutex_lock(g_hDemuxMutex);

	ret = HI_UNF_DMX_DestroyChannel( (HI_U32)pChannel->hChanHandle ) ;
	if( HI_SUCCESS != ret )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_DestroyChannel failed. ch is 0x%x , ret = %x\n", 
						pChannel->hChanHandle, ret);
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_INFO, "HI_UNF_DMX_DestroyChannel %x success .\n", pChannel->hChanHandle);
	}
#endif
	rocme_channel[slot_ID].bUsed = HI_FALSE;
	rocme_channel[slot_ID].poolsize = 0;
	rocme_channel[slot_ID].eType = 0;
	rocme_channel[slot_ID].u32DemuxId = HI_UNF_DMX_ID_0_PLAY;
	rocme_channel[slot_ID].bRun = HI_FALSE;
	rocme_channel[slot_ID].u32Pid = 0xffffffff;
	rocme_channel[slot_ID].hChanHandle= 0xffffffff;
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_wait
功能说明: 
            指定数据通道索引，中间件通过此方法主动查询是否有slot过滤到数据，
        并且可以设置等待超时时限，若此数据通道上过滤到了数据，则返回过滤到
        了数据的slot控制ID。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ time_out_ms   ] : 超时时间，单位为毫秒(ms)
    输出参数：
            
返    回： 
    成功 : slot控制ID   ( 成功查询到有slot过滤到数据 )
    失败 : -1 或 错误码 ( 查询失败/slot在time_out_ms时限内未过滤到数据 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait(const INT32_T channel_index,const INT32_T time_out_ms)
{
ROCME_TEST_PRINT

	INT32_T i,j;
	HI_U32 ret = 0;
	HI_U32 u32ChnNum ;
	HI_UNF_DMX_DATA_S stBuf;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	for(i=0;i<ROCME_DMX_CHANNEL_NUM;i++)
	{	
		if(rocme_channel[i].hChanHandle == 0xffffffff)
			continue;
		
		if(HI_UNF_DMX_AcquireBuf(rocme_channel[i].hChanHandle,1,&u32ChnNum,&stBuf,0) == HI_SUCCESS)
		{
			memcpy(&(rocme_channel[i].stDataBuf),&stBuf,sizeof(HI_UNF_DMX_DATA_S));
			rocme_porting_mutex_unlock(g_hDemuxMutex);
			return i;
		}
		
	}
	rocme_porting_mutex_unlock(g_hDemuxMutex);
	ROCME_PRINTF(ROCME_LOG_ERROR, "no channel get data err\r\n");
	return ROC_ERR;

}

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_wait_multi
功能说明: 
            指定数据通道索引，中间件通过此方法主动查询是否有slot过滤到数据，
        并且可以设置等待超时时限，若此数据通道上过滤到了数据，则将获取到数
        据的slot赋给slot_ID_ar数组成员,并修改*count为已经获取到数据的slot个数。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ time_out_ms   ] : 超时时间，单位为毫秒(ms)
            [ *count        ] : slot_ID_ar数组成员最大个数
    输出参数：
            [ slot_ID_ar    ] : 获取到数据的slot
            [ *count        ] : 已经获取到数据的slot的个数
返    回： 
    成功 : 0
    失败 : -1 或 错误码 ( 查询失败/slot在time_out_ms时限内未过滤到数据 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait_multi(const INT32_T channel_index, INT32_T *slot_ID_ar, INT32_T *count , const INT32_T time_out_ms)
{
	ROCME_TEST_PRINT

		INT32_T i,j;
		HI_U32 ret = 0;
		HI_U32 u32ChnNum ;
		HI_UNF_DMX_DATA_S stBuf;
		HI_HANDLE ChannelHandle[ROCME_DMX_CHANNEL_NUM];
		memset(ChannelHandle,0xffffffff,ROCME_DMX_CHANNEL_NUM);
	
		u32ChnNum = ROCME_DMX_CHANNEL_NUM;
//		rocme_porting_mutex_lock(g_hDemuxMutex);
		ret = HI_UNF_DMX_GetDataHandle(ChannelHandle, &u32ChnNum, 100);
		if( HI_SUCCESS != ret )
		{	
//			rocme_porting_mutex_unlock(g_hDemuxMutex);
			//ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_GetDataHandle err\r\n");
			return ROC_ERR;
		}
		*count = u32ChnNum;
		j = 0;
		for(i=0;i<ROCME_DMX_CHANNEL_NUM;i++)
		{
			if(rocme_channel[i].hChanHandle == 0xffffffff)
				continue;
			
			if(HI_UNF_DMX_AcquireBuf(rocme_channel[i].hChanHandle,1,&u32ChnNum,&stBuf,100) == HI_SUCCESS)
			{
				slot_ID_ar[j] = i;
				memcpy(&(rocme_channel[i].stDataBuf),&stBuf,sizeof(HI_UNF_DMX_DATA_S));
				j++;
			}
		}
//		rocme_porting_mutex_unlock(g_hDemuxMutex);		
		return ROC_OK;

}


/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_get
功能说明: 
            从指定slot的buff中的复制(提取)出指定长度的数据，中间件只有在调用
        了rocme_porting_slot_buff_wait后，才会使用此函数判断过滤的数据的归属。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ *buff_ptr  ] : 存储提取到的数据的buff的头指针
            [ buff_size  ] : 需要提取的数据的长度，即存储buff的长度
    输出参数：
            [ *data_size ] : 实际提取到的数据的长度
返    回： 
    成功 : 0            ( 提取数据成功 )
    失败 : -1 或 错误码 ( 提取数据失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_get(const INT32_T slot_ID, UINT8_T *buff_ptr, const UINT32_T buff_size, UINT32_T *data_size)
{
ROCME_TEST_PRINT

	HI_S32 ret=0;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	*data_size = rocme_channel[slot_ID].stDataBuf.u32Size> buff_size ? buff_size : rocme_channel[slot_ID].stDataBuf.u32Size;
	memcpy(buff_ptr, rocme_channel[slot_ID].stDataBuf.pu8Data, *data_size);
	rocme_porting_mutex_unlock(g_hDemuxMutex);
	 return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_read
功能说明: 
            从指定的slot的buff中读取数据，读取数据后，要求清空buff。中间件会
        要求将slot的buff中的数据读到2个buff中，分别是data0和data1，读取数据时
        ，先将数据读到data0中，当data0放满后，再将数据读取到data1中，当空间不
        够时，返回读取失败。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ *p_data0   ] : 存储缓冲区0的头指针
            [ size0      ] : 存储缓冲区0的长度
            [ *p_data1   ] : 存储缓冲区1的头指针
            [ size1      ] : 存储缓冲区1的长度
    输出参数：
            [ *datasize  ] : 实际读取到的数据长度
返    回： 
    成功 : 0            ( 读取数据成功 )
    失败 : -1 或 错误码 ( 读取数据失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_read(const INT32_T slot_ID, UINT8_T *p_data0, UINT32_T size0, UINT8_T *p_data1, UINT32_T size1, UINT32_T *datasize)
{
ROCME_TEST_PRINT

	HI_S32 ret=0;
	ROCME_PRINTF(ROCME_LOG_INFO, "size =%d,data_ptr = 0x%x\n",rocme_channel[slot_ID].stDataBuf.u32Size,rocme_channel[slot_ID].stDataBuf.pu8Data);

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(rocme_channel[slot_ID].stDataBuf.u32Size>size0+size1)
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "size too small\n");
		return ROC_ERR;
	}
	else if(rocme_channel[slot_ID].stDataBuf.u32Size>size0)
	{
		memcpy(p_data0,rocme_channel[slot_ID].stDataBuf.pu8Data,size0);
		memcpy(p_data1,rocme_channel[slot_ID].stDataBuf.pu8Data+size0,rocme_channel[slot_ID].stDataBuf.u32Size - size0);
	}
	else
	{
		memcpy(p_data0,rocme_channel[slot_ID].stDataBuf.pu8Data,size0);
	}
	*datasize =rocme_channel[slot_ID].stDataBuf.u32Size;
	rocme_porting_mutex_unlock(g_hDemuxMutex);
	return ROC_OK;

	
}


/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_flush
功能说明: 
            清空指定的slot的buff。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 清除指定slot的buff成功 )
    失败 : -1 或 错误码 ( 清除指定slot的buff失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_flush(const INT32_T slot_ID)
{
	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(HI_UNF_DMX_ReleaseBuf(rocme_channel[slot_ID].hChanHandle,1,&(rocme_channel[slot_ID].stDataBuf)) == HI_SUCCESS)
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		return ROC_OK;
	}
	else
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "release err \n");
		return ROC_ERR;
	}
}


/**************************************************************************
函数名称: 
            rocme_porting_filter_alloc
功能说明: 
            在指定的数据通道上申请分配一个filter(指定filter的类型)，若成功申
        请到filter，返回一个filter的控制ID，中间件获得对此filter的控制权，即
        通过此ID对此filter设备进行修改、启动、释放等具体操作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ filter_type   ] : filter的类型，具体如下:
                                ROC_FILTER_TYPE_SECTION       -  Provides 8 byte filter/mask
                                ROC_FILTER_TYPE_PES           -  Filter PES
                                ROC_FILTER_TYPE_TSHEADER      -  Filter TSHeader
                                ROC_FILTER_TYPE_PES_STREAMID  -  Filter PES stream ID
                                ROC_FILTER_TYPE_NEG_MATCH     -  Negative Match Mode filtering
                                ROC_FILTER_TYPE_RESERVE       -  扩展保留
    输出参数：
            无
返    回： 
    成功 : 申请到的filter控制ID ( 申请成功 )
    失败 : -1 或 错误码         ( 申请失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_alloc(const INT32_T channel_index,const Roc_Filter_Type_e filter_type)
{
ROCME_TEST_PRINT
	INT32_T i = 0;
	HI_S32 ret=0;

	HI_UNF_DMX_FILTER_ATTR_S	stFilterAttr;


	//寻找空闲位置
	for( i = 0; i < ROCME_DMX_FILTER_NUM; i ++ )
	{
		if( !Rocme_filter[i].bUsed)
		{
			break;
		}
	}
	
	if( i >= ROCME_DMX_FILTER_NUM )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "no more free filter, failed. \n");
		return ROC_ERR;
	}
	else
	{
		rocme_porting_mutex_lock(g_hDemuxMutex);
		
		memset(&stFilterAttr, 0, sizeof(HI_UNF_DMX_FILTER_ATTR_S));//不过滤任何数据，等下面set以后再过滤。

		ret = HI_UNF_DMX_CreateFilter(HI_UNF_DMX_ID_0_PLAY, &stFilterAttr, (HI_HANDLE*)&Rocme_filter[i].hFilterHandle);
		if( HI_SUCCESS != ret)
		{
			rocme_porting_mutex_unlock(g_hDemuxMutex);
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CreateFilter failed . ret %x . \n", ret);
			return ROC_ERR;
		}
		Rocme_filter[i].bUsed = ROC_TRUE;
		Rocme_filter[i].eType = filter_type;
		rocme_porting_mutex_unlock(g_hDemuxMutex);

		return i;
	}



}


/**************************************************************************
函数名称: 
            rocme_porting_filter_associate
功能说明: 
            将指定的slot和filter关联起来。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 关联成功 )
    失败 : -1 或 错误码 ( 关联失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_associate(const INT32_T filter_ID,const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_UNF_DMX_FILTER_ATTR_S	stFilterAttr;
	int i = 0;
	HI_S32 ret=0;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}

	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", slot_ID);
		return ROC_ERR;
	}

	rocme_porting_mutex_lock(g_hDemuxMutex);

	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];
	ROCME_DMX_FILTER_ATTR_S	*pFitler = &Rocme_filter[filter_ID];
		
	ret = HI_UNF_DMX_AttachFilter( pFitler->hFilterHandle, pChannel->hChanHandle); 
	if( HI_SUCCESS != ret)
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CreateFilter failed . ret %x . \n", ret);
		return ROC_ERR;
	}
	Rocme_filter[filter_ID].hChanIndex = slot_ID;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
	
}


/**************************************************************************
函数名称: 
            rocme_porting_filter_disassociate
功能说明: 
            将指定的slot和filter断开。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到        
    输出参数：
            无
返    回： 
    成功 : 0            ( 断开成功 )
    失败 : -1 或 错误码 ( 断开失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_disassociate(const INT32_T filter_ID,const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}

	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];
	ROCME_DMX_FILTER_ATTR_S	*pFitler = &Rocme_filter[filter_ID];

	
	ret = HI_UNF_DMX_DetachFilter( pFitler->hFilterHandle, pChannel->hChanHandle);
	if( HI_SUCCESS != ret)
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CreateFilter failed . ret %x . \n", ret);
		return ROC_ERR;
	}
	
	Rocme_filter[filter_ID].hChanIndex = 0xffffffff;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
}


/**************************************************************************
函数名称: 
            rocme_porting_filter_modify
功能说明: 
            根据filter_ID，修改相应的filter设备的二级过滤条件(即具体cofe和mask值)。
        例如，过滤TDT，设置这两项为:
        cafe[8]赋值为{0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        mask[8]赋值为{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00}.
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ *cofe      ] : 二级过滤条件头指针
            [ c_size     ] : 二级过滤条件长度
            [ *mask      ] : 二级过滤条件掩码值头指针
            [ m_size     ] : 二级过滤条件掩码值长度
    输出参数：
            
返    回： 
    成功 : 0            ( 修改二级过滤条件成功 )
    失败 : -1 或 错误码 ( 修改二级过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_modify(const INT32_T filter_ID,
                                    const UINT8_T*cofe,const UINT8_T c_size,
                                    const UINT8_T*mask,const UINT8_T m_size,
                                    const UINT8_T*nega,const UINT8_T m_nega)
{
ROCME_TEST_PRINT
	
	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", filter_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	memcpy(Rocme_filter[filter_ID].au8Coef,cofe,c_size);
	memcpy(Rocme_filter[filter_ID].au8Mask,mask,m_size);
	
	Rocme_filter[filter_ID].s32Wide = ROCME_DMX_FILTER_DEPTH;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;



}


/**************************************************************************
函数名称: 
            rocme_porting_filter_start
功能说明: 
            根据filter_ID，启动一个filter设备开始工作。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( filter设备启动成功 )
    失败 : -1 或 错误码 ( filter设备启动失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_start(const INT32_T filter_ID)
{
ROCME_TEST_PRINT
	HI_S32 i;
	HI_S32 ret=0;

	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;
	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", filter_ID);
		return ROC_ERR;
	}
		/* FILTER 处理*/

	rocme_porting_mutex_lock(g_hDemuxMutex);
	memset(stFilterAttr.au8Match, 0x00, ROCME_DMX_FILTER_DEPTH);
	memset(stFilterAttr.au8Mask, 0xff, ROCME_DMX_FILTER_DEPTH);
	memset(stFilterAttr.au8Negate, 0x00, ROCME_DMX_FILTER_DEPTH);

	for ( i=0; i<Rocme_filter[filter_ID].s32Wide; i++ )
	{
		stFilterAttr.au8Match[i] = Rocme_filter[filter_ID].au8Coef[i];
		stFilterAttr.au8Mask[i] = ~Rocme_filter[filter_ID].au8Mask[i];
		stFilterAttr.au8Negate[i] = Rocme_filter[filter_ID].au8Excl[i];

	}

	stFilterAttr.u32FilterDepth = Rocme_filter[filter_ID].s32Wide;

	ret = HI_UNF_DMX_SetFilterAttr(Rocme_filter[filter_ID].hFilterHandle, &stFilterAttr);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_SetFilterAttr failed, filter  %x(%x) , ret %x . \n", 
						filter_ID, Rocme_filter[filter_ID].hFilterHandle, ret);
		return ROC_ERR;
	}
	else
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		return ROC_OK;
	}

}


/**************************************************************************
函数名称: 
            rocme_porting_filter_stop
功能说明: 
            根据filter_ID，停止一个filter设备的工作。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( filter设备停止成功 )
    失败 : -1 或 错误码 ( filter设备停止失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_stop(const INT32_T filter_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	memset(&stFilterAttr,0,sizeof(HI_UNF_DMX_FILTER_ATTR_S));
	ret = HI_UNF_DMX_SetFilterAttr(Rocme_filter[filter_ID].hFilterHandle, &stFilterAttr);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_SetFilterAttr failed, filter  %x(%x) , ret %x . \n", 
						filter_ID, Rocme_filter[filter_ID].hFilterHandle, ret);
		return ROC_ERR;
	}
	else
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		return ROC_OK;
	}

}


/**************************************************************************
函数名称: 
            rocme_porting_filter_free
功能说明: 
            释放掉对一个fitler设备的控制权。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 释放成功 )
    失败 : -1 或 错误码 ( 释放失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_free(const INT32_T filter_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;

	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", filter_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	ret = HI_UNF_DMX_DestroyFilter( (HI_U32)Rocme_filter[filter_ID].hFilterHandle );
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_DestroyFilter failed .  , filter %x , ret %x. \n", 
			filter_ID, ret);
		return ROC_ERR;
	}

	Rocme_filter[filter_ID].bUsed = ROC_FALSE;
	Rocme_filter[filter_ID].hFilterHandle = 0xffffffff;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
	
}

#endif

#include "rocme_porting_osp.h"
#include "rocme_porting_demux.h"
#include "hi_unf_demux.h"



#define ROCME_DEMUX_SUCCESS (0)
#define ROCME_DEMUX_FAILURE (-1)
#define ROCME_DEMUX_PRINT rocme_porting_dprintf
#define ROCME_DEMUX_DEFAULT_ID (0)

#define DEFAULT_DVB_PORT 0


struct stListDemuxHandle
{
	HI_HANDLE hDemuxChannelHandle;
	struct stListDemuxHandle *pNext;
};


struct stListDemuxBufInfo
{
	HI_HANDLE hChannel;
	HI_UNF_DMX_DATA_S stDataBuf;
	struct stListDemuxBufInfo *pNext;
};

typedef struct FilterInfo
{
	HI_HANDLE hFilter;
	HI_U8 au8Match[DMX_FILTER_MAX_DEPTH];
	HI_U8 au8Mask[DMX_FILTER_MAX_DEPTH];
	struct FilterInfo* pstNext;
}FilterInfo_t;

static UINT32_T g_hDemuxMutex = 0;
static ROC_BOOL g_hDemuxInit = ROC_FALSE;
static struct stListDemuxHandle *g_pstDemuxHandleList = NULL;
static struct stListDemuxBufInfo *g_pstDemuxBufInfoList = NULL; 
static FilterInfo_t* g_pstFilterInfo = NULL;

//static HI_HANDLE g_DemuxChannelHandle[DMX_TOTALCHAN_CNT];

#define FindNodeFromLinkList(name,member,thisNode,linkList)\
{\
	name##Info_t* pstHeadNode= linkList;\
	name##Info_t* pstCurNode = pstHeadNode;\
	name##Info_t* pstPreNode = pstCurNode;\
	while(pstCurNode!=NULL)\
	{\
		if(pstCurNode->h##name == member) break;\
		pstPreNode = pstCurNode;\
		pstCurNode = pstCurNode->pstNext;\
	}\
	if(pstCurNode!=NULL) {thisNode = pstCurNode;}\
	else {thisNode = NULL;ROCME_DEMUX_PRINT("fun=%s.line=%d.%s not found.this may be an err.\n",__FUNCTION__,__LINE__,#name);}\
}

#define AddNode2LinkList(name,node,linkList)\
{\
	name##Info_t* pstThisNode=(name##Info_t*)node;\
	if(linkList == NULL) {linkList = pstThisNode;}\
	else {pstThisNode->pstNext=linkList->pstNext; linkList->pstNext=pstThisNode;}\
}

#define DelNodeFromLinkList(name,node,linkList)\
{\
	name##Info_t* pstThisNode=(name##Info_t*)node;\
	name##Info_t* pstCurNode = linkList;\
	name##Info_t* pstPreNode = pstCurNode;\
	while(pstCurNode!=NULL)\
	{\
		if(pstCurNode == pstThisNode) break;\
		pstPreNode = pstCurNode;\
		pstCurNode = pstCurNode->pstNext;\
	}\
	if(pstCurNode != pstThisNode) {ROCME_DEMUX_PRINT("Error happens.in fun=%s.line=%d.\n",__FUNCTION__,__LINE__);}\
	else\
	{\
		if(pstCurNode==linkList) {linkList = pstCurNode->pstNext;}\
		else {pstPreNode->pstNext = pstCurNode->pstNext;}\
		free(pstCurNode);\
	}\
}


/**************************************************************************
函数名称: 
            rocme_porting_demux_init
功能说明: 
            DEMUX功能初始化，中间件会在启动时调用此函数，若在启动中间件之前
        机顶盒已经做好了DEMUX的初始化，此函数可以实现为空，直接返回0。
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
INT32_T rocme_porting_demux_init(void)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	do
	{
		if (g_hDemuxInit)
		{
			ROCME_DEMUX_PRINT("[%s]demux has inited\n", __FUNCTION__);
			nRet = ROCME_DEMUX_SUCCESS;
			break;
		}
		
		if (g_hDemuxMutex == 0)
		{
			g_hDemuxMutex  = rocme_porting_mutex_create(ROC_MUTEX_RECURSIVE_NP);
			if (g_hDemuxMutex == 0)
			{
				ROCME_DEMUX_PRINT("[%s]mutex create failed\n", __FUNCTION__);
				nRet = ROCME_DEMUX_FAILURE;
				break;
			}
		}
		
		nRet = HI_UNF_DMX_Init();
		if (nRet != HI_SUCCESS)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_Init errorcode = %d\n", __FUNCTION__, nRet);
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}
		
		nRet = HI_UNF_DMX_AttachTSPort(0,DEFAULT_DVB_PORT);
		if (HI_SUCCESS != nRet)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_Init errorcode = %d\n", __FUNCTION__, nRet);
			nRet = ROCME_DEMUX_FAILURE;
			break;

		}


		g_hDemuxInit = ROC_TRUE;

		ROCME_DEMUX_PRINT("[%s]demux init success\n", __FUNCTION__);
		nRet = ROCME_DEMUX_SUCCESS;
	}while (0);

	return nRet;
}



/**************************************************************************
函数名称: 
            rocme_porting_demux_term
功能说明: 
            卸载DEMUX功能。目前此函数可以实现为空。
参数说明：
    输入参数：
            void
    输出参数：
            无
返    回： 
    成功 : 0            ( 卸载成功 )
    失败 : -1 或 错误码 ( 卸载失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_demux_term(void)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		if (HI_UNF_DMX_DeInit() != HI_SUCCESS)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_DeInit errorcode = %d\n", __FUNCTION__, nRet);
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}
		
		//memset(g_DemuxChannelHandle, 0, sizeof(g_DemuxChannelHandle));
		nRet = ROCME_DEMUX_SUCCESS;
	}while (0);
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	if (nRet == ROCME_DEMUX_SUCCESS)
	{
		rocme_porting_mutex_destroy(g_hDemuxMutex);
		g_hDemuxMutex = 0;
		g_hDemuxInit = ROC_FALSE;
	}

	return nRet;
}



/**************************************************************************
函数名称: 
            rocme_porting_slot_query_PID
功能说明: 
            指定数据通道上，查询一个PID是否已经被某个slot(包括中间件使用的
        slot和中间件之外的slot)占用，若平台不支持slot的PID设定不能重复，此
        功能必须实现。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ pid           ] : 需要查询的PID值
    输出参数：
            
返    回： 
    此PID未被占用 :  0
    此PID已被占用 : -1
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_query_PID(const INT32_T channel_index,const UINT16_T pid)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	HI_HANDLE hChannel;

	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		if (channel_index != ROCME_DEMUX_DEFAULT_ID)
		{
			ROCME_DEMUX_PRINT("[%s]channel_index=%d is invaild\n",__FUNCTION__, channel_index);
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}
		
		nRet = HI_UNF_DMX_GetChannelHandle(channel_index, (unsigned int)pid, &hChannel);

		if ((nRet == HI_SUCCESS) && (hChannel != NULL))
		{
			ROCME_DEMUX_PRINT("[%s]pid =0x%xis not free\n",__FUNCTION__, pid);
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}	

		nRet = ROCME_DEMUX_SUCCESS;
		ROCME_DEMUX_PRINT("[%s]pid=0x%x is free\n",__FUNCTION__, pid);
	}while (0);

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}



static HI_UNF_DMX_CHAN_TYPE_E DemuxGetChannelType(const Roc_Slot_Type_e slot_type)
{
	HI_UNF_DMX_CHAN_TYPE_E eChannelType = HI_UNF_DMX_CHAN_TYPE_BUTT;
	
	switch (slot_type)
	{
		case ROC_SLOT_TYPE_SECTION:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_SEC;
			break;

		case ROC_SLOT_TYPE_PES:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_PES;
			break;
			
		case ROC_SLOT_TYPE_RAW:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_POST;
			break;

		default:
			break;	
	}

	return eChannelType;
}


static void addBufInfoList(struct stListDemuxBufInfo **pListHead, HI_HANDLE hChannel, HI_UNF_DMX_DATA_S stDataBuf)
{
	struct stListDemuxBufInfo *head = *pListHead;
	struct stListDemuxBufInfo *current = NULL;

	current = (struct stListDemuxBufInfo *)rocme_porting_malloc(sizeof(struct stListDemuxBufInfo));
	current->hChannel = hChannel;
	memcpy(&current->stDataBuf, &stDataBuf, sizeof(HI_UNF_DMX_DATA_S));
	current->pNext = NULL;

	/*如果链表为空链表*/
	if (head == NULL)
	{
		*pListHead = current;
	}
	else
	{
		while(head->pNext != NULL)
		{
			head = head->pNext;
		}
		head->pNext = current;
	}

	return;
}


static void delBufInfoList(struct stListDemuxBufInfo **pListHead, HI_HANDLE hChannel, HI_U8 * pu8Buf)
{
	struct stListDemuxBufInfo *head = *pListHead;
	struct stListDemuxBufInfo *pLast, *pNext;

	pLast = head;
	pNext = NULL;

	while (head != NULL)
	{
		if ((head->hChannel == hChannel) && ((head->stDataBuf.pu8Data == pu8Buf ) || (pu8Buf == NULL)))
		{
			pNext = head->pNext;
			
			/*如果要删除的节点为头结点*/
			if (head == *pListHead)
			{
				*pListHead = pNext;
			}
			else
			{
				pLast->pNext = pNext;
			}
			//rocme_porting_dprintf("[%s]head->hChannel=%d, head->stDataBuf->pu8Buf=0x%x\n",__FUNCTION__, head->hChannel, head->stDataBuf.pu8Buf);
			rocme_porting_free(head);
			
			if (pu8Buf == NULL)
			{
				head = *pListHead;
				continue;
			}
			else
			{
				break;
			}
		}

		pLast = head;
		head = head->pNext;
	}

	return;
}



static void addChannelList(struct stListDemuxHandle **pListHead, HI_HANDLE hChannelID)
{
	struct stListDemuxHandle *current = NULL;
	struct stListDemuxHandle *head = NULL;
	
	/*增加节点*/
	current = (struct stListDemuxHandle *)rocme_porting_malloc(sizeof(struct stListDemuxHandle));
	current->hDemuxChannelHandle = hChannelID;
	current->pNext = NULL;
	head = *pListHead;
	
	/*如果链表为空链表*/
	if (head == NULL)
	{
		*pListHead = current;
	}
	else
	{
		while (head->pNext != NULL)
		{
			head = head->pNext;
		}
		/*找到一个链表尾*/
		head->pNext = current;
	}

	return;
}



static void delChannelList(struct stListDemuxHandle **pListHead, HI_HANDLE hChannelID)
{
	struct stListDemuxHandle *head = *pListHead;
	struct stListDemuxHandle *pLast, *pNext;

	pLast = head;
	pNext = NULL;
	while (head != NULL)
	{
		/*找到要删除的节点*/
		if (head->hDemuxChannelHandle == hChannelID)
		{
			pNext = head->pNext;
			rocme_porting_free(head);
			/*删除的节点为头结点*/
			if (head == *pListHead)
			{
				*pListHead = pNext;
			}
			else
			{
				pLast->pNext = pNext;
			}
			
			break;
		}

		pLast = head;
		head = head->pNext;
	}

	return;
}


/**************************************************************************
函数名称: 
            rocme_porting_slot_alloc
功能说明: 
            在指定的数据通道上申请分配一个slot(指定slot的类型、buff的大小)，
        若成功申请到slot，返回一个slot的控制ID，中间件获得对此slot的控制权，
        即通过此ID对此slot设备进行修改、启动、释放等具体操作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ slot_type     ] : slot的类型，具体如下:
                                ROC_SLOT_TYPE_NULL     -  used with inject carousel 
                            packet only flag
                                ROC_SLOT_TYPE_SECTION  -  for section data - Signal 
                            every section
                                ROC_SLOT_TYPE_PES      -  signal every complete PES
                            packet except when signal_on_every_transport_packet is 
                            supplied as a flag
                                ROC_SLOT_TYPE_RAW      -  Raw transport packets, si-
                            -gnalled every packet
                                ROC_SLOT_TYPE_PCR      -  specifies that the data c-
                            -ollected on this slot is collected for PCR gathering purposes
                                ROC_SLOT_TYPE_RESERVE  -  扩展保留
             [ buff_size    ] : 需要开辟的slot使用的buff的大小，中间件除特殊情况外，
                            会申请64KB。
    输出参数：
            无
返    回： 
    成功 : 申请到的slot控制ID ( 申请成功 )
    失败 : -1 或 错误码       ( 申请失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_alloc(const INT32_T channel_index,const Roc_Slot_Type_e slot_type,const INT32_T buff_size)
{
	INT32_T nRet = 0;
	HI_UNF_DMX_CHAN_ATTR_S stChanAttr;
	INT32_T nSlotID = ROCME_DEMUX_FAILURE;
	HI_HANDLE hChannelID;
	struct stListDemuxHandle *head, *current;
	

	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		nRet = HI_UNF_DMX_GetChannelDefaultAttr(&stChanAttr);
		if (nRet != HI_SUCCESS)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_GetChannelDefaultAttr failed errorcode =%d\n", __FUNCTION__, nRet);
			nSlotID = ROCME_DEMUX_FAILURE;
			break;
		}
		
		stChanAttr.enChannelType = DemuxGetChannelType(slot_type);
		if (stChanAttr.enChannelType == HI_UNF_DMX_CHAN_TYPE_SEC)
		{
			stChanAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_DISCARD; 
		}
		else
		{
			stChanAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_FORBID; 
		}

		stChanAttr.u32BufSize = buff_size;

		nRet = HI_UNF_DMX_CreateChannel(ROCME_DEMUX_DEFAULT_ID, &stChanAttr,&hChannelID);
		if (nRet != HI_SUCCESS)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_CreateChannel failed errorcode=%d\n", __FUNCTION__, nRet);
			nSlotID = ROCME_DEMUX_FAILURE;
			break;
		}

		nSlotID = hChannelID;

		addChannelList(&g_pstDemuxHandleList, nSlotID);
    }while(0);

    rocme_porting_mutex_unlock(g_hDemuxMutex);

    return nSlotID;
}




/**************************************************************************
函数名称: 
            rocme_porting_slot_modify
功能说明: 
            根据slot_ID，修改相应的slot设备的一级过滤条件(即具体PID值)。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ pid        ] : 需要设置的一级过滤条件值
    输出参数：
            无
返    回： 
    成功 : 0            ( 修改slot一级过滤条件成功 )
    失败 : -1 或 错误码 ( 修改slot一级过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_modify(const INT32_T slot_ID,const UINT16_T pid)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

    if(HI_UNF_DMX_CloseChannel(slot_ID) == HI_SUCCESS)
    {
        nRet = ROCME_DEMUX_SUCCESS;
    }
    if (HI_UNF_DMX_SetChannelPID(slot_ID, pid) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    }
    else
    {
        nRet = ROCME_DEMUX_FAILURE;
        ROCME_DEMUX_PRINT("[%s] failed \n", __FUNCTION__);
    }
    
    rocme_porting_mutex_unlock(g_hDemuxMutex);

    return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_slot_clear
功能说明: 
            根据slot_ID，清除其设置的一级过滤条件(即具体的PID值)。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 清除slot过滤条件成功 )
    失败 : -1 或 错误码 ( 清除slot过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_clear(const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

    HI_UNF_DMX_CloseChannel(slot_ID);
    if(HI_UNF_DMX_SetChannelPID(slot_ID, 0x1fff) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    }

    rocme_porting_mutex_unlock(g_hDemuxMutex);
    return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_slot_start
功能说明: 
            启动一个slot设备开始过滤数据，如果底层平台的slot设备无此设置的实现，
        则此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 启动slot设备成功 )
    失败 : -1 或 错误码 ( 启动slot设备失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_start(const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(HI_UNF_DMX_OpenChannel(slot_ID) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    }
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_slot_stop
功能说明: 
            停止一个slot设备过滤数据，如果底层平台的slot设备无此设置的实现，
        则此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 停止slot设备成功 )
    失败 : -1 或 错误码 ( 停止slot设备失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_stop(const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(HI_UNF_DMX_CloseChannel(slot_ID) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    }
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}
/**************************************************************************
函数名称: 
            rocme_porting_slot_free
功能说明: 
            释放掉对一个指定slot的控制权。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 释放成功 )
    失败 : -1 或 错误码 ( 释放失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_free(const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(HI_UNF_DMX_DestroyChannel(slot_ID) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    	delBufInfoList(&g_pstDemuxBufInfoList, slot_ID, NULL);
    	delChannelList(&g_pstDemuxHandleList, slot_ID);
    }
    
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_wait
功能说明: 
            指定数据通道索引，中间件通过此方法主动查询是否有slot过滤到数据，
        并且可以设置等待超时时限，若此数据通道上过滤到了数据，则返回过滤到
        了数据的slot控制ID。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ time_out_ms   ] : 超时时间，单位为毫秒(ms)
    输出参数：
            
返    回： 
    成功 : slot控制ID   ( 成功查询到有slot过滤到数据 )
    失败 : -1 或 错误码 ( 查询失败/slot在time_out_ms时限内未过滤到数据 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait(const INT32_T channel_index,const INT32_T time_out_ms)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	HI_HANDLE hChannel = 0;
	HI_U32 u32AcquireNum = 1;
	HI_U32 u32ReadNum;
	struct stListDemuxHandle *head = g_pstDemuxHandleList;
	HI_UNF_DMX_DATA_S stBuf;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	while (head != NULL)
	{
		hChannel = head->hDemuxChannelHandle;
		
		if(HI_UNF_DMX_AcquireBuf(hChannel, u32AcquireNum,&u32ReadNum, &stBuf,0)== HI_SUCCESS)
		{
			nRet = hChannel;
			addBufInfoList(&g_pstDemuxBufInfoList, hChannel, stBuf);
			break;
		}

		head = head->pNext;
	}
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}


static ROC_BOOL CheckHandleValid(HI_HANDLE hChannel, HI_HANDLE *phGetChannel, int nNum)
{
	int ii;
	ROC_BOOL bRet = ROC_FALSE;

	for (ii=0; ii<nNum; ii++)
	{
		if (phGetChannel[ii] == hChannel)
		{
			bRet = ROC_TRUE;
			break;
		}
	}

	return bRet;
}


INT32_T rocme_porting_slot_buff_wait_multi(const INT32_T channel_index, INT32_T *slot_ID_ar, INT32_T *count , const INT32_T time_out_ms)
{
#if 0
	*slot_ID_ar = rocme_porting_slot_buff_wait(channel_index,time_out_ms);
	if(ROCME_DEMUX_FAILURE!=*slot_ID_ar)
	{
		*count = 1;
		return ROC_OK;
	}
    Sleep(20);
	return ROC_ERR;
#else
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	HI_HANDLE hChannel = 0;
	HI_U32 u32AcquireNum = 1;
	HI_U32 u32ReadNum;
	HI_HANDLE hGetChannel[32];
	UINT32_T u32ChNum = 0;
	struct stListDemuxHandle *head = NULL;
	HI_UNF_DMX_DATA_S stBuf;
	int nSlotIndex = 0;


	if ((slot_ID_ar == NULL) || (count == NULL) || (*count <= 0))
	{
		return ROCME_DEMUX_FAILURE;
	}


	u32ChNum = sizeof(hGetChannel)/sizeof(HI_HANDLE);
    nRet = HI_UNF_DMX_GetDataHandle(hGetChannel, &u32ChNum, 100);
	if (nRet != HI_SUCCESS)
	{
		//rocme_porting_dprintf("[%s]exit, nRet=[0x%x]\n", __FUNCTION__, nRet);
		return ROCME_DEMUX_FAILURE;
	}

	rocme_porting_mutex_lock(g_hDemuxMutex);
	head = g_pstDemuxHandleList;
	//rocme_porting_mutex_unlock(g_hDemuxMutex);
	
	while (head != NULL)
	{
		hChannel = head->hDemuxChannelHandle;
		if (!CheckHandleValid(hChannel, hGetChannel, u32ChNum))
		{
			head = head->pNext;
			continue;
		}

        nRet = HI_UNF_DMX_AcquireBuf(hChannel, u32AcquireNum,&u32ReadNum, &stBuf,100);
		
		if(nRet == HI_SUCCESS)
		{
            rocme_porting_dprintf("rocme_porting_slot_buff_wait_multi: addBufInfoList [0x%x] \n", u32ReadNum);
			if (nSlotIndex < *count)
			{
				slot_ID_ar[nSlotIndex] = hChannel;
				nSlotIndex++;
			}
			else
			{
				break;
			}
		//	rocme_porting_mutex_lock(g_hDemuxMutex);
			addBufInfoList(&g_pstDemuxBufInfoList, hChannel, stBuf);
		//	rocme_porting_mutex_unlock(g_hDemuxMutex);
		}
        else
        {
            rocme_porting_dprintf("HI_UNF_DMX_AcquireBuf Fail. nRet=[0x%x]!\n", nRet);
        }

		head = head->pNext;
	}

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	if (nSlotIndex > 0)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}
	*count = nSlotIndex;

	//rocme_porting_dprintf("[%s]exit\n", __FUNCTION__);
	return nRet;
#endif
}

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_get
功能说明: 
            从指定slot的buff中的复制(提取)出指定长度的数据，中间件只有在调用
        了rocme_porting_slot_buff_wait后，才会使用此函数判断过滤的数据的归属。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ *buff_ptr  ] : 存储提取到的数据的buff的头指针
            [ buff_size  ] : 需要提取的数据的长度，即存储buff的长度
    输出参数：
            [ *data_size ] : 实际提取到的数据的长度
返    回： 
    成功 : 0            ( 提取数据成功 )
    失败 : -1 或 错误码 ( 提取数据失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_get(const INT32_T slot_ID, UINT8_T *buff_ptr, const UINT32_T buff_size, UINT32_T *data_size)
{
	struct stListDemuxBufInfo *head = g_pstDemuxBufInfoList;
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		if ((buff_ptr == NULL) || (buff_size == 0) ||(data_size == NULL))
		{
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}

		while (head != NULL)
		{
			if (head->hChannel == slot_ID)
			{
				*data_size = head->stDataBuf.u32Size > buff_size ? buff_size : head->stDataBuf.u32Size;
				memcpy(buff_ptr, head->stDataBuf.pu8Data, *data_size);
				nRet = ROCME_DEMUX_SUCCESS;
				break;
			}
			
			head = head->pNext;
		}
	}while (0);
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}



/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_read
功能说明: 
            从指定的slot的buff中读取数据，读取数据后，要求清空buff。中间件会
        要求将slot的buff中的数据读到2个buff中，分别是data0和data1，读取数据时
        ，先将数据读到data0中，当data0放满后，再将数据读取到data1中，当空间不
        够时，返回读取失败。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ *p_data0   ] : 存储缓冲区0的头指针
            [ size0      ] : 存储缓冲区0的长度
            [ *p_data1   ] : 存储缓冲区1的头指针
            [ size1      ] : 存储缓冲区1的长度
    输出参数：
            [ *datasize  ] : 实际读取到的数据长度
返    回： 
    成功 : 0            ( 读取数据成功 )
    失败 : -1 或 错误码 ( 读取数据失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_read(const INT32_T slot_ID, UINT8_T *p_data0, UINT32_T size0, UINT8_T *p_data1, UINT32_T size1, UINT32_T *datasize)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	struct stListDemuxBufInfo *head = g_pstDemuxBufInfoList;
	UINT32_T unData0ReadSize = 0;
	UINT32_T unReadSize = 0;
	UINT32_T unLeftSize = 0;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		if ((p_data0 == NULL) || (datasize == NULL))
		{	
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}

		while (head != NULL)
		{
			if (head->hChannel == slot_ID)
			{
				*datasize = 0;
				if (head->stDataBuf.u32Size > (size0+size1))
				{
					ROCME_DEMUX_PRINT("[%s]head->stDataBuf.u32Size=%d, (size0+size1)=%d\n", 
					__FUNCTION__, head->stDataBuf.u32Size, (size0+size1));
					nRet = ROCME_DEMUX_FAILURE;
					break;
				}
				unReadSize = head->stDataBuf.u32Size > size0 ? size0 : head->stDataBuf.u32Size;
				unData0ReadSize = unReadSize;
				memcpy(p_data0, head->stDataBuf.pu8Data, unReadSize);
				*datasize += unReadSize;
				unLeftSize = head->stDataBuf.u32Size - unReadSize;
				unReadSize = unLeftSize > size1? size1:unLeftSize;
				if ((unReadSize > 0) && (p_data1 != NULL))
				{
					memcpy(p_data1, head->stDataBuf.pu8Data+unData0ReadSize, unReadSize);
					*datasize += unReadSize;
				}

				if (*datasize != head->stDataBuf.u32Size)
				{
					nRet = ROCME_DEMUX_FAILURE;
					break;
				}
				/*释放buf, 删除节点*/
				HI_UNF_DMX_ReleaseBuf(slot_ID, 1,&head->stDataBuf);
				delBufInfoList(&g_pstDemuxBufInfoList, slot_ID, head->stDataBuf.pu8Data);
				
				nRet = ROCME_DEMUX_SUCCESS;
				break;
			}
			
			head = head->pNext;
		}
		
	}while (0);

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
	
}

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_flush
功能说明: 
            清空指定的slot的buff。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 清除指定slot的buff成功 )
    失败 : -1 或 错误码 ( 清除指定slot的buff失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_flush(const INT32_T slot_ID)
{
    //ROCME_DEMUX_PRINT("[%s]not supported yet\n", __FUNCTION__);
    return 0;
}

/**************************************************************************
函数名称: 
            rocme_porting_filter_alloc
功能说明: 
            在指定的数据通道上申请分配一个filter(指定filter的类型)，若成功申
        请到filter，返回一个filter的控制ID，中间件获得对此filter的控制权，即
        通过此ID对此filter设备进行修改、启动、释放等具体操作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ filter_type   ] : filter的类型，具体如下:
                                ROC_FILTER_TYPE_SECTION       -  Provides 8 byte filter/mask
                                ROC_FILTER_TYPE_PES           -  Filter PES
                                ROC_FILTER_TYPE_TSHEADER      -  Filter TSHeader
                                ROC_FILTER_TYPE_PES_STREAMID  -  Filter PES stream ID
                                ROC_FILTER_TYPE_NEG_MATCH     -  Negative Match Mode filtering
                                ROC_FILTER_TYPE_RESERVE       -  扩展保留
    输出参数：
            无
返    回： 
    成功 : 申请到的filter控制ID ( 申请成功 )
    失败 : -1 或 错误码         ( 申请失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_alloc(const INT32_T channel_index,const Roc_Filter_Type_e filter_type)
{
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;
	HI_HANDLE hFilter;
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	FilterInfo_t* pstNewFilter = NULL;
	
	//rocme_porting_mutex_lock(g_hDemuxMutex);

	//memset(&stFilterAttr,0,sizeof(HI_UNF_DMX_FILTER_ATTR_S));
	stFilterAttr.u32FilterDepth = 0;
	memset(&stFilterAttr.au8Match,0,sizeof(stFilterAttr.au8Match));
	memset(&stFilterAttr.au8Mask,0,sizeof(stFilterAttr.au8Mask));
	memset(&stFilterAttr.au8Negate,0,sizeof(stFilterAttr.au8Negate));

	nRet = HI_UNF_DMX_CreateFilter(ROCME_DEMUX_DEFAULT_ID, &stFilterAttr, &hFilter);
	if (nRet != HI_SUCCESS)
	{
		ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_CreateFilter failed.err=%#x.\n", __FUNCTION__,nRet);
		nRet = ROCME_DEMUX_FAILURE;
	}
	else
	{
		nRet = hFilter;
	}

	pstNewFilter = malloc(sizeof(FilterInfo_t));
	if(pstNewFilter == NULL)
	{
		ROCME_DEMUX_PRINT("Error happens.in fun=%s.line=%d.\n",__FUNCTION__,__LINE__);
		nRet = ROCME_DEMUX_FAILURE;
	}
	else
	{
		memset(pstNewFilter,0,sizeof(FilterInfo_t));
		pstNewFilter->hFilter = hFilter;
		AddNode2LinkList(Filter,pstNewFilter,g_pstFilterInfo);
		ROCME_DEMUX_PRINT("fun=%s.line=%d.g_pstFilterInfo=%#x.\n",__FUNCTION__,__LINE__,g_pstFilterInfo);
	}

	//rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_filter_associate
功能说明: 
            将指定的slot和filter关联起来。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 关联成功 )
    失败 : -1 或 错误码 ( 关联失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_associate(const INT32_T filter_ID,const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if (HI_UNF_DMX_AttachFilter(filter_ID, slot_ID) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}	

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_filter_disassociate
功能说明: 
            将指定的slot和filter断开。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到        
    输出参数：
            无
返    回： 
    成功 : 0            ( 断开成功 )
    失败 : -1 或 错误码 ( 断开失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_disassociate(const INT32_T filter_ID,const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if (HI_UNF_DMX_DetachFilter(filter_ID, slot_ID) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_filter_modify
功能说明: 
            根据filter_ID，修改相应的filter设备的二级过滤条件(即具体cofe和mask值)。
        例如，过滤TDT，设置这两项为:
        cafe[8]赋值为{0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        mask[8]赋值为{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00}.
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ *cofe      ] : 二级过滤条件头指针
            [ c_size     ] : 二级过滤条件长度
            [ *mask      ] : 二级过滤条件掩码值头指针
            [ m_size     ] : 二级过滤条件掩码值长度
    输出参数：
            
返    回： 
    成功 : 0            ( 修改二级过滤条件成功 )
    失败 : -1 或 错误码 ( 修改二级过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_modify(const INT32_T filter_ID,
                                    const UINT8_T*cofe,const UINT8_T c_size,
                                    const UINT8_T*mask,const UINT8_T m_size,
                                    const UINT8_T*nega,const UINT8_T m_nega)
{
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr ;
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	UINT8_T tmpmask[DMX_FILTER_MAX_DEPTH];
	UINT8_T tmpnega[DMX_FILTER_MAX_DEPTH];
	int ii;
	FilterInfo_t* pstFilter;

	//ROCME_DEMUX_PRINT("fun=%s.line=%d.\n",__FUNCTION__,__LINE__);

	if ((cofe==NULL) || (mask == NULL) || (c_size == 0) ||(m_size == NULL))
	{
		return ROCME_DEMUX_FAILURE;
	}

	if ((c_size > DMX_FILTER_MAX_DEPTH) || (m_size > DMX_FILTER_MAX_DEPTH))
	{
		ROCME_DEMUX_PRINT("[%s]max size is %d \n", __FUNCTION__, DMX_FILTER_MAX_DEPTH);
		return ROCME_DEMUX_FAILURE;
	}
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

	for (ii=0; ii<m_size; ii++)
	{
		tmpmask[ii] = ~mask[ii];
	}

	for (ii=0; ii<m_nega; ii++)
	{
		tmpnega[ii] = nega[ii];
	}

	
#if 0	
	memset(&stFilterAttr, 0, sizeof(HI_UNF_DMX_FILTER_ATTR_S));
	stFilterAttr.u32FilterDepth = c_size > m_size ? c_size : m_size;
	memcpy(stFilterAttr.au8Match, cofe, c_size);
	memcpy(stFilterAttr.au8Mask, tmpmask, m_size);
	/*print filter attr.
		int i=0; 
		ROCME_DEMUX_PRINT("fun=%s.line=%d.stFilterAttr.u32FilterDepth=%d.\n", __FUNCTION__,__LINE__,stFilterAttr.u32FilterDepth);
		ROCME_DEMUX_PRINT("math  :");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Match[i]);
		ROCME_DEMUX_PRINT("\nmask  :");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Mask[i]);
		ROCME_DEMUX_PRINT("\nnegate:");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Negate[i]);        
		ROCME_DEMUX_PRINT("\n");*/
	if (HI_UNF_DMX_SetFilterAttr(filter_ID, &stFilterAttr) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}
#else
	FindNodeFromLinkList(Filter,filter_ID,pstFilter,g_pstFilterInfo);
	if(pstFilter!=NULL)
	{
		memcpy(pstFilter->au8Match, cofe, c_size);
		memcpy(pstFilter->au8Mask, tmpmask, m_size);
		nRet = ROCME_DEMUX_SUCCESS;
	}
#endif
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	//ROCME_DEMUX_PRINT("fun=%s.line=%d.\n",__FUNCTION__,__LINE__);

	return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_filter_start
功能说明: 
            根据filter_ID，启动一个filter设备开始工作。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( filter设备启动成功 )
    失败 : -1 或 错误码 ( filter设备启动失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_start(const INT32_T filter_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	FilterInfo_t* pstFilter;
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr ;

	//ROCME_DEMUX_PRINT("[%s]not supported\n", __FUNCTION__);
	
	FindNodeFromLinkList(Filter,filter_ID,pstFilter,g_pstFilterInfo);
	if(pstFilter != NULL)
	{
		memset(&stFilterAttr, 0, sizeof(HI_UNF_DMX_FILTER_ATTR_S));
		stFilterAttr.u32FilterDepth = 8;//?
		memcpy(stFilterAttr.au8Match, pstFilter->au8Match, 8);
		memcpy(stFilterAttr.au8Mask, pstFilter->au8Mask, 8);

		/*print filter attr.
		int i=0; 
		ROCME_DEMUX_PRINT("fun=%s.line=%d.stFilterAttr.u32FilterDepth=%d.\n", __FUNCTION__,__LINE__,stFilterAttr.u32FilterDepth);
		ROCME_DEMUX_PRINT("math  :");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Match[i]);
		ROCME_DEMUX_PRINT("\nmask  :");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Mask[i]);
		ROCME_DEMUX_PRINT("\nnegate:");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Negate[i]);        
		ROCME_DEMUX_PRINT("\n");*/
		
		if (HI_UNF_DMX_SetFilterAttr(filter_ID, &stFilterAttr) == HI_SUCCESS)
		{
			nRet = ROCME_DEMUX_SUCCESS;
		}
	}
	
	return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_filter_stop
功能说明: 
            根据filter_ID，停止一个filter设备的工作。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( filter设备停止成功 )
    失败 : -1 或 错误码 ( filter设备停止失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_stop(const INT32_T filter_ID)
{
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr ;
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);
	memset(&stFilterAttr, 0, sizeof(HI_UNF_DMX_FILTER_ATTR_S));
	if (HI_UNF_DMX_SetFilterAttr(filter_ID, &stFilterAttr) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
函数名称: 
            rocme_porting_filter_free
功能说明: 
            释放掉对一个fitler设备的控制权。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 释放成功 )
    失败 : -1 或 错误码 ( 释放失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_free(const INT32_T filter_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	FilterInfo_t* pstFilter;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if (HI_UNF_DMX_DestroyFilter(filter_ID) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
		FindNodeFromLinkList(Filter, filter_ID, pstFilter, g_pstFilterInfo);
		DelNodeFromLinkList(Filter,pstFilter,g_pstFilterInfo)
	}
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}


#if 0/*test code*/

#define TEST_PRINT printf
#define DO_FAIL_PRINT(fun)\
{\
    if(ROC_OK != (fun)) TEST_PRINT("Error happens,in fun=%s.line=%d.\n",__FUNCTION__,__LINE__);\
}

INT32_T testDmxEnter(void)
{
    INT32_T nSlotID;
    INT32_T nFilterID1;
    INT32_T nFilterID2;
    UINT8_T cofe1[8]={0x50, 0x00, 0x00, 0x00, 0x00, 0x00,0x00,0x00};
    UINT8_T mask1[8]={0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    UINT8_T cofe2[8]={0x4e, 0x00, 0x00, 0x00, 0x00, 0x00,0x00,0x00};
    UINT8_T mask2[8]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    char *pData0 = NULL;
    char* pData1 = NULL;
    UINT32_T nDatasize;
    INT32_T nDataSlot;
    
    DO_FAIL_PRINT(testLockTuner(259,2000));

    DO_FAIL_PRINT(rocme_porting_demux_init());

    nSlotID = rocme_porting_slot_alloc(0,ROC_SLOT_TYPE_SECTION,64*1024);
    DO_FAIL_PRINT(nSlotID>0?ROC_OK:ROC_ERR);
    TEST_PRINT("fun=%s.line=%d.nSlotID=%#x.\n",__FUNCTION__,__LINE__,nSlotID);
    
    DO_FAIL_PRINT(rocme_porting_slot_modify(nSlotID, 0x12));    
    
    nFilterID1 = rocme_porting_filter_alloc(0,ROC_FILTER_TYPE_SECTION);
    DO_FAIL_PRINT(nFilterID1>0?ROC_OK:ROC_ERR);
    TEST_PRINT("fun=%s.line=%d.nFilterID1=%#x.\n",__FUNCTION__,__LINE__,nFilterID1);
    nFilterID2 = rocme_porting_filter_alloc(0,ROC_FILTER_TYPE_SECTION);
    DO_FAIL_PRINT(nFilterID2>0?ROC_OK:ROC_ERR);
    TEST_PRINT("fun=%s.line=%d.nFilterID2=%#x.\n",__FUNCTION__,__LINE__,nFilterID2);

    DO_FAIL_PRINT(rocme_porting_filter_associate(nFilterID1,nSlotID));                
    DO_FAIL_PRINT(rocme_porting_filter_associate(nFilterID2,nSlotID));
    TEST_PRINT("fun=%s.line=%d.filter associate ok.\n",__FUNCTION__,__LINE__);	

    DO_FAIL_PRINT(rocme_porting_filter_modify(nFilterID1,cofe1,8,mask1,8));
    TEST_PRINT("fun=%s.line=%d.filter modify ok.\n",__FUNCTION__,__LINE__);
    DO_FAIL_PRINT(rocme_porting_filter_modify(nFilterID2,cofe2,8,mask2,8));
    TEST_PRINT("fun=%s.line=%d.filter modify ok.\n",__FUNCTION__,__LINE__);

    DO_FAIL_PRINT(rocme_porting_slot_start(nSlotID));
    TEST_PRINT("fun=%s.line=%d.slot start ok.\n",__FUNCTION__,__LINE__);
    
    DO_FAIL_PRINT(rocme_porting_filter_start(nFilterID1));
    DO_FAIL_PRINT(rocme_porting_filter_start(nFilterID2));
    TEST_PRINT("fun=%s.line=%d.filter start ok.\n",__FUNCTION__,__LINE__);

	

    pData0 = malloc(512*1024);
    DO_FAIL_PRINT(pData0!=NULL?ROC_OK:ROC_ERR);
    memset(pData0,0,512*1024);

    while(1)
    {
        nDataSlot = rocme_porting_slot_buff_wait(0,0x7fffffff);
        TEST_PRINT("fun=%s.line=%d.wait nDataSlot=%#x.\n",__FUNCTION__,__LINE__,nDataSlot);
    
        DO_FAIL_PRINT(rocme_porting_slot_buff_get(nDataSlot, pData0, 10, &nDatasize));
        TEST_PRINT("fun=%s.line=%d.get tableid=%#x.\n",__FUNCTION__,__LINE__,pData0[0]);
        
        DO_FAIL_PRINT(rocme_porting_slot_buff_read(nDataSlot,pData0,512*1024,pData1,0,&nDatasize));
        TEST_PRINT("fun=%s.line=%d.read tableid=%#x.nDatasize=%d.\n",__FUNCTION__,__LINE__,pData0[0],nDatasize);
    }

    while(1)
    {
        rocme_porting_task_sleep(3000);
        TEST_PRINT("fun into sleep while.\n",__FUNCTION__);
    }
}

#endif

