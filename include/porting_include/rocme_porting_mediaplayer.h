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
	ROC_MEDIA_SPEED_NORMAL = 0,		// �����ٶ�
	ROC_MEDIA_SPEED_FF2X,			// 2���ٿ��
	ROC_MEDIA_SPEED_FF4X,			// 4���ٿ��
	ROC_MEDIA_SPEED_FF8X,			// 8���ٿ��
	ROC_MEDIA_SPEED_FF16X,			// 16���ٿ��
	ROC_MEDIA_SPEED_FF32X,			// 32���ٿ��
	ROC_MEDIA_SPEED_FS2X,			// 1/2��������	
	ROC_MEDIA_SPEED_FS4X,			// 1/4���ٿ��	
	ROC_MEDIA_SPEED_FS8X,			// 1/8���ٿ��	
	ROC_MEDIA_SPEED_FS16X,			// 1/16���ٿ��
	ROC_MEDIA_SPEED_FS32X,			// 1/32���ٿ��
	ROC_MEDIA_SPEED_BF2X,			// 2���ٿ���
	ROC_MEDIA_SPEED_BF4X,			// 4���ٿ���
	ROC_MEDIA_SPEED_BF8X,			// 8���ٿ���
	ROC_MEDIA_SPEED_BF16X,			// 16���ٿ���
	ROC_MEDIA_SPEED_BF32X,			// 32���ٿ���
	ROC_MEDIA_SPEED_BS2X,			// 1/2��������	
	ROC_MEDIA_SPEED_BS4X,			// 1/4��������
	ROC_MEDIA_SPEED_BS8X,			// 1/8��������
	ROC_MEDIA_SPEED_BS16X,			// 1/16��������
	ROC_MEDIA_SPEED_BS32X,			// 1/32��������
} Roc_Media_Speed_t;


typedef enum {
	ROC_MEDIA_CODEC_UNKNOWN 	= 0,
/* ����Ƶ��������֧�� */
	ROC_MEDIA_CODEC_V_MPEG	= (1<<0),
	ROC_MEDIA_CODEC_V_H264	= (1<<1),
	ROC_MEDIA_CODEC_V_MPEG4	= (1<<2),
	ROC_MEDIA_CODEC_V_VC1	= (1<<3),
	ROC_MEDIA_CODEC_V_FLV1	= (1<<4),
	ROC_MEDIA_CODEC_V_VP6	= (1<<5),
	ROC_MEDIA_CODEC_V_VP6F	= (1<<6),
	ROC_MEDIA_CODEC_V_RAW	= (1<<7),
	ROC_MEDIA_CODEC_V_AVS	= (1<<8),

/* ����Ƶ��������֧�� */
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
 * ƽ̨������ͨ���˺����ӿڻ�ȡ�û�����µ�����ѭ����������дָ��
 * ����
 *		@handle			�û������������ݶ���
 *		@address_p		��������ѭ����������дָ��
 * ����ֵ
 *		0				�ɹ�
 *		< 0				ʧ��
 ************************************************************************************/
typedef UINT32_T (*Roc_Media_GetWriteAddress_t)(void * const handle, void** const address_p);

/************************************************************************************
 * ƽ̨������ͨ���˺����ӿ�֪ͨ�û�������ѭ���������Ķ�ָ��
 * ����
 *		@handle			�û������������ݶ���
 *		@address_p		��������ѭ���������Ķ�ָ��
 *		0				�ɹ�
 *		< 0				ʧ��
 ************************************************************************************/
typedef UINT32_T (*Roc_Media_InformReadAddress_t)(void * const handle, void* const address);

/************************************************************************************
 * ƽ̨������ͨ���˺����ӿ�֪ͨ�û������һ֡�µ���Ƶ����Ƶ֡
 * ����
 *		@handle			�û������������ݶ���
 *		@timestamp		�µ���Ƶ����Ƶʱ���
 *		0				�ɹ�
 *		< 0				ʧ��
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
 * ��ʼ��ƽ̨ý�������ģ��
 * 
 * ����:	
 *		��
 *		
 * ˵��:
 *		��
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_init(void);

/************************************************************************************
 * ����ƽ̨ý�������ģ��
 * 
 * ����:	
 *		��
 *		
 * ˵��:
 *		��
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_term(void);


INT32_T rocme_porting_media2_codec(UINT32_T *CodecMask);
/************************************************************************************
 * ��ƽ̨��һ��Ӳ��ý�������
 * 
 * ����:	
 *		@MediaHandle: ����ƽ̨���������, ��ƽ̨�������Ĳ������ڴ˾��
 *		@OpenParams
 *           .StreamSource: ROC_MEDIA_STREAM_SOURCE_DVB		- ֱ��������
 *                          ROC_MEDIA_STREAM_SOURCE_FILE	- �ļ�����
 *           .StreamType: ROC_MEDIA_STREAM_VIDEO	-��ȡ��Ƶ������
 *                        ROC_MEDIA_STREAM_AUDIO	-��ȡ��Ƶ������,
 *                        ROC_MEDIA_STREAM_TS	    -��ȡTS��������
 *                         
 *           .CodecType:  ���������ı����ʽ, �μ�Roc_Media_Stream_t����
 *           
 *           .BufferHandler: ��������������λ������������Ķ���
 *
 *           .GetWriteAddress_p: ƽ̨������ͨ���˺����ӿڻ�ȡλ�������дָ��
 *
 *           .InformReadAddress_p: ƽ̨������ͨ���˺����ӿ�֪ͨӦ�ø���λ������Ķ�ָ��
 *             
 *      @BitBufferAddr: �����Ϊ��, ����λ������Ļ���ַ
 *
 *      @BitBufferSize: �����Ϊ��, ����λ������Ĵ�С
 *		
 * ˵��:
 *		
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_open(UINT32_T *MediaHandle,
								  Roc_Media_OpenParams_t *OpenParams,
								  void **BitBufferBase,
								  UINT32_T *BitBufferSize);

/************************************************************************************
 * �ر�ƽ̨������
 * 
 * ����:	
 *		@MediaHandle	ƽ̨������������
 *		
 * ˵��:
 *
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_close(UINT32_T MediaHandle);

/************************************************************************************
 * ����ƽ̨�Ľ�������ʼ����
 * 
 * ����:	
 *		@MediaHandle			ƽ̨������������
 *		
 * ˵��:
 *		���ô˽ӿڿ�ʼƽ̨�������Ľ���
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
 ************************************************************************************/
INT32_T rocme_porting_media2_start(UINT32_T MediaHandle);

/************************************************************************************
 * ֹͣƽ̨�������Ľ���
 * 
 * ����:	
 *		@MediaHandle: ���������
 *		
 * ˵��:
 *		None
 *
 * @return: 
 *		==0: ���óɹ�
 *		<0:  ����ʧ��
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
