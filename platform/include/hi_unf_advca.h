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
/** @{ */  /** <!-- 【ADVCA】 */


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
/** @{ */  /** <!-- 【ADVCA】 */

/**
\brief 初始化advance CA模块
\attention \n
在进行advance CA相关操作前应该首先调用本接口\n
重复调用本接口，会返回成功
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_OPEN_ERR 打开CA设备失败
\see \n
::HI_UNF_ADVCA_DeInit
*/
HI_S32 HI_UNF_ADVCA_Init(HI_VOID);

/**
\brief 去初始化advance CA模块
\attention \n
无
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_ADVCA_DeInit(HI_VOID);


/**
\brief 获取芯片ID
\attention \n
芯片ID只能读不能写
\param[out] pu32ChipId   芯片ID
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_ADVCA_GetChipId(HI_U32 *pu32ChipId);

/**
\brief 获取Market ID
\attention \n
无
\param[out] pu32MarketId   针对市场的标识序号
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT  CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA  输入参数非法
\see \n
::HI_UNF_ADVCA_SetMarketId
*/
HI_S32 HI_UNF_ADVCA_GetMarketId(HI_U32 *pu32MarketId);

/**
\brief 设置Market ID
\attention \n
在机顶盒出厂时设置，仅支持设置一次 设置后重启生效
\param[in] u32MarketId   针对市场的标识序号
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT  CA未初始化
\retval ::HI_ERR_CA_SETPARAM_AGAIN  重复设置
\see \n
无
*/
HI_S32 HI_UNF_ADVCA_SetMarketId(HI_U32 u32MarketId);


/**
\brief 获取机顶盒序列号
\attention \n
无
\param[out] pu32StbSn   机顶盒序列号
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_SetStbSn
*/
HI_S32 HI_UNF_ADVCA_GetStbSn(HI_U32 *pu32StbSn);

/**
\brief 设置机顶盒序列号
\attention \n
在机顶盒出厂时设置，仅支持设置一次 设置后重启生效
\param[in] u32StbSn   机顶盒序列号
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT  CA未初始化
\retval ::HI_ERR_CA_SETPARAM_AGAIN  重复设置
\see \n
无
*/
HI_S32 HI_UNF_ADVCA_SetStbSn(HI_U32 u32StbSn);

/** 
\brief  设置固定使用硬件CW字
\attention
在机顶盒出厂时选择是否设置，仅支持设置一次
默认根据Demux的配置选择使用硬件CW字还是软件CW字
\param[in] 

\retval ::HI_SUCCESS                  成功
\retval ::HI_ERR_CA_NOT_INIT          CA未初始化
\return ::HI_ERR_CA_SETPARAM_AGAIN    重复设置参数

\see
\li :: 
*/
HI_S32 HI_UNF_ADVCA_LockHardCwSel(HI_VOID);

/** 
\brief 设置必须对BootLoader进行解密
\attention
在机顶盒出厂时选择是否设置，仅支持设置一次
默认根据Flash中的数据标识，决定BootLoader是否需要解密

\retval ::HI_SUCCESS                  成功
\retval ::HI_ERR_CA_NOT_INIT          CA未初始化
\return ::HI_ERR_CA_SETPARAM_AGAIN    重复设置参数

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_LockBootDecEn(HI_VOID);

/** 
\brief 设置固定用硬件密钥作为R2R的密钥
\attention
在机顶盒出厂时选择是否设置，仅支持设置一次
默认根据CPU配置选择 使用软件密钥加密 还是硬件密钥加密

\retval ::HI_SUCCESS                  成功
\retval ::HI_ERR_CA_NOT_INIT          CA未初始化
\return ::HI_ERR_CA_SETPARAM_AGAIN    重复设置参数

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_LockR2RHardKey(HI_VOID);

/** 
\brief 关闭Link Protection功能
\attention
在机顶盒出厂时选择是否设置，仅支持设置一次
默认开启Link Protection功能
\retval ::HI_SUCCESS                  成功
\retval ::HI_ERR_CA_NOT_INIT          CA未初始化
\return ::HI_ERR_CA_SETPARAM_AGAIN    重复设置参数

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_DisableLinkProtection(HI_VOID);

/** 
\brief 关闭SelfBoot功能
\attention
在机顶盒出厂时选择是否设置，仅支持设置一次
默认使能SelfBoot功能

\retval ::HI_SUCCESS                  成功
\retval ::HI_ERR_CA_NOT_INIT          CA未初始化
\return ::HI_ERR_CA_SETPARAM_AGAIN    重复设置参数

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_DisableSelfBoot(HI_VOID);


/**
\brief 获取安全启动使能状态
\attention \n
无
\param[out] pbEnable   安全启动是否使能，HI_TRUE 使能， HI_FALSE 不使能
\param[out] penFlashType 仅在安全启动使能时有效，表示安全启动的Flash类型
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_ADVCA_GetSecBootStat(HI_BOOL *pbEnable,HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType);

/**
\brief 设置安全启动使能,同时指定安全启动的Flash类型
\attention \n
只能使能，使能之后不可修改。
\param[in]  enFlashType  启动的Flash类型
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_SETPARAM_AGAIN  重复设置
\see \n
无
*/
HI_S32 HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType);

/**
\brief 获取JTAG调试口模式
\attention \n
无
\param[out] penJtagMode   JTAG调试口模式
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_ADVCA_GetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E *penJtagMode);

/**
\brief 设置JTAG调试口模式  
\attention \n
不支持设置为打开状态。\n
打开的时候可以关闭或设置为密钥保护状态。\n
处于密钥保护状态时可以关闭。\n
关闭之后不能打开和设置为密钥保护状态
\param[in] enJtagMode   JTAG调试口模式
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\retval ::HI_ERR_CA_SETPARAM_AGAIN 重复设置
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_ADVCA_SetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E enJtagMode);

/**
\brief 获取OTP写保护是否使能
\attention \n
无
\param[out] pbEnable   安全启动使能，HI_TRUE 使能， HI_FALSE 不使能
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_ADVCA_GetOtpWrProtect(HI_BOOL *pbEnable);

/**
\brief 设置OTP写保护使能  
\attention \n
只能使能，使能之后不可修改。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_SETPARAM_AGAIN  重复设置
\see \n
无
*/
HI_S32 HI_UNF_ADVCA_SetOtpWrProtect(HI_VOID);

/**
\brief 获取R2R key ladder级数
\attention \n
无
\param[out] penStage   key ladder级数
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief 设置R2R key ladder的级数   
\attention \n
机顶盒出厂时设置 仅能设置一次 不可更改
\param[in] enStage   key ladder级数\n
		   取值只能为HI_UNF_ADVCA_KEYLADDER_LEV2 或者 HI_UNF_ADVCA_KEYLADDER_LEV3
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief 获取DVB key ladder的级数
\attention \n
无
\param[out] penStage   key ladder级数
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief 设置DVB key ladder的级数   
\attention \n
机顶盒出厂时设置 仅能设置一次 不可更改
\param[in] enStage  key ladder级数\n
		   取值只能为HI_UNF_ADVCA_KEYLADDER_lev2 或者 HI_UNF_ADVCA_KEYLADDER_lev3
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief 为R2R key ladder配置会话密钥   
\attention \n
注意配置的级数不能超过设置的级数值，最后一级由CIPHER模块内部配置，不用通过此接口配置。\n
也就是说，对于3级key ladder，只用配置会话密钥1和会话密钥2。\n
对于2级的key ladder，只用配置会话密钥1。\n
请先调用HI_UNF_ADVCA_SetR2RKeyLadderStage设置key ladder级数。\n
会话密钥可以初始时设置一次，也可以随时修改。
\param[in] enStage    密钥级数，[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]
\param[in] pu8Key     保护密钥指针，共128bit(16byte)
\retval ::HI_SUCCESS  成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\retval ::HI_ERR_CA_WAIT_TIMEOUT CA等待加解密超时
\retval ::HI_ERR_CA_R2R_DECRYPT  R2R解密失败
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

/**
\brief 为DVB key ladder配置会话密钥   
\attention \n
注意配置的级数不能超过设置的级数值，最后一级由Descrambler模块内部配置，不用通过此接口配置。\n
也就是说，对于3级key ladder，只用配置会话密钥1和会话密钥2。\n
对于2级的key ladder，只用配置会话密钥1。\n
请先调用HI_UNF_ADVCA_SetR2RKeyLadderStage设置key ladder级数。\n
会话密钥可以初始时设置一次，也可以随时修改。
\param[in] enStage    密钥级数，[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]
\param[in] pu8Key     保护密钥指针，共128bit(16byte)
\retval ::HI_SUCCESS  成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\retval ::HI_ERR_CA_WAIT_TIMEOUT CA等待加解密超时
\retval ::HI_ERR_CA_CW_DECRYPT   CW解密失败

\see \n
无
*/
HI_S32 HI_UNF_ADVCA_SetDVBSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);


/** 
\brief  加载LPK
\attention
无
\param[in] pEncryptedLpk  用R2RROOTKEY加密的LPK
\retval ::HI_SUCCESS               成功
\retval ::HI_ERR_CA_NOT_INIT       CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA   输入参数非法
\retval ::HI_ERR_CA_NOT_SUPPORT    功能不支持                         
\retval ::HI_ERR_CA_WAIT_TIMEOUT   CA等待加解密超时
\retval ::HI_ERR_CA_LPK_DECRYPT    LPK解密失败
\see
\li ::
*/

HI_S32 HI_UNF_ADVCA_LoadLpk(HI_U8 *pEncryptedLpk);

/** 
\brief 解密智能卡传送给CPU的经过链路保护的分组数据 (Link Protection)
\attention
无
\param[in] pEncryptedBlock   经LPK加密的分组数据
\param[out] pPlainBlock      明文分组数据 空间由调用者分配 
\retval ::HI_SUCCESS               成功
\retval ::HI_ERR_CA_NOT_INIT       CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA   输入参数非法
\retval ::HI_ERR_CA_NOT_SUPPORT    功能不支持                         
\retval ::HI_ERR_CA_WAIT_TIMEOUT   CA等待加解密超时
\retval ::HI_ERR_CA_LPK_DECRYPT    LPK解密失败
\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_DecryptLptBlock(HI_U8 *pEncryptedBlock,HI_U8 *pPlainBlock);

/** 
\brief 解密智能卡传送给CPU的经过链路保护的数据 (Link Protection)
\attention
无
\param[in] pCipherText   密文
\param[in] s32TextLen    密文长度 要求大于一个Block长度 8byte
\param[out] pPlainText   明文
\retval ::HI_SUCCESS               成功
\retval ::HI_ERR_CA_NOT_INIT       CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA   输入参数非法
\retval ::HI_ERR_CA_NOT_SUPPORT    功能不支持                         
\retval ::HI_ERR_CA_WAIT_TIMEOUT   CA等待加解密超时
\retval ::HI_ERR_CA_LPK_DECRYPT    LPK解密失败
\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_DecryptLptParam(HI_U8 *pCipherText,HI_S32 s32TextLen,HI_U8 *pPlainText);

/** 
\brief 加密软件保护密钥
\attention
机顶盒出厂时 从Flash上读取明文的SWPK(Software Protect Key),调用该接口加密,将加密的SWPK存储在Flash中，用于安全启动
\param[in]  pPlainSwpk    明文SWPK
\param[out] pEncryptedSwpk  加密后的SWPK

\retval ::HI_SUCCESS               成功
\retval ::HI_ERR_CA_NOT_INIT       CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA   输入参数非法
\retval ::HI_ERR_CA_NOT_SUPPORT    功能不支持                         
\retval ::HI_ERR_CA_WAIT_TIMEOUT   CA等待加解密超时
\return ::HI_ERR_CA_SWPK_ENCRYPT   SWPK加密失败

\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_EncryptSWPK(HI_U8 *pPlainSwpk,HI_U8 *pEncryptedSwpk);

/**
\brief 设置DVB key ladder的算法   
\attention \n
每次会话过程中使用key ladder之前，须设置具体算法, 系统初始默认值 HI_UNF_ADVCA_ALG_TYPE_TDES；\n
本次会话过程中，建议保持算法的稳定不变。
\param[in] enType  key ladder算法\n
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief 设置R2R key ladder的算法   
\attention \n
每次会话过程中使用key ladder之前，须设置具体算法, 系统初始默认值 HI_UNF_ADVCA_ALG_TYPE_TDES；\n
本次会话过程中，建议保持算法的稳定不变。
\param[in] enType  key ladder算法\n
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief 获取 DVB key ladder的算法   
\attention \n
无
\param[in] pEnType  key ladder算法\n
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
\brief 获取 R2R key ladder的算法   
\attention \n
无
\param[in] enType  key ladder算法\n
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_INVALID_PARA 输入参数非法
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
\brief 写入HDCP KEY 
\attention \n
仅能设置一次 不可更改
\param[in] HI_UNF_ADVCA_HDCPKEY_S stHdcpKey\n
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CA_NOT_INIT CA未初始化
\retval ::HI_ERR_CA_SETPARAM_AGAIN 重复设置参数
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

