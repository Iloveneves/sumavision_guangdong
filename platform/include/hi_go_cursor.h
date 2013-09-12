#ifndef _HI_GO_CURSOR_H
#define _HI_GO_CURSOR_H

#include "hi_go_comm.h"
#include "hi_go_gdev.h"
#ifdef __cplusplus
extern "C" {
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_3 */
/** @{ */  /** <!-- 【CURSOR】 */

typedef struct
{
    HI_HANDLE hCursor;    /**< 光标图片最大128*128,最小16*16像素, 
                               支持像素alpha和colorkey */
    HI_U32    HotspotX;   /**< 光标热点X坐标，相对于图片 */
    HI_U32    HotspotY;   /**< 光标热点Y坐标，相对于图片 */
} HIGO_CURSOR_INFO_S;

/** 光标层状态结构 */
typedef struct 
{
    HI_BOOL bShow;             /**< 光标层是否显示 */
} HIGO_CURSOR_STATUS_S;
/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_3 */
/** @{ */  /** <!-- 【CURSOR】 */
/**
\brief 光标初始化
\attention \n

\param 无

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_INITFAILED
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_DeinitCursor
*/

HI_S32 HI_GO_InitCursor();

/**
\brief 去初始化光标初始化
\attention \n

\param 无

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_InitCursor
*/

HI_S32 HI_GO_DeinitCursor();

/**
\brief 显示光标
\attention \n
1 输出层的光标位置默认在屏幕中间
2.show光标的时候，需要首先设置光标的信息。
\param[in] bVisible 光标层可见状态， HI_TRUE:可见， HI_FASLE:光标层不可见。

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NOCURSORINF
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_GetCursorStatus
::HI_GO_SetCursorInfo
*/
HI_S32 HI_GO_ShowCursor(HI_BOOL bVisible);

/** 
\brief 获取光标层当前状态
\attention \n
无

\param[out] pCursorStatus 光标层当前状态结构指针，不可为空

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_ShowLayer
*/
HI_S32 HI_GO_GetCursorStatus( HIGO_CURSOR_STATUS_S* pCursorStatus);


/**
\brief 移动光标到指定屏幕指定位置
\attention \n
必须在cursor为show的情况下才能改变光标位置

\param[in] x 屏幕X坐标,单位像素, 相对于图层canvas surface
\param[in] y 屏幕Y坐标,单位像素, 相对于图层canvas surface

\retval ::HIGO_ERR_NOTINIT
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_SetCursorPos(HI_S32 x, HI_S32 y);

/**
\brief 取得光标的屏幕坐标
\attention \n
无
\param[out] pX 光标的屏幕X坐标,单位像素
\param[out] pY 光标的屏幕Y坐标,单位像素

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_GetCursorPos(HI_S32* pX, HI_S32* pY);


/**
\brief 设置光标的显示图片的热点
\attention \n
图片最小16x16,最大128x128像素，支持colorkey, alpha。 
\param[in] pCursorInfo 光标图片，热点坐标信息

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVHOTSPOT
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_SetCursorInfo(const HIGO_CURSOR_INFO_S* pCursorInfo);

/**
\brief 获取光标的显示图片信息
\attention \n
\param[in] pCursorInfo 光标图片，热点坐标信息

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_GetCursorInfo(HIGO_CURSOR_INFO_S* pCursorInfo);

/**
\brief 将光标绑定到图层上，支持一个光标绑定到多个图层上
\attention \n
必须将光标绑定到一个已经open的图层上。
\param[in] hLayer 图层ID

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_NOTOPEN
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32  HI_GO_AttchCursorToLayer(HI_HANDLE hLayer);

/**
\brief 将光标解绑定图层
\attention \n
\param[in] hLayer 图层ID

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32  HI_GO_DetachCursorFromLayer(HI_HANDLE hLayer);
/** @} */  /** <!-- ==== API declaration end ==== */
#ifdef __cplusplus
}
#endif


#endif
