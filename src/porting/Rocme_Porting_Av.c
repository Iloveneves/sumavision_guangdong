/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_Av.c
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/mman.h>
	
	//#include <asm/io.h>
#include <linux/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
	
#include "hi_unf_avplay.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_sound.h"
#include "hi_go_gdev.h"
#include "hi_unf_so.h"
	
	
#include "hi_unf_hdmi.h"
	
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.AAC.encode.h"
#include "HA.AUDIO.AC3.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"	
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.DTS.decode.h"
#include "HA.AUDIO.EAC3.decode.h"
#include "HA.AUDIO.G711.codec.h"
#include "HA.AUDIO.G722.codec.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.PCM.decode.h"	
#include "HA.AUDIO.TRUEHD.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"


#include "porter_rocme.h"


static HI_BOOL					g_bAVInitialed = HI_FALSE;	


HI_HANDLE						g_hAvHandle; 
HI_HANDLE						g_hAoHandle; 
HI_HANDLE						g_hVoHandle; 
HI_HANDLE						g_hDispHandle;

HI_HANDLE						g_VideoDesHandle;
HI_HANDLE						g_AudioDesHandle;


//for hisi3716m about av: add by yj^^
HI_UNF_DISP_E					g_DispE = HI_UNF_DISP_HD0;
HI_UNF_VO_E						g_VoE = HI_UNF_VO_HD0;
HI_HANDLE						g_hWindowHandle; 

HI_U32 g_AudioInputType   = HI_UNF_SND_INTERFACE_I2S;//HI_UNF_SND_INTERFACE_I2S;//HI_UNF_SND_INTERFACE_I2S;//HI_UNF_SND_INTERFACE_SPDIF;
HI_U32 g_AudioFreq        = HI_UNF_SAMPLE_RATE_48K;

HI_UNF_AVPLAY_I_FRAME_S g_stIframe;


static HI_U32 	g_AudioType = HA_AUDIO_ID_MP3;
static HI_UNF_VCODEC_TYPE_E 	g_VideoType = HI_UNF_VCODEC_TYPE_MPEG2;



typedef struct hiHDMI_ARGS_S
{
    HI_UNF_HDMI_ID_E  enHdmi;
    HI_UNF_ENC_FMT_E  enWantFmt;
    HI_UNF_SAMPLE_RATE_E AudioFreq;
    HI_U32            AduioBitPerSample;
    HI_U32            AudioChannelNum;
    HI_UNF_SND_INTERFACE_E AudioInputType;
    HI_U32            ForceHDMIFlag;
}HDMI_ARGS_S;
static HDMI_ARGS_S g_stHdmiArgs;


#define SYS_PINSHARED_ADDR			(0x10203000)
#define	MUTECTL_PINSHARED_OFFSET	(0x00000158)
#define MUTECTL_MASK				(0x00000003)
#define MUTECTL_BITS				(0x00000003)
#define MUTECTL_GPIO_NUM			(8 * 12 + 5)


extern HI_HANDLE Get_Osd_Handle();

 static Roc_AV_Evt_Param_t s_stAvEvtPara[HI_UNF_AVPLAY_EVENT_BUTT] = {0};

 HI_S32 Rocme_Av_event_Notify(HI_HANDLE hAvplay, HI_UNF_AVPLAY_EVENT_E enEvent, HI_U32 u32Para)
 {

		HI_S32 s32Ret = HI_FAILURE;
		if (HI_NULL != s_stAvEvtPara[enEvent].callback)
		{
			s32Ret = s_stAvEvtPara[enEvent].callback(s_stAvEvtPara[enEvent].channel_index, 
				(void *)s_stAvEvtPara[enEvent].cb_param, 
				s_stAvEvtPara[enEvent].av_event, (UINT32_T)enEvent);
			if (HI_SUCCESS != s32Ret)
			{
				ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_av_event_callback failed s32Ret = %d\n", s32Ret);
			}
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"event not registered, enHiEvent = %d\n", enEvent);
		}
	
		return s32Ret;

 }


/***********************************************************************
func
****************************************************************************/
HI_HANDLE TDRV_GetAVHandle(void)
{
	return g_hAvHandle;
}

HI_HANDLE TDRV_GetWindonHandle(void)
{
	return g_hWindowHandle;
}

ROC_BOOL TDRV_Set_Video_type( Roc_Video_Type_e bVideoType )
{
ROCME_TEST_PRINT
	switch( bVideoType )
	{
	case ROC_VIDEO_TYPE_MPEG:
	case ROC_VIDEO_TYPE_MPEG2:
		g_VideoType = HI_UNF_VCODEC_TYPE_MPEG2;
		break;

	case ROC_VIDEO_TYPE_H264:
		g_VideoType = HI_UNF_VCODEC_TYPE_H264;
		break;

	case ROC_VIDEO_TYPE_MPEG4:
		g_VideoType = HI_UNF_VCODEC_TYPE_MPEG4;
		break;

	case ROC_VIDEO_TYPE_VC1:
		g_VideoType = HI_UNF_VCODEC_TYPE_VC1;
		break;

	case ROC_VIDEO_TYPE_AVS:
		g_VideoType = HI_UNF_VCODEC_TYPE_AVS;
		break;

	default:
		g_VideoType = HI_UNF_VCODEC_TYPE_MPEG2;
		break;
	}

	return ROC_OK;
}


/***********************************************************************
func
****************************************************************************/

ROC_BOOL TDRV_Set_Audio_type( Roc_Audio_Type_e bAudioType )
{
ROCME_TEST_PRINT
	switch( bAudioType )
	{
	case ROC_AUDIO_TYPE_MLP:
	case ROC_AUDIO_TYPE_MP3:
		g_AudioType = HA_AUDIO_ID_MP3;
		break;

	case ROC_AUDIO_TYPE_MPEG_AAC:
		g_AudioType = HA_AUDIO_ID_AAC;
		break;

	case ROC_AUDIO_TYPE_AC3:
		g_AudioType = HA_AUDIO_ID_AC3;
		break;

	case ROC_AUDIO_TYPE_MPEG1:
	case ROC_AUDIO_TYPE_MPEG2:
		g_AudioType = HA_AUDIO_ID_MP2;
		break;
		
	case ROC_AUDIO_TYPE_PCM:
		g_AudioType = HA_AUDIO_ID_PCM;
		break;

	default:
		g_AudioType = HA_AUDIO_ID_MP2;
		break;
	}

	return ROC_OK;
}

/***********************************************************************
func
****************************************************************************/
HI_S32 SetReg32Val(HI_U32 u32Base, HI_U32 u32Offset, HI_U32 u32ANDVal, HI_U32 u32ORVal)
{
ROCME_TEST_PRINT
    HI_S32 s32MapFd = -1;
    HI_U32 *pu32TmpAddr = NULL;
    HI_U32 u32TmpVal;
	
    s32MapFd = open("/dev/mem", O_RDWR | O_SYNC);
    if (-1 == s32MapFd)
    {
        return HI_FAILURE;
    }
	
    pu32TmpAddr = (HI_U32 *)mmap((void *)0, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, s32MapFd, u32Base);
    if (MAP_FAILED == pu32TmpAddr)
    {
        close(s32MapFd);
        return HI_FAILURE;
    }
	
    u32TmpVal  = *(pu32TmpAddr + (u32Offset >> 2));
    u32TmpVal &= u32ANDVal;
    u32TmpVal |= u32ORVal;
    *(pu32TmpAddr + (u32Offset >> 2)) = u32TmpVal;
	
    munmap((HI_VOID *)pu32TmpAddr, 0x1000);
    close(s32MapFd);
	
    return HI_SUCCESS;
}


/***********************************************************************
func
****************************************************************************/

ROC_BOOL TDRV_GPIO_AudioMute(ROC_BOOL bMute)
{
ROCME_TEST_PRINT
    SetReg32Val(SYS_PINSHARED_ADDR, MUTECTL_PINSHARED_OFFSET, ~MUTECTL_MASK, MUTECTL_BITS);
    HI_UNF_GPIO_Open();
    HI_UNF_GPIO_SetDirBit(MUTECTL_GPIO_NUM, ROC_FALSE);
	if( bMute )
	{
		HI_UNF_GPIO_WriteBit(MUTECTL_GPIO_NUM, ROC_TRUE);
    }
	else
	{
		HI_UNF_GPIO_WriteBit(MUTECTL_GPIO_NUM, ROC_FALSE);
	}
	HI_UNF_GPIO_Close();

	return ROC_TRUE;
}

/***********************************************************************
func
****************************************************************************/

HI_VOID HDMI_Event_Proc(HI_UNF_HDMI_EVENT_TYPE_E event, HI_VOID *pPrivateData)
{
ROCME_TEST_PRINT
	switch(event)
	{
	case HI_UNF_HDMI_EVENT_HOTPLUG:
		break;

	case HI_UNF_HDMI_EVENT_NO_PLUG:
		break;

	case HI_UNF_HDMI_EVENT_EDID_FAIL:
		break;

	case HI_UNF_HDMI_EVENT_HDCP_FAIL:
		break;

	case HI_UNF_HDMI_EVENT_HDCP_SUCCESS:
		break;

	default:
		break;
	}
	//Private Usage
}

/***********************************************************************
func
****************************************************************************/

HI_S32 HIADP_HDMI_SetAdecAttr(HI_UNF_SND_INTERFACE_E enInterface, HI_UNF_SAMPLE_RATE_E enRate)
{
ROCME_TEST_PRINT
    if (enRate)
    {
        g_AudioFreq = enRate;
    }
	
    if (enInterface)
    {
        g_AudioInputType = enInterface;
    }
    return 0;
}

/***********************************************************************
func
****************************************************************************/

HI_S32 HIADP_AVPlay_SetAdecAttr(HI_HANDLE hAvplay, HI_U32 enADecType, HI_HA_DECODEMODE_E enMode, HI_S32 isCoreOnly)
{
ROCME_TEST_PRINT
    HI_UNF_ACODEC_ATTR_S AdecAttr;
    DTS_DECODE_PORFILE stDTSProfile;
    WAV_FORMAT_S stWavFormat;

    DOFUNC_RETURN(HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &AdecAttr));
    AdecAttr.enType = enADecType;

    if (HA_AUDIO_ID_PCM == AdecAttr.enType)
    {
        HI_BOOL isBigEndian;
        /* set pcm wav format here base on pcm file */
        stWavFormat.nChannels = 1;
        stWavFormat.nSamplesPerSec = 48000;
        stWavFormat.wBitsPerSample = 16;
        /* if big-endian pcm */
        isBigEndian = HI_FALSE;
        if(HI_TRUE == isBigEndian)
        {
        	stWavFormat.cbSize =4;
        	stWavFormat.cbExtWord[0] = 1;
        }
        HA_PCM_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam),&stWavFormat);
    }
#if 0    
    else if (HA_AUDIO_ID_G711 == AdecAttr.enType)
    {
         HA_G711_GetDecDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
#endif    
    else if (HA_AUDIO_ID_MP2 == AdecAttr.enType)
    {
    	 HA_MP2_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
    else if (HA_AUDIO_ID_AAC == AdecAttr.enType)
    {
    	 HA_AAC_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
    else if (HA_AUDIO_ID_MP3 == AdecAttr.enType)
    {
    	 HA_MP3_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
//     else if (HA_AUDIO_ID_AMRNB== AdecAttr.enType)
//     {
//         AMRNB_DECODE_OPENCONFIG_S *pstConfig = (AMRNB_DECODE_OPENCONFIG_S *)u8DecOpenBuf;        
//         HA_AMRNB_GetDecDefalutOpenParam(&(AdecAttr.stDecodeParam), pstConfig);
//         pstConfig->enFormat = AMRNB_MIME;
//     }
    else if (HA_AUDIO_ID_AC3 == AdecAttr.enType)
    {
        HA_AC3_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
        AdecAttr.stDecodeParam.enDecMode = enMode;
        if (HD_DEC_MODE_THRU == enMode)
        {
		 	HIADP_HDMI_SetAdecAttr(HI_UNF_SND_INTERFACE_SPDIF, HI_UNF_SAMPLE_RATE_UNKNOWN);
        }
    }
    else if (HA_AUDIO_ID_EAC3 == AdecAttr.enType)
    {
        HA_EAC3_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
        if (HD_DEC_MODE_THRU != enMode)
        {
            return -1;
        }

        AdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_THRU;/* eac3 just support pass-through */
        HI_UNF_SND_SetSampleRate(HI_UNF_SND_0, HI_UNF_SAMPLE_RATE_192K);        
	    HIADP_HDMI_SetAdecAttr(HI_UNF_SND_INTERFACE_SPDIF, HI_UNF_SAMPLE_RATE_192K);
    }
    else if (HA_AUDIO_ID_TRUEHD == AdecAttr.enType)
    {
        HA_TRUEHD_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
        if (HD_DEC_MODE_THRU != enMode)
        {
            return -1;
        }

        AdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_THRU;        /* truehd just support pass-through */
        HIADP_HDMI_SetAdecAttr(HI_UNF_SND_INTERFACE_HBR, HI_UNF_SAMPLE_RATE_192K);
        HI_UNF_SND_SetSampleRate(HI_UNF_SND_0, HI_UNF_SAMPLE_RATE_192K); 
    }
    else if (HA_AUDIO_ID_DTS == AdecAttr.enType)
    {
        stDTSProfile.isCoreOnlyDecode = isCoreOnly;  /* you can set isCoreOnlyDecode=1 to decode dts core data at dts hd stream */
        HA_DTS_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam), &stDTSProfile);
        if (stDTSProfile.isCoreOnlyDecode)
        {
            AdecAttr.stDecodeParam.enDecMode = enMode;
            if (HD_DEC_MODE_THRU == enMode)
            {
		        HIADP_HDMI_SetAdecAttr(HI_UNF_SND_INTERFACE_SPDIF,HI_UNF_SAMPLE_RATE_UNKNOWN);
            }

        }
        else
        {
            if (HD_DEC_MODE_THRU != enMode)
            {
                return -1;
            }

            AdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_THRU;        /* dsthd just support pass-through */
	        HIADP_HDMI_SetAdecAttr(HI_UNF_SND_INTERFACE_HBR, HI_UNF_SAMPLE_RATE_192K);
            HI_UNF_SND_SetSampleRate(HI_UNF_SND_0, HI_UNF_SAMPLE_RATE_192K); 
        }
    }
    else
    {
	     HA_DRA_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }

    DOFUNC_RETURN(HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &AdecAttr));

    return HI_SUCCESS;
}

/**************************************************************************
��������: 
            rocme_porting_av_init
����˵��: 
            ����Ƶ�����ʼ�����м����������ʱ���ô˺��������������м��֮ǰ
        �������Ѿ�����������Ƶ�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            void
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʼ���ɹ� )
    ʧ�� : -1 �� ������ ( ��ʼ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_init(void)
{
ROCME_TEST_PRINT

	HI_UNF_AVPLAY_ATTR_S	stAttr;
	
	HI_UNF_SYNC_ATTR_S stSyncAttr;
	HI_UNF_DISP_INTERFACE_S stInterface;
	HI_UNF_WINDOW_ATTR_S stWinAttr;
	HI_UNF_DISP_BG_COLOR_S		BgColor;
	HI_UNF_DISP_INTERFACE_S 	DacMode;
	HI_UNF_HDMI_INIT_PARA_S   stHdmiInitParam;
	HI_UNF_AVPLAY_OPEN_OPT_S maxCapbility;
	HI_RECT_S stRect;

	HI_S32					Ret = HI_FAILURE;
	HI_UNF_SND_INTERFACE_S		SndIntf;

	HI_U32 u32Width, u32Height;
	HI_UNF_ENC_FMT_E   eEncFmt = HI_UNF_ENC_FMT_1080i_50;
  

	if(g_bAVInitialed == HI_TRUE)
	{
		return ROC_OK;			
	}



	maxCapbility.enCapLevel= HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
	maxCapbility.enDecType= HI_UNF_VCODEC_DEC_TYPE_NORMAL;
	maxCapbility.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;
	//---------------------------------------------------------------sound init
	Ret = HI_UNF_SND_Init();
	if (Ret != HI_SUCCESS)
	{
		return Ret;
	}
	
	Ret = HI_UNF_SND_Open(HI_UNF_SND_0);
	if (Ret != HI_SUCCESS)
	{
		return Ret;
	}
	
	SndIntf.enInterface = HI_UNF_SND_INTERFACE_I2S;
	SndIntf.bEnable = HI_TRUE;
	Ret = HI_UNF_SND_SetInterface(HI_UNF_SND_0, &SndIntf);
	if (Ret != HI_SUCCESS )
	{
		HI_UNF_SND_Close(HI_UNF_SND_0);
		HI_UNF_SND_DeInit();
		return Ret;
	}
	
	SndIntf.enInterface = HI_UNF_SND_INTERFACE_SPDIF;
	SndIntf.bEnable = HI_TRUE;
	Ret = HI_UNF_SND_SetInterface(HI_UNF_SND_0, &SndIntf);
	if (Ret != HI_SUCCESS )
	{
		HI_UNF_SND_Close(HI_UNF_SND_0);
		HI_UNF_SND_DeInit();
		return Ret;
	}
	
	//--------------------------------------------disp init 
#if 0
		Ret = HI_UNF_DISP_Init();
		if (Ret != HI_SUCCESS)
		{
			return Ret;
		}
	
		BgColor.u8Red = 0;
		BgColor.u8Green =0;
		BgColor.u8Blue =0;
		HI_UNF_DISP_SetBgColor(HI_UNF_DISP_HD0, &BgColor);
		HI_UNF_DISP_SetIntfType(HI_UNF_DISP_HD0, HI_UNF_DISP_INTF_TYPE_TV);
		HI_UNF_DISP_SetFormat(HI_UNF_DISP_HD0, eEncFmt);  

	
		DacMode.bScartEnable = HI_FALSE;
		DacMode.bBt1120Enable = HI_FALSE;
		DacMode.bBt656Enable = HI_FALSE;
	
	//��sample\common\hi_adp_mpi.c�е�����һ��,�ܹ��������
		DacMode.enDacMode[0] = HI_UNF_DISP_DAC_MODE_HD_Y;
		DacMode.enDacMode[1] = HI_UNF_DISP_DAC_MODE_HD_PR;
		DacMode.enDacMode[2] = HI_UNF_DISP_DAC_MODE_HD_PB;
		DacMode.enDacMode[3] = HI_UNF_DISP_DAC_MODE_SILENCE;
		DacMode.enDacMode[4] = HI_UNF_DISP_DAC_MODE_SILENCE;
		DacMode.enDacMode[5] = HI_UNF_DISP_DAC_MODE_CVBS;  //Ϊ�˽��͹���3·CVBSֻ��һ·��
		HI_UNF_DISP_SetDacMode(&DacMode);
		
		Ret = HI_UNF_DISP_Attach(HI_UNF_DISP_SD0, HI_UNF_DISP_HD0);
		if (Ret != HI_SUCCESS)
		{
			HI_UNF_DISP_DeInit();
			return Ret;
		}
		
		Ret = HI_UNF_DISP_Open(HI_UNF_DISP_HD0);
		if (Ret != HI_SUCCESS)
		{
			HI_UNF_DISP_DeInit();
			return Ret;
		}
		
		Ret = HI_UNF_DISP_Open(HI_UNF_DISP_SD0);
		if (Ret != HI_SUCCESS)
		{
			HI_UNF_DISP_Close(HI_UNF_DISP_HD0);
			HI_UNF_DISP_DeInit();
			return Ret;
		}

#endif

	//---------------------------------------------------Hdmi init
	HI_SYS_WriteRegister(0x10203014, 0x2);
	HI_SYS_WriteRegister(0x10203018, 0x2);
	HI_SYS_WriteRegister(0x10203020, 0x1);	  
	
	g_stHdmiArgs.enHdmi 	  = HI_UNF_HDMI_ID_0;
	g_stHdmiArgs.enWantFmt	  = HI_UNF_ENC_FMT_1080i_50;

	{
		g_stHdmiArgs.AudioFreq		   = HI_UNF_SAMPLE_RATE_48K;
		g_stHdmiArgs.AduioBitPerSample = 16;
		g_stHdmiArgs.AudioChannelNum   = 2;
		g_stHdmiArgs.AudioInputType    = HI_UNF_SND_INTERFACE_I2S;//HI_UNF_SND_INTERFACE_I2S;//HI_UNF_SND_INTERFACE_SPDIF;
		g_stHdmiArgs.ForceHDMIFlag	   = HI_FALSE;
	}
	
	stHdmiInitParam.pfnHdmiEventCallback = HDMI_Event_Proc;//NULL
	stHdmiInitParam.pCallBackArgs		 = &g_stHdmiArgs;
	stHdmiInitParam.enForceMode 		 = HI_UNF_HDMI_FORCE_HDMI;//HI_UNF_HDMI_FORCE_NULL;
	Ret = HI_UNF_HDMI_Init(&stHdmiInitParam);
	if (HI_SUCCESS != Ret)
	{
		return ROC_ERR;
	}
	
	Ret = HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0);
	if (Ret != HI_SUCCESS)
	{
		HI_UNF_HDMI_DeInit();
		return ROC_ERR;
	}

	//----------------------------------------vo init------------------------------------------//
	DOFUNC_RETURN(Ret = HI_UNF_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL));		
	DOFUNC_RETURN(HI_UNF_VO_Open(g_VoE));


	stRect.s32X = 0;
	stRect.s32Y = 0;
	stRect.s32Width = 1920;
	stRect.s32Height = 1080;
	
	stWinAttr.enVo = HI_UNF_VO_HD0;
	stWinAttr.bVirtual = HI_FALSE;
	stWinAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_4TO3;
	stWinAttr.enAspectCvrs = HI_UNF_ASPECT_CVRS_IGNORE;
	stWinAttr.stInputRect = stRect;
	stWinAttr.stOutputRect = stRect;

	DOFUNC_RETURN(HI_UNF_VO_CreateWindow(&stWinAttr, &g_hWindowHandle));

	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AAC.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AC3.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.COOK.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DRA.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DTS.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.EAC3.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.MP2.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.MP3.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.PCM.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.TRUEHD.decode.so");
	HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.WMA.decode.so");

	DOFUNC_RETURN(HI_UNF_AVPLAY_Init());


	DOFUNC_RETURN(HI_UNF_SO_Init());


	DOFUNC_RETURN(HI_UNF_AVPLAY_GetDefaultConfig(&stAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS));
	stAttr.stStreamAttr.u32VidBufSize = (9*1024*1024);
	stAttr.u32DemuxId = (HI_U32)0;

	DOFUNC_RETURN(HI_UNF_AVPLAY_Create(&stAttr, &g_hAvHandle));
	DOFUNC_RETURN(HI_UNF_AVPLAY_ChnOpen(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &maxCapbility));
	DOFUNC_RETURN(HI_UNF_AVPLAY_ChnOpen(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL));
	DOFUNC_RETURN(HI_UNF_VO_AttachWindow(g_hWindowHandle, g_hAvHandle));
	DOFUNC_RETURN(HI_UNF_VO_SetWindowEnable(g_hWindowHandle, HI_TRUE));
	DOFUNC_RETURN(HI_UNF_SND_Attach(HI_UNF_SND_0, g_hAvHandle, HI_UNF_SND_MIX_TYPE_MASTER, 100));


	HI_UNF_AVPLAY_GetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr);
	stSyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
	stSyncAttr.stSyncStartRegion.s32VidPlusTime = 60;
	stSyncAttr.stSyncStartRegion.s32VidNegativeTime = -20;
	stSyncAttr.stSyncNovelRegion.s32VidPlusTime =3000;
	stSyncAttr.stSyncNovelRegion.s32VidNegativeTime =-3000;
	stSyncAttr.s32VidPtsAdjust = -40;
	stSyncAttr.s32AudPtsAdjust = 0;
	stSyncAttr.u32PreSyncTimeoutMs =0;
	stSyncAttr.bQuickOutput = HI_FALSE;
	DOFUNC_RETURN(HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr));
	
	TDRV_GPIO_AudioMute(HI_FALSE);
	

	g_bAVInitialed = HI_TRUE;

	
	return ROC_OK;
}


/**************************************************************************
��������: 
            rocme_porting_av_play
����˵��: 
            ���ݴ��������Ƶ��������ָ��������ͨ���ϲ���ָ���Ľ�Ŀ�����޷���
        ��ʵ������Ƶ�ķ�����ƣ������º���ʱ
        rocme_porting_av_pid_set();
        rocme_porting_audio_play();
        rocme_porting_video_play();
        �˺������ܱ���ʵ�֡�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ avpara        ] : ����Ƶ���Ų����ṹ��,��������:
                                aud_pid   -  ��Ŀ��Ƶpid 
                                vid_pid   -  ��Ŀ��Ƶpid 
                                pcr_pid   -  ��ĿPCR pid 
                                aud_type  -  ��Ŀ��Ƶ���� 
                                vid_type  -  ��Ŀ��Ƶ���� 
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��Ŀ�ɹ����� )
    ʧ�� : -1 �� ������ ( ��Ŀ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_play(const INT32_T channel_index,const Roc_AV_Para_t av_para)
{
ROCME_TEST_PRINT
	HI_UNF_VCODEC_ATTR_S  VdecAttr;
	HI_U32 u32Vpid = av_para.vid_pid;
	HI_U32 u32Ppid = av_para.pcr_pid;
	HI_U32 u32Apid = av_para.aud_pid;
	
	if(g_bAVInitialed == HI_FALSE)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"AV not initial\n");
		return ROC_ERR;
	}

	
	if( 0x1fff == u32Apid)
	{
		DOFUNC_RETURN(HI_UNF_AVPLAY_Stop(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL));
		
	}
	else
	{
		TDRV_Set_Audio_type(av_para.aud_type);
		DOFUNC_RETURN(HIADP_AVPlay_SetAdecAttr(g_hAvHandle,g_AudioType,HD_DEC_MODE_RAWPCM, 1));
		DOFUNC_RETURN(HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &u32Apid)); 
	
	}

	if( 0x1fff == u32Vpid )
	{
		DOFUNC_RETURN(HI_UNF_AVPLAY_Stop(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, NULL));

	}
	else
	{
		DOFUNC_RETURN(HI_UNF_AVPLAY_GetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr));
		TDRV_Set_Video_type(av_para.vid_type);
		
		VdecAttr.enType = g_VideoType;
		VdecAttr.enMode = HI_UNF_VCODEC_MODE_NORMAL;
		VdecAttr.u32ErrCover = 100;
		VdecAttr.u32Priority = 3;

		DOFUNC_RETURN(HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr));
		DOFUNC_RETURN(HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_VID_PID, &u32Vpid)); 

	}
	
	DOFUNC_RETURN(HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_PCR_PID, &u32Ppid)); 
	
	DOFUNC_RETURN(HI_UNF_AVPLAY_Start(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL));
	DOFUNC_RETURN(HI_UNF_AVPLAY_Start(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, NULL));

	return ROC_OK;
	
}

/**************************************************************************
��������: 
            rocme_porting_av_stop
����˵��: 
            ָֹͣ������ͨ���ϵ���Ƶ���ţ����޷�����ʵ������Ƶ�ķ�����ƣ���
        ���º���ʱ
        rocme_porting_av_pid_clean();
        rocme_porting_audio_stop();
        rocme_porting_video_stop();
        �˺������ܱ���ʵ�֡�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ is_last_pic   ] : �Ƿ���ֹͣ��Ƶǰ�����һ֡����:
                                ROC_TRUE   -  �������һ֡����
                                ROC_FALSE  -  ���������һ֡���棬������ʾ����
                            ��I ֡
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��Ŀ�ɹ�ֹͣ )
    ʧ�� : -1 �� ������ ( ��Ŀֹͣʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_stop(const INT32_T channel_index,const ROC_BOOL is_last_pic)
{
ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{	
		return ROC_ERR;
	}

	HI_UNF_AVPLAY_STOP_OPT_S stStopOpt;
	memset(&stStopOpt, 0, sizeof(HI_UNF_AVPLAY_STOP_OPT_S));
	if(is_last_pic)
	{
		stStopOpt.enMode		= HI_UNF_AVPLAY_STOP_MODE_STILL;
	}
	else
	{	
		stStopOpt.enMode		= HI_UNF_AVPLAY_STOP_MODE_BLACK;
	}
	stStopOpt.u32TimeoutMs= 0;
	
	DOFUNC_RETURN(HI_UNF_AVPLAY_Stop(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stStopOpt)); 
	DOFUNC_RETURN(HI_UNF_AVPLAY_Stop(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL)); 
	
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_av_pid_set
����˵��: 
            ����ָ������ͨ���ϵ�ָ������Դ(��Ƶ����Ƶ��PCR����Ļ��)��PID
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ type          ] : PID�������ͽṹ�壬��������:
                                ROC_AUDIO_PID     -  ���������PIDΪ��ƵPID 
                                ROC_VIDEO_PID     -  ���������PIDΪ��ƵPID
                                ROC_PCR_PID       -  ���������PIDΪPCR PID
                                ROC_SUBTITLE_PID  -  ���������PIDΪ��ĻPID
            [ pid           ] : �����PID��ֵ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �ɹ�������ָ������Դ��PID )
    ʧ�� : -1 �� ������ ( ����PID���� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_pid_set(const INT32_T channel_index,const Roc_PID_Type_e type,const UINT16_T pid)
{
	printf("rocme_porting_av_pid_set ........ THE TYPE = %d, the pid = %d\n",type,pid);
	UINT16_T tpid = pid;
	HI_UNF_VCODEC_ATTR_S  VdecAttr;

	switch(type)
	{
		case ROC_AUDIO_PID:
		{
			DOFUNC_RETURN(HIADP_AVPlay_SetAdecAttr(g_hAvHandle,g_AudioType,HD_DEC_MODE_RAWPCM, 1));
			DOFUNC_RETURN( HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &tpid)); 

		}
		break;
		
		case ROC_VIDEO_PID:
		{
	 	DOFUNC_RETURN( HI_UNF_AVPLAY_GetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr));

		
		VdecAttr.enType = g_VideoType;
		VdecAttr.enMode = HI_UNF_VCODEC_MODE_NORMAL;
		VdecAttr.u32ErrCover = 100;
		VdecAttr.u32Priority = 3;

		DOFUNC_RETURN( HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr));
	

		DOFUNC_RETURN( HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_VID_PID, &tpid)); 	
		}
		break;
		
		case ROC_PCR_PID:
		{
			DOFUNC_RETURN( HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_PCR_PID, &tpid)); 
	
		}
		break;
		
		case ROC_SUBTITLE_PID:
		{
				
		}
		break;
		
		default:
			break;
	}

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_av_pid_clean
����˵��: 
            ���ָ������ͨ���ϵ�ָ������Դ(��Ƶ����Ƶ��PCR����Ļ��)����PID
        ��ռ�ã����������slot�Ĺ�������ֵ��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ type          ] : PID�������ͽṹ�壬��������:
                                ROC_AUDIO_PID     -  ���������PIDΪ��ƵPID 
                                ROC_VIDEO_PID     -  ���������PIDΪ��ƵPID
                                ROC_PCR_PID       -  ���������PIDΪPCR PID
                                ROC_SUBTITLE_PID  -  ���������PIDΪ��ĻPID
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���PID�ɹ� )
    ʧ�� : -1 �� ������ ( ���PIDʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_pid_clean(const INT32_T channel_index,const Roc_PID_Type_e type)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_audio_play
����˵��: 
            ʹ��ָ��������ͨ���ϵ���Ƶ��������ʼ������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ type          ] : ��Ƶ���ݵı������ͣ���������:
                                ROC_AUDIO_TYPE_AC3       -  AC3��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MPEG1     -  MPEG1��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MPEG2     -  MPEG2��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_PCM       -  PCM��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MP3       -  MP3��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MLP       -  MLP��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MPEG_AAC  -  AAC��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_UNKNOWN   -  δ֪��Ƶ�����ʽ 
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ�������ɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_play(const INT32_T channel_index,const Roc_Audio_Type_e type)
{
ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}
	printf("the type is = %d\n",type);
	TDRV_Set_Audio_type(type);
	
	DOFUNC_RETURN(HIADP_AVPlay_SetAdecAttr(g_hAvHandle,g_AudioType,HD_DEC_MODE_RAWPCM, 1));

	DOFUNC_RETURN(HI_UNF_AVPLAY_Start(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL));

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_audio_stop
����˵��: 
            ָֹͣ��������ͨ���ϵ���Ƶ������������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣ��Ƶ�������ɹ� )
    ʧ�� : -1 �� ������ ( ֹͣ��Ƶ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_stop(const INT32_T channel_index)
{
ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}		
	
	DOFUNC_RETURN(HI_UNF_AVPLAY_Stop(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL)); 

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_audio_set_volume
����˵��: 
            ����ָ������ͨ���ϵĽ�Ŀ�������������ȡֵ��Χ 0 ~ 100��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ volume        ] : ����ֵ��ȡֵ��Χ 0 ~ 100
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����趨�ɹ� )
    ʧ�� : -1 �� ������ ( �����趨ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_set_volume(const INT32_T channel_index,const UINT32_T volume)
{

ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}			
	
	DOFUNC_RETURN( HI_UNF_SND_SetVolume(HI_UNF_SND_0, volume)); 

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_audio_set_mute
����˵��: 
            ����ָ������ͨ���ϵĽ�Ŀ����Ƿ��Ǿ�����
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ is_mute       ] : �Ƿ�����ʶ:
                                ROC_TRUE   -  ����
                                ROC_FALSE  -  �Ǿ��� 
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �Ƿ������óɹ� )
    ʧ�� : -1 �� ������ ( �Ƿ�������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_set_mute(const INT32_T channel_index,const ROC_BOOL is_mute)
{
ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}
	
	if(is_mute == ROC_TRUE)
	{

		HI_UNF_SND_SetAnalogMute(HI_UNF_SND_0, HI_TRUE);
		HI_UNF_SND_SetDigitalMute(HI_UNF_SND_0, HI_TRUE);

	}
	else
	{
		HI_UNF_SND_SetAnalogMute(HI_UNF_SND_0, HI_FALSE);
		HI_UNF_SND_SetDigitalMute(HI_UNF_SND_0, HI_FALSE);
	}
	

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_audio_set_mode
����˵��: 
            ����ָ������ͨ���ϵĽ�Ŀ�������ģʽ��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ aud_mode      ] : ����ģʽ����������:
                                ROC_AUDIO_MODE_MONO    -  ������
                                ROC_AUDIO_MODE_STEREO  -  ������
                                ROC_AUDIO_MODE_LEFT    -  ������
                                ROC_AUDIO_MODE_RIGHT   -  ������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��������ģʽ�ɹ� )
    ʧ�� : -1 �� ������ ( ��������ģʽʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_set_mode(const INT32_T channel_index,const Roc_Audio_Mode_e aud_mode)
{

ROCME_TEST_PRINT
	HI_UNF_TRACK_MODE_E	enMode;


	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}			

	switch (aud_mode)
	{
	case ROC_AUDIO_MODE_MONO :
		enMode = HI_UNF_TRACK_MODE_DOUBLE_MONO;
		break;

	case ROC_AUDIO_MODE_LEFT :
		enMode = HI_UNF_TRACK_MODE_DOUBLE_LEFT;
		break;

	case ROC_AUDIO_MODE_RIGHT :
		enMode = HI_UNF_TRACK_MODE_DOUBLE_RIGHT;
		break;

	case ROC_AUDIO_MODE_STEREO:
		enMode = HI_UNF_TRACK_MODE_STEREO;
		break;
	default:
		enMode = HI_UNF_TRACK_MODE_STEREO;
		break;
	}	

	DOFUNC_RETURN(HI_UNF_SND_SetTrackMode(HI_UNF_SND_0, enMode)); 

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_audio_set_output_mode
����˵��: 
            ����ָ����Ƶ����豸�����Ƶ�����ͣ�Ĭ��Ϊpcm�����
����˵����
    ���������
            [ aud_device ] : ��Ƶ����豸���μ����Ͳμ�Roc_Audio_Device_e
            [ aud_type    ] : ��Ƶ������ͣ��������Ͳμ�Roc_Audio_Type_e
��    �أ� 
    �ɹ� : 0            ( ���óɹ� )
    ʧ�� : -1 �� ������ ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_set_output_mode(Roc_Audio_Device_e aud_device,const Roc_Audio_Type_e aud_type)
{
ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}			

	TDRV_Set_Audio_type(aud_type);
	DOFUNC_RETURN(HIADP_AVPlay_SetAdecAttr(g_hAvHandle,g_AudioType,HD_DEC_MODE_RAWPCM, 1));

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_video_play
����˵��: 
            ʹ��ָ��������ͨ���ϵ���Ƶ��������ʼ������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ type          ] : ��Ƶ���ݵı������ͣ���������:
                                ROC_VIDEO_TYPE_MPEG     -  MPGE ��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_MPEG2    -  MPGE2��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_MPEG4    -  MPGE4��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_H264     -  H.264��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_VC1      -  VC1��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_AVS      -  AVS��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_UNKNOWN  -  δ֪��Ƶ�����ʽ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ�������ɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_play(const INT32_T channel_index,const Roc_Video_Type_e type)
{
ROCME_TEST_PRINT
	HI_UNF_VCODEC_ATTR_S  VdecAttr;
	
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}

	DOFUNC_RETURN(HI_UNF_AVPLAY_GetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr));
	TDRV_Set_Video_type(type);
	
	ROCME_PRINTF(ROCME_LOG_INFO,"the video type = %d\n",g_VideoType);
	
	VdecAttr.enType = g_VideoType;
	VdecAttr.enMode = HI_UNF_VCODEC_MODE_NORMAL;
	VdecAttr.u32ErrCover = 100;
	VdecAttr.u32Priority = 3;
	
	DOFUNC_RETURN(HI_UNF_AVPLAY_SetAttr(g_hAvHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr));


	DOFUNC_RETURN(HI_UNF_AVPLAY_Start(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, NULL));



	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_video_stop
����˵��: 
            ָֹͣ��������ͨ���ϵ���Ƶ������������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ is_last_pic   ] : �Ƿ���ֹͣ��Ƶǰ�����һ֡����:
                                ROC_TRUE   -  �������һ֡����
                                ROC_FALSE  -  ���������һ֡���棬������ʾ����
                            ��I ֡
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣ��Ƶ�������ɹ� )
    ʧ�� : -1 �� ������ ( ֹͣ��Ƶ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_stop(const INT32_T channel_index, const ROC_BOOL is_last_pic)
{
ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{	
		return ROC_ERR;
	}

	HI_UNF_AVPLAY_STOP_OPT_S stStopOpt;
	memset(&stStopOpt, 0, sizeof(HI_UNF_AVPLAY_STOP_OPT_S));
	if(is_last_pic)
	{
		stStopOpt.enMode		= HI_UNF_AVPLAY_STOP_MODE_STILL;
	}
	else
	{	
		stStopOpt.enMode		= HI_UNF_AVPLAY_STOP_MODE_BLACK;
	}
	stStopOpt.u32TimeoutMs= 0;
	
	DOFUNC_RETURN(HI_UNF_AVPLAY_Stop(g_hAvHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stStopOpt));

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_video_set_display
����˵��: 
            �����Ƿ���ָ������ͨ���ϵ���Ƶ�㡣
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ enable        ] : �Ƿ�����Ƶ���ʶ:
                                ROC_TRUE   -  ����ָ������Ƶ��
                                ROC_FALSE  -  �ر�ָ������Ƶ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����Ƿ�����Ƶ��ɹ� )
    ʧ�� : -1 �� ������ ( �����Ƿ�����Ƶ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_display(const INT32_T channel_index,const ROC_BOOL enable)
{
ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}	

	if( ROC_TRUE== enable)
	{
		DOFUNC_RETURN(HI_UNF_VO_SetWindowEnable(g_hWindowHandle, HI_TRUE));
	}
	else
	{	
		DOFUNC_RETURN(HI_UNF_VO_SetWindowEnable(g_hWindowHandle, HI_FALSE));
	}

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_video_set_window
����˵��: 
            ����ָ��������ͨ���ϵ���Ƶ������ڵ�����ʹ�С��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ height        ] : ��Ƶ���ڵĸ�
            [ width         ] : ��Ƶ���ڵĿ�
            [ x_start       ] : ��Ƶ���ڵĺ���ʼ����
            [ y_start       ] : ��Ƶ���ڵ�����ʼ����
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ����λ�óɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ����λ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_window(const INT32_T channel_index,const UINT32_T height,const UINT32_T width,const UINT32_T x_start,const UINT32_T y_start)
{

	ROCME_TEST_PRINT
	HI_UNF_WINDOW_ATTR_S 		WindowAttr;
	HI_UNF_ENC_FMT_E enDisplayFmt = HI_UNF_ENC_FMT_BUTT;
	HI_U32 u32Width = 1280;
	HI_U32 u32Height = 720;
	
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}	

	DOFUNC_RETURN(HI_UNF_DISP_GetFormat(HI_UNF_DISP_HD0, &enDisplayFmt));

	switch (enDisplayFmt)
	{
		case HI_UNF_ENC_FMT_1080P_60:
		case HI_UNF_ENC_FMT_1080P_50:
		case HI_UNF_ENC_FMT_1080P_30:	
		case HI_UNF_ENC_FMT_1080P_25:
		case HI_UNF_ENC_FMT_1080P_24:	
		case HI_UNF_ENC_FMT_1080i_60:	
		case HI_UNF_ENC_FMT_1080i_50:
			u32Width = 1920;
			u32Height = 1080;
			break;

		case HI_UNF_ENC_FMT_720P_60:	
		case HI_UNF_ENC_FMT_720P_50:
			u32Width = 1280;
			u32Height = 720;
			break;
		
		case HI_UNF_ENC_FMT_576P_50: 	
		case HI_UNF_ENC_FMT_PAL:		
		case HI_UNF_ENC_FMT_PAL_N:			
		case HI_UNF_ENC_FMT_PAL_Nc:		
		case HI_UNF_ENC_FMT_SECAM_SIN:	
		case HI_UNF_ENC_FMT_SECAM_COS:	
			u32Width = 720;
			u32Height = 576;
			break;

		case HI_UNF_ENC_FMT_NTSC:			
		case HI_UNF_ENC_FMT_NTSC_J:		
		case HI_UNF_ENC_FMT_NTSC_PAL_M:
		case HI_UNF_ENC_FMT_480P_60:
			u32Width = 720;
			u32Height = 480;
			break;

		default:
			return ROC_ERR;

	}

	

	HI_UNF_VO_GetWindowAttr(g_hWindowHandle, &WindowAttr);
	
	WindowAttr.stOutputRect.s32X			= x_start*u32Width/1280;
	WindowAttr.stOutputRect.s32Y			= y_start*u32Height/720;
	WindowAttr.stOutputRect.s32Width		= width*u32Width/1280;
	WindowAttr.stOutputRect.s32Height		= height*u32Height/720;
	


	DOFUNC_RETURN(HI_UNF_VO_SetWindowAttr(g_hWindowHandle, &WindowAttr));

    return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_video_set_denc
����˵��: 
            ����ָ������ͨ���ϵ���Ƶ�����ʽ��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ denc_mode     ] : ��Ƶ��ʽ����������:
                                ROC_DENC_MODE_NONE   -  δ�������Ƶ��ʽ
                                ROC_DENC_MODE_NTSCM  -  ����ƽ�������ʽ
                                ROC_DENC_MODE_PALN   -  ���е�������ƽ�������ʽ
                                ROC_DENC_MODE_SECAM  -  ˳���Ͳ�ɫ��洢������ʽ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ��ʽ�ɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ��ʽʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_denc(const INT32_T channel_index,const Roc_Vid_DENC_Mode_e denc_mode)
{
ROCME_TEST_PRINT
	HI_S32 						Ret = HI_FAILURE;
	HI_UNF_ENC_FMT_E 			fmt = HI_UNF_ENC_FMT_PAL;

	HI_HANDLE	hLayer;
	HI_HANDLE	hSurface;
	int nWidth = 1920;
	int nHeight = 1080;

	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}		

	switch ( denc_mode)
	{
		case ROC_DENC_MODE_PALN:
			fmt = HI_UNF_ENC_FMT_PAL;
			//nWidth = 720;
			//nHeight = 576;
			break;

		case ROC_DENC_MODE_NTSCM:
			fmt = HI_UNF_ENC_FMT_NTSC;
			//nWidth = 720;
			//nHeight = 480;
			break;
		case ROC_DENC_MODE_SECAM:
			fmt = HI_UNF_ENC_FMT_SECAM_SIN;
			break;
		default:
			return ROC_ERR;
	}
	
	DOFUNC_RETURN(HI_UNF_DISP_SetFormat(HI_UNF_DISP_SD0, fmt));


	//DOFUNC_RETURN(HI_GO_SetScreenSize(Get_Osd_Handle(), nWidth, nHeight));
	return ROC_OK;


}

/**************************************************************************
��������: 
            rocme_porting_video_set_aspect
����˵��: 
            ����ָ������ͨ���ϵ���Ƶ�������Ŀ�߱ȡ�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ aspect_ratio  ] : ��Ƶ�������Ŀ�߱ȣ���������:
                                ROC_ASPECT_RATIO_NONE    -  δ�������Ƶ�������
                                ROC_ASPECT_RATIO_16TO9   -  16:9�������
                                ROC_ASPECT_RATIO_4TO3    -  4:3�������
                                ROC_ASPECT_RATIO_SQUARE  -  1:1�������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���û�������ɹ� )
    ʧ�� : -1 �� ������ ( ���û������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_aspect(const INT32_T channel_index,const Roc_Plane_Aspect_Ratio_e aspect_ratio)
{
ROCME_TEST_PRINT
	HI_UNF_WINDOW_ATTR_S 		WindowAttr;

	
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}

	HI_UNF_VO_GetWindowAttr(g_hWindowHandle, &WindowAttr);


	switch(aspect_ratio)
	{
		case ROC_ASPECT_RATIO_4TO3:
			WindowAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_4TO3;
			break;

		case ROC_ASPECT_RATIO_16TO9:
			WindowAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_16TO9;
			break;

		case ROC_ASPECT_RATIO_SQUARE:
			WindowAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_SQUARE;
			break;
		default:
			WindowAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_UNKNOWN;
			break;
	}

	DOFUNC_RETURN(HI_UNF_VO_SetWindowAttr(g_hWindowHandle, &WindowAttr));

    return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_video_set_aspect_conversion
����˵��: 
            ����ָ������ͨ���ϵĻ���ǿ��ת��������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ ar_conversion ] : ����ǿ��ת���������ͣ���������:
                                ROC_DISPLAY_AR_CONVERSION_NONE        
                            -  δ�������Ƶ�������ת��
                                ROC_DISPLAY_AR_CONVERSION_PAN_SCAN    
                            -  PAN&SCAN �ͻ����ת�������ü�ԭʼ���棬������
                            ����Ļ������޺ڱ�
                                ROC_DISPLAY_AR_CONVERSION_LETTER_BOX  
                            -  LETTER BOX �ͻ����ת����������ȫ��ԭʼ���棬
                            ��Ļδʹ�ò����úڱ������
                                ROC_DISPLAY_AR_CONVERSION_COMBINED    
                            -  PAN&SCAN��LETTER BOX ��ϱ���ת��
                                ROC_DISPLAY_AR_CONVERSION_IGNORE      
                            -  ����ת����ֱ�Ӱ���ԭʼ�����������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���û������ǿ��ת���ɹ� )
    ʧ�� : -1 �� ������ ( ���û������ǿ��ת��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_aspect_conversion(const INT32_T channel_index,const Roc_Vid_AspectRatioConversion_e ar_conversion)
{
	ROCME_TEST_PRINT
	HI_UNF_WINDOW_ATTR_S 		WindowAttr;

	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}

	HI_UNF_VO_GetWindowAttr(g_hWindowHandle, &WindowAttr);


	switch(ar_conversion)
	{
		case ROC_DISPLAY_AR_CONVERSION_PAN_SCAN:
			//WindowAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_4TO3;
			WindowAttr.enAspectCvrs = HI_UNF_ASPECT_CVRS_PANANDSCAN;
			break;

		case ROC_DISPLAY_AR_CONVERSION_LETTER_BOX:
			//WindowAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_16TO9;			
			WindowAttr.enAspectCvrs = HI_UNF_ASPECT_CVRS_LETTERBOX;
			break;

		case ROC_DISPLAY_AR_CONVERSION_COMBINED:
			//WindowAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_UNKNOWN;		
			WindowAttr.enAspectCvrs = HI_UNF_ASPECT_CVRS_COMBINED;
			break;
		case ROC_DISPLAY_AR_CONVERSION_NONE:
		case ROC_DISPLAY_AR_CONVERSION_IGNORE:
			//WindowAttr.enAspectRatio = HI_UNF_ASPECT_RATIO_UNKNOWN;		
			WindowAttr.enAspectCvrs = HI_UNF_ASPECT_CVRS_IGNORE;
			break;
		default:
			return ROC_ERR;
	}

	DOFUNC_RETURN(HI_UNF_VO_SetWindowAttr(g_hWindowHandle, &WindowAttr));

    return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_video_set_bcs
����˵��: 
            ����ָ������ͨ���ϵ���Ƶ���ֲ���(���ȡ��ԱȶȺͱ��Ͷ�)��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ bcs_level     ] : ��Ƶ���ֲ�������������:
                                 brightness  -  ��Ƶ������  ����Χ 0 ~ 100
                                 contrast    -  ��Ƶ��Աȶȣ���Χ 0 ~ 100
                                 saturation  -  ��Ƶ�㱥�Ͷȣ���Χ 0 ~ 100
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ���ֲ����ɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ���ֲ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_bcs(const INT32_T channel_index,const Roc_Vid_BCSLevel_t bcs_level)
{

ROCME_TEST_PRINT
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}		
		
	DOFUNC_RETURN(HI_UNF_DISP_SetBrightness(g_DispE, (HI_U32)bcs_level.brightness));

	DOFUNC_RETURN(HI_UNF_DISP_SetContrast(g_DispE, bcs_level.contrast));	

	DOFUNC_RETURN(HI_UNF_DISP_SetSaturation(g_DispE, bcs_level.saturation));


	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_video_set_vtg
����˵��: 
            ����ָ������ͨ���ϵ���Ƶ����ֱ��ʡ�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ vtg_mode     ] : ��Ƶ����ֱ���
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ����ֱ��ʳɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ����ֱ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_vtg(const INT32_T channel_index,const ROC_VTG_TimingMode_e vtg_mode)
{
ROCME_TEST_PRINT

	HI_UNF_ENC_FMT_E enEncFmt = HI_UNF_ENC_FMT_BUTT;
	
	switch(vtg_mode)
	{
		case ROC_1080P:
			enEncFmt = HI_UNF_ENC_FMT_1080P_60;
			break;
		case ROC_1080I:
			enEncFmt = HI_UNF_ENC_FMT_1080i_60;
			break;
		case ROC_720P:
			enEncFmt = HI_UNF_ENC_FMT_720P_60;
			break;	
		case ROC_576P:
			enEncFmt = HI_UNF_ENC_FMT_576P_50;
			break;
		case ROC_576I:
			enEncFmt = HI_UNF_ENC_FMT_PAL;
			break;
		case ROC_480P:
			enEncFmt = HI_UNF_ENC_FMT_480P_60;
			break;
		case ROC_480I:
			enEncFmt = HI_UNF_ENC_FMT_NTSC;
			break;			
		default:
			return HI_FAILURE;
			
	}
	
	DOFUNC_RETURN(HI_UNF_DISP_SetFormat(g_DispE, enEncFmt));

	return ROC_OK;

#if 0
	HI_UNF_ENC_FMT_E 			fmt = HI_UNF_ENC_FMT_PAL;

	HI_HANDLE	hLayer;
	HI_HANDLE	hSurface;
	int nWidth = 1920;
	int nHeight = 1080;


	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}		


	switch ( vtg_mode)
	{
	case ROC_1080P:
		fmt = HI_UNF_ENC_FMT_1080P_50;
		break;

	case ROC_1080I:
		fmt = HI_UNF_ENC_FMT_1080i_50;
		break;
		
	case ROC_720P:
		fmt = HI_UNF_ENC_FMT_720P_60;
		nWidth = 1280;
		nHeight = 720;
		break;
		
	case ROC_576P:
		fmt = HI_UNF_ENC_FMT_576P_50;
		nWidth = 720;
		nHeight = 576;
		break;
	case ROC_480P:
		fmt = HI_UNF_ENC_FMT_480P_60;
		nWidth = 720;
		nHeight = 480;
		break;
		
	case ROC_576I:
		fmt = HI_UNF_ENC_FMT_PAL;
		nWidth = 720;
		nHeight = 576;
		break;

	case ROC_480I:
		fmt = HI_UNF_ENC_FMT_NTSC;
		nWidth = 720;
		nHeight = 480;
		break;

	}
	
	DOFUNC_RETURN(HI_UNF_DISP_SetFormat(g_DispE, fmt));

	//TDRV_JPG_GetLayerSurface(&hLayer, &hSurface);
	//��ȡosd����

	HI_GO_SetScreenSize(hLayer, nWidth, nHeight);


	return ROC_OK;
#endif
}


/*************************************************************************
��������: 
            rocme_porting_video_set_fullscreen
����˵��: 
            ������ƵΪȫ����
����˵����
    ���������
	     ��
���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���óɹ� )
    ʧ�� : -1 �� ������ ( ����ʧ�� )
�޸ļ�¼��
***************************************************************************/
INT32_T rocme_porting_video_set_fullscreen(void)
{
ROCME_TEST_PRINT
#if 0
	HI_UNF_WINDOW_ATTR_S 		WindowAttr;

	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}	

	HI_UNF_VO_GetWindowAttr(g_hWindowHandle, &WindowAttr);
	
	WindowAttr.stOutputRect.s32X			= 0;
	WindowAttr.stOutputRect.s32Y			= 0;
	WindowAttr.stOutputRect.s32Width		= 1920;
	WindowAttr.stOutputRect.s32Height		= 1080;
	


	DOFUNC_RETURN(HI_UNF_VO_SetWindowAttr(g_hWindowHandle, &WindowAttr));

    return ROC_OK;
#endif
}


/**************************************************************************
��������: 
            rocme_porting_iframe_set_display
����˵��: 
            �����Ƿ�����̬�����ʾ
����˵����
    ���������
            [ enable        ] : �Ƿ�����̬���ʶ:
                                ROC_TRUE   -  ������̬�㣬���Կ�����̬��I֡ͼƬ����ʾ
                                ROC_FALSE  -  �رվ�̬�㣬�����Կ�����̬��I֡ͼƬ����ʾ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����Ƿ�����̬��ɹ� )
    ʧ�� : -1 �� ������ ( �����Ƿ�����̬��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_iframe_set_display(ROC_BOOL enable)
{
ROCME_TEST_PRINT
	return 0;
#if 0
	HI_UNF_AVPLAY_PAUSE_OPT_S stPauseOpt;
	HI_UNF_AVPLAY_RESUME_OPT_S stResumeOpt;
	
	stPauseOpt.u32Reserved = 0;
	stResumeOpt.u32Reserved = 0;
	
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}

	if(enable)
	{
		HI_UNF_AVPLAY_Pause(g_hAvHandle, &stPauseOpt);

		HI_UNF_SND_SetAnalogMute(HI_UNF_SND_0, HI_TRUE);
		HI_UNF_SND_SetDigitalMute(HI_UNF_SND_0, HI_TRUE);
	}
	else
	{
		HI_UNF_AVPLAY_Resume(g_hAvHandle, &stResumeOpt);

		HI_UNF_SND_SetAnalogMute(HI_UNF_SND_0, HI_FALSE);
		HI_UNF_SND_SetDigitalMute(HI_UNF_SND_0, HI_FALSE);
	}
	

	return ROC_OK;
#endif
}

/**************************************************************************
��������: 
            rocme_porting_dec_iframe_still
����˵��: 
            ʹ��ָ������ͨ������ָ����һ��I֡������������ʾ��ָ���Ĳ��ϡ�
            ��ָ��layer = ROC_LAYER_VIDEO������������ϵ�I֡�����ʾ��
            ��Ƶ����(����Ƶ��رգ������Զ���)
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ *data_ptr     ] : I֡���ݵ�ͷָ��
            [ data_len      ] : I֡���ݵĳ���
            [ layer         ] : ��ʾ�Ĳ������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����I֡�ɹ� )
    ʧ�� : -1 �� ������ ( ����I֡ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_dec_iframe_still(const INT32_T channel_index,const UINT8_T *data_ptr,const UINT32_T data_len,const Roc_OutPut_Layer_e layer)
{

ROCME_TEST_PRINT
	HI_UNF_CAPTURE_PICTURE_S *stPicture =  NULL;
	HI_S32 ret=0;

	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}	
	

	DOFUNC_RETURN(HI_UNF_VO_SetWindowEnable(g_hWindowHandle, HI_TRUE));


	g_stIframe.enType		= HI_UNF_VCODEC_TYPE_MPEG2;
	g_stIframe.pu8Addr	= data_ptr;
	g_stIframe.u32BufSize	= data_len;

	ret = HI_UNF_VO_AttachWindow(g_hWindowHandle,g_hAvHandle);
	if( HI_SUCCESS != ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_VO_AttachWindow failed ret = 0x%x \n",ret);
		return ROC_ERR;
	}

	ret = HI_UNF_AVPLAY_DecodeIFrame(g_hAvHandle, &g_stIframe, NULL);
	if( HI_SUCCESS != ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_AVPLAY_DecodeIFrame failed ret = 0x%x \n",ret);
		return ROC_ERR;
	}

	return ROC_OK;	
}

/**************************************************************************
��������: 
            rocme_porting_get_iframe_buff
����˵��: 
            ��ȡ�ײ����I֡ʱ��ʹ�õ��ڴ�buff��ͷָ��ͳ���
����˵����
    ���������
            ��
    ���������
            [ **buff_ptr ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ *buff_len     ] : I֡���ݵ�ͷָ��
��    �أ� 
    �ɹ� : 0            ( ����I֡�ɹ� )
    ʧ�� : -1 �� ������ ( ����I֡ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_iframe_buff( void **buff_ptr , UINT32_T *buff_len )
{
ROCME_TEST_PRINT
	#if 0
	*buff_ptr = g_stIframe.pu8Addr;
	*buff_len = g_stIframe.u32BufSize;
	return ROC_OK;
	#endif
}


/**************************************************************************
��������: 
            rocme_porting_dec_black_iframe
����˵��: 
            ��ĳ��������Ϊ��ɫ
����˵����
    ���������
            [ layer         ] : ��ʾ�Ĳ������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���ɹ� )
    ʧ�� : -1 �� ������ ( ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_dec_black_iframe(const Roc_OutPut_Layer_e layer)
{
ROCME_TEST_PRINT
#if 0
	HI_UNF_CAPTURE_PICTURE_S *stPicture =  NULL;
	HI_S32 ret=0;
	if(g_bAVInitialed == HI_FALSE)
	{
		return ROC_ERR;
	}
	
	ROCME_PRINTF(ROCME_LOG_INFO,"rocme_porting_dec_iframe_still  layer = %d\r\n",layer);
#if 0
	if(layer ==ROC_LAYER_VIDEO )
	{
		g_stIframe.enType		= HI_UNF_VCODEC_TYPE_MPEG2;
		memset(g_stIframe.pu8Addr,0,g_stIframe.u32BufSize);
		HI_UNF_AVPLAY_DecodeIFrame(g_hAvHandle, &g_stIframe, stPicture);
	}
	else
	{
		return ROC_ERR;
	}
#endif



	g_stIframe.enType		= HI_UNF_VCODEC_TYPE_MPEG2;
	memset(g_stIframe.pu8Addr,0,g_stIframe.u32BufSize);
	ret = HI_UNF_AVPLAY_DecodeIFrame(g_hAvHandle, &g_stIframe, NULL);
	if( HI_SUCCESS != ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_AVPLAY_DecodeIFrame failed ret = 0x%x \n",ret);
		return ROC_ERR;
	}
	
	return ROC_OK;	
	#endif
}

/**************************************************************************
��������: 
            rocme_porting_des_init
����˵��: 
            ��ʼ����������
����˵����
    ���������
            ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��������ʼ���ɹ� )
    ʧ�� : -1 �� ������ ( ��������ʼ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_init(void)
{
ROCME_TEST_PRINT
	if( HI_SUCCESS != HI_UNF_DMX_CreateDescrambler(0, &g_VideoDesHandle) )//HI_UNF_DMX_NewDescrambler
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[TDRV_DescramSetPID] HI_DMX_CreateDescrambler error !!!!!\r\n");
		return ROC_ERR;
	}

	if( HI_SUCCESS != HI_UNF_DMX_CreateDescrambler(0, &g_AudioDesHandle ) )//HI_UNF_DMX_NewDescrambler
	{
		HI_UNF_DMX_DestroyDescrambler(g_VideoDesHandle);
		ROCME_PRINTF(ROCME_LOG_ERROR,"[TDRV_DescramSetPID] HI_DMX_CreateDescrambler error !!!!!\r\n");
		return ROC_ERR;
	}
	
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_des_term
����˵��: 
            �رս�����
����˵����
    ���������
            ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �������رճɹ� )
    ʧ�� : -1 �� ������ ( �������ر�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_term(void)
{
ROCME_TEST_PRINT
	HI_S32 s32Ret = HI_SUCCESS;
			
	s32Ret = HI_UNF_DMX_DestroyDescrambler(g_VideoDesHandle);
	s32Ret != HI_UNF_DMX_DestroyDescrambler(g_AudioDesHandle);
	
	if (HI_SUCCESS != s32Ret)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR," s32Ret = 0x%x\n", s32Ret);
	}
	
	return s32Ret;	

}

/**************************************************************************
��������: 
            rocme_porting_des_audio_start
����˵��: 
            ʹ��ָ������ͨ���ϵ���Ƶ���ſ�ʼ������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ���ųɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_audio_start(const INT32_T channel_index)
{
ROCME_TEST_PRINT
	HI_HANDLE hChanHandle;
	
	if( HI_SUCCESS != HI_UNF_AVPLAY_GetDmxAudChnHandle (g_hAvHandle, &hChanHandle))
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "[TDRV_DescramDisablePID] HI_UNF_DMX_GetAudioChannelId failed! nChannelId: 0x%x\r\n", &hChanHandle);
		return ROC_ERR;
	}

	if( HI_SUCCESS != HI_UNF_DMX_AttachDescrambler( g_AudioDesHandle, hChanHandle ) )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[TDRV_DescramEnablePID] HI_DMX_AttachDescrambler failed!\r\n");
		return ROC_ERR;
	}
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_des_audio_stop
����˵��: 
            ָֹͣ������ͨ���ϵ���Ƶ���š�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣ��Ƶ���ųɹ� )
    ʧ�� : -1 �� ������ ( ֹͣ��Ƶ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_audio_stop(const INT32_T channel_index)
{
ROCME_TEST_PRINT
	HI_HANDLE hChanHandle;
	
	if( HI_SUCCESS != HI_UNF_AVPLAY_GetDmxVidChnHandle (g_hAvHandle, &hChanHandle))
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "[TDRV_DescramDisablePID] HI_UNF_DMX_GetAudioChannelId failed! nChannelId: 0x%x\r\n", &hChanHandle);
		return ROC_ERR;
	}
	
	//HI_UNF_DMX_CloseChannel(hChanHandle);

	if( HI_SUCCESS != HI_UNF_DMX_DetachDescrambler( g_AudioDesHandle, hChanHandle ) )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[TDRV_DescramDisablePID] HI_DMX_AttachDescrambler failed!\r\n");
		return ROC_ERR;
	}

	//HI_UNF_DMX_OpenChannel(hChanHandle);

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_des_video_start
����˵��: 
            ʹ��ָ������ͨ���ϵ���Ƶ���ſ�ʼ������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ���ųɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_video_start(const INT32_T channel_index)
{
ROCME_TEST_PRINT
	HI_HANDLE hChanHandle;
	
	if( HI_SUCCESS != HI_UNF_AVPLAY_GetDmxVidChnHandle (g_hAvHandle, &hChanHandle))
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "[TDRV_DescramDisablePID] HI_UNF_DMX_GetAudioChannelId failed! nChannelId: 0x%x\r\n", &hChanHandle);
		return ROC_ERR;
	}

	if( HI_SUCCESS != HI_UNF_DMX_AttachDescrambler( g_VideoDesHandle, hChanHandle ) )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[TDRV_DescramEnablePID] HI_DMX_AttachDescrambler failed!\r\n");
		return ROC_ERR;
	}
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_des_video_stop
����˵��: 
            ָֹͣ������ͨ���ϵ���Ƶ���š�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣ��Ƶ���ųɹ� )
    ʧ�� : -1 �� ������ ( ֹͣ��Ƶ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_video_stop(const INT32_T channel_index)
{
	ROCME_TEST_PRINT
	HI_HANDLE hChanHandle;
	
	if( HI_SUCCESS != HI_UNF_AVPLAY_GetDmxVidChnHandle (g_hAvHandle, &hChanHandle))
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "[TDRV_DescramDisablePID] HI_UNF_DMX_GetAudioChannelId failed! nChannelId: 0x%x\r\n", &hChanHandle);
		return ROC_ERR;
	}
	
	//HI_UNF_DMX_CloseChannel(hChanHandle);

	if( HI_SUCCESS != HI_UNF_DMX_DetachDescrambler( g_VideoDesHandle, hChanHandle ) )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"[TDRV_DescramDisablePID] HI_DMX_AttachDescrambler failed!\r\n");
		return ROC_ERR;
	}

	//HI_UNF_DMX_OpenChannel(hChanHandle);

	return ROC_OK;
}

/***************************************************************************
����˵����
    ������Ƶ������������

����˵����
    channel_index:ͨ����ʶ��,�����ڶ�ͨ��ƽ̨
    pbyEvenKey:ż��Կ,����Ϊ8�ֽ�
    pbyOddKey: ����Կ,����Ϊ8�ֽ�

��    �أ� 
    0    ----�ɹ�
    -1   ----ʧ��
***************************************************************************/
INT32_T rocme_porting_des_video_setcw(const INT32_T channel_index, UINT8_T *pbyEvenKey, UINT8_T *pbyOddKey)
{
ROCME_TEST_PRINT
	HI_S32 ssret;
	ssret = HI_UNF_DMX_SetDescramblerEvenKey(g_VideoDesHandle,pbyEvenKey);
	
	if(ssret != HI_SUCCESS)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"(%d):HI_UNF_DMX_SetDescramblerEvenKey Error,ssret=0x%x\n", __LINE__, ssret);
		return ROC_ERR;
	}

	ssret = HI_UNF_DMX_SetDescramblerOddKey(g_VideoDesHandle,pbyOddKey);
	
	if(ssret != HI_SUCCESS)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"(%d):HI_UNF_DMX_SetDescramblerEvenKey Error,ssret=0x%x\n", __LINE__, ssret);
		return ROC_ERR;
	}

	return ROC_OK;
}

/***************************************************************************
����˵����
    ������Ƶ������������

����˵����
    channel_index:ͨ����ʶ��,�����ڶ�ͨ��ƽ̨
    pbyEvenKey:ż��Կ,����Ϊ8�ֽ�
    pbyOddKey: ����Կ,����Ϊ8�ֽ�

��    �أ� 
    0    ----�ɹ�
    -1   ----ʧ��
***************************************************************************/
INT32_T rocme_porting_des_audio_setcw(const INT32_T channel_index, UINT8_T *pbyEvenKey, UINT8_T *pbyOddKey)
{
ROCME_TEST_PRINT
	HI_S32 ssret;
	ssret = HI_UNF_DMX_SetDescramblerEvenKey(g_AudioDesHandle,pbyEvenKey);
	
	if(ssret != HI_SUCCESS)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"(%d):HI_UNF_DMX_SetDescramblerEvenKey Error,ssret=0x%x\n", __LINE__, ssret);
		return ROC_ERR;
	}

	ssret = HI_UNF_DMX_SetDescramblerOddKey(g_AudioDesHandle,pbyOddKey);
	
	if(ssret != HI_SUCCESS)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"(%d):HI_UNF_DMX_SetDescramblerEvenKey Error,ssret=0x%x\n", __LINE__, ssret);
		return ROC_ERR;
	}

	return ROC_OK;
}

	
/**************************************************************************
��������: 
            rocme_porting_av_event_register
����˵��: 
            ע��ײ�����¼���֪ͨ
����˵����
    ���������
            [ av_evt_param ] : ע��������¼��Ĳ���
    ���������
            [ *handler     ] : ���ƴ��¼�ע��ľ��
��    �أ� 
    �ɹ� : 0            ( ע���¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע���¼�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_event_register(const Roc_AV_Evt_Param_t av_evt_param,UINT32_T *handler)
{
ROCME_TEST_PRINT


	HI_UNF_AVPLAY_EVENT_E enHiAvEvent = HI_UNF_AVPLAY_EVENT_BUTT;
	switch(av_evt_param.av_event)
	{
		/* TODO start decoding event */
		case ROC_VID_STOPPED_EVT:
			enHiAvEvent = HI_UNF_AVPLAY_EVENT_STOP;
			memcpy(&s_stAvEvtPara[HI_UNF_AVPLAY_EVENT_STOP], &av_evt_param, sizeof(Roc_AV_Evt_Param_t));
			*handler = HI_UNF_AVPLAY_EVENT_STOP;
			break;
		case ROC_VID_NEW_FRAME_EVT:
			enHiAvEvent = HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME;
			memcpy(&s_stAvEvtPara[HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME], &av_evt_param, sizeof(Roc_AV_Evt_Param_t));
			*handler = HI_UNF_AVPLAY_EVENT_STOP;
			break;
		case ROC_AUD_NEW_FRAME_EVT:
			enHiAvEvent = HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME;
			memcpy(&s_stAvEvtPara[HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME], &av_evt_param, sizeof(Roc_AV_Evt_Param_t));
			*handler = HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME;
			break;
		default:
			return HI_FAILURE;
			
	}

	
	HI_S32 ssret;
	ssret =HI_UNF_AVPLAY_RegisterEvent(g_hAvHandle,enHiAvEvent,(HI_UNF_AVPLAY_EVENT_CB_FN)Rocme_Av_event_Notify);
	if(ssret != HI_SUCCESS)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"HI_UNF_AVPLAY_RegisterEvent Error,ssret=0x%x\n",ssret);
		return ROC_ERR;
	}
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_av_event_unregister
����˵��: 
            ע��һ���ײ�����¼���֪ͨ
����˵����
    ���������
            [ handler     ] : ���ƴ��¼�ע��ľ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ע���¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע���¼�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_event_unregister(const UINT32_T handler)
{
ROCME_TEST_PRINT

	HI_UNF_AVPLAY_UnRegisterEvent(g_hAvHandle,handler);
	return ROC_OK;
}

/**************************************************************************
��������: 
	rocme_porting_dec_iframe
����˵��: 
	����mpeg2-I֡ͼƬ���ڴ�
����˵����
���������
	[ pSrcData     ] : I֡����buffer
	[ nSrcDataLen  ] : I֡���ݳ���
	[ pDataBuf	   ] : λͼ����ָ��(�����������)
	[ ColorType    ] : ����������ɺ󷵻ص�λͼ��ɫ��ʽ
���������
	[ pDataBuf	   ] : λͼ����ָ��(�����������)
	[ pWidth	   ] : λͼ���
	[ pHeight	   ] : λͼ�߶�
��    �أ� 
�ɹ� : 0
ʧ�� : -1 �� ������
�޸ļ�¼��
	��������MPEG2-IFrame�ӿ� [4/30/2010 ��˼��]
**************************************************************************/
INT32_T rocme_porting_dec_iframe(
				 const UINT8_T * pSrcData, 
				 const UINT32_T nSrcDataLen, 
				 UINT8_T *pDataBuf, 
				 UINT32_T *pWidth, 
				 UINT32_T *pHeight,
				 const Roc_Plane_Color_Type_e ColorType
				 )
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_OK;
}

/**************************************************************************
��������: 
	rocme_porting_file_play_start
����˵��: 
	����mpeg��Ƶ��ָ����
����˵����
���������
	[ file_name    ] : ��Ƶ�ļ�·��,����/mnt/adv/rootMedia.mpg
    [ layer        ] : ��ʾ�Ĳ������
�����������
��    �أ� 
�ɹ� : 0
ʧ�� : -1 �� ������
�޸ļ�¼��
	��ʱ���ӽ���MPEG��Ƶ�ӿڣ�Ҫ��ѭ�����Ÿ���Ƶ��ֱ������ rocme_porting_file_play_stop[3/30/2011 BAIGANG]
**************************************************************************/
INT32_T rocme_porting_file_play_start(const CHAR_T *file_name, const Roc_OutPut_Layer_e layer)
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_OK;
}

/**************************************************************************
��������: 
	rocme_porting_file_play_stop
����˵��: 
	ֹͣ����mpeg��Ƶ��ָ����
����˵����
�����������
�����������
��    �أ� 
�ɹ� : 0
ʧ�� : -1 �� ������
�޸ļ�¼��
	��ʱ���ӽ���MPEG��Ƶ�ӿ� [3/30/2011 BAIGANG]
**************************************************************************/
INT32_T rocme_porting_file_play_stop()
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_OK;
}

INT32_T rocme_porting_show_bitmap(UINT32_T  bmWidth,UINT32_T  bmHeight,UINT32_T  bmPitch,UINT8_T *bmBits,const Roc_OutPut_Layer_e layer)
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_OK;
}


