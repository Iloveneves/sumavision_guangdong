/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_media.cpp
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

#define ROC_NULL 0 

extern HI_HANDLE						g_hAvHandle; 
extern HI_HANDLE						g_hAoHandle; 
extern HI_HANDLE						g_hVoHandle; 
extern HI_HANDLE						g_hDispHandle;

static HI_HANDLE				hWindowHandle;
static HI_HANDLE				h_PlayerHandle;
static pthread_t hisi_player_thread_pid = -1;
static HI_U32 hisi_player_thread_status = HI_FALSE;
static Roc_Player_Event_Notify hisi_mplayer_callback = NULL;
static HI_U32 player_mp3_stream_status = HI_FALSE;

static int Play_Finish = 0;
static char playe_flag = 0;

HI_VOID       player_event_thread (HI_VOID *para);


/*****************************************************************************
����˵��: ��ʼ��mediaģ�����Դ
����˵��:
�������:
  
����:
    ʧ��: -1              
    �ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_media_init(void)
{
ROCME_TEST_PRINT
#if 0
	return ROC_OK;
#endif
}

/*****************************************************************************
����˵��: ����mediaģ�����Դ
����˵��:
�������:
  
����:
    ʧ��: -1              
    �ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_media_term(void)
{
ROCME_TEST_PRINT
#if 0
	if (HI_SVR_PLAYER_INVALID_HDL != g_hAvHandle)
    {
        /* HiPlayer -> dvb�����¿�������Ƶͨ�� */
       DOFUNC_RETURN(HI_UNF_AVPLAY_ChnOpen(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL));
       DOFUNC_RETURN(HI_UNF_AVPLAY_ChnOpen(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL));
    }

	return ROC_OK;
#endif
}


/*****************************************************************************
����˵��: ��ý�岥���� 
����˵��:
�������:
    [des] ���������ƣ��ַ��� "WAV"��"MP3"
    [cbk] �������¼��ص�����������ΪNULL
  
����:
    ʧ��: -1              
    �ɹ�: ���������
*****************************************************************************/
UINT32_T rocme_porting_media_open(const CHAR_T *des, Roc_Player_Event_Notify cbk)
{
ROCME_TEST_PRINT
#if 0
	g_hAvHandle	= HI_SVR_PLAYER_INVALID_HDL;
	s_stParam.hAVPlayer = g_hAvHandle;
    HI_S32 s32Ret = HI_SVR_PLAYER_Create(&s_stParam, &h_PlayerHandle);

    if (HI_SUCCESS != s32Ret)
    {
        printf("ERR: player open fail, ret = 0x%x \n", s32Ret);
       return ROC_ERR;
    }


   hisi_player_thread_status = HI_TRUE;

   HI_S32 ret = pthread_create( &hisi_player_thread_pid, NULL, (void*)player_event_thread, NULL);
    if (0 != ret)
    {
    	playe_flag	= 0;
        hisi_player_thread_status = HI_FALSE;

		return ROC_ERR;
    }
	
	hisi_mplayer_callback = cbk;

	return h_PlayerHandle;
#endif
}


/*****************************************************************************
����˵��: �ر�ý�岥���� 
����˵��:
�������:
    [player] ���������

����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_media_close(UINT32_T player)
{
ROCME_TEST_PRINT
#if 0
	DOFUNC_RETURN(HI_SVR_PLAYER_Destroy(player));
	DOFUNC_RETURN(HI_SVR_PLAYER_Deinit());

	playe_flag = 0;
    hisi_player_thread_status = HI_FALSE;
	pthread_cancel((pthread_t)hisi_player_thread_pid);

    hisi_player_thread_pid = -1;
	return ROC_OK;
#endif
}


/*****************************************************************************
����˵��: ����ý���ļ� 
����˵��:
�������:
    [player] ���������
    [mrl   ] Ҫ���ŵ�ý���ļ��������ṹ��MEDIA_FILE_t
    [des   ] ����������, "MP3" or "WAV"
����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_media_play(UINT32_T player,const CHAR_T *mrl,const CHAR_T *des)
{
ROCME_TEST_PRINT
#if 0
	HI_SVR_PLAYER_MEDIA_S stMedia;
	
	if(player == ROC_NULL || des == NULL)
	{
		return ROC_ERR;
	}
	
	memset(&stMedia, 0, sizeof(stMedia));
	sprintf(stMedia.aszUrl, "%s", des);

	DOFUNC_RETURN(HI_SVR_PLAYER_SetMedia(player, HI_SVR_PLAYER_MEDIA_STREAMFILE, &stMedia));

	DOFUNC_RETURN(HI_SVR_PLAYER_Play(player));
	
	playe_flag = 1;
	return ROC_OK;
#endif
}


/*****************************************************************************
����˵��: ���²���ý��
����˵��:
�������:
    [player] ���������
����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_media_replay(UINT32_T player)
{
ROCME_TEST_PRINT
#if 0
	if(ROC_NULL == player)
	{
		return ROC_ERR;
	}

	DOFUNC_RETURN( HI_SVR_PLAYER_Play(player));

	return ROC_OK;
#endif
}


/*****************************************************************************
����˵��: ֹͣý���ļ��Ĳ���
����˵��:
�������:
    [player] ���������

����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_media_stop(UINT32_T player)
{
ROCME_TEST_PRINT
#if 0
	if(ROC_NULL == player)
	{
		return ROC_ERR;
	}

	DOFUNC_RETURN( HI_SVR_PLAYER_Stop(player));

	return ROC_OK;
#endif
}


/*****************************************************************************
����˵��: ��ͣý���ļ��Ĳ���
����˵��:
�������:
    [player] ���������

����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_media_pause(UINT32_T player)
{
ROCME_TEST_PRINT
#if 0
	if(ROC_NULL == player)
	{
		return ROC_ERR;
	}

	DOFUNC_RETURN( HI_SVR_PLAYER_Pause(player));

	return ROC_OK;
#endif
}


/*****************************************************************************
����˵��: �ָ�ý���ļ��Ĳ���
����˵��:
�������:
    [player] ���������

����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_media_resume(UINT32_T player)
{
ROCME_TEST_PRINT
#if 0
	if(ROC_NULL == player)
	{
		return ROC_ERR;
	}

	DOFUNC_RETURN( HI_SVR_PLAYER_Resume(player));

	return ROC_OK;
#endif 
}


/*****************************************************************************
����˵��: ������ź���
����˵����
���������
    [player] ���������
    [  rate] ����ı���

����:
    �ɹ�:  0
    ʧ��: -1
*****************************************************************************/
INT32_T rocme_porting_media_forward_rate(UINT32_T player,INT32_T rate)
{
ROCME_TEST_PRINT
#if 0
	if(rate > HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_FORWARD || rate < HI_SVR_PLAYER_PLAY_SPEED_2X_FAST_FORWARD)
	{
		printf("beyond the play speed\n");

		return ROC_ERR;
	}

	DOFUNC_RETURN(HI_SVR_PLAYER_TPlay(player, rate));
#endif
}


/*****************************************************************************
����˵��: ���˲��ź���
����˵����
���������
    [player] ���������
    [  rate] ���˵ı���

����:
    �ɹ�:  0
    ʧ��: -1
*****************************************************************************/
INT32_T rocme_porting_media_rewind_rate(UINT32_T player, INT32_T rate)
{
ROCME_TEST_PRINT
#if 0
	if(rate > HI_SVR_PLAYER_PLAY_SPEED_2X_FAST_BACKWARD || rate < HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_BACKWARD)
	{
		printf("beyond the play speed\n");

		return ROC_ERR;
	}

	DOFUNC_RETURN(HI_SVR_PLAYER_TPlay(player, rate));

	return ROC_OK;
#endif
}



/*****************************************************************************
����˵��: ���������ƺ���
����˵����
    ���������
        [player] ���������
        [    op] �������ͣ����Roc_Media_Player_IOCtl_e
        [ param] ���صĿ�����Ϣ

����:
    �ɹ�:  0
    ʧ��: -1
*****************************************************************************/
INT32_T rocme_porting_media_ioctl(UINT32_T player, Roc_Media_Player_IOCtl_e op, void *param)
{
ROCME_TEST_PRINT
#if 0
	if(player == ROC_NULL || op > ROC_MEDIA_GET_TRANS_NET|| op < ROC_MEDIA_GET_DURATION)
	{
		return ROC_ERR;
	}

	HI_SVR_PLAYER_INFO_S pstruInfo;
	HI_FORMAT_FILE_INFO_S stFileInfo;

	
	memset(&stFileInfo, 0, sizeof(stFileInfo));

	DOFUNC_RETURN(HI_SVR_PLAYER_GetFileInfo(player, &stFileInfo));

	DOFUNC_RETURN(HI_SVR_PLAYER_GetPlayerInfo(player, &pstruInfo));

	switch(op)
	{
	case ROC_MEDIA_GET_DURATION:
		param = stFileInfo.s64Duration;
		break;
		
	case ROC_MEDIA_GET_STATUS: 

		if(Play_Finish)
		{
			param = ROC_MEDIA_FINISH;
			break;
		}
		switch(pstruInfo.eStatus)
		{
			case HI_SVR_PLAYER_STATE_PLAY:
				param = ROC_MEDIA_RUNNING;
				break;
		    case HI_SVR_PLAYER_STATE_FORWARD:
				param = ROC_MEDIA_FORWARD;
				break;
		    case HI_SVR_PLAYER_STATE_BACKWARD:
				param = ROC_MEDIA_REWIND;
				break;
			case HI_SVR_PLAYER_STATE_PAUSE:
				param = ROC_MEDIA_PAUSED;
				break;
		    case HI_SVR_PLAYER_STATE_STOP: 
				param = ROC_MEDIA_STOPPED;
				break;

				default:
					param = ROC_MEDIA_SLOW;
					break;
		}
		break;
		
	case ROC_MEDIA_GET_RATE:
		param	= pstruInfo.s32Speed;
		break;
		
	case ROC_MEDIA_GET_POSITION:
		param	= pstruInfo.u32Progress * stFileInfo.s64Duration;
		break;
		
	case ROC_MEDIA_GET_STARTTIME:
		param = stFileInfo.s64StartTime;
		break;
	case ROC_MEDIA_GET_ENDTIIME:
		param = stFileInfo.s64StartTime + stFileInfo.s64Duration;
		break;
	case ROC_MEDIA_GET_TRANS_NET:
		param = stFileInfo.u32Bps;
		break;

		default:

			return ROC_ERR;
			break;
	}

	return ROC_OK;
#endif
}


/*****************************************************************************
����˵��: ���ò��������ڵ�λ�úʹ�С
����˵��:
�������:
    [  x,y] ���ڵ�����λ��
    [width] ���ڵĿ��
    [ high] ���ڵĸ߶�
����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_media_set_window(INT32_T x , INT32_T y, UINT32_T width, UINT32_T high)
{
ROCME_TEST_PRINT
#if 0
	HI_UNF_WINDOW_ATTR_S stWinAttr;

	stWinAttr.enVo = HI_UNF_VO_HD0;
    stWinAttr.bVirtual = HI_FALSE;
    stWinAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_4TO3;
    stWinAttr.enAspectCvrs  = HI_UNF_ASPECT_CVRS_IGNORE;
    stWinAttr.stInputRect.s32X = x;
    stWinAttr.stInputRect.s32Y = y;
    stWinAttr.stInputRect.s32Width  = 1920;
    stWinAttr.stInputRect.s32Height = 1080;
    stWinAttr.stOutputRect.s32X = x;
    stWinAttr.stOutputRect.s32Y = y;
    stWinAttr.stOutputRect.s32Width  = 1920;
    stWinAttr.stOutputRect.s32Height = 1080;

    DOFUNC_RETURN( HI_UNF_VO_CreateWindow(&stWinAttr, &hWindowHandle));
	DOFUNC_RETURN(HI_UNF_VO_SetWindowEnable(hWindowHandle, HI_TRUE));
	return ROC_OK;
#endif
}


/*****************************************************************************
����˵��: ��ָ����ʱ��㲥��ý���ļ�����λΪ��
����˵��:
�������:
    [player] ���������
    [time  ] Ҫ���ŵ�ʱ��㣬��λΪ��
����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_media_seekplay(UINT32_T player ,INT32_T Time)
{
ROCME_TEST_PRINT
#if 0
	if(ROC_NULL == player)
	{
		return ROC_ERR;
	}

	DOFUNC_RETURN( HI_SVR_PLAYER_Seek(player, Time*1000));

	return ROC_OK;
#endif
}


HI_VOID player_event_thread (HI_VOID *para)
{
ROCME_TEST_PRINT
#if 0
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32Total, u32Cur;

    while (hisi_player_thread_status == HI_TRUE)
    {
        usleep(500000);   /*sleep*/

		if(playe_flag)
		{

			ret |= HI_Player_GetCurrentTime(&u32Cur);
			if (HI_SUCCESS != ret)
			{
				printf("HI_Player_GetDuration & HI_Player_GetCurrentTime ErrorCode: 0x%08x\n", ret);
                if (hisi_mplayer_callback)
                {
                    (*hisi_mplayer_callback)(MPLAYER_EVENT_ERROR, 0, 0, 0);
                }
                continue;
            }

            if ((u32Cur == u32Total) && (hisi_mplayer_callback))
            {
                (*hisi_mplayer_callback)(MPLAYER_EVENT_EOF, 0, 0, 0);
            }
		}
	}
#endif
}

#ifdef __cplusplus
}
#endif