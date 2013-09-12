/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_demux.h

Author      : DSM

Description : The poriting interface & macro definition for DEMUX module.

History     :
        2009.12.20          Created         Jason
        2010.01.08          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTNG_DEMUX_H_
#define _ROCME_PORTNG_DEMUX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/


/*SLOT������*/
typedef enum Roc_Slot_Type
{
    ROC_SLOT_TYPE_NULL      = 0x00,  /*used with inject carousel packet only flag*/
    ROC_SLOT_TYPE_SECTION   = 0x01,  /*for section data - Signal every section*/
    ROC_SLOT_TYPE_PES       = 0x02,  /*signal every complete PES packet except when signal_on_every_transport_packet is supplied as a flag*/
    ROC_SLOT_TYPE_RAW       = 0x03,  /*Raw transport packets, signalled every packet*/
    ROC_SLOT_TYPE_PCR       = 0x04,  /*specifies that the data collected on this slot is collected for PCR gathering purposes*/
    ROC_SLOT_TYPE_RESERVE   = 0xFF   /*��չ����*/
}Roc_Slot_Type_e;

/*FILTER������*/
typedef enum Roc_Filter_Type
{
    ROC_FILTER_TYPE_SECTION        = 0x00,  /*Provides 8 byte filter/mask*/
    ROC_FILTER_TYPE_PES            = 0x01,  /*Filter PES*/
    ROC_FILTER_TYPE_TSHEADER       = 0x02,  /*Filter TSHeader*/
    ROC_FILTER_TYPE_PES_STREAMID   = 0x03,  /*Filter PES stream ID*/
    ROC_FILTER_TYPE_NEG_MATCH      = 0x04,  /*Negative Match Mode filtering*/
    ROC_FILTER_TYPE_RESERVE        = 0xFF   /*��չ����*/
}Roc_Filter_Type_e;


/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/


/**************************************************************************
��������: 
            rocme_porting_demux_init
����˵��: 
            DEMUX���ܳ�ʼ�����м����������ʱ���ô˺��������������м��֮ǰ
        �������Ѿ�������DEMUX�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
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
INT32_T rocme_porting_demux_init(void);

/**************************************************************************
��������: 
            rocme_porting_demux_term
����˵��: 
            ж��DEMUX���ܡ�Ŀǰ�˺�������ʵ��Ϊ�ա�
����˵����
    ���������
            void
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ж�سɹ� )
    ʧ�� : -1 �� ������ ( ж��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_demux_term(void);

/**************************************************************************
��������: 
            rocme_porting_slot_query_PID
����˵��: 
            ָ������ͨ���ϣ���ѯһ��PID�Ƿ��Ѿ���ĳ��slot(�����м��ʹ�õ�
        slot���м��֮���slot)ռ�ã���ƽ̨��֧��slot��PID�趨�����ظ�����
        ���ܱ���ʵ�֡�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ pid           ] : ��Ҫ��ѯ��PIDֵ
    ���������
            
��    �أ� 
    ��PIDδ��ռ�� :  0
    ��PID�ѱ�ռ�� : -1
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_query_PID(const INT32_T channel_index,const UINT16_T pid);

/**************************************************************************
��������: 
            rocme_porting_slot_alloc
����˵��: 
            ��ָ��������ͨ�����������һ��slot(ָ��slot�����͡�buff�Ĵ�С)��
        ���ɹ����뵽slot������һ��slot�Ŀ���ID���м����öԴ�slot�Ŀ���Ȩ��
        ��ͨ����ID�Դ�slot�豸�����޸ġ��������ͷŵȾ��������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ slot_type     ] : slot�����ͣ���������:
                                ROC_SLOT_TYPE_NULL     -  used with inject carousel 
                            packet only flag
                                ROC_SLOT_TYPE_SECTION  -  for section data - Signal 
                            every section
                                ROC_SLOT_TYPE_PES      -  signal every complete PES
                            packet except when signal_on_every_transport_packet is 
                            supplied as a flag
                                ROC_SLOT_TYPE_RAW      -  Raw transport packets, si-
                            -gnalled every packet
                                ROC_SLOT_TYPE_PCR      -  specifies that the data c-
                            -ollected on this slot is collected for PCR gathering purposes
                                ROC_SLOT_TYPE_RESERVE  -  ��չ����
             [ buff_size    ] : ��Ҫ���ٵ�slotʹ�õ�buff�Ĵ�С���м������������⣬
                            ������64KB��
    ���������
            ��
��    �أ� 
    �ɹ� : ���뵽��slot����ID ( ����ɹ� )
    ʧ�� : -1 �� ������       ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_alloc(const INT32_T channel_index,const Roc_Slot_Type_e slot_type,const INT32_T buff_size);

/**************************************************************************
��������: 
            rocme_porting_slot_modify
����˵��: 
            ����slot_ID���޸���Ӧ��slot�豸��һ����������(������PIDֵ)��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ pid        ] : ��Ҫ���õ�һ����������ֵ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �޸�slotһ�����������ɹ� )
    ʧ�� : -1 �� ������ ( �޸�slotһ����������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_modify(const INT32_T slot_ID,const UINT16_T pid);

/**************************************************************************
��������: 
            rocme_porting_slot_clear
����˵��: 
            ����slot_ID����������õ�һ����������(�������PIDֵ)��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���slot���������ɹ� )
    ʧ�� : -1 �� ������ ( ���slot��������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_clear(const INT32_T slot_ID);

/**************************************************************************
��������: 
            rocme_porting_slot_start
����˵��: 
            ����һ��slot�豸��ʼ�������ݣ�����ײ�ƽ̨��slot�豸�޴����õ�ʵ�֣�
        ��˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����slot�豸�ɹ� )
    ʧ�� : -1 �� ������ ( ����slot�豸ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_start(const INT32_T slot_ID);

/**************************************************************************
��������: 
            rocme_porting_slot_stop
����˵��: 
            ֹͣһ��slot�豸�������ݣ�����ײ�ƽ̨��slot�豸�޴����õ�ʵ�֣�
        ��˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣslot�豸�ɹ� )
    ʧ�� : -1 �� ������ ( ֹͣslot�豸ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_stop(const INT32_T slot_ID);

/**************************************************************************
��������: 
            rocme_porting_slot_free
����˵��: 
            �ͷŵ���һ��ָ��slot�Ŀ���Ȩ��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �ͷųɹ� )
    ʧ�� : -1 �� ������ ( �ͷ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_free(const INT32_T slot_ID);

/**************************************************************************
��������: 
            rocme_porting_slot_buff_wait
����˵��: 
            ָ������ͨ���������м��ͨ���˷���������ѯ�Ƿ���slot���˵����ݣ�
        ���ҿ������õȴ���ʱʱ�ޣ���������ͨ���Ϲ��˵������ݣ��򷵻ع��˵�
        �����ݵ�slot����ID��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ time_out_ms   ] : ��ʱʱ�䣬��λΪ����(ms)
    ���������
            
��    �أ� 
    �ɹ� : slot����ID   ( �ɹ���ѯ����slot���˵����� )
    ʧ�� : -1 �� ������ ( ��ѯʧ��/slot��time_out_msʱ����δ���˵����� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait(const INT32_T channel_index,const INT32_T time_out_ms);

/**************************************************************************
��������: 
            rocme_porting_slot_buff_wait_multi
����˵��: 
            ָ������ͨ���������м��ͨ���˷���������ѯ�Ƿ���slot���˵����ݣ�
        ���ҿ������õȴ���ʱʱ�ޣ���������ͨ���Ϲ��˵������ݣ��򽫻�ȡ����
        �ݵ�slot����slot_ID_ar�����Ա,���޸�*countΪ�Ѿ���ȡ�����ݵ�slot������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ time_out_ms   ] : ��ʱʱ�䣬��λΪ����(ms)
            [ *count        ] : slot_ID_ar�����Ա������
    ���������
            [ slot_ID_ar    ] : ��ȡ�����ݵ�slot
            [ *count        ] : �Ѿ���ȡ�����ݵ�slot�ĸ���
��    �أ� 
    �ɹ� : 0
    ʧ�� : -1 �� ������ ( ��ѯʧ��/slot��time_out_msʱ����δ���˵����� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait_multi(const INT32_T channel_index, INT32_T *slot_ID_ar, INT32_T *count , const INT32_T time_out_ms);

/**************************************************************************
��������: 
            rocme_porting_slot_buff_get
����˵��: 
            ��ָ��slot��buff�еĸ���(��ȡ)��ָ�����ȵ����ݣ��м��ֻ���ڵ���
        ��rocme_porting_slot_buff_wait�󣬲Ż�ʹ�ô˺����жϹ��˵����ݵĹ�����
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ *buff_ptr  ] : �洢��ȡ�������ݵ�buff��ͷָ��
            [ buff_size  ] : ��Ҫ��ȡ�����ݵĳ��ȣ����洢buff�ĳ���
    ���������
            [ *data_size ] : ʵ����ȡ�������ݵĳ���
��    �أ� 
    �ɹ� : 0            ( ��ȡ���ݳɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_get(const INT32_T slot_ID, UINT8_T *buff_ptr, const UINT32_T buff_size, UINT32_T *data_size);

/**************************************************************************
��������: 
            rocme_porting_slot_buff_read
����˵��: 
            ��ָ����slot��buff�ж�ȡ���ݣ���ȡ���ݺ�Ҫ�����buff���м����
        Ҫ��slot��buff�е����ݶ���2��buff�У��ֱ���data0��data1����ȡ����ʱ
        ���Ƚ����ݶ���data0�У���data0�������ٽ����ݶ�ȡ��data1�У����ռ䲻
        ��ʱ�����ض�ȡʧ�ܡ�
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ *p_data0   ] : �洢������0��ͷָ��
            [ size0      ] : �洢������0�ĳ���
            [ *p_data1   ] : �洢������1��ͷָ��
            [ size1      ] : �洢������1�ĳ���
    ���������
            [ *datasize  ] : ʵ�ʶ�ȡ�������ݳ���
��    �أ� 
    �ɹ� : 0            ( ��ȡ���ݳɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_read(const INT32_T slot_ID, UINT8_T *p_data0, UINT32_T size0, UINT8_T *p_data1, UINT32_T size1, UINT32_T *datasize);

/**************************************************************************
��������: 
            rocme_porting_slot_buff_flush
����˵��: 
            ���ָ����slot��buff��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���ָ��slot��buff�ɹ� )
    ʧ�� : -1 �� ������ ( ���ָ��slot��buffʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_flush(const INT32_T slot_ID);

/**************************************************************************
��������: 
            rocme_porting_filter_alloc
����˵��: 
            ��ָ��������ͨ�����������һ��filter(ָ��filter������)�����ɹ���
        �뵽filter������һ��filter�Ŀ���ID���м����öԴ�filter�Ŀ���Ȩ����
        ͨ����ID�Դ�filter�豸�����޸ġ��������ͷŵȾ��������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ filter_type   ] : filter�����ͣ���������:
                                ROC_FILTER_TYPE_SECTION       -  Provides 8 byte filter/mask
                                ROC_FILTER_TYPE_PES           -  Filter PES
                                ROC_FILTER_TYPE_TSHEADER      -  Filter TSHeader
                                ROC_FILTER_TYPE_PES_STREAMID  -  Filter PES stream ID
                                ROC_FILTER_TYPE_NEG_MATCH     -  Negative Match Mode filtering
                                ROC_FILTER_TYPE_RESERVE       -  ��չ����
    ���������
            ��
��    �أ� 
    �ɹ� : ���뵽��filter����ID ( ����ɹ� )
    ʧ�� : -1 �� ������         ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_alloc(const INT32_T channel_index,const Roc_Filter_Type_e filter_type);

/**************************************************************************
��������: 
            rocme_porting_filter_associate
����˵��: 
            ��ָ����slot��filter����������
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����ɹ� )
    ʧ�� : -1 �� ������ ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_associate(const INT32_T filter_ID,const INT32_T slot_ID);

/**************************************************************************
��������: 
            rocme_porting_filter_disassociate
����˵��: 
            ��ָ����slot��filter�Ͽ���
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��        
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �Ͽ��ɹ� )
    ʧ�� : -1 �� ������ ( �Ͽ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_disassociate(const INT32_T filter_ID,const INT32_T slot_ID);

/**************************************************************************
��������: 
            rocme_porting_filter_modify
����˵��: 
            ����filter_ID���޸���Ӧ��filter�豸�Ķ�����������(������cofe��maskֵ)��
        ���磬����TDT������������Ϊ:
        cafe[8]��ֵΪ{0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        mask[8]��ֵΪ{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00}.
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ *cofe      ] : ������������ͷָ��
            [ c_size     ] : ����������������
            [ *mask      ] : ����������������ֵͷָ��
            [ m_size     ] : ����������������ֵ����
            [ *nega      ] : ��������������ģʽ��ʶ
            [ m_nega     ] : ��������������ģʽ��ʶ����
    ���������

��    �أ� 
    �ɹ� : 0            ( �޸Ķ������������ɹ� )
    ʧ�� : -1 �� ������ ( �޸Ķ�����������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_modify(const INT32_T filter_ID,
                                    const UINT8_T*cofe,const UINT8_T c_size,
                                    const UINT8_T*mask,const UINT8_T m_size,
                                    const UINT8_T*nega,const UINT8_T m_nega);

/**************************************************************************
��������: 
            rocme_porting_filter_start
����˵��: 
            ����filter_ID������һ��filter�豸��ʼ������
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( filter�豸�����ɹ� )
    ʧ�� : -1 �� ������ ( filter�豸����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_start(const INT32_T filter_ID);

/**************************************************************************
��������: 
            rocme_porting_filter_stop
����˵��: 
            ����filter_ID��ֹͣһ��filter�豸�Ĺ�����
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( filter�豸ֹͣ�ɹ� )
    ʧ�� : -1 �� ������ ( filter�豸ֹͣʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_stop(const INT32_T filter_ID);

/**************************************************************************
��������: 
            rocme_porting_filter_free
����˵��: 
            �ͷŵ���һ��fitler�豸�Ŀ���Ȩ��
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �ͷųɹ� )
    ʧ�� : -1 �� ������ ( �ͷ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_free(const INT32_T filter_ID);


#ifdef __cplusplus
}
#endif

#endif
