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
 * \brief 提供SOUND的相关信息
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
/** @{ */  /** <!-- 【SOUND】 */

/**定义音频输出设备号*/
typedef enum hiUNF_SND_E
{
    HI_UNF_SND_0,           /**<音频输出设备0 */
    HI_UNF_SND_BUTT    
} HI_UNF_SND_E;


/**定义音频输出接口类型*/
typedef enum hiUNF_SND_INTERFACE_E
{
    HI_UNF_SND_INTERFACE_I2S,      /**<I2S（Inter-IC Sound）模式 */
    HI_UNF_SND_INTERFACE_SPDIF,    /**<SPDIF（Sony/Philips Digital Interface）模式 */
    HI_UNF_SND_INTERFACE_HBR,    /**<SPDIF（Sony/Philips Digital Interface）模式 */
    HI_UNF_SND_INTERFACE_BUTT
}HI_UNF_SND_INTERFACE_E;


/**音频混音类型 */
typedef enum hiHI_UNF_SND_MIX_TYPE_E
{
    HI_UNF_SND_MIX_TYPE_MASTER,     /**<作为主音 */
    HI_UNF_SND_MIX_TYPE_SLAVE,      /**<作为混音 */
    HI_UNF_SND_MIX_TYPE_BUTT 
} HI_UNF_SND_MIX_TYPE_E;


/**定义音频输出模式结构体*/
typedef struct hiUNF_SND_INTERFACE_S
{
    HI_UNF_SND_INTERFACE_E  enInterface;     /**<音频接口输出类型 */
    HI_BOOL                 bEnable;         /**<是否使能音频输出 */
}HI_UNF_SND_INTERFACE_S;

/**定义音频输出属性结构体*/
typedef struct hiHI_UNF_SND_ATTR_S
{

    HI_U32              u32MasterOutputBufSize; /**<主音回放缓冲区空间大小. unit:byte, note: size must 64 time word8 */
    HI_U32              u32SlaveOutputBufSize; /**<辅音回放缓冲区空间大小. unit:byte, note: size must 64 time word8 */
    HI_BOOL            bMixerEngineSupport;   /**< if bMixerEngineSupport == HI_TRUE,  UNF_SND support MixerEngine,slave pcm is repalced by one mixer of the MixerEngine,
    									  if bMixerEngineSupport == HI_FALSE, UNF_SND dont support MixerEngine default: HI_FALSE
    									  */  
} HI_UNF_SND_ATTR_S;

/**Audio Mixer attribute                                               			*/
typedef struct hiHI_UNF_MIXER_ATTR_S
{
    HI_U32              u32MixerWeight;    /**< 混音权重: 0~100 */
    HI_U32              u32MixerBufSize;   /**< 混音器缓冲区大小(1024*16) ~ (1024*1024), unit:byte */
} HI_UNF_MIXER_ATTR_S;

typedef struct hiHI_UNF_MIXER_STATUSINFO_S
{
    HI_S32 u32MixerID;   /**< 混音器硬件ID : 范围0~7 */
    HI_S32 u32Working;   /**< 混音器工作状态: 0 : stop, 1: pause, 2:running */

    HI_U32 u32BufferSize;           /**< 混音器缓冲区大小unit: byte.*/
    HI_U32 u32BufferByteLeft;      /**< 混音器缓冲区音频数据剩余 unit : byte.*/
    HI_BOOL bDataNotEnough;      /**< HI_FALSE : data is enough, HI_TRUE: data is not enough,need more data */
    HI_U32  u32BufDurationMs;    /**< 混音器缓冲区剩余音频数据可播放时长  unit : MS.*/

} HI_UNF_MIXER_STATUSINFO_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_4 */
/** @{ */  /** <!-- 【SOUND】 */

/** 
\brief 初始化音频输出设备
\attention \n
调用SND模块要求首先调用该接口
\param 无
\retval HI_SUCCESS 成功
\see \n
无
*/
HI_S32 HI_UNF_SND_Init(HI_VOID);


/** 
\brief 去初始化音频输出设备
\attention \n
无
\param 无
\retval HI_SUCCESS 成功
\see \n
无
*/
HI_S32 HI_UNF_SND_DeInit(HI_VOID);

/** 
\brief 设置音频输出设备, 
\attention \n
 必须在HI_UNF_SND_Open 前调用，否则按照默认方式打开音频设备
\param[in] enSound     音频输出设备号
\param[in] pstAttr     音频设置属性
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetOpenAttr(HI_UNF_SND_E enSound,HI_UNF_SND_ATTR_S *pstAttr);

/** 
\brief 获取音频输出设备设置参数
\attention \n
\param[in] enSound     音频输出设备号
\param[out] pstAttr     音频属性
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetOpenAttr(HI_UNF_SND_E enSound, HI_UNF_SND_ATTR_S *pstAttr);

/** 
\brief 打开音频输出设备
\attention \n
无
\param[in] enSound     音频输出设备号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_CREATE_FAIL	    打开设备失败
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_Open(HI_UNF_SND_E enSound);


/** 
\brief 销毁音频输出Sound实例
\attention \n
不支持重复销毁
\param[in] enSound   音频输出设备号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_INVALID_PARA	无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_Close(HI_UNF_SND_E enSound);

/** 
\brief 设置音频输出端口使能控制
\attention \n
可以分别控制模拟I2S输出和SPDIF输出
\param[in] enSound        音频输出设备号
\param[in] pInterface    指针类型，音频输出模式结构体，请参见::HI_UNF_SND_INTERFACE_S
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN       Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetInterface(HI_UNF_SND_E enSound, const HI_UNF_SND_INTERFACE_S *pInterface);


/** 
\brief 获取音频输出端口使能状态
\attention \n
第二个参数中结构体的第一个参数（enInterface）为输入参数，第二个参数（bEnable）为输出参数
\param[in] enSound           音频输出设备号
\param[in/out] pInterface   指针类型。音频输出模式结构体，请参见::HI_UNF_SND_INTERFACE_S
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetInterface(HI_UNF_SND_E enSound, HI_UNF_SND_INTERFACE_S *pInterface);


/** 
\brief 音频模拟输出的静音开关设置
\attention \n
无
\param[in] enSound   音频输出设备号
\param[in] bMute    模拟输出静音开关。HI_TRUE：静音；HI_FALSE：非静音
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN       Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetAnalogMute(HI_UNF_SND_E enSound, HI_BOOL bMute);


/** 
\brief 获取音频模拟输出的静音开关状态
\attention \n
无
\param[in] enSound     音频输出设备号
\param[out] pbMute    指针类型。HI_TRUE：静音；HI_FALSE：非静音
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetAnalogMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);


/** 
\brief 音频数字输出的静音开关设置
\attention \n
无
\param[in] enSound   音频输出设备号
\param[in] bMute    数字输出静音开关。HI_TRUE：静音；HI_FALSE：非静音
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetDigitalMute(HI_UNF_SND_E enSound, HI_BOOL bMute);


/** 
\brief 获取音频数字输出的静音开关状态
\attention \n
无
\param[in] enSound   音频输出设备号
\param[out] pbMute  指针类型。HI_TRUE：静音；HI_FALSE：非静音
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN       Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetDigitalMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);


/** 
\brief 音频数字和模拟输出的静音开关设置
\attention \n
\param[in] enSound
\param[in] bMute
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetMute(HI_UNF_SND_E enSound, HI_BOOL bMute);


/** 
\brief 获取音频数字和模拟输出的静音开关状态
\attention \n
\param[in] enSound
\param[in] pbMute
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);

/** 
\brief 音频模拟输出的DAC静音开关设置
\attention \n
用于模拟输出静音而保留HDMI声音输出的场景，一般情况下不需要使用
\param[in] enSound   音频输出设备号
\param[in] bMute    DAC静音开关。HI_TRUE：静音；HI_FALSE：非静音
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetADACMute(HI_UNF_SND_E enSound, HI_BOOL bMute);


/** 
\brief 获取音频模拟输出的DAC的静音开关状态
\attention \n
无
\param[in] enSound   音频输出设备号
\param[out] pbMute  指针类型。HI_TRUE：静音；HI_FALSE：非静音
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN       Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetADACMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);

/** 
\brief 设置SPDIF 音频数据输出
\attention \n
使用该接口时，音频解码模式必须设定为:HD_DEC_MODE_SIMUL(PCM + 透传解码模式)
同时，对于SPDIF接口，不管输出什么数据，必须使能INTERFACE_SPDIF
\param[in] enSound   音频输出设备号
\param[in] bEnable   透传数据输出开关。HI_TRUE：输出透传数据；HI_FALSE：输出PCM数据
\retval ::HI_SUCCESS 成功
\see \n
无
*/
HI_S32 HI_UNF_SND_SetSpdifPassThrough(HI_UNF_SND_E enSound, HI_BOOL bEnable);

/** 
\brief set HDMI pass-torough
\attention \n
sure audio decoder work at HD_DEC_MODE_SIMUL mode
\param[in] enSound  
\param[in] bEnable , HI_TRUE: pass-torough enable HI_FALSE:  pass-torough disable
\retval ::HI_SUCCESS 成功
\see \n
无
*/
HI_S32 HI_UNF_SND_SetHdmiPassThrough(HI_UNF_SND_E enSound, HI_BOOL bEnable);


/** 
\brief 设置输出音量
\attention \n
如果u32Volume设置大于100，默认设置的值为100
\param[in] enSound        音频输出设备号
\param[in] u32Volume     设置的音量值，范围0～100。0：静音；100：最大音量
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetVolume(HI_UNF_SND_E enSound, HI_U32 u32Volume);


/** 
\brief 获取输出音量
\attention \n
查询的默认音量值为100
\param[in] enSound         音频输出设备号
\param[out] pu32Volume    指针类型，获取到的音量值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetVolume(HI_UNF_SND_E enSound, HI_U32 *pu32Volume);


/** 
\brief 设置音频输出时的采样率
\attention \n
目前暂不支持采样率设置，输出采样率固定为48k，非48k采样率码流重采样为48k输出
\param[in] enSound          音频输出设备号
\param[in] enSampleRate    音频采样率。请参见::HI_UNF_SAMPLE_RATE_E
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetSampleRate(HI_UNF_SND_E enSound, HI_UNF_SAMPLE_RATE_E enSampleRate);


/** 
\brief 获取音频输出时的采样率
\attention \n
此接口默认返回48kHz采样率
\param[in] enSound           音频输出设备号
\param[out] penSampleRate   指针类型，音频采样率的类型
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetSampleRate(HI_UNF_SND_E enSound, HI_UNF_SAMPLE_RATE_E *penSampleRate);


/** 
\brief 音频输出自动进行重采样开关设置
\attention \n
默认已经打开重采样，不允许关闭\n
目前仅支持源采样率为8kHz、16kHz、22.05kHz、24kHz、32kHz、44.1kHz和48kHz，默认以48kHz输出\n
如果通过本接口设置bAutoResample为HI_TRUE，则此接口将直接返回成功\n
如果通过本接口设置bAutoResample为HI_FALSE，则此接口将直接返回HI_UNF_ERR_SND_NOTSUPPORT错误码
\param[in] enSound            音频输出设备号
\param[in] bAutoResample     是否自动重采样。HI_TRUE：设置自动重采样；HI_FALSE：不设置自动重采样
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetAutoResample(HI_UNF_SND_E enSound, HI_BOOL bAutoResample);


/** 
\brief 获取音频输出自动重采样开关状态
\attention \n
无
\param[in] enSound              音频输出设备号
\param[out] pbAutoResample     指针类型，是否自动重采样
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetAutoResample(HI_UNF_SND_E enSound, HI_BOOL *pbAutoResample);

/** 
\brief 音频输出进行智能音量处理处理开关设置
\attention \n
1. 默认关闭该智能音量\n
2. 智能音量仅对主音有效\n
3. 智能音量仅在切换节目时触发
\param[in] enSound        音频输出设备号
\param[in] bSmartVolume     是否打开智能音量。HI_TRUE：打开；HI_FALSE：关闭
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetSmartVolume(HI_UNF_SND_E enSound, HI_BOOL bSmartVolume);

/** 
\brief 获取音频输出智能音量开关状态\attention \n
\param[in] enSound        音频输出设备号
\param[out] pbSmartVolume     指针类型，是否打开智能音量
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetSmartVolume(HI_UNF_SND_E enSound, HI_BOOL *pbSmartVolume);


/** 
\brief 设置音频输出声道模式
\attention \n
无
\param[in] enSound     音频输出设备号
\param[in] enMode     音频声道模式，请参见::HI_UNF_TRACK_MODE_E
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetTrackMode(HI_UNF_SND_E enSound, HI_UNF_TRACK_MODE_E enMode);


/** 
\brief 获取音频输出声道模式
\attention \n
无
\param[in] enSound     音频输出设备号
\param[out] penMode   指针类型，音频声道模式。请参见::HI_UNF_TRACK_MODE_E
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	    Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR           指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	    无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetTrackMode(HI_UNF_SND_E enSound, HI_UNF_TRACK_MODE_E *penMode);


/** 
\brief 绑定音频输出Sound和AV（Audio Video）播放器
\attention \n
调用此接口前必须先创建播放器，对应这路播放器没有输出
\param[in] enSound          音频输出设备号
\param[in] hSource         
\param[in] enMixType       AV播放器播放实例句柄
\param[in] u32MixWeight    权重，范围为0～100。0：最小值；100：最大值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PORT	        无效绑定类型
\retval ::HI_ERR_HIAO_INVALID_PARA	        无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_Attach(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_UNF_SND_MIX_TYPE_E enMixType, HI_U32 u32MixWeight);


/** 
\brief 解除Sound和AV播放器绑定
\attention \n
无
\param[in] enSound     音频输出设备号
\param[in] hSource    AV播放器播放实例句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	        无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_Detach(HI_UNF_SND_E enSound, HI_HANDLE hSource);


/** 
\brief 设置音频播放器混音权重
\attention \n
两个播放器输出音量的计算方法为：（设置的音量%权重1+设置的音量%权重2）/100，多个播放器的计算方法与此类似
\param[in] enSound              音频输出设备号
\param[in] hSource             AV播放器播放实例句柄
\param[in] u32MixWeight        权重，范围为0～100。0：最小值；100：最大值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	        无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetMixWeight(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_U32 u32MixWeight);


/** 
\brief 获取音频播放器混音权重
\attention \n

\param[in] enSound            音频输出设备号
\param[in] hSource           AV播放器播放实例句柄
\param[in] pu32MixWeight     指针类型，权重值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR               指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	        无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetMixWeight(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_U32 *pu32MixWeight);

/** 
\brief 设置音频播放器淡入淡出时间
\attention \n
\param[in] enSound             音频输出设备号
\param[in] hSource             AV播放器播放实例句柄
\param[in] u32FadeinMs         淡入时间，单位为毫秒，最大取值2000
\param[in] u32FadeoutMs        淡出时间，单位为毫秒，最大取值500
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio设备未打开
\retval ::HI_ERR_HIAO_INVALID_PARA	        无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_SetFadeTime(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_U32 u32FadeinMs, HI_U32 u32FadeoutMs);

/** 
\brief 获取音频播放器淡入淡出时间
\attention \n
\param[in] enSound           音频输出设备号
\param[in] hSource           AV播放器播放实例句柄
\param[in] pu32FadeinMs      指针类型，淡入时间
\param[in] pu32FadeoutMs     指针类型，淡出时间
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_HIAO_DEV_NOT_OPEN	        Audio设备未打开
\retval ::HI_ERR_HIAO_NULL_PTR               指针参数为空
\retval ::HI_ERR_HIAO_INVALID_PARA	        无效的参数
\see \n
无
*/
HI_S32 HI_UNF_SND_GetFadeTime(HI_UNF_SND_E enSound, HI_HANDLE hSource, HI_U32 *pu32FadeinMs, HI_U32 *pu32FadeoutMs);

/** 
\brief 打开一个混音器
\attention \n
只有HI_UNF_SND_Open 成功后，才能操作混音设备
\param[in] enSound   音频输出设备号
\param[out] phMixer   指针类型，创建的混音器 句柄
\param[in] pstMixerAttr    指针类型，混音器属性
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_SND_INVALID_ID	无效的参数
\retval ::HI_ERR_SND_INVALID_PARA	无效的参数
\see \n
无
*/
HI_S32   HI_UNF_SND_Mixer_Open(HI_UNF_SND_E enSound,HI_HANDLE *phMixer, HI_UNF_MIXER_ATTR_S *pstMixerAttr);

/** 
\brief 关闭 一个混音器
\attention \n
无
\param[in] hMixer   混音器句柄
\retval ::HI_SUCCESS 成功
\see \n
无
*/
HI_S32   HI_UNF_SND_Mixer_Close(HI_HANDLE hMixer);

/** 
\brief 启动混音器
\attention \n
无
\param[in] hMixer   混音器句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_SND_INVALID_PARA	无效的参数
\see \n
无
*/
HI_S32   HI_UNF_SND_Mixer_Start(HI_HANDLE hMixer);

/** 
\brief 停止混音器
\attention \n
缓冲区数据将会丢弃
\param[in] hMixer   混音器句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_SND_INVALID_PARA	无效的参数
\see \n
无
*/
HI_S32   HI_UNF_SND_Mixer_Stop(HI_HANDLE hMixer);

/** 
\brief 暂停混音器
\attention \n
缓冲区数据仍然保留
\param[in] hMixer   混音器句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_SND_INVALID_PARA	无效的参数
\see \n
无
*/
HI_S32   HI_UNF_SND_Mixer_Pause(HI_HANDLE hMixer);

/** 
\brief  混音器状态复位
\attention \n
无
\param[in] hMixer   混音器句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_SND_INVALID_PARA	无效的参数
\see \n
无
*/
HI_S32   HI_UNF_SND_Mixer_Flush(HI_HANDLE hMixer);

/** 
\brief  获取混音器状态信息
\attention \n
无
\param[in] hMixer   混音器句柄
\param[out] pstStatus   混音器句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_SND_NULL_PTR	无效的参数
\retval ::HI_ERR_SND_INVALID_PARA	无效的参数
\see \n
无
*/
HI_S32   HI_UNF_SND_Mixer_GetStatus(HI_HANDLE hMixer, HI_UNF_MIXER_STATUSINFO_S *pstStatus);

/** 
\brief  送数据到混音器
\attention \n
1 如果返回HI_ERR_HIAO_OUT_BUF_FULL，需要调度者继续送上次失败数据，才能保证声音的连续
2 PCM 数据格式在混音器的限制如下
    s32BitPerSample: 必须为16
    bInterleaved: 必须为HI_TRUE, 仅支持交织模式
    u32Channels: 1 或2
    u32PtsMs: 忽略该参数
    ps32PcmBuffer: PCM 数据指针
    ps32BitsBuffer: 忽略该参数
    u32PcmSamplesPerFrame: 音频样点数, 数据长度(unit:Bytes): u32PcmSamplesPerFrame*u32Channels*sizeof(HI_u16)
    u32BitsBytesPerFrame: 忽略该参数
    u32FrameIndex: 忽略该参数
\param[in] hMixer   混音器句柄
\param[out] pstAOFrame   音频数据信息
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_SND_NULL_PTR	无效的参数
\retval ::HI_ERR_SND_INVALID_PARA	无效的参数
\retval ::HI_ERR_HIAO_OUT_BUF_FULL,混音缓冲区数据满，送数据失败
\see \n
无
*/

HI_S32	 HI_UNF_SND_Mixer_SendData(HI_HANDLE hMixer, const HI_UNF_AO_FRAMEINFO_S *pstAOFrame);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif  /*__HI_UNF_SND_H__*/

