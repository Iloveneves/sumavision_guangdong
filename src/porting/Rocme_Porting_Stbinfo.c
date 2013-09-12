/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_errno.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


#include "hi_type.h"


#include "porter_rocme.h"


char blockname[4][10] = {"block1","block2","block3","block4"};
/*
���ܣ���ȡ��������flashBlock����Ϣ�����������ܴ�С�ȣ�����μ�RocFlashBlockInfo_t
������
    info��RocFlashBlockInfo_t�ṹ��ָ�룬���ڴ洢RocFlashBlockInfo_t��Ϣ
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_get_flashBlockInfo(RocFlashBlockInfo_t* info)
{
	ROCME_TEST_PRINT
	info->num = 4;
	info->size = 128*1024*1024;
	return ROC_OK;
}


/*
���ܣ���ȡflash��flashBlock���飬�����е�flashBlock����ϸ��Ϣ
������    
    num�������������������������������ʱ��ʾ�ϲ㴫���flashBlock����Ĵ�С��
        ������ʱ��ʾ�ײ�ʵ�ʴ��ڵ�flashBlock������
    flashBlocks��RocFlashBlock_t�ṹ������ָ�룬name��Ա�ڴ��ɵײ����
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_get_flashBlocks(RocFlashBlock_t* flashBlocks, UINT32_T* num)
{
	ROCME_TEST_PRINT
	if((*num <4)||(flashBlocks == NULL))
	{
		ROCME_PRINTF(ROCME_LOG_ERROR," params err\n");
		return ROC_ERR;
	}
	HI_U32 i;
	for(i=0;i<4;i++)
	{
		flashBlocks->size = 1024*1024;
		flashBlocks->name = blockname[i];
	}
	*num = 4;
	return ROC_OK;
}


/*
���ܣ���ȡ����ϵͳos�������Ϣ��������Ϣ�μ�RocOsInfo_t
������
    osInfo��os��Ϣ�ṹ��ָ�룬���ڴ洢os��Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_os_info(RocOsInfo_t* osInfo)
{
ROCME_TEST_PRINT
	static CHAR_T szName[] = "linux";
    static CHAR_T szProvider[] = "Hisi";
    static CHAR_T szVersion[] = "2.6";

    if(osInfo == NULL)
    {
        return ROC_ERR;
    }

    osInfo->name = szName;
    osInfo->provider = szProvider;
    osInfo->version = szVersion;

  
	return ROC_OK;
}


/*
���ܣ���ȡϵͳ�����������Ϣ��������Ϣ�μ�RocDriverInfo_t
������
    driverInfo��������Ϣ�ṹ��ָ�룬���ڴ洢������Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_driver_info(RocDriverInfo_t* driverInfo)
{
	ROCME_TEST_PRINT
	static CHAR_T szName[] = "Hi3716M";
	static CHAR_T szProvider[] = "Hisi";
	static CHAR_T szVersion[] = "V100R001C00SPC040";
	
	if(driverInfo == NULL)
	{
		return ROC_ERR;
	}
	
	driverInfo->name = szName;
	driverInfo->provider = szProvider;
	driverInfo->version = szVersion;
	driverInfo->size = 6*1024*1024;
	
	return ROC_OK;

}


/*
���ܣ���ȡ����ϵͳloader�������Ϣ��������Ϣ�μ�RocLoaderInfo_t
������
    loaderInfo��loader��Ϣ�ṹ��ָ�룬���ڴ洢loader��Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_loader_info(RocLoaderInfo_t* loaderInfo)
{
ROCME_TEST_PRINT
	static CHAR_T szName[] = "jiacai loader";
	static CHAR_T szProvider[] = "jiacai";
	static CHAR_T szVersion[] = "1.0";
	
	if(loaderInfo == NULL)
	{
		return ROC_ERR;
	}
	
	loaderInfo->name = szName;
	loaderInfo->provider = szProvider;
	loaderInfo->version = szVersion;
	loaderInfo->size = 0;
	
	return ROC_OK;

}



/*
���ܣ���ȡ�����е������Ϣ��������Ϣ�μ�RocSTBInfo_t
������
    stbInfo��STB��Ϣ�ṹ��ָ�룬���ڴ洢STB��Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_stb_info(RocSTBInfo_t* stbInfo)
{
ROCME_TEST_PRINT
	static CHAR_T szbrand[] = "jiacai";
	static CHAR_T szmodel[] = "DC3550";
	static CHAR_T szprovider[] = "Huawei Device Co, Ltd.";
	static CHAR_T sztype[] = "DVB-C��IP  ˫ģ";
	static CHAR_T szsocProvider[] = "Hisi";
	static CHAR_T szsocModel[] = "Hi3716M";
	
	if(NULL == stbInfo)
	{
		return ROC_ERR;
	}
	
	stbInfo->brand = szbrand;
	stbInfo->model = szmodel;
	stbInfo->provider = szprovider;
	stbInfo->type = sztype;
	stbInfo->socProvider = szsocProvider;
	stbInfo->socModel = szsocModel;
	
	return ROC_OK;

}



/*
���ܣ���ǰ�����ʾָ���Ŀ��Ʒ��ơ�
������lightName���ַ�����ָ����ǰ�����ʾ��:��text��,��mail��,��signal��,��audio��,��power��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_panel_display_light(CHAR_T* lightName)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}


/*
���ܣ�ǰ�����ʾָ���ı�����
�������ַ�������ʾ��ʾ���ı����ݻ�ʱ�䣬ʱ���ʽΪhh:mm:ss
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_panel_display_text(CHAR_T* text)
{
	ROCME_TEST_PRINT
	CHAR_T buffer[8] = {0};
    rocme_porting_dprintf("%s: %s\n", __FUNCTION__, text);
    if(NULL == text)
    {
        rocme_porting_frontpanel_show_2point(ROC_FALSE);
        rocme_porting_frontpanel_show_string("    ", strlen("    "));
    }
    else
    {
        if (text[0] == ':')
        {
            buffer[0] = '0';
            buffer[1] = '0';
            buffer[2] = text[1];
            buffer[3] = text[2];
            rocme_porting_frontpanel_show_2point(ROC_TRUE);
        }
        else if (text[1] == ':')
        {
            buffer[0] = '0';
            buffer[1] = text[0];
            buffer[2] = text[2];
            buffer[3] = text[3];
            rocme_porting_frontpanel_show_2point(ROC_TRUE);
        }
        else if (text[2] == ':')
        {
            buffer[0] = text[0];
            buffer[1] = text[1];
            buffer[2] = text[3];
            buffer[3] = text[4];
            rocme_porting_frontpanel_show_2point(ROC_TRUE);
        }
        else
        {
            rocme_porting_frontpanel_show_2point(ROC_FALSE);
            memcpy(buffer, text, 4);
        }         

        rocme_porting_frontpanel_show_string(buffer, 4);
    }
	return ROC_OK;
}


/*
���ܣ����ǰ�����ʾ��Ϣ
������lightName���ַ�����ȡֵ��Χ�μ�����2�еĶ���
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע��
*/
INT32_T rocme_porting_panel_clear(CHAR_T* lightName)
{
	ROCME_TEST_PRINT
	if(0 == strncmp(lightName, "text", strlen("text")))
    {
        rocme_porting_frontpanel_show_2point(ROC_FALSE);
        rocme_porting_frontpanel_show_string("    ", strlen("    "));
    }
	return ROC_OK;
}



/*
���ܣ���Ӧ�ò����м������������Ϣ���м���Ծ�ͨ��type��which��modifiers���Ե�֪����������Ϣ
������
    type��������Ϣ����
    which���������Ϣ����ֵ����ֵ�ͣ�16λ�����ƴ洢��ʮ���Ʒ�ʽʹ�ã�
    modifiers��������Ϣ����չ����ֵ
����ֵ����ֵ�ͣ�1Ϊ�ɹ�����������Ϣ��0Ϊ����ʧ��
��ע��
*/
INT32_T rocme_porting_send_event(INT32_T type, INT16_T which, CHAR_T* modifiers)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}

#if 0


/*
����: ��ȡ�洢�豸�ĸ���
������
	��
����ֵ���豸����
��ע��
*/
UINT32_T rocme_porting_get_storage_num(void)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}




/*
����: ��ȡĳ���洢�豸�ķ�������
������
	storageName:  �豸����
����ֵ�����豸�ķ�������
��ע��
*/
UINT32_T rocme_porting_get_partition_num(CHAR_T* storageName)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}



/*
���ܣ�ж���豸
������storageName���ַ������豸����
����ֵ����ֵ�ͣ�1��ʾж�سɹ���0��ʾж��ʧ��
��ע��
*/
INT32_T rocme_porting_uninstall_storage(CHAR_T* storageName)
{
	ROCME_TEST_PRINT
	return 1;;
}


/*
���ܣ���ʽ���豸
���������
     storageName���ַ������豸����
     eFormatType:   ö�����ͣ���ʽ�����ļ�ϵͳ���ͣ����RocStorageFSType_E
����ֵ����ֵ�ͣ�1��ʾ��ʽ���ɹ���0��ʾ��ʽ��ʧ��
��ע��

*/
INT32_T rocme_porting_format_storage(CHAR_T* storageName, RocStorageFSType_E eFormatType)
{
	ROCME_TEST_PRINT
	return 1;
}


/*
���ܣ���ȡ�洢�豸��Ϣ(���ơ���С�����У�����)��������Ϣ�μ�RocStorageInfo_t
������
    storageInfo���洢�豸��Ϣ�ṹ��ָ�룬���ڻ�ȡ�洢�豸��Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_storage_infos(RocStorageInfo_t* storageInfo, UINT32_T* storageNum)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}



/*
���ܣ���ȡ�洢�豸�ķ�����Ϣ�����ơ���С�����У�����·�����������ͣ���������Ϣ�μ�RocStorageInfo_t
������
    storagePartInfo���洢�豸�ķ�����Ϣ�ṹ��ָ�룬���ڻ�ȡ�洢�豸�ķ�����Ϣ��
����ֵ����ֵ�ͣ�0��ʾ�ɹ���-1Ϊ����
��ע����νṹ���ڴ����ϲ���䣬����ָ���Ա���ʵ��
    ��Ϣ���ڴ��ɵײ��ṩ����name��Աָ����ַ����ڴ��ɵײ����
*/
INT32_T rocme_porting_get_storage_partition_infos(CHAR_T* storageName, RocStoragePartitionInfo_t* storagePartInfo, UINT32_T* storagePartNum)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}

#endif

/*
����  ����ȡ��ǰ��Ʒ�϶�̬�ڴ�Ĵ�С
����  ����
����ֵ����ֵ�ͣ���λ Mbyte��ֻ��
��ע  ����
*/
INT32_T rocme_porting_get_dram_size()
{
	ROCME_TEST_PRINT
	return 0x400000;
}



/*
����  ����̬�ڴ�Ĺ���Ƶ��
����  ����
����ֵ����ֵ�ͣ���λHundred HZ 
��ע  ����
*/
INT32_T rocme_porting_get_dram_frequency()
{
	ROCME_TEST_PRINT
	return 400000;
}


/*
����  ������Ĵ�С
����  ����
����ֵ����ֵ�ͣ���λ Mbyte��ֻ��
��ע  ����
*/
INT32_T rocme_porting_get_flash_size()
{
	ROCME_TEST_PRINT
	return 128;
}



