/**
 \file
 \brief Gdev模块头文件
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author w66592
 \date 2008-5-16
 */

#ifndef __HI_GO_GDEV_H__
#define __HI_GO_GDEV_H__

#include "hi_go_comm.h"
#include "hi_go_surface.h"
#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_6 */
/** @{ */  /** <!-- 【Gdev模块】 */

/*图层ID定义*/
typedef enum
{
    HIGO_LAYER_SD_0 = 0,
    HIGO_LAYER_SD_1, 
    HIGO_LAYER_HD_0,
    HIGO_LAYER_HD_1,
    HIGO_LAYER_AD_0, 
    HIGO_LAYER_BUTT,
}HIGO_LAYER_E;   /* start from 0 */


/** 标清图形叠加层0 */
#define HIGO_LAYER_RGB0 HIGO_LAYER_SD_0

/** 标清图形叠加层1 */
#define HIGO_LAYER_RGB1 HIGO_LAYER_SD_1

/*下面宏定义了higo的每个图层的buffer模式，其中canvas buffer是供用户绘制的buffer,
display buffer是用于显示输出的buffer.*/
#define HIGO_LAYER_BUFFER_SINGLE      0x02 /**< 1块canvas buffer, 无display buffer */    
#define HIGO_LAYER_BUFFER_DOUBLE      0x04 /**< 1块canvas buffer, 1块display buffer 支持双缓冲 */ 
#define HIGO_LAYER_BUFFER_TRIPLE      0x08 /**< 1块canvas buffer, 2块display buffer 支持flip,刷新的时候等待任务完成 */
#define HIGO_LAYER_BUFFER_OVER        0x10 /**< 1块canvas buffer, 2块display buffer 支持flip,如果刷新的时候带有任务忙，则丢弃当前帧 */


/**为兼容老定义，图层的刷新方式，不建议使用*/
typedef enum 
{
    HIGO_LAYER_FLUSH_FLIP        = HIGO_LAYER_BUFFER_TRIPLE, 
    HIGO_LAYER_FLUSH_DOUBBUFER   = HIGO_LAYER_BUFFER_DOUBLE, 
    HIGO_LAYER_FLUSH_NORMAL      = HIGO_LAYER_BUFFER_SINGLE, 
    HIGO_LAYER_FLUSH_OVER        = HIGO_LAYER_BUFFER_OVER,
    HIGO_LAYER_FLUSH_BUTT
} HIGO_LAYER_FLUSHTYPE_E;

typedef enum
{
    HIGO_LAYER_DEFLICKER_NONE = 0, /*抗闪烁级别，值为LOW~HIGH,值越大抗闪烁效果越好，但越模糊*/
    HIGO_LAYER_DEFLICKER_LOW,
    HIGO_LAYER_DEFLICKER_MIDDLE,
    HIGO_LAYER_DEFLICKER_HIGH,
    HIGO_LAYER_DEFLICKER_AUTO,    
    HIGO_LAYER_DEFLICKER_BUTT
}HIGO_LAYER_DEFLICKER_E;

/**图层属性参数*/
typedef struct 
{
    HI_S32                 ScreenWidth;    /**< 图层在屏幕上显示宽度，必须大于0 */
    HI_S32                 ScreenHeight;   /**< 图层在屏幕上显示高度，必须大于0 */
    HI_S32                 CanvasWidth;    /**< 图层的绘制buffer宽度，为0时，不创建绘制buffer */
    HI_S32                 CanvasHeight;   /**< 图层的绘制buffer高度，为0时，不创建绘制buffer */
    HI_S32                 DisplayWidth;   /**< 图层的显示buffer宽度，为0时，和ScreenWidth相同*/
    HI_S32                 DisplayHeight;  /**< 图层的显示buffer高度，为0时，和ScreenHeight相同*/
    HIGO_LAYER_FLUSHTYPE_E LayerFlushType; /**< 图层的刷新方式，用户可根据使用场景选择不同的刷新模式来提高刷新效率,等于0时默认使用双缓冲+Flip刷新模式 */
    HIGO_LAYER_DEFLICKER_E AntiLevel;      /**< 图层抗闪烁级别 */
    HIGO_PF_E              PixelFormat;    /**< 图层的像素格式，此格式必须为硬件图层所支持的格式，请根据不同硬件设备来选择图层的像素格式参数 */
    HIGO_LAYER_E           LayerID;        /**< 图层硬件ID，能支持图层取决于芯片平台，hi3720高清支持一个高清和一个标清 */
} HIGO_LAYER_INFO_S;

/** 图层状态结构 */
typedef struct 
{
    HI_BOOL bShow;             /**< 图层是否显示 */
} HIGO_LAYER_STATUS_S;

typedef struct
{
    HI_COLOR ColorKey;         /**< 图层的透明色*/
    HI_BOOL bEnableCK;         /**< 图层是否使能colorkey */
}HIGO_LAYER_KEY_S;

typedef struct
{
    HI_BOOL bAlphaEnable;   /**<  alpha像素使能标志 */
    HI_BOOL bAlphaChannel;  /**<  alpha通道使能标志  */
    HI_U8   Alpha0;         /**<  alpha0值,在ARGB1555格式下生效 */
    HI_U8   Alpha1;         /**<  alpha1值,在ARGB1555格式下生效 */
    HI_U8   GlobalAlpha;    /**<  全局alpha，该值只有在alpha通道有效的时候才有意义 */
}HIGO_LAYER_ALPHA_S;

/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_6 */
/** @{ */  /** <!-- 【Gdev模块】 */

/** 
\brief 初始化显示设备
\attention \n
::HI_GO_Init已包含了对该接口的调用
\param 无

\retval ::HI_FAILURE
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INITFAILED

\see \n
::HI_GO_Init \n
::HI_GO_DeinitDisplay
*/
HI_S32 HI_GO_InitDisplay(HI_VOID);

/** 
\brief 去初始化显示设备
\attention \n
::HI_GO_Deinit已包含了对该接口的调用
\param 无

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_Deinit \n
::HI_GO_InitDisplay
*/
HI_S32 HI_GO_DeinitDisplay(HI_VOID);

/**
\brief 根据图层ID获取相应图层(SD,HD)创建时的默认参数，
如果需要使用非默认值，可以直接设置pLayerInfo各个成员
\attention \n

\param[in] LayerID 图层ID
\param[in]  pLayerInfo 获取到的创建参数

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVPARAM
\see \n
无
*/
HI_S32 HI_GO_GetLayerDefaultParam (HIGO_LAYER_E LayerID, HIGO_LAYER_INFO_S *pLayerInfo);


/** 
\brief 创建图层
\attention \n
是否支持VO硬件缩放取决于平台。
如果平台支持VO 硬件缩放，即在设置displaysize与screensize不一致的情况下，最终会缩放到screensize的大小。
如果平台不支持VO 硬件缩放，即使displaysize与screensize不一致，也会强制要求displaysize与screensize一致

\param[in]  pLayerInfo 图层基本属性，不可为空
\param[out] pLayer 图层的句柄指针，不可为空

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT 
\retval ::HIGO_ERR_NULLPTR 
\retval ::HIGO_ERR_INVSIZE 
\retval ::HIGO_ERR_INVLAYERID 
\retval ::HIGO_ERR_INVPIXELFMT 
\retval ::HIGO_ERR_INVFLUSHTYPE
\retval ::HIGO_ERR_INVANILEVEL
\retval ::HIGO_ERR_INVSIZE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB
\retval ::HIGO_ERR_ALREADYBIND
\retval ::HIGO_ERR_INVLAYERSURFACE

\see \n
::HI_GO_DestroyLayer
*/
HI_S32 HI_GO_CreateLayer (const HIGO_LAYER_INFO_S *pLayerInfo, HI_HANDLE* pLayer);

/** 
\brief 销毁图层
\attention \n
当图层正在被使用时（例如基于此图层的桌面未销毁），则图层无法被销毁
\param[in] Layer 图层句柄

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE


\see \n
::HI_GO_CreateLayer
*/
HI_S32 HI_GO_DestroyLayer(HI_HANDLE Layer);


/** 
\brief 设置图层在屏幕中的位置
\attention \n
立即生效，无需刷新。当设置的图层的起始位置超出屏幕范围时会自动调整至屏幕的边界值
\param[in] Layer  图层句柄
\param[in] u32StartX 图层在屏幕上的显示位置X坐标
\param[in] u32StartY 图层在屏幕上的显示位置Y坐标

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERPOS
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerPos
*/
HI_S32 HI_GO_SetLayerPos(HI_HANDLE Layer, HI_U32 u32StartX, HI_U32 u32StartY);

/** 
\brief 获取图层在屏幕上的位置
\attention \n
无
\param[in] Layer 图层句柄
\param[out] pStartX 图层在屏幕上的显示位置X坐标指针，不可为空
\param[out] pStartY 图层在屏幕上的显示位置Y坐标指针，不可为空

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_SetLayerPos
*/
HI_S32 HI_GO_GetLayerPos(HI_HANDLE Layer, HI_U32 *pStartX, HI_U32 *pStartY);


/** 
\brief 设置在输出显示设备上的输出的高度和宽度
\attention \n
在内存支持的前提下，该接口可以支持缩放\n

\param[in]  Layer 图层句柄
\param[in] u32SWidth  实际输出宽度
\param[in] u32SHeight 实际输出高度
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVSIZE
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetScreenSize
*/
HI_S32 HI_GO_SetScreenSize(HI_HANDLE Layer, HI_U32 u32SWidth, HI_U32 u32SHeight);


/** 
\brief 获取在输出显示设备上的输出的高度和宽度。
\attention \n
\param[in]  Layer 图层句柄
\param[out] pSWidth  实际输出宽度指针
\param[out] pSHeight 实际输出高度指针
\retval none
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_SetScreenSize
*/
HI_S32 HI_GO_GetScreenSize(HI_HANDLE Layer, HI_U32 *pSWidth, HI_U32 *pSHeight);

/** 
\brief 设置图层surface的全局alpha值
\attention \n
立即生效，无需刷新
\param[in] Layer 图层句柄
\param[in] Alpha 全局alpha值，不可为空，范围0-255

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_SETALPHAFAILED
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerAlpha
*/

HI_S32 HI_GO_SetLayerAlpha(HI_HANDLE Layer, HI_U8 Alpha);

/** 
\brief 获取图层surface的全局alpha值
\attention \n
无
\param[in] Layer 图层句柄
\param[out] pAlpha 全局alpha指针

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_SetLayerAlpha
*/
HI_S32 HI_GO_GetLayerAlpha(HI_HANDLE Layer, HI_U8* pAlpha);


/** 
\brief 获取图层的surface
\attention \n
图层surface，不能使用HI_GO_FreeSurface来释放。只有在销毁图层的时候才会被释放
进程切换之后必须调用该接口来重新获取图层surface;
\param[in] Layer 图层句柄
\param[out] pSurface surface句柄指针，不可为空

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_DEPEND_FB

\see \n
无
*/
HI_S32 HI_GO_GetLayerSurface(HI_HANDLE Layer, HI_HANDLE *pSurface);

/** 
\brief 显示或隐藏图层
\attention \n
立即生效，无需刷新
\param[in] Layer 图层句柄
\param[in] bVisbile 显示隐藏标志。HI_TRUE：显示；HI_FALSE：隐藏

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerStatus
*/
HI_S32 HI_GO_ShowLayer(HI_HANDLE Layer, HI_BOOL bVisbile);

/** 
\brief 获取图层当前状态
\attention \n
无
\param[in] Layer 图层句柄
\param[out] pLayerStatus 图层当前状态结构指针，不可为空

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_ShowLayer
*/
HI_S32 HI_GO_GetLayerStatus(HI_HANDLE Layer, HIGO_LAYER_STATUS_S* pLayerStatus);

/** 
\brief 刷新图层
\attention \n
1.绘制完成后，需刷新图层才能显示绘制后结果
2.刷新有两种模式，一种是没有任何窗口的时候就显示layersurface的内容，否则显示窗口中的内容。
\param[in] Layer 图层句柄
\param[in]  pRect 刷新的矩形区域，如果是NULL, 则刷新整个全屏
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_DEPEND_FB
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_EMPTYRECT

\see \n
无
*/
HI_S32 HI_GO_RefreshLayer(HI_HANDLE Layer, const HI_RECT* pRect);


/**
\brief 设置层的canvas surface.
\attention \n
     高清和标清同源时，我们可以让标清的canvas buffer与高清的共享同一个
     Surrface的内存类型必须是MMZ类型的.
\param[in] Layer     图层句柄
\param[in] hSurface  图层的surface，如果该参数为INVALID_HANDLE表示没有用户句柄

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVPARAM

\see \n
无
*/
HI_S32 HI_GO_SetLayerSurface(HI_HANDLE Layer, HI_HANDLE hSurface);



/**
\brief 设置图层的背景颜色
\attention \n
图层背景色，只有在叠加窗口才有效
\param[in] Layer 图层句柄
\param[in] Color 图层背景颜色

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_SetLayerBGColor(HI_HANDLE Layer, HI_COLOR Color);

/**
\brief 获取图层的背景颜色
\attention \n
此接口只有在图层上有窗口的时候才会有效。否则该颜色设置无效。
\param[in] Layer 图层句柄
\param[in] pColor 存储图层背景颜色

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_GetLayerBGColor(HI_HANDLE Layer, HI_COLOR* pColor);

/**
\brief 设置显示buffer size
\attention \n
无

\param[in] Layer      图层句柄
\param[in] u32DWidth     宽度指针
\param[in] u32DHeight    高度指针
\param[out] 无 

\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVSIZE 
\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE

\see \n
    ::HI_GO_GetDisplaySize 
*/
HI_S32 HI_GO_SetDisplaySize(HI_HANDLE Layer, HI_U32 u32DWidth, HI_U32 u32DHeight);

/**
\brief 获取显示buffer的size
\attention \n
无

\param[in] Layer      图层句柄
\param[in] pDWidth    宽度指针，不可为空 
\param[in] pDHeight   高度指针，不可为空
\param[out] 无 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
    ::HI_GO_SetDisplaySize 
*/
HI_S32 HI_GO_GetDisplaySize(HI_HANDLE Layer, HI_U32 *pDWidth, HI_U32 *pDHeight);

/**
\brief 设置刷新类型
\attention \n
无

\param[in] Layer         图层句柄           
\param[in] FlushType     图层刷新类型
\param[out] 无

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVFLUSHTYPE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetFlushType 
*/
HI_S32 HI_GO_SetFlushType(HI_HANDLE Layer, HIGO_LAYER_FLUSHTYPE_E FlushType);

/**
\brief 获取刷新类型
\attention \n
无

\param[in] Layer       图层句柄              
\param[in] *pFlushType 图层刷新类型，不可为空 
\param[out] 无 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetFlushType
*/
HI_S32 HI_GO_GetFlushType(HI_HANDLE Layer, HIGO_LAYER_FLUSHTYPE_E *pFlushType);

/**
\brief 设置图层的透明色
\attention \n
无

\param[in] Layer       图层句柄              
\param[in] pKey        透明色信息指针，不可为空
\param[out] 无 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetLayerColorkey
*/
HI_S32 HI_GO_SetLayerColorkey(HI_HANDLE Layer, const HIGO_LAYER_KEY_S *pKey);

/**
\brief 获取透明色信息
\attention \n
无

\param[in] Layer       图层句柄              
\param[in] pKey        透明色信息指针
\param[out] 无 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE 
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerColorkey
*/
HI_S32 HI_GO_GetLayerColorkey(HI_HANDLE Layer, HIGO_LAYER_KEY_S *pKey);

/**
\brief 设置图层的调色板
\attention \n
无

\param[in] Layer       图层句柄              
\param[in] Palette     图层调色板
\param[out] 无 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetLayerPalette
*/
HI_S32 HI_GO_SetLayerPalette(HI_HANDLE Layer, const HI_PALETTE Palette);

/**
\brief 获取图层调色板
\attention \n
无

\param[in] Layer       图层句柄              
\param[in] Palette     图层调色板
\param[out] 无 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE 
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerPalette
*/
HI_S32 HI_GO_GetLayerPalette(HI_HANDLE Layer, HI_PALETTE Palette);

/**
\brief 等待消隐区
\attention \n
无

\param[in] Layer       图层句柄              
\param[out] 无 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE 
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerPalette
*/
HI_S32 HI_GO_WaitForBlank(HI_HANDLE Layer);


/**
\brief 设置图层alpha信息，扩展接口
\attention \n
该接口HIGO_LAYER_ALPHA_S结构体的alpha0,alpha1只在ARGB1555格式下才有效，
用于在ARGB1555格式下实现半透明效果

\param[in] Layer       图层句柄              
\param[in] pAlphaInfo   图层alpha信息，不可为空   
\param[out] 无 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE 
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerAlphaEx
*/
HI_S32 HI_GO_SetLayerAlphaEx(HI_HANDLE Layer,  HIGO_LAYER_ALPHA_S *pAlphaInfo);


/**
\brief 获取图层alpha信息，扩展接口
\attention \n
无

\param[in] Layer       图层句柄              
\param[out] pAlphaInfo  图层alpha信息，不可为空   

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE 
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerAlphaEx
*/
HI_S32 HI_GO_GetLayerAlphaEx(HI_HANDLE Layer,  HIGO_LAYER_ALPHA_S *pAlphaInfo);

/** @} */  /*! <!-- API declaration end */


#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_GDEV_H__ */
