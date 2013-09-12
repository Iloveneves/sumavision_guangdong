/******************************************************************************

Copyright (C), 2004-2008, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_demux.h
Version       : Initial
Author        : Hisilicon multimedia software group
Created       : 2008-06-10
Last Modified :
Description   : Hisilicon DEMUX API declaration
Function List :
History       :
* Version   Date         Author     DefectNum    Description
* main\1    2008-06-10   j40671     NULL         Create this file.
* main\2    2010-04-02   j40671     NULL         modify for HD series.
******************************************************************************/
/**
 * \file
 * \brief �ṩDEMUX�������Ϣ
 */

#ifndef __HI_UNF_DEMUX_H__
#define __HI_UNF_DEMUX_H__

#include "hi_unf_common.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_2 */
/** @{ */  /** <!-- ��DEMUX�� */

/**DMX�豸��Ŀ*/
#define DMX_CNT                         5

/**DVB�˿�����,ͨ��tuner��������*/
#define DMX_DVBPORT_CNT                 3

/**RAM�˿�����,ʹ��TS BUFFER��������*/
#define DMX_RAMPORT_CNT                 4

/**DMXģ��˿�����*/
#define DMX_TOTALPORT_CNT               7

/**DMXģ������Ƶͨ������ */
#define DMX_AVCHAN_CNT                  32

/**DMXͨ������Ŀ*/
#define DMX_TOTALCHAN_CNT               96

/**DMX����������Ŀ*/
#define DMX_TOTALFILTER_CNT             96

 /**filter������*/
#define DMX_FILTER_MAX_DEPTH            16

/** PCRͨ������*/
#define DMX_PCRCHAN_CNT                 16


/** Ĭ��ͨ��ͨ����������С 16K Byte*/
#define DMX_DEFAULT_CHANBUF_SIZE        (16*1024)


/** DEMUX ID����*/
#define HI_UNF_DMX_ID_0_PLAY            0
#define HI_UNF_DMX_ID_1_REC             1
#define HI_UNF_DMX_ID_2_REC             2
#define HI_UNF_DMX_ID_3_REC             3
#define HI_UNF_DMX_ID_4_PLAY            4


/*************************** Structure Definition ****************************/

/**����DEMUXģ��ҵ���ܽṹ��*/
typedef struct hiUNF_DMX_CAPABILITY_S
{
    HI_U32 u32PortNum;          /**< �˿�����     */
    HI_U32 u32DmxNum;           /**< �豸����     *///AI7D04684
    HI_U32 u32CommonChannelNum; /**< ͨ��ͨ������ */
    HI_U32 u32AudioChannelNum;  /**< ��Ƶͨ������ */
    HI_U32 u32VideoChannelNum;  /**< ��Ƶͨ������ */
    HI_U32 u32FilterNum;        /**< ����������   */
    HI_U32 u32KeyNum;           /**< ��Կ������   */
}HI_UNF_DMX_CAPABILITY_S;

/**TS�˿�ID */
typedef enum hiUNF_DMX_PORT_E
{
    HI_UNF_DMX_PORT_0_TUNER,     /**< port0, Tunerģʽ */
    HI_UNF_DMX_PORT_1_TUNER,     /**< port1, Tunerģʽ */
    HI_UNF_DMX_PORT_2_TUNER,     /**< port2, Tunerģʽ */
    HI_UNF_DMX_PORT_3_RAM,       /**< port3, RAMģʽ */
    HI_UNF_DMX_PORT_4_RAM,       /**< port4, RAMģʽ */
    HI_UNF_DMX_PORT_5_RAM,       /**< port5, RAMģʽ */
    HI_UNF_DMX_PORT_6_RAM,       /**< port6, RAMģʽ */

    HI_UNF_DMX_PORT_BUTT
}HI_UNF_DMX_PORT_E;

/**TS�˿�ģʽ */
typedef enum hiUNF_DMX_PORT_MODE_E
{
    HI_UNF_DMX_PORT_MODE_EXTERNAL,  /**<�ⲿTS����*/
    HI_UNF_DMX_PORT_MODE_INTERNAL,  /**<�ڲ�TS����*/
    HI_UNF_DMX_PORT_MODE_RAM,       /**<���ڴ�����*/

    HI_UNF_DMX_PORT_MODE_BUTT
}HI_UNF_DMX_PORT_MODE_E;

/**TS�˿����� */
typedef enum hiUNF_DMX_PORT_TYPE_E
{
    HI_UNF_DMX_PORT_TYPE_PARALLEL_BURST,          /**< ����BURSTģʽ             */
    HI_UNF_DMX_PORT_TYPE_PARALLEL_VALID,          /**< ����VALIDģʽ             */
    HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_188,     /**< ��ͬ��188ģʽ             */
    HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_204,     /**< ��ͬ��204ģʽ             */
    HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_188_204, /**< ��ͬ��188/204�Զ�ʶ��ģʽ */
    HI_UNF_DMX_PORT_TYPE_SERIAL,                  /**< ����ģʽ                  */

    HI_UNF_DMX_PORT_TYPE_BUTT
}HI_UNF_DMX_PORT_TYPE_E;

/**TS�˿�����*/
typedef struct hiUNF_DMX_PORT_ATTR_S
{
    HI_UNF_DMX_PORT_MODE_E enPortMod;  /**< �˿�ģʽ */
    HI_UNF_DMX_PORT_TYPE_E enPortType; /**< �˿����� */
    HI_U32 u32SyncLostTh;              /**< ͬ����ʧ���ޣ��Ƽ�ʹ��Ĭ��ֵ */
    HI_U32 u32SyncLockTh;              /**< ͬ���������ޣ��Ƽ�ʹ��Ĭ��ֵ */
    HI_U32 u32TunerInClk;              /**<Tuner����ʱ���Ƿ���.0: ͬ��(Ĭ��); 1: ����*/
    HI_U32 u32SerialBitSelector;       /**<�˿�����ѡ�񡣲���ʱ:0: ��ʾcdata[7]���λ(Ĭ��);1: ��ʾcdata[0]���λ��
                                           ����ʱ:1: ��ʾcdata[0]Ϊ������(Ĭ��); 0: ��ʾcdata[7]Ϊ������*/

    HI_U32 u32TunerErrMod;             /**<tuner��DEMUX��cerr_n�ߵ�ƽģʽ:
                                           0: ��ʾcerr_n��Ϊ��ʱ��ʾ���ݴ���;
                                           1: ��ʾcerr_n��Ϊ��ʱ��ʾ���ݴ��� (Ĭ��) */

} HI_UNF_DMX_PORT_ATTR_S;

/**TS�˿ڵ�״̬*/
typedef struct hiUNF_DMX_PORT_PACKETNUM_S
{
	HI_U32 				   u32TsPackCnt;	/**<�˿��յ���TS������*/
	HI_U32  			   u32ErrTsPackCnt;	/**<�˿��ϴ���TS���ļ���*/
}HI_UNF_DMX_PORT_PACKETNUM_S;

/**DEMUX��TS Buffer״̬ */
typedef struct hiUNF_DMX_TSBUF_STATUS_S
{
    HI_U32 u32BufSize;    /**< ��������С       */
    HI_U32 u32UsedSize;   /**< ��������ʹ�ô�С */
} HI_UNF_DMX_TSBUF_STATUS_S;

/**ͨ������ */
typedef enum hiUNF_DMX_CHAN_TYPE_E
{
    HI_UNF_DMX_CHAN_TYPE_SEC = 0, /**<���ڽ��� PSI/SI��secitons���ݵ�ͨ��*/
    HI_UNF_DMX_CHAN_TYPE_PES,     /**<���ڽ���PES�����ݵ�ͨ��*/
    HI_UNF_DMX_CHAN_TYPE_AUD,     /**<���ڽ�����Ƶ���ݵ�ͨ��*/
    HI_UNF_DMX_CHAN_TYPE_VID,     /**<���ڽ�����Ƶ���ݵ�ͨ��*/
    HI_UNF_DMX_CHAN_TYPE_POST,      /**<��������ͨ�������ڽ���ĳPID������TS��*/
    HI_UNF_DMX_CHAN_TYPE_ECM_EMM,   /**<���ڽ���ECM��EMM���ݵ�ͨ��*/

    HI_UNF_DMX_CHAN_TYPE_BUTT
}HI_UNF_DMX_CHAN_TYPE_E;

/**ͨ����CRCģʽ */
typedef enum hiUNF_DMX_CHAN_CRC_MODE_E
{
    HI_UNF_DMX_CHAN_CRC_MODE_FORBID = 0,                /**< CRCУ���ֹ */
    HI_UNF_DMX_CHAN_CRC_MODE_FORCE_AND_DISCARD = 1,     /**< CRCУ��ʹ�ܣ�����������Section */
    HI_UNF_DMX_CHAN_CRC_MODE_FORCE_AND_SEND = 2,        /**< CRCУ��ʹ�ܣ������ʹ���Section */
    HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_DISCARD = 3, /**< �����﷨�ж��Ƿ����CRCУ�飬����������Section */
    HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_SEND = 4,    /**< �����﷨�ж��Ƿ����CRCУ�飬�����ʹ���Section */

    HI_UNF_DMX_CHAN_CRC_MODE_BUTT
}HI_UNF_DMX_CHAN_CRC_MODE_E;

/**ͨ�������ģʽ */
typedef enum hiUNF_DMX_CHAN_OUTPUT_MODE_E
{
    HI_UNF_DMX_CHAN_OUTPUT_MODE_PLAY = 0x1,     /**< ����Ƶ���Ż����ݽ��� */
    HI_UNF_DMX_CHAN_OUTPUT_MODE_REC  = 0x2,     /**< ¼�� */
    HI_UNF_DMX_CHAN_OUTPUT_MODE_PLAY_REC = 0x3, /**< ͬʱ¼�ƺͲ��Ż����ݽ��� */
    HI_UNF_DMX_CHAN_OUTPUT_MODE_BUTT = -1
}HI_UNF_DMX_CHAN_OUTPUT_MODE_E;

/**ͨ������*/
typedef struct hiUNF_DMX_CHAN_ATTR_S
{
    HI_U32 u32BufSize;                            /**< ͨ��Ӳ��ʹ��buffer��С*/
    HI_UNF_DMX_CHAN_TYPE_E enChannelType;       /**< ͨ������ */
    HI_UNF_DMX_CHAN_CRC_MODE_E enCRCMode;       /**< CRCģʽ��ͨ������ΪDMX_CHAN_SEC ʱ��Ч */
    HI_UNF_DMX_CHAN_OUTPUT_MODE_E enOutputMode;   /**< ͨ���������ģʽ */
}HI_UNF_DMX_CHAN_ATTR_S;

/**ͨ�����ݵļ��ű�־ */
typedef enum hiUNF_DMX_SCRAMBLED_FLAG_E
{
    HI_UNF_DMX_SCRAMBLED_FLAG_TS,  /**<���ݱ�TS������*/
    HI_UNF_DMX_SCRAMBLED_FLAG_PES, /**<���ݱ�PES������*/
    HI_UNF_DMX_SCRAMBLED_FLAG_NO,  /**<����δ������*/

    HI_UNF_DMX_SCRAMBLED_FLAG_BUTT
}HI_UNF_DMX_SCRAMBLED_FLAG_E;

/**ͨ��״̬ */
typedef enum hiUNF_DMX_CHAN_STATUS_E
{
    HI_UNF_DMX_CHAN_CLOSE = 0x0,        /**<ͨ�����ڹر�״̬*/
    HI_UNF_DMX_CHAN_PLAY_EN = 0x1,      /**<ͨ����������Ƶ���Ż����ݽ���״̬*/
    HI_UNF_DMX_CHAN_REC_EN = 0X2,       /**<ͨ����������¼��״̬*/
    HI_UNF_DMX_CHAN_PLAY_REC_EN = 0X3,  /**<ͨ������ͬʱ¼�ƺ����ݽ���״̬*/
}HI_UNF_DMX_CHAN_STATUS_E;

/**����ͨ��״̬�ṹ��*/
typedef struct hiUNF_DMX_CHAN_STATUS_S
{
    HI_UNF_DMX_CHAN_STATUS_E enChanStatus;   /**<ͨ��״̬*/
}HI_UNF_DMX_CHAN_STATUS_S;

/******************  Filter Attr  ***********************/


/** ����������*/
typedef struct hiUNF_DMX_FILTER_ATTR_S
{
    HI_U32 u32FilterDepth;                    /**<���������*/
    HI_U8 au8Match[DMX_FILTER_MAX_DEPTH];     /**<������ƥ���ֽ�,��bit�Ƚ�*/
    HI_U8 au8Mask[DMX_FILTER_MAX_DEPTH] ;     /**<�����������ֽ�,��bit����, 0:û��mask��Ҫ���бȽ�, 1:mask�����ã������бȽ�*/
    HI_U8 au8Negate[DMX_FILTER_MAX_DEPTH] ;   /**<������ȡ���ֽ�,��byte����, 0:��ȡ��,1:ȡ��*/
}HI_UNF_DMX_FILTER_ATTR_S;

/** CA���ͣ��Ƿ�ʹ�ø߰�ȫCA*/
typedef enum hiUNF_DMX_CA_TYPE_E
{
    HI_UNF_DMX_CA_NORMAL = 0,    /**<��ͨCA*/
    HI_UNF_DMX_CA_ADVANCE,       /**<�߰�ȫCA*/

    HI_UNF_DMX_CA_BUTT
}HI_UNF_DMX_CA_TYPE_E;

/** �ؼ���ģʽ*/
typedef enum hiUNF_DMX_CA_ENTROPY_REDUCTION_E
{
    HI_UNF_DMX_CA_ENTROPY_REDUCTION_OPEN = 0,    /**<48bit*/
    HI_UNF_DMX_CA_ENTROPY_REDUCTION_CLOSE,       /**<64bit*/

    HI_UNF_DMX_CA_ENTROPY_REDUCTION_BUTT
}HI_UNF_DMX_CA_ENTROPY_E;


/** ������Э������*/
typedef enum hiUNF_DMX_DESCRAMBLER_TYPE_E
{
    HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2 = 0,    /**<CSA2.0*/
    HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3,       /**<CSA3.0*/

    HI_UNF_DMX_DESCRAMBLER_TYPE_BUTT
}HI_UNF_DMX_DESCRAMBLER_TYPE_E;


/** ��Կ������*/
typedef struct hiUNF_DMX_DESCRAMBLER_ATTR_S
{
    HI_UNF_DMX_CA_TYPE_E enCaType;                    /**<�������Ƿ�ʹ�ø߰�ȫCA*/
    HI_UNF_DMX_DESCRAMBLER_TYPE_E enDescramblerType;  /**<����������Э������*/
    HI_UNF_DMX_CA_ENTROPY_E enEntropyReduction;       /**<0:48bitģʽ��1:64 bitģʽ��cas2.0ʱ��Ч*/
}HI_UNF_DMX_DESCRAMBLER_ATTR_S;


/** DEMUX���ݰ�������*/
typedef enum hiUNF_DMX_DATA_TYPE_E
{
    HI_UNF_DMX_DATA_TYPE_WHOLE = 0,  /**< �˶����ݰ������������ݰ�, ����SECTIONÿ��������������*/
    HI_UNF_DMX_DATA_TYPE_HEAD,       /**< �˶����ݰ������ݰ�����ʼ�����ǲ�һ���������İ�, ֻ����PES����*/
    HI_UNF_DMX_DATA_TYPE_BODY,       /**< �˶����ݰ������ݰ������ݣ���������ʼ�������н�β, ֻ����PES����*/
    HI_UNF_DMX_DATA_TYPE_TAIL,       /**< �˶����ݰ������ݰ��Ľ�β������ָʾ��ʶ��İ�����, ֻ����PES����*/

    HI_UNF_DMX_DATA_TYPE_BUTT
}HI_UNF_DMX_DATA_TYPE_E;

/** DEMUX���ݰ��ṹ*/
typedef struct hiUNF_DMX_DATA_S
{
    HI_U8   *pu8Data;                   /**< ����ָ�� */
    HI_U32  u32Size;                    /**< ���ݳ��� */
    HI_UNF_DMX_DATA_TYPE_E enDataType;  /**< ���ݰ������� */
}HI_UNF_DMX_DATA_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_1 */
/** @{ */  /** <!-- ��DEMUX�� */

/**
\brief ��ʼ��DEMUXģ��
\attention \n
�ڽ���DEMUX��ز���ǰӦ�����ȵ��ñ��ӿ�\n
��ʹ��PVR��AVPLAYǰ����ǰ����DEMUXģ��ĳ�ʼ��\n
�ظ����ñ��ӿڣ��᷵�سɹ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_Init(HI_VOID);


/**
\brief ȥ��ʼ��DEMUXģ��
\attention \n
���ñ��ӿ�ֹͣʹ��DEMUXģ�飬���ͷű�������ռ�õ�DEMUX��Դ\n
���ӿڵ�һ�ε���������,�ظ����÷��سɹ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_DeInit(HI_VOID);


/**
\brief ��ѯDEMUXģ��ҵ��������ҵ���ܰ���ͨ��ͨ����Ŀ����������Ŀ����Կ��Ŀ���˿���Ŀ��DEMUX�豸��Ŀ������Ƶͨ����Ŀ��
\attention \n
��
\param[out] pstCap  ָ�����ͣ����DEMUXģ��������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
::HI_UNF_DMX_CAPABILITY_S
*/
HI_S32 HI_UNF_DMX_GetCapability(HI_UNF_DMX_CAPABILITY_S *pstCap);


/**
\brief ��ȡDEMUX�˿�����
\attention \n
��
\param[in] u32PortId  �˿ں�
\param[out] pstAttr   ָ�����ͣ�����˿����ԡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetTSPortAttr(HI_UNF_DMX_PORT_E enPortId, HI_UNF_DMX_PORT_ATTR_S *pstAttr);


/**
\brief ����DEMUX�˿�����
\attention \n
������ͨ��HI_UNF_DMX_GetTSPortAttr��ȡĬ�����ԣ�Ȼ���Ҫ�ı�����Խ�������\n
�˿�0~2ΪHI_UNF_DMX_PORT_MODE_EXTERNAL���ͣ��˿�3~6ΪHI_UNF_DMX_PORT_MODE_RAM���Ͷ˿�\n
�˿�ģʽֻ֧�ֲ�ѯ����֧���޸ģ��������Ծ�֧����ʱ��̬�޸�\n
�ڴ�ģʽ�Ķ˿ڽ�֧������Ϊ��ͬ������ģʽ�����������˿����ͻ�ʧ��\n
ͬ����ʧ��ͬ���������ޣ��Ƽ�ʹ��Ĭ��ֵ\n
tuner����ʱ�ӷ��򡢶˿�����ѡ���tuner error�ߵ�ƽģʽ����������ѯӲ������ʦ\n
���ο�tuner���û��ֲᣬȻ������Ϊ���ʵ�ֵ
\param[in] u32PortId   �˿ںš�
\param[in] pstAttr  ָ�����ͣ��˿�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_SetTSPortAttr(HI_UNF_DMX_PORT_E enPortId, const HI_UNF_DMX_PORT_ATTR_S *pstAttr);


/**
\brief ��DEMUX���˿���
\attention \n
֧��5·DEMUX��ÿ·DEMUXֻ�ܰ󶨵�һ��PORT������һ��PORT�����ݿ��Էַ������DEMUX\n
DEMUX�󶨵��˿���֮��Ϳ�ʼ��������˿������������\n
����ʹ����·DEMUX�������ݺ�ʹ��HI_UNF_DMX_DetachTSPort�ӿڽ��DEMUX\n
���Զ�̬�İ󶨵���ͬ�Ķ˿��ϣ������Ƚ��\n
�ظ����ô˽ӿڰ󶨵���ͬͨ���Ϸ��سɹ�
\param[in] u32DmxId  DEMUX ID��
\param[in] enPortId  �˿ںš�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
::HI_UNF_DMX_DetachTSPort
*/
HI_S32 HI_UNF_DMX_AttachTSPort(HI_U32 u32DmxId, HI_UNF_DMX_PORT_E enPortId);


/**
\brief �Ӷ˿��Ͻ��DEMUX
\attention \n
����ʹ��DEMUX�����κ�����ʱʹ�ô˽ӿڽ�DEMUX�Ӷ˿��Ͻ��\n
���Զ�̬ʹ�ý�󶨽ӿڣ�����ͨ����󶨽ӿ��ж�DEMUX������Դ\n
�ظ���󶨷��سɹ�
\param[in] u32DmxId  DEMUX ID��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
::HI_UNF_DMX_AttachTSPort
*/
HI_S32 HI_UNF_DMX_DetachTSPort(HI_U32 u32DmxId);


/**
\brief ��ȡDEMUX���󶨵Ķ˿ڵĶ˿ں�
\attention \n
���DEMUXû�а󶨵��κζ˿��ϻ᷵�ش�����
\param[in] u32DmxId  DEMUX ID��
\param[out] penPortId  ָ�����ͣ����DEMUX�󶨵Ķ˿ںš�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOATTACH_PORT  ��·DEMUXû�а󶨵��κζ˿���
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetTSPortId(HI_U32 u32DmxId, HI_UNF_DMX_PORT_E *penPortId);


/**
\brief ΪRAM�˿ڴ���TS Buffer���ڽ��մ�����򱾵ش洢�������TS����
\attention \n
ֻ��RAM���Ͷ˿ڿ��Դ���TS Buffer\n
buffer��С������4K��16M֮�䣬��λΪ�ֽ�\n
buffer��С���Ϊ4K��������������������������ڲ���������¶������\n
ͬһ���˿ڲ����ظ�����TS Buffer,���򷵻ش�����
\param[in] enPortId  �˿ںš�
\param[in] u32TsBufSize TS Buffer��С
\param[out] phTsBuffer  ָ�����ͣ����������TS Buffer �����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_RECREAT_TSBUFFER  �ظ�����TS Buffer
\see \n
��
*/
HI_S32 HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_E enPortId, HI_U32 u32TsBufSize, HI_HANDLE *phTsBuffer);


/**
\brief ���ٴ�����TS Buffer
\attention \n
�����ظ�����һ��TS Buffer,����֮��handle�Ͳ�������\n
����֮��buffer�е����ݾͻᱻ��գ������ٽ���Get��Put����\n
����TS buffer���������ͨ�������ݣ�Ҫ�л�������Ҫע��ر�ͨ�������´�
\param[in] hTsBuffer TS Buffer���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_DestroyTSBuffer(HI_HANDLE hTsBuffer);


/**
\brief ��ȡTS Buffer�ռ䣬������������
\attention \n
�ظ�get����ͬһ��buffer��ַ\n
��������ʱע��ÿ����������ݳ��ȣ�̫�����ܻᵼ���������ݲ���ʱ\n
̫�̿��ܻᵼ�µ���̫Ƶ���������½�\n
��ʣ��ռ�С�ڵ�������ĳ���ʱ�����ش�����\n
ÿ������ĳ���ҪС��ʣ��ʣ�೤�ȣ���buffer�����ܱ�����\n
���󳤶Ȳ�����Ϊ0�����򷵻ز����Ƿ�������\n
u32TimeOutMs����Ϊ0��ʾ���ȴ�������Ϊ0xffffffff��ʾһֱ�ȴ�������Ϊ����ֵ��ʾ�ȴ�u32TimeOutMs���롣\n
����������ʱ�䣬���޷����뵽Buffer���򷵻�HI_ERR_DMX_TIMEOUT������\n
u32TimeOutMs����Ϊ0ʱ��������벻��Buffer��˵����ʱ�ڲ�TS Buffer�ռ���������Ҫͨ��usleep(10000)�ͷ�cpu
��ʹ�����߳��ܹ��õ����ȡ�
\param[in] hTsBuffer TS Buffer���
\param[in] u32ReqLen �������ݵĳ���
\param[out] pstData   ����buffer�ṹ
\param[in] u32TimeOutMs      �ȴ���ʱʱ�䣬��λms
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_TIMEOUT  �ȴ���ʱ
\retval ::HI_ERR_DMX_NOAVAILABLE_BUF  ʣ��buffer�ռ�С�����󳤶�
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetTSBuffer(HI_HANDLE hTsBuffer, HI_U32 u32ReqLen,
            HI_UNF_STREAM_BUF_S *pstData, HI_U32 u32TimeOutMs);


/**
\brief TS����������ϣ����ڸ���TS Bufferдָ��
\attention \n
�˽ӿڱ����Get�ӿ����ʹ�ã����û��Get�����Put�������򲻻�����κβ����������سɹ�\n
Put�ĳ������Ϊ0��Ҳ��������κβ���ֱ�ӷ��سɹ�\n
������Put���ȴ���ʵ��Get���ĳ��ȣ����򷵻ز����Ƿ�������\n
����Put����С��Get���ȣ�����ֻ������һ��������
\param[in] hTsBuffer TS Buffer���
\param[in] u32ValidDataLen ��Ч���ݵĳ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_PutTSBuffer(HI_HANDLE hTsBuffer, HI_U32 u32ValidDataLen);


/**
\brief ��λTS Buffer�����TS Buffer�е�����
\attention \n
TS Buffer��λ����Ҫ����get����ִ��put����
\param[in] hTsBuffer TS Buffer���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_ResetTSBuffer(HI_HANDLE hTsBuffer);


/**
\brief ��ȡTS Buffer״̬
\attention \n
���Բ�ѯTS Buffer��С�����õĿռ��С
\param[in] hTsBuffer TS Buffer���
\param[out] pStatus  TS Buffer״̬�ṹ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetTSBufferStatus(HI_HANDLE hTsBuffer, HI_UNF_DMX_TSBUF_STATUS_S *pStatus);

/**
\brief ��ȡTS Buffer��Ӧ��Port ID
\attention \n
����û�������TS buffer,��ѯ�᷵�ش���
\param[in] hTsBuffer TS Buffer���
\param[out] penPortId   TS Buffer��Ӧ��Port ID
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetTSBufferPortId(HI_HANDLE hTsBuffer, HI_UNF_DMX_PORT_E *penPortId);

/**
\brief ��ȡPort ID��Ӧ��TS Buffer handle
\attention \n
����û�������TS buffer,��ѯ�᷵�ش���
\param[in] enPortId   Port ID
\param[out] phTsBuffer TS Buffer���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetTSBufferHandle(HI_UNF_DMX_PORT_E enPortId, HI_HANDLE *phTsBuffer);

/**
\brief ��ȡ�˿ڵ�TS����Ϣ
\attention \n
����û�а󶨵Ķ˿�,��ѯ�᷵�ش���
\param[in] u32PortId   Port ID
\param[out] sPortStat  TS��������Ϣ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/

HI_S32 HI_UNF_DMX_GetTSPortPacketNum(HI_U32 u32PortId, HI_UNF_DMX_PORT_PACKETNUM_S *sPortStat);

/**
\brief ��ȡͨ��Ĭ������
\attention \n
���������ͨ��֮ǰʹ�ô˽ӿڻ�ȡĬ�����ԣ�Ȼ��ı���Ҫ�޸ĵ����Լ���\n
Ĭ�����԰�һ���sectionͨ�����صģ����Ҫʹ���������͵�ͨ��ע���޸�����ֵ��
\param[out] pstChAttr ͨ�����Խṹ��ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetChannelDefaultAttr(HI_UNF_DMX_CHAN_ATTR_S *pstChAttr);


/**
\brief ����ͨ�����Դ���һ��PIDͨ��
\attention \n
������ô˽ӿ�֮ǰ�������ȵ���HI_UNF_DMX_GetChannelDefaultAttr��ȡͨ��Ĭ������\n
ֻ��section���͵�ͨ����ecm emm���͵�ͨ��֧������CRCģʽ�����ҿ���ͨ���������ýӿڶ�̬�޸�CRCģʽ\n
��������ͨ��ֻ֧������ΪCRC��ֹ�����ѡ�����������͵�CRC�ᱻĬ���޸�ΪCRC��ֹ\n
������ͨ��ʱע��Buffer��С�����ã�Ĭ�ϴ�СΪ16K��buffer��С�ĵ�λΪ�ֽ�\n
Section��ecm emm��POSTͨ������ʹ��16K���ϵ�buffer��С�����С��16K�ᱻĬ���޸�Ϊ16K\n
PESͨ������ʹ��64K���ϵ�buffer��С�����С��64K�ᱻĬ���޸�Ϊ64K\n
DEMUX_1��DEMUX_2��DEMUX_3֧��¼�ƹ��ܣ��������¼�����͵�����Ƶͨ������PVRģ��ʹ�ã�\n
�������ͺ�ͬʱ������¼�����͵�����Ƶͨ���ǲ��������\n
����Ƶ�Ĳ���ͨ����Playerͳһ����͹���
\param[in] u32DmxId  DEMUX ID��
\param[in] pstChAttr  ָ�����ͣ�����ͨ�����ԡ���μ�::HI_UNF_DMX_CHAN_ATTR_S
\param[out] phChannel  ָ�����ͣ���������ͨ��Handle��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOFREE_CHAN  û�п���ͨ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_CreateChannel(HI_U32 u32DmxId, const HI_UNF_DMX_CHAN_ATTR_S *pstChAttr,
            HI_HANDLE *phChannel);


/**
\brief ���ٴ�����PIDͨ��
\attention \n
�ͷ�ͨ��ʱ���ͨ�����ڴ�״̬���Զ��ر�ͨ�������ͨ���ϰ��˹���������Կ�������Զ����\n
���ǲ������ͷŹ���������Կ��
����ʹ�ý�󶨽ӿڽ�����ʽ�Ľ�󶨲���������Դ��ʹ�ý��������Ĺ���
\param[in] hChannel  ͨ�������
\retval none
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
��
*/
HI_S32 HI_UNF_DMX_DestroyChannel(HI_HANDLE hChannel);


/**
\brief ��ȡͨ������
\attention \n
���ӿڱ�����ͨ�������Ժ�ſ��Ե���
\param[in] hChannel   ͨ��Handle��
\param[out] pstChAttr  ָ�����ͣ����ָ��ͨ�����ԡ���μ�::HI_UNF_DMX_CHAN_ATTR_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetChannelAttr(HI_HANDLE hChannel, HI_UNF_DMX_CHAN_ATTR_S *pstChAttr);


/**
\brief ����ͨ������
\attention \n
���ӿڱ�����ͨ�������Ժ�ſ��Ե���\n
����CRCģʽ�������Զ�������ʹ��HI_UNF_DMX_SetChannelAttr�ӿڽ��ж�̬�޸�\n
CRCģʽ������ͨ������������ʱ���޸ģ���̬��Ч\n
Ҫ�޸��������Ի᷵�ز����Ƿ�������
\param[in] hChannel   ͨ�������
\param[in] pstChAttr   ָ�����ͣ�����ͨ�����ԡ���μ� ::HI_UNF_DMX_CHAN_ATTR_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_SetChannelAttr(HI_HANDLE hChannel, const HI_UNF_DMX_CHAN_ATTR_S *pstChAttr);


/**
\brief ����ͨ��PID
\attention \n
ͬһ·DEMUX������ͨ��������ͬ��PID�������õ�ͨ����Ч�������õ�ͨ����PID���޸�Ϊ0x1fff\n
������ͨ���رյ�״̬������ͨ����PID\n
����ͨ����PID����Ϊ0x1fff,����Ϊ0x1fff�󲻽����κ����ݣ��൱�ڹر�ͨ��
\param[in] hChannel   ͨ�������
\param[in] u32Pid     ͨ��PID
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_OPENING_CHAN  ͨ�����ڴ�״̬
\see \n
��
*/
HI_S32 HI_UNF_DMX_SetChannelPID(HI_HANDLE hChannel, HI_U32 u32Pid);


/**
\brief ��ȡͨ�����õ�PID
\attention \n
û������PIDǰ����ȡ����PIDΪ0x1fff\n
������ͨ������������ʱ�̻�ȡͨ��PID
\param[in] hChannel  ͨ�������
\param[out] pu32Pid   ָ�����ͣ����ͨ����PID
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetChannelPID(HI_HANDLE hChannel, HI_U32 *pu32Pid);


/**
\brief ��ͨ��
\attention \n
��PIDͨ����״̬�£����ñ��ӿڴ�ͨ�����ᷢ������\n
����sectionͨ������ͨ��û�а󶨹�����ʱ���ñ��ӿڣ�ͨ�����ܽ�������\n
�������ʹ��filter�������ݣ���������һ��filter�������������Ϊ0���������ݽ���
\param[in] hChannel  ͨ�������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_OpenChannel(HI_HANDLE hChannel);


/**
\brief �ر�ͨ��
\attention \n
��PIDͨ���ر�״̬�£����ñ��ӿڹر�ͨ�����ᷢ������
\param[in] hChannel   ͨ�������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_CloseChannel(HI_HANDLE hChannel);


/**
\brief ��ȡͨ��״̬
\attention \n
������ͨ������������ʱ�̵���
\param[in] hChannel   ͨ�������
\param[out] pstStatus  ָ�����ͣ����ͨ��״̬����μ�::HI_UNF_DMX_CHAN_STATUS_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetChannelStatus(HI_HANDLE hChannel, HI_UNF_DMX_CHAN_STATUS_S *pstStatus);


/**
\brief ��ȡ����ĳPID��ͨ�����
\attention \n
��ͬDEMUX�豸��ͨ������������ͬ��PID�����ñ��ӿ���Ҫָ��DEMUX ID\n
�������ѯ0x1fff�����ϵķǷ�PIDֵ�����򷵻ز����Ƿ�������\n
���û�в�ѯ���κ�ͨ��������Ҫ��ѯ��PID�������ش�����
\param[in] u32DmxId    DEMUX ID��
\param[in] u32Pid      ͨ��PID
\param[out] phChannel  ָ�����ͣ����ͨ��Handle��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_UNMATCH_CHAN  û�в�ѯ��ƥ��ͨ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetChannelHandle(HI_U32 u32DmxId , HI_U32 u32Pid, HI_HANDLE *phChannel);


/**
\brief ��ȡDEMUX�豸���õĿ���ͨ��������
\attention \n
���ص�����Ϊ����ͨ��ʣ��������������ѱ�ʹ�õ�����Ƶͨ��\n
����ͨ����Դͳһ�������Բ���u32DmxId�Ѿ�û�����塣
\param[in] u32DmxId         DEMUX ID��
\param[out] pu32FreeCount   ָ�����ͣ����DEMUX����ͨ����Ŀ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetFreeChannelCount (HI_U32 u32DmxId, HI_U32 *pu32FreeCount);


/**
\brief ��ȡͨ�����ݼ��ű�־
\attention \n
֧��PES�����ź�TS�����ŵĲ�ѯ
\param[in] hChannel   ͨ�������
\param[out] penScrambleFlag   ָ�����ͣ����ͨ�����ݼ��ű�־����μ�::HI_UNF_DMX_SCRAMBLED_FLAG_E
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetScrambledFlag(HI_HANDLE hChannel, HI_UNF_DMX_SCRAMBLED_FLAG_E *penScrambleFlag);


/**
\brief ����һ�����ݹ�����
\attention \n
������������Ϊ16\n
����������������ο�::HI_UNF_DMX_FILTER_ATTR_S\n
����������ʱ��ͬʱʵ�ֶԹ����������ã�������Ҫ���ݹ��ˣ����ù��������Ϊ0����\n
����Ҫ�޸Ĺ��������ԣ��ɵ���HI_UNF_DMX_SetFilterAttr���������޸�\n
֧�����ԵĶ�̬�޸�\n
���������ڹ���Section����ʱ����Ч�����ֽ�Ϊ��1�ֽڼ���4�ֽڡ���18�ֽ�\n
���������ڹ���PES����ʱ����Ч�����ֽ�Ϊ��4�ֽڼ���7�ֽڡ���21�ֽ�\n
������ֻ������ͨ��ͨ�������ݹ��ˣ�����sectionͨ����ECM/EMMͨ����PESͨ��\n
������ɹ���phFilter���ػ�ȡ�Ĺ�����Handle
\param[in] u32DmxId    DEMUX ID��
\param[in] pstFilterAttr   ָ�����ͣ�������������ԡ�
\param[out] phFilter   ָ�����ͣ��������Ĺ�����Handle��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOFREE_FILTER  û�п���filter
\see \n
��
*/
HI_S32 HI_UNF_DMX_CreateFilter(HI_U32 u32DmxId, const HI_UNF_DMX_FILTER_ATTR_S  *pstFilterAttr,
            HI_HANDLE *phFilter);


/**
\brief ���ٴ��������ݹ�����
\attention \n
����������ͨ��ͨ���󶨣�������ͨ���򿪻��߹ر�״̬�£����ñ��ӿ��ͷŹ�����\n
����sectionͨ����ͨ����û���κι�������ʱ�����ٽ������ݣ�����ͨ��û�д�����
\param[in] hFilter  �����������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_DestroyFilter(HI_HANDLE hFilter);


/**
\brief �ͷŰ���ĳ��ͨ���ϵ����й�����
\attention \n
������ͨ���򿪻��߹ر�״̬�£����ñ��ӿ��ͷ�ͨ���ϰ󶨵����й�����
\param[in] hChannel  ͨ�������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_DeleteAllFilter(HI_HANDLE hChannel);


/**
\brief ���ù������Ĺ�������
\attention \n
���������������u32FilterDepth���Ϊ16\n
����������������ο�::HI_UNF_DMX_FILTER_ATTR_S\n
���������ڹ���Section����ʱ����Ч�����ֽ�Ϊ��1�ֽڼ���4�ֽڡ���18�ֽ�\n
���������ڹ���PES����ʱ����Ч�����ֽ�Ϊ��4�ֽڼ���7�ֽڡ���21�ֽ�\n
֧�����ԵĶ�̬�޸�
\param[in] hFilter   �����������
\param[in] pstFilterAttr   ָ�����ͣ�������������ԡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_ATTACHED_FILTER  ����������ͨ���ϣ����ܶ�̬����
\see \n
��
*/
HI_S32 HI_UNF_DMX_SetFilterAttr(HI_HANDLE hFilter, const HI_UNF_DMX_FILTER_ATTR_S *pstFilterAttr );


/**
\brief ��ȡ�������Ĺ�������
\attention \n
�ڹ�����δ����ʱ���øýӿڣ����ش���
\param[in] hFilter   �����������
\param[out] pstFilterAttr   ָ�����ͣ�������������ԡ���μ�::HI_UNF_DMX_FILTER_ATTR_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetFilterAttr(HI_HANDLE hFilter, HI_UNF_DMX_FILTER_ATTR_S *pstFilterAttr );


/**
\brief �󶨹�������ָ����ͨ����
\attention \n
һ��ͨ��ͨ�����԰�һ�����߶�����ݹ����������й�����֮��Ĺ��˹�ϵ�ǻ�\n
��ֻҪ���������κ�һ���������Ĺ�����������ǰ���˵����ݶ���ͨ�����˶�������DMA������\n
��֧������Ƶͨ����POSTͨ���Ĺ�������\n
���ܽ�һ���������ظ��󶨵�һ������ͨ����\n
��������ͨ��������ͬһ·DEMUXʱ�����ܽ��а󶨲���\n
֧��ͨ��ͨ���򿪻��߹ر�״̬�µĹ�������
\param[in] hFilter  �����������
\param[in] hChannel   ͨ�������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_ATTACHED_FILTER  �������Ѿ����ڰ�״̬
\retval ::HI_ERR_DMX_NOT_SUPPORT  ������ͨ����֧�ְ󶨹�����
\see \n
��
*/
HI_S32 HI_UNF_DMX_AttachFilter(HI_HANDLE hFilter, HI_HANDLE hChannel);



/**
\brief ����������ָ��ͨ���Ͻ��
\attention \n
ͨ����û�а󶨹��������н�󶨷���ʧ��\n
��������ͨ��������ͬһ·DEMUXά��ʱ�����ش���\n
֧��ͨ��ͨ���򿪻��߹ر�״̬�µĹ��������

\param[in] hFilter   �����������
\param[in] hChannel  ͨ�������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NOATTACH_FILTER  filterû�а����κ�ͨ����
\retval ::HI_ERR_DMX_UNMATCH_FILTER  filterû�а��ڴ�ͨ����
\see \n
��
*/
HI_S32 HI_UNF_DMX_DetachFilter(HI_HANDLE hFilter, HI_HANDLE hChannel);


/**
\brief ��ȡ���������󶨵�ͨ�����
\attention \n
ÿ��������Ψһ��Ӧһ��ͨ������������û�а��κε�ͨ���ϣ��򷵻�HI_ERR_DMX_NOATTACH_FILTER������
\param[in] hFilter    �����������
\param[out] phChannel   ָ�����ͣ�����������󶨵�ͨ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOATTACH_FILTER  filterû�а����κ�ͨ����
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetFilterChannelHandle(HI_HANDLE hFilter, HI_HANDLE *phChannel);


/**
\brief ��ȡDEMUX�豸���õĿ��й���������
\attention \n
���ص�ǰδ����Ĺ�������Ŀ���ѷ��䵫δ�󶨵�ͨ���ϵĹ�������ͳ��
\param[in] u32DmxId   DEMUX ID��
\param[out]  pu32FreeCount  ָ�����ͣ������ǰδ����Ĺ�������Ŀ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetFreeFilterCount(HI_U32 u32DmxId ,  HI_U32 * pu32FreeCount);


/**
\brief ����һ����Կ��
\attention \n
������Կ�������ù���������·DEMUX������DEMUX����������Կ��
\param[in] u32DmxId   DEMUX ID��
\param[out] phKey      ָ�����ͣ�������뵽����Կ��Handle��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOFREE_KEY  û�п��е���Կ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_CreateDescrambler(HI_U32 u32DmxId, HI_HANDLE *phKey);


/**
\brief ����һ����Կ��,֧��ѡ��߰�ȫCA�ͽ���Э������
\attention \n
����Ǹ߰�ȫCA������Э���Ѿ���Ӳ���������ӿڵ����ñ�����\n
�߰�ȫCA�ĸ���Ҳ����Ӳ�������ģ�ʹ��ǰ���ʹ��HI_UNF_DMX_GetFreeDescramblerCountExt��һ��ʣ��ĸ���
\param[in] u32DmxId   DEMUX ID��
\param[in] pstDesramblerAttr  ��Կ������ָ��  
\param[out] phKey      ָ�����ͣ�������뵽����Կ��Handle��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOFREE_KEY  û�п��е���Կ��
\retval ::HI_ERR_DMX_NOT_SUPPORT  ��֧�ֵ�HI_UNF_DMX_DESCRAMBLER_ATTR_S����
\see \n
��
*/
HI_S32 HI_UNF_DMX_CreateDescramblerExt(HI_U32 u32DmxId, const HI_UNF_DMX_DESCRAMBLER_ATTR_S *pstDesramblerAttr, HI_HANDLE *phKey);

/**
\brief ���ٴ�������Կ��
\attention \n
�����Կ������ͨ���ϣ����ȴ�ͨ���Ͻ����Կ��������ע�ⲻ��ر�ͨ��\n
���û�йر�ͨ���������Կ���Ľ�󶨻����ٲ��������ܵ������ݽ��յĴ���
\param[in] hKey  ��ɾ������Կ��Handle��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DMX_DestroyDescrambler(HI_HANDLE hKey);


/**
\brief ������Կ����ż��Կ��CAϵͳ�õ������ֺ󣬿ɵ��ñ��ӿڽ�ż��Կ���õ�DEMUX����ģ��
\attention \n
pEvenKeyָ��Ҫ���õ�ż��Կ���ݡ����ݹ�16byte��byte������CW1��CW2��������CW16\n
֧����Կ���Ķ�̬���ã���������Կ������������ʱ��������Կֵ\n
��������Կ֮ǰ����Կ�ĳ�ʱֵ����0����ʾ��������
\param[in] hKey  �����õ���Կ�������
\param[in] pu8EvenKey  ָ�����ͣ�ָ��Ҫ���õ�ż��Կ���ݣ�������16���ֽڵ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_SetDescramblerEvenKey(HI_HANDLE hKey, const HI_U8 *pu8EvenKey);


/**
\brief ������Կ��������Կ��CAϵͳ�õ������ֺ󣬿ɵ��ñ��ӿڽ�����Կ���õ�DEMUX����ģ��
\attention \n
pOddKeyָ��Ҫ���õ�����Կ���ݡ�����Կ���ݹ�16byte��byte������CW1��CW2��������CW16\n
֧����Կ���Ķ�̬���ã���������Կ������������ʱ��������Կֵ\n
��������Կ֮ǰ����Կ�ĳ�ʱֵ����0����ʾ��������
\param[in] hKey  �����õ���Կ�������
\param[in] pu8OddKey   ָ�����ͣ�ָ��Ҫ���õ�����Կ���ݣ�������16���ֽڵ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_SetDescramblerOddKey(HI_HANDLE hKey, const HI_U8 *pu8OddKey);


/**
\brief ����Կ����ָ��ͨ��
\attention \n
һ����Կ�����԰󶨵����ͨ���ϣ�ͨ���������ڲ�·��DEMUX\n
���Զ��������͵�ͨ������Կ�����о������ݵĽ���\n
�������ظ�����ͬ��ͬ����Կ����ͬһ��ͨ����
\param[in] hKey    ���󶨵���Կ�������
\param[in] hChannel   ͨ�������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_ATTACHED_KEY  ͨ�����Ѿ���һ����Կ����������
\see \n
��
*/
HI_S32 HI_UNF_DMX_AttachDescrambler(HI_HANDLE hKey, HI_HANDLE hChannel);


/**
\brief ����Կ����ͨ���Ͻ��
\attention \n
���Զ�̬�Ľ��ͨ��ʹ�õ���Կ���������ڰ󶨺������ʱ��ʹ�ô˽ӿڽ����Կ��\n
���ǽ�󶨺���ܵ��¼�������û�б����ţ��������ݴ���\n
�����Կ�������ܸı���Կ����ֵ��������°���Կ������Կֵ��Ȼ���ϴ����õ�ֵ\n
���������н��ţ����˽����Կ��֮�⣬Ҳ����ֱ�ӽ���Կֵȫ������Ϊ0��ʵ��
\param[in] hKey   ����󶨵���Կ�������
\param[in] hChannel  ͨ�������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NOATTACH_KEY  ͨ����û�а��κ���Կ��
\retval ::HI_ERR_DMX_UNMATCH_KEY  ָ������Կ��û�а���ָ����ͨ����
\see \n
��
*/
HI_S32 HI_UNF_DMX_DetachDescrambler(HI_HANDLE hKey, HI_HANDLE hChannel);


/**
\brief ��ȡͨ���󶨵���Կ�����
\attention \n
��ͨ��û�а���Կ��ʱ�����ñ��ӿڷ���HI_ERR_DMX_NOATTACH_KEY������
\param[in] hChannel  Ҫ��ѯ��ͨ�������
\param[out] phKey     ָ�����ͣ����ͨ���󶨵���Կ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOATTACH_KEY  ͨ����û�а��κ���Կ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetDescramblerKeyHandle(HI_HANDLE hChannel, HI_HANDLE *phKey);


/**
\brief ��ȡ������Կ������
\attention \n
��Կ���ڼ�·DEMUX֮�乲�ã����Ե�һ������û�����壬ֻҪ����һ���Ϸ�ֵ�Ϳ����ˡ�
\param[in] u32DmxId   DEMUX ID��
\param[out]  pu32FreeCount   ָ�����ͣ����������Կ����Ŀ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetFreeDescramblerKeyCount(HI_U32 u32DmxId , HI_U32 * pu32FreeCount);

/**
\brief ��ȡ������Կ�������������߰�ȫCA����ͨCA
\attention \n
������Ϊ�߰�ȫCA����ͨCA������ѯ�Ľӿ�ʹ�á�
\param[out]  pu32FreeNormal   ָ�����ͣ����ͨ��CA������Կ����Ŀ
\param[out]  pu32FreeAdvance   ָ�����ͣ�����߰�ȫCA������Կ����Ŀ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_DMX_GetFreeDescramblerCountExt(HI_U32 * pu32FreeNormal, HI_U32 * pu32FreeAdvance);



/**
\brief ��ȡ�������ݵ��������ͨ���ľ��
\attention \n
���øýӿ�ʱ��pu32ChNum��Ϊ�������������ָ��phChannelָ������ĳ��ȣ���ʾҪ��ѯ��ͨ��������\n
ͨ�����������ʼ�����ҳ�ʼֵ����Ϊ��0ֵ��\n
���齫ͨ����������Ϊͨ�����ܸ���, ͨ���ܸ����ο��궨�� ::DMX_TOTALCHAN_CNT\n
���ýӿڵ��óɹ�ʱ��pu32ChNum��Ϊ���������ָ��phChannelָ���������Ч����\n
����ʱ��������ã�ʱ�䵥λΪ���룬����Ϊ0���ȴ�������Ϊ0xffffffffһֱ�ȴ���\n
����������ʱ�䣬����ͨ����û�����ݵ���򷵻صȴ���ʱ����\n
����ȴ�ʱ��Ϊ0������û���κ�ͨ���������򷵻�::HI_ERR_DMX_NOAVAILABLE_DATA

\param[out] phChannel      ָ�����ͣ�ָ��ͨ��������顣���鳤����pu32ChNum����
\param[in/out] pu32ChNum   ָ�����͡�
                           ���룺pChannelHandleָ������ĳ��ȡ�
                           ������ײ���������ͨ������Ŀ����಻�����������ֵ
\param[in] u32TimeOutMs      �ȴ���ʱʱ�䣬��λms
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOAVAILABLE_DATA  û���κ�ͨ�������ݵ���
\retval ::HI_ERR_DMX_TIMEOUT  �ȴ���ʱ
\see \n
��
*/
/*#define HI_UNF_DMX_GetDataHandle(phChannel, pu32ChNum, u32TimeOutMs) \
            HI_UNF_DMX_SelectDataHandle(NULL, *pu32ChNum, phChannel, pu32ChNum, u32TimeOutMs)*/
HI_S32  HI_UNF_DMX_GetDataHandle(HI_HANDLE *phChannel, HI_U32 *pu32ChNum,
            HI_U32 u32TimeOutMs);

/**
\brief ��ѯ����ͨ���Ƿ������ݵ���
\attention \n
������Ϊ::HI_UNF_DMX_GetDataHandle�Ĳ��䣬��Ӧ����ֻ��ע����ͨ�������ݵ������ʱʹ�ô˽ӿ�\n
������ͨ���ľ����phWatchChannelָ����������u32WatchNumָ��\n
phWatchChannelΪNULL,��ѯ����ͨ�������ݵ��������u32WatchNum����Ϊ��0ֵ\n
����ʱ��������ã�ʱ�䵥λΪ���룬����Ϊ0���ȴ�������Ϊ0xffffffffһֱ�ȴ���\n
����������ʱ�䣬����ͨ����û�����ݵ���򷵻صȴ���ʱ����\n
����ȴ�ʱ��Ϊ0������û���κ�ͨ���������򷵻�::HI_ERR_DMX_NOAVAILABLE_DATA

\param[in] phWatchChannel   ָ�����ͣ�ָ�򱻼���ͨ���ľ�����顣���鳤����u32WatchNum����
\param[in] u32WatchNum      ����ͨ���ĸ���
\param[in] phDataChannel    ָ�����ͣ�ָ��������ݵ�ͨ���ľ�����顣���鳤����pu32ChNum����
\param[out] pu32ChNum       ָ�����͡��ײ���������ͨ������Ŀ����಻���������ӵ�ͨ������ֵ
\param[in] u32TimeOutMs     �ȴ���ʱʱ�䣬��λms
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOAVAILABLE_DATA  û���κ�ͨ�������ݵ���
\retval ::HI_ERR_DMX_TIMEOUT  �ȴ���ʱ
\see \n
��
*/
HI_S32  HI_UNF_DMX_SelectDataHandle(HI_HANDLE *phWatchChannel, HI_U32 u32WatchNum,
            HI_HANDLE *phDataChannel, HI_U32 *pu32ChNum, HI_U32 u32TimeOutMs);


/**
\brief ��ָ��ͨ���л�ȡ��������ݰ�
\attention \n
�ڵ��ñ��ӿ�֮ǰ����u32AcquireNum��ֵ��ָ�������ѯ�Ļ�������Ϣ�����Ŀ����Ϣ����������ĳ�����u32AcquireNum����\n
ʵ�ʻ�ȡ�Ļ�������Ϣ��Ŀpu32AcquiredNum��ֵ���ᳬ��u32AcquireNum\n
����sectionͨ����ECM/EMMͨ����ÿ�����ݰ�����һ��������section\n
����PESͨ����ÿ�����ݰ���������������pes���������pes̫�󣬿���Ҫ�ֶ��pes�������\n
����������Ƿ�����ͨ�����ݰ��ṹ��enDataType�ֶ�ָ��\n
����POST���͵�ͨ����ÿ�����ݰ�����һ������������TS����TS����188�ֽ�\n
��������Ƶͨ���ǲ���ͨ���˽ӿڻ�ȡ���ݵģ�����Ƶ���ݻ�ͨ���ڲ��ӿ�ֱ���͸����������н���\n
�������ظ����ô˽ӿڣ�����һ���������ͷţ������ͷű��밴˳�򣬶����ͷŵĵ�ַ�ͳ��ȱ���������һ��\n
����ֻ���ͷ������е����ݰ������ٴ����󣬷��򷵻��ظ����������
\param[in] hChannel            ͨ�������
\param[in] u32AcquireNum       ��������ݰ���������
\param[out] pu32AcquiredNum    ָ�����ͣ����ʵ�����󵽵����ݰ�����
\param[out] pstBuf             ָ�����ͣ�ָ�����ݰ���Ϣ���飬���������pu32AcquiredNum����
\param[in] u32TimeOutMs        �ȴ���ʱʱ�䣬��λΪms
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_DMX_NOAVAILABLE_DATA  ͨ����û����Ч����
\retval ::HI_ERR_DMX_TIMEOUT  �ȴ���ʱ
\retval ::HI_ERR_DMX_REACQUIRE_BUF  �ظ��������ݰ�
\see \n
��
*/
HI_S32  HI_UNF_DMX_AcquireBuf(HI_HANDLE hChannel, HI_U32 u32AcquireNum,
            HI_U32 * pu32AcquiredNum, HI_UNF_DMX_DATA_S *pstBuf,
            HI_U32 u32TimeOutMs);


/**
\brief ���������ݰ������ݺ��ͷ����ݰ�ռ�õĻ���ռ�
\attention \n
���ӿ��ͷŵĻ�����һ����ͨ��::HI_UNF_DMX_AcquireBuf��ȡ�Ļ��������������ĵ�ַ�ͳ��Ȳ��ܸ���\n
�ͷŵĻ�������������С�ڻ�ȡ�Ļ���������
\param[in] hChannel        ͨ�������
\param[in] u32ReleaseNum   �ͷ����ݰ�����
\param[in] pstBuf          ָ�����ͣ�ָ���ͷŻ�������Ϣ���飬������u32ReleaseNum����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_DMX_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_DMX_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DMX_NULL_PTR  ָ�����Ϊ��
\see \n
��
*/
HI_S32  HI_UNF_DMX_ReleaseBuf(HI_HANDLE hChannel, HI_U32 u32ReleaseNum,
            HI_UNF_DMX_DATA_S *pstBuf);

/** @} */  /** <!-- ==== API declaration end ==== */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_DEMUX_H__ */

