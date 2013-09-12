/**
 \file
 \brief HiGo公共内容头文件
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author s37678
 \date 2008-5-16
 */

#ifndef __HI_GO_COMM_H__
#define __HI_GO_COMM_H__

/* add include here */
#include "hi_type.h"
#include "hi_go_errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_2 */
/** @{ */  /** <!-- 【HiGo公共内容】 */

/** 调色板最大颜色数 */
#define MAX_PALETTE_COLOR_SIZE 256

/** 颜色值 */
typedef HI_U32 HI_COLOR;

/** 调色板 */
typedef HI_COLOR HI_PALETTE[MAX_PALETTE_COLOR_SIZE];

typedef enum 
{
    HIGO_IMGTYPE_JPEG = 0, /**< JPEG格式图片*/
    HIGO_IMGTYPE_GIF,      /**< GIF格式图片*/
    HIGO_IMGTYPE_BMP,      /**< BMP格式图片 */
    HIGO_IMGTYPE_PNG,      /**< PNG格式图片 */
    HIGO_IMGTPYE_BUTT
} HIGO_IMGTYPE_E;


/** 矩形 */
typedef struct
{
    HI_S32 x, y;

    HI_S32 w, h;
} HI_RECT;

/** 区域 */
typedef struct
{
    HI_S32 l;
    HI_S32 t;
    HI_S32 r;
    HI_S32 b;
} HI_REGION;


#define HIGO_INVALID_HANDLE 0x0

/** 流式位置*/


/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_2 */
/** @{ */  /** <!-- 【HiGo公共内容】 */

/** 
\brief HiGo初始化
\attention \n
使用HiGo功能必须先调用该接口，完成HiGo的初始化，主要包括gdev, decoder, winc, blit, surface模块
\param 无

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_INITFAILED

\see \n
::HI_GO_Deinit
*/
HI_S32	HI_GO_Init(HI_VOID);

/** 
\brief HiGo去初始化
\attention \n
不再使用HiGo功能时需要调用该接口，释放资源
\param 无

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_Init
*/
HI_S32	HI_GO_Deinit(HI_VOID);


/** 
\brief HiGo 扩展库初始化
\attention \n
不再使用HiGo扩展库功能时需要调用该接口，释放资源，主要是CURSOR和TEXT模块。
\param 无

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_DeInitExt
*/
HI_S32 HI_GO_InitExt();

/** 
\brief HiGo扩展库去初始化
\attention \n
不再使用HiGo功能时需要调用该接口，释放资源
\param 无

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_InitExt
*/
HI_S32 HI_GO_DeInitExt();

/** 
\brief 获取版本信息
\attention \n
无
\param[out] ppVersion  版本信息字符串输出地址，不可为空
\param[out] ppBuildTime Build时间字符串输出地址，不可为空

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR

\see \n
无
*/
HI_S32 HI_GO_GetVersion(HI_CHAR ** ppVersion, HI_CHAR **ppBuildTime);

/** 
\brief 将Surface中的数据转换成BMP格式图象输出。
\attention \n
输出文件名为[year]-[date]-[hour]-[min]-[second]-[ms].bmp
输出图片固定为16位图。
建议使用HI_GO_EncodeToFile接口来代替此接口

\param[in] Surface需要进行截屏的数据。
\param[in] pRect区域指针,为空表示整个surface。


\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVSURFACEPF
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NOMEM

*/
HI_S32	HI_GO_Surface2Bmp(HI_HANDLE Surface, const HI_RECT *pRect);

/** 
\brief 使能内存管理模块
\attention \n
默认情况处于非使能状态，只有该接口打开后才能使用内存统计功能

\param[in] bEnable是否开启内存统计功能

\retval ::HI_SUCCESS

*/
HI_S32 HI_GO_EnableMemMng(HI_BOOL bEnable);

/** 
\brief 获取内存管理模块使能状态
\attention \n
\param[out] pbEnable 获取内存统计功能是否开启

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR

*/
HI_S32 HI_GO_GetMemMngStatus(HI_BOOL *pbEnable);

/** 
\brief 输出系统内存的总体信息
\attention \n
\param 无

\retval ::HI_SUCCESS
*/
HI_S32 HI_GO_SysMemQuene(HI_VOID);

/** 
\brief 输出MMZ内存的总体信息。
\attention \n
\param 无

\retval ::HI_SUCCESS

*/
HI_S32 HI_GO_MMZMemQuene(HI_VOID);

/** @} */  /*! <!-- API declaration end */


#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_COMM_H__ */
