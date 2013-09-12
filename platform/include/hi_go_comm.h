/**
 \file
 \brief HiGo��������ͷ�ļ�
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author s37678
 \date 2008-5-16
 */

#ifndef __HI_GO_COMM_H__
#define __HI_GO_COMM_H__

/* add include here */
#include "hi_type.h"
#include "hi_go_errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_2 */
/** @{ */  /** <!-- ��HiGo�������ݡ� */

/** ��ɫ�������ɫ�� */
#define MAX_PALETTE_COLOR_SIZE 256

/** ��ɫֵ */
typedef HI_U32 HI_COLOR;

/** ��ɫ�� */
typedef HI_COLOR HI_PALETTE[MAX_PALETTE_COLOR_SIZE];

typedef enum 
{
    HIGO_IMGTYPE_JPEG = 0, /**< JPEG��ʽͼƬ*/
    HIGO_IMGTYPE_GIF,      /**< GIF��ʽͼƬ*/
    HIGO_IMGTYPE_BMP,      /**< BMP��ʽͼƬ */
    HIGO_IMGTYPE_PNG,      /**< PNG��ʽͼƬ */
    HIGO_IMGTPYE_BUTT
} HIGO_IMGTYPE_E;


/** ���� */
typedef struct
{
    HI_S32 x, y;

    HI_S32 w, h;
} HI_RECT;

/** ���� */
typedef struct
{
    HI_S32 l;
    HI_S32 t;
    HI_S32 r;
    HI_S32 b;
} HI_REGION;


#define HIGO_INVALID_HANDLE 0x0

/** ��ʽλ��*/


/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_2 */
/** @{ */  /** <!-- ��HiGo�������ݡ� */

/** 
\brief HiGo��ʼ��
\attention \n
ʹ��HiGo���ܱ����ȵ��øýӿڣ����HiGo�ĳ�ʼ������Ҫ����gdev, decoder, winc, blit, surfaceģ��
\param ��

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_INITFAILED

\see \n
::HI_GO_Deinit
*/
HI_S32	HI_GO_Init(HI_VOID);

/** 
\brief HiGoȥ��ʼ��
\attention \n
����ʹ��HiGo����ʱ��Ҫ���øýӿڣ��ͷ���Դ
\param ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_Init
*/
HI_S32	HI_GO_Deinit(HI_VOID);


/** 
\brief HiGo ��չ���ʼ��
\attention \n
����ʹ��HiGo��չ�⹦��ʱ��Ҫ���øýӿڣ��ͷ���Դ����Ҫ��CURSOR��TEXTģ�顣
\param ��

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_DeInitExt
*/
HI_S32 HI_GO_InitExt();

/** 
\brief HiGo��չ��ȥ��ʼ��
\attention \n
����ʹ��HiGo����ʱ��Ҫ���øýӿڣ��ͷ���Դ
\param ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_InitExt
*/
HI_S32 HI_GO_DeInitExt();

/** 
\brief ��ȡ�汾��Ϣ
\attention \n
��
\param[out] ppVersion  �汾��Ϣ�ַ��������ַ������Ϊ��
\param[out] ppBuildTime Buildʱ���ַ��������ַ������Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR

\see \n
��
*/
HI_S32 HI_GO_GetVersion(HI_CHAR ** ppVersion, HI_CHAR **ppBuildTime);

/** 
\brief ��Surface�е�����ת����BMP��ʽͼ�������
\attention \n
����ļ���Ϊ[year]-[date]-[hour]-[min]-[second]-[ms].bmp
���ͼƬ�̶�Ϊ16λͼ��
����ʹ��HI_GO_EncodeToFile�ӿ�������˽ӿ�

\param[in] Surface��Ҫ���н��������ݡ�
\param[in] pRect����ָ��,Ϊ�ձ�ʾ����surface��


\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVSURFACEPF
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NOMEM

*/
HI_S32	HI_GO_Surface2Bmp(HI_HANDLE Surface, const HI_RECT *pRect);

/** 
\brief ʹ���ڴ����ģ��
\attention \n
Ĭ��������ڷ�ʹ��״̬��ֻ�иýӿڴ򿪺����ʹ���ڴ�ͳ�ƹ���

\param[in] bEnable�Ƿ����ڴ�ͳ�ƹ���

\retval ::HI_SUCCESS

*/
HI_S32 HI_GO_EnableMemMng(HI_BOOL bEnable);

/** 
\brief ��ȡ�ڴ����ģ��ʹ��״̬
\attention \n
\param[out] pbEnable ��ȡ�ڴ�ͳ�ƹ����Ƿ���

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR

*/
HI_S32 HI_GO_GetMemMngStatus(HI_BOOL *pbEnable);

/** 
\brief ���ϵͳ�ڴ��������Ϣ
\attention \n
\param ��

\retval ::HI_SUCCESS
*/
HI_S32 HI_GO_SysMemQuene(HI_VOID);

/** 
\brief ���MMZ�ڴ��������Ϣ��
\attention \n
\param ��

\retval ::HI_SUCCESS

*/
HI_S32 HI_GO_MMZMemQuene(HI_VOID);

/** @} */  /*! <!-- API declaration end */


#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_COMM_H__ */
