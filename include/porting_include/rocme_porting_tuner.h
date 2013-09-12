/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_tuner.h

Author      : DSM

Description : The poriting interface & macro definition for TUNER module.

History     :
              2009.12.20          Created         Jason
              2010.01.10          Modified        DSM
*******************************************************************************/
#ifndef _ROCME_PORTING_TUNER_H_
#define _ROCME_PORTING_TUNER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/
/*  refer Digital video broadcasting:  specification for Chinese service information (SI) : 
                cable_delivery_system_descriptor( ),
                satellite_delivery_system_descriptor( ),
                terrestrial_delivery_system_descriptor( ).                 */ 

/*高频头类型*/
typedef enum Roc_Tuner_Type
{
    ROC_TUNER_TYPE_CABLE            = 0x00,  /*有线类型    */
    ROC_TUNER_TYPE_TERRAIN          = 0x01,  /*地面无线类型*/
    ROC_TUNER_TYPE_SATELITE         = 0x02,  /*卫星信号类型*/
    ROC_TUNER_TYPE_RESERVE          = 0xFF   /*预留*/
}Roc_Tuner_Type_e;

/*向前纠错外码类型*/
typedef enum Roc_Signal_FEC_Outer
{
    ROC_SIGNAL_FEC_OUTER_NONE       = 0x0000,  /*未定义     */
    ROC_SIGNAL_FEC_OUTER_WITHOUT    = 0x0001,  /*无FEC外码  */
    ROC_SIGNAL_FEC_OUTER_RS         = 0x0010,  /*RS(204/188)*/
    ROC_SIGNAL_FEC_OUTER_RESERVE    = 0xFF     /*预留*/
}Roc_Signal_FEC_Outer_e;

/*向前纠错内码类型*/
typedef enum Roc_Signal_FEC_Inner
{
    ROC_SIGNAL_FEC_INNER_NONE                   = 0x0000,  /*未定义     */
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_1_2        = 0x0001,  /*卷积码率1/2*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_2_3        = 0x0010,  /*卷积码率2/3*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_3_4        = 0x0011,  /*卷积码率3/4*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_5_6        = 0x0100,  /*卷积码率5/6*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_7_8        = 0x0101,  /*卷积码率7/8*/
    ROC_SIGNAL_FEC_INNER_CONVOLUTION_WITHOUT    = 0x1111,  /*无卷积编码 */
    ROC_SIGNAL_FEC_INNER_RESERVE                = 0x0110   /*预留*/
}Roc_Signal_FEC_Inner_e;

/*有线调制方式类型*/
typedef enum Roc_CableTnr_Modulation
{
    ROC_CABLETNR_QAM_NONE     = 0x00,  /*未定义 */
    ROC_CABLETNR_QAM_16_T     = 0x01,  /*16 -QAM*/
    ROC_CABLETNR_QAM_32_T     = 0x02,  /*32 -QAM*/
    ROC_CABLETNR_QAM_64_T     = 0x03,  /*64 -QAM*/
    ROC_CABLETNR_QAM_128_T    = 0x04,  /*128-QAM*/
    ROC_CABLETNR_QAM_256_T    = 0x05,  /*256-QAM*/
    ROC_CABLETNR_QAM_RESERVE  = 0xFF   /*预留*/
}Roc_CableTnr_Modulation_e;

/*卫星信号参数-极化方式类型*/
typedef enum Roc_SateliteTnr_Polarization
{
    ROC_SATELITETNR_POLARIZATION_HORIZONTAL       = 0x00,  /*线性   水平极化*/
    ROC_SATELITETNR_POLARIZATION_VERTICAL         = 0x01,  /*线性   垂直极化*/
    ROC_SATELITETNR_POLARIZATION_LEFT_ROTUNDITY   = 0x10,  /*环型极化 左半圆*/
    ROC_SATELITETNR_POLARIZATION_RIGHT_ROTUNDITY  = 0x11   /*环型极化 右半圆*/
}Roc_SateliteTnr_Polarization_e;

/*卫星调制方式类型*/
typedef enum Roc_SateliteTnr_Modulation
{
    ROC_SATELITETNR_SATEMODUL_NONE          = 0x00,  /*未定义*/
    ROC_SATELITETNR_QPSK_T                  = 0x01,  /*QPSK  */
    ROC_SATELITETNR_SATEMODUL_RESERVE       = 0xFF   /*预留*/
}Roc_SateliteTnr_Modulation_e;

/*地面传送系统带宽类型*/
typedef enum Roc_TerrainTnr_Bandwidth
{
    ROC_TERRAINTNR_BANDWIDTH_8MHz           = 0x000,  /*8MHz带宽*/
    ROC_TERRAINTNR_BANDWIDTH_7MHz           = 0x001,  /*7MHz带宽*/
    ROC_TERRAINTNR_BANDWIDTH_6MHz           = 0x010,  /*6MHz带宽*/
    ROC_TERRAINTNR_BANDWIDTH_RESERVE        = 0x111   /*预留*/
}Roc_TerrainTnr_Bandwidth_e;

/*地面传送系统使用的星座模式类型*/
typedef enum Roc_TerrainTnr_Constellation
{
    ROC_TERRAINTNR_CONSTELLATION_QPSK       = 0x00,  /*QPSK  */
    ROC_TERRAINTNR_CONSTELLATION_16QAM      = 0x01,  /*16-QAM*/
    ROC_TERRAINTNR_CONSTELLATION_64QAM      = 0x10,  /*64-QAM*/
    ROC_TERRAINTNR_CONSTELLATION_RESERVE    = 0x11   /*预留*/
}Roc_TerrainTnr_Constellation_e;

/*地面传送系统分层类型*/
typedef enum Roc_TerrainTnr_Hierarchy_info
{
    ROC_TERRAINTNR_HIERARCHY_NONE           = 0x000,  /*未分层*/
    ROC_TERRAINTNR_HIERARCHY_ALPHA_1        = 0x001,  /*α=1  */
    ROC_TERRAINTNR_HIERARCHY_ALPHA_2        = 0x010,  /*α=2  */
    ROC_TERRAINTNR_HIERARCHY_ALPHA_4        = 0x011,  /*α=4  */
    ROC_TERRAINTNR_HIERARCHY_RESERVE        = 0x111   /*预留*/
}Roc_TerrainTnr_Hierarchy_info_e;

/*地面传送系统保护间隔类型*/
typedef enum Roc_TerrainTnr_Guard_Interval
{
    ROC_TERRAINTNR_GUARD_INTERVAL_1_32      = 0x00,  /*间隔值1/32*/
    ROC_TERRAINTNR_GUARD_INTERVAL_1_16      = 0x01,  /*间隔值1/16*/
    ROC_TERRAINTNR_GUARD_INTERVAL_1_8       = 0x10,  /*间隔值1/8 */
    ROC_TERRAINTNR_GUARD_INTERVAL_1_4       = 0x11,  /*间隔值1/4 */
    ROC_TERRAINTNR_GUARD_INTERVAL_RESERVE   = 0xFF   /*预留*/
}Roc_TerrainTnr_Guard_Interval_e;

/*地面传送系统OFDM帧中的载波数类型*/
typedef enum Roc_TerrainTnr_Transmission_mode
{
    ROC_TERRAINTNR_TRANSMISSION_MODE_2K         = 0x00,  /*2k 模式*/
    ROC_TERRAINTNR_TRANSMISSION_MODE_8K         = 0x01,  /*8k 模式*/
    ROC_TERRAINTNR_TRANSMISSION_MODE_RESERVE    = 0x11   /*预留*/
}Roc_TerrainTnr_Transmission_mode_e;

/*有线高频头输入参数*/
typedef struct Roc_CableTnr_Param
{
    UINT32_T                            frequency;    /*频率(单位 KHz)*/
    UINT32_T                            symbol_rate;  /*符号率(单位 Ksymbol/s)*/
    Roc_CableTnr_Modulation_e           modulation;   /*有线信号调制方式*/   
    Roc_Signal_FEC_Outer_e              FEC_outer;    /*向前纠错外码，暂不使用*/
    Roc_Signal_FEC_Inner_e              FEC_inner;    /*向前纠错内码，暂不使用*/
    INT32_T                             reserved;     /*预留*/
}Roc_CableTnr_Param_t;

/*卫星高频头输入参数*/
typedef struct Roc_SateliteTnr_Param
{
    UINT32_T                            frequency;         /*频率(单位 KHz)*/
    UINT32_T                            symbol_rate;       /*符号率(单位 Ksymbol/s)*/
    Roc_SateliteTnr_Modulation_e        modulation;        /*卫星信号调制方式*/
    UINT16_T                            orbital_position;  /*轨道位置*/
    ROC_BOOL                            west_east_flag;    /*东西标志*/
    Roc_SateliteTnr_Polarization_e      polarization;      /*极化方式*/
    Roc_Signal_FEC_Inner_e              FEC_inner;         /*向前纠错内码*/
    INT32_T                             reserved;          /*预留*/
}Roc_SateliteTnr_Param_t;

/*地面波高频头输入参数*/
typedef struct Roc_TerrainTnr_Param
{
    UINT32_T                            centre_frequency;       /*中心频率(单位 KHz)*/
    Roc_TerrainTnr_Bandwidth_e          bandwidth;              /*带宽*/
    Roc_TerrainTnr_Constellation_e      constellation;          /*星座模式*/
    Roc_TerrainTnr_Hierarchy_info_e     hierarchy_information;  /*分层信息*/
    Roc_Signal_FEC_Inner_e              code_rate;              /*向前纠错内码*/
    Roc_TerrainTnr_Guard_Interval_e     guard_interval;         /*间隔保护*/
    Roc_TerrainTnr_Transmission_mode_e  transmission_mode;      /*载波模式*/
    ROC_BOOL                            other_frequency_flag;   /*标明是否使用了其它频率.ROC_TRUE：使用一个或多个其它频率;ROC_FALSE：未使用其它频率*/
    INT32_T                             reserved;               /*预留*/
}Roc_TerrainTnr_Param_t;

/*高频头参数*/
typedef struct Roc_Tuner_Param
{
    Roc_Tuner_Type_e            type;       /*高频头类型*/      
    union{
        Roc_CableTnr_Param_t    cab_param;  /*有线高频头参数*/
        Roc_SateliteTnr_Param_t sat_param;  /*卫星高频头参数*/
        Roc_TerrainTnr_Param_t  ter_param;  /*地面高频头参数*/
    }param;                                 /*高频头参数*/
}Roc_Tuner_Param_t;

/*信号误码率结构定义*/
typedef struct Roc_Siganl_ber
{
    UINT32_T    total_counter;  /*单位时间内元码计数总数*/
    UINT32_T    error_counter;  /*单位时间内出现的误码数*/
}Roc_Siganl_ber_t;

/*信号信息结构定义*/
typedef struct Roc_Signal_Info
{
    UINT32_T            signal_strength;  /*信号强度*/
    UINT32_T            signal_snr;       /*信号信噪比/信号质量*/
    Roc_Siganl_ber_t    signal_ber;       /*信号误码率*/
    UINT32_T						signal_RFLevle;   /*信号电平值*/
}Roc_Signal_Info_t;

/*高频头工作状态定义*/
typedef enum Roc_Tuner_State
{
    ROC_TUNER_STATE_UNKNOWN     = 0x00,  /*未知状态      */
    ROC_TUNER_STATE_IDLE        = 0x01,  /*空闲状态      */
    ROC_TUNER_STATE_STANDBY     = 0x02,  /*休眠状态      */
    ROC_TUNER_STATE_UNLOCK      = 0x03,  /*信号未锁定状态*/
    ROC_TUNER_STATE_LOST        = 0x04,  /*信号丢失状态  */
    ROC_TUNER_STATE_SCANNING    = 0x05,  /*信号搜索中状态*/
    ROC_TUNER_STATE_LOCKED      = 0x06,  /*信号锁定状态  */
    ROC_TUNER_STATE_RESERVE     = 0xFF   /*预留*/
}Roc_Tuner_State_e;


/**************************************************************************
函数名称: 
            rocme_porting_tuner_init
功能说明: 
            高频头设备初始化，中间件会在启动时调用此函数，若在启动中间件之前
        机顶盒已经做好了高频头的初始化，此函数可以实现为空，直接返回0。
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
INT32_T rocme_porting_tuner_init( void );

/**************************************************************************
函数名称: 
            rocme_porting_tuner_scanning
功能说明: 
            高频头参数设置函数，根据指定的参数，设置指定的数据通道上的高频头工作
        在指定的频点，不要求同步锁频，要求正确设置参数后，函数立即返回。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的高频头ID)
            [ tnr_param     ] : 高频头参数,具体如下:
                                type  -  高频头类型
                                cab_param  -  type为有线高频头时，此参数有效
                                sat_param  -  type为卫星高频头时，此参数有效
                                ter_param  -  type为地面高频头时，此参数有效
    输出参数：
            [ tnr_state     ] : 锁频操作后的高频头的工作状态 
返    回： 
    成功 : 0            ( 锁频设置操作成功 )
    失败 : -1 或 错误码 ( 锁频设置操作失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_tuner_scanning( const INT32_T channel_index,const Roc_Tuner_Param_t tnr_param );

/**************************************************************************
函数名称: 
            rocme_porting_tuner_get_state
功能说明: 
           查询指定数据通道上的高频头的当前状态。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的高频头ID)
    输出参数：
            [ tnr_state     ] : 高频头的当前工作状态 
返    回： 
    成功 : 0            ( 查询高频头状态成功 )
    失败 : -1 或 错误码 ( 查询高频头状态失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_tuner_get_state( const INT32_T channel_index,Roc_Tuner_State_e *tnr_state );

/**************************************************************************
函数名称: 
            rocme_porting_tuner_get_signal_info
功能说明: 
           获取指定数据通道上的高频头的当前信号信息，包括信号强度、信噪比和
       误码率。
参数说明：
    输入参数：
            [ channel_index ] : 数据通道索引值(非具体的高频头ID)
    输出参数：
            [ signal_info   ] : 高频头的当前信号信息，包括:
                                signal_strength  -  信号强度
                                signal_snr       -  信号信噪比/信号质量
                                signal_ber       -  信号误码率
返    回： 
    成功 : 0            ( 查询高频头信息成功 )
    失败 : -1 或 错误码 ( 查询高频头信息失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_tuner_get_signal_info( const INT32_T channel_index,Roc_Signal_Info_t *signal_info );


#ifdef __cplusplus
}
#endif

#endif
