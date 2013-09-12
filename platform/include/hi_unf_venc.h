/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_venc.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/04/07
  Description   :
  History       :
  1.Date        : 2010/04/07
    Author      : j00131665
    Modification: Created file

*******************************************************************************/
/** 
 * \file
 * \brief �ṩVENC�������Ϣ
 */

#ifndef  __HI_UNF_VENC_H__
#define  __HI_UNF_VENC_H__

#include "hi_unf_common.h"
#include "hi_unf_vi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/********************************Macro Definition********************************/
/** \addtogroup      H_2_2_11 */
/** @{ */  /** <!-- ��VENC�� */

/**<��������*/
#define HI_UNF_VENC_MAX_WIDTH       (1920)		
/**<��С������*/	
#define HI_UNF_VENC_MIN_WIDTH       (96)			  
/**<������߶�*/
#define HI_UNF_VENC_MAX_HEIGTH      (1080)		
/**<��С����߶�*/	
#define HI_UNF_VENC_MIN_HEIGTH      (96)			  
/**<ͼ���С�����ֽ�*/
#define HI_UNF_VENC_PIC_SZIE_ALIGN  (16)			  
/**<��󻺴��ֽ�*/
#define HI_UNF_VENC_MAX_BUF_SIZE    (20*1024*1024)	
/**<��С�����ֽ�*/
#define HI_UNF_VENC_MIN_BUF_SIZE    (256*1024)	
/**<��СGOP*/
#define HI_UNF_VENC_MIN_GOP         (1)				  
/**<����������*/
#define HI_UNF_VENC_MAX_bps         (42*1024*1024)	
/**<��С�������*/
#define HI_UNF_VENC_MIN_bps         (32*1024)		
/**<���Split�ֽ�*/
#define HI_UNF_VENC_MAX_SPLIT_SIZE  (0xFFFF)		
/**<��СSplit�ֽ�*/
#define HI_UNF_VENC_MIN_SPLIT_SIZE  (512)			  
/**<�����������*/
#define HI_UNF_VENC_MAX_Q_VALUE     (99)		 
/**<��С��������*/ 
#define HI_UNF_VENC_MIN_Q_VALUE     (1)				  
/**<���֡��*/
#define HI_UNF_VENC_MAX_fps         (30)		
/**<��С֡��*/	  
#define HI_UNF_VENC_MIN_fps         (1)				 
/**<���ʱ����ֽڴ�С*/
#define HI_UNF_VENC_STREAM_RESERV_SIZE 48			  
/** @} */  /** <!-- ==== Macro Definition end ==== */

/********************************Struct Definition********************************/
/** \addtogroup      H_2_2_16 */
/** @{ */  /** <!-- ��VENC�� */

/** H.264NALU���� */
typedef enum hiUNF_H264E_NALU_TYPE_E
{
    HI_UNF_H264E_NALU_PSLICE = 1,		/**<P slice NALU*/
    HI_UNF_H264E_NALU_ISLICE = 5,		/**<I slice NALU*/
    HI_UNF_H264E_NALU_SEI = 6,			/**<SEI NALU*/
    HI_UNF_H264E_NALU_SPS = 7,			/**<SPS NALU*/
    HI_UNF_H264E_NALU_PPS = 8,			/**<PPS NALU*/
    HI_UNF_H264E_NALU_BUTT
} HI_UNF_H264E_NALU_TYPE_E;

/** H.263NALU���� */
typedef enum hiUNF_H263E_PACK_TYPE_E
{
    HI_UNF_H263E_NALU_PSLICE = 1,		/**<P slice NALU*/
    HI_UNF_H263E_NALU_ISLICE = 5,		/**<I slice NALU*/
    HI_UNF_H263E_NALU_SEI = 6,			/**<SEI NALU*/
    HI_UNF_H263E_NALU_SPS = 7,			/**<SPS NALU*/
    HI_UNF_H263E_NALU_PPS = 8,			/**<PPS NALU*/
    HI_UNF_H263E_NALU_BUTT
} HI_UNF_H263E_PACK_TYPE_E;

/** JPEG������� */
typedef enum hiUNF_JPEGE_PACK_TYPE_E
{
    HI_UNF_JPEGE_PACK_ECS = 5,			/**<ECS ��*/
    HI_UNF_JPEGE_PACK_APP = 6,			/**<APP ��*/
    HI_UNF_JPEGE_PACK_VDO = 7,			/**<VDO ��*/
    HI_UNF_JPEGE_PACK_PIC = 8,			/**<PIC ��*/
    HI_UNF_JPEGE_PACK_BUTT
} HI_UNF_JPEGE_PACK_TYPE_E;

/** MPEG4������� */
typedef enum hiUNF_MPEG4E_PACK_TYPE_E
{
    HI_UNF_MPEG4E_PACK_VO = 1,			/**<VO ��*/
    HI_UNF_MPEG4E_PACK_VOS = 2,			/**<VOS ��*/
    HI_UNF_MPEG4E_PACK_VOL = 3,			/**<VOL ��*/
    HI_UNF_MPEG4E_PACK_VOP = 4,			/**<VOP ��*/
    HI_UNF_MPEG4E_PACK_SLICE = 5		/**<SLICE ��*/	
} HI_UNF_MPEG4E_PACK_TYPE_E;

/** �������� */
typedef union hiUNF_VENC_DATA_TYPE_U
{
    HI_UNF_H264E_NALU_TYPE_E   enH264EType;	/**<264��������*/	
    HI_UNF_H263E_PACK_TYPE_E   enH263EType;	/**<263��������*/	
    HI_UNF_JPEGE_PACK_TYPE_E   enJPEGEType;	/**<JPEG��������*/	
    HI_UNF_MPEG4E_PACK_TYPE_E  enMPEG4EType;/**<MPEG4��������*/		
}HI_UNF_VENC_DATA_TYPE_U;

/** ����������� */
typedef struct hiVENC_STREAM_S
{
    HI_U8                   au8Reserved[HI_UNF_VENC_STREAM_RESERV_SIZE];  /**< inner use, don't touch */
    HI_U8                   *pu8Addr[2];		  /**<���������ַ��ѭ��buffer����ʱ��2����ַ*/	
    HI_U32                  u32PhyAddr[2];		/**<���������ַ��ѭ��buffer����ʱ��2����ַ*/	
    HI_U32                  u32SlcLen[2];		  /**<��������*/		
    HI_U32                  u32PTS0;			    /**<PTS0*/	
    HI_U32                  u32PTS1;			    /**<PTS1*/	
    HI_U32                  bFrameEnd;  	  	/**<�Ƿ�Ϊ֡����*/
    HI_UNF_VENC_DATA_TYPE_U enDataType;			  /**<������������ */
}HI_UNF_VENC_STREAM_S;

/** �������ݴ洢���� */
typedef enum hiUNF_VENC_YUV_TYPE_E
{
    HI_UNF_VENC_YUV_420=0,		/**<YUV420ģʽ*/
    HI_UNF_VENC_YUV_422,		  /**<YUV422ģʽ*/	
    HI_UNF_VENC_YUV_444,		  /**<YUV444ģʽ*/
    HI_UNF_VENC_YUV_BUTT
}HI_UNF_VENC_YUV_TYPE_E;

/** �������ݴ洢ģʽ */
typedef enum hiUNF_VENC_STORE_TYPE_E
{
    HI_UNF_VENC_STORE_SEMIPLANNAR=0,	/**<semi plannarģʽ*/
    HI_UNF_VENC_STORE_PLANNAR,			  /**<plannarģʽ*/
    HI_UNF_VENC_STORE_PACKAGE,			  /**<packageģʽ*/
    HI_UNF_VENC_STORE_BUTT	
}HI_UNF_VENC_STORE_TYPE_E;

/** package YUV���˳�� */
typedef enum hiUNF_VENC_PACKAGE_SEQ_E
{
    HI_UNF_VENC_PACKAGE_Y0UY1V =0,	    /**<Y0U0Y1V0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y0UVY1 ,	    /**<Y0U0V0Y1ģʽ*/
    HI_UNF_VENC_PACKAGE_Y0Y1UV ,	    /**<Y0Y1U0V0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y0Y1VU ,	    /**<Y0Y1V0U0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y0VY1U ,	    /**<Y0V0Y1U0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y0VUY1 ,	    /**<Y0V0U0Y1ģʽ*/
    
    HI_UNF_VENC_PACKAGE_UY0Y1V ,	    /**<U0Y0Y1V0ģʽ*/
    HI_UNF_VENC_PACKAGE_UY0VY1 ,	    /**<U0Y0V0Y1ģʽ*/
    HI_UNF_VENC_PACKAGE_UY1Y0V ,	    /**<U0Y1Y0V0ģʽ*/
    HI_UNF_VENC_PACKAGE_UY1VY0 ,	    /**<U0Y1V0Y0ģʽ*/
    HI_UNF_VENC_PACKAGE_UVY1Y0 ,	    /**<U0V0Y1Y0ģʽ*/
    HI_UNF_VENC_PACKAGE_UVY0Y1 ,	    /**<U0V0Y0Y1ģʽ*/

    HI_UNF_VENC_PACKAGE_Y1UY0V ,	    /**<Y1U0Y0V0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y1UVY0 ,	    /**<Y1U0V0Y0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y1Y0UV ,	    /**<Y1Y0U0V0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y1Y0VU ,	    /**<Y1Y0V0U0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y1VY0U ,	    /**<Y1V0Y0U0ģʽ*/
    HI_UNF_VENC_PACKAGE_Y1VUY0 ,	    /**<Y1V0U0Y0ģʽ*/

    HI_UNF_VENC_PACKAGE_VY0Y1U ,	    /**<V0Y0Y1U0ģʽ*/
    HI_UNF_VENC_PACKAGE_VY0UY1 ,	    /**<V0Y0U0Y1ģʽ*/
    HI_UNF_VENC_PACKAGE_VY1Y0U ,	    /**<V0Y1Y0U0ģʽ*/
    HI_UNF_VENC_PACKAGE_VY1UY0 ,	    /**<V0Y1U0Y0ģʽ*/
    HI_UNF_VENC_PACKAGE_VUY1Y0 ,	    /**<V0U0Y1Y0ģʽ*/
    HI_UNF_VENC_PACKAGE_VUY0Y1 ,	    /**<V0U0Y0Y1ģʽ*/	
    HI_UNF_VENC_PACKAGE_BUTT	
}HI_UNF_VENC_PACKAGE_SEQ_E;

/* ����ͨ������ */
typedef struct hiUNF_VENC_CHN_ATTR_S
{
    HI_U32                      u32Width;   /**< ��ȣ�16�ֽڶ���,��֧�ֶ�̬����  */
    HI_U32                      u32Height;  /**< �߶ȣ�16�ֽڶ���,��֧�ֶ�̬���� */
    HI_UNF_VCODEC_TYPE_E        enVencType;	/**< ���������� */
    HI_U32                      u32StrmBufSize;	/**< ����buffer��С */

    HI_UNF_VENC_YUV_TYPE_E      enYuvSampleType; /**< �洢���ͣ�420 422, 422��ʽֻ֧��package  */
    HI_UNF_VENC_STORE_TYPE_E    enYuvStoreType;  /**< �洢��ʽ, Ŀǰֻ֧��semiplanar ���� package*/
    HI_U32                      u32RotationAngle;/**< ��ת�Ƕ�,��Ч����  */

	HI_UNF_VENC_PACKAGE_SEQ_E   enPackageSel;	  /**< package YUV���˳��*/ 	
    HI_BOOL                     bSlcSplitEn;	  /**< �Ƿ�ʹ�ָܷ�slice */ 	
    HI_U32                      u32SplitSize;     /**< �ָ�Ĵ�С��JPGE����MCUΪ��λ,H264����MP4���ֽ�Ϊ��λ, H263������ */
    
    HI_U32                      u32Qlevel;        /**< JPGEȡֵ��Χ1-99����������Ϊ0 */
    
    HI_U32                      u32TargetBitRate; /**< Venc����RC����,�ɶ�̬���� */
    HI_U32                      u32TargetFrmRate; /**< Ŀ��֡��,�ɶ�̬���� */ 
    HI_U32                      u32InputFrmRate;  /**< ����֡��,�ɶ�̬����,u32TargetFrmRate <= u32InputFrmRate */ 
    HI_U32                      u32Gop;			  /**< GOP��С,�ɶ�̬���� */ 	
	HI_BOOL        				bSendToNet;       /**< �Ƿ��͵����磬 �����������磬���򱣳�����������
										���û�ͨ���ӿڻ�ȡ��������ͬʱ������·�������û���ȡ�ò���ʱ����������ʱ */
	HI_UNF_VP_NET_PARA_S        stNetCfgPara;		  /**< ���������bSendToNetΪ��ʱ��Ч */
    
}HI_UNF_VENC_CHN_ATTR_S;

/** @} */  /** <!-- ==== Struct Definition end ==== */

/********************************API declaration********************************/
/** \addtogroup      H_1_2_9 */
/** @{ */  /** <!-- ��VENC�� */

/** 
\brief ��ʼ����Ƶ������
\attention \n
����VENCģ��Ҫ�����ȵ��øýӿ�
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_DEV_NOT_EXIST �豸������
\retval ::HI_ERR_VENC_NOT_DEV_FILE �ļ����豸
\retval ::HI_ERR_VENC_DEV_OPEN_ERR ���豸ʧ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_Init(HI_VOID);


/** 
\brief ȥ��ʼ����Ƶ������
\attention \n
��
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_DEV_CLOSE_ERR �رձ�����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_DeInit(HI_VOID);


/** 
\brief ��ȡ����ͨ��Ĭ������
\attention \n
Ĭ��D1���룬H.264��ʽ��һ֡Ϊһ��Slice
\param[in] pstAttr ָ�����ͨ�����Ե�ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_NULL_PTR ����ָ�����Ϊ��ָ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_GetDefaultAttr(HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief ������Ƶ����ͨ��
\attention \n
������Ƶ����Ҫ�����ȴ�������ͨ�� 
\param[in] phVencChn ָ�����ͨ�������ָ��
\param[in] pstAttr ָ�����ͨ�����Ե�ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_NULL_PTR ����ָ������п�ָ��
\retval ::HI_ERR_VENC_CREATE_ERR ����ͨ��������
\retval ::HI_ERR_VENC_INVALID_PARA ͨ���������ô���
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_CreateChn(HI_HANDLE *phVenc, const HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief ������Ƶ����ͨ��
\attention \n
\param[in] hVenc ����ͨ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ���������
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_DestroyChn(HI_HANDLE hVenc);


/** 
\brief �󶨱���ͨ������ƵԴ
\attention \n
��ʼ����ͻ�ȡ����֮ǰ��Ҫ���ȵ��øýӿ�
\param[in] hVenc ����ͨ�����
\param[in] hSrc ��ƵԴ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_INVALID_PARA ��ƵԴ����
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_AttachInput(HI_HANDLE hVenc,HI_HANDLE hSrc);


/** 
\brief �����ƵԴ
\attention \n
���øýӿ���Ҫ����ֹͣ����
\param[in] hVenc ����ͨ�����
\param[in] hSrc ��ƵԴ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_INVALID_PARA ��ƵԴ����
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\retval ::HI_ERR_VENC_CHN_INVALID_STAT ������δֹͣ����
\see \n
��
*/
HI_S32 HI_UNF_VENC_DetachInput(HI_HANDLE hVenc,HI_HANDLE hSrc);


/** 
\brief ��ʼ����
\attention \n
���øýӿ���Ҫ���ȳ�ʼ������������������ͨ��������ƵԴ
\param[in] hVenc ����ͨ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\retval ::HI_ERR_VENC_CHN_NO_ATTACH ����ͨ��û�а󶨵���ƵԴ
\see \n
��
*/
HI_S32 HI_UNF_VENC_Start(HI_HANDLE hVenc);


/** 
\brief ֹͣ����
\attention \n
���øýӿ���Ҫ���ȳ�ʼ������������������ͨ��������ƵԴ
���Ѿ���ʼ����
\param[in] hVenc ����ͨ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\retval ::HI_ERR_VENC_CHN_NO_ATTACH ����ͨ��û�а󶨵���ƵԴ
\see \n
��
*/
HI_S32 HI_UNF_VENC_Stop(HI_HANDLE hVenc);

/** 
\brief ��ȡ��Ƶ��������
\attention \n
���øýӿ���Ҫ���Ȱ���ƵԴ����ʼ����
����ʱ��������ã�ʱ�䵥λΪ���룬����Ϊ0���ȴ�������Ϊ0xffffffffһֱ�ȴ���\n
����������ʱ�䣬��û�����ݵ���򷵻�::HI_ERR_VENC_BUF_EMPTY\n
����ȴ�ʱ��Ϊ0����û���������ݣ��򷵻�::HI_ERR_VENC_BUF_EMPTY\n
��ʱ��֧�ַ�����ģʽ�����u32TimeOutMs����Ϊ0,�����ڴ˽ӿڷ���HI_ERR_VENC_BUF_EMPTY��ʱ�򣬵���usleep(10000)����CPU \n
\param[in] hVenc ����ͨ�����
\param[in] pstStream ��������ṹ��ָ��
\param[in] u32TimeOutMs      �ȴ���ʱʱ�䣬��λms
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\retval ::HI_ERR_VENC_NULL_PTR ����ָ��Ϊ��
\retval ::HI_ERR_VENC_CHN_NO_ATTACH ����ͨ��û�а󶨵���ƵԴ
\retval ::HI_ERR_VENC_BUF_EMPTY ��ȡ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_AcquireStream(HI_HANDLE hVenc,HI_UNF_VENC_STREAM_S *pstStream, HI_U32 u32TimeoutMs);


/** 
\brief �ͷ���Ƶ��������
\attention \n
���øýӿ���Ҫ���Ȼ�ȡ�������Ҳ��ܸı���������
\param[in] hVenc ����ͨ�����
\param[in] pstStream ��������ṹ��ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\retval ::HI_ERR_VENC_NULL_PTR ����ָ��Ϊ��
\retval ::HI_ERR_VENC_CHN_NO_ATTACH ����ͨ��û�а󶨵���ƵԴ
\see \n
��
*/
HI_S32 HI_UNF_VENC_ReleaseStream(HI_HANDLE hVenc, const HI_UNF_VENC_STREAM_S *pstStream);


/** 
\brief ��̬���ñ���ͨ������
\attention \n
���øýӿ���Ҫ���ȴ�������ͨ��
\param[in] hVenc ����ͨ�����
\param[in] pstAttr ��ű���ͨ�����Ե�ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\retval ::HI_ERR_VENC_NULL_PTR ָ��Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_SetAttr(HI_HANDLE hVenc,const HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief ��ȡ����ͨ������
\attention \n
���øýӿ���Ҫ���ȴ�������ͨ��
\param[in] hVenc ����ͨ�����
\param[in] pstAttr ����ͨ������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\retval ::HI_ERR_VENC_NULL_PTR ָ��Ϊ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_GetAttr(HI_HANDLE hVenc, HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief ����I֡
\attention \n
���øýӿں󣬱������ᾡ������һ��I֡��.\n
�˽ӿ�һ�����ڿ��ӵ绰������ͨ�������ʹ���ָ�.\n
�˽ӿ�ֻ��"���������"��������һ��I֡��������ڶ�ʱ���ڶ�ε��ô˽ӿڣ���ô���ܱ�֤ÿ�ε��ö��ܶ�Ӧ�����һ��I֡��.\n
\param[in] hVenc ����ͨ�����
\param[in] pstStream ��ű���ͨ�����Ե�ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VENC_CHN_NOT_EXIST ����ͨ�����������
\retval ::HI_ERR_VENC_NO_INIT ������δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_VENC_RequestIFrame(HI_HANDLE hVencChn);
/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif//__HI_UNF_VENC_H__
