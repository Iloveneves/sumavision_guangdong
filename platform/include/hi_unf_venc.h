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
 * \brief 提供VENC的相关信息
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
/** @{ */  /** <!-- 【VENC】 */

/**<最大编码宽度*/
#define HI_UNF_VENC_MAX_WIDTH       (1920)		
/**<最小编码宽度*/	
#define HI_UNF_VENC_MIN_WIDTH       (96)			  
/**<最大编码高度*/
#define HI_UNF_VENC_MAX_HEIGTH      (1080)		
/**<最小编码高度*/	
#define HI_UNF_VENC_MIN_HEIGTH      (96)			  
/**<图像大小对齐字节*/
#define HI_UNF_VENC_PIC_SZIE_ALIGN  (16)			  
/**<最大缓存字节*/
#define HI_UNF_VENC_MAX_BUF_SIZE    (20*1024*1024)	
/**<最小缓存字节*/
#define HI_UNF_VENC_MIN_BUF_SIZE    (256*1024)	
/**<最小GOP*/
#define HI_UNF_VENC_MIN_GOP         (1)				  
/**<最大输出码率*/
#define HI_UNF_VENC_MAX_bps         (42*1024*1024)	
/**<最小输出码率*/
#define HI_UNF_VENC_MIN_bps         (32*1024)		
/**<最大Split字节*/
#define HI_UNF_VENC_MAX_SPLIT_SIZE  (0xFFFF)		
/**<最小Split字节*/
#define HI_UNF_VENC_MIN_SPLIT_SIZE  (512)			  
/**<最大量化级别*/
#define HI_UNF_VENC_MAX_Q_VALUE     (99)		 
/**<最小量化级别*/ 
#define HI_UNF_VENC_MIN_Q_VALUE     (1)				  
/**<最大帧率*/
#define HI_UNF_VENC_MAX_fps         (30)		
/**<最小帧率*/	  
#define HI_UNF_VENC_MIN_fps         (1)				 
/**<码率保留字节大小*/
#define HI_UNF_VENC_STREAM_RESERV_SIZE 48			  
/** @} */  /** <!-- ==== Macro Definition end ==== */

/********************************Struct Definition********************************/
/** \addtogroup      H_2_2_16 */
/** @{ */  /** <!-- 【VENC】 */

/** H.264NALU类型 */
typedef enum hiUNF_H264E_NALU_TYPE_E
{
    HI_UNF_H264E_NALU_PSLICE = 1,		/**<P slice NALU*/
    HI_UNF_H264E_NALU_ISLICE = 5,		/**<I slice NALU*/
    HI_UNF_H264E_NALU_SEI = 6,			/**<SEI NALU*/
    HI_UNF_H264E_NALU_SPS = 7,			/**<SPS NALU*/
    HI_UNF_H264E_NALU_PPS = 8,			/**<PPS NALU*/
    HI_UNF_H264E_NALU_BUTT
} HI_UNF_H264E_NALU_TYPE_E;

/** H.263NALU类型 */
typedef enum hiUNF_H263E_PACK_TYPE_E
{
    HI_UNF_H263E_NALU_PSLICE = 1,		/**<P slice NALU*/
    HI_UNF_H263E_NALU_ISLICE = 5,		/**<I slice NALU*/
    HI_UNF_H263E_NALU_SEI = 6,			/**<SEI NALU*/
    HI_UNF_H263E_NALU_SPS = 7,			/**<SPS NALU*/
    HI_UNF_H263E_NALU_PPS = 8,			/**<PPS NALU*/
    HI_UNF_H263E_NALU_BUTT
} HI_UNF_H263E_PACK_TYPE_E;

/** JPEG打包类型 */
typedef enum hiUNF_JPEGE_PACK_TYPE_E
{
    HI_UNF_JPEGE_PACK_ECS = 5,			/**<ECS 包*/
    HI_UNF_JPEGE_PACK_APP = 6,			/**<APP 包*/
    HI_UNF_JPEGE_PACK_VDO = 7,			/**<VDO 包*/
    HI_UNF_JPEGE_PACK_PIC = 8,			/**<PIC 包*/
    HI_UNF_JPEGE_PACK_BUTT
} HI_UNF_JPEGE_PACK_TYPE_E;

/** MPEG4打包类型 */
typedef enum hiUNF_MPEG4E_PACK_TYPE_E
{
    HI_UNF_MPEG4E_PACK_VO = 1,			/**<VO 包*/
    HI_UNF_MPEG4E_PACK_VOS = 2,			/**<VOS 包*/
    HI_UNF_MPEG4E_PACK_VOL = 3,			/**<VOL 包*/
    HI_UNF_MPEG4E_PACK_VOP = 4,			/**<VOP 包*/
    HI_UNF_MPEG4E_PACK_SLICE = 5		/**<SLICE 包*/	
} HI_UNF_MPEG4E_PACK_TYPE_E;

/** 数据类型 */
typedef union hiUNF_VENC_DATA_TYPE_U
{
    HI_UNF_H264E_NALU_TYPE_E   enH264EType;	/**<264编码数据*/	
    HI_UNF_H263E_PACK_TYPE_E   enH263EType;	/**<263编码数据*/	
    HI_UNF_JPEGE_PACK_TYPE_E   enJPEGEType;	/**<JPEG编码数据*/	
    HI_UNF_MPEG4E_PACK_TYPE_E  enMPEG4EType;/**<MPEG4编码数据*/		
}HI_UNF_VENC_DATA_TYPE_U;

/** 输出码流属性 */
typedef struct hiVENC_STREAM_S
{
    HI_U8                   au8Reserved[HI_UNF_VENC_STREAM_RESERV_SIZE];  /**< inner use, don't touch */
    HI_U8                   *pu8Addr[2];		  /**<码流虚拟地址，循环buffer环回时用2个地址*/	
    HI_U32                  u32PhyAddr[2];		/**<码流物理地址，循环buffer环回时用2个地址*/	
    HI_U32                  u32SlcLen[2];		  /**<码流长度*/		
    HI_U32                  u32PTS0;			    /**<PTS0*/	
    HI_U32                  u32PTS1;			    /**<PTS1*/	
    HI_U32                  bFrameEnd;  	  	/**<是否为帧结束*/
    HI_UNF_VENC_DATA_TYPE_U enDataType;			  /**<编码数据类型 */
}HI_UNF_VENC_STREAM_S;

/** 输入数据存储类型 */
typedef enum hiUNF_VENC_YUV_TYPE_E
{
    HI_UNF_VENC_YUV_420=0,		/**<YUV420模式*/
    HI_UNF_VENC_YUV_422,		  /**<YUV422模式*/	
    HI_UNF_VENC_YUV_444,		  /**<YUV444模式*/
    HI_UNF_VENC_YUV_BUTT
}HI_UNF_VENC_YUV_TYPE_E;

/** 输入数据存储模式 */
typedef enum hiUNF_VENC_STORE_TYPE_E
{
    HI_UNF_VENC_STORE_SEMIPLANNAR=0,	/**<semi plannar模式*/
    HI_UNF_VENC_STORE_PLANNAR,			  /**<plannar模式*/
    HI_UNF_VENC_STORE_PACKAGE,			  /**<package模式*/
    HI_UNF_VENC_STORE_BUTT	
}HI_UNF_VENC_STORE_TYPE_E;

/** package YUV存放顺序 */
typedef enum hiUNF_VENC_PACKAGE_SEQ_E
{
    HI_UNF_VENC_PACKAGE_Y0UY1V =0,	    /**<Y0U0Y1V0模式*/
    HI_UNF_VENC_PACKAGE_Y0UVY1 ,	    /**<Y0U0V0Y1模式*/
    HI_UNF_VENC_PACKAGE_Y0Y1UV ,	    /**<Y0Y1U0V0模式*/
    HI_UNF_VENC_PACKAGE_Y0Y1VU ,	    /**<Y0Y1V0U0模式*/
    HI_UNF_VENC_PACKAGE_Y0VY1U ,	    /**<Y0V0Y1U0模式*/
    HI_UNF_VENC_PACKAGE_Y0VUY1 ,	    /**<Y0V0U0Y1模式*/
    
    HI_UNF_VENC_PACKAGE_UY0Y1V ,	    /**<U0Y0Y1V0模式*/
    HI_UNF_VENC_PACKAGE_UY0VY1 ,	    /**<U0Y0V0Y1模式*/
    HI_UNF_VENC_PACKAGE_UY1Y0V ,	    /**<U0Y1Y0V0模式*/
    HI_UNF_VENC_PACKAGE_UY1VY0 ,	    /**<U0Y1V0Y0模式*/
    HI_UNF_VENC_PACKAGE_UVY1Y0 ,	    /**<U0V0Y1Y0模式*/
    HI_UNF_VENC_PACKAGE_UVY0Y1 ,	    /**<U0V0Y0Y1模式*/

    HI_UNF_VENC_PACKAGE_Y1UY0V ,	    /**<Y1U0Y0V0模式*/
    HI_UNF_VENC_PACKAGE_Y1UVY0 ,	    /**<Y1U0V0Y0模式*/
    HI_UNF_VENC_PACKAGE_Y1Y0UV ,	    /**<Y1Y0U0V0模式*/
    HI_UNF_VENC_PACKAGE_Y1Y0VU ,	    /**<Y1Y0V0U0模式*/
    HI_UNF_VENC_PACKAGE_Y1VY0U ,	    /**<Y1V0Y0U0模式*/
    HI_UNF_VENC_PACKAGE_Y1VUY0 ,	    /**<Y1V0U0Y0模式*/

    HI_UNF_VENC_PACKAGE_VY0Y1U ,	    /**<V0Y0Y1U0模式*/
    HI_UNF_VENC_PACKAGE_VY0UY1 ,	    /**<V0Y0U0Y1模式*/
    HI_UNF_VENC_PACKAGE_VY1Y0U ,	    /**<V0Y1Y0U0模式*/
    HI_UNF_VENC_PACKAGE_VY1UY0 ,	    /**<V0Y1U0Y0模式*/
    HI_UNF_VENC_PACKAGE_VUY1Y0 ,	    /**<V0U0Y1Y0模式*/
    HI_UNF_VENC_PACKAGE_VUY0Y1 ,	    /**<V0U0Y0Y1模式*/	
    HI_UNF_VENC_PACKAGE_BUTT	
}HI_UNF_VENC_PACKAGE_SEQ_E;

/* 编码通道属性 */
typedef struct hiUNF_VENC_CHN_ATTR_S
{
    HI_U32                      u32Width;   /**< 宽度，16字节对齐,不支持动态设置  */
    HI_U32                      u32Height;  /**< 高度，16字节对齐,不支持动态设置 */
    HI_UNF_VCODEC_TYPE_E        enVencType;	/**< 编码器类型 */
    HI_U32                      u32StrmBufSize;	/**< 码流buffer大小 */

    HI_UNF_VENC_YUV_TYPE_E      enYuvSampleType; /**< 存储类型，420 422, 422格式只支持package  */
    HI_UNF_VENC_STORE_TYPE_E    enYuvStoreType;  /**< 存储格式, 目前只支持semiplanar 或者 package*/
    HI_U32                      u32RotationAngle;/**< 旋转角度,无效设置  */

	HI_UNF_VENC_PACKAGE_SEQ_E   enPackageSel;	  /**< package YUV存放顺序*/ 	
    HI_BOOL                     bSlcSplitEn;	  /**< 是否使能分割slice */ 	
    HI_U32                      u32SplitSize;     /**< 分割的大小，JPGE下以MCU为单位,H264或者MP4以字节为单位, H263不关心 */
    
    HI_U32                      u32Qlevel;        /**< JPGE取值范围1-99，其他设置为0 */
    
    HI_U32                      u32TargetBitRate; /**< Venc下是RC参数,可动态设置 */
    HI_U32                      u32TargetFrmRate; /**< 目标帧率,可动态设置 */ 
    HI_U32                      u32InputFrmRate;  /**< 输入帧率,可动态设置,u32TargetFrmRate <= u32InputFrmRate */ 
    HI_U32                      u32Gop;			  /**< GOP大小,可动态设置 */ 	
	HI_BOOL        				bSendToNet;       /**< 是否发送到网络， 是则发生到网络，否则保持现有数据流
										（用户通过接口获取）。不能同时走两条路，避免用户获取得不及时导致网络延时 */
	HI_UNF_VP_NET_PARA_S        stNetCfgPara;		  /**< 网络参数，bSendToNet为真时有效 */
    
}HI_UNF_VENC_CHN_ATTR_S;

/** @} */  /** <!-- ==== Struct Definition end ==== */

/********************************API declaration********************************/
/** \addtogroup      H_1_2_9 */
/** @{ */  /** <!-- 【VENC】 */

/** 
\brief 初始化视频编码器
\attention \n
调用VENC模块要求首先调用该接口
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_DEV_NOT_EXIST 设备不存在
\retval ::HI_ERR_VENC_NOT_DEV_FILE 文件非设备
\retval ::HI_ERR_VENC_DEV_OPEN_ERR 打开设备失败
\see \n
无
*/
HI_S32 HI_UNF_VENC_Init(HI_VOID);


/** 
\brief 去初始化视频编码器
\attention \n
无
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_DEV_CLOSE_ERR 关闭编码器失败
\see \n
无
*/
HI_S32 HI_UNF_VENC_DeInit(HI_VOID);


/** 
\brief 获取编码通道默认属性
\attention \n
默认D1编码，H.264格式，一帧为一个Slice
\param[in] pstAttr 指向编码通道属性的指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_NULL_PTR 输入指针参数为空指针
\see \n
无
*/
HI_S32 HI_UNF_VENC_GetDefaultAttr(HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief 创建视频编码通道
\attention \n
进行视频编码要求首先创建编码通道 
\param[in] phVencChn 指向编码通道句柄的指针
\param[in] pstAttr 指向编码通道属性的指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_NULL_PTR 输入指针参数有空指针
\retval ::HI_ERR_VENC_CREATE_ERR 编码通道数已满
\retval ::HI_ERR_VENC_INVALID_PARA 通道属性设置错误
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\see \n
无
*/
HI_S32 HI_UNF_VENC_CreateChn(HI_HANDLE *phVenc, const HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief 销毁视频编码通道
\attention \n
\param[in] hVenc 编码通道句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 句柄不存在
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\see \n
无
*/
HI_S32 HI_UNF_VENC_DestroyChn(HI_HANDLE hVenc);


/** 
\brief 绑定编码通道到视频源
\attention \n
开始编码和获取码流之前需要首先调用该接口
\param[in] hVenc 编码通道句柄
\param[in] hSrc 视频源句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_INVALID_PARA 视频源错误
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\see \n
无
*/
HI_S32 HI_UNF_VENC_AttachInput(HI_HANDLE hVenc,HI_HANDLE hSrc);


/** 
\brief 解绑定视频源
\attention \n
调用该接口需要首先停止编码
\param[in] hVenc 编码通道句柄
\param[in] hSrc 视频源句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_INVALID_PARA 视频源错误
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\retval ::HI_ERR_VENC_CHN_INVALID_STAT 编码器未停止编码
\see \n
无
*/
HI_S32 HI_UNF_VENC_DetachInput(HI_HANDLE hVenc,HI_HANDLE hSrc);


/** 
\brief 开始编码
\attention \n
调用该接口需要首先初始化编码器，创建编码通道，绑定视频源
\param[in] hVenc 编码通道句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\retval ::HI_ERR_VENC_CHN_NO_ATTACH 编码通道没有绑定到视频源
\see \n
无
*/
HI_S32 HI_UNF_VENC_Start(HI_HANDLE hVenc);


/** 
\brief 停止编码
\attention \n
调用该接口需要首先初始化编码器，创建编码通道，绑定视频源
，已经开始编码
\param[in] hVenc 编码通道句柄
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\retval ::HI_ERR_VENC_CHN_NO_ATTACH 编码通道没有绑定到视频源
\see \n
无
*/
HI_S32 HI_UNF_VENC_Stop(HI_HANDLE hVenc);

/** 
\brief 获取视频编码码流
\attention \n
调用该接口需要首先绑定视频源，开始编码
阻塞时间可以设置，时间单位为毫秒，设置为0不等待，设置为0xffffffff一直等待。\n
若超过阻塞时间，还没有数据到达，则返回::HI_ERR_VENC_BUF_EMPTY\n
如果等待时间为0，且没有码流数据，则返回::HI_ERR_VENC_BUF_EMPTY\n
暂时不支持非阻塞模式，请把u32TimeOutMs配置为0,并且在此接口返回HI_ERR_VENC_BUF_EMPTY的时候，调用usleep(10000)出让CPU \n
\param[in] hVenc 编码通道句柄
\param[in] pstStream 存放码流结构的指针
\param[in] u32TimeOutMs      等待超时时间，单位ms
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\retval ::HI_ERR_VENC_NULL_PTR 码流指针为空
\retval ::HI_ERR_VENC_CHN_NO_ATTACH 编码通道没有绑定到视频源
\retval ::HI_ERR_VENC_BUF_EMPTY 获取码流失败
\see \n
无
*/
HI_S32 HI_UNF_VENC_AcquireStream(HI_HANDLE hVenc,HI_UNF_VENC_STREAM_S *pstStream, HI_U32 u32TimeoutMs);


/** 
\brief 释放视频编码码流
\attention \n
调用该接口需要首先获取码流，且不能改变码流内容
\param[in] hVenc 编码通道句柄
\param[in] pstStream 存放码流结构的指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\retval ::HI_ERR_VENC_NULL_PTR 码流指针为空
\retval ::HI_ERR_VENC_CHN_NO_ATTACH 编码通道没有绑定到视频源
\see \n
无
*/
HI_S32 HI_UNF_VENC_ReleaseStream(HI_HANDLE hVenc, const HI_UNF_VENC_STREAM_S *pstStream);


/** 
\brief 动态设置编码通道属性
\attention \n
调用该接口需要首先创建编码通道
\param[in] hVenc 编码通道句柄
\param[in] pstAttr 存放编码通道属性的指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\retval ::HI_ERR_VENC_NULL_PTR 指针为空
\see \n
无
*/
HI_S32 HI_UNF_VENC_SetAttr(HI_HANDLE hVenc,const HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief 获取编码通道属性
\attention \n
调用该接口需要首先创建编码通道
\param[in] hVenc 编码通道句柄
\param[in] pstAttr 编码通道属性
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\retval ::HI_ERR_VENC_NULL_PTR 指针为空
\see \n
无
*/
HI_S32 HI_UNF_VENC_GetAttr(HI_HANDLE hVenc, HI_UNF_VENC_CHN_ATTR_S *pstAttr);


/** 
\brief 请求I帧
\attention \n
调用该接口后，编码器会尽快编码出一个I帧来.\n
此接口一般用于可视电话场景的通话建立和错误恢复.\n
此接口只是"尽最大能力"尽快编码出一个I帧来，如果在短时间内多次调用此接口，那么不能保证每次调用都能对应编码出一个I帧来.\n
\param[in] hVenc 编码通道句柄
\param[in] pstStream 存放编码通道属性的指针
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VENC_CHN_NOT_EXIST 编码通道句柄不存在
\retval ::HI_ERR_VENC_NO_INIT 编码器未初始化
\see \n
无
*/
HI_S32 HI_UNF_VENC_RequestIFrame(HI_HANDLE hVencChn);
/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif//__HI_UNF_VENC_H__
