/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_cas.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/

#include "porter_rocme.h"


/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_ca_get_data_info(UINT32_T *addr, UINT32_T *length)
{
ROCME_TEST_PRINT
	
}


/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_CASInit(void)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetCASProviderID( ROC_CAS_PROVIDER_e *provider )
{
	ROCME_TEST_PRINT

}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetCASProviderName(CHAR_T * name)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetCASVer(CHAR_T *strVersion)
{
	ROCME_TEST_PRINT

}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetCardID(CHAR_T *strCardID)
{
	ROCME_TEST_PRINT

}

/***************************************************************
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
***************************************************************/
ROC_BOOL rocme_porting_CASIDVerify(const UINT16_T wCaSystemID)
{
	ROCME_TEST_PRINT

}

/***************************************************************
��������:
    rocme_porting_SetCurEcmInfos

����˵��:
    �û�ת��Ƶ����ʱ��������������
    ���õ�ǰ�����տ��Ľ�Ŀ����ϸ��Ϣ��
    
    ���û���Ƶ��ʱ���м����Ҫ���ô�porting�ӿڣ�
    ����ǰ��Ŀ��ԭʼ��Ϣ��ECM PIDͨ�������д��ݸ�CASģ�飬
    CASģ�����ݵ�ǰƵ������Ϣ�����뵱ǰƵ����صĲ�����
    �����ǰƵ��Ϊ�����ŵ�Ƶ��������Ҫ��ECM��PID��Ϊ0��
    
    ����pmt���е�ca������ʱ��ʹ��rocme_porting_CASIDVerify()��֤�������Ƿ��Ӧ��ǰCA����Ӧ����Ϣ����������������̨ʹ�á�

����˵��:
    �������:
      ServiceNetInfo:   Ҫ�տ��Ľ�Ŀ��Ӧ��net id, ts id, service id�ȹ�����Ϣ
      componentCount:   compEcmInfosָ��Roc_ComponentEcmInfo�ṹ��ĸ���
      pCompEcmInfos:    ����Ҫ�տ���Ŀ��pid��Ϣ��
    �������:
            �ޡ�
***************************************************************/
void rocme_porting_SetCurEcmInfos(Roc_NetID_Serv ServiceNetInfo,UINT32_T componentCount, const Roc_ComponentEcmInfo* pCompEcmInfos)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
void rocme_porting_SetEmmInfo(INT32_T nEmmCount,const Roc_ComponentEmmInfo *EmmInfo)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
void rocme_porting_ServiceChangeNotify(void)
{
	ROCME_TEST_PRINT
}

/***************************************************************
��������:
    rocme_porting_ServiceStopNotify

����˵��: 
    �м�����ô˺���֪ͨCAģ�鵱ǰ���ŵĽ�Ŀֹͣ����
    
����˵��:
    ��

��    ��:
    ��
***************************************************************/
void rocme_porting_ServiceStopNotify(void)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_IsPinLocked(INT32_T * pState)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_IsPinPass(INT32_T * pState)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_ChangePin(UINT8_T type, UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T* pbysNewPin, UINT8_T byNewPinLen)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetRating(UINT8_T* pbyRating)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_SetRating(UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T byRating)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetWorkTime(UINT16_T * pwStartTime, UINT16_T * pwEndTime)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_SetWorkTime(UINT8_T* pbysPin, UINT8_T byPinLen, UINT16_T wStartTime, UINT16_T wEndTime)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetOperatorInfo(UINT16_T wTVSID,UINT8_T * pbyCount,Roc_OperatorInfo * pOperatorInfo)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetServiceEntitles(UINT16_T wTVSID,UINT16_T *pEntitleCount,Roc_ServiceEntitle* psEntitles)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
void rocme_porting_ChangeLanguage(UINT8_T byLanguage)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetEmailCount(UINT16_T * pEmailCount, UINT16_T * pNewEmailCount)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetEmailHead(UINT16_T * pEmailCount, Roc_EmailInfo * pEmail)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetEmailContent(UINT32_T tVersion, Roc_EmailContent * pEmail)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_DelEmail(UINT32_T tVersion)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_CheckNewEmail(void)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetBookIpps(UINT16_T wTVSID, UINT8_T * pbyCount, Roc_CAIpp * pIpps)
{
	ROCME_TEST_PRINT
}

/***************************************************************
��������:
    rocme_porting_GetInquireIpp

����˵��:
    �õ���ȡ��ʱ������IPP��Ŀ��Ϣ
    
����˵��:
    [ *pIpp ]: ��ʱ������ippv��Ŀ��Ϣ

��    ��:
    �ɹ�: 0
    ʧ��: ����,�ο�ʡ�������붨��
***************************************************************/
INT32_T rocme_porting_GetInquireIpp(Roc_CAIpp * pIpp)
{
	ROCME_TEST_PRINT
}

/***************************************************************
��������:
    rocme_porting_CancelInquireIpp

����˵��:
    ���û�������IPP��Ʒ,�ϲ�Ӧ���˳�IPP������ʾ��ʱ
    ���ô˺���֪ͨCA��
    
����˵��:
    ��

��    ��:
    ��
***************************************************************/
void rocme_porting_CancelInquireIpp()
{
	ROCME_TEST_PRINT
}


/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_BookIpp(UINT8_T* pbysPin, UINT8_T byPinLen, UINT8_T PriceType)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetViewedIpps(UINT32_T * pbyCount, Roc_CAViewedIpp * pIpps)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
INT32_T rocme_porting_GetMoneyInfo(UINT16_T wTVSID, UINT8_T* pbyCount, Roc_TVSSlotInfo * pSlotInfos)
{
	ROCME_TEST_PRINT
}

/***************************************************************
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
***************************************************************/
void rocme_porting_SendNITToCA( UINT8_T *sec, UINT32_T len )
{
	ROCME_TEST_PRINT
}
/***************************************************************
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
***************************************************************/
#if 0
INT32_T rocme_porting_ca_send_msg(UINT32_T type, UINT8_T *data, UINT32_T dataLen)
{
}
#endif

