#ifndef _HI_GO_CURSOR_H
#define _HI_GO_CURSOR_H

#include "hi_go_comm.h"
#include "hi_go_gdev.h"
#ifdef __cplusplus
extern "C" {
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_3 */
/** @{ */  /** <!-- ��CURSOR�� */

typedef struct
{
    HI_HANDLE hCursor;    /**< ���ͼƬ���128*128,��С16*16����, 
                               ֧������alpha��colorkey */
    HI_U32    HotspotX;   /**< ����ȵ�X���꣬�����ͼƬ */
    HI_U32    HotspotY;   /**< ����ȵ�Y���꣬�����ͼƬ */
} HIGO_CURSOR_INFO_S;

/** ����״̬�ṹ */
typedef struct 
{
    HI_BOOL bShow;             /**< �����Ƿ���ʾ */
} HIGO_CURSOR_STATUS_S;
/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_3 */
/** @{ */  /** <!-- ��CURSOR�� */
/**
\brief ����ʼ��
\attention \n

\param ��

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_INITFAILED
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_DeinitCursor
*/

HI_S32 HI_GO_InitCursor();

/**
\brief ȥ��ʼ������ʼ��
\attention \n

\param ��

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_InitCursor
*/

HI_S32 HI_GO_DeinitCursor();

/**
\brief ��ʾ���
\attention \n
1 �����Ĺ��λ��Ĭ������Ļ�м�
2.show����ʱ����Ҫ�������ù�����Ϣ��
\param[in] bVisible ����ɼ�״̬�� HI_TRUE:�ɼ��� HI_FASLE:���㲻�ɼ���

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NOCURSORINF
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_GetCursorStatus
::HI_GO_SetCursorInfo
*/
HI_S32 HI_GO_ShowCursor(HI_BOOL bVisible);

/** 
\brief ��ȡ���㵱ǰ״̬
\attention \n
��

\param[out] pCursorStatus ���㵱ǰ״̬�ṹָ�룬����Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_ShowLayer
*/
HI_S32 HI_GO_GetCursorStatus( HIGO_CURSOR_STATUS_S* pCursorStatus);


/**
\brief �ƶ���굽ָ����Ļָ��λ��
\attention \n
������cursorΪshow������²��ܸı���λ��

\param[in] x ��ĻX����,��λ����, �����ͼ��canvas surface
\param[in] y ��ĻY����,��λ����, �����ͼ��canvas surface

\retval ::HIGO_ERR_NOTINIT
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_SetCursorPos(HI_S32 x, HI_S32 y);

/**
\brief ȡ�ù�����Ļ����
\attention \n
��
\param[out] pX ������ĻX����,��λ����
\param[out] pY ������ĻY����,��λ����

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_GetCursorPos(HI_S32* pX, HI_S32* pY);


/**
\brief ���ù�����ʾͼƬ���ȵ�
\attention \n
ͼƬ��С16x16,���128x128���أ�֧��colorkey, alpha�� 
\param[in] pCursorInfo ���ͼƬ���ȵ�������Ϣ

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVHOTSPOT
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_SetCursorInfo(const HIGO_CURSOR_INFO_S* pCursorInfo);

/**
\brief ��ȡ������ʾͼƬ��Ϣ
\attention \n
\param[in] pCursorInfo ���ͼƬ���ȵ�������Ϣ

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_GetCursorInfo(HIGO_CURSOR_INFO_S* pCursorInfo);

/**
\brief �����󶨵�ͼ���ϣ�֧��һ�����󶨵����ͼ����
\attention \n
���뽫���󶨵�һ���Ѿ�open��ͼ���ϡ�
\param[in] hLayer ͼ��ID

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_NOTOPEN
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32  HI_GO_AttchCursorToLayer(HI_HANDLE hLayer);

/**
\brief �������ͼ��
\attention \n
\param[in] hLayer ͼ��ID

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32  HI_GO_DetachCursorFromLayer(HI_HANDLE hLayer);
/** @} */  /** <!-- ==== API declaration end ==== */
#ifdef __cplusplus
}
#endif


#endif
