/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_errno.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


#include "hi_type.h"


#include "porter_rocme.h"


char blockname[4][10] = {"block1","block2","block3","block4"};
/*
功能：获取机顶盒中flashBlock的信息，如总数、总大小等，具体参见RocFlashBlockInfo_t
参数：
    info，RocFlashBlockInfo_t结构体指针，用于存储RocFlashBlockInfo_t信息
返回值：数值型，0表示成功，-1为错误
备注：
*/
INT32_T rocme_porting_get_flashBlockInfo(RocFlashBlockInfo_t* info)
{
	ROCME_TEST_PRINT
	info->num = 4;
	info->size = 128*1024*1024;
	return ROC_OK;
}


/*
功能：获取flash中flashBlock数组，即所有的flashBlock的详细信息
参数：    
    num，既是输入参数又是输出参数，做入参时表示上层传入的flashBlock数组的大小，
        做出参时表示底层实际存在的flashBlock数量。
    flashBlocks，RocFlashBlock_t结构体数组指针，name成员内存由底层分配
返回值：数值型，0表示成功，-1为错误
备注：
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
功能：获取操作系统os的相关信息，具体信息参见RocOsInfo_t
参数：
    osInfo，os信息结构体指针，用于存储os信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
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
功能：获取系统驱动的相关信息，具体信息参见RocDriverInfo_t
参数：
    driverInfo，驱动信息结构体指针，用于存储驱动信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
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
功能：获取升级系统loader的相关信息，具体信息参见RocLoaderInfo_t
参数：
    loaderInfo，loader信息结构体指针，用于存储loader信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
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
功能：获取机顶盒的相关信息，具体信息参见RocSTBInfo_t
参数：
    stbInfo，STB信息结构体指针，用于存储STB信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_stb_info(RocSTBInfo_t* stbInfo)
{
ROCME_TEST_PRINT
	static CHAR_T szbrand[] = "jiacai";
	static CHAR_T szmodel[] = "DC3550";
	static CHAR_T szprovider[] = "Huawei Device Co, Ltd.";
	static CHAR_T sztype[] = "DVB-C＋IP  双模";
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
功能：让前面板显示指定的控制符灯。
参数：lightName：字符串，指明了前面板显示灯:“text”,“mail”,“signal”,“audio”,“power”
返回值：数值型，0表示成功，-1为错误
备注：
*/
INT32_T rocme_porting_panel_display_light(CHAR_T* lightName)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}


/*
功能：前面板显示指定文本内容
参数：字符串，表示显示的文本内容或时间，时间格式为hh:mm:ss
返回值：数值型，0表示成功，-1为错误
备注：
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
功能：清除前面板显示信息
参数：lightName：字符串，取值范围参见方法2中的定义
返回值：数值型，0表示成功，-1为错误
备注：
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
功能：从应用层向中间件发送虚拟消息，中间件仍旧通过type，which，modifiers属性得知其是虚拟消息
参数：
    type：虚拟消息分类
    which：虚拟的消息代码值，数值型（16位二进制存储，十进制方式使用）
    modifiers：虚拟消息的扩展属性值
返回值：数值型，1为成功发送虚拟消息，0为发送失败
备注：
*/
INT32_T rocme_porting_send_event(INT32_T type, INT16_T which, CHAR_T* modifiers)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}

#if 0


/*
功能: 获取存储设备的个数
参数：
	无
返回值：设备个数
备注：
*/
UINT32_T rocme_porting_get_storage_num(void)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}




/*
功能: 获取某个存储设备的分区个数
参数：
	storageName:  设备名称
返回值：该设备的分区个数
备注：
*/
UINT32_T rocme_porting_get_partition_num(CHAR_T* storageName)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}



/*
功能：卸载设备
参数：storageName：字符串，设备名称
返回值：数值型，1表示卸载成功，0表示卸载失败
备注：
*/
INT32_T rocme_porting_uninstall_storage(CHAR_T* storageName)
{
	ROCME_TEST_PRINT
	return 1;;
}


/*
功能：格式化设备
输入参数：
     storageName：字符串，设备名称
     eFormatType:   枚举类型，格式化的文件系统类型，详见RocStorageFSType_E
返回值：数值型，1表示格式化成功，0表示格式化失败
备注：

*/
INT32_T rocme_porting_format_storage(CHAR_T* storageName, RocStorageFSType_E eFormatType)
{
	ROCME_TEST_PRINT
	return 1;
}


/*
功能：获取存储设备信息(名称、大小，空闲，分区)，具体信息参见RocStorageInfo_t
参数：
    storageInfo，存储设备信息结构体指针，用于获取存储设备信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_storage_infos(RocStorageInfo_t* storageInfo, UINT32_T* storageNum)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}



/*
功能：获取存储设备的分区信息（名称、大小，空闲，访问路径、分区类型），具体信息参见RocStorageInfo_t
参数：
    storagePartInfo，存储设备的分区信息结构体指针，用于获取存储设备的分区信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_storage_partition_infos(CHAR_T* storageName, RocStoragePartitionInfo_t* storagePartInfo, UINT32_T* storagePartNum)
{
	ROCME_TEST_PRINT
	return ROC_OK;
}

#endif

/*
功能  ：获取当前产品上动态内存的大小
参数  ：无
返回值：数值型，单位 Mbyte，只读
备注  ：无
*/
INT32_T rocme_porting_get_dram_size()
{
	ROCME_TEST_PRINT
	return 0x400000;
}



/*
功能  ：动态内存的工作频率
参数  ：无
返回值：数值型，单位Hundred HZ 
备注  ：无
*/
INT32_T rocme_porting_get_dram_frequency()
{
	ROCME_TEST_PRINT
	return 400000;
}


/*
功能  ：缓存的大小
参数  ：无
返回值：数值型，单位 Mbyte，只读
备注  ：无
*/
INT32_T rocme_porting_get_flash_size()
{
	ROCME_TEST_PRINT
	return 128;
}



