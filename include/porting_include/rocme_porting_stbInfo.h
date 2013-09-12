/*******************************************************************************
File name   : rocme_porting_stbInfo.h

Author		: XXX			

Description : .
	          
Copyright (C) BeiJing SUMAVision, Inc., 2011 .All rights reserved.

History		:
				2011.01.12		Created 						
*******************************************************************************/
#ifndef _ROCME_PORTING_STBINFO_H_
#define _ROCME_PORTING_STBINFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


typedef struct RocFlashBlockInfo
{
    UINT32_T num;/*flashBlock����*/
    UINT32_T size;/*flashBlock�ܴ�С*/
}RocFlashBlockInfo_t;

typedef struct RocFlashBlock
{
    CHAR_T*  name;/*��flashBlock����*/
    UINT32_T size;/*��flashBlock��С*/
}RocFlashBlock_t;


typedef struct RocOsInfo
{
    CHAR_T* name;
    CHAR_T* provider;
    CHAR_T* version;
}RocOsInfo_t;

typedef struct RocDriverInfo
{
    UINT32_T size;
    CHAR_T*  name;
    CHAR_T*  provider;
    CHAR_T*  version;
}RocDriverInfo_t;

typedef struct RocLoaderInfo
{
    UINT32_T size;
    CHAR_T*  name;
    CHAR_T*  provider;
    CHAR_T*  version;
}RocLoaderInfo_t;


typedef struct RocSTBInfo
{
    CHAR_T* socModel;     //��ȡ��ǰ��Ʒ��ʹ�õ���оƬ�������ͺ�
    CHAR_T* socProvider;  //��ȡ��оƬ�ĳ���
    CHAR_T* provider;     //��ȡ�����еĳ�������
    CHAR_T* type;         //�����е�����,ȡֵ��Χ���£�"DVB-C  ����"��"DVB-C��IP  ˫ģ"��IPTV"��"IPTV +·��"��"DVB-T  ����"��"DVB-T + IP  ˫ģ"��"DVB-S  ����"��"DVB-S + IP˫ģ"
    CHAR_T* brand;        //��ȡ�����е�Ʒ������
    CHAR_T* model;        //��ȡ�����е��ͺ�
    CHAR_T* serialNumber;//��ȡ�����е����к�
}RocSTBInfo_t;


typedef struct RocStoragePartitionInfo
{
    CHAR_T  name[64];               //��ȡ�豸��������
    UINT32_T size;               //��ȡ�豸������С
    UINT32_T freeSize;           //��ȡ�豸���з�����С
    CHAR_T  path[128];               //��ȡ�豸��������·��
    CHAR_T  fsType[64];             //��ȡ�豸�����ļ�ϵͳ����
}RocStoragePartitionInfo_t;


typedef struct RocStorageInfo
{
    CHAR_T  name[64];                           //��ȡ�豸����
    UINT32_T size;                           //��ȡ�豸��С
    UINT32_T freeSize;                       //��ȡ�豸���д�С
}RocStorageInfo_t;



/*�ļ�ϵͳ����*/
typedef enum RocStorageFSType
{
	EM_FS_UNKOWN,
	EM_FS_VFAT,     //vfat�ļ�ϵͳ����
	EM_FS_EXT2,     //ext2�ļ�ϵͳ����
	EM_FS_EXT3      //ext3�ļ�ϵͳ����
}RocStorageFSType_E;

/*
���ܣ���ȡ��������flashBlock����Ϣ�����������ܴ�С�ȣ�����μ�RocFlashBlockInfo_t
������
    info��RocFlashBlockInfo_t�ṹ��ָ�룬���ڴ洢RocFlashBlockInfo_t��Ϣ
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_get_flashBlockInfo(RocFlashBlockInfo_t* info);

/*
���ܣ���ȡflash��flashBlock���飬�����е�flashBlock����ϸ��Ϣ
������    
    num�������������������������������ʱ��ʾ�ϲ㴫���flashBlock����Ĵ�С��
        ������ʱ��ʾ�ײ�ʵ�ʴ��ڵ�flashBlock������
    flashBlocks��RocFlashBlock_t�ṹ������ָ�룬name��Ա�ڴ��ɵײ����
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_get_flashBlocks(RocFlashBlock_t* flashBlocks, UINT32_T* num);

/*
���ܣ���ȡ����ϵͳos�������Ϣ��������Ϣ�μ�RocOsInfo_t
������
    osInfo��os��Ϣ�ṹ��ָ�룬���ڴ洢os��Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_os_info(RocOsInfo_t* osInfo);

/*
���ܣ���ȡϵͳ�����������Ϣ��������Ϣ�μ�RocDriverInfo_t
������
    driverInfo��������Ϣ�ṹ��ָ�룬���ڴ洢������Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_driver_info(RocDriverInfo_t* driverInfo);

/*
���ܣ���ȡ����ϵͳloader�������Ϣ��������Ϣ�μ�RocLoaderInfo_t
������
    loaderInfo��loader��Ϣ�ṹ��ָ�룬���ڴ洢loader��Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_loader_info(RocLoaderInfo_t* loaderInfo);


/*
���ܣ���ȡ�����е������Ϣ��������Ϣ�μ�RocSTBInfo_t
������
    stbInfo��STB��Ϣ�ṹ��ָ�룬���ڴ洢STB��Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_stb_info(RocSTBInfo_t* stbInfo);


/*
���ܣ���ǰ�����ʾָ���Ŀ��Ʒ��ơ�
������lightName���ַ�����ָ����ǰ�����ʾ��:��text��,��mail��,��signal��,��audio��,��power��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_panel_display_light(CHAR_T* lightName);


/*
���ܣ�ǰ�����ʾָ���ı�����
�������ַ�������ʾ��ʾ���ı����ݻ�ʱ�䣬ʱ���ʽΪhh:mm:ss
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_panel_display_text(CHAR_T* text);

/*
���ܣ����ǰ�����ʾ��Ϣ
������lightName���ַ�����ȡֵ��Χ�μ�����2�еĶ���
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_panel_clear(CHAR_T* lightName);


/*
���ܣ���Ӧ�ò����м������������Ϣ���м���Ծ�ͨ��type��which��modifiers���Ե�֪����������Ϣ
������
    type��������Ϣ����
    which���������Ϣ����ֵ����ֵ�ͣ�16λ�����ƴ洢��ʮ���Ʒ�ʽʹ�ã�
    modifiers��������Ϣ����չ����ֵ
����ֵ����ֵ�ͣ�1Ϊ�ɹ�����������Ϣ��0Ϊ����ʧ��
��ע��
*/
INT32_T rocme_porting_send_event(INT32_T type, INT16_T which, CHAR_T* modifiers);



/*
����: ��ȡ�洢�豸�ĸ���
������
	��
����ֵ���豸����
��ע��
*/
UINT32_T rocme_porting_get_storage_num(void);



/*
����: ��ȡĳ���洢�豸�ķ�������
������
	storageName:  �豸����
����ֵ�����豸�ķ�������
��ע��
*/
UINT32_T rocme_porting_get_partition_num(CHAR_T* storageName);


/*
���ܣ�ж���豸
������storageName���ַ������豸����
����ֵ����ֵ�ͣ�1��ʾж�سɹ���0��ʾж��ʧ��
��ע��
*/
INT32_T rocme_porting_uninstall_storage(CHAR_T* storageName);

/*
���ܣ���ʽ���豸
���������
     storageName���ַ������豸����
     eFormatType:   ö�����ͣ���ʽ�����ļ�ϵͳ���ͣ����RocStorageFSType_E
����ֵ����ֵ�ͣ�1��ʾ��ʽ���ɹ���0��ʾ��ʽ��ʧ��
��ע��

*/
INT32_T rocme_porting_format_storage(CHAR_T* storageName, RocStorageFSType_E eFormatType);

/*
���ܣ���ȡ�洢�豸��Ϣ(���ơ���С�����У�����)��������Ϣ�μ�RocStorageInfo_t
������
    storageInfo���洢�豸��Ϣ�ṹ��ָ�룬���ڻ�ȡ�洢�豸��Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_storage_infos(RocStorageInfo_t* storageInfo, UINT32_T* storageNum);


/*
���ܣ���ȡ�洢�豸�ķ�����Ϣ�����ơ���С�����У�����·�����������ͣ���������Ϣ�μ�RocStorageInfo_t
������
    storagePartInfo���洢�豸�ķ�����Ϣ�ṹ��ָ�룬���ڻ�ȡ�洢�豸�ķ�����Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_storage_partition_infos(CHAR_T* storageName, RocStoragePartitionInfo_t* storagePartInfo, UINT32_T* storagePartNum);


/*
����  ����ȡ��ǰ��Ʒ�϶�̬�ڴ�Ĵ�С
����  ����
����ֵ����ֵ�ͣ���λ Mbyte��ֻ��
��ע  ����
*/
INT32_T rocme_porting_get_dram_size();


/*
����  ����̬�ڴ�Ĺ���Ƶ��
����  ����
����ֵ����ֵ�ͣ���λHundred HZ 
��ע  ����
*/
INT32_T rocme_porting_get_dram_frequency();

/*
����  ������Ĵ�С
����  ����
����ֵ����ֵ�ͣ���λ Mbyte��ֻ��
��ע  ����
*/
INT32_T rocme_porting_get_flash_size();


#ifdef __cplusplus
}
#endif

#endif

