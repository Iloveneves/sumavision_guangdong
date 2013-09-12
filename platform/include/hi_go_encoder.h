/**
 \file
 \brief ϵͳ���õ���������
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author 
 \date 2005-4-23
 */
 
#ifndef __HI_GO_ENCODER_H__
#define __HI_GO_ENCODER_H__

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

#include "hi_go_comm.h"

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_5 */
/** @{ */  /** <!-- ��encoder�� */

/**����������*/
typedef struct 
{
   HIGO_IMGTYPE_E ExpectType;   /**< ����ͼƬ����*/
   HI_U32 QualityLevel;        /**<1-99��, ����Խ�ߣ�����Խ�ã��������ͼ���ļ����ڴ�ҲԽ��ֻ��JPEG��Ч*/ 	
}HIGO_ENC_ATTR_S;
/** @} */  /*! <!-- Structure Definition end */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_5 */
/** @{ */  /** <!-- ��ENCODER�� */
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

HI_S32 HI_GO_InitEncoder(HI_VOID);


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

HI_S32 HI_GO_DeinitEncoder(HI_VOID);

/**
\brief ��һ��surface���뵽ָ��ͼ���ʽ�����浽�ļ���
\attention \n
֧�ֱ����bmp��ʽ�ļ�
(�Ƿ�֧�ֱ����JPEG,ȡ����Ӳ��ƽ̨)

\param[in] hSurface  ��Ҫ�����surface,
\param[in] pFile     �������ļ���������Ϊ�գ�Ϊ�����õ�ǰʱ��[��]-[��]-[��]-[ʱ]-[��]-[��]������
\param[in] pAttr     �������õ����ԣ�����Ϊ��

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVSRCTYPE
\retval ::HIGO_ERR_INVIMAGETYPE
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVMIRRORTYPE
\retval ::HIGO_ERR_INVROTATETYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_NOCOLORKEY
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_DEPEND_JPGE

\see \n
*/
HI_S32 HI_GO_EncodeToFile(HI_HANDLE hSurface, const HI_CHAR* pFile, const HIGO_ENC_ATTR_S* pAttr);

/**
\brief ��һ��surface���뵽ָ��ͼ���ʽ�����浽�ڴ��У������б�ָ֤���ڴ���㹻��
\attention \n
֧�ֱ����bmp��ʽ���ݴ�ŵ�ָ�����ڴ���
(�Ƿ�֧�ֱ����JPEG,ȡ����Ӳ��ƽ̨)

\param[in] hSurface     ��Ҫ�����surface,
\param[in] pMem         ���������ͼ�������ڴ�����ʼ��ַ
\param[in] MemLen       ָ���ڴ�Ĵ�С
\param[out] pOutLen     ʵ��ʹ�õ��ڴ��С����������ݳ���(����ȷ��pOutLen <= MemLen)
\param[in] pAttr        �������õ����ԣ�����Ϊ��

\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE ��ʾʧ��
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVSRCTYPE
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVIMAGETY
\retval ::HIGO_ERR_INVIMAGETYPE
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVMIRRORTYPE
\retval ::HIGO_ERR_INVROTATETYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_NOCOLORKEY
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_DEPEND_JPGE

\see \n
*/

HI_S32 HI_GO_EncodeToMem(HI_HANDLE hSurface, HI_U8* pMem, HI_U32 MemLen, HI_U32* pOutLen, const HIGO_ENC_ATTR_S* pAttr);
  
/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
 #if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */
