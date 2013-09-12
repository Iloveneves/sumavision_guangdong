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
 * \brief 提供VI的相关信息
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
/** @{ */  /** <!-- 【VI】 */

/**<输入错误参数*/
#define HI_UNF_VI_INVALID_PARA_U32   (HI_U32)(-1)	

/** @} */  /** <!-- ==== Error Code Definition end ==== */




/********************************Struct Definition********************************/
/** \addtogroup      H_2_2_10 */
/** @{ */  /** <!-- 【VI】 */

/** BT.1120 YC分离模式通道类型 */
typedef enum hiUNF_VI_CHN_YC_SEL_E
{
    HI_UNF_VI_CHN_YC_SEL_Y = 0,		/**<BT.1120 YC分离模式下Y分离通道*/
    HI_UNF_VI_CHN_YC_SEL_C,			/**<BT.1120 YC分离模式下C分离通道*/
    HI_UNF_VI_CHN_YC_SEL_BUTT
}HI_UNF_VI_CHN_YC_SEL_E;

/** 存储类型 */
typedef enum hiUNF_VI_STOREMETHOD_E
{
    HI_UNF_VI_STORE_METHOD_PNYUV = 0,  /**<plannar YCbCr*/
    HI_UNF_VI_STORE_METHOD_SPNYC,      /**<semi_plannar YC*/
    HI_UNF_VI_STORE_METHOD_PKYUV,      /**<package yuv*/
    HI_UNF_VI_STORE_METHOD_RAWDATA,    /**<裸码流*/
    HI_UNF_VI_STORE_METHOD_BUTT     
} HI_UNF_VI_STOREMETHOD_E;

/* enumeration of possible VIU data width select. */
/*目前逻辑固定只支持8bit，从配置中删除*/
/*typedef enum hiUNF_VI_DATAWIDTH_E
{
    HI_UNF_VI_DATA_WIDTH8 = 0  
    HI_UNF_VI_DATA_WIDTH10 = 2, 
} HI_UNF_VI_DATAWIDTH_E;
*/

/** 场模式行选择模式 */
typedef enum hiUNF_VI_LINESEL_E
{
    HI_UNF_VI_LINESEL_ODD=0,     /**<仅对奇数行采集*/
    HI_UNF_VI_LINESEL_EVEN,      /**<仅对偶数行采集*/
    HI_UNF_VI_LINESEL_BOTH,      /**<对奇数行和偶数行都采集*/
    HI_UNF_VI_LINESEL_0347,      /**<每4行中只采集0、3行*/
    HI_UNF_VI_LINESEL_1256,      /**<每4行中只采集1、2行*/
    HI_UNF_VI_LINESEL_BUTT
} HI_UNF_VI_LINESEL_E;

/** 奇偶场选择模式 */
typedef enum hiUNF_VI_CAPSEL_E
{
    HI_UNF_VI_CAPSEL_ODD=0,     /**<仅对奇数场采集*/
    HI_UNF_VI_CAPSEL_EVEN,      /**<仅对偶数场采集*/
    HI_UNF_VI_CAPSEL_BOTH,       /**<对奇数场和偶数场都采集*/
    HI_UNF_VI_CAPSEL_BUTT
} HI_UNF_VI_CAPSEL_E;

/** 帧场存储模式 */
typedef enum hiUNF_VI_STORE_MODE_E
{
    HI_UNF_VI_STORE_FIELD = 0,   /**<场存储模式*/
    HI_UNF_VI_STORE_FRAME,       /**<帧存储模式*/
    HI_UNF_VI_STORE_BUTT
}HI_UNF_VI_STORE_MODE_E;

/** 输入端口 */
typedef enum hiUNF_VI_E
{
    HI_UNF_VI_PORT0   = 0x0,  /**<端口0 */
    HI_UNF_VI_PORT1,          /**<端口1 */    
    HI_UNF_VI_BUTT
}HI_UNF_VI_E;

/** 输入接口模式 */
typedef enum hiUNF_VI_INPUT_MODE_E
{
    HI_UNF_VI_MODE_BT656=0,        /**<ITU-R BT.656 YUV4:2:2 标准.  */
    HI_UNF_VI_MODE_BT601,          /**<ITU-R BT.601 YUV4:2:2 标准.  */
    HI_UNF_VI_MODE_DIGITAL_CAMERA, /**<数字摄像头，数据可能是RGB或者YCbCr.*/
    HI_UNF_VI_MODE_RAW_DATA,       /**<通过CVBS输入的数据，不需要处理. */
    HI_UNF_VI_MODE_USB_CAM,        /**<USB 摄像头，靠用户Get/Put输入数据  */ 
    HI_UNF_VI_MODE_VIRTUAL,        /**<虚拟VI,不从硬件输入数据，靠用户Get/Put输入数据 */
    HI_UNF_VI_MODE_BT1120_720P,	   /**<ITU-R BT.1120 YUV4:2:2 标准，720P  */ 
    HI_UNF_VI_MODE_BT1120_1080I,   /**<ITU-R BT.1120 YUV4:2:2 标准，1080I  */ 	
    HI_UNF_VI_MODE_BT1120_1080P,   /**<ITU-R BT.1120 YUV4:2:2 标准，1080p  */ 
    HI_UNF_VI_MODE_BUTT            
} HI_UNF_VI_INPUT_MODE_E;

/** VI属性 */
typedef struct hiUNF_VI_ATTR_S
{
    HI_UNF_VI_E              enViPort;		/**<输入端口 */
    HI_UNF_VI_INPUT_MODE_E   enInputMode;   /**<视频输入模式*/
    HI_RECT_S                stInputRect;   /**< 窗口的裁减区域 */
    HI_UNF_VI_CAPSEL_E       enCapSel;		/**< 奇偶场采集选择 */

    HI_UNF_VI_CHN_YC_SEL_E   enChnYC;       /**<只有在bt1120模式下有效 */
    HI_UNF_VI_STOREMETHOD_E  enStoreMethod; /**<视频格式*/
    HI_UNF_VI_STORE_MODE_E	 enStoreMode;   /**<帧场模式*/
    
    HI_U32 u32YStride;		/**<planar模式下Y的stride，其他模式的唯一stride*/
    HI_U32 u32CStride;		/**<planar模式下C的stride，其他模式无效*/
    HI_U32 u32BufPhyAddr;	/**<帧buf物理地址, 用户不需要配置 */
    HI_U32 u32FrameSize;    /**<一帧占用的内存空间,输出参数，用户不需要配置 */
    HI_U32 u32BufSize;		/**<帧buf的大小,输出参数，用户不需要配置 */
    HI_U32 u32BufNum;       /**<可用的帧buf的个数*/
} HI_UNF_VI_ATTR_S;

/** VI Buffer 属性 */
typedef struct  hiUNF_VI_BUF_S
{ 
    HI_U32                      u32FrameIndex;	/**< 帧索引       */
    HI_UNF_VIDEO_FORMAT_E       enPixelFormat;  /**< 输入视频采样格式  */
    HI_U32                      u32Width;       /**< 输入宽度.       */
    HI_U32                      u32Height;      /**< 输入高度.      */
                                                        
    HI_UNF_VIDEO_FIELD_MODE_E   enField;        /**< 采场类型 ,top/bottom/all       */
    HI_U32                      u32DownScaled;  /**< 是否要下采样. */

    /* 如果是RGB或者package存储模式，只有u32PhyAddr[0]有效.
       如果是semi-planar存储模式，只有u32PhyAddr[0-1]有效,
       相应的pVirAddr，u32Stride也与u32PhyAddr有效性一致.  */
    HI_U32                      u32PhyAddr[3];        /**< A/B/C 分量物理地址. */	
    HI_VOID                     *pVirAddr[3];         /**< A/B/C 分量虚拟地址. */
    HI_U32                      u32Stride[3];         /**< A/B/C 分量stride.      */

    HI_U32                      u32PtsMs;                   /**< 时间戳. */                     
}HI_UNF_VI_BUF_S;

/** @} */  /** <!-- ==== Struct Definition end ==== */

/********************************API declaration********************************/
/** \addtogroup      H_1_2_8 */
/** @{ */  /** <!-- 【VI】 */

/** 
\brief 初始化VI
\attention \n
调用VI模块要求首先调用该接口
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_DEV_NOT_EXIST 设备不存在
\retval ::HI_ERR_VI_NOT_DEV_FILE 文件非设备
\retval ::HI_ERR_VI_DEV_OPENED 打开设备失败
\see \n
无
*/
HI_S32 HI_UNF_VI_Init(HI_VOID);


/** 
\brief 去初始化VI
\attention \n
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_DEV_NOT_EXIST 设备不存在
\retval ::HI_ERR_VI_DEV_CLOSE_ERR 关闭VI 设备失败
\see \n
无
*/
HI_S32 HI_UNF_VI_DeInit(HI_VOID);


/** 
\brief 获取VI端口默认属性
\attention \n
默认Port=0, HALF-D1, BT656，采集偶场，输出SemiPlanner YUV4:2:0格式数据
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_NULL_PTR 空指针
\see \n
无
*/
HI_S32 HI_UNF_VI_GetDefaultAttr(HI_UNF_VI_ATTR_S *pstAttr);


/** 
\brief 设置VI Port属性
\attention \n
预留接口，与Create合一，不可动态调用
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_NULL_PTR 空指针
\retval ::HI_ERR_VI_CHN_NOT_EXIST 句柄错误
\retval ::HI_ERR_VI_CHN_INIT_BUF_ERR 初始化buffer错误
\retval ::HI_ERR_VI_INVALID_PARA 属性参数错误
\see \n
无
*/
HI_S32 HI_UNF_VI_SetAttr(HI_HANDLE hVi, HI_UNF_VI_ATTR_S *pstAttr);


/** 
\brief 获取VI Port属性
\attention \n
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_NULL_PTR 空指针
\retval ::HI_ERR_VI_CHN_NOT_EXIST 句柄错误
\see \n
无
*/
HI_S32 HI_UNF_VI_GetAttr(HI_HANDLE hVi, HI_UNF_VI_ATTR_S *pstAttr);


/** 
\brief 打开Vi Port，创建Vi句柄
\attention \n
调用VI 模块需要首先调用该接口\n
除非使用虚拟VI, 否则PortID需要与硬件对应,硬件上使用了哪个Port,那么软件也必须使用哪个Port.\n
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_NULL_PTR 空指针
\retval ::HI_ERR_VI_CHN_INIT_BUF_ERR 初始化buffer错误
\retval ::HI_ERR_VI_INVALID_PARA 属性参数错误
\see \n
无
*/
HI_S32 HI_UNF_VI_Create(HI_UNF_VI_ATTR_S *pstAttr, HI_HANDLE *phandle);


/** 
\brief 关闭Vi Port，销毁句柄
\attention \n
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_CHN_NOT_EXIST 句柄错误
\see \n
无
*/
HI_S32 HI_UNF_VI_Destroy(HI_HANDLE hVi);


/** 
\brief 获取虚拟Vi Port 一帧图像Buffer
\attention \n
如果用户创建的是虚拟VI Port，可以调用此接口获取Vi Buf来填入用户YUV数据。\n
一般用于USB摄像头\n
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_CHN_NOT_EXIST 句柄错误
\retval ::HI_ERR_VI_NULL_PTR 空指针
\see \n
无
*/
HI_S32 HI_UNF_VI_GetFrame(HI_HANDLE hVi, HI_UNF_VI_BUF_S * pViBuf);


/** 
\brief 发送虚拟Vi Port 一帧图像Buffer，驱动虚拟Port工作
\attention 用户调用::HI_UNF_VI_GetFrame获取到一帧YUV数据的地址，并且拷贝好YUV数据后，就可以调用此接口通知VI数据已经准备好，VI会在此接口被调用后，把数据送去编码或者送去VO显示。\n
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_CHN_NOT_EXIST 句柄错误
\retval ::HI_ERR_VI_NULL_PTR 空指针
\see \n
无
*/
HI_S32 HI_UNF_VI_PutFrame(HI_HANDLE hVi, const HI_UNF_VI_BUF_S * pViBuf);


/** 
\brief 获取一帧YUV 图像地址
\attention \n
一般情况下，用户不需要调用此接口，推荐直接将VI与VENC或者VO进行绑定以便实现编码或者VIVO环回功能。
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_CHN_NOT_EXIST 句柄错误
\retval ::HI_ERR_VI_NULL_PTR 空指针
\see \n
无
*/
HI_S32 HI_UNF_VI_AcquireFrame(HI_HANDLE hVi, HI_UNF_VI_BUF_S * pViBuf);


/** 
\brief 用户归还一帧YUV 图像地址
\attention \n
一般情况下，用户不需要调用此接口，推荐直接将VI与VENC或者VO进行绑定以便实现编码或者VIVO环回功能。
\param[in] 无
\retval ::HI_SUCCESS 成功
\retval ::HI_ERR_VI_CHN_NOT_EXIST 句柄错误
\retval ::HI_ERR_VI_NULL_PTR 空指针
\see \n
无
*/
HI_S32 HI_UNF_VI_ReleaseFrame(HI_HANDLE hVi, const HI_UNF_VI_BUF_S * pViBuf);
/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif
