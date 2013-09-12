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
 * \brief 提供VOIP语音引擎的相关信息
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

/**定义VOIP 通道工作模式类型 */
typedef enum hiUNF_VOIP_WORKMODE_E
{
    HI_UNF_VOIP_MODE_DTMF  = 0x00,  /**< DTMF收号模式，保留 */
    HI_UNF_VOIP_MODE_VOIVE = 0x01,  /**<  语音模式 */
    HI_UNF_VOIP_MODE_FAX   = 0x02, /**<  传真模式 ，保留*/
    HI_UNF_VOIP_MODE_MODEM = 0x03,  /**< Modem 模式，保留*/
    HI_UNF_VOIP_MODE_BUTT = 0x4
} HI_UNF_VOIP_WORKMODE_E;

/**定义VOIP 通道事件上报类型 */
typedef enum hiUNF_VOIP_EVENT_E
{
    HI_UNF_VOIP_CH_EVENT_FAULT,               /**< 通道故障*/
    HI_UNF_VOIP_CH_EVENT_NORMAL,              /**< 通道恢复正常，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_OPEN_FAILED,         /**< 打开通道失败，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_CLOSE_FAILED,        /**< 关闭通道失败，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_LOCAL_PLAY_END,      /**< LOCAL PLAY结束*/
    HI_UNF_VOIP_CH_EVENT_REMOTE_PLAY_END,     /**< REMOTE PLAY结束*/
    HI_UNF_VOIP_CH_EVENT_FAX_START,           /**< 传真开始，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_FAX_END,             /**< 传真结束，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_MODEM_START,         /**< MODEM开始，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_MODEM_END,           /**< MODEM结束，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_DETECT_DTMF,         /**< DTMF检测*/
    HI_UNF_VOIP_CH_EVENT_DETECT_FSK,          /**< FSK检测，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_DETECT_BUSY_TONE,    /**< 忙音检测，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_RTCP_ALARM,          /**< RTCP告警，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_GENCALLID_FAILED,    /**< 主叫显示失败，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_STOPCALLID_FAILED,   /**< 停主叫显示失败，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_DATA_TONE,           /**< CNG, V8, V25相关信号音，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_REMOTE_FAX_START,    /**< 芯片检测到对端发送了T38报文，在T38 */
    HI_UNF_VOIP_CH_EVENT_FSK_END,             /**< FSK结束，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_DTMF_END,            /**< DTMF结束，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_RTP_STATISTIC,       /**< RTP统计，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_RTCP_ALARM_RESTORE,  /**< QOS告警恢复，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_VQM_STATISTIC,       /**< VQM统计，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_PT_CHANGE,           /**< PT change，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_CHIP_FAULT,          /**< DSP Fault，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_CLEAR_RTP,           /**< 用于上报RTCP统计清零前的统计值，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_ANI_START,           /**< ANI信号检测，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_ANI_END,             /**< ANI结束事件，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_BUTT
} HI_UNF_VOIP_EVENT_E;


/**
定义VOIP 通道属性ID枚举类型 
注意 : 该结枚举类型必须与HME_Api.h中的OPEN_CHN_PARA_ENUM 定义一致。
*/
typedef enum hiUNF_VOIP_ATTR_ID_E
{
    HI_UNF_VOIP_ATTR_ID_MAC = 1,         /**< Mac层配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_IPUDP = 2,       /**< IP UDP层配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_DSP = 3,         /**< dsp common配置参数 */
    HI_UNF_VOIP_ATTR_ID_EC = 4,          /**< ec配置参数 */
    HI_UNF_VOIP_ATTR_ID_JB = 5,          /**< jb配置参数 */
    HI_UNF_VOIP_ATTR_ID_VQE = 6,         /**< VQE配置参数 */
    HI_UNF_VOIP_ATTR_ID_T38 = 7,         /**< T38配置参数,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_DTMFINRTP = 8,   /**< Dtmf in rtp配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_2198REDRTP = 9,  /**< 2198Red rtp配置参数,暂不支持 */
    HI_UNF_VOIP_ATTR_ID_RTCP = 10,      /**< 2198Red rtp配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_R2 = 11,        /**< 2198Red rtp配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_NET = 13,      /**< 网络 配置参数 */
    HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV = 14,   /**< 配置音频设备参数*/

    HI_UNF_VOIP_ATTR_ID_BUTT
}HI_UNF_VOIP_ATTR_ID_E;

/**定义TLV头*/
typedef struct hiUNF_VOIP_TLV_HEAD_S
{
    HI_U16  u16BlockType;    /**<  块类型 , VOIP通道属性结构体中，对应枚举类型HI_UNF_VOIP_ATTR_ID_E */
    HI_U16  u16BlockLen;     /**<  块长度 , 参数长度*/
}HI_UNF_VOIP_TLV_HEAD_S;

/**定义TLV头长度*/
#define HI_NUF_TVL_HEAD_LEN    ((HI_S32)sizeof(HI_UNF_VOIP_TLV_HEAD_S))

/** Dsp Common参数结构变更标志位 */
typedef struct hiUNF_DSP_CHANGE_FLAG_S
{
    HI_U32   bit1WorkMode:1;           /**< 保留, 工作模式变更 */    
    HI_U32   bit1ConnectMode:1;        /**< 连接模式变更 */
    HI_U32   bit1Codec:1;              /**< 本端编码变更 */
    HI_U32   bit1RtpPt:1;              /**< RTP的Payload type变更 */     
    HI_U32   bit1PacketPeriod:1;       /**< 本端打包时长变更 */
    HI_U32   bit1DtmfTransMode:1;      /**< 保留，DTMF传输模式变更 */
    HI_U32   bit1V34Control:1;         /**< 保留，V34降速变更标志 */
    HI_U32   bit25Resv:25;
}HI_UNF_DSP_CHANGE_FLAG_S;

/** Dsp Common参数配置 */
typedef struct hiUNF_DSP_CONFIG_BODY_S
{
    HI_U8   u8WorkMode;      /**< 保留, 通道工作模式 对应变更标志 bit1WorkMode */
    HI_U8   u8ConnectMode;   /**< 连接模式, 控制是否发送和接收RTP包, 对应变更标志 bit1ConnectMode,
                                                   对应枚举类型enum TERMINAL_MODE :
                                                  0 -- 只发送数据
                                                  1 -- 只接收数据
                                                  2 -- 同时发送和接收
                                                  3 -- 不发送和不接收数据
                                            **/
    HI_U16  u16Codec;           /**< VOIP通道的编解码类型,  对应变更标志 bit1Codec, 
                                                对应枚举类型enum CODER_DECODER :
                                                0 -- G.711A
                                                1 -- G.711Mu
                                            **/  
    HI_U8   u8RtpPT;             /**< 发送的RTP报文头中的RTP净荷类型, 对应变更标志 bit1RtpPt ,
                                                对应枚举类型enum EN_VOIP_MEDIA_PROTOCOL_TYPE  :
                                                0 --  G.711Mu
                                                8 --  G.711A
                                                注意必须与u16Codec类型保持一致。
                                           **/
    HI_U8   u8PacketPeriod;      /**< RTP打包解包时长，有效值[10,20,30,40,50,60]ms,  对应变更标志 bit1PacketPeriod **/
    HI_U8   u8DtmfTransMode;    /**< 保留，DTMF传输模式 对应变更标志 bit1DtmfTransMode */
    HI_U8   u8V34Control;           /**< 保留，是否支持V34降速配置 对应变更标志 bit1V34Control */
}HI_UNF_DSP_CONFIG_BODY_S;


/** 配置Dsp Common参数结构 */
typedef struct hiUNF_VOIP_DSP_CONFIG_PARA_S
{
    HI_UNF_DSP_CHANGE_FLAG_S stChange;  /**< 变更标志位 , 修改通道属性时有效，创建通道时无效*/
    HI_UNF_DSP_CONFIG_BODY_S stBody;   /**< Dsp Common配置参数 */    
}HI_UNF_VOIP_DSP_CONFIG_PARA_S;


/** DSP语音相关参数结构变更标志位 */
typedef struct hiUNF_VOICE_CHANGE_FLAG_S
{
    HI_U32   bit1EcEnable:1;           /**<EC变更标志 */  
    HI_U32   bit1NlpEnable:1;          /**<保留，NLP使能变更标志*/
    HI_U32   bit1NlpMode:1;            /**<保留，NLP模式变更标志, 不支持配置*/
    HI_U32   bit1VadEnable:1;          /**<Vad参数变更 */
    HI_U32   bit1VadMode:1;            /**<保留，Vad模式变更标志, 目前不支持*/
    HI_U32   bit1CngEnable:1;          /**<保留，Cng使能变更标志*/
    HI_U32   bit1CngLevel:1;           /**<保留，Cng模式变更标志*/
    HI_U32   bit1PlcMode:1;            /**<保留，PLC模式变更标志,目前没有多种模式选择 */
    HI_U32   bit1InputGain:1;          /**<输入增益变更 */
    HI_U32   bit1OutputGain:1;         /**<输出增益变更 */
    HI_U32   bit22Resv:22;
}HI_UNF_VOICE_CHANGE_FLAG_S;

/** DSP语音相关参数配置 */
typedef struct hiUNF_VOICE_CONFIG_BODY_S
{
    HI_U8   u8EcEnableFlag;     /**< 回声抑制使能标志: 0 -- EC Off , 1 -- EC On ,  对应变更标志 bit1EcEnable */
    HI_U8   u8NlpEnableFlag;    /**< 保留， NLP使能标志,  对应变更标志 bit1NlpEnable */  
    HI_U8   u8NlpMode;          /**< 保留，NLP模式,    对应变更标志 bit1NlpMode */    
    HI_U8   u8VadEnableFlag;    /**< VAD使能标志: 0 -- VAD Off , 1 -- VAD On , 对应变更标志 bit1VadEnable */
    HI_U8   u8VadMode;          /**< 保留，VAD模式,     对应变更标志 bit1VadMode */
    HI_U8   u8CngEnableFlag;    /**< 保留，Cng使能标志,  对应变更标志 bit1CngEnable */   
    HI_U8   u8CngLevel;         /**< 保留，CNG能量,    对应变更标志 bit1CngLevel */   
    HI_U8   u8PlcMode;          /**< 保留，PLC模式,     对应变更标志 bit1PlcMode */    
    HI_U8   u8InputGain;        /**< 输入增益 [0 ~ 15] (对应-10 dB~5 dB) , 缺省值为10 (0dB) ,  对应变更标志 bit1InputGain */
    HI_U8   u8OutputGain;       /**< 输出增益 [0 ~ 20] (对应-10dB~10dB), 缺省值为10 (0dB),  对应变更标志 bit1OutputGain */
    HI_U16  u16Rsev;
}HI_UNF_VOICE_CONFIG_BODY_S;

/** 配置dsp语音参数结构 */
typedef struct hiUNF_VOICE_CONFIG_PARA_S
{
    HI_UNF_VOICE_CHANGE_FLAG_S stChange;  /**< 变更标志位 , 修改通道属性时有效，创建通道时无效*/
    HI_UNF_VOICE_CONFIG_BODY_S stBody;    /**< 语音配置参数 */    
}HI_UNF_VOICE_CONFIG_PARA_S;

/** JB参数结构变更标志位 */
typedef struct hiUNF_JB_CHANGE_FLAG_S
{
    HI_U32   bit1JbMode:1;      /**< JB 模式   变更标志 */
    HI_U32   bit1JbInit:1;      /**< JB 初始值 变更标志 */
    HI_U32   bit1JbMax:1;       /**< JB 最大值 变更标志 */
    HI_U32   bit1JbMin:1;       /**< 保留，JB 最小值 变更标志 */
    HI_U32   bit28Resv:28;         
}HI_UNF_JB_CHANGE_FLAG_S;

/** JB参数配置 */
typedef struct hiUNF_JB_CONFIG_BODY_S
{
    HI_U8  u8JbMode;           /**< JitterBuffer模式: 0--动态JB , 1--静态JB,  对应变更标志 bit1JbMode */
    HI_U8  u8JbInit;           /**< JitterBuffer的初始值 [0 ~ 150]ms  ,对应变更标志 bit1JbInit */
    HI_U8  u8JbMax;            /**< JitterBuffer的最大值 [0 ~ 150]ms , 对应变更标志 bit1JbMax */
    HI_U8  u8JbMin;            /**< 保留，JitterBuffer的最小值  [0 ~ 150]ms  ,对应变更标志 bit1JbMin */
}HI_UNF_JB_CONFIG_BODY_S;

/** 配置JB参数结构 */
typedef struct hiUNF_JB_CONFIG_PARA_S
{
    HI_UNF_JB_CHANGE_FLAG_S stChange;  /**< 变更标志位 ,  创建通道时无效，修改通道属性时不处理JB参数*/
    HI_UNF_JB_CONFIG_BODY_S stBody;  /**< JB配置参数 */    
}HI_UNF_JB_CONFIG_PARA_S;


/** VQE参数结构变更标志位 */
/** 这里的本端是指mic输入,远端是指网络输入*/
typedef struct hiUNF_VQE_CHANGE_FLAG_S
{
    HI_U32   bit1LocalAgcFlag:1;            /**< 本端AGC 使能标志参数 变更标志 */
    HI_U32   bit1LocalAgcValue:1;           /**< 保留，本端AGC 目标值 变更标志 */ 

    HI_U32   bit1RemoteAgcFlag:1;         /**< 远端AGC 使能标志参数 变更标志 */
    HI_U32   bit1RemoteAgcValue:1;       /**< 保留，远端AGC 目标值 变更标志 */ 
    
    HI_U32   bit1LocalAnrFlag:1;            /**< 本端ANR 使能标志参数 变更标志*/ 
    HI_U32   bit1LocalAnrValue:1;           /**< 保留，ANR 目标值 变更标志 */

    HI_U32   bit1RemoteAnrFlag:1;          /**< 远端ANR 使能标志参数 变更标志*/ 
    HI_U32   bit1RemoteAnrValue:1;        /**< 保留，ANR 目标值 变更标志 */
    
    HI_U32   bit24Resv:24;         
}HI_UNF_VQE_CHANGE_FLAG_S;

/** VQE参数配置 */
typedef struct hiUNF_VQE_CONFIG_BODY_S
{
    HI_U8   u8LocalAgcFlag;          /**< 本端AGC 使能标志: 0 -- Agc Off , 1 -- Agc On , 对应变更标志 bit1LocalAgcFlag */
    HI_U8   u8LocalAgcValue;        /**< 保留，本端自动增益调整参数, 
                                                            [0 ~ 15] 对应 实际性能参数的-9dBm0 ~ -24dBm0, 缺省值13 ,
                                                            对应变更标志 bit1LocalAgcValue */
    HI_U8   u8RemoteAgcFlag;          /**< 远端AGC 使能标志: 0 -- Agc Off , 1 -- Agc On ,  对应变更标志 bit1RemoteAgcFlag */
    HI_U8   u8RemoteAgcValue;       /**< 保留，远端自动增益调整参数, 
                                                            [0 ~ 15]对应实际性能参数的-9dBm0 ~ -24dBm0, 缺省值13 ,
                                                            对应变更标志 bit1RemoteAgcValue */
    HI_U8   u8LocalAnrFlag;          /**< 本端ANR 使能标志: 0 -- Anr Off , 1 -- Anr On ,  对应变更标志 bit1LocalAnrFlag */
    HI_U8   u8LocalAnrValue;        /**< 保留，本端ANR 目标值(背景噪声抑制调整参数) ,  对应变更标志 bit1LocalAnrValue */  
    
    HI_U8   u8RemoteAnrFlag;          /**< 远端ANR 使能标志: 0 -- Anr Off, 1 -- Anr On   , 对应变更标志 bit1RemoteAnrFlag */
    HI_U8   u8RemoteAnrValue;        /**< 保留，远端ANR 目标值(背景噪声抑制调整参数)  ,   对应变更标志 bit1RemoteAnrValue */  
}HI_UNF_VQE_CONFIG_BODY_S;


/**  配置VQE参数结构 */
typedef struct hiUNF_VQE_CONFIG_PARA_S
{
    HI_UNF_VQE_CHANGE_FLAG_S stChange;  /**< 变更标志位 , 修改通道属性时有效，创建通道时无效*/
    HI_UNF_VQE_CONFIG_BODY_S stBody;  /**< VQE配置参数 */    
}HI_UNF_VQE_CONFIG_PARA_S;

/** 网络参数结构变更标志位 */
typedef struct hiUNF_NET_CHANGE_FLAG_S
{
   HI_U32   bit1SrcIP:1;     /**<source ip变更标记, 32SrcIPLen和u8SrcIP[16]有更改*/
   HI_U32   bit1DstIP:1;     /**<dest ip变更标记, u32DstIPLen和u8DstIP[16]有更改*/
   HI_U32   bit1SrcPort:1;   /**<source port 变更标记,u16SrcPort有更改*/
   HI_U32   bit1DstPort:1;   /**<dest port变更标记,u16DstPort有更改*/
   HI_U32   bit1IPTos:1;     /**<IP服务类型变更标记,u32IPTos和u32Mask有更改*/
   HI_U32   bit1Vlan:1;      /**<Vlan变更标记,u32VlanEn,u32VlanPri,u32VlanPid有更改，保留*/
   HI_U32   bit1Protocol:1;   /**<协议类型变更标记，目前只支持IPV4,保留*/
   HI_U32   bit25Resv:25;         
}HI_UNF_NET_CHANGE_FLAG_S;

/** 网络参数配置 */
typedef struct hiUNF_NET_CONFIG_BODY_S
{
   HI_U32   u32SrcIPLen;      /**<source ip地址长度，4(IPV4)或16(IPV6)，其它值无效*/
   HI_U8    u8SrcIP[16];       /**<source ip地址，4字节(IPV4)或16字节(IPV6)，不是字符串，以192.168.1.1为例，4字节依次为192,168,1,1 */
   HI_U32   u32DstIPLen;      /**<dest ip地址长度，4(IPV4)或16(IPV6)，其它值无效*/
   HI_U8    u8DstIP[16];       /**<dest ip地址，4字节(IPV4)或16字节(IPV6)，不是字符串*/

   HI_U16   u16SrcPort;        /**<source RTP 端口号，应为偶数；对应RTCP端口号为该数值+1 */
   HI_U16   u16DstPort;         /**<dest RTP 端口号，应为偶数；对应RTCP端口号为该数值+1 */

   HI_U32   u32Mask;         /**<bit0: u32IPTos valid*/
   HI_U32   u32IPTos;       /**<IP服务类型,8bit*/
   HI_U32   u32VlanEn;     /**<vlan使能: 0--vlan 无效,1--vlan 有效, 保留*/
   HI_U32   u32VlanPri;     /**<vlan优先级,3bit, vlan为1时有效, 保留*/
   HI_U32   u32VlanPid;     /**<vlan pid, 12bit, vlan为1时有效, 保留*/
   HI_U32   u32Protocol;     /**<协议类型,0x0800--IPV4, 0x86dd--IPV6, 保留*/
}HI_UNF_NET_CONFIG_BODY_S;

/** 配置网络参数结构 */
typedef struct hiUNF_NET_CONFIG_PARA_S
{
    HI_UNF_NET_CHANGE_FLAG_S stChange;  /**< 网络参数变更标志位 ,创建或修改通道时对应位必须设置*/

    HI_UNF_NET_CONFIG_BODY_S stBody;  /**< 网络配置参数 */    
}HI_UNF_NET_CONFIG_PARA_S;

/**音频设备参数变更标志*/
typedef struct hiUNF_AUDDEV_FLAG_S
{
    HI_U32   bit1AudioDevId:1;        /**< AudioDevId 变更标志 */
    HI_U32   bit1AiAttrChange:1;      /**< AI SampleRate/BitPerSample/Channels变更标志 */
    HI_U32   bit1AoAttrChange:1;      /**< AO SampleRate/BitPerSample/Channels变更标志 */
    HI_U32   bit29Resv:29;
}HI_UNF_AUDDEV_FLAG_S;

/** 音频设备系统参数 */
typedef struct hiUNF_AUDDEV_BODY_S
{
    HI_S32 s32AudioDevId;               /**< 音频设备ID , [0]*/
 
    /** 音频输入参数 */ 
    HI_S32 s32AiSampleRate;           /**< 采样率, [8000]*/
    HI_S32 s32AiBitPerSample;       /**< 采样精度, [16]*/
    HI_S32 s32AiChannels;               /**< 通道数, [1]*/
  
    /** 音频输出参数*/ 
    HI_S32 s32AoSampleRate;          /**< 采样率, [8000]*/
    HI_S32 s32AoBitPerSample;       /**< 采样精度, [16]*/
    HI_S32 s32AoChannels;               /**< 通道数, [1]*/
    
}HI_UNF_AUDDEV_BODY_S;

/** 音频设备参数*/
typedef struct hiUNF_AUDDEV_PARA_S
{
    HI_UNF_AUDDEV_FLAG_S    stChang;        /**< 音频设备参数变更标记， 修改通道属性时有效，创建通道时无效*/
    HI_UNF_AUDDEV_BODY_S    stBody;         /**< 音频设备配置参数*/
}HI_UNF_AUDDEV_PARA_S;


/** 定义VOIP 通道属性 */  
typedef struct hiUNF_VOIP_CHN_ATTR_S
{    
    HI_UNF_VOIP_TLV_HEAD_S stTlvHead; /**< 其中，u16BlockType无效，这里u16BlockLen表示整个HI_UNF_VOIP_CHN_ATTR_S 结构体长度*/
    
    HI_UNF_VOIP_TLV_HEAD_S stDspHead;           /**<  u16BlockType  为HI_UNF_VOIP_ATTR_ID_DSP, u16BlockLen为HI_UNF_VOIP_DSP_CONFIG_PARA_S结构体长度*/
    HI_UNF_VOIP_DSP_CONFIG_PARA_S stDspPara;  /**< dsp common配置参数，打开通道时是必填项，修改通道时可选*/

    HI_UNF_VOIP_TLV_HEAD_S stEcHead;            /**<  u16BlockType  为HI_UNF_VOIP_ATTR_ID_EC, u16BlockLen为HI_UNF_VOICE_CONFIG_PARA_S结构体长度*/
    HI_UNF_VOICE_CONFIG_PARA_S stEcPara;      /**<  Ec配置参数, 打开通道时是必填项，修改通道时可选*/

    HI_UNF_VOIP_TLV_HEAD_S stJBHead;         /**<  u16BlockType  为HI_UNF_VOIP_ATTR_ID_JB, u16BlockLen为HI_UNF_JB_CONFIG_PARA_S结构体长度*/
    HI_UNF_JB_CONFIG_PARA_S stJBPara;         /**<  JB配置参数, 打开通道时是必填项，修改通道时无效*/
    
    HI_UNF_VOIP_TLV_HEAD_S stVQEHead;           /**<  u16BlockType  为HI_UNF_VOIP_ATTR_ID_VQE, u16BlockLen为HI_UNF_VQE_CONFIG_PARA_S结构体长度*/
    HI_UNF_VQE_CONFIG_PARA_S stVQEPara;       /**<  VQE配置参数，打开通道时是必填项，修改通道时可选*/

    HI_UNF_VOIP_TLV_HEAD_S stNetHead;           /**<  u16BlockType  为HI_UNF_VOIP_ATTR_ID_NET, u16BlockLen为HI_UNF_NET_CONFIG_PARA_S结构体长度*/
    HI_UNF_NET_CONFIG_PARA_S stNetPara;       /**<  NET配置参数，可选项*/
    
    HI_UNF_VOIP_TLV_HEAD_S stAudevHead;    /**<  u16BlockType  为HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV, u16BlockLen为HI_UNF_AUDDEV_PARA_S结构体长度*/        
    HI_UNF_AUDDEV_PARA_S   stAudevPara;     /**<  音频设备配置参数，打开通道为必填项，修改通道时可选*/
}HI_UNF_VOIP_CHN_ATTR_S;

/** 基本频率描述，保留*/
typedef struct hiUNF_VOIP_BASE_FREQ_INFO_S
{
    HI_U16  u16Frequence;        /**< 基波频率*/
    HI_U16  u16Amplitude;        /**< 基波幅度*/
}HI_UNF_VOIP_BASE_FREQ_INFO_S;

/** 基本节拍描述，保留*/
typedef struct hiUNF_VOIP_CADENCE_INFO_S
{
    HI_U16  u16FreqFlag;         /**< 使用的基波标志*/
    HI_U16  u16Reserved;         /**< 保留域*/
    HI_U16  u16OnTime;           /**< 有效时间*/
    HI_U16  u16OffTime;          /**< 静音时间*/
}HI_UNF_VOIP_CADENCE_INFO_S;

/** 回铃音参数描述，保留*/
typedef struct hiUNF_VOIP_TONE_ATTR_S
{
    HI_UNF_VOIP_BASE_FREQ_INFO_S   stBaseFreqInfo[4]; /**< 基本频率描述*/
    HI_U32                u32CadenceCount;    /**< 节拍的数量*/
    HI_U32                u32Resve;
    HI_UNF_VOIP_CADENCE_INFO_S     stCadenceInfo[8]; /**< 节拍描述*/
}HI_UNF_VOIP_TONE_ATTR_S;

/** 回铃音播放属性描述符，保留*/
typedef struct hiUNF_VOIP_PLAY_TONE_ATTR_S
{   
    HI_UNF_VOIP_TONE_ATTR_S stToneParam;    /**< 回铃音参数，保留*/
    HI_U32 u32MixFlag;                                      /**< 混音标志: 0--不混音, 1--混音*/
    HI_U32 u32LoopTime;                                 /**< 重复次数: 0--不重复, 1~254 -- 重复次数, 255 -- 一直播放*/
}HI_UNF_VOIP_PLAY_TONE_ATTR_S; 

/** 音频文件播放属性描述符*/
typedef struct hiUNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S
{   
    HI_U32 u32DataAddr;         /**< 音频文件地址*/
    HI_U32 u32DataLen;            /**< 音频文件长度*/
    HI_U16 u16SourceFormat;  /**< 音频文件编码类型: 0 -- G.711A, 1 -- G.711Mu
                                            注: 目前只支持播放711类型的标准wav文件，且文件为纯净荷。*/
    HI_U16 u16Resv;
    HI_U32 u32MixFlag;            /**< 混音标志: 0--不混音, 1--混音*/
    HI_U32 u32Direction;         /**< 播放方向: 0--播放到本端, 1-- 播放到远端(保留)*/
    HI_U32 u32LoopTime;         /**< 重复次数: 0--不重复, 1~254 -- 重复次数, 255 -- 一直播放*/
}HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S;


/** 网络质量信息描述符*/
typedef struct hiUNF_VOIP_NET_QUALITY_STATIC_INFO_S
{
    HI_U32 u32TotalLostPacket;              /**< 数据丢包统计*/
    HI_U32 u32LossFraction;                  /**< 丢包率(%) */
    HI_U32 u32Jitter;                               /**< 平均抖动(ms) */
    HI_U32 u32Delay;                              /**< 平均时延(ms) */
}HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S; 

/** RTCP统计信息描述符 */
typedef struct hiUNF_VOIP_RTCP_STATIC_INFO_S
{
    HI_U32 u32SendPacketNum;                /**< 发送包总数*/
    HI_U32 u32SendBytes;                            /**< 发送字节数*/
    HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S stSendInfo;          /**< 发送统计*/
    HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S stRecvInfo;          /**< 接收统计*/
}HI_UNF_VOIP_RTCP_STATIC_INFO_S;

/** RTCP配置描述符*/
typedef struct hiUNF_VOIP_CFG_RTCP_ATTR_S
{   
    HI_U32 u32EnableFlag;               /**< RTCP统计使能: 0--不使能, 1--使能*/
    HI_U32 u32SendInterval;             /**< RTCP报告发送间隔, [500 ~ 65535] ms , 必须为500ms的整数倍*/
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
/** @{ */  /** <!-- 【VOIP】 */

/**
 \brief 初始化VOIP模块
 \attention \n
 \param 无
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_DEV_OPEN_ERR  设备打开错误
 \retval ::HI_ERR_VOIP_HME_DEV_NOT_EXIST  设备不存在
 \retval ::HI_ERR_VOIP_HME_NOT_DEV_FILE  不是设备文件
 \retval ::HI_ERR_VOIP_HME_NO_INIT    EVENT初始化失败
 \see \n
无
 */
HI_S32 HI_UNF_VOIP_Init(HI_VOID);

/**
 \brief 去初始化VOIP模块
 \attention \n
 \param 无
 \retval ::0  成功
 \see \n
无
 */
HI_S32 HI_UNF_VOIP_DeInit(HI_VOID);

/**
 \brief 获取缺省的VOIP 通道配置
 \attention \n
        请正确输入想要创建VOIP 通道工作模式，目前只支持语音模式HI_UNF_VOIP_MODE_VOIVE
        创建VOIP 通道前建议调用本接口，获取到默认属性，避免创建VOIP 通道时由于参数不全或参数错误导致创建不成功现象
 \param[in] enWorkMode       VOIP 通道工作模式，请参见::HI_UNF_VOIP_WORKMODE_E
 \param[out] pstDefChAttr  指针类型，VOIP 通道默认属性，参见:HI_UNF_VOIP_CHN_ATTR_S
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \see \n
无
 */
HI_S32 HI_UNF_VOIP_GetChDefaultAttr(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstDefChAttr);

/**
 \brief 创建VOIP 通道
 \attention \n
 创建通道前，建议先调用HI_UNF_VOIP_GetChDefaultAttr()获取默认通道属性，再对参数做必要修改。
 \param[in] enWorkMode       VOIP 通道工作模式，请参见::HI_UNF_VOIP_WORKMODE_E
 \param[in]  pstChAttr  指针类型，VOIP 通道属性，请参见::HI_UNF_VOIP_CHN_ATTR_S
 \param[out] phVoip   指针类型，创建的VOIP 通道句柄
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::HI_ERR_VOIP_HME_CREATE_ERR   创建通道失败
 \retval ::其它  创建通道失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_CreateChannel(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVoip);


/**
 \brief 销毁VOIP 通道
 \attention \n
无
 \param[in] hVOIP  VOIP 通道句柄
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA  无效参数
 \retval ::HI_ERR_VOIP_HME_DESTROY_ERR   销毁通道失败
 \retval ::其它  销毁通道失败
 \see \n
无
 */
 HI_S32 HI_UNF_VOIP_DestroyChannel(HI_HANDLE hVoip);

/**
 \brief 获取VOIP 通道配置
 \attention \n
 \param[in] hVOIP  VOIP 通道句柄
 \param[out] pstChAttr  指针类型，VOIP 通道属性，参见:HI_UNF_VOIP_CHN_ATTR_S
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::其它  获取通道属性失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_GetChAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);

/**
 \brief 修改VOIP 通道配置
 \attention \n
        建议先调用HI_UNF_VOIP_GetChAttr()获取当前通道配置，再对参数做必要修改，对应的更改标记置1，无关更改标志置0。
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] pstChAttr  指针类型，VOIP 通道属性，参见:HI_UNF_VOIP_CHN_ATTR_S
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::其它  修改通道属性失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_ModifyChnAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);

#if 0
/**
 \brief 获取VOIP 通道子属性
 \attention \n
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] enAttrID  VOIP 通道配置参数ID，参见: HI_UNF_VOIP_ATTR_ID_E
 \param[out] pChSubAttr  指针类型，VOIP 通道子属性，结构体与enAttrID 对应。
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::其它  获取通道属性失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_GetChSubAttr(HI_HANDLE hVoip, HI_UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr);

/**
 \brief 修改VOIP 通道子属性
 \attention \n
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] enAttrID  VOIP 通道配置参数ID，参见: HI_UNF_VOIP_ATTR_ID_E
 \param[in] pChSubAttr  指针类型，VOIP 通道子属性，结构体与enAttrID 对应。
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::其它  修改通道属性失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_ModifyChnSubAttr(HI_HANDLE hVoip, HI_UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr);

/**
 \brief 播放回铃音
 \attention \n
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] pstToneAttr  指针类型，回铃音播放参数，参见: HI_UNF_VOIP_PLAY_TONE_ATTR_S
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::其它  播放回铃音失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_PlayTone(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr);

/**
 \brief 停止播放回铃音
 \attention \n
 \param[in] hVOIP  VOIP 通道句柄
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::其它  停止播放回铃音失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_StopTone(HI_HANDLE hVoip);
#endif

/**
 \brief 播放音频文件
 \attention \n
        目前只支持播放711类型的标准wav文件，且文件为纯净荷。
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] pstAnnAttr  指针类型，音频文件播放参数，参见: HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::其它  播放音频文件失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_PlayAnnouncement(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr);

/**
 \brief 停止播放音频文件
 \attention \n
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] u32Direction  播放方向，必须与音频文件播放属性中的u32Direction 保持一致。
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::其它  停止 播放音频文件失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_StopAnnouncement(HI_HANDLE hVoip, HI_U32 u32Direction);

/**
 \brief 定义事件回调函数类型
 \attention \n
无
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] enEvent     枚举类型，表示事件类型，参见: HI_UNF_VOIP_EVENT_E 定义
 \param[in] s32EventValue  事件类型参数，用于为event附带一些输出参数， 比如错误事件的错误码
 \param[in] args        注册时传入的args参数。
 \retval ::0  成功
 \retval ::其它  失败
 \see \n
无
 */
typedef HI_S32 (*HI_UNF_VOIP_EVENT_CB_FN)(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_E enEvent, HI_S32 s32EventValue, HI_U32 u32Args);


/**
 \brief 注册事件
 \attention \n
无
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] pfnEventCB  回调函数指针，指向与注册事件对应的回调函数。指针为NULL表示UnRegister
 \param[in] args        回调函数私有参数，此参数在回调函数被调用的时候会传递给回调函数。
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NOT_EXIST   通道不存在
 \see \n
无
 */
HI_S32 HI_UNF_VOIP_RegisterEvent(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);


/**
 \brief 获取RTCP统计信息
 \attention \n
 \param[in] hVOIP  VOIP 通道句柄
 \param[out] pstRtcpInfo  指针类型，RTCP统计信息，参见: HI_UNF_VOIP_RTCP_STATIC_INFO_S
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::其它  获取RTCP统计信息失败
 \see \n
无
 */

HI_S32 HI_UNF_VOIP_GetRtcpStaticInfo(HI_HANDLE hVoip, HI_UNF_VOIP_RTCP_STATIC_INFO_S * pstRtcpInfo);

/**
 \brief  RTCP配置
 \attention \n
 \param[in] hVOIP  VOIP 通道句柄
 \param[in] pstRtcpAttr  指针类型，RTCP配置，参见: HI_UNF_VOIP_CFG_RTCP_ATTR_S
 \retval ::0  成功
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  空指针
 \retval ::其它  RTCP配置失败
 \see \n
无
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
无
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
无
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
无
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
无
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
无
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
无
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
无
 */

HI_S32 HI_UNF_AUDADP_RegisterEvent(HI_UNF_AUDADP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
