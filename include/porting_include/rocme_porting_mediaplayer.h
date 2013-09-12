#ifndef _ROCME_PORTING_MEDIAPLAYER_H_
#define _ROCME_PORTING_MEDIAPLAYER_H_
#include "rocme_porting_typedef.h"
#ifdef __cplusplus
extern "C" {
#endif

#define INVALID_MPEG2TS_PID 0x1FFF

typedef enum {
	ROC_MEDIA_STREAM_SOURCE_DVB,
	ROC_MEDIA_STREAM_SOURCE_FILE
} Roc_Media_StreamSource_t;

typedef enum {
	ROC_MEDIA_STREAM_UNKNOWN 	= 0,	
	ROC_MEDIA_STREAM_VIDEO		= (1<<0),
	ROC_MEDIA_STREAM_AUDIO		= (1<<1),
	ROC_MEDIA_STREAM_SUBTITLE	= (1<<2),
} Roc_Media_Stream_t;

typedef enum {
	ROC_MEDIA_SPEED_NORMAL = 0,		// 正常速度
	ROC_MEDIA_SPEED_FF2X,			// 2倍速快进
	ROC_MEDIA_SPEED_FF4X,			// 4倍速快进
	ROC_MEDIA_SPEED_FF8X,			// 8倍速快进
	ROC_MEDIA_SPEED_FF16X,			// 16倍速快进
	ROC_MEDIA_SPEED_FF32X,			// 32倍速快进
	ROC_MEDIA_SPEED_FS2X,			// 1/2倍速慢进	
	ROC_MEDIA_SPEED_FS4X,			// 1/4倍速快进	
	ROC_MEDIA_SPEED_FS8X,			// 1/8倍速快进	
	ROC_MEDIA_SPEED_FS16X,			// 1/16倍速快进
	ROC_MEDIA_SPEED_FS32X,			// 1/32倍速快进
	ROC_MEDIA_SPEED_BF2X,			// 2倍速快退
	ROC_MEDIA_SPEED_BF4X,			// 4倍速快退
	ROC_MEDIA_SPEED_BF8X,			// 8倍速快退
	ROC_MEDIA_SPEED_BF16X,			// 16倍速快退
	ROC_MEDIA_SPEED_BF32X,			// 32倍速快退
	ROC_MEDIA_SPEED_BS2X,			// 1/2倍速慢退	
	ROC_MEDIA_SPEED_BS4X,			// 1/4倍速慢退
	ROC_MEDIA_SPEED_BS8X,			// 1/8倍速慢退
	ROC_MEDIA_SPEED_BS16X,			// 1/16倍速慢退
	ROC_MEDIA_SPEED_BS32X,			// 1/32倍速慢退
} Roc_Media_Speed_t;


typedef enum {
	ROC_MEDIA_CODEC_UNKNOWN 	= 0,
/* 对视频解码器的支持 */
	ROC_MEDIA_CODEC_V_MPEG	= (1<<0),
	ROC_MEDIA_CODEC_V_H264	= (1<<1),
	ROC_MEDIA_CODEC_V_MPEG4	= (1<<2),
	ROC_MEDIA_CODEC_V_VC1	= (1<<3),
	ROC_MEDIA_CODEC_V_FLV1	= (1<<4),
	ROC_MEDIA_CODEC_V_VP6	= (1<<5),
	ROC_MEDIA_CODEC_V_VP6F	= (1<<6),
	ROC_MEDIA_CODEC_V_RAW	= (1<<7),
	ROC_MEDIA_CODEC_V_AVS	= (1<<8),

/* 对音频解码器的支持 */
	ROC_MEDIA_CODEC_A_MPEG1	= (1<<16),
	ROC_MEDIA_CODEC_A_MPEG2	= (1<<17),
	ROC_MEDIA_CODEC_A_MPEG3	= (1<<18),
	ROC_MEDIA_CODEC_A_AC3	= (1<<19),
	ROC_MEDIA_CODEC_A_AAC	= (1<<20),
	ROC_MEDIA_CODEC_A_HEAAC	= (1<<21),
	ROC_MEDIA_CODEC_A_WMA	= (1<<22),
	ROC_MEDIA_CODEC_A_DDPLS	= (1<<23),
	ROC_MEDIA_CODEC_A_PCM	= (1<<24),
	ROC_MEDIA_CODEC_A_ADPCM	= (1<<25),
	ROC_MEDIA_CODEC_A_VORBIS = (1<<26),

} Roc_Media_Codec_t;

typedef enum {
	ROC_MEDIA_EVT_UNKNOWN = -1,
	ROC_MEDIA_EVT_NEW_FRAME = 0,
	ROC_MEDIA_EVT_BITBUFFER_UNDERFLOW,

	ROC_MEDIA_EVT_NR
} Roc_Media_Event_t;

typedef struct {
	long long TimeStamp;
} Roc_Media_NewFrameEventData_t;

/************************************************************************************
 * 平台解码器通过此函数接口获取用户层更新的输入循环缓冲区的写指针
 * 参数
 *		@handle			用户层上下文数据对象
 *		@address_p		返回输入循环缓冲区的写指针
 * 返回值
 *		0				成功
 *		< 0				失败
 ************************************************************************************/
typedef UINT32_T (*Roc_Media_GetWriteAddress_t)(void * const handle, void** const address_p);

/************************************************************************************
 * 平台解码器通过此函数接口通知用户层输入循环缓冲区的读指针
 * 参数
 *		@handle			用户层上下文数据对象
 *		@address_p		传入输入循环缓冲区的读指针
 *		0				成功
 *		< 0				失败
 ************************************************************************************/
typedef UINT32_T (*Roc_Media_InformReadAddress_t)(void * const handle, void* const address);

/************************************************************************************
 * 平台解码器通过此函数接口通知用户层输出一帧新的音频或视频帧
 * 参数
 *		@handle			用户层上下文数据对象
 *		@timestamp		新的音频或视频时间戳
 *		0				成功
 *		< 0				失败
 ************************************************************************************/
typedef void (* Roc_Media_EventCallback_t)(Roc_Media_Event_t Event, 
										   const void *EventData,
										   const void *SubscriberData);

typedef struct {
	Roc_Media_StreamSource_t StreamSource;
	Roc_Media_Stream_t StreamType;
	Roc_Media_Codec_t CodecType;
	void *BufferHandler;
	Roc_Media_GetWriteAddress_t GetWriteAddress_p;
	Roc_Media_InformReadAddress_t InformReadAddress_p;	
} Roc_Media_OpenParams_t;

/************************************************************************************
 * 初始化平台媒体解码器模块
 * 
 * 参数:	
 *		无
 *		
 * 说明:
 *		无
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_init(void);

/************************************************************************************
 * 销毁平台媒体解码器模块
 * 
 * 参数:	
 *		无
 *		
 * 说明:
 *		无
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_term(void);


INT32_T rocme_porting_media2_codec(UINT32_T *CodecMask);
/************************************************************************************
 * 从平台打开一个硬件媒体解码器
 * 
 * 参数:	
 *		@MediaHandle: 返回平台解码器句柄, 对平台解码器的操作基于此句柄
 *		@OpenParams
 *           .StreamSource: ROC_MEDIA_STREAM_SOURCE_DVB		- 直播流播放
 *                          ROC_MEDIA_STREAM_SOURCE_FILE	- 文件播放
 *           .StreamType: ROC_MEDIA_STREAM_VIDEO	-获取视频解码器
 *                        ROC_MEDIA_STREAM_AUDIO	-获取音频解码器,
 *                        ROC_MEDIA_STREAM_TS	    -获取TS流解码器
 *                         
 *           .CodecType:  基本码流的编码格式, 参见Roc_Media_Stream_t定义
 *           
 *           .BufferHandler: 操作解码器输入位流缓存的上下文对象
 *
 *           .GetWriteAddress_p: 平台解码器通过此函数接口获取位流缓存的写指针
 *
 *           .InformReadAddress_p: 平台解码器通过此函数接口通知应用更新位流缓存的读指针
 *             
 *      @BitBufferAddr: 如果不为空, 返回位流缓存的基地址
 *
 *      @BitBufferSize: 如果不为空, 返回位流缓存的大小
 *		
 * 说明:
 *		
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_open(UINT32_T *MediaHandle,
								  Roc_Media_OpenParams_t *OpenParams,
								  void **BitBufferBase,
								  UINT32_T *BitBufferSize);

/************************************************************************************
 * 关闭平台解码器
 * 
 * 参数:	
 *		@MediaHandle	平台解码器对象句柄
 *		
 * 说明:
 *
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_close(UINT32_T MediaHandle);

/************************************************************************************
 * 启动平台的解码器开始解码
 * 
 * 参数:	
 *		@MediaHandle			平台解码器对象句柄
 *		
 * 说明:
 *		调用此接口开始平台解码器的解码
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_start(UINT32_T MediaHandle);

/************************************************************************************
 * 停止平台解码器的解码
 * 
 * 参数:	
 *		@MediaHandle: 解码器句柄
 *		
 * 说明:
 *		None
 *
 * @return: 
 *		==0: 调用成功
 *		<0:  调用失败
 ************************************************************************************/
INT32_T rocme_porting_media2_stop(UINT32_T MediaHandle);

INT32_T rocme_porting_media2_pause(UINT32_T MediaHandle);

INT32_T rocme_porting_media2_resume(UINT32_T MediaHandle);

INT32_T rocme_porting_media2_hide(UINT32_T MediaHandle);

INT32_T rocme_porting_media2_display(UINT32_T MediaHandle);



INT32_T rocme_porting_media2_speed(UINT32_T MediaHandle, Roc_Media_Speed_t Speed, int FrameDuration);

INT32_T rocme_porting_media2_subscribe_event(UINT32_T MediaHandle, 
										     Roc_Media_Event_t Event, 
										     Roc_Media_EventCallback_t CallbackFunc,
										     void *SubscriberData);

INT32_T rocme_porting_media2_unsubscribe_event(UINT32_T MediaHandle, Roc_Media_Event_t Event);

#ifdef __cplusplus
} // c++ support
#endif

#endif
