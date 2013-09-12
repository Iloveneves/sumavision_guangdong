/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_avplay.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/21
  Description   :
  History       :
  1.Date        : 2009/12/21
    Author      : w58735
    Modification: Created file

*******************************************************************************/
/** 
 * \file
 * \brief �ṩAVPLAY�������Ϣ
 */
#ifndef __HI_UNF_AVPLAY_H__
#define __HI_UNF_AVPLAY_H__

#include "hi_unf_common.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*********************************error  macro******************************************/
/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_4 */
/** @{ */  /** <!-- ��AVPLAY�� */

/**��Ƶ��������������ȼ�*/
#define HI_UNF_VCODEC_MAX_PRIORITY  16


/**����AV����������Ҫ��BufferIDö������ */
typedef enum hiUNF_AVPLAY_BUFID_E
{
    HI_UNF_AVPLAY_BUF_ID_ES_VID  = 0,    /**<AV������ES��ƵBuffer ID*/
    HI_UNF_AVPLAY_BUF_ID_ES_AUD  = 1,    /**<AV������ES��ƵBuffer ID*/
    HI_UNF_AVPLAY_BUF_ID_BUTT
} HI_UNF_AVPLAY_BUFID_E;

/********************************************************************************/
/**����ý��ͨ������ */
typedef enum hiUNF_AVPLAY_MEDIA_CHAN
{
    HI_UNF_AVPLAY_MEDIA_CHAN_AUD  = 0x01,  /**< ��Ƶͨ�� */
    HI_UNF_AVPLAY_MEDIA_CHAN_VID  = 0x02,  /**< ��Ƶͨ�� */

    HI_UNF_AVPLAY_MEDIA_CHAN_BUTT = 0x8
} HI_UNF_AVPLAY_MEDIA_CHAN_E;


/**���������������ӿ����� */
typedef enum hiUNF_AVPLAY_STREAM_TYPE_E
{
    HI_UNF_AVPLAY_STREAM_TYPE_TS = 0,   /**< ts  stream */
    HI_UNF_AVPLAY_STREAM_TYPE_ES,       /**< es  stream */
	HI_UNF_AVPLAY_STREAM_TYPE_VP,       /**< vp  stream */
    HI_UNF_AVPLAY_STREAM_TYPE_BUTT
} HI_UNF_AVPLAY_STREAM_TYPE_E;

/********************************************************************************/

/**�����������ԵĽṹ�� */
typedef struct hiUNF_AVPLAY_STREAM_ATTR_S
{
    HI_UNF_AVPLAY_STREAM_TYPE_E enStreamType;   /**< �������� */

    HI_U32                      u32VidBufSize;  /**< ��Ƶ�����С */
    HI_U32                      u32AudBufSize;  /**< ��Ƶ�����С */

	HI_UNF_VP_NET_PARA_S        stNetCfgPara;		  /**< �����������������ΪVPʱ��Ч */

} HI_UNF_AVPLAY_STREAM_ATTR_S;

/**֧�ֵ�ͬ������ģʽ */
typedef enum hiUNF_SYNC_REF_E
{
    HI_UNF_SYNC_REF_NONE = 0, /**< ���ɲ���*/
    HI_UNF_SYNC_REF_AUDIO,    /**< ����ƵΪ׼  */
    HI_UNF_SYNC_REF_VIDEO,    /**< ����ƵΪ׼  */
    HI_UNF_SYNC_REF_PCR,      /**< ��PCR��Program Clock Reference��Ϊ׼ */

    HI_UNF_AVPLAY_SYNC_REF_BUTT
} HI_UNF_SYNC_REF_E;


/**����ʹ�õĻ�����״̬ö������ */
typedef enum hiUNF_AVPLAY_BUF_STATE_E
{
    HI_UNF_AVPLAY_BUF_STATE_EMPTY = 0,   /**<����������*/
    HI_UNF_AVPLAY_BUF_STATE_LOW,         /**<������ռ���ʹ���*/
    HI_UNF_AVPLAY_BUF_STATE_NORMAL,      /**<������ʹ������*/
    HI_UNF_AVPLAY_BUF_STATE_HIGH,        /**<������ռ���ʹ���*/
    HI_UNF_AVPLAY_BUF_STATE_FULL         /**<����������*/
}HI_UNF_AVPLAY_BUF_STATE_E;


/**�¼��ص��������� */
typedef enum hiUNF_AVPLAY_EVENT_E
{
    HI_UNF_AVPLAY_EVENT_EOS,                   /**< EOSִ�н���, NULL    */
    HI_UNF_AVPLAY_EVENT_STOP,                  /**< STOPִ�н���, NULL   */
    HI_UNF_AVPLAY_EVENT_RNG_BUF_STATE,         /**< ý�建�����״̬�仯, HI_UNF_AVPLAY_EVENT_RNG_BUF_STATE */
    HI_UNF_AVPLAY_EVENT_NORM_SWITCH,           /**< ��ʽ�л�, HI_UNF_ENC_FMT_E        */
    //HI_UNF_AVPLAY_EVENT_NEW_SEQ,                        /**< ��������Ϣ, HI_UNF_VIDEO_SEQUENCE_INFO_S    */
    HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME,         /**< ����Ƶ֡, HI_UNF_VO_FRAMEINFO_S             */
    HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME,         /**< ����Ƶ֡, HI_UNF_AO_FRAMEINFO_S             */
    HI_UNF_AVPLAY_EVENT_NEW_USER_DATA,         /**< ����Ƶ�û�����, HI_UNF_VIDEO_USERDATA_S     */
    HI_UNF_AVPLAY_EVENT_GET_AUD_ES,            /**< ����ƵES����, HI_UNF_ES_BUF_S     */
    HI_UNF_AVPLAY_EVENT_BUTT
} HI_UNF_AVPLAY_EVENT_E;

/**��������������� */
typedef enum hiUNF_AVPLAY_OVERFLOW_E
{
    HI_UNF_AVPLAY_OVERFLOW_RESET,              /**< ���ʱ���и�λ  */
    HI_UNF_AVPLAY_OVERFLOW_DISCARD,            /**< ���ʱ���ж���  */
    HI_UNF_AVPLAY_OVERFLOW_BUTT
} HI_UNF_AVPLAY_OVERFLOW_E;

/**�����¼��ص�����ö������*/
typedef HI_S32 (*HI_UNF_AVPLAY_EVENT_CB_FN)(HI_HANDLE hAvplay, HI_UNF_AVPLAY_EVENT_E enEvent, HI_U32 u32Para);

/**����AV����������IDö������ */
typedef enum hiUNF_AVPLAY_ATTR_ID_E
{
    HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE = 0,  /**< ����ģʽ , HI_UNF_AVPLAY_ATTR_S */

    HI_UNF_AVPLAY_ATTR_ID_ADEC,             /**< ��Ƶ���� , HI_UNF_ACODEC_ATTR_S */
    HI_UNF_AVPLAY_ATTR_ID_VDEC,             /**< ��Ƶ���� , HI_UNF_VCODEC_ATTR_S  */

    HI_UNF_AVPLAY_ATTR_ID_VDEC_ADV,          /**< �߼���Ƶ���� , HI_UNF_VCODEC_ADV_ATTR_S  */

    HI_UNF_AVPLAY_ATTR_ID_AUD_PID,          /**< ��ƵPID , HI_U32*/
    HI_UNF_AVPLAY_ATTR_ID_VID_PID,          /**< ��ƵPID , HI_U32*/
    HI_UNF_AVPLAY_ATTR_ID_PCR_PID,          /**<PCR PID , HI_U32*/

    HI_UNF_AVPLAY_ATTR_ID_SYNC,             /**< ͬ������ , HI_UNF_SYNC_ATTR_S */
    HI_UNF_AVPLAY_ATTR_ID_AFD,              /**< AFD �Ƿ����� HI_BOOL * */
    HI_UNF_AVPLAY_ATTR_ID_OVERFLOW,         /**< ����������� , HI_UNF_AVPLAY_OVERFLOW_E * */

    HI_UNF_AVPLAY_ATTR_ID_FRMRATE,          /**< FrameRate HI_UNF_VCODEC_FRMRATE_S * */

    HI_UNF_AVPLAY_ATTR_ID_BUTT
} HI_UNF_AVPLAY_ATTR_ID_E;

/*******************************************************************************/
typedef struct hiUNF_SYNC_REGION_S
{
    HI_S32                s32VidPlusTime;        /**< ��Ƶͬ����ǰ��ʱ�䷶Χ */
    HI_S32                s32VidNegativeTime;    /**< ��Ƶͬ������ʱ�䷶Χ */
    HI_BOOL               bSmoothPlay;           /**< ����ʹ�� */
} HI_UNF_SYNC_REGION_S;

/**��������Ƶͬ������ */
typedef struct hiUNF_SYNC_ATTR_S
{
    HI_UNF_SYNC_REF_E     enSyncRef;             /**< ��ƵΪ׼��PCRΪ׼�����ɲ��ŵ� */
    HI_UNF_SYNC_REGION_S  stSyncStartRegion;     /**< ͬ��������� */
    HI_UNF_SYNC_REGION_S  stSyncNovelRegion;     /**< ͬ���쳣���� */
    HI_S32                s32VidPtsAdjust;       /**< ��ƵPTS����*/
    HI_S32                s32AudPtsAdjust;       /**< ��ƵPTS����*/

    HI_U32                u32PreSyncTimeoutMs;   /**< Ԥͬ���ĳ�ʱʱ�䣬��λΪ���� */
    HI_BOOL               bQuickOutput;          /**< �������ʹ�� */
} HI_UNF_SYNC_ATTR_S;


/**����AV�������� */
typedef struct hiUNF_AVPLAY_ATTR_S
{
    HI_U32                       u32DemuxId;   /**<AVPLAY��ʹ�õ�DEMUX ID ������������ΪTSʱ��Ч*/
    HI_UNF_AVPLAY_STREAM_ATTR_S  stStreamAttr; /**< �������� */
} HI_UNF_AVPLAY_ATTR_S;

/********************************************************************************/
/**���岥��������״̬��Ϣ��ͬ��״̬��Ϣ���� */
typedef struct hiUNF_SYNC_STATUS_S
{
    HI_U32 u32FirstAudPts;    /**< ��һ����Ƶ֡ PTS         */
    HI_U32 u32FirstVidPts;    /**< ��һ����Ƶ֡ PTS         */
    HI_U32 u32LastAudPts;     /**<������ŵ�һ����Ƶ֡ PTS */
    HI_U32 u32LastVidPts;     /**< ������ŵ�һ����Ƶ֡ PTS */
    HI_S32 s32DiffAvPlayTime; /**< ����Ƶ ����ʱ��          */
    HI_U32 u32PlayTime;       /**< ��ǰ�Ѳ���ʱ��           */
    HI_U32 u32LocalTime;      /**< ����ͬ���ο�ʱ��         */
} HI_UNF_SYNC_STATUS_S;


/**����ý�建������״̬��Ϣ */
typedef struct hiUNF_AVPLAY_BUF_STATUS_S
{
    HI_U32 u32BufId;         /**< ý�建�� ��ʶ      */
    HI_U32 u32BufSize;       /**< ý�建���С       */
    HI_U32 u32BufRptr;       /*ý�建���ָ��,Ts����ʱ��Ч*/
    HI_U32 u32BufWptr;       /*ý�建��дָ��,Ts����ʱ��Ч*/
    HI_U32 u32UsedSize;      /**<ý�建����ʹ�ô�С */
    HI_U32 u32FrameBufTime;  /**<֡����ʱ�� */
} HI_UNF_AVPLAY_BUF_STATUS_S;


/**����AV�Ĳ���״̬ */
typedef enum hiUNF_AVPLAY_STATUS_E
{
    HI_UNF_AVPLAY_STATUS_STOP = 0, /**< ֹͣ                 */
    HI_UNF_AVPLAY_STATUS_PLAY,     /**< ����                 */
    HI_UNF_AVPLAY_STATUS_TPLAY,    /**<Trick Play, ������� */
    HI_UNF_AVPLAY_STATUS_PAUSE,    /**< ��ͣ                 */
    HI_UNF_AVPLAY_STATUS_EOS,      /**< �������Ž���         */
    HI_UNF_AVPLAY_STATUS_SEEK ,    /**< ��λ����             */

    HI_UNF_AVPLAY_STATUS_BUTT
}HI_UNF_AVPLAY_STATUS_E;


/**����AV����״̬��ѯ���ֵ���� */
typedef struct hiUNF_AVPLAY_STATUS_INFO_S
{
    HI_UNF_SYNC_STATUS_S       stSyncStatus;      /**< ͬ��״̬ */
    HI_UNF_AVPLAY_STATUS_E     enRunStatus;       /**< ����״̬ */
    HI_U32                     u32VidFrameCount;  /**< ��Ƶ�Ѳ���֡�� */
    HI_U32                     u32AuddFrameCount; /**< ��Ƶ�Ѳ���֡�� */
    HI_UNF_AVPLAY_BUF_STATUS_S stBufStatus[HI_UNF_AVPLAY_BUF_ID_BUTT]; /**<ý�建��״̬ */
    HI_U32                     u32VidErrorFrameCount; /**< ��Ƶ�������֡�� */    
} HI_UNF_AVPLAY_STATUS_INFO_S;

/********************************************************************************/
/** ���岥�Ž�Ŀ����ѯ��Ϣ����*/
typedef struct hiUNF_AVPLAY_STREAM_INFO_S
{
    HI_UNF_VCODEC_STREAMINFO_S stVidStreamInfo; /**<��Ƶ����Ϣ */
    HI_UNF_ACODEC_STREAMINFO_S stAudStreamInfo; /**<��Ƶ����Ϣ */
} HI_UNF_AVPLAY_STREAM_INFO_S;

/********************************************************************************/
/**����I֡������Ϣ���� */
typedef struct hiUNF_AVPLAY_I_FRAME_S
{
    HI_U8  *             pu8Addr;    /**<֡�����û�̬�����ַ*/
    HI_U32               u32BufSize; /**<֡���ݴ�С����λ�ֽ�*/
    HI_UNF_VCODEC_TYPE_E enType;     /**<��Ƭ���ݵ�Э������*/
} HI_UNF_AVPLAY_I_FRAME_S;

/********************************************************************************/
/**������������� ��ͬ���͵Ľ�����ռ���ڴ治ͬ*/
typedef enum hiHI_UNF_VCODEC_DEC_TYPE_E
{
    HI_UNF_VCODEC_DEC_TYPE_NORMAL,            /**<��ͨ����*/
    HI_UNF_VCODEC_DEC_TYPE_ISINGLE,           /**<I֡�������� ���avplay������I֡����(HI_UNF_AVPLAY_DecodeIFrame) ����Ϊ�����Ϳ��Խ�ʡ�ڴ�*/
    HI_UNF_VCODEC_DEC_TYPE_BUTT				
}HI_UNF_VCODEC_DEC_TYPE_E;

/**���������֧�ֵ�Э�鼶�� Ӱ��NORMAL���ͽ����������֡����� ֵԽ����Ҫ��֡����ĿԽ��*/
typedef enum hiHI_UNF_VCODEC_PRTCL_LEVEL_E
{
	HI_UNF_VCODEC_PRTCL_LEVEL_MPEG = 0,	 /**<��h264�������Э�� */
	HI_UNF_VCODEC_PRTCL_LEVEL_H264 = 1,  /**<h264Э�������Э�� */    
	HI_UNF_VCODEC_PRTCL_LEVEL_BUTT
}HI_UNF_VCODEC_PRTCL_LEVEL_E;

/**����AV����������Ƶ������ʱ�������ýṹ�� Ӱ����Ƶ������ռ���ڴ��С����������*/
typedef struct hiHI_UNF_AVPLAY_OPEN_OPT_S
{
    HI_UNF_VCODEC_DEC_TYPE_E    enDecType;       /**<����������*/   
    HI_UNF_VCODEC_CAP_LEVEL_E   enCapLevel;      /**<������֧�ֵ����ֱ��� Ӱ��ÿ��֡��Ĵ�С*/
    HI_UNF_VCODEC_PRTCL_LEVEL_E enProtocolLevel; /**<֧�ֵ�Э�鼶�� Ӱ��֡����Ŀ*/
}HI_UNF_AVPLAY_OPEN_OPT_S;


/**����AV������ֹͣʱ��Ƶ��ʾģʽ */
typedef enum hiUNF_AVPLAY_STOP_MODE_E
{
    HI_UNF_AVPLAY_STOP_MODE_STILL = 0,  /**<stop�������һ֡*/
    HI_UNF_AVPLAY_STOP_MODE_BLACK = 1,  /**<stop�����*/
    HI_UNF_AVPLAY_STOP_MODE_BUTT
} HI_UNF_AVPLAY_STOP_MODE_E;

/**����AV����������ʱ�������ýṹ��*/
typedef struct hiAVPLAY_START_OPT_S
{
    HI_U32       u32Reserved;
} HI_UNF_AVPLAY_START_OPT_S;


/**����AV������ֹͣʱ�������ýṹ��*/
typedef struct hiAVPLAY_STOP_OPT_S
{
    /*
      s32Timeout: end of stream timeout
         s32Timeout = 0   �������ȴ��������Ž�������������
         s32Timeout > 0   ������ʱʱ�䣬��λΪ����
         s32Timeout = -1  ���޵ȴ�
     */
    HI_U32                    u32TimeoutMs;    /**<��ʱֵ*/
    HI_UNF_AVPLAY_STOP_MODE_E enMode;          /**<��Ƶ��ʾģʽ*/
} HI_UNF_AVPLAY_STOP_OPT_S;

/* ����AV��������ͣʱ�������ýṹ��*/
typedef struct hiAVPLAY_PAUSE_OPT_S
{
    HI_U32       u32Reserved;
} HI_UNF_AVPLAY_PAUSE_OPT_S;

/**����AV�������������ʱ�������ýṹ��*/
typedef struct hiAVPLAY_TPLAY_OPT_S
{
    HI_U32       u32TplaySpeed;
} HI_UNF_AVPLAY_TPLAY_OPT_S;

/**����AV�������ָ�ʱ�������ýṹ��*/
typedef struct hiAVPLAY_RESUME_OPT_S
{
    HI_U32       u32Reserved;
} HI_UNF_AVPLAY_RESUME_OPT_S;

/**����AV��������λʱ�������ýṹ��*/
typedef struct hiAVPLAY_RESET_OPT_S
{
    HI_U32       u32Reserved;
} HI_UNF_AVPLAY_RESET_OPT_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_3 */
/** @{ */  /** <!-- ��AVPLAY�� */

/**
\brief ��ʼ��AVPLAYģ��
\attention \n
�ڵ���::HI_UNF_AVPLAY_Create�ӿڴ���������֮ǰ�����ñ��ӿ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NOT_EXIST AVPLAY�豸������
\retval ::HI_ERR_AVPLAY_NOT_DEV_FILE  AVPLAY���豸
\retval ::HI_ERR_AVPLAY_DEV_OPEN_ERR  AVPLAY��ʧ��
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Init(HI_VOID);

/**
\brief ȥ��ʼ��AVPLAYģ��
\attention \n
�ڵ���::HI_UNF_AVPLAY_Destroy�ӿ��������еĲ������󣬵��ñ��ӿ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_AVPLAY_DEV_CLOSE_ERR  AVPLAY�ر�ʧ��
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_DeInit(HI_VOID);

/**
\brief ��ȡȱʡ��AV��������
\attention \n
���ñ��ӿ�����enCfg����ʱ������ȷ������Ҫ����������ģʽ\n
����AV������ǰ������ñ��ӿڣ���ȡ��AV������Ĭ�����ԣ����ⴴ��AV������ʱ���ڲ�����ȫ����������²������������ɹ�����
\param[out] pstAvAttr  ָ�����ͣ�AV�������ԣ���μ�::HI_UNF_AVPLAY_ATTR_S
\param[in] enCfg       AV���ŵ����ͣ���μ�::HI_UNF_AVPLAY_STREAM_TYPE_E
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_GetDefaultConfig(HI_UNF_AVPLAY_ATTR_S *pstAvAttr, HI_UNF_AVPLAY_STREAM_TYPE_E enCfg);

/**
\brief ע����Ƶ��̬�����
\attention \n
\param[in] pFileName ��Ƶ������ļ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ʧ��
\retval ::HI_ERR_AVPLAY_NULL_PTR  ����ָ��Ϊ��

\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_RegisterAcodecLib(const HI_CHAR *pFileName);

/**
\brief ����ע����Ƶ��̬�����
\attention \n
\param[in] enDstCodecID ��Ƶ�����CodecID
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ʧ��
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_FoundRegisterDeoder(const HI_U32 enDstCodecID);

/**
\brief ������Ƶ��ʽ, ����ע����Ƶ��̬�����
\attention \n
\param[in] enFormat ��Ƶ��ʽ
\param[out] penDstCodecID �ɹ��򷵻���Ƶ�����CodecID
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ʧ��
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_FoundSupportDeoder(const HA_FORMAT_E enFormat,HI_U32 * penDstCodecID);


/**
\brief ����˽���������Ƶ��̬�����, ����ha_codec ���� 
HI_HA_ERRORTYPE_E (*DecSetConfig)(HI_VOID * hDecoder, HI_VOID * pstConfigStructure);
\attention \n
\param[in] hAvplay         AV���ž��
\param[in] HI_VOID *pPara  ���Խṹ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ʧ��
\retval ::HI_ERR_AVPLAY_NULL_PTR  ����ָ��Ϊ��

\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_ControlAcodec( HI_HANDLE hAvplay, HI_VOID *pPara);

/**
\brief ����AV������
\attention \n
�������Բ���pstAttr���м�����Ҫע�⣺����Դ֧��HI_UNF_AVPLAY_STREAM_TYPE_ES���ڴ�����ES������HI_UNF_AVPLAY_STREAM_TYPE_TS���ڴ�����TS����TUNER����TS ����
\param[in]  pstAvAttr  ָ�����ͣ�AV�������ԣ���μ�::HI_UNF_AVPLAY_ATTR_S
\param[out] phAvplay   ָ�����ͣ�������AV���ž��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_CREATE_ERR       AVPLAY����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Create(const HI_UNF_AVPLAY_ATTR_S *pstAvAttr, HI_HANDLE *phAvplay);

/**
\brief ����AV������
\attention \n
��
\param[in] hAvplay  AV���ž��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Destroy(HI_HANDLE hAvplay);

/**
\brief ����AV��������
\attention \n
���ñ��ӿڿ�ʵ����������ƵPID����������Ƶ�������͡�����ͬ����ʽ�ȹ���\n
��ͬ������ID��Ӧ�Ľṹ����μ��ṹ��HI_UNF_AVPLAY_ATTR_ID_E��"��ע�⡿"��pPara����Ҫ��enAttrID��Ӧ�����Խṹ�����ͱ���һ��\n
����Ҫ����HI_UNF_AVPLAY_ATTR_ID_ADEC����Ƶ�������ԣ���HI_UNF_AVPLAY_ATTR_ID_VDEC����Ƶ�������ԣ�ʱ�\\n
��Ҫ�ȹر���Ƶ����Ƶͨ���������������ԣ�Ȼ�������´���Ƶ����Ƶͨ�������Բſ�����Ч��
\param[in] hAvplay         AV���ž��
\param[in] enAttrID        ����ID
\param[in] HI_VOID *pPara  ����ID��Ӧ�ṹ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_SetAttr(HI_HANDLE hAvplay, HI_UNF_AVPLAY_ATTR_ID_E enAttrID, HI_VOID *pPara);

/**
\brief ��ȡAV��������
\attention \n
��
\param[in] hAvplay          AV���ž��
\param[in] enAttrID         ����ID
\param[in] HI_VOID *pPara   ����ID��Ӧ�ṹ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_GetAttr(HI_HANDLE hAvplay, HI_UNF_AVPLAY_ATTR_ID_E enAttrID, HI_VOID *pPara);

/**
\brief ����I֡����
\attention \n
��pstCapPictureΪ��ָ��ʱ�������I֡����window����ʾ������ǿգ��򲻻���ʾ���ǽ�I֡��Ϣ�ϱ���
���øýӿ�ǰ����ֹͣ��Ƶ��������I֡����û�����ʱ��Ҳ����������Ƶ������
\param[in] hAvplay         AV���ž��
\param[in] pstFrame        ָ�����ͣ�֡��������
\param[in] pstCapPicture   ָ�����ͣ�֡��Ϣ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_DecodeIFrame(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_I_FRAME_S *pstFrame, HI_UNF_CAPTURE_PICTURE_S *pstCapPicture);

/**
\brief ������Ƶ��������ģʽ
\attention \n
���ӿ���ҪӦ���ڱ��ٲ��ŵĳ��������л������ٲ���ǰ���ȵ��ñ��ӿڽ�����������Ϊֻ��I֡��\n
���л�����������ǰ���ȵ��ñ��ӿڽ�����������ΪNORMAL��
\param[in] hAvplay            AV���ž��
\param[in] enDecodeMode       ����ģʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_SetDecodeMode(HI_HANDLE hAvplay, HI_UNF_VCODEC_MODE_E enDecodeMode);

/**
\brief ע���¼�
\attention \n
��
\param[in] hAvplay     AV���ž��
\param[in] enEvent     ö�����ͣ���ʾ�¼�����
\param[in] pfnEventCB  �ص�����ָ�룬ָ����ע���¼���Ӧ�Ļص�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_RegisterEvent(HI_HANDLE      hAvplay,
                                   HI_UNF_AVPLAY_EVENT_E     enEvent,
                                   HI_UNF_AVPLAY_EVENT_CB_FN pfnEventCB);


/**
\brief ȡ��ע���¼�
\attention \n
��
\param[in] hAvplay   AV���ž��
\param[in] enEvent   ö�����ͣ���ʾ�¼�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_UnRegisterEvent(HI_HANDLE hAvplay, HI_UNF_AVPLAY_EVENT_E enEvent);

/**
\brief ��AV������ͨ��
\attention \n
ÿ��AV��������֧�ִ�����Ƶͨ����1�������ֻ������Ƶ����Ƶ��ֻ��Ҫ����Ӧͨ�����Խ�ʡ��Դ��
\param[in] hAvplay  AV���ž��
\param[in] enChn    ����������Ƶͨ������μ�::HI_UNF_AVPLAY_MEDIA_CHAN_E
\param[in] pPara    ָ�����ͣ���μ�::HI_UNF_AVPLAY_OPEN_OPT_S
    enChnΪHI_UNF_AVPLAY_MEDIA_CHAN_VIDʱ����ָ����Ƶ��������������������
    �����ΪNULL����Ĭ��Ϊ�������: H264+HI_UNF_VCODEC_CAP_LEVEL_FULLHD��
    ����֧�ֵ�����Խ����Ҫ��MMZ�����ڴ�Ҳ��Խ�󣬽��鰴�����ü��ɡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_ChnOpen(HI_HANDLE hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_E enChn, const HI_VOID *pPara);

/**
\brief �ر�AV������ͨ��
\attention \n
��
\param[in] hAvplay   AV���ž��
\param[in] enChn     ����������Ƶͨ������μ�::HI_UNF_AVPLAY_MEDIA_CHAN_E
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_ChnClose(HI_HANDLE hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_E enChn);

/**
\brief ����������������PLAY״̬
\attention \n
�����ͨ���򿪺��������ú󣬵��ñ��ӿ��������ţ�����PLAY״̬��֧�ֱַ��ͬʱ��������Ƶ���š�
\param[in] hAvplay        AV���ž��
\param[in] enChn          ����������Ƶͨ������μ�::HI_UNF_AVPLAY_MEDIA_CHAN_E
\param[in] pstStartOpt    ָ�����ͣ�����չʹ�ã���ΪNULL����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Start(HI_HANDLE hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_E enChn, const HI_UNF_AVPLAY_START_OPT_S *pstStartOpt);

/**
\brief ֹͣAV���ţ�����STOP״̬
\attention \n
���ñ��ӿڽ�ֹͣ��ѡͨ���Ĳ��ţ�֧�ֱַ��ͬʱֹͣ����Ƶ���š�\n
����ѡͨ���а�����Ƶͨ��ʱ������pstStopOpt->enMode�������塣\n
��pstStopOpt->enModeΪ�ջ���ΪHI_UNF_AVPLAY_STOP_MODE_STILLʱ���������һ֡��Ƶͼ��\n
��pstStopOpt->enModeΪHI_UNF_AVPLAY_STOP_MODE_BLACKʱ�������Ƶ���һ֡����Ƶ���Ϊ������\n
��pstStopOpt->u32TimeoutMsΪ0ʱ���뿪ֹͣ���Ų����ء�\n
��pstStopOpt->u32TimeoutMs>0ʱ��������Ӧʱ�䣬ֱ�������е����ݲ��ꡣ\n
��pstStopOpt->u32TimeoutMs=-1ʱ��һֱ�����������е����ݲ��ꡣ\n
������Ƶ�����ڿ���״̬ʱ,Ҫ����ֹͣ��Ƶ����Ƶ����������pstStopOpt->u32TimeoutMsΪ0
\param[in] hAvplay      AV���ž��
\param[in] enChn        ����������Ƶͨ������μ�::HI_UNF_AVPLAY_MEDIA_CHAN_E
\param[in] pstStopOpt   ָ�����ͣ�����ģʽ����μ�::HI_UNF_AVPLAY_STOP_OPT_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Stop(HI_HANDLE hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_E enChn, const HI_UNF_AVPLAY_STOP_OPT_S *pstStopOpt);

/**
\brief ��ͣAV���ţ�����PAUSE״̬
\attention \n
��
\param[in] hAvplay      AV���ž��
\param[in] pstPauseOpt  ָ�����ͣ�����չʹ�ã���ΪΪNULL����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Pause(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_PAUSE_OPT_S *pstPauseOpt);

/**
\brief ���ٲ��ţ�����TPLAY״̬
\attention \n
��
\param[in] hAvplay       AV���ž��
\param[in] pstTplayOpt   ָ�����ͣ�����չʹ�ã���ΪΪNULL����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Tplay(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_TPLAY_OPT_S *pstTplayOpt);

/**
\brief �ָ�AV���ţ�����PLAY״̬
\attention \n
���ӿ����������ٻ���ͣ״̬�ָ�Ϊ����״̬�����޷���ֹͣ״̬�ָ�Ϊ����״̬��
\param[in] hAvplay  AV���ž��
\param[in] pOption  ָ�����ͣ�����չʹ�ã�����Ϊ�ռ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Resume(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_RESUME_OPT_S *pstResumeOpt);

/**
\brief ��λAV���ţ����ı�״̬
\attention \n
��
\param[in] hAvplay       AV���ž��
\param[in] pstResetOpt   ָ�����ͣ�����չʹ�ã���ΪΪNULL����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_Reset(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_RESET_OPT_S *pstResetOpt);

/**
\brief ����AV���ŵ���������
\attention \n
����������򱾵�ES��ʱ����Ҫʹ�ñ��ӿڡ�\n
����pstData�������سɹ����뵽��Buffer���׵�ַ�Լ���С��\n
u32TimeOutMs����Ϊ0��ʾ���ȴ�������Ϊ0xffffffff��ʾһֱ�ȴ�������Ϊ����ֵ��ʾ�ȴ�u32TimeOutMs���롣\n
����������ʱ�䣬���޷����뵽Buffer���򷵻�buffer��������\n
u32TimeOutMs����Ϊ0ʱ��������벻��Buffer��˵����ʱ����Ƶ��Buffer��������Ҫͨ��usleep(N*1000)�ͷ�cpu
��ʹ�����߳��ܹ��õ����ȡ�
\param[in] hAvplay     AV���ž��
\param[in] enBufId     �������ID
\param[in] u32ReqLen   ���뻺��Ĵ�С
\param[out] pstData    ���ػ���ָ��
\param[in] u32TimeOutMs      �ȴ���ʱʱ�䣬��λms
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
��
*/
HI_S32 HI_UNF_AVPLAY_GetBuf(HI_HANDLE  hAvplay,
                            HI_UNF_AVPLAY_BUFID_E enBufId,
                            HI_U32                u32ReqLen,
                            HI_UNF_STREAM_BUF_S  *pstData,
                            HI_U32                u32TimeOutMs);

/**
\brief �������ݳɹ��󣬸���дָ��
\attention \n
�������뵽�Ļ���������������Ϻ󣬵��ñ��ӿڸ�������Ƶ��������дָ�롣\n
����������������û�ж�Ӧ��PTS��u32ptsMs����Ϊ-1��
\param[in] hAvplay             AV���ž��
\param[in] enBufId             �������ID
\param[in] u32ValidDataLen     ʵ��д�뻺�������ֽ���
\param[in] u32ptsMs            ʱ���,�Ժ���Ϊ��λ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_PutBuf(HI_HANDLE hAvplay, HI_UNF_AVPLAY_BUFID_E enBufId,
                         HI_U32 u32ValidDataLen, HI_U32 u32PtsMs);


/**
\brief �������ŵ��ٶ�
\attention \n
�������ŵ��ٶȡ�1����������2����2��֮1�ٶȡ����Ҫ�����Żָ�����������,�Ե��øýӿڣ�u32Repeat����Ϊ1
\param[in] hAvplay             AV���ž��
\param[in] u32Repeat           �����ٶ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_SetWindowRepeat(HI_HANDLE hAvplay, HI_U32 u32Repeat);


/**
\brief TSģʽʱ��ȡAV������ʹ�õ�DMX��Ƶͨ����Handle
\attention \n
��
\param[in] hAvplay        AV���ž��
\param[in] phDmxAudChn    DMX��Ƶͨ��Handleָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_GetDmxAudChnHandle(HI_HANDLE hAvplay, HI_HANDLE *phDmxAudChn);

/**
\brief TSģʽʱ��ȡAV������ʹ�õ�DMX��Ƶͨ����Handle
\attention \n
��
\param[in] hAvplay        AV���ž��
\param[in] phDmxAudChn    DMX��Ƶͨ��Handleָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_GetDmxVidChnHandle(HI_HANDLE hAvplay, HI_HANDLE *phDmxVidChn);


/**
\brief ��ȡAV����״̬��Ϣ
\attention \n
�ṹ��pstStatusInfo�в���stSyncStatus��ʾ��ȡ�ĵ�ǰͬ��״̬����������֧�������Ļ�ȵ�ͬ����\n
enRunStatus��ʾ��ȡ��AV����������״̬��\n
u32VidFrameCount��u32AuddFrameCount������ʾ��ǰ����Ƶ�Ѳ��ŵ�֡����\n
�����ESģʽ������ͨ��stBufStatus��ѯ����ƵBuffer��״̬��
\param[in] hAvplay         AV���ž��
\param[out] pstStatusInfo  ָ�����ͣ�AV����״̬��Ϣ����μ�HI_UNF_AVPLAY_STATUS_INFO_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_GetStatusInfo(HI_HANDLE          hAvplay,
                                 HI_UNF_AVPLAY_STATUS_INFO_S *pstStatusInfo);


/**
\brief ��ȡ����Ƶ������Ϣ
\attention \n
��
\param[in] hAvplay           AV���ž��
\param[in] pstStreamInfo     ָ�����ͣ�����Ƶ������Ϣ����μ�HI_UNF_AVPLAY_STREAM_INFO_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_GetStreamInfo(HI_HANDLE          hAvplay,
                                   HI_UNF_AVPLAY_STREAM_INFO_S *pstStreamInfo);

/**
\brief ��ȡ��Ƶ������Ϣ
\attention \n
��
\param[in] hAvplay        AV���ž��
\param[in] pSpectrum      ָ�����ͣ���Ƶ������Ϣ����ָ��
\param[in] u32BandNum     ��Ƶ������Ϣ���鳤��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\retval ::HI_ERR_AVPLAY_INVALID_OPT      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_GetAudioSpectrum(HI_HANDLE hAvplay, HI_U16 *pSpectrum, HI_U32 u32BandNum);

/**
\brief ��ѯAVPLAY buffer�Ƿ��Ѿ�Ϊ��
\attention \n
��
\param[in] hAvplay        AV���ž��
\param[out] pbIsEmpty      ָ�����ͣ�ָʾbuffer�Ƿ��Ѿ�Ϊ��(�������)
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAYδ��ʼ��
\retval ::HI_ERR_AVPLAY_NULL_PTR         ����ָ��Ϊ��
\retval ::HI_ERR_AVPLAY_INVALID_PARA     ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_AVPLAY_IsBuffEmpty(HI_HANDLE hAvplay, HI_BOOL * pbIsEmpty);



/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
