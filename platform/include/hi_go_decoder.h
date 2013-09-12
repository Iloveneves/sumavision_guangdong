/**
 \file
 \brief Decoderģ��ͷ�ļ�
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author 1.0
 \date 2008-5-16
 */

#ifndef __HI_GO_DECODE_H__
#define __HI_GO_DECODE_H__

#include "hi_type.h"
#include "hi_go_comm.h"
#include "hi_go_surface.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_4 */
/** @{ */  /** <!-- ��Decoder�� */

/** ����ʵ���Ľ������� */
typedef enum 
{
    HIGO_DEC_IMGTYPE_JPEG = HIGO_IMGTYPE_JPEG, /**< JPEG��ʽͼƬ*/
    HIGO_DEC_IMGTYPE_GIF  = HIGO_IMGTYPE_GIF,  /**< GIF��ʽͼƬ*/
    HIGO_DEC_IMGTYPE_BMP  = HIGO_IMGTYPE_BMP,  /**< BMP��ʽͼƬ */
    HIGO_DEC_IMGTYPE_PNG  = HIGO_IMGTYPE_PNG,  /**< PNG��ʽͼƬ */
    HIGO_DEC_IMGTPYE_BUTT
} HIGO_DEC_IMGTYPE_E;

/** ��������Դ */
typedef enum 
{
    HIGO_DEC_SRCTYPE_FILE = 0, /**< ������Դ���ļ�*/
    HIGO_DEC_SRCTYPE_MEM,      /**< ������Դ���ڴ�*/
    HIGO_DEC_SRCTYPE_STREAM,   /**< ������Դ����ʽ����*/    
    HIGO_DEC_SRCTYPE_BUTT
} HIGO_DEC_SRCTYPE_E;

typedef enum 
{
    HIGO_DEC_POSITION_SET = 0,   /*��ʼλ��*/
    HIGO_DEC_POSITION_CUR,       /*�ӵ�ǰλ��*/
    HIGO_DEC_POSITION_END,       /*�ӽ���λ��*/
    HIGO_DEC_POSITION_BUTT
}HIGO_DEC_POSITION_E;

typedef HI_S32 (*PTR_Dec_WriteStreamCB_FN)(HIGO_DEC_POSITION_E Position,  HI_S32 Offset);


/**������Դ����ϸ��Ϣ*/
typedef union 
{
    //����ԴΪ�ڴ��ʱ��Ҫ����Ϣ
    struct
    {
        HI_CHAR* pAddr;      /**< �ڴ�ָ���ַ*/
        HI_U32 Length;       /**< ����*/
    } MemInfo;

    //ͼƬ�ļ���
    const HI_CHAR *pFileName;
    PTR_Dec_WriteStreamCB_FN pWriteCB;
} HIGO_DEC_SRCINFO_U;

/** ��������ʵ����Ҫ�Ĳ��� */
typedef struct 
{
    HIGO_DEC_SRCTYPE_E SrcType; /**< ��������������*/
    HIGO_DEC_SRCINFO_U SrcInfo; /**< ����Դ��ϸ��Ϣ*/
} HIGO_DEC_ATTR_S;

/** ���������Ϣ */
typedef struct 
{
    HI_U32             Count;           /**< ͼƬ�ĸ��� */
    HIGO_DEC_IMGTYPE_E ImgType;         /**< ����Դ���� */
    HI_U32             ScrWidth;        /**< ��Ļ��ȣ��˴���Ļ��ʾͼƬ�ļ���Ļ��0��ʾ��Ч */
    HI_U32             ScrHeight;       /**< ��Ļ�߶ȣ��˴���Ļ��ʾͼƬ�ļ���Ļ��0��ʾ��Ч */
    HI_BOOL            IsHaveBGColor;   /**< �Ƿ��б���ɫ */
    HI_COLOR           BGColor;         /**< ������ɫ */
} HIGO_DEC_PRIMARYINFO_S;

/** ����ͼƬ��ʽ */
typedef struct 
{
    HI_U32    OffSetX;                /**< ����Ļ�ϵ�Xƫ�������˴���Ļ��ʾͼƬ�ļ���Ļ����ͬ */
    HI_U32    OffSetY;                /**< ����Ļ�ϵ�Yƫ����*/
    HI_U32    Width;                  /**< ԭʼͼƬ�Ŀ�� */
    HI_U32    Height;                 /**< ԭʼͼƬ�ĸ߶� */
    HI_U8     Alpha;                  /**< ����ͼƬ���е��ӵ�ͨ��alpha��Ϣ����Χ��0-255 */
    HI_BOOL   IsHaveKey;              /**< �Ƿ���KEY�� HI_FALSE: KEY��ʹ�ܣ�HI_TRUE: KEYʹ�� */
    HI_COLOR  Key;                    /**< ����ͼƬ���е��ӵ�colorkey��Ϣ */
    HIGO_PF_E Format;                 /**< ͼƬԴ���ظ�ʽ */
    HI_U32    DelayTime;              /**< ����һ��ͼƬ��ʱ����(10ms)��0��ʾ�ò�����Ч */
    HI_U32    DisposalMethod;         /**< ��ǰ֡���������˽ӿ�ֻ��GIF��Ч��0:�û���������ʽ��1:��������2:ʹ�ñ���ɫ��*/    
} HIGO_DEC_IMGINFO_S;

/** �����ͼƬ���� */
typedef struct 
{
    HI_U32    Width;                  /**< ����������� */
    HI_U32    Height;                 /**< ���������߶�*/
    HIGO_PF_E Format;                 /**< ������������ظ�ʽ*/
} HIGO_DEC_IMGATTR_S;

/** ��չ���ݸ�ʽ���� */
typedef enum 
{
    HIGO_DEC_EXTEND_EXIF = 0,         /**< EXIF��ʽ����չ���� */
    HIGO_DEC_EXTEND_EXIF_BUTT
} HIGO_DEC_EXTENDTYPE_E;

/** ͼƬ������Ϣ */
typedef struct 
{
    HI_U32    Width;                /**< ͼƬ�Ŀ�� */
    HI_U32    Height;               /**< ͼƬ�ĸ߶� */
    HIGO_PF_E PixelFormat;          /**< ���ظ�ʽ */
    HI_U32    VirAddr[3];           /**< �����ַ�������RGB��ʽ��ֻ�е�һ��VirAddr[0]Ϊ��ʼ��ַ��
                                                VirAddr[1]��VirAddr[2]��Ч�������YC��ʽ��
                                                VirAddr[0]��ʾY������ʼ��ַ��VirAddr[1]��ʾC������ʼ��ַ��
                                                VirAddr[2]��Ч */
    HI_U32    PhyAddr[3];           /**< �����ַ��ʹ��ԭ��ͬ�� */
    HI_U32    Pitch[3];             /**< �м�࣬ʹ��ԭ��ͬ�� */
    HI_U32    Palate[256];          /**< ��ɫ�� */
} HIGO_DEC_IMGDATA_S;

/** ��������Ϣ*/
typedef struct
{
    HI_VOID *pStreamAddr;    /**< ��������ʼ��ַ*/
    HI_U32   StreamLen;      /**< ������*/
    HI_BOOL  EndFlag;        /**< �����������*/
    HI_U32   CopyLen;        /**< ʵ�ʿ��������ݳ���*/
}HIGO_DEC_WRITESTREAM_S;


/** @} */  /*! <!-- Structure Definition end */
/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_4 */
/** @{ */  /** <!-- ��Decoder�� */


 /** 
\brief ��������ʼ��
\attention \n
::HI_GO_Init���Ѱ����Ըýӿڵĵ���
\param  ��

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
::HI_GO_Init \n
::HI_GO_DeinitDecoder
*/

HI_S32 HI_GO_InitDecoder(HI_VOID);


/** 
\brief ������ȥ��ʼ��
\attention \n
::HI_GO_Deinit���Ѱ����Ըýӿڵĵ���
\param  ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_Deinit \n
::HI_GO_InitDecoder
*/

HI_S32 HI_GO_DeinitDecoder(HI_VOID);

 /** 
 \brief ����������
 \attention \n
Ŀǰ֧��BMP��PNG��JPEG��GIF��ʽ��ͼƬ����Դֻ����Ϊ�ڴ桢�ļ��Լ���ʽ����ʽĿǰֻ��JPEG��ʽ��Ч��

 \param[in] pSrcDesc ����Դ��Ϣ������Ϊ��
                ��������������Ҫ������Դ��ϸ��Ϣһһƥ�䣬��FILE��������Ҫ������Ӧ���ļ���
                ��Memory��������Ҫ����memory�ĵ�ַ�Լ�����
 \param[out] pDecoder ����ʵ�����ָ�룬����Ϊ��
 
 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_NOTINIT
 \retval ::HIGO_ERR_NOMEM
 \retval ::HIGO_ERR_INVHANDLE
 \retval ::HIGO_ERR_INVFILE
 \retval ::HIGO_ERR_INVSRCTYPE
 \retval ::HIGO_ERR_INVIMAGETYPE
 \retval ::HIGO_ERR_INVIMGDATA

\see \n
::HI_GO_DestroyDecoder
*/
HI_S32 HI_GO_CreateDecoder(const HIGO_DEC_ATTR_S* pSrcDesc, HI_HANDLE* pDecoder);

 /** 
 \brief ���ٽ�����
 \attention \n
  �� 
 \param[in] Decoder ����ʵ�����
 
 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_CreateDecoder
*/
HI_S32 HI_GO_DestroyDecoder(HI_HANDLE Decoder);

/** 
 \brief ��ʽ�����ӿ�
 \attention \n
  �� 
 \param[in] Decoder ����ʵ�����
 \param[in] pStream ������Ϣָ�� ������Ϊ��
 
 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_INVHANDLE
 \retval ::HIGO_ERR_UNSUPPORTED

\see \n
::HI_GO_CreateDecoder
*/
HI_S32 HI_GO_DecWriteStream(HI_HANDLE Decoder, HIGO_DEC_WRITESTREAM_S *pStream);

/** 
 \brief ��λ������������Ҫ��ֹ�����ʱ��ͽ��н�������λ
 \attention \n
 ��
 \param[in] Decoder ����ʵ�����
 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE
 \retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_CreateDecoder \n
::HI_GO_DestroyDecoder
*/
HI_S32 HI_GO_ResetDecoder(HI_HANDLE Decoder);


 /** 
 \brief ��ȡͼƬ�ļ�����Ҫ��Ϣ
 \attention
 ��
\param[in] Decoder ����ʵ�����
\param[out] pPrimaryInfo ����ͼƬ����Ϣָ�룬����Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR
\retval ::HI_NULL_PTR
\retval ::HIGO_ERR_INVIMGDATA

\see \n
::HI_GO_DecImgInfo
*/
HI_S32 HI_GO_DecCommInfo(HI_HANDLE Decoder, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);

/** 
 \brief ��ȡָ��ͼƬ����Ϣ����ͬʱ�û���������������ͼ���ʽ
 \attention \n
 ��
 \param[in] Decoder ����ʵ�����
 \param[in] Index  ͼƬ�����š�JPEG��ʽͼƬ����ͼ����������0������ͼ��������1��ʼ��
                   GIF��ʽͼƬ�������ļ��еĴ洢˳����������0��ʼ�ݼ�
 \param[out] pImgInfo ͼƬ��Ϣ������Ϊ��
 
 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_INVHANDLE
 \retval ::HIGO_ERR_INVINDEX
 \retval ::HI_FAILURE
 \retval ::HI_NULL_PTR
 \retval ::HIGO_ERR_INVIMGDATA

\see \n
::HI_GO_DecCommInfo
*/
HI_S32 HI_GO_DecImgInfo(HI_HANDLE Decoder, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo);

 /** 
 \brief ��ȡ����ͼƬ������
 \attention \n
 Ŀ��ͼƬ�����е�ͼ���ʽ��֧�ֺ���ʽ
 
\param[in] Decoder ����ʵ�����
\param[in] Index ͼƬ�����ţ������Ŵ�0��ʼ
\param[in] pImgAttr Ŀ��ͼƬ���ԣ�Ϊ�ձ�ʾ����ԭͼƬ����
\param[out] pSurface ��������ݴ�ŵ�surface�ľ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVINDEX
\retval ::HI_FAILURE
\retval ::HI_NULL_PTR
\retval ::HIGO_ERR_INVIMGDATA
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
::HI_GO_DecCommInfo
*/
HI_S32 HI_GO_DecImgData(HI_HANDLE Decoder, HI_U32 Index, const HIGO_DEC_IMGATTR_S *pImgAttr, HI_HANDLE *pSurface);


/** 
 \brief ��ȡ��չ����
 \attention \n
 Hi3110E��֧�ִ˺�����
 \param[in] Decoder ����ʵ�����
 \param[in] DecExtendType ��ȡ��չ���ݵ����ͣ�Ŀǰ��Ҫֻ��JPEG��EXIF��Ϣ
 \param[out] ppData ָ����չ����ָ���ָ��
 \param[out] pLength ppData����
 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_INVHANDLE
 \retval ::HIGO_ERR_UNSUPPORTED

\see \n
::HI_GO_ReleaseDecExtendData
*/
HI_S32 HI_GO_DecExtendData(HI_HANDLE Decoder, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID **ppData, HI_U32 *pLength);

 /** 
 \brief �ͷ���չ����
 \attention \n
 Hi3110E��֧�ִ˺�����
 \param[in] Decoder Decoder���
 \param[in] DecExtendType ��ȡ��չ���ݵ����ͣ�Ŀǰ��Ҫֻ��JPEG��EXIF��Ϣ
 \param[in] pData ָ����չ����ָ��
 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_UNSUPPORTED

\see \n
::HI_GO_DecExtendData
*/
HI_S32 HI_GO_ReleaseDecExtendData(HI_HANDLE Decoder, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID *pData);


/**
\brief ��ͼ����뵽ָ����surface
\attention \n
������Surface���Զ�����Ŀ��surface�Ĵ�С�������ţ����һ�ı�Ŀ��surface��COLORKEY��ALPHA�Լ���ɫ������
\param[in] Decoder ����ʵ�����
\param[in] Index   ����ͼƬ����
\param[out] Surface �����Ŀ��surface

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVINDEX
\retval ::HIGO_ERR_NULLPTR
\retval ::HI_FAILURE
\retval ::HI_NULL_PTR
\retval ::HIGO_ERR_INVIMGDATA
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
��
*/
HI_S32 HI_GO_DecImgToSurface(HI_HANDLE Decoder, HI_U32 Index, HI_HANDLE Surface);

/**
\brief ����ָ�����ļ���������һ���µ�surface
\attention \n
    ����ļ����ж���ͼƬ������:gif������JPEG����ͼ������ͼ��
    JPEGֻ����ͼ��GIF��������һ��ͼƬ
    surface�Ĵ�С��ͼƬ�Ĵ�Сһ��
\param[in] pszFile ͼƬ�ļ�����������GIF, PNG, JPG, BMP
\param[out] pSurface, ��������ͼ�� 

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVINDEX
\retval ::HIGO_ERR_NULLPTR
\retval ::HI_NULL_PTR
\retval ::HIGO_ERR_INVIMGDATA
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVSRCTYPE
\retval ::HIGO_ERR_INVIMAGETYPE

\see \n
��
*/
HI_S32 HI_GO_DecodeFile(const HI_CHAR* pszFile, HI_HANDLE* pSurface);
 
/** @} */  /*! <!-- API declaration end */
#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_DECODE_H__ */
