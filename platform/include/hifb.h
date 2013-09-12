/** 
 * \file
 * \brief 提供HIBF的相关信息
 */
 
#ifndef __HIFB_H__
#define __HIFB_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include <linux/fb.h>
/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_2 */
/** @{ */  /** <!-- 【HIBF】 */
#define IOC_TYPE_HIFB       'F'
/** 获取图层colorkey信息 */
#define FBIOGET_COLORKEY_HIFB       _IOR(IOC_TYPE_HIFB, 90, HIFB_COLORKEY_S)
/** 设置图层colorkey信息 */
#define FBIOPUT_COLORKEY_HIFB       _IOW(IOC_TYPE_HIFB, 91, HIFB_COLORKEY_S)
/** 获取图层alpha信息,包括像素和全局alpha */
#define FBIOGET_ALPHA_HIFB          _IOR(IOC_TYPE_HIFB, 92, HIFB_ALPHA_S)
/** 设置图层alpha信息,包括像素和全局alpha */
#define FBIOPUT_ALPHA_HIFB          _IOW(IOC_TYPE_HIFB, 93, HIFB_ALPHA_S)
/** 获取图层屏幕原点信息 */
#define FBIOGET_SCREEN_ORIGIN_HIFB  _IOR(IOC_TYPE_HIFB, 94, HIFB_POINT_S)
/** 设置图层屏幕原点信息 */
#define FBIOPUT_SCREEN_ORIGIN_HIFB  _IOW(IOC_TYPE_HIFB, 95, HIFB_POINT_S)
/** 获取图层抗闪烁*/
#define FBIOGET_DEFLICKER_HIFB       _IOR(IOC_TYPE_HIFB, 98, HIFB_DEFLICKER_S)
/** 设置图层抗闪烁 */
#define FBIOPUT_DEFLICKER_HIFB       _IOW(IOC_TYPE_HIFB, 99, HIFB_DEFLICKER_S)
/** 等待图层垂直水隐中断 */
#define FBIOGET_VBLANK_HIFB         _IO(IOC_TYPE_HIFB, 100)
/** 设置图层显示 */
#define FBIOPUT_SHOW_HIFB           _IOW(IOC_TYPE_HIFB, 101, HI_BOOL)
/** 获取图层显示显示信息 */
#define FBIOGET_SHOW_HIFB           _IOR(IOC_TYPE_HIFB, 102, HI_BOOL)
/** 获取图层能力 */
#define FBIOGET_CAPABILITY_HIFB    _IOR(IOC_TYPE_HIFB, 103, HIFB_CAPABILITY_S)
/**设置屏幕输出范围*/
#define FBIOPUT_SCREENSIZE          _IOW(IOC_TYPE_HIFB, 130, HIFB_SIZE_S*)
/**获取屏幕输出范围*/
#define FBIOGET_SCREENSIZE          _IOR(IOC_TYPE_HIFB, 131, HIFB_SIZE_S*)

/*范围类型定义*/
typedef struct
{
    HI_U32  u32Width;         /**< 屏幕上输出的宽度 */
    HI_U32  u32Height;        /**< 屏幕上输出的高度 */
}HIFB_SIZE_S;

/** layer ID */
typedef enum 
{
    HIFB_LAYER_SD_0 = 0x0,
    HIFB_LAYER_SD_1,
    HIFB_LAYER_HD_0,
    HIFB_LAYER_HD_1,    
    HIFB_LAYER_AD_0,
    HIFB_LAYER_CURSOR,
    HIFB_LAYER_ID_BUTT
} HIFB_LAYER_ID_E;

/**根据颜色分量，获取其扩展到32位后值。扩展规则:低位补其高位*/
static inline HI_U8  hifb_rgb(const struct fb_bitfield* pBit, HI_S32 color)
{
    return ((HI_U8)((((HI_U32)color)>>pBit->offset) << (8-pBit->length)) +
             ((HI_U8)(((HI_U32)(color)>>pBit->offset) << (8-pBit->length)) >> pBit->length));
}

/**根据像素格式信息，将一个颜色值，转换成一个32位的颜色key值,将低色深如16bit扩展为高色深如32bit的策略是:
   低位补高几位，芯片有多种方式。芯片的方式必须如这个方式一致，否则图层colorkey无效*/
static inline HI_S32 hifb_color2key(const struct fb_var_screeninfo* pVar, HI_S32 color)
{
   if (pVar->bits_per_pixel <= 8)
   {
       return color; 
   }
   else
   {
      HI_U8 r, g, b;
      r = hifb_rgb(&pVar->red, color);
      g = hifb_rgb(&pVar->green, color);      
      b = hifb_rgb(&pVar->blue, color);
      return (r<<16) + (g<<8) + b;
   }
}

typedef struct
{
    HI_BOOL bKeyEnable;         /**<  colorkey 是否使能 */
    HI_U32 u32Key;              /**<  该值应该通过::hifb_color2key得到*/
}HIFB_COLORKEY_S;

/** 矩形信息 */
typedef struct
{
    HI_S32 x, y;    /**< x:矩形左上点横坐标 y:矩形左上点纵坐标*/
    HI_S32 w, h;    /**< w:矩形宽度 h:矩形高度*/
} HIFB_RECT;

/** 点坐标信息 */
typedef struct
{
    HI_S32 s32XPos;         /**<  horizontal position */
    HI_S32 s32YPos;         /**<  vertical position */
}HIFB_POINT_S;

/** 抗闪烁信息 */
typedef struct hiHIFB_DEFLICKER_S
{
    HI_U32  u32HDfLevel;    /**<  horizontal deflicker level */     
    HI_U32  u32VDfLevel;    /**<  vertical deflicker level */
    HI_U8   *pu8HDfCoef;    /**<  horizontal deflicker coefficient */
    HI_U8   *pu8VDfCoef;    /**<  vertical deflicker coefficient */
}HIFB_DEFLICKER_S;

/** Alpha信息 */
typedef struct
{
    HI_BOOL bAlphaEnable;   /**<  alpha enable flag */
    HI_BOOL bAlphaChannel;  /**<  alpha channel enable flag */
    HI_U8 u8Alpha0;         /**<  alpha0 value, used in ARGB1555 */
    HI_U8 u8Alpha1;         /**<  alpha1 value, used in ARGB1555 */
    HI_U8 u8GlobalAlpha;    /**<  global alpha value */
    HI_U8 u8Reserved;
}HIFB_ALPHA_S;

/** 像素格式枚举 */
typedef enum
{        
	HIFB_FMT_RGB565 = 0,        
	HIFB_FMT_RGB888,		      /**<  RGB888 24bpp */
	
    HIFB_FMT_KRGB444,       /**<  RGB444 16bpp */
    HIFB_FMT_KRGB555,       /**<  RGB555 16bpp */
    HIFB_FMT_KRGB888,       /**<  RGB888 32bpp */
    
    HIFB_FMT_ARGB4444,      /**< ARGB4444 */     
    HIFB_FMT_ARGB1555,      /**< ARGB1555 */  
    HIFB_FMT_ARGB8888,      /**< ARGB8888 */   
	HIFB_FMT_ARGB8565,      /**< ARGB8565 */
	
	HIFB_FMT_RGBA4444,      /**< ARGB4444 */
    HIFB_FMT_RGBA5551,      /**< RGBA5551 */
    HIFB_FMT_RGBA5658,      /**< RGBA5658 */
    HIFB_FMT_RGBA8888,      /**< RGBA8888 */
    
    HIFB_FMT_BGR565,        /**< BGR565 */   
    HIFB_FMT_BGR888,        /**< BGR888 */   
    HIFB_FMT_ABGR4444,      /**< ABGR4444 */   
    HIFB_FMT_ABGR1555,      /**< ABGR1555 */   
    HIFB_FMT_ABGR8888,      /**< ABGR8888 */   
    HIFB_FMT_ABGR8565,      /**< ABGR8565 */      
    HIFB_FMT_KBGR444,       /**< BGR444 16bpp */
    HIFB_FMT_KBGR555,       /**< BGR555 16bpp */
    HIFB_FMT_KBGR888,       /**< BGR888 32bpp */
    
    HIFB_FMT_1BPP,          /**<  clut1 */
    HIFB_FMT_2BPP,          /**<  clut2 */    
    HIFB_FMT_4BPP,          /**<  clut4 */ 
    HIFB_FMT_8BPP,          /**< clut8 */
    HIFB_FMT_ACLUT44,       /**< AClUT44*/
	HIFB_FMT_ACLUT88,         /**< ACLUT88 */
    HIFB_FMT_PUYVY,         /**< UYVY */
    HIFB_FMT_PYUYV,         /**< YUYV */
    HIFB_FMT_PYVYU,         /**< YVYU */
    HIFB_FMT_YUV888,        /**< YUV888 */
    HIFB_FMT_AYUV8888,      /**< AYUV8888 */
    HIFB_FMT_YUVA8888,      /**< YUVA8888 */
    HIFB_FMT_BUTT
}HIFB_COLOR_FMT_E;

/** hifb能力集 */
typedef struct
{
    HI_BOOL bKeyAlpha;      /**<  whether support colorkey alpha */
    HI_BOOL bGlobalAlpha;   /**<  whether support global alpha */
    HI_BOOL bCmap;          /**<  whether support color map */
    HI_BOOL bHasCmapReg;    /**<  whether has color map register*/
    HI_BOOL bColFmt[HIFB_FMT_BUTT]; /**<  support which color format */
    HI_BOOL bVoScale;       /**< support vo scale*/
    HI_BOOL bLayerSupported;    /**< whether support a certain layer, for example:x5 HD support HIFB_SD_0 not support HIFB_SD_1*/
    HI_U32  u32MaxWidth;    /**<  the max pixels per line */
    HI_U32  u32MaxHeight;   /**<  the max lines */
    HI_U32  u32MinWidth;    /**<  the min pixels per line */
    HI_U32  u32MinHeight;   /**<  the min lines */ 
    HI_U32  u32VDefLevel;   /**<  vertical deflicker level, 0 means vertical deflicker is unsupported */
    HI_U32  u32HDefLevel;   /**<  horizontal deflicker level, 0 means horizontal deflicker is unsupported  */
}HIFB_CAPABILITY_S;

/*refresh mode*/
typedef enum 
{
    HIFB_LAYER_BUF_DOUBLE = 0x0,       /**<  2 display buf in fb */
    HIFB_LAYER_BUF_ONE    = 0x1,       /**<  1 display buf in fb */
    HIFB_LAYER_BUF_NONE   = 0x2,       /**<  no display buf in fb,the buf user refreshed will be directly set to VO*/    
    HIFB_LAYER_BUF_DOUBLE_IMMEDIATE=0x3, /**< 2 display buf in fb, each refresh will be displayed*/
    HIFB_LAYER_BUF_BUTT
} HIFB_LAYER_BUF_E;

/* surface info */
typedef struct
{
    HI_U32  u32PhyAddr;     /**<  start physical address */
    HI_U32  u32Width;       /**<  width pixels */
    HI_U32  u32Height;      /**<  height pixels */   
    HI_U32  u32Pitch;       /**<  line pixels */         
    HIFB_COLOR_FMT_E enFmt; /**<  color format */     
}HIFB_SURFACE_S;

/* refresh surface info */
typedef struct
{
    HIFB_SURFACE_S stCanvas;    
    HIFB_RECT UpdateRect;       /* refresh region*/
}HIFB_BUFFER_S;

/* cursor info */
typedef struct
{
    HIFB_SURFACE_S stCursor;
    HIFB_POINT_S stHotPos;
} HIFB_CURSOR_S;

/* crusor handle */
/* Attention:surface in cursor will be released by user*/
#define FBIOPUT_CURSOR_INFO		      _IOW(IOC_TYPE_HIFB, 104, HIFB_CURSOR_S *)
#define FBIOGET_CURSOR_INFO		      _IOW(IOC_TYPE_HIFB, 105, HIFB_CURSOR_S *)

#define FBIOPUT_CURSOR_STATE		  _IOW(IOC_TYPE_HIFB, 106, HI_BOOL *)
#define FBIOGET_CURSOR_STATE		  _IOW(IOC_TYPE_HIFB, 107, HI_BOOL *)

#define FBIOPUT_CURSOR_POS		      _IOW(IOC_TYPE_HIFB, 108, HIFB_POINT_S *)	
#define FBIOGET_CURSOR_POS		      _IOR(IOC_TYPE_HIFB, 109, HIFB_POINT_S *)

#define FBIOPUT_CURSOR_COLORKEY       _IOR(IOC_TYPE_HIFB, 110, HIFB_COLORKEY_S *)
#define FBIOGET_CURSOR_COLORKEY       _IOW(IOC_TYPE_HIFB, 111, HIFB_COLORKEY_S *)
#define FBIOPUT_CURSOR_ALPHA          _IOR(IOC_TYPE_HIFB, 112, HIFB_ALPHA_S *)
#define FBIOGET_CURSOR_ALPHA          _IOW(IOC_TYPE_HIFB, 113, HIFB_ALPHA_S *)

/** cursor will be separated from attached layer automatically if you attach cursor to another layer,that means
cursor can be attached to only one layer at any time*/
#define FBIOPUT_CURSOR_ATTCHCURSOR    _IOW(IOC_TYPE_HIFB, 114, HIFB_LAYER_ID_E *)
#define FBIOPUT_CURSOR_DETACHCURSOR   _IOW(IOC_TYPE_HIFB, 115, HIFB_LAYER_ID_E *)

/**antiflicker level*/
/**Auto means fb will choose a appropriate antiflicker level automatically according to the color info of map*/
typedef enum
{
    HIFB_LAYER_ANTIFLICKER_NONE = 0x0,	/**< no antiflicker*/
    HIFB_LAYER_ANTIFLICKER_LOW = 0x1,	/**< low level*/
    HIFB_LAYER_ANTIFLICKER_MIDDLE = 0x2,/**< middle level*/
	HIFB_LAYER_ANTIFLICKER_HIGH = 0x3, /**< high level*/
	HIFB_LAYER_ANTIFLICKER_AUTO = 0x4, /**< auto*/
    HIFB_LAYER_ANTIFLICKER_BUTT
}HIFB_LAYER_ANTIFLICKER_LEVEL_E;

/*layer info maskbit*/
typedef enum
{
	HIFB_LAYERMASK_BUFMODE = 0x1,           /**< 设置图层信息时，HIFB_LAYER_INFO_S中buf模式是否有效掩码 */
	HIFB_LAYERMASK_ANTIFLICKER_MODE = 0x2,  /**< 抗闪烁模式是否有效掩码 */
	HIFB_LAYERMASK_POS = 0x4,               /**< 图层位置是否有效掩码 */
    HIFB_LAYERMASK_CANVASSIZE = 0x8,      /**< canvassize是否有效掩码 */
    HIFB_LAYERMASK_DISPSIZE = 0x10,       /**< displaysize是否有效掩码 */
    HIFB_LAYERMASK_SCREENSIZE = 0x20,     /**< screensize是否有效掩码 */
    HIFB_LAYERMASK_BMUL = 0x40,           /**< 是否预乘是否有效掩码 */
	HIFB_LAYERMASK_BUTT
}HIFB_LAYER_INFO_MASKBIT;

/**layer info*/
typedef struct
{
	HIFB_LAYER_BUF_E BufMode;
	HIFB_LAYER_ANTIFLICKER_LEVEL_E eAntiflickerLevel;	
    HI_S32 s32XPos;           /**<  the x pos of origion point in screen */
    HI_S32 s32YPos;	          /**<  the y pos of origion point in screen */
    HI_S32 u32CanvasWidth;    /**<  the width of canvas buffer */
    HI_S32 u32CanvasHeight;   /**<  the height of canvas buffer */
	HI_U32 u32DisplayWidth;	  /**<  the width of display buf in fb.for 0 buf ,there is no display buf in fb, so it's effectless*/
	HI_U32 u32DisplayHeight;  /**<  the height of display buf in fb. */
    HI_U32 u32ScreenWidth;    /**<  the width of screen */
    HI_U32 u32ScreenHeight;   /**<  the height of screen */
    HI_BOOL bPreMul;          /**<  The data drawed in buf is premul data or not*/
	HI_U32 u32Mask;			  /**<  param modify mask bit*/
}HIFB_LAYER_INFO_S;

/** 设置图层信息 */
#define FBIOPUT_LAYER_INFO                _IOW(IOC_TYPE_HIFB, 120, HIFB_LAYER_INFO_S*)
/** 获取图层信息 */
#define FBIOGET_LAYER_INFO                _IOR(IOC_TYPE_HIFB, 121, HIFB_LAYER_INFO_S*)
/** 获取canvas buf */
#define FBIOGET_CANVAS_BUFFER             _IOR(IOC_TYPE_HIFB, 123, HIFB_BUFFER_S*) 
/** 刷新图层 */
#define FBIO_REFRESH                      _IOW(IOC_TYPE_HIFB, 124, HIFB_BUFFER_S*) 

/**sync refresh*/
#define FBIO_WAITFOR_FREFRESH_DONE        _IO(IOC_TYPE_HIFB, 125)

/** @} */  /** <!-- ==== Structure Definition end ==== */

#if 0
/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_2 */
/** @{ */  /** <!-- 【HiFB】 */

/**-----标准功能--------*/
/**
\brief 获取屏幕的可变信息.
\attention \n
系统默认的标清图层分辨率为720×576，象素格式为ARGB1555。系统默认的高清图层分辨率为1280×720，象素格式为ARGB888。

\param[in] fd Framebuffer设备号
\param[in] FBIOGET_VSCREENINFO  ioctl号
\param[out] var  可变信息结构体指针
\retval 0  SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOPUT_VSCREENINFO
\par example
\code
struct fb_var_screeninfo vinfo;
if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo) < 0)
{
    return -1;
}

\endcode
*/
int ioctl (int fd, FBIOGET_VSCREENINFO, struct fb_var_screeninfo *var);


/**
\brief 设置Framebuffer的屏幕分辨率和象素格式等。
\attention \n
分辨率的大小必须在各叠加层支持的分辨率范围内，各叠加层支持的最大分辨率和最小分辨率可通过FBIOGET_CAPABILITY_HIFB获取。\n
必须保证实际分辨率与偏移的和在虚拟分辨率范围内，否则系统会自动调整实际分辨率的大小让其在虚拟分辨率范围内。

\param[in] fd Framebuffer设备号
\param[in] FBIOPUT_VSCREENINFO ioctl号
\param[in] var 可变信息结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOGET_VSCREENINFO
\par example
\code
//设置实际分辨率为720×576，虚拟分辨率为720×576，偏移为（0，0），象素格式为ARGB8888的示例代码如下：
struct fb_bitfield r32 = {16, 8, 0};
struct fb_bitfield g32 = {8, 8, 0};
struct fb_bitfield b32 = {0, 8, 0}; 
struct fb_bitfield a32 = {24, 8, 0};
struct fb_var_screeninfo vinfo;
if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo) < 0)
{
    return -1;
}
vinfo.xres_virtual = 720;
vinfo.yres_virtual = 576;
vinfo.xres = 720;
vinfo.yres = 576;
vinfo.activate = FB_ACTIVATE_NOW;
vinfo.bits_per_pixel = 32;
vinfo.xoffset = 0;
vinfo.yoffset = 0;
vinfo.red = r32;
vinfo.green = g32;
vinfo.blue = b32;
vinfo.transp= a32;
if (ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo) < 0)
{
    return -1;
}

\endcode
*/
int ioctl (int fd, FBIOPUT_VSCREENINFO, struct fb_var_screeninfo *var);



/**
\brief 获取Framebuffer的固定信息。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOGET_FSCREENINFO  ioctl号
\param[out] fix 固定信息结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
无
*/
int ioctl (int fd, FBIOGET_FSCREENINFO, struct fb_fix_screeninfo *fix);



/**
\brief 设置从虚拟分辨率中的不同偏移处开始显示。
\attention \n
必须保证实际分辨率与偏移的和在虚拟分辨率范围内，否则设置不成功。

\param[in] fd  Framebuffer设备号
\param[in] FBIOPAN_DISPLAY  ioctl号
\param[out] var 可变信息结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
无
\par example
\code
//设置实际分辨率为300×300，虚拟分辨率为720×576，起始偏移为（50，50），然后偏移到（300，0）处开始显示的PAN设置代码如下：
struct fb_bitfield r32 = {16, 8, 0};
struct fb_bitfield g32 = {8, 8, 0};
struct fb_bitfield b32 = {0, 8, 0};
struct fb_bitfield a32 = {24, 8, 0};
struct fb_var_screeninfo vinfo;

vinfo.xres_virtual = 720;
vinfo.yres_virtual = 576;
vinfo.xres = 300;
vinfo.yres = 300;
vinfo.activate = FB_ACTIVATE_NOW;
vinfo.bits_per_pixel = 32;
vinfo.xoffset = 50;
vinfo.yoffset = 50;
vinfo.red = r32;
vinfo.green = g32;
vinfo.blue = b32;
vinfo.transp= a32;
if (ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo) < 0)
{
    return -1;
}
vinfo.xoffset = 300;
vinfo.yoffset = 0;
if (ioctl(fd, FBIOPAN_DISPLAY, &vinfo) < 0)
{
    return -1;
}

\endcode
*/
int ioctl (int fd, FBIOPAN_DISPLAY, struct fb_var_screeninfo *var);



/**
\brief 获取调色板信息。
\attention \n
无

\param[in] fd  Framebuffer设备号
\param[in] FBIOGETCMAP  ioctl号
\param[out] cmap 调色板结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOPUTCMAP
\par example
\code
//only low 8bits valid 
unsigned short Red256[256];   
//only low 8bits valid 
unsigned short Green256[256];  
// only low 8bits valid 
unsigned short Blue256[256];   
struct fb_cmap cmap;

cmap.start = 0;
cmap.len = 256;
cmap.red = Red256;
cmap.green = Green256;
cmap.blue = Blue256;
cmap.transp = 0;

if (ioctl(fd, FBIOGETCMAP, &cmap) < 0)
{
    printf("fb ioctl get cmap err!\n");
    return -1;
}

\endcode
*/
int ioctl (int fd, FBIOGETCMAP, struct fb_cmap *cmap);



/**
\brief 设置调色板信息。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOPUTCMAP  ioctl号
\param[in] cmap 调色板结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOGETCMAP
\par example
\code
//only low 8bits valid 
unsigned short Red256[256];     
//only low 8bits valid 
unsigned short Green256[256]; 
//only low 8bits valid 
unsigned short Blue256[256];    
struct fb_cmap cmap;

//create a palette which contains 256 color 
Palette_Create(Red256, Green256, Blue256);

cmap.start = 0;
cmap.len = 256;
cmap.red = Red256;
cmap.green = Green256;
cmap.blue = Blue256;
cmap.transp = 0;

if (ioctl(fd, FBIOPUTCMAP, &cmap) < 0)
{
    printf("fb ioctl put cmap err!\n");
    return -1;
}

\endcode
*/
int ioctl (int fd, FBIOPUTCMAP, struct fb_cmap *cmap);




/**-----扩展功能--------*/
/**
\brief 获取叠加层的支持能力。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOGET_CAPABILITY_HIFB  ioctl号
\param[out] pstCap 支持能力结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
无
*/
int ioctl (int fd, FBIOGET_CAPABILITY_HIFB, HIFB_CAPABILITY_S *pstCap);



/**
\brief 获取叠加层在屏幕上显示的起始点坐标。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOGET_SCREEN_ORIGIN_HIFB  ioctl号
\param[out] pstPoint 坐标原点结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOPUT_SCREEN_ORIGIN_HIFB
*/
int ioctl (int fd, FBIOGET_SCREEN_ORIGIN_HIFB, HIFB_POINT_S *pstPoint);



/**
\brief 设置叠加层在屏幕上显示的起始点坐标。
\attention \n
如果叠加层坐标原点超出了范围，默认将坐标原点设置为（u32MaxWidth –u32MinWidth,，u32MaxHeight –u32MinHeight）。
\param[in] fd  Framebuffer设备号
\param[in] FBIOPUT_SCREEN_ORIGIN_HIFB  ioctl号
\param[in] pstPoint 坐标原点结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOGET_SCREEN_ORIGIN_HIFB
*/
int ioctl (int fd, FBIOPUT_SCREEN_ORIGIN_HIFB, HIFB_POINT_S *pstPoint);



/**
\brief 获取当前叠加层的显示状态。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOGET_SHOW_HIFB  ioctl号
\param[out] bShow 指示当前叠加层的状态：*bShow = HI_TRUE：当前叠加层处于显示状态；*bShow = HI_FALSE：当前叠加层处于隐藏状态
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOPUT_SHOW_HIFB
*/
int ioctl (int fd, FBIOGET_SHOW_HIFB, HI_BOOL *bShow);



/**
\brief 显示或隐藏该叠加层。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOPUT_SHOW_HIFB  ioctl号
\param[in] bShow 该叠加层的显示状态：*bShow = HI_TRUE：显示当前叠加层；*bShow = HI_FALSE：隐藏当前叠加层
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOGET_SHOW_HIFB
*/
int ioctl (int fd, FBIOPUT_SHOW_HIFB, HI_BOOL *bShow);



/**
\brief 获取叠加层的colorkey。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOGET_COLORKEY_HIFB  ioctl号
\param[out] pstColorKey  colorkey结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOPUT_COLORKEY_HIFB
*/
int ioctl (int fd, FBIOGET_COLORKEY_HIFB, HIFB_COLORKEY_S *pstColorKey);



/**
\brief 设置叠加层的colorkey。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOPUT_COLORKEY_HIFB  ioctl号
\param[in] pstColorKey  colorkey结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOGET_COLORKEY_HIFB
\par example
\code
//假设当前象素格式为ARGB8888，则要过滤掉红色,具体设置如下：
HIFB_COLORKEY_S stColorKey;

stColorKey.bKeyEnable = HI_TRUE;
stColorKey.u32Key = 0xFF0000;
if (ioctl(fd, FBIOPUT_COLORKEY_HIFB, &stColorKey) < 0)
{
    return -1;
}

\endcode
*/
int ioctl (int fd, FBIOPUT_COLORKEY_HIFB, HIFB_COLORKEY_S *pstColorKey);



/**
\brief 获取叠加层Alpha。
\attention \n
请参见::HIFB_ALPHA_S的说明。

\param[in] fd  Framebuffer设备号
\param[in] FBIOGET_ALPHA_HIFB  ioctl号
\param[out] pstAlpha  Alpha结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOPUT_ALPHA_HIFB
*/
int ioctl (int fd, FBIOGET_ALPHA_HIFB, HIFB_ALPHA_S *pstAlpha);




/**
\brief 设置叠加层的Alpha。
\attention \n
请参见::HIFB_ALPHA_S的说明。

\param[in] fd  Framebuffer设备号
\param[in] FBIOPUT_ALPHA_HIFB  ioctl号
\param[in] pstAlpha  Alpha结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOGET_ALPHA_HIFB
*/
int ioctl (int fd, FBIOPUT_ALPHA_HIFB, HIFB_ALPHA_S *pstAlpha);



/**
\brief 获取叠加层的抗闪烁设置。高清平台不支持设置。
\attention \n
在获取抗闪烁参数时，必须设置能够获取抗闪烁的最大级别，且为抗闪烁系数分配足够的内存。目前该接口在高清无效。

\param[in] fd  Framebuffer设备号
\param[in] FBIOGET_DEFLICKER_HIFB  ioctl号
\param[out] pstDeflicker  抗闪烁结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOPUT_DEFLICKER_HIFB
\par example
\code
//获取水平和垂直抗闪烁最大级别为2的示例代码如下：
HI_U8 u8HDefCoef;
HI_U8 u8VDefCoef;
HIFB_DEFLICKER_S stDeflicker;

stDeflicker.u32HDfLevel = 2;
stDeflicker.u32VDfLevel = 2;
stDeflicker.pu8HDfCoef = &u8HDefCoef;
stDeflicker.pu8VDfCoef = &u8VDefCoef;

if (ioctl(fd, FBIOGET_DEFLICKER_HIFB, &stDeflicker) < 0)
{
    return -1;
}

\endcode
*/
int ioctl (int fd, FBIOGET_DEFLICKER_HIFB, HIFB_DEFLICKER_S *pstDeflicker);



/**
\brief 设置叠加层的抗闪烁功能。
\attention \n
请参见::HIFB_DEFLICKER_S的说明。目前该接口在高清无效。

\param[in] fd  Framebuffer设备号
\param[in] FBIOPUT_DEFLICKER_HIFB  ioctl号
\param[in] pstDeflicker  抗闪烁结构体指针
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
::FBIOGET_DEFLICKER_HIFB
\par example
\code
//设置水平和垂直2阶抗闪烁的代码如下：
HI_U8 u8HDefCoef = 0x80;
HI_U8 u8VDefCoef = 0x80;
HIFB_DEFLICKER_S stDeflicker;

stDeflicker.u32HDfLevel = 2;
stDeflicker.u32VDfLevel = 2;
stDeflicker.pu8HDfCoef = &u8HDefCoef;
stDeflicker.pu8VDfCoef = &u8VDefCoef;

if (ioctl(fd, FBIOPUT_DEFLICKER_HIFB, &stDeflicker) < 0)
{
    return -1;
}
\endcode
*/
int ioctl (int fd, FBIOPUT_DEFLICKER_HIFB, HIFB_DEFLICKER_S *pstDeflicker);



/**
\brief 为了操作显存时而不引起撕裂现象，一般可以在该叠加层的垂直消隐区对显存进行操作，通过该接口可以等待该叠加层垂直消隐区的到来。
\attention \n
无
\param[in] fd  Framebuffer设备号
\param[in] FBIOGET_VBLANK_HIFB  ioctl号
\retval  0 SUCCESS 成功
\retval ::EPERM  1,不支持该操作
\retval ::ENOMEM  12,内存不够
\retval ::EFAULT  14,传入参数指针地址无效
\retval ::EINVAL  22,传入参数无效
\see \n
无
*/
int ioctl (int fd, FBIOGET_VBLANK_HIFB);

/** @} */  /** <!-- ==== API declaration end ==== */
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HIFB_H__ */

