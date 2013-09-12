/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_vo.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/16
  Description   :
  History       :
  1.Date        : 2009/12/16
    Author      : w58735
    Modification: Created file

*******************************************************************************/
/** 
 * \file
 * \brief 提供VO的相关信息
 */
 
#ifndef  __HI_UNF_VO_H__
#define  __HI_UNF_VO_H__

#include "hi_unf_common.h"
#include "hi_unf_vi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_7 */
/** @{ */  /** <!-- 【VO】 */


/**定义VO枚举*/
typedef enum hiUNF_VO_E
{
    HI_UNF_VO_SD0   = 0x0,  /**< 标清视频层0 */
    HI_UNF_VO_HD0,          /**< 高清视频层0 */
    HI_UNF_VO_BUTT
}HI_UNF_VO_E;

/**定义WINDOW属性*/
typedef struct hiUNF_WINDOW_ATTR_S
{
    HI_UNF_VO_E               enVo;          /**< 窗口所在的视频层 */
    HI_BOOL                   bVirtual;      /**< 是否为虚拟窗口 */
    HI_UNF_VIDEO_FORMAT_E     enVideoFormat; /**< 虚拟窗口数据格式 */
    HI_UNF_ASPECT_RATIO_E     enAspectRatio; /**< 窗口的宽高转换比例 */
    HI_UNF_ASPECT_CVRS_E      enAspectCvrs;  /**< 窗口的宽高转换方式 */
    HI_RECT_S                 stInputRect;   /**< 窗口的裁减区域 */
    HI_RECT_S                 stOutputRect;  /**< 窗口在视频层上的显示区域 */
} HI_UNF_WINDOW_ATTR_S;

typedef struct hiUNF_BUFFER_ATTR_S
{
    HI_S32              s32Stride;
    HI_U32              u32PhyAddr[16];
    HI_U32              u32BuffIndex[16];
    HI_S32              s32BuffNum;
}HI_UNF_BUFFER_ATTR_S;

/**VO设备的运行模式 */
typedef enum hiUNF_VO_DEV_MODE_E
{
    HI_UNF_VO_DEV_MODE_NORMAL,  /**< 正常模式，只能创建2个WINDOW */
    HI_UNF_VO_DEV_MODE_MOSAIC,  /**< 马赛克模式，可以创建多个WINDOW */
    HI_UNF_VO_DEV_MODE_BUTT
} HI_UNF_VO_DEV_MODE_E;

/**定义Freeze模式枚举*/
typedef enum hiUNF_WINDOW_FREEZE_MODE_E
{
    HI_UNF_WINDOW_FREEZE_MODE_LAST = 0,   /**< freeze时显示最后一帧*/
    HI_UNF_WINDOW_FREEZE_MODE_BLACK = 1,  /**< freeze时显示后黑屏*/
    HI_UNF_WINDOW_FREEZE_MODE_BUTT
} HI_UNF_WINDOW_FREEZE_MODE_E;
/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_5 */
/** @{ */  /** <!-- 【VO】 */

/**
\brief 初始化VO模块
\attention \n
调用VO模块要求首先调用本接口
\param[in]   enDevMode  VO模块的运行模式
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_DEV_NOT_EXIST   VO设备不存在
\retval ::HI_ERR_VO_NOT_DEV_FILE    VO非设备
\retval ::HI_ERR_VO_DEV_OPEN_ERR    VO打开失败
\retval ::HI_ERR_VO_INVALID_PARA    输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_VO_Init(HI_UNF_VO_DEV_MODE_E enDevMode);

/**
\brief 去初始化VO模块
\attention \n
在调用::HI_UNF_VO_Close接口关闭所有打开的VO后调用本接口
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_DEV_CLOSE_ERR  VO关闭失败
\see \n
无
*/
HI_S32 HI_UNF_VO_DeInit(HI_VOID);

/**
\brief 打开指定VO
\attention \n
无
\param[in] enVo    VO层号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT   DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA  输入参数非法
\retval ::HI_ERR_VO_CREATE_ERR    创建失败
\see \n
无
*/
HI_S32 HI_UNF_VO_Open(HI_UNF_VO_E enVo);

/**
\brief 关闭指定VO
\attention \n
无
\param[in] enVo  VO层号
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT   DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_VO_Close(HI_UNF_VO_E enVo);




/**
\brief 设置指定VO的ALPHA
\attention \n
无
\param[in] enVo         VO层号
\param[in] u32Alpha     视频图像显示透明度值，取值范围为0～255。取值为0时：全透明；取值为255时：不透明
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT   DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_VO_SetAlpha(HI_UNF_VO_E enVo, HI_U32 u32Alpha);

/**
\brief 获取指定vo的ALPHA
\attention \n
无
\param[in]  enVo        VO层号
\param[out] pu32Alpha   指针类型，视频图像显示透明度值
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT   DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA  输入参数非法
\retval ::HI_ERR_VO_NULL_PTR      输入指针为空
\see \n
无
*/
HI_S32 HI_UNF_VO_GetAlpha(HI_UNF_VO_E enVo, HI_U32 *pu32Alpha);

/**
\brief 设置指定VO的rect
\attention \n
只有在VO工作在MOSAIC模式才能调用本接口
\param[in] enVo      VO层号
\param[in] pstRect   rect的结构指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT   DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA  输入参数非法
\retval ::HI_ERR_VO_NULL_PTR      输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_VO_SetRect(HI_UNF_VO_E enVo, const HI_RECT_S *pstRect);


/**
\brief 获取指定VO的rect
\attention \n
只有在VO工作在MOSAIC模式才能调用本接口
\param[in] enVo      VO层号
\param[in] pstRect   rect的结构指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT   DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA  输入参数非法
\retval ::HI_ERR_VO_NULL_PTR      输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT   操作非法
\see \n
无
*/
HI_S32 HI_UNF_VO_GetRect(HI_UNF_VO_E enVo, HI_RECT_S *pstRect);

/**
\brief 创建WINDOW
\attention \n
只有打开VO后，才能在其之上创建WINDOW
\param[in] pWinAttr   WINDO属性结构指针
\param[in] phWindow   创建的WINDOW句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_CREATE_ERR     创建失败
\see \n
无
*/
HI_S32 HI_UNF_VO_CreateWindow(const HI_UNF_WINDOW_ATTR_S *pWinAttr, HI_HANDLE *phWindow);

/**
\brief 销毁WINDOW
\attention \n
无
\param[in] hWindow     WINDOW句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_DestroyWindow(HI_HANDLE hWindow);


/**
\brief 使能/禁止WINDOW
\attention \n
只有先将AVPLAY的VID通道stop后，才能禁止window，否则将引起数据的溢出
\param[in] hWindow     WINDOW句柄
\param[in] bEnable     使能/禁止标志
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_SetWindowEnable(HI_HANDLE hWindow, HI_BOOL bEnable);

/**
\brief 获取WINDOW的使能状态
\attention \n
无
\param[in] hWindow     WINDOW句柄
\param[in] pbEnable    使能/禁止指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_GetWindowEnable(HI_HANDLE hWindow, HI_BOOL *pbEnable);

/**
\brief 设置WINDOW属性
\attention \n
enVo和bVirtual参数一旦创建后就不能再进行修改。
\param[in] hWindow    WINDOW句柄
\param[in] pWinAttr   WINDO属性结构指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_SetWindowAttr(HI_HANDLE hWindow, const HI_UNF_WINDOW_ATTR_S *pWinAttr);

/**
\brief 获取WINDOW属性
\attention \n
无
\param[in] hWindow     WINDOW句柄
\param[in] pWinAttr    WINDO属性结构指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_GetWindowAttr(HI_HANDLE hWindow, HI_UNF_WINDOW_ATTR_S *pWinAttr);

/**
\brief 获取WINDOW的Frame信息，专门用于3D图形测试
\attention \n
无
\param[in] hWindow     WINDOW句柄
\param[out] pstFrameinfo Frame信息
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_AcquireFrame(HI_HANDLE hWindow, HI_UNF_VO_FRAMEINFO_S *pstFrameinfo);

/**
\brief 释放用户获取WINDOW的Frame，专门用于3D图形测试
\attention \n
无
\param[in] hWindow     WINDOW句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_ReleaseFrame(HI_HANDLE hWindow);

/**
\brief 设置WINDOW的Z序
\attention \n
无
\param[in] hWindow    WINDOW句柄
\param[in] enZFlag    Z序调节方式
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_SetWindowZorder(HI_HANDLE hWindow, HI_LAYER_ZORDER_E enZFlag);

/**
\brief 获取WINDOW的Z序
\attention \n
无
\param[in] hWindow       WINDOW句柄
\param[in] pu32Zorder    Z序数值，数值越大优先级越高
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_GetWindowZorder(HI_HANDLE hWindow, HI_U32 *pu32Zorder);

/**
\brief 把WINDOW与指定的AVPLAY/VI绑定
\attention \n
可以将AVPLAY或VI的句柄绑定到WINDOW上。
\param[in] hWindow      WINDOW句柄
\param[in] hSrc         数据源句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_AttachWindow(HI_HANDLE hWindow, HI_HANDLE hSrc);


/**
\brief 把WINDOW与指定的AVPLAY/VI解绑定
\attention \n
无
\param[in] hWindow     WINDOW句柄
\param[in] hSrc        数据源句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_DetachWindow(HI_HANDLE hWindow, HI_HANDLE hSrc);

/**
\brief 设置Winsow的播放速率
\attention \n
此功能用于在播放过程中改变播放速率
\param[in] hWindow           WINDOW句柄
\param[in] u32WinRatio      取值范围为 [16, 4096]，256代表正常速度播放
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_SetWindowRatio(HI_HANDLE hWindow, HI_U32 u32WinRatio);


/**
\brief 冻结WINDOW的显示内容
\attention \n
此功能用于在播放过程中冻结屏幕显示内容，此时WINDOW中的数据流继续运行，\n
因此取消冻结后，会立刻显示最新的内容。
\param[in] hWindow           WINDOW句柄
\param[in] bEnable           使能/禁止标志
\param[in] enWinFreezeMode   冻结的方式
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_FreezeWindow(HI_HANDLE hWindow, HI_BOOL bEnable, HI_UNF_WINDOW_FREEZE_MODE_E enWinFreezeMode);


/**
\brief 捕获WINDOW的当前帧
\attention \n
只有在WINDOW显示内容不再变化后调用本接口才有意义。例如Freeze或是停止AV播放。
\param[in] hWindow           WINDOW句柄
\param[in] pstCapPicture
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_CapturePicture(HI_HANDLE hWindow, HI_UNF_CAPTURE_PICTURE_S *pstCapPicture);

/**
\brief 复位WINDOW
\attention \n
此功能清空window中的缓冲，根据参数显示黑帧或最后一帧。
\param[in] hWindow           WINDOW句柄
\param[in] enWinFreezeMode   复位的方式
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_ResetWindow(HI_HANDLE hWindow, HI_UNF_WINDOW_FREEZE_MODE_E enWinFreezeMode);

/**
\brief 向WINDOW传递用户外部分配的buffer，专门用于3D图形测试
\attention \n
无
\param[in] hWindow     WINDOW句柄
\param[in] pstBufAttr  外部的buffer
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_AttachExternBuffer(HI_HANDLE hWindow,HI_UNF_BUFFER_ATTR_S* pstBufAttr);

/**
\brief 设置WINDOW是否工作在快速输出模式，快速输出模式强制关闭去隔行算法关闭
\attention \n
无
\param[in] hWindow     WINDOW句柄
\param[in] bQuickOutputEnable  快速输出模式使能/禁止标志
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VO_NO_INIT    DISP未初始化
\retval ::HI_ERR_VO_INVALID_PARA   输入参数非法
\retval ::HI_ERR_VO_NULL_PTR       输入指针为空
\retval ::HI_ERR_VO_INVALID_OPT    操作非法
\retval ::HI_ERR_VO_WIN_NOT_EXIST  窗口不存在
\see \n
无
*/
HI_S32 HI_UNF_VO_SetQuickOutputEnable(HI_HANDLE hWindow, HI_BOOL bQuickOutputEnable);

/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif
