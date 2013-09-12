/**
 \file
 \brief bliterͷ�ļ�
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
/** @{ */  /** <!-- ��bliter�� */

/** ���ؼ�alpha��ϲ������� */
typedef enum
{
    HIGO_COMPOPT_NONE = 0, /**< Porter/Duff None��ϲ��� */
    HIGO_COMPOPT_CLEAR,    /**< Porter/Duff clear��ϲ��� */
    HIGO_COMPOPT_SRC     , /**< Porter/Duff Src��ϲ��� */ 
    HIGO_COMPOPT_SRCOVER , /**< Porter/Duff Srcover��ϲ��� */ 
    HIGO_COMPOPT_DSTOVER , /**< Porter/Duff DstOver��ϲ��� */ 
    HIGO_COMPOPT_SRCIN   , /**< Porter/Duff SrcIn��ϲ��� */ 
    HIGO_COMPOPT_DSTIN   , /**< Porter/Duff DstIn��ϲ��� */ 
    HIGO_COMPOPT_SRCOUT  , /**< Porter/Duff SrcOut��ϲ��� */ 
    HIGO_COMPOPT_DSTOUT  , /**< Porter/Duff DstOut��ϲ��� */ 
    HIGO_COMPOPT_SRCATOP , /**< Porter/Duff SrcAtop��ϲ��� */ 
    HIGO_COMPOPT_DSTATOP , /**< Porter/Duff DstAtop��ϲ��� */ 
    HIGO_COMPOPT_ADD     , /**< Porter/Duff DstAtop��ϲ��� */ 
    HIGO_COMPOPT_XOR     , /**< Porter/Duff Xor��ϲ��� */ 
    HIGO_COMPOPT_DST     , /**< Porter/Duff DstAtop��ϲ��� */ 
    HIGO_COMPOPT_AKS,      /**< ����Ŀ��surfaceΪ��͸������alpha��ϣ��������Դalpha */
    HIGO_COMPOPT_AKD,      /**< ����Ŀ��surfaceΪ��͸������alpha��ϣ��������Ŀ��alpha */

    HIGO_COMPOPT_BUTT
} HIGO_COMPOPT_E;

/** Colorkey��Ӧ�Ĳ�����ʽ */
typedef enum
{
    HIGO_CKEY_NONE = 0, /**< ��ʹ��colorkey */
    HIGO_CKEY_SRC,      /**< ʹ��Դcolorkey */
    HIGO_CKEY_DST,      /**< ʹ��Ŀ��colorkey */

    HIGO_CKEY_BUTT
} HIGO_CKEY_E;

/** 2ԪROP���� */
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
    HIGO_ROTATE_90,     /**< ˳ʱ����ת90�� */
    HIGO_ROTATE_180,    /**< ˳ʱ����ת180�� */
    HIGO_ROTATE_270,    /**< ˳ʱ����ת270�� */

    HIGO_ROTATE_BUTT
} HIGO_ROTATE_E;

typedef enum
{
    HIGO_MIRROR_NONE = 0,

    HIGO_MIRROR_LR,     /**< ���Ҿ��� */
    HIGO_MIRROR_TB,     /**< ���¾��� */

    HIGO_MIRROR_BUTT
} HIGO_MIRROR_E;

typedef struct 
{
    HI_BOOL EnableGlobalAlpha;      /**< ȫ��alphaʹ�ܱ�־ */
    HI_BOOL EnablePixelAlpha;       /**< ����alphaʹ�ܱ�־ */
    HIGO_COMPOPT_E PixelAlphaComp;  /**< ����alpha���� */
    HIGO_CKEY_E    ColorKeyFrom;    /**< ColorKey���� */
    HI_BOOL        EnableRop;       /**< ����ROP2���� */
    HIGO_ROP_E     Rop;             /**< ROP2�������� */
    HIGO_ROP_E     RopAlpha;        /**< ROP alpha��������*/
 }HIGO_BLTOPT2_S;

/** blit�������� */
typedef struct
{
    HI_BOOL EnableGlobalAlpha;      /**< ȫ��alphaʹ�ܱ�־,�򿪴˿���֮�⻹����ָ��PixelAlphaComp�Ļ�Ϸ�ʽ*/
    HI_BOOL EnablePixelAlpha;       /**< ����alphaʹ�ܱ�־ */
    HIGO_COMPOPT_E PixelAlphaComp;  /**< ����alpha���� */
    HIGO_CKEY_E    ColorKeyFrom;    /**< ColorKey���� */
    HI_BOOL        EnableRop;       /**< ����ROP2���� */
    HIGO_ROP_E     Rop;             /**< ROP2�������� */
    HIGO_ROP_E     RopAlpha;        /**< ROP alpha��������*/    
    HI_BOOL        EnableScale;     /**< �������� */
    HIGO_ROTATE_E  RotateType;      /**< ��ת��ʽ */
    HIGO_MIRROR_E  MirrorType;      /**< ����ʽ */
} HIGO_BLTOPT_S;

typedef struct
{
    HI_BOOL EnableGlobalAlpha;      /**< ȫ��alphaʹ�ܱ�־ */

    HIGO_COMPOPT_E PixelAlphaComp;  /**< ����alpha���� */
    HI_BOOL        EnableRop;       /**< ����ROP2���� */
    HIGO_ROP_E     RopColor;        /**< ROP2�������� */
	HIGO_ROP_E     RopAlpha;
		
} HIGO_MASKOPT_S;

/** ����˸���� */
typedef enum
{
    HIGO_DEFLICKER_AUTO = 0, /*����˸����ֵΪLOW~HIGH,ֵԽ����˸Ч��Խ�ã���Խģ��*/
    HIGO_DEFLICKER_LOW,
    HIGO_DEFLICKER_MIDDLE,
    HIGO_DEFLICKER_HIGH,
    HIGO_DEFLICKER_BUTT
}HIGO_DEFLICKEROPT_E;

/** ����˸���� */
typedef struct
{
    HIGO_DEFLICKEROPT_E DefLevel;
}HIGO_DEFLICKEROPT_S;
/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_1 */
/** @{ */  /** <!-- ��bliter�� */

/** 
\brief ��ʼ��Bliterģ��
\attention \n
::HI_GO_Init���Ѱ����˶Ըýӿڵĵ���
\param ��

\retval ::HI_SUCCESS  
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
::HI_GO_Init \n
::HI_GO_DeinitBliter
*/
HI_S32 HI_GO_InitBliter(HI_VOID);

/** 
\brief ȥ��ʼ��Bliterģ��
\attention \n
::HI_GO_Deinit���Ѱ����˶Ըýӿڵĵ���
\param ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_Deinit \n
::HI_GO_InitBliter
*/

HI_S32 HI_GO_DeinitBliter(HI_VOID);

/** 
\brief �������
\attention \n
��
\param[in] Surface Surface���
\param[in] pRect �����δ�С��Ϊ�ձ�ʾ�������surface
\param[in] Color �����ɫ,ע�������RGB��ʽ��ͳһ���32λɫ�������ɫ�壬��ֱ�������ɫ����(0 ~ 255)��
\param[in] CompositeOpt ��Ϸ�ʽ

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
��
*/
HI_S32 HI_GO_FillRect(HI_HANDLE Surface, const HI_RECT* pRect, HI_COLOR Color, HIGO_COMPOPT_E CompositeOpt);

/** 
\brief λ����ƣ��ڰ��ƹ����У�����ʵ��ɫ�ʿռ�ת�������š���ת����
\attention \n
ɫ�ʿռ�ת����֧��YUV��RGBת�� \n
����֧�ֲ�������colorkey��alpha��ROP��colorkey+ROP\
���š���ת���񲻿����ʹ�� \n
���š���ת����Ҫ��Դ��Ŀ�����ظ�ʽ��ȫ��ͬ����������YUV��ʽ��CLUT��ʽ \n

\param[in] SrcSurface Դsurface���
\param[in] pSrcRect ���Ƶ�Դ����Ϊ�ձ�ʾ����Դsurface����
\param[in] DstSurface Ŀ��surface���
\param[in] pDstRect ���Ƶ�Ŀ������Ϊ�ձ�ʾ����Ŀ��surface����
\param[in] pBlitOpt ��Ϸ�ʽ

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
��
*/
HI_S32 HI_GO_Blit (HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                   HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                   const HIGO_BLTOPT_S* pBlitOpt);

/** 
\brief �����߶Σ���֧�ֲü�
\attention \n
��֧�ֲü���ʹ���߱��뱣֤����ֱ����surface������

\param[in] Surface Ŀ��surface���
\param[in] x0 ���x����
\param[in] y0 ���y����
\param[in] x1 �յ�x����
\param[in] y1 �յ�y���� 
\param[in] color �߶���ɫ

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
��
*/
HI_S32 HI_GO_DrawLine(HI_HANDLE Surface, HI_S32 x0, HI_S32 y0, HI_S32 x1, HI_S32 y1, HI_COLOR color);

/** 
\brief ������Բ
\attention \n
��֧�ֲü���ʹ���߱��뱣֤������Բ��surface������

\param[in] Surface Ŀ��surface���
\param[in] sx Բ��x����
\param[in] sy Բ��y����
\param[in] rx x��뾶 
\param[in] ry y��뾶
\param[in] color ��Բ��ɫ

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
��
*/
HI_S32 HI_GO_DrawEllipse(HI_HANDLE Surface, HI_S32 sx, HI_S32 sy, HI_S32 rx, HI_S32 ry, HI_COLOR color);

/** 
\brief ����Բ����֧�ֲü�
\attention \n
��֧�ֲü���ʹ���߱��뱣֤����Բ��surface������

\param[in] Surface Ŀ��surface���
\param[in] x Բ��x����
\param[in] y Բ��y����
\param[in] r �뾶
\param[in] color Բ��ɫ, ��ɫ����32λɫ�������

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
��
*/
HI_S32 HI_GO_DrawCircle(HI_HANDLE Surface, HI_S32 x, HI_S32 y, HI_S32 r, HI_COLOR color);

/** 
\brief ���ƾ���
\attention \n
����Ϊ�ձ�ʾ������δ�С��surface��ͬ
��֧�ֲü���ʹ���߱��뱣֤����������surface������

\param[in] Surface Ŀ��surface���
\param[in] pRect ��������
\param[in] color ������ɫ

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
��
*/
HI_S32 HI_GO_DrawRect(HI_HANDLE Surface, const HI_RECT* pRect, HI_COLOR color);

/** 
\brief �Թ�դλͼ����Mask Rop����Mask Blend���Ʋ���
\attention \n
Mask��A1��A8��λͼSurface��
���Ƚ�Maskλͼ��Դλͼ��һ�ε��ӣ�Ȼ���õ��ӵĽ����Ŀ�������������Ŀ��λͼ
Rop��Blend���ͬʱֻ����һ������Ч�ģ����߶�ѡֻ��Rop��Ч

\param[in] SrcSurface Դsurface���
\param[in] pSrcRect Դ����
\param[in] DstSurface Ŀ��surface���
\param[in] pDstRect Ŀ�����
\param[in] MaskSurface MASK surface���
\param[in] pMaskRect MASK����
\param[in] pOpt ����ѡ��

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
��
*/

HI_S32 HI_GO_MaskBlit(HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                      HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                      HI_HANDLE MaskSurface, const HI_RECT* pMaskRect,
                      const HIGO_MASKOPT_S* pOpt);


/** 
\brief λ����ƣ��ڰ��ƹ����У�����ʵ��ɫ�ʿռ�ת��
\attention \n
ɫ�ʿռ�ת����֧��YUV��RGBת�� \n
����֧�ֲ�������colorkey��alpha��ROP��colorkey+ROP\

\param[in] SrcSurface Դsurface���
\param[in] pSrcRect ���Ƶ�Դ����Ϊ�ձ�ʾ����Դsurface����
\param[in] DstSurface Ŀ��surface���
\param[in] pDstRect ���Ƶ�Ŀ������Ϊ�ձ�ʾ����Ŀ��surface����
\param[in] pBlitOpt ��Ϸ�ʽ������Ϊ��ʹ��Ĭ�ϲ�������

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
��
*/
HI_S32 HI_GO_BitBlit (HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                       HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                       const HIGO_BLTOPT2_S* pBlitOpt);

/** 
\brief λ����ƣ��ڰ��ƹ����У�����ʵ��ɫ�ʿռ�ת��, ����
\attention \n
ɫ�ʿռ�ת����֧��YUV��RGBת�� \n
����֧�ֲ�������colorkey��alpha��ROP��colorkey+ROP\

\param[in] SrcSurface Դsurface���
\param[in] pSrcRect ���Ƶ�Դ����Ϊ�ձ�ʾ����Դsurface����
\param[in] DstSurface Ŀ��surface���
\param[in] pDstRect ���Ƶ�Ŀ������Ϊ�ձ�ʾ����Ŀ��surface����
\param[in] pBlitOpt ��Ϸ�ʽ,����Ϊ��ʹ��Ĭ�ϲ�������

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
��
*/
HI_S32 HI_GO_StretchBlit (HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                       HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                       const HIGO_BLTOPT2_S* pBlitOpt);


/**
\brief ����ģʽ���
\attention \n
\param[in] SrcSurface Դsurface���
\param[in] pSrcRect ���Ƶ�Դ����Ϊ�ձ�ʾ����Դsurface����
\param[in] DstSurface Ŀ��surface���
\param[in] pDstRect ���Ƶ�Ŀ������Ϊ�ձ�ʾ����Ŀ��surface����
\param[in] pParOpt ��Ϸ�ʽ,����Ϊ��ʹ��Ĭ�ϲ�������

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
��
*/
HI_S32 HI_GO_PatternBlit(HI_HANDLE SrcSurface, const HI_RECT* pSrcRect, 
                              HI_HANDLE DstSurface, const HI_RECT * pDstRect, 
                              const HIGO_BLTOPT2_S* pParOpt);


/**
\brief ����˸���ƣ�����ӿ����ڵڶ��ο���˸��
\attention \n
��������õ��ýӿ�
1 ��ͼ����Զ�����˸Ч�����Ǻܺ�ʱ������ʹ������ӿ�����һ�Ρ�
2 ��ͼ���bufferģʽ�ǵ�bufferģʽ(HIGO_LAYER_BUFFER_SINGLE)ʱ���û���Ҫ�Լ�������˸
��Դ��Ŀ���С��ͬ��ʱ���Զ��������š�

\param[in] SrcSurface Դsurface���
\param[in] pSrcRect ���Ƶ�Դ����Ϊ�ձ�ʾ����Դsurface����
\param[in] DstSurface Ŀ��surface���
\param[in] pDstRect ���Ƶ�Ŀ������Ϊ�ձ�ʾ����Ŀ��surface����
\param[in] pDefOpt ����˸����ѡ�Ϊ�ձ�ʾAUTO ����

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
��
*/
HI_S32 HI_GO_DeflickerBlit(HI_HANDLE SrcSurface, const HI_RECT* pSrcRect, 
                                 HI_HANDLE DstSurface, const HI_RECT * pDstRect, 
                                 const HIGO_DEFLICKEROPT_S* pDefOpt);


/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_BLITER_H__ */
