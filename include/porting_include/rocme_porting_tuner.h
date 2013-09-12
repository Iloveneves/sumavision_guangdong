/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_tuner.h

Author      : DSM

Description : The poriting interface & macro definition for TUNER module.

History     :
              2009.12.20          Created         Jason
              2010.01.10          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTING_TUNER_H_
#define _ROCME_PORTING_TUNER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/
/*  refer Digital video broadcasting:  specification for Chinese service information (SI) : 
                cable_delivery_system_descriptor( ),
                satellite_delivery_system_descriptor( ),
                terrestrial_delivery_system_descriptor( ).                 */ 

/*��Ƶͷ����*/
typedef enum Roc_Tuner_Type
{
    ROC_TUNER_TYPE_CABLE            = 0x00,  /*��������    */
    ROC_TUNER_TYPE_TERRAIN          = 0x01,  /*������������*/
    ROC_TUNER_TYPE_SATELITE         = 0x02,  /*�����ź�����*/
    ROC_TUNER_TYPE_RESERVE          = 0xFF   /*Ԥ��*/
}Roc_Tuner_Type_e;

/*��ǰ������������*/
typedef enum Roc_Signal_FEC_Outer
{
    ROC_SIGNAL_FEC_OUTER_NONE       = 0x0000,  /*δ����     */
    ROC_SIGNAL_FEC_OUTER_WITHOUT    = 0x0001,  /*��FEC����  */
    ROC_SIGNAL_FEC_OUTER_RS         = 0x0010,  /*RS(204/188)*/
    ROC_SIGNAL_FEC_OUTER_RESERVE    = 0xFF     /*Ԥ��*/
}Roc_Signal_FEC_Outer_e;

/*��ǰ������������*/
typedef enum Roc_Signal_FEC_Inner
{
    ROC_SIGNAL_FEC_INNER_NONE                   = 0x0000,  /*δ����     */
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_1_2        = 0x0001,  /*�������1/2*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_2_3        = 0x0010,  /*�������2/3*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_3_4        = 0x0011,  /*�������3/4*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_5_6        = 0x0100,  /*�������5/6*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_7_8        = 0x0101,  /*�������7/8*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_WITHOUT    = 0x1111,  /*�޾������ */
    ROC_SIGNAL_FEC_INNER_RESERVE                = 0x0110   /*Ԥ��*/
}Roc_Signal_FEC_Inner_e;

/*���ߵ��Ʒ�ʽ����*/
typedef enum Roc_CableTnr_Modulation
{
    ROC_CABLETNR_QAM_NONE     = 0x00,  /*δ���� */
    ROC_CABLETNR_QAM_16_T     = 0x01,  /*16 -QAM*/
    ROC_CABLETNR_QAM_32_T     = 0x02,  /*32 -QAM*/
    ROC_CABLETNR_QAM_64_T     = 0x03,  /*64 -QAM*/
    ROC_CABLETNR_QAM_128_T    = 0x04,  /*128-QAM*/
    ROC_CABLETNR_QAM_256_T    = 0x05,  /*256-QAM*/
    ROC_CABLETNR_QAM_RESERVE  = 0xFF   /*Ԥ��*/
}Roc_CableTnr_Modulation_e;

/*�����źŲ���-������ʽ����*/
typedef enum Roc_SateliteTnr_Polarization
{
    ROC_SATELITETNR_POLARIZATION_HORIZONTAL       = 0x00,  /*����   ˮƽ����*/
    ROC_SATELITETNR_POLARIZATION_VERTICAL         = 0x01,  /*����   ��ֱ����*/
    ROC_SATELITETNR_POLARIZATION_LEFT_ROTUNDITY   = 0x10,  /*���ͼ��� ���Բ*/
    ROC_SATELITETNR_POLARIZATION_RIGHT_ROTUNDITY  = 0x11   /*���ͼ��� �Ұ�Բ*/
}Roc_SateliteTnr_Polarization_e;

/*���ǵ��Ʒ�ʽ����*/
typedef enum Roc_SateliteTnr_Modulation
{
    ROC_SATELITETNR_SATEMODUL_NONE          = 0x00,  /*δ����*/
    ROC_SATELITETNR_QPSK_T                  = 0x01,  /*QPSK  */
    ROC_SATELITETNR_SATEMODUL_RESERVE       = 0xFF   /*Ԥ��*/
}Roc_SateliteTnr_Modulation_e;

/*���洫��ϵͳ��������*/
typedef enum Roc_TerrainTnr_Bandwidth
{
    ROC_TERRAINTNR_BANDWIDTH_8MHz           = 0x000,  /*8MHz����*/
    ROC_TERRAINTNR_BANDWIDTH_7MHz           = 0x001,  /*7MHz����*/
    ROC_TERRAINTNR_BANDWIDTH_6MHz           = 0x010,  /*6MHz����*/
    ROC_TERRAINTNR_BANDWIDTH_RESERVE        = 0x111   /*Ԥ��*/
}Roc_TerrainTnr_Bandwidth_e;

/*���洫��ϵͳʹ�õ�����ģʽ����*/
typedef enum Roc_TerrainTnr_Constellation
{
    ROC_TERRAINTNR_CONSTELLATION_QPSK       = 0x00,  /*QPSK  */
    ROC_TERRAINTNR_CONSTELLATION_16QAM      = 0x01,  /*16-QAM*/
    ROC_TERRAINTNR_CONSTELLATION_64QAM      = 0x10,  /*64-QAM*/
    ROC_TERRAINTNR_CONSTELLATION_RESERVE    = 0x11   /*Ԥ��*/
}Roc_TerrainTnr_Constellation_e;

/*���洫��ϵͳ�ֲ�����*/
typedef enum Roc_TerrainTnr_Hierarchy_info
{
    ROC_TERRAINTNR_HIERARCHY_NONE           = 0x000,  /*δ�ֲ�*/
    ROC_TERRAINTNR_HIERARCHY_ALPHA_1        = 0x001,  /*��=1  */
    ROC_TERRAINTNR_HIERARCHY_ALPHA_2        = 0x010,  /*��=2  */
    ROC_TERRAINTNR_HIERARCHY_ALPHA_4        = 0x011,  /*��=4  */
    ROC_TERRAINTNR_HIERARCHY_RESERVE        = 0x111   /*Ԥ��*/
}Roc_TerrainTnr_Hierarchy_info_e;

/*���洫��ϵͳ�����������*/
typedef enum Roc_TerrainTnr_Guard_Interval
{
    ROC_TERRAINTNR_GUARD_INTERVAL_1_32      = 0x00,  /*���ֵ1/32*/
    ROC_TERRAINTNR_GUARD_INTERVAL_1_16      = 0x01,  /*���ֵ1/16*/
    ROC_TERRAINTNR_GUARD_INTERVAL_1_8       = 0x10,  /*���ֵ1/8 */
    ROC_TERRAINTNR_GUARD_INTERVAL_1_4       = 0x11,  /*���ֵ1/4 */
    ROC_TERRAINTNR_GUARD_INTERVAL_RESERVE   = 0xFF   /*Ԥ��*/
}Roc_TerrainTnr_Guard_Interval_e;

/*���洫��ϵͳOFDM֡�е��ز�������*/
typedef enum Roc_TerrainTnr_Transmission_mode
{
    ROC_TERRAINTNR_TRANSMISSION_MODE_2K         = 0x00,  /*2k ģʽ*/
    ROC_TERRAINTNR_TRANSMISSION_MODE_8K         = 0x01,  /*8k ģʽ*/
    ROC_TERRAINTNR_TRANSMISSION_MODE_RESERVE    = 0x11   /*Ԥ��*/
}Roc_TerrainTnr_Transmission_mode_e;

/*���߸�Ƶͷ�������*/
typedef struct Roc_CableTnr_Param
{
    UINT32_T                            frequency;    /*Ƶ��(��λ KHz)*/
    UINT32_T                            symbol_rate;  /*������(��λ Ksymbol/s)*/
    Roc_CableTnr_Modulation_e           modulation;   /*�����źŵ��Ʒ�ʽ*/   
    Roc_Signal_FEC_Outer_e              FEC_outer;    /*��ǰ�������룬�ݲ�ʹ��*/
    Roc_Signal_FEC_Inner_e              FEC_inner;    /*��ǰ�������룬�ݲ�ʹ��*/
    INT32_T                             reserved;     /*Ԥ��*/
}Roc_CableTnr_Param_t;

/*���Ǹ�Ƶͷ�������*/
typedef struct Roc_SateliteTnr_Param
{
    UINT32_T                            frequency;         /*Ƶ��(��λ KHz)*/
    UINT32_T                            symbol_rate;       /*������(��λ Ksymbol/s)*/
    Roc_SateliteTnr_Modulation_e        modulation;        /*�����źŵ��Ʒ�ʽ*/
    UINT16_T                            orbital_position;  /*���λ��*/
    ROC_BOOL                            west_east_flag;    /*������־*/
    Roc_SateliteTnr_Polarization_e      polarization;      /*������ʽ*/
    Roc_Signal_FEC_Inner_e              FEC_inner;         /*��ǰ��������*/
    INT32_T                             reserved;          /*Ԥ��*/
}Roc_SateliteTnr_Param_t;

/*���沨��Ƶͷ�������*/
typedef struct Roc_TerrainTnr_Param
{
    UINT32_T                            centre_frequency;       /*����Ƶ��(��λ KHz)*/
    Roc_TerrainTnr_Bandwidth_e          bandwidth;              /*����*/
    Roc_TerrainTnr_Constellation_e      constellation;          /*����ģʽ*/
    Roc_TerrainTnr_Hierarchy_info_e     hierarchy_information;  /*�ֲ���Ϣ*/
    Roc_Signal_FEC_Inner_e              code_rate;              /*��ǰ��������*/
    Roc_TerrainTnr_Guard_Interval_e     guard_interval;         /*�������*/
    Roc_TerrainTnr_Transmission_mode_e  transmission_mode;      /*�ز�ģʽ*/
    ROC_BOOL                            other_frequency_flag;   /*�����Ƿ�ʹ��������Ƶ��.ROC_TRUE��ʹ��һ����������Ƶ��;ROC_FALSE��δʹ������Ƶ��*/
    INT32_T                             reserved;               /*Ԥ��*/
}Roc_TerrainTnr_Param_t;

/*��Ƶͷ����*/
typedef struct Roc_Tuner_Param
{
    Roc_Tuner_Type_e            type;       /*��Ƶͷ����*/      
    union{
        Roc_CableTnr_Param_t    cab_param;  /*���߸�Ƶͷ����*/
        Roc_SateliteTnr_Param_t sat_param;  /*���Ǹ�Ƶͷ����*/
        Roc_TerrainTnr_Param_t  ter_param;  /*�����Ƶͷ����*/
    }param;                                 /*��Ƶͷ����*/
}Roc_Tuner_Param_t;

/*�ź������ʽṹ����*/
typedef struct Roc_Siganl_ber
{
    UINT32_T    total_counter;  /*��λʱ����Ԫ���������*/
    UINT32_T    error_counter;  /*��λʱ���ڳ��ֵ�������*/
}Roc_Siganl_ber_t;

/*�ź���Ϣ�ṹ����*/
typedef struct Roc_Signal_Info
{
    UINT32_T            signal_strength;  /*�ź�ǿ��*/
    UINT32_T            signal_snr;       /*�ź������/�ź�����*/
    Roc_Siganl_ber_t    signal_ber;       /*�ź�������*/
    UINT32_T						signal_RFLevle;   /*�źŵ�ƽֵ*/
}Roc_Signal_Info_t;

/*��Ƶͷ����״̬����*/
typedef enum Roc_Tuner_State
{
    ROC_TUNER_STATE_UNKNOWN     = 0x00,  /*δ֪״̬      */
    ROC_TUNER_STATE_IDLE        = 0x01,  /*����״̬      */
    ROC_TUNER_STATE_STANDBY     = 0x02,  /*����״̬      */
    ROC_TUNER_STATE_UNLOCK      = 0x03,  /*�ź�δ����״̬*/
    ROC_TUNER_STATE_LOST        = 0x04,  /*�źŶ�ʧ״̬  */
    ROC_TUNER_STATE_SCANNING    = 0x05,  /*�ź�������״̬*/
    ROC_TUNER_STATE_LOCKED      = 0x06,  /*�ź�����״̬  */
    ROC_TUNER_STATE_RESERVE     = 0xFF   /*Ԥ��*/
}Roc_Tuner_State_e;


/**************************************************************************
��������: 
            rocme_porting_tuner_init
����˵��: 
            ��Ƶͷ�豸��ʼ�����м����������ʱ���ô˺��������������м��֮ǰ
        �������Ѿ������˸�Ƶͷ�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
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
INT32_T rocme_porting_tuner_init( void );

/**************************************************************************
��������: 
            rocme_porting_tuner_scanning
����˵��: 
            ��Ƶͷ�������ú���������ָ���Ĳ���������ָ��������ͨ���ϵĸ�Ƶͷ����
        ��ָ����Ƶ�㣬��Ҫ��ͬ����Ƶ��Ҫ����ȷ���ò����󣬺����������ء�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���ĸ�ƵͷID)
            [ tnr_param     ] : ��Ƶͷ����,��������:
                                type  -  ��Ƶͷ����
                                cab_param  -  typeΪ���߸�Ƶͷʱ���˲�����Ч
                                sat_param  -  typeΪ���Ǹ�Ƶͷʱ���˲�����Ч
                                ter_param  -  typeΪ�����Ƶͷʱ���˲�����Ч
    ���������
            [ tnr_state     ] : ��Ƶ������ĸ�Ƶͷ�Ĺ���״̬ 
��    �أ� 
    �ɹ� : 0            ( ��Ƶ���ò����ɹ� )
    ʧ�� : -1 �� ������ ( ��Ƶ���ò���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_tuner_scanning( const INT32_T channel_index,const Roc_Tuner_Param_t tnr_param );

/**************************************************************************
��������: 
            rocme_porting_tuner_get_state
����˵��: 
           ��ѯָ������ͨ���ϵĸ�Ƶͷ�ĵ�ǰ״̬��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���ĸ�ƵͷID)
    ���������
            [ tnr_state     ] : ��Ƶͷ�ĵ�ǰ����״̬ 
��    �أ� 
    �ɹ� : 0            ( ��ѯ��Ƶͷ״̬�ɹ� )
    ʧ�� : -1 �� ������ ( ��ѯ��Ƶͷ״̬ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_tuner_get_state( const INT32_T channel_index,Roc_Tuner_State_e *tnr_state );

/**************************************************************************
��������: 
            rocme_porting_tuner_get_signal_info
����˵��: 
           ��ȡָ������ͨ���ϵĸ�Ƶͷ�ĵ�ǰ�ź���Ϣ�������ź�ǿ�ȡ�����Ⱥ�
       �����ʡ�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���ĸ�ƵͷID)
    ���������
            [ signal_info   ] : ��Ƶͷ�ĵ�ǰ�ź���Ϣ������:
                                signal_strength  -  �ź�ǿ��
                                signal_snr       -  �ź������/�ź�����
                                signal_ber       -  �ź�������
��    �أ� 
    �ɹ� : 0            ( ��ѯ��Ƶͷ��Ϣ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ѯ��Ƶͷ��Ϣʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_tuner_get_signal_info( const INT32_T channel_index,Roc_Signal_Info_t *signal_info );


#ifdef __cplusplus
}
#endif

#endif
