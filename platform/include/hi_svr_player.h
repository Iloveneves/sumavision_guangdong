/**
 \file
 \brief svr player模块
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author 
 \date 2010-02-10
 */

#ifndef __HI_SVR_PLAYER_H__
#define __HI_SVR_PLAYER_H__

#include "hi_type.h"
#include "hi_svr_format.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2 */
/** @{ */  /** <!-- 【Hiplayer数据结构】 */

/** 非法句柄 */
#define HI_SVR_PLAYER_INVALID_HDL        (0)   
/** 正常速度播放 */  
#define HI_SVR_PLAYER_PLAY_SPEED_NORMAL  (1024)  

/** 设置的文件类型 */
typedef enum hiSVR_PLAYER_MEDIA_PARAM_E
{
    HI_SVR_PLAYER_MEDIA_STREAMFILE = (1 << 0),    /**< 音视频媒体文件 */
    HI_SVR_PLAYER_MEDIA_SUBTITLE   = (1 << 1),    /**< 字幕文件 */
    HI_SVR_PLAYER_MEDIA_BUTT       = (1 << 2)
} HI_SVR_PLAYER_MEDIA_PARAM_E;

/** 播放器属性ID */
typedef enum hiSVR_PLAYER_ATTR_E
{
    HI_SVR_PLAYER_ATTR_STREAMID = 0x0,         /**< 设置/获取流编号，该属性针对多音频、多视频流的情况，参数为::HI_SVR_PLAYER_STREAMID_S */
    HI_SVR_PLAYER_ATTR_WINDOW_HDL,             /**< 获取window id，参数为HI_U32变量 */
    HI_SVR_PLAYER_ATTR_AVPLAYER_HDL,           /**< 获取AVPlayer句柄，参数为HI_HANDLE变量 */
    HI_SVR_PLAYER_ATTR_SO_HDL,                 /**< 获取so句柄，参数为HI_HANDLE变量 */
    HI_SVR_PLAYER_ATTR_BUTT
} HI_SVR_PLAYER_ATTR_E;

/** PLAYER状态 */
typedef enum hiSVR_PLAYER_STATE_E
{
    HI_SVR_PLAYER_STATE_INI = 0,    /**< 播放器当前处于初始状态，create后播放器处于ini状态 */
    HI_SVR_PLAYER_STATE_DEINI,      /**< 播放器已经去初始状态 */
    HI_SVR_PLAYER_STATE_PLAY,       /**< 播放器当前处于播放状态 */
    HI_SVR_PLAYER_STATE_FORWARD,    /**< 播放器当前处于快进状态 */
    HI_SVR_PLAYER_STATE_BACKWARD,   /**< 播放器当前处于快退状态 */
    HI_SVR_PLAYER_STATE_PAUSE,      /**< 播放器当前处于暂停状态 */
    HI_SVR_PLAYER_STATE_STOP,       /**< 播放器当前处于停止状态 */
    HI_SVR_PLAYER_STATE_BUTT
} HI_SVR_PLAYER_STATE_E;

/** 事件类型 */
typedef enum hiSVR_PLAYER_EVENT_E
{
    HI_SVR_PLAYER_EVENT_STATE = 0x0,   /**< 播放器状态转换事件，参数值为::HI_SVR_PLAYER_STATE_E */
    HI_SVR_PLAYER_EVENT_SOF,           /**< 文件开始播放或快退到文件头事件，参数类型为HI_U32，
                                            值为::HI_SVR_PLAYER_STATE_PLAY表示开始播放，参数值为::HI_SVR_PLAYER_STATE_BACKWARD表示快退到文件头 */
    HI_SVR_PLAYER_EVENT_EOF,           /**< 文件播放到尾事件，无参数 */
    HI_SVR_PLAYER_EVENT_PROGRESS,      /**< 播放器当前播放进度事件，每隔500ms上报一次该事件，参数值为HI_U32类型变量，值0-100 */
    HI_SVR_PLAYER_EVENT_STREAMID_CHG,  /**< stream id 发生变化事件，参数为::HI_SVR_PLAYER_STREAMID_S */
    HI_SVR_PLAYER_EVENT_BUTT
} HI_SVR_PLAYER_EVENT_E;

/** 注册的动态库类型 */
typedef enum hiSVR_PLAYER_DLLTYPE_E
{
    HI_SVR_PLAYER_DLL_PARSER = 0x0,    /**< 音视频媒体文件解析、字幕解析动态库 */
    HI_SVR_PLAYER_DLL_BUTT
} HI_SVR_PLAYER_DLLTYPE_E;

/** 播放速度标识 */
typedef enum hiSVR_PLAYER_PLAY_SPEED_E
{
    HI_SVR_PLAYER_PLAY_SPEED_2X_FAST_FORWARD   = 2 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,      /**< 2倍速快放 */
    HI_SVR_PLAYER_PLAY_SPEED_4X_FAST_FORWARD   = 4 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,      /**< 4倍速快放 */
    HI_SVR_PLAYER_PLAY_SPEED_8X_FAST_FORWARD   = 8 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,      /**< 8倍速快放 */
    HI_SVR_PLAYER_PLAY_SPEED_16X_FAST_FORWARD  = 16 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 16倍速快放 */
    HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_FORWARD  = 32 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 32倍速快放 */
    HI_SVR_PLAYER_PLAY_SPEED_2X_FAST_BACKWARD  = -2 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 2倍速快退 */
    HI_SVR_PLAYER_PLAY_SPEED_4X_FAST_BACKWARD  = -4 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 4倍速快退 */
    HI_SVR_PLAYER_PLAY_SPEED_8X_FAST_BACKWARD  = -8 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,     /**< 8倍速快退 */
    HI_SVR_PLAYER_PLAY_SPEED_16X_FAST_BACKWARD = -16 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,    /**< 16倍速快退 */
    HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_BACKWARD = -32 * HI_SVR_PLAYER_PLAY_SPEED_NORMAL,    /**< 32倍速快退 */
    HI_SVR_PLAYER_PLAY_SPEED_BUTT                                                          /**< 无效的速度值 */
} HI_SVR_PLAYER_PLAY_SPEED_E;

/** 播放器打开参数 */
typedef struct hiSVR_PLAYER_PARAM_S
{
    HI_U32  u32DmxId;                 /**< dmx id，播放ts流时需设置该参数 */
    HI_U32  u32PortId;                /**< port id，播放ts流时需设置该参数 */
    HI_U32  x, y, w, h;               /**< 视频输出窗口坐标及宽高，hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL，该参数无效 */
    HI_U32  u32MixHeight;             /**< 音频输出混音权重0-100，hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL，该参数无效 */
    HI_HANDLE hAVPlayer;              /**< 外部已经创建了avplay并绑定了window,sound，并设置好window的大小位置，sound的音量，
                                           可以将avplay句柄传给HiPlayer，HiPlayer继续使用该avplay播放。如果该参数设置为
                                           HI_SVR_PLAYER_INVALID_HDL，HiPlayer内部会自动创建avplayer和window */
} HI_SVR_PLAYER_PARAM_S;

/** 输入的媒体文件 */
typedef struct hiSVR_PLAYER_MEDIA_S
{
    HI_CHAR  aszUrl[HI_FORMAT_MAX_URL_LEN];          /**< 文件路径，绝对路径，如/mnt/filename.ts */
    HI_U32   u32SubTitileNum;                        /**< 字幕文件个数 */
    HI_CHAR  aszSubTitle[HI_FORMAT_MAX_LANG_NUM][HI_FORMAT_MAX_URL_LEN];  /**< 字幕文件路径，绝对路径，如/mnt/filename.ts */
} HI_SVR_PLAYER_MEDIA_S;

/** 音视频、字幕ID切换属性 */
typedef struct hiSVR_PLAYER_STREAMID_S
{
    HI_U32 u32ProgramId;   /**< 节目id，值为::HI_FORMAT_FILE_INFO_S结构astProgramInfo数组下标，0-(u32ProgramNum - 1) */
    HI_U32 u32VStreamId;   /**< 视频流id，值与u32ProgramId相等 */
    HI_U32 u32AStreamId;   /**< 音频流id，值为::HI_FORMAT_PROGRAM_INFO_S结构astAudStream数组下标，0-(u32AudStreamNum - 1)*/
    HI_U32 u32SubTitleId;  /**< 字幕id，值为::HI_FORMAT_PROGRAM_INFO_S结构astSubTitle数组下标，0-(u32SubTitleNum - 1) */
} HI_SVR_PLAYER_STREAMID_S;

/** 播放器事件回调参数 */
typedef struct hiSVR_PLAYER_EVENT_S
{
    HI_SVR_PLAYER_EVENT_E  eEvent;    /**< 事件类型 */
    HI_U32  u32Len;                   /**< 事件参数长度，字节为单位 */
    HI_U8   *pu8Data;                 /**< 事件参数数据起始地址 */
} HI_SVR_PLAYER_EVENT_S;

/** 播放器信息 */
typedef struct hiSVR_PLAYER_INFO_S
{
    HI_U32  u32Progress;                 /**< 播放百分比，0-100 */
    HI_U64  u64TimePlayed;               /**< 已播放时间，单位ms */
    HI_S32  s32Speed;                    /**< 播放速率 */
    HI_SVR_PLAYER_STATE_E  eStatus;      /**< 播放状态 */
} HI_SVR_PLAYER_INFO_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_1 */
/** @{ */  /** <!-- 【Hiplayer】 */

/** 
\brief 播放器事件回调函数，调用::HI_SVR_PLAYER_RegCallback接口注册该回调函数
\attention \n
无
\param[out] hPlayer 播放器句柄
\param[out] pstruEvent 事件参数

\retval ::HI_SUCCESS

\see \n
无
*/
typedef HI_S32 (*HI_SVR_PLAYER_EVENT_FN)(HI_HANDLE hPlayer, HI_SVR_PLAYER_EVENT_S *pstruEvent);

/** 
\brief 初始化Player
\attention \n
初始化成功后再调用该接口返回成功，不支持多进程，调用其它接口前必须先调用该接口
\param 无

\retval ::HI_SUCCESS 初始化成功
\retval ::HI_FAILURE 初始化失败

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Init(HI_VOID);

/** 
\brief 去初始化player模块，不再使用player模块，调用该接口去初始化player模块
\attention \n
必须先调用::HI_SVR_PLAYER_Destroy接口释放掉创建的播放器，再调用该接口，否则会返回失败，Deinit不负责释放\n
播放器资源。去初始化成功后再调用该接口返回成功
\param 无

\retval ::HI_SUCCESS 去初始化成功
\retval ::HI_FAILURE 去初始化失败，没有释放掉创建的播放器

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Deinit(HI_VOID);

/** 
\brief 创建一个播放器
\attention \n
该接口必须在初始化后调用，支持最多创建一个播放器\n
\param[in] pstruParam 播放器初始化属性，播放ts流，必须指定可用的dmx id和port id
\param[out] phPlayer 创建的播放器句柄

\retval ::HI_SUCCESS 创建成功，播放器句柄有效
\retval ::HI_FAILURE 创建失败，参数非法或资源不够

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Create(const HI_SVR_PLAYER_PARAM_S *pstruParam, HI_HANDLE *phPlayer); 

/** 
\brief 设置要播放的媒体文件url地址，url格式为:绝对路径+媒体文件名
\attention \n
同步接口，该接口必须在调用::HI_SVR_PLAYER_Create之后调用，或者调用::HI_SVR_PLAYER_Stop接口停止播放器后调用
该接主要执行以下处理:
1、查找解析器解析设置的媒体文件
2、如果没有指定字幕文件，则查找字幕文件
3、如果没有指定avplay则
   创建avplay，根据解析出的文件属性设置音视频属性，如音视频编码类型
   创建window，设置window窗口位置，将window绑定到avplay
   将HI_UNF_SND_0设备绑定到avplay
window显示位置，HI_UNF_SND_0绑定到avplay设置的mixheight(如果avplay是外部指定，则显示位置和mixheight参数无效)，
在调用::HI_SVR_PLAYER_Create接口时指定，如果是播放ts流，播放器会根据指定的dmx id,port id创建ts buffer

\param[in] hPlayer 调用::HI_SVR_PLAYER_Create接口创建的播放器句柄
\param[in] eType 媒体文件。只指定音视频媒体文件，则该参数设置为HI_SVR_PLAYER_MEDIA_STREAMFILE，\n
            如果还指定了字幕文件则设置(HI_SVR_PLAYER_MEDIA_STREAMFILE | HI_SVR_PLAYER_MEDIA_SUBTITLE)
\param[in] pstruMedia 媒体文件信息，只支持绝对路径。如果没有设置字幕文件，播放器会自动在音视频媒\n
            体文件所在目录下查找与音视频媒体文件名相同的字幕文件

\retval ::HI_SUCCESS 媒体文件设置成功，此时调用::HI_SVR_PLAYER_Play接口可以开始播放
\retval ::HI_FAILURE 媒体文件设置失败
\retval ::HI_ERRNO_NOT_SUPPORT_FORMAT 不支持的文件格式
\retval ::HI_ERRNO_NOT_SUPPORT_PROTOCOL 不支持的协议

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_SetMedia(HI_HANDLE hPlayer, HI_U32 eType, HI_SVR_PLAYER_MEDIA_S *pstruMedia);

/** 
\brief 销毁一个播放器实例
\attention \n
调用::HI_SVR_PLAYER_Create创建播放器后，调用该接口销毁播放器资源
\param[in] hPlayer 播放器句柄

\retval ::HI_SUCCESS 播放器释放成功
\retval ::HI_FAILURE 非法操作

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Destroy(HI_HANDLE hPlayer);

/** 
\brief 设置播放器参数
\attention \n
支持的操作如下
::HI_SVR_PLAYER_ATTR_STREAMID : 设置播放的流id，对于单视频、多音频文件，可以通过该操作设置要播放的音频流\n
播放过程中调用该接口为异步操作，播放前，SetMedia后调用该接口为同步操作，异步操作不能通过接口返回值来判断\n
流id是否设置成功，播放器会通过::HI_SVR_PLAYER_EVENT_STREAMID_CHG事件通知app，事件参数为::HI_SVR_PLAYER_STREAMID_S

\param[in] hPlayer 播放器句柄
\param[in] eAttrId 要设置的播放器参数ID
\param[in] pArg 要设置的播放器参数

\retval ::HI_SUCCESS 参数设置成功
\retval ::HI_FAILURE 操作失败

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_SetParam(HI_HANDLE hPlayer, HI_SVR_PLAYER_ATTR_E eAttrId, const HI_VOID *pArg);

/** 
\brief 获取播放器参数
\attention \n
支持的操作如下
::HI_SVR_PLAYER_ATTR_STREAMID : 当前播放的流id
::HI_SVR_PLAYER_ATTR_WINDOW_HDL : 播放器创建的window句柄
::HI_SVR_PLAYER_ATTR_AVPLAYER_HDL : 播放器创建的avplay句柄
::HI_SVR_PLAYER_ATTR_SO_HDL : 播放器创建的字幕输出模块(so)句柄

\param[in] hPlayer 播放器句柄
\param[in] eAttrId 播放器参数ID
\param[out] pArg 获取的播放器参数

\retval ::HI_SUCCESS 获取参数成功
\retval ::HI_FAILURE 操作失败

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_GetParam(HI_HANDLE hPlayer, HI_SVR_PLAYER_ATTR_E eAttrId, HI_VOID *pArg);

/** 
\brief 注册播放器事件回调函数
\attention \n
该函数必须在调用::HI_SVR_PLAYER_Create接口后调用，该接口与播放器状态无关
\param[in] hPlayer 播放器句柄
\param[in] pfnCallback 播放器事件回调函数，回调函数定义::HI_SVR_PLAYER_EVENT_FN

\retval ::HI_SUCCESS 注册成功
\retval ::HI_FAILURE 设置失败

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_RegCallback(HI_HANDLE hPlayer, HI_SVR_PLAYER_EVENT_FN pfnCallback);

/** 
\brief 开始播放
\attention \n
异步接口，该接口必须在调用::HI_SVR_PLAYER_SetMedia接口后调用，播放成功后再调用该接口返回HI_FAILURE，\n
不能通过该接口返回值来判断播放器是否播放成功，播放器会通过::HI_SVR_PLAYER_EVENT_STATE事件通知\n
app播放成功，事件参数值为::HI_SVR_PLAYER_STATE_PLAY。停止播放后，可以调用该接口重新播放

\param[in] hPlayer 播放器句柄

\retval ::HI_SUCCESS 合法操作
\retval ::HI_FAILURE 非法操作

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Play(HI_HANDLE hPlayer);

/** 
\brief 停止播放
\attention \n
异步接口，播放、快进、快退、暂停过程中都可以调用该接口停止播放，不能通过该接口返回值来判断播放器\n
是否停止成功，播放器会通过::HI_SVR_PLAYER_EVENT_STATE事件通知app停止成功，事件参数值为::HI_SVR_PLAYER_STATE_STOP。\n
停止播放后，可以调用::HI_SVR_PLAYER_Play接口重新播放

\param[in] hPlayer 播放器句柄

\retval ::HI_SUCCESS 合法操作
\retval ::HI_FAILURE 非法操作

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Stop(HI_HANDLE hPlayer);

/** 
\brief 暂停播放
\attention \n
异步接口，播放过程中可以调用该接口暂停播放，快进、快退状态下不能调用该接口，不能通过该接口返回值来判断播放器\n
是否暂停成功，播放器会通过::HI_SVR_PLAYER_EVENT_STATE事件通知app停止成功，事件参数值为::HI_SVR_PLAYER_STATE_PAUSE。\n
暂停成功后，可以调用::HI_SVR_PLAYER_Resume继续播放

\param[in] hPlayer 播放器句柄

\retval ::HI_SUCCESS 合法操作
\retval ::HI_FAILURE 非法操作

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Pause(HI_HANDLE hPlayer);

/** 
\brief 恢复播放
\attention \n
异步接口，暂停、快进、快退状态下，调用该接口恢复正常播放，不能通过该接口返回值来判断播放器是否恢复播放\n
播放器会通过::HI_SVR_PLAYER_EVENT_STATE事件通知app恢复成功，事件参数值为::HI_SVR_PLAYER_STATE_PLAY。

\param[in] hPlayer 播放器句柄

\retval ::HI_SUCCESS 合法操作
\retval ::HI_FAILURE 非法操作

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Resume(HI_HANDLE hPlayer);

/** 
\brief 快进、快退
\attention \n
异步接口，该函数必须调用::HI_SVR_PLAYER_Play后调用，s32Speed为负表示快退，为正表示快进，不能通过该接口\n
返回值来判断是否快进或快退成功，播放器会通过::HI_SVR_PLAYER_EVENT_STATE事件通知app，事件参数值为\n
::HI_SVR_PLAYER_STATE_FORWARD或::HI_SVR_PLAYER_STATE_BACKWARD，快进、快退后通过调用::HI_SVR_PLAYER_Resume\n
接口恢复正常播放。

\param[in] hPlayer 播放器句柄
\param[in] s32Speed 播放倍数,值为HI_SVR_PLAYER_PLAY_SPEED_E

\retval ::HI_SUCCESS 合法操作
\retval ::HI_FAILURE 非法操作

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_TPlay(HI_HANDLE hPlayer, HI_S32 s32Speed);

/** 
\brief 跳到指定位置播放
\attention \n
异步接口，该接口必须在调用::HI_SVR_PLAYER_SetMedia接口后调用，播放、停止状态下，调用该接口跳到指定时间点播放

\param[in] hPlayer 播放器句柄
\param[in] s64TimeInMs seek时间，单位ms

\retval ::HI_SUCCESS Seek成功
\retval ::HI_FAILURE 非法操作

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_Seek(HI_HANDLE hPlayer, HI_S64 s64TimeInMs);

/** 
\brief 获取当前打开文件信息，如文件大小、文件播放时长、码率等，视频宽、高，编码格式，帧率、码率，音频编码、码率等
\attention \n
该函数必须在调用::HI_SVR_PLAYER_SetMedia接口后调用

\param[in] hPlayer 播放器句柄
\param[out] pstruInfo 获取的文件信息

\retval ::HI_SUCCESS 获取到文件信息
\retval ::HI_FAILURE 获取文件信息失败

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_GetFileInfo(HI_HANDLE hPlayer, HI_FORMAT_FILE_INFO_S *pstruInfo);

/** 
\brief 获取播放器信息，如当前播放状态、播放进度、已播放时间等
\attention \n
该函数必须在调用::HI_SVR_PLAYER_Create接口后调用，播放进度、已播放时间只有在调用::HI_SVR_PLAYER_Play接口后有效

\param[in] hPlayer 播放器句柄
\param[out] pstruInfo 播放器信息

\retval ::HI_SUCCESS 播放器信息获取成功
\retval ::HI_FAILURE 播放器信息获取失败

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_GetPlayerInfo(HI_HANDLE hPlayer, HI_SVR_PLAYER_INFO_S *pstruInfo);

/** 
\brief 注册文件解析、字幕解析器，解析器必须是动态库，且按hi_svr_format.h头文件规范实现
\attention \n
该接口必须在调用::HI_SVR_PLAYER_Init接口后调用
动态库放在/usr/lib目录下，如libformat.so，则调用该接口方式为:
HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libformat.so")

\param[in] eDllType 动态库类型
\param[in] dllName 动态库名称

\retval ::HI_SUCCESS 动态库注册成功
\retval ::HI_FAILURE 注册失败

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLLTYPE_E eDllType, const HI_CHAR *dllName);

/** 
\brief 卸载所有文件解析、字幕解析动态库
\attention \n
该接口必须在调用::HI_SVR_PLAYER_Init接口后调用

\param[in] eDllType 动态库类型
\param[in] dllName 动态库名称，保留参数，暂不使用

\retval ::HI_SUCCESS 卸载成功
\retval ::HI_FAILURE 卸载失败

\see \n
无
*/
HI_S32 HI_SVR_PLAYER_UnRegisterDynamic(HI_SVR_PLAYER_DLLTYPE_E eDllType, const HI_CHAR *dllName);

/** 
\brief 打开/关闭player dbg信息
\attention \n
该接口可以在任何状态调用

\param[in] bEnable 使能值，HI_TRUE:打开player日志信息，HI_FALSE:关闭日志信息

\retval :: 无

\see \n
无
*/
HI_VOID HI_SVR_PLAYER_EnableDbg(HI_BOOL bEnable);

/** 
\brief 获取播放器版本号
\attention \n
该接口可以在任何状态调用

\param[out] pstVersion 播放器版本号

\retval :: 无

\see \n
无
*/
HI_VOID HI_SVR_PLAYER_GetVersion(HI_FORMAT_LIB_VERSION_S *pstVersion);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_SVR_PLAYER_H__ */

