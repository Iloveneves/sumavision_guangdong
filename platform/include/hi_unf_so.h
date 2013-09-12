/**
 \file
 \brief Subtitle output模块
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author 
 \date 2010-03-10
 */

#ifndef __HI_UNF_SO_H__
#define __HI_UNF_SO_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Macro Definition ****************************/
#define HI_UNF_SO_PALETTE_ENTRY (256)    /**< 调色板颜色个数 */
#define HI_UNF_SO_NO_PTS        (-1)

/*************************** Structure Definition ****************************/

/** 字幕类型 */
typedef enum hiUNF_SO_SUBTITLE_TYPE_E
{
    HI_UNF_SUBTITLE_BITMAP = 0x0,  /**< 图像字幕 */
    HI_UNF_SUBTITLE_TEXT,          /**< string字幕 */
    HI_UNF_SUBTITLE_ASS,           /**< ass字幕 */
    HI_UNF_SUBTITLE_BUTT
} HI_UNF_SO_SUBTITLE_TYPE_E;

/** 显示消息，对于teltext，含显示和擦除两个消息 */
typedef enum hiUNF_SO_DISP_MSG_TYPE_E
{
	HI_UNF_SO_DISP_MSG_NORM  = 0x0,     /**< 正常显示数据 */
	HI_UNF_SO_DISP_MSG_ERASE,           /**< 擦除 */
	HI_UNF_SO_DISP_MSG_END              /**< 整页显示结束 */
} HI_UNF_SO_DISP_MSG_TYPE_E;

/** 颜色结构 */
typedef struct hiUNF_SO_COLOR_S
{
    HI_U8 u8Red;      /**< R分量颜色值 */
    HI_U8 u8Green;    /**< G分量颜色值 */
    HI_U8 u8Blue;     /**< B分量颜色值 */
    HI_U8 u8Alpha;    /**< 透明度 */
} HI_UNF_SO_COLOR_S;

/** 图像字幕信息 */
typedef struct hiUNF_SO_GFX_S
{
    HI_S64 s64Pts;         /**< 显示时间戳 */
	HI_U32 u32Duration;    /**< 显示时长 */
    HI_U32 u32Len;         /**< 数据长度 */
	HI_U8  *pu8PixData;    /**< 图像数据 */

    HI_UNF_SO_DISP_MSG_TYPE_E enMsgType;                   /**< 显示消息类型 */  
    HI_UNF_SO_COLOR_S stPalette[HI_UNF_SO_PALETTE_ENTRY];  /**< 调色板 */
	HI_S32 s32BitWidth;    /**< 象素位宽 , 可以为 2,4,8位*/
    HI_U32 x, y, w, h;     /**< 显示位置和高宽信息 */
} HI_UNF_SO_GFX_S;

/** 文本字幕信息 */
typedef struct hiUNF_SO_TEXT_S
{
    HI_S64 s64Pts;              /**< 显示时间戳 */
    HI_U32 u32Duration;         /**< 显示时长 */
    HI_U32 u32Len;              /**< 字幕数据长度 */
    HI_U8 *pu8Data;             /**< 字幕数据 */

    HI_U32 x, y, w, h;          /**< 显示位置和高宽信息 */
} HI_UNF_SO_TEXT_S;

/** ass字幕信息 */
typedef struct hiUNF_SO_ASS_S
{
    HI_S64 s64Pts;                /**< 显示时间戳 */
    HI_U32 u32Duration;           /**< 显示时长 */
    HI_U32 u32FrameLen;           /**< 帧长度 */
    HI_U8  *pu8EventData;         /**< 帧数据 */
    HI_U32 u32ExtradataSize;      /**< 扩展数据长度 */
    HI_U8  *pu8Extradata;         /**< 扩展数据 */
} HI_UNF_SO_ASS_S;

typedef struct hiUNF_SO_SUBTITLE_INFO_S
{
    HI_UNF_SO_SUBTITLE_TYPE_E eType;

    union
    {
        HI_UNF_SO_GFX_S  stGfx;
        HI_UNF_SO_TEXT_S stText;
        HI_UNF_SO_ASS_S  stAss;
    } unSubtitleParam;
} HI_UNF_SO_SUBTITLE_INFO_S;

/** 
\brief 获取当前播放帧的时间戳，如果当前时间无效，ps64CurrentPts赋值为HI_UNF_SO_NO_PTS
\attention \n
无
\param[in] u32UserData 注册传入的用户数据
\param[out] ps64CurrentPts 当前播放帧时间戳，单位ms 

\retval ::HI_SUCCESS

\see \n
无
*/
typedef HI_S32 (*HI_UNF_SO_GETPTS_FN)(HI_U32 u32UserData, HI_S64 *ps64CurrentPts);

/** 
\brief 字幕画图回调函数
\attention \n
无
\param[in] u32UserData 注册传入的用户数据
\param[in] pstInfo 字幕信息
\param[in] pArg 扩展数据

\retval ::HI_SUCCESS

\see \n
无
*/
typedef HI_S32 (*HI_UNF_SO_ONDRAW_FN)(HI_U32 u32UserData, const HI_UNF_SO_SUBTITLE_INFO_S *pstInfo, HI_VOID *pArg);

/** 
\brief 字幕显示到时清除函数
\attention \n
无
\param[in] u32UserData 注册传入的用户数据

\retval ::HI_SUCCESS

\see \n
无
*/
typedef HI_S32 (*HI_UNF_SO_ONCLEAR_FN)(HI_U32 u32UserData);

/******************************* API declaration *****************************/

/**
\brief  subtitle output模块初始化
\attention \n
无
\param 无

\retval ::HI_SUCCESS  初始化成功
\retval ::HI_FAILURE  初始化失败

\see \n
无
*/
HI_S32 HI_UNF_SO_Init(HI_VOID);

/**
\brief  subtitle output模块去初始化
\attention \n
无
\param 无

\retval ::HI_SUCCESS  去初始化成功
\retval ::HI_FAILURE  去初始化失败

\see \n
无
*/
HI_S32 HI_UNF_SO_DeInit(HI_VOID);

/**
\brief  创建一个so实例
\attention \n
无
\param[out] phdl 播放器实例

\retval ::HI_SUCCESS  创建成功，句柄有效
\retval ::HI_FAILURE  创建失败

\see \n
无
*/
HI_S32 HI_UNF_SO_Create(HI_HANDLE *phdl);

/**
\brief  销毁一个so实例
\attention \n
无
\param[in] handle so实例句柄

\retval ::HI_SUCCESS  销毁成功
\retval ::HI_FAILURE  销毁失败，参数非法

\see \n
无
*/
HI_S32 HI_UNF_SO_Destroy(HI_HANDLE handle);

/**
\brief  注册时间戳获取回调函数，so通过获取当前播放时间戳同步字幕
\attention \n
无
\param[in] handle so实例句柄
\param[in] pstCallback 回调函数参数
\param[in] u32UserData 用户数据

\retval ::HI_SUCCESS  注册成功
\retval ::HI_FAILURE  注册失败

\see \n
无
*/
HI_S32 HI_UNF_SO_RegGetPtsCb(HI_HANDLE handle, HI_UNF_SO_GETPTS_FN pstCallback, HI_U32 u32UserData);

/**
\brief  注册字幕绘制清除回调函数，如果设置了该函数，则so使用该函数实现字幕输出，
        字幕显示时长到达后，so调用清除函数通知清除
\attention \n
无
\param[in] handle so实例句柄
\param[in] pfnOnDraw 绘制函数
\param[in] pfnOnClear 清除函数
\param[in] u32UserData 用户数据

\retval ::HI_SUCCESS  注册成功
\retval ::HI_FAILURE  注册失败

\see \n
无
*/
HI_S32 HI_UNF_SO_RegOnDrawCb(HI_HANDLE handle, HI_UNF_SO_ONDRAW_FN pfnOnDraw,
                                          HI_UNF_SO_ONCLEAR_FN pfnOnClear, HI_U32 u32UserData);

/**
\brief  设置字幕绘制画布句柄，如果没有设置ondraw回调函数，则so使用设置的画布句柄输出字幕
\attention \n
无
\param[in] handle so实例句柄
\param[in] hSurfaceHandle 画布句柄

\retval ::HI_SUCCESS  设置成功
\retval ::HI_FAILURE  设置失败

\see \n
无
*/
HI_S32 HI_UNF_SO_SetDrawSurface(HI_HANDLE handle, HI_HANDLE hSurfaceHandle);

/**
\brief  设置字幕显示字体，该设置仅对设置画布输出字幕的方式起作用
\attention \n
无
\param[in] handle so实例句柄
\param[in] hFont 创建的字体句柄

\retval ::HI_SUCCESS  设置成功
\retval ::HI_FAILURE  设置失败

\see \n
无
*/
HI_S32 HI_UNF_SO_SetFont(HI_HANDLE handle, HI_HANDLE hFont);

/**
\brief  设置字幕显示颜色，该设置仅对设置画布输出字幕的方式起作用
\attention \n
无
\param[in] handle so实例句柄
\param[in] u32Color 颜色值

\retval ::HI_SUCCESS  设置成功
\retval ::HI_FAILURE  设置失败

\see \n
无
*/
HI_S32 HI_UNF_SO_SetColor(HI_HANDLE handle, HI_U32 u32Color);

/**
\brief  设置字幕显示坐标，该设置仅对设置画布输出字幕的方式起作用
\attention \n
无
\param[in] handle so实例句柄
\param[in] u32x x坐标
\param[in] u32y y坐标

\retval ::HI_SUCCESS  设置成功
\retval ::HI_FAILURE  设置失败

\see \n
无
*/
HI_S32 HI_UNF_SO_SetPos(HI_HANDLE handle, HI_U32 u32x, HI_U32 u32y);

/**
\brief  获取缓冲buffer中未显示的字幕数据个数
\attention \n
无
\param[in] handle so实例句柄
\param[out] pu32SubNum 缓冲字幕个数

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 失败

\see \n
无
*/
HI_S32 HI_UNF_SO_GetSubNumInBuff(HI_HANDLE handle, HI_U32 *pu32SubNum);

/**
\brief  清除字幕缓冲中的数据，字幕切换时，需调用该接口清除so字幕缓存
\attention \n
无
\param[in] handle so实例句柄

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 失败

\see \n
无
*/
HI_S32 HI_UNF_SO_ResetSubBuf(HI_HANDLE handle);

/**
\brief  发送字幕数据给so
\attention \n
无
\param[in] handle so实例句柄
\param[in] pstSubInfo 字幕信息
\param[in] u32TimeOut 发送超时时间，单位ms

\retval ::HI_SUCCESS  发送成功
\retval ::HI_FAILURE  发送失败

\see \n
无
*/
HI_S32 HI_UNF_SO_SendData(HI_HANDLE handle, const HI_UNF_SO_SUBTITLE_INFO_S *pstSubInfo, HI_U32 u32TimeOutMs);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_SO_H__ */

