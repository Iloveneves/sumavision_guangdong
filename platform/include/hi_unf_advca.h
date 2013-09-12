/******************************************************************************

Copyright (C), 2004-2010, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_advca.h
Version       : Initial
Author        : Hisilicon multimedia software group
Created       : 2010-05-05
Last Modified :
Description   : Hisilicon CA API declaration
Function List :
History       :
* Version   Date         Author     DefectNum    Description
* main\1    2010-05-05   j40671     NULL         Create this file.
* main\2    2010-02-10   x57522     NULL         Modify this file.
******************************************************************************/
/**
 * \file
 * \brief provide CA info.
 */

#ifndef __HI_UNF_ADVCA_H__
#define __HI_UNF_ADVCA_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_11 */
/** @{ */  /** <!-- ��ADVCA�� */


/** advanced CA session serect key class*/
typedef enum hiUNF_ADVCA_KEYLADDER_LEV_E
{
	HI_UNF_ADVCA_KEYLADDER_LEV1 = 0,   /**<session serect key level 1*/
	HI_UNF_ADVCA_KEYLADDER_LEV2 ,	   /**<session serect key level 2*/
	HI_UNF_ADVCA_KEYLADDER_LEV3 ,	   /**<session serect key level 3*/

	HI_UNF_ADVCA_KEYLADDER_BUTT 
}HI_UNF_ADVCA_KEYLADDER_LEV_E;


/** advanced CA Encrypt arith*/
typedef enum hiUNF_ADVCA_ALG_TYPE_E
{
    HI_UNF_ADVCA_ALG_TYPE_TDES = 0,    /**<Encrypt arith :3 DES*/
    HI_UNF_ADVCA_ALG_TYPE_AES,         /**<Encrypt arith : AES*/

    HI_UNF_ADVCA_ALG_TYPE_BUTT
}HI_UNF_ADVCA_ALG_TYPE_E;

/** FLASH device types*/
typedef enum hiUNF_ADVCA_FLASH_TYPE_E
{
    HI_UNF_ADVCA_FLASH_TYPE_SPI = 0,     /**<SPI flash*/
    HI_UNF_ADVCA_FLASH_TYPE_NAND,        /**<nand flash*/
    HI_UNF_ADVCA_FLASH_TYPE_NOR,         /**<nor flash*/
    HI_UNF_ADVCA_FLASH_TYPE_EMMC,        /**<eMMC*/
    HI_UNF_ADVCA_FLASH_TYPE_BUTT
}HI_UNF_ADVCA_FLASH_TYPE_E;

/** JTAG protect mode*/
typedef enum hiUNF_ADVCA_JTAG_MODE_E
{
    HI_UNF_ADVCA_JTAG_MODE_OPEN = 0,     
    HI_UNF_ADVCA_JTAG_MODE_PROTECT,       
    HI_UNF_ADVCA_JTAG_MODE_CLOSED,     

    HI_UNF_ADVCA_JTAG_MODE_BUTT
}HI_UNF_ADVCA_JTAG_MODE_E;

typedef struct hiUNF_DECRYPT_HDCP_S
{
	HI_U8 u8KSV[5];              /**<HDCP KSV:40bits, Orignal data */
	HI_U8 u8PrivateKey[280];     /**<HDCP Device Private key:40*56bits, Orignal data */
}HI_UNF_DECRYPT_HDCP_S;

typedef struct hiUNF_ENCRYPT_HDCP_S
{
	HI_U8 u8EncryptKey[384];     /**<HDCP Encryption key */
}HI_UNF_ENCRYPT_HDCP_S;

typedef struct hiUNF_ADVCA_HDCPKEY_S
{
    HI_BOOL EncryptionFlag;                 /**<HI_TRUE:Encryption, HI_FALSE: Uncryption */
    
    union
    {
        HI_UNF_DECRYPT_HDCP_S DecryptData;  /**<Orignal data, if EncryptionFlag == HI_FALSE */
        HI_UNF_ENCRYPT_HDCP_S EncryptData;  /**<Encrpytion data, if EncryptionFlag == HI_TRUE */
    }key;

    HI_U32 Reserved;                        /**<Reserved for future use */
}HI_UNF_ADVCA_HDCPKEY_S;


/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_12 */
/** @{ */  /** <!-- ��ADVCA�� */

/**
\brief ��ʼ��advance CAģ��
\attention \n
�ڽ���advance CA��ز���ǰӦ�����ȵ��ñ��ӿ�\n
�ظ����ñ��ӿڣ��᷵�سɹ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_OPEN_ERR ��CA�豸ʧ��
\see \n
::HI_UNF_ADVCA_DeInit
*/
HI_S32 HI_UNF_ADVCA_Init(HI_VOID);

/**
\brief ȥ��ʼ��advance CAģ��
\attention \n
��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_ADVCA_DeInit(HI_VOID);


/**
\brief ��ȡоƬID
\attention \n
оƬIDֻ�ܶ�����д
\param[out] pu32ChipId   оƬID
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_ADVCA_GetChipId(HI_U32 *pu32ChipId);

/**
\brief ��ȡMarket ID
\attention \n
��
\param[out] pu32MarketId   ����г��ı�ʶ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT  CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA  ��������Ƿ�
\see \n
::HI_UNF_ADVCA_SetMarketId
*/
HI_S32 HI_UNF_ADVCA_GetMarketId(HI_U32 *pu32MarketId);

/**
\brief ����Market ID
\attention \n
�ڻ����г���ʱ���ã���֧������һ�� ���ú�������Ч
\param[in] u32MarketId   ����г��ı�ʶ���
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT  CAδ��ʼ��
\retval ::HI_ERR_CA_SETPARAM_AGAIN  �ظ�����
\see \n
��
*/
HI_S32 HI_UNF_ADVCA_SetMarketId(HI_U32 u32MarketId);


/**
\brief ��ȡ���������к�
\attention \n
��
\param[out] pu32StbSn   ���������к�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_SetStbSn
*/
HI_S32 HI_UNF_ADVCA_GetStbSn(HI_U32 *pu32StbSn);

/**
\brief ���û��������к�
\attention \n
�ڻ����г���ʱ���ã���֧������һ�� ���ú�������Ч
\param[in] u32StbSn   ���������к�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT  CAδ��ʼ��
\retval ::HI_ERR_CA_SETPARAM_AGAIN  �ظ�����
\see \n
��
*/
HI_S32 HI_UNF_ADVCA_SetStbSn(HI_U32 u32StbSn);

/** 
\brief  ���ù̶�ʹ��Ӳ��CW��
\attention
�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϸ���Demux������ѡ��ʹ��Ӳ��CW�ֻ������CW��
\param[in] 

\retval ::HI_SUCCESS                  �ɹ�
\retval ::HI_ERR_CA_NOT_INIT          CAδ��ʼ��
\return ::HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò���

\see
\li :: 
*/
HI_S32 HI_UNF_ADVCA_LockHardCwSel(HI_VOID);

/** 
\brief ���ñ����BootLoader���н���
\attention
�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϸ���Flash�е����ݱ�ʶ������BootLoader�Ƿ���Ҫ����

\retval ::HI_SUCCESS                  �ɹ�
\retval ::HI_ERR_CA_NOT_INIT          CAδ��ʼ��
\return ::HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò���

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_LockBootDecEn(HI_VOID);

/** 
\brief ���ù̶���Ӳ����Կ��ΪR2R����Կ
\attention
�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϸ���CPU����ѡ�� ʹ�������Կ���� ����Ӳ����Կ����

\retval ::HI_SUCCESS                  �ɹ�
\retval ::HI_ERR_CA_NOT_INIT          CAδ��ʼ��
\return ::HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò���

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_LockR2RHardKey(HI_VOID);

/** 
\brief �ر�Link Protection����
\attention
�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�Ͽ���Link Protection����
\retval ::HI_SUCCESS                  �ɹ�
\retval ::HI_ERR_CA_NOT_INIT          CAδ��ʼ��
\return ::HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò���

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_DisableLinkProtection(HI_VOID);

/** 
\brief �ر�SelfBoot����
\attention
�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ��ʹ��SelfBoot����

\retval ::HI_SUCCESS                  �ɹ�
\retval ::HI_ERR_CA_NOT_INIT          CAδ��ʼ��
\return ::HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò���

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_DisableSelfBoot(HI_VOID);


/**
\brief ��ȡ��ȫ����ʹ��״̬
\attention \n
��
\param[out] pbEnable   ��ȫ�����Ƿ�ʹ�ܣ�HI_TRUE ʹ�ܣ� HI_FALSE ��ʹ��
\param[out] penFlashType ���ڰ�ȫ����ʹ��ʱ��Ч����ʾ��ȫ������Flash����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_ADVCA_GetSecBootStat(HI_BOOL *pbEnable,HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType);

/**
\brief ���ð�ȫ����ʹ��,ͬʱָ����ȫ������Flash����
\attention \n
ֻ��ʹ�ܣ�ʹ��֮�󲻿��޸ġ�
\param[in]  enFlashType  ������Flash����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_SETPARAM_AGAIN  �ظ�����
\see \n
��
*/
HI_S32 HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType);

/**
\brief ��ȡJTAG���Կ�ģʽ
\attention \n
��
\param[out] penJtagMode   JTAG���Կ�ģʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_ADVCA_GetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E *penJtagMode);

/**
\brief ����JTAG���Կ�ģʽ  
\attention \n
��֧������Ϊ��״̬��\n
�򿪵�ʱ����Թرջ�����Ϊ��Կ����״̬��\n
������Կ����״̬ʱ���Թرա�\n
�ر�֮���ܴ򿪺�����Ϊ��Կ����״̬
\param[in] enJtagMode   JTAG���Կ�ģʽ
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\retval ::HI_ERR_CA_SETPARAM_AGAIN �ظ�����
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_ADVCA_SetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E enJtagMode);

/**
\brief ��ȡOTPд�����Ƿ�ʹ��
\attention \n
��
\param[out] pbEnable   ��ȫ����ʹ�ܣ�HI_TRUE ʹ�ܣ� HI_FALSE ��ʹ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_ADVCA_GetOtpWrProtect(HI_BOOL *pbEnable);

/**
\brief ����OTPд����ʹ��  
\attention \n
ֻ��ʹ�ܣ�ʹ��֮�󲻿��޸ġ�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_SETPARAM_AGAIN  �ظ�����
\see \n
��
*/
HI_S32 HI_UNF_ADVCA_SetOtpWrProtect(HI_VOID);

/**
\brief ��ȡR2R key ladder����
\attention \n
��
\param[out] penStage   key ladder����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief ����R2R key ladder�ļ���   
\attention \n
�����г���ʱ���� ��������һ�� ���ɸ���
\param[in] enStage   key ladder����\n
		   ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_LEV2 ���� HI_UNF_ADVCA_KEYLADDER_LEV3
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief ��ȡDVB key ladder�ļ���
\attention \n
��
\param[out] penStage   key ladder����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief ����DVB key ladder�ļ���   
\attention \n
�����г���ʱ���� ��������һ�� ���ɸ���
\param[in] enStage  key ladder����\n
		   ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_lev2 ���� HI_UNF_ADVCA_KEYLADDER_lev3
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief ΪR2R key ladder���ûỰ��Կ   
\attention \n
ע�����õļ������ܳ������õļ���ֵ�����һ����CIPHERģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetR2RKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ�
\param[in] enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]
\param[in] pu8Key     ������Կָ�룬��128bit(16byte)
\retval ::HI_SUCCESS  �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\retval ::HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ
\retval ::HI_ERR_CA_R2R_DECRYPT  R2R����ʧ��
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

/**
\brief ΪDVB key ladder���ûỰ��Կ   
\attention \n
ע�����õļ������ܳ������õļ���ֵ�����һ����Descramblerģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetR2RKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ�
\param[in] enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]
\param[in] pu8Key     ������Կָ�룬��128bit(16byte)
\retval ::HI_SUCCESS  �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\retval ::HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ
\retval ::HI_ERR_CA_CW_DECRYPT   CW����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_ADVCA_SetDVBSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);


/** 
\brief  ����LPK
\attention
��
\param[in] pEncryptedLpk  ��R2RROOTKEY���ܵ�LPK
\retval ::HI_SUCCESS               �ɹ�
\retval ::HI_ERR_CA_NOT_INIT       CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧��                         
\retval ::HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ
\retval ::HI_ERR_CA_LPK_DECRYPT    LPK����ʧ��
\see
\li ::
*/

HI_S32 HI_UNF_ADVCA_LoadLpk(HI_U8 *pEncryptedLpk);

/** 
\brief �������ܿ����͸�CPU�ľ�����·�����ķ������� (Link Protection)
\attention
��
\param[in] pEncryptedBlock   ��LPK���ܵķ�������
\param[out] pPlainBlock      ���ķ������� �ռ��ɵ����߷��� 
\retval ::HI_SUCCESS               �ɹ�
\retval ::HI_ERR_CA_NOT_INIT       CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧��                         
\retval ::HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ
\retval ::HI_ERR_CA_LPK_DECRYPT    LPK����ʧ��
\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_DecryptLptBlock(HI_U8 *pEncryptedBlock,HI_U8 *pPlainBlock);

/** 
\brief �������ܿ����͸�CPU�ľ�����·���������� (Link Protection)
\attention
��
\param[in] pCipherText   ����
\param[in] s32TextLen    ���ĳ��� Ҫ�����һ��Block���� 8byte
\param[out] pPlainText   ����
\retval ::HI_SUCCESS               �ɹ�
\retval ::HI_ERR_CA_NOT_INIT       CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧��                         
\retval ::HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ
\retval ::HI_ERR_CA_LPK_DECRYPT    LPK����ʧ��
\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_DecryptLptParam(HI_U8 *pCipherText,HI_S32 s32TextLen,HI_U8 *pPlainText);

/** 
\brief �������������Կ
\attention
�����г���ʱ ��Flash�϶�ȡ���ĵ�SWPK(Software Protect Key),���øýӿڼ���,�����ܵ�SWPK�洢��Flash�У����ڰ�ȫ����
\param[in]  pPlainSwpk    ����SWPK
\param[out] pEncryptedSwpk  ���ܺ��SWPK

\retval ::HI_SUCCESS               �ɹ�
\retval ::HI_ERR_CA_NOT_INIT       CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA   ��������Ƿ�
\retval ::HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧��                         
\retval ::HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ
\return ::HI_ERR_CA_SWPK_ENCRYPT   SWPK����ʧ��

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_EncryptSWPK(HI_U8 *pPlainSwpk,HI_U8 *pEncryptedSwpk);

/**
\brief ����DVB key ladder���㷨   
\attention \n
ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣
\param[in] enType  key ladder�㷨\n
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief ����R2R key ladder���㷨   
\attention \n
ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣
\param[in] enType  key ladder�㷨\n
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief ��ȡ DVB key ladder���㷨   
\attention \n
��
\param[in] pEnType  key ladder�㷨\n
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
\brief ��ȡ R2R key ladder���㷨   
\attention \n
��
\param[in] enType  key ladder�㷨\n
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_INVALID_PARA ��������Ƿ�
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
\brief д��HDCP KEY 
\attention \n
��������һ�� ���ɸ���
\param[in] HI_UNF_ADVCA_HDCPKEY_S stHdcpKey\n
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CA_NOT_INIT CAδ��ʼ��
\retval ::HI_ERR_CA_SETPARAM_AGAIN �ظ����ò���
\see \n
::HI_UNF_ADVCA_HDCPKEY_S
*/
HI_S32 HI_UNF_ADVCA_SetHDCPKey(HI_UNF_ADVCA_HDCPKEY_S stHdcpKey);
/** @} */  /** <!-- ==== API declaration end ==== */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_ADVCA_H__ */

