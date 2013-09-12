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
 * \brief �ṩPVR�������Ϣ
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
/** @{ */  /** <!-- ��PVR�� */

/** ¼��������u32ScdBufSize���Ƽ�ֵ */
#define PVR_STUB_SC_BUF_SZIE (7*4*2048)

/** ¼��������u32DavBufSize���Ƽ�ֵ */
#define PVR_STUB_TSDATA_SIZE (188*12*2048)

/*****************Macro Definition*******************************/
/** �ļ�����󳤶ȣ���λ:�ֽ�*/
#define PVR_MAX_FILENAME_LEN            128
/** ������Կ��󳤶ȣ���λ:�ֽڡ�ע��: ��Կ����Ч���Ȳ�һ������󳤶ȣ������ɼ��ܵ��㷨���� */
#define PVR_MAX_CIPHER_KEY_LEN          128
/** �û�������󳤶ȣ� ��λ:�ֽ� */
#define PVR_MAX_USERDATA_LEN            (1024*1024)


/***********************************************************
                Data Structure Definition
 ***********************************************************/

/***** data structure for common *****/

/** PVR index�ļ���ѭ�����ƽṹ��Ϣ */
typedef struct hiPVR_CYC_HEADER_INFO_S
{
    HI_U32 u32StartFrame;     /**< ��������ʼ֡��index�ļ��е�ƫ��, ��ʼ֡����u32StartFrame��λ��*/
    HI_U32 u32EndFrame;       /**< �����Ľ���֡��index�ļ��е�ƫ��, ����֡����u32EndFrame-1��λ��*/
    HI_U32 u32LastFrame;      /**< index�ļ��н�β֡��ƫ��, ��β֡����u32LastFrame-1��λ��*/
    HI_U32 u32IsRewind;       /**< �ļ��Ƿ����¼��, 0 �ǻ���, 1 ����*/
}PVR_CYC_HEADER_INFO_S;

/** PVR index�ļ����ļ�ͷ��Ϣ�ṹ */
typedef struct hiPVR_IDX_HEADER_INFO_S
{
    HI_U32 u32StartCode;                          /**<  ��ʼ��(0x5A5A5A5A) */
    HI_U32 u32HeaderLen;                          /**< ��u32StartCode��ʼ��UsrData�����ĳ��� */
    PVR_CYC_HEADER_INFO_S stCycInfo;              /**< index��¼�ƻ��ؿ�����Ϣ */
    HI_U64 u64ValidSize;                          /**< �ļ�����Ч���ݴ�С ��λByte */
    HI_U32 u32Reserved;                           /**< �������������� */
    HI_U32 u32UsrDataInfoLen;                     /**< �û���Ϣ���� */
}PVR_IDX_HEADER_INFO_S;

/** PVR index�ļ��б�����������ݽṹ */
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

/** PVR�ӽ������� */
typedef struct hiUNF_PVR_CIPHER_S
{
    HI_BOOL             bDoCipher;                             /**< �Ƿ���м��ܻ��߽��ܣ���������ΪHI_FALSEʱ��������û������ */
    HI_UNF_CIPHER_ALG_E enType;                                /**< ���ܻ��߽�����㷨���� */
    HI_U8               au8Key[PVR_MAX_CIPHER_KEY_LEN];        /**< ��Կ */
    HI_U32              u32KeyLen;                             /**< ��Կ���� */
}HI_UNF_PVR_CIPHER_S;

/** PVR�¼����� */
typedef enum hiUNF_PVR_EVENT_E
{

    HI_UNF_PVR_EVENT_PLAY_EOF        = 0x001,          /**< ���ŵ��ļ�β */
    HI_UNF_PVR_EVENT_PLAY_SOF        = 0x002,          /**< ���˵��ļ�ͷ */
    HI_UNF_PVR_EVENT_PLAY_ERROR      = 0x003,          /**< �����ڲ����� */
    HI_UNF_PVR_EVENT_PLAY_REACH_REC  = 0x004,          /**< ʱ�Ƶ�ʱ�򲥷�׷��¼�� */
    HI_UNF_PVR_EVENT_PLAY_RESV       = 0x00f,          /**< ���� */
    HI_UNF_PVR_EVENT_REC_DISKFULL    = 0x010,          /**< ������ */
    HI_UNF_PVR_EVENT_REC_ERROR       = 0x011,          /**< ¼���ڲ����� */
    HI_UNF_PVR_EVENT_REC_OVER_FIX    = 0x012,          /**< ¼�Ƴ��ȴﵽָ���ĳ���,ֻ�зǻ���¼�Ʋ�������¼� */
    HI_UNF_PVR_EVENT_REC_REACH_PLAY  = 0x013,          /**< ʱ�Ƶ�ʱ��¼��׷�ϲ��� */
    HI_UNF_PVR_EVENT_REC_DISK_SLOW   = 0x014,          /**< ���̴洢�ٶ�����¼���ٶ� */
    HI_UNF_PVR_EVENT_REC_RESV        = 0x01f,          /**< ���� */
    HI_UNF_PVR_EVENT_BUTT            = 0x020           /**< ��Ч���¼����� */
} HI_UNF_PVR_EVENT_E;


/** PVR�¼��ص����� */
typedef void (*eventCallBack)(HI_U32 u32ChnID, HI_UNF_PVR_EVENT_E EventType, HI_S32 s32EventValue, HI_VOID *args);


/** PVR¼�ơ����ŵ��������� */
typedef enum hiUNF_PVR_STREAM_TYPE_E
{
    HI_UNF_PVR_STREAM_TYPE_TS,        /**< TS�� */
    HI_UNF_PVR_STREAM_TYPE_PES,       /**< PES�� */
    HI_UNF_PVR_STREAM_TYPE_ALL_TS,    /**< ȫ����¼�ƣ�¼������Ƶ����������� */
    HI_UNF_PVR_STREAM_TYPE_OTHER,     /**< ��Ч������ */
    HI_UNF_PVR_STREAM_TYPE_BUTT
} HI_UNF_PVR_STREAM_TYPE_E;

/**�������� */
typedef enum hiUNF_PVR_REC_INDEX_TYPE_E
{
    HI_UNF_PVR_REC_INDEX_TYPE_NONE,      /**<����������ȫ����¼�Ƶ�ʱ����ʹ�ô�����  */
    HI_UNF_PVR_REC_INDEX_TYPE_VIDEO,     /**<�����Ƶ���������� */
    HI_UNF_PVR_REC_INDEX_TYPE_AUDIO,     /**<�����Ƶ���������� */
    HI_UNF_PVR_REC_INDEX_TYPE_BUTT       /**<��Ч���������͡�   */
} HI_UNF_PVR_REC_INDEX_TYPE_E;

/** PVR¼�Ƶ������ļ���Ϣ */
typedef struct hiUNF_PVR_FILE_ATTR_S
{
    HI_UNF_PVR_REC_INDEX_TYPE_E enIdxType;          /**< �������� */
    HI_U32                      u32FrameNum;        /**< ����Ƶ�ļ����ļ�֡��;����Ƶ�ļ����ļ��е�PES�� */
    HI_U32                      u32StartTimeInMs;   /**< �ļ����ݵ���ʼʱ�䣬��ʼ֡PTS����λms */
    HI_U32                      u32EndTimeInMs;     /**< �ļ����ݵĽ���ʱ�䣬����֡PTS����λms  */
    HI_U64                      u64ValidSizeInByte; /**< �ļ�����Ч���ݳ��ȣ���λbyte */
} HI_UNF_PVR_FILE_ATTR_S;

/***** data structs for rec *****/
/* record states*/
/**INVALID -> INIT -> RUNNING -> STOPPING ->    STOP ->    INVALID  (saveIndex)  (saveStream)*/

/**¼��ͨ����״̬ */
typedef enum hiUNF_PVR_REC_STATE_E
{
  HI_UNF_PVR_REC_STATE_INVALID,        /**< δ��ʼ����    */
  HI_UNF_PVR_REC_STATE_INIT,           /**< ��ʼ����      */
  HI_UNF_PVR_REC_STATE_RUNNING,        /**< ¼���С�      */
  HI_UNF_PVR_REC_STATE_PAUSE,          /**< ��ͣ��        */
  HI_UNF_PVR_REC_STATE_STOPPING,       /**< ����ֹͣ��    */
  HI_UNF_PVR_REC_STATE_STOP,           /**< �Ѿ�ֹͣ��    */
  HI_UNF_PVR_REC_STATE_BUTT            /**< ��Ч��״ֵ̬��*/
} HI_UNF_PVR_REC_STATE_E;

/** ¼��ͨ���������ݽṹ */
typedef struct hiUNF_PVR_REC_ATTR_S
{
    HI_UNF_PVR_REC_INDEX_TYPE_E enIndexType;                           /**< �������ͣ���̬���ԡ� */
    HI_UNF_VCODEC_TYPE_E        enIndexVidType;                        /**< ��������������������Ƶ����Э��, ����������HI_UNF_PVR_REC_INDEX_TYPE_VIDEOʱ����Ҫ����,��̬����  */
    HI_U32                      u32IndexPid;                           /**< ����PID����̬����*/
    HI_U32                      u32DemuxID;                            /**< ¼��DEMUX�ţ���̬���ԡ�*/
    HI_U32                      u32DavBufSize;                         /**< ��������������С����λΪByte����̬���ԡ�  */
    HI_U32                      u32ScdBufSize;                         /**< �������ݻ�������С����λΪByte����̬���ԡ�*/
    HI_U32                      u32UsrDataInfoSize;                    /**< �û�˽�����ݴ�С����λΪByte����̬���ԡ�  */
    HI_BOOL                     bIsClearStream;                        /**< �Ƿ������¼�Ƴ���������̬���ԡ��������˼�Ǵ��������������������Ǽ������������¼�ƵĽ�Ŀ�Ǽ���������Ҫ��¼��DEMUX������һ·CA����¼������,PVR¼��ģ�鲢������Լ������Ľ��Ų�����*/
    HI_UNF_PVR_STREAM_TYPE_E    enStreamType;                          /**< ��¼�Ƶ��������ͣ���̬���ԡ�*/
    HI_UNF_PVR_CIPHER_S         stEncryptCfg;                          /**< ��������������Ϣ����̬���ԡ�*/
    HI_U64                      u64MaxFileSize;                        /**< ��¼�Ƶ��ļ���С��Ϊ0ʱ��ʾ�����ƣ���̬���ԡ���СֵΪ50M,������̿ռ��㹻�Ļ����Ƽ�����Ϊ512M���ϡ�����Ϊ����ʱ����������Ϊ0�� */
    HI_BOOL                     bRewind;                               /**< �Ƿ���ƣ���̬���ԡ�������ΪHI_TRUE��¼���ļ���С����u64MaxFileSize�󣬻���Ƶ��ļ�ͷ��������¼�ƣ�������ΪHI_FALSE����¼���ļ���С����u64MaxFileSize�󣬻�ֹͣ¼�ơ�*/
    HI_CHAR                     szFileName[PVR_MAX_FILENAME_LEN];      /**< �����ļ�������̬���ԡ�*/
    HI_U32                      u32FileNameLen;                        /**< �����ļ������ȣ���̬���ԡ�ȡֵΪstrlen��szFileName������ */
    HI_U32                      u32Reserved;
}HI_UNF_PVR_REC_ATTR_S;


/**����PVR��������״̬��Ϣ */
typedef struct hiUNF_PVR_BUF_STATUS_S
{
    HI_U32 u32BufSize;       /**< ��������С       */
    HI_U32 u32UsedSize;      /**< ��������ʹ�ô�С */
} HI_UNF_PVR_BUF_STATUS_S;

/** ¼��ͨ��״̬���ݽṹ.
��u32CurTimeInMs��u32StartTimeInMs��u32EndTimeInMs���ߵĹ�ϵ����˵�����£�
1������ӿ�ʼ¼�ƺ�һ��¼����10000���룬���û�з������ƣ���ôu32StartTimeInMs Ϊ0��u32EndTimeInMs Ϊ10000�� u32CurTimeInMsΪ10000��
2������ӿ�ʼ¼�ƺ�һ��¼����10000���룬�����ڵ�8000�����ʱ�����˻��ƣ���ôu32StartTimeInMs Ϊ2000��u32EndTimeInMs Ϊ10000�� u32CurTimeInMsΪ8000��
*/
typedef struct hiUNF_PVR_REC_STATUS_S
{
    HI_UNF_PVR_REC_STATE_E      enState;                 /**< ͨ��������״̬��    */
    HI_U32                      u32Reserved;             /**< �������������롣    */
    HI_U64                      u64CurWritePos;          /**< ��ǰ¼���ļ��Ĵ�С����λ��byte���� */
    HI_U32                      u32CurWriteFrame;        /**< ��ǰ¼�Ƶ�֡����                  */
    HI_U32                      u32CurTimeInMs;          /**< ��ǰ¼�Ƶĺ���������ֵΪ¼���ļ���ʵ����Чʱ����*/
    HI_U32                      u32StartTimeInMs;        /**< ¼���ļ���ʵ����ʼ�㡣¼�ƻ���ǰ��Ϊ��һ֡ʱ�䣻¼�ƻ��ƺ�Ϊ���Ƶ��ʱ�䡣 */
    HI_U32                      u32EndTimeInMs;          /**< ¼���ļ��н���֡��ʱ�䣬û�л���ǰ�����һ֡��ʱ�䡣    */
    HI_UNF_PVR_BUF_STATUS_S     stRecBufStatus;          /**< ¼��ͨ��������״̬��    */
}HI_UNF_PVR_REC_STATUS_S;


/** data structs for play */

/** PVR���ŷ���:��ǰ���� */
#define HI_UNF_PVR_PLAY_DIRECTION_FORWARD             (1)
/** PVR���ŷ���:���󲥷� */
#define HI_UNF_PVR_PLAY_DIRECTION_BACK                (-1)

/** ����λ������ */
typedef enum hiUNF_PVR_PLAY_POS_TYPE_E
{
  HI_UNF_PVR_PLAY_POS_TYPE_SIZE,              /**< �ô�С����λ��byte����ʾλ�ã��ݲ�֧�֣� */
  HI_UNF_PVR_PLAY_POS_TYPE_TIME,              /**< ��ʱ�䣨��λ��ms������ʾλ�� */
  HI_UNF_PVR_PLAY_POS_TYPE_FRAME,             /**< ��֡��������PES������ʾλ��  */
  HI_UNF_PVR_PLAY_POS_TYPE_BUTT               /**< ��Ч��λ������*/
} HI_UNF_PVR_PLAY_POS_TYPE_E;


/** ����ͨ����״̬  */
typedef enum hiUNF_PVR_PALY_STATE_E
{
    HI_UNF_PVR_PLAY_STATE_INVALID,       /**< δ��ʼ��            */
    HI_UNF_PVR_PLAY_STATE_INIT,          /**< ��ʼ��              */
    HI_UNF_PVR_PLAY_STATE_PLAY,          /**< ����������          */
    HI_UNF_PVR_PLAY_STATE_PAUSE,         /**< ��ͣ                */
    HI_UNF_PVR_PLAY_STATE_FF,            /**< ���                */
    HI_UNF_PVR_PLAY_STATE_FB,            /**< ����                */
    HI_UNF_PVR_PLAY_STATE_SF,            /**< ����                */
    HI_UNF_PVR_PLAY_STATE_STEPF,         /**< ��֡����            */
    HI_UNF_PVR_PLAY_STATE_STEPB,         /**< ��֡����            */
    HI_UNF_PVR_PLAY_STATE_STOP,          /**< ֹͣ                */
    HI_UNF_PVR_PLAY_STATE_BUTT           /**< ��Ч��״ֵ̬        */
} HI_UNF_PVR_PLAY_STATE_E;

/** �����ٶȱ�ʶ */
typedef enum hiUNF_PVR_PLAY_SPEED_E
{
    HI_UNF_PVR_PLAY_SPEED_NORMAL            = 1024,                                     /**<    �����ٶȲ��š�    */
    HI_UNF_PVR_PLAY_SPEED_2X_FAST_FORWARD   = 2 * HI_UNF_PVR_PLAY_SPEED_NORMAL,         /**<2���ٿ�š�            */
    HI_UNF_PVR_PLAY_SPEED_4X_FAST_FORWARD   = 4 * HI_UNF_PVR_PLAY_SPEED_NORMAL,         /**<4���ٿ�š�            */
    HI_UNF_PVR_PLAY_SPEED_8X_FAST_FORWARD   = 8 * HI_UNF_PVR_PLAY_SPEED_NORMAL,         /**<8���ٿ�š�            */
    HI_UNF_PVR_PLAY_SPEED_16X_FAST_FORWARD  = 16 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<16���ٿ�š�           */
    HI_UNF_PVR_PLAY_SPEED_32X_FAST_FORWARD  = 32 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<32���ٿ�š�           */
    HI_UNF_PVR_PLAY_SPEED_2X_FAST_BACKWARD  = -2 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<2���ٿ��ˡ�            */
    HI_UNF_PVR_PLAY_SPEED_4X_FAST_BACKWARD  = -4 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<4���ٿ��ˡ�            */
    HI_UNF_PVR_PLAY_SPEED_8X_FAST_BACKWARD  = -8 * HI_UNF_PVR_PLAY_SPEED_NORMAL,        /**<8���ٿ��ˡ�            */
    HI_UNF_PVR_PLAY_SPEED_16X_FAST_BACKWARD = -16 * HI_UNF_PVR_PLAY_SPEED_NORMAL,       /**<16���ٿ��ˡ�           */
    HI_UNF_PVR_PLAY_SPEED_32X_FAST_BACKWARD = -32 * HI_UNF_PVR_PLAY_SPEED_NORMAL,       /**<32���ٿ��ˡ�           */
    HI_UNF_PVR_PLAY_SPEED_2X_SLOW_FORWARD   = HI_UNF_PVR_PLAY_SPEED_NORMAL / 2,         /**<1/2�������š�          */
    HI_UNF_PVR_PLAY_SPEED_4X_SLOW_FORWARD   = HI_UNF_PVR_PLAY_SPEED_NORMAL / 4,         /**<1/4�������š�          */
    HI_UNF_PVR_PLAY_SPEED_8X_SLOW_FORWARD   = HI_UNF_PVR_PLAY_SPEED_NORMAL / 8,         /**<1/8�������š�          */
    HI_UNF_PVR_PLAY_SPEED_16X_SLOW_FORWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / 16,        /**<1/16�������š�         */
    HI_UNF_PVR_PLAY_SPEED_32X_SLOW_FORWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / 32,        /**<1/32�������š�         */
    HI_UNF_PVR_PLAY_SPEED_2X_SLOW_BACKWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-2),      /**<2�������ˣ��ݲ�֧�֡�  */
    HI_UNF_PVR_PLAY_SPEED_4X_SLOW_BACKWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-4),      /**<4�������ˣ��ݲ�֧�֡�  */
    HI_UNF_PVR_PLAY_SPEED_8X_SLOW_BACKWARD  = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-8),      /**<8�������ˣ��ݲ�֧�֡�  */
    HI_UNF_PVR_PLAY_SPEED_16X_SLOW_BACKWARD = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-16),     /**<16�������ˣ��ݲ�֧�֡� */
    HI_UNF_PVR_PLAY_SPEED_32X_SLOW_BACKWARD = HI_UNF_PVR_PLAY_SPEED_NORMAL / (-32),     /**<32�������ˣ��ݲ�֧�֡� */
    HI_UNF_PVR_PLAY_SPEED_BUTT                                                          /**<��Ч���ٶ�ֵ��         */
} HI_UNF_PVR_PLAY_SPEED_E;

/** �ؼ����ŵ�ģʽ  */
typedef struct hiUNF_PVR_PLAY_MODE_S
{
    HI_UNF_PVR_PLAY_SPEED_E               enSpeed;    /**< �ٶȣ���HI_UNF_PVR_PLAY_SPEED_E�Ķ��� */
}HI_UNF_PVR_PLAY_MODE_S;

/** ����ͨ������ */
typedef struct hiUNF_PVR_PLAY_ATTR_S
{

    HI_UNF_PVR_STREAM_TYPE_E    enStreamType;                         /**< �����������ͣ�Ŀǰֻ֧��TS����̬���ԡ�*/
    HI_BOOL                     bIsClearStream;                       /**< �����ŵ������Ƿ���������̬���ԡ���������֧���ؼ����ţ�ֻ֧���������� */
    HI_UNF_PVR_CIPHER_S         stDecryptCfg;                         /**< �������ã���̬���ԡ�                  */
    HI_CHAR                     szFileName[PVR_MAX_FILENAME_LEN];     /**< �������������ļ�������̬���ԡ�        */
    HI_U32                      u32FileNameLen;                       /**< �ļ������ȣ���̬���ԡ�ȡֵΪstrlen��szFileName������ */
}HI_UNF_PVR_PLAY_ATTR_S;


/** ����λ������  */
typedef struct hiUNF_PVR_PLAY_POSITION_S
{
    HI_UNF_PVR_PLAY_POS_TYPE_E  enPositionType;       /**< λ�����͡�           */
    HI_S32                      s32Whence;            /**< ƫ�����ͣ�ȡֵ��ΧΪSEEK_SET/SEEK_CUR/SEEK_END��*/
    HI_S64                      s64Offset;            /**< ƫ�ơ� ƫ������Ϊʱ��ʱ����λ���룻ƫ������Ϊ֡ʱ����λΪһ֡ */
}HI_UNF_PVR_PLAY_POSITION_S;

/** ���������ļ���Ҫ����Ϣ */
typedef struct hiUNF_PVR_GEN_IDX_ATTR_S
{
    HI_U32                      u32UsrDataInfoLen;         /**< �û����ݳ��� */
    HI_U32                      u32IdxPid;                 /**< ����ĸ�Pid�������� */
    HI_UNF_PVR_REC_INDEX_TYPE_E enIdxType;                 /**< �������� */
}HI_UNF_PVR_GEN_IDX_ATTR_S;

/** ����ͨ����״̬ */
typedef struct hiUNF_PVR_PLAY_STATUS_S
{
    HI_UNF_PVR_PLAY_STATE_E     enState;                              /**< ����ͨ��״̬��                                  */
    HI_UNF_PVR_PLAY_SPEED_E     enSpeed;                              /**< ����ͨ���Ĳ����ٶȡ�                            */
    HI_U64                      u64CurPlayPos;                        /**< ��ǰ����֡����ʼ���ļ��е�λ�ã�byte������      */
    HI_U32                      u32CurPlayFrame;                      /**< ��ǰ����֡���ļ��е�λ�ã�֡������PES����       */
    HI_U32                      u32CurPlayTimeInMs;                   /**< ��ǰ����֡��PTS, ��λ���롣                     */
}HI_UNF_PVR_PLAY_STATUS_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_2 */
/** @{ */  /** <!-- ��PVR�� */

/***** APIs for PVR recode *****/

/**
\brief ��ʼ��PVR¼��ģ��
\attention \n
�ظ���ʼ�����سɹ�\n
ÿ������ʹ��PVR¼��ģ��ӿ�ǰ�������ȵ��ô˽ӿڣ����������ӿھ��޷�ʹ��
\param  ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ����ϵͳ����API����ʧ��
\see \n
::HI_UNF_PVR_RecDeInit
*/
HI_S32 HI_UNF_PVR_RecInit(HI_VOID);

/**
\brief ȥ��ʼ��PVR¼��ģ��
\attention \n
�ظ�ȥ��ʼ�����سɹ�\n
ȥ��ʼ��PVR¼��ģ��ǰ��ر�֤������������¼��ͨ�����Ѿ��ͷţ��������¼��ͨ��û���ͷţ��˽ӿڽ��᷵�ش�����HI_ERR_PVR_BUSY

\param ��
\retval ::HI_SUCCESS  �ɹ�
\retval ::HI_FAILURE  ����ϵͳ����API����ʧ��
\retval ::HI_ERR_PVR_BUSY  PVR¼��ģ�黹��ʹ����
\retval ::HI_ERR_PVR_NOT_INIT  PVR¼��ģ��δ��ʼ��
\see \n
::HI_UNF_PVR_RecInit
*/
HI_S32 HI_UNF_PVR_RecDeInit(HI_VOID);


/**
\brief ����1·¼��ͨ��
\attention \n
PVR¼��ģ������pAttr��ָ�����ļ����Զ�����һ����׺��Ϊ".idx"�����ļ�\n
PVR¼��ģ����¼�Ƶ������ļ����зָ��ȷ�������ļ�������4G�Ĵ�С��ÿ���ļ��Ĵ�СԼΪ3.99G����
���ɵ������ļ�����ΪszFileName��szFileName.0001��szFileName.0002��szFileName.0003��szFileName.0004������\n
���pAttr��ָ�����ļ��Ѿ����ڣ���ô����ļ��ᱻ����\n
���PVR¼��ģ�齫Ҫ�����������ļ��Ѿ����ڣ��������ļ�Ҳ�ᱻ����\n
����PVRʹ�õ�������ģ���API�ӿں�������������ƵAPI�ӿں�DEMUX API�ӿڣ�����˷��صĴ������п���������ģ��Ĵ����룬
���������ֵ��ο���Ӧģ�������ֵ���塣���������API���������д������

\param[in] pu32ChnID   ��ȡ����¼��ͨ��ID
\param[in] pstRecAttr  ָ�����ͣ�ָ��ͨ����������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT  PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_NUL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_PVR_FILE_INVALID_FNAME  �ļ��������Ƿ�
\retval ::HI_ERR_PVR_FILE_EXIST  �ļ��Ѿ�����
\retval ::HI_ERR_PVR_NO_CHN_LEFT  �Ѿ�û�п��е�ͨ��������
\retval ::HI_ERR_PVR_FILE_CANT_OPEN  �޷����ļ�
\retval ::HI_ERR_PVR_INDEX_CANT_MKIDX  �޷��������ļ�
\retval ::HI_ERR_PVR_REC_INVALID_DMXID  ¼��ʱ�����˴����DEMUX ID
\see \n
��
*/
HI_S32 HI_UNF_PVR_RecCreateChn(HI_U32 *pu32ChnID, const HI_UNF_PVR_REC_ATTR_S *pstRecAttr);
/**
\brief �ͷ�ָ����¼��ͨ��
\attention \n
������ͷŵ�ͨ��û��ֹͣ�������ش�����::HI_ERR_PVR_BUSY
\param[in] u32ChnID   ��Ҫ�ͷŵ�ͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT  PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID  ͨ���ŷǷ�
\retval ::HI_ERR_PVR_BUSY  ͨ��æ����������е�ǰ����
\see \n
��
*/
HI_S32 HI_UNF_PVR_RecDestroyChn(HI_U32 u32ChnID);


/**
\brief ����¼��ͨ������
\attention \n
ֻ�ж�̬���Բ����ô˽ӿڸı�����
\param[in] u32ChnID    ͨ����
\param[in] pstRecAttr  �����õ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT  PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID  ͨ���ŷǷ�
\see \n
��
*/
HI_S32 HI_UNF_PVR_RecSetChn(HI_U32 u32ChnID, const HI_UNF_PVR_REC_ATTR_S *pstRecAttr);


/**
\brief ��ȡ¼��ͨ������
\attention \n
��
\param[in] u32ChnID   ͨ����
\param[in] pstRecAttr   ָ�����ͣ�ָ���ȡ����ͨ����������
\retval ::HI_SUCCESS  �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT   PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID    ͨ���ŷǷ�
\retval ::HI_ERR_PVR_NUL_PTR        ָ�����Ϊ��
\retval ::HI_ERR_PVR_CHN_NOT_INIT   ָ����ͨ��δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_PVR_RecGetChn(HI_U32 u32ChnID, HI_UNF_PVR_REC_ATTR_S *pstRecAttr);


/**
\brief ����¼��ͨ��
\attention \n
��
\param[in] u32ChnID ͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT   PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID    ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT   ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_ALREADY        ָ����ͨ���Ѿ�����
\retval ::HI_FAILURE                ����ϵͳ����API����ʧ��
\see \n
::HI_UNF_PVR_RecStopChn
*/
HI_S32 HI_UNF_PVR_RecStartChn(HI_U32 u32ChnID);


/**
\brief ֹͣ¼��ͨ��
\attention \n
���1��¼��ͨ�����ڽ���ʱ�Ʋ��Ų���������ֹͣʱ�Ʋ���֮ǰ��������ֹͣ��¼��ͨ�� \n
�����ͨ�����ڽ���ʱ�Ʋ��Ų����������ش�����HI_ERR_PVR_BUSY
\param[in] u32ChnID   ͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT     PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID      ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT     ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_ALREADY          ָ����ͨ���Ѿ�ֹͣ
\retval ::HI_ERR_PVR_BUSY             ͨ��æ����������е�ǰ����
\see \n
::HI_UNF_PVR_RecStartChn
*/
HI_S32 HI_UNF_PVR_RecStopChn(HI_U32 u32ChnID);


/**
\brief ��ȡ¼��ͨ��״̬
\attention \n
��
\param[in] u32ChnID  ͨ����
\param[in] pstRecStatus   ¼��״̬��Ϣָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT    PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID     ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT    ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_NUL_PTR        ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_PVR_RecGetStatus(HI_U32 u32ChnID, HI_UNF_PVR_REC_STATUS_S *pstRecStatus);


/***** APIs for PVR play *****/
/**
\brief ��ʼ��PVR����ģ��
\attention \n
�ظ���ʼ�����سɹ� \n
ÿ������ʹ��PVR����ģ��ӿ�ǰ�������ȵ��ô˽ӿڣ����������ӿھ��޷�ʹ��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE           ����ϵͳ����API����ʧ��
\see \n
::HI_UNF_PVR_PlayDeInit
*/
HI_S32 HI_UNF_PVR_PlayInit(HI_VOID);


/**
\brief ȥ��ʼ��PVR����ģ��
\attention \n
�ظ�ȥ��ʼ�����سɹ� \n
ȥ��ʼ��PVR����ģ��ǰ��ر�֤�����������в���ͨ�����Ѿ��ͷţ�������в���ͨ��û���ͷţ��˽ӿڽ��᷵�ش�����::HI_ERR_PVR_BUSY
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE         ����ϵͳ����API����ʧ��
\retval ::HI_ERR_PVR_BUSY    PVR����ģ�黹��ʹ����
\retval ::HI_ERR_PVR_NOT_INIT    PVR¼��ģ��δ��ʼ��

\see \n
::HI_UNF_PVR_PlayInit
*/
HI_S32 HI_UNF_PVR_PlayDeInit(HI_VOID);


/**
\brief ����1·����ͨ��
\attention \n
PVR����ģ������pAttr��ָ�����ļ����Զ�Ѱ�Һ�׺��Ϊ".idx"�������ļ� \n
��������ļ������ڣ�PVR����ģ��Ҳ�᳢�Բ�������ļ������ǿ����޷�֧��ĳЩ���ԣ�
���������˻���SEEK���������ݰ汾�Ĳ�ͬ��������𣬵�ǰ�汾ֻ֧�ֲ��ţ�\n
���ŵ��ļ�����������¼�Ƶ��ļ���������ʱ�Ʋ��ţ�
hAVPlay�������avplay���봦��stop״̬��
\param[out] pu32ChnID    ��ȡ���Ĳ���ͨ��ID
\param[in] pstPlayAttr   ͨ����������ָ��
\param[in] hAVPlay       avplay�������ʶ���ĸ�avplay������
\param[in] hTsBuffer     ts buffer�������ʶ���ĸ�ts buffer���طţ�һ����˵����ts buffer��Ӧ��ts�˿�Ӧ���ǰ���hAVPlay��Ӧ��demux�ϵ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT         PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_NUL_PTR              ָ�����Ϊ��
\retval ::HI_ERR_DMX_INVALID_PARA          �����Ƿ�
\retval ::HI_ERR_PVR_FILE_INVALID_FNAME     �ļ��������Ƿ�
\retval ::HI_ERR_PVR_FILE_EXIST           �ļ��Ѿ�����
\retval ::HI_ERR_PVR_NO_CHN_LEFT          �Ѿ�û�п��е�ͨ��������
\retval ::HI_ERR_PVR_FILE_CANT_OPEN       �޷����ļ�
\retval ::HI_ERR_PVR_FILE_NOT_EXIST       �ļ������ڣ��޷�����
\retval ::HI_ERR_PVR_NO_MEM               �ڴ治�㣬�޷����䲥����Ҫ��Buffer
\retval ::HI_ERR_PVR_FILE_CANT_READ       �ļ���ȡ����
\see \n
��
*/
HI_S32 HI_UNF_PVR_PlayCreateChn(HI_U32 *pu32ChnID, const HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr, HI_HANDLE hAvplay, HI_HANDLE hTsBuffer);


/**
\brief �ͷ�ָ���Ĳ���ͨ��
\attention \n
������ͷŵ�ͨ��û��ֹͣ�������ش�����::HI_ERR_PVR_BUSY
\param[in] u32ChnID  ��Ҫ�ͷŵ�ͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT        PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID         ͨ���ŷǷ�
\retval ::HI_ERR_PVR_BUSY    ͨ��æ����������е�ǰ����
\see \n
��
*/
HI_S32 HI_UNF_PVR_PlayDestroyChn(HI_U32 u32ChnID);


/**
\brief ����ʱ�Ʋ���ͨ�������ô˽ӿڿ��Ը��������¼��ͨ���ţ�����1·ʱ�Ʋ��š��˽ӿڽ����ݶ�Ӧ¼��ͨ���Ĳ����Զ���ʼ��1������ͨ��������ʼ����
\attention \n
���Ƽ�ʹ�ô˽ӿڣ������˽ӿ�ֻ��Ϊ�˱������Ͻӿڵļ��ݣ��Ƽ�ʹ��HI_UNF_PVR_PlayCreateChn���ٵ���HI_UNF_PVR_PlayStartChn�������ţ����Ҫ����ʱ�ƣ�
ֻ��Ҫ���ò��ŵ��ļ�����¼�Ƶ��ļ���һ�����ɣ�PVR���Զ�ʶ����ͬ���ļ���������ʱ��״̬��
���ô˽ӿڿ���ֱ������1·ʱ�Ʋ��ţ��ӿ��ڲ����Զ�����HI_UNF_PVR_PlayCreateChn���䲥��ͨ�����û�����Ҫ���ȵ���HI_UNF_PVR_PlayCreateChn��������ͨ�� \n
���ô˽ӿ�ǰ��ȷ����Ӧ��¼��ͨ���Ѿ����������򽫻᷵�ش�����HI_ERR_PVR_REC_INVAL_STATE \n
���ô˽ӿ�����1·ʱ�ƺ󣬶�Ӧ��¼��ͨ�������ܱ�ֹͣ��������ֱ��ʱ�Ʋ���ֹͣ

\param[out] pu32PlayChnID   ����ͨ����
\param[in] u32RecChnID     ��Ҫʱ�Ƶ�¼��ͨ����
\param[in] hAVPlay       avplay�������ʶ���ĸ�avplay������
\param[in] hTsBuffer     ts buffer�������ʶ���ĸ�ts buffer���طţ�һ����˵����ts buffer��Ӧ��ts�˿�Ӧ���ǰ���hAVPlay��Ӧ��demux�ϵ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NUL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_PVR_PLAY_INVALID_DMXID ����ʱ�����˴����DEMUX ID
\retval ::HI_ERR_PVR_INVALID_CHNID  ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT  ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_ALREADY ָ����ͨ���Ѿ�����
\retval ::HI_ERR_PVR_NO_CHN_LEFT  �Ѿ�û�п��еĲ���ͨ��������
\retval ::HI_ERR_PVR_REC_INVALID_STATE ¼��ͨ��û������
\retval ::HI_ERR_PVR_NO_MEM  �ڴ治�㣬�޷����䲥����Ҫ��Buffer
\retval ::HI_FAILURE  ����ϵͳ����API����ʧ��

\see \n
::HI_UNF_PVR_PlayStopTimeShift
*/
HI_S32 HI_UNF_PVR_PlayStartTimeShift(HI_U32 *pu32PlayChnID, HI_U32 u32RecChnID, HI_HANDLE hAvplay, HI_HANDLE hTsBuffer);



/**
\brief ֹͣ����ͨ��
\attention \n
�˽ӿ���::HI_UNF_PVR_PlayStartTimeShift�ӿڱ������ʹ�ã��˽ӿ�ֻ��ֹͣʹ��::HI_UNF_PVR_PlayStartTimeShift�����Ĳ���ͨ�� \n
ͨ��::HI_UNF_PVR_PlayStartTimeShift�ӿ������Ĳ���ͨ������ʹ�ô˽ӿ���ֹͣ������������::HI_UNF_PVR_PlayStopChn�ӿ���ֹͣ
\param[in] u32PlayChnID  ͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT         PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID          ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT         ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_ALREADY              ָ����ͨ���Ѿ�����
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE     ͨ��״̬�������磺����::HI_UNF_PVR_PlayStartChn�����Ĳ���ͨ�����ô˽ӿ�
\see \n
::HI_UNF_PVR_PlayStartTimeShift
*/
HI_S32 HI_UNF_PVR_PlayStopTimeShift(HI_U32 u32PlayChnID, const HI_UNF_AVPLAY_STOP_OPT_S *pstStopOpt);


/**
\brief ���ò���ͨ������
\attention \n
ֻ�ж�̬���Բ���ͨ���˽ӿڽ�������
\param[in] u32ChnID     ͨ����
\param[in] pstPlayAttr  ָ�����ͣ�ָ��Ҫ���õ�ͨ����������
\retval ::HI_SUCCESS  �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT  PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID  ͨ���ŷǷ�
\see \n
::HI_UNF_PVR_PlayGetChn
*/
HI_S32 HI_UNF_PVR_PlaySetChn(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr);


/**
\brief ��ȡ����ͨ������
\attention \n
��
\param[in] u32ChnID  ͨ����
\param[out] pstPlayAttr   ָ�����ͣ�ָ���ȡ����ͨ����������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT    PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID     ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT    ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_NUL_PTR         ָ�����Ϊ��
\see \n
::HI_UNF_PVR_PlaySetChn
*/
HI_S32 HI_UNF_PVR_PlayGetChn(HI_U32 u32ChnID, HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr);



/**
\brief ��������ͨ��
\attention \n
����::HI_UNF_PVR_PlayCreateChn�����ͨ��ֻ��ͨ���˽ӿ�����һ�Σ������Ҫ��ͣ/�ָ����ţ�
��ʹ��::HI_UNF_PVR_PlayPauseChn��::HI_UNF_PVR_PlayResumeChn�ӿ�

\param[in] u32ChnID  ͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT      PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID       ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT      ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_ALREADY           ָ����ͨ���Ѿ�����
\retval ::HI_FAILURE                   ����ϵͳ����API����ʧ��

\see \n
::HI_UNF_PVR_PlayStopChn
*/
HI_S32 HI_UNF_PVR_PlayStartChn(HI_U32 u32ChnID);
/**
\brief ֹͣ����ͨ��
\attention \n
�˽ӿ���::HI_UNF_PVR_PlayStartChn�ӿڱ������ʹ�ã��˽ӿ�ֻ��ֹͣʹ��::HI_UNF_PVR_PlayStartChn�����Ĳ���ͨ�� \n
ͨ��::HI_UNF_PVR_PlayStartChn�ӿ������Ĳ���ͨ������ʹ�ô˽ӿ���ֹͣ������������::HI_UNF_PVR_PlayStopTimeShift�ӿ���ֹͣ

\param[in] u32ChnID  ͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT      PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID       ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT      ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_ALREADY           ָ����ͨ���Ѿ�����
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE  ͨ��״̬�������磺����::HI_UNF_PVR_PlayStartTimeShift�����Ĳ���ͨ�����ô˽ӿ�
\see \n
::HI_UNF_PVR_PlayStartChn
*/
HI_S32 HI_UNF_PVR_PlayStopChn(HI_U32 u32ChnID, const HI_UNF_AVPLAY_STOP_OPT_S *pstStopOpt);


/**
\brief ��ͣ����ͨ��
\attention \n
��ͨ���Ѿ���ͣ��������ٴε���::HI_UNF_PVR_PlayPauseChn��ͣͨ�������سɹ� \n
��ͨ���Ѿ���ֹͣ������µ��ô˽ӿ���ͣͨ�������ش�����::HI_ERR_PVR_PLAY_INVALID_STATE
\param[in] u32ChnID   ͨ����
\retval ::HI_SUCCESS  �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT        PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID         ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT        ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE    ͨ��״̬����ͨ���Ѿ�ֹͣ����
\see \n
::HI_UNF_PVR_PlayResumeChn
*/
HI_S32 HI_UNF_PVR_PlayPauseChn(HI_U32 u32ChnID);


/**
\brief �ָ�����ͨ�������ô˽ӿڿ��Իָ�����ͨ�����������ͨ������ͣ״̬
\attention \n
�˽ӿ���::HI_UNF_PVR_PlayPauseChn�ӿڱ������ʹ�ã�ֻ����ͨ���Ѿ���ͣ������²�����ָ�ͨ��
\param[in] u32ChnID ͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT       PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID        ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT       ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE   ָ����ͨ��������ͣ״̬
\see \n
::HI_UNF_PVR_PlayPauseChn
*/
HI_S32 HI_UNF_PVR_PlayResumeChn(HI_U32 u32ChnID);


/**
\brief �����ؼ����š����ô˽ӿڿ��Խ����ؼ����ţ������п�������ˡ����š��������ŵȲ���
\attention \n
�����ؼ�����ģʽ��������˻���������ģʽ��ֻ��Ҫ�����ؼ�����ģʽ���ٶ�ΪPVR_PLAY_SPEED_NORMAL
\param[in] u32ChnID       ͨ����
\param[in] pstTrickMode   �ؼ�����ģʽ��Ϣָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT         PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID          ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT         ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE     ͨ��״̬����ͨ���Ѿ�ֹͣ����
\retval ::HI_ERR_DMX_INVALID_PARA          �����Ƿ�
\retval ::HI_ERR_PVR_NOT_SUPPORT     ��֧�ֵ��ؼ�����ģʽ
\see \n
��
*/
HI_S32 HI_UNF_PVR_PlayTPlay(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_MODE_S *pstTrickMode);

/**
\brief ��λ��ָ��λ�ý��в���
\attention \n
��ͨ���Ѿ�ֹͣ������µ��ñ��ӿڽ����ش�����::HI_ERR_PVR_PLAY_INVALID_STATE\n
seekʱ��������߽磬�Զ��������߽�\n
���seek�ʹӿ�ʼseek����seek����Ӧλ�õ���һ��I֡�����ɹ�����ǰһ��I֡\n
��ǰseek�ʹӽ�βseek����seek����Ӧλ�õ�ǰһ��I֡�����ɹ�������һ��I֡\n
�Ҳ���I֡�᷵�ش���

\param[in] u32ChnID   ͨ����
\param[in] pstPosition  ����λ����Ϣָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT         PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID          ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT         ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE     ͨ��״̬����ͨ���Ѿ�ֹͣ����
\retval ::HI_ERR_DMX_INVALID_PARA          �����Ƿ�
\retval ::HI_ERR_PVR_NOT_SUPPORT     ��֧�ֵ�Seekģʽ
\retval ::HI_ERR_PVR_FILE_TILL_END        Seek���ļ�βû���ҵ���Ӧ��֡
\retval ::HI_ERR_PVR_FILE_TILL_START      Seek���ļ�ͷû���ҵ���Ӧ��֡
\retval ::HI_ERR_PVR_FILE_CANT_READ       ��ȡ�ļ�ʧ��
\see \n
��
*/
HI_S32 HI_UNF_PVR_PlaySeek(HI_U32 u32ChnID, const HI_UNF_PVR_PLAY_POSITION_S *pstPosition);

/**
\brief ��֡���š����ô˽ӿڿ��Խ�����֡���˻�����֡ǰ������
\attention \n
Ŀǰ��֧����֡����
\param[in] u32ChnID    ͨ����
\param[in] s32Direction   ���ŷ��򡣴��ڵ���0��ʾǰ����С��0��ʾ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT         PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID          ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT         ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_PLAY_INVALID_STATE     ͨ��״̬����ͨ���Ѿ�ֹͣ����
\retval ::HI_ERR_PVR_NOT_SUPPORT     ��֧�ֵĹ���

\see \n
NULL
*/
HI_S32 HI_UNF_PVR_PlayStep(HI_U32 u32ChnID, HI_S32 s32Direction);


/**
\brief ��ȡPVR�طŵ�״̬
\attention \n
��ȡ���ŵ�״̬��ע���ڲ���������֮�����
\param[in] u32ChnID
\param[in] pstStatus
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT  PVR¼��ģ��δ��ʼ��
\retval ::HI_ERR_PVR_INVALID_CHNID  ͨ���ŷǷ�
\retval ::HI_ERR_PVR_BUSY ϵͳæ��������������������ԡ�
\see \n
��
*/
HI_S32 HI_UNF_PVR_PlayGetStatus(HI_U32 u32ChnID, HI_UNF_PVR_PLAY_STATUS_S *pstStatus);



/**
\brief ͨ������ͨ��ID����ȡPVR¼�Ƶ������ļ���Ϣ
\attention \n
���ô˽ӿ�������ȡ�����ļ��Ĺ̶���Ϣ�����Ƕ���ʱ�Ƴ�����Щ��Ϣ�ǲ��ϱ仯��
�ڲ��Ź����п���ͨ��::HI_UNF_PVR_PlayGetStatus�ӿڻ�ȡ��ǰ�Ĳ���λ�� \n
��ʱ�ƹ����п���ͨ��::HI_UNF_PVR_RecGetStatus�ӿڻ�ȡ��ǰ��¼��λ��
���⣬�����û������¼��Ҳû���������ţ�����ͨ��::HI_UNF_PVR_GetFileAttrByFileName�ӿڻ�ȡ�ļ�����
\param[in] u32ChnID  ͨ����
\param[in] pAttr   ����״̬��Ϣָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NOT_INIT             PVR����ģ��δ��ʼ��
\retval ::HI_ERR_PVR_NUL_PTR              ��ָ�����
\retval ::HI_ERR_PVR_INVALID_CHNID        ͨ���ŷǷ�
\retval ::HI_ERR_PVR_CHN_NOT_INIT         ָ����ͨ��δ��ʼ��
\retval ::HI_ERR_PVR_FILE_CANT_OPEN       �޷����ļ�
\retval ::HI_ERR_PVR_FILE_CANT_READ       �޷����ļ�
\see \n
��
*/
HI_S32 HI_UNF_PVR_PlayGetFileAttr(HI_U32 u32ChnID, HI_UNF_PVR_FILE_ATTR_S *pAttr);


/**
\brief ��ȡ�����ļ���Ϣ�����ô˽ӿڿ����ڲ����벥��ͨ��������»�ȡָ�������ļ�����Ϣ
\attention \n
pFileNameָ�������ļ��������������ļ��� \n
�κ�ʱ�򶼿��Ե��ô˽ӿڻ�ȡ�����ļ�������
\param[in] pFileName  �����ļ���
\param[in] pAttr     ����״̬��Ϣָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NUL_PTR          ��ָ�����
\retval ::HI_ERR_PVR_FILE_CANT_OPEN   �޷����ļ�
\retval ::HI_ERR_PVR_FILE_CANT_READ   �޷����ļ�
\see \n
��
*/
HI_S32 HI_UNF_PVR_GetFileAttrByFileName(const HI_CHAR *pFileName, HI_UNF_PVR_FILE_ATTR_S *pAttr);


/**
\brief д���û�����
\attention \n
pFileNameָ�������ļ��������������ļ��� \n
u32UsrDataLen��ȡֵ���ܴ���¼�ƴ��ļ�ʱ��¼��ͨ����������ָ����u32UsrDataInfoSize��ȡֵ \n
�û����ݱ������������ļ��� \n
��������¼��ͨ������д���û�������Ϣ
\param[in] pFileName  �����ļ���
\param[in] pInfo     �û�����ָ�룬�ռ����û�����
\param[in] u32UsrDataLen    �û����ݳ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NUL_PTR          ��ָ�����
\retval ::HI_ERR_PVR_FILE_CANT_OPEN   �޷����ļ�
\retval ::HI_ERR_PVR_FILE_CANT_READ   �޷����ļ�
\retval ::HI_ERR_DMX_INVALID_PARA      �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_PVR_SetUsrDataInfoByFileName(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32UsrDataLen);


/**
\brief ��ȡ�û�����
\attention \n
pFileNameָ�������ļ��������������ļ��� \n
pUsrDataLen���ض�ȡ�����û����ݵĳ��ȣ���ȡֵΪu32BufLen��"ʵ���û����ݳ���"�����еĽ�Сֵ��
"ʵ���û����ݳ���"����С��HI_UNF_PVR_RecNewChnʱ���õ�����û����ݳ��ȣ��Ա�֤�ܹ���ȫ���û����ݶ��� \n
PVRģ�鲻����HI_UNF_PVR_SetUsrDataInfoByFileNameʱ������û����ݳ��ȣ�ֻ����HI_UNF_PVR_RecNewChnʱ���õ�����û����ݳ���

\param[in] pFileName   �����ļ���
\param[in] pInfo       �û����ݻ��������ռ����û�����
\param[in] u32BufLen   ����������
\param[in] pUsrDataLen  ʵ�ʶ�ȡ�����û����ݳ���

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_NUL_PTR           ��ָ�����
\retval ::HI_ERR_PVR_FILE_CANT_OPEN    �޷����ļ�
\retval ::HI_ERR_PVR_FILE_CANT_READ    �޷����ļ�
\retval ::HI_ERR_DMX_INVALID_PARA       �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_PVR_GetUsrDataInfoByFileName(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32BufLen, HI_U32* pUsrDataLen);


/**
\brief ע���¼��ص����������ô˽ӿڿ���ע��PVR�¼��Ļص��������Ӷ���PVR¼�ơ����Ź����в������¼����д���
\attention \n
����ʹ��::HI_UNF_PVR_UnRegisterEvent����ע��1���¼��������Ѿ�ע����¼���һֱ������Ч
����PVR_EVENT_PLAY_REACH_REC��Ϣ�������û���ע��Ļص�������ֹͣPVR���ţ����л���ֱ��ģʽ��AVPLAY���в��š�
��¼����������Ϊ�����Ƶ�ʱ��PVR_EVENT_REC_OVER_FIX��Ϣ��¼�Ƴ��ȵ���ָ�����ȣ�����ֹͣ¼�Ƶ�ʱ���ϱ���
��¼����������Ϊ���Ƶ�ʱ��PVR_EVENT_REC_OVER_FIX��Ϣ��ÿ�λ��Ƶ�ʱ�򶼻��ϱ�����ʱ����Ϣ����ص�������s32EventValue����ֵΪ���ƵĴ���(��1��ʼ����)��
PVR_EVENT_REC_REACH_PLAY��Ϣ��¼�Ƽ���׷�ϲ��ŵ�ʱ���ϱ�����ʱ����Ϣ����ص�������s32EventValue����ֵΪ¼��λ�þ��벥��λ�õ��ֽ�����

\param[in] enEventType ��Ҫע����¼�����
\param[in] callBack    �¼�������
\param[in] args        �û��Զ���ص������Ĳ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_INTF_EVENT_INVAL    �Ƿ����¼�
\retval ::HI_ERR_PVR_ALREADY             ���Զ��Ѿ�ע����¼��ٴ�ע��
\retval ::HI_ERR_PVR_INTF_EVENT_NOREG    �ص�����ָ������޷�ע��ɹ�
\see \n
��
*/
HI_S32 HI_UNF_PVR_RegisterEvent(HI_UNF_PVR_EVENT_E enEventType, eventCallBack callBack, HI_VOID *args);


/**
\brief ȥע��PVR�¼��Ļص�����
\attention \n
����ʹ�ô˽ӿ���ȥע��1���¼��������Ѿ�ע����¼���һֱ������Ч
\param[in] enEventType          ��Ҫȥע����¼�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_PVR_INTF_EVENT_INVAL  �Ƿ����¼�
\retval ::HI_ERR_PVR_INTF_EVENT_NOREG  ��û��ע����¼�����ȥע��
\see \n
��
*/
HI_S32 HI_UNF_PVR_UnRegisterEvent(HI_UNF_PVR_EVENT_E enEventType);


/**
\brief
\attention \n
��ʱ��֧�ִ˹���
\param[in] pstTsFileName
\param[in] pstIdxFileName
\param[in] pAttr
\retval ::HI_SUCCESS  �ɹ�
\retval ::HI_ERR_PVR_NOT_SUPPORT ��֧�ִ˹���
\see \n
��
*/
HI_S32 HI_UNF_PVR_CreateIdxFile(HI_U8* pstTsFileName, HI_U8* pstIdxFileName, HI_UNF_PVR_GEN_IDX_ATTR_S* pAttr);



/**
\brief �����Ƿ����������Ϣ
\attention \n
Ĭ�����error���ϼ���ĵ�����Ϣ
\param[in] enDebugLevel  ������Ϣ�������
\retval none
\see \n
��
*/
HI_VOID HI_UNF_PVR_ConfigDebugInfo(HI_LOG_LEVEL_E enDebugLevel);



/**
\brief ɾ��¼��ʱ���ɵ������ļ��������ļ�
\attention \n
pFileNameָ�������ļ��������������ļ���\n
���ô˽ӿں�¼�ƴ�����ʱ���ɵ������ļ��������ļ�������ɾ��\n
��������ļ�����4G��������data.ts, data.ts.0001, data.ts.0002, data.ts.0003 ...\n
�ȶ���ļ�������ɾ��ʱֻ��Ҫ�����ļ���"data.ts"�Ϳ����ˡ�
\param[in] pFileName   �����ļ���
\retval none
\see \n
��
*/
HI_VOID HI_UNF_PVR_RemoveFile(const HI_CHAR *pFileName);


/**
\brief
\attention \n
\param[in] u64Size
\retval none
\see \n
��
*/
//HI_S32 HI_UNF_PVR_SetFileNodeMaxSize(HI_U64 u64Size);


/**
\brief
\attention \n
\param ��
\retval none
\see \n
��
*/
//HI_U64 HI_UNF_PVR_GetFileNodeMaxSize();
/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __HI_UNF_PVR_H__ */
