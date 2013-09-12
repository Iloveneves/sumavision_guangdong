/**
 \file
 \brief Surfaceģ��ͷ�ļ�
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author s37678
 \date 2008-5-13
 */

#ifndef __HI_GO_SURFACE_H__
#define __HI_GO_SURFACE_H__

#include "hi_go_comm.h"
#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
/** \addtogroup      H_3_3 */
/** @{ */  /** <!-- ��Surfaceģ������롿 */

typedef enum
{
    HIGO_PF_CLUT8 = 0,  /**< ��ɫ�� */
    HIGO_PF_CLUT1,
    HIGO_PF_CLUT4,
    HIGO_PF_4444,       /**< һ������ռ16bit��ARGBÿ����ռ4bit������ַ�ɸ��������� */
    HIGO_PF_0444,       /**< һ������ռ16bit��ARGBÿ����ռ4bit������ַ�ɸ���������, A������������ */

    HIGO_PF_1555,       /**< һ������ռ16bit��RGBÿ����ռ5bit��A����1bit������ַ�ɸ��������� */
    HIGO_PF_0555,       /**< һ������ռ16bit��RGBÿ����ռ5bit��A����1bit������ַ�ɸ���������, A������������ */
    HIGO_PF_565,        /**< һ������ռ16bit��RGBÿ�����ֱ�ռ5bit��6bit��5bit������ַ�ɸ��������� */
    HIGO_PF_8565,       /**< һ������ռ24bit��ARGBÿ�����ֱ�ռ8bit, 5bit��6bit��5bit������ַ�ɸ��������� */
    HIGO_PF_8888,       /**< һ������ռ32bit��ARGBÿ����ռ8bit������ַ�ɸ��������� */
    HIGO_PF_0888,       /**< һ������ռ24bit��ARGBÿ����ռ8bit������ַ�ɸ��������У�A������������ */

    HIGO_PF_YUV400,     /**< ��˼�����semi-planar YUV 400��ʽ */    
    HIGO_PF_YUV420,     /**< ��˼�����semi-planar YUV 420��ʽ */
    HIGO_PF_YUV422,     /**< ��˼�����semi-planar YUV 422��ʽ  ˮƽ������ʽ*/
    HIGO_PF_YUV422_V,   /**< ��˼�����semi-planar YUV 422��ʽ  ��ֱ������ʽ*/    
    HIGO_PF_YUV444,     /**< ��˼�����semi-planar YUV 444��ʽ */
    
	HIGO_PF_A1, 
	HIGO_PF_A8,
        
    HIGO_PF_YUV888,
    HIGO_PF_YUV8888,

    HIGO_PF_BUTT
} HIGO_PF_E;
/** @} */  /*! <!-- Macro Definition end */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_7 */
/** @{ */  /** <!-- ��Surface�� */
/** �������� */
typedef enum
{
    HIGO_PDFORMAT_RGB = 0,
    HIGO_PDFORMAT_RGB_PM,   /**< pre-multiplied */
    HIGO_PDFORMAT_Y,
    HIGO_PDFORMAT_UV,
    HIGO_PDFORMAT_UV_LE,    

    HIGO_PDFORMAT_BUTT
} HIGO_PDFORMAT_E;

typedef struct
{
    HIGO_PDFORMAT_E Format;     /**< �������� */
    HI_VOID*        pData;      /**< ���������ַָ�� */
    HI_VOID*        pPhyData;   /**< ���������ַָ�� */    
    HI_U32          Pitch;      /**< �����п� */
    HI_U32          Bpp;        /**< bytes per pixel */
    HI_U32          Offset;
} HIGO_PIXELDATA_S;


/** ������ݷ����� */
#define MAX_PARTPIXELDATA 3


/**����ͬ��ģʽ�������ʹ�ã����Զ�ͬ����ʽ���� */
typedef enum 
{
    HIGO_SYNC_MODE_CPU = 0x01, /*ͬ������һ����Ҫ����CPU����*/
    HIGO_SYNC_MODE_TDE = 0x02, /*ͬ������һ����Ҫ����2D���ٲ���*/
    HIGO_SYNC_MODE_BUTT,
} HIGO_SYNC_MODE_E;


typedef enum
{
    HIGO_MEMTYPE_MMZ = 0,       /**< ʹ��MMZ�ڴ���д��� */
    HIGO_MEMTYPE_OS,            /**< ʹ��ϵͳ�ڴ���д��� */
    HIGO_MEMTYPE_BUTT
}HIGO_MEMTYPE_E;

typedef enum 
{
	HIGO_OWNER_USER = 0,        /**< ���û����й�����Ҫ�û����з����ڴ棬�����ڴ� */
	HIGO_OWNER_HIGO,            /**< ��HIGO���й����û�����Ҫ�����ڴ� */
	HIGO_OWNER_BUTT
}HIGO_OWNER_E;

typedef struct
{
    HI_S32 Width;                               /**< surface��� */
    HI_S32 Height;                              /**< surface�߶� */
    HIGO_PF_E PixelFormat;                      /**< surface���ظ�ʽ*/
    HI_U32   Pitch[MAX_PARTPIXELDATA];          /**< surface�м����*/
    HI_CHAR* pPhyAddr[MAX_PARTPIXELDATA];       /**< surface�����ַ*/
    HI_CHAR* pVirAddr[MAX_PARTPIXELDATA];       /**< surface�����ַ*/
    HIGO_MEMTYPE_E MemType;                     /**< surface�ڴ�����*/
}HIGO_SURINFO_S;

typedef struct
{
    HI_S32 Width;                               /**< surface��� */
    HI_S32 Height;                              /**< surface�߶� */
    HIGO_PF_E PixelFormat;                      /**< surface���ظ�ʽ*/
    HI_U32   Pitch[MAX_PARTPIXELDATA];          /**< surface�м���룬
                                                     Pitch[0]��ʾRGB��ʽ�м�࣬ ����Semi-planner��Y�������м��
                                                     Pitch[1]��ʾSemi-planner��C�������м��
                                                     Pitch[2]��ʱ��ʹ�á�
                                                     */
    HI_CHAR* pPhyAddr[MAX_PARTPIXELDATA];       /**< surface�����ַ
                                                     pPhyAddr[0]��ʾRGB��ʽ�����ַ�� ����Semi-planner��Y�����������ַ
                                                     pPhyAddr[1]��ʾSemi-planner��C�����������ַ
                                                */
    HI_CHAR* pVirAddr[MAX_PARTPIXELDATA];       /**< surface�����ַ
                                                     pVirAddr[0]��ʾRGB��ʽ�����ַ�� ����Semi-planner��Y�����������ַ
                                                     pVirAddr[1]��ʾSemi-planner��C�����������ַ
                                                */
    HIGO_MEMTYPE_E MemType;                     /**< surface�ڴ�����*/
    HIGO_OWNER_E   MemOwner;                    /**< �ڴ����Դ,�������û�����,����HIGO����*/
}HIGO_SURINFOEX_S;

/** ���ݷ����ṹ */
typedef HIGO_PIXELDATA_S HI_PIXELDATA[MAX_PARTPIXELDATA];

/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_7 */
/** @{ */  /** <!-- ��surface�� */

/** 
\brief ��ʼ��Surface
\attention \n
::HI_GO_Init�Ѿ������Ըýӿڵĵ���
\param ��

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_GO_DeinitSurface
*/
HI_S32 HI_GO_InitSurface(HI_VOID);

/** 
\brief ȥ��ʼ��Surface
\attention \n
::HI_GO_Deinit�Ѿ������Ըýӿڵĵ���
\param ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_InitSurface
*/
HI_S32 HI_GO_DeinitSurface(HI_VOID);

/** 
\brief ����surface��alphaֵ
\attention \n
��
\param[in]  Surface Surface���
\param[in]  Alpha Alphaֵ����Χ��0-255��0��ʾ͸����255��ʾ��͸��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_GetSurfaceAlpha
*/
HI_S32 HI_GO_SetSurfaceAlpha(HI_HANDLE Surface, HI_U8 Alpha);

/** 
\brief ��ȡsurface��alphaֵ
\attention \n
��
\param[in]  Surface Surface���
\param[out] pAlpha ����alhpaֵ�Ŀռ�ָ�룬����Ϊ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
::HI_GO_SetSurfaceAlpha
*/
HI_S32 HI_GO_GetSurfaceAlpha(HI_HANDLE Surface, HI_U8* pAlpha);

/** 
\brief �����Ƿ�ʹ��surface��colorkey
\attention \n
��
\param[in] Surface Surface���
\param[in] Enable �Ƿ�ʹ��colorKey��HI_TRUE��ʹ�ܣ�HI_FALSE����ʹ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_EnableSurfaceColorKey(HI_HANDLE Surface, HI_BOOL Enable);

/** 
\brief ����surface��colorKeyֵ
\attention \n
��
\param[in] Surface Surface���
\param[in] ColorKey Colorkeyֵ, �����RGB��ʽ��ʹ��ȫ������32bit��������䣬�����CLUT��ʽ��ʹ����ɫ��������䡣

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_GetSurfaceColorKey
*/
HI_S32 HI_GO_SetSurfaceColorKey(HI_HANDLE Surface, HI_COLOR ColorKey);

/** 
\brief ��ȡsurface��colorkeyֵ
\attention \n
��
\param[in]  Surface Surface���
\param[out] pColorKey ����colorkeyֵ�Ŀռ�ָ�룬����Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_NOCOLORKEY

\see \n
::HI_GO_SetSurfaceColorKey
*/
HI_S32 HI_GO_GetSurfaceColorKey(HI_HANDLE Surface, HI_COLOR* pColorKey);

/** 
\brief ����Surface�ĵ�ɫ��
\attention \n
��
\param[in] Surface Surface���
\param[in] Palette ��ɫ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVSURFACEPF

\see \n
::HI_GO_GetSurfaceColorKey
*/
HI_S32 HI_GO_SetSurfacePalette(HI_HANDLE Surface, const HI_PALETTE Palette);

/** 
\brief ��ȡsurface�ĵ�ɫ��
\attention \n
��
\param[in]  Surface Surface���
\param[out] Palette ���յ�ɫ��Ŀռ�ָ�� 

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVSURFACEPF

\see \n
::HI_GO_SetSurfacePalette
*/
HI_S32 HI_GO_GetSurfacePalette(HI_HANDLE Surface, HI_PALETTE Palette);

/** 
\brief ����surface����ȡ���ڴ�ָ��
\attention \n
����surface����ǰ��Ҫ���øýӿ�����surface \n
���ܶ�ͬһsurface�ظ�����
\param[in] Surface Surface���
\param[out] pData ���ڴ������ص����ظ�ʽ��Ϣ
\param[in] bSync  �Ƿ�ͬ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_LOCKED

\see \n
::HI_GO_UnlockSurface
*/
HI_S32 HI_GO_LockSurface(HI_HANDLE Surface, HI_PIXELDATA pData, HI_BOOL bSync);


/** 
\brief ������surface
\attention \n
��surface���ݷ��ʽ�����Ҫ��ʱ���øýӿڽ�����surface
\param[in] Surface Surface���

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NOTLOCKED

\see \n
::HI_GO_LockSurface
*/
HI_S32 HI_GO_UnlockSurface(HI_HANDLE Surface);

/** 
\brief ��ȡsurface�ߴ�
\attention \n
pWidth��pHeight����ͬʱΪ��
\param[in]  Surface Surface���
\param[out]  pWidth Surface��������ַ������Ϊ��
\param[out]  pHeight Surface�߶������ַ������Ϊ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR 

\see \n
��
*/
HI_S32 HI_GO_GetSurfaceSize(HI_HANDLE Surface, HI_S32* pWidth, HI_S32* pHeight);

/** 
\brief ��ȡsurface���ظ�ʽ
\attention \n
��
\param[in]  Surface Surface���
\param[out] pPixelFormat ���ظ�ʽ�����ַ������Ϊ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
��
*/
HI_S32 HI_GO_GetSurfacePixelFormat(HI_HANDLE Surface, HIGO_PF_E* pPixelFormat);

/** 
\brief ���û����ڴ��װ��surface
\attention \n
pSurInfo�������Զ�����������ȷ,֧����������ظ�ʽΪRGB��ʽ��clut8��ʽ���Լ�YUV semi-planner��ʽ��

\param[in]  pSurInfo �û��ڴ���Ϣ������Ϊ��
\param[out] pSurface �����Ϣ������Ϊ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVSURFACEPF
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NOMEM

\see \n
��
*/
HI_S32 HI_GO_CreateSurfaceFromMem(const HIGO_SURINFO_S *pSurInfo, HI_HANDLE * pSurface);

/** 
\brief �����ڴ�surface
\attention \n
���ܴ���::HIGO_PF_CLUT1��::HIGO_PF_CLUT4��::HIGO_PF_YUV420��::HIGO_PF_YUV422��ʽ��surface

\param[in] Width Surface���
\param[in] Height Surface�߶�
\param[in] PixelFormat Surface���ظ�ʽ
\param[out] pSurface Surface���

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVSURFACEPF
\retval ::HIGO_ERR_NOMEM

\see \n
::HI_GO_FreeSurface
*/
HI_S32 HI_GO_CreateSurface(HI_S32 Width, HI_S32 Height, HIGO_PF_E PixelFormat, HI_HANDLE* pSurface);

/** 
\brief ������surface����surface���丸surface����ͬһ���ڴ�
\attention \n
��

\param[in] Surface ��surface���
\param[in] pRect ��surface�ڸ�surface�е����򣬲���Ϊ��
\param[out] pSubSurface ��surface���������Ϊ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_NOMEM

\see \n
::HI_GO_FreeSurface
*/
HI_S32 HI_GO_CreateSubSurface(HI_HANDLE Surface, const HI_RECT *pRect, HI_HANDLE* pSubSurface);


/** 
\brief ����surface
\attention \n
��
\param[in] Surface Surface���

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INUSE

\see \n
::HI_GO_CreateSurface \n
::HI_GO_DecImgData
*/
HI_S32 HI_GO_FreeSurface(HI_HANDLE Surface);


/**
\brief �������surface�Ļ�ͼ�����Ƿ���Ҫ�Զ�ͬ����
\attention \n
     surface����ʱ��Ĭ�����Զ�ͬ���ġ�ͬ������˼��: ʹ��TDE����֮ǰ����Ҫ��CPU�Ļ�����cache������\n
     ���µ�surface���ڴ��У�ʹ��CPU����֮ǰ����Ҫ��TDE������ɡ�
     �ýӿڶ�����surface�Ĳ�������Ч
     
\param[in] hSurface Surface������ú�������ʱû���õ�
\param[in] bAutoSync �Ƿ��Զ�����

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_EnableSurfaceAutoSync(HI_HANDLE hSurface, HI_BOOL bAutoSync);



/**
\brief ͬ��surface,ͬ���������ڱ�֤CPU��2D����Ӳ�����������Ѿ����µ�surface���ڴ���
\attention \n
�������::HI_GO_EnableSurfaceAutoSync��ֹ�Զ�����������ʹ��TDE��CPU����ʱ�����øú�����֤ͬ����\n
������ƽ�����ȷ��
\param[in] hSurface Surface�������ʱ����
\param[in] mode ͬ��ģʽ���ο�::HIGO_SYNC_MODE_E

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_SyncSurface(HI_HANDLE hSurface, HIGO_SYNC_MODE_E mode);


/**
\brief ����surface�����֣�ͨ������surface���֣������������� cat /proc/higo ���Բ鿴����surface
���ڲ���Ϣ�������ڴ�ռ�ã���ߣ����ظ�ʽ
\attention \n
�����Ϊ16���ַ���������β��'\0'��

\param[in] hSurface surface��� 
\param[in] pName surface���ִ�

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
��
*/
HI_S32 HI_GO_SetSurfaceName(HI_HANDLE hSurface, const HI_CHAR* pName);


/**
\brief ��ȡsurface������
\attention \n
�����Ϊ16���ַ���������β��'\0'��

\param[in] hSurface surface���
\param[in] pNameBuf �������ֵ�buffer
\param[in] BufLen buffer ����

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVPARAM

\see \n
��
*/
HI_S32 HI_GO_GetSurfaceName(HI_HANDLE hSurface,  HI_CHAR* pNameBuf, HI_U32 BufLen);



/** 
\brief ��ȡ�ڴ�����
\attention \n
 
\param[in]  Surface Surface���
\param[out]  pMemType �ڴ�����ָ�룬����Ϊ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR 

\see \n
��
*/
HI_S32 HI_GO_GetSurfaceMemType(HI_HANDLE Surface, HIGO_MEMTYPE_E *pMemType);


/** 
\brief ��ѯ�ڴ�����
\attention \n
 
\param[in]   Surface  surface
\param[out]  pOwner   Owner����ָ�룬����Ϊ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR 

\see \n
��
*/
HI_S32 HI_GO_GetSurfaceOwner(HI_HANDLE Surface, HIGO_OWNER_E *pOwner);

/** 
\brief ����OS�����ڴ�
���߼�����������һ���ڴ����򣨵������ϲ�һ�����������û�ֱ�ӵ���malloc��������򣩣�
�ⲻ�ܱ�Ӳ����ʶ�𣬵���HIGOĳЩ������ǿ��Ա�ʶ��ģ������Ϳ���ĳ�̶ֳ��ϻ���MMZ�ڴ�Ĳ���

\attention \n
 
Ŀǰ����os ���͵�surface�����������µ�ʹ�÷�Χ��
1).�������ţ��޸�ʽת���£�֧����bmp��gif��png���������ʹ��	
2).֧����RGB��ʽ��surface�ı����bmp��ʹ��
3).֧�ֽ�text����������͵�surface
4).MMZ������OS����surface֮���ת������ͨ��HI_GO_Blit���У�����HI_GO_Blit������֧��HIGO_BLTOPT_S ����={0}��
	 ��������Colorkey��ز�������������surface��RGB��ʽ�����blit��������ϲ�����֧�֡�
5).MemOwnerΪHIGO_OWNER_USER��֧�ָ�ʽ����YUV(semi-planner), RGB��CLUT8��ʽ��ʽ������֧��RGB��CLUT8��ʽ��
�������һ����ô����YUV���ֳ��ø�ʽ��surface��
	HI_U32 u32AlignWidth_Y,u32AlignHeight_Y; //Y���������Ĵ�С
	HI_U32 u32AlignWidth_C,u32AlignHeight_C; //UV���������Ĵ�С
	HI_U32 uExpectWidth,uExpectHeight;       //ԭͼƬ�Ĵ�С��������ͼƬ�Ĵ�С
	HIGO_PF_E szPixelFormat;                 //ԭͼƬ�����ظ�ʽ��������ͼƬ�����ظ�ʽ����HIGO_PF_YUV400,HIGO_PF_YUV420,HIGO_PF_YUV422,HIGO_PF_YUV422_V,HIGO_PF_YUV444
	HIGO_SURINFOEX_S SurfaceInfoEx = {0};
    
	SurfaceInfoEx.Width = uExpectWidth;
	SurfaceInfoEx.Height = uExpectHeight;
	SurfaceInfoEx.PixelFormat = szPixelFormat;
	SurfaceInfoEx.MemType = HIGO_MEMTYPE_MMZ;
  	SurfaceInfoEx.MemOwner = HIGO_OWNER_USER;
    	
	SurfaceInfoEx.Pitch[0] = u32AlignWidth_Y;
	SurfaceInfoEx.pPhyAddr[0] = HI_MMZ_New(SurfaceInfoEx.Pitch[0]*u32AlignHeight_Y, 4, NULL, "higoSurface");
	SurfaceInfoEx.pVirAddr[0] = HI_MMZ_Map((HI_U32)SurfaceInfoEx.pPhyAddr[0], 0);
    
	SurfaceInfoEx.Pitch[1] = u32AlignWidth_C;
	SurfaceInfoEx.pPhyAddr[1] = HI_MMZ_New(SurfaceInfoEx.Pitch[1]*u32AlignHeight_C, 4, NULL, "higoSurfaceCbCr");
	SurfaceInfoEx.pVirAddr[1] = HI_MMZ_Map((HI_U32)SurfaceInfoEx.pPhyAddr[1], 0);
	
	ret = HI_GO_CreateSurfaceEx(&SurfaceInfoEx, &picSurface);

---------------------------------------------------------------------------------------
����˵��һ�¸���szPixelFormat˵��u32AlignWidth_Y��u32AlignHeight_Y��u32AlignWidth_C��u32AlignHeight_C��ȡֵ��
1 ) YUV400�����
	u32AlignWidth_Y   = (uExpectWidth + 127) +(~(127));       //��128 byte����
	u32AlignHeight_Y  = (uExpectHeight + 7) + (~(7));	      //��8 byte����
	u32AlignWidth_C   = 0;
	u32AlignHeight_C  = 0;
2 ) YUV420�����
	u32AlignWidth_Y   = (uExpectWidth + 127) +(~(127));       //��128 byte����
	u32AlignHeight_Y  = (uExpectHeight + 15) + (~(15));	      //��16 byte����
	u32AlignWidth_C   = u32AlignWidth_Y;
	u32AlignHeight_C  = u32AlignHeight_Y / 2;
3 ) YUV422�����
	u32AlignWidth_Y   = (uExpectWidth + 127) +(~(127));       //��128 byte����
	u32AlignHeight_Y  = (uExpectHeight + 7) + (~(7));	      //��8 byte����
	u32AlignWidth_C   = u32AlignWidth_Y;
	u32AlignHeight_C  = u32AlignHeight_Y;
4 ) YUV422_V�����
	u32AlignWidth_Y   = (uExpectWidth + 127) +(~(127));       //��128 byte����
	u32AlignHeight_Y  = (uExpectHeight + 15) + (~(15));	      //��16 byte����
	u32AlignWidth_C   = u32AlignWidth_Y * 2;
	u32AlignHeight_C  = u32AlignHeight_Y / 2;
5 ) YUV444�����
	u32AlignWidth_Y   = (uExpectWidth + 127) +(~(127));       //��128 byte����
	u32AlignHeight_Y  = (uExpectHeight + 7) + (~(7));	      //��8 byte����
	u32AlignWidth_C   = u32AlignWidth_Y * 2;
	u32AlignHeight_C  = u32AlignHeight_Y;
\param[in]   pSurInfo      surface��Ϣָ�룬����Ϊ��
\param[out]  pSurface      surfaceָ�룬����Ϊ��

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR 

\see \n
��
*/
HI_S32 HI_GO_CreateSurfaceEx(const HIGO_SURINFOEX_S  *pSurInfo, HI_HANDLE* pSurface);

/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_SURFACE_H__ */
