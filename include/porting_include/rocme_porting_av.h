/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_av.h

Author      : DSM

Description : The poriting interface & macro definition for Audio/video module.

History     :
              2009.12.20          Created         Jason
              2010.01.08          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTNG_AV_H_
#define _ROCME_PORTNG_AV_H_

#include "rocme_porting_typedef.h"
#include "rocme_porting_graphics.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/

/*音频输出通道*/
typedef enum Roc_Audio_Device
{
    ROC_AUDIO_DEVICE_UNKNOW,/*未知输出设备*/
    ROC_AUDIO_DEVICE_HDMI,/*HDMI 输出设备*/
    ROC_AUDIO_DEVICE_SPDIF,/*SPDIF 输出设备*/
}Roc_Audio_Device_e;


/*音频类型*/
typedef enum Roc_Audio_Type
{
    ROC_AUDIO_TYPE_AC3      = 0x00,  /*AC3音频编码格式  */
    ROC_AUDIO_TYPE_MPEG1    = 0x01,  /*MPEG1音频编码格式*/
    ROC_AUDIO_TYPE_MPEG2    = 0x02,  /*MPEG2音频编码格式*/
    ROC_AUDIO_TYPE_PCM      = 0x03,  /*PCM音频编码格式  */
    ROC_AUDIO_TYPE_MP3      = 0x04,  /*MP3音频编码格式  */
    ROC_AUDIO_TYPE_MLP      = 0x05,  /*MLP音频编码格式  */
    ROC_AUDIO_TYPE_MPEG_AAC = 0x06,  /*AAC音频编码格式  */
    ROC_AUDIO_TYPE_UNKNOWN  = 0xFF   /*未知音频编码格式 */
}Roc_Audio_Type_e;


/*声道模式*/
typedef enum Roc_Audio_Mode
{
    ROC_AUDIO_MODE_MONO     = 0x00,  /*单声道*/
    ROC_AUDIO_MODE_STEREO   = 0x01,  /*立体声*/
    ROC_AUDIO_MODE_LEFT     = 0x02,  /*左声道*/
    ROC_AUDIO_MODE_RIGHT    = 0x03,  /*右声道*/
    ROC_AUDIO_MODE_UNKNOWN  = 0xFF   /*未知声道类型*/
}Roc_Audio_Mode_e;

/*视频类型*/
typedef enum Roc_Video_Type
{
    ROC_VIDEO_TYPE_MPEG     = 0x00,  /*MPGE 视频编码格式*/
    ROC_VIDEO_TYPE_MPEG2    = 0x01,  /*MPGE2视频编码格式*/
    ROC_VIDEO_TYPE_MPEG4    = 0x02,  /*MPGE4视频编码格式*/
    ROC_VIDEO_TYPE_H264     = 0x03,  /*H.264视频编码格式*/
    ROC_VIDEO_TYPE_VC1      = 0x04,  /*VC1视频编码格式  */
    ROC_VIDEO_TYPE_AVS      = 0x05,  /*AVS视频编码格式  */
    ROC_VIDEO_TYPE_UNKNOWN  = 0xFF   /*未知视频编码格式 */
}Roc_Video_Type_e;

/*视频制式*/
typedef enum Roc_Vid_DENC_Mode
{
    ROC_DENC_MODE_NONE      = 0x00,  /*未定义的视频制式          */
    ROC_DENC_MODE_NTSCM     = 0x01,  /*正交平衡调幅制式          */
    ROC_DENC_MODE_PALN      = 0x02,  /*逐行倒相正交平衡调幅制式  */
    ROC_DENC_MODE_SECAM     = 0x03   /*顺序传送彩色与存储复用制式*/
}Roc_Vid_DENC_Mode_e;

/*视频画面比例*/
typedef enum Roc_Vid_Aspect_Ratio
{
    ROC_ASPECT_RATIO_NONE   = 0x00,  /*未定义的视频画面比例*/
    ROC_ASPECT_RATIO_16TO9  = 0x01,  /*16:9画面比例        */
    ROC_ASPECT_RATIO_4TO3   = 0x02,  /*4:3画面比例         */
    ROC_ASPECT_RATIO_SQUARE = 0x03   /*1:1画面比例         */
}Roc_Vid_Aspect_Ratio_e;

/*显示分层定义*/
typedef enum Roc_OutPut_Layer
{   
    ROC_LAYER_CURSOR     = 0x00,  /*光标层,目前未使用*/
    ROC_LAYER_OSD        = 0x01,  /*默认是最上层,GUI使用此层*/
    ROC_LAYER_VIDEO      = 0x02,  /*默认是第二层,VIDEO使用此层*/
    ROC_LAYER_STILL      = 0x03,  /*默认是第三层,静态单帧I帧使用此层*/
    ROC_LAYER_BACKGROUND = 0x04,  /*默认是第四层,通常为单色层*/
    ROC_NUM_LAYERS       = 0x05,
    ROC_STILL_NOT_DISPLAY        /*仅仅解码到静态层的缓冲区，但不做输出显示*/
}Roc_OutPut_Layer_e;

/*视频画面比例强制转换，详细说明见数码视讯中间件移植文档*/
typedef enum Roc_Vid_AspectRatioConversion
{
    ROC_DISPLAY_AR_CONVERSION_NONE          = 0x00,  /*未定义的视频画面比例转换*/
    ROC_DISPLAY_AR_CONVERSION_PAN_SCAN      = 0x01,  /*PAN&SCAN 型画面比转换，即裁剪原始画面，整体以满屏幕输出，无黑边*/
    ROC_DISPLAY_AR_CONVERSION_LETTER_BOX    = 0x02,  /*LETTER BOX 型画面比转换，即保留全部原始画面，屏幕未使用部分用黑边来填充*/
    ROC_DISPLAY_AR_CONVERSION_COMBINED      = 0x03,  /*PAN&SCAN和LETTER BOX 混合比例转换*/
    ROC_DISPLAY_AR_CONVERSION_IGNORE        = 0x04   /*忽略转换，直接按照原始比例输出画面*/
}Roc_Vid_AspectRatioConversion_e;

/*视频参数*/
typedef struct Roc_Vid_BCSLevel
{
    UINT8_T         brightness;  /*视频层亮度  ，范围 0 ~ 100   */
    UINT8_T         contrast;    /*视频层对比度，范围 0 ~ 100   */
    UINT8_T         saturation;  /*视频层饱和度，范围 0 ~ 100   */
}Roc_Vid_BCSLevel_t;

/*节目播出参数*/
typedef struct Roc_AV_Para
{
    UINT16_T            aud_pid;   /*节目音频pid */
    UINT16_T            vid_pid;   /*节目视频pid */
    UINT16_T            pcr_pid;   /*节目PCR pid */
    Roc_Audio_Type_e    aud_type;  /*节目音频类型*/
    Roc_Video_Type_e    vid_type;  /*节目视频类型*/
}Roc_AV_Para_t;

/*PID参数类型*/
typedef enum Roc_PID_Type
{
    ROC_AUDIO_PID       = 0x00,  /*表明传入的PID为音频PID*/
    ROC_VIDEO_PID       = 0x01,  /*表明传入的PID为视频PID*/
    ROC_PCR_PID         = 0x02,  /*表明传入的PID为PCR PID*/
    ROC_SUBTITLE_PID    = 0x03,  /*表明传入的PID为字幕PID*/
    ROC_RESERVE_PID     = 0xFF   /*保留位*/
}Roc_PID_Type_e;

/*视频解码事件*/
typedef enum Roc_AV_Event
{
    ROC_VID_START_EVT           = 0x00, /*正常视频解码开始事件*/
    ROC_VID_STOPPED_EVT         = 0x01, /*视频解码器停止工作事件*/
    ROC_VID_NEW_FRAME_EVT       = 0x02, /*视频解码新FRAME的事件*/
    ROC_VID_DECODING_ERROR_EVT  = 0x03, /*视频解码器解码出错事件*/
    ROC_VID_DATA_ERROR_EVT      = 0x04, /*视频数据流错误事件-overflow、underflow、data-stream error etc.*/

    ROC_AUD_START_EVT           = 0x10, /*正常音频解码开始事件*/
    ROC_AUD_STOPPED_EVT         = 0x11, /*音频解码器停止工作事件*/
    ROC_AUD_NEW_FRAME_EVT       = 0x12, /*音频解码新FRAME的事件*/
    /*ROC_AUD_DECODING_ERROR_EVT  = 0x13, 音频解码器解码出错事件*/
    ROC_AUD_DATA_ERROR_EVT      = 0x14  /*音频数据流错误事件-overflow、underflow、data-stream error etc.*/
    
}Roc_AV_Event_e;

/*视频输出分辨率*/
typedef enum ROC_VTG_TimingMode
{
	ROC_1080P,      /*STVTG_TIMING_MODE_1080P50000_148500 : SMPTE 274M #3  P50 */
	ROC_1080I,      /*STVTG_TIMING_MODE_1080I50000_74250 :  SMPTE 295M #2  I50 */
	ROC_720P,       /*STVTG_TIMING_MODE_720P60000_74250 :   EIA770.3 #1 P60 = SMPTE 296M #1 P60 */
	ROC_576P,       /*STVTG_TIMING_MODE_576P50000_27000 :   Australian mode*/
	ROC_576I,       /*STVTG_TIMING_MODE_576I50000_13500 :   PAL B,D,G,H,I,N, SECAM */
	ROC_480P,       /*STVTG_TIMING_MODE_480P60000_25200 :   VGA modes*/
	ROC_480I,       /*STVTG_TIMING_MODE_480I59940_13500 :   NTSC, PAL M */
	ROC_COUNT	
}ROC_VTG_TimingMode_e;


/*视频解码事件回调函数定义*/
typedef INT32_T (*rocme_porting_av_event_callback) ( INT32_T channel_index, void *param, Roc_AV_Event_e av_event,UINT32_T handler);

/*视频解码事件注册参数结构定义*/
typedef struct Roc_AV_Evt_Param
{
    INT32_T                         channel_index;  /*解码器关联的数据通道索引*/
    Roc_AV_Event_e                  av_event;       /*视频解码事件*/
    rocme_porting_av_event_callback callback;       /*事件回调函数*/
    void                            *cb_param;      /*回调函数的私有参数*/
}Roc_AV_Evt_Param_t;

/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/


/**************************************************************************
函数名称: 
            rocme_porting_av_init
功能说明: 
            音视频解码初始化，中间件会在启动时调用此函数，若在启动中间件之前
        机顶盒已经做好了音视频的初始化，此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            void
    输出参数：
            无
返    回： 
    成功 : 0            ( 初始化成功 )
    失败 : -1 或 错误码 ( 初始化失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_av_init(void);

/**************************************************************************
函数名称: 
            rocme_porting_av_play
功能说明: 
            根据传入的音视频参数，在指定的数据通道上播放指定的节目，当无法单
        独实现音视频的分离控制，即如下函数时
        rocme_porting_av_pid_set();
        rocme_porting_audio_play();
        rocme_porting_video_play();
        此函数功能必须实现。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ avpara        ] : 音视频播放参数结构体,具体如下:
                                aud_pid   -  节目音频pid 
                                vid_pid   -  节目视频pid 
                                pcr_pid   -  节目PCR pid 
                                aud_type  -  节目音频类型 
                                vid_type  -  节目视频类型 
    输出参数：
            无
返    回： 
    成功 : 0            ( 节目成功播放 )
    失败 : -1 或 错误码 ( 节目播放失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_av_play(const INT32_T channel_index,const Roc_AV_Para_t av_para);

/**************************************************************************
函数名称: 
            rocme_porting_av_stop
功能说明: 
            停止指定数据通道上的视频播放，当无法单独实现音视频的分离控制，即
        如下函数时
        rocme_porting_av_pid_clean();
        rocme_porting_audio_stop();
        rocme_porting_video_stop();
        此函数功能必须实现。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ is_last_pic   ] : 是否保留停止视频前的最后一帧画面:
                                ROC_TRUE   -  保留最后一帧画面
                                ROC_FALSE  -  不保留最后一帧画面，并可显示出背
                            景I 帧
    输出参数：
            无
返    回： 
    成功 : 0            ( 节目成功停止 )
    失败 : -1 或 错误码 ( 节目停止失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_av_stop(const INT32_T channel_index,const ROC_BOOL is_last_pic);

/**************************************************************************
函数名称: 
            rocme_porting_av_pid_set
功能说明: 
            设置指定数据通道上的指定数据源(音频、视频、PCR和字幕等)的PID
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ type          ] : PID参数类型结构体，具体如下:
                                ROC_AUDIO_PID     -  表明传入的PID为音频PID 
                                ROC_VIDEO_PID     -  表明传入的PID为视频PID
                                ROC_PCR_PID       -  表明传入的PID为PCR PID
                                ROC_SUBTITLE_PID  -  表明传入的PID为字幕PID
            [ pid           ] : 具体的PID数值
    输出参数：
            无
返    回： 
    成功 : 0            ( 成功设置了指定数据源的PID )
    失败 : -1 或 错误码 ( 设置PID出错 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_av_pid_set(const INT32_T channel_index,const Roc_PID_Type_e type,const UINT16_T pid);

/**************************************************************************
函数名称: 
            rocme_porting_av_pid_clean
功能说明: 
            清除指定数据通道上的指定数据源(音频、视频、PCR和字幕等)对其PID
        的占用，即清除掉其slot的过滤条件值。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ type          ] : PID参数类型结构体，具体如下:
                                ROC_AUDIO_PID     -  表明传入的PID为音频PID 
                                ROC_VIDEO_PID     -  表明传入的PID为视频PID
                                ROC_PCR_PID       -  表明传入的PID为PCR PID
                                ROC_SUBTITLE_PID  -  表明传入的PID为字幕PID
    输出参数：
            无
返    回： 
    成功 : 0            ( 清除PID成功 )
    失败 : -1 或 错误码 ( 清除PID失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_av_pid_clean(const INT32_T channel_index,const Roc_PID_Type_e type);

/**************************************************************************
函数名称: 
            rocme_porting_audio_play
功能说明: 
            使能指定的数据通道上的音频解码器开始工作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ type          ] : 音频数据的编码类型，具体如下:
                                ROC_AUDIO_TYPE_AC3       -  AC3音频编码格式
                                ROC_AUDIO_TYPE_MPEG1     -  MPEG1音频编码格式
                                ROC_AUDIO_TYPE_MPEG2     -  MPEG2音频编码格式
                                ROC_AUDIO_TYPE_PCM       -  PCM音频编码格式
                                ROC_AUDIO_TYPE_MP3       -  MP3音频编码格式
                                ROC_AUDIO_TYPE_MLP       -  MLP音频编码格式
                                ROC_AUDIO_TYPE_MPEG_AAC  -  AAC音频编码格式
                                ROC_AUDIO_TYPE_UNKNOWN   -  未知音频编码格式 
    输出参数：
            无
返    回： 
    成功 : 0            ( 启动音频解码器成功 )
    失败 : -1 或 错误码 ( 启动音频解码器失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_audio_play(const INT32_T channel_index,const Roc_Audio_Type_e type);

/**************************************************************************
函数名称: 
            rocme_porting_audio_stop
功能说明: 
            停止指定的数据通道上的音频解码器工作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
    输出参数：
            无
返    回： 
    成功 : 0            ( 停止音频解码器成功 )
    失败 : -1 或 错误码 ( 停止音频解码器失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_audio_stop(const INT32_T channel_index);

/**************************************************************************
函数名称: 
            rocme_porting_audio_set_volume
功能说明: 
            设置指定数据通道上的节目输出音量，音量取值范围 0 ~ 100。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ volume        ] : 音量值，取值范围 0 ~ 100
    输出参数：
            无
返    回： 
    成功 : 0            ( 音量设定成功 )
    失败 : -1 或 错误码 ( 音量设定失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_audio_set_volume(const INT32_T channel_index,const UINT32_T volume);

/**************************************************************************
函数名称: 
            rocme_porting_audio_set_mute
功能说明: 
            设置指定数据通道上的节目输出是否是静音。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ is_mute       ] : 是否静音标识:
                                ROC_TRUE   -  静音
                                ROC_FALSE  -  非静音 
    输出参数：
            无
返    回： 
    成功 : 0            ( 是否静音设置成功 )
    失败 : -1 或 错误码 ( 是否静音设置失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_audio_set_mute(const INT32_T channel_index,const ROC_BOOL is_mute);

/**************************************************************************
函数名称: 
            rocme_porting_audio_set_mode
功能说明: 
            设置指定数据通道上的节目输出声道模式。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ aud_mode      ] : 声道模式，具体如下:
                                ROC_AUDIO_MODE_MONO    -  单声道
                                ROC_AUDIO_MODE_STEREO  -  立体声
                                ROC_AUDIO_MODE_LEFT    -  左声道
                                ROC_AUDIO_MODE_RIGHT   -  右声道
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置声道模式成功 )
    失败 : -1 或 错误码 ( 设置声道模式失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_audio_set_mode(const INT32_T channel_index,const Roc_Audio_Mode_e aud_mode);

/**************************************************************************
函数名称: 
            rocme_porting_audio_set_output_mode
功能说明: 
            设置指定音频输出设备输出音频的类型，默认为pcm输出。
参数说明：
    输入参数：
            [ aud_device ] : 音频输出设备，参见类型参见Roc_Audio_Device_e
            [ aud_type    ] : 音频输出类型，具体类型参见Roc_Audio_Type_e
返    回： 
    成功 : 0            ( 设置成功 )
    失败 : -1 或 错误码 ( 设置失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_audio_set_output_mode(Roc_Audio_Device_e aud_device,const Roc_Audio_Type_e aud_type);

/**************************************************************************
函数名称: 
            rocme_porting_video_play
功能说明: 
            使能指定的数据通道上的视频解码器开始工作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ type          ] : 视频数据的编码类型，具体如下:
                                ROC_VIDEO_TYPE_MPEG     -  MPGE 视频编码格式
                                ROC_VIDEO_TYPE_MPEG2    -  MPGE2视频编码格式
                                ROC_VIDEO_TYPE_MPEG4    -  MPGE4视频编码格式
                                ROC_VIDEO_TYPE_H264     -  H.264视频编码格式
                                ROC_VIDEO_TYPE_VC1      -  VC1视频编码格式
                                ROC_VIDEO_TYPE_AVS      -  AVS视频编码格式
                                ROC_VIDEO_TYPE_UNKNOWN  -  未知视频编码格式
    输出参数：
            无
返    回： 
    成功 : 0            ( 启动视频解码器成功 )
    失败 : -1 或 错误码 ( 启动视频解码器失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_play(const INT32_T channel_index,const Roc_Video_Type_e type);

/**************************************************************************
函数名称: 
            rocme_porting_video_stop
功能说明: 
            停止指定的数据通道上的视频解码器工作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ is_last_pic   ] : 是否保留停止视频前的最后一帧画面:
                                ROC_TRUE   -  保留最后一帧画面
                                ROC_FALSE  -  不保留最后一帧画面，并可显示出背
                            景I 帧
    输出参数：
            无
返    回： 
    成功 : 0            ( 停止视频解码器成功 )
    失败 : -1 或 错误码 ( 停止视频解码器失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_stop(const INT32_T channel_index, const ROC_BOOL is_last_pic);

/**************************************************************************
函数名称: 
            rocme_porting_video_set_display
功能说明: 
            设置是否开启指定数据通道上的视频层。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ enable        ] : 是否开启视频层标识:
                                ROC_TRUE   -  开启指定的视频层
                                ROC_FALSE  -  关闭指定的视频层
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置是否开启视频层成功 )
    失败 : -1 或 错误码 ( 设置是否开启视频层失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_set_display(const INT32_T channel_index,const ROC_BOOL enable);

/**************************************************************************
函数名称: 
            rocme_porting_video_set_window
功能说明: 
            设置指定的数据通道上的视频输出窗口的坐标和大小。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ height        ] : 视频窗口的高
            [ width         ] : 视频窗口的宽
            [ x_start       ] : 视频窗口的横起始坐标
            [ y_start       ] : 视频窗口的纵起始坐标
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置视频窗口位置成功 )
    失败 : -1 或 错误码 ( 设置视频窗口位置失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_set_window(const INT32_T channel_index,const UINT32_T height,const UINT32_T width,const UINT32_T x_start,const UINT32_T y_start);

/**************************************************************************
函数名称: 
            rocme_porting_video_set_denc
功能说明: 
            设置指定数据通道上的视频输出制式。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ denc_mode     ] : 视频制式，具体如下:
                                ROC_DENC_MODE_NONE   -  未定义的视频制式
                                ROC_DENC_MODE_NTSCM  -  正交平衡调幅制式
                                ROC_DENC_MODE_PALN   -  逐行倒相正交平衡调幅制式
                                ROC_DENC_MODE_SECAM  -  顺序传送彩色与存储复用制式
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置视频制式成功 )
    失败 : -1 或 错误码 ( 设置视频制式失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_set_denc(const INT32_T channel_index,const Roc_Vid_DENC_Mode_e denc_mode);

/**************************************************************************
函数名称: 
            rocme_porting_video_set_aspect
功能说明: 
            设置指定数据通道上的视频输出画面的宽高比。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ aspect_ratio  ] : 视频输出画面的宽高比，具体如下:
                                ROC_ASPECT_RATIO_NONE    -  未定义的视频画面比例
                                ROC_ASPECT_RATIO_16TO9   -  16:9画面比例
                                ROC_ASPECT_RATIO_4TO3    -  4:3画面比例
                                ROC_ASPECT_RATIO_SQUARE  -  1:1画面比例
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置画面比例成功 )
    失败 : -1 或 错误码 ( 设置画面比例失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_set_aspect(const INT32_T channel_index,const Roc_Plane_Aspect_Ratio_e aspect_ratio);

/**************************************************************************
函数名称: 
            rocme_porting_video_set_aspect_conversion
功能说明: 
            设置指定数据通道上的画面强制转换比例。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ ar_conversion ] : 画面强制转换比例类型，具体如下:
                                ROC_DISPLAY_AR_CONVERSION_NONE        
                            -  未定义的视频画面比例转换
                                ROC_DISPLAY_AR_CONVERSION_PAN_SCAN    
                            -  PAN&SCAN 型画面比转换，即裁剪原始画面，整体以
                            满屏幕输出，无黑边
                                ROC_DISPLAY_AR_CONVERSION_LETTER_BOX  
                            -  LETTER BOX 型画面比转换，即保留全部原始画面，
                            屏幕未使用部分用黑边来填充
                                ROC_DISPLAY_AR_CONVERSION_COMBINED    
                            -  PAN&SCAN和LETTER BOX 混合比例转换
                                ROC_DISPLAY_AR_CONVERSION_IGNORE      
                            -  忽略转换，直接按照原始比例输出画面
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置画面比例强制转换成功 )
    失败 : -1 或 错误码 ( 设置画面比例强制转换失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_set_aspect_conversion(const INT32_T channel_index,const Roc_Vid_AspectRatioConversion_e ar_conversion);

/**************************************************************************
函数名称: 
            rocme_porting_video_set_bcs
功能说明: 
            设置指定数据通道上的视频表现参数(亮度、对比度和饱和度)。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ bcs_level     ] : 视频表现参数，具体如下:
                                 brightness  -  视频层亮度  ，范围 0 ~ 100
                                 contrast    -  视频层对比度，范围 0 ~ 100
                                 saturation  -  视频层饱和度，范围 0 ~ 100
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置视频表现参数成功 )
    失败 : -1 或 错误码 ( 设置视频表现参数失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_set_bcs(const INT32_T channel_index,const Roc_Vid_BCSLevel_t bcs_level);

/**************************************************************************
函数名称: 
            rocme_porting_video_set_vtg
功能说明: 
            设置指定数据通道上的视频输出分辨率。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ vtg_mode     ] : 视频输出分辨率
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置视频输出分辨率成功 )
    失败 : -1 或 错误码 ( 设置视频输出分辨率失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_video_set_vtg(const INT32_T channel_index,const ROC_VTG_TimingMode_e vtg_mode);


/*************************************************************************
函数名称: 
            rocme_porting_video_set_fullscreen
功能说明: 
            设置视频为全屏。
参数说明：
    输入参数：
	     无
输出参数：
            无
返    回： 
    成功 : 0            ( 设置成功 )
    失败 : -1 或 错误码 ( 设置失败 )
修改记录：
***************************************************************************/
INT32_T rocme_porting_video_set_fullscreen(void);


/**************************************************************************
函数名称: 
            rocme_porting_iframe_set_display
功能说明: 
            设置是否开启静态层的显示
参数说明：
    输入参数：
            [ enable        ] : 是否开启静态层标识:
                                ROC_TRUE   -  开启静态层，可以看到静态层I帧图片的显示
                                ROC_FALSE  -  关闭静态层，不可以看到静态层I帧图片的显示
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置是否开启静态层成功 )
    失败 : -1 或 错误码 ( 设置是否开启静态层失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_iframe_set_display(ROC_BOOL enable);

/**************************************************************************
函数名称: 
            rocme_porting_dec_iframe_still
功能说明: 
            使用指定数据通道解码指定的一幅I帧，并将其在显示在指定的层上。
            如指定layer = ROC_LAYER_VIDEO，即将解码完毕的I帧输出显示到
            视频层上(若视频层关闭，则将其自动打开)
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
            [ *data_ptr     ] : I帧数据的头指针
            [ data_len      ] : I帧数据的长度
            [ layer         ] : 显示的层的类型
    输出参数：
            无
返    回： 
    成功 : 0            ( 解码I帧成功 )
    失败 : -1 或 错误码 ( 解码I帧失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_dec_iframe_still(const INT32_T channel_index,const UINT8_T *data_ptr,const UINT32_T data_len,const Roc_OutPut_Layer_e layer);

/**************************************************************************
函数名称: 
            rocme_porting_get_iframe_buff
功能说明: 
            获取底层解码I帧时，使用的内存buff的头指针和长度
参数说明：
    输入参数：
            无
    输出参数：
            [ **buff_ptr ] : 数据通道索引值(非具体的解码器ID)
            [ *buff_len     ] : I帧数据的头指针
返    回： 
    成功 : 0            ( 解码I帧成功 )
    失败 : -1 或 错误码 ( 解码I帧失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_get_iframe_buff( void **buff_ptr , UINT32_T *buff_len );


/**************************************************************************
函数名称: 
            rocme_porting_dec_black_iframe
功能说明: 
            将某输入层填充为黑色
参数说明：
    输入参数：
            [ layer         ] : 显示的层的类型
    输出参数：
            无
返    回： 
    成功 : 0            ( 填充成功 )
    失败 : -1 或 错误码 ( 填充失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_dec_black_iframe(const Roc_OutPut_Layer_e layer);

/**************************************************************************
函数名称: 
            rocme_porting_des_init
功能说明: 
            初始化解扰器。
参数说明：
    输入参数：
            无
    输出参数：
            无
返    回： 
    成功 : 0            ( 解扰器初始化成功 )
    失败 : -1 或 错误码 ( 解扰器初始化失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_des_init(void);

/**************************************************************************
函数名称: 
            rocme_porting_des_term
功能说明: 
            关闭解扰器
参数说明：
    输入参数：
            无
    输出参数：
            无
返    回： 
    成功 : 0            ( 解扰器关闭成功 )
    失败 : -1 或 错误码 ( 解扰器关闭失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_des_term(void);

/**************************************************************************
函数名称: 
            rocme_porting_des_audio_start
功能说明: 
            使能指定数据通道上的音频解扰开始工作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
    输出参数：
            无
返    回： 
    成功 : 0            ( 启动音频解扰成功 )
    失败 : -1 或 错误码 ( 启动音频解扰失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_des_audio_start(const INT32_T channel_index);

/**************************************************************************
函数名称: 
            rocme_porting_des_audio_stop
功能说明: 
            停止指定数据通道上的音频解扰。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
    输出参数：
            无
返    回： 
    成功 : 0            ( 停止音频解扰成功 )
    失败 : -1 或 错误码 ( 停止音频解扰失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_des_audio_stop(const INT32_T channel_index);

/**************************************************************************
函数名称: 
            rocme_porting_des_video_start
功能说明: 
            使能指定数据通道上的视频解扰开始工作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
    输出参数：
            无
返    回： 
    成功 : 0            ( 启动视频解扰成功 )
    失败 : -1 或 错误码 ( 启动视频解扰失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_des_video_start(const INT32_T channel_index);

/**************************************************************************
函数名称: 
            rocme_porting_des_video_stop
功能说明: 
            停止指定数据通道上的视频解扰。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的解码器ID)
    输出参数：
            无
返    回： 
    成功 : 0            ( 停止视频解扰成功 )
    失败 : -1 或 错误码 ( 停止视频解扰失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_des_video_stop(const INT32_T channel_index);

/***************************************************************************
功能说明：
    设置视频解扰器控制字

参数说明：
    channel_index:通道标识符,适用于多通道平台
    pbyEvenKey:偶密钥,长度为8字节
    pbyOddKey: 奇密钥,长度为8字节

返    回： 
    0    ----成功
    -1   ----失败
***************************************************************************/
INT32_T rocme_porting_des_video_setcw(const INT32_T channel_index, UINT8_T *pbyEvenKey, UINT8_T *pbyOddKey);

/***************************************************************************
功能说明：
    设置音频解扰器控制字

参数说明：
    channel_index:通道标识符,适用于多通道平台
    pbyEvenKey:偶密钥,长度为8字节
    pbyOddKey: 奇密钥,长度为8字节

返    回： 
    0    ----成功
    -1   ----失败
***************************************************************************/
INT32_T rocme_porting_des_audio_setcw(const INT32_T channel_index, UINT8_T *pbyEvenKey, UINT8_T *pbyOddKey);

/**************************************************************************
函数名称: 
            rocme_porting_av_event_register
功能说明: 
            注册底层解码事件的通知
参数说明：
    输入参数：
            [ av_evt_param ] : 注册的数据事件的参数
    输出参数：
            [ *handler     ] : 控制此事件注册的句柄
返    回： 
    成功 : 0            ( 注册事件成功 )
    失败 : -1 或 错误码 ( 注册事件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_av_event_register(const Roc_AV_Evt_Param_t av_evt_param,UINT32_T *handler);

/**************************************************************************
函数名称: 
            rocme_porting_av_event_unregister
功能说明: 
            注销一个底层解码事件的通知
参数说明：
    输入参数：
            [ handler     ] : 控制此事件注册的句柄
    输出参数：
            无
返    回： 
    成功 : 0            ( 注册事件成功 )
    失败 : -1 或 错误码 ( 注册事件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_av_event_unregister(const UINT32_T handler);

/**************************************************************************
函数名称: 
	rocme_porting_dec_iframe
功能说明: 
	解码mpeg2-I帧图片到内存
参数说明：
输入参数：
	[ pSrcData     ] : I帧数据buffer
	[ nSrcDataLen  ] : I帧数据长度
	[ pDataBuf	   ] : 位图数据指针(输入输出参数)
	[ ColorType    ] : 期望解码完成后返回的位图颜色格式
输出参数：
	[ pDataBuf	   ] : 位图数据指针(输入输出参数)
	[ pWidth	   ] : 位图宽度
	[ pHeight	   ] : 位图高度
返    回： 
成功 : 0
失败 : -1 或 错误码
修改记录：
	新增解码MPEG2-IFrame接口 [4/30/2010 刘思翔]
**************************************************************************/
INT32_T rocme_porting_dec_iframe(
				 const UINT8_T * pSrcData, 
				 const UINT32_T nSrcDataLen, 
				 UINT8_T *pDataBuf, 
				 UINT32_T *pWidth, 
				 UINT32_T *pHeight,
				 const Roc_Plane_Color_Type_e ColorType
				 );

/**************************************************************************
函数名称: 
	rocme_porting_file_play_start
功能说明: 
	解码mpeg视频到指定层
参数说明：
输入参数：
	[ file_name    ] : 视频文件路径,比如/mnt/adv/rootMedia.mpg
    [ layer        ] : 显示的层的类型
输出参数：无
返    回： 
成功 : 0
失败 : -1 或 错误码
修改记录：
	临时增加解码MPEG视频接口，要求循环播放该视频，直到调用 rocme_porting_file_play_stop[3/30/2011 BAIGANG]
**************************************************************************/
INT32_T rocme_porting_file_play_start(const CHAR_T *file_name, const Roc_OutPut_Layer_e layer);

/**************************************************************************
函数名称: 
	rocme_porting_file_play_stop
功能说明: 
	停止解码mpeg视频到指定层
参数说明：
输入参数：无
输出参数：无
返    回： 
成功 : 0
失败 : -1 或 错误码
修改记录：
	临时增加解码MPEG视频接口 [3/30/2011 BAIGANG]
**************************************************************************/
INT32_T rocme_porting_file_play_stop();

INT32_T rocme_porting_show_bitmap(UINT32_T  bmWidth,UINT32_T  bmHeight,UINT32_T  bmPitch,UINT8_T *bmBits,const Roc_OutPut_Layer_e layer);


#endif
