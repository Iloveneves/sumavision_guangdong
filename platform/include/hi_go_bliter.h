/**
 \file
 \brief bliter头文件
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author s37678
 \date 2008-5-23
 */

#ifndef __HI_GO_BLITER_H__
#define __HI_GO_BLITER_H__

#include "hi_go_comm.h"
#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/


/****************************** Error Number ********************************/


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_1 */
/** @{ */  /** <!-- 【bliter】 */

/** 像素级alpha混合操作运算 */
typedef enum
{
    HIGO_COMPOPT_NONE = 0, /**< Porter/Duff None混合操作 */
    HIGO_COMPOPT_CLEAR,    /**< Porter/Duff clear混合操作 */
    HIGO_COMPOPT_SRC     , /**< Porter/Duff Src混合操作 */ 
    HIGO_COMPOPT_SRCOVER , /**< Porter/Duff Srcover混合操作 */ 
    HIGO_COMPOPT_DSTOVER , /**< Porter/Duff DstOver混合操作 */ 
    HIGO_COMPOPT_SRCIN   , /**< Porter/Duff SrcIn混合操作 */ 
    HIGO_COMPOPT_DSTIN   , /**< Porter/Duff DstIn混合操作 */ 
    HIGO_COMPOPT_SRCOUT  , /**< Porter/Duff SrcOut混合操作 */ 
    HIGO_COMPOPT_DSTOUT  , /**< Porter/Duff DstOut混合操作 */ 
    HIGO_COMPOPT_SRCATOP , /**< Porter/Duff SrcAtop混合操作 */ 
    HIGO_COMPOPT_DSTATOP , /**< Porter/Duff DstAtop混合操作 */ 
    HIGO_COMPOPT_ADD     , /**< Porter/Duff DstAtop混合操作 */ 
    HIGO_COMPOPT_XOR     , /**< Porter/Duff Xor混合操作 */ 
    HIGO_COMPOPT_DST     , /**< Porter/Duff DstAtop混合操作 */ 
    HIGO_COMPOPT_AKS,      /**< 假设目标surface为不透明，简单alpha混合，结果保留源alpha */
    HIGO_COMPOPT_AKD,      /**< 假设目标surface为不透明，简单alpha混合，结果保留目标alpha */

    HIGO_COMPOPT_BUTT
} HIGO_COMPOPT_E;

/** Colorkey对应的操作方式 */
typedef enum
{
    HIGO_CKEY_NONE = 0, /**< 不使用colorkey */
    HIGO_CKEY_SRC,      /**< 使用源colorkey */
    HIGO_CKEY_DST,      /**< 使用目标colorkey */

    HIGO_CKEY_BUTT
} HIGO_CKEY_E;

/** 2元ROP操作 */
typedef enum
{
    HIGO_ROP_BLACK = 0, /**< Blackness */
    HIGO_ROP_PSDon,     /**< ~(PS+D) */
    HIGO_ROP_PSDna,     /**< ~PS & D */
    HIGO_ROP_PSn,       /**< ~PS */
    HIGO_ROP_DPSna,     /**< PS & ~D */
    HIGO_ROP_Dn,        /**< ~D */
    HIGO_ROP_PSDx,      /**< PS^D */
    HIGO_ROP_PSDan,     /**< ~(PS&D) */
    HIGO_ROP_PSDa,      /**< PS & D */
    HIGO_ROP_PSDxn,     /**< ~(PS^D) */
    HIGO_ROP_D,         /**< D */
    HIGO_ROP_PSDno,     /**< ~PS + D */
    HIGO_ROP_PS,        /**< PS */
    HIGO_ROP_DPSno,     /**< PS + ~D */
    HIGO_ROP_PSDo,      /**< PS+D */
    HIGO_ROP_WHITE,     /**< Whiteness */

    HIGO_ROP_BUTT
} HIGO_ROP_E;

typedef enum
{
    HIGO_ROTATE_NONE = 0,
    HIGO_ROTATE_90,     /**< 顺时针旋转90度 */
    HIGO_ROTATE_180,    /**< 顺时针旋转180度 */
    HIGO_ROTATE_270,    /**< 顺时针旋转270度 */

    HIGO_ROTATE_BUTT
} HIGO_ROTATE_E;

typedef enum
{
    HIGO_MIRROR_NONE = 0,

    HIGO_MIRROR_LR,     /**< 左右镜像 */
    HIGO_MIRROR_TB,     /**< 上下镜像 */

    HIGO_MIRROR_BUTT
} HIGO_MIRROR_E;

typedef struct 
{
    HI_BOOL EnableGlobalAlpha;      /**< 全局alpha使能标志 */
    HI_BOOL EnablePixelAlpha;       /**< 像素alpha使能标志 */
    HIGO_COMPOPT_E PixelAlphaComp;  /**< 像素alpha操作 */
    HIGO_CKEY_E    ColorKeyFrom;    /**< ColorKey操作 */
    HI_BOOL        EnableRop;       /**< 启用ROP2操作 */
    HIGO_ROP_E     Rop;             /**< ROP2操作类型 */
    HIGO_ROP_E     RopAlpha;        /**< ROP alpha操作类型*/
 }HIGO_BLTOPT2_S;

/** blit操作属性 */
typedef struct
{
    HI_BOOL EnableGlobalAlpha;      /**< 全局alpha使能标志,打开此开关之外还必须指定PixelAlphaComp的混合方式*/
    HI_BOOL EnablePixelAlpha;       /**< 像素alpha使能标志 */
    HIGO_COMPOPT_E PixelAlphaComp;  /**< 像素alpha操作 */
    HIGO_CKEY_E    ColorKeyFrom;    /**< ColorKey操作 */
    HI_BOOL        EnableRop;       /**< 启用ROP2操作 */
    HIGO_ROP_E     Rop;             /**< ROP2操作类型 */
    HIGO_ROP_E     RopAlpha;        /**< ROP alpha操作类型*/    
    HI_BOOL        EnableScale;     /**< 启用缩放 */
    HIGO_ROTATE_E  RotateType;      /**< 旋转方式 */
    HIGO_MIRROR_E  MirrorType;      /**< 镜像方式 */
} HIGO_BLTOPT_S;

typedef struct
{
    HI_BOOL EnableGlobalAlpha;      /**< 全局alpha使能标志 */

    HIGO_COMPOPT_E PixelAlphaComp;  /**< 像素alpha操作 */
    HI_BOOL        EnableRop;       /**< 启用ROP2操作 */
    HIGO_ROP_E     RopColor;        /**< ROP2操作类型 */
	HIGO_ROP_E     RopAlpha;
		
} HIGO_MASKOPT_S;

/** 抗闪烁级别 */
typedef enum
{
    HIGO_DEFLICKER_AUTO = 0, /*抗闪烁级别，值为LOW~HIGH,值越大抗闪烁效果越好，但越模糊*/
    HIGO_DEFLICKER_LOW,
    HIGO_DEFLICKER_MIDDLE,
    HIGO_DEFLICKER_HIGH,
    HIGO_DEFLICKER_BUTT
}HIGO_DEFLICKEROPT_E;

/** 抗闪烁级别 */
typedef struct
{
    HIGO_DEFLICKEROPT_E DefLevel;
}HIGO_DEFLICKEROPT_S;
/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_1 */
/** @{ */  /** <!-- 【bliter】 */

/** 
\brief 初始化Bliter模块
\attention \n
::HI_GO_Init中已包含了对该接口的调用
\param 无

\retval ::HI_SUCCESS  
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
::HI_GO_Init \n
::HI_GO_DeinitBliter
*/
HI_S32 HI_GO_InitBliter(HI_VOID);

/** 
\brief 去初始化Bliter模块
\attention \n
::HI_GO_Deinit中已包含了对该接口的调用
\param 无

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_Deinit \n
::HI_GO_InitBliter
*/

HI_S32 HI_GO_DeinitBliter(HI_VOID);

/** 
\brief 矩形填充
\attention \n
无
\param[in] Surface Surface句柄
\param[in] pRect 填充矩形大小，为空表示填充整个surface
\param[in] Color 填充颜色,注意如果是RGB格式，统一填充32位色，如果调色板，就直接填充颜色索引(0 ~ 255)。
\param[in] CompositeOpt 混合方式

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_OUTOFPAL
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS
\see \n
无
*/
HI_S32 HI_GO_FillRect(HI_HANDLE Surface, const HI_RECT* pRect, HI_COLOR Color, HIGO_COMPOPT_E CompositeOpt);

/** 
\brief 位块搬移，在搬移过程中，可以实现色彩空间转换、缩放、旋转功能
\attention \n
色彩空间转换仅支持YUV到RGB转换 \n
可以支持操作如下colorkey、alpha、ROP、colorkey+ROP\
缩放、旋转或镜像不可组合使用 \n
缩放、旋转或镜像要求源与目标像素格式完全相同，但不能是YUV格式和CLUT格式 \n

\param[in] SrcSurface 源surface句柄
\param[in] pSrcRect 搬移的源区域，为空表示整个源surface区域
\param[in] DstSurface 目的surface句柄
\param[in] pDstRect 搬移的目的区域，为空表示整个目标surface区域
\param[in] pBlitOpt 混合方式

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVMIRRORTYPE
\retval ::HIGO_ERR_INVROTATETYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_NOCOLORKEY
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_INTERNAL

\see \n
无
*/
HI_S32 HI_GO_Blit (HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                   HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                   const HIGO_BLTOPT_S* pBlitOpt);

/** 
\brief 绘制线段，不支持裁减
\attention \n
不支持裁减，使用者必须保证整条直线在surface区域内

\param[in] Surface 目的surface句柄
\param[in] x0 起点x坐标
\param[in] y0 起点y坐标
\param[in] x1 终点x坐标
\param[in] y1 终点y坐标 
\param[in] color 线段颜色

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
无
*/
HI_S32 HI_GO_DrawLine(HI_HANDLE Surface, HI_S32 x0, HI_S32 y0, HI_S32 x1, HI_S32 y1, HI_COLOR color);

/** 
\brief 绘制椭圆
\attention \n
不支持裁减，使用者必须保证整个椭圆在surface区域内

\param[in] Surface 目的surface句柄
\param[in] sx 圆心x坐标
\param[in] sy 圆心y坐标
\param[in] rx x轴半径 
\param[in] ry y轴半径
\param[in] color 椭圆颜色

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
无
*/
HI_S32 HI_GO_DrawEllipse(HI_HANDLE Surface, HI_S32 sx, HI_S32 sy, HI_S32 rx, HI_S32 ry, HI_COLOR color);

/** 
\brief 绘制圆，不支持裁减
\attention \n
不支持裁减，使用者必须保证整个圆在surface区域内

\param[in] Surface 目的surface句柄
\param[in] x 圆心x坐标
\param[in] y 圆心y坐标
\param[in] r 半径
\param[in] color 圆颜色, 颜色按照32位色进行填充

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
无
*/
HI_S32 HI_GO_DrawCircle(HI_HANDLE Surface, HI_S32 x, HI_S32 y, HI_S32 r, HI_COLOR color);

/** 
\brief 绘制矩形
\attention \n
矩形为空表示输出矩形大小与surface相同
不支持裁减，使用者必须保证整个矩形在surface区域内

\param[in] Surface 目的surface句柄
\param[in] pRect 矩形区域
\param[in] color 矩形颜色

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
无
*/
HI_S32 HI_GO_DrawRect(HI_HANDLE Surface, const HI_RECT* pRect, HI_COLOR color);

/** 
\brief 对光栅位图进行Mask Rop或者Mask Blend搬移操作
\attention \n
Mask是A1或A8的位图Surface。
首先将Mask位图与源位图做一次叠加，然后用叠加的结果和目标做叠加输出到目标位图
Rop和Blend混合同时只能有一个是有效的，两者都选只有Rop生效

\param[in] SrcSurface 源surface句柄
\param[in] pSrcRect 源矩形
\param[in] DstSurface 目标surface句柄
\param[in] pDstRect 目标矩形
\param[in] MaskSurface MASK surface句柄
\param[in] pMaskRect MASK矩形
\param[in] pOpt 操作选项

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_INVRECT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_INTERNAL

\see \n
无
*/

HI_S32 HI_GO_MaskBlit(HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                      HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                      HI_HANDLE MaskSurface, const HI_RECT* pMaskRect,
                      const HIGO_MASKOPT_S* pOpt);


/** 
\brief 位块搬移，在搬移过程中，可以实现色彩空间转换
\attention \n
色彩空间转换仅支持YUV到RGB转换 \n
可以支持操作如下colorkey、alpha、ROP、colorkey+ROP\

\param[in] SrcSurface 源surface句柄
\param[in] pSrcRect 搬移的源区域，为空表示整个源surface区域
\param[in] DstSurface 目的surface句柄
\param[in] pDstRect 搬移的目的区域，为空表示整个目标surface区域
\param[in] pBlitOpt 混合方式，参数为空使用默认参数操作

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS

\see \n
无
*/
HI_S32 HI_GO_BitBlit (HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                       HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                       const HIGO_BLTOPT2_S* pBlitOpt);

/** 
\brief 位块搬移，在搬移过程中，可以实现色彩空间转换, 缩放
\attention \n
色彩空间转换仅支持YUV到RGB转换 \n
可以支持操作如下colorkey、alpha、ROP、colorkey+ROP\

\param[in] SrcSurface 源surface句柄
\param[in] pSrcRect 搬移的源区域，为空表示整个源surface区域
\param[in] DstSurface 目的surface句柄
\param[in] pDstRect 搬移的目的区域，为空表示整个目标surface区域
\param[in] pBlitOpt 混合方式,参数为空使用默认参数操作

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS

\see \n
无
*/
HI_S32 HI_GO_StretchBlit (HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                       HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                       const HIGO_BLTOPT2_S* pBlitOpt);


/**
\brief 进行模式填充
\attention \n
\param[in] SrcSurface 源surface句柄
\param[in] pSrcRect 搬移的源区域，为空表示整个源surface区域
\param[in] DstSurface 目的surface句柄
\param[in] pDstRect 搬移的目的区域，为空表示整个目标surface区域
\param[in] pParOpt 混合方式,参数为空使用默认参数操作

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_NOCOLORKEY
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS

\see \n
无
*/
HI_S32 HI_GO_PatternBlit(HI_HANDLE SrcSurface, const HI_RECT* pSrcRect, 
                              HI_HANDLE DstSurface, const HI_RECT * pDstRect, 
                              const HIGO_BLTOPT2_S* pParOpt);


/**
\brief 抗闪烁搬移，这个接口用于第二次抗闪烁，
\attention \n
两种情况用到该接口
1 当图层的自动抗闪烁效果不是很好时，可以使用这个接口再做一次。
2 当图层的buffer模式是单buffer模式(HIGO_LAYER_BUFFER_SINGLE)时，用户需要自己做抗闪烁
当源和目标大小不同的时候自动进行缩放。

\param[in] SrcSurface 源surface句柄
\param[in] pSrcRect 搬移的源区域，为空表示整个源surface区域
\param[in] DstSurface 目的surface句柄
\param[in] pDstRect 搬移的目的区域，为空表示整个目标surface区域
\param[in] pDefOpt 抗闪烁级别选项，为空表示AUTO 级别

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_NOCOLORKEY
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS

\see \n
无
*/
HI_S32 HI_GO_DeflickerBlit(HI_HANDLE SrcSurface, const HI_RECT* pSrcRect, 
                                 HI_HANDLE DstSurface, const HI_RECT * pDstRect, 
                                 const HIGO_DEFLICKEROPT_S* pDefOpt);


/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_BLITER_H__ */
