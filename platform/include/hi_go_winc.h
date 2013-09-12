/**
 \file
 \brief Wincģ��ͷ�ļ�
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author s37678
 \date 2008-8-5
 */

#ifndef __HI_GO_WINC_H__
#define __HI_GO_WINC_H__

#include "hi_type.h"
#include "hi_go_comm.h"
#include "hi_go_surface.h"
#ifdef __cplusplus
extern "C" {
#endif


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_9 */
/** @{ */  /** <!-- ��Wincģ�顿 */

/**����Z�������ʽ*/
typedef enum
{
    HIGO_ZORDER_MOVETOP = 0,  /**<�Ƶ����*/
    HIGO_ZORDER_MOVEUP,       /**<������*/
    HIGO_ZORDER_MOVEBOTTOM,   /**<�Ƶ���ײ�*/
    HIGO_ZORDER_MOVEDOWN,     /**<������*/
    HIGO_ZORDER_BUTT
} HIGO_ZORDER_E;

/**windowʹ��buffer�ķ�ʽ*/
typedef enum
{
    HIGO_BUFFER_SINGLE = 0,  /**<windowʹ�õ�buffer*/
    HIGO_BUFFER_DOUBLE,      /**<windowʹ��˫buffer*/
    HIGO_BUFFER_BUTT
}HIGO_BUFFERTYPE_E;

/** ��󴰿ڲ��� */
#define HIGO_WINTREE_NUM 16

typedef struct
{
    HI_HANDLE hLayer; /**<������ʾ��ͼ��*/
    HI_RECT rect;     /**<���ڵķ�Χ*/
    HI_U32 LayerNum;     /**<������ʾ�ļ���,���Ϊ0-15������Խ��Ĵ���Խ������*/         
    HIGO_PF_E PixelFormat;/**<���ڵ����ظ�ʽ*/
    HIGO_BUFFERTYPE_E BufferType; /**<������Ҫ��surface buffer����������*/ 
} HIGO_WNDINFO_S;
/** @} */  /*! <!-- Structure Definition end */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_9 */
/** @{ */  /** <!-- ��Wincģ�顿 */
/**
\brief ��ָ��ͼ���ϴ�������
\attention \n
�´����Ĵ���ʼ����ָ�����������, ����ʾʱ������ͼ��canvas surface��Χ���ֻᱻ���е���
\param[in] pInfo ���ڴ�������Ϣ���������ظ�ʽֻ֧���������е����ظ�ʽ:
    HIGO_PF_CLUT8
    HIGO_PF_4444
    HIGO_PF_0444
    HIGO_PF_1555
    HIGO_PF_0555
    HIGO_PF_565
    HIGO_PF_8565
    HIGO_PF_8888
    HIGO_PF_0888
    ���д��ڲ��ֻ����0��15�ķ�Χ��(����0��15)����Ŵ�Ĵ�����Զ��ͼ���С������
    
\param[out] pWindow  �洢���ھ���ĵ�ַ������Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVPF

\see \n
::HI_GO_DestroyWindow
*/
HI_S32 HI_GO_CreateWindowEx(const HIGO_WNDINFO_S* pInfo, HI_HANDLE* pWindow);

/**
\brief ��ָ��ͼ���ϴ�������
\attention \n
��ͼ������ظ�ʽ��������alphaʱ�����ڵ�surface����ѡ���Ƿ�ʹ������alpha
\param[in] hLayer  ͼ����
\param[in] pRect ���δ�������Ϊ�ձ�ʾ������������
\param[in] LayerNum ���������Ĳ��,���Ϊ0-15��
\param[in] bHasPixelAlpha �����Ƿ������alpha
\param[out] pWindow  �洢���ھ���ĵ�ַ������Ϊ��
\param[out] eBufferType windwoʹ��surface buffer������

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_DestroyWindow
*/
HI_S32 HI_GO_CreateWindow(HI_HANDLE hLayer, const HI_RECT* pRect,
                          HI_U32 LayerNum, HI_BOOL bHasPixelAlpha,
                          HI_HANDLE* pWindow,HIGO_BUFFERTYPE_E eBufferType);

/**
\brief ���ٴ���
\attention \n
\param[in] Window �����ٴ��ھ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVPARAM

\see \n
::HI_GO_CreateWindow
*/
HI_S32 HI_GO_DestroyWindow(HI_HANDLE Window);

/**
\brief ��ȡ���ھ���
\attention \n
��
\param[in] Window ���ھ��
\param[out] pRect ���ھ��ε�ַ������Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
::HI_GO_SetWindowPos \n
::HI_GO_ResizeWindow
*/
HI_S32 HI_GO_GetWindowRect(HI_HANDLE Window, HI_RECT* pRect);

/**
\brief ���ô����ڰ󶨲��ϵ���ʼλ��
\attention \n
��
\param[in] Window ���ھ��
\param[in] StartX X����
\param[in] StartY Y����

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_GetWindowRect
*/
HI_S32 HI_GO_SetWindowPos(HI_HANDLE Window, HI_S32 StartX, HI_S32 StartY);

/**
\brief �ı䴰�ڴ�С
\attention \n
�ı䴰�ڴ�С�󣬴�����Ҫ�ػ�
\param[in] Window ���ھ��
\param[in] Width ���ڿ��
\param[in] Height ���ڸ߶�

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVSURFACEPF
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_NOMEM

\see \n
::HI_GO_GetWindowRect
*/
HI_S32 HI_GO_ResizeWindow(HI_HANDLE Window, HI_S32 Width, HI_S32 Height);

/**
\brief ��ȡ����Z��z��ֵС�Ĵ��ڱ�ֵ�󴰿ڸ��ǡ�
\attention \n
��
\param[in] Window ���ھ��
\param[out] pZOrder �洢����Z��ĵ�ַ������Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
::HI_GO_ChangeWindowZOrder
*/
HI_S32 HI_GO_GetWindowZOrder(HI_HANDLE Window, HI_U32* pZOrder);

/**
\brief ���Ĵ���Z��
\attention \n
��
\param[in] Window ���ھ��
\param[in] EnType ����Z�������ʽ

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVZORDERTYPE
\retval ::HIGO_ERR_LOCKED

\see \n
::HI_GO_GetWindowZOrder
*/
HI_S32 HI_GO_ChangeWindowZOrder(HI_HANDLE Window, HIGO_ZORDER_E EnType);

/**
\brief ��ȡ���ڿɼ���
\attention \n
��
\param[in] Window ���ھ��
\param[out] pOpacity �洢���ڲ�͸���ȵĵ�ַ������Ϊ�գ�255Ϊ��͸��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_SetWindowOpacity
*/
HI_S32 HI_GO_GetWindowOpacity(HI_HANDLE Window, HI_U8* pOpacity);

/**
\brief ���ô��ڲ�͸����
\attention \n
��
\param[in] Window ���ھ��
\param[in] Opacity ���ڲ�͸���ȣ���ΧΪ0~255, ��Ϊ0ʱ���ô��ڲ��ɼ���255ʱ��������ȫ�ɼ�

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_GetWindowOpacity
*/
HI_S32 HI_GO_SetWindowOpacity(HI_HANDLE Window, HI_U8 Opacity);

/**
\brief ���ô��ڵ�colorkey
\attention \n
\param[in] Window ���ھ��
\param[in] ColorKey Colorkeyֵ

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_LOCKED

\see \n
��
*/
HI_S32 HI_GO_SetWindowColorkey(HI_HANDLE Window, HI_COLOR ColorKey);

/**
\brief ��ȡ���ڵ�surface���
\attention \n
�����˫buffer��window��HI_GO_FlipWindowSurface֮����Ҫ���µ��øýӿڣ�
    �Ӷ���ȡ����һ��buffer���л���

\param[in] Window   ���ھ��
\param[in] pSurface �洢����surface����ĵ�ַ������Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
::HI_GO_FlipWindowSurface \n
*/
HI_S32 HI_GO_GetWindowSurface(HI_HANDLE Window, HI_HANDLE* pSurface);

/**
\brief ˢ�´���
\attention \n
���´���surface����֮����Ҫ���ô˽ӿڲ�����Ч

\param[in] Window ���ھ��
\param[in] pRect ���µĴ�������

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_UpdateWindow(HI_HANDLE Window, const HI_RECT* pRect);


/**
\brief �޸Ĵ�������ͼ�㣬��ɾ������
\attention \n
��
\param[in] hWindow  ���ھ��
\param[in] hNewLayer  ��ͼ����

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/
HI_S32 HI_GO_ChangeWindowLayer(HI_HANDLE hWindow, HI_HANDLE hNewLayer);


/**
\brief �л�window ��surface������double surface��window��Ч
\attention \n
��
\param[in] hWindow  ���ھ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
��
*/

HI_S32 HI_GO_FlipWindowSurface(HI_HANDLE hWindow);
    
/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_WINC_H__ */
