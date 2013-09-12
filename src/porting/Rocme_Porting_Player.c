/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_player.cpp
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
#include "hi_unf_sound.h"
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

static unsigned char g_Media_Init_Status =0;

HI_HANDLE TDRV_MediaPlayerHandle;

extern HI_HANDLE TDRV_GetAVHandle();
extern HI_HANDLE TDRV_GetWindonHandle();


HI_S32 Media_Play_Notify(HI_HANDLE hPlayer, HI_SVR_PLAYER_EVENT_S *pstruEvent)
{
	ROCME_TEST_PRINT
	switch(pstruEvent->eEvent)
	{
		case HI_SVR_PLAYER_EVENT_STATE:
			break;
		case HI_SVR_PLAYER_EVENT_SOF:

			break;
		case HI_SVR_PLAYER_EVENT_EOF:
			break;
		case HI_SVR_PLAYER_EVENT_PROGRESS:
			break;
		case HI_SVR_PLAYER_EVENT_STREAMID_CHG:
			break;
		case HI_SVR_PLAYER_EVENT_BUTT:
			break;
		default:
			break;
	}
	return 0;
}


/************************************************************************************
 * 初始化解码器模块
 * 
 * 参数:	
 *		None
 *		
 * 说明: 
 *		初始化播放器模块，在中间件启动时调用，完成:
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_init(void)
{
	ROCME_TEST_PRINT
	HI_S32 s32Ret = HI_SUCCESS;
	
	if(g_Media_Init_Status==0)
	{
		if(HI_SVR_PLAYER_Init())
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Init error \n");
			return ROC_PORTING_PLAYER_FAILURE;
		}


		s32Ret = HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libformat.so");
		if (HI_SUCCESS != s32Ret)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"register file parser libformat.so fail, ret = 0x%x \n", s32Ret);
		}
		
		s32Ret = HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libffmpegformat.so");
		if (HI_SUCCESS != s32Ret)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"register file parser libffmpegformat.so fail, ret = 0x%x \n", s32Ret);
		}
		g_Media_Init_Status = 1;

	}
	return ROC_PORTING_PLAYER_SUCCESS;
}


/************************************************************************************
 * 去初始化解码器模块
 * 
 * 参数:	
 *		None
 *		
 * 说明:
 *		释放初始化时创建的资源
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_deinit(void)
{
	ROCME_TEST_PRINT
	if(g_Media_Init_Status == 1)
	{
		if( HI_SVR_PLAYER_Deinit() == HI_SUCCESS)
		{
			return ROC_PORTING_PLAYER_SUCCESS;
		}
		else
		{			
			ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Deinit error \n");
			return ROC_PORTING_PLAYER_FAILURE;
		}
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"not init  \n");
		return ROC_PORTING_PLAYER_FAILURE;
		
	}
	
}


/************************************************************************************
 * 创建一个播放器实例
 * 
 * 参数:	
 *		@pPlayerParam	创建播放器实例的参数
 *		@phPlayer	用户提供指针，接口调用成功返回播放器实例句柄，否则返回NULL
 *		
 * 说明:
 *		1) 
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS	    成功
 *		ROC_PORTING_PLAYER_FAILURE	    失败  
 *      ROC_PORTING_PLAYER_INVALID_PARAM   参数错误
 ************************************************************************************/
 Roc_Player_ErrCode_e rocme_porting_player_create(Roc_Player_Param_t *pPlayerParam, INT32_T *phPlayer)
{
	ROCME_TEST_PRINT
		HI_S32 s32Ret = HI_SUCCESS;
		HI_SVR_PLAYER_PARAM_S params;

		if((NULL == pPlayerParam)||(NULL == phPlayer))
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"params error \n");
			return ROC_PORTING_PLAYER_INVALID_PARAM;
		}
		memset(&params, 0, sizeof(HI_SVR_PLAYER_PARAM_S));
		#if 0
		params.hAVPlayer= TDRV_GetAVHandle();
		params.w = pPlayerParam->w;
		params.y = pPlayerParam->y;
		params.x = pPlayerParam->x;
		params.h = pPlayerParam->h;
		#endif
		params.x = 0;
 		params.y = 0;
 		params.w = 1920;
 		params.h = 1080;
 		params.u32MixHeight = 100;
			
		s32Ret = HI_SVR_PLAYER_Create(&params,phPlayer);
		if (HI_SUCCESS != s32Ret)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Create error \n");
			return ROC_PORTING_PLAYER_FAILURE;
		}
	
		HI_SVR_PLAYER_RegCallback(*phPlayer, Media_Play_Notify);

	return ROC_PORTING_PLAYER_SUCCESS;
}




/************************************************************************************
 * 设置要播放媒体文件url地址
 * 
 * 参数:	
 *		@hPlayer	调用Roc_Player_Create返回的句柄
 *		@pPlayerSrcInfo	媒体文件信息，详见Roc_Player_Source_t定义
 * 说明:
 *		1) 
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS	    成功
 *		ROC_PORTING_PLAYER_FAILURE	    失败  
 *      ROC_PORTING_PLAYER_INVALID_PARAM   参数错误
 ************************************************************************************/
 Roc_Player_ErrCode_e rocme_porting_player_setsource(INT32_T hPlayer, Roc_Player_Source_t *pPlayerSrcInfo)
{
	ROCME_TEST_PRINT
	HI_S32 s32Ret = HI_SUCCESS;

	
	HI_SVR_PLAYER_MEDIA_S mediaparams;
	HI_U32 mediatype;
	
	memset(&mediaparams, 0, sizeof(mediaparams));
    	sprintf(mediaparams.aszUrl, "%s", pPlayerSrcInfo->aszSrcUrl);

	mediatype = (HI_U32)HI_SVR_PLAYER_MEDIA_STREAMFILE;

	s32Ret = HI_SVR_PLAYER_SetMedia(hPlayer,mediatype,&mediaparams);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_SetMedia error \n");
		return ROC_PORTING_PLAYER_FAILURE;
	}

	return ROC_PORTING_PLAYER_SUCCESS;
}



/************************************************************************************
 * 启动播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		开始播放媒体，只有当播放器包含有效的媒体资源时，才能执行
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_play(INT32_T hPlayer)
{
	ROCME_TEST_PRINT

	HI_S32 s32Ret = HI_SUCCESS;

	HI_UNF_SND_Detach(HI_UNF_SND_0, TDRV_GetAVHandle());
	HI_UNF_VO_SetWindowEnable(TDRV_GetWindonHandle(),HI_FALSE);
	HI_UNF_VO_DetachWindow(TDRV_GetWindonHandle(), TDRV_GetAVHandle());
	HI_UNF_AVPLAY_ChnClose(TDRV_GetAVHandle(), HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
	
	s32Ret = HI_SVR_PLAYER_Play(hPlayer);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Play error \n");
		return ROC_PORTING_PLAYER_FAILURE;
	}
	return ROC_PORTING_PLAYER_SUCCESS;
}



/************************************************************************************
 * 暂停播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		暂停媒体播放，当播放器处于播放状态时，调此接口进入暂停状态；当播放器处于其他状态时，调此接口出错。
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_pause(INT32_T hPlayer)
{
	ROCME_TEST_PRINT
	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = HI_SVR_PLAYER_Pause(hPlayer);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Pause error \n");
		return ROC_PORTING_PLAYER_FAILURE;
    	}
	return ROC_PORTING_PLAYER_SUCCESS;
}


/************************************************************************************
 * 播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		恢复媒体播放，当播放器处于暂停、快退、快进状态时，调此接口恢复播放；
 *      当播放器处于其他状态时，调此接口出错。
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_resume(INT32_T hPlayer)
{
	ROCME_TEST_PRINT

	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = HI_SVR_PLAYER_Resume(hPlayer);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Resume error \n");
		return ROC_PORTING_PLAYER_FAILURE;
    	}
	return ROC_PORTING_PLAYER_SUCCESS;

}




/************************************************************************************
 * 停止播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		停止媒体播放，当播放器处于播放状态时，调用此接口可以停止播放
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_stop(INT32_T hPlayer)
{
	ROCME_TEST_PRINT
	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = HI_SVR_PLAYER_Stop(hPlayer);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Stop error \n");
		return ROC_PORTING_PLAYER_FAILURE;
    	}
	return ROC_PORTING_PLAYER_SUCCESS;
}




/************************************************************************************
 * 跳到指定位置播放,在播放状态下，跳到指定位置播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 		@unTime     Seek的时间，单位为秒
 *		
 * 说明:
 *		
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_seek(INT32_T hPlayer, UINT32_T unTime)
{
	ROCME_TEST_PRINT
 	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = HI_SVR_PLAYER_Seek(hPlayer,unTime);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Stop error \n");
		return ROC_PORTING_PLAYER_FAILURE;
    	}
	return ROC_PORTING_PLAYER_SUCCESS;
}


/************************************************************************************
 * 设置快退快进
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 		@ePace      播放速率
 *		
 * 说明:
 *		
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_setpace(INT32_T hPlayer, Roc_Player_Pace_e ePace)
{
	ROCME_TEST_PRINT
 	HI_S32 s32Ret = HI_SUCCESS;
	HI_S32 nspeed;

	switch(ePace)
	{
		case ROC_PACE_1X_FORWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_NORMAL;
			break;
			
		case ROC_PACE_2X_FORWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_2X_FAST_FORWARD;
			break;

		case ROC_PACE_4X_FORWARD:	
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_4X_FAST_FORWARD;
			break;

		case ROC_PACE_8X_FORWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_8X_FAST_FORWARD;
			break;

		case ROC_PACE_16X_FORWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_16X_FAST_FORWARD;
			break;

		case ROC_PACE_32X_FORWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_FORWARD;
			break;

		case ROC_PACE_2X_BACKWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_2X_FAST_BACKWARD;
			break;

		case ROC_PACE_4X_BACKWARD:	
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_4X_FAST_BACKWARD;
			break;

		case ROC_PACE_8X_BACKWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_8X_FAST_BACKWARD;
			break;

		case ROC_PACE_16X_BACKWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_16X_FAST_BACKWARD;
			break;

		case ROC_PACE_32X_BACKWARD:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_BACKWARD;
			break;


		default:
			nspeed = HI_SVR_PLAYER_PLAY_SPEED_BUTT;
			break;
	}

	s32Ret = HI_SVR_PLAYER_TPlay(hPlayer,nspeed);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_TPlay error \n");
		return ROC_PORTING_PLAYER_FAILURE;
    	}
	return ROC_PORTING_PLAYER_SUCCESS;
}



/************************************************************************************
 * 获取媒体文件信息
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		@pMediaInfo	媒体文件信息指针
 *		
 * 说明:
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_get_media_info(INT32_T hPlayer, Roc_Player_Media_Info_t *pMediaInfo)
{
	ROCME_TEST_PRINT
 	HI_S32 s32Ret = HI_SUCCESS;
	HI_FORMAT_FILE_INFO_S npstruInfo;

	s32Ret = HI_SVR_PLAYER_GetFileInfo(hPlayer,&npstruInfo);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Stop error \n");
		return ROC_PORTING_PLAYER_FAILURE;
    }

	pMediaInfo->u32Bit_rate = npstruInfo.u32Bps;
	pMediaInfo->u32Duration = npstruInfo.s64Duration/1000;
	pMediaInfo->u32FileSize = npstruInfo.u32FileSize;
	return ROC_PORTING_PLAYER_SUCCESS;
}



/************************************************************************************
 * 获取播放器信息
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		@pMediaInfo	播放器信息指针，详见Roc_Player_Info_t定义
 *		
 * 说明:
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_get_info(INT32_T hPlayer, Roc_Player_Info_t *pPlayerInfo)
{
	ROCME_TEST_PRINT
	HI_S32 s32Ret = HI_SUCCESS;
	HI_SVR_PLAYER_INFO_S npstruInfo;

	s32Ret = HI_SVR_PLAYER_GetPlayerInfo(hPlayer,&npstruInfo);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_SVR_PLAYER_Stop error \n");
		return ROC_PORTING_PLAYER_FAILURE;
    }

	pPlayerInfo->unPlayeTime = npstruInfo.u64TimePlayed/1000;
	pPlayerInfo->unProgress = npstruInfo.u32Progress;
	return ROC_PORTING_PLAYER_SUCCESS;
}



/************************************************************************************
 * 销毁播放器实例
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		销毁播放器实例
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_destory(INT32_T hPlayer)
{
	ROCME_TEST_PRINT
	HI_S32 s32Ret = HI_SUCCESS;
	
	s32Ret = HI_SVR_PLAYER_Destroy(hPlayer);
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_SVR_PLAYER_Destroy(): ret is 0x%08x\n", s32Ret);
		return ROC_PORTING_PLAYER_FAILURE;
    }

	
	HI_UNF_AVPLAY_ChnOpen(TDRV_GetAVHandle(), HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
	HI_UNF_AVPLAY_ChnOpen(TDRV_GetAVHandle(), HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
	HI_UNF_VO_AttachWindow(TDRV_GetWindonHandle(), TDRV_GetAVHandle());
	HI_UNF_VO_SetWindowEnable(TDRV_GetWindonHandle(), HI_TRUE);
	
	HI_UNF_SND_Attach(HI_UNF_SND_0, TDRV_GetAVHandle(), HI_UNF_SND_MIX_TYPE_MASTER, 100);
#if 0
	HI_UNF_AVPLAY_ATTR_S  m_attrs;
	HI_UNF_AVPLAY_GetAttr(TDRV_GetAVHandle(),HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE,&m_attrs);
	m_attrs.stStreamAttr.enStreamType = HI_UNF_AVPLAY_STREAM_TYPE_TS;
	HI_UNF_AVPLAY_SetAttr(TDRV_GetAVHandle(),HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE,&m_attrs);
#endif
	return ROC_PORTING_PLAYER_SUCCESS;
}
