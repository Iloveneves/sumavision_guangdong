/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_flash.h

Author      : DSM

Description : The poriting interface & macro definition for flash module.

History     :
              2009.12.20          Created         Jason
              2010.01.08          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTING_FLASH_H_
#define _ROCME_PORTING_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/


/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/


/**************************************************************************
函数名称: 
            rocme_porting_flash_init
功能说明: 
            flash存储设备初始化，中间件会在启动时调用此函数，若在启动中间件
        之前机顶盒已经做好了flash设备的初始化，此函数可以实现为空，直接返回0。
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
INT32_T rocme_porting_flash_init(void);

/**************************************************************************
函数名称: 
            rocme_porting_flash_info
功能说明: 
            获得flash存储空间的起始地址、块数和每块的长度，建议给RocME中间件
        划分的flash memory每块合适尺寸是32k/64k/128k/256kBytes。但flash的最小
        空间不得小于512k。
参数说明：
    输入参数：
            无
    输出参数：
            [ *addr       ] : 分配给中间件的flash的起始地址头指针
            [ num_of_sect ] : 分配给中间件的flash的总块数
            [ sect_size   ] : 分配给中间件的flash的每块的大小
返    回： 
    成功 : 0            ( flash基本信息获取成功 )
    失败 : -1 或 错误码 ( flash基本信息获取失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_flash_info(UINT8_T **addr, INT32_T *num_of_sect,  INT32_T *sect_size);

/**************************************************************************
函数名称: 
            rocme_porting_flash_read
功能说明: 
            从指定的flash存储空间的指定地址读取数据到指定的数据缓冲区中。
参数说明：
    输入参数：
            [ flash_addr  ] : 中间件读取flash的目标地址
            [ *buff_addr  ] : 读取数据的存储缓冲区头指针
            [ nbytes      ] : 需要读取的长度
    输出参数：
            无
返    回： 
    成功 : >=0的数值    ( 实际读取的数据长度 )
    失败 : -1 或 错误码 ( 读取flash内容失败  )
修改记录：
**************************************************************************/
INT32_T rocme_porting_flash_read(UINT32_T flash_addr, UINT8_T *buff_addr, INT32_T nbytes);

/**************************************************************************
函数名称: 
            rocme_porting_flash_burn
功能说明: 
            将指定的数据写入到指定的flash存储区中，实现为同步方式写入。
参数说明：
    输入参数：
            [ flash_addr  ] : 中间件写入flash的目标地址
            [ *buff_addr  ] : 写入数据的存储缓冲区头指针
            [ nbytes      ] : 需要写入的长度
    输出参数：
            无
返    回： 
    成功 : >=0的数值    ( 实际写入的数据长度 )
    失败 : -1 或 错误码 ( 写入flash内容失败  )
修改记录：
**************************************************************************/
INT32_T rocme_porting_flash_burn(UINT32_T flash_addr, const UINT8_T *buff_addr, INT32_T nbytes);

/**************************************************************************
函数名称: 
            rocme_porting_flash_status
功能说明: 
            判断当前flash的写入状态，此函数目前不做要求，可以实现为空，直接返
        回已经写成功( 1 )即可。
参数说明：
    输入参数：
            [ flash_addr  ] : 中间件写入flash的目标地址
            [ nbytes      ] : 写入的长度
    输出参数：
            无
返    回： 
    正在写 :  0
    写成功 :  1
    写失败 : -1 
修改记录：
**************************************************************************/
INT32_T rocme_porting_flash_status(UINT32_T flash_addr, INT32_T nbytes);

/**************************************************************************
函数名称: 
            rocme_porting_flash_erase
功能说明: 
            擦除指定flash存储空间中的数据。
参数说明：
    输入参数：
            [ flash_addr  ] : 中间件需要擦除flash的目标地址
            [ nbytes      ] : 擦除的长度
    输出参数：
            无
返    回： 
    成功 : 0            ( flash擦除成功 )
    失败 : -1 或 错误码 ( flash擦除失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_flash_erase(UINT32_T flash_addr, INT32_T nbytes);

/**************************************************************************
函数名称: 
            rocme_porting_get_iframe_data
功能说明: 
            取得指定ID的I帧数据，目前中间件要求有2幅默认I帧，Iframe_id为0时，
        代表开机默认背景帧，Iframe_id为1时，代表音频节目背景帧，每幅I帧大小
        不可超过64Kb。
参数说明：
    输入参数：
            [ Iframe_id     ] : I帧编号
            [ *pdata        ] : 存储I帧buff的头指针
            [ container_len ] : 存储I帧buff的最大长度，目前RocME中间件定义其
                            为65536字节(64Kb)大小。
    输出参数：
            无
返    回： 
    成功 : 0            ( 获取I帧数据成功 )
    失败 : -1 或 错误码 ( 获取I帧数据失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_get_iframe_data(UINT32_T Iframe_id,const UINT8_T *pdata,const UINT32_T container_len);

/**************************************************************************
函数名称: 
            rocme_porting_save_Iframe
功能说明: 
            保存I帧到对应的I帧存储空间。
参数说明：
    输入参数：
            [ Iframe_id     ] : I帧编号
            [ *pdata        ] : 存储I帧buff的头指针
            [ container_len ] : I帧buff的长度，目前RocME中间件定义其最大为
                            65536字节(64Kb)大小。
    输出参数：
            无
返    回： 
    成功 : 0            ( 保存I帧数据成功 )
    失败 : -1 或 错误码 ( 保存I帧数据失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_save_Iframe(UINT32_T Iframe_id,const UINT8_T *pdata,const UINT32_T len); 

/**************************************************************************
函数名称: 
            rocme_porting_flash_save_boot_pic
功能说明: 
            保存开机图片到对应的flash空间。
参数说明：
    输入参数：
            [ type          ] : 文件保存方法，0为内存方式，1为文件方式。
            [ *data_ptr     ] : 图片内存地址或者存储路径
            [ data_len      ] : 图片大小
    输出参数：
            无
返    回： 
    成功 : 0            ( 保存数据成功 )
    失败 : -1 或 错误码 ( 保存数据失败 )
注意：
    保存完图片后，需要发送消息10602.
**************************************************************************/
INT32_T rocme_porting_flash_save_boot_pic(UINT8_T type, const CHAR_T *data_ptr, const UINT32_T data_len);

/**************************************************************************
函数名称: 
            rocme_porting_flash_set_boot_tag
功能说明: 
            将一个标识写入机顶盒。
参数说明：
    输入参数：
            [ index         ] : 该标识指定在时段2是运行应用，1是A类应用，0是默认应用
    输出参数：
            无
返    回： 
    成功 : 0            ( 标记设置成功 )
    失败 : -1 或 错误码 ( 标记设置失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_flash_set_boot_tag(UINT32_T index);

#ifdef __cplusplus
}
#endif

#endif
