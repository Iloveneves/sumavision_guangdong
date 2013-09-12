/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_mediaplayer.cpp
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
 * ��ʼ��ƽ̨ý�������ģ��
 * 
 * ����:	
 *		��
 *		
 * ˵��:
 *		��
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_init(void)
{
}

/************************************************************************************
 * ����ƽ̨ý�������ģ��
 * 
 * ����:	
 *		��
 *		
 * ˵��:
 *		��
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_term(void)
{
}

INT32_T rocme_porting_media2_codec(UINT32_T *CodecMask)
{
}

/************************************************************************************
 * ��ƽ̨��һ��Ӳ��ý�������
 * 
 * ����:	
 *		@MediaHandle: ����ƽ̨���������, ��ƽ̨�������Ĳ������ڴ˾��
 *		@OpenParams
 *           .StreamType: ROC_MEDIA_STREAM_VIDEO	-��ȡ��Ƶ������
 *                        ROC_MEDIA_STREAM_AUDIO	-��ȡ��Ƶ������,
 *                        ROC_MEDIA_STREAM_TS	    -��ȡTS��������
 *                         
 *           .CodecType:  ���������ı����ʽ, �μ�Roc_Media_Stream_t����
 *           
 *           .BufferHandler: ��������������λ������������Ķ���
 *
 *           .GetWriteAddress_p: ƽ̨������ͨ���˺����ӿڻ�ȡλ�������дָ��
 *
 *           .InformReadAddress_p: ƽ̨������ͨ���˺����ӿ�֪ͨӦ�ø���λ������Ķ�ָ��
 *             
 *           .BitBufferAddr: ����λ������Ļ���ַ
 *
 *           .BitBufferSize: ����λ������Ĵ�С
 *		
 * ˵��:
 *		
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_open(UINT32_T *MediaHandle,
								  Roc_Media_OpenParams_t *OpenParams,
								  void **BitBufferBase,
								  UINT32_T *BitBufferSize)
{
	return ROC_OK;
}

/************************************************************************************
 * �ر�ƽ̨������
 * 
 * ����:	
 *		@MediaHandle	ƽ̨������������
 *		
 * ˵��:
 *
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_close(UINT32_T MediaHandle)
{
}

/************************************************************************************
 * ����ƽ̨�Ľ�������ʼ����
 * 
 * ����:	
 *		@MediaHandle			ƽ̨������������
 *		
 * ˵��:
 *		���ô˽ӿڿ�ʼƽ̨�������Ľ���
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_start(UINT32_T MediaHandle)
{
}

/************************************************************************************
 * ֹͣƽ̨�������Ľ���
 * 
 * ����:	
 *		@MediaHandle: ���������
 *		
 * ˵��:
 *		None
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_stop(UINT32_T MediaHandle)
{
	HI_UNF_AVPLAY_STOP_OPT_S strStopOpt;	
	
	/*�������һ֡*/
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