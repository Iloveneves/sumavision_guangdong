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
    UINT32_T num;/*flashBlock总数*/
    UINT32_T size;/*flashBlock总大小*/
}RocFlashBlockInfo_t;

typedef struct RocFlashBlock
{
    CHAR_T*  name;/*该flashBlock名称*/
    UINT32_T size;/*该flashBlock大小*/
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
    CHAR_T* socModel;     //获取当前产品中使用的主芯片的名称型号
    CHAR_T* socProvider;  //获取主芯片的厂商
    CHAR_T* provider;     //获取机顶盒的厂商名称
    CHAR_T* type;         //机顶盒的类型,取值范围如下："DVB-C  单向"、"DVB-C＋IP  双模"、IPTV"，"IPTV +路由"、"DVB-T  单向"、"DVB-T + IP  双模"、"DVB-S  单向"、"DVB-S + IP双模"
    CHAR_T* brand;        //获取机顶盒的品牌名称
    CHAR_T* model;        //获取机顶盒的型号
    CHAR_T* serialNumber;//获取机顶盒的序列号
}RocSTBInfo_t;


typedef struct RocStoragePartitionInfo
{
    CHAR_T  name[64];               //获取设备分区名称
    UINT32_T size;               //获取设备分区大小
    UINT32_T freeSize;           //获取设备空闲分区大小
    CHAR_T  path[128];               //获取设备分区访问路径
    CHAR_T  fsType[64];             //获取设备分区文件系统类型
}RocStoragePartitionInfo_t;


typedef struct RocStorageInfo
{
    CHAR_T  name[64];                           //获取设备名称
    UINT32_T size;                           //获取设备大小
    UINT32_T freeSize;                       //获取设备空闲大小
}RocStorageInfo_t;



/*文件系统类型*/
typedef enum RocStorageFSType
{
	EM_FS_UNKOWN,
	EM_FS_VFAT,     //vfat文件系统类型
	EM_FS_EXT2,     //ext2文件系统类型
	EM_FS_EXT3      //ext3文件系统类型
}RocStorageFSType_E;

/*
功能：获取机顶盒中flashBlock的信息，如总数、总大小等，具体参见RocFlashBlockInfo_t
参数：
    info，RocFlashBlockInfo_t结构体指针，用于存储RocFlashBlockInfo_t信息
返回值：数值型，0表示成功，-1为错误
备注：
*/
INT32_T rocme_porting_get_flashBlockInfo(RocFlashBlockInfo_t* info);

/*
功能：获取flash中flashBlock数组，即所有的flashBlock的详细信息
参数：    
    num，既是输入参数又是输出参数，做入参时表示上层传入的flashBlock数组的大小，
        做出参时表示底层实际存在的flashBlock数量。
    flashBlocks，RocFlashBlock_t结构体数组指针，name成员内存由底层分配
返回值：数值型，0表示成功，-1为错误
备注：
*/
INT32_T rocme_porting_get_flashBlocks(RocFlashBlock_t* flashBlocks, UINT32_T* num);

/*
功能：获取操作系统os的相关信息，具体信息参见RocOsInfo_t
参数：
    osInfo，os信息结构体指针，用于存储os信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_os_info(RocOsInfo_t* osInfo);

/*
功能：获取系统驱动的相关信息，具体信息参见RocDriverInfo_t
参数：
    driverInfo，驱动信息结构体指针，用于存储驱动信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_driver_info(RocDriverInfo_t* driverInfo);

/*
功能：获取升级系统loader的相关信息，具体信息参见RocLoaderInfo_t
参数：
    loaderInfo，loader信息结构体指针，用于存储loader信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_loader_info(RocLoaderInfo_t* loaderInfo);


/*
功能：获取机顶盒的相关信息，具体信息参见RocSTBInfo_t
参数：
    stbInfo，STB信息结构体指针，用于存储STB信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_stb_info(RocSTBInfo_t* stbInfo);


/*
功能：让前面板显示指定的控制符灯。
参数：lightName：字符串，指明了前面板显示灯:“text”,“mail”,“signal”,“audio”,“power”
返回值：数值型，0表示成功，-1为错误
备注：
*/
INT32_T rocme_porting_panel_display_light(CHAR_T* lightName);


/*
功能：前面板显示指定文本内容
参数：字符串，表示显示的文本内容或时间，时间格式为hh:mm:ss
返回值：数值型，0表示成功，-1为错误
备注：
*/
INT32_T rocme_porting_panel_display_text(CHAR_T* text);

/*
功能：清除前面板显示信息
参数：lightName：字符串，取值范围参见方法2中的定义
返回值：数值型，0表示成功，-1为错误
备注：
*/
INT32_T rocme_porting_panel_clear(CHAR_T* lightName);


/*
功能：从应用层向中间件发送虚拟消息，中间件仍旧通过type，which，modifiers属性得知其是虚拟消息
参数：
    type：虚拟消息分类
    which：虚拟的消息代码值，数值型（16位二进制存储，十进制方式使用）
    modifiers：虚拟消息的扩展属性值
返回值：数值型，1为成功发送虚拟消息，0为发送失败
备注：
*/
INT32_T rocme_porting_send_event(INT32_T type, INT16_T which, CHAR_T* modifiers);



/*
功能: 获取存储设备的个数
参数：
	无
返回值：设备个数
备注：
*/
UINT32_T rocme_porting_get_storage_num(void);



/*
功能: 获取某个存储设备的分区个数
参数：
	storageName:  设备名称
返回值：该设备的分区个数
备注：
*/
UINT32_T rocme_porting_get_partition_num(CHAR_T* storageName);


/*
功能：卸载设备
参数：storageName：字符串，设备名称
返回值：数值型，1表示卸载成功，0表示卸载失败
备注：
*/
INT32_T rocme_porting_uninstall_storage(CHAR_T* storageName);

/*
功能：格式化设备
输入参数：
     storageName：字符串，设备名称
     eFormatType:   枚举类型，格式化的文件系统类型，详见RocStorageFSType_E
返回值：数值型，1表示格式化成功，0表示格式化失败
备注：

*/
INT32_T rocme_porting_format_storage(CHAR_T* storageName, RocStorageFSType_E eFormatType);

/*
功能：获取存储设备信息(名称、大小，空闲，分区)，具体信息参见RocStorageInfo_t
参数：
    storageInfo，存储设备信息结构体指针，用于获取存储设备信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_storage_infos(RocStorageInfo_t* storageInfo, UINT32_T* storageNum);


/*
功能：获取存储设备的分区信息（名称、大小，空闲，访问路径、分区类型），具体信息参见RocStorageInfo_t
参数：
    storagePartInfo，存储设备的分区信息结构体指针，用于获取存储设备的分区信息。
返回值：数值型，0表示成功，-1为错误
备注：入参结构体内存由上层分配，但其指针成员存放实际
    信息的内存由底层提供，如name成员指向的字符串内存由底层分配
*/
INT32_T rocme_porting_get_storage_partition_infos(CHAR_T* storageName, RocStoragePartitionInfo_t* storagePartInfo, UINT32_T* storagePartNum);


/*
功能  ：获取当前产品上动态内存的大小
参数  ：无
返回值：数值型，单位 Mbyte，只读
备注  ：无
*/
INT32_T rocme_porting_get_dram_size();


/*
功能  ：动态内存的工作频率
参数  ：无
返回值：数值型，单位Hundred HZ 
备注  ：无
*/
INT32_T rocme_porting_get_dram_frequency();

/*
功能  ：缓存的大小
参数  ：无
返回值：数值型，单位 Mbyte，只读
备注  ：无
*/
INT32_T rocme_porting_get_flash_size();


#ifdef __cplusplus
}
#endif

#endif

