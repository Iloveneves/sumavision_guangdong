/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_demux.h

Author      : DSM

Description : The poriting interface & macro definition for DEMUX module.

History     :
        2009.12.20          Created         Jason
        2010.01.08          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTNG_DEMUX_H_
#define _ROCME_PORTNG_DEMUX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/


/*SLOT的类型*/
typedef enum Roc_Slot_Type
{
    ROC_SLOT_TYPE_NULL      = 0x00,  /*used with inject carousel packet only flag*/
    ROC_SLOT_TYPE_SECTION   = 0x01,  /*for section data - Signal every section*/
    ROC_SLOT_TYPE_PES       = 0x02,  /*signal every complete PES packet except when signal_on_every_transport_packet is supplied as a flag*/
    ROC_SLOT_TYPE_RAW       = 0x03,  /*Raw transport packets, signalled every packet*/
    ROC_SLOT_TYPE_PCR       = 0x04,  /*specifies that the data collected on this slot is collected for PCR gathering purposes*/
    ROC_SLOT_TYPE_RESERVE   = 0xFF   /*扩展保留*/
}Roc_Slot_Type_e;

/*FILTER的类型*/
typedef enum Roc_Filter_Type
{
    ROC_FILTER_TYPE_SECTION        = 0x00,  /*Provides 8 byte filter/mask*/
    ROC_FILTER_TYPE_PES            = 0x01,  /*Filter PES*/
    ROC_FILTER_TYPE_TSHEADER       = 0x02,  /*Filter TSHeader*/
    ROC_FILTER_TYPE_PES_STREAMID   = 0x03,  /*Filter PES stream ID*/
    ROC_FILTER_TYPE_NEG_MATCH      = 0x04,  /*Negative Match Mode filtering*/
    ROC_FILTER_TYPE_RESERVE        = 0xFF   /*扩展保留*/
}Roc_Filter_Type_e;


/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/


/**************************************************************************
函数名称: 
            rocme_porting_demux_init
功能说明: 
            DEMUX功能初始化，中间件会在启动时调用此函数，若在启动中间件之前
        机顶盒已经做好了DEMUX的初始化，此函数可以实现为空，直接返回0。
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
INT32_T rocme_porting_demux_init(void);

/**************************************************************************
函数名称: 
            rocme_porting_demux_term
功能说明: 
            卸载DEMUX功能。目前此函数可以实现为空。
参数说明：
    输入参数：
            void
    输出参数：
            无
返    回： 
    成功 : 0            ( 卸载成功 )
    失败 : -1 或 错误码 ( 卸载失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_demux_term(void);

/**************************************************************************
函数名称: 
            rocme_porting_slot_query_PID
功能说明: 
            指定数据通道上，查询一个PID是否已经被某个slot(包括中间件使用的
        slot和中间件之外的slot)占用，若平台不支持slot的PID设定不能重复，此
        功能必须实现。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ pid           ] : 需要查询的PID值
    输出参数：
            
返    回： 
    此PID未被占用 :  0
    此PID已被占用 : -1
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_query_PID(const INT32_T channel_index,const UINT16_T pid);

/**************************************************************************
函数名称: 
            rocme_porting_slot_alloc
功能说明: 
            在指定的数据通道上申请分配一个slot(指定slot的类型、buff的大小)，
        若成功申请到slot，返回一个slot的控制ID，中间件获得对此slot的控制权，
        即通过此ID对此slot设备进行修改、启动、释放等具体操作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ slot_type     ] : slot的类型，具体如下:
                                ROC_SLOT_TYPE_NULL     -  used with inject carousel 
                            packet only flag
                                ROC_SLOT_TYPE_SECTION  -  for section data - Signal 
                            every section
                                ROC_SLOT_TYPE_PES      -  signal every complete PES
                            packet except when signal_on_every_transport_packet is 
                            supplied as a flag
                                ROC_SLOT_TYPE_RAW      -  Raw transport packets, si-
                            -gnalled every packet
                                ROC_SLOT_TYPE_PCR      -  specifies that the data c-
                            -ollected on this slot is collected for PCR gathering purposes
                                ROC_SLOT_TYPE_RESERVE  -  扩展保留
             [ buff_size    ] : 需要开辟的slot使用的buff的大小，中间件除特殊情况外，
                            会申请64KB。
    输出参数：
            无
返    回： 
    成功 : 申请到的slot控制ID ( 申请成功 )
    失败 : -1 或 错误码       ( 申请失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_alloc(const INT32_T channel_index,const Roc_Slot_Type_e slot_type,const INT32_T buff_size);

/**************************************************************************
函数名称: 
            rocme_porting_slot_modify
功能说明: 
            根据slot_ID，修改相应的slot设备的一级过滤条件(即具体PID值)。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ pid        ] : 需要设置的一级过滤条件值
    输出参数：
            无
返    回： 
    成功 : 0            ( 修改slot一级过滤条件成功 )
    失败 : -1 或 错误码 ( 修改slot一级过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_modify(const INT32_T slot_ID,const UINT16_T pid);

/**************************************************************************
函数名称: 
            rocme_porting_slot_clear
功能说明: 
            根据slot_ID，清除其设置的一级过滤条件(即具体的PID值)。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 清除slot过滤条件成功 )
    失败 : -1 或 错误码 ( 清除slot过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_clear(const INT32_T slot_ID);

/**************************************************************************
函数名称: 
            rocme_porting_slot_start
功能说明: 
            启动一个slot设备开始过滤数据，如果底层平台的slot设备无此设置的实现，
        则此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 启动slot设备成功 )
    失败 : -1 或 错误码 ( 启动slot设备失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_start(const INT32_T slot_ID);

/**************************************************************************
函数名称: 
            rocme_porting_slot_stop
功能说明: 
            停止一个slot设备过滤数据，如果底层平台的slot设备无此设置的实现，
        则此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 停止slot设备成功 )
    失败 : -1 或 错误码 ( 停止slot设备失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_stop(const INT32_T slot_ID);

/**************************************************************************
函数名称: 
            rocme_porting_slot_free
功能说明: 
            释放掉对一个指定slot的控制权。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 释放成功 )
    失败 : -1 或 错误码 ( 释放失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_free(const INT32_T slot_ID);

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_wait
功能说明: 
            指定数据通道索引，中间件通过此方法主动查询是否有slot过滤到数据，
        并且可以设置等待超时时限，若此数据通道上过滤到了数据，则返回过滤到
        了数据的slot控制ID。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ time_out_ms   ] : 超时时间，单位为毫秒(ms)
    输出参数：
            
返    回： 
    成功 : slot控制ID   ( 成功查询到有slot过滤到数据 )
    失败 : -1 或 错误码 ( 查询失败/slot在time_out_ms时限内未过滤到数据 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait(const INT32_T channel_index,const INT32_T time_out_ms);

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_wait_multi
功能说明: 
            指定数据通道索引，中间件通过此方法主动查询是否有slot过滤到数据，
        并且可以设置等待超时时限，若此数据通道上过滤到了数据，则将获取到数
        据的slot赋给slot_ID_ar数组成员,并修改*count为已经获取到数据的slot个数。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ time_out_ms   ] : 超时时间，单位为毫秒(ms)
            [ *count        ] : slot_ID_ar数组成员最大个数
    输出参数：
            [ slot_ID_ar    ] : 获取到数据的slot
            [ *count        ] : 已经获取到数据的slot的个数
返    回： 
    成功 : 0
    失败 : -1 或 错误码 ( 查询失败/slot在time_out_ms时限内未过滤到数据 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait_multi(const INT32_T channel_index, INT32_T *slot_ID_ar, INT32_T *count , const INT32_T time_out_ms);

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_get
功能说明: 
            从指定slot的buff中的复制(提取)出指定长度的数据，中间件只有在调用
        了rocme_porting_slot_buff_wait后，才会使用此函数判断过滤的数据的归属。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ *buff_ptr  ] : 存储提取到的数据的buff的头指针
            [ buff_size  ] : 需要提取的数据的长度，即存储buff的长度
    输出参数：
            [ *data_size ] : 实际提取到的数据的长度
返    回： 
    成功 : 0            ( 提取数据成功 )
    失败 : -1 或 错误码 ( 提取数据失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_get(const INT32_T slot_ID, UINT8_T *buff_ptr, const UINT32_T buff_size, UINT32_T *data_size);

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_read
功能说明: 
            从指定的slot的buff中读取数据，读取数据后，要求清空buff。中间件会
        要求将slot的buff中的数据读到2个buff中，分别是data0和data1，读取数据时
        ，先将数据读到data0中，当data0放满后，再将数据读取到data1中，当空间不
        够时，返回读取失败。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
            [ *p_data0   ] : 存储缓冲区0的头指针
            [ size0      ] : 存储缓冲区0的长度
            [ *p_data1   ] : 存储缓冲区1的头指针
            [ size1      ] : 存储缓冲区1的长度
    输出参数：
            [ *datasize  ] : 实际读取到的数据长度
返    回： 
    成功 : 0            ( 读取数据成功 )
    失败 : -1 或 错误码 ( 读取数据失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_read(const INT32_T slot_ID, UINT8_T *p_data0, UINT32_T size0, UINT8_T *p_data1, UINT32_T size1, UINT32_T *datasize);

/**************************************************************************
函数名称: 
            rocme_porting_slot_buff_flush
功能说明: 
            清空指定的slot的buff。
参数说明：
    输入参数：
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 清除指定slot的buff成功 )
    失败 : -1 或 错误码 ( 清除指定slot的buff失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_slot_buff_flush(const INT32_T slot_ID);

/**************************************************************************
函数名称: 
            rocme_porting_filter_alloc
功能说明: 
            在指定的数据通道上申请分配一个filter(指定filter的类型)，若成功申
        请到filter，返回一个filter的控制ID，中间件获得对此filter的控制权，即
        通过此ID对此filter设备进行修改、启动、释放等具体操作。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值
            [ filter_type   ] : filter的类型，具体如下:
                                ROC_FILTER_TYPE_SECTION       -  Provides 8 byte filter/mask
                                ROC_FILTER_TYPE_PES           -  Filter PES
                                ROC_FILTER_TYPE_TSHEADER      -  Filter TSHeader
                                ROC_FILTER_TYPE_PES_STREAMID  -  Filter PES stream ID
                                ROC_FILTER_TYPE_NEG_MATCH     -  Negative Match Mode filtering
                                ROC_FILTER_TYPE_RESERVE       -  扩展保留
    输出参数：
            无
返    回： 
    成功 : 申请到的filter控制ID ( 申请成功 )
    失败 : -1 或 错误码         ( 申请失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_alloc(const INT32_T channel_index,const Roc_Filter_Type_e filter_type);

/**************************************************************************
函数名称: 
            rocme_porting_filter_associate
功能说明: 
            将指定的slot和filter关联起来。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 关联成功 )
    失败 : -1 或 错误码 ( 关联失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_associate(const INT32_T filter_ID,const INT32_T slot_ID);

/**************************************************************************
函数名称: 
            rocme_porting_filter_disassociate
功能说明: 
            将指定的slot和filter断开。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ slot_ID    ] : slot设备的控制ID，由rocme_porting_slot_alloc获取到        
    输出参数：
            无
返    回： 
    成功 : 0            ( 断开成功 )
    失败 : -1 或 错误码 ( 断开失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_disassociate(const INT32_T filter_ID,const INT32_T slot_ID);

/**************************************************************************
函数名称: 
            rocme_porting_filter_modify
功能说明: 
            根据filter_ID，修改相应的filter设备的二级过滤条件(即具体cofe和mask值)。
        例如，过滤TDT，设置这两项为:
        cafe[8]赋值为{0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        mask[8]赋值为{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00}.
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
            [ *cofe      ] : 二级过滤条件头指针
            [ c_size     ] : 二级过滤条件长度
            [ *mask      ] : 二级过滤条件掩码值头指针
            [ m_size     ] : 二级过滤条件掩码值长度
            [ *nega      ] : 二级过滤条件非模式标识
            [ m_nega     ] : 二级过滤条件非模式标识长度
    输出参数：

返    回： 
    成功 : 0            ( 修改二级过滤条件成功 )
    失败 : -1 或 错误码 ( 修改二级过滤条件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_modify(const INT32_T filter_ID,
                                    const UINT8_T*cofe,const UINT8_T c_size,
                                    const UINT8_T*mask,const UINT8_T m_size,
                                    const UINT8_T*nega,const UINT8_T m_nega);

/**************************************************************************
函数名称: 
            rocme_porting_filter_start
功能说明: 
            根据filter_ID，启动一个filter设备开始工作。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( filter设备启动成功 )
    失败 : -1 或 错误码 ( filter设备启动失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_start(const INT32_T filter_ID);

/**************************************************************************
函数名称: 
            rocme_porting_filter_stop
功能说明: 
            根据filter_ID，停止一个filter设备的工作。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( filter设备停止成功 )
    失败 : -1 或 错误码 ( filter设备停止失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_stop(const INT32_T filter_ID);

/**************************************************************************
函数名称: 
            rocme_porting_filter_free
功能说明: 
            释放掉对一个fitler设备的控制权。
参数说明：
    输入参数：
            [ filter_ID  ] : filter设备的控制ID，由rocme_porting_filter_alloc获取到
    输出参数：
            无
返    回： 
    成功 : 0            ( 释放成功 )
    失败 : -1 或 错误码 ( 释放失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_filter_free(const INT32_T filter_ID);


#ifdef __cplusplus
}
#endif

#endif
