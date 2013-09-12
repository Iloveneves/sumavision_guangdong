/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_common.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/15
  Description   : Common apis for hisilicon system.
  History       :
  1.Date        : 2010/01/25
    Author      : jianglei
    Modification: Created file

*******************************************************************************/

#ifndef __HI_COMMON_H__
#define __HI_COMMON_H__

#include <hi_type.h>
#include <hi_debug.h>
#include <hi_struct.h>
#include <hi_reg.h>

/******************************* API declaration *****************************/
/** \addtogroup      H_1_1_1 */
/** @{ */  /** <!-- 【通用API函数】 */

/**定义FastPlay 退出模式枚举 */
typedef enum
{
    HI_UNF_PREAV_NULL = 0x000, /**< 默认方式,直接关闭 */
    HI_UNF_PREAV_STEP1= 0X038, /**< 逐步关闭模式，Step1 */
    HI_UNF_PREAV_STEP2,        /**< 逐步关闭模式，Step2 */
    HI_UNF_PREAV_STEP3,        /**< 逐步关闭模式，Step3 */
    HI_UNF_PREAV_STEP4,        /**< 逐步关闭模式，Step4 */
    HI_UNF_PREAV_BUTT
}HI_UNF_PREAV_E;

typedef struct
{
    HI_UNF_PREAV_E enOption;   /**< FastPlay退出模式枚举 */
    unsigned int StepParam1;   /**< 逐步关闭模式的参数1 */
    unsigned int StepParam2;   /**< 逐步关闭模式的参数2 */
}HI_SYS_PREAV_PARAM_S;


#ifndef __KERNEL__
#include <time.h>

/**
\brief 系统初始化
\attention \n
在使用所有模块的接口之前都需要先调用此接口对系统进行初始化\n
在调用这个接口之前调用其他接口，不会返回失败，但是不保证执行的正确性
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_Init(HI_VOID);

/**
\brief 系统去初始化
\attention \n
所有模块都不再使用后调用此接口去初始化
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_DeInit(HI_VOID);

/**
\brief 系统音视频图形操作前准备工作
\attention \n
如果存在开机画面或开机节目的情况下，由用户根据实际情况在具体时机调用，释放相关资源，以达到无缝切换的效果
例如：正常情况下，应用程序打开图层后会默认完成开机画面所使用资源的释放;但是如果用户不进行图层打开操作而直接进行视频播放接口的调用，建议使用该接口；
建议 HI_SYS_Init 后立即调用，支持多次调用
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_PreAV(HI_SYS_PREAV_PARAM_S *pstPreParm);

/**
\brief 获取版本的编译时间
\attention \n
时间为进行common模块重新make的时间
\param[out] pstAttr   指针类型，输出版本编译的时间。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_GetBuildTime(struct tm * ptm);

/**
\brief 获取当前使用播放时间 
\attention \n
时间单位:秒
\param[out] pstVersion   指针类型，输出当前消费时间。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_GetPlayTime(HI_U32 *pu32Playtime);
/**
\brief 获取版本号
\attention \n
无
\param[out] pstVersion   指针类型，输出版本号。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/

HI_S32 HI_SYS_GetVersion(HI_SYS_VERSION_S *pstVersion);

/**
\brief 设置系统的全局配置
\attention \n
无
\param[in] pstSysConf   指针类型，系统配置指针地址。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_SetConf(const HI_SYS_CONF_S *pstSysConf);

/**
\brief 获取系统的全局配置
\attention \n
无
\param[out] pstSysConf   指针类型，输出系统配置。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_GetConf(HI_SYS_CONF_S *pstSysConf);

/**
\brief 设置模块的调试信息级别
\attention \n
无
\param[in] enModId   模块的调试ID。
\param[in] enLogLevel  模块的调试信息级别。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_SetLogLevel(HI_DEBUG_MOD_ID_E enModId,  HI_LOG_LEVEL_E enLogLevel);


/**
\brief 写寄存器或内存
\attention \n
无
\param[in] u32RegAddr  寄存器或内存的物理地址。
\param[in] u32Value  寄存器的值。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_WriteRegister(HI_U32 u32RegAddr, HI_U32 u32Value);

/**
\brief 读寄存器或内存
\attention \n
无
\param[in] u32RegAddr  寄存器或内存的物理地址。
\param[out] pu32Value  指针类型，输出寄存器的值。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_SYS_ReadRegister(HI_U32 u32RegAddr, HI_U32 *pu32Value);


/**
\brief 申请mmz内存，并映射用户态地址
\attention \n
无
\param[in/out] pBuf  buffer信息结构，bufname和bufsize作为输入,物理地址和用户态虚拟地址作为输出
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_MMZ_Malloc(HI_MMZ_BUF_S *pBuf);

/**
\brief 解除用户态地址的映射，并释放mmz内存
\attention \n
保证传入的物理地址、用户态虚拟地址和长度正确
\param[in] pBuf  buffer信息结构
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_MMZ_Free(HI_MMZ_BUF_S *pBuf);

/**
\brief 指定mmz的名字申请mmz内存，返回物理地址
\attention \n
无
\param[in] size  buffer大小
\param[in] align  对齐方式
\param[in] mmz_name  buffer分区的名字，传入NULL匿名申请
\param[in] mmb_name  buffer块的名字
\retval ::NULL 申请失败
\retval 物理地址
\see \n
无
*/
HI_VOID *HI_MMZ_New(HI_U32 size , HI_U32 align, HI_CHAR *mmz_name, HI_CHAR *mmb_name);

/**
\brief 通过物理地址释放mmz内存
\attention \n
无
\param[in] phys_addr  buffer物理地址
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_MMZ_Delete(HI_U32 phys_addr);

/**
\brief 将mmz申请的物理地址映射成用户态虚拟地址，可以指定是否cached
\attention \n
无
\param[in] phys_addr  buffer物理地址
\param[in] cached  是否使用cache，0不使用，1使用
\retval ::NULL 申请失败
\retval 用户态虚地址
\see \n
无
*/
HI_VOID *HI_MMZ_Map(HI_U32 phys_addr, HI_U32 cached);

/**
\brief 解除mmz内存用户态地址的映射
\attention \n
无
\param[in] phys_addr  buffer物理地址
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_MMZ_Unmap(HI_U32 phys_addr);


/**
\brief 对于cached类型MMZ，刷Dcache到内存
\attention \n
如果传入0，则刷新所有的Dcache；否则只刷传入的那块内存
\param[in] phys_addr  buffer物理地址
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_MMZ_Flush(HI_U32 phys_addr);


/**
\brief 将物理地址映射成用户态虚拟地址
\attention \n
无
\param[in] phys_addr  buffer物理地址
\param[in] u32Size  buffer的大小
\retval ::NULL 申请失败
\retval 用户态虚地址
\see \n
无
*/
HI_VOID *HI_MEM_Map(HI_U32 u32PhyAddr, HI_U32 u32Size);


/**
\brief 解除用户态地址的映射
\attention \n
无
\param[in] pAddrMapped  buffer的用户态虚地址
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_MEM_Unmap(HI_VOID *pAddrMapped);

/**
\brief 根据虚拟地址获取物理地址，以及大小
\attention \n
无
\param[in] pVir  用户态虚地址
\param[out] pu32Phyaddr 物理地址
\param[out] pu32Size 大小
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_MMZ_GetPhyaddr(HI_VOID * pVir, HI_U32 *pu32Phyaddr, HI_U32 *pu32Size);


/** @} */  /** <!-- ==== Structure Definition end ==== */

#endif
#endif /* __HI_COMMON_H__ */
