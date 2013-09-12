/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_disp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/15
  Description   :
  History       :
  1.Date        : 2009/12/15
    Author      : w58735
    Modification: Created file

*******************************************************************************/
/** 
 * \file
 * \brief �ṩDISPLAY�������Ϣ
 */
 
#ifndef  __HI_UNF_DISP_H__
#define  __HI_UNF_DISP_H__

#include "hi_unf_common.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_8 */
/** @{ */  /** <!-- ��DISPLAY�� */

/**����DAC��Ŀ*/
#define MAX_DAC_NUM (6)


/**����DISPLAYͨ��ö��*/
typedef enum hiUNF_DISP_E
{
    HI_UNF_DISP_SD0 = 0x0,   /**< ����DISPLAY0 */
    HI_UNF_DISP_HD0,         /**< ����DISPLAY0 */
    HI_UNF_DISP_BUTT
}HI_UNF_DISP_E;

/**����֧�ֵ�DAC�źŸ�ʽ*/
typedef enum hiUNF_DISP_DAC_MODE_E
{
    HI_UNF_DISP_DAC_MODE_SILENCE = 0,    /**<�����*/
    HI_UNF_DISP_DAC_MODE_CVBS,           /**<CVBS���*/
    HI_UNF_DISP_DAC_MODE_Y,              /**<Y���ȷ������*/
    HI_UNF_DISP_DAC_MODE_PB,             /**<��ɫɫ��������*/
    HI_UNF_DISP_DAC_MODE_PR,             /**<��ɫɫ��������*/
    HI_UNF_DISP_DAC_MODE_R,              /**<��ɫ�������*/
    HI_UNF_DISP_DAC_MODE_G,              /**<��ɫ�������*/
    HI_UNF_DISP_DAC_MODE_B,              /**<��ɫ�������*/
    HI_UNF_DISP_DAC_MODE_SVIDEO_Y,       /**<SVIDEO_Y�������*/
    HI_UNF_DISP_DAC_MODE_SVIDEO_C,       /**<SVIDEO_C�������*/
    HI_UNF_DISP_DAC_MODE_HD_Y,           /**<����Y���ȷ������*/
    HI_UNF_DISP_DAC_MODE_HD_PB,          /**<������ɫɫ��������*/
    HI_UNF_DISP_DAC_MODE_HD_PR,          /**<�����ɫɫ��������*/
    HI_UNF_DISP_DAC_MODE_HD_R,           /**<�����ɫ�������*/
    HI_UNF_DISP_DAC_MODE_HD_G,           /**<������ɫ�������*/
    HI_UNF_DISP_DAC_MODE_HD_B,           /**<������ɫ�������*/
    HI_UNF_DISP_DAC_MODE_BUTT
}HI_UNF_DISP_DAC_MODE_E;


/**����֧�ֵ���ʾ����ӿ� */
typedef struct  hiUNF_DISP_INTERFACE_S
{
    HI_BOOL                      bScartEnable;                /**<�Ƿ����Scart�ź�*/
    HI_BOOL                      bBt1120Enable;               /**<�Ƿ����Bt1120�����ź�*/
    HI_BOOL                      bBt656Enable;                /**<�Ƿ����Bt656�����ź�*/
    HI_UNF_DISP_DAC_MODE_E       enDacMode[MAX_DAC_NUM];      /**<����DAC������ź�*/
}HI_UNF_DISP_INTERFACE_S ;


/**����LCD���������λ��*/
typedef enum hiUNF_DISP_LCD_DATA_WIDTH_E
{
    HI_UNF_DISP_LCD_DATA_WIDTH8 = 0,       /**<8λ*/
    HI_UNF_DISP_LCD_DATA_WIDTH16,          /**<16λ*/
    HI_UNF_DISP_LCD_DATA_WIDTH24,          /**<24λ*/
    HI_UNF_DISP_LCD_DATA_WIDTH_BUTT
}HI_UNF_DISP_LCD_DATA_WIDTH_E;


/**����LCD�����ݸ�ʽ*/
typedef enum hiHI_UNF_DISP_LCD_DATA_FMT
{
    HI_UNF_DISP_LCD_DATA_FMT_YUV422 = 0,         /**<YUV422��λ��Ϊ16*/
    HI_UNF_DISP_LCD_DATA_FMT_RGB565 = 0x8,       /**<RGB565��λ��Ϊ16*/
    HI_UNF_DISP_LCD_DATA_FMT_RGB444 = 0xa,       /**<RGB444��λ��Ϊ16*/
    HI_UNF_DISP_LCD_DATA_FMT_RGB666 = 0xb,       /**<RGB666��λ��Ϊ24*/
    HI_UNF_DISP_LCD_DATA_FMT_RGB888 = 0xc,       /**<RGB888��λ��Ϊ24*/
    HI_UNF_DISP_LCD_DATA_FMT_BUTT
}HI_UNF_DISP_LCD_DATA_FMT_E;

/**����LCD��ʱ�����*/
typedef struct hiUNF_DISP_LCD_PARA_S
{
    HI_U32                    VFB;                 /**<��ֱǰ����*/
    HI_U32                    VBB;                 /**<��ֱ������*/
    HI_U32                    VACT;                /**<��ֱ��Ч��*/
    HI_U32                    HFB;                 /**<ˮƽǰ����*/
    HI_U32                    HBB;                 /**<ˮƽ������*/
    HI_U32                    HACT;                /**<ˮƽ��Ч��*/
    HI_U32                    VPW;                 /**<��ֱ������*/
    HI_U32                    HPW;                 /**<ˮƽ������*/
    HI_BOOL                   IDV;                 /**<��Ч�����ź��Ƿ�ת*/
    HI_BOOL                   IHS;                 /**<ˮƽͬ�������ź��Ƿ�ת*/
    HI_BOOL                   IVS;                 /**<��ֱͬ�������ź��Ƿ�ת*/
    HI_BOOL                   ClockReversal;       /**<ʱ���Ƿ�ת*/
    HI_UNF_DISP_LCD_DATA_WIDTH_E   DataWidth;      /**<����λ��*/
    HI_UNF_DISP_LCD_DATA_FMT_E       ItfFormat;      /**<���ݸ�ʽ.*/
    HI_BOOL                   DitherEnable;        /**<�Ƿ�ʹ��Dither*/
} HI_UNF_DISP_LCD_PARA_S;


/**��������ɰ󶨵ĵ��Ӳ�*/
typedef enum hiUNF_DISP_FREE_LAYER_E
{
    HI_UNF_DISP_FREE_LAYER_OSD_0,         /**<�����ɰ�ͼ�β�0*/

    HI_UNF_DISP_FREE_LAYER_BUTT
}HI_UNF_DISP_FREE_LAYER_E;

/**����DISPLAYͨ���ϵĵ��Ӳ�*/
typedef enum hiUNF_DISP_LAYER_E
{
    HI_UNF_DISP_LAYER_VIDEO_0 = 0,   /**<��Ƶ��0*/
    HI_UNF_DISP_LAYER_OSD_0,         /**<ͼ�β�0*/
    HI_UNF_DISP_LAYER_ATTACH_OSD_0,  /**<��ͼ�β�0*/

    HI_UNF_DISP_LAYER_BUTT
}HI_UNF_DISP_LAYER_E;

/**������ʾ��ɫ�Ľṹ�� */
typedef struct  hiUNF_DISP_BG_COLOR_S
{
    HI_U8 u8Red ;            /**<��ɫ����*/
    HI_U8 u8Green ;          /**<��ɫ����*/
    HI_U8 u8Blue ;           /**<��ɫ����*/
} HI_UNF_DISP_BG_COLOR_S;

/********************************ENCODER STRUCT********************************/
/** ��ʾ���Macrovisionģʽö�ٶ���*/
typedef enum hiUNF_DISP_MACROVISION_MODE_E
{
    HI_UNF_DISP_MACROVISION_MODE_TYPE0,  /**<��������0 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE1,  /**<��������1 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE2,  /**<��������2 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE3,  /**<��������3 */
    HI_UNF_DISP_MACROVISION_MODE_CUSTOM, /**<�û��Զ������� */
    HI_UNF_DISP_MACROVISION_MODE_BUTT
} HI_UNF_DISP_MACROVISION_MODE_E;

/** ����ͼ����Ϣ���ݽṹ*/
typedef struct hiUNF_DISP_TTX_DATA_S
{
    HI_U8   *pu8DataAddr;               /**<Ttx�����û������ַ*/
    HI_U32   u32DataLen;                /**<Ttx���ݳ���*/
} HI_UNF_DISP_TTX_DATA_S;


/** ����VBI��Ϣ���ݽṹ*/
typedef struct hiUNF_DISP_VBI_DATA_S
{
    HI_U8  *pu8DataAddr;                 /**<Vbi�����û������ַ*/
    HI_U32  u32DataLen;                  /**<Vbi���ݳ���*/
} HI_UNF_DISP_VBI_DATA_S;


/**����ͼ����Ϣ���ݽṹ */
typedef struct hiUNF_DISP_WSS_DATA_S
{
    HI_BOOL bEnable;                /**<WSS����ʹ�ܡ�HI_TRUE��ʹ�ܣ�HI_FALSE����ֹ*/
    HI_U16  u16Data;                /**<Wss����*/
} HI_UNF_DISP_WSS_DATA_S;

/**����DISPLAYͨ���Ľӿ�����*/
typedef enum hiUNF_DISP_INTF_TYPE_E
{
    HI_UNF_DISP_INTF_TYPE_TV = 0,    /**<����ӿ�ΪTV*/
    HI_UNF_DISP_INTF_TYPE_LCD,       /**<����ӿ�ΪLCD*/
    HI_UNF_DISP_INTF_TYPE_BUTT
}HI_UNF_DISP_INTF_TYPE_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_6 */
/** @{ */  /** <!-- ��DISPLAY�� */

/**
\brief ��ʼ��DISPģ��
\attention \n
����DISPģ�������ӿ�ǰҪ�����ȵ��ñ��ӿ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NOT_EXIST DISP�豸������
\retval ::HI_ERR_DISP_NOT_DEV_FILE  DISP���豸
\retval ::HI_ERR_DISP_DEV_OPEN_ERR  DISP��ʧ��
\see \n
��
*/
HI_S32 HI_UNF_DISP_Init(HI_VOID);

/**
\brief ȥ��ʼ��DISPģ��
\attention \n
�ڵ���::HI_UNF_DISP_Close�ӿڹر����д򿪵�DISP����ñ��ӿ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_CLOSE_ERR  DISP�ر�ʧ��
\see \n
��
*/
HI_S32 HI_UNF_DISP_DeInit(HI_VOID);

/**
\brief ������DISPͨ����
\attention \n
Ŀǰ֧�ֽ�����DISP�󶨵�����DISPͨ���ϣ����ڴ�DISPͨ��ǰ������ɰ󶨲�����
\param[in] enDstDisp     Ŀ��DISPͨ����
\param[in] enSrcDisp     ԴDISPͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_Attach(HI_UNF_DISP_E enDstDisp, HI_UNF_DISP_E enSrcDisp);

/**
\brief ������DISPͨ�����
\attention \n
ֻ���ڹر�����DISPͨ������ܽ��н�󶨲�����
\param[in] enDstDisp     Ŀ��DISPͨ����
\param[in] enSrcDisp     ԴDISPͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_Detach(HI_UNF_DISP_E enDstDisp, HI_UNF_DISP_E enSrcDisp);

/**
\brief ��ָ��DISPͨ��
\attention \n
�ڴ�DISP֮ǰ������ɶ���Ĳ������ã����⻭����˸
\param[in] enDisp   DISPͨ���ţ���μ�::HI_UNF_DISP_E
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_CREATE_ERR    DISP����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_DISP_Open(HI_UNF_DISP_E enDisp);

/**
\brief �ر�ָ��DISP
\attention \n
��
\param[in] enDisp  DISPͨ����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_Close(HI_UNF_DISP_E enDisp);

/**
\brief ��OSD�󶨵�DISP��
\attention \n
������DISP��֮ǰ��ɰ󶨡�
\param[in] enDisp      DISPͨ����
\param[in] enLayer     �ɰ󶨵�ͼ�β�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_AttachOsd(HI_UNF_DISP_E enDisp, HI_UNF_DISP_FREE_LAYER_E enLayer);

/**
\brief ��OSD��DISP���
\attention \n
��
\param[in] enDisp      DISPͨ����
\param[in] enLayer     �ɰ󶨵�ͼ�β�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_DetachOsd(HI_UNF_DISP_E enDisp, HI_UNF_DISP_FREE_LAYER_E enLayer);

/**
\brief ����DISP�Ľӿ�����
\attention \n
�ӿ�������DISPӦ�����õĵ�һ��������
\param[in] enDisp      DISPͨ����
\param[in] enIntfType  DISP�Ľӿ�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetIntfType(HI_UNF_DISP_E enDisp, HI_UNF_DISP_INTF_TYPE_E enIntfType);

/**
\brief ��ȡDISP�Ľӿ�����
\attention \n
��
\param[in] enDisp        DISPͨ����
\param[in] penIntfType   DISP�Ľӿ�����ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetIntfType(HI_UNF_DISP_E enDisp, HI_UNF_DISP_INTF_TYPE_E *penIntfType);

/**
\brief ����DISP����ʽ
\attention \n
ֻ�е�����DISPΪTV�󣬵��ñ��ӿڲ������塣\n
�Ը����DISP��ֻ�����ø������ʽ���Ա����DISP��ֻ�����ñ������ʽ��\n
��ͬԴ��ʾ�����£��ݲ�֧��ˢ���ʷ�50Hz/60Hz����ʽ���磺�ݲ�֧��1080P24/1080P25/1080P30
\param[in] enDisp              DISPͨ����
\param[in] enEncodingFormat    DISP����ʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetFormat(HI_UNF_DISP_E enDisp, HI_UNF_ENC_FMT_E enEncodingFormat);

/**
\brief ��ȡDISP����ʽ
\attention \n
��
\param[in] enDisp               DISPͨ����
\param[in] penEncodingFormat    DISP����ʽָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetFormat(HI_UNF_DISP_E enDisp, HI_UNF_ENC_FMT_E *penEncodingFormat);

/**
\brief ����DACģʽ
\attention \n
DAC��������DISP������Դ�������DISP�Ĳ������ò��򿪺��ٵ��ñ��ӿ����DAC�����á�\n
����6��DAC���Ƽ�0��1��2�������������3��4��5�������������
\param[in] pstDacMode   ָ�����ͣ�DACģʽ����μ�::HI_UNF_OUTPUT_INTERFACE_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�

\see \n
��
*/
HI_S32 HI_UNF_DISP_SetDacMode(const HI_UNF_DISP_INTERFACE_S *pstDacMode);

/**
\brief ��ȡDACģʽ
\attention \n
��
\param[out] pstDacMode    ָ�����ͣ�DACģʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetDacMode(HI_UNF_DISP_INTERFACE_S *pstDacMode);

/**
\brief ����DISP��LCD����
\attention \n
ֻ�е�����DISPΪLCD�󣬵��ñ��ӿڲ������塣
\param[in] enDisp         DISPͨ����
\param[in] pstLcdPara     ָ�����ͣ�LCD��������μ�::HI_UNF_DISP_LCD_PARA_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetLcdPara(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_LCD_PARA_S *pstLcdPara);

/**
\brief ��ȡDISP��LCD����
\attention \n
��
\param[in] enDisp          DISPͨ����
\param[in] pstLcdPara      ָ�����ͣ�LCD����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetLcdPara(HI_UNF_DISP_E enDisp, HI_UNF_DISP_LCD_PARA_S *pstLcdPara);

/**
\brief ����DISP�ϵ��Ӳ��Z��
\attention \n
��
\param[in] enDisp          DISPͨ����
\param[in] enLayer         DISP�ϵĵ��Ӳ�
\param[in] enZFlag         Z����ڷ�ʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetLayerZorder(HI_UNF_DISP_E enDisp, HI_UNF_DISP_LAYER_E enLayer, HI_LAYER_ZORDER_E enZFlag);

/**
\brief ��ȡDISP�ϵ��Ӳ��Z��
\attention \n
�ڸ߱��������£�����DISP�����û��Զ�ͬ��������DISP������DISP�����û��Զ�ͬ��������DISP��
\param[in] enDisp            DISPͨ����
\param[in] enLayer           DISP�ϵĵ��Ӳ�
\param[in] pu32Zorder        ���Ӳ�Z����ֵ����ֵԽ�����ȼ�Խ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetLayerZorder(HI_UNF_DISP_E enDisp, HI_UNF_DISP_LAYER_E enLayer, HI_U32 *pu32Zorder);

/**
\brief ����DISP����ɫ
\attention \n
��
\param[in] enDisp       DISPͨ����
\param[in] pstBgColor   ָ�����ͣ������õ���ʾ�������ɫ����μ�::HI_UNF_BG_COLOR_S
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetBgColor(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_BG_COLOR_S *pstBgColor);

/**
\brief ��ȡDISP����ɫ
\attention \n
�ڸ߱��������£�����DISP�����û��Զ�ͬ��������DISP������DISP�����û��Զ�ͬ��������DISP��
\param[in] enDisp         DISPͨ����
\param[out] pstBgColor    ָ�����ͣ���ʾ�������ɫ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetBgColor(HI_UNF_DISP_E enDisp, HI_UNF_DISP_BG_COLOR_S *pstBgColor);

/**
\brief ����DISP����
\attention \n
����100��ֵ��100����
\param[in] enDisp           DISPͨ����
\param[in] u32Brightness    �����õ���ʾ�������ֵ��ȡֵ��ΧΪ0��100��0����С���ȣ�100���������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetBrightness(HI_UNF_DISP_E enDisp, HI_U32 u32Brightness);

/**
\brief ��ȡDISP����
\attention \n
��ѯ��Ĭ������ֵΪ50��\n
�ڸ߱��������£�����DISP�����û��Զ�ͬ��������DISP������DISP�����û��Զ�ͬ��������DISP��
\param[in] enDisp              DISPͨ����
\param[out] pu32Brightness     ָ�����ͣ���ʾ�������ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetBrightness(HI_UNF_DISP_E enDisp, HI_U32 *pu32Brightness);

/**
\brief ����DISP�Աȶ�
\attention \n
����100��ֵ��100����
\param[in] enDisp          DISPͨ����
\param[in] u32Contrast     �����õ���ʾ����Աȶ�ֵ��ȡֵ��ΧΪ0��100��0����С�Աȶȣ�100�����Աȶ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetContrast(HI_UNF_DISP_E enDisp, HI_U32 u32Contrast);

/**
\brief ��ȡDISP�Աȶ�
\attention \n
��ѯ��Ĭ�϶Աȶ�ֵΪ50��\n
�ڸ߱��������£�����DISP�����û��Զ�ͬ��������DISP������DISP�����û��Զ�ͬ��������DISP��
\param[in] enDisp           DISPͨ����
\param[out] pu32Contrast    ָ�����ͣ���ʾ����Աȶ�ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetContrast(HI_UNF_DISP_E enDisp, HI_U32 *pu32Contrast);

/**
\brief ����DISP���Ͷ�
\attention \n
����100��ֵ��100����
\param[in] enDisp             DISPͨ����
\param[in] u32Saturation      �����õ���ʾ������Ͷ�ֵ��ȡֵ��ΧΪ0��100��0����С���Ͷȣ�100����󱥺Ͷ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetSaturation(HI_UNF_DISP_E enDisp, HI_U32 u32Saturation);

/**
\brief ��ȡDISP���Ͷ�
\attention \n
��ѯ��Ĭ�ϱ��Ͷ�ֵΪ50��\n
�ڸ߱��������£�����DISP�����û��Զ�ͬ��������DISP������DISP�����û��Զ�ͬ��������DISP��
\param[in] enDisp             DISPͨ����
\param[out] pu32Saturation    ָ�����ͣ���ʾ������Ͷ�ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetSaturation(HI_UNF_DISP_E enDisp, HI_U32 *pu32Saturation);

/**
\brief ����DISPɫ��
\attention \n
��
\param[in] enDisp           DISPͨ����
\param[in] u32HuePlus       ��ʾ���ɫ������ֵ����ΧΪ0��100��0����ʾ��Сɫ�����棻100����ʾ���ɫ������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetHuePlus(HI_UNF_DISP_E enDisp, HI_U32 u32HuePlus);

/**
\brief ��ȡDISPɫ��
\attention \n
��ѯ��Ĭ��ɫ��ֵΪ50��\n
�ڸ߱��������£�����DISP�����û��Զ�ͬ��������DISP������DISP�����û��Զ�ͬ��������DISP��
\param[in] enDisp           DISPͨ����
\param[out] pu32HuePlus     ָ�����ͣ���ʾ���ɫ������ֵ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetHuePlus(HI_UNF_DISP_E enDisp, HI_U32 *pu32HuePlus);

/**
\brief ����Ӧ�Աȶȵ���
\attention \n
��
\param[in] enDisp           DISPͨ����
\param[out] bEnable         ʹ��/��ֹ��־
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetAccEnable(HI_UNF_DISP_E enDisp, HI_BOOL bEnable);

/**
\brief ����ͼ������PES��
\attention \n
��
\param[in] enDisp            DISPͨ����
\param[in] pstTtxData        ָ�����ͣ�ָ��ͼ�����ݰ���ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SendTtxData(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_TTX_DATA_S *pstTtxData);

/**
\brief ����VBI��Vertical Blanking Interval������PES��
\attention \n
��
\param[in] enDisp            DISPͨ����
\param[in] pstVbiData        ָ�����ͣ�ָ��VBI���ݰ���ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SendVbiData(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_VBI_DATA_S *pstVbiData);

/**
\brief ֱ������WSS��Wide Screen Singnalling������
\attention \n
��
\param[in] enDisp           DISPͨ����
\param[in] pstWssData       ָ�����ͣ�ָ��WSS���ݵ�ָ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetWss(HI_UNF_DISP_E enDisp, const HI_UNF_DISP_WSS_DATA_S *pstWssData);

/**
\brief ����Macrovisionģʽ
\attention \n
��
\param[in] enDisp          DISPͨ����
\param[in] enMode          Macrovisionģʽ����μ�::HI_UNF_MACROVISION_MODE_E
\param[in] pData           ָ�����ͣ��Զ����Macrovision��������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_SetMacrovision(HI_UNF_DISP_E enDisp, HI_UNF_DISP_MACROVISION_MODE_E enMode, const HI_VOID *pData);

/**
\brief ��ȡMacrovisionģʽ
\attention \n
��
\param[in] enDisp      DISPͨ����
\param[out] penMode    ָ�����ͣ�MACROVISIONģʽ
\param[out] pData      ָ�����ͣ�����penMode=HI_MACROVISION_MODE_CUSTOMʱ��Ч
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_DISP_DEV_NO_INIT   DISPδ��ʼ��
\retval ::HI_ERR_DISP_NULL_PTR      ����ָ��Ϊ��
\retval ::HI_ERR_DISP_INVALID_PARA  ��������Ƿ�
\retval ::HI_ERR_DISP_INVALID_OPT   �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_DISP_GetMacrovision(HI_UNF_DISP_E enDisp, HI_UNF_DISP_MACROVISION_MODE_E *penMode, const HI_VOID *pData);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif
