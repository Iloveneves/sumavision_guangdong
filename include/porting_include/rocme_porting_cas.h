/******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_cas.h

Author      : 

Description : The poriting interface & macro definition for CAS module.
              ��ͷ�ļ�����3��������:
              1. �������ṹ�嶨��
              2. Ҫ������У�ʵ����CAS���̵�CAģ�飬����������ת���ṩ�Ľӿڣ�
                 �м�������Լ��Ľ�������̽��е���
              3. �м��ʵ�ֵĽӿڣ��������У�ʵ����CAS���̵�CAģ�飬��������
                 ��ת������

              ��INT32_T���ͷ���ֵ�������ر�˵����0��ʾ�ɹ���������ʾ����š�
              �㶫��Ŀ���صĴ������ο�ʡ���淶����ض��塣
              
History     :
              2010.01.26          Created         
              2010.06.08          modify EMM&ECM API
              2011.02.10          modify for guangdong
*******************************************************************************/

#ifndef _ROCME_PORTING_CAS_H_2010_01_26_
#define _ROCME_PORTING_CAS_H_2010_01_26_


#include "rocme_porting_typedef.h"
#include "rocme_porting_event.h"

/*++++++++++++++++++++++++++++    ��������    ++++++++++++++++++++++++++++*/

/* ������Ƴ��� */
#define ROC_CAS_MAX_WALLET_COUNT                  4     /* ÿ����Ӫ�����Ǯ����*/
#define ROC_CAS_MAX_TVS_COUNT                     5     /* �����Ӫ�̸��� */
#define ROC_CAS_MAX_ENTITLE_COUNT               300     /* �����Ȩ��¼���� */
#define ROC_CAS_MAXLEN_PRODUCT_NAME              21     /* ��Ĳ�Ʒ����,���20���ַ�+\0 */
#define ROC_CAS_MAXLEN_SERVICE_NAME              21     /* ���ҵ������,���20���ַ�+\0 */
#define ROC_CAS_MAXLEN_TVSINFO                   33     /* ��Ӫ����Ϣ����,����\0*/
#define ROC_CAS_MAXLEN_CARDID                    21     /* ������ܿ���,���20���ַ�+\0 */
#define ROC_CAS_MAXLEN_PROVIDERNAME              21     /* ���CA��������,���20���ַ�+\0 */
#define ROC_CAS_MAXLEN_VERSION                   21     /* ��汾��,���20���ַ�+\0 */
#define ROC_CAS_MAXLEN_IPP                      250     /* ���IPP��Ŀ���� */
#define ROC_CAS_MAXLEN_EMAIL_TITLE               21     /* ��ʼ�����,20���ַ�+\0*/
#define ROC_CAS_MAXLEN_EMAIL_CONTENT           3073     /* ��ʼ�����,3072���ַ�+\0*/
#define ROC_CAS_MAXLEN_EMAIL_SEND_NAME           11     /* ����ʼ�����������,10���ַ�+\0*/

/* INT32_T���ͷ���ֵ�Ĵ���Ŷ��� */
#define ROC_CAS_OK                                0    /* �ɹ� */
#define ROC_CAS_UNIMPL_INF                       -1    /* δʵ�ֵĽӿ� */

/* �������ͣ�rocme_porting_ChangeLanguageʹ�� */
#define ROC_CAS_LANG_CHN_SIM                   1    /* ��������(Ĭ��) */
#define ROC_CAS_LANG_ENG                       2    /* Ӣ�� */

/*CA�ṩ��*/
typedef enum ROC_CAS_PROVIDER
{
    ROC_CAS_SUMAVISION      = 0x00,     /* ������Ѷ     */
    ROC_CAS_NDS             = 0x01,     /* NDS          */
    ROC_CAS_IRDETO          = 0x02,     /* Irdeto       */
    ROC_CAS_CONAX           = 0x03,     /* CONAX        */
    ROC_CAS_NAGRAVISION     = 0x04,     /* Nagravision  */
    ROC_CAS_VIACESS         = 0x05,     /* Viacess      */
    ROC_CAS_NOVEL           = 0x06,     /* �����Ӳ�     */
    ROC_CAS_DVN             = 0x07,     /* ���         */
    ROC_CAS_CTI             = 0x08,     /* ��ͨ         */
    ROC_CAS_RESERVE0,
    ROC_CAS_RESERVE1
}ROC_CAS_PROVIDER_e;

typedef enum ROC_CA_EVENT
{
    ROC_CA_EVENT_IPP                = 11701,
    ROC_CA_EVENT_HIDE_PROMPT_MSG    = 11702,
    ROC_CA_EVENT_RESERVE    
}ROC_CA_EVENT_e;


/*++++++++++++++++++++++++++++    �ṹ�嶨��    ++++++++++++++++++++++++++++*/


/* ��Ӫ����Ϣ */
typedef struct _Roc_OperatorInfo{
    UINT16_T m_wTVSID;                              /* ��Ӫ�̵��ⲿ��� */
    INT8_T   m_szTVSName[ROC_CAS_MAXLEN_TVSINFO];   /* ��Ӫ�����ƻ�������Ϣ,CA��֧�ִ�����m_szTVSName[0]=0*/
    UINT8_T  m_byServiceStatus;                     /* ��Ӫ�̶Դ˿��ķ���״̬��0����������1���ƹ��� */
}Roc_OperatorInfo;

/* ��Ȩ��Ϣ */
typedef struct _Roc_ServiceEntitle{
    UINT16_T    m_wProductID;                       /* ��Ʒ�� */
    UINT32_T    m_tStartTime;                       /* ��ʼʱ�� */
    UINT32_T    m_tEndTime;                         /* ����ʱ�䣬��Щcasû�У���Щ��Ӫ��Ҫ����ʾ */
    INT8_T      m_ProductName[ROC_CAS_MAXLEN_PRODUCT_NAME];                  /* ��Ʒ���ơ�û����m_ProductName[0]��ֵΪ0*/
}Roc_ServiceEntitle;/*��ͨ��Ʒ��Ȩ*/


/* mail ͷ��Ϣ */
typedef struct _Roc_EmailInfo{
    UINT32_T    m_dwVersion;                                    /* �ʼ���ʶ */
    INT8_T      m_szSenderName[ROC_CAS_MAXLEN_EMAIL_SEND_NAME]; /* ��������������CAû�д˽ṹ,����Ϊ��Ӫ��ID*/
    UINT8_T     m_Status;                                       /* �ʼ���״̬��0δ���ʼ��� 1�Ѷ��ʼ� */
    INT8_T      m_szTitle[ROC_CAS_MAXLEN_EMAIL_TITLE];          /* �ʼ������ݣ���'\0'���ַ��������ʼ����ݿ�ͷ��ȡһ���� */
    UINT16_T    m_wImportance;                                  /* ��Ҫ�ԡ�0��ͨ,1��Ҫ����CAû�д˽ṹ����Ϊ��ͨ */
    UINT32_T    m_dwCreateTime;                                 /* �ʼ�����ʱ��,time_t��ʽ*/
}Roc_EmailInfo;

/* mail ��Ϣ */
typedef struct _Roc_EmailContent{
    INT8_T      m_szEmail[ROC_CAS_MAXLEN_EMAIL_CONTENT];    /* �ʼ����ݣ���'\0'���ַ��� ��������CA����,���֧��(ROC_CAS_MAXLEN_EMAIL_CONTENT)3073���ֽڵ��ʼ�*/
}Roc_EmailContent;

/* ����ecm pid�ṹ */
typedef struct _Roc_ServiceInfo{
    UINT16_T    m_wEcmPid;                          /* ��Ŀ��Ӧ������Ϣ��PID��������Ѷֻ��Ҫ�����Ա��������Աֵ���⡣����ͬ����Ҫ������Աֵ�� */                               
    UINT8_T     m_byServiceNum;                     /* ��ǰPID�µĽ�Ŀ���� */
    UINT16_T    m_wServiceID[4];                    /* ��ǰPID�µĽ�ĿID�б� */       
}Roc_ServiceInfo;

/* ����ecm pid, ���pid����Ϣ */
typedef struct _Roc_ComponentEcmInfo
{
    UINT16_T            component_pid;          /*���PID*/
    UINT8_T             component_type;         /*������ͣ�����mpeg1��mpeg2��h.264��Ƶ��mpeg1��3�㣨mp3����ac3��Ƶ�����ݹ㲥��˽�����͵ȵ�*/
    UINT16_T            ca_system_id;           /*CAϵͳ��ʶ��,����ͨ��CAУ��,������ʱ��0*/
    UINT16_T            ecm_pid;                /*��\��Ƶ��ECM PID,������ʱ��0*/
    UINT8_T             ca_private_data_len;    /*CA�������ڵ�˽�����ݳ���,��\��Ƶ������ʱΪ0*/
    UINT8_T             *ca_private_data;       /*CA�������ڵ�˽������,��\��Ƶ������ʱΪNULL*/
}Roc_ComponentEcmInfo;

/* ����ecm pid, ���pid����Ϣ */
typedef struct _Roc_ComponentEmmInfo
{
    UINT16_T            ca_system_id;       /*CAϵͳ��ʶ��,����ͨ��CAУ��*/
    UINT16_T            emm_pid;            /*Emm PID*/
    UINT8_T             ca_private_data_len;/*CA�������ڵ�˽�����ݳ���,û��˽������ʱ��0*/
    UINT8_T             *ca_private_data;   /*CA�������ڵ�˽������*/
}Roc_ComponentEmmInfo;


/* ipp������ݽṹ */
typedef struct _Roc_CAIpp{
    UINT16_T    m_wTVSID;                           /* ��Ӫ�̱�� */
    UINT16_T    m_wProdID;                          /* ��ƷID */
    UINT8_T     m_bySlotID;                         /* Ǯ��ID */
    INT8_T      m_szProdName[ROC_CAS_MAXLEN_PRODUCT_NAME];      /* ��Ʒ���� */
    UINT32_T    m_tStartTime;                       /* ��ʼʱ�䣬time_t��ʽ */
    UINT32_T    m_tEndTime;                         /* ����ʱ��, time_t��ʽ */
    UINT16_T    m_wCurTppTapPrice;                  /* ��ǰ�Ĳ��ش�����¼��۸�(��)���۸�����ֵΪ0 */
    UINT16_T    m_wCurTppNoTapPrice;                /* ��ǰ�Ĳ��ش�������¼��۸�(��)���۸�����ֵΪ1 */
    UINT16_T    m_wCurCppTapPrice;                  /* ��ǰ��Ҫ�ش�����¼��۸�(��)���۸�����ֵΪ2 */
    UINT16_T    m_wCurCppNoTapPrice;                /* ��ǰ��Ҫ�ش�������¼��۸�(��)���۸�����ֵΪ3 */
    UINT8_T     m_byIppStatus;                      /* Ipp��Ʒ״̬:��4λ����:0--IPPT����;1--IPPV; ��4λ����:0--δ����;1--�Ѷ���*/
}Roc_CAIpp;

typedef struct _Roc_CAViewedIpp{
    UINT16_T    m_wTVSID;                           /* ��Ӫ�̱�� */
    INT8_T      m_szProdName[ROC_CAS_MAXLEN_PRODUCT_NAME];   /* ��Ʒ���ơ�������Ѷ�У�����ͬ���ޡ� */
    UINT32_T    m_tStartTime;                       /* ��ʼʱ�䣬time_t��ʽ�� */
    UINT32_T    m_tEndTime;                         /* �������� */
    UINT16_T    m_wBookedPrice;                     /* Ԥ���۸�*/
    UINT8_T     m_byBookedPriceType;                /* Ԥ���۸�����:0:TppTap;1:TppNoTap;2:CppTap;3:CppNoTap; */
}Roc_CAViewedIpp;

typedef struct _Roc_TVSSlotInfo{
    UINT32_T m_dwBalance;            /* �ѻ���,��λ:�� */
    UINT32_T m_dwRemainder;          /* ʣ��,��λ:��   */
    UINT16_T m_wSlotID;              /* Ǯ��ID������0xff��ʾ������Ч������ʾ��TF�ĸ���Чֵ��������Ѷ�ĸ���Чֵ */
}Roc_TVSSlotInfo;

/*----------------- Ӧ���㲥��ǿ����̨��������ݽṹ --------------*/

/*
Ƶ�ʺͷ�����bcd���뷽ʽ����:
    ��Ƶ��Ϊ355000KHz����355.0000MHz�����Ӧ��m_dwFrequency��ֵӦΪ0x03550000��
    ��������Ϊ6875KHz����6.8750MHz�����Ӧ��m_symbol_rate��ֵӦΪ0x00068750��

���Ʒ�ʽȡֵ:
        0               Reserved
        1               QAM16
        2               QAM32
        3               QAM64
        4               QAM128
        5               QAM256
        6��255  Reserved
*/
typedef struct _Roc_Freq_Serv{
    UINT8_T     m_Modulation;           /* ���Ʒ�ʽ */
    UINT32_T    m_dwFrequency;          /* Ƶ�ʣ�BCD�� */
    UINT32_T    m_symbol_rate;          /* �����ʣ�BCD�� */
    UINT16_T    m_wServiceID;           /* service id */
}Roc_Freq_Serv;

typedef struct _Roc_NetID_Serv{
    UINT16_T    m_wOriNetID;            /* ԭʼ����ID */
    UINT16_T    m_wTSID;                /* TSID */
    UINT16_T    m_wServiceID;           /* service id */
}Roc_NetID_Serv;

/*+++++++++++++++++++++����Ϊ����������ѶCAʱ,�����г�����Ҫʵ�ֵĺ���+++++++++++++++++++++++++++++*/
/*
��������:
    rocme_porting_ca_get_data_info

����˵��: 
    ȡ��CA��FLASH�д洢�ռ�ĵ�ַ�ʹ�С

����˵��:
    �������:
            ��
    �������:
            [ addr   ] : CA��FLASH�д洢�ռ�ĵ�ַ
            [ length ] : CA��FLASH�д洢�ռ�Ĵ�С

��    ��: 
    �ɹ�: 0          
    ʧ��: -1

��ע:
    ���ʹ��������ѶCA����ʵ�ִ˽ӿڡ����ʹ���������̣��˽ӿ�ֱ�ӷ���0��

�޸ļ�¼:
*/
INT32_T rocme_porting_ca_get_data_info(UINT32_T *addr, UINT32_T *length);

/*++++++++++++++++++++++����Ϊ����������ѶCAʱ,�����г�����Ҫʵ�ֵĺ���+++++++++++++++++++++++++++*/






/*++++++++++++++++++++����Ϊ���ɷ�������ѶCAʱ,�����г�����Ҫʵ�ֵĺ���+++++++++++++++++++++++++++*/

/*
��������:
    rocme_porting_CASInit

����˵��:
    �м��������ʱ����ã���CASģ���ʼ��

����˵��:
    �������:
            �ޡ�
    �������:
            �ޡ�
��    ��:
    �ɹ�: 0
    ʧ��: -1
*/
INT32_T rocme_porting_CASInit(void);

/*
��������:
    rocme_porting_GetCASProvider

����˵��:
    ��ȡcas���ṩ��

����˵��:
    �������:
            �ޡ�
    �������:
            [ *provider ]: cas�ṩ�̵�ö��

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetCASProviderID( ROC_CAS_PROVIDER_e *provider );

/*
��������:
    rocme_porting_GetCASProvider

����˵��:
    ��ȡcas���ṩ�̵�ȫ��

����˵��:
    �������:
            [ *name ]: cas�ṩ�̵�ȫ��,���21���ֽ�,����������

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetCASProviderName(CHAR_T * name);

/*
��������:
    rocme_porting_GetCASVer

����˵��:
    �м�����CAģ��İ汾

����˵��: 
    �������:
            �ޡ�
    �������:
            [ *strVersion   ]: ����汾��,���21(ROC_CAS_MAXLEN_PROVIDERNAME)���ַ�,����������

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetCASVer(CHAR_T *strVersion);

/*
��������:
    rocme_porting_GetCardID

����˵��: 
    ������ܿ��ڲ�ID��
    
����˵��: 
    �������:
            �ޡ�
    �������:
            [ *strCardID]: ������ܿ��ڲ�ID,��'\0'�������ַ�������󳤶�21(ROC_CAS_MAXLEN_VERSION)��

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetCardID(CHAR_T *strCardID);

/*
��������:
    rocme_porting_CASIDVerify

����˵��: 
    �м�����CASID����øýӿ��ж�CASID�Ƿ���Ч�������Ч�򷵻�ROC_TRUE�����򷵻�ROC_FALSE
    
����˵��:
    �������:
            wCaSystemID: ����SI/PSI��Ϣ��pmt/cat���е�ca����������õ�CASID
    �������:
            �ޡ�

��    ��:
    ROC_TRUE:   CASID��Ч
    ROC_FALSE:  CASID��Ч
*/
ROC_BOOL rocme_porting_CASIDVerify(const UINT16_T wCaSystemID);

/*
��������:
    rocme_porting_SetCurEcmInfos

����˵��:
    �м�����ô˽ӿ���ӻ���ɾ��ECM��
    ��������Ҫ�������õ�ECM����
    ��������component_pid��Ӧ��ecm pid��Ϊ0��ʾ���һ��ecm������
    ��������component_pid��Ӧ��ecm pidΪ0��ʾɾ��һ��ecm������
    �����б���ά���Ѿ����ù���ecm��¼��
    
    ����pmt���е�ca������ʱ��ʹ��rocme_porting_CASIDVerify()��֤�������Ƿ��Ӧ��ǰCA����Ӧ����Ϣ����������������̨ʹ�á�

����˵��:
    �������:
      ServiceNetInfo:   Ҫ�տ��Ľ�Ŀ��Ӧ��net id, ts id, service id�ȹ�����Ϣ
      componentCount:   compEcmInfosָ��Roc_ComponentEcmInfo�ṹ��ĸ���
      pCompEcmInfos:    ����Ҫ�տ���Ŀ��pid��Ϣ��
    �������:
            �ޡ�
*/
void rocme_porting_SetCurEcmInfos(Roc_NetID_Serv ServiceNetInfo,UINT32_T componentCount, const Roc_ComponentEcmInfo* pCompEcmInfos);

/*
��������:
    rocme_porting_SetEmmInfo

����˵��: 
    ����EMMPID��CASģ�齫�������õ�EMMPID��Ϣ����EMM���ݽ��մ���

    �м���յ�CAT��󣬵��ô˺�������EMM PID����ȥ������CA����Ϳ��Ը��ݴ�PID��ȡ
    ˽�б������û��������Ȩ��Ϊ�û��ṩ��ֵ����
    ������EMM��PIDΪ0ʱ����ʾ֪ͨCAģ��ֹͣ��ȡEMM��
    
����˵��: 
    �������:
            [ *EmmInfo  ]: EMM��Ϣ���ο�Roc_ComponentEmmInfo�ṹ���塣 
            [ nEmmCount ]: EmmPid�ĸ�����Ŀǰֻ֧��nEmmCount��1
    �������:
            �ޡ�
��    ע:
    �м�������rocme_porting_CASIDVerify()��֤ca system id��ͨ����֤��ŰѶ�Ӧ��EMM����������
*/
void rocme_porting_SetEmmInfo(INT32_T nEmmCount,const Roc_ComponentEmmInfo *EmmInfo);

/*
��������:
    rocme_porting_ServiceChangeNotify

����˵��: 
    �м�����ô˺���֪ͨCAģ���Ŀ�иı�
    
����˵��:
    �������:
            void
    �������:
            ��

��    ��:
    ��
*/
void rocme_porting_ServiceChangeNotify(void);

/*
��������:
    rocme_porting_ServiceStopNotify

����˵��: 
    �м�����ô˺���֪ͨCAģ�鵱ǰ���ŵĽ�Ŀֹͣ����
    
����˵��:
    ��

��    ��:
    ��
*/
void rocme_porting_ServiceStopNotify(void);

/*
��������:
    rocme_porting_IsPinLocked

����˵��: 
    �жϿ��Ƿ���ס��
    
����˵��: 
    �������:
            �ޡ�
    �������:
            [ *pState ]: ���������1��ʾ��ס�ˣ�0��ʾδ��ס, -1��ʾ��֧�ִ˹��ܡ�
��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��

��    ע:
    ��֧��PIN������״̬��鹦��ʱ,��*pState��ֵΪ-1,���ҷ���0
*/
INT32_T rocme_porting_IsPinLocked(INT32_T * pState);

/*
��������:
    rocme_porting_IsPinPass

����˵��: 
    �ж��û��Ƿ�ͨ��pin����֤��

����˵��: 
    �������:
            �ޡ�

    �������:
            [ *pState ]: 1--��ʾͨ���ˣ�0--��ʾû��; (-1)��ʾ��֧�ִ˹��ܡ�

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��

��ע:
    ��֧�ִ˹���ʱ,��*pState��ֵΪ-1,���ҷ���0
*/
INT32_T rocme_porting_IsPinPass(INT32_T * pState);

/*
��������:
    rocme_porting_ChangePin

����˵��: 
    �޸����ܿ���PIN�롣
    
����˵��:  
    �������:
            [ type        ]: PIN������,0Ϊ��ĸ����PIN�������ùۿ�ʱ��ͼ��𣩣�1ΪǮ������PIN(��IPP����ʱ�����PIN)��
            [ *pbysPin    ]: PIN��
            [ byPinLen    ]: PIN�볤��
            [ *pbysNewPin ]: ��PIN��
            [ byNewPinLen ]: ��PIN��ĳ���
    �������:
            ��
��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��

��ע:
    �м�����ݵ�PIN�붼��ASCII�롣
    ���������:12345678,
    �м�����ݵ�pbysPin[8]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38}
*/
INT32_T rocme_porting_ChangePin(UINT8_T type, UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T* pbysNewPin, UINT8_T byNewPinLen);

/*
��������:
    rocme_porting_GetRating

����˵��: 
    ������ܿ�Ŀǰ��߹ۿ�����
    �ۿ�����Ϊ3~18����15������ʼֵΪ18�������Թۿ����м���Ľ�Ŀ��
    
����˵��:  
    �������:
            ��
    �������:
            [ *pbyRating]: ����ۿ�����

��    ��:
    0:      �ɹ�
    (-1):   CA��֧�ִ˹���:     
    ����:   ʧ��,����ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetRating(UINT8_T* pbyRating);

/*
��������:
    rocme_porting_SetRating

����˵��: 
    �������ܿ��ۿ�����
    
����˵��:  
    �������:
            [ *pbysPin  ]: PIN��
            [ byPinLen  ]: PIN�볤��
            [ byRating  ]:Ҫ���õ��µĹۿ�����
    �������:
            ��
��    ��:
    0:      �ɹ�
    (-1):   CA��֧�ִ˹���:     
    ����:   ʧ��,����ο�ʡ�������붨��

��    ע:
    ��ʱPIN������Ǹ�ĸ���Ƶ�PIN��

��ע:
    �м�����ݵ�PIN�붼��ASCII�롣
    ���������:12345678,
    �м�����ݵ�pbysPin[8]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38}
*/
INT32_T rocme_porting_SetRating(UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T byRating);

/*
��������:
    rocme_porting_GetWorkTime

����˵��: 
    ������ܿ���ǰ���õĹ���ʱ���
    ����ʱ�γ�ʼֵΪ00:00~23:59����ȫ�춼���տ���
    
����˵��: 
    �������:
            ��
    �������:
            [ *pwStartTime ]: ��ʼ������ʱ�䣬���ֽڱ�ʾСʱ�����ֽڱ�ʾ����
            [ *pwEndTime   ]: ����������ʱ�䣬��ʽͬ��
��    ��:
    0:      �ɹ�
    (-1):   CA��֧�ִ˹���:     
    ����:   ʧ��,����ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetWorkTime(UINT16_T * pwStartTime, UINT16_T * pwEndTime);

/*
��������:
    rocme_porting_SetWorkTime

����˵��: 
    �������ܿ�����ʱ��
    
����˵��: 
    �������:
            [ *pbysPin   ]: PIN��
            [ byPinLen   ]: PIN�볤��
            [ wStartTime ]: ��ʼ������ʱ�䣬���ֽڱ�ʾСʱ�����ֽڱ�ʾ����
            [ wEndTime   ]: ����������ʱ�䣬��ʽͬ��
    �������:
            ��

��    ��:
    0:      �ɹ�
    (-1):   CA��֧�ִ˹���:     
    ����:   ʧ��,����ο�ʡ�������붨��

��    ע:
    ��ʱPIN������Ǹ�ĸ���Ƶ�PIN��


��ע:
    �м�����ݵ�PIN�붼��ASCII�롣
    ���������:12345678,
    �м�����ݵ�pbysPin[8]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38}
*/
INT32_T rocme_porting_SetWorkTime(UINT8_T* pbysPin, UINT8_T byPinLen, UINT16_T wStartTime, UINT16_T wEndTime);

/*
��������:
    rocme_porting_GetOperatorInfo

����˵��: 
    ���CAS��Ӫ����Ϣ
    
����˵��:  
    �������:
            [ wTVSID         ]: CAS��Ӫ�̵�ID  �����0xFFFF �򷵻����е���Ӫ����Ϣ
            [ *pbyCount      ]: ����ĳ���
    �������:
            [ *pOperatorInfo ]: �����Ӫ����Ϣ
            [ *pbyCount      ]: ʵ�������Ӫ����Ϣ�ĸ���

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetOperatorInfo(UINT16_T wTVSID,UINT8_T * pbyCount,Roc_OperatorInfo * pOperatorInfo);

/*
��������:
    rocme_porting_GetServiceEntitles

����˵��: 
    �����ͨ��Ȩ��Ŀ���������������ڽ�������ʾ��
    
����˵��: 
    �������:
            [ wTVSID         ]: ��Ӫ�̵��ڲ���š�
            [ *pEntitleCount ]: psEntitlesָ��ռ�����Roc_ServiceEntitle����
    �������:
            [ *pEntitleCount ]: psEntitles��ʵ�ʻ�õ�Roc_ServiceEntitle����
            [ *psEntitles    ]: �����Ȩ

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetServiceEntitles(UINT16_T wTVSID,UINT16_T *pEntitleCount,Roc_ServiceEntitle* psEntitles);

/*
��������:
    rocme_porting_ChangeLanguage

����˵��:
    �л���ʾ���ԣ�������CAģ���ʼ������á�
    Ĭ��ʹ�����ġ����û��л����Ժ�,�м�����ô˺���֪ͨCAģ��

����˵��: 
    �������:
            [ byLanguage ]: ��������
                            ROC_CAS_LANG_CHN_SIM  ��������(Ĭ��)
                            ROC_CAS_LANG_ENG      Ӣ��
    �������:
            ��

��    ��:
    ��
*/
void rocme_porting_ChangeLanguage(UINT8_T byLanguage);

/*
��������:
    rocme_porting_GetEmailCount

����˵��: 
    ��ȡE-mail����
    
����˵��: 
    �������:
            ��
    �������:
            [ *pEmailCount    ]: ����E-mail�ܸ�����
            [ *pNewEmailCount ]: ����������ѶCAS����δ������E-mail��������������ͬ��CAS����ʣ����ÿռ����
��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetEmailCount(UINT16_T * pEmailCount, UINT16_T * pNewEmailCount);

/*
��������:
    rocme_porting_GetEmailHead

����˵��:
    ��ȡ���E-mail��Ҫ��Ϣ
    
����˵��: 
    �������:
            [ *pEmailCount ]: pEmail���ɴ�Roc_EmailInfo���ܸ���
    �������:
            [ *pEmailCount ]: ȡ����pEmail��Roc_EmailInfo���ܸ�����
            [ *pEmail      ]: ȡ����E-mail��Ҫ��Ϣ��
��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetEmailHead(UINT16_T * pEmailCount, Roc_EmailInfo * pEmail);

/*
��������:
    rocme_porting_GetEmailContent

����˵��: 
    ��ȡһ��E-mail������
    
����˵��: 
    �������:
            [ tVersion  ]: E-mail�汾��
    �������:
            [ *pEmail   ]: ��ȡ��E-mail�ṹ��
��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetEmailContent(UINT32_T tVersion, Roc_EmailContent * pEmail);

/*
��������;
    rocme_porting_DelEmail

����˵��: 
    ɾ��ָ��E-mail��
    
����˵��:
    �������:
            [ tVersion  ]: E-mail�汾�����Ϊ-1����ʾɾ������������email������Ϊ�����id��
��    ��
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_DelEmail(UINT32_T tVersion);

/*
��������:
    rocme_porting_CheckNewEmail

����˵��: 
    �м����ѯ�Ƿ������ʼ������ڿ�������ʱ���������Ĳ�ѯ
    
����˵��:
    ��

��    ��
    �ɹ�: 1                         ���µ��ʼ�
          0                         û���µ��ʼ�
    ʧ��: ����
*/
INT32_T rocme_porting_CheckNewEmail(void);

/*
��������:
    rocme_porting_GetBookIpps

����˵��:
    �õ���Ԥ�������Ѿ�Ԥ����IPP��Ŀ�б�
    
����˵��:
    �������:
        [ wTVSID    ]: ��Ӫ��ID
        [ *pbyCount ]: pIpps�����ɵ�IPP�ṹ�ĸ���
    �������:
        [ *pbyCount ]: �ѻ�ȡ��IPP��Ŀ����
        [ *pIpp     ]: IPP��Ŀ��Ϣ

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetBookIpps(UINT16_T wTVSID, UINT8_T * pbyCount, Roc_CAIpp * pIpps);

/*
��������:
    rocme_porting_GetInquireIpp

����˵��:
    �õ���ȡ��ʱ������IPP��Ŀ��Ϣ
    
����˵��:
    [ *pIpp ]: ��ʱ������ippv��Ŀ��Ϣ

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetInquireIpp(Roc_CAIpp * pIpp);

/*
��������:
    rocme_porting_CancelInquireIpp

����˵��:
    ���û�������IPP��Ʒ,�ϲ�Ӧ���˳�IPP������ʾ��ʱ
    ���ô˺���֪ͨCA��
    
����˵��:
    ��

��    ��:
    ��
*/
void rocme_porting_CancelInquireIpp();


/*
��������:
    rocme_porting_BookIpp

����˵��:
    Ԥ��Ipp��Ŀ
    
����˵��:
    �������:
            [ *pbysPin  ]: PIN��
            [ byPinLen  ]: PIN�볤��
            [ PriceType ]: ҪԤ����ȷ�Ϲ����ipp��Ŀ�ļ۸�����
    �������:
            ��

��    ��:
    0:      �ɹ�
    ����:   �ο��㶫ʡ�������붨��                    

��ע:
    �м�����ݵ�PIN�붼��ASCII�롣
    ���������:12345678,
    �м�����ݵ�pbysPin[8]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38}
*/
INT32_T rocme_porting_BookIpp(UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T PriceType);

/*
��������:
    rocme_porting_GetViewedIpps

����˵��:
    �õ��ѹۿ���Ipp��Ŀ��
    
����˵��:
    �������:
            [ *pbyCount ]: pIppsָ�����������ɽ�Ŀ����
    �������:
            [ *pbyCount ]: pIpps�еõ����ѹۿ���Ŀ��Ϣ������
            [ *pIpps    ]: �ѹۿ���ippv��Ŀ��Ϣ
��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetViewedIpps(UINT32_T * pbyCount, Roc_CAViewedIpp * pIpps);

/*
��������:
    rocme_porting_GetMoneyInfo

����˵��:
    �õ�ĳ����Ӫ�̵��ѻ���Ǯ����ʣ��Ǯ����
    
����˵��:
    �������:
            [ wTVSID       ]: ��Ӫ�̵��ڲ���š�
            [ *pbyCount    ]: pSlotInfosָ������������Ǯ����Ϣ����
    �������:
            [ *pbyCount    ]: pSlotInfos�еõ���Ǯ����Ϣ����
            [ *pSlotInfos  ]: ���Ǯ����Ϣ

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
*/
INT32_T rocme_porting_GetMoneyInfo(UINT16_T wTVSID, UINT8_T* pbyCount, Roc_TVSSlotInfo * pSlotInfos); 

/*
��������:
    rocme_porting_SendNITToCA

����˵��: 
    �м���յ�NIT���section��,���ô˺��������ݸ�CA
    
����˵��:
    �������:
            [ sec    ]: nit section ������
            [ len    ]: nit section �������Ĵ�С
    �������:
            ��

��    ��:
    ��

��    ע:
    �ú�������������
    ��CA�޴�����,�������ÿռ��ɡ�
*/
void rocme_porting_SendNITToCA( UINT8_T *sec, UINT32_T len );
/*++++++++++++++++++++����Ϊ���ɷ�������ѶCAʱ,�����г�����Ҫʵ�ֵĺ���+++++++++++++++++++++++++++*/



/*++++++++++++++++++++����Ϊ���ɷ�������ѶCAʱ,�м���ṩ�������г��̵��õĺ���+++++++++++++++++++*/
/*
����:
    rocme_porting_ca_send_msg

����:
    ���������м������CA��Ϣ

����:
    type:�ο��㶫ʡ���淶�е�"��Ϣ����"�й���CA���ֵĶ���.
    data:��Ϊ0ʱ,Ϊ��Ϣ����
    dataLen:data��Ϊ0ʱ,Ϊ�������ݵ����ݳ���

��    ��:
    0    --  �ɹ�
    ���� --  ʧ��

��    ע:
    ��CA��Ҫ���ϲ�Ӧ�ý���ʱ,ʹ�ô˺���
*/
//INT32_T rocme_porting_ca_send_msg(UINT32_T type, UINT8_T *data, UINT32_T dataLen);
/*++++++++++++++++++++����Ϊ���ɷ�������ѶCAʱ,�м���ṩ�������г��̵��õĺ���+++++++++++++++++++*/

//#define rocme_porting_ca_send_msg


#endif

