/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_common.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/15
  Description   : Common apis for hisilicon system.
  History       :
  1.Date        : 2010/01/25
    Author      : jianglei
    Modification: Created file

*******************************************************************************/

#ifndef __HI_COMMON_H__
#define __HI_COMMON_H__

#include <hi_type.h>
#include <hi_debug.h>
#include <hi_struct.h>
#include <hi_reg.h>

/******************************* API declaration *****************************/
/** \addtogroup      H_1_1_1 */
/** @{ */  /** <!-- ��ͨ��API������ */

/**����FastPlay �˳�ģʽö�� */
typedef enum
{
    HI_UNF_PREAV_NULL = 0x000, /**< Ĭ�Ϸ�ʽ,ֱ�ӹر� */
    HI_UNF_PREAV_STEP1= 0X038, /**< �𲽹ر�ģʽ��Step1 */
    HI_UNF_PREAV_STEP2,        /**< �𲽹ر�ģʽ��Step2 */
    HI_UNF_PREAV_STEP3,        /**< �𲽹ر�ģʽ��Step3 */
    HI_UNF_PREAV_STEP4,        /**< �𲽹ر�ģʽ��Step4 */
    HI_UNF_PREAV_BUTT
}HI_UNF_PREAV_E;

typedef struct
{
    HI_UNF_PREAV_E enOption;   /**< FastPlay�˳�ģʽö�� */
    unsigned int StepParam1;   /**< �𲽹ر�ģʽ�Ĳ���1 */
    unsigned int StepParam2;   /**< �𲽹ر�ģʽ�Ĳ���2 */
}HI_SYS_PREAV_PARAM_S;


#ifndef __KERNEL__
#include <time.h>

/**
\brief ϵͳ��ʼ��
\attention \n
��ʹ������ģ��Ľӿ�֮ǰ����Ҫ�ȵ��ô˽ӿڶ�ϵͳ���г�ʼ��\n
�ڵ�������ӿ�֮ǰ���������ӿڣ����᷵��ʧ�ܣ����ǲ���ִ֤�е���ȷ��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_Init(HI_VOID);

/**
\brief ϵͳȥ��ʼ��
\attention \n
����ģ�鶼����ʹ�ú���ô˽ӿ�ȥ��ʼ��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_DeInit(HI_VOID);

/**
\brief ϵͳ����Ƶͼ�β���ǰ׼������
\attention \n
������ڿ�������򿪻���Ŀ������£����û�����ʵ������ھ���ʱ�����ã��ͷ������Դ���Դﵽ�޷��л���Ч��
���磺��������£�Ӧ�ó����ͼ����Ĭ����ɿ���������ʹ����Դ���ͷ�;��������û�������ͼ��򿪲�����ֱ�ӽ�����Ƶ���Žӿڵĵ��ã�����ʹ�øýӿڣ�
���� HI_SYS_Init ���������ã�֧�ֶ�ε���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_PreAV(HI_SYS_PREAV_PARAM_S *pstPreParm);

/**
\brief ��ȡ�汾�ı���ʱ��
\attention \n
ʱ��Ϊ����commonģ������make��ʱ��
\param[out] pstAttr   ָ�����ͣ�����汾�����ʱ�䡣
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_GetBuildTime(struct tm * ptm);

/**
\brief ��ȡ��ǰʹ�ò���ʱ�� 
\attention \n
ʱ�䵥λ:��
\param[out] pstVersion   ָ�����ͣ������ǰ����ʱ�䡣
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_GetPlayTime(HI_U32 *pu32Playtime);
/**
\brief ��ȡ�汾��
\attention \n
��
\param[out] pstVersion   ָ�����ͣ�����汾�š�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/

HI_S32 HI_SYS_GetVersion(HI_SYS_VERSION_S *pstVersion);

/**
\brief ����ϵͳ��ȫ������
\attention \n
��
\param[in] pstSysConf   ָ�����ͣ�ϵͳ����ָ���ַ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_SetConf(const HI_SYS_CONF_S *pstSysConf);

/**
\brief ��ȡϵͳ��ȫ������
\attention \n
��
\param[out] pstSysConf   ָ�����ͣ����ϵͳ���á�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_GetConf(HI_SYS_CONF_S *pstSysConf);

/**
\brief ����ģ��ĵ�����Ϣ����
\attention \n
��
\param[in] enModId   ģ��ĵ���ID��
\param[in] enLogLevel  ģ��ĵ�����Ϣ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_SetLogLevel(HI_DEBUG_MOD_ID_E enModId,  HI_LOG_LEVEL_E enLogLevel);


/**
\brief д�Ĵ������ڴ�
\attention \n
��
\param[in] u32RegAddr  �Ĵ������ڴ�������ַ��
\param[in] u32Value  �Ĵ�����ֵ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_WriteRegister(HI_U32 u32RegAddr, HI_U32 u32Value);

/**
\brief ���Ĵ������ڴ�
\attention \n
��
\param[in] u32RegAddr  �Ĵ������ڴ�������ַ��
\param[out] pu32Value  ָ�����ͣ�����Ĵ�����ֵ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_SYS_ReadRegister(HI_U32 u32RegAddr, HI_U32 *pu32Value);


/**
\brief ����mmz�ڴ棬��ӳ���û�̬��ַ
\attention \n
��
\param[in/out] pBuf  buffer��Ϣ�ṹ��bufname��bufsize��Ϊ����,�����ַ���û�̬�����ַ��Ϊ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_MMZ_Malloc(HI_MMZ_BUF_S *pBuf);

/**
\brief ����û�̬��ַ��ӳ�䣬���ͷ�mmz�ڴ�
\attention \n
��֤����������ַ���û�̬�����ַ�ͳ�����ȷ
\param[in] pBuf  buffer��Ϣ�ṹ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_MMZ_Free(HI_MMZ_BUF_S *pBuf);

/**
\brief ָ��mmz����������mmz�ڴ棬���������ַ
\attention \n
��
\param[in] size  buffer��С
\param[in] align  ���뷽ʽ
\param[in] mmz_name  buffer���������֣�����NULL��������
\param[in] mmb_name  buffer�������
\retval ::NULL ����ʧ��
\retval �����ַ
\see \n
��
*/
HI_VOID *HI_MMZ_New(HI_U32 size , HI_U32 align, HI_CHAR *mmz_name, HI_CHAR *mmb_name);

/**
\brief ͨ�������ַ�ͷ�mmz�ڴ�
\attention \n
��
\param[in] phys_addr  buffer�����ַ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_MMZ_Delete(HI_U32 phys_addr);

/**
\brief ��mmz����������ַӳ����û�̬�����ַ������ָ���Ƿ�cached
\attention \n
��
\param[in] phys_addr  buffer�����ַ
\param[in] cached  �Ƿ�ʹ��cache��0��ʹ�ã�1ʹ��
\retval ::NULL ����ʧ��
\retval �û�̬���ַ
\see \n
��
*/
HI_VOID *HI_MMZ_Map(HI_U32 phys_addr, HI_U32 cached);

/**
\brief ���mmz�ڴ��û�̬��ַ��ӳ��
\attention \n
��
\param[in] phys_addr  buffer�����ַ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_MMZ_Unmap(HI_U32 phys_addr);


/**
\brief ����cached����MMZ��ˢDcache���ڴ�
\attention \n
�������0����ˢ�����е�Dcache������ֻˢ������ǿ��ڴ�
\param[in] phys_addr  buffer�����ַ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_MMZ_Flush(HI_U32 phys_addr);


/**
\brief �������ַӳ����û�̬�����ַ
\attention \n
��
\param[in] phys_addr  buffer�����ַ
\param[in] u32Size  buffer�Ĵ�С
\retval ::NULL ����ʧ��
\retval �û�̬���ַ
\see \n
��
*/
HI_VOID *HI_MEM_Map(HI_U32 u32PhyAddr, HI_U32 u32Size);


/**
\brief ����û�̬��ַ��ӳ��
\attention \n
��
\param[in] pAddrMapped  buffer���û�̬���ַ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_MEM_Unmap(HI_VOID *pAddrMapped);

/**
\brief ���������ַ��ȡ�����ַ���Լ���С
\attention \n
��
\param[in] pVir  �û�̬���ַ
\param[out] pu32Phyaddr �����ַ
\param[out] pu32Size ��С
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_MMZ_GetPhyaddr(HI_VOID * pVir, HI_U32 *pu32Phyaddr, HI_U32 *pu32Size);


/** @} */  /** <!-- ==== Structure Definition end ==== */

#endif
#endif /* __HI_COMMON_H__ */
