/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_pvr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/04/09
  Description   : hi_pvr_api.h header file
  History       :
  1.Date        : 2008/04/09
    Author      : q46153
    Modification: Created file

******************************************************************************/
/**
 * \file
 * \brief 提供PVR的相关信息
 */
#ifndef __HI_UNF_PVR_H__
#define __HI_UNF_PVR_H__


#include "hi_type.h"
#include "hi_debug.h"
#include "hi_unf_ecs.h"
#include "hi_unf_common.h"
#include "hi_unf_avplay.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* End of #ifdef __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_3 */
/** @{ */  /** <!-- 【PVR】 */

/** 录制属性中u32ScdBufSize的推荐值 */
#define PVR_STUB_SC_BUF_SZIE (7*4*2048)

/** 录制属性中u32DavBufSize的推荐值 */
#define PVR_STUB_TSDATA_SIZE (188*12*2048)

/*****************Macro Definition*******************************/
/** 文件名最大长度，单位:字节*/
#define PVR_MAX_FILENAME_LEN            128
/** 加密密钥最大长度，单位:字节。注意: 密钥的有效长度不一定是最大长度，而是由加密的算法决定 */
#define PVR_MAX_CIPHER_KEY_LEN          128
/** 用户数据最大长度， 单位:字节 */
#define PVR_MAX_USERDATA_LEN            (1024*1024)


/***********************************************************
                Data Structure Definition
 ***********************************************************/

/***** data structure for common *****/

/** PVR index文件中循环控制结构信息 */
typedef struct hiPVR_CYC_HEADER_INFO_S
{
    HI_U32 u32StartFrame;     /**< 码流的起始帧在index文件中的偏移, 起始帧放在u32StartFrame的位置*/
    HI_U32 u32EndFrame;       /**< 码流的结束帧在index文件中的偏移, 结束帧放在u32EndFrame-1的位置*/
    HI_U32 u32LastFrame;      /**< index文件中结尾帧的偏移, 结尾帧放在u32LastFrame-1的位置*/
    HI_U32 u32IsRewind;       /**< 文件是否回绕录制, 0 非回绕, 1 回绕*/
}PVR_CYC_HEADER_INFO_S;

/** PVR index文件中文件头信息结构 */
typedef struct hiPVR_IDX_HEADER_INFO_S
{
    HI_U32 u32StartCode;                          /**<  起始码(0x5A5A5A5A) */
    HI_U32 u32HeaderLen;                          /**< 从u32StartCode开始到UsrData结束的长度 */
    PVR_CYC_HEADER_INFO_S stCycInfo;              /**< index中录制环回控制信息 */
    HI_U64 u64ValidSize;                          /**< 文件中有效内容大小 单位Byte */
    HI_U32 u32Reserved;                           /**< 保留，用作对齐 */
    HI_U32 u32UsrDataInfoLen;                     /**< 用户信息长度 */
}PVR_IDX_HEADER_INFO_S;

/** PVR index文件中保存的索引数据结构 */
typedef struct hiPVR_INDEX_ENTRY_S
{
    HI_U16 u16FrameTypeAndGop;                    /**< 2bit frameType and 14bit GOP */
    HI_U16 u16UpFlowFlag;                         /**< DAV overflow  flag */
    HI_U32 s32CycTimes;                           /**< how many times the file had rewind   */
    HI_U64 u64GlobalOffset;                       /**< Total Global Offset, ignore rewind, byte */
    HI_U32 u32DisplayTimeMs;                      /**< display time, no rewind, unit: ms */
    HI_U32 u32FrameSize;                          /**< frame size */
    HI_U64 u64Offset;                             /**< offset of frame at stream file */
    HI_U32 u32PtsMs;                              /**< pts of ms */
    HI_U16 u16IndexType;                          /**< index type   */
    HI_U16 u161stFrameOfTT;                       /**< useless  */
}PVR_INDEX_ENTRY_S,*PTR_PVR_INDEX_ENTRY;

/** PVR加解密配置 */
typedef struct hiUNF_PVR_CIPHER_S
{
    HI_BOOL             bDoCipher;                             /**< 是否进行加密或者解密，此项配置为HI_FALSE时，其他项没有意义 */
    HI_UNF_CIPHER_ALG_E enType;                                /**< 加密或者解码的算法类型 */
    HI_U8               au8Key[PVR_MAX_CIPHER_KEY_LEN];        /**< 密钥 */
    HI_U32              u32KeyLen;                             /**< 密钥长度 */
}HI_UNF_PVR_CIPHER_S;

/** PVR事件类型 */
typedef enum hiUNF_PVR_EVENT_E
{

    HI_UNF_PVR_EVENT_PLAY_EOF        = 0x001,          /**< 播放到文件尾 */
    HI_UNF_PVR_EVENT_PLAY_SOF        = 0x002,          /**< 回退到文件头 */
    HI_UNF_PVR_EVENT_PLAY_ERROR      = 0x003,          /**< 播放内部错误 */
    HI_UNF_PVR_EVENT_PLAY_REACH_REC  = 0x004,          /**< 时移的时候播放追上录制 */
    HI_UNF_PVR_EVENT_PLAY_RESV       = 0x00f,          /**< 保留 */
    HI_UNF_PVR_EVENT_REC_DISKFULL    = 0x010,          /**< 磁盘满 */
    HI_UNF_PVR_EVENT_REC_ERROR       = 0x011,          /**< 录制内部错误 */
    HI_UNF_PVR_EVENT_REC_OVER_FIX    = 0x012,          /**< 录制长度达到指定的长度,只有非回绕录制才有这个事件 */
    HI_UNF_PVR_EVENT_REC_REACH_PLAY  = 0x013,          /**< 时移的时候录制追上播放 */
    HI_UNF_PVR_EVENT_REC_DISK_SLOW   = 0x014,          /**< 磁盘存储速度慢于录制速度 */
    HI_UNF_PVR_EVENT_REC_RESV        = 0x01f,          /**< 保留 */
    HI_UNF_PVR_EVENT_BUTT            = 0x020           /**< 无效的事件类型 */
} HI_UNF_PVR_EVENT_E;


/** PVR事件回调函数 */
typedef void (*eventCallBack)(HI_U32 u32ChnID, HI_UNF_PVR_EVENT_E EventType, HI_S32 s32EventValue, HI_VOID *args);


/** PVR录制、播放的码流类型 */
typedef enum hiUNF_PVR_STREAM_TYPE_E
{
    HI_UNF_PVR_STREAM_TYPE_TS,        /**< TS流 */
    HI_UNF_PVR_STREAM_TYPE_PES,       /**< PES流 */
    HI_UNF_PVR_STREAM_TYPE_ALL_TS,    /**< 全码流录制，录制整个频点的所有码流 */
    HI_UNF_PVR_STREAM_TYPE_OTHER,     /**< 无效的类型 */
    HI_UNF_PVR_STREAM_TYPE_BUTT
} HI_UNF_PVR_STREAM_TYPE_E;

/**索引类型 */
typedef enum hiUNF_PVR_REC_INDEX_TYPE_E
{
    HI_UNF_PVR_REC_INDEX_TYPE_NONE,      /**<不建索引。全码流录制的时候请使用此类型  */
    HI_UNF_PVR_REC_INDEX_TYPE_VIDEO,     /**<针对视频建立索引。 */
    HI_UNF_PVR_REC_INDEX_TYPE_AUDIO,     /**<针对音频建立索引。 */
    HI_UNF_PVR_REC_INDEX_TYPE_BUTT       /**<无效的索引类型。   */
} HI_UNF_PVR_REC_INDEX_TYPE_E;

/** PVR录制的码流文件信息 */
typedef struct hiUNF_PVR_FILE_ATTR_S
{
    HI_UNF_PVR_REC_INDEX_TYPE_E enIdxType;          /**< 索引类型 */
    HI_U32                      u32FrameNum;        /**< 对视频文件：文件帧数;对音频文件：文件中的PES数 */
    HI_U32                      u32StartTimeInMs;   /**< 文件内容的起始时间，起始帧PTS，单位ms */
    HI_U32                      u32EndTimeInMs;     /**< 文件内容的结束时间，结束帧PTS，单位ms  */
    HI_U64                      u64ValidSizeInByte; /**< 文件的有效数据长度，单位byte */
} HI_UNF_PVR_FILE_ATTR_S;

/***** data structs for rec *****/
/* record states*/
/**INVALID -> INIT -> RUNNING -> STOPPING ->    STOP ->    INVALID  (saveIndex)  (saveStream)*/

/**录制通道的状态 */
typedef enum hiUNF_PVR_REC_STATE_E
{
  HI_UNF_PVR_REC_STATE_INVALID,        /**< 未初始化。    */
  HI_UNF_PVR_REC_STATE_INIT,           /**< 初始化。      */
  HI_UNF_PVR_REC_STATE_RUNNING,        /**< 录制中。      */
  HI_UNF_PVR_REC_STATE_PAUSE,          /**< 暂停中        */
  HI_UNF_PVR_REC_STATE_STOPPING,       /**< 正在停止。    */
  HI_UNF_PVR_REC_STATE_STOP,           /**< 已经停止。    */
  HI_UNF_PVR_REC_STATE_BUTT            /**< 无效的状态值。*/
} HI_UNF_PVR_REC_STATE_E;

/** 录制通道属性数据结构 */
typedef struct hiUNF_PVR_REC_ATTR_S
{
    HI_UNF_PVR_REC_INDEX_TYPE_E enIndexType;                           /**< 索引类型，静态属性。 */
    HI_UNF_VCODEC_TYPE_E        enIndexVidType;                        /**< 待建立索引的码流的视频编码协议, 索引类型是HI_UNF_PVR_REC_INDEX_TYPE_VIDEO时才需要配置,静态属性  */
    HI_U32                      u32IndexPid;                           /**< 索引PID，静态属性*/
    HI_U32                      u32DemuxID;                            /**< 录制DEMUX号，静态属性。*/
    HI_U32                      u32DavBufSize;                         /**< 数据流缓冲区大小，单位为Byte，静态属性。  */
    HI_U32                      u32ScdBufSize;                         /**< 索引数据缓存区大小，单位为Byte，静态属性。*/
    HI_U32                      u32UsrDataInfoSize;                    /**< 用户私有数据大小，单位为Byte，静态属性。  */
    HI_BOOL                     bIsClearStream;                        /**< 是否把码流录制成清流，静态属性。此项的意思是存下来的码流是清流还是加扰流。如果待录制的节目是加扰流，需要在录制DEMUX上启动一路CA才能录制清流,PVR录制模块并不负责对加扰流的解扰操作。*/
    HI_UNF_PVR_STREAM_TYPE_E    enStreamType;                          /**< 待录制的数据类型，静态属性。*/
    HI_UNF_PVR_CIPHER_S         stEncryptCfg;                          /**< 码流加密配置信息，静态属性。*/
    HI_U64                      u64MaxFileSize;                        /**< 待录制的文件大小，为0时表示无限制，静态属性。最小值为50M,如果磁盘空间足够的话，推荐配置为512M以上。配置为回绕时不允许配置为0。 */
    HI_BOOL                     bRewind;                               /**< 是否回绕，静态属性。如配置为HI_TRUE，录制文件大小到达u64MaxFileSize后，会回绕到文件头继续进行录制；如配置为HI_FALSE，则录制文件大小到达u64MaxFileSize后，会停止录制。*/
    HI_CHAR                     szFileName[PVR_MAX_FILENAME_LEN];      /**< 码流文件名，静态属性。*/
    HI_U32                      u32FileNameLen;                        /**< 码流文件名长度，静态属性。取值为strlen（szFileName）即可 */
    HI_U32                      u32Reserved;
}HI_UNF_PVR_REC_ATTR_S;


/**定义PVR缓冲区的状态信息 */
typedef struct hiUNF_PVR_BUF_STATUS_S
{
    HI_U32 u32BufSize;       /**< 缓冲区大小       */
    HI_U32 u32UsedSize;      /**< 缓冲区已使用大小 */
} HI_UNF_PVR_BUF_STATUS_S;

/** 录制通道状态数据结构.
对u32CurTimeInMs、u32StartTimeInMs、u32EndTimeInMs三者的关系举例说明如下：
1·假设从开始录制后一共录制了10000毫秒，如果没有发生回绕，那么u32StartTimeInMs 为0，u32EndTimeInMs 为10000， u32CurTimeInMs为10000。
2·假设从开始录制后一共录制了10000毫秒，并且在第8000毫秒的时候发生了回绕，那么u32StartTimeInMs 为2000，u32EndTimeInMs 为10000， u32CurTimeInMs为8000。
*/
typedef struct hiUNF_PVR_REC_STATUS_S
{
    HI_UNF_PVR_REC_STATE_E      enState;                 /**< 通道所处的状态。    */
    HI_U32                      u32Reserved;             /**< 保留，用作对齐。    */
    HI_U64                      u64CurWritePos;          /**< 当前录制文件的大小（单位：byte）。 */
    HI_U32                      u32CurWriteFrame;        /**< 当前录制的帧数。                  */
    HI_U32                      u32CurTimeInMs;          /**< 当前录制的毫秒数。其值为录制文件的实际有效时长。*/
    HI_U32                      u32StartTimeInMs;        /**< 录制文件的实际起始点。录制回绕前，为第一帧时间；录制回绕后，为回绕点的时间。 */
    HI_U32                      u32EndTimeInMs;          /**< 录制文件中结束帧的时间，没有环回前即最后一帧的时间。    */
    HI_UNF_PVR_BUF_STATUS_S     stRecBufStatus;          /**< 录制通道缓冲区状态。    */
}HI_UNF_PVR_REC_STATUS_S;


/** data structs for play */

/** PVR播放方向:往前播放 */
#define HI_UNF_PVR_PLAY_DIRECTION_FORWARD             (1)
/** PVR播放方向:往后播放 */
#define HI_UNF_PVR_PLAY_DIRECTION_BACK                (-1)

/** 播放位置类型 */
typedef enum hiUNF_PVR_PLAY_POS_TYPE_E
{
  HI_UNF_PVR_PLAY_POS_TYPE_SIZE,              /**< 用大小（单位：byte）表示位置（暂不支持） */
  HI_UNF_PVR_PLAY_POS_TYPE_TIME,              /**< 用时间（单位：ms）数表示位置 */
  HI_UNF_PVR_PLAY_POS_TYPE_FRAME,             /**< 用帧数（或者PES数）表示位置  */
  HI_UNF_PVR_PLAY_POS_TYPE_BUTT               /**< 无效的位置类型*/
} HI_UNF_PVR_PLAY_POS_TYPE_E;


/** 播放通道的状态  */
typedef enum hiUNF_PVR_PALY_STATE_E
{
    HI_UNF_PVR_PLAY_STATE_INVALID,       /**< 未初始化            */
    HI_UNF_PVR_PLAY_STATE_INIT,          /**< 初始化              */
    HI_UNF_PVR_PLAY_STATE_PLAY,          /**< 正常播放中          */
    HI_UNF_PVR_PLAY_STATE_PAUSE,         /**< 暂停                */
    HI_UNF_PVR_PLAY_STATE_FF,            /**< 快进                */
    HI_UNF_PVR_PLAY_STATE_FB,            /**< 快退                */
    HI_UNF_PVR_PLAY_STATE_SF,            /**< 慢放                */
    HI_UNF_PVR_PLAY_STATE_STEPF,         /**< 逐帧播放            */
    HI_UNF_PVR_PLAY_STATE_STEPB,         /**< 逐帧倒放            */
    HI_UNF_PVR_PLAY_STATE_STOP,          /**< 停止                */
    HI_UNF_PVR_PLAY_STATE_BUTT           /**< 无效的状态值        */
} HI_UNF_PVR_PLAY_STATE_E;

/** 播放速度标识 */
typedef enum hiUNF_PVR_PLAY_SPEED_E
{
    HI_UNF_PVR_PLAY_SPEED_NORMAL            = 1024,                                     /**<    正常速度播放。    */
    HI_UNF_PVR_PLAY_SPEED_2X_FAST_FORWARD   = 2 * HI_UNF_PVR_PLAY_SPEED_NORMAL,         /**<2倍速快放。            */
    HI_UNF_PVR_PLAY_SPEED_4X_FAST_FORWARD   = 4 * HI_UNF_PVR_PLAY_SPEED_NORMAL,         /**<4倍速快放。            */
    HI_UNF_PVR_PLAY_SPEED_8X_FAST_FORWARD   = 8 * HI_UNF_PVR_PLAY_SPEED_NORMAL,         /**<8倍速快放。            */
    HI_UNF_PVR_PLAY_SPEED_16X_FAST_FORWARD  = 16 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<16倍速快放。           */
    HI_UNF_PVR_PLAY_SPEED_32X_FAST_FORWARD  = 32 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<32倍速快放。           */
    HI_UNF_PVR_PLAY_SPEED_2X_FAST_BACKWARD  = -2 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<2倍速快退。            */
    HI_UNF_PVR_PLAY_SPEED_4X_FAST_BACKWARD  = -4 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<4倍速快退。            */
    HI_UNF_PVR_PLAY_SPEED_8X_FAST_BACKWARD  = -8 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<8倍速快退。            */
    HI_UNF_PVR_PLAY_SPEED_16X_FAST_BACKWARD = -16 * HI_UNF_PVR_PLAY_SPEED_NORMAL,       /**<16倍速快退。           */
    HI_UNF_PVR_PLAY_SPEED_32X_FAST_BACKWARD = -32 * HI_UNF_PVR_PLAY_SPEED_NORMAL,       /**<32倍速快退。           */
    HI_UNF_PVR_PLAY_SPEED_2X_SLOW_FORWARD   = HI_UNF_PVR_PLAY_SPEED_NORMAL / 2,         /**<1/2倍速慢放。          */
    HI_UNF_PVR_PLAY_SPEED_4X_SLOW_FORWARD   = HI_UNF_PVR_PLAY_SPEED_NORMAL / 4,         /**<1/4倍速慢放。          */
    HI_UNF_PVR_PLAY_SPEED_8X_SLOW_FORWARD   = HI_UNF_PVR_PLAY_SPEED_NORMAL / 8,         /**<1/8倍速慢放。          */
    HI_UNF_PVR_PLAY_SPEED_16X_SLOW_FORWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / 16,        /**<1/16倍速慢放。         */
    HI_UNF_PVR_PLAY_SPEED_32X_SLOW_FORWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / 32,        /**<1/32倍速慢放。         */
    HI_UNF_PVR_PLAY_SPEED_2X_SLOW_BACKWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-2),      /**<2倍速慢退，暂不支持。  */
    HI_UNF_PVR_PLAY_SPEED_4X_SLOW_BACKWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-4),      /**<4倍速慢退，暂不支持。  */
    HI_UNF_PVR_PLAY_SPEED_8X_SLOW_BACKWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-8),      /**<8倍速慢退，暂不支持。  */
    HI_UNF_PVR_PLAY_SPEED_16X_SLOW_BACKWARD = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-16),     /**<16倍速慢退，暂不支持。 */
    HI_UNF_PVR_PLAY_SPEED_32X_SLOW_BACKWARD = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-32),     /**<32倍速慢退，暂不支持。 */
    HI_UNF_PVR_PLAY_SPEED_BUTT                                                          /**<无效的速度值。         */
} HI_UNF_PVR_PLAY_SPEED_E;

/** 特技播放的模式  */
typedef struct hiUNF_PVR_PLAY_MODE_S
{
    HI_UNF_PVR_PLAY_SPEED_E               enSpeed;    /**< 速度，见HI_UNF_PVR_PLAY_SPEED_E的定义 */
}HI_UNF_PVR_PLAY_MODE_S;

/** 播放通道属性 */
typedef struct hiUNF_PVR_PLAY_ATTR_S
{

    HI_UNF_PVR_STREAM_TYPE_E    enStreamType;                         /**< 播放码流类型，目前只支持TS，静态属性。*/
    HI_BOOL                     bIsClearStream;                       /**< 待播放的码流是否清流，静态属性。加扰流不支持特技播放，只支持正常播放 */
    HI_UNF_PVR_CIPHER_S         stDecryptCfg;                         /**< 解密配置，静态属性。                  */
    HI_CHAR                     szFileName[PVR_MAX_FILENAME_LEN];     /**< 待播放码流的文件名，静态属性。        */
    HI_U32                      u32FileNameLen;                       /**< 文件名长度，静态属性。取值为strlen（szFileName）即可 */
}HI_UNF_PVR_PLAY_ATTR_S;


/** 播放位置描述  */
typedef struct hiUNF_PVR_PLAY_POSITION_S
{
    HI_UNF_PVR_PLAY_POS_TYPE_E  enPositionType;       /**< 位置类型。           */
    HI_S32                      s32Whence;            /**< 偏移类型，取值范围为SEEK_SET/SEEK_CUR/SEEK_END。*/
    HI_S64                      s64Offset;            /**< 偏移。 偏移类型为时间时，单位毫秒；偏移类型为帧时，单位为一帧 */
}HI_UNF_PVR_PLAY_POSITION_S;

/** 创建索引文件需要的信息 */
typedef struct hiUNF_PVR_GEN_IDX_ATTR_S
{
    HI_U32                      u32UsrDataInfoLen;         /**< 用户数据长度 */
    HI_U32                      u32IdxPid;                 /**< 针对哪个Pid建立索引 */
    HI_UNF_PVR_REC_INDEX_TYPE_E enIdxType;                 /**< 索引类型 */
}HI_UNF_PVR_GEN_IDX_ATTR_S;

/** 播放通道的状态 */
typedef struct hiUNF_PVR_PLAY_STATUS_S
{
    HI_UNF_PVR_PLAY_STATE_E     enState;                              /**< 播放通道状态。                                  */
    HI_UNF_PVR_PLAY_SPEED_E     enSpeed;                              /**< 播放通道的播放速度。                            */
    HI_U64                      u64CurPlayPos;                        /**< 当前播放帧的起始在文件中的位置（byte数）。      */
    HI_U32                      u32CurPlayFrame;                      /**< 当前播放帧在文件中的位置（帧数或者PES数）       */
    HI_U32                      u32CurPlayTimeInMs;                   /**< 当前播放帧的PTS, 单位毫秒。                     */
}HI_UNF_PVR_PLAY_STATUS_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_2 */
/** @{ */  /** <!-- 【PVR】 */

/***** APIs for PVR recode *****/

/**
\brief 初始化PVR录制模块
\attention \n
重复初始化返回成功\n
每个进程使用PVR录制模块接口前，必须先调用此接口，否则其他接口均无法使用
\param  无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 出现系统错误，API调用失败
\see \n
::HI_UNF_PVR_RecDeInit
*/
HI_S32 HI_UNF_PVR_RecInit(HI_VOID);

/**
\brief 去初始化PVR录制模块
\attention \n
重复去初始化返回成功\n
去初始化PVR录制模块前务必保证本进程内所有录制通道都已经释放，如果还有录制通道没有释放，此接口将会返回错误码HI_ERR_PVR_BUSY

\param 无
\retval ::HI_SUCCESS  成功
\retval ::HI_FAILURE  出现系统错误，API调用失败
\retval ::HI_ERR_PVR_BUSY  PVR录制模块还在使用中
\retval ::HI_ERR_PVR_NOT_INIT  PVR录制模块未初始化
\see \n
::HI_UNF_PVR_RecInit
*/
HI_S32 HI_UNF_PVR_RecDeInit(HI_VOID);


/**
\brief 创建1路录制通道
\attention \n
PVR录制模块会根据pAttr中指定的文件名自动生成一个后缀名为".idx"索引文件\n
PVR录制模块会对录制的码流文件进行分割，以确保码流文件不超过4G的大小（每个文件的大小约为3.99G），
生成的码流文件依次为szFileName，szFileName.0001，szFileName.0002，szFileName.0003，szFileName.0004···\n
如果pAttr中指定的文件已经存在，那么这个文件会被覆盖\n
如果PVR录制模块将要创建的索引文件已经存在，则索引文件也会被覆盖\n
由于PVR使用到了其他模块的API接口函数（比如音视频API接口和DEMUX API接口），因此返回的错误码有可能是其他模块的错误码，
具体错误码值请参考相应模块错误码值定义。后面的其他API函数均会有此种情况

\param[in] pu32ChnID   获取到的录制通道ID
\param[in] pstRecAttr  指针类型，指向通道属性配置
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT  PVR录制模块未初始化
\retval ::HI_ERR_PVR_NUL_PTR  指针参数为空
\retval ::HI_ERR_DMX_INVALID_PARA  参数非法
\retval ::HI_ERR_PVR_FILE_INVALID_FNAME  文件名参数非法
\retval ::HI_ERR_PVR_FILE_EXIST  文件已经存在
\retval ::HI_ERR_PVR_NO_CHN_LEFT  已经没有空闲的通道供分配
\retval ::HI_ERR_PVR_FILE_CANT_OPEN  无法打开文件
\retval ::HI_ERR_PVR_INDEX_CANT_MKIDX  无法打开索引文件
\retval ::HI_ERR_PVR_REC_INVALID_DMXID  录制时传入了错误的DEMUX ID
\see \n
无
*/
HI_S32 HI_UNF_PVR_RecCreateChn(HI_U32 *pu32ChnID, const HI_UNF_PVR_REC_ATTR_S *pstRecAttr);
/**
\brief 释放指定的录制通道
\attention \n
如果待释放的通道没有停止，将返回错误码::HI_ERR_PVR_BUSY
\param[in] u32ChnID   需要释放的通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT  PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID  通道号非法
\retval ::HI_ERR_PVR_BUSY  通道忙，不允许进行当前操作
\see \n
无
*/
HI_S32 HI_UNF_PVR_RecDestroyChn(HI_U32 u32ChnID);


/**
\brief 设置录制通道属性
\attention \n
只有动态属性才能用此接口改变设置
\param[in] u32ChnID    通道号
\param[in] pstRecAttr  待设置的属性
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT  PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID  通道号非法
\see \n
无
*/
HI_S32 HI_UNF_PVR_RecSetChn(HI_U32 u32ChnID, const HI_UNF_PVR_REC_ATTR_S *pstRecAttr);


/**
\brief 获取录制通道属性
\attention \n
无
\param[in] u32ChnID   通道号
\param[in] pstRecAttr   指针类型，指向获取到的通道属性配置
\retval ::HI_SUCCESS  成功
\retval ::HI_ERR_PVR_NOT_INIT   PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID    通道号非法
\retval ::HI_ERR_PVR_NUL_PTR        指针参数为空
\retval ::HI_ERR_PVR_CHN_NOT_INIT   指定的通道未初始化
\see \n
无
*/
HI_S32 HI_UNF_PVR_RecGetChn(HI_U32 u32ChnID, HI_UNF_PVR_REC_ATTR_S *pstRecAttr);


/**
\brief 启动录制通道
\attention \n
无
\param[in] u32ChnID 通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT   PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID    通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT   指定的通道未初始化
\retval ::HI_ERR_PVR_ALREADY        指定的通道已经启动
\retval ::HI_FAILURE                出现系统错误，API调用失败
\see \n
::HI_UNF_PVR_RecStopChn
*/
HI_S32 HI_UNF_PVR_RecStartChn(HI_U32 u32ChnID);


/**
\brief 停止录制通道
\attention \n
如果1个录制通道正在进行时移播放操作，则在停止时移播放之前，不允许停止该录制通道 \n
如果该通道正在进行时移播放操作，将返回错误码HI_ERR_PVR_BUSY
\param[in] u32ChnID   通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT     PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID      通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT     指定的通道未初始化
\retval ::HI_ERR_PVR_ALREADY          指定的通道已经停止
\retval ::HI_ERR_PVR_BUSY             通道忙，不允许进行当前操作
\see \n
::HI_UNF_PVR_RecStartChn
*/
HI_S32 HI_UNF_PVR_RecStopChn(HI_U32 u32ChnID);


/**
\brief 获取录制通道状态
\attention \n
无
\param[in] u32ChnID  通道号
\param[in] pstRecStatus   录制状态信息指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT    PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID     通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT    指定的通道未初始化
\retval ::HI_ERR_PVR_NUL_PTR        指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_PVR_RecGetStatus(HI_U32 u32ChnID, HI_UNF_PVR_REC_STATUS_S *pstRecStatus);


/***** APIs for PVR play *****/
/**
\brief 初始化PVR播放模块
\attention \n
重复初始化返回成功 \n
每个进程使用PVR播放模块接口前，必须先调用此接口，否则其他接口均无法使用
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE           出现系统错误，API调用失败
\see \n
::HI_UNF_PVR_PlayDeInit
*/
HI_S32 HI_UNF_PVR_PlayInit(HI_VOID);


/**
\brief 去初始化PVR播放模块
\attention \n
重复去初始化返回成功 \n
去初始化PVR播放模块前务必保证本进程内所有播放通道都已经释放，如果还有播放通道没有释放，此接口将会返回错误码::HI_ERR_PVR_BUSY
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE         出现系统错误，API调用失败
\retval ::HI_ERR_PVR_BUSY    PVR播放模块还在使用中
\retval ::HI_ERR_PVR_NOT_INIT    PVR录制模块未初始化

\see \n
::HI_UNF_PVR_PlayInit
*/
HI_S32 HI_UNF_PVR_PlayDeInit(HI_VOID);


/**
\brief 创建1路播放通道
\attention \n
PVR播放模块会根据pAttr中指定的文件名自动寻找后缀名为".idx"的索引文件 \n
如果索引文件不存在，PVR播放模块也会尝试播放这个文件，但是可能无法支持某些特性，
比如快进快退或者SEEK操作（根据版本的不同而有所差别，当前版本只支持播放）\n
播放的文件可以是正在录制的文件（即进行时移播放）
hAVPlay所代表的avplay必须处于stop状态。
\param[out] pu32ChnID    获取到的播放通道ID
\param[in] pstPlayAttr   通道属性配置指针
\param[in] hAVPlay       avplay句柄，标识用哪个avplay来播放
\param[in] hTsBuffer     ts buffer句柄，标识用哪个ts buffer来回放，一般来说，此ts buffer对应的ts端口应该是绑定在hAVPlay对应的demux上的
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT         PVR录制模块未初始化
\retval ::HI_ERR_PVR_NUL_PTR              指针参数为空
\retval ::HI_ERR_DMX_INVALID_PARA          参数非法
\retval ::HI_ERR_PVR_FILE_INVALID_FNAME     文件名参数非法
\retval ::HI_ERR_PVR_FILE_EXIST           文件已经存在
\retval ::HI_ERR_PVR_NO_CHN_LEFT          已经没有空闲的通道供分配
\retval ::HI_ERR_PVR_FILE_CANT_OPEN       无法打开文件
\retval ::HI_ERR_PVR_FILE_NOT_EXIST       文件不存在，无法播放
\retval ::HI_ERR_PVR_NO_MEM               内存不足，无法分配播放需要的Buffer
\retval ::HI_ERR_PVR_FILE_CANT_READ       文件读取出错
\see \n
无
*/
HI_S32 HI_UNF_PVR_PlayCreateChn(HI_U32 *pu32ChnID, const HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr, HI_HANDLE hAvplay, HI_HANDLE hTsBuffer);


/**
\brief 释放指定的播放通道
\attention \n
如果待释放的通道没有停止，将返回错误码::HI_ERR_PVR_BUSY
\param[in] u32ChnID  需要释放的通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT        PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID         通道号非法
\retval ::HI_ERR_PVR_BUSY    通道忙，不允许进行当前操作
\see \n
无
*/
HI_S32 HI_UNF_PVR_PlayDestroyChn(HI_U32 u32ChnID);


/**
\brief 启动时移播放通道。调用此接口可以根据输入的录制通道号，启动1路时移播放。此接口将根据对应录制通道的参数自动初始化1个播放通道，并开始播放
\attention \n
不推荐使用此接口，保留此接口只是为了保持与老接口的兼容，推荐使用HI_UNF_PVR_PlayCreateChn后再调用HI_UNF_PVR_PlayStartChn启动播放，如果要进行时移，
只需要设置播放的文件名与录制的文件名一样即可，PVR会自动识别相同的文件名并进入时移状态。
调用此接口可以直接启动1路时移播放，接口内部会自动调用HI_UNF_PVR_PlayCreateChn分配播放通道，用户不需要再先调用HI_UNF_PVR_PlayCreateChn创建播放通道 \n
调用此接口前请确保对应的录制通道已经启动，否则将会返回错误码HI_ERR_PVR_REC_INVAL_STATE \n
调用此接口启动1路时移后，对应的录制通道将不能被停止或者销毁直到时移播放停止

\param[out] pu32PlayChnID   播放通道号
\param[in] u32RecChnID     需要时移的录制通道号
\param[in] hAVPlay       avplay句柄，标识用哪个avplay来播放
\param[in] hTsBuffer     ts buffer句柄，标识用哪个ts buffer来回放，一般来说，此ts buffer对应的ts端口应该是绑定在hAVPlay对应的demux上的
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NUL_PTR  指针参数为空
\retval ::HI_ERR_PVR_PLAY_INVALID_DMXID 播放时传入了错误的DEMUX ID
\retval ::HI_ERR_PVR_INVALID_CHNID  通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT  指定的通道未初始化
\retval ::HI_ERR_PVR_ALREADY 指定的通道已经启动
\retval ::HI_ERR_PVR_NO_CHN_LEFT  已经没有空闲的播放通道供分配
\retval ::HI_ERR_PVR_REC_INVALID_STATE 录制通道没有启动
\retval ::HI_ERR_PVR_NO_MEM  内存不足，无法分配播放需要的Buffer
\retval ::HI_FAILURE  出现系统错误，API调用失败

\see \n
::HI_UNF_PVR_PlayStopTimeShift
*/
HI_S32 HI_UNF_PVR_PlayStartTimeShift(HI_U32 *pu32PlayChnID, HI_U32 u32RecChnID, HI_HANDLE hAvplay, HI_HANDLE hTsBuffer);



/**
\brief 停止播放通道
\attention \n
此接口与::HI_UNF_PVR_PlayStartTimeShift接口必须配对使用，此接口只能停止使用::HI_UNF_PVR_PlayStartTimeShift启动的播放通道 \n
通过::HI_UNF_PVR_PlayStartTimeShift接口启动的播放通道必须使用此接口来停止，而不允许用::HI_UNF_PVR_PlayStopChn接口来停止
\param[in] u32PlayChnID  通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT         PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID          通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT         指定的通道未初始化
\retval ::HI_ERR_PVR_ALREADY              指定的通道已经启动
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE     通道状态错误。例如：对用::HI_UNF_PVR_PlayStartChn启动的播放通道调用此接口
\see \n
::HI_UNF_PVR_PlayStartTimeShift
*/
HI_S32 HI_UNF_PVR_PlayStopTimeShift(HI_U32 u32PlayChnID, const HI_UNF_AVPLAY_STOP_OPT_S *pstStopOpt);


/**
\brief 设置播放通道属性
\attention \n
只有动态属性才能通过此接口进行设置
\param[in] u32ChnID     通道号
\param[in] pstPlayAttr  指针类型，指向要设置的通道属性配置
\retval ::HI_SUCCESS  成功
\retval ::HI_ERR_PVR_NOT_INIT  PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID  通道号非法
\see \n
::HI_UNF_PVR_PlayGetChn
*/
HI_S32 HI_UNF_PVR_PlaySetChn(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr);


/**
\brief 获取播放通道属性
\attention \n
无
\param[in] u32ChnID  通道号
\param[out] pstPlayAttr   指针类型，指向获取到的通道属性配置
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT    PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID     通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT    指定的通道未初始化
\retval ::HI_ERR_PVR_NUL_PTR         指针参数为空
\see \n
::HI_UNF_PVR_PlaySetChn
*/
HI_S32 HI_UNF_PVR_PlayGetChn(HI_U32 u32ChnID, HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr);



/**
\brief 启动播放通道
\attention \n
调用::HI_UNF_PVR_PlayCreateChn申请的通道只能通过此接口启动一次，如果想要暂停/恢复播放，
需使用::HI_UNF_PVR_PlayPauseChn和::HI_UNF_PVR_PlayResumeChn接口

\param[in] u32ChnID  通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT      PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID       通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT      指定的通道未初始化
\retval ::HI_ERR_PVR_ALREADY           指定的通道已经启动
\retval ::HI_FAILURE                   出现系统错误，API调用失败

\see \n
::HI_UNF_PVR_PlayStopChn
*/
HI_S32 HI_UNF_PVR_PlayStartChn(HI_U32 u32ChnID);
/**
\brief 停止播放通道
\attention \n
此接口与::HI_UNF_PVR_PlayStartChn接口必须配对使用，此接口只能停止使用::HI_UNF_PVR_PlayStartChn启动的播放通道 \n
通过::HI_UNF_PVR_PlayStartChn接口启动的播放通道必须使用此接口来停止，而不允许用::HI_UNF_PVR_PlayStopTimeShift接口来停止

\param[in] u32ChnID  通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT      PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID       通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT      指定的通道未初始化
\retval ::HI_ERR_PVR_ALREADY           指定的通道已经启动
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE  通道状态错误。例如：对用::HI_UNF_PVR_PlayStartTimeShift启动的播放通道调用此接口
\see \n
::HI_UNF_PVR_PlayStartChn
*/
HI_S32 HI_UNF_PVR_PlayStopChn(HI_U32 u32ChnID, const HI_UNF_AVPLAY_STOP_OPT_S *pstStopOpt);


/**
\brief 暂停播放通道
\attention \n
在通道已经暂停的情况下再次调用::HI_UNF_PVR_PlayPauseChn暂停通道将返回成功 \n
在通道已经被停止的情况下调用此接口暂停通道将返回错误码::HI_ERR_PVR_PLAY_INVALID_STATE
\param[in] u32ChnID   通道号
\retval ::HI_SUCCESS  成功
\retval ::HI_ERR_PVR_NOT_INIT        PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID         通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT        指定的通道未初始化
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE    通道状态错误：通道已经停止运行
\see \n
::HI_UNF_PVR_PlayResumeChn
*/
HI_S32 HI_UNF_PVR_PlayPauseChn(HI_U32 u32ChnID);


/**
\brief 恢复播放通道。调用此接口可以恢复播放通道，解除播放通道的暂停状态
\attention \n
此接口与::HI_UNF_PVR_PlayPauseChn接口必须配对使用，只有在通道已经暂停的情况下才允许恢复通道
\param[in] u32ChnID 通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT       PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID        通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT       指定的通道未初始化
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE   指定的通道不在暂停状态
\see \n
::HI_UNF_PVR_PlayPauseChn
*/
HI_S32 HI_UNF_PVR_PlayResumeChn(HI_U32 u32ChnID);


/**
\brief 进行特技播放。调用此接口可以进行特技播放，即进行快进、快退、慢放、正常播放等操作
\attention \n
进入特技播放模式后，如果想退回正常播放模式，只需要设置特技播放模式的速度为PVR_PLAY_SPEED_NORMAL
\param[in] u32ChnID       通道号
\param[in] pstTrickMode   特技播放模式信息指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT         PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID          通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT         指定的通道未初始化
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE     通道状态错误：通道已经停止运行
\retval ::HI_ERR_DMX_INVALID_PARA          参数非法
\retval ::HI_ERR_PVR_NOT_SUPPORT     不支持的特技播放模式
\see \n
无
*/
HI_S32 HI_UNF_PVR_PlayTPlay(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_MODE_S *pstTrickMode);

/**
\brief 定位到指定位置进行播放
\attention \n
在通道已经停止的情况下调用本接口将返回错误码::HI_ERR_PVR_PLAY_INVALID_STATE\n
seek时如果超过边界，自动调整到边界\n
向后seek和从开始seek，则seek到对应位置的下一个I帧，不成功则找前一个I帧\n
向前seek和从结尾seek，则seek到对应位置的前一个I帧，不成功则找下一个I帧\n
找不到I帧会返回错误

\param[in] u32ChnID   通道号
\param[in] pstPosition  播放位置信息指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT         PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID          通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT         指定的通道未初始化
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE     通道状态错误：通道已经停止运行
\retval ::HI_ERR_DMX_INVALID_PARA          参数非法
\retval ::HI_ERR_PVR_NOT_SUPPORT     不支持的Seek模式
\retval ::HI_ERR_PVR_FILE_TILL_END        Seek到文件尾没有找到相应的帧
\retval ::HI_ERR_PVR_FILE_TILL_START      Seek到文件头没有找到相应的帧
\retval ::HI_ERR_PVR_FILE_CANT_READ       读取文件失败
\see \n
无
*/
HI_S32 HI_UNF_PVR_PlaySeek(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_POSITION_S *pstPosition);

/**
\brief 逐帧播放。调用此接口可以进行逐帧倒退或者逐帧前进播放
\attention \n
目前不支持逐帧播放
\param[in] u32ChnID    通道号
\param[in] s32Direction   播放方向。大于等于0表示前进；小于0表示后退
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT         PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID          通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT         指定的通道未初始化
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE     通道状态错误：通道已经停止运行
\retval ::HI_ERR_PVR_NOT_SUPPORT     不支持的功能

\see \n
NULL
*/
HI_S32 HI_UNF_PVR_PlayStep(HI_U32 u32ChnID, HI_S32 s32Direction);


/**
\brief 获取PVR回放的状态
\attention \n
获取播放的状态，注意在播放器创建之后调用
\param[in] u32ChnID
\param[in] pstStatus
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT  PVR录制模块未初始化
\retval ::HI_ERR_PVR_INVALID_CHNID  通道号非法
\retval ::HI_ERR_PVR_BUSY 系统忙，遇到这种情况，请重试。
\see \n
无
*/
HI_S32 HI_UNF_PVR_PlayGetStatus(HI_U32 u32ChnID, HI_UNF_PVR_PLAY_STATUS_S *pstStatus);



/**
\brief 通过播放通道ID，获取PVR录制的码流文件信息
\attention \n
调用此接口用来获取播放文件的固定信息，但是对于时移场景这些信息是不断变化的
在播放过程中可以通过::HI_UNF_PVR_PlayGetStatus接口获取当前的播放位置 \n
在时移过程中可以通过::HI_UNF_PVR_RecGetStatus接口获取当前的录制位置
此外，如果既没有启动录制也没有启动播放，可以通过::HI_UNF_PVR_GetFileAttrByFileName接口获取文件属性
\param[in] u32ChnID  通道号
\param[in] pAttr   播放状态信息指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NOT_INIT             PVR播放模块未初始化
\retval ::HI_ERR_PVR_NUL_PTR              空指针错误
\retval ::HI_ERR_PVR_INVALID_CHNID        通道号非法
\retval ::HI_ERR_PVR_CHN_NOT_INIT         指定的通道未初始化
\retval ::HI_ERR_PVR_FILE_CANT_OPEN       无法打开文件
\retval ::HI_ERR_PVR_FILE_CANT_READ       无法读文件
\see \n
无
*/
HI_S32 HI_UNF_PVR_PlayGetFileAttr(HI_U32 u32ChnID, HI_UNF_PVR_FILE_ATTR_S *pAttr);


/**
\brief 获取码流文件信息。调用此接口可以在不申请播放通道的情况下获取指定码流文件的信息
\attention \n
pFileName指向码流文件名而不是索引文件名 \n
任何时候都可以调用此接口获取码流文件的属性
\param[in] pFileName  码流文件名
\param[in] pAttr     播放状态信息指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NUL_PTR          空指针错误
\retval ::HI_ERR_PVR_FILE_CANT_OPEN   无法打开文件
\retval ::HI_ERR_PVR_FILE_CANT_READ   无法读文件
\see \n
无
*/
HI_S32 HI_UNF_PVR_GetFileAttrByFileName(const HI_CHAR *pFileName, HI_UNF_PVR_FILE_ATTR_S *pAttr);


/**
\brief 写入用户数据
\attention \n
pFileName指向码流文件名而不是索引文件名 \n
u32UsrDataLen的取值不能大于录制此文件时在录制通道属性里面指定的u32UsrDataInfoSize的取值 \n
用户数据被保存在索引文件中 \n
请在启动录制通道后再写入用户数据信息
\param[in] pFileName  码流文件名
\param[in] pInfo     用户数据指针，空间由用户分配
\param[in] u32UsrDataLen    用户数据长度
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NUL_PTR          空指针错误
\retval ::HI_ERR_PVR_FILE_CANT_OPEN   无法打开文件
\retval ::HI_ERR_PVR_FILE_CANT_READ   无法读文件
\retval ::HI_ERR_DMX_INVALID_PARA      参数非法
\see \n
无
*/
HI_S32 HI_UNF_PVR_SetUsrDataInfoByFileName(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32UsrDataLen);


/**
\brief 读取用户数据
\attention \n
pFileName指向码流文件名而不是索引文件名 \n
pUsrDataLen返回读取到的用户数据的长度，其取值为u32BufLen和"实际用户数据长度"二者中的较小值。
"实际用户数据长度"将不小于HI_UNF_PVR_RecNewChn时配置的最大用户数据长度，以保证能够把全部用户数据读出 \n
PVR模块不保存HI_UNF_PVR_SetUsrDataInfoByFileName时传入的用户数据长度，只保存HI_UNF_PVR_RecNewChn时配置的最大用户数据长度

\param[in] pFileName   码流文件名
\param[in] pInfo       用户数据缓冲区，空间由用户分配
\param[in] u32BufLen   缓冲区长度
\param[in] pUsrDataLen  实际读取到的用户数据长度

\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_NUL_PTR           空指针错误
\retval ::HI_ERR_PVR_FILE_CANT_OPEN    无法打开文件
\retval ::HI_ERR_PVR_FILE_CANT_READ    无法读文件
\retval ::HI_ERR_DMX_INVALID_PARA       参数非法
\see \n
无
*/
HI_S32 HI_UNF_PVR_GetUsrDataInfoByFileName(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32BufLen, HI_U32* pUsrDataLen);


/**
\brief 注册事件回调函数。调用此接口可以注册PVR事件的回调函数，从而对PVR录制、播放过程中产生的事件进行处理
\attention \n
可以使用::HI_UNF_PVR_UnRegisterEvent来反注册1个事件，否则已经注册的事件将一直保持有效
对于PVR_EVENT_PLAY_REACH_REC消息，建议用户在注册的回调函数中停止PVR播放，并切换到直播模式用AVPLAY进行播放。
当录制属性配置为不回绕的时候，PVR_EVENT_REC_OVER_FIX消息在录制长度到达指定长度，即将停止录制的时候上报；
当录制属性配置为回绕的时候，PVR_EVENT_REC_OVER_FIX消息在每次回绕的时候都会上报，此时，消息处理回调函数的s32EventValue参数值为回绕的次数(从1开始计数)。
PVR_EVENT_REC_REACH_PLAY消息在录制即将追上播放的时候上报，此时，消息处理回调函数的s32EventValue参数值为录制位置距离播放位置的字节数。

\param[in] enEventType 想要注册的事件类型
\param[in] callBack    事件处理函数
\param[in] args        用户自定义回调函数的参数
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_INTF_EVENT_INVAL    非法的事件
\retval ::HI_ERR_PVR_ALREADY             尝试对已经注册的事件再次注册
\retval ::HI_ERR_PVR_INTF_EVENT_NOREG    回调函数指针出错，无法注册成功
\see \n
无
*/
HI_S32 HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_E enEventType, eventCallBack callBack, HI_VOID *args);


/**
\brief 去注册PVR事件的回调函数
\attention \n
可以使用此接口来去注册1个事件，否则已经注册的事件将一直保持有效
\param[in] enEventType          想要去注册的事件类型
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_PVR_INTF_EVENT_INVAL  非法的事件
\retval ::HI_ERR_PVR_INTF_EVENT_NOREG  对没有注册的事件进行去注册
\see \n
无
*/
HI_S32 HI_UNF_PVR_UnRegisterEvent(HI_UNF_PVR_EVENT_E enEventType);


/**
\brief
\attention \n
暂时不支持此功能
\param[in] pstTsFileName
\param[in] pstIdxFileName
\param[in] pAttr
\retval ::HI_SUCCESS  成功
\retval ::HI_ERR_PVR_NOT_SUPPORT 不支持此功能
\see \n
无
*/
HI_S32 HI_UNF_PVR_CreateIdxFile(HI_U8* pstTsFileName, HI_U8* pstIdxFileName, HI_UNF_PVR_GEN_IDX_ATTR_S* pAttr);



/**
\brief 配置是否输出调试信息
\attention \n
默认输出error以上级别的调试信息
\param[in] enDebugLevel  调试信息输出级别
\retval none
\see \n
无
*/
HI_VOID HI_UNF_PVR_ConfigDebugInfo(HI_LOG_LEVEL_E enDebugLevel);



/**
\brief 删除录制时生成的码流文件和索引文件
\attention \n
pFileName指向码流文件名而不是索引文件名\n
调用此接口后，录制此码流时生成的码流文件和索引文件都将被删除\n
如果码流文件大于4G将会生成data.ts, data.ts.0001, data.ts.0002, data.ts.0003 ...\n
等多个文件，但是删除时只需要传入文件名"data.ts"就可以了。
\param[in] pFileName   码流文件名
\retval none
\see \n
无
*/
HI_VOID HI_UNF_PVR_RemoveFile(const HI_CHAR *pFileName);


/**
\brief
\attention \n
\param[in] u64Size
\retval none
\see \n
无
*/
//HI_S32 HI_UNF_PVR_SetFileNodeMaxSize(HI_U64 u64Size);


/**
\brief
\attention \n
\param 无
\retval none
\see \n
无
*/
//HI_U64 HI_UNF_PVR_GetFileNodeMaxSize();
/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __HI_UNF_PVR_H__ */
