/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_vi.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/03/26
  Description   :
  History       :
  1.Date        : 2010/03/26
    Author      : j00131665
    Modification: Created file

*******************************************************************************/
/** 
 * \file
 * \brief �ṩVI�������Ϣ
 */

#ifndef  __HI_UNF_VI_H__
#define  __HI_UNF_VI_H__

#include "hi_type.h"
#include "hi_unf_common.h"


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif


/********************************Error Code Definition********************************/
/** \addtogroup      H_3_6 */
/** @{ */  /** <!-- ��VI�� */

/**<����������*/
#define HI_UNF_VI_INVALID_PARA_U32   (HI_U32)(-1)	

/** @} */  /** <!-- ==== Error Code Definition end ==== */




/********************************Struct Definition********************************/
/** \addtogroup      H_2_2_10 */
/** @{ */  /** <!-- ��VI�� */

/** BT.1120 YC����ģʽͨ������ */
typedef enum hiUNF_VI_CHN_YC_SEL_E
{
    HI_UNF_VI_CHN_YC_SEL_Y = 0,		/**<BT.1120 YC����ģʽ��Y����ͨ��*/
    HI_UNF_VI_CHN_YC_SEL_C,			/**<BT.1120 YC����ģʽ��C����ͨ��*/
    HI_UNF_VI_CHN_YC_SEL_BUTT
}HI_UNF_VI_CHN_YC_SEL_E;

/** �洢���� */
typedef enum hiUNF_VI_STOREMETHOD_E
{
    HI_UNF_VI_STORE_METHOD_PNYUV = 0,  /**<plannar YCbCr*/
    HI_UNF_VI_STORE_METHOD_SPNYC,      /**<semi_plannar YC*/
    HI_UNF_VI_STORE_METHOD_PKYUV,      /**<package yuv*/
    HI_UNF_VI_STORE_METHOD_RAWDATA,    /**<������*/
    HI_UNF_VI_STORE_METHOD_BUTT     
} HI_UNF_VI_STOREMETHOD_E;

/* enumeration of possible VIU data width select. */
/*Ŀǰ�߼��̶�ֻ֧��8bit����������ɾ��*/
/*typedef enum hiUNF_VI_DATAWIDTH_E
{
    HI_UNF_VI_DATA_WIDTH8 = 0  
    HI_UNF_VI_DATA_WIDTH10 = 2, 
} HI_UNF_VI_DATAWIDTH_E;
*/

/** ��ģʽ��ѡ��ģʽ */
typedef enum hiUNF_VI_LINESEL_E
{
    HI_UNF_VI_LINESEL_ODD=0,     /**<���������вɼ�*/
    HI_UNF_VI_LINESEL_EVEN,      /**<����ż���вɼ�*/
    HI_UNF_VI_LINESEL_BOTH,      /**<�������к�ż���ж��ɼ�*/
    HI_UNF_VI_LINESEL_0347,      /**<ÿ4����ֻ�ɼ�0��3��*/
    HI_UNF_VI_LINESEL_1256,      /**<ÿ4����ֻ�ɼ�1��2��*/
    HI_UNF_VI_LINESEL_BUTT
} HI_UNF_VI_LINESEL_E;

/** ��ż��ѡ��ģʽ */
typedef enum hiUNF_VI_CAPSEL_E
{
    HI_UNF_VI_CAPSEL_ODD=0,     /**<�����������ɼ�*/
    HI_UNF_VI_CAPSEL_EVEN,      /**<����ż�����ɼ�*/
    HI_UNF_VI_CAPSEL_BOTH,       /**<����������ż�������ɼ�*/
    HI_UNF_VI_CAPSEL_BUTT
} HI_UNF_VI_CAPSEL_E;

/** ֡���洢ģʽ */
typedef enum hiUNF_VI_STORE_MODE_E
{
    HI_UNF_VI_STORE_FIELD = 0,   /**<���洢ģʽ*/
    HI_UNF_VI_STORE_FRAME,       /**<֡�洢ģʽ*/
    HI_UNF_VI_STORE_BUTT
}HI_UNF_VI_STORE_MODE_E;

/** ����˿� */
typedef enum hiUNF_VI_E
{
    HI_UNF_VI_PORT0   = 0x0,  /**<�˿�0 */
    HI_UNF_VI_PORT1,          /**<�˿�1 */    
    HI_UNF_VI_BUTT
}HI_UNF_VI_E;

/** ����ӿ�ģʽ */
typedef enum hiUNF_VI_INPUT_MODE_E
{
    HI_UNF_VI_MODE_BT656=0,        /**<ITU-R BT.656 YUV4:2:2 ��׼.  */
    HI_UNF_VI_MODE_BT601,          /**<ITU-R BT.601 YUV4:2:2 ��׼.  */
    HI_UNF_VI_MODE_DIGITAL_CAMERA, /**<��������ͷ�����ݿ�����RGB����YCbCr.*/
    HI_UNF_VI_MODE_RAW_DATA,       /**<ͨ��CVBS��������ݣ�����Ҫ����. */
    HI_UNF_VI_MODE_USB_CAM,        /**<USB ����ͷ�����û�Get/Put��������  */ 
    HI_UNF_VI_MODE_VIRTUAL,        /**<����VI,����Ӳ���������ݣ����û�Get/Put�������� */
    HI_UNF_VI_MODE_BT1120_720P,	   /**<ITU-R BT.1120 YUV4:2:2 ��׼��720P  */ 
    HI_UNF_VI_MODE_BT1120_1080I,   /**<ITU-R BT.1120 YUV4:2:2 ��׼��1080I  */ 	
    HI_UNF_VI_MODE_BT1120_1080P,   /**<ITU-R BT.1120 YUV4:2:2 ��׼��1080p  */ 
    HI_UNF_VI_MODE_BUTT            
} HI_UNF_VI_INPUT_MODE_E;

/** VI���� */
typedef struct hiUNF_VI_ATTR_S
{
    HI_UNF_VI_E              enViPort;		/**<����˿� */
    HI_UNF_VI_INPUT_MODE_E   enInputMode;   /**<��Ƶ����ģʽ*/
    HI_RECT_S                stInputRect;   /**< ���ڵĲü����� */
    HI_UNF_VI_CAPSEL_E       enCapSel;		/**< ��ż���ɼ�ѡ�� */

    HI_UNF_VI_CHN_YC_SEL_E   enChnYC;       /**<ֻ����bt1120ģʽ����Ч */
    HI_UNF_VI_STOREMETHOD_E  enStoreMethod; /**<��Ƶ��ʽ*/
    HI_UNF_VI_STORE_MODE_E	 enStoreMode;   /**<֡��ģʽ*/
    
    HI_U32 u32YStride;		/**<planarģʽ��Y��stride������ģʽ��Ψһstride*/
    HI_U32 u32CStride;		/**<planarģʽ��C��stride������ģʽ��Ч*/
    HI_U32 u32BufPhyAddr;	/**<֡buf�����ַ, �û�����Ҫ���� */
    HI_U32 u32FrameSize;    /**<һ֡ռ�õ��ڴ�ռ�,����������û�����Ҫ���� */
    HI_U32 u32BufSize;		/**<֡buf�Ĵ�С,����������û�����Ҫ���� */
    HI_U32 u32BufNum;       /**<���õ�֡buf�ĸ���*/
} HI_UNF_VI_ATTR_S;

/** VI Buffer ���� */
typedef struct  hiUNF_VI_BUF_S
{ 
    HI_U32                      u32FrameIndex;	/**< ֡����       */
    HI_UNF_VIDEO_FORMAT_E       enPixelFormat;  /**< ������Ƶ������ʽ  */
    HI_U32                      u32Width;       /**< ������.       */
    HI_U32                      u32Height;      /**< ����߶�.      */
                                                        
    HI_UNF_VIDEO_FIELD_MODE_E   enField;        /**< �ɳ����� ,top/bottom/all       */
    HI_U32                      u32DownScaled;  /**< �Ƿ�Ҫ�²���. */

    /* �����RGB����package�洢ģʽ��ֻ��u32PhyAddr[0]��Ч.
       �����semi-planar�洢ģʽ��ֻ��u32PhyAddr[0-1]��Ч,
       ��Ӧ��pVirAddr��u32StrideҲ��u32PhyAddr��Ч��һ��.  */
    HI_U32                      u32PhyAddr[3];        /**< A/B/C ���������ַ. */	
    HI_VOID                     *pVirAddr[3];         /**< A/B/C ���������ַ. */
    HI_U32                      u32Stride[3];         /**< A/B/C ����stride.      */

    HI_U32                      u32PtsMs;                   /**< ʱ���. */                     
}HI_UNF_VI_BUF_S;

/** @} */  /** <!-- ==== Struct Definition end ==== */

/********************************API declaration********************************/
/** \addtogroup      H_1_2_8 */
/** @{ */  /** <!-- ��VI�� */

/** 
\brief ��ʼ��VI
\attention \n
����VIģ��Ҫ�����ȵ��øýӿ�
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_DEV_NOT_EXIST �豸������
\retval ::HI_ERR_VI_NOT_DEV_FILE �ļ����豸
\retval ::HI_ERR_VI_DEV_OPENED ���豸ʧ��
\see \n
��
*/
HI_S32 HI_UNF_VI_Init(HI_VOID);


/** 
\brief ȥ��ʼ��VI
\attention \n
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_DEV_NOT_EXIST �豸������
\retval ::HI_ERR_VI_DEV_CLOSE_ERR �ر�VI �豸ʧ��
\see \n
��
*/
HI_S32 HI_UNF_VI_DeInit(HI_VOID);


/** 
\brief ��ȡVI�˿�Ĭ������
\attention \n
Ĭ��Port=0, HALF-D1, BT656���ɼ�ż�������SemiPlanner YUV4:2:0��ʽ����
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_NULL_PTR ��ָ��
\see \n
��
*/
HI_S32 HI_UNF_VI_GetDefaultAttr(HI_UNF_VI_ATTR_S *pstAttr);


/** 
\brief ����VI Port����
\attention \n
Ԥ���ӿڣ���Create��һ�����ɶ�̬����
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_NULL_PTR ��ָ��
\retval ::HI_ERR_VI_CHN_NOT_EXIST �������
\retval ::HI_ERR_VI_CHN_INIT_BUF_ERR ��ʼ��buffer����
\retval ::HI_ERR_VI_INVALID_PARA ���Բ�������
\see \n
��
*/
HI_S32 HI_UNF_VI_SetAttr(HI_HANDLE hVi, HI_UNF_VI_ATTR_S *pstAttr);


/** 
\brief ��ȡVI Port����
\attention \n
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_NULL_PTR ��ָ��
\retval ::HI_ERR_VI_CHN_NOT_EXIST �������
\see \n
��
*/
HI_S32 HI_UNF_VI_GetAttr(HI_HANDLE hVi, HI_UNF_VI_ATTR_S *pstAttr);


/** 
\brief ��Vi Port������Vi���
\attention \n
����VI ģ����Ҫ���ȵ��øýӿ�\n
����ʹ������VI, ����PortID��Ҫ��Ӳ����Ӧ,Ӳ����ʹ�����ĸ�Port,��ô���Ҳ����ʹ���ĸ�Port.\n
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_NULL_PTR ��ָ��
\retval ::HI_ERR_VI_CHN_INIT_BUF_ERR ��ʼ��buffer����
\retval ::HI_ERR_VI_INVALID_PARA ���Բ�������
\see \n
��
*/
HI_S32 HI_UNF_VI_Create(HI_UNF_VI_ATTR_S *pstAttr, HI_HANDLE *phandle);


/** 
\brief �ر�Vi Port�����پ��
\attention \n
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_CHN_NOT_EXIST �������
\see \n
��
*/
HI_S32 HI_UNF_VI_Destroy(HI_HANDLE hVi);


/** 
\brief ��ȡ����Vi Port һ֡ͼ��Buffer
\attention \n
����û�������������VI Port�����Ե��ô˽ӿڻ�ȡVi Buf�������û�YUV���ݡ�\n
һ������USB����ͷ\n
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_CHN_NOT_EXIST �������
\retval ::HI_ERR_VI_NULL_PTR ��ָ��
\see \n
��
*/
HI_S32 HI_UNF_VI_GetFrame(HI_HANDLE hVi, HI_UNF_VI_BUF_S * pViBuf);


/** 
\brief ��������Vi Port һ֡ͼ��Buffer����������Port����
\attention �û�����::HI_UNF_VI_GetFrame��ȡ��һ֡YUV���ݵĵ�ַ�����ҿ�����YUV���ݺ󣬾Ϳ��Ե��ô˽ӿ�֪ͨVI�����Ѿ�׼���ã�VI���ڴ˽ӿڱ����ú󣬰�������ȥ���������ȥVO��ʾ��\n
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_CHN_NOT_EXIST �������
\retval ::HI_ERR_VI_NULL_PTR ��ָ��
\see \n
��
*/
HI_S32 HI_UNF_VI_PutFrame(HI_HANDLE hVi, const HI_UNF_VI_BUF_S * pViBuf);


/** 
\brief ��ȡһ֡YUV ͼ���ַ
\attention \n
һ������£��û�����Ҫ���ô˽ӿڣ��Ƽ�ֱ�ӽ�VI��VENC����VO���а��Ա�ʵ�ֱ������VIVO���ع��ܡ�
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_CHN_NOT_EXIST �������
\retval ::HI_ERR_VI_NULL_PTR ��ָ��
\see \n
��
*/
HI_S32 HI_UNF_VI_AcquireFrame(HI_HANDLE hVi, HI_UNF_VI_BUF_S * pViBuf);


/** 
\brief �û��黹һ֡YUV ͼ���ַ
\attention \n
һ������£��û�����Ҫ���ô˽ӿڣ��Ƽ�ֱ�ӽ�VI��VENC����VO���а��Ա�ʵ�ֱ������VIVO���ع��ܡ�
\param[in] ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_VI_CHN_NOT_EXIST �������
\retval ::HI_ERR_VI_NULL_PTR ��ָ��
\see \n
��
*/
HI_S32 HI_UNF_VI_ReleaseFrame(HI_HANDLE hVi, const HI_UNF_VI_BUF_S * pViBuf);
/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif
