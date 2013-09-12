/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_vp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/03/25
  Description   :
  History       :
  1.Date        : 2011/03/25
    Author      :
    Modification: Created file

 *******************************************************************************/

/**
 * \file
 * \brief �ṩVP��Ƶ����������Ϣ
 */
#ifndef __HI_UNF_VP_H__
#define __HI_UNF_VP_H__
#include "hi_common.h"
#include "hi_unf_common.h"
#include "hi_unf_vi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

typedef struct hi_VP_VENC_CHN_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E     enEncType;	       /**<���������� */
    HI_UNF_VI_E              enViPort;		   /**<����˿� */
    HI_UNF_VI_INPUT_MODE_E   enInputMode;      /**<��Ƶ����ģʽ��Ŀǰֻ֧��USB����ͷ*/
    HI_U32                   u32Width;
    HI_U32                   u32Height;
    HI_U32                   u32TargetBitRate; /**< RC����,�ɶ�̬���� */
    HI_U32                   u32TargetFrmRate; /**< Ŀ��֡��,�ɶ�̬���� */ 
    HI_U32                   u32InputFrmRate;  /**< ����֡��,�ɶ�̬����,u32TargetFrmRate <= u32InputFrmRate */ 
    HI_U32                   u32Gop;		   /**< GOP��С,�ɶ�̬���� */ 
	HI_UNF_VP_NET_PARA_S     stEncNetPara;	   /**< �����������*/	
}HI_VP_VENC_CHN_ATTR_S; 

typedef struct hi_VP_VDEC_CHN_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E     enDecType;	       /**< ���������� */
	HI_UNF_VP_NET_PARA_S     stDecNetPara;	   /**< �����������*/
	
}HI_VP_VDEC_CHN_ATTR_S;          


/* ��Ƶ����ͨ������ */
typedef struct hiUNF_VP_CHN_ATTR_S
{
    HI_HANDLE hLocalWin;                       /**< ����VO���ھ�� */  
    HI_HANDLE hRemoteWin;                      /**< Զ��VO���ھ�� */	
    HI_VP_VENC_CHN_ATTR_S stEncAttr;           /**< ���������� */
	HI_VP_VDEC_CHN_ATTR_S stDecAttr;           /**< ���������� */
}HI_UNF_VP_CHN_ATTR_S;


/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_3 */
/** @{ */  /** <!-- ��VP�� */

/**
 \brief ��ʼ��VPģ��
 \attention \n
�ڵ���::HI_UNF_VP_Create�ӿڴ�������֮ǰ�����ñ��ӿ�
 \param ��
 \retval ::HI_SUCCESS �ɹ�
 \retval ::HI_ERR_VP_DEV_NOT_EXIST   �豸������
 \retval ::HI_ERR_VP_DEV_OPEN_ERR   �豸�򿪴���
 \see \n
��
 */
HI_S32 HI_UNF_VP_Init(HI_VOID);

/**
 \brief ȥ��ʼ��VPģ��
 \attention \n
�ڵ���::HI_UNF_VP_DestroyChannel�ӿ��������е�VPͨ���󣬵��ñ��ӿ�
 \param ��
 \retval ::HI_SUCCESS �ɹ�
 \retval ::HI_ERR_VP_NOT_INIT    VP�豸������
 \see \n
��
 */
HI_S32 HI_UNF_VP_DeInit(HI_VOID);

/**
 \brief ��ȡVPͨ��ȱʡ����
 \attention \n
�ڵ���::HI_UNF_VP_CreateChannel�ӿڴ���VPͨ��֮ǰ�����ñ��ӿڣ�������д����
 \param[in] ��
 \param[out] pstDefChAttr  ָ�����ͣ�VPͨ��Ĭ�����ԣ��μ�:HI_UNF_VP_CHN_ATTR_S
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_NULL_PTR  ��ָ��
 \see \n
��
 */
HI_S32 HI_UNF_VP_GetChDefaultAttr(HI_UNF_VP_CHN_ATTR_S *pstDefChAttr);

/**
 \brief ����VPͨ��
 \attention \n
��
 \param[in]  pstChAttr ͨ������
 \param[out] phVp  ָ�����ͣ�VPͨ�����
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_NULL_PTR  ��ָ��
 \retval ::HI_ERR_VP_NOT_SUPPORT          ��������Ƿ�
 \retval ::HI_ERR_VP_NOT_SUPPORT          ��֧��ģʽ
 \see \n
��
 */
HI_S32 HI_UNF_VP_CreateChannel(HI_UNF_VP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVp);

/**
 \brief ����VP ͨ��
 \attention \n
��
 \param[in] hVp  VP ͨ�����
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_NOT_INIT         VPδ��ʼ��
 \retval ::HI_ERR_VP_INVALID_HANDLE   �Ƿ���VP���
 \retval ::����  ����ͨ��ʧ��
 \see \n
��
 */
HI_S32 HI_UNF_VP_DestroyChannel(HI_HANDLE hVp);

/**
 \brief ��ȡVP ͨ������
 \attention \n
 \param[in] hVP  VP ͨ�����
 \param[out] pstChAttr  ָ�����ͣ�VP ͨ�����ԣ��μ�:HI_UNF_VP_CHN_ATTR_S
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VP_NULL_PTR  ��ָ��
 \retval ::����  ��ȡͨ������ʧ��
 \see \n
��
 */
HI_S32 HI_UNF_VP_GetChAttr(HI_HANDLE hVp, HI_UNF_VP_CHN_ATTR_S *pstChAttr);

/**
 \brief �޸�VPͨ������
 \attention \n
        �����ȵ���HI_UNF_VP_GetChAttr()��ȡ��ǰͨ�����ã��ٶԲ�������Ҫ�޸ģ���Ӧ�ĸ��ı����1���޹ظ��ı�־��0��
 \param[in] hVp  VP ͨ�����
 \param[in] pstChAttr  ָ�����ͣ�VP ͨ�����ԣ��μ�:HI_UNF_VP_CHN_ATTR_S
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VP_NULL_PTR  ��ָ��
 \retval ::����  �޸�ͨ������ʧ��
 \see \n
��
 */
HI_S32 HI_UNF_VP_SetChAttr(HI_HANDLE hVp, HI_UNF_VP_CHN_ATTR_S *pstChAttr);

/**
 \brief VPͨ����ʼ����
 \attention \n
        �ڲ���׼���ú󣬰������������VI/VO������ȷ�󣬵��ô˽ӿڿ���������Ƶ��������У�ʵ�������շ�����ʾ���ء�Զ����Ƶ���
 \param[in] hVp  VP ͨ�����
 
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VP_NULL_PTR  ��ָ��
 \retval ::����  VPͨ����ʼ����ʧ��
 \see \n
��
 */
HI_S32 HI_UNF_VP_Start(HI_HANDLE hVp);

/**
 \brief VPͨ��ֹͣ����
 \attention \n
        ��VPͨ�������������к󣬿���ͨ���˽ӿ���ͣ���У�ʹ���涳�ᡢ�����շ���ͣ�����Ե���HI_UNF_VP_Start�ָ�����
 \param[in] hVp  VP ͨ�����
 
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VP_NULL_PTR  ��ָ��
 \retval ::����  VPͨ����ʼ����ʧ��
 \see \n
��
 */
HI_S32 HI_UNF_VP_Stop(HI_HANDLE hVp);

/**
 \brief VPͨ����ʼԤ��������Ƶ
 \attention \n
        ��VI��hLocalWin׼����֮�󣬿�ʼԤ��������Ƶ
 \param[in] hVp  VP ͨ�����
 
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VP_NULL_PTR  ��ָ��
 \retval ::����  VPͨ����ʼ����ʧ��
 \see \n
��
 */
HI_S32 HI_UNF_VP_StartPreView(HI_HANDLE hVp);

/**
 \brief VPͨ��Ԥ��������Ƶ
 \attention \n
        ��VPͨ��Ԥ��������Ƶ�󣬵���ֹͣԤ��
 \param[in] hVp  VP ͨ�����
 
 \retval ::HI_SUCCESS  �ɹ�
 \retval ::HI_ERR_VP_INVALID_PARA   ��Ч���������
 \retval ::HI_ERR_VP_NULL_PTR  ��ָ��
 \retval ::����  VPͨ����ʼ����ʧ��
 \see \n
��
 */
HI_S32 HI_UNF_VP_StopPreView(HI_HANDLE hVp);
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
