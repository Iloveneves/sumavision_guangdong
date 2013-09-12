/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_eeprom.h

Author      : DSM

Description : The poriting interface & macro definition for EEPROM module.

History     :
              2009.12.20          Created         Jason
              2010.01.08          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTING_EEPROM_H_
#define _ROCME_PORTING_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/

typedef enum
{
    ROCME_NVRAM_DATA_BASIC         = 0,  /* 基本FFS, 保存重要但不经常变化的数据(如, 频道搜索结果) */
    ROCME_NVRAM_DATA_SKIN          = 1,  /* Skin专用 */
    ROCME_NVRAM_DATA_THIRD_PART    = 2,  /* 第三方共用 */
    ROCME_NVRAM_DATA_QUICK         = 3,  /* 立即写入的NVRAM */
    ROCME_NVRAM_DATA_APPMGR        = 4,  /* 保存下载应用程序 */
    ROCME_NVRAM_DATA_USERDEF       = 5,  /* 保存中间件下载的用户自定义数据*/
    ROCME_NVRAM_DATA_AUX           = 6,  /* 辅助FFS, 保存可以丢失且经常写的数据(如, cookie) */
	ROCME_NVRAM_DATA_BOOT          = 7,  /* BOOT程序 */
	ROCME_NVRAM_DATA_LOADER        = 8,  /* LOADER程序 */
    ROCME_NVRAM_DATA_ROOTFFS       = 9,  /* Rootfs for Application 0 */
    ROCME_NVRAM_DATA_SYSTEM        = 10, /* Kernel or OS for Application 0 */
    ROCME_NVRAM_DATA_APPSOFT       = 11, /* Application 0 */
    ROCME_NVRAM_DATA_UPGRADE_PARAM = 12, /* ipanel IP LOADER的升级参数区 */
    ROCME_NVRAM_DATA_ROOTFFS_1     = 13, /* Rootfs for Application 1 */
    ROCME_NVRAM_DATA_SYSTEM_1      = 14, /* Kernel or OS for Application 1 */
    ROCME_NVRAM_DATA_APPSOFT_1     = 15, /* Application 1 */
	ROCME_NVRAM_DATA_AD            = 16, /* 开机广告*/
	ROCME_NVRAM_DATA_INITVIDEO     = 17, /* 开机视频*/
	ROCME_NVRAM_DATA_INITIFRAME    = 18, /* 开机I帧*/
	ROCME_NVRAM_DATA_BASIC_EXT     = 19, /*BASIC的备份区，功能与BASIC区完全相同。用于双备份数据。注意：BASIC_EXT 的长度必须与BASIC区一样，否则中间件会报错*/
	ROCME_NVRAM_DATA_QUICK_EXT     = 20, /*QUICK的备份区，功能与QUICK区完全相同。用于双备份数据。注意：QUICK _EXT 的长度必须与QUICK区一样，否则中间件会报错*/
	ROCME_NVRAM_DATA_SYSINFO		= 100,/*system update info*/
	ROCME_NVRAM_DATA_TEST			= 101,
	ROCME_NVRAM_DATA_UNKNOWN
} ROCME_NVRAM_DATA_TYPE_e;
/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/

/**************************************************************************
函数名称: 
            rocme_porting_eeprom_init
功能说明: 
            eeprom存储设备初始化，中间件会在启动时调用此函数，若在启动中间件
        之前机顶盒已经做好了eeprom设备的初始化，此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            void
    输出参数：
            无
返    回： 
    成功 : 0            ( 初始化成功 )
    失败 : -1 或 错误码 ( 初始化失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_init(void); 

/**************************************************************************
函数名称: 
            rocme_porting_eeprom_info
功能说明: 
            获得eeprom存储空间的起始地址、块数和每块的长度，eeprom的最小
        空间不得小于1k。
参数说明：
    输入参数：
            无
    输出参数：
            [ *eep_addr   ] : 分配给中间件的eeprom的起始地址头指针
            [ num_of_sect ] : 分配给中间件的eeprom的总块数
            [ sect_size   ] : 分配给中间件的eeprom的每块的大小
返    回： 
    成功 : 0            ( eeprom基本信息获取成功 )
    失败 : -1 或 错误码 ( eeprom基本信息获取失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_info(UINT8_T **eep_addr, INT32_T *num_of_sect,  INT32_T *sect_size);

/**************************************************************************
函数名称: 
            rocme_porting_eeprom_read
功能说明: 
            从指定的eeprom存储空间的指定地址读取数据到指定的数据缓冲区中。
参数说明：
    输入参数：
            [ eep_addr    ] : 中间件读取eeprom的目标地址
            [ *buff_addr  ] : 读取数据的存储缓冲区头指针
            [ nbytes      ] : 需要读取的长度
    输出参数：
            无
返    回： 
    成功 : >=0的数值    ( 实际读取的数据长度  )
    失败 : -1 或 错误码 ( 读取eeprom内容失败  )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_read(UINT32_T eep_addr, UINT8_T *buff_addr, INT32_T nbytes);

/**************************************************************************
函数名称: 
            rocme_porting_eeprom_burn
功能说明: 
            将指定的数据写入到指定的eeprom存储区中，实现为同步方式写入。
参数说明：
    输入参数：
            [ eep_addr    ] : 中间件写入flash的目标地址
            [ *buff_addr  ] : 写入数据的存储缓冲区头指针
            [ nbytes      ] : 需要写入的长度
    输出参数：
            无
返    回： 
    成功 : >=0的数值    ( 实际写入的数据长度 )
    失败 : -1 或 错误码 ( 写入eeprom内容失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_burn(UINT32_T eep_addr, const INT8_T *buff_addr, INT32_T nbytes);

/**************************************************************************
函数名称: 
            rocme_porting_eeprom_status
功能说明: 
            判断当前eeprom的写入状态，此函数目前不做要求，可以实现为空，直接返
        回已经写成功( 1 )即可。
参数说明：
    输入参数：
            [ eep_addr    ] : 中间件写入eeprom的目标地址
            [ nbytes      ] : 写入的长度
    输出参数：
            无
返    回： 
    正在写 :  0
    写成功 :  1
    写失败 : -1 
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_status(UINT32_T eep_addr, INT32_T nbytes);

/**************************************************************************
函数名称: 
            rocme_porting_eeprom_erase
功能说明: 
            擦除指定eeprom存储空间中的数据。
参数说明：
    输入参数：
            [ eep_addr    ] : 中间件需要擦除eeprom的目标地址
            [ nbytes      ] : 擦除的长度
    输出参数：
            无
返    回： 
    成功 : 0            ( eeprom擦除成功 )
    失败 : -1 或 错误码 ( eeprom擦除失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_eeprom_erase(UINT32_T eep_addr, INT32_T nbytes);


#ifdef __cplusplus
}
#endif

#endif
