/**
 \file
 \brief 系统共用的数据类型
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
/** @{ */  /** <!-- 【encoder】 */

/**编码器属性*/
typedef struct 
{
   HIGO_IMGTYPE_E ExpectType;   /**< 编码图片类型*/
   HI_U32 QualityLevel;        /**<1-99级, 级别越高，质量越好，编码出来图像文件或内存也越大，只对JPEG有效*/ 	
}HIGO_ENC_ATTR_S;
/** @} */  /*! <!-- Structure Definition end */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_5 */
/** @{ */  /** <!-- 【ENCODER】 */
 /** 
\brief 编码器初始化
\attention \n
::HI_GO_Init中已包含对该接口的调用
\param  无

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
::HI_GO_Init \n
::HI_GO_DeinitDecoder
*/

HI_S32 HI_GO_InitEncoder(HI_VOID);


/** 
\brief 编码器去初始化
\attention \n
::HI_GO_Deinit中已包含对该接口的调用
\param  无

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_Deinit \n
::HI_GO_InitDecoder
*/

HI_S32 HI_GO_DeinitEncoder(HI_VOID);

/**
\brief 将一个surface编码到指定图像格式并保存到文件中
\attention \n
支持编码成bmp格式文件
(是否支持编码成JPEG,取决于硬件平台)

\param[in] hSurface  需要编码的surface,
\param[in] pFile     编码后的文件名，可以为空，为空则用当前时间[年]-[月]-[日]-[时]-[分]-[秒]来命名
\param[in] pAttr     编码设置的属性，不可为空

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
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
\brief 将一个surface编码到指定图像格式并保存到内存中，请自行保证指定内存块足够大
\attention \n
支持编码成bmp格式数据存放到指定的内存中
(是否支持编码成JPEG,取决于硬件平台)

\param[in] hSurface     需要编码的surface,
\param[in] pMem         保存编码后的图像数据内存块的起始地址
\param[in] MemLen       指定内存的大小
\param[out] pOutLen     实际使用的内存大小，编码后数据长度(自行确保pOutLen <= MemLen)
\param[in] pAttr        编码设置的属性，不可为空

\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE 显示失败
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
