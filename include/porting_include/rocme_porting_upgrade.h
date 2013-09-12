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

#define LOADER_STB_ID_LEN        26   /**< 机顶盒外部序列号 */



//标志进度区数据有效的标志
#define 	LOADER_PROGRESS_FLAG		0xfe841930

//正常状态，跳转到应用程序
#define 	CALL_PROGRAM				0x00

//跳转到loader
#define 	CALL_LOADER					0xff

typedef struct tagLoaderDbInfo
{
#if 0
	ROC_BOOL	bCallMainProgram;	//0 跳转到主程序，0xff跳转到loader
	ROC_BOOL	bFlag;				//数据是进度数据的标志， LOADER_PROGRESS_FLAG

	UINT32_T	nSerialNumber_hi;	//本机序列号
	UINT32_T	nSerialNumber_lo;
	
	////////////////////
	//程序下载的频点信息
	UINT32_T	nFrequency;			//频点
	UINT32_T	nSymbolRate;		//符号率
	UINT8_T	bQamSize;			//Qam方式
	UINT8_T	bInversion;			//频谱反置，可忽略

	UINT16_T	nPID;				//下载PID
	
	/////////////////////
	//程序信息
	UINT16_T	sManufacturer;		//厂家代号
	UINT16_T	sModelID;			//产品型号，暂时不用
	UINT32_T	nHardwareVersion;	//硬件版本号
	UINT32_T	nSoftwareVersion;	//软件版本号
	
	UINT32_T	nReleaseDate;		//发布日期
	UINT32_T	nDownloadTime;
	UINT32_T	nCRC;				//进度区的CRC校验
#endif
	unsigned int bFlag; //是否是loaderinfo数据的标识，取值 0x4C4F4144
	unsigned int bCallMainProgram; //跳转类型
	unsigned int nPID; //升级pid
	unsigned int nFrequency; //升级频点
	unsigned int nSymbolRate; //符号率
	unsigned int bQamSize; //调制方式
	unsigned int ota_tableid;
	unsigned int u32Loaderversion;
	unsigned int db_len;
	
	unsigned int eOTAType;
	unsigned int u32NewSoftware;
	unsigned int nSoftwareVersion; //软件版本号
	unsigned int download_data;
	unsigned int u32FailedCnt; //失败次数
	unsigned int nHardwareVersion; //硬件版本号
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
	
	unsigned int nManufacturer; //厂商代码
	unsigned int nReleaseDate; //软件发布日期
	unsigned int nSTBID_hi;
	unsigned int nSTBID_lo;
	
	unsigned int nCRC; //crc校验
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
    ROC_UPD_NO, /*无升级信息*/
    ROC_UPD_ASK /*请求升级  */
};


typedef struct roc_stb_info {
    UINT16_T manu_code;     /*厂商代码。        */
    UINT16_T hw_batch_no;   /*硬件批次号。      */
    UINT16_T major_hw_ver;  /*机顶盒硬件主版本。*/
    UINT16_T minor_hw_ver;  /*机顶盒硬件次版本。*/
    UINT16_T major_sw_ver;  /*机顶盒软件主版本。*/
    UINT16_T minor_sw_ver;  /*机顶盒软件次版本。*/
    UINT32_T stb_serial_no; /*机顶盒序列号。    */
    UINT16_T region_code;   /*机顶盒区域代码。  */
    UINT8_T  stb_type;      /*机顶盒类型。(运营 测试)*/  
}roc_stb_info_t;


typedef struct roc_upd_info {
    UINT8_T  flag;         /*升级标志              */
    UINT16_T download_pid; /*下载的pid             */
    UINT8_T  modulation;   /*调制方式              */
    UINT32_T symbol_rate;  /*符号率 Ksymbol/s 6875 */
    UINT32_T frequency;    /*频点 KHz 698000       */
    UINT16_T major_sw_ver;  /*机顶盒软件主版本。*/
    UINT16_T minor_sw_ver;  /*机顶盒软件次版本。*/
}roc_upd_info_t;


/*****************************************************************************
功能说明: 
    设置机顶盒信息

参数说明:
    输出参数:
        [info ] 机顶盒信息
        typedef struct roc_stb_info {
            UINT32_T swv; //软件版本号  
            UINT32_T hwv; //硬件版本号  
            UINT32_T serial; //机顶盒序列号
        }roc_stb_info_t;
        该信息在机顶盒出厂时应该保持到flash中，
        当loader升级成功后更新该信息

返    回:
    失败: 非0              
    成功:  0
*****************************************************************************/
UINT32_T rocme_porting_get_stbinfo( roc_stb_info_t *info );


/*****************************************************************************
功能说明: 
    设置机顶盒升级信息

参数说明:
    输入参数:
        [info ] 机顶盒升级信息
        typedef struct roc_upd_info
        {
            UINT8_T  flag;         //升级标志 
            UINT16_T download_pid; //下载的pid
            UINT8_T  modulation;   //调制方式 
            UINT32_T symbol_rate;  //符号率   
            UINT32_T frequency;    //频点    
        }roc_upd_info_t;

        loader启动时检查升级标志 
        当升级标志为ROC_UPD_ASK时，则启动升级
        升级成功后将该标志置为ROC_UPD_NO

返    回:
    失败: 非0              
    成功:  0
*****************************************************************************/
UINT32_T rocme_porting_set_updinfo( roc_upd_info_t *info );


#ifdef __cplusplus
}
#endif

#endif

