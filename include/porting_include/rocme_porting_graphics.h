/*******************************************************************************
File name   : rocme_porting_graphics.h

Author		: DSM

Description : The poriting interface & macro definition for GUI , VIDEO and OSD module.
	          
Copyright (C) BeiJing SUMAVision, Inc., 2010 .All rights reserved.

History		:
				2010.11.30  		Created 					
*******************************************************************************/
#ifndef _ROCME_PORTING_GRAPHICS_H_
#define _ROCME_PORTING_GRAPHICS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/
//层的类型定义
typedef enum Roc_Plane_Type
{
    ROC_PLANE_BACKGROUND        = 0x00,         //背景层
    ROC_PLANE_STILLPICTURE      = 0x01,         //静态图像层
    ROC_PLANE_VIDEO             = 0x02,         //视频层
    ROC_PLANE_GRAPHICS          = 0x03,         //OSD层
    ROC_PLANE_CURSOR            = 0x04,         //光标层
    ROC_PLANE_RESERVE
}Roc_Plane_Type_e;

//层的输出扫描类型定义
typedef enum Roc_Plane_Scan_Type
{
    ROC_PLANE_SCANTYPE_PROGRESSIVE = 1,         //逐行扫描
    ROC_PLANE_SCANTYPE_INTERLACED  = 2,         //隔行扫描
    ROC_PLANE_SCANTYPE_RESERVE
}Roc_Plane_Scan_Type_e;

//可显示的图片类型定义
typedef enum Roc_Plane_Pic_Type
{
    ROC_PLANE_PIC_I_MPEG2_F         = 0x00,     //I帧
    ROC_PLANE_PIC_BMP               = 0x01,     //bitmap位图
    ROC_PLANE_PIC_JPEG              = 0x02,     //jpeg图片
    ROC_PLANE_PIC_PNG               = 0x03,     //png图片
    ROC_PLANE_PIC_GIF               = 0x04,     //gif图片
    ROC_PLANE_PIC_RESERVE
}Roc_Plane_Pic_Type_e;

//层的输出画面比例定义
typedef enum Roc_Plane_Aspect_Ratio
{
    ROC_PLANE_AR_4TO3               = 0x00,     //4比3比例
    ROC_PLANE_AR_16TO9              = 0x01,     //16比9比例
    ROC_PLANE_AR_16TO10             = 0x02,     //16比10比例
    ROC_PLANE_AR_1TO1               = 0x03,     //1比1比例
    ROC_PLANE_AR_SESERVE0,
    ROC_PLANE_AR_SESERVE1,
    ROC_PLANE_AR_SESERVE2,
    ROC_PLANE_AR_SESERVE3
}Roc_Plane_Aspect_Ratio_e;

//层的输出分辨率定义
typedef enum Roc_Plane_Resolution
{
    ROC_PLANE_RS_480_320            = 0x00,     //480*320的分辨率
    ROC_PLANE_RS_720_576            = 0x01,     //720*576的分辨率
    ROC_PLANE_RS_1280_720           = 0x02,     //1280*720的分辨率
    ROC_PLANE_RS_1920_1080          = 0x03,     //1920*1080的分辨率
    ROC_PLANE_RS_SESERVE0,
    ROC_PLANE_RS_SESERVE1,
    ROC_PLANE_RS_SESERVE2,
    ROC_PLANE_RS_SESERVE3   
}Roc_Plane_Resolution_e;

/*7101平台使用BLIT，新增加的数据结构*/
typedef enum Roc_Blit_Mode
{
    ROC_BLIT_CLEAR              = 0,
    ROC_BLIT_AND                = 1,
    ROC_BLIT_AND_REV            = 2,
    ROC_BLIT_COPY               = 3,
    ROC_BLIT_AND_INVERT         = 4,
    ROC_BLIT_NOOP               = 5,
    ROC_BLIT_XOR                = 6,
    ROC_BLIT_OR                 = 7,
    ROC_BLIT_NOR                = 8,
    ROC_BLIT_EQUIV              = 9,
    ROC_BLIT_NVERT              = 10,
    ROC_BLIT_OR_REVERSE         = 11,
    ROC_BLIT_COPY_INVERT        = 12,
    ROC_BLIT_OR_INVERT          = 13,
    ROC_BLIT_NAND               = 14,
    ROC_BLIT_SET                = 15,
    ROC_BLIT_ALPHA_BLEND        = 16,
    ROC_BLIT_ALPHA_BLEND_B      = 17
	/*...*/
}Roc_Blit_Mode_e;

typedef struct Roc_Blit_Context
{
	Roc_Blit_Mode_e 	emBlitMode;
	ROC_BOOL 	        bColorKeyEnable;
	INT32_T             nColorKeyValue;
	UINT8_T             ucGlobalAlpha;
}Roc_Blit_Context_t;

//层的缓冲区参数定义
typedef struct Roc_Plane_Buff
{
    INT32_T     width;
    INT32_T     height;
    INT32_T     pitch;
    void        *buff_ptr;      //如果无法提供，可以为空
    INT32_T     buff_len;
}Roc_Plane_Buff_t;

//层的区域定位定义
typedef struct Roc_Plane_Area
{
    INT32_T     offset_x;
    INT32_T     offset_y;
    INT32_T     width;
    INT32_T     height;
}Roc_Plane_Area_t;

//颜色类型定义
typedef enum Roc_Plane_Color_Type
{
    ROC_PLANE_COLOR_TYPE_ARGB8888                 = 0x00,
    ROC_PLANE_COLOR_TYPE_RGB888                   = 0x01,
    ROC_PLANE_COLOR_TYPE_ARGB8565                 = 0x02,
    ROC_PLANE_COLOR_TYPE_RGB565                   = 0x03,
    ROC_PLANE_COLOR_TYPE_ARGB1555                 = 0x04,
    ROC_PLANE_COLOR_TYPE_ARGB4444                 = 0x05,
    ROC_PLANE_COLOR_TYPE_CLUT8                    = 0x06,
    ROC_PLANE_COLOR_TYPE_CLUT4                    = 0x07,
    ROC_PLANE_COLOR_TYPE_CLUT2                    = 0x08,
    ROC_PLANE_COLOR_TYPE_CLUT1                    = 0x09,
    ROC_PLANE_COLOR_TYPE_ACLUT88                  = 0x0A,
    ROC_PLANE_COLOR_TYPE_ACLUT44                  = 0x0B,
    ROC_PLANE_COLOR_TYPE_SIGNED_YCBCR888_444      = 0x0C,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_YCBCR888_444    = 0x0D,
    ROC_PLANE_COLOR_TYPE_SIGNED_YCBCR888_422      = 0x0E,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_YCBCR888_422    = 0x0F,
    ROC_PLANE_COLOR_TYPE_SIGNED_YCBCR888_420      = 0x10,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_YCBCR888_420    = 0x11,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_AYCBCR6888_444  = 0x12,
    ROC_PLANE_COLOR_TYPE_SIGNED_AYCBCR8888        = 0x13,
    ROC_PLANE_COLOR_TYPE_UNSIGNED_AYCBCR8888      = 0x14,
    ROC_PLANE_COLOR_TYPE_ALPHA1                   = 0x15,
    ROC_PLANE_COLOR_TYPE_ALPHA4                   = 0x16,
    ROC_PLANE_COLOR_TYPE_ALPHA8                   = 0x17,
    ROC_PLANE_COLOR_TYPE_BYTE                     = 0x18,
    ROC_PLANE_COLOR_TYPE_ARGB7888                 = 0x1D,

	ROC_PLANE_COLOR_TYPE_PARGB8888,
	ROC_PLANE_COLOR_TYPE_RGBA8888,

    ROC_PLANE_COLOR_RESERVE                       = 0xFF
}Roc_Plane_Color_Type_e;

//层的基本配置定义
typedef struct Roc_Plane_Cfg
{
    INT32_T                     plane_id;           //此层的id标识,不可以小于0
    Roc_Plane_Type_e            plane_type;         //此层的类型
    ROC_BOOL                    is_complex_pic;     //是否支持复杂图像的显示, ROC_TRUE:支持 \ ROC_FALSE:不支持(仅支持显示单色)
    ROC_BOOL                    is_still_image;     //是否支持显示静态图像, ROC_TRUE:支持 \ ROC_FALSE:不支持
    ROC_BOOL                    is_flicker_filter;  //是否支持防闪烁(减少重叠部分的闪烁,详见电视中间件规范－接收设备 第3部分 附录A.2.2.2.3)
    Roc_Plane_Area_t            area;               //此层的起始坐标及长宽
    Roc_Plane_Buff_t            buff_parm;          //此层的buff的参数,
    Roc_Plane_Color_Type_e      color;              //此层当前的颜色类型
    INT32_T                     color_depth;        //此层的当前颜色深度
    Roc_Plane_Scan_Type_e       scan_type;          //此层输出的扫描类型
    Roc_Plane_Aspect_Ratio_e    aspectratio;        //此层当前输出的画面比例(4:3,16:9等等)
    Roc_Plane_Resolution_e      resolution;         //此层当前输出的分辨率(720*576,480*320等等)
    ROC_BOOL                    realtime;           //对此层所做的操作是否是立即生效的(若为ROC_FALSE，则改变此层后需要调用rocme_porting_plane_update()函数使之生效),若需要双缓冲可以设置为ROC_FALSE
    INT32_T                     reserve;
}Roc_Plane_Cfg_t;
#if 0
#define MAX_LAYER_COUNT 16 //每种设备的最大层数
#define MAX_FRONTPANEL_CHARACTER_SUPPORT 40

typedef enum Roc_Cursor_Bitmap_Type
{
    ROC_CURSOR_BMP,
    ROC_CURSOR_GIF,
    ROC_CURSOR_JPEG,
    ROC_CURSOR_PNG
}Roc_Cursor_Bitmap_Type_e;

typedef struct Roc_Cursor_Configuration
{
    Roc_Cursor_Bitmap_Type_e bmpType;    //光标层支持的图片格式
    ROC_BOOL isInterlacedSupported;      //是否支持隔行扫描
    ROC_BOOL isAntiflickerSupported;     //是否支持抗闪烁
    INT32_T x;                           //此配置所处荧幕区域的x坐标
    INT32_T y;                           //此配置所处荧幕区域的y坐标
    INT32_T width;                       //光标层宽
    INT32_T height;                      //光标层高
    Roc_Plane_Color_Type_e colorType;      //光标层颜色格式
    Roc_Plane_Aspect_Ratio_e aspectRation; //宽高比
}Roc_Cursor_Configuration;
/**
前面板的配置信息
*/
typedef struct Roc_FrontPanel_Configuration{

	INT16_T displayCharAmount;/*显示的数量*/
	INT16_T characterSetCount;/*支持显示的字符数*/
	CHAR_T supportChar[MAX_FRONTPANEL_CHARACTER_SUPPORT];/*支持的字符*/
	

} Roc_FrontPanel_Configuration_fp;

typedef struct Roc_Graphics_Configuration
{
    
    ROC_BOOL isInterlacedSupported;      //是否支持隔行扫描
    ROC_BOOL isAntiflickerSupported;     //是否支持抗闪烁
    void* pBuffer;                       //图像层显示缓存（实时生效）；如果无法提供，可以为空。
    INT32_T x;                           //此配置所处荧幕区域的x坐标
    INT32_T y;                           //此配置所处荧幕区域的y坐标
    INT32_T width;                       //图像层宽
    INT32_T height;                      //图像层高
    INT32_T pitch;                       //图像层每行占据的字节数
    Roc_Plane_Color_Type_e colorType;      //图像层颜色格式
    Roc_Plane_Aspect_Ratio_e aspectRation; //宽高比
}Roc_Graphics_Configuration;

typedef struct Roc_Video_Configuration
{

    ROC_BOOL isInterlacedSupported;      //是否支持隔行扫描
    ROC_BOOL isAntiflickerSupported;     //是否支持抗闪烁
    INT32_T x;                           //此配置所处荧幕区域的x坐标
    INT32_T y;                           //此配置所处荧幕区域的y坐标
    INT32_T width;                       //视频层宽
    INT32_T height;                      //视频层高
    Roc_Plane_Color_Type_e colorType;      //视频层颜色格式
    Roc_Plane_Aspect_Ratio_e aspectRation; //宽高比
}Roc_Video_Configuration;

typedef struct Roc_StillPicture_Configuration
{
    ROC_BOOL isStillComplPlot;           //静止图像层是否支持复杂绘图的绘图功能
    ROC_BOOL isInterlacedSupported;      //是否支持隔行扫描
    ROC_BOOL isAntiflickerSupported;     //是否支持抗闪烁
    INT32_T x;                           //此配置所处荧幕区域的x坐标
    INT32_T y;                           //此配置所处荧幕区域的y坐标
    INT32_T width;                       //静止图像层宽
    INT32_T height;                      //静止图像层高
    Roc_Plane_Color_Type_e colorType;      //静止图像层颜色格式
    Roc_Plane_Aspect_Ratio_e aspectRation; //宽高比
}Roc_StillPicture_Configuration;

typedef struct Roc_Background_Configuration
{
    ROC_BOOL isBgComplPlot;                //背景层是否支持复杂绘图的绘图功能
    ROC_BOOL isBgColorAreaFilledSupported ;//背景层是否支持区域填充
    ROC_BOOL isColorChangeable;            //是否支持改变填充颜色
    ROC_BOOL isInterlacedSupported;        //是否支持隔行扫描
    ROC_BOOL isAntiflickerSupported;       //是否支持抗闪烁
    INT32_T x;                             //此配置所处荧幕区域的x坐标
    INT32_T y;                             //此配置所处荧幕区域的y坐标
    INT32_T width;                         //背景层宽
    INT32_T height;                        //背景层高
    Roc_Plane_Color_Type_e colorType;        //背景层颜色格式
    Roc_Plane_Aspect_Ratio_e aspectRation;   //宽高比
}Roc_Background_Configuration;

typedef struct Roc_Layer_Context
{
    INT32_T frontpanelLayerCount;     //前面板设备的数量
    INT32_T cursorLayerCount;         //光标层的层数量
    Roc_Cursor_Configuration       cursorConf[MAX_LAYER_COUNT];          //光标层配置，索引低的层在后（可以被遮挡）
    INT32_T graphicsLayerCount;       //图像层的层数量
    Roc_Graphics_Configuration     graphicsConf[MAX_LAYER_COUNT];        //图像层配置，索引低的层在后（可以被遮挡）；图形库将使用索引为0的层
    INT32_T videoLayerCount;          //视频层的层数量
    Roc_Video_Configuration        videoConf[MAX_LAYER_COUNT];           //视频层配置，索引低的层在后（可以被遮挡）
    INT32_T stillPictureLayerCount;   //静止图像层的层数量
    Roc_StillPicture_Configuration stillPictureConf[MAX_LAYER_COUNT];    //静止图像层配置，索引低的层在后（可以被遮挡）
    INT32_T backgroundLayerCount;     //背景层的层数量
    Roc_Background_Configuration   backgroundConf[MAX_LAYER_COUNT];      //背景层配置，索引低的层在后（可以被遮挡）
}Roc_Layer_Context_t;
#endif
/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/

/**************************************************************************
函数名称: 
            rocme_porting_plane_init
功能说明: 
            初始化各个显示层信息
参数说明：
    输入参数：
            无
    输出参数：
            无
返    回： 
    成功 : 0            ( 初始化成功 )
    失败 : -1 	 ( 失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_init( void );

/**************************************************************************
函数名称: 
            rocme_porting_plane_get_info
功能说明: 
            获取指定显示层底层是否支持的信息
参数说明：
    输入参数：
            [plane_type  ] : 指定的层
    输出参数：
            [ *number    ] : 底层是否支持此层, <=0 不支持，>0为支持的层数
返    回： 
    成功 : 0            ( 获取硬件平台信息成功 )
    失败 : -1 或 错误码 ( 获取硬件平台信息失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_get_info( Roc_Plane_Type_e plane_type , INT32_T *number );

/**************************************************************************
函数名称: 
            rocme_porting_plane_get_cfg
功能说明: 
            获取指定显示层的当前配置信息,number从1开始
参数说明：
    输入参数：
            [plane_type  ] : 指定的层
            [number      ] : 指定具体的某一层的索引，例如指定第二个osd层，此值为2
    输出参数：
            [*plane_cfg  ] : 指定层的具体配置信息
返    回： 
    成功 : 0            ( 获取硬件平台信息成功 )
    失败 : -1 或 错误码 ( 获取硬件平台信息失败 )
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_get_cfg( Roc_Plane_Type_e plane_type , INT32_T number , Roc_Plane_Cfg_t *plane_cfg );

/**************************************************************************
函数名称: 
            rocme_porting_plane_set_cfg
功能说明: 
            设置指定显示层的当前配置信息
参数说明：
    输入参数：
            [*plane_cfg  ] : 指定层的具体配置信息,其中的plane_cfg->plane_id和plane_cfg->plane_type
                             两个参数不可以改动。
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_set_cfg( Roc_Plane_Cfg_t *plane_cfg );

/**************************************************************************
函数名称: 
            rocme_porting_plane_display
功能说明: 
            开启或关闭指定层是否显示
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
            [is_on      ] : 是否开启显示,ROC_TRUE~开启； ROC_FALSE~关闭，可以透视到下一层
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_display( const INT32_T plane_id , const ROC_BOOL is_on );

/**************************************************************************
函数名称: 
            rocme_porting_plane_remove
功能说明: 
            移除某层上正在显示的图像，并显示为黑场
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_remove( const INT32_T plane_id );

/**************************************************************************
函数名称: 
            rocme_porting_plane_update
功能说明: 
            当函数rocme_porting_plane_get_cfg返回的参数plane_cfg->realtime=ROC_FALSE，
        说明此层不支持实时更新，需要在调用函数rocme_porting_plane_fill_color或函数ro-
        -cme_porting_plane_fill_picture后需要调用此函数进行显示的更新。或者当需要使用
        双缓冲机制时，应用可以改变参数plane_cfg->realtime=ROC_FALSE，表明需要实现双缓
        冲，当调用fill_color和fill_picture后会调用此函数显示。
参数说明：
    输入参数：
            [plane_id   ] : 指定的层的id标识
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_update( const INT32_T plane_id, const Roc_Plane_Area_t* area );
INT32_T rocme_porting_plane_update_ex( const INT32_T plane_id, const Roc_Plane_Area_t* srcArea, const Roc_Plane_Area_t* dstArea );

/**************************************************************************
函数名称: 
            rocme_porting_plane_fill_color
功能说明: 
            填充某层为一单色
参数说明：
    输入参数：
        [buffer		 ] :要绘图的buffer结构指针
        [color       ] :颜色值,0xaarrggbb格式
        [area        ] :需要填充的坐标及大小，若不支持区域填充则将整层填充
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_fill_color( 
				   const Roc_Plane_Buff_t*	buffer, 
				   const UINT32_T			color, 
				   const Roc_Plane_Area_t*	area 
				   );

/**************************************************************************
函数名称: 
            rocme_porting_plane_fill_rectangle
功能说明: 
            向某层拷贝矩形bitmap数据
参数说明：
    输入参数：
        [plane_id    ] :指定的层的id标识
        [buff_parm   ] :需要显示填充的数据的参数，包括宽、高、pitch值和数据头指针
        [area        ] :需要填充的坐标及大小，若不支持区域填充则将整层填充
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：

其他说明:

**************************************************************************/
INT32_T rocme_porting_plane_fill_rectangle( const INT32_T plane_id , const Roc_Plane_Buff_t *buff_parm , const Roc_Plane_Area_t *area  );

/**************************************************************************
函数名称: 
            rocme_porting_plane_set_alpha
功能说明: 
            设置某层的Alpha(透明度)的相对值，0 ~ 100, 0 - 最小，完全不可见；100 - 最大，OSD完全可见；
        其他值该函数不操作，直接返回-1
参数说明：
    输入参数：
        [plane_id    ] :指定的层的id标识
        [alpha       ] :指定的层的alpha值
    输出参数：

返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：
     
其他说明:
     
**************************************************************************/
INT32_T rocme_porting_plane_set_alpha( const INT32_T plane_id , const INT32_T alpha );

/***************************************************************************
函数名称:
        rocme_porting_alpha_blend_blit
功能说明：
        实现硬件BLIT加速alpha混合。
参数说明：
    输入参数：
            [SrcBuf               ] : 源位图的数据存储buff的参数
            [SrcBmp               ] : 源位图的需要拷贝的区域
            [SrcBmpType           ] : 源位图类型 (类似ARGB8888这样的)
            [DstBuf               ] : 目的位图的buff参数
            [DstBmp               ] : 目的位图的需要做alpha_blend的区域
            [DstBmpType           ] : 目的位图类型(Roc_Plane_Color_Type_e)
            [BlitContext          ] : 配置BLIT参数的结构体
    输出参数：
            无
返    回： 
    成功 : 0            ( 填充成功 )
    失败 : -1 或 错误码 ( 填充失败 )
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口
***************************************************************************/
INT32_T rocme_porting_plane_alpha_blend_blit(
                    const Roc_Plane_Buff_t          *SrcBuf,                 // 源位图的数据存储buff的参数
                    const Roc_Plane_Area_t          *SrcBmp,                 // 源位图的需要拷贝的区域
			        const Roc_Plane_Color_Type_e    SrcBmpType,             // 源位图类型 (类似ARGB8888这样的)
                    const Roc_Plane_Buff_t          *DstBuf,                 // 目的位图的buff参数
                    const Roc_Plane_Area_t          *DstBmp,                 // 目的位图的需要做alpha_blend的区域
                    const Roc_Plane_Color_Type_e	DstBmpType,             // 目的位图类型(Roc_Plane_Color_Type_e)
				    Roc_Blit_Context_t              *BlitContext			// 配置BLIT参数的结构体
					);

/***************************************************************************
函数名称:
        rocme_porting_avmem_allocate
功能说明：
        在AVMEM中申请显存空间
参数说明：
    输入参数：
            [         Size] : 需要申请显存空间的大小
            [    Alignment] : 申请显存空间的对齐字节数          
    输出参数：
            无
返    回： 
    成功 : 申请到的显存空间指针  ( 申请成功 )
    失败 : NULL ( 申请失败 )
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口    
***************************************************************************/ 
void * rocme_porting_avmem_allocate( UINT32_T Size, UINT32_T Alignment );

/***************************************************************************
函数名称:
        rocme_porting_avmem_deallocate
功能说明：
        释放在AVMEM中申请的显存空间
参数说明：
    输入参数：
            [       pBuffer] : 需要释放的显存空间的指针
    输出参数：
            无
返    回： 
            无
参考实现：
    rocme_graphics.c
其他说明:
    7101新增加的接口
***************************************************************************/ 
void  rocme_porting_avmem_deallocate( void* pBuffer );




#ifdef __cplusplus
}
#endif

#endif

