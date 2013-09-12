/**
\file
\brief hisilicon HDMI APIs
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author QuYaxin 46153
\date 2009-12-10
*/

#ifndef __HI_UNF_HDMI_H__
#define __HI_UNF_HDMI_H__

/* add include here */
#include "hi_unf_common.h"
#include "hi_unf_sound.h"

#ifndef __GNUC__	
#define  __attribute__(x)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_9 */
/** @{ */  /** <!-- 【HDMI】 */

/**最大音频能力集个数 */
#define HI_UNF_HDMI_MAX_AUDIO_CAP_COUNT     15 

/**最大音频采样率个数 */
#define HI_UNF_HDMI_MAX_AUDIO_SMPRATE_COUNT 10 

/**< 最大信息帧长度 */
#define HI_UNF_HDMI_MAX_INFOFRAME_LEN   0X20   

/**< HDMI 缺省值 */
#define HI_UNF_HDMI_DEFAULT_SETTING     0x00

/** HDMI接口ID  */
typedef enum hiUNF_HDMI_ID_E
{
    HI_UNF_HDMI_ID_0         = 0,           /**< HDMI接口0 */
    HI_UNF_HDMI_ID_BUTT
} HI_UNF_HDMI_ID_E;

/** HDMI事件类型 */
typedef enum hiUNF_HDMI_EVENT_TYPE_E
{
    HI_UNF_HDMI_EVENT_HOTPLUG = 0x10,       /**<HDMI热插拔事件 */
    HI_UNF_HDMI_EVENT_NO_PLUG,              /**<HDMI Cable没有连接 事件 */
    HI_UNF_HDMI_EVENT_EDID_FAIL,            /**<HDMI EDID读取失败事件 */
    HI_UNF_HDMI_EVENT_HDCP_FAIL,            /**<HDCP验证失败事件 */
    HI_UNF_HDMI_EVENT_HDCP_SUCCESS,         /**<HDCP验证成功 */
    HI_UNF_HDMI_EVENT_HDCP_USERSETTING,     /**<HDMI Reset */
    HI_UNF_HDMI_EVENT_BUTT
}HI_UNF_HDMI_EVENT_TYPE_E;

/**视频颜色空间类型*/
typedef enum hiUNF_HDMI_VIDEO_MODE
{
    HI_UNF_HDMI_VIDEO_MODE_RGB444,          /**<RGB444输出模式 */ 
    HI_UNF_HDMI_VIDEO_MODE_YCBCR422,        /**<YCBCR422输出模式 */ 
    HI_UNF_HDMI_VIDEO_MODE_YCBCR444,        /**<YCBCR444输出模式 */ 
        
    HI_UNF_HDMI_VIDEO_MODE_BUTT    
}HI_UNF_HDMI_VIDEO_MODE_E;


/** HDMI Deep Color 模式 */
typedef enum hiUNF_HDMI_DEEP_COLOR_E
{
    HI_UNF_HDMI_DEEP_COLOR_24BIT = 0x00,    /**< HDMI Deep Color 24bit 模式  */
    HI_UNF_HDMI_DEEP_COLOR_30BIT,           /**< HDMI Deep Color 30bit 模式  */
    HI_UNF_HDMI_DEEP_COLOR_36BIT,           /**< HDMI Deep Color 36bit 模式  */  
    HI_UNF_HDMI_DEEP_COLOR_OFF   = 0xff,
    HI_UNF_HDMI_DEEP_COLOR_BUTT
}HI_UNF_HDMI_DEEP_COLOR_E;

/** HDMI AVI信息帧 BarInfo 枚举 */
typedef enum hiUNF_HDMI_BARINFO_E
{
   HDMI_BAR_INFO_NOT_VALID,                 /**< Bar Data not valid */
   HDMI_BAR_INFO_V,                         /**< Vertical bar data valid */
   HDMI_BAR_INFO_H,                         /**< Horizental bar data valid */
   HDMI_BAR_INFO_VH                         /**< Horizental and Vertical bar data valid */
}HI_UNF_HDMI_BARINFO_E;

/** HDMI AVI信息帧 ScanInfo 枚举 */
typedef enum hiUNF_HDMI_SCANINFO_E
{
    HDMI_SCAN_INFO_NO_DATA      = 0,        /**< No Scan information*/
    HDMI_SCAN_INFO_OVERSCANNED  = 1,        /**< Scan information, Overscanned (for television) */
    HDMI_SCAN_INFO_UNDERSCANNED = 2,        /**< Scan information, Underscanned (for computer) */
    HDMI_SCAN_INFO_FUTURE
}HI_UNF_HDMI_SCANINFO_E;

/** HDMI AVI信息帧 Picture scan 枚举 */
typedef enum hiUNF_HDMI_PICTURE_SCALING_E
{
    HDMI_PICTURE_NON_UNIFORM_SCALING,       /**< No Known, non-uniform picture scaling  */
    HDMI_PICTURE_SCALING_H,                 /**< Picture has been scaled horizentally */
    HDMI_PICTURE_SCALING_V,                 /**< Picture has been scaled Vertically */
    HDMI_PICTURE_SCALING_HV                 /**< Picture has been scaled Horizentally and Vertically   */
 }HI_UNF_HDMI_PICTURE_SCALING_E;

/** HDMI AVI信息帧 色度空间 枚举 */
typedef enum hiUNF_HDMI_COLORSPACE_E
{
    HDMI_COLORIMETRY_NO_DATA,               /**< Colorimetry No Data选项 */
    HDMI_COLORIMETRY_ITU601,                /**< Colorimetry ITU601色度空间选项 */
    HDMI_COLORIMETRY_ITU709,                /**< Colorimetry ITU709色度空间选项 */
    HDMI_COLORIMETRY_EXTENDED,              /**< Colorimetry 扩展选项 */
    HDMI_COLORIMETRY_XVYCC_601,             /**< Colorimetry xvYCC601扩展选项 */
    HDMI_COLORIMETRY_XVYCC_709              /**< Colorimetry xvYCC709扩展选项 */
}HI_UNF_HDMI_COLORSPACE_E;

/** HDMI AVI信息帧 RGB色度范围 枚举 */
typedef enum hiUNF_HDMI_RGB_QUAN_RAGE_E
{
    HDMI_RGB_QUANTIZATION_DEFAULT_RANGE,    /**< Defaulr range, it depends on the video format */
    HDMI_RGB_QUANTIZATION_LIMITED_RANGE,    /**< Limited quantization range of 220 levels when receiving a CE video format*/
    HDMI_RGB_QUANTIZATION_FULL_RANGE        /**< Full quantization range of 256 levels when receiving an IT video format*/
}HI_UNF_HDMI_RGB_QUAN_RAGE_E;

/** HDMI AVI信息帧 YCC色度范围 枚举 */
typedef enum hiUNF_HDMI_YCC_QUAN_RAGE_E
{
    HDMI_YCC_QUANTIZATION_LIMITED_RANGE,    /**< Limited quantization range of 220 levels when receiving a CE video format*/
    HDMI_YCC_QUANTIZATION_FULL_RANGE        /**< Full quantization range of 256 levels when receiving an IT video format*/
}HI_UNF_HDMI_YCC_QUAN_RAGE_E;

/** HDMI AVI信息帧 AVI视频内容的类型 枚举 */
typedef enum hiUNF_HDMI_CONTENT_TYPE_E
{
    HDMI_CONTNET_GRAPHIC,                   /**< Graphics type*/
    HDMI_CONTNET_PHOTO,                     /**< Photo type*/
    HDMI_CONTNET_CINEMA,                    /**< Cinema type*/
    HDMI_CONTNET_GAME                       /**< Game type*/
}HI_UNF_HDMI_CONTENT_TYPE_E;

/** HDMI AUD信息帧 音频类型 枚举 */
typedef enum hiUNF_HDMI_CODING_TYPE_E
{
    HDMI_AUDIO_CODING_REFER_STREAM_HEAD,  /**< 音频编码类型，参考数据流，缺省格式 */
    HDMI_AUDIO_CODING_PCM,                /**< 音频编码PCM格式 */
    HDMI_AUDIO_CODING_AC3,                /**< 音频编码AC3格式 */
    HDMI_AUDIO_CODING_MPEG1,              /**< 音频编码MPEG1格式 */
    HDMI_AUDIO_CODING_MP3,                /**< 音频编码MP3格式 */
    HDMI_AUDIO_CODING_MPEG2,              /**< 音频编码MPEG2格式 */
    HDMI_AUDIO_CODING_AAC,                /**< 音频编码AAC格式 */
    HDMI_AUDIO_CODING_DTS,                /**< 音频编码DTS格式 */
    HDMI_AUDIO_CODING_DDPLUS,             /**< 音频编码DDPLUS格式 */
    HDMI_AUDIO_CODING_MLP,                /**< 音频编码MLP格式 */
    HDMI_AUDIO_CODING_WMA,                /**< 音频编码WMA格式 */
    HDMI_AUDIO_CODING_MAX
}HI_UNF_HDMI_CODING_TYPE_E;

/** HDMI牵制输出模式 枚举 */
typedef enum hiUNF_HDMI_FORCE_ACTION_E
{
    HI_UNF_HDMI_FORCE_NULL,               /**< 标准模式 */
    HI_UNF_HDMI_FORCE_HDMI,               /**< 强制按HDMI方式输出 */
    HI_UNF_HDMI_FORCE_DVI,                /**< 强制按DVI方式输出 */
    HI_UNF_HDMI_INIT_BOOT_CONFIG          /**< 使用boot对HDMI设置的参数初始化HDMI, Test Only */
}HI_UNF_HDMI_FORCE_ACTION_E;

/** 接口热插拔回调函数 */
typedef void (*HI_UNF_HDMI_CallBack)(HI_UNF_HDMI_EVENT_TYPE_E event, HI_VOID *pPrivateData);

/** HDMI接口初始化参数 */
typedef struct hiUNF_HDMI_INIT_PARA_S
{
    HI_UNF_HDMI_CallBack pfnHdmiEventCallback;    /**< 事件回调 */
    HI_VOID             *pCallBackArgs;           /**< 回调函数参数私有数据 */
    HI_UNF_HDMI_FORCE_ACTION_E enForceMode;       /**< 0:按标准协议模式 HDMI ATC测试必须使用0,1:强制HDMI模式,2:强制为DVI模式 */
}HI_UNF_HDMI_INIT_PARA_S;

/** HDMI sink 接口能力集 */
typedef struct hiUNF_HDMI_SINK_CAPABILITY_S
{
    HI_BOOL             bConnected;               /**< 设备是否连接 */
    HI_BOOL             bSupportHdmi;             /**< 设备是否支持HDMI，如果不支持，则为DVI设备.*/
    HI_BOOL             bIsSinkPowerOn;           /**< Sink设备是否上电 */
    HI_BOOL             bIsRealEDID;              /**< EDID是否是真正从sink设备获取标志，HI_TRUE为正确读取，HI_FASE为强制设置结果 */

    HI_UNF_ENC_FMT_E    enNativeVideoFormat;      /**< 显示设备物理分辨率 */
    HI_BOOL             bVideoFmtSupported[HI_UNF_ENC_FMT_BUTT]; /**< 视频能力集,HI_TRUE表示支持这种显示格式，HI_FALSE表示不支持 */
    HI_BOOL             bSupportYCbCr;            /**< 是否支持YCBCR显示， 如果为HI_FALSE,表示只支持RGB显示 */
    
    HI_BOOL             bSupportxvYCC601;         /**< 是否支持xvYCC601颜色格式 */
    HI_BOOL             bSupportxvYCC709;         /**< 是否支持xvYCC709颜色格式 */
    HI_U8               u8MDBit;                  /**< xvYCC601支持的传输profile:1:P0,2:P1,4:P2 */
    
    HI_BOOL             bAudioFmtSupported[HI_UNF_HDMI_MAX_AUDIO_CAP_COUNT]; /**< 音频能力集, 请参考EIA-CEA-861-D 表37;HI_TRUE表示支持这种显示格式，HI_FALSE表示不支持 */
    HI_U32              u32AudioSampleRateSupported[HI_UNF_HDMI_MAX_AUDIO_SMPRATE_COUNT]; /**< PCM音频采样率能力集，0为非法值，其他为支持的音频采样率 */
    HI_U32              u32MaxPcmChannels;        /**< 音频最大的PCM通道数 */
    HI_U8               u8Speaker;                /**< 扬声器位置，请参考EIA-CEA-861-D中SpeakerDATABlock的定义 */
    
    HI_U8               u8IDManufactureName[4];   /**< 设备厂商标识 */
    HI_U32              u32IDProductCode;         /**< 设备ID */
    HI_U32              u32IDSerialNumber;        /**< 设备序列号 */
    HI_U32              u32WeekOfManufacture;     /**< 设备生产日期(周) */
    HI_U32              u32YearOfManufacture;     /**< 设备生产日期(年) */
    HI_U8               u8Version;                /**< 设备版本号 */
    HI_U8               u8Revision;               /**< 设备子版本号 */
    HI_U8               u8EDIDExternBlockNum;     /**< EDID扩展块数目 */

    HI_U8               u8IEERegId[3];            /**< 24-bit IEEE Registration Identifier (0x000C03) */
    HI_BOOL             bIsPhyAddrValid;          /**< CEC物理地址是否有效标志 */   
    HI_U8               u8PhyAddr_A;              /**< CEC物理地址A */
    HI_U8               u8PhyAddr_B;              /**< CEC物理地址B */  
    HI_U8               u8PhyAddr_C;              /**< CEC物理地址C */  
    HI_U8               u8PhyAddr_D;              /**< CEC物理地址D */  
    HI_BOOL             bSupportDVIDual;          /**< 是否支持 DVI dual-link 操作 */
    HI_BOOL             bSupportDeepColorYCBCR444;/**< 是否支持 YCBCR 4:4:4  Deep Color 模式 */
    HI_BOOL             bSupportDeepColor30Bit;   /**< 是否支持Deep Color 30bit 模式 */
    HI_BOOL             bSupportDeepColor36Bit;   /**< 是否支持Deep Color 36bit 模式 */
    HI_BOOL             bSupportDeepColor48Bit;   /**< 是否支持Deep Color 48bit 模式 */
    HI_BOOL             bSupportAI;               /**< 是否支持 Supports_AI 模式 */
    HI_U32              u8MaxTMDSClock;           /**< 最大TMDS时钟 */
    HI_BOOL             bI_Latency_Fields_Present;/**< 延时标志位 */
    HI_BOOL             bLatency_Fields_Present;  /**< whether Video_Latency and Audio_Latency fields are present */
    HI_BOOL             bHDMI_Video_Present;      /**< 特殊的视频格式 */
    HI_U8               u8Video_Latency;          /**< 视频延时 */
    HI_U8               u8Audio_Latency;          /**< 音频延时 */
    HI_U8               u8Interlaced_Video_Latency;/**< 隔行视频模式下的视频延时 */
    HI_U8               u8Interlaced_Audio_Latency;/**< 隔行视频模式下的音频延时 */
} HI_UNF_HDMI_SINK_CAPABILITY_S;

/**HDMI 接口参数配置 */
typedef struct hiUNF_HDMI_ATTR_S
{
	HI_BOOL                 bEnableHdmi;         /**< 是否强制HDMI,否则为DVI.该值必须在 HI_UNF_HDMI_Start之前或者HI_UNF_HDMI_Stop之后设置  */

    HI_BOOL                 bEnableVideo;        /**< 必须是HI_TRUE, 如果是HI_FALSE:HDMI驱动会强制设置为HI_TRUE */
    HI_UNF_ENC_FMT_E        enVideoFmt;          /**< 视频制式,此参数需要与Display配置的制式保持一致 */
    
    HI_UNF_HDMI_VIDEO_MODE_E enVidOutMode;       /**< HDMI输出视频模式，VIDEO_MODE_YCBCR444，VIDEO_MODE_YCBCR422，VIDEO_MODE_RGB444 */
    HI_UNF_HDMI_DEEP_COLOR_E enDeepColorMode;    /**< DeepColor输出模式, 默认为HI_UNF_HDMI_DEEP_COLOR_24BIT */
    HI_BOOL                 bxvYCCMode;          /**< xvYCC输出模式，默认为HI_FALSE */

    HI_BOOL                 bEnableAudio;        /**< 是否Enable音频 */
    HI_UNF_SND_INTERFACE_E  enSoundIntf;         /**< HDMI音频来源, 建议HI_UNF_SND_INTERFACE_I2S,此参数需要与AO输入保持一致 */
    HI_BOOL                 bIsMultiChannel;     /**< 多声道还是立体声，0:立体声，1:多声道固定为8声道 */
    HI_UNF_SAMPLE_RATE_E    enSampleRate;        /**< PCM音频采样率,此参数需要与AO的配置保持一致 */
    HI_U8                   u8DownSampleParm;    /**< PCM音频向下downsample采样率的参数，默认为0 */
    
    HI_UNF_BIT_DEPTH_E      enBitDepth;          /**< 音频位宽，默认为16,此参数需要与AO的配置保持一致 */
    HI_U8                   u8I2SCtlVbit;        /**< 保留，请配置为0, I2S control (0x7A:0x1D) */

    HI_BOOL                 bEnableAviInfoFrame; /**< 是否使能 AVI InfoFrame，建议使能 */
    HI_BOOL                 bEnableAudInfoFrame; /**< 是否使能 AUDIO InfoFrame，建议使能 */
    HI_BOOL                 bEnableSpdInfoFrame; /**< 是否使能 SPD InfoFrame， 建议关闭 */
    HI_BOOL                 bEnableMpegInfoFrame;/**< 是否使能 MPEG InfoFrame， 建议关闭 */

    HI_U32                  bDebugFlag;          /**< 是否使能 打开hdmi内部debug信息， 建议关闭 */
    HI_BOOL                 bHDCPEnable;         /**< 0:HDCP不激活，1:HDCP模式打开 */
    
    HI_BOOL                 b3DEnable;           /**< 0:3D不激活，1:3D模式打开 */
    HI_U32                  u83DParam;           /**< 3D Parameter, 默认为HI_FALSE */
} HI_UNF_HDMI_ATTR_S;


/** HDMI InfoFrame 类型定义 */
typedef enum tagHI_UNF_HDMI_INFOFRAME_TYPE_E
{
    HI_INFOFRAME_TYPE_AVI,          /**< HDMI AVI InfoFrame 类型定义 */
    HI_INFOFRAME_TYPE_SPD,          /**< HDMI SPD InfoFrame 类型定义 */
    HI_INFOFRAME_TYPE_AUDIO,        /**< HDMI AUDIO InfoFrame 类型定义 */    
    HI_INFOFRAME_TYPE_MPEG,         /**< HDMI MPEG InfoFrame 类型定义 */
    HI_INFOFRAME_TYPE_VENDORSPEC,   /**< HDMI Vendor Specific InfoFrame 类型定义 */  
    HI_INFOFRAME_TYPE_BUTT 
}HI_UNF_HDMI_INFOFRAME_TYPE_E;

/** HDMI AVI InfoFrame 参数结构, 请参考EIA-CEA-861-D */
typedef struct hiUNF_HDMI_AVI_INFOFRAME_VER2_S
{
    HI_UNF_ENC_FMT_E               enTimingMode;            /**< AVI视频timing格式 */
    HI_UNF_HDMI_VIDEO_MODE_E       enOutputType;            /**< AVI视频输出颜色格式 */   
    HI_BOOL                        bActive_Infor_Present;   /**< AVI视频Active_Infor_Present标志位 */
    HI_UNF_HDMI_BARINFO_E          enBarInfo;               /**< AVI视频BarInfo类型 */
    HI_UNF_HDMI_SCANINFO_E         enScanInfo;              /**< AVI视频ScanInfo类型 */
    HI_UNF_HDMI_COLORSPACE_E       enColorimetry;           /**< AVI视频Colorimetry类型 */
    HI_UNF_ASPECT_RATIO_E          enAspectRatio;           /**< AVI视频宽高比格式 */
    HI_UNF_ASPECT_RATIO_E          enActiveAspectRatio;     /**< AVI视频有效宽高比格式 */
    HI_UNF_HDMI_PICTURE_SCALING_E  enPictureScaling;        /**< AVI视频scaling格式 */
    HI_UNF_HDMI_RGB_QUAN_RAGE_E    enRGBQuantization;       /**< AVI视频RGB色度范围 */
    HI_BOOL                        bIsITContent;            /**< AVI视频ITcontent */
    HI_U32                         u32PixelRepetition;      /**< AVI视频像素重传标志位 */

    HI_UNF_HDMI_CONTENT_TYPE_E     enContentType;           /**< AVI视频内容的类型 */
    HI_UNF_HDMI_YCC_QUAN_RAGE_E    enYCCQuantization;       /**< AVI视频YCC色度范围 */
    
    HI_U32                         u32LineNEndofTopBar;     /**< AVI视频EndofTopBar坐标，缺省为0 */
    HI_U32                         u32LineNStartofBotBar;   /**< AVI视频StartofBotBar坐标，缺省为0 */
    HI_U32                         u32PixelNEndofLeftBar;   /**< AVI视频EndofLeft坐标，缺省为0 */
    HI_U32                         u32PixelNStartofRightBar;/**< AVI视频StartofRightBar坐标，缺省为0 */ 
}HI_UNF_HDMI_AVI_INFOFRAME_VER2_S;

/** HDMI AUDIO InfoFrame 参数结构, 请参考EIA-CEA-861-D */
typedef struct hiUNF_HDMI_AUD_INFOFRAME_VER1_S
{
    HI_U32                         u32ChannelCount;          /**< 音频 声道数 */
    HI_UNF_HDMI_CODING_TYPE_E      enCodingType;             /**< 音频 编码类型，缺省为0：Refer to Stream Header */
    HI_U32                         u32SampleSize;            /**< 音频 采样大小，缺省为0：Refer to Stream Header */
    HI_U32                         u32SamplingFrequency;     /**< 音频 采样频率，缺省为0：Refer to Stream Header */
    HI_U32                         u32ChannelAlloc;          /**< 音频 声道分配，缺省为0：Refer to Stream Header */
    HI_U32                         u32LevelShift;            /**< 音频 Levelshift，缺省为0：Refer to Stream Header */
    HI_BOOL                        u32DownmixInhibit;        /**< 音频 DownmixInhibit，缺省为0：Refer to Stream Header */
}HI_UNF_HDMI_AUD_INFOFRAME_VER1_S;

/** HDMI Source Product Description InfoFrame 参数结构 , 请参考EIA-CEA-861-D */
typedef struct hiUNF_HDMI_SPD_INFOFRAME_S
{
    HI_U8                          u8VendorName[8];          /**< 卖方名称 */
    HI_U8                          u8ProductDescription[16]; /**< 产品描述符 */  
}HI_UNF_HDMI_SPD_INFOFRAME_S;

/** HDMI MEPG SOURCE Description InfoFrame 参数结构 , 请参考EIA-CEA-861-D */
typedef struct hiUNF_HDMI_MPEGSOURCE_INFOFRAME_S
{
    HI_U32                         u32MPEGBitRate;           /**< MPEG位率 */
    HI_BOOL                        bIsFieldRepeated;         /**< FieldRepeater标志位 */
}HI_UNF_HDMI_MPEGSOURCE_INFOFRAME_S;

/** HDMI Vendor Specific InfoFrame 参数结构 , 请参考EIA-CEA-861-D */
typedef struct hiUNF_HDMI_VENDORSPEC_INFOFRAME_S
{
    HI_U32                         u32RegistrationId;       /**< 注册ID号 */
}HI_UNF_HDMI_VENDORSPEC_INFOFRAME_S;

/** HDMI InfoFrame 联合定义体 */
typedef union hiUNF_HDMI_INFOFRAME_UNIT_U
{
    HI_UNF_HDMI_AVI_INFOFRAME_VER2_S   stAVIInfoFrame;      /**< AVI信息帧 */
    HI_UNF_HDMI_AUD_INFOFRAME_VER1_S   stAUDInfoFrame;      /**< AUD信息帧 */
    HI_UNF_HDMI_SPD_INFOFRAME_S        stSPDInfoFrame;      /**< SPD信息帧 */
    HI_UNF_HDMI_MPEGSOURCE_INFOFRAME_S stMPEGSourceInfoFrame;/**< MPEGSource信息帧 */
    HI_UNF_HDMI_VENDORSPEC_INFOFRAME_S stVendorSpecInfoFrame;/**< VS信息帧 */
}HI_UNF_HMDI_INFORFRAME_UNIT_U;

/** HDMI InfoFrame 数据结构 */
typedef struct hiUNF_HDMI_INFOFRAME_S
{
    HI_UNF_HDMI_INFOFRAME_TYPE_E    enInfoFrameType;  /**<InfoFrame类型 */
    HI_UNF_HMDI_INFORFRAME_UNIT_U   unInforUnit;      /**<InfoFrame数据 */  
}HI_UNF_HDMI_INFOFRAME_S;

typedef enum hiUNF_HDMI_CEC_CMDTYPE_E
{
    HI_UNF_HDMI_CEC_AUTOPING,                         /**< CEC AutoPing命令 */
    HI_UNF_HDMI_CEC_RAWCOMMND,                        /**< CEC 原始命令 */
    HI_UNF_HDMI_CEC_BUTT
}HI_UNF_HDMI_CEC_CMDTYPE_E;

/** HDMI CEC 参数结构 */
typedef struct hiUNF_HDMI_CEC_CMD_S
{
    HI_U32    u32Reserved;                           /**< 暂不支持此功能 */
    HI_UNF_HDMI_CEC_CMDTYPE_E  enCMD;                /**< CEC 命令类型 */
}HI_UNF_HDMI_CEC_CMD_S;

typedef enum hiUNF_HDMI_3D_FORMAT_E
{
    HI_UNF_3D_FRAME_PACKETING                 = 0x00,
    HI_UNF_3D_FIELD_ALTERNATIVE               = 0x01,
    HI_UNF_3D_LINE_ALTERNATIVE                = 0x02,
    HI_UNF_3D_SIDE_BY_SIDE_FULL               = 0x03,
    HI_UNF_3D_L_DEPTH                         = 0x04,
    HI_UNF_3D_L_DEPTH_GRAPHICS_GRAPHICS_DEPTH = 0x05,
    HI_UNF_3D_TOP_AND_BOTTOM                  = 0x06,
    HI_UNF_3D_SIDE_BY_SIDE_HALF               = 0x08,
    HI_UNF_3D_MAX_BUTT
}HI_UNF_HDMI_3D_FORMAT_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_2_7 */
/** @{ */  /** <!-- 【HDMI】 */
/** 
\brief HDMI接口驱动软件初始化
\attention 必须在DISP驱动Setup之后和VO驱动Setup之前打开
\param[in] pstHdmiPara 初始化参数.
\子参数:pfnHdmiEventCallback 该hdmi回调事件在多线程中只有第一个调用进程有效，其他进程不能获得回调事件。
\retval HI_SUCCESS 成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_Init(HI_UNF_HDMI_INIT_PARA_S *pstHdmiPara);


/** 
\brief HDMI接口去初始化
\attention 必须在VO驱动Exit之后和DISP驱动Exit之前打开
\param 无
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_DeInit(void);


/** 
\brief 创建HDMI设备
\attention \n
\param[in] enHdmi  要打开的HDMI设备 
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_E enHdmi);


/** 
\brief 销毁由HI_UNF_HDMI_Open创建的句柄
\attention \n
\param[in] enHdmi   HDMI设备ID
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_E enHdmi);


/** 
\brief 查询获取HDMI Sink设备的能力集
\attention \n
\param[in] enHdmi   HDMI设备ID
\param[out] pCapability  SINK能力集
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see ::HI_UNF_HDMI_SINK_CAPABILITY_S\n
无
*/
HI_S32 HI_UNF_HDMI_GetSinkCapability(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_SINK_CAPABILITY_S *pCapability);


/** 
\brief 设置HDMI接口属性。
\attention \n
\param[in] enHdmi   HDMI设备ID
\param[in] pstAttr      HDMI接口属性
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see ::HI_UNF_HDMI_ATTR_S\n
无
*/
HI_S32 HI_UNF_HDMI_SetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr);


/** 
\brief 查询HDMI接口当前属性
\attention \n
\param[in] enHdmi   HDMI设备ID
\param[out] pstAttr     HDMI接口属性
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see HI_UNF_HDMI_ATTR_S\n
无
*/
HI_S32 HI_UNF_HDMI_GetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr);


/** 
\brief 发送CEC 命令
\attention 暂时不支持这个接口\n
\param[in] enHdmi   HDMI设备ID
\param[in] pCECCmd      Cec Command 内容
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see ::HI_UNF_HDMI_CEC_CMD_S\n
无
*/
HI_S32 HI_UNF_HDMI_SetCECCommand(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_CEC_CMD_S  *pCECCmd);


/** 
\brief 接收的CEC 命令
\attention 暂时不支持这个接口\n
\param[in] enHdmi   HDMI设备ID
\param[in] pCECCmd      Cec Command 内容
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see ::HI_UNF_HDMI_CEC_CMD_S\n
无
*/
HI_S32 HI_UNF_HDMI_GetCECCommand(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_CEC_CMD_S  *pCECCmd);


/** 
\brief 设置并发送InfoFrame
\attention \n
\param[in] enHdmi       HDMI设备ID
\param[in] pstInfoFrame InfoFrame内容
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_SetInfoFrame(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_INFOFRAME_S *pstInfoFrame);

/** 
\brief 获取正在发送的InfoFrame的信息
\attention \n
\param[in] enHdmi       HDMI设备ID
\param[in] pstInfoFrame InfoFrame内容
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_GetInfoFrame(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_INFOFRAME_TYPE_E enInfoFrameType, HI_UNF_HDMI_INFOFRAME_S *pstInfoFrame);



/** 
\brief 启动HDMI接口。一般在HI_UNF_HDMI_SetAttr之后调用
\attention \n
\param[in] enHdmi   HDMI设备ID
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_Start(HI_UNF_HDMI_ID_E enHdmi);

/** 
\brief 停止HDMI接口，下电,当HDMI线被拔除后，HDMI回调函数应该调用该函数。
\attention \n
\param[in] enHdmi   HDMI设备ID
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_Stop(HI_UNF_HDMI_ID_E enHdmi);

/** 
\brief 设置HDMI DeepColor模式
\attention \n
\param[in] enHdmi   HDMI设备ID
\param[in] enDeepColor   DeepColor模式，请参考::HI_UNF_HDMI_DEEP_COLOR_E  
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_SetDeepColor(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_DEEP_COLOR_E enDeepColor);

/** 
\brief 设置HDMI xvYCC 模式
\attention \n
\param[in] enHdmi   HDMI设备ID
\param[in] bEnalbe   是否使能xvYCC模式
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_SetxvYCCMode(HI_UNF_HDMI_ID_E enHdmi, HI_BOOL bEnalbe);

/** 
\brief 设置HDMI AV mute 模式
\attention \n
\param[in] enHdmi   HDMI设备ID
\param[in] bAvMute   是否mute AV
\retval HI_SUCCESS      成功
\retval 请参考MPI错误码
\see \n
无
*/
HI_S32 HI_UNF_HDMI_SetAVMute(HI_UNF_HDMI_ID_E enHdmi, HI_BOOL bAvMute);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
}
#endif
#endif /* __HI_UNF_HDMI_H__ */

