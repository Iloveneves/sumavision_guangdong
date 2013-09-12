/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_vo.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/16
  Description   :
  History       :
  1.Date        : 2009/12/16
    Author      : w58735
    Modification: Created file

*******************************************************************************/
/** 
 * \file
 * \brief �ṩVO�������Ϣ
 */
 
#ifndef  __HI_UNF_VO_H__
#define  __HI_UNF_VO_H__

#include "hi_unf_common.h"
#include "hi_unf_vi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_7 */
/** @{ */  /** <!-- ��VO�� */


/**����VOö��*/
typedef enum hiUNF_VO_E
{
    HI_UNF_VO_SD0   = 0x0,  /**< ������Ƶ��0 */
    HI_UNF_VO_HD0,          /**< ������Ƶ��0 */
    HI_UNF_VO_BUTT
}HI_UNF_VO_E;

/**����WINDOW����*/
typedef struct hiUNF_WINDOW_ATTR_S
{
    HI_UNF_VO_E               enVo;          /**< �������ڵ���Ƶ�� */
    HI_BOOL                   bVirtual;      /**< �Ƿ�Ϊ���ⴰ�� */
    HI_UNF_VIDEO_FORMAT_E     enVideoFormat; /**< ���ⴰ�����ݸ�ʽ */
    HI_UNF_ASPECT_RATIO_E     enAspectRatio; /**< ���ڵĿ��ת������ */
    HI_UNF_ASPECT_CVRS_E      enAspectCvrs;  /**< ���ڵĿ��ת����ʽ */
    HI_RECT_S                 stInputRect;   /**< ���ڵĲü����� */
    HI_RECT_S                 stOutputRect;  /**< ��������Ƶ���ϵ���ʾ���� */
} HI_UNF_WINDOW_ATTR_S;

typedef struct hiUNF_BUFFER_ATTR_S
{
    HI_S32              s32Stride;
    HI_U32              u32PhyAddr[16];
    HI_U32              u32BuffIndex[16];
    HI_S32              s32BuffNum;
}HI_UNF_BUFFER_ATTR_S;

/**VO�豸������ģʽ */
typedef enum hiUNF_VO_DEV_MODE_E
{
    HI_UNF_VO_DEV_MODE_NORMAL,  /**< ����ģʽ��ֻ�ܴ���2��WINDOW */
    HI_UNF_VO_DEV_MODE_MOSAIC,  /**< ������ģʽ�����Դ������WINDOW */
    HI_UNF_VO_DEV_MODE_BUTT
} HI_UNF_VO_DEV_MODE_E;

/**����Freezeģʽö��*/
typedef enum hiUNF_WINDOW_FREEZE_MODE_E
{
    HI_UNF_WINDOW_FREEZE_MODE_LAST = 0,   /**< freezeʱ��ʾ���һ֡*/
    HI_UNF_WINDOW_FREEZE_MODE_BLACK = 1,  /**< freezeʱ��ʾ�����*/
    HI_UNF_WINDOW_FREEZE_MODE_BUTT
} HI_UNF_WINDOW_FREEZE_MODE_E;
/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_5 */
/** @{ */  /** <!-- ��VO�� */

/**
\brief ��ʼ��VOģ��
\attention \n
����VOģ��Ҫ�����ȵ��ñ��ӿ�
\param[in]   enDevMode  VOģ�������ģʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_DEV_NOT_EXIST   VO�豸������
\retval ::HI_ERR_VO_NOT_DEV_FILE    VO���豸
\retval ::HI_ERR_VO_DEV_OPEN_ERR    VO��ʧ��
\retval ::HI_ERR_VO_INVALID_PARA    ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_VO_Init(HI_UNF_VO_DEV_MODE_E enDevMode);

/**
\brief ȥ��ʼ��VOģ��
\attention \n
�ڵ���::HI_UNF_VO_Close�ӿڹر����д򿪵�VO����ñ��ӿ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_DEV_CLOSE_ERR  VO�ر�ʧ��
\see \n
��
*/
HI_S32 HI_UNF_VO_DeInit(HI_VOID);

/**
\brief ��ָ��VO
\attention \n
��
\param[in] enVo    VO���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_VO_CREATE_ERR    ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_VO_Open(HI_UNF_VO_E enVo);

/**
\brief �ر�ָ��VO
\attention \n
��
\param[in] enVo  VO���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_VO_Close(HI_UNF_VO_E enVo);




/**
\brief ����ָ��VO��ALPHA
\attention \n
��
\param[in] enVo         VO���
\param[in] u32Alpha     ��Ƶͼ����ʾ͸����ֵ��ȡֵ��ΧΪ0��255��ȡֵΪ0ʱ��ȫ͸����ȡֵΪ255ʱ����͸��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_VO_SetAlpha(HI_UNF_VO_E enVo, HI_U32 u32Alpha);

/**
\brief ��ȡָ��vo��ALPHA
\attention \n
��
\param[in]  enVo        VO���
\param[out] pu32Alpha   ָ�����ͣ���Ƶͼ����ʾ͸����ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR      ����ָ��Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_VO_GetAlpha(HI_UNF_VO_E enVo, HI_U32 *pu32Alpha);

/**
\brief ����ָ��VO��rect
\attention \n
ֻ����VO������MOSAICģʽ���ܵ��ñ��ӿ�
\param[in] enVo      VO���
\param[in] pstRect   rect�Ľṹָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_VO_SetRect(HI_UNF_VO_E enVo, const HI_RECT_S *pstRect);


/**
\brief ��ȡָ��VO��rect
\attention \n
ֻ����VO������MOSAICģʽ���ܵ��ñ��ӿ�
\param[in] enVo      VO���
\param[in] pstRect   rect�Ľṹָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_VO_GetRect(HI_UNF_VO_E enVo, HI_RECT_S *pstRect);

/**
\brief ����WINDOW
\attention \n
ֻ�д�VO�󣬲�������֮�ϴ���WINDOW
\param[in] pWinAttr   WINDO���Խṹָ��
\param[in] phWindow   ������WINDOW���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_CREATE_ERR     ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_VO_CreateWindow(const HI_UNF_WINDOW_ATTR_S *pWinAttr, HI_HANDLE *phWindow);

/**
\brief ����WINDOW
\attention \n
��
\param[in] hWindow     WINDOW���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_DestroyWindow(HI_HANDLE hWindow);


/**
\brief ʹ��/��ֹWINDOW
\attention \n
ֻ���Ƚ�AVPLAY��VIDͨ��stop�󣬲��ܽ�ֹwindow�������������ݵ����
\param[in] hWindow     WINDOW���
\param[in] bEnable     ʹ��/��ֹ��־
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_SetWindowEnable(HI_HANDLE hWindow, HI_BOOL bEnable);

/**
\brief ��ȡWINDOW��ʹ��״̬
\attention \n
��
\param[in] hWindow     WINDOW���
\param[in] pbEnable    ʹ��/��ָֹ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_GetWindowEnable(HI_HANDLE hWindow, HI_BOOL *pbEnable);

/**
\brief ����WINDOW����
\attention \n
enVo��bVirtual����һ��������Ͳ����ٽ����޸ġ�
\param[in] hWindow    WINDOW���
\param[in] pWinAttr   WINDO���Խṹָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_SetWindowAttr(HI_HANDLE hWindow, const HI_UNF_WINDOW_ATTR_S *pWinAttr);

/**
\brief ��ȡWINDOW����
\attention \n
��
\param[in] hWindow     WINDOW���
\param[in] pWinAttr    WINDO���Խṹָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_GetWindowAttr(HI_HANDLE hWindow, HI_UNF_WINDOW_ATTR_S *pWinAttr);

/**
\brief ��ȡWINDOW��Frame��Ϣ��ר������3Dͼ�β���
\attention \n
��
\param[in] hWindow     WINDOW���
\param[out] pstFrameinfo Frame��Ϣ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_AcquireFrame(HI_HANDLE hWindow, HI_UNF_VO_FRAMEINFO_S *pstFrameinfo);

/**
\brief �ͷ��û���ȡWINDOW��Frame��ר������3Dͼ�β���
\attention \n
��
\param[in] hWindow     WINDOW���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_ReleaseFrame(HI_HANDLE hWindow);

/**
\brief ����WINDOW��Z��
\attention \n
��
\param[in] hWindow    WINDOW���
\param[in] enZFlag    Z����ڷ�ʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_SetWindowZorder(HI_HANDLE hWindow, HI_LAYER_ZORDER_E enZFlag);

/**
\brief ��ȡWINDOW��Z��
\attention \n
��
\param[in] hWindow       WINDOW���
\param[in] pu32Zorder    Z����ֵ����ֵԽ�����ȼ�Խ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_GetWindowZorder(HI_HANDLE hWindow, HI_U32 *pu32Zorder);

/**
\brief ��WINDOW��ָ����AVPLAY/VI��
\attention \n
���Խ�AVPLAY��VI�ľ���󶨵�WINDOW�ϡ�
\param[in] hWindow      WINDOW���
\param[in] hSrc         ����Դ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_AttachWindow(HI_HANDLE hWindow, HI_HANDLE hSrc);


/**
\brief ��WINDOW��ָ����AVPLAY/VI���
\attention \n
��
\param[in] hWindow     WINDOW���
\param[in] hSrc        ����Դ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_DetachWindow(HI_HANDLE hWindow, HI_HANDLE hSrc);

/**
\brief ����Winsow�Ĳ�������
\attention \n
�˹��������ڲ��Ź����иı䲥������
\param[in] hWindow           WINDOW���
\param[in] u32WinRatio      ȡֵ��ΧΪ [16, 4096]��256���������ٶȲ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_SetWindowRatio(HI_HANDLE hWindow, HI_U32 u32WinRatio);


/**
\brief ����WINDOW����ʾ����
\attention \n
�˹��������ڲ��Ź����ж�����Ļ��ʾ���ݣ���ʱWINDOW�е��������������У�\n
���ȡ������󣬻�������ʾ���µ����ݡ�
\param[in] hWindow           WINDOW���
\param[in] bEnable           ʹ��/��ֹ��־
\param[in] enWinFreezeMode   ����ķ�ʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_FreezeWindow(HI_HANDLE hWindow, HI_BOOL bEnable, HI_UNF_WINDOW_FREEZE_MODE_E enWinFreezeMode);


/**
\brief ����WINDOW�ĵ�ǰ֡
\attention \n
ֻ����WINDOW��ʾ���ݲ��ٱ仯����ñ��ӿڲ������塣����Freeze����ֹͣAV���š�
\param[in] hWindow           WINDOW���
\param[in] pstCapPicture
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_CapturePicture(HI_HANDLE hWindow, HI_UNF_CAPTURE_PICTURE_S *pstCapPicture);

/**
\brief ��λWINDOW
\attention \n
�˹������window�еĻ��壬���ݲ�����ʾ��֡�����һ֡��
\param[in] hWindow           WINDOW���
\param[in] enWinFreezeMode   ��λ�ķ�ʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_ResetWindow(HI_HANDLE hWindow, HI_UNF_WINDOW_FREEZE_MODE_E enWinFreezeMode);

/**
\brief ��WINDOW�����û��ⲿ�����buffer��ר������3Dͼ�β���
\attention \n
��
\param[in] hWindow     WINDOW���
\param[in] pstBufAttr  �ⲿ��buffer
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_AttachExternBuffer(HI_HANDLE hWindow,HI_UNF_BUFFER_ATTR_S* pstBufAttr);

/**
\brief ����WINDOW�Ƿ����ڿ������ģʽ���������ģʽǿ�ƹر�ȥ�����㷨�ر�
\attention \n
��
\param[in] hWindow     WINDOW���
\param[in] bQuickOutputEnable  �������ģʽʹ��/��ֹ��־
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VO_NO_INIT    DISPδ��ʼ��
\retval ::HI_ERR_VO_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_VO_NULL_PTR       ����ָ��Ϊ��
\retval ::HI_ERR_VO_INVALID_OPT    �����Ƿ�
\retval ::HI_ERR_VO_WIN_NOT_EXIST  ���ڲ�����
\see \n
��
*/
HI_S32 HI_UNF_VO_SetQuickOutputEnable(HI_HANDLE hWindow, HI_BOOL bQuickOutputEnable);

/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif
