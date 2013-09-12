/******************************************************************************

Copyright (C), 2004-2008, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_demux.h
Version       : Initial
Author        : Hisilicon multimedia software group
Created       : 2008-06-10
Last Modified :
Description   : Hisilicon DEMUX API declaration
Function List :
History       :
* Version   Date         Author     DefectNum    Description
* main\1    2008-06-10   j40671     NULL         Create this file.
* main\2    2010-04-02   j40671     NULL         modify for HD series.
******************************************************************************/
/**
 * \file
 * \brief 提供DEMUX的相关信息
 */

#ifndef __HI_UNF_DEMUX_H__
#define __HI_UNF_DEMUX_H__

#include "hi_unf_common.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_2 */
/** @{ */  /** <!-- 【DEMUX】 */

/**DMX设备数目*/
#define DMX_CNT                         5

/**DVB端口数量,通过tuner送入数据*/
#define DMX_DVBPORT_CNT                 3

/**RAM端口数量,使用TS BUFFER送入数据*/
#define DMX_RAMPORT_CNT                 4

/**DMX模块端口数量*/
#define DMX_TOTALPORT_CNT               7

/**DMX模块音视频通道数量 */
#define DMX_AVCHAN_CNT                  32

/**DMX通道总数目*/
#define DMX_TOTALCHAN_CNT               96

/**DMX过滤器总数目*/
#define DMX_TOTALFILTER_CNT             96

 /**filter最大深度*/
#define DMX_FILTER_MAX_DEPTH            16

/** PCR通道数量*/
#define DMX_PCRCHAN_CNT                 16


/** 默认通用通道缓冲区大小 16K Byte*/
#define DMX_DEFAULT_CHANBUF_SIZE        (16*1024)


/** DEMUX ID定义*/
#define HI_UNF_DMX_ID_0_PLAY            0
#define HI_UNF_DMX_ID_1_REC             1
#define HI_UNF_DMX_ID_2_REC             2
#define HI_UNF_DMX_ID_3_REC             3
#define HI_UNF_DMX_ID_4_PLAY            4


/*************************** Structure Definition ****************************/

/**定义DEMUX模块业务功能结构体*/
typedef struct hiUNF_DMX_CAPABILITY_S
{
    HI_U32 u32PortNum;          /**< 端口数量     */
    HI_U32 u32DmxNum;           /**< 设备数量     *///AI7D04684
    HI_U32 u32CommonChannelNum; /**< 通用通道数量 */
    HI_U32 u32AudioChannelNum;  /**< 音频通道数量 */
    HI_U32 u32VideoChannelNum;  /**< 视频通道数量 */
    HI_U32 u32FilterNum;        /**< 过滤器数量   */
    HI_U32 u32KeyNum;           /**< 密钥区数量   */
}HI_UNF_DMX_CAPABILITY_S;

/**TS端口ID */
typedef enum hiUNF_DMX_PORT_E
{
    HI_UNF_DMX_PORT_0_TUNER,     /**< port0, Tuner模式 */
    HI_UNF_DMX_PORT_1_TUNER,     /**< port1, Tuner模式 */
    HI_UNF_DMX_PORT_2_TUNER,     /**< port2, Tuner模式 */
    HI_UNF_DMX_PORT_3_RAM,       /**< port3, RAM模式 */
    HI_UNF_DMX_PORT_4_RAM,       /**< port4, RAM模式 */
    HI_UNF_DMX_PORT_5_RAM,       /**< port5, RAM模式 */
    HI_UNF_DMX_PORT_6_RAM,       /**< port6, RAM模式 */

    HI_UNF_DMX_PORT_BUTT
}HI_UNF_DMX_PORT_E;

/**TS端口模式 */
typedef enum hiUNF_DMX_PORT_MODE_E
{
    HI_UNF_DMX_PORT_MODE_EXTERNAL,  /**<外部TS输入*/
    HI_UNF_DMX_PORT_MODE_INTERNAL,  /**<内部TS输入*/
    HI_UNF_DMX_PORT_MODE_RAM,       /**<从内存输入*/

    HI_UNF_DMX_PORT_MODE_BUTT
}HI_UNF_DMX_PORT_MODE_E;

/**TS端口类型 */
typedef enum hiUNF_DMX_PORT_TYPE_E
{
    HI_UNF_DMX_PORT_TYPE_PARALLEL_BURST,          /**< 并行BURST模式             */
    HI_UNF_DMX_PORT_TYPE_PARALLEL_VALID,          /**< 并行VALID模式             */
    HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_188,     /**< 自同步188模式             */
    HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_204,     /**< 自同步204模式             */
    HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_188_204, /**< 自同步188/204自动识别模式 */
    HI_UNF_DMX_PORT_TYPE_SERIAL,                  /**< 串行模式                  */

    HI_UNF_DMX_PORT_TYPE_BUTT
}HI_UNF_DMX_PORT_TYPE_E;

/**TS端口属性*/
typedef struct hiUNF_DMX_PORT_ATTR_S
{
    HI_UNF_DMX_PORT_MODE_E enPortMod;  /**< 端口模式 */
    HI_UNF_DMX_PORT_TYPE_E enPortType; /**< 端口类型 */
    HI_U32 u32SyncLostTh;              /**< 同步丢失门限，推荐使用默认值 */
    HI_U32 u32SyncLockTh;              /**< 同步锁定门限，推荐使用默认值 */
    HI_U32 u32TunerInClk;              /**<Tuner输入时钟是否反相.0: 同相(默认); 1: 反相*/
    HI_U32 u32SerialBitSelector;       /**<端口线序选择。并行时:0: 表示cdata[7]最高位(默认);1: 表示cdata[0]最高位。
                                           串行时:1: 表示cdata[0]为数据线(默认); 0: 表示cdata[7]为数据线*/

    HI_U32 u32TunerErrMod;             /**<tuner到DEMUX的cerr_n线电平模式:
                                           0: 表示cerr_n线为高时表示数据错误;
                                           1: 表示cerr_n线为低时表示数据错误 (默认) */

} HI_UNF_DMX_PORT_ATTR_S;

/**TS端口的状态*/
typedef struct hiUNF_DMX_PORT_PACKETNUM_S
{
	HI_U32 				   u32TsPackCnt;	/**<端口收到的TS包计数*/
	HI_U32  			   u32ErrTsPackCnt;	/**<端口上错误TS包的计数*/
}HI_UNF_DMX_PORT_PACKETNUM_S;

/**DEMUX的TS Buffer状态 */
typedef struct hiUNF_DMX_TSBUF_STATUS_S
{
    HI_U32 u32BufSize;    /**< 缓冲区大小       */
    HI_U32 u32UsedSize;   /**< 缓冲区已使用大小 */
} HI_UNF_DMX_TSBUF_STATUS_S;

/**通道类型 */
typedef enum hiUNF_DMX_CHAN_TYPE_E
{
    HI_UNF_DMX_CHAN_TYPE_SEC = 0, /**<用于接收 PSI/SI等secitons数据的通道*/
    HI_UNF_DMX_CHAN_TYPE_PES,     /**<用于接收PES包数据的通道*/
    HI_UNF_DMX_CHAN_TYPE_AUD,     /**<用于接收音频数据的通道*/
    HI_UNF_DMX_CHAN_TYPE_VID,     /**<用于接收视频数据的通道*/
    HI_UNF_DMX_CHAN_TYPE_POST,      /**<整包上送通道，用于接收某PID的完整TS包*/
    HI_UNF_DMX_CHAN_TYPE_ECM_EMM,   /**<用于接收ECM或EMM数据的通道*/

    HI_UNF_DMX_CHAN_TYPE_BUTT
}HI_UNF_DMX_CHAN_TYPE_E;

/**通道的CRC模式 */
typedef enum hiUNF_DMX_CHAN_CRC_MODE_E
{
    HI_UNF_DMX_CHAN_CRC_MODE_FORBID = 0,                /**< CRC校验禁止 */
    HI_UNF_DMX_CHAN_CRC_MODE_FORCE_AND_DISCARD = 1,     /**< CRC校验使能，并丢弃错误Section */
    HI_UNF_DMX_CHAN_CRC_MODE_FORCE_AND_SEND = 2,        /**< CRC校验使能，并上送错误Section */
    HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_DISCARD = 3, /**< 根据语法判断是否进行CRC校验，并丢弃错误Section */
    HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_SEND = 4,    /**< 根据语法判断是否进行CRC校验，并上送错误Section */

    HI_UNF_DMX_CHAN_CRC_MODE_BUTT
}HI_UNF_DMX_CHAN_CRC_MODE_E;

/**通道的输出模式 */
typedef enum hiUNF_DMX_CHAN_OUTPUT_MODE_E
{
    HI_UNF_DMX_CHAN_OUTPUT_MODE_PLAY = 0x1,     /**< 音视频播放或数据接收 */
    HI_UNF_DMX_CHAN_OUTPUT_MODE_REC  = 0x2,     /**< 录制 */
    HI_UNF_DMX_CHAN_OUTPUT_MODE_PLAY_REC = 0x3, /**< 同时录制和播放或数据接收 */
    HI_UNF_DMX_CHAN_OUTPUT_MODE_BUTT = -1
}HI_UNF_DMX_CHAN_OUTPUT_MODE_E;

/**通道属性*/
typedef struct hiUNF_DMX_CHAN_ATTR_S
{
    HI_U32 u32BufSize;                            /**< 通道硬件使用buffer大小*/
    HI_UNF_DMX_CHAN_TYPE_E enChannelType;       /**< 通道类型 */
    HI_UNF_DMX_CHAN_CRC_MODE_E enCRCMode;       /**< CRC模式，通道类型为DMX_CHAN_SEC 时有效 */
    HI_UNF_DMX_CHAN_OUTPUT_MODE_E enOutputMode;   /**< 通道数据输出模式 */
}HI_UNF_DMX_CHAN_ATTR_S;

/**通道数据的加扰标志 */
typedef enum hiUNF_DMX_SCRAMBLED_FLAG_E
{
    HI_UNF_DMX_SCRAMBLED_FLAG_TS,  /**<数据被TS级加扰*/
    HI_UNF_DMX_SCRAMBLED_FLAG_PES, /**<数据被PES级加扰*/
    HI_UNF_DMX_SCRAMBLED_FLAG_NO,  /**<数据未被加扰*/

    HI_UNF_DMX_SCRAMBLED_FLAG_BUTT
}HI_UNF_DMX_SCRAMBLED_FLAG_E;

/**通道状态 */
typedef enum hiUNF_DMX_CHAN_STATUS_E
{
    HI_UNF_DMX_CHAN_CLOSE = 0x0,        /**<通道处于关闭状态*/
    HI_UNF_DMX_CHAN_PLAY_EN = 0x1,      /**<通道处于音视频播放或数据接收状态*/
    HI_UNF_DMX_CHAN_REC_EN = 0X2,       /**<通道处于数据录制状态*/
    HI_UNF_DMX_CHAN_PLAY_REC_EN = 0X3,  /**<通道处于同时录制和数据接收状态*/
}HI_UNF_DMX_CHAN_STATUS_E;

/**定义通道状态结构体*/
typedef struct hiUNF_DMX_CHAN_STATUS_S
{
    HI_UNF_DMX_CHAN_STATUS_E enChanStatus;   /**<通道状态*/
}HI_UNF_DMX_CHAN_STATUS_S;

/******************  Filter Attr  ***********************/


/** 过滤器属性*/
typedef struct hiUNF_DMX_FILTER_ATTR_S
{
    HI_U32 u32FilterDepth;                    /**<过滤器深度*/
    HI_U8 au8Match[DMX_FILTER_MAX_DEPTH];     /**<过滤器匹配字节,按bit比较*/
    HI_U8 au8Mask[DMX_FILTER_MAX_DEPTH] ;     /**<过滤器屏蔽字节,按bit设置, 0:没有mask，要进行比较, 1:mask起作用，不进行比较*/
    HI_U8 au8Negate[DMX_FILTER_MAX_DEPTH] ;   /**<过滤器取反字节,按byte设置, 0:不取反,1:取反*/
}HI_UNF_DMX_FILTER_ATTR_S;

/** CA类型，是否使用高安全CA*/
typedef enum hiUNF_DMX_CA_TYPE_E
{
    HI_UNF_DMX_CA_NORMAL = 0,    /**<普通CA*/
    HI_UNF_DMX_CA_ADVANCE,       /**<高安全CA*/

    HI_UNF_DMX_CA_BUTT
}HI_UNF_DMX_CA_TYPE_E;

/** 熵减少模式*/
typedef enum hiUNF_DMX_CA_ENTROPY_REDUCTION_E
{
    HI_UNF_DMX_CA_ENTROPY_REDUCTION_OPEN = 0,    /**<48bit*/
    HI_UNF_DMX_CA_ENTROPY_REDUCTION_CLOSE,       /**<64bit*/

    HI_UNF_DMX_CA_ENTROPY_REDUCTION_BUTT
}HI_UNF_DMX_CA_ENTROPY_E;


/** 解扰器协议类型*/
typedef enum hiUNF_DMX_DESCRAMBLER_TYPE_E
{
    HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2 = 0,    /**<CSA2.0*/
    HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3,       /**<CSA3.0*/

    HI_UNF_DMX_DESCRAMBLER_TYPE_BUTT
}HI_UNF_DMX_DESCRAMBLER_TYPE_E;


/** 密钥区属性*/
typedef struct hiUNF_DMX_DESCRAMBLER_ATTR_S
{
    HI_UNF_DMX_CA_TYPE_E enCaType;                    /**<解扰器是否使用高安全CA*/
    HI_UNF_DMX_DESCRAMBLER_TYPE_E enDescramblerType;  /**<解扰器解扰协议类型*/
    HI_UNF_DMX_CA_ENTROPY_E enEntropyReduction;       /**<0:48bit模式，1:64 bit模式，cas2.0时有效*/
}HI_UNF_DMX_DESCRAMBLER_ATTR_S;


/** DEMUX数据包的类型*/
typedef enum hiUNF_DMX_DATA_TYPE_E
{
    HI_UNF_DMX_DATA_TYPE_WHOLE = 0,  /**< 此段数据包含完整的数据包, 对于SECTION每个包都是完整的*/
    HI_UNF_DMX_DATA_TYPE_HEAD,       /**< 此段数据包含数据包的起始，但是不一定是完整的包, 只用于PES数据*/
    HI_UNF_DMX_DATA_TYPE_BODY,       /**< 此段数据包含数据包的内容，不包含起始，可能有结尾, 只用于PES数据*/
    HI_UNF_DMX_DATA_TYPE_TAIL,       /**< 此段数据包含数据包的结尾，用于指示可识别的包结束, 只用于PES数据*/

    HI_UNF_DMX_DATA_TYPE_BUTT
}HI_UNF_DMX_DATA_TYPE_E;

/** DEMUX数据包结构*/
typedef struct hiUNF_DMX_DATA_S
{
    HI_U8   *pu8Data;                   /**< 数据指针 */
    HI_U32  u32Size;                    /**< 数据长度 */
    HI_UNF_DMX_DATA_TYPE_E enDataType;  /**< 数据包的类型 */
}HI_UNF_DMX_DATA_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_1 */
/** @{ */  /** <!-- 【DEMUX】 */

/**
\brief 初始化DEMUX模块
\attention \n
在进行DEMUX相关操作前应该首先调用本接口\n
在使用PVR和AVPLAY前请提前进行DEMUX模块的初始化\n
重复调用本接口，会返回成功
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_DMX_Init(HI_VOID);


/**
\brief 去初始化DEMUX模块
\attention \n
调用本接口停止使用DEMUX模块，并释放本进程所占用的DEMUX资源\n
本接口第一次调用起作用,重复调用返回成功
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_DMX_DeInit(HI_VOID);


/**
\brief 查询DEMUX模块业务能力。业务功能包括通用通道数目、过滤器数目、密钥数目、端口数目、DEMUX设备数目和音视频通道数目等
\attention \n
无
\param[out] pstCap  指针类型，输出DEMUX模块能力。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
::HI_UNF_DMX_CAPABILITY_S
*/
HI_S32 HI_UNF_DMX_GetCapability(HI_UNF_DMX_CAPABILITY_S *pstCap);


/**
\brief 获取DEMUX端口属性
\attention \n
无
\param[in] u32PortId  端口号
\param[out] pstAttr   指针类型，输出端口属性。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetTSPortAttr(HI_UNF_DMX_PORT_E enPortId, HI_UNF_DMX_PORT_ATTR_S *pstAttr);


/**
\brief 设置DEMUX端口属性
\attention \n
建议先通过HI_UNF_DMX_GetTSPortAttr获取默认属性，然后对要改变的属性进行设置\n
端口0~2为HI_UNF_DMX_PORT_MODE_EXTERNAL类型，端口3~6为HI_UNF_DMX_PORT_MODE_RAM类型端口\n
端口模式只支持查询，不支持修改，其他属性均支持随时动态修改\n
内存模式的端口仅支持设置为自同步并行模式，设置其他端口类型会失败\n
同步丢失和同步锁定门限，推荐使用默认值\n
tuner输入时钟反向、端口线序选择和tuner error线电平模式的设置请咨询硬件工程师\n
并参考tuner的用户手册，然后设置为合适的值
\param[in] u32PortId   端口号。
\param[in] pstAttr  指针类型，端口属性
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_SetTSPortAttr(HI_UNF_DMX_PORT_E enPortId, const HI_UNF_DMX_PORT_ATTR_S *pstAttr);


/**
\brief 绑定DEMUX到端口上
\attention \n
支持5路DEMUX，每路DEMUX只能绑定到一个PORT，但是一个PORT的数据可以分发到多个DEMUX\n
DEMUX绑定到端口上之后就开始接收这个端口上输入的数据\n
不再使用这路DEMUX接收数据后，使用HI_UNF_DMX_DetachTSPort接口解绑定DEMUX\n
可以动态的绑定到不同的端口上，不用先解绑定\n
重复调用此接口绑定到相同通道上返回成功
\param[in] u32DmxId  DEMUX ID。
\param[in] enPortId  端口号。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
::HI_UNF_DMX_DetachTSPort
*/
HI_S32 HI_UNF_DMX_AttachTSPort(HI_U32 u32DmxId, HI_UNF_DMX_PORT_E enPortId);


/**
\brief 从端口上解绑定DEMUX
\attention \n
不再使用DEMUX接收任何数据时使用此接口将DEMUX从端口上解绑定\n
可以动态使用解绑定接口，可以通过解绑定接口切断DEMUX的输入源\n
重复解绑定返回成功
\param[in] u32DmxId  DEMUX ID。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
::HI_UNF_DMX_AttachTSPort
*/
HI_S32 HI_UNF_DMX_DetachTSPort(HI_U32 u32DmxId);


/**
\brief 获取DEMUX所绑定的端口的端口号
\attention \n
如果DEMUX没有绑定到任何端口上会返回错误码
\param[in] u32DmxId  DEMUX ID。
\param[out] penPortId  指针类型，输出DEMUX绑定的端口号。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOATTACH_PORT  此路DEMUX没有绑定到任何端口上
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetTSPortId(HI_U32 u32DmxId, HI_UNF_DMX_PORT_E *penPortId);


/**
\brief 为RAM端口创建TS Buffer用于接收从网络或本地存储中输入的TS数据
\attention \n
只有RAM类型端口可以创建TS Buffer\n
buffer大小必须在4K和16M之间，单位为字节\n
buffer大小最好为4K的整数倍，如果不是整数倍，内部会进行向下对齐操作\n
同一个端口不能重复创建TS Buffer,否则返回错误码
\param[in] enPortId  端口号。
\param[in] u32TsBufSize TS Buffer大小
\param[out] phTsBuffer  指针类型，输出创建的TS Buffer 句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_RECREAT_TSBUFFER  重复创建TS Buffer
\see \n
无
*/
HI_S32 HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_E enPortId, HI_U32 u32TsBufSize, HI_HANDLE *phTsBuffer);


/**
\brief 销毁创建的TS Buffer
\attention \n
不能重复销毁一个TS Buffer,销毁之后handle就不存在了\n
销毁之后buffer中的数据就会被清空，不能再进行Get和Put操作\n
销毁TS buffer并不能清空通道中数据，要切换码流，要注意关闭通道，重新打开
\param[in] hTsBuffer TS Buffer句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_DestroyTSBuffer(HI_HANDLE hTsBuffer);


/**
\brief 获取TS Buffer空间，用于数据输入
\attention \n
重复get返回同一个buffer地址\n
输入数据时注意每次输入的数据长度，太长可能会导致输入数据不及时\n
太短可能会导致调度太频繁，性能下降\n
当剩余空间小于等于请求的长度时，返回错误码\n
每次申请的长度要小于剩余剩余长度，即buffer不可能被填满\n
请求长度不允许为0，否则返回参数非法错误码\n
u32TimeOutMs设置为0表示不等待，设置为0xffffffff表示一直等待，设置为其他值表示等待u32TimeOutMs毫秒。\n
若超过阻塞时间，还无法申请到Buffer，则返回HI_ERR_DMX_TIMEOUT错误码\n
u32TimeOutMs配置为0时，如果申请不到Buffer，说明此时内部TS Buffer空间已满，需要通过usleep(10000)释放cpu
以使其它线程能够得到调度。
\param[in] hTsBuffer TS Buffer句柄
\param[in] u32ReqLen 请求数据的长度
\param[out] pstData   数据buffer结构
\param[in] u32TimeOutMs      等待超时时间，单位ms
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_TIMEOUT  等待超时
\retval ::HI_ERR_DMX_NOAVAILABLE_BUF  剩余buffer空间小于请求长度
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetTSBuffer(HI_HANDLE hTsBuffer, HI_U32 u32ReqLen,
            HI_UNF_STREAM_BUF_S *pstData, HI_U32 u32TimeOutMs);


/**
\brief TS数据输入完毕，用于更新TS Buffer写指针
\attention \n
此接口必须和Get接口配对使用，如果没有Get则进行Put操作，则不会进行任何操作，但返回成功\n
Put的长度如果为0，也不会进行任何操作直接返回成功\n
不允许Put长度大于实际Get到的长度，否则返回参数非法错误码\n
允许Put长度小于Get长度，表明只输入了一部分数据
\param[in] hTsBuffer TS Buffer句柄
\param[in] u32ValidDataLen 有效数据的长度
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_PutTSBuffer(HI_HANDLE hTsBuffer, HI_U32 u32ValidDataLen);


/**
\brief 复位TS Buffer，清空TS Buffer中的数据
\attention \n
TS Buffer复位后需要重新get才能执行put操作
\param[in] hTsBuffer TS Buffer句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_ResetTSBuffer(HI_HANDLE hTsBuffer);


/**
\brief 获取TS Buffer状态
\attention \n
可以查询TS Buffer大小和已用的空间大小
\param[in] hTsBuffer TS Buffer句柄
\param[out] pStatus  TS Buffer状态结构
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetTSBufferStatus(HI_HANDLE hTsBuffer, HI_UNF_DMX_TSBUF_STATUS_S *pStatus);

/**
\brief 获取TS Buffer对应的Port ID
\attention \n
对于没有申请的TS buffer,查询会返回错误
\param[in] hTsBuffer TS Buffer句柄
\param[out] penPortId   TS Buffer对应的Port ID
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetTSBufferPortId(HI_HANDLE hTsBuffer, HI_UNF_DMX_PORT_E *penPortId);

/**
\brief 获取Port ID对应的TS Buffer handle
\attention \n
对于没有申请的TS buffer,查询会返回错误
\param[in] enPortId   Port ID
\param[out] phTsBuffer TS Buffer句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetTSBufferHandle(HI_UNF_DMX_PORT_E enPortId, HI_HANDLE *phTsBuffer);

/**
\brief 获取端口的TS包信息
\attention \n
对于没有绑定的端口,查询会返回错误
\param[in] u32PortId   Port ID
\param[out] sPortStat  TS包计数信息
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/

HI_S32 HI_UNF_DMX_GetTSPortPacketNum(HI_U32 u32PortId, HI_UNF_DMX_PORT_PACKETNUM_S *sPortStat);

/**
\brief 获取通道默认属性
\attention \n
最好在申请通道之前使用此接口获取默认属性，然后改变需要修改的属性即可\n
默认属性按一般的section通道返回的，如果要使用其他类型的通道注意修改属性值。
\param[out] pstChAttr 通道属性结构体指针
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetChannelDefaultAttr(HI_UNF_DMX_CHAN_ATTR_S *pstChAttr);


/**
\brief 根据通道属性创建一个PID通道
\attention \n
建议调用此接口之前，建议先调用HI_UNF_DMX_GetChannelDefaultAttr获取通道默认属性\n
只有section类型的通道和ecm emm类型的通道支持设置CRC模式，并且可以通过属性设置接口动态修改CRC模式\n
其他类型通道只支持设置为CRC禁止，如果选择了其他类型的CRC会被默认修改为CRC禁止\n
在申请通道时注意Buffer大小的配置，默认大小为16K，buffer大小的单位为字节\n
Section、ecm emm和POST通道建议使用16K以上的buffer大小，如果小于16K会被默认修改为16K\n
PES通道建议使用64K以上的buffer大小，如果小于64K会被默认修改为64K\n
DEMUX_1、DEMUX_2和DEMUX_3支持录制功能，允许分配录制类型的音视频通道（供PVR模块使用）\n
播放类型和同时播放与录制类型的音视频通道是不能申请的\n
音视频的播放通道由Player统一分配和管理
\param[in] u32DmxId  DEMUX ID。
\param[in] pstChAttr  指针类型，输入通道属性。请参见::HI_UNF_DMX_CHAN_ATTR_S
\param[out] phChannel  指针类型，输出分配的通道Handle。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOFREE_CHAN  没有空闲通道
\see \n
无
*/
HI_S32 HI_UNF_DMX_CreateChannel(HI_U32 u32DmxId, const HI_UNF_DMX_CHAN_ATTR_S *pstChAttr,
            HI_HANDLE *phChannel);


/**
\brief 销毁创建的PID通道
\attention \n
释放通道时如果通道处于打开状态会自动关闭通道，如果通道上绑定了过滤器或密钥区，会自动解绑定\n
但是并不会释放过滤器和密钥区
建议使用解绑定接口进行显式的解绑定操作，对资源的使用进行清晰的管理。
\param[in] hChannel  通道句柄。
\retval none
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
无
*/
HI_S32 HI_UNF_DMX_DestroyChannel(HI_HANDLE hChannel);


/**
\brief 获取通道属性
\attention \n
本接口必须在通道分配以后才可以调用
\param[in] hChannel   通道Handle。
\param[out] pstChAttr  指针类型，输出指定通道属性。请参见::HI_UNF_DMX_CHAN_ATTR_S
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetChannelAttr(HI_HANDLE hChannel, HI_UNF_DMX_CHAN_ATTR_S *pstChAttr);


/**
\brief 设置通道属性
\attention \n
本接口必须在通道分配以后才可以调用\n
除了CRC模式其他属性都不允许使用HI_UNF_DMX_SetChannelAttr接口进行动态修改\n
CRC模式可以在通道申请后的任意时刻修改，动态生效\n
要修改其他属性会返回参数非法错误码
\param[in] hChannel   通道句柄。
\param[in] pstChAttr   指针类型，输入通道属性。请参见 ::HI_UNF_DMX_CHAN_ATTR_S
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_SetChannelAttr(HI_HANDLE hChannel, const HI_UNF_DMX_CHAN_ATTR_S *pstChAttr);


/**
\brief 设置通道PID
\attention \n
同一路DEMUX的两个通道设置相同的PID。后设置的通道有效，先设置的通道的PID被修改为0x1fff\n
必须在通道关闭的状态下配置通道的PID\n
允许将通道的PID配置为0x1fff,配置为0x1fff后不接收任何数据，相当于关闭通道
\param[in] hChannel   通道句柄。
\param[in] u32Pid     通道PID
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_OPENING_CHAN  通道处于打开状态
\see \n
无
*/
HI_S32 HI_UNF_DMX_SetChannelPID(HI_HANDLE hChannel, HI_U32 u32Pid);


/**
\brief 获取通道配置的PID
\attention \n
没有配置PID前，获取到的PID为0x1fff\n
可以在通道申请后的任意时刻获取通道PID
\param[in] hChannel  通道句柄。
\param[out] pu32Pid   指针类型，输出通道的PID
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetChannelPID(HI_HANDLE hChannel, HI_U32 *pu32Pid);


/**
\brief 打开通道
\attention \n
在PID通道打开状态下，调用本接口打开通道不会发生错误\n
对于section通道，在通道没有绑定过滤器时调用本接口，通道不能接收数据\n
如果不想使用filter接收数据，可以申请一个filter将过滤深度配置为0，进行数据接收
\param[in] hChannel  通道句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_OpenChannel(HI_HANDLE hChannel);


/**
\brief 关闭通道
\attention \n
在PID通道关闭状态下，调用本接口关闭通道不会发生错误
\param[in] hChannel   通道句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_CloseChannel(HI_HANDLE hChannel);


/**
\brief 获取通道状态
\attention \n
可以在通道申请后的任意时刻调用
\param[in] hChannel   通道句柄。
\param[out] pstStatus  指针类型，输出通道状态。请参见::HI_UNF_DMX_CHAN_STATUS_S
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetChannelStatus(HI_HANDLE hChannel, HI_UNF_DMX_CHAN_STATUS_S *pstStatus);


/**
\brief 获取配置某PID的通道句柄
\attention \n
因不同DEMUX设备的通道允许设置相同的PID，调用本接口需要指定DEMUX ID\n
不允许查询0x1fff及以上的非法PID值，否则返回参数非法错误码\n
如果没有查询到任何通道设置了要查询的PID，将返回错误码
\param[in] u32DmxId    DEMUX ID。
\param[in] u32Pid      通道PID
\param[out] phChannel  指针类型，输出通道Handle。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_UNMATCH_CHAN  没有查询到匹配通道
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetChannelHandle(HI_U32 u32DmxId , HI_U32 u32Pid, HI_HANDLE *phChannel);


/**
\brief 获取DEMUX设备可用的空闲通道的数量
\attention \n
返回的数量为所有通道剩余的数量，包括已被使用的音视频通道\n
由于通道资源统一分配所以参数u32DmxId已经没有意义。
\param[in] u32DmxId         DEMUX ID。
\param[out] pu32FreeCount   指针类型，输出DEMUX空闲通道数目
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetFreeChannelCount (HI_U32 u32DmxId, HI_U32 *pu32FreeCount);


/**
\brief 获取通道数据加扰标志
\attention \n
支持PES级加扰和TS级加扰的查询
\param[in] hChannel   通道句柄。
\param[out] penScrambleFlag   指针类型，输出通道数据加扰标志。请参见::HI_UNF_DMX_SCRAMBLED_FLAG_E
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetScrambledFlag(HI_HANDLE hChannel, HI_UNF_DMX_SCRAMBLED_FLAG_E *penScrambleFlag);


/**
\brief 创建一个数据过滤器
\attention \n
过滤器深度最大为16\n
过滤器属性配置请参考::HI_UNF_DMX_FILTER_ATTR_S\n
创建过滤器时，同时实现对过滤器的设置；若不需要数据过滤，设置过滤器深度为0即可\n
若需要修改过滤器属性，可调用HI_UNF_DMX_SetFilterAttr进行属性修改\n
支持属性的动态修改\n
过滤器用于过滤Section数据时，有效过滤字节为第1字节及第4字节～第18字节\n
过滤器用于过滤PES数据时，有效过滤字节为第4字节及第7字节～第21字节\n
过滤器只适用于通用通道的数据过滤，包括section通道、ECM/EMM通道和PES通道\n
若分配成功，phFilter返回获取的过滤器Handle
\param[in] u32DmxId    DEMUX ID。
\param[in] pstFilterAttr   指针类型，输入过滤器属性。
\param[out] phFilter   指针类型，输出申请的过滤器Handle。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOFREE_FILTER  没有空闲filter
\see \n
无
*/
HI_S32 HI_UNF_DMX_CreateFilter(HI_U32 u32DmxId, const HI_UNF_DMX_FILTER_ATTR_S  *pstFilterAttr,
            HI_HANDLE *phFilter);


/**
\brief 销毁创建的数据过滤器
\attention \n
若过滤器和通用通道绑定，允许在通道打开或者关闭状态下，调用本接口释放过滤器\n
对于section通道当通道上没有任何过滤器绑定时，则不再接收数据，其他通道没有此限制
\param[in] hFilter  过滤器句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_DestroyFilter(HI_HANDLE hFilter);


/**
\brief 释放绑定在某个通道上的所有过滤器
\attention \n
允许在通道打开或者关闭状态下，调用本接口释放通道上绑定的所有过滤器
\param[in] hChannel  通道句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_DeleteAllFilter(HI_HANDLE hChannel);


/**
\brief 设置过滤器的过滤条件
\attention \n
过滤器的深度属性u32FilterDepth最大为16\n
过滤器属性配置请参考::HI_UNF_DMX_FILTER_ATTR_S\n
过滤器用于过滤Section数据时，有效过滤字节为第1字节及第4字节～第18字节\n
过滤器用于过滤PES数据时，有效过滤字节为第4字节及第7字节～第21字节\n
支持属性的动态修改
\param[in] hFilter   过滤器句柄。
\param[in] pstFilterAttr   指针类型，输入过滤器属性。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_ATTACHED_FILTER  过滤器绑定在通道上，不能动态设置
\see \n
无
*/
HI_S32 HI_UNF_DMX_SetFilterAttr(HI_HANDLE hFilter, const HI_UNF_DMX_FILTER_ATTR_S *pstFilterAttr );


/**
\brief 获取过滤器的过滤条件
\attention \n
在过滤器未分配时调用该接口，返回错误
\param[in] hFilter   过滤器句柄。
\param[out] pstFilterAttr   指针类型，输出过滤器属性。请参见::HI_UNF_DMX_FILTER_ATTR_S
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetFilterAttr(HI_HANDLE hFilter, HI_UNF_DMX_FILTER_ATTR_S *pstFilterAttr );


/**
\brief 绑定过滤器到指定的通道。
\attention \n
一个通用通道可以绑定一个或者多个数据过滤器，所有过滤器之间的过滤关系是或。\n
即只要满足其中任何一个过滤器的过滤条件，当前过滤的数据都将通过过滤而被送入DMA缓冲区\n
不支持音视频通道和POST通道的过滤器绑定\n
不能将一个过滤器重复绑定到一个或多个通道上\n
过滤器与通道不属于同一路DEMUX时，不能进行绑定操作\n
支持通用通道打开或者关闭状态下的过滤器绑定
\param[in] hFilter  过滤器句柄。
\param[in] hChannel   通道句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_ATTACHED_FILTER  过滤器已经处于绑定状态
\retval ::HI_ERR_DMX_NOT_SUPPORT  此类型通道不支持绑定过滤器
\see \n
无
*/
HI_S32 HI_UNF_DMX_AttachFilter(HI_HANDLE hFilter, HI_HANDLE hChannel);



/**
\brief 将过滤器从指定通道上解绑定
\attention \n
通道上没有绑定过滤器进行解绑定返回失败\n
过滤器与通道不属于同一路DEMUX维护时，返回错误\n
支持通用通道打开或者关闭状态下的过滤器解绑定

\param[in] hFilter   过滤器句柄。
\param[in] hChannel  通道句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NOATTACH_FILTER  filter没有绑定在任何通道上
\retval ::HI_ERR_DMX_UNMATCH_FILTER  filter没有绑定在此通道上
\see \n
无
*/
HI_S32 HI_UNF_DMX_DetachFilter(HI_HANDLE hFilter, HI_HANDLE hChannel);


/**
\brief 获取过滤器所绑定的通道句柄
\attention \n
每个过滤器唯一对应一个通道。若过滤器没有绑定任何到通道上，则返回HI_ERR_DMX_NOATTACH_FILTER错误码
\param[in] hFilter    过滤器句柄。
\param[out] phChannel   指针类型，输出过滤器绑定的通道句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOATTACH_FILTER  filter没有绑定在任何通道上
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetFilterChannelHandle(HI_HANDLE hFilter, HI_HANDLE *phChannel);


/**
\brief 获取DEMUX设备可用的空闲过滤器数量
\attention \n
返回当前未分配的过滤器数目，已分配但未绑定到通道上的过滤器不统计
\param[in] u32DmxId   DEMUX ID。
\param[out]  pu32FreeCount  指针类型，输出当前未分配的过滤器数目
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetFreeFilterCount(HI_U32 u32DmxId ,  HI_U32 * pu32FreeCount);


/**
\brief 创建一个密钥区
\attention \n
申请密钥区，不用关心属于哪路DEMUX，所有DEMUX共用所有密钥区
\param[in] u32DmxId   DEMUX ID。
\param[out] phKey      指针类型，输出申请到的密钥区Handle。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOFREE_KEY  没有空闲的密钥区
\see \n
无
*/
HI_S32 HI_UNF_DMX_CreateDescrambler(HI_U32 u32DmxId, HI_HANDLE *phKey);


/**
\brief 创建一个密钥区,支持选择高安全CA和解扰协议类型
\attention \n
如果是高安全CA，解扰协议已经由硬件决定，接口的设置被忽略\n
高安全CA的个数也是由硬件决定的，使用前最好使用HI_UNF_DMX_GetFreeDescramblerCountExt查一下剩余的个数
\param[in] u32DmxId   DEMUX ID。
\param[in] pstDesramblerAttr  密钥区属性指针  
\param[out] phKey      指针类型，输出申请到的密钥区Handle。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOFREE_KEY  没有空闲的密钥区
\retval ::HI_ERR_DMX_NOT_SUPPORT  不支持的HI_UNF_DMX_DESCRAMBLER_ATTR_S类型
\see \n
无
*/
HI_S32 HI_UNF_DMX_CreateDescramblerExt(HI_U32 u32DmxId, const HI_UNF_DMX_DESCRAMBLER_ATTR_S *pstDesramblerAttr, HI_HANDLE *phKey);

/**
\brief 销毁创建的密钥区
\attention \n
如果密钥区绑定在通道上，会先从通道上解绑定密钥区，但是注意不会关闭通道\n
如果没有关闭通道则进行密钥区的解绑定或销毁操作，可能导致数据接收的错误
\param[in] hKey  待删除的密钥区Handle。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DMX_DestroyDescrambler(HI_HANDLE hKey);


/**
\brief 设置密钥区的偶密钥。CA系统得到控制字后，可调用本接口将偶密钥配置到DEMUX解扰模块
\attention \n
pEvenKey指向要设置的偶密钥数据。数据共16byte，byte依次是CW1、CW2、……、CW16\n
支持密钥区的动态设置，可以在密钥区申请后的任意时刻设置密钥值\n
当设置密钥之前，密钥的初时值都是0，表示不做解扰
\param[in] hKey  待设置的密钥区句柄。
\param[in] pu8EvenKey  指针类型，指向要设置的偶密钥数据，必须是16个字节的数组
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_SetDescramblerEvenKey(HI_HANDLE hKey, const HI_U8 *pu8EvenKey);


/**
\brief 设置密钥区的奇密钥。CA系统得到控制字后，可调用本接口将奇密钥配置到DEMUX解扰模块
\attention \n
pOddKey指向要设置的奇密钥数据。奇密钥数据共16byte，byte依次是CW1、CW2、……、CW16\n
支持密钥区的动态设置，可以在密钥区申请后的任意时刻设置密钥值\n
当设置密钥之前，密钥的初时值都是0，表示不做解扰
\param[in] hKey  待设置的密钥区句柄。
\param[in] pu8OddKey   指针类型，指向要设置的奇密钥数据，必须是16个字节的数组
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_SetDescramblerOddKey(HI_HANDLE hKey, const HI_U8 *pu8OddKey);


/**
\brief 绑定密钥区到指定通道
\attention \n
一个密钥区可以绑定到多个通道上，通道可以属于不路的DEMUX\n
可以对所有类型的通道绑定密钥区进行静荷数据的解扰\n
不允许重复绑定相同或不同的密钥区到同一个通道上
\param[in] hKey    待绑定的密钥区句柄。
\param[in] hChannel   通道句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_ATTACHED_KEY  通道上已经有一个密钥区绑定在上面
\see \n
无
*/
HI_S32 HI_UNF_DMX_AttachDescrambler(HI_HANDLE hKey, HI_HANDLE hChannel);


/**
\brief 将密钥区从通道上解绑定
\attention \n
可以动态的解绑定通道使用的密钥区，可以在绑定后的任意时刻使用此接口解绑定密钥区\n
但是解绑定后可能导致加扰数据没有被解扰，导致数据错误\n
解绑定密钥区并不能改变密钥区的值，如果重新绑定密钥区，密钥值仍然是上次设置的值\n
如果不想进行解扰，除了解绑定密钥区之外，也可以直接将密钥值全部设置为0来实现
\param[in] hKey   待解绑定的密钥区句柄。
\param[in] hChannel  通道句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NOATTACH_KEY  通道上没有绑定任何密钥区
\retval ::HI_ERR_DMX_UNMATCH_KEY  指定的密钥区没有绑定在指定的通道上
\see \n
无
*/
HI_S32 HI_UNF_DMX_DetachDescrambler(HI_HANDLE hKey, HI_HANDLE hChannel);


/**
\brief 获取通道绑定的密钥区句柄
\attention \n
当通道没有绑定密钥区时，调用本接口返回HI_ERR_DMX_NOATTACH_KEY错误码
\param[in] hChannel  要查询的通道句柄。
\param[out] phKey     指针类型，输出通道绑定的密钥区句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOATTACH_KEY  通道上没有绑定任何密钥区
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetDescramblerKeyHandle(HI_HANDLE hChannel, HI_HANDLE *phKey);


/**
\brief 获取空闲密钥区数量
\attention \n
密钥区在几路DEMUX之间共用，所以第一个参数没有意义，只要输入一个合法值就可以了。
\param[in] u32DmxId   DEMUX ID。
\param[out]  pu32FreeCount   指针类型，输出空闲密钥区数目
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetFreeDescramblerKeyCount(HI_U32 u32DmxId , HI_U32 * pu32FreeCount);

/**
\brief 获取空闲密钥区数量，包含高安全CA和普通CA
\attention \n
可以最为高安全CA和普通CA个数查询的接口使用。
\param[out]  pu32FreeNormal   指针类型，输出通用CA空闲密钥区数目
\param[out]  pu32FreeAdvance   指针类型，输出高安全CA空闲密钥区数目
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32 HI_UNF_DMX_GetFreeDescramblerCountExt(HI_U32 * pu32FreeNormal, HI_U32 * pu32FreeAdvance);



/**
\brief 获取有新数据到达的所有通道的句柄
\attention \n
调用该接口时，pu32ChNum作为输入参数，用于指定phChannel指向数组的长度，表示要查询的通道个数；\n
通道个数必须初始化，且初始值必须为非0值，\n
建议将通道个数设置为通道的总个数, 通道总个数参考宏定义 ::DMX_TOTALCHAN_CNT\n
当该接口调用成功时，pu32ChNum作为输出参数，指定phChannel指向数组的有效长度\n
阻塞时间可以设置，时间单位为毫秒，设置为0不等待，设置为0xffffffff一直等待。\n
若超过阻塞时间，所有通道都没有数据到达，则返回等待超时错误\n
如果等待时间为0，而且没有任何通道有数据则返回::HI_ERR_DMX_NOAVAILABLE_DATA

\param[out] phChannel      指针类型，指向通道句柄数组。数组长度有pu32ChNum决定
\param[in/out] pu32ChNum   指针类型。
                           输入：pChannelHandle指向数组的长度。
                           输出：底层有新数据通道的数目；最多不超过输入的数值
\param[in] u32TimeOutMs      等待超时时间，单位ms
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOAVAILABLE_DATA  没有任何通道有数据到达
\retval ::HI_ERR_DMX_TIMEOUT  等待超时
\see \n
无
*/
/*#define HI_UNF_DMX_GetDataHandle(phChannel, pu32ChNum, u32TimeOutMs) \
            HI_UNF_DMX_SelectDataHandle(NULL, *pu32ChNum, phChannel, pu32ChNum, u32TimeOutMs)*/
HI_S32  HI_UNF_DMX_GetDataHandle(HI_HANDLE *phChannel, HI_U32 *pu32ChNum,
            HI_U32 u32TimeOutMs);

/**
\brief 查询部分通道是否有数据到达
\attention \n
用来作为::HI_UNF_DMX_GetDataHandle的补充，当应用中只关注部分通道的数据到达情况时使用此接口\n
被监视通道的句柄由phWatchChannel指定，个数由u32WatchNum指定\n
phWatchChannel为NULL,查询所有通道的数据到达情况，u32WatchNum必须为非0值\n
阻塞时间可以设置，时间单位为毫秒，设置为0不等待，设置为0xffffffff一直等待。\n
若超过阻塞时间，所有通道都没有数据到达，则返回等待超时错误\n
如果等待时间为0，而且没有任何通道有数据则返回::HI_ERR_DMX_NOAVAILABLE_DATA

\param[in] phWatchChannel   指针类型，指向被监视通道的句柄数组。数组长度有u32WatchNum决定
\param[in] u32WatchNum      监视通道的个数
\param[in] phDataChannel    指针类型，指向存在数据的通道的句柄数组。数组长度有pu32ChNum决定
\param[out] pu32ChNum       指针类型。底层有新数据通道的数目；最多不超过被监视的通道的数值
\param[in] u32TimeOutMs     等待超时时间，单位ms
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOAVAILABLE_DATA  没有任何通道有数据到达
\retval ::HI_ERR_DMX_TIMEOUT  等待超时
\see \n
无
*/
HI_S32  HI_UNF_DMX_SelectDataHandle(HI_HANDLE *phWatchChannel, HI_U32 u32WatchNum,
            HI_HANDLE *phDataChannel, HI_U32 *pu32ChNum, HI_U32 u32TimeOutMs);


/**
\brief 从指定通道中获取输出的数据包
\attention \n
在调用本接口之前，给u32AcquireNum赋值，指定允许查询的缓冲区信息最大数目。消息缓冲区数组的长度由u32AcquireNum决定\n
实际获取的缓冲区信息数目pu32AcquiredNum数值不会超过u32AcquireNum\n
对于section通道和ECM/EMM通道，每个数据包包含一个完整的section\n
对于PES通道，每个数据包尽量包含完整的pes，但是如果pes太大，可能要分多个pes包输出，\n
输出的数据是否完整通过数据包结构的enDataType字段指定\n
对于POST类型的通道，每个数据包包含一个或多个完整的TS包，TS包长188字节\n
对于音视频通道是不能通过此接口获取数据的，音视频数据会通过内部接口直接送给解码器进行解码\n
不允许重复调用此接口，可以一次请求多次释放，但是释放必须按顺序，而且释放的地址和长度必须和请求的一致\n
并且只有释放完所有的数据包才能再次请求，否则返回重复请求错误码
\param[in] hChannel            通道句柄。
\param[in] u32AcquireNum       请求的数据包的最大个数
\param[out] pu32AcquiredNum    指针类型，输出实际请求到的数据包个数
\param[out] pstBuf             指针类型，指向数据包信息数组，数组个数由pu32AcquiredNum决定
\param[in] u32TimeOutMs        等待超时时间，单位为ms
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\retval ::HI_ERR_DMX_NOAVAILABLE_DATA  通道中没有有效数据
\retval ::HI_ERR_DMX_TIMEOUT  等待超时
\retval ::HI_ERR_DMX_REACQUIRE_BUF  重复请求数据包
\see \n
无
*/
HI_S32  HI_UNF_DMX_AcquireBuf(HI_HANDLE hChannel, HI_U32 u32AcquireNum,
            HI_U32 * pu32AcquiredNum, HI_UNF_DMX_DATA_S *pstBuf,
            HI_U32 u32TimeOutMs);


/**
\brief 处理完数据包的数据后，释放数据包占用的缓冲空间
\attention \n
本接口释放的缓冲区一定是通过::HI_UNF_DMX_AcquireBuf获取的缓冲区，缓冲区的地址和长度不能更改\n
释放的缓冲区个数可以小于获取的缓冲区个数
\param[in] hChannel        通道句柄。
\param[in] u32ReleaseNum   释放数据包个数
\param[in] pstBuf          指针类型，指向释放缓冲区信息数组，长度由u32ReleaseNum决定
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_DMX_NOT_INIT  模块没有初始化
\retval ::HI_ERR_DMX_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DMX_NULL_PTR  指针参数为空
\see \n
无
*/
HI_S32  HI_UNF_DMX_ReleaseBuf(HI_HANDLE hChannel, HI_U32 u32ReleaseNum,
            HI_UNF_DMX_DATA_S *pstBuf);

/** @} */  /** <!-- ==== API declaration end ==== */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_DEMUX_H__ */

