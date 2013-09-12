/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_vp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/03/25
  Description   :
  History       :
  1.Date        : 2011/03/25
    Author      :
    Modification: Created file

 *******************************************************************************/

/**
 * \file
 * \brief 提供VP视频引擎的相关信息
 */
#ifndef __HI_UNF_VP_H__
#define __HI_UNF_VP_H__
#include "hi_common.h"
#include "hi_unf_common.h"
#include "hi_unf_vi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

typedef struct hi_VP_VENC_CHN_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E     enEncType;	       /**<解码器类型 */
    HI_UNF_VI_E              enViPort;		   /**<输入端口 */
    HI_UNF_VI_INPUT_MODE_E   enInputMode;      /**<视频输入模式，目前只支持USB摄像头*/
    HI_U32                   u32Width;
    HI_U32                   u32Height;
    HI_U32                   u32TargetBitRate; /**< RC参数,可动态设置 */
    HI_U32                   u32TargetFrmRate; /**< 目标帧率,可动态设置 */ 
    HI_U32                   u32InputFrmRate;  /**< 输入帧率,可动态设置,u32TargetFrmRate <= u32InputFrmRate */ 
    HI_U32                   u32Gop;		   /**< GOP大小,可动态设置 */ 
	HI_UNF_VP_NET_PARA_S     stEncNetPara;	   /**< 本地网络参数*/	
}HI_VP_VENC_CHN_ATTR_S; 

typedef struct hi_VP_VDEC_CHN_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E     enDecType;	       /**< 解码器类型 */
	HI_UNF_VP_NET_PARA_S     stDecNetPara;	   /**< 本地网络参数*/
	
}HI_VP_VDEC_CHN_ATTR_S;          


/* 视频引擎通道属性 */
typedef struct hiUNF_VP_CHN_ATTR_S
{
    HI_HANDLE hLocalWin;                       /**< 本地VO窗口句柄 */  
    HI_HANDLE hRemoteWin;                      /**< 远端VO窗口句柄 */	
    HI_VP_VENC_CHN_ATTR_S stEncAttr;           /**< 编码器参数 */
	HI_VP_VDEC_CHN_ATTR_S stDecAttr;           /**< 解码器参数 */
}HI_UNF_VP_CHN_ATTR_S;


/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_3 */
/** @{ */  /** <!-- 【VP】 */

/**
 \brief 初始化VP模块
 \attention \n
在调用::HI_UNF_VP_Create接口创建引擎之前，调用本接口
 \param 无
 \retval ::HI_SUCCESS 成功
 \retval ::HI_ERR_VP_DEV_NOT_EXIST   设备不存在
 \retval ::HI_ERR_VP_DEV_OPEN_ERR   设备打开错误
 \see \n
无
 */
HI_S32 HI_UNF_VP_Init(HI_VOID);

/**
 \brief 去初始化VP模块
 \attention \n
在调用::HI_UNF_VP_DestroyChannel接口销毁所有的VP通道后，调用本接口
 \param 无
 \retval ::HI_SUCCESS 成功
 \retval ::HI_ERR_VP_NOT_INIT    VP设备不存在
 \see \n
无
 */
HI_S32 HI_UNF_VP_DeInit(HI_VOID);

/**
 \brief 获取VP通道缺省参数
 \attention \n
在调用::HI_UNF_VP_CreateChannel接口创建VP通道之前，调用本接口，方便填写参数
 \param[in] 无
 \param[out] pstDefChAttr  指针类型，VP通道默认属性，参见:HI_UNF_VP_CHN_ATTR_S
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_NULL_PTR  空指针
 \see \n
无
 */
HI_S32 HI_UNF_VP_GetChDefaultAttr(HI_UNF_VP_CHN_ATTR_S *pstDefChAttr);

/**
 \brief 创建VP通道
 \attention \n
无
 \param[in]  pstChAttr 通道参数
 \param[out] phVp  指针类型，VP通道句柄
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_NULL_PTR  空指针
 \retval ::HI_ERR_VP_NOT_SUPPORT          输入参数非法
 \retval ::HI_ERR_VP_NOT_SUPPORT          不支持模式
 \see \n
无
 */
HI_S32 HI_UNF_VP_CreateChannel(HI_UNF_VP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVp);

/**
 \brief 销毁VP 通道
 \attention \n
无
 \param[in] hVp  VP 通道句柄
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_NOT_INIT         VP未初始化
 \retval ::HI_ERR_VP_INVALID_HANDLE   非法的VP句柄
 \retval ::其它  销毁通道失败
 \see \n
无
 */
HI_S32 HI_UNF_VP_DestroyChannel(HI_HANDLE hVp);

/**
 \brief 获取VP 通道配置
 \attention \n
 \param[in] hVP  VP 通道句柄
 \param[out] pstChAttr  指针类型，VP 通道属性，参见:HI_UNF_VP_CHN_ATTR_S
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VP_NULL_PTR  空指针
 \retval ::其它  获取通道属性失败
 \see \n
无
 */
HI_S32 HI_UNF_VP_GetChAttr(HI_HANDLE hVp, HI_UNF_VP_CHN_ATTR_S *pstChAttr);

/**
 \brief 修改VP通道配置
 \attention \n
        建议先调用HI_UNF_VP_GetChAttr()获取当前通道配置，再对参数做必要修改，对应的更改标记置1，无关更改标志置0。
 \param[in] hVp  VP 通道句柄
 \param[in] pstChAttr  指针类型，VP 通道属性，参见:HI_UNF_VP_CHN_ATTR_S
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VP_NULL_PTR  空指针
 \retval ::其它  修改通道属性失败
 \see \n
无
 */
HI_S32 HI_UNF_VP_SetChAttr(HI_HANDLE hVp, HI_UNF_VP_CHN_ATTR_S *pstChAttr);

/**
 \brief VP通道开始运行
 \attention \n
        在参数准备好后，包括编解码器、VI/VO设置正确后，调用此接口可以启动视频引擎的运行，实现网络收发、显示本地、远端视频输出
 \param[in] hVp  VP 通道句柄
 
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VP_NULL_PTR  空指针
 \retval ::其它  VP通道开始运行失败
 \see \n
无
 */
HI_S32 HI_UNF_VP_Start(HI_HANDLE hVp);

/**
 \brief VP通道停止运行
 \attention \n
        在VP通道正常启动运行后，可以通过此接口暂停运行，使画面冻结、网络收发暂停。可以调用HI_UNF_VP_Start恢复运行
 \param[in] hVp  VP 通道句柄
 
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VP_NULL_PTR  空指针
 \retval ::其它  VP通道开始运行失败
 \see \n
无
 */
HI_S32 HI_UNF_VP_Stop(HI_HANDLE hVp);

/**
 \brief VP通道开始预览本地视频
 \attention \n
        在VI和hLocalWin准备好之后，开始预览本地视频
 \param[in] hVp  VP 通道句柄
 
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VP_NULL_PTR  空指针
 \retval ::其它  VP通道开始运行失败
 \see \n
无
 */
HI_S32 HI_UNF_VP_StartPreView(HI_HANDLE hVp);

/**
 \brief VP通道预览本地视频
 \attention \n
        在VP通道预览本地视频后，调用停止预览
 \param[in] hVp  VP 通道句柄
 
 \retval ::HI_SUCCESS  成功
 \retval ::HI_ERR_VP_INVALID_PARA   无效的输入参数
 \retval ::HI_ERR_VP_NULL_PTR  空指针
 \retval ::其它  VP通道开始运行失败
 \see \n
无
 */
HI_S32 HI_UNF_VP_StopPreView(HI_HANDLE hVp);
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
