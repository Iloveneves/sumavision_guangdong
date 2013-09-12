/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_player.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
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
 * ��ʼ��������ģ��
 * 
 * ����:	
 *		None
 *		
 * ˵��: 
 *		��ʼ��������ģ�飬���м������ʱ���ã����:
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
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
 * ȥ��ʼ��������ģ��
 * 
 * ����:	
 *		None
 *		
 * ˵��:
 *		�ͷų�ʼ��ʱ��������Դ
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
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
 * ����һ��������ʵ��
 * 
 * ����:	
 *		@pPlayerParam	����������ʵ���Ĳ���
 *		@phPlayer	�û��ṩָ�룬�ӿڵ��óɹ����ز�����ʵ����������򷵻�NULL
 *		
 * ˵��:
 *		1) 
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS	    �ɹ�
 *		ROC_PORTING_PLAYER_FAILURE	    ʧ��  
 *      ROC_PORTING_PLAYER_INVALID_PARAM   ��������
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
 * ����Ҫ����ý���ļ�url��ַ
 * 
 * ����:	
 *		@hPlayer	����Roc_Player_Create���صľ��
 *		@pPlayerSrcInfo	ý���ļ���Ϣ�����Roc_Player_Source_t����
 * ˵��:
 *		1) 
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS	    �ɹ�
 *		ROC_PORTING_PLAYER_FAILURE	    ʧ��  
 *      ROC_PORTING_PLAYER_INVALID_PARAM   ��������
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
 * ��������
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		��ʼ����ý�壬ֻ�е�������������Ч��ý����Դʱ������ִ��
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
 * ��ͣ����
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		��ͣý�岥�ţ������������ڲ���״̬ʱ�����˽ӿڽ�����ͣ״̬������������������״̬ʱ�����˽ӿڳ���
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
 * ����
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		�ָ�ý�岥�ţ���������������ͣ�����ˡ����״̬ʱ�����˽ӿڻָ����ţ�
 *      ����������������״̬ʱ�����˽ӿڳ���
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
 * ֹͣ����
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		ֹͣý�岥�ţ������������ڲ���״̬ʱ�����ô˽ӿڿ���ֹͣ����
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
 * ����ָ��λ�ò���,�ڲ���״̬�£�����ָ��λ�ò���
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 		@unTime     Seek��ʱ�䣬��λΪ��
 *		
 * ˵��:
 *		
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
 * ���ÿ��˿��
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 		@ePace      ��������
 *		
 * ˵��:
 *		
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
 * ��ȡý���ļ���Ϣ
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		@pMediaInfo	ý���ļ���Ϣָ��
 *		
 * ˵��:
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
 * ��ȡ��������Ϣ
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		@pMediaInfo	��������Ϣָ�룬���Roc_Player_Info_t����
 *		
 * ˵��:
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
 * ���ٲ�����ʵ��
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		���ٲ�����ʵ��
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
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
