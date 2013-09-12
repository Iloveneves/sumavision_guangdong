/******************************************************************************
  Copyright (C), 2004-2050, Hisilicon Tech. Co., Ltd.
******************************************************************************
  File Name     : hi_unf_vo.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/1/22
  Last Modified :
  Description   : header file for audio and video output control
  Function List :
  History       :
  1.Date        :
  Author        : z67193
  Modification  : Created file
******************************************************************************/
/** 
 * \file
 * \brief �ṩSOUND�������Ϣ
 */
 
#ifndef  __HI_UNF_SND_H__
#define  __HI_UNF_SND_H__

#include "hi_unf_common.h"
//#include "hi_debug.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_6 */
/** @{ */  /** <!-- ��SOUND�� */

/**������Ƶ����豸��*/
typedef enum hiUNF_SND_E
{
    HI_UNF_SND_0,           /**<��Ƶ����豸0 */
    HI_UNF_SND_BUTT    
} HI_UNF_SND_E;


/**������Ƶ����ӿ�����*/
typedef enum hiUNF_SND_INTERFACE_E
{
    HI_UNF_SND_INTERFACE_I2S,      /**<I2S��Inter-IC Sound��ģʽ */
    HI_UNF_SND_INTERFACE_SPDIF,    /**<SPDIF��Sony/Philips Digital Interface��ģʽ */
    HI_UNF_SND_INTERFACE_HBR,    /**<SPDIF��Sony/Philips Digital Interface��ģʽ */
    HI_UNF_SND_INTERFACE_BUTT
}HI_UNF_SND_INTERFACE_E;


/**��Ƶ�������� */
typedef enum hiHI_UNF_SND_MIX_TYPE_E
{
    HI_UNF_SND_MIX_TYPE_MASTER,     /**<��Ϊ���� */
    HI_UNF_SND_MIX_TYPE_SLAVE,      /**<��Ϊ���� */
    HI_UNF_SND_MIX_TYPE_BUTT 
} HI_UNF_SND_MIX_TYPE_E;


/**������Ƶ���ģʽ�ṹ��*/
typedef struct hiUNF_SND_INTERFACE_S
{
    HI_UNF_SND_INTERFACE_E  enInterface;     /**<��Ƶ�ӿ�������� */
    HI_BOOL                 bEnable;         /**<�Ƿ�ʹ����Ƶ��� */
}HI_UNF_SND_INTERFACE_S;

/**������Ƶ������Խṹ��*/
typedef struct hiHI_UNF_SND_ATTR_S
{

    HI_U32              u32MasterOutputBufSize; /**<�����طŻ������ռ��С. unit:byte, note: size must 64 time word8 */
    HI_U32              u32SlaveOutputBufSize; /**<�����طŻ������ռ��С. unit:byte, note: size must 64 time word8 */
    HI_BOOL            bMixerEngineSupport;   /**< if bMixerEngineSupport == HI_TRUE,  UNF_SND support MixerEngine,slave pcm is repalced by one mixer of the MixerEngine,
    									  if bMixerEngineSupport == HI_FALSE, UNF_SND dont support MixerEngine default: HI_FALSE
    									  */  
} HI_UNF_SND_ATTR_S;

/**Audio Mixer attribute                                               			*/
typedef struct hiHI_UNF_MIXER_ATTR_S
{
    HI_U32              u32MixerWeight;    /**< ����Ȩ��: 0~100 */
    HI_U32              u32MixerBufSize;   /**< ��������������С(1024*16) ~ (1024*1024), unit:byte */
} HI_UNF_MIXER_ATTR_S;

typedef struct hiHI_UNF_MIXER_STATUSINFO_S
{
    HI_S32 u32MixerID;   /**< ������Ӳ��ID : ��Χ0~7 */
    HI_S32 u32Working;   /**< ����������״̬: 0 : stop, 1: pause, 2:running */

    HI_U32 u32BufferSize;           /**< ��������������Сunit: byte.*/
    HI_U32 u32BufferByteLeft;      /**< ��������������Ƶ����ʣ�� unit : byte.*/
    HI_BOOL bDataNotEnough;      /**< HI_FALSE : data is enough, HI_TRUE: data is not enough,need more data */
    HI_U32  u32BufDurationMs;    /**< ������������ʣ����Ƶ���ݿɲ���ʱ��  unit : MS.*/

} HI_UNF_MIXER_STATUSINFO_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_4 */
/** @{ */  /** <!-- ��SOUND�� */

/** 
\brief ��ʼ����Ƶ����豸
\attention \n
����SNDģ��Ҫ�����ȵ��øýӿ�
\param ��
\retval HI_SUCCESS �ɹ�
\see \n
��
*/
HI_S32 HI_UNF_SND_Init(HI_VOID);


/** 
\brief ȥ��ʼ����Ƶ����豸
\attention \n
��
\param ��
\retval HI_SUCCESS �ɹ�
\see \n
��
*/
HI_S32 HI_UNF_SND_DeInit(HI_VOID);

/** 
\brief ������Ƶ����豸, 
\attention \n
 ������HI_UNF_SND_Open ǰ���ã�������Ĭ�Ϸ�ʽ����Ƶ�豸
\param[in] enSound     ��Ƶ����豸��
\param[in] pstAttr     ��Ƶ��������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetOpenAttr(HI_UNF_SND_E enSound,HI_UNF_SND_ATTR_S *pstAttr);

/** 
\brief ��ȡ��Ƶ����豸���ò���
\attention \n
\param[in] enSound     ��Ƶ����豸��
\param[out] pstAttr     ��Ƶ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetOpenAttr(HI_UNF_SND_E enSound, HI_UNF_SND_ATTR_S *pstAttr);

/** 
\brief ����Ƶ����豸
\attention \n
��
\param[in] enSound     ��Ƶ����豸��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_CREATE_FAIL	    ���豸ʧ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_Open(HI_UNF_SND_E enSound);


/** 
\brief ������Ƶ���Soundʵ��
\attention \n
��֧���ظ�����
\param[in] enSound   ��Ƶ����豸��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_INVALID_PARA	��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_Close(HI_UNF_SND_E enSound);

/** 
\brief ������Ƶ����˿�ʹ�ܿ���
\attention \n
���Էֱ����ģ��I2S�����SPDIF���
\param[in] enSound        ��Ƶ����豸��
\param[in] pInterface    ָ�����ͣ���Ƶ���ģʽ�ṹ�壬��μ�::HI_UNF_SND_INTERFACE_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN       Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetInterface(HI_UNF_SND_E enSound, const HI_UNF_SND_INTERFACE_S *pInterface);


/** 
\brief ��ȡ��Ƶ����˿�ʹ��״̬
\attention \n
�ڶ��������нṹ��ĵ�һ��������enInterface��Ϊ����������ڶ���������bEnable��Ϊ�������
\param[in] enSound           ��Ƶ����豸��
\param[in/out] pInterface   ָ�����͡���Ƶ���ģʽ�ṹ�壬��μ�::HI_UNF_SND_INTERFACE_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetInterface(HI_UNF_SND_E enSound, HI_UNF_SND_INTERFACE_S *pInterface);


/** 
\brief ��Ƶģ������ľ�����������
\attention \n
��
\param[in] enSound   ��Ƶ����豸��
\param[in] bMute    ģ������������ء�HI_TRUE��������HI_FALSE���Ǿ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN       Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetAnalogMute(HI_UNF_SND_E enSound, HI_BOOL bMute);


/** 
\brief ��ȡ��Ƶģ������ľ�������״̬
\attention \n
��
\param[in] enSound     ��Ƶ����豸��
\param[out] pbMute    ָ�����͡�HI_TRUE��������HI_FALSE���Ǿ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetAnalogMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);


/** 
\brief ��Ƶ��������ľ�����������
\attention \n
��
\param[in] enSound   ��Ƶ����豸��
\param[in] bMute    ��������������ء�HI_TRUE��������HI_FALSE���Ǿ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetDigitalMute(HI_UNF_SND_E enSound, HI_BOOL bMute);


/** 
\brief ��ȡ��Ƶ��������ľ�������״̬
\attention \n
��
\param[in] enSound   ��Ƶ����豸��
\param[out] pbMute  ָ�����͡�HI_TRUE��������HI_FALSE���Ǿ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN       Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetDigitalMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);


/** 
\brief ��Ƶ���ֺ�ģ������ľ�����������
\attention \n
\param[in] enSound
\param[in] bMute
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetMute(HI_UNF_SND_E enSound, HI_BOOL bMute);


/** 
\brief ��ȡ��Ƶ���ֺ�ģ������ľ�������״̬
\attention \n
\param[in] enSound
\param[in] pbMute
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);

/** 
\brief ��Ƶģ�������DAC������������
\attention \n
����ģ���������������HDMI��������ĳ�����һ������²���Ҫʹ��
\param[in] enSound   ��Ƶ����豸��
\param[in] bMute    DAC�������ء�HI_TRUE��������HI_FALSE���Ǿ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetADACMute(HI_UNF_SND_E enSound, HI_BOOL bMute);


/** 
\brief ��ȡ��Ƶģ�������DAC�ľ�������״̬
\attention \n
��
\param[in] enSound   ��Ƶ����豸��
\param[out] pbMute  ָ�����͡�HI_TRUE��������HI_FALSE���Ǿ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN       Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetADACMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);

/** 
\brief ����SPDIF ��Ƶ�������
\attention \n
ʹ�øýӿ�ʱ����Ƶ����ģʽ�����趨Ϊ:HD_DEC_MODE_SIMUL(PCM + ͸������ģʽ)
ͬʱ������SPDIF�ӿڣ��������ʲô���ݣ�����ʹ��INTERFACE_SPDIF
\param[in] enSound   ��Ƶ����豸��
\param[in] bEnable   ͸������������ء�HI_TRUE�����͸�����ݣ�HI_FALSE�����PCM����
\retval ::HI_SUCCESS �ɹ�
\see \n
��
*/
HI_S32 HI_UNF_SND_SetSpdifPassThrough(HI_UNF_SND_E enSound, HI_BOOL bEnable);

/** 
\brief set HDMI pass-torough
\attention \n
sure audio decoder work at HD_DEC_MODE_SIMUL mode
\param[in] enSound  
\param[in] bEnable , HI_TRUE: pass-torough enable HI_FALSE:  pass-torough disable
\retval ::HI_SUCCESS �ɹ�
\see \n
��
*/
HI_S32 HI_UNF_SND_SetHdmiPassThrough(HI_UNF_SND_E enSound, HI_BOOL bEnable);


/** 
\brief �����������
\attention \n
���u32Volume���ô���100��Ĭ�����õ�ֵΪ100
\param[in] enSound        ��Ƶ����豸��
\param[in] u32Volume     ���õ�����ֵ����Χ0��100��0��������100���������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetVolume(HI_UNF_SND_E enSound, HI_U32 u32Volume);


/** 
\brief ��ȡ�������
\attention \n
��ѯ��Ĭ������ֵΪ100
\param[in] enSound         ��Ƶ����豸��
\param[out] pu32Volume    ָ�����ͣ���ȡ��������ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetVolume(HI_UNF_SND_E enSound, HI_U32 *pu32Volume);


/** 
\brief ������Ƶ���ʱ�Ĳ�����
\attention \n
Ŀǰ�ݲ�֧�ֲ��������ã���������ʹ̶�Ϊ48k����48k�����������ز���Ϊ48k���
\param[in] enSound          ��Ƶ����豸��
\param[in] enSampleRate    ��Ƶ�����ʡ���μ�::HI_UNF_SAMPLE_RATE_E
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetSampleRate(HI_UNF_SND_E enSound, HI_UNF_SAMPLE_RATE_E enSampleRate);


/** 
\brief ��ȡ��Ƶ���ʱ�Ĳ�����
\attention \n
�˽ӿ�Ĭ�Ϸ���48kHz������
\param[in] enSound           ��Ƶ����豸��
\param[out] penSampleRate   ָ�����ͣ���Ƶ�����ʵ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetSampleRate(HI_UNF_SND_E enSound, HI_UNF_SAMPLE_RATE_E *penSampleRate);


/** 
\brief ��Ƶ����Զ������ز�����������
\attention \n
Ĭ���Ѿ����ز�����������ر�\n
Ŀǰ��֧��Դ������Ϊ8kHz��16kHz��22.05kHz��24kHz��32kHz��44.1kHz��48kHz��Ĭ����48kHz���\n
���ͨ�����ӿ�����bAutoResampleΪHI_TRUE����˽ӿڽ�ֱ�ӷ��سɹ�\n
���ͨ�����ӿ�����bAutoResampleΪHI_FALSE����˽ӿڽ�ֱ�ӷ���HI_UNF_ERR_SND_NOTSUPPORT������
\param[in] enSound            ��Ƶ����豸��
\param[in] bAutoResample     �Ƿ��Զ��ز�����HI_TRUE�������Զ��ز�����HI_FALSE���������Զ��ز���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetAutoResample(HI_UNF_SND_E enSound, HI_BOOL bAutoResample);


/** 
\brief ��ȡ��Ƶ����Զ��ز�������״̬
\attention \n
��
\param[in] enSound              ��Ƶ����豸��
\param[out] pbAutoResample     ָ�����ͣ��Ƿ��Զ��ز���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetAutoResample(HI_UNF_SND_E enSound, HI_BOOL *pbAutoResample);

/** 
\brief ��Ƶ���������������������������
\attention \n
1. Ĭ�Ϲرո���������\n
2. ������������������Ч\n
3. �������������л���Ŀʱ����
\param[in] enSound        ��Ƶ����豸��
\param[in] bSmartVolume     �Ƿ������������HI_TRUE���򿪣�HI_FALSE���ر�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetSmartVolume(HI_UNF_SND_E enSound, HI_BOOL bSmartVolume);

/** 
\brief ��ȡ��Ƶ���������������״̬\attention \n
\param[in] enSound        ��Ƶ����豸��
\param[out] pbSmartVolume     ָ�����ͣ��Ƿ����������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetSmartVolume(HI_UNF_SND_E enSound, HI_BOOL *pbSmartVolume);


/** 
\brief ������Ƶ�������ģʽ
\attention \n
��
\param[in] enSound     ��Ƶ����豸��
\param[in] enMode     ��Ƶ����ģʽ����μ�::HI_UNF_TRACK_MODE_E
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetTrackMode(HI_UNF_SND_E enSound, HI_UNF_TRACK_MODE_E enMode);


/** 
\brief ��ȡ��Ƶ�������ģʽ
\attention \n
��
\param[in] enSound     ��Ƶ����豸��
\param[out] penMode   ָ�����ͣ���Ƶ����ģʽ����μ�::HI_UNF_TRACK_MODE_E
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR           ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	    ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetTrackMode(HI_UNF_SND_E enSound, HI_UNF_TRACK_MODE_E *penMode);


/** 
\brief ����Ƶ���Sound��AV��Audio Video��������
\attention \n
���ô˽ӿ�ǰ�����ȴ�������������Ӧ��·������û�����
\param[in] enSound          ��Ƶ����豸��
\param[in] hSource         
\param[in] enMixType       AV����������ʵ�����
\param[in] u32MixWeight    Ȩ�أ���ΧΪ0��100��0����Сֵ��100�����ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PORT	        ��Ч������
\retval ::HI_ERR_HIAO_INVALID_PARA	        ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_Attach(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_UNF_SND_MIX_TYPE_E enMixType, HI_U32 u32MixWeight);


/** 
\brief ���Sound��AV��������
\attention \n
��
\param[in] enSound     ��Ƶ����豸��
\param[in] hSource    AV����������ʵ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	        ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_Detach(HI_UNF_SND_E enSound, HI_HANDLE hSource);


/** 
\brief ������Ƶ����������Ȩ��
\attention \n
������������������ļ��㷽��Ϊ�������õ�����%Ȩ��1+���õ�����%Ȩ��2��/100������������ļ��㷽���������
\param[in] enSound              ��Ƶ����豸��
\param[in] hSource             AV����������ʵ�����
\param[in] u32MixWeight        Ȩ�أ���ΧΪ0��100��0����Сֵ��100�����ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	        ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetMixWeight(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_U32 u32MixWeight);


/** 
\brief ��ȡ��Ƶ����������Ȩ��
\attention \n

\param[in] enSound            ��Ƶ����豸��
\param[in] hSource           AV����������ʵ�����
\param[in] pu32MixWeight     ָ�����ͣ�Ȩ��ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR               ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	        ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetMixWeight(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_U32 *pu32MixWeight);

/** 
\brief ������Ƶ���������뵭��ʱ��
\attention \n
\param[in] enSound             ��Ƶ����豸��
\param[in] hSource             AV����������ʵ�����
\param[in] u32FadeinMs         ����ʱ�䣬��λΪ���룬���ȡֵ2000
\param[in] u32FadeoutMs        ����ʱ�䣬��λΪ���룬���ȡֵ500
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio�豸δ��
\retval ::HI_ERR_HIAO_INVALID_PARA	        ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_SetFadeTime(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_U32 u32FadeinMs, HI_U32 u32FadeoutMs);

/** 
\brief ��ȡ��Ƶ���������뵭��ʱ��
\attention \n
\param[in] enSound           ��Ƶ����豸��
\param[in] hSource           AV����������ʵ�����
\param[in] pu32FadeinMs      ָ�����ͣ�����ʱ��
\param[in] pu32FadeoutMs     ָ�����ͣ�����ʱ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio�豸δ��
\retval ::HI_ERR_HIAO_NULL_PTR               ָ�����Ϊ��
\retval ::HI_ERR_HIAO_INVALID_PARA	        ��Ч�Ĳ���
\see \n
��
*/
HI_S32 HI_UNF_SND_GetFadeTime(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_U32 *pu32FadeinMs, HI_U32 *pu32FadeoutMs);

/** 
\brief ��һ��������
\attention \n
ֻ��HI_UNF_SND_Open �ɹ��󣬲��ܲ��������豸
\param[in] enSound   ��Ƶ����豸��
\param[out] phMixer   ָ�����ͣ������Ļ����� ���
\param[in] pstMixerAttr    ָ�����ͣ�����������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_SND_INVALID_ID	��Ч�Ĳ���
\retval ::HI_ERR_SND_INVALID_PARA	��Ч�Ĳ���
\see \n
��
*/
HI_S32   HI_UNF_SND_Mixer_Open(HI_UNF_SND_E enSound,HI_HANDLE *phMixer, HI_UNF_MIXER_ATTR_S *pstMixerAttr);

/** 
\brief �ر� һ��������
\attention \n
��
\param[in] hMixer   ���������
\retval ::HI_SUCCESS �ɹ�
\see \n
��
*/
HI_S32   HI_UNF_SND_Mixer_Close(HI_HANDLE hMixer);

/** 
\brief ����������
\attention \n
��
\param[in] hMixer   ���������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_SND_INVALID_PARA	��Ч�Ĳ���
\see \n
��
*/
HI_S32   HI_UNF_SND_Mixer_Start(HI_HANDLE hMixer);

/** 
\brief ֹͣ������
\attention \n
���������ݽ��ᶪ��
\param[in] hMixer   ���������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_SND_INVALID_PARA	��Ч�Ĳ���
\see \n
��
*/
HI_S32   HI_UNF_SND_Mixer_Stop(HI_HANDLE hMixer);

/** 
\brief ��ͣ������
\attention \n
������������Ȼ����
\param[in] hMixer   ���������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_SND_INVALID_PARA	��Ч�Ĳ���
\see \n
��
*/
HI_S32   HI_UNF_SND_Mixer_Pause(HI_HANDLE hMixer);

/** 
\brief  ������״̬��λ
\attention \n
��
\param[in] hMixer   ���������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_SND_INVALID_PARA	��Ч�Ĳ���
\see \n
��
*/
HI_S32   HI_UNF_SND_Mixer_Flush(HI_HANDLE hMixer);

/** 
\brief  ��ȡ������״̬��Ϣ
\attention \n
��
\param[in] hMixer   ���������
\param[out] pstStatus   ���������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_SND_NULL_PTR	��Ч�Ĳ���
\retval ::HI_ERR_SND_INVALID_PARA	��Ч�Ĳ���
\see \n
��
*/
HI_S32   HI_UNF_SND_Mixer_GetStatus(HI_HANDLE hMixer, HI_UNF_MIXER_STATUSINFO_S *pstStatus);

/** 
\brief  �����ݵ�������
\attention \n
1 �������HI_ERR_HIAO_OUT_BUF_FULL����Ҫ�����߼������ϴ�ʧ�����ݣ����ܱ�֤����������
2 PCM ���ݸ�ʽ�ڻ���������������
    s32BitPerSample: ����Ϊ16
    bInterleaved: ����ΪHI_TRUE, ��֧�ֽ�֯ģʽ
    u32Channels: 1 ��2
    u32PtsMs: ���Ըò���
    ps32PcmBuffer: PCM ����ָ��
    ps32BitsBuffer: ���Ըò���
    u32PcmSamplesPerFrame: ��Ƶ������, ���ݳ���(unit:Bytes): u32PcmSamplesPerFrame*u32Channels*sizeof(HI_u16)
    u32BitsBytesPerFrame: ���Ըò���
    u32FrameIndex: ���Ըò���
\param[in] hMixer   ���������
\param[out] pstAOFrame   ��Ƶ������Ϣ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_SND_NULL_PTR	��Ч�Ĳ���
\retval ::HI_ERR_SND_INVALID_PARA	��Ч�Ĳ���
\retval ::HI_ERR_HIAO_OUT_BUF_FULL,������������������������ʧ��
\see \n
��
*/

HI_S32	 HI_UNF_SND_Mixer_SendData(HI_HANDLE hMixer, const HI_UNF_AO_FRAMEINFO_S *pstAOFrame);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif  /*__HI_UNF_SND_H__*/

