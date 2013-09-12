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

/*��Ƶ���ͨ��*/
typedef enum Roc_Audio_Device
{
    ROC_AUDIO_DEVICE_UNKNOW,/*δ֪����豸*/
    ROC_AUDIO_DEVICE_HDMI,/*HDMI ����豸*/
    ROC_AUDIO_DEVICE_SPDIF,/*SPDIF ����豸*/
}Roc_Audio_Device_e;


/*��Ƶ����*/
typedef enum Roc_Audio_Type
{
    ROC_AUDIO_TYPE_AC3      = 0x00,  /*AC3��Ƶ�����ʽ  */
    ROC_AUDIO_TYPE_MPEG1    = 0x01,  /*MPEG1��Ƶ�����ʽ*/
    ROC_AUDIO_TYPE_MPEG2    = 0x02,  /*MPEG2��Ƶ�����ʽ*/
    ROC_AUDIO_TYPE_PCM      = 0x03,  /*PCM��Ƶ�����ʽ  */
    ROC_AUDIO_TYPE_MP3      = 0x04,  /*MP3��Ƶ�����ʽ  */
    ROC_AUDIO_TYPE_MLP      = 0x05,  /*MLP��Ƶ�����ʽ  */
    ROC_AUDIO_TYPE_MPEG_AAC = 0x06,  /*AAC��Ƶ�����ʽ  */
    ROC_AUDIO_TYPE_UNKNOWN  = 0xFF   /*δ֪��Ƶ�����ʽ */
}Roc_Audio_Type_e;


/*����ģʽ*/
typedef enum Roc_Audio_Mode
{
    ROC_AUDIO_MODE_MONO     = 0x00,  /*������*/
    ROC_AUDIO_MODE_STEREO   = 0x01,  /*������*/
    ROC_AUDIO_MODE_LEFT     = 0x02,  /*������*/
    ROC_AUDIO_MODE_RIGHT    = 0x03,  /*������*/
    ROC_AUDIO_MODE_UNKNOWN  = 0xFF   /*δ֪��������*/
}Roc_Audio_Mode_e;

/*��Ƶ����*/
typedef enum Roc_Video_Type
{
    ROC_VIDEO_TYPE_MPEG     = 0x00,  /*MPGE ��Ƶ�����ʽ*/
    ROC_VIDEO_TYPE_MPEG2    = 0x01,  /*MPGE2��Ƶ�����ʽ*/
    ROC_VIDEO_TYPE_MPEG4    = 0x02,  /*MPGE4��Ƶ�����ʽ*/
    ROC_VIDEO_TYPE_H264     = 0x03,  /*H.264��Ƶ�����ʽ*/
    ROC_VIDEO_TYPE_VC1      = 0x04,  /*VC1��Ƶ�����ʽ  */
    ROC_VIDEO_TYPE_AVS      = 0x05,  /*AVS��Ƶ�����ʽ  */
    ROC_VIDEO_TYPE_UNKNOWN  = 0xFF   /*δ֪��Ƶ�����ʽ */
}Roc_Video_Type_e;

/*��Ƶ��ʽ*/
typedef enum Roc_Vid_DENC_Mode
{
    ROC_DENC_MODE_NONE      = 0x00,  /*δ�������Ƶ��ʽ          */
    ROC_DENC_MODE_NTSCM     = 0x01,  /*����ƽ�������ʽ          */
    ROC_DENC_MODE_PALN      = 0x02,  /*���е�������ƽ�������ʽ  */
    ROC_DENC_MODE_SECAM     = 0x03   /*˳���Ͳ�ɫ��洢������ʽ*/
}Roc_Vid_DENC_Mode_e;

/*��Ƶ�������*/
typedef enum Roc_Vid_Aspect_Ratio
{
    ROC_ASPECT_RATIO_NONE   = 0x00,  /*δ�������Ƶ�������*/
    ROC_ASPECT_RATIO_16TO9  = 0x01,  /*16:9�������        */
    ROC_ASPECT_RATIO_4TO3   = 0x02,  /*4:3�������         */
    ROC_ASPECT_RATIO_SQUARE = 0x03   /*1:1�������         */
}Roc_Vid_Aspect_Ratio_e;

/*��ʾ�ֲ㶨��*/
typedef enum Roc_OutPut_Layer
{   
    ROC_LAYER_CURSOR     = 0x00,  /*����,Ŀǰδʹ��*/
    ROC_LAYER_OSD        = 0x01,  /*Ĭ�������ϲ�,GUIʹ�ô˲�*/
    ROC_LAYER_VIDEO      = 0x02,  /*Ĭ���ǵڶ���,VIDEOʹ�ô˲�*/
    ROC_LAYER_STILL      = 0x03,  /*Ĭ���ǵ�����,��̬��֡I֡ʹ�ô˲�*/
    ROC_LAYER_BACKGROUND = 0x04,  /*Ĭ���ǵ��Ĳ�,ͨ��Ϊ��ɫ��*/
    ROC_NUM_LAYERS       = 0x05,
    ROC_STILL_NOT_DISPLAY        /*�������뵽��̬��Ļ������������������ʾ*/
}Roc_OutPut_Layer_e;

/*��Ƶ�������ǿ��ת������ϸ˵����������Ѷ�м����ֲ�ĵ�*/
typedef enum Roc_Vid_AspectRatioConversion
{
    ROC_DISPLAY_AR_CONVERSION_NONE          = 0x00,  /*δ�������Ƶ�������ת��*/
    ROC_DISPLAY_AR_CONVERSION_PAN_SCAN      = 0x01,  /*PAN&SCAN �ͻ����ת�������ü�ԭʼ���棬����������Ļ������޺ڱ�*/
    ROC_DISPLAY_AR_CONVERSION_LETTER_BOX    = 0x02,  /*LETTER BOX �ͻ����ת����������ȫ��ԭʼ���棬��Ļδʹ�ò����úڱ������*/
    ROC_DISPLAY_AR_CONVERSION_COMBINED      = 0x03,  /*PAN&SCAN��LETTER BOX ��ϱ���ת��*/
    ROC_DISPLAY_AR_CONVERSION_IGNORE        = 0x04   /*����ת����ֱ�Ӱ���ԭʼ�����������*/
}Roc_Vid_AspectRatioConversion_e;

/*��Ƶ����*/
typedef struct Roc_Vid_BCSLevel
{
    UINT8_T         brightness;  /*��Ƶ������  ����Χ 0 ~ 100   */
    UINT8_T         contrast;    /*��Ƶ��Աȶȣ���Χ 0 ~ 100   */
    UINT8_T         saturation;  /*��Ƶ�㱥�Ͷȣ���Χ 0 ~ 100   */
}Roc_Vid_BCSLevel_t;

/*��Ŀ��������*/
typedef struct Roc_AV_Para
{
    UINT16_T            aud_pid;   /*��Ŀ��Ƶpid */
    UINT16_T            vid_pid;   /*��Ŀ��Ƶpid */
    UINT16_T            pcr_pid;   /*��ĿPCR pid */
    Roc_Audio_Type_e    aud_type;  /*��Ŀ��Ƶ����*/
    Roc_Video_Type_e    vid_type;  /*��Ŀ��Ƶ����*/
}Roc_AV_Para_t;

/*PID��������*/
typedef enum Roc_PID_Type
{
    ROC_AUDIO_PID       = 0x00,  /*���������PIDΪ��ƵPID*/
    ROC_VIDEO_PID       = 0x01,  /*���������PIDΪ��ƵPID*/
    ROC_PCR_PID         = 0x02,  /*���������PIDΪPCR PID*/
    ROC_SUBTITLE_PID    = 0x03,  /*���������PIDΪ��ĻPID*/
    ROC_RESERVE_PID     = 0xFF   /*����λ*/
}Roc_PID_Type_e;

/*��Ƶ�����¼�*/
typedef enum Roc_AV_Event
{
    ROC_VID_START_EVT           = 0x00, /*������Ƶ���뿪ʼ�¼�*/
    ROC_VID_STOPPED_EVT         = 0x01, /*��Ƶ������ֹͣ�����¼�*/
    ROC_VID_NEW_FRAME_EVT       = 0x02, /*��Ƶ������FRAME���¼�*/
    ROC_VID_DECODING_ERROR_EVT  = 0x03, /*��Ƶ��������������¼�*/
    ROC_VID_DATA_ERROR_EVT      = 0x04, /*��Ƶ�����������¼�-overflow��underflow��data-stream error etc.*/

    ROC_AUD_START_EVT           = 0x10, /*������Ƶ���뿪ʼ�¼�*/
    ROC_AUD_STOPPED_EVT         = 0x11, /*��Ƶ������ֹͣ�����¼�*/
    ROC_AUD_NEW_FRAME_EVT       = 0x12, /*��Ƶ������FRAME���¼�*/
    /*ROC_AUD_DECODING_ERROR_EVT  = 0x13, ��Ƶ��������������¼�*/
    ROC_AUD_DATA_ERROR_EVT      = 0x14  /*��Ƶ�����������¼�-overflow��underflow��data-stream error etc.*/
    
}Roc_AV_Event_e;

/*��Ƶ����ֱ���*/
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


/*��Ƶ�����¼��ص���������*/
typedef INT32_T (*rocme_porting_av_event_callback) ( INT32_T channel_index, void *param, Roc_AV_Event_e av_event,UINT32_T handler);

/*��Ƶ�����¼�ע������ṹ����*/
typedef struct Roc_AV_Evt_Param
{
    INT32_T                         channel_index;  /*����������������ͨ������*/
    Roc_AV_Event_e                  av_event;       /*��Ƶ�����¼�*/
    rocme_porting_av_event_callback callback;       /*�¼��ص�����*/
    void                            *cb_param;      /*�ص�������˽�в���*/
}Roc_AV_Evt_Param_t;

/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/


/**************************************************************************
��������: 
            rocme_porting_av_init
����˵��: 
            ����Ƶ�����ʼ�����м����������ʱ���ô˺��������������м��֮ǰ
        �������Ѿ�����������Ƶ�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            void
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʼ���ɹ� )
    ʧ�� : -1 �� ������ ( ��ʼ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_init(void);

/**************************************************************************
��������: 
            rocme_porting_av_play
����˵��: 
            ���ݴ��������Ƶ��������ָ��������ͨ���ϲ���ָ���Ľ�Ŀ�����޷���
        ��ʵ������Ƶ�ķ�����ƣ������º���ʱ
        rocme_porting_av_pid_set();
        rocme_porting_audio_play();
        rocme_porting_video_play();
        �˺������ܱ���ʵ�֡�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ avpara        ] : ����Ƶ���Ų����ṹ��,��������:
                                aud_pid   -  ��Ŀ��Ƶpid 
                                vid_pid   -  ��Ŀ��Ƶpid 
                                pcr_pid   -  ��ĿPCR pid 
                                aud_type  -  ��Ŀ��Ƶ���� 
                                vid_type  -  ��Ŀ��Ƶ���� 
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��Ŀ�ɹ����� )
    ʧ�� : -1 �� ������ ( ��Ŀ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_play(const INT32_T channel_index,const Roc_AV_Para_t av_para);

/**************************************************************************
��������: 
            rocme_porting_av_stop
����˵��: 
            ָֹͣ������ͨ���ϵ���Ƶ���ţ����޷�����ʵ������Ƶ�ķ�����ƣ���
        ���º���ʱ
        rocme_porting_av_pid_clean();
        rocme_porting_audio_stop();
        rocme_porting_video_stop();
        �˺������ܱ���ʵ�֡�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ is_last_pic   ] : �Ƿ���ֹͣ��Ƶǰ�����һ֡����:
                                ROC_TRUE   -  �������һ֡����
                                ROC_FALSE  -  ���������һ֡���棬������ʾ����
                            ��I ֡
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��Ŀ�ɹ�ֹͣ )
    ʧ�� : -1 �� ������ ( ��Ŀֹͣʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_stop(const INT32_T channel_index,const ROC_BOOL is_last_pic);

/**************************************************************************
��������: 
            rocme_porting_av_pid_set
����˵��: 
            ����ָ������ͨ���ϵ�ָ������Դ(��Ƶ����Ƶ��PCR����Ļ��)��PID
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ type          ] : PID�������ͽṹ�壬��������:
                                ROC_AUDIO_PID     -  ���������PIDΪ��ƵPID 
                                ROC_VIDEO_PID     -  ���������PIDΪ��ƵPID
                                ROC_PCR_PID       -  ���������PIDΪPCR PID
                                ROC_SUBTITLE_PID  -  ���������PIDΪ��ĻPID
            [ pid           ] : �����PID��ֵ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �ɹ�������ָ������Դ��PID )
    ʧ�� : -1 �� ������ ( ����PID���� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_pid_set(const INT32_T channel_index,const Roc_PID_Type_e type,const UINT16_T pid);

/**************************************************************************
��������: 
            rocme_porting_av_pid_clean
����˵��: 
            ���ָ������ͨ���ϵ�ָ������Դ(��Ƶ����Ƶ��PCR����Ļ��)����PID
        ��ռ�ã����������slot�Ĺ�������ֵ��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ type          ] : PID�������ͽṹ�壬��������:
                                ROC_AUDIO_PID     -  ���������PIDΪ��ƵPID 
                                ROC_VIDEO_PID     -  ���������PIDΪ��ƵPID
                                ROC_PCR_PID       -  ���������PIDΪPCR PID
                                ROC_SUBTITLE_PID  -  ���������PIDΪ��ĻPID
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���PID�ɹ� )
    ʧ�� : -1 �� ������ ( ���PIDʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_pid_clean(const INT32_T channel_index,const Roc_PID_Type_e type);

/**************************************************************************
��������: 
            rocme_porting_audio_play
����˵��: 
            ʹ��ָ��������ͨ���ϵ���Ƶ��������ʼ������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ type          ] : ��Ƶ���ݵı������ͣ���������:
                                ROC_AUDIO_TYPE_AC3       -  AC3��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MPEG1     -  MPEG1��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MPEG2     -  MPEG2��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_PCM       -  PCM��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MP3       -  MP3��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MLP       -  MLP��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_MPEG_AAC  -  AAC��Ƶ�����ʽ
                                ROC_AUDIO_TYPE_UNKNOWN   -  δ֪��Ƶ�����ʽ 
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ�������ɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_play(const INT32_T channel_index,const Roc_Audio_Type_e type);

/**************************************************************************
��������: 
            rocme_porting_audio_stop
����˵��: 
            ָֹͣ��������ͨ���ϵ���Ƶ������������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣ��Ƶ�������ɹ� )
    ʧ�� : -1 �� ������ ( ֹͣ��Ƶ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_stop(const INT32_T channel_index);

/**************************************************************************
��������: 
            rocme_porting_audio_set_volume
����˵��: 
            ����ָ������ͨ���ϵĽ�Ŀ�������������ȡֵ��Χ 0 ~ 100��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ volume        ] : ����ֵ��ȡֵ��Χ 0 ~ 100
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����趨�ɹ� )
    ʧ�� : -1 �� ������ ( �����趨ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_set_volume(const INT32_T channel_index,const UINT32_T volume);

/**************************************************************************
��������: 
            rocme_porting_audio_set_mute
����˵��: 
            ����ָ������ͨ���ϵĽ�Ŀ����Ƿ��Ǿ�����
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ is_mute       ] : �Ƿ�����ʶ:
                                ROC_TRUE   -  ����
                                ROC_FALSE  -  �Ǿ��� 
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �Ƿ������óɹ� )
    ʧ�� : -1 �� ������ ( �Ƿ�������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_set_mute(const INT32_T channel_index,const ROC_BOOL is_mute);

/**************************************************************************
��������: 
            rocme_porting_audio_set_mode
����˵��: 
            ����ָ������ͨ���ϵĽ�Ŀ�������ģʽ��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ aud_mode      ] : ����ģʽ����������:
                                ROC_AUDIO_MODE_MONO    -  ������
                                ROC_AUDIO_MODE_STEREO  -  ������
                                ROC_AUDIO_MODE_LEFT    -  ������
                                ROC_AUDIO_MODE_RIGHT   -  ������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��������ģʽ�ɹ� )
    ʧ�� : -1 �� ������ ( ��������ģʽʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_set_mode(const INT32_T channel_index,const Roc_Audio_Mode_e aud_mode);

/**************************************************************************
��������: 
            rocme_porting_audio_set_output_mode
����˵��: 
            ����ָ����Ƶ����豸�����Ƶ�����ͣ�Ĭ��Ϊpcm�����
����˵����
    ���������
            [ aud_device ] : ��Ƶ����豸���μ����Ͳμ�Roc_Audio_Device_e
            [ aud_type    ] : ��Ƶ������ͣ��������Ͳμ�Roc_Audio_Type_e
��    �أ� 
    �ɹ� : 0            ( ���óɹ� )
    ʧ�� : -1 �� ������ ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_audio_set_output_mode(Roc_Audio_Device_e aud_device,const Roc_Audio_Type_e aud_type);

/**************************************************************************
��������: 
            rocme_porting_video_play
����˵��: 
            ʹ��ָ��������ͨ���ϵ���Ƶ��������ʼ������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ type          ] : ��Ƶ���ݵı������ͣ���������:
                                ROC_VIDEO_TYPE_MPEG     -  MPGE ��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_MPEG2    -  MPGE2��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_MPEG4    -  MPGE4��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_H264     -  H.264��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_VC1      -  VC1��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_AVS      -  AVS��Ƶ�����ʽ
                                ROC_VIDEO_TYPE_UNKNOWN  -  δ֪��Ƶ�����ʽ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ�������ɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_play(const INT32_T channel_index,const Roc_Video_Type_e type);

/**************************************************************************
��������: 
            rocme_porting_video_stop
����˵��: 
            ָֹͣ��������ͨ���ϵ���Ƶ������������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ is_last_pic   ] : �Ƿ���ֹͣ��Ƶǰ�����һ֡����:
                                ROC_TRUE   -  �������һ֡����
                                ROC_FALSE  -  ���������һ֡���棬������ʾ����
                            ��I ֡
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣ��Ƶ�������ɹ� )
    ʧ�� : -1 �� ������ ( ֹͣ��Ƶ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_stop(const INT32_T channel_index, const ROC_BOOL is_last_pic);

/**************************************************************************
��������: 
            rocme_porting_video_set_display
����˵��: 
            �����Ƿ���ָ������ͨ���ϵ���Ƶ�㡣
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ enable        ] : �Ƿ�����Ƶ���ʶ:
                                ROC_TRUE   -  ����ָ������Ƶ��
                                ROC_FALSE  -  �ر�ָ������Ƶ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����Ƿ�����Ƶ��ɹ� )
    ʧ�� : -1 �� ������ ( �����Ƿ�����Ƶ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_display(const INT32_T channel_index,const ROC_BOOL enable);

/**************************************************************************
��������: 
            rocme_porting_video_set_window
����˵��: 
            ����ָ��������ͨ���ϵ���Ƶ������ڵ�����ʹ�С��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ height        ] : ��Ƶ���ڵĸ�
            [ width         ] : ��Ƶ���ڵĿ�
            [ x_start       ] : ��Ƶ���ڵĺ���ʼ����
            [ y_start       ] : ��Ƶ���ڵ�����ʼ����
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ����λ�óɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ����λ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_window(const INT32_T channel_index,const UINT32_T height,const UINT32_T width,const UINT32_T x_start,const UINT32_T y_start);

/**************************************************************************
��������: 
            rocme_porting_video_set_denc
����˵��: 
            ����ָ������ͨ���ϵ���Ƶ�����ʽ��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ denc_mode     ] : ��Ƶ��ʽ����������:
                                ROC_DENC_MODE_NONE   -  δ�������Ƶ��ʽ
                                ROC_DENC_MODE_NTSCM  -  ����ƽ�������ʽ
                                ROC_DENC_MODE_PALN   -  ���е�������ƽ�������ʽ
                                ROC_DENC_MODE_SECAM  -  ˳���Ͳ�ɫ��洢������ʽ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ��ʽ�ɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ��ʽʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_denc(const INT32_T channel_index,const Roc_Vid_DENC_Mode_e denc_mode);

/**************************************************************************
��������: 
            rocme_porting_video_set_aspect
����˵��: 
            ����ָ������ͨ���ϵ���Ƶ�������Ŀ�߱ȡ�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ aspect_ratio  ] : ��Ƶ�������Ŀ�߱ȣ���������:
                                ROC_ASPECT_RATIO_NONE    -  δ�������Ƶ�������
                                ROC_ASPECT_RATIO_16TO9   -  16:9�������
                                ROC_ASPECT_RATIO_4TO3    -  4:3�������
                                ROC_ASPECT_RATIO_SQUARE  -  1:1�������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���û�������ɹ� )
    ʧ�� : -1 �� ������ ( ���û������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_aspect(const INT32_T channel_index,const Roc_Plane_Aspect_Ratio_e aspect_ratio);

/**************************************************************************
��������: 
            rocme_porting_video_set_aspect_conversion
����˵��: 
            ����ָ������ͨ���ϵĻ���ǿ��ת��������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ ar_conversion ] : ����ǿ��ת���������ͣ���������:
                                ROC_DISPLAY_AR_CONVERSION_NONE        
                            -  δ�������Ƶ�������ת��
                                ROC_DISPLAY_AR_CONVERSION_PAN_SCAN    
                            -  PAN&SCAN �ͻ����ת�������ü�ԭʼ���棬������
                            ����Ļ������޺ڱ�
                                ROC_DISPLAY_AR_CONVERSION_LETTER_BOX  
                            -  LETTER BOX �ͻ����ת����������ȫ��ԭʼ���棬
                            ��Ļδʹ�ò����úڱ������
                                ROC_DISPLAY_AR_CONVERSION_COMBINED    
                            -  PAN&SCAN��LETTER BOX ��ϱ���ת��
                                ROC_DISPLAY_AR_CONVERSION_IGNORE      
                            -  ����ת����ֱ�Ӱ���ԭʼ�����������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���û������ǿ��ת���ɹ� )
    ʧ�� : -1 �� ������ ( ���û������ǿ��ת��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_aspect_conversion(const INT32_T channel_index,const Roc_Vid_AspectRatioConversion_e ar_conversion);

/**************************************************************************
��������: 
            rocme_porting_video_set_bcs
����˵��: 
            ����ָ������ͨ���ϵ���Ƶ���ֲ���(���ȡ��ԱȶȺͱ��Ͷ�)��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ bcs_level     ] : ��Ƶ���ֲ�������������:
                                 brightness  -  ��Ƶ������  ����Χ 0 ~ 100
                                 contrast    -  ��Ƶ��Աȶȣ���Χ 0 ~ 100
                                 saturation  -  ��Ƶ�㱥�Ͷȣ���Χ 0 ~ 100
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ���ֲ����ɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ���ֲ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_bcs(const INT32_T channel_index,const Roc_Vid_BCSLevel_t bcs_level);

/**************************************************************************
��������: 
            rocme_porting_video_set_vtg
����˵��: 
            ����ָ������ͨ���ϵ���Ƶ����ֱ��ʡ�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ vtg_mode     ] : ��Ƶ����ֱ���
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ����ֱ��ʳɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ����ֱ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_video_set_vtg(const INT32_T channel_index,const ROC_VTG_TimingMode_e vtg_mode);


/*************************************************************************
��������: 
            rocme_porting_video_set_fullscreen
����˵��: 
            ������ƵΪȫ����
����˵����
    ���������
	     ��
���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���óɹ� )
    ʧ�� : -1 �� ������ ( ����ʧ�� )
�޸ļ�¼��
***************************************************************************/
INT32_T rocme_porting_video_set_fullscreen(void);


/**************************************************************************
��������: 
            rocme_porting_iframe_set_display
����˵��: 
            �����Ƿ�����̬�����ʾ
����˵����
    ���������
            [ enable        ] : �Ƿ�����̬���ʶ:
                                ROC_TRUE   -  ������̬�㣬���Կ�����̬��I֡ͼƬ����ʾ
                                ROC_FALSE  -  �رվ�̬�㣬�����Կ�����̬��I֡ͼƬ����ʾ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����Ƿ�����̬��ɹ� )
    ʧ�� : -1 �� ������ ( �����Ƿ�����̬��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_iframe_set_display(ROC_BOOL enable);

/**************************************************************************
��������: 
            rocme_porting_dec_iframe_still
����˵��: 
            ʹ��ָ������ͨ������ָ����һ��I֡������������ʾ��ָ���Ĳ��ϡ�
            ��ָ��layer = ROC_LAYER_VIDEO������������ϵ�I֡�����ʾ��
            ��Ƶ����(����Ƶ��رգ������Զ���)
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ *data_ptr     ] : I֡���ݵ�ͷָ��
            [ data_len      ] : I֡���ݵĳ���
            [ layer         ] : ��ʾ�Ĳ������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����I֡�ɹ� )
    ʧ�� : -1 �� ������ ( ����I֡ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_dec_iframe_still(const INT32_T channel_index,const UINT8_T *data_ptr,const UINT32_T data_len,const Roc_OutPut_Layer_e layer);

/**************************************************************************
��������: 
            rocme_porting_get_iframe_buff
����˵��: 
            ��ȡ�ײ����I֡ʱ��ʹ�õ��ڴ�buff��ͷָ��ͳ���
����˵����
    ���������
            ��
    ���������
            [ **buff_ptr ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
            [ *buff_len     ] : I֡���ݵ�ͷָ��
��    �أ� 
    �ɹ� : 0            ( ����I֡�ɹ� )
    ʧ�� : -1 �� ������ ( ����I֡ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_iframe_buff( void **buff_ptr , UINT32_T *buff_len );


/**************************************************************************
��������: 
            rocme_porting_dec_black_iframe
����˵��: 
            ��ĳ��������Ϊ��ɫ
����˵����
    ���������
            [ layer         ] : ��ʾ�Ĳ������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���ɹ� )
    ʧ�� : -1 �� ������ ( ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_dec_black_iframe(const Roc_OutPut_Layer_e layer);

/**************************************************************************
��������: 
            rocme_porting_des_init
����˵��: 
            ��ʼ����������
����˵����
    ���������
            ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��������ʼ���ɹ� )
    ʧ�� : -1 �� ������ ( ��������ʼ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_init(void);

/**************************************************************************
��������: 
            rocme_porting_des_term
����˵��: 
            �رս�����
����˵����
    ���������
            ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �������رճɹ� )
    ʧ�� : -1 �� ������ ( �������ر�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_term(void);

/**************************************************************************
��������: 
            rocme_porting_des_audio_start
����˵��: 
            ʹ��ָ������ͨ���ϵ���Ƶ���ſ�ʼ������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ���ųɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_audio_start(const INT32_T channel_index);

/**************************************************************************
��������: 
            rocme_porting_des_audio_stop
����˵��: 
            ָֹͣ������ͨ���ϵ���Ƶ���š�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣ��Ƶ���ųɹ� )
    ʧ�� : -1 �� ������ ( ֹͣ��Ƶ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_audio_stop(const INT32_T channel_index);

/**************************************************************************
��������: 
            rocme_porting_des_video_start
����˵��: 
            ʹ��ָ������ͨ���ϵ���Ƶ���ſ�ʼ������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ������Ƶ���ųɹ� )
    ʧ�� : -1 �� ������ ( ������Ƶ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_video_start(const INT32_T channel_index);

/**************************************************************************
��������: 
            rocme_porting_des_video_stop
����˵��: 
            ָֹͣ������ͨ���ϵ���Ƶ���š�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���Ľ�����ID)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣ��Ƶ���ųɹ� )
    ʧ�� : -1 �� ������ ( ֹͣ��Ƶ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_des_video_stop(const INT32_T channel_index);

/***************************************************************************
����˵����
    ������Ƶ������������

����˵����
    channel_index:ͨ����ʶ��,�����ڶ�ͨ��ƽ̨
    pbyEvenKey:ż��Կ,����Ϊ8�ֽ�
    pbyOddKey: ����Կ,����Ϊ8�ֽ�

��    �أ� 
    0    ----�ɹ�
    -1   ----ʧ��
***************************************************************************/
INT32_T rocme_porting_des_video_setcw(const INT32_T channel_index, UINT8_T *pbyEvenKey, UINT8_T *pbyOddKey);

/***************************************************************************
����˵����
    ������Ƶ������������

����˵����
    channel_index:ͨ����ʶ��,�����ڶ�ͨ��ƽ̨
    pbyEvenKey:ż��Կ,����Ϊ8�ֽ�
    pbyOddKey: ����Կ,����Ϊ8�ֽ�

��    �أ� 
    0    ----�ɹ�
    -1   ----ʧ��
***************************************************************************/
INT32_T rocme_porting_des_audio_setcw(const INT32_T channel_index, UINT8_T *pbyEvenKey, UINT8_T *pbyOddKey);

/**************************************************************************
��������: 
            rocme_porting_av_event_register
����˵��: 
            ע��ײ�����¼���֪ͨ
����˵����
    ���������
            [ av_evt_param ] : ע��������¼��Ĳ���
    ���������
            [ *handler     ] : ���ƴ��¼�ע��ľ��
��    �أ� 
    �ɹ� : 0            ( ע���¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע���¼�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_event_register(const Roc_AV_Evt_Param_t av_evt_param,UINT32_T *handler);

/**************************************************************************
��������: 
            rocme_porting_av_event_unregister
����˵��: 
            ע��һ���ײ�����¼���֪ͨ
����˵����
    ���������
            [ handler     ] : ���ƴ��¼�ע��ľ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ע���¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע���¼�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_av_event_unregister(const UINT32_T handler);

/**************************************************************************
��������: 
	rocme_porting_dec_iframe
����˵��: 
	����mpeg2-I֡ͼƬ���ڴ�
����˵����
���������
	[ pSrcData     ] : I֡����buffer
	[ nSrcDataLen  ] : I֡���ݳ���
	[ pDataBuf	   ] : λͼ����ָ��(�����������)
	[ ColorType    ] : ����������ɺ󷵻ص�λͼ��ɫ��ʽ
���������
	[ pDataBuf	   ] : λͼ����ָ��(�����������)
	[ pWidth	   ] : λͼ���
	[ pHeight	   ] : λͼ�߶�
��    �أ� 
�ɹ� : 0
ʧ�� : -1 �� ������
�޸ļ�¼��
	��������MPEG2-IFrame�ӿ� [4/30/2010 ��˼��]
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
��������: 
	rocme_porting_file_play_start
����˵��: 
	����mpeg��Ƶ��ָ����
����˵����
���������
	[ file_name    ] : ��Ƶ�ļ�·��,����/mnt/adv/rootMedia.mpg
    [ layer        ] : ��ʾ�Ĳ������
�����������
��    �أ� 
�ɹ� : 0
ʧ�� : -1 �� ������
�޸ļ�¼��
	��ʱ���ӽ���MPEG��Ƶ�ӿڣ�Ҫ��ѭ�����Ÿ���Ƶ��ֱ������ rocme_porting_file_play_stop[3/30/2011 BAIGANG]
**************************************************************************/
INT32_T rocme_porting_file_play_start(const CHAR_T *file_name, const Roc_OutPut_Layer_e layer);

/**************************************************************************
��������: 
	rocme_porting_file_play_stop
����˵��: 
	ֹͣ����mpeg��Ƶ��ָ����
����˵����
�����������
�����������
��    �أ� 
�ɹ� : 0
ʧ�� : -1 �� ������
�޸ļ�¼��
	��ʱ���ӽ���MPEG��Ƶ�ӿ� [3/30/2011 BAIGANG]
**************************************************************************/
INT32_T rocme_porting_file_play_stop();

INT32_T rocme_porting_show_bitmap(UINT32_T  bmWidth,UINT32_T  bmHeight,UINT32_T  bmPitch,UINT8_T *bmBits,const Roc_OutPut_Layer_e layer);


#endif
