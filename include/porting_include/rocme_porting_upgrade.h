/*****************************************************************************
File name   : rocme_porting_upgrade.h

Author		: XXX			

Description : The poriting interface & macro definition for UPGRADE module.
	          
Copyright (C) BeiJing SUMAVision, Inc., 2009 .All rights reserved.

History		:
				2009.12.20  		Created 					
*****************************************************************************/
#ifndef _ROCME_PORTING_UPGRADE_H_
#define _ROCME_PORTING_UPGRADE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"

#define LOADER_STB_ID_LEN        26   /**< �������ⲿ���к� */



//��־������������Ч�ı�־
#define 	LOADER_PROGRESS_FLAG		0xfe841930

//����״̬����ת��Ӧ�ó���
#define 	CALL_PROGRAM				0x00

//��ת��loader
#define 	CALL_LOADER					0xff

typedef struct tagLoaderDbInfo
{
#if 0
	ROC_BOOL	bCallMainProgram;	//0 ��ת��������0xff��ת��loader
	ROC_BOOL	bFlag;				//�����ǽ������ݵı�־�� LOADER_PROGRESS_FLAG

	UINT32_T	nSerialNumber_hi;	//�������к�
	UINT32_T	nSerialNumber_lo;
	
	////////////////////
	//�������ص�Ƶ����Ϣ
	UINT32_T	nFrequency;			//Ƶ��
	UINT32_T	nSymbolRate;		//������
	UINT8_T	bQamSize;			//Qam��ʽ
	UINT8_T	bInversion;			//Ƶ�׷��ã��ɺ���

	UINT16_T	nPID;				//����PID
	
	/////////////////////
	//������Ϣ
	UINT16_T	sManufacturer;		//���Ҵ���
	UINT16_T	sModelID;			//��Ʒ�ͺţ���ʱ����
	UINT32_T	nHardwareVersion;	//Ӳ���汾��
	UINT32_T	nSoftwareVersion;	//����汾��
	
	UINT32_T	nReleaseDate;		//��������
	UINT32_T	nDownloadTime;
	UINT32_T	nCRC;				//��������CRCУ��
#endif
	unsigned int bFlag; //�Ƿ���loaderinfo���ݵı�ʶ��ȡֵ 0x4C4F4144
	unsigned int bCallMainProgram; //��ת����
	unsigned int nPID; //����pid
	unsigned int nFrequency; //����Ƶ��
	unsigned int nSymbolRate; //������
	unsigned int bQamSize; //���Ʒ�ʽ
	unsigned int ota_tableid;
	unsigned int u32Loaderversion;
	unsigned int db_len;
	
	unsigned int eOTAType;
	unsigned int u32NewSoftware;
	unsigned int nSoftwareVersion; //����汾��
	unsigned int download_data;
	unsigned int u32FailedCnt; //ʧ�ܴ���
	unsigned int nHardwareVersion; //Ӳ���汾��
	unsigned int u32DestroyFlag;
	
	//unsigned int u32BootKernelCnt;
	//here add IP upgrade parameter
	unsigned int eIpType;
	unsigned char u8EthAddr[6];
	unsigned char Reserved1[2];
	
	unsigned int ipOurIp;
	unsigned int ipGateway;
	unsigned int ipSubnetMask;
	unsigned int ipServer;
	unsigned int ipServerPort;
	unsigned char Reserved2[2];
	unsigned char as8FileName[128];
	
	unsigned char au8AppUse[20];
	unsigned char au8LoaderReserved[8];
	
	unsigned int nManufacturer; //���̴���
	unsigned int nReleaseDate; //�����������
	unsigned int nSTBID_hi;
	unsigned int nSTBID_lo;
	
	unsigned int nCRC; //crcУ��
} LOADER_DB_INFO_S;

enum {
    ROC_UPD_QPSK  =0x0,
    ROC_UPD_QAM_16,
    ROC_UPD_QAM_32,
    ROC_UPD_QAM_64,
    ROC_UPD_QAM_128,
    ROC_UPD_QAM_256,
    ROC_UPD_UNKNOWN
};


enum {
    ROC_UPD_NO, /*��������Ϣ*/
    ROC_UPD_ASK /*��������  */
};


typedef struct roc_stb_info {
    UINT16_T manu_code;     /*���̴��롣        */
    UINT16_T hw_batch_no;   /*Ӳ�����κš�      */
    UINT16_T major_hw_ver;  /*������Ӳ�����汾��*/
    UINT16_T minor_hw_ver;  /*������Ӳ���ΰ汾��*/
    UINT16_T major_sw_ver;  /*������������汾��*/
    UINT16_T minor_sw_ver;  /*����������ΰ汾��*/
    UINT32_T stb_serial_no; /*���������кš�    */
    UINT16_T region_code;   /*������������롣  */
    UINT8_T  stb_type;      /*���������͡�(��Ӫ ����)*/  
}roc_stb_info_t;


typedef struct roc_upd_info {
    UINT8_T  flag;         /*������־              */
    UINT16_T download_pid; /*���ص�pid             */
    UINT8_T  modulation;   /*���Ʒ�ʽ              */
    UINT32_T symbol_rate;  /*������ Ksymbol/s 6875 */
    UINT32_T frequency;    /*Ƶ�� KHz 698000       */
    UINT16_T major_sw_ver;  /*������������汾��*/
    UINT16_T minor_sw_ver;  /*����������ΰ汾��*/
}roc_upd_info_t;


/*****************************************************************************
����˵��: 
    ���û�������Ϣ

����˵��:
    �������:
        [info ] ��������Ϣ
        typedef struct roc_stb_info {
            UINT32_T swv; //����汾��  
            UINT32_T hwv; //Ӳ���汾��  
            UINT32_T serial; //���������к�
        }roc_stb_info_t;
        ����Ϣ�ڻ����г���ʱӦ�ñ��ֵ�flash�У�
        ��loader�����ɹ�����¸���Ϣ

��    ��:
    ʧ��: ��0              
    �ɹ�:  0
*****************************************************************************/
UINT32_T rocme_porting_get_stbinfo( roc_stb_info_t *info );


/*****************************************************************************
����˵��: 
    ���û�����������Ϣ

����˵��:
    �������:
        [info ] ������������Ϣ
        typedef struct roc_upd_info
        {
            UINT8_T  flag;         //������־ 
            UINT16_T download_pid; //���ص�pid
            UINT8_T  modulation;   //���Ʒ�ʽ 
            UINT32_T symbol_rate;  //������   
            UINT32_T frequency;    //Ƶ��    
        }roc_upd_info_t;

        loader����ʱ���������־ 
        ��������־ΪROC_UPD_ASKʱ������������
        �����ɹ��󽫸ñ�־��ΪROC_UPD_NO

��    ��:
    ʧ��: ��0              
    �ɹ�:  0
*****************************************************************************/
UINT32_T rocme_porting_set_updinfo( roc_upd_info_t *info );


#ifdef __cplusplus
}
#endif

#endif

