/**
\file
\brief textģ��ͷ�ļ�
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
/** @{ */  /** <!-- ��textģ�顿 */

#define LAYOUT_LEFT          HIGO_LAYOUT_LEFT     /**< ˮƽ����*/
#define LAYOUT_RIGHT         HIGO_LAYOUT_RIGHT    /**< ˮƽ����*/
#define LAYOUT_HCENTER       HIGO_LAYOUT_HCENTER  /**< ˮƽ����*/
#define LAYOUT_TOP           HIGO_LAYOUT_TOP      /**< ��ֱ�Ӷ�*/
#define LAYOUT_BOTTOM        HIGO_LAYOUT_BOTTOM   /**< ��ֱ�ӵ�*/
#define LAYOUT_VCENTER       HIGO_LAYOUT_VCENTER  /**< ��ֱ����*/
#define LAYOUT_WRAP          HIGO_LAYOUT_WRAP     /**< �Զ�����*/
#define LAYOUT_WORDELLIPSIS  HIGO_LAYOUT_WORDELLIPSIS  /**< ʹ��ʡ�Ժŷ��*/

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

/**< �ַ������� */
typedef enum 
{
    HIGO_CHARSET_UNKOWN,
    HIGO_CHARSET_ASCI,
    HIGO_CHARSET_GB2312,
    HIGO_CHARSET_UCS2,
    HIGO_CHARSET_UTF8,
    HIGO_CHARSET_BUTT,
} HIGO_CHARSET_E;

/** �������� */
typedef struct
{
    HIGO_CHARSET_E Charset; /**< �ַ������� */
    HI_U8 Height;         /**< ����߶� */
    HI_U8 MaxWidth;      /**< ��������� */
}HIGO_FONTATTR_S;

/** �ı������������ */
typedef struct
{
    HI_COLOR        BgColor;     /**< ����ɫ */
    HI_COLOR        FgColor;     /**< ǰ��ɫ */ 
    HIGO_FONTATTR_S SbFontAttr;  /**< ���ֽ��ַ����������� */  
    HIGO_FONTATTR_S MbFontAttr;  /**< ���ֽ��ַ����������� */    
} HIGO_TEXTOUTATTR_S;

/** @} */  /*! <!-- Structure Definition end */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_8 */
/** @{ */  /** <!-- ��textģ�顿 */

/** 
\brief �����ı��������
\attention \n
pSbFontFile��pMbFontFile����ͬʱΪ��,����������ʸ�������ļ���,������߶Ȱ�
22���󴴽�
\param[in] pSbFontFile ���ֽ��ַ��������ļ���Ϊ�ձ�ʾ��ʹ�õ��ֽ��ַ����ֿ�
\param[in] pMbFontFile ���ֽ��ַ��������ļ���Ϊ�ձ�ʾ��ʹ�ö��ֽ��ַ����ֿ⣬���ǲ����뵥�ֽ��ַ��ļ�ͬʱΪ�ա�
\param[out]  pTextOut �ı����������

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
\brief �����ı��������
\attention \n
��
\param[in] TextOut �ı����������

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_CreateText
*/
HI_S32 HI_GO_DestroyText(HI_HANDLE TextOut);

/** 
\brief ��ȡ�ı������������
\attention \n
��
\param[in] TextOut �ı����������
\param[out] pTextOutAttr  �ı������������

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_GetTextAttr(HI_HANDLE TextOut,HIGO_TEXTOUTATTR_S *pTextOutAttr);

/** 
\brief ��ȡ�ı����ݵĿ��
\attention \n
��
\param[in] TextOut �ı����������
\param[in] pText �ı�����
\param[out] pWidth �ı����ݿ�ȣ�����Ϊ��
\param[out] pHeight �ı����ݸ߶ȣ�����Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORT_CHARSET

\see \n
��
*/
HI_S32 HI_GO_GetTextExtent(HI_HANDLE TextOut, const HI_CHAR *pText, HI_S32 *pWidth, HI_S32 *pHeight);

/** 
\brief �����ı��������ı���ɫ�Ƿ���ʾ
\attention \n
none
\param[in] TextOut �ı����������
\param[in] bTransparent  �ı�������󱳾�ɫ�Ƿ���ʾ��ΪHI_TRUE, ����ʾ��Ĭ��ΪHI_TRUE

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_SetTextBGTransparent(HI_HANDLE TextOut, HI_BOOL bTransparent);

/** 
\brief �����ı��������ı���ɫ
\attention \n
���Ŀ��surface�ǵ�ɫ�壬��Color�ǵ�ɫ������
\param[in] TextOut �ı����������
\param[in] Color  �ı�������󱳾�ɫ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_SetTextBGColor(HI_HANDLE TextOut, HI_COLOR Color);


/** 
\brief �����ı���������������ɫ
\attention \n
���Ŀ��surface�ǵ�ɫ�壬��Color�ǵ�ɫ������
\param[in] TextOut �ı����������
\param[in] Color  �ı��������������ɫ

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_SetTextColor(HI_HANDLE TextOut, HI_COLOR Color);

/** 
\brief ����ı����ݵ�ָ��surface
\attention
��
\param[in] TextOut �ı����������
\param[in] Surface Surface���
\param[in] pText  �ı�����
\param[in] pRect  �ı��������Ϊ�ձ�ʾ��surfaceԭ�����

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_TextOut(HI_HANDLE TextOut,HI_HANDLE Surface, const HI_CHAR *pText, 
                           const HI_RECT *pRect);

/** 
\brief �ı������չ�ӿ�,������ݿ��԰����û�ָ�����Ű���������
\param[in] hTextOut �ı�������
\param[in] hSurface Surface���
\param[in] pText    ��/0��β���ı�����
\param[in] pRect    �ı��������
\param[in] Style    �Ű��ʽ����LAYOUT_LEFT��LAYOUT_RIGHT��LAYOUT_HCENTER��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
��
*/
HI_S32 HI_GO_TextOutEx(HI_HANDLE hTextOut, HI_HANDLE hSurface, 
                               const HI_CHAR *pText,  const HI_RECT *pRect, 
                               HIGO_LAYOUT_E Style);


/** 
\brief ����ָ���ı���������ַ�����
\attention \n
��
\param[in] hTextOut �ı�������
\param[in] pText    ��/0��β���ı�����
\param[in] pRect    �ı��������,����Ϊ��
\param[in] pLen     �ַ�������ָ��

\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HI_SUCCESS

\see \n
��
*/
HI_S32 HI_GO_GetTextExtentEx(HI_HANDLE TextOut, const HI_CHAR *pText, 
                                       const HI_RECT *pRect, HI_U32 *pLen);

typedef enum
{
    HIGO_TEXT_STYLE_NORMAL = 0x00, /*��������*/ 
    HIGO_TEXT_STYLE_ITALIC = 0x01, /*б������*/ 
    HIGO_TEXT_STYLE_BOLD   = 0x02, /*��������*/ 
    HIGO_TEXT_STYLE_BUTT   = 0x80,
} HIGO_TEXT_STYLE_E;

typedef struct
{
    const HI_CHAR* pSbcFontFile;
    const HI_CHAR* pMbcFontFile;
    HI_U32   u32Size; /*����ǵ������壬���ֵ������*/
} HIGO_TEXT_INFO_S;

/** 
\brief ��������
\attention \n
��
\param[in] phText �ı�������
\param[in] pInfo  �ļ���Ϣ

\retval ::HI_SUCCESS ���崴���ɹ�
\retval ::HI_FAILURE ���崴��ʧ��
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_CreateTextEx(const HIGO_TEXT_INFO_S* pInfo, HI_HANDLE* phText);

/** 
\brief ��������ķ�񣬱���:���壬б�壬������
\attention \n
��
\param[in] hTextOut �ı�������
\param[in] eStyle   ������

\retval ::HI_SUCCESS �ɹ�
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_SetTextStyle(HI_HANDLE hTextOut, HIGO_TEXT_STYLE_E eStyle);

/** 
\brief �����ַ���ʾˮƽ��࣬�����ַ���ˮƽ���
\attention \n
��

\param[in] hTextOut �ı�������
\param[in] u32Distance ˮƽ���

\retval ::HI_SUCCESS �ɹ�
\retval ::HIGO_ERR_INVHANDLE ʧ��

\see \n
��
*/
HI_S32 HI_GO_SetCharExtra(HI_HANDLE hTextOut, HI_U32 u32Distance);

/** 
\brief ���ô�ֱˮƽ���
\attention \n
ֻ�л��з�����Ч

\param[in] hTextOut �ı�������
\param[in] u32Distance ��ֱ���

\retval ::HI_SUCCESS �ɹ�
\retval ::HIGO_ERR_INVHANDLE ʧ��

\see \n
��
*/
HI_S32 HI_GO_SetLineExtra(HI_HANDLE hText, HI_U32 u32Distance);

/** 
\brief ��ʼ���ַ�ģ��
\attention \n
��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ʧ��
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
��
*/
HI_S32 HI_GO_InitText();

/** 
\brief ȥ��ʼ���ַ�ģ��
\attention \n
��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HIGO_ERR_NOTINIT ʧ��

\see \n
��
*/
HI_S32 HI_GO_DeinitText();


/** @} */  /*! <!-- API declaration end */
#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_TEXT_H__ */

