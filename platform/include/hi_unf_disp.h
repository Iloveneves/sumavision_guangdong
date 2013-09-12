/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_disp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/15
  Description   :
  History       :
  1.Date        : 2009/12/15
    Author      : w58735
    Modification: Created file

*******************************************************************************/
/** 
 * \file
 * \brief 提供DISPLAY的相关信息
 */
 
#ifndef  __HI_UNF_DISP_H__
#define  __HI_UNF_DISP_H__

#include "hi_unf_common.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_8 */
/** @{ */  /** <!-- 【DISPLAY】 */

/**最大的DAC数目*/
#define MAX_DAC_NUM (6)


/**定义DISPLAY通道枚举*/
typedef enum hiUNF_DISP_E
{
    HI_UNF_DISP_SD0 = 0x0,   /**< 标清DISPLAY0 */
    HI_UNF_DISP_HD0,         /**< 高清DISPLAY0 */
    HI_UNF_DISP_BUTT
}HI_UNF_DISP_E;

/**定义支持的DAC信号格式*/
typedef enum hiUNF_DISP_DAC_MODE_E
{
    HI_UNF_DISP_DAC_MODE_SILENCE = 0,    /**<无输出*/
    HI_UNF_DISP_DAC_MODE_CVBS,           /**<CVBS输出*/
    HI_UNF_DISP_DAC_MODE_Y,              /**<Y亮度分量输出*/
    HI_UNF_DISP_DAC_MODE_PB,             /**<蓝色色差分量输出*/
    HI_UNF_DISP_DAC_MODE_PR,             /**<红色色差分量输出*/
    HI_UNF_DISP_DAC_MODE_R,              /**<红色分量输出*/
    HI_UNF_DISP_DAC_MODE_G,              /**<绿色分量输出*/
    HI_UNF_DISP_DAC_MODE_B,              /**<蓝色分量输出*/
    HI_UNF_DISP_DAC_MODE_SVIDEO_Y,       /**<SVIDEO_Y分量输出*/
    HI_UNF_DISP_DAC_MODE_SVIDEO_C,       /**<SVIDEO_C分量输出*/
    HI_UNF_DISP_DAC_MODE_HD_Y,           /**<高清Y亮度分量输出*/
    HI_UNF_DISP_DAC_MODE_HD_PB,          /**<高清蓝色色差分量输出*/
    HI_UNF_DISP_DAC_MODE_HD_PR,          /**<高清红色色差分量输出*/
    HI_UNF_DISP_DAC_MODE_HD_R,           /**<高清红色分量输出*/
    HI_UNF_DISP_DAC_MODE_HD_G,           /**<高清绿色分量输出*/
    HI_UNF_DISP_DAC_MODE_HD_B,           /**<高清蓝色分量输出*/
    HI_UNF_DISP_DAC_MODE_BUTT
}HI_UNF_DISP_DAC_MODE_E;


/**定义支持的显示输出接口 */
typedef struct  hiUNF_DISP_INTERFACE_S
{
    HI_BOOL                      bScartEnable;                /**<是否输出Scart信号*/
    HI_BOOL                      bBt1120Enable;               /**<是否输出Bt1120数字信号*/
    HI_BOOL                      bBt656Enable;                /**<是否输出Bt656数字信号*/
    HI_UNF_DISP_DAC_MODE_E       enDacMode[MAX_DAC_NUM];      /**<各个DAC的输出信号*/
}HI_UNF_DISP_INTERFACE_S ;


/**定义LCD输出的数据位宽*/
typedef enum hiUNF_DISP_LCD_DATA_WIDTH_E
{
    HI_UNF_DISP_LCD_DATA_WIDTH8 = 0,       /**<8位*/
    HI_UNF_DISP_LCD_DATA_WIDTH16,          /**<16位*/
    HI_UNF_DISP_LCD_DATA_WIDTH24,          /**<24位*/
    HI_UNF_DISP_LCD_DATA_WIDTH_BUTT
}HI_UNF_DISP_LCD_DATA_WIDTH_E;


/**定义LCD的数据格式*/
typedef enum hiHI_UNF_DISP_LCD_DATA_FMT
{
    HI_UNF_DISP_LCD_DATA_FMT_YUV422 = 0,         /**<YUV422，位宽为16*/
    HI_UNF_DISP_LCD_DATA_FMT_RGB565 = 0x8,       /**<RGB565，位宽为16*/
    HI_UNF_DISP_LCD_DATA_FMT_RGB444 = 0xa,       /**<RGB444，位宽为16*/
    HI_UNF_DISP_LCD_DATA_FMT_RGB666 = 0xb,       /**<RGB666，位宽为24*/
    HI_UNF_DISP_LCD_DATA_FMT_RGB888 = 0xc,       /**<RGB888，位宽为24*/
    HI_UNF_DISP_LCD_DATA_FMT_BUTT
}HI_UNF_DISP_LCD_DATA_FMT_E;

/**定义LCD的时序参数*/
typedef struct hiUNF_DISP_LCD_PARA_S
{
    HI_U32                    VFB;                 /**<垂直前消隐*/
    HI_U32                    VBB;                 /**<垂直后消隐*/
    HI_U32                    VACT;                /**<垂直有效区*/
    HI_U32                    HFB;                 /**<水平前消隐*/
    HI_U32                    HBB;                 /**<水平后消隐*/
    HI_U32                    HACT;                /**<水平有效区*/
    HI_U32                    VPW;                 /**<垂直脉冲宽度*/
    HI_U32                    HPW;                 /**<水平脉冲宽度*/
    HI_BOOL                   IDV;                 /**<有效数据信号是否翻转*/
    HI_BOOL                   IHS;                 /**<水平同步脉冲信号是否翻转*/
    HI_BOOL                   IVS;                 /**<垂直同步脉冲信号是否翻转*/
    HI_BOOL                   ClockReversal;       /**<时钟是否翻转*/
    HI_UNF_DISP_LCD_DATA_WIDTH_E   DataWidth;      /**<数据位宽*/
    HI_UNF_DISP_LCD_DATA_FMT_E       ItfFormat;      /**<数据格式.*/
    HI_BOOL                   DitherEnable;        /**<是否使能Dither*/
} HI_UNF_DISP_LCD_PARA_S;


/**定义可自由绑定的叠加层*/
typedef enum hiUNF_DISP_FREE_LAYER_E
{
    HI_UNF_DISP_FREE_LAYER_OSD_0,         /**<可自由绑定图形层0*/

    HI_UNF_DISP_FREE_LAYER_BUTT
}HI_UNF_DISP_FREE_LAYER_E;

/**定义DISPLAY通道上的叠加层*/
typedef enum hiUNF_DISP_LAYER_E
{
    HI_UNF_DISP_LAYER_VIDEO_0 = 0,   /**<视频层0*/
    HI_UNF_DISP_LAYER_OSD_0,         /**<图形层0*/
    HI_UNF_DISP_LAYER_ATTACH_OSD_0,  /**<绑定图形层0*/

    HI_UNF_DISP_LAYER_BUTT
}HI_UNF_DISP_LAYER_E;

/**定义显示颜色的结构体 */
typedef struct  hiUNF_DISP_BG_COLOR_S
{
    HI_U8 u8Red ;            /**<红色分量*/
    HI_U8 u8Green ;          /**<绿色分量*/
    HI_U8 u8Blue ;           /**<蓝色分量*/
} HI_UNF_DISP_BG_COLOR_S;

/********************************ENCODER STRUCT********************************/
/** 显示输出Macrovision模式枚举定义*/
typedef enum hiUNF_DISP_MACROVISION_MODE_E
{
    HI_UNF_DISP_MACROVISION_MODE_TYPE0,  /**<典型配置0 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE1,  /**<典型配置1 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE2,  /**<典型配置2 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE3,  /**<典型配置3 */
    HI_UNF_DISP_MACROVISION_MODE_CUSTOM, /**<用户自定义配置 */
    HI_UNF_DISP_MACROVISION_MODE_BUTT
} HI_UNF_DISP_MACROVISION_MODE_E;

/** 定义图文信息数据结构*/
typedef struct hiUNF_DISP_TTX_DATA_S
{
    HI_U8   *pu8DataAddr;               /**<Ttx数据用户虚拟地址*/
    HI_U32   u32DataLen;                /**<Ttx数据长度*/
} HI_UNF_DISP_TTX_DATA_S;


/** 定义VBI信息数据结构*/
typedef struct hiUNF_DISP_VBI_DATA_S
{
    HI_U8  *pu8DataAddr;                 /**<Vbi数据用户虚拟地址*/
    HI_U32  u32DataLen;                  /**<Vbi数据长度*/
} HI_UNF_DISP_VBI_DATA_S;


/**定义图文信息数据结构 */
typedef struct hiUNF_DISP_WSS_DATA_S
{
    HI_BOOL bEnable;                /**<WSS配置使能。HI_TRUE：使能；HI_FALSE：禁止*/
    HI_U16  u16Data;                /**<Wss数据*/
} HI_UNF_DISP_WSS_DATA_S;

/**定义DISPLAY通道的接口类型*/
typedef enum hiUNF_DISP_INTF_TYPE_E
{
    HI_UNF_DISP_INTF_TYPE_TV = 0,    /**<输出接口为TV*/
    HI_UNF_DISP_INTF_TYPE_LCD,       /**<输出接口为LCD*/
    HI_UNF_DISP_INTF_TYPE_BUTT
}HI_UNF_DISP_INTF_TYPE_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_6 */
/** @{ */  /** <!-- 【DISPLAY】 */

/**
\brief 初始化DISP模块
\attention \n
调用DISP模块其它接口前要求首先调用本接口
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NOT_EXIST DISP设备不存在
\retval ::HI_ERR_DISP_NOT_DEV_FILE  DISP非设备
\retval ::HI_ERR_DISP_DEV_OPEN_ERR  DISP打开失败
\see \n
无
*/
HI_S32 HI_UNF_DISP_Init(HI_VOID);

/**
\brief 去初始化DISP模块
\attention \n
在调用::HI_UNF_DISP_Close接口关闭所有打开的DISP后调用本接口
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_CLOSE_ERR  DISP关闭失败
\see \n
无
*/
HI_S32 HI_UNF_DISP_DeInit(HI_VOID);

/**
\brief 将两个DISP通道绑定
\attention \n
目前支持将高清DISP绑定到标清DISP通道上，绑定在打开DISP通道前必须完成绑定操作。
\param[in] enDstDisp     目标DISP通道号
\param[in] enSrcDisp     源DISP通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_Attach(HI_UNF_DISP_E enDstDisp, HI_UNF_DISP_E enSrcDisp);

/**
\brief 将两个DISP通道解绑定
\attention \n
只有在关闭两个DISP通道后才能进行解绑定操作。
\param[in] enDstDisp     目标DISP通道号
\param[in] enSrcDisp     源DISP通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_Detach(HI_UNF_DISP_E enDstDisp, HI_UNF_DISP_E enSrcDisp);

/**
\brief 打开指定DISP通道
\attention \n
在打开DISP之前，先完成对其的参数设置，避免画面闪烁
\param[in] enDisp   DISP通道号，请参见::HI_UNF_DISP_E
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_CREATE_ERR    DISP创建失败
\see \n
无
*/
HI_S32 HI_UNF_DISP_Open(HI_UNF_DISP_E enDisp);

/**
\brief 关闭指定DISP
\attention \n
无
\param[in] enDisp  DISP通道号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_Close(HI_UNF_DISP_E enDisp);

/**
\brief 将OSD绑定到DISP上
\attention \n
必须在DISP打开之前完成绑定。
\param[in] enDisp      DISP通道号
\param[in] enLayer     可绑定的图形层
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_AttachOsd(HI_UNF_DISP_E enDisp, HI_UNF_DISP_FREE_LAYER_E enLayer);

/**
\brief 将OSD从DISP解绑定
\attention \n
无
\param[in] enDisp      DISP通道号
\param[in] enLayer     可绑定的图形层
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_DetachOsd(HI_UNF_DISP_E enDisp, HI_UNF_DISP_FREE_LAYER_E enLayer);

/**
\brief 设置DISP的接口类型
\attention \n
接口类型是DISP应该设置的第一个参数。
\param[in] enDisp      DISP通道号
\param[in] enIntfType  DISP的接口类型
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetIntfType(HI_UNF_DISP_E enDisp, HI_UNF_DISP_INTF_TYPE_E enIntfType);

/**
\brief 获取DISP的接口类型
\attention \n
无
\param[in] enDisp        DISP通道号
\param[in] penIntfType   DISP的接口类型指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetIntfType(HI_UNF_DISP_E enDisp, HI_UNF_DISP_INTF_TYPE_E *penIntfType);

/**
\brief 设置DISP的制式
\attention \n
只有当设置DISP为TV后，调用本接口才有意义。\n
对高清的DISP，只能设置高清的制式；对标清的DISP，只能设置标清的制式。\n
在同源显示场景下，暂不支持刷新率非50Hz/60Hz的制式，如：暂不支持1080P24/1080P25/1080P30
\param[in] enDisp              DISP通道号
\param[in] enEncodingFormat    DISP的制式
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetFormat(HI_UNF_DISP_E enDisp, HI_UNF_ENC_FMT_E enEncodingFormat);

/**
\brief 获取DISP的制式
\attention \n
无
\param[in] enDisp               DISP通道号
\param[in] penEncodingFormat    DISP的制式指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetFormat(HI_UNF_DISP_E enDisp, HI_UNF_ENC_FMT_E *penEncodingFormat);

/**
\brief 设置DAC模式
\attention \n
DAC属于所有DISP共有资源，在完成DISP的参数配置并打开后，再调用本接口完成DAC的配置。\n
共有6个DAC，推荐0，1，2用作高清输出，3，4，5用作标清输出。
\param[in] pstDacMode   指针类型，DAC模式，请参见::HI_UNF_OUTPUT_INTERFACE_S
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法

\see \n
无
*/
HI_S32 HI_UNF_DISP_SetDacMode(const HI_UNF_DISP_INTERFACE_S *pstDacMode);

/**
\brief 获取DAC模式
\attention \n
无
\param[out] pstDacMode    指针类型，DAC模式
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetDacMode(HI_UNF_DISP_INTERFACE_S *pstDacMode);

/**
\brief 设置DISP的LCD参数
\attention \n
只有当设置DISP为LCD后，调用本接口才有意义。
\param[in] enDisp         DISP通道号
\param[in] pstLcdPara     指针类型，LCD参数，请参见::HI_UNF_DISP_LCD_PARA_S
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetLcdPara(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_LCD_PARA_S *pstLcdPara);

/**
\brief 获取DISP的LCD参数
\attention \n
无
\param[in] enDisp          DISP通道号
\param[in] pstLcdPara      指针类型，LCD参数
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetLcdPara(HI_UNF_DISP_E enDisp, HI_UNF_DISP_LCD_PARA_S *pstLcdPara);

/**
\brief 设置DISP上叠加层的Z序
\attention \n
无
\param[in] enDisp          DISP通道号
\param[in] enLayer         DISP上的叠加层
\param[in] enZFlag         Z序调节方式
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetLayerZorder(HI_UNF_DISP_E enDisp, HI_UNF_DISP_LAYER_E enLayer, HI_LAYER_ZORDER_E enZFlag);

/**
\brief 获取DISP上叠加层的Z序
\attention \n
在高标清绑定情况下，高清DISP的设置会自动同步到标清DISP；标清DISP的设置会自动同步到高清DISP。
\param[in] enDisp            DISP通道号
\param[in] enLayer           DISP上的叠加层
\param[in] pu32Zorder        叠加层Z序数值，数值越大优先级越高
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetLayerZorder(HI_UNF_DISP_E enDisp, HI_UNF_DISP_LAYER_E enLayer, HI_U32 *pu32Zorder);

/**
\brief 设置DISP背景色
\attention \n
无
\param[in] enDisp       DISP通道号
\param[in] pstBgColor   指针类型，待配置的显示输出背景色。请参见::HI_UNF_BG_COLOR_S
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetBgColor(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_BG_COLOR_S *pstBgColor);

/**
\brief 获取DISP背景色
\attention \n
在高标清绑定情况下，高清DISP的设置会自动同步到标清DISP；标清DISP的设置会自动同步到高清DISP。
\param[in] enDisp         DISP通道号
\param[out] pstBgColor    指针类型，显示输出背景色
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetBgColor(HI_UNF_DISP_E enDisp, HI_UNF_DISP_BG_COLOR_S *pstBgColor);

/**
\brief 设置DISP亮度
\attention \n
大于100的值按100处理
\param[in] enDisp           DISP通道号
\param[in] u32Brightness    待设置的显示输出亮度值。取值范围为0～100。0：最小亮度；100：最大亮度
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetBrightness(HI_UNF_DISP_E enDisp, HI_U32 u32Brightness);

/**
\brief 获取DISP亮度
\attention \n
查询的默认亮度值为50。\n
在高标清绑定情况下，高清DISP的设置会自动同步到标清DISP；标清DISP的设置会自动同步到高清DISP。
\param[in] enDisp              DISP通道号
\param[out] pu32Brightness     指针类型，显示输出亮度值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetBrightness(HI_UNF_DISP_E enDisp, HI_U32 *pu32Brightness);

/**
\brief 设置DISP对比度
\attention \n
大于100的值按100处理
\param[in] enDisp          DISP通道号
\param[in] u32Contrast     待设置的显示输出对比度值。取值范围为0～100。0：最小对比度；100：最大对比度
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetContrast(HI_UNF_DISP_E enDisp, HI_U32 u32Contrast);

/**
\brief 获取DISP对比度
\attention \n
查询的默认对比度值为50。\n
在高标清绑定情况下，高清DISP的设置会自动同步到标清DISP；标清DISP的设置会自动同步到高清DISP。
\param[in] enDisp           DISP通道号
\param[out] pu32Contrast    指针类型，显示输出对比度值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetContrast(HI_UNF_DISP_E enDisp, HI_U32 *pu32Contrast);

/**
\brief 设置DISP饱和度
\attention \n
大于100的值按100处理
\param[in] enDisp             DISP通道号
\param[in] u32Saturation      待设置的显示输出饱和度值。取值范围为0～100。0：最小饱和度；100：最大饱和度
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetSaturation(HI_UNF_DISP_E enDisp, HI_U32 u32Saturation);

/**
\brief 获取DISP饱和度
\attention \n
查询的默认饱和度值为50。\n
在高标清绑定情况下，高清DISP的设置会自动同步到标清DISP；标清DISP的设置会自动同步到高清DISP。
\param[in] enDisp             DISP通道号
\param[out] pu32Saturation    指针类型，显示输出饱和度值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetSaturation(HI_UNF_DISP_E enDisp, HI_U32 *pu32Saturation);

/**
\brief 设置DISP色调
\attention \n
无
\param[in] enDisp           DISP通道号
\param[in] u32HuePlus       显示输出色调增益值。范围为0～100。0：表示最小色调增益；100：表示最大色调增益
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetHuePlus(HI_UNF_DISP_E enDisp, HI_U32 u32HuePlus);

/**
\brief 获取DISP色调
\attention \n
查询的默认色调值为50。\n
在高标清绑定情况下，高清DISP的设置会自动同步到标清DISP；标清DISP的设置会自动同步到高清DISP。
\param[in] enDisp           DISP通道号
\param[out] pu32HuePlus     指针类型，显示输出色调增益值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetHuePlus(HI_UNF_DISP_E enDisp, HI_U32 *pu32HuePlus);

/**
\brief 自适应对比度调节
\attention \n
无
\param[in] enDisp           DISP通道号
\param[out] bEnable         使能/禁止标志
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetAccEnable(HI_UNF_DISP_E enDisp, HI_BOOL bEnable);

/**
\brief 发送图文数据PES包
\attention \n
无
\param[in] enDisp            DISP通道号
\param[in] pstTtxData        指针类型，指向图文数据包的指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SendTtxData(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_TTX_DATA_S *pstTtxData);

/**
\brief 发送VBI（Vertical Blanking Interval）数据PES包
\attention \n
无
\param[in] enDisp            DISP通道号
\param[in] pstVbiData        指针类型，指向VBI数据包的指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SendVbiData(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_VBI_DATA_S *pstVbiData);

/**
\brief 直接设置WSS（Wide Screen Singnalling）数据
\attention \n
无
\param[in] enDisp           DISP通道号
\param[in] pstWssData       指针类型，指向WSS数据的指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetWss(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_WSS_DATA_S *pstWssData);

/**
\brief 设置Macrovision模式
\attention \n
无
\param[in] enDisp          DISP通道号
\param[in] enMode          Macrovision模式，请参见::HI_UNF_MACROVISION_MODE_E
\param[in] pData           指针类型，自定义的Macrovision控制数据
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_SetMacrovision(HI_UNF_DISP_E enDisp, HI_UNF_DISP_MACROVISION_MODE_E enMode, const HI_VOID *pData);

/**
\brief 获取Macrovision模式
\attention \n
无
\param[in] enDisp      DISP通道号
\param[out] penMode    指针类型，MACROVISION模式
\param[out] pData      指针类型，仅当penMode=HI_MACROVISION_MODE_CUSTOM时有效
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISP未初始化
\retval ::HI_ERR_DISP_NULL_PTR      输入指针为空
\retval ::HI_ERR_DISP_INVALID_PARA  输入参数非法
\retval ::HI_ERR_DISP_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_DISP_GetMacrovision(HI_UNF_DISP_E enDisp, HI_UNF_DISP_MACROVISION_MODE_E *penMode, const HI_VOID *pData);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif
