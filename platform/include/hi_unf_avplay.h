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
 * \brief 提供AVPLAY的相关信息
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
/** @{ */  /** <!-- 【AVPLAY】 */

/**视频解码器的最大优先级*/
#define HI_UNF_VCODEC_MAX_PRIORITY  16


/**定义AV播放器中需要的BufferID枚举类型 */
typedef enum hiUNF_AVPLAY_BUFID_E
{
    HI_UNF_AVPLAY_BUF_ID_ES_VID  = 0,    /**<AV播放器ES视频Buffer ID*/
    HI_UNF_AVPLAY_BUF_ID_ES_AUD  = 1,    /**<AV播放器ES音频Buffer ID*/
    HI_UNF_AVPLAY_BUF_ID_BUTT
} HI_UNF_AVPLAY_BUFID_E;

/********************************************************************************/
/**定义媒体通道类型 */
typedef enum hiUNF_AVPLAY_MEDIA_CHAN
{
    HI_UNF_AVPLAY_MEDIA_CHAN_AUD  = 0x01,  /**< 音频通道 */
    HI_UNF_AVPLAY_MEDIA_CHAN_VID  = 0x02,  /**< 视频通道 */

    HI_UNF_AVPLAY_MEDIA_CHAN_BUTT = 0x8
} HI_UNF_AVPLAY_MEDIA_CHAN_E;


/**定义数据输入流接口类型 */
typedef enum hiUNF_AVPLAY_STREAM_TYPE_E
{
    HI_UNF_AVPLAY_STREAM_TYPE_TS = 0,   /**< ts  stream */
    HI_UNF_AVPLAY_STREAM_TYPE_ES,       /**< es  stream */
	HI_UNF_AVPLAY_STREAM_TYPE_VP,       /**< vp  stream */
    HI_UNF_AVPLAY_STREAM_TYPE_BUTT
} HI_UNF_AVPLAY_STREAM_TYPE_E;

/********************************************************************************/

/**定义码流属性的结构体 */
typedef struct hiUNF_AVPLAY_STREAM_ATTR_S
{
    HI_UNF_AVPLAY_STREAM_TYPE_E enStreamType;   /**< 码流类型 */

    HI_U32                      u32VidBufSize;  /**< 视频缓冲大小 */
    HI_U32                      u32AudBufSize;  /**< 音频缓冲大小 */

	HI_UNF_VP_NET_PARA_S        stNetCfgPara;		  /**< 网络参数，码流类型为VP时有效 */

} HI_UNF_AVPLAY_STREAM_ATTR_S;

/**支持的同步控制模式 */
typedef enum hiUNF_SYNC_REF_E
{
    HI_UNF_SYNC_REF_NONE = 0, /**< 自由播放*/
    HI_UNF_SYNC_REF_AUDIO,    /**< 以音频为准  */
    HI_UNF_SYNC_REF_VIDEO,    /**< 以视频为准  */
    HI_UNF_SYNC_REF_PCR,      /**< 以PCR（Program Clock Reference）为准 */

    HI_UNF_AVPLAY_SYNC_REF_BUTT
} HI_UNF_SYNC_REF_E;


/**定义使用的缓冲区状态枚举类型 */
typedef enum hiUNF_AVPLAY_BUF_STATE_E
{
    HI_UNF_AVPLAY_BUF_STATE_EMPTY = 0,   /**<缓冲区空闲*/
    HI_UNF_AVPLAY_BUF_STATE_LOW,         /**<缓冲区占用率过低*/
    HI_UNF_AVPLAY_BUF_STATE_NORMAL,      /**<缓冲区使用正常*/
    HI_UNF_AVPLAY_BUF_STATE_HIGH,        /**<缓冲区占用率过高*/
    HI_UNF_AVPLAY_BUF_STATE_FULL         /**<缓冲区已满*/
}HI_UNF_AVPLAY_BUF_STATE_E;


/**事件回调函数类型 */
typedef enum hiUNF_AVPLAY_EVENT_E
{
    HI_UNF_AVPLAY_EVENT_EOS,                   /**< EOS执行结束, NULL    */
    HI_UNF_AVPLAY_EVENT_STOP,                  /**< STOP执行结束, NULL   */
    HI_UNF_AVPLAY_EVENT_RNG_BUF_STATE,         /**< 媒体缓存队列状态变化, HI_UNF_AVPLAY_EVENT_RNG_BUF_STATE */
    HI_UNF_AVPLAY_EVENT_NORM_SWITCH,           /**< 制式切换, HI_UNF_ENC_FMT_E        */
    //HI_UNF_AVPLAY_EVENT_NEW_SEQ,                        /**< 新序列信息, HI_UNF_VIDEO_SEQUENCE_INFO_S    */
    HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME,         /**< 新视频帧, HI_UNF_VO_FRAMEINFO_S             */
    HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME,         /**< 新音频帧, HI_UNF_AO_FRAMEINFO_S             */
    HI_UNF_AVPLAY_EVENT_NEW_USER_DATA,         /**< 新视频用户数据, HI_UNF_VIDEO_USERDATA_S     */
    HI_UNF_AVPLAY_EVENT_GET_AUD_ES,            /**< 新音频ES数据, HI_UNF_ES_BUF_S     */
    HI_UNF_AVPLAY_EVENT_BUTT
} HI_UNF_AVPLAY_EVENT_E;

/**缓冲溢出处理类型 */
typedef enum hiUNF_AVPLAY_OVERFLOW_E
{
    HI_UNF_AVPLAY_OVERFLOW_RESET,              /**< 溢出时进行复位  */
    HI_UNF_AVPLAY_OVERFLOW_DISCARD,            /**< 溢出时进行丢弃  */
    HI_UNF_AVPLAY_OVERFLOW_BUTT
} HI_UNF_AVPLAY_OVERFLOW_E;

/**定义事件回调函数枚举类型*/
typedef HI_S32 (*HI_UNF_AVPLAY_EVENT_CB_FN)(HI_HANDLE hAvplay, HI_UNF_AVPLAY_EVENT_E enEvent, HI_U32 u32Para);

/**定义AV播放器属性ID枚举类型 */
typedef enum hiUNF_AVPLAY_ATTR_ID_E
{
    HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE = 0,  /**< 播放模式 , HI_UNF_AVPLAY_ATTR_S */

    HI_UNF_AVPLAY_ATTR_ID_ADEC,             /**< 音频属性 , HI_UNF_ACODEC_ATTR_S */
    HI_UNF_AVPLAY_ATTR_ID_VDEC,             /**< 视频属性 , HI_UNF_VCODEC_ATTR_S  */

    HI_UNF_AVPLAY_ATTR_ID_VDEC_ADV,          /**< 高级视频属性 , HI_UNF_VCODEC_ADV_ATTR_S  */

    HI_UNF_AVPLAY_ATTR_ID_AUD_PID,          /**< 音频PID , HI_U32*/
    HI_UNF_AVPLAY_ATTR_ID_VID_PID,          /**< 视频PID , HI_U32*/
    HI_UNF_AVPLAY_ATTR_ID_PCR_PID,          /**<PCR PID , HI_U32*/

    HI_UNF_AVPLAY_ATTR_ID_SYNC,             /**< 同步属性 , HI_UNF_SYNC_ATTR_S */
    HI_UNF_AVPLAY_ATTR_ID_AFD,              /**< AFD 是否开启， HI_BOOL * */
    HI_UNF_AVPLAY_ATTR_ID_OVERFLOW,         /**< 溢出处理类型 , HI_UNF_AVPLAY_OVERFLOW_E * */

    HI_UNF_AVPLAY_ATTR_ID_FRMRATE,          /**< FrameRate HI_UNF_VCODEC_FRMRATE_S * */

    HI_UNF_AVPLAY_ATTR_ID_BUTT
} HI_UNF_AVPLAY_ATTR_ID_E;

/*******************************************************************************/
typedef struct hiUNF_SYNC_REGION_S
{
    HI_S32                s32VidPlusTime;        /**< 视频同步超前的时间范围 */
    HI_S32                s32VidNegativeTime;    /**< 视频同步落后的时间范围 */
    HI_BOOL               bSmoothPlay;           /**< 慢放使能 */
} HI_UNF_SYNC_REGION_S;

/**定义音视频同步属性 */
typedef struct hiUNF_SYNC_ATTR_S
{
    HI_UNF_SYNC_REF_E     enSyncRef;             /**< 音频为准，PCR为准，自由播放等 */
    HI_UNF_SYNC_REGION_S  stSyncStartRegion;     /**< 同步起调区间 */
    HI_UNF_SYNC_REGION_S  stSyncNovelRegion;     /**< 同步异常区间 */
    HI_S32                s32VidPtsAdjust;       /**< 视频PTS调整*/
    HI_S32                s32AudPtsAdjust;       /**< 音频PTS调整*/

    HI_U32                u32PreSyncTimeoutMs;   /**< 预同步的超时时间，单位为毫秒 */
    HI_BOOL               bQuickOutput;          /**< 快速输出使能 */
} HI_UNF_SYNC_ATTR_S;


/**定义AV播放属性 */
typedef struct hiUNF_AVPLAY_ATTR_S
{
    HI_U32                       u32DemuxId;   /**<AVPLAY所使用的DEMUX ID 仅当码流类型为TS时有效*/
    HI_UNF_AVPLAY_STREAM_ATTR_S  stStreamAttr; /**< 码流属性 */
} HI_UNF_AVPLAY_ATTR_S;

/********************************************************************************/
/**定义播放器运行状态信息中同步状态信息类型 */
typedef struct hiUNF_SYNC_STATUS_S
{
    HI_U32 u32FirstAudPts;    /**< 第一个音频帧 PTS         */
    HI_U32 u32FirstVidPts;    /**< 第一个视频帧 PTS         */
    HI_U32 u32LastAudPts;     /**<最近播放的一个音频帧 PTS */
    HI_U32 u32LastVidPts;     /**< 最近播放的一个视频帧 PTS */
    HI_S32 s32DiffAvPlayTime; /**< 音视频 播放时差          */
    HI_U32 u32PlayTime;       /**< 当前已播放时间           */
    HI_U32 u32LocalTime;      /**< 本地同步参考时间         */
} HI_UNF_SYNC_STATUS_S;


/**定义媒体缓冲区的状态信息 */
typedef struct hiUNF_AVPLAY_BUF_STATUS_S
{
    HI_U32 u32BufId;         /**< 媒体缓冲 标识      */
    HI_U32 u32BufSize;       /**< 媒体缓冲大小       */
    HI_U32 u32BufRptr;       /*媒体缓冲读指针,Ts播放时有效*/
    HI_U32 u32BufWptr;       /*媒体缓冲写指针,Ts播放时有效*/
    HI_U32 u32UsedSize;      /**<媒体缓冲已使用大小 */
    HI_U32 u32FrameBufTime;  /**<帧缓冲时间 */
} HI_UNF_AVPLAY_BUF_STATUS_S;


/**定义AV的播放状态 */
typedef enum hiUNF_AVPLAY_STATUS_E
{
    HI_UNF_AVPLAY_STATUS_STOP = 0, /**< 停止                 */
    HI_UNF_AVPLAY_STATUS_PLAY,     /**< 播放                 */
    HI_UNF_AVPLAY_STATUS_TPLAY,    /**<Trick Play, 快进快退 */
    HI_UNF_AVPLAY_STATUS_PAUSE,    /**< 暂停                 */
    HI_UNF_AVPLAY_STATUS_EOS,      /**< 码流播放结束         */
    HI_UNF_AVPLAY_STATUS_SEEK ,    /**< 定位播放             */

    HI_UNF_AVPLAY_STATUS_BUTT
}HI_UNF_AVPLAY_STATUS_E;


/**定义AV播放状态查询输出值类型 */
typedef struct hiUNF_AVPLAY_STATUS_INFO_S
{
    HI_UNF_SYNC_STATUS_S       stSyncStatus;      /**< 同步状态 */
    HI_UNF_AVPLAY_STATUS_E     enRunStatus;       /**< 运行状态 */
    HI_U32                     u32VidFrameCount;  /**< 视频已播放帧数 */
    HI_U32                     u32AuddFrameCount; /**< 音频已播放帧数 */
    HI_UNF_AVPLAY_BUF_STATUS_S stBufStatus[HI_UNF_AVPLAY_BUF_ID_BUTT]; /**<媒体缓冲状态 */
    HI_U32                     u32VidErrorFrameCount; /**< 视频解码错误帧数 */    
} HI_UNF_AVPLAY_STATUS_INFO_S;

/********************************************************************************/
/** 定义播放节目流查询信息类型*/
typedef struct hiUNF_AVPLAY_STREAM_INFO_S
{
    HI_UNF_VCODEC_STREAMINFO_S stVidStreamInfo; /**<视频流信息 */
    HI_UNF_ACODEC_STREAMINFO_S stAudStreamInfo; /**<音频流信息 */
} HI_UNF_AVPLAY_STREAM_INFO_S;

/********************************************************************************/
/**定义I帧数据信息类型 */
typedef struct hiUNF_AVPLAY_I_FRAME_S
{
    HI_U8  *             pu8Addr;    /**<帧数据用户态虚拟地址*/
    HI_U32               u32BufSize; /**<帧数据大小，单位字节*/
    HI_UNF_VCODEC_TYPE_E enType;     /**<该片数据的协议类型*/
} HI_UNF_AVPLAY_I_FRAME_S;

/********************************************************************************/
/**定义解码器类型 不同类型的解码器占用内存不同*/
typedef enum hiHI_UNF_VCODEC_DEC_TYPE_E
{
    HI_UNF_VCODEC_DEC_TYPE_NORMAL,            /**<普通类型*/
    HI_UNF_VCODEC_DEC_TYPE_ISINGLE,           /**<I帧解码类型 如果avplay仅用于I帧解码(HI_UNF_AVPLAY_DecodeIFrame) 设置为此类型可以节省内存*/
    HI_UNF_VCODEC_DEC_TYPE_BUTT				
}HI_UNF_VCODEC_DEC_TYPE_E;

/**定义解码器支持的协议级别 影响NORMAL类型解码器分配的帧存个数 值越大需要的帧存数目越多*/
typedef enum hiHI_UNF_VCODEC_PRTCL_LEVEL_E
{
	HI_UNF_VCODEC_PRTCL_LEVEL_MPEG = 0,	 /**<除h264外的其他协议 */
	HI_UNF_VCODEC_PRTCL_LEVEL_H264 = 1,  /**<h264协议和其他协议 */    
	HI_UNF_VCODEC_PRTCL_LEVEL_BUTT
}HI_UNF_VCODEC_PRTCL_LEVEL_E;

/**定义AV播放器打开视频解码器时属性设置结构体 影响视频解码器占用内存大小及解码能力*/
typedef struct hiHI_UNF_AVPLAY_OPEN_OPT_S
{
    HI_UNF_VCODEC_DEC_TYPE_E    enDecType;       /**<解码器类型*/   
    HI_UNF_VCODEC_CAP_LEVEL_E   enCapLevel;      /**<解码器支持的最大分辨率 影响每个帧存的大小*/
    HI_UNF_VCODEC_PRTCL_LEVEL_E enProtocolLevel; /**<支持的协议级别 影响帧存数目*/
}HI_UNF_AVPLAY_OPEN_OPT_S;


/**定义AV播放器停止时视频显示模式 */
typedef enum hiUNF_AVPLAY_STOP_MODE_E
{
    HI_UNF_AVPLAY_STOP_MODE_STILL = 0,  /**<stop后保留最后一帧*/
    HI_UNF_AVPLAY_STOP_MODE_BLACK = 1,  /**<stop后黑屏*/
    HI_UNF_AVPLAY_STOP_MODE_BUTT
} HI_UNF_AVPLAY_STOP_MODE_E;

/**定义AV播放器启动时属性设置结构体*/
typedef struct hiAVPLAY_START_OPT_S
{
    HI_U32       u32Reserved;
} HI_UNF_AVPLAY_START_OPT_S;


/**定义AV播放器停止时属性设置结构体*/
typedef struct hiAVPLAY_STOP_OPT_S
{
    /*
      s32Timeout: end of stream timeout
         s32Timeout = 0   非阻塞等待码流播放结束，立即返回
         s32Timeout > 0   阻塞超时时间，单位为毫秒
         s32Timeout = -1  无限等待
     */
    HI_U32                    u32TimeoutMs;    /**<超时值*/
    HI_UNF_AVPLAY_STOP_MODE_E enMode;          /**<视频显示模式*/
} HI_UNF_AVPLAY_STOP_OPT_S;

/* 定义AV播放器暂停时属性设置结构体*/
typedef struct hiAVPLAY_PAUSE_OPT_S
{
    HI_U32       u32Reserved;
} HI_UNF_AVPLAY_PAUSE_OPT_S;

/**定义AV播放器快进快退时属性设置结构体*/
typedef struct hiAVPLAY_TPLAY_OPT_S
{
    HI_U32       u32TplaySpeed;
} HI_UNF_AVPLAY_TPLAY_OPT_S;

/**定义AV播放器恢复时属性设置结构体*/
typedef struct hiAVPLAY_RESUME_OPT_S
{
    HI_U32       u32Reserved;
} HI_UNF_AVPLAY_RESUME_OPT_S;

/**定义AV播放器复位时属性设置结构体*/
typedef struct hiAVPLAY_RESET_OPT_S
{
    HI_U32       u32Reserved;
} HI_UNF_AVPLAY_RESET_OPT_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_3 */
/** @{ */  /** <!-- 【AVPLAY】 */

/**
\brief 初始化AVPLAY模块
\attention \n
在调用::HI_UNF_AVPLAY_Create接口创建播放器之前，调用本接口
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NOT_EXIST AVPLAY设备不存在
\retval ::HI_ERR_AVPLAY_NOT_DEV_FILE  AVPLAY非设备
\retval ::HI_ERR_AVPLAY_DEV_OPEN_ERR  AVPLAY打开失败
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Init(HI_VOID);

/**
\brief 去初始化AVPLAY模块
\attention \n
在调用::HI_UNF_AVPLAY_Destroy接口销毁所有的播放器后，调用本接口
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_INVALID_OPT    操作非法
\retval ::HI_ERR_AVPLAY_DEV_CLOSE_ERR  AVPLAY关闭失败
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_DeInit(HI_VOID);

/**
\brief 获取缺省的AV播放配置
\attention \n
调用本接口输入enCfg参数时，请正确输入想要创建播放器模式\n
创建AV播放器前建议调用本接口，获取到AV播放器默认属性，避免创建AV播放器时由于参数不全或参数错误导致播放器创建不成功现象
\param[out] pstAvAttr  指针类型，AV播放属性，请参见::HI_UNF_AVPLAY_ATTR_S
\param[in] enCfg       AV播放的类型，请参见::HI_UNF_AVPLAY_STREAM_TYPE_E
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_GetDefaultConfig(HI_UNF_AVPLAY_ATTR_S *pstAvAttr, HI_UNF_AVPLAY_STREAM_TYPE_E enCfg);

/**
\brief 注册音频动态解码库
\attention \n
\param[in] pFileName 音频解码库文件名
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 失败
\retval ::HI_ERR_AVPLAY_NULL_PTR  输入指针为空

\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_RegisterAcodecLib(const HI_CHAR *pFileName);

/**
\brief 查找注册音频动态解码库
\attention \n
\param[in] enDstCodecID 音频解码库CodecID
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 失败
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_FoundRegisterDeoder(const HI_U32 enDstCodecID);

/**
\brief 根据音频格式, 查找注册音频动态解码库
\attention \n
\param[in] enFormat 音频格式
\param[out] penDstCodecID 成功则返回音频解码库CodecID
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 失败
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_FoundSupportDeoder(const HA_FORMAT_E enFormat,HI_U32 * penDstCodecID);


/**
\brief 设置私有命令给音频动态解码库, 调用ha_codec 方法 
HI_HA_ERRORTYPE_E (*DecSetConfig)(HI_VOID * hDecoder, HI_VOID * pstConfigStructure);
\attention \n
\param[in] hAvplay         AV播放句柄
\param[in] HI_VOID *pPara  属性结构
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 失败
\retval ::HI_ERR_AVPLAY_NULL_PTR  输入指针为空

\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_ControlAcodec( HI_HANDLE hAvplay, HI_VOID *pPara);

/**
\brief 创建AV播放器
\attention \n
输入属性参数pstAttr中有几点需要注意：码流源支持HI_UNF_AVPLAY_STREAM_TYPE_ES（内存输入ES流）、HI_UNF_AVPLAY_STREAM_TYPE_TS（内存输入TS流或TUNER输入TS 流）
\param[in]  pstAvAttr  指针类型，AV播放属性，请参见::HI_UNF_AVPLAY_ATTR_S
\param[out] phAvplay   指针类型，创建的AV播放句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_CREATE_ERR       AVPLAY创建失败
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Create(const HI_UNF_AVPLAY_ATTR_S *pstAvAttr, HI_HANDLE *phAvplay);

/**
\brief 销毁AV播放器
\attention \n
无
\param[in] hAvplay  AV播放句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Destroy(HI_HANDLE hAvplay);

/**
\brief 设置AV播放属性
\attention \n
调用本接口可实现设置音视频PID、设置音视频解码类型、设置同步方式等功能\n
不同的属性ID对应的结构体请参见结构体HI_UNF_AVPLAY_ATTR_ID_E的"【注意】"。pPara参数要与enAttrID对应的属性结构体类型保持一致\n
当需要设置HI_UNF_AVPLAY_ATTR_ID_ADEC（音频解码属性）、HI_UNF_AVPLAY_ATTR_ID_VDEC（视频解码属性）时\n
需要先关闭音频或视频通道，再设置新属性，然后再重新打开音频或视频通道新属性才可以生效。
\param[in] hAvplay         AV播放句柄
\param[in] enAttrID        属性ID
\param[in] HI_VOID *pPara  属性ID对应结构
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_SetAttr(HI_HANDLE hAvplay, HI_UNF_AVPLAY_ATTR_ID_E enAttrID, HI_VOID *pPara);

/**
\brief 获取AV播放属性
\attention \n
无
\param[in] hAvplay          AV播放句柄
\param[in] enAttrID         属性ID
\param[in] HI_VOID *pPara   属性ID对应结构
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_GetAttr(HI_HANDLE hAvplay, HI_UNF_AVPLAY_ATTR_ID_E enAttrID, HI_VOID *pPara);

/**
\brief 解码I帧码流
\attention \n
当pstCapPicture为空指针时，解完的I帧将在window上显示，如果非空，则不会显示而是将I帧信息上报。
调用该接口前，需停止视频解码器；I帧处理没有完成时，也不能启动视频解码器
\param[in] hAvplay         AV播放句柄
\param[in] pstFrame        指针类型，帧数据属性
\param[in] pstCapPicture   指针类型，帧信息
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_DecodeIFrame(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_I_FRAME_S *pstFrame, HI_UNF_CAPTURE_PICTURE_S *pstCapPicture);

/**
\brief 设置视频解码器的模式
\attention \n
本接口主要应用在倍速播放的场景，当切换到倍速播放前，先调用本接口将解码器设置为只解I帧，\n
当切换回正常播放前，先调用本接口将解码器设置为NORMAL。
\param[in] hAvplay            AV播放句柄
\param[in] enDecodeMode       解码模式
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_SetDecodeMode(HI_HANDLE hAvplay, HI_UNF_VCODEC_MODE_E enDecodeMode);

/**
\brief 注册事件
\attention \n
无
\param[in] hAvplay     AV播放句柄
\param[in] enEvent     枚举类型，表示事件类型
\param[in] pfnEventCB  回调函数指针，指向与注册事件对应的回调函数
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_RegisterEvent(HI_HANDLE      hAvplay,
                                   HI_UNF_AVPLAY_EVENT_E     enEvent,
                                   HI_UNF_AVPLAY_EVENT_CB_FN pfnEventCB);


/**
\brief 取消注册事件
\attention \n
无
\param[in] hAvplay   AV播放句柄
\param[in] enEvent   枚举类型，表示事件类型
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_UnRegisterEvent(HI_HANDLE hAvplay, HI_UNF_AVPLAY_EVENT_E enEvent);

/**
\brief 打开AV播放器通道
\attention \n
每个AV播放器仅支持打开音视频通道各1个。如果只播放音频或视频，只需要打开相应通道，以节省资源。
\param[in] hAvplay  AV播放句柄
\param[in] enChn    单独的音视频通道，请参见::HI_UNF_AVPLAY_MEDIA_CHAN_E
\param[in] pPara    指针类型，请参见::HI_UNF_AVPLAY_OPEN_OPT_S
    enChn为HI_UNF_AVPLAY_MEDIA_CHAN_VID时用来指定视频解码器的最大解码能力。
    如果设为NULL，将默认为最大能力: H264+HI_UNF_VCODEC_CAP_LEVEL_FULLHD。
    配置支持的能力越大，需要的MMZ物理内存也就越大，建议按需配置即可。
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_ChnOpen(HI_HANDLE hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_E enChn, const HI_VOID *pPara);

/**
\brief 关闭AV播放器通道
\attention \n
无
\param[in] hAvplay   AV播放句柄
\param[in] enChn     单独的音视频通道，请参见::HI_UNF_AVPLAY_MEDIA_CHAN_E
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_ChnClose(HI_HANDLE hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_E enChn);

/**
\brief 启动播放器，进入PLAY状态
\attention \n
当完成通道打开和属性设置后，调用本接口启动播放，进入PLAY状态。支持分别和同时启动音视频播放。
\param[in] hAvplay        AV播放句柄
\param[in] enChn          单独的音视频通道，请参见::HI_UNF_AVPLAY_MEDIA_CHAN_E
\param[in] pstStartOpt    指针类型，待扩展使用，设为NULL即可
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Start(HI_HANDLE hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_E enChn, const HI_UNF_AVPLAY_START_OPT_S *pstStartOpt);

/**
\brief 停止AV播放，进入STOP状态
\attention \n
调用本接口将停止所选通道的播放，支持分别和同时停止音视频播放。\n
当所选通道中包含视频通道时，参数pstStopOpt->enMode才有意义。\n
当pstStopOpt->enMode为空或者为HI_UNF_AVPLAY_STOP_MODE_STILL时，保留最后一帧视频图像。\n
当pstStopOpt->enMode为HI_UNF_AVPLAY_STOP_MODE_BLACK时，清除视频最后一帧，视频输出为黑屏。\n
当pstStopOpt->u32TimeoutMs为0时将离开停止播放并返回。\n
当pstStopOpt->u32TimeoutMs>0时将阻塞相应时间，直到缓冲中的数据播完。\n
当pstStopOpt->u32TimeoutMs=-1时将一直阻塞到缓冲中的数据播完。\n
当音视频都处于开启状态时,要单独停止音频和视频，必须设置pstStopOpt->u32TimeoutMs为0
\param[in] hAvplay      AV播放句柄
\param[in] enChn        单独的音视频通道，请参见::HI_UNF_AVPLAY_MEDIA_CHAN_E
\param[in] pstStopOpt   指针类型，清屏模式，请参见::HI_UNF_AVPLAY_STOP_OPT_S
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Stop(HI_HANDLE hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_E enChn, const HI_UNF_AVPLAY_STOP_OPT_S *pstStopOpt);

/**
\brief 暂停AV播放，进入PAUSE状态
\attention \n
无
\param[in] hAvplay      AV播放句柄
\param[in] pstPauseOpt  指针类型，待扩展使用，设为为NULL即可
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Pause(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_PAUSE_OPT_S *pstPauseOpt);

/**
\brief 倍速播放，进入TPLAY状态
\attention \n
无
\param[in] hAvplay       AV播放句柄
\param[in] pstTplayOpt   指针类型，待扩展使用，设为为NULL即可
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Tplay(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_TPLAY_OPT_S *pstTplayOpt);

/**
\brief 恢复AV播放，进入PLAY状态
\attention \n
本接口用来将倍速或暂停状态恢复为播放状态，但无法将停止状态恢复为播放状态。
\param[in] hAvplay  AV播放句柄
\param[in] pOption  指针类型，待扩展使用，暂置为空即可
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Resume(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_RESUME_OPT_S *pstResumeOpt);

/**
\brief 复位AV播放，不改变状态
\attention \n
无
\param[in] hAvplay       AV播放句柄
\param[in] pstResetOpt   指针类型，待扩展使用，设为为NULL即可
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_Reset(HI_HANDLE hAvplay, const HI_UNF_AVPLAY_RESET_OPT_S *pstResetOpt);

/**
\brief 申请AV播放的码流缓冲
\attention \n
当播放网络或本地ES流时才需要使用本接口。\n
参数pstData用来返回成功申请到的Buffer的首地址以及大小。\n
u32TimeOutMs设置为0表示不等待，设置为0xffffffff表示一直等待，设置为其他值表示等待u32TimeOutMs毫秒。\n
若超过阻塞时间，还无法申请到Buffer，则返回buffer满错误码\n
u32TimeOutMs配置为0时，如果申请不到Buffer，说明此时音视频的Buffer已满，需要通过usleep(N*1000)释放cpu
以使其它线程能够得到调度。
\param[in] hAvplay     AV播放句柄
\param[in] enBufId     缓冲队列ID
\param[in] u32ReqLen   申请缓存的大小
\param[out] pstData    返回缓存指针
\param[in] u32TimeOutMs      等待超时时间，单位ms
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
无
*/
HI_S32 HI_UNF_AVPLAY_GetBuf(HI_HANDLE  hAvplay,
                            HI_UNF_AVPLAY_BUFID_E enBufId,
                            HI_U32                u32ReqLen,
                            HI_UNF_STREAM_BUF_S  *pstData,
                            HI_U32                u32TimeOutMs);

/**
\brief 拷贝数据成功后，更新写指针
\attention \n
在向申请到的缓冲区内送码流完毕后，调用本接口更新音视频缓冲区的写指针。\n
如果本次送入的码流没有对应的PTS，u32ptsMs必须为-1。
\param[in] hAvplay             AV播放句柄
\param[in] enBufId             缓冲队列ID
\param[in] u32ValidDataLen     实际写入缓冲区的字节数
\param[in] u32ptsMs            时间戳,以毫秒为单位
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_PutBuf(HI_HANDLE hAvplay, HI_UNF_AVPLAY_BUFID_E enBufId,
                         HI_U32 u32ValidDataLen, HI_U32 u32PtsMs);


/**
\brief 设置慢放的速度
\attention \n
设置慢放的速度。1代表正常，2代表2分之1速度。如果要从慢放恢复到正常播放,仍调用该接口，u32Repeat设置为1
\param[in] hAvplay             AV播放句柄
\param[in] u32Repeat           慢放速度
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_SetWindowRepeat(HI_HANDLE hAvplay, HI_U32 u32Repeat);


/**
\brief TS模式时获取AV播放器使用的DMX音频通道的Handle
\attention \n
无
\param[in] hAvplay        AV播放句柄
\param[in] phDmxAudChn    DMX音频通道Handle指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_GetDmxAudChnHandle(HI_HANDLE hAvplay, HI_HANDLE *phDmxAudChn);

/**
\brief TS模式时获取AV播放器使用的DMX视频通道的Handle
\attention \n
无
\param[in] hAvplay        AV播放句柄
\param[in] phDmxAudChn    DMX视频通道Handle指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_GetDmxVidChnHandle(HI_HANDLE hAvplay, HI_HANDLE *phDmxVidChn);


/**
\brief 获取AV播放状态信息
\attention \n
结构体pstStatusInfo中参数stSyncStatus表示获取的当前同步状态，可以用来支持外挂字幕等的同步。\n
enRunStatus表示获取的AV播放器整体状态。\n
u32VidFrameCount和u32AuddFrameCount用来表示当前音视频已播放的帧数。\n
如果是ES模式，可以通过stBufStatus查询音视频Buffer的状态。
\param[in] hAvplay         AV播放句柄
\param[out] pstStatusInfo  指针类型，AV播放状态信息，请参见HI_UNF_AVPLAY_STATUS_INFO_S
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_GetStatusInfo(HI_HANDLE          hAvplay,
                                 HI_UNF_AVPLAY_STATUS_INFO_S *pstStatusInfo);


/**
\brief 获取音视频码流信息
\attention \n
无
\param[in] hAvplay           AV播放句柄
\param[in] pstStreamInfo     指针类型，音视频码流信息，请参见HI_UNF_AVPLAY_STREAM_INFO_S
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_GetStreamInfo(HI_HANDLE          hAvplay,
                                   HI_UNF_AVPLAY_STREAM_INFO_S *pstStreamInfo);

/**
\brief 获取音频能量信息
\attention \n
无
\param[in] hAvplay        AV播放句柄
\param[in] pSpectrum      指针类型，音频能量信息数组指针
\param[in] u32BandNum     音频能量信息数组长度
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\retval ::HI_ERR_AVPLAY_INVALID_OPT      操作非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_GetAudioSpectrum(HI_HANDLE hAvplay, HI_U16 *pSpectrum, HI_U32 u32BandNum);

/**
\brief 查询AVPLAY buffer是否已经为空
\attention \n
无
\param[in] hAvplay        AV播放句柄
\param[out] pbIsEmpty      指针类型，指示buffer是否已经为空(播放完成)
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_AVPLAY_DEV_NO_INIT      AVPLAY未初始化
\retval ::HI_ERR_AVPLAY_NULL_PTR         输入指针为空
\retval ::HI_ERR_AVPLAY_INVALID_PARA     输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_AVPLAY_IsBuffEmpty(HI_HANDLE hAvplay, HI_BOOL * pbIsEmpty);



/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
