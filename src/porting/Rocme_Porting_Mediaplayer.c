/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_mediaplayer.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/

#include <malloc.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "hi_type.h"
#include "hi_unf_avplay.h"
#include "hi_svr_player.h"
#include "hi_unf_vo.h"

#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.AC3.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.DTS.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.EAC3.decode.h"
#include "HA.AUDIO.G711.codec.h"
#include "HA.AUDIO.G722.codec.h"
#include "HA.AUDIO.TRUEHD.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.COOK.decode.h"
#include "porter_rocme.h"


#ifdef __cplusplus
extern "C"
{
#endif

extern HI_HANDLE						g_hAvHandle; 
extern HI_HANDLE						g_hAoHandle; 
extern HI_HANDLE						g_hVoHandle; 
extern HI_HANDLE						g_hDispHandle;

/************************************************************************************
 * 初始化平台媒体解码器模块
 * 
 * 参数:	
 *		无
 *		
 * 说明:
 *		无
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_init(void)
{
}

/************************************************************************************
 * 销毁平台媒体解码器模块
 * 
 * 参数:	
 *		无
 *		
 * 说明:
 *		无
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_term(void)
{
}

INT32_T rocme_porting_media2_codec(UINT32_T *CodecMask)
{
}

/************************************************************************************
 * 从平台打开一个硬件媒体解码器
 * 
 * 参数:	
 *		@MediaHandle: 返回平台解码器句柄, 对平台解码器的操作基于此句柄
 *		@OpenParams
 *           .StreamType: ROC_MEDIA_STREAM_VIDEO	-获取视频解码器
 *                        ROC_MEDIA_STREAM_AUDIO	-获取音频解码器,
 *                        ROC_MEDIA_STREAM_TS	    -获取TS流解码器
 *                         
 *           .CodecType:  基本码流的编码格式, 参见Roc_Media_Stream_t定义
 *           
 *           .BufferHandler: 操作解码器输入位流缓存的上下文对象
 *
 *           .GetWriteAddress_p: 平台解码器通过此函数接口获取位流缓存的写指针
 *
 *           .InformReadAddress_p: 平台解码器通过此函数接口通知应用更新位流缓存的读指针
 *             
 *           .BitBufferAddr: 返回位流缓存的基地址
 *
 *           .BitBufferSize: 返回位流缓存的大小
 *		
 * 说明:
 *		
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_open(UINT32_T *MediaHandle,
								  Roc_Media_OpenParams_t *OpenParams,
								  void **BitBufferBase,
								  UINT32_T *BitBufferSize)
{
	return ROC_OK;
}

/************************************************************************************
 * 关闭平台解码器
 * 
 * 参数:	
 *		@MediaHandle	平台解码器对象句柄
 *		
 * 说明:
 *
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_close(UINT32_T MediaHandle)
{
}

/************************************************************************************
 * 启动平台的解码器开始解码
 * 
 * 参数:	
 *		@MediaHandle			平台解码器对象句柄
 *		
 * 说明:
 *		调用此接口开始平台解码器的解码
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_start(UINT32_T MediaHandle)
{
}

/************************************************************************************
 * 停止平台解码器的解码
 * 
 * 参数:	
 *		@MediaHandle: 解码器句柄
 *		
 * 说明:
 *		None
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_stop(UINT32_T MediaHandle)
{
	HI_UNF_AVPLAY_STOP_OPT_S strStopOpt;	
	
	/*保留最后一帧*/
	strStopOpt.enMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
			
	strStopOpt.u32TimeoutMs = 0;
	DOFUNC_RETURN_ERR( HI_UNF_AVPLAY_Stop(MediaHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &strStopOpt), ROC_ERR );
	DOFUNC_RETURN_ERR( HI_UNF_AVPLAY_Stop(MediaHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL ), ROC_ERR );

	return ROC_OK;
}

INT32_T rocme_porting_media2_pause(UINT32_T MediaHandle)
{
	HI_UNF_AVPLAY_STOP_OPT_S strStopOpt;

	strStopOpt.enMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
	strStopOpt.u32TimeoutMs = 0;
	printf("HI_UNF_AVPLAY_Pause_____\n");
	DOFUNC_RETURN_ERR( HI_UNF_AVPLAY_Pause(MediaHandle, &strStopOpt), ROC_ERR );

	return ROC_OK;

}

INT32_T rocme_porting_media2_resume(UINT32_T MediaHandle)
{
	DOFUNC_RETURN_ERR( HI_UNF_AVPLAY_Start( MediaHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, NULL ), ROC_ERR );   

	return ROC_OK;
}

INT32_T rocme_porting_media2_hide(UINT32_T MediaHandle)
{
}

INT32_T rocme_porting_media2_display(UINT32_T MediaHandle)
{
}

INT32_T rocme_porting_media2_subscribe_event(UINT32_T MediaHandle, 
										     Roc_Media_Event_t Event, 
										     Roc_Media_EventCallback_t CallbackFunc,
										     void *SubscriberData)
{
}

INT32_T rocme_porting_media2_unsubscribe_event(UINT32_T MediaHandle, Roc_Media_Event_t Event)
{
}


#ifdef __cplusplus
}
#endif