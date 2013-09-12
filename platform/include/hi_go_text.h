/**
\file
\brief text模块头文件
\author Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version 1.0
\author s37678
\date 2008-7-21
*/

#ifndef __HI_GO_TEXT_H__
#define __HI_GO_TEXT_H__

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_8 */
/** @{ */  /** <!-- 【text模块】 */

#define LAYOUT_LEFT          HIGO_LAYOUT_LEFT     /**< 水平居左*/
#define LAYOUT_RIGHT         HIGO_LAYOUT_RIGHT    /**< 水平居右*/
#define LAYOUT_HCENTER       HIGO_LAYOUT_HCENTER  /**< 水平居中*/
#define LAYOUT_TOP           HIGO_LAYOUT_TOP      /**< 垂直居顶*/
#define LAYOUT_BOTTOM        HIGO_LAYOUT_BOTTOM   /**< 垂直居底*/
#define LAYOUT_VCENTER       HIGO_LAYOUT_VCENTER  /**< 垂直居中*/
#define LAYOUT_WRAP          HIGO_LAYOUT_WRAP     /**< 自动换行*/
#define LAYOUT_WORDELLIPSIS  HIGO_LAYOUT_WORDELLIPSIS  /**< 使用省略号风格*/

/** */
typedef enum 
{
    HIGO_LAYOUT_LEFT             = 0x0001,
    HIGO_LAYOUT_RIGHT            = 0x0002,
    HIGO_LAYOUT_HCENTER          = 0x0004,
    HIGO_LAYOUT_WRAP             = 0x0008,
    HIGO_LAYOUT_WORDELLIPSIS     = 0x0010,    
    HIGO_LAYOUT_TOP              = 0x0100,
    HIGO_LAYOUT_BOTTOM           = 0x0200,
    HIGO_LAYOUT_VCENTER          = 0x0400,
    HIGO_LAYOUT_BUTT             = 0x8000,
} HIGO_LAYOUT_E;

/**< 字符集定义 */
typedef enum 
{
    HIGO_CHARSET_UNKOWN,
    HIGO_CHARSET_ASCI,
    HIGO_CHARSET_GB2312,
    HIGO_CHARSET_UCS2,
    HIGO_CHARSET_UTF8,
    HIGO_CHARSET_BUTT,
} HIGO_CHARSET_E;

/** 字体属性 */
typedef struct
{
    HIGO_CHARSET_E Charset; /**< 字符集名称 */
    HI_U8 Height;         /**< 字体高度 */
    HI_U8 MaxWidth;      /**< 字体最大宽度 */
}HIGO_FONTATTR_S;

/** 文本输出对像属性 */
typedef struct
{
    HI_COLOR        BgColor;     /**< 背景色 */
    HI_COLOR        FgColor;     /**< 前景色 */ 
    HIGO_FONTATTR_S SbFontAttr;  /**< 单字节字符集字体属性 */  
    HIGO_FONTATTR_S MbFontAttr;  /**< 多字节字符集字体属性 */    
} HIGO_TEXTOUTATTR_S;

/** @} */  /*! <!-- Structure Definition end */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_8 */
/** @{ */  /** <!-- 【text模块】 */

/** 
\brief 创建文本输出对象
\attention \n
pSbFontFile和pMbFontFile不可同时为空,如果传入的是矢量字体文件名,则字体高度按
22点阵创建
\param[in] pSbFontFile 单字节字符集字体文件，为空表示不使用单字节字符集字库
\param[in] pMbFontFile 多字节字符集字体文件，为空表示不使用多字节字符集字库，但是不能与单字节字符文件同时为空。
\param[out]  pTextOut 文本输出对象句柄

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NOMEM

\see \n
::HI_GO_DestroyText
*/
HI_S32 HI_GO_CreateText(const HI_CHAR* pSbFontFile, const HI_CHAR* pMbFontFile, HI_HANDLE* pTextOut);

/** 
\brief 销毁文本输出对象
\attention \n
无
\param[in] TextOut 文本输出对象句柄

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_CreateText
*/
HI_S32 HI_GO_DestroyText(HI_HANDLE TextOut);

/** 
\brief 获取文本输出对象属性
\attention \n
无
\param[in] TextOut 文本输出对象句柄
\param[out] pTextOutAttr  文本输出对象属性

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_GetTextAttr(HI_HANDLE TextOut,HIGO_TEXTOUTATTR_S *pTextOutAttr);

/** 
\brief 获取文本内容的宽高
\attention \n
无
\param[in] TextOut 文本输出对象句柄
\param[in] pText 文本内容
\param[out] pWidth 文本内容宽度，不可为空
\param[out] pHeight 文本内容高度，不可为空

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORT_CHARSET

\see \n
无
*/
HI_S32 HI_GO_GetTextExtent(HI_HANDLE TextOut, const HI_CHAR *pText, HI_S32 *pWidth, HI_S32 *pHeight);

/** 
\brief 设置文本输出对象的背景色是否显示
\attention \n
none
\param[in] TextOut 文本输出对象句柄
\param[in] bTransparent  文本输出对象背景色是否显示，为HI_TRUE, 则不显示，默认为HI_TRUE

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_SetTextBGTransparent(HI_HANDLE TextOut, HI_BOOL bTransparent);

/** 
\brief 设置文本输出对象的背景色
\attention \n
如果目标surface是调色板，则Color是调色板索引
\param[in] TextOut 文本输出对象句柄
\param[in] Color  文本输出对象背景色，

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_SetTextBGColor(HI_HANDLE TextOut, HI_COLOR Color);


/** 
\brief 设置文本输出对象的字体颜色
\attention \n
如果目标surface是调色板，则Color是调色板索引
\param[in] TextOut 文本输出对象句柄
\param[in] Color  文本输出对象字体颜色

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_SetTextColor(HI_HANDLE TextOut, HI_COLOR Color);

/** 
\brief 输出文本内容到指定surface
\attention
无
\param[in] TextOut 文本输出对象句柄
\param[in] Surface Surface句柄
\param[in] pText  文本内容
\param[in] pRect  文本输出区域，为空表示从surface原点输出

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_TextOut(HI_HANDLE TextOut,HI_HANDLE Surface, const HI_CHAR *pText, 
                           const HI_RECT *pRect);

/** 
\brief 文本输出扩展接口,输出内容可以按照用户指定的排版进行输出。
\param[in] hTextOut 文本输出句柄
\param[in] hSurface Surface句柄
\param[in] pText    以/0结尾的文本内容
\param[in] pRect    文本输出区域
\param[in] Style    排版格式，如LAYOUT_LEFT、LAYOUT_RIGHT、LAYOUT_HCENTER等

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
无
*/
HI_S32 HI_GO_TextOutEx(HI_HANDLE hTextOut, HI_HANDLE hSurface, 
                               const HI_CHAR *pText,  const HI_RECT *pRect, 
                               HIGO_LAYOUT_E Style);


/** 
\brief 计算指定文本输出区域字符个数
\attention \n
无
\param[in] hTextOut 文本输出句柄
\param[in] pText    以/0结尾的文本内容
\param[in] pRect    文本输出区域,不可为空
\param[in] pLen     字符串长度指针

\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HI_SUCCESS

\see \n
无
*/
HI_S32 HI_GO_GetTextExtentEx(HI_HANDLE TextOut, const HI_CHAR *pText, 
                                       const HI_RECT *pRect, HI_U32 *pLen);

typedef enum
{
    HIGO_TEXT_STYLE_NORMAL = 0x00, /*正常字体*/ 
    HIGO_TEXT_STYLE_ITALIC = 0x01, /*斜体字体*/ 
    HIGO_TEXT_STYLE_BOLD   = 0x02, /*粗体字体*/ 
    HIGO_TEXT_STYLE_BUTT   = 0x80,
} HIGO_TEXT_STYLE_E;

typedef struct
{
    const HI_CHAR* pSbcFontFile;
    const HI_CHAR* pMbcFontFile;
    HI_U32   u32Size; /*如果是点阵字体，则该值被忽略*/
} HIGO_TEXT_INFO_S;

/** 
\brief 创建字体
\attention \n
无
\param[in] phText 文本输出句柄
\param[in] pInfo  文件信息

\retval ::HI_SUCCESS 字体创建成功
\retval ::HI_FAILURE 字体创建失败
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_CreateTextEx(const HIGO_TEXT_INFO_S* pInfo, HI_HANDLE* phText);

/** 
\brief 设置字体的风格，比如:粗体，斜体，正常体
\attention \n
无
\param[in] hTextOut 文本输出句柄
\param[in] eStyle   字体风格

\retval ::HI_SUCCESS 成功
\retval ::HIGO_ERR_INVHANDLE

\see \n
无
*/
HI_S32 HI_GO_SetTextStyle(HI_HANDLE hTextOut, HIGO_TEXT_STYLE_E eStyle);

/** 
\brief 设置字符显示水平间距，两个字符行水平间距
\attention \n
无

\param[in] hTextOut 文本输出句柄
\param[in] u32Distance 水平间距

\retval ::HI_SUCCESS 成功
\retval ::HIGO_ERR_INVHANDLE 失败

\see \n
无
*/
HI_S32 HI_GO_SetCharExtra(HI_HANDLE hTextOut, HI_U32 u32Distance);

/** 
\brief 设置垂直水平间距
\attention \n
只有换行风格才有效

\param[in] hTextOut 文本输出句柄
\param[in] u32Distance 垂直间距

\retval ::HI_SUCCESS 成功
\retval ::HIGO_ERR_INVHANDLE 失败

\see \n
无
*/
HI_S32 HI_GO_SetLineExtra(HI_HANDLE hText, HI_U32 u32Distance);

/** 
\brief 初始化字符模块
\attention \n
无
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 失败
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
无
*/
HI_S32 HI_GO_InitText();

/** 
\brief 去初始化字符模块
\attention \n
无
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HIGO_ERR_NOTINIT 失败

\see \n
无
*/
HI_S32 HI_GO_DeinitText();


/** @} */  /*! <!-- API declaration end */
#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_TEXT_H__ */

