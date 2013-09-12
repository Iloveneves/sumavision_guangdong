/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_voip.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/11/16
  Description   :
  History       :
  1.Date        : 2010/11/16
    Author      :
    Modification: Created file

 *******************************************************************************/

/**
 * \file
 * \brief �ṩVOIP��������������Ϣ
 */
#ifndef __HI_UNF_VOIP_H__
#define __HI_UNF_VOIP_H__
#include "hi_common.h"
#include "hi_error_voip.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/**����VOIP ͨ������ģʽ���� */
typedef enum hiUNF_VOIP_WORKMODE_E
{
    HI_UNF_VOIP_MODE_DTMF  = 0x00,  /**< DTMF�պ�ģʽ������ */
    HI_UNF_VOIP_MODE_VOIVE = 0x01,  /**<  ����ģʽ */
    HI_UNF_VOIP_MODE_FAX   = 0x02, /**<  ����ģʽ ������*/
    HI_UNF_VOIP_MODE_MODEM = 0x03,  /**< Modem ģʽ������*/
    HI_UNF_VOIP_MODE_BUTT = 0x4
} HI_UNF_VOIP_WORKMODE_E;

/**����VOIP ͨ���¼��ϱ����� */
typedef enum hiUNF_VOIP_EVENT_E
{
    HI_UNF_VOIP_CH_EVENT_FAULT,               /**< ͨ������*/
    HI_UNF_VOIP_CH_EVENT_NORMAL,              /**< ͨ���ָ��������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_OPEN_FAILED,         /**< ��ͨ��ʧ�ܣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_CLOSE_FAILED,        /**< �ر�ͨ��ʧ�ܣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_LOCAL_PLAY_END,      /**< LOCAL PLAY����*/
    HI_UNF_VOIP_CH_EVENT_REMOTE_PLAY_END,     /**< REMOTE PLAY����*/
    HI_UNF_VOIP_CH_EVENT_FAX_START,           /**< ���濪ʼ���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_FAX_END,             /**< ����������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_MODEM_START,         /**< MODEM��ʼ���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_MODEM_END,           /**< MODEM�������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_DETECT_DTMF,         /**< DTMF���*/
    HI_UNF_VOIP_CH_EVENT_DETECT_FSK,          /**< FSK��⣬�ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_DETECT_BUSY_TONE,    /**< æ����⣬�ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_RTCP_ALARM,          /**< RTCP�澯���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_GENCALLID_FAILED,    /**< ������ʾʧ�ܣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_STOPCALLID_FAILED,   /**< ͣ������ʾʧ�ܣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_DATA_TONE,           /**< CNG, V8, V25����ź������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_REMOTE_FAX_START,    /**< оƬ��⵽�Զ˷�����T38���ģ���T38 */
    HI_UNF_VOIP_CH_EVENT_FSK_END,             /**< FSK�������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_DTMF_END,            /**< DTMF�������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_RTP_STATISTIC,       /**< RTPͳ�ƣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_RTCP_ALARM_RESTORE,  /**< QOS�澯�ָ����ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_VQM_STATISTIC,       /**< VQMͳ�ƣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_PT_CHANGE,           /**< PT change���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_CHIP_FAULT,          /**< DSP Fault���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_CLEAR_RTP,           /**< �����ϱ�RTCPͳ������ǰ��ͳ��ֵ���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_ANI_START,           /**< ANI�źż�⣬�ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_ANI_END,             /**< ANI�����¼����ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_BUTT
} HI_UNF_VOIP_EVENT_E;


/**
����VOIP ͨ������IDö������ 
ע�� : �ý�ö�����ͱ�����HME_Api.h�е�OPEN_CHN_PARA_ENUM ����һ�¡�
*/
typedef enum hiUNF_VOIP_ATTR_ID_E
{
    HI_UNF_VOIP_ATTR_ID_MAC = 1,         /**< Mac�����ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_IPUDP = 2,       /**< IP UDP�����ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_DSP = 3,         /**< dsp common���ò��� */
    HI_UNF_VOIP_ATTR_ID_EC = 4,          /**< ec���ò��� */
    HI_UNF_VOIP_ATTR_ID_JB = 5,          /**< jb���ò��� */
    HI_UNF_VOIP_ATTR_ID_VQE = 6,         /**< VQE���ò��� */
    HI_UNF_VOIP_ATTR_ID_T38 = 7,         /**< T38���ò���,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_DTMFINRTP = 8,   /**< Dtmf in rtp���ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_2198REDRTP = 9,  /**< 2198Red rtp���ò���,�ݲ�֧�� */
    HI_UNF_VOIP_ATTR_ID_RTCP = 10,      /**< 2198Red rtp���ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_R2 = 11,        /**< 2198Red rtp���ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_NET = 13,      /**< ���� ���ò��� */
    HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV = 14,   /**< ������Ƶ�豸����*/

    HI_UNF_VOIP_ATTR_ID_BUTT
}HI_UNF_VOIP_ATTR_ID_E;

/**����TLVͷ*/
typedef struct hiUNF_VOIP_TLV_HEAD_S
{
    HI_U16  u16BlockType;    /**<  ������ , VOIPͨ�����Խṹ���У���Ӧö������HI_UNF_VOIP_ATTR_ID_E */
    HI_U16  u16BlockLen;     /**<  �鳤�� , ��������*/
}HI_UNF_VOIP_TLV_HEAD_S;

/**����TLVͷ����*/
#define HI_NUF_TVL_HEAD_LEN    ((HI_S32)sizeof(HI_UNF_VOIP_TLV_HEAD_S))

/** Dsp Common�����ṹ�����־λ */
typedef struct hiUNF_DSP_CHANGE_FLAG_S
{
    HI_U32   bit1WorkMode:1;           /**< ����, ����ģʽ��� */    
    HI_U32   bit1ConnectMode:1;        /**< ����ģʽ��� */
    HI_U32   bit1Codec:1;              /**< ���˱����� */
    HI_U32   bit1RtpPt:1;              /**< RTP��Payload type��� */     
    HI_U32   bit1PacketPeriod:1;       /**< ���˴��ʱ����� */
    HI_U32   bit1DtmfTransMode:1;      /**< ������DTMF����ģʽ��� */
    HI_U32   bit1V34Control:1;         /**< ������V34���ٱ����־ */
    HI_U32   bit25Resv:25;
}HI_UNF_DSP_CHANGE_FLAG_S;

/** Dsp Common�������� */
typedef struct hiUNF_DSP_CONFIG_BODY_S
{
    HI_U8   u8WorkMode;      /**< ����, ͨ������ģʽ ��Ӧ�����־ bit1WorkMode */
    HI_U8   u8ConnectMode;   /**< ����ģʽ, �����Ƿ��ͺͽ���RTP��, ��Ӧ�����־ bit1ConnectMode,
                                                   ��Ӧö������enum TERMINAL_MODE :
                                                  0 -- ֻ��������
                                                  1 -- ֻ��������
                                                  2 -- ͬʱ���ͺͽ���
                                                  3 -- �����ͺͲ���������
                                            **/
    HI_U16  u16Codec;           /**< VOIPͨ���ı��������,  ��Ӧ�����־ bit1Codec, 
                                                ��Ӧö������enum CODER_DECODER :
                                                0 -- G.711A
                                                1 -- G.711Mu
                                            **/  
    HI_U8   u8RtpPT;             /**< ���͵�RTP����ͷ�е�RTP��������, ��Ӧ�����־ bit1RtpPt ,
                                                ��Ӧö������enum EN_VOIP_MEDIA_PROTOCOL_TYPE  :
                                                0 --  G.711Mu
                                                8 --  G.711A
                                                ע�������u16Codec���ͱ���һ�¡�
                                           **/
    HI_U8   u8PacketPeriod;      /**< RTP������ʱ������Чֵ[10,20,30,40,50,60]ms,  ��Ӧ�����־ bit1PacketPeriod **/
    HI_U8   u8DtmfTransMode;    /**< ������DTMF����ģʽ ��Ӧ�����־ bit1DtmfTransMode */
    HI_U8   u8V34Control;           /**< �������Ƿ�֧��V34�������� ��Ӧ�����־ bit1V34Control */
}HI_UNF_DSP_CONFIG_BODY_S;


/** ����Dsp Common�����ṹ */
typedef struct hiUNF_VOIP_DSP_CONFIG_PARA_S
{
    HI_UNF_DSP_CHANGE_FLAG_S stChange;  /**< �����־λ , �޸�ͨ������ʱ��Ч������ͨ��ʱ��Ч*/
    HI_UNF_DSP_CONFIG_BODY_S stBody;   /**< Dsp Common���ò��� */    
}HI_UNF_VOIP_DSP_CONFIG_PARA_S;


/** DSP������ز����ṹ�����־λ */
typedef struct hiUNF_VOICE_CHANGE_FLAG_S
{
    HI_U32   bit1EcEnable:1;           /**<EC�����־ */  
    HI_U32   bit1NlpEnable:1;          /**<������NLPʹ�ܱ����־*/
    HI_U32   bit1NlpMode:1;            /**<������NLPģʽ�����־, ��֧������*/
    HI_U32   bit1VadEnable:1;          /**<Vad������� */
    HI_U32   bit1VadMode:1;            /**<������Vadģʽ�����־, Ŀǰ��֧��*/
    HI_U32   bit1CngEnable:1;          /**<������Cngʹ�ܱ����־*/
    HI_U32   bit1CngLevel:1;           /**<������Cngģʽ�����־*/
    HI_U32   bit1PlcMode:1;            /**<������PLCģʽ�����־,Ŀǰû�ж���ģʽѡ�� */
    HI_U32   bit1InputGain:1;          /**<���������� */
    HI_U32   bit1OutputGain:1;         /**<��������� */
    HI_U32   bit22Resv:22;
}HI_UNF_VOICE_CHANGE_FLAG_S;

/** DSP������ز������� */
typedef struct hiUNF_VOICE_CONFIG_BODY_S
{
    HI_U8   u8EcEnableFlag;     /**< ��������ʹ�ܱ�־: 0 -- EC Off , 1 -- EC On ,  ��Ӧ�����־ bit1EcEnable */
    HI_U8   u8NlpEnableFlag;    /**< ������ NLPʹ�ܱ�־,  ��Ӧ�����־ bit1NlpEnable */  
    HI_U8   u8NlpMode;          /**< ������NLPģʽ,    ��Ӧ�����־ bit1NlpMode */    
    HI_U8   u8VadEnableFlag;    /**< VADʹ�ܱ�־: 0 -- VAD Off , 1 -- VAD On , ��Ӧ�����־ bit1VadEnable */
    HI_U8   u8VadMode;          /**< ������VADģʽ,     ��Ӧ�����־ bit1VadMode */
    HI_U8   u8CngEnableFlag;    /**< ������Cngʹ�ܱ�־,  ��Ӧ�����־ bit1CngEnable */   
    HI_U8   u8CngLevel;         /**< ������CNG����,    ��Ӧ�����־ bit1CngLevel */   
    HI_U8   u8PlcMode;          /**< ������PLCģʽ,     ��Ӧ�����־ bit1PlcMode */    
    HI_U8   u8InputGain;        /**< �������� [0 ~ 15] (��Ӧ-10 dB~5 dB) , ȱʡֵΪ10 (0dB) ,  ��Ӧ�����־ bit1InputGain */
    HI_U8   u8OutputGain;       /**< ������� [0 ~ 20] (��Ӧ-10dB~10dB), ȱʡֵΪ10 (0dB),  ��Ӧ�����־ bit1OutputGain */
    HI_U16  u16Rsev;
}HI_UNF_VOICE_CONFIG_BODY_S;

/** ����dsp���������ṹ */
typedef struct hiUNF_VOICE_CONFIG_PARA_S
{
    HI_UNF_VOICE_CHANGE_FLAG_S stChange;  /**< �����־λ , �޸�ͨ������ʱ��Ч������ͨ��ʱ��Ч*/
    HI_UNF_VOICE_CONFIG_BODY_S stBody;    /**< �������ò��� */    
}HI_UNF_VOICE_CONFIG_PARA_S;

/** JB�����ṹ�����־λ */
typedef struct hiUNF_JB_CHANGE_FLAG_S
{
    HI_U32   bit1JbMode:1;      /**< JB ģʽ   �����־ */
    HI_U32   bit1JbInit:1;      /**< JB ��ʼֵ �����־ */
    HI_U32   bit1JbMax:1;       /**< JB ���ֵ �����־ */
    HI_U32   bit1JbMin:1;       /**< ������JB ��Сֵ �����־ */
    HI_U32   bit28Resv:28;         
}HI_UNF_JB_CHANGE_FLAG_S;

/** JB�������� */
typedef struct hiUNF_JB_CONFIG_BODY_S
{
    HI_U8  u8JbMode;           /**< JitterBufferģʽ: 0--��̬JB , 1--��̬JB,  ��Ӧ�����־ bit1JbMode */
    HI_U8  u8JbInit;           /**< JitterBuffer�ĳ�ʼֵ [0 ~ 150]ms  ,��Ӧ�����־ bit1JbInit */
    HI_U8  u8JbMax;            /**< JitterBuffer�����ֵ [0 ~ 150]ms , ��Ӧ�����־ bit1JbMax */
    HI_U8  u8JbMin;            /**< ������JitterBuffer����Сֵ  [0 ~ 150]ms  ,��Ӧ�����־ bit1JbMin */
}HI_UNF_JB_CONFIG_BODY_S;

/** ����JB�����ṹ */
typedef struct hiUNF_JB_CONFIG_PARA_S
{
    HI_UNF_JB_CHANGE_FLAG_S stChange;  /**< �����־λ ,  ����ͨ��ʱ��Ч���޸�ͨ������ʱ������JB����*/
    HI_UNF_JB_CONFIG_BODY_S stBody;  /**< JB���ò��� */    
}HI_UNF_JB_CONFIG_PARA_S;


/** VQE�����ṹ�����־λ */
/** ����ı�����ָmic����,Զ����ָ��������*/
typedef struct hiUNF_VQE_CHANGE_FLAG_S
{
    HI_U32   bit1LocalAgcFlag:1;            /**< ����AGC ʹ�ܱ�־���� �����־ */
    HI_U32   bit1LocalAgcValue:1;           /**< ����������AGC Ŀ��ֵ �����־ */ 

    HI_U32   bit1RemoteAgcFlag:1;         /**< Զ��AGC ʹ�ܱ�־���� �����־ */
    HI_U32   bit1RemoteAgcValue:1;       /**< ������Զ��AGC Ŀ��ֵ �����־ */ 
    
    HI_U32   bit1LocalAnrFlag:1;            /**< ����ANR ʹ�ܱ�־���� �����־*/ 
    HI_U32   bit1LocalAnrValue:1;           /**< ������ANR Ŀ��ֵ �����־ */

    HI_U32   bit1RemoteAnrFlag:1;          /**< Զ��ANR ʹ�ܱ�־���� �����־*/ 
    HI_U32   bit1RemoteAnrValue:1;        /**< ������ANR Ŀ��ֵ �����־ */
    
    HI_U32   bit24Resv:24;         
}HI_UNF_VQE_CHANGE_FLAG_S;

/** VQE�������� */
typedef struct hiUNF_VQE_CONFIG_BODY_S
{
    HI_U8   u8LocalAgcFlag;          /**< ����AGC ʹ�ܱ�־: 0 -- Agc Off , 1 -- Agc On , ��Ӧ�����־ bit1LocalAgcFlag */
    HI_U8   u8LocalAgcValue;        /**< �����������Զ������������, 
                                                            [0 ~ 15] ��Ӧ ʵ�����ܲ�����-9dBm0 ~ -24dBm0, ȱʡֵ13 ,
                                                            ��Ӧ�����־ bit1LocalAgcValue */
    HI_U8   u8RemoteAgcFlag;          /**< Զ��AGC ʹ�ܱ�־: 0 -- Agc Off , 1 -- Agc On ,  ��Ӧ�����־ bit1RemoteAgcFlag */
    HI_U8   u8RemoteAgcValue;       /**< ������Զ���Զ������������, 
                                                            [0 ~ 15]��Ӧʵ�����ܲ�����-9dBm0 ~ -24dBm0, ȱʡֵ13 ,
                                                            ��Ӧ�����־ bit1RemoteAgcValue */
    HI_U8   u8LocalAnrFlag;          /**< ����ANR ʹ�ܱ�־: 0 -- Anr Off , 1 -- Anr On ,  ��Ӧ�����־ bit1LocalAnrFlag */
    HI_U8   u8LocalAnrValue;        /**< ����������ANR Ŀ��ֵ(�����������Ƶ�������) ,  ��Ӧ�����־ bit1LocalAnrValue */  
    
    HI_U8   u8RemoteAnrFlag;          /**< Զ��ANR ʹ�ܱ�־: 0 -- Anr Off, 1 -- Anr On   , ��Ӧ�����־ bit1RemoteAnrFlag */
    HI_U8   u8RemoteAnrValue;        /**< ������Զ��ANR Ŀ��ֵ(�����������Ƶ�������)  ,   ��Ӧ�����־ bit1RemoteAnrValue */  
}HI_UNF_VQE_CONFIG_BODY_S;


/**  ����VQE�����ṹ */
typedef struct hiUNF_VQE_CONFIG_PARA_S
{
    HI_UNF_VQE_CHANGE_FLAG_S stChange;  /**< �����־λ , �޸�ͨ������ʱ��Ч������ͨ��ʱ��Ч*/
    HI_UNF_VQE_CONFIG_BODY_S stBody;  /**< VQE���ò��� */    
}HI_UNF_VQE_CONFIG_PARA_S;

/** ��������ṹ�����־λ */
typedef struct hiUNF_NET_CHANGE_FLAG_S
{
   HI_U32   bit1SrcIP:1;     /**<source ip������, 32SrcIPLen��u8SrcIP[16]�и���*/
   HI_U32   bit1DstIP:1;     /**<dest ip������, u32DstIPLen��u8DstIP[16]�и���*/
   HI_U32   bit1SrcPort:1;   /**<source port ������,u16SrcPort�и���*/
   HI_U32   bit1DstPort:1;   /**<dest port������,u16DstPort�и���*/
   HI_U32   bit1IPTos:1;     /**<IP�������ͱ�����,u32IPTos��u32Mask�и���*/
   HI_U32   bit1Vlan:1;      /**<Vlan������,u32VlanEn,u32VlanPri,u32VlanPid�и��ģ�����*/
   HI_U32   bit1Protocol:1;   /**<Э�����ͱ����ǣ�Ŀǰֻ֧��IPV4,����*/
   HI_U32   bit25Resv:25;         
}HI_UNF_NET_CHANGE_FLAG_S;

/** ����������� */
typedef struct hiUNF_NET_CONFIG_BODY_S
{
   HI_U32   u32SrcIPLen;      /**<source ip��ַ���ȣ�4(IPV4)��16(IPV6)������ֵ��Ч*/
   HI_U8    u8SrcIP[16];       /**<source ip��ַ��4�ֽ�(IPV4)��16�ֽ�(IPV6)�������ַ�������192.168.1.1Ϊ����4�ֽ�����Ϊ192,168,1,1 */
   HI_U32   u32DstIPLen;      /**<dest ip��ַ���ȣ�4(IPV4)��16(IPV6)������ֵ��Ч*/
   HI_U8    u8DstIP[16];       /**<dest ip��ַ��4�ֽ�(IPV4)��16�ֽ�(IPV6)�������ַ���*/

   HI_U16   u16SrcPort;        /**<source RTP �˿ںţ�ӦΪż������ӦRTCP�˿ں�Ϊ����ֵ+1 */
   HI_U16   u16DstPort;         /**<dest RTP �˿ںţ�ӦΪż������ӦRTCP�˿ں�Ϊ����ֵ+1 */

   HI_U32   u32Mask;         /**<bit0: u32IPTos valid*/
   HI_U32   u32IPTos;       /**<IP��������,8bit*/
   HI_U32   u32VlanEn;     /**<vlanʹ��: 0--vlan ��Ч,1--vlan ��Ч, ����*/
   HI_U32   u32VlanPri;     /**<vlan���ȼ�,3bit, vlanΪ1ʱ��Ч, ����*/
   HI_U32   u32VlanPid;     /**<vlan pid, 12bit, vlanΪ1ʱ��Ч, ����*/
   HI_U32   u32Protocol;     /**<Э������,0x0800--IPV4, 0x86dd--IPV6, ����*/
}HI_UNF_NET_CONFIG_BODY_S;

/** ������������ṹ */
typedef struct hiUNF_NET_CONFIG_PARA_S
{
    HI_UNF_NET_CHANGE_FLAG_S stChange;  /**< ������������־λ ,�������޸�ͨ��ʱ��Ӧλ��������*/

    HI_UNF_NET_CONFIG_BODY_S stBody;  /**< �������ò��� */    
}HI_UNF_NET_CONFIG_PARA_S;

/**��Ƶ�豸���������־*/
typedef struct hiUNF_AUDDEV_FLAG_S
{
    HI_U32   bit1AudioDevId:1;        /**< AudioDevId �����־ */
    HI_U32   bit1AiAttrChange:1;      /**< AI SampleRate/BitPerSample/Channels�����־ */
    HI_U32   bit1AoAttrChange:1;      /**< AO SampleRate/BitPerSample/Channels�����־ */
    HI_U32   bit29Resv:29;
}HI_UNF_AUDDEV_FLAG_S;

/** ��Ƶ�豸ϵͳ���� */
typedef struct hiUNF_AUDDEV_BODY_S
{
    HI_S32 s32AudioDevId;               /**< ��Ƶ�豸ID , [0]*/
 
    /** ��Ƶ������� */ 
    HI_S32 s32AiSampleRate;           /**< ������, [8000]*/
    HI_S32 s32AiBitPerSample;       /**< ��������, [16]*/
    HI_S32 s32AiChannels;               /**< ͨ����, [1]*/
  
    /** ��Ƶ�������*/ 
    HI_S32 s32AoSampleRate;          /**< ������, [8000]*/
    HI_S32 s32AoBitPerSample;       /**< ��������, [16]*/
    HI_S32 s32AoChannels;               /**< ͨ����, [1]*/
    
}HI_UNF_AUDDEV_BODY_S;

/** ��Ƶ�豸����*/
typedef struct hiUNF_AUDDEV_PARA_S
{
    HI_UNF_AUDDEV_FLAG_S    stChang;        /**< ��Ƶ�豸���������ǣ� �޸�ͨ������ʱ��Ч������ͨ��ʱ��Ч*/
    HI_UNF_AUDDEV_BODY_S    stBody;         /**< ��Ƶ�豸���ò���*/
}HI_UNF_AUDDEV_PARA_S;


/** ����VOIP ͨ������ */  
typedef struct hiUNF_VOIP_CHN_ATTR_S
{    
    HI_UNF_VOIP_TLV_HEAD_S stTlvHead; /**< ���У�u16BlockType��Ч������u16BlockLen��ʾ����HI_UNF_VOIP_CHN_ATTR_S �ṹ�峤��*/
    
    HI_UNF_VOIP_TLV_HEAD_S stDspHead;           /**<  u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_DSP, u16BlockLenΪHI_UNF_VOIP_DSP_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_VOIP_DSP_CONFIG_PARA_S stDspPara;  /**< dsp common���ò�������ͨ��ʱ�Ǳ�����޸�ͨ��ʱ��ѡ*/

    HI_UNF_VOIP_TLV_HEAD_S stEcHead;            /**<  u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_EC, u16BlockLenΪHI_UNF_VOICE_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_VOICE_CONFIG_PARA_S stEcPara;      /**<  Ec���ò���, ��ͨ��ʱ�Ǳ�����޸�ͨ��ʱ��ѡ*/

    HI_UNF_VOIP_TLV_HEAD_S stJBHead;         /**<  u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_JB, u16BlockLenΪHI_UNF_JB_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_JB_CONFIG_PARA_S stJBPara;         /**<  JB���ò���, ��ͨ��ʱ�Ǳ�����޸�ͨ��ʱ��Ч*/
    
    HI_UNF_VOIP_TLV_HEAD_S stVQEHead;           /**<  u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_VQE, u16BlockLenΪHI_UNF_VQE_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_VQE_CONFIG_PARA_S stVQEPara;       /**<  VQE���ò�������ͨ��ʱ�Ǳ�����޸�ͨ��ʱ��ѡ*/

    HI_UNF_VOIP_TLV_HEAD_S stNetHead;           /**<  u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_NET, u16BlockLenΪHI_UNF_NET_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_NET_CONFIG_PARA_S stNetPara;       /**<  NET���ò�������ѡ��*/
    
    HI_UNF_VOIP_TLV_HEAD_S stAudevHead;    /**<  u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV, u16BlockLenΪHI_UNF_AUDDEV_PARA_S�ṹ�峤��*/        
    HI_UNF_AUDDEV_PARA_S   stAudevPara;     /**<  ��Ƶ�豸���ò�������ͨ��Ϊ������޸�ͨ��ʱ��ѡ*/
}HI_UNF_VOIP_CHN_ATTR_S;

/** ����Ƶ������������*/
typedef struct hiUNF_VOIP_BASE_FREQ_INFO_S
{
    HI_U16  u16Frequence;        /**< ����Ƶ��*/
    HI_U16  u16Amplitude;        /**< ��������*/
}HI_UNF_VOIP_BASE_FREQ_INFO_S;

/** ������������������*/
typedef struct hiUNF_VOIP_CADENCE_INFO_S
{
    HI_U16  u16FreqFlag;         /**< ʹ�õĻ�����־*/
    HI_U16  u16Reserved;         /**< ������*/
    HI_U16  u16OnTime;           /**< ��Чʱ��*/
    HI_U16  u16OffTime;          /**< ����ʱ��*/
}HI_UNF_VOIP_CADENCE_INFO_S;

/** ��������������������*/
typedef struct hiUNF_VOIP_TONE_ATTR_S
{
    HI_UNF_VOIP_BASE_FREQ_INFO_S   stBaseFreqInfo[4]; /**< ����Ƶ������*/
    HI_U32                u32CadenceCount;    /**< ���ĵ�����*/
    HI_U32                u32Resve;
    HI_UNF_VOIP_CADENCE_INFO_S     stCadenceInfo[8]; /**< ��������*/
}HI_UNF_VOIP_TONE_ATTR_S;

/** ��������������������������*/
typedef struct hiUNF_VOIP_PLAY_TONE_ATTR_S
{   
    HI_UNF_VOIP_TONE_ATTR_S stToneParam;    /**< ����������������*/
    HI_U32 u32MixFlag;                                      /**< ������־: 0--������, 1--����*/
    HI_U32 u32LoopTime;                                 /**< �ظ�����: 0--���ظ�, 1~254 -- �ظ�����, 255 -- һֱ����*/
}HI_UNF_VOIP_PLAY_TONE_ATTR_S; 

/** ��Ƶ�ļ���������������*/
typedef struct hiUNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S
{   
    HI_U32 u32DataAddr;         /**< ��Ƶ�ļ���ַ*/
    HI_U32 u32DataLen;            /**< ��Ƶ�ļ�����*/
    HI_U16 u16SourceFormat;  /**< ��Ƶ�ļ���������: 0 -- G.711A, 1 -- G.711Mu
                                            ע: Ŀǰֻ֧�ֲ���711���͵ı�׼wav�ļ������ļ�Ϊ�����ɡ�*/
    HI_U16 u16Resv;
    HI_U32 u32MixFlag;            /**< ������־: 0--������, 1--����*/
    HI_U32 u32Direction;         /**< ���ŷ���: 0--���ŵ�����, 1-- ���ŵ�Զ��(����)*/
    HI_U32 u32LoopTime;         /**< �ظ�����: 0--���ظ�, 1~254 -- �ظ�����, 255 -- һֱ����*/
}HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S;


/** ����������Ϣ������*/
typedef struct hiUNF_VOIP_NET_QUALITY_STATIC_INFO_S
{
    HI_U32 u32TotalLostPacket;              /**< ���ݶ���ͳ��*/
    HI_U32 u32LossFraction;                  /**< ������(%) */
    HI_U32 u32Jitter;                               /**< ƽ������(ms) */
    HI_U32 u32Delay;                              /**< ƽ��ʱ��(ms) */
}HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S; 

/** RTCPͳ����Ϣ������ */
typedef struct hiUNF_VOIP_RTCP_STATIC_INFO_S
{
    HI_U32 u32SendPacketNum;                /**< ���Ͱ�����*/
    HI_U32 u32SendBytes;                            /**< �����ֽ���*/
    HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S stSendInfo;          /**< ����ͳ��*/
    HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S stRecvInfo;          /**< ����ͳ��*/
}HI_UNF_VOIP_RTCP_STATIC_INFO_S;

/** RTCP����������*/
typedef struct hiUNF_VOIP_CFG_RTCP_ATTR_S
{   
    HI_U32 u32EnableFlag;               /**< RTCPͳ��ʹ��: 0--��ʹ��, 1--ʹ��*/
    HI_U32 u32SendInterval;             /**< RTCP���淢�ͼ��, [500 ~ 65535] ms , ����Ϊ500ms��������*/
}HI_UNF_VOIP_CFG_RTCP_ATTR_S;


/******************************* Voip Audio Adapter ******************************/

typedef enum hiUNF_AUDADP_EVENT_E
{
    HI_UNF_AUDADP_EVENT_OPEN_SUCCESS,
    HI_UNF_AUDADP_EVENT_OPEN_FAILURE,
    HI_UNF_AUDADP_EVENT_CLOSED,
    HI_UNF_AUDADP_EVENT_STREAM_ERROR,
    HI_UNF_AUDADP_EVENT_BLUETOOTH_NOT_CONNECTED,    /**< the bluetooth device not connected*/
    HI_UNF_AUDADP_EVENT_BUTT
} HI_UNF_AUDADP_EVENT_E;

typedef enum hiUNF_AUDADP_STATUS_E
{
    HI_UNF_AUDADP_STATUS_CLOSED  = 0x00,  /**< audio device closed */
    HI_UNF_AUDADP_STATUS_OPENING,         /**<  audio device is opening */
    HI_UNF_AUDADP_STATUS_OPENED,          /**<  audio device is opened*/
    HI_UNF_AUDADP_STATUS_RUNNING,         /**< transmiting the audio data*/
    HI_UNF_AUDADP_STATUS_ERROR,           /**< open the audio device or transmit the audio data failure*/
    HI_UNF_AUDADP_STATUS_BLUETOOTH_NOT_CONNECTED,    /**< the bluetooth device not connected*/
    HI_UNF_AUDADP_STATUS_BUTT
} HI_UNF_AUDADP_STATUS_E;

typedef struct hiUNF_AUDADP_EVENT_S
{
    HI_S32 s32AudioDevIndex;
    HI_BOOL bAudioInDev;
    HI_UNF_AUDADP_EVENT_E enEvent;
    HI_UNF_AUDADP_STATUS_E enStatus;
    HI_U32 u32Args;
}HI_UNF_AUDADP_EVENT_S;

/**The operating flag*/
typedef struct hiUNF_AUDDEV_OPT_FLAG_S
{
    HI_U32   bit1AudInDev:1;        /**< Audio in device */
    HI_U32   bit1AudOutDev:1;      /**< Audio out device */
    HI_U32   bit30Resv:30;
}HI_UNF_AUDDEV_OPT_FLAG_S;


/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_3 */
/** @{ */  /** <!-- ��VOIP�� */

/**
 \brief ��ʼ��VOIPģ��
 \attention \n
 \param ��
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_DEV_OPEN_ERR  �豸�򿪴���
 \retval ::HI_ERR_VOIP_HME_DEV_NOT_EXIST  �豸������
 \retval ::HI_ERR_VOIP_HME_NOT_DEV_FILE  �����豸�ļ�
 \retval ::HI_ERR_VOIP_HME_NO_INIT    EVENT��ʼ��ʧ��
 \see \n
��
 */
HI_S32 HI_UNF_VOIP_Init(HI_VOID);

/**
 \brief ȥ��ʼ��VOIPģ��
 \attention \n
 \param ��
 \retval ::0  �ɹ�
 \see \n
��
 */
HI_S32 HI_UNF_VOIP_DeInit(HI_VOID);

/**
 \brief ��ȡȱʡ��VOIP ͨ������
 \attention \n
        ����ȷ������Ҫ����VOIP ͨ������ģʽ��Ŀǰֻ֧������ģʽHI_UNF_VOIP_MODE_VOIVE
        ����VOIP ͨ��ǰ������ñ��ӿڣ���ȡ��Ĭ�����ԣ����ⴴ��VOIP ͨ��ʱ���ڲ�����ȫ����������´������ɹ�����
 \param[in] enWorkMode       VOIP ͨ������ģʽ����μ�::HI_UNF_VOIP_WORKMODE_E
 \param[out] pstDefChAttr  ָ�����ͣ�VOIP ͨ��Ĭ�����ԣ��μ�:HI_UNF_VOIP_CHN_ATTR_S
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \see \n
��
 */
HI_S32 HI_UNF_VOIP_GetChDefaultAttr(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstDefChAttr);

/**
 \brief ����VOIP ͨ��
 \attention \n
 ����ͨ��ǰ�������ȵ���HI_UNF_VOIP_GetChDefaultAttr()��ȡĬ��ͨ�����ԣ��ٶԲ�������Ҫ�޸ġ�
 \param[in] enWorkMode       VOIP ͨ������ģʽ����μ�::HI_UNF_VOIP_WORKMODE_E
 \param[in]  pstChAttr  ָ�����ͣ�VOIP ͨ�����ԣ���μ�::HI_UNF_VOIP_CHN_ATTR_S
 \param[out] phVoip   ָ�����ͣ�������VOIP ͨ�����
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::HI_ERR_VOIP_HME_CREATE_ERR   ����ͨ��ʧ��
 \retval ::����  ����ͨ��ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_CreateChannel(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVoip);


/**
 \brief ����VOIP ͨ��
 \attention \n
��
 \param[in] hVOIP  VOIP ͨ�����
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA  ��Ч����
 \retval ::HI_ERR_VOIP_HME_DESTROY_ERR   ����ͨ��ʧ��
 \retval ::����  ����ͨ��ʧ��
 \see \n
��
 */
 HI_S32 HI_UNF_VOIP_DestroyChannel(HI_HANDLE hVoip);

/**
 \brief ��ȡVOIP ͨ������
 \attention \n
 \param[in] hVOIP  VOIP ͨ�����
 \param[out] pstChAttr  ָ�����ͣ�VOIP ͨ�����ԣ��μ�:HI_UNF_VOIP_CHN_ATTR_S
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::����  ��ȡͨ������ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_GetChAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);

/**
 \brief �޸�VOIP ͨ������
 \attention \n
        �����ȵ���HI_UNF_VOIP_GetChAttr()��ȡ��ǰͨ�����ã��ٶԲ�������Ҫ�޸ģ���Ӧ�ĸ��ı����1���޹ظ��ı�־��0��
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] pstChAttr  ָ�����ͣ�VOIP ͨ�����ԣ��μ�:HI_UNF_VOIP_CHN_ATTR_S
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::����  �޸�ͨ������ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_ModifyChnAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);

#if 0
/**
 \brief ��ȡVOIP ͨ��������
 \attention \n
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] enAttrID  VOIP ͨ�����ò���ID���μ�: HI_UNF_VOIP_ATTR_ID_E
 \param[out] pChSubAttr  ָ�����ͣ�VOIP ͨ�������ԣ��ṹ����enAttrID ��Ӧ��
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::����  ��ȡͨ������ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_GetChSubAttr(HI_HANDLE hVoip, HI_UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr);

/**
 \brief �޸�VOIP ͨ��������
 \attention \n
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] enAttrID  VOIP ͨ�����ò���ID���μ�: HI_UNF_VOIP_ATTR_ID_E
 \param[in] pChSubAttr  ָ�����ͣ�VOIP ͨ�������ԣ��ṹ����enAttrID ��Ӧ��
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::����  �޸�ͨ������ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_ModifyChnSubAttr(HI_HANDLE hVoip, HI_UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr);

/**
 \brief ���Ż�����
 \attention \n
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] pstToneAttr  ָ�����ͣ����������Ų������μ�: HI_UNF_VOIP_PLAY_TONE_ATTR_S
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::����  ���Ż�����ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_PlayTone(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr);

/**
 \brief ֹͣ���Ż�����
 \attention \n
 \param[in] hVOIP  VOIP ͨ�����
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::����  ֹͣ���Ż�����ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_StopTone(HI_HANDLE hVoip);
#endif

/**
 \brief ������Ƶ�ļ�
 \attention \n
        Ŀǰֻ֧�ֲ���711���͵ı�׼wav�ļ������ļ�Ϊ�����ɡ�
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] pstAnnAttr  ָ�����ͣ���Ƶ�ļ����Ų������μ�: HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::����  ������Ƶ�ļ�ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_PlayAnnouncement(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr);

/**
 \brief ֹͣ������Ƶ�ļ�
 \attention \n
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] u32Direction  ���ŷ��򣬱�������Ƶ�ļ����������е�u32Direction ����һ�¡�
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::����  ֹͣ ������Ƶ�ļ�ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_StopAnnouncement(HI_HANDLE hVoip, HI_U32 u32Direction);

/**
 \brief �����¼��ص���������
 \attention \n
��
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] enEvent     ö�����ͣ���ʾ�¼����ͣ��μ�: HI_UNF_VOIP_EVENT_E ����
 \param[in] s32EventValue  �¼����Ͳ���������Ϊevent����һЩ��������� ��������¼��Ĵ�����
 \param[in] args        ע��ʱ�����args������
 \retval ::0  �ɹ�
 \retval ::����  ʧ��
 \see \n
��
 */
typedef HI_S32 (*HI_UNF_VOIP_EVENT_CB_FN)(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_E enEvent, HI_S32 s32EventValue, HI_U32 u32Args);


/**
 \brief ע���¼�
 \attention \n
��
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] pfnEventCB  �ص�����ָ�룬ָ����ע���¼���Ӧ�Ļص�������ָ��ΪNULL��ʾUnRegister
 \param[in] args        �ص�����˽�в������˲����ڻص����������õ�ʱ��ᴫ�ݸ��ص�������
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NOT_EXIST   ͨ��������
 \see \n
��
 */
HI_S32 HI_UNF_VOIP_RegisterEvent(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);


/**
 \brief ��ȡRTCPͳ����Ϣ
 \attention \n
 \param[in] hVOIP  VOIP ͨ�����
 \param[out] pstRtcpInfo  ָ�����ͣ�RTCPͳ����Ϣ���μ�: HI_UNF_VOIP_RTCP_STATIC_INFO_S
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::����  ��ȡRTCPͳ����Ϣʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_GetRtcpStaticInfo(HI_HANDLE hVoip, HI_UNF_VOIP_RTCP_STATIC_INFO_S * pstRtcpInfo);

/**
 \brief  RTCP����
 \attention \n
 \param[in] hVOIP  VOIP ͨ�����
 \param[in] pstRtcpAttr  ָ�����ͣ�RTCP���ã��μ�: HI_UNF_VOIP_CFG_RTCP_ATTR_S
 \retval ::0  �ɹ�
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  ��ָ��
 \retval ::����  RTCP����ʧ��
 \see \n
��
 */

HI_S32 HI_UNF_VOIP_CfgRtcp(HI_HANDLE hVoip, HI_UNF_VOIP_CFG_RTCP_ATTR_S * pstRtcpAttr);


/******************************* Voip Audio Adapter ******************************/

/**
 \brief Initial the voip audio adapter module
 \attention \n
 Should initial the VOIP module first before initial audio adapter module
 \param None
 \retval ::0  HI_SUCCESS
 \retval ::HI_ERR_VOIP_HME_DEV_OPEN_ERR
 \retval ::HI_ERR_VOIP_HME_DEV_NOT_EXIST
 \retval ::HI_ERR_VOIP_HME_NOT_DEV_FILE
 \retval ::Others    FAILURE
 \see \n
None
 */

HI_S32 HI_UNF_AUDADP_Init(HI_VOID);

/**
 \brief Deinitial the voip audio adapter module
 \attention \n
 It's better to deinitial the audio adapter module after deinitial VOIP module.
 \param None
 \retval ::0  HI_SUCCESS
 \see \n
None
 */

HI_S32 HI_UNF_AUDADP_DeInit(HI_VOID);

/**
 \brief Open the audio device
 \attention \n
 It's better to open the audio device immediately after initial audio adapter module
 \param[in] pstAudDev   The parameters of opened audio device
 \param[in] stAudDevOptFlag  The operate object flag
 \retval ::0  HI_SUCCESS
 \retval ::HI_ERR_VOIP_HME_NO_INIT  
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA
 \see \n
��
 */

HI_S32 HI_UNF_AUDADP_AudDev_Open(HI_UNF_AUDDEV_BODY_S *pstAudDev, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Close the audio device
 \attention \n
 None
 \param[in] s32AudioDevIndex   The audio device id
 \param[in] stAudDevOptFlag  The operate object flag
 \retval ::0  HI_SUCCESS
 \retval ::HI_ERR_VOIP_HME_NO_INIT  
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA
 \see \n
��
 */

HI_S32 HI_UNF_AUDADP_AudDev_Close(HI_S32 s32AudioDevIndex, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Start the audio data transmiting
 \attention \n
 None
 \param[in] s32AudioDevIndex   The audio device id
 \param[in] stAudDevOptFlag  The operate object flag
 \retval ::0  HI_SUCCESS
 \retval ::HI_ERR_VOIP_HME_NO_INIT  
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA
 \see \n
��
 */

HI_S32 HI_UNF_AUDADP_AudDev_Start(HI_S32 s32AudioDevIndex, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Stop the audio data transmiting
 \attention \n
 None
 \param[in] s32AudioDevIndex   The audio device id
 \param[in] stAudDevOptFlag  The operate object flag
 \retval ::0  HI_SUCCESS
 \retval ::HI_ERR_VOIP_HME_NO_INIT  
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA
 \see \n
��
 */

HI_S32 HI_UNF_AUDADP_AudDev_Stop(HI_S32 s32AudioDevIndex, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Get the audio device status
 \attention \n
 None
 \param[in] s32AudioDevIndex   The audio device id
 \param[in] bAudioInDev  HI_TRUE for audio in device, HI_FALSE for audio out device
 \param[out] ps32Status  returned audio device status
 \retval ::0  HI_SUCCESS
 \retval ::HI_ERR_VOIP_HME_NO_INIT  
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA
 \see \n
��
 */

HI_S32 HI_UNF_AUDADP_AudDev_GetStatus(HI_S32 s32AudioDevIndex, HI_BOOL bAudioInDev, HI_UNF_AUDADP_STATUS_E *ps32Status);

/**
 \brief Define the audio adapter event call back function
 \attention \n
 None
 \param[in] pstAudadpEvent   The event structure
 \retval ::0  HI_SUCCESS
 \retval ::others FAILURE
 \see \n
��
 */

typedef HI_S32 (*HI_UNF_AUDADP_EVENT_CB_FN)(HI_UNF_AUDADP_EVENT_S *pstAudadpEvent);

/**
 \brief Register call back function for audio adapter events 
 \attention \n
 None
 \param[in] pfnEventCB   The pointer of call back function , NULL to unregister.
 \param[in] u32Args  The private parameter from user application.
 \retval ::0  HI_SUCCESS
 \retval ::HI_ERR_VOIP_HME_NO_INIT  
 \see \n
��
 */

HI_S32 HI_UNF_AUDADP_RegisterEvent(HI_UNF_AUDADP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
