/**
 \file
 \brief Gdevģ��ͷ�ļ�
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
/** @{ */  /** <!-- ��Gdevģ�顿 */

/*ͼ��ID����*/
typedef enum
{
    HIGO_LAYER_SD_0 = 0,
    HIGO_LAYER_SD_1, 
    HIGO_LAYER_HD_0,
    HIGO_LAYER_HD_1,
    HIGO_LAYER_AD_0, 
    HIGO_LAYER_BUTT,
}HIGO_LAYER_E;   /* start from 0 */


/** ����ͼ�ε��Ӳ�0 */
#define HIGO_LAYER_RGB0 HIGO_LAYER_SD_0

/** ����ͼ�ε��Ӳ�1 */
#define HIGO_LAYER_RGB1 HIGO_LAYER_SD_1

/*����궨����higo��ÿ��ͼ���bufferģʽ������canvas buffer�ǹ��û����Ƶ�buffer,
display buffer��������ʾ�����buffer.*/
#define HIGO_LAYER_BUFFER_SINGLE      0x02 /**< 1��canvas buffer, ��display buffer */    
#define HIGO_LAYER_BUFFER_DOUBLE      0x04 /**< 1��canvas buffer, 1��display buffer ֧��˫���� */ 
#define HIGO_LAYER_BUFFER_TRIPLE      0x08 /**< 1��canvas buffer, 2��display buffer ֧��flip,ˢ�µ�ʱ��ȴ�������� */
#define HIGO_LAYER_BUFFER_OVER        0x10 /**< 1��canvas buffer, 2��display buffer ֧��flip,���ˢ�µ�ʱ���������æ��������ǰ֡ */


/**Ϊ�����϶��壬ͼ���ˢ�·�ʽ��������ʹ��*/
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
    HIGO_LAYER_DEFLICKER_NONE = 0, /*����˸����ֵΪLOW~HIGH,ֵԽ����˸Ч��Խ�ã���Խģ��*/
    HIGO_LAYER_DEFLICKER_LOW,
    HIGO_LAYER_DEFLICKER_MIDDLE,
    HIGO_LAYER_DEFLICKER_HIGH,
    HIGO_LAYER_DEFLICKER_AUTO,    
    HIGO_LAYER_DEFLICKER_BUTT
}HIGO_LAYER_DEFLICKER_E;

/**ͼ�����Բ���*/
typedef struct 
{
    HI_S32                 ScreenWidth;    /**< ͼ������Ļ����ʾ��ȣ��������0 */
    HI_S32                 ScreenHeight;   /**< ͼ������Ļ����ʾ�߶ȣ��������0 */
    HI_S32                 CanvasWidth;    /**< ͼ��Ļ���buffer��ȣ�Ϊ0ʱ������������buffer */
    HI_S32                 CanvasHeight;   /**< ͼ��Ļ���buffer�߶ȣ�Ϊ0ʱ������������buffer */
    HI_S32                 DisplayWidth;   /**< ͼ�����ʾbuffer��ȣ�Ϊ0ʱ����ScreenWidth��ͬ*/
    HI_S32                 DisplayHeight;  /**< ͼ�����ʾbuffer�߶ȣ�Ϊ0ʱ����ScreenHeight��ͬ*/
    HIGO_LAYER_FLUSHTYPE_E LayerFlushType; /**< ͼ���ˢ�·�ʽ���û��ɸ���ʹ�ó���ѡ��ͬ��ˢ��ģʽ�����ˢ��Ч��,����0ʱĬ��ʹ��˫����+Flipˢ��ģʽ */
    HIGO_LAYER_DEFLICKER_E AntiLevel;      /**< ͼ�㿹��˸���� */
    HIGO_PF_E              PixelFormat;    /**< ͼ������ظ�ʽ���˸�ʽ����ΪӲ��ͼ����֧�ֵĸ�ʽ������ݲ�ͬӲ���豸��ѡ��ͼ������ظ�ʽ���� */
    HIGO_LAYER_E           LayerID;        /**< ͼ��Ӳ��ID����֧��ͼ��ȡ����оƬƽ̨��hi3720����֧��һ�������һ������ */
} HIGO_LAYER_INFO_S;

/** ͼ��״̬�ṹ */
typedef struct 
{
    HI_BOOL bShow;             /**< ͼ���Ƿ���ʾ */
} HIGO_LAYER_STATUS_S;

typedef struct
{
    HI_COLOR ColorKey;         /**< ͼ���͸��ɫ*/
    HI_BOOL bEnableCK;         /**< ͼ���Ƿ�ʹ��colorkey */
}HIGO_LAYER_KEY_S;

typedef struct
{
    HI_BOOL bAlphaEnable;   /**<  alpha����ʹ�ܱ�־ */
    HI_BOOL bAlphaChannel;  /**<  alphaͨ��ʹ�ܱ�־  */
    HI_U8   Alpha0;         /**<  alpha0ֵ,��ARGB1555��ʽ����Ч */
    HI_U8   Alpha1;         /**<  alpha1ֵ,��ARGB1555��ʽ����Ч */
    HI_U8   GlobalAlpha;    /**<  ȫ��alpha����ֵֻ����alphaͨ����Ч��ʱ��������� */
}HIGO_LAYER_ALPHA_S;

/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_6 */
/** @{ */  /** <!-- ��Gdevģ�顿 */

/** 
\brief ��ʼ����ʾ�豸
\attention \n
::HI_GO_Init�Ѱ����˶Ըýӿڵĵ���
\param ��

\retval ::HI_FAILURE
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INITFAILED

\see \n
::HI_GO_Init \n
::HI_GO_DeinitDisplay
*/
HI_S32 HI_GO_InitDisplay(HI_VOID);

/** 
\brief ȥ��ʼ����ʾ�豸
\attention \n
::HI_GO_Deinit�Ѱ����˶Ըýӿڵĵ���
\param ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_Deinit \n
::HI_GO_InitDisplay
*/
HI_S32 HI_GO_DeinitDisplay(HI_VOID);

/**
\brief ����ͼ��ID��ȡ��Ӧͼ��(SD,HD)����ʱ��Ĭ�ϲ�����
�����Ҫʹ�÷�Ĭ��ֵ������ֱ������pLayerInfo������Ա
\attention \n

\param[in] LayerID ͼ��ID
\param[in]  pLayerInfo ��ȡ���Ĵ�������

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVPARAM
\see \n
��
*/
HI_S32 HI_GO_GetLayerDefaultParam (HIGO_LAYER_E LayerID, HIGO_LAYER_INFO_S *pLayerInfo);


/** 
\brief ����ͼ��
\attention \n
�Ƿ�֧��VOӲ������ȡ����ƽ̨��
���ƽ̨֧��VO Ӳ�����ţ���������displaysize��screensize��һ�µ�����£����ջ����ŵ�screensize�Ĵ�С��
���ƽ̨��֧��VO Ӳ�����ţ���ʹdisplaysize��screensize��һ�£�Ҳ��ǿ��Ҫ��displaysize��screensizeһ��

\param[in]  pLayerInfo ͼ��������ԣ�����Ϊ��
\param[out] pLayer ͼ��ľ��ָ�룬����Ϊ��

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
\brief ����ͼ��
\attention \n
��ͼ�����ڱ�ʹ��ʱ��������ڴ�ͼ�������δ���٣�����ͼ���޷�������
\param[in] Layer ͼ����

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE


\see \n
::HI_GO_CreateLayer
*/
HI_S32 HI_GO_DestroyLayer(HI_HANDLE Layer);


/** 
\brief ����ͼ������Ļ�е�λ��
\attention \n
������Ч������ˢ�¡������õ�ͼ�����ʼλ�ó�����Ļ��Χʱ���Զ���������Ļ�ı߽�ֵ
\param[in] Layer  ͼ����
\param[in] u32StartX ͼ������Ļ�ϵ���ʾλ��X����
\param[in] u32StartY ͼ������Ļ�ϵ���ʾλ��Y����

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
\brief ��ȡͼ������Ļ�ϵ�λ��
\attention \n
��
\param[in] Layer ͼ����
\param[out] pStartX ͼ������Ļ�ϵ���ʾλ��X����ָ�룬����Ϊ��
\param[out] pStartY ͼ������Ļ�ϵ���ʾλ��Y����ָ�룬����Ϊ��

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
\brief �����������ʾ�豸�ϵ�����ĸ߶ȺͿ��
\attention \n
���ڴ�֧�ֵ�ǰ���£��ýӿڿ���֧������\n

\param[in]  Layer ͼ����
\param[in] u32SWidth  ʵ��������
\param[in] u32SHeight ʵ������߶�
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
\brief ��ȡ�������ʾ�豸�ϵ�����ĸ߶ȺͿ�ȡ�
\attention \n
\param[in]  Layer ͼ����
\param[out] pSWidth  ʵ��������ָ��
\param[out] pSHeight ʵ������߶�ָ��
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
\brief ����ͼ��surface��ȫ��alphaֵ
\attention \n
������Ч������ˢ��
\param[in] Layer ͼ����
\param[in] Alpha ȫ��alphaֵ������Ϊ�գ���Χ0-255

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
\brief ��ȡͼ��surface��ȫ��alphaֵ
\attention \n
��
\param[in] Layer ͼ����
\param[out] pAlpha ȫ��alphaָ��

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
\brief ��ȡͼ���surface
\attention \n
ͼ��surface������ʹ��HI_GO_FreeSurface���ͷš�ֻ��������ͼ���ʱ��Żᱻ�ͷ�
�����л�֮�������øýӿ������»�ȡͼ��surface;
\param[in] Layer ͼ����
\param[out] pSurface surface���ָ�룬����Ϊ��

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_DEPEND_FB

\see \n
��
*/
HI_S32 HI_GO_GetLayerSurface(HI_HANDLE Layer, HI_HANDLE *pSurface);

/** 
\brief ��ʾ������ͼ��
\attention \n
������Ч������ˢ��
\param[in] Layer ͼ����
\param[in] bVisbile ��ʾ���ر�־��HI_TRUE����ʾ��HI_FALSE������

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerStatus
*/
HI_S32 HI_GO_ShowLayer(HI_HANDLE Layer, HI_BOOL bVisbile);

/** 
\brief ��ȡͼ�㵱ǰ״̬
\attention \n
��
\param[in] Layer ͼ����
\param[out] pLayerStatus ͼ�㵱ǰ״̬�ṹָ�룬����Ϊ��

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
\brief ˢ��ͼ��
\attention \n
1.������ɺ���ˢ��ͼ�������ʾ���ƺ���
2.ˢ��������ģʽ��һ����û���κδ��ڵ�ʱ�����ʾlayersurface�����ݣ�������ʾ�����е����ݡ�
\param[in] Layer ͼ����
\param[in]  pRect ˢ�µľ������������NULL, ��ˢ������ȫ��
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_DEPEND_FB
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_EMPTYRECT

\see \n
��
*/
HI_S32 HI_GO_RefreshLayer(HI_HANDLE Layer, const HI_RECT* pRect);


/**
\brief ���ò��canvas surface.
\attention \n
     ����ͱ���ͬԴʱ�����ǿ����ñ����canvas buffer�����Ĺ���ͬһ��
     Surrface���ڴ����ͱ�����MMZ���͵�.
\param[in] Layer     ͼ����
\param[in] hSurface  ͼ���surface������ò���ΪINVALID_HANDLE��ʾû���û����

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVPARAM

\see \n
��
*/
HI_S32 HI_GO_SetLayerSurface(HI_HANDLE Layer, HI_HANDLE hSurface);



/**
\brief ����ͼ��ı�����ɫ
\attention \n
ͼ�㱳��ɫ��ֻ���ڵ��Ӵ��ڲ���Ч
\param[in] Layer ͼ����
\param[in] Color ͼ�㱳����ɫ

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_SetLayerBGColor(HI_HANDLE Layer, HI_COLOR Color);

/**
\brief ��ȡͼ��ı�����ɫ
\attention \n
�˽ӿ�ֻ����ͼ�����д��ڵ�ʱ��Ż���Ч���������ɫ������Ч��
\param[in] Layer ͼ����
\param[in] pColor �洢ͼ�㱳����ɫ

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_GetLayerBGColor(HI_HANDLE Layer, HI_COLOR* pColor);

/**
\brief ������ʾbuffer size
\attention \n
��

\param[in] Layer      ͼ����
\param[in] u32DWidth     ���ָ��
\param[in] u32DHeight    �߶�ָ��
\param[out] �� 

\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVSIZE 
\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE

\see \n
    ::HI_GO_GetDisplaySize 
*/
HI_S32 HI_GO_SetDisplaySize(HI_HANDLE Layer, HI_U32 u32DWidth, HI_U32 u32DHeight);

/**
\brief ��ȡ��ʾbuffer��size
\attention \n
��

\param[in] Layer      ͼ����
\param[in] pDWidth    ���ָ�룬����Ϊ�� 
\param[in] pDHeight   �߶�ָ�룬����Ϊ��
\param[out] �� 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
    ::HI_GO_SetDisplaySize 
*/
HI_S32 HI_GO_GetDisplaySize(HI_HANDLE Layer, HI_U32 *pDWidth, HI_U32 *pDHeight);

/**
\brief ����ˢ������
\attention \n
��

\param[in] Layer         ͼ����           
\param[in] FlushType     ͼ��ˢ������
\param[out] ��

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
\brief ��ȡˢ������
\attention \n
��

\param[in] Layer       ͼ����              
\param[in] *pFlushType ͼ��ˢ�����ͣ�����Ϊ�� 
\param[out] �� 

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
\brief ����ͼ���͸��ɫ
\attention \n
��

\param[in] Layer       ͼ����              
\param[in] pKey        ͸��ɫ��Ϣָ�룬����Ϊ��
\param[out] �� 

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
\brief ��ȡ͸��ɫ��Ϣ
\attention \n
��

\param[in] Layer       ͼ����              
\param[in] pKey        ͸��ɫ��Ϣָ��
\param[out] �� 

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
\brief ����ͼ��ĵ�ɫ��
\attention \n
��

\param[in] Layer       ͼ����              
\param[in] Palette     ͼ���ɫ��
\param[out] �� 

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
\brief ��ȡͼ���ɫ��
\attention \n
��

\param[in] Layer       ͼ����              
\param[in] Palette     ͼ���ɫ��
\param[out] �� 

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
\brief �ȴ�������
\attention \n
��

\param[in] Layer       ͼ����              
\param[out] �� 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE 
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerPalette
*/
HI_S32 HI_GO_WaitForBlank(HI_HANDLE Layer);


/**
\brief ����ͼ��alpha��Ϣ����չ�ӿ�
\attention \n
�ýӿ�HIGO_LAYER_ALPHA_S�ṹ���alpha0,alpha1ֻ��ARGB1555��ʽ�²���Ч��
������ARGB1555��ʽ��ʵ�ְ�͸��Ч��

\param[in] Layer       ͼ����              
\param[in] pAlphaInfo   ͼ��alpha��Ϣ������Ϊ��   
\param[out] �� 

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
\brief ��ȡͼ��alpha��Ϣ����չ�ӿ�
\attention \n
��

\param[in] Layer       ͼ����              
\param[out] pAlphaInfo  ͼ��alpha��Ϣ������Ϊ��   

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
