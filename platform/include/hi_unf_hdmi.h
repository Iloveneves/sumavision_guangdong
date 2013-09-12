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
/** @{ */  /** <!-- ��HDMI�� */

/**�����Ƶ���������� */
#define HI_UNF_HDMI_MAX_AUDIO_CAP_COUNT     15 

/**�����Ƶ�����ʸ��� */
#define HI_UNF_HDMI_MAX_AUDIO_SMPRATE_COUNT 10 

/**< �����Ϣ֡���� */
#define HI_UNF_HDMI_MAX_INFOFRAME_LEN   0X20   

/**< HDMI ȱʡֵ */
#define HI_UNF_HDMI_DEFAULT_SETTING     0x00

/** HDMI�ӿ�ID  */
typedef enum hiUNF_HDMI_ID_E
{
    HI_UNF_HDMI_ID_0         = 0,           /**< HDMI�ӿ�0 */
    HI_UNF_HDMI_ID_BUTT
} HI_UNF_HDMI_ID_E;

/** HDMI�¼����� */
typedef enum hiUNF_HDMI_EVENT_TYPE_E
{
    HI_UNF_HDMI_EVENT_HOTPLUG = 0x10,       /**<HDMI�Ȳ���¼� */
    HI_UNF_HDMI_EVENT_NO_PLUG,              /**<HDMI Cableû������ �¼� */
    HI_UNF_HDMI_EVENT_EDID_FAIL,            /**<HDMI EDID��ȡʧ���¼� */
    HI_UNF_HDMI_EVENT_HDCP_FAIL,            /**<HDCP��֤ʧ���¼� */
    HI_UNF_HDMI_EVENT_HDCP_SUCCESS,         /**<HDCP��֤�ɹ� */
    HI_UNF_HDMI_EVENT_HDCP_USERSETTING,     /**<HDMI Reset */
    HI_UNF_HDMI_EVENT_BUTT
}HI_UNF_HDMI_EVENT_TYPE_E;

/**��Ƶ��ɫ�ռ�����*/
typedef enum hiUNF_HDMI_VIDEO_MODE
{
    HI_UNF_HDMI_VIDEO_MODE_RGB444,          /**<RGB444���ģʽ */ 
    HI_UNF_HDMI_VIDEO_MODE_YCBCR422,        /**<YCBCR422���ģʽ */ 
    HI_UNF_HDMI_VIDEO_MODE_YCBCR444,        /**<YCBCR444���ģʽ */ 
        
    HI_UNF_HDMI_VIDEO_MODE_BUTT    
}HI_UNF_HDMI_VIDEO_MODE_E;


/** HDMI Deep Color ģʽ */
typedef enum hiUNF_HDMI_DEEP_COLOR_E
{
    HI_UNF_HDMI_DEEP_COLOR_24BIT = 0x00,    /**< HDMI Deep Color 24bit ģʽ  */
    HI_UNF_HDMI_DEEP_COLOR_30BIT,           /**< HDMI Deep Color 30bit ģʽ  */
    HI_UNF_HDMI_DEEP_COLOR_36BIT,           /**< HDMI Deep Color 36bit ģʽ  */  
    HI_UNF_HDMI_DEEP_COLOR_OFF   = 0xff,
    HI_UNF_HDMI_DEEP_COLOR_BUTT
}HI_UNF_HDMI_DEEP_COLOR_E;

/** HDMI AVI��Ϣ֡ BarInfo ö�� */
typedef enum hiUNF_HDMI_BARINFO_E
{
   HDMI_BAR_INFO_NOT_VALID,                 /**< Bar Data not valid */
   HDMI_BAR_INFO_V,                         /**< Vertical bar data valid */
   HDMI_BAR_INFO_H,                         /**< Horizental bar data valid */
   HDMI_BAR_INFO_VH                         /**< Horizental and Vertical bar data valid */
}HI_UNF_HDMI_BARINFO_E;

/** HDMI AVI��Ϣ֡ ScanInfo ö�� */
typedef enum hiUNF_HDMI_SCANINFO_E
{
    HDMI_SCAN_INFO_NO_DATA      = 0,        /**< No Scan information*/
    HDMI_SCAN_INFO_OVERSCANNED  = 1,        /**< Scan information, Overscanned (for television) */
    HDMI_SCAN_INFO_UNDERSCANNED = 2,        /**< Scan information, Underscanned (for computer) */
    HDMI_SCAN_INFO_FUTURE
}HI_UNF_HDMI_SCANINFO_E;

/** HDMI AVI��Ϣ֡ Picture scan ö�� */
typedef enum hiUNF_HDMI_PICTURE_SCALING_E
{
    HDMI_PICTURE_NON_UNIFORM_SCALING,       /**< No Known, non-uniform picture scaling  */
    HDMI_PICTURE_SCALING_H,                 /**< Picture has been scaled horizentally */
    HDMI_PICTURE_SCALING_V,                 /**< Picture has been scaled Vertically */
    HDMI_PICTURE_SCALING_HV                 /**< Picture has been scaled Horizentally and Vertically   */
 }HI_UNF_HDMI_PICTURE_SCALING_E;

/** HDMI AVI��Ϣ֡ ɫ�ȿռ� ö�� */
typedef enum hiUNF_HDMI_COLORSPACE_E
{
    HDMI_COLORIMETRY_NO_DATA,               /**< Colorimetry No Dataѡ�� */
    HDMI_COLORIMETRY_ITU601,                /**< Colorimetry ITU601ɫ�ȿռ�ѡ�� */
    HDMI_COLORIMETRY_ITU709,                /**< Colorimetry ITU709ɫ�ȿռ�ѡ�� */
    HDMI_COLORIMETRY_EXTENDED,              /**< Colorimetry ��չѡ�� */
    HDMI_COLORIMETRY_XVYCC_601,             /**< Colorimetry xvYCC601��չѡ�� */
    HDMI_COLORIMETRY_XVYCC_709              /**< Colorimetry xvYCC709��չѡ�� */
}HI_UNF_HDMI_COLORSPACE_E;

/** HDMI AVI��Ϣ֡ RGBɫ�ȷ�Χ ö�� */
typedef enum hiUNF_HDMI_RGB_QUAN_RAGE_E
{
    HDMI_RGB_QUANTIZATION_DEFAULT_RANGE,    /**< Defaulr range, it depends on the video format */
    HDMI_RGB_QUANTIZATION_LIMITED_RANGE,    /**< Limited quantization range of 220 levels when receiving a CE video format*/
    HDMI_RGB_QUANTIZATION_FULL_RANGE        /**< Full quantization range of 256 levels when receiving an IT video format*/
}HI_UNF_HDMI_RGB_QUAN_RAGE_E;

/** HDMI AVI��Ϣ֡ YCCɫ�ȷ�Χ ö�� */
typedef enum hiUNF_HDMI_YCC_QUAN_RAGE_E
{
    HDMI_YCC_QUANTIZATION_LIMITED_RANGE,    /**< Limited quantization range of 220 levels when receiving a CE video format*/
    HDMI_YCC_QUANTIZATION_FULL_RANGE        /**< Full quantization range of 256 levels when receiving an IT video format*/
}HI_UNF_HDMI_YCC_QUAN_RAGE_E;

/** HDMI AVI��Ϣ֡ AVI��Ƶ���ݵ����� ö�� */
typedef enum hiUNF_HDMI_CONTENT_TYPE_E
{
    HDMI_CONTNET_GRAPHIC,                   /**< Graphics type*/
    HDMI_CONTNET_PHOTO,                     /**< Photo type*/
    HDMI_CONTNET_CINEMA,                    /**< Cinema type*/
    HDMI_CONTNET_GAME                       /**< Game type*/
}HI_UNF_HDMI_CONTENT_TYPE_E;

/** HDMI AUD��Ϣ֡ ��Ƶ���� ö�� */
typedef enum hiUNF_HDMI_CODING_TYPE_E
{
    HDMI_AUDIO_CODING_REFER_STREAM_HEAD,  /**< ��Ƶ�������ͣ��ο���������ȱʡ��ʽ */
    HDMI_AUDIO_CODING_PCM,                /**< ��Ƶ����PCM��ʽ */
    HDMI_AUDIO_CODING_AC3,                /**< ��Ƶ����AC3��ʽ */
    HDMI_AUDIO_CODING_MPEG1,              /**< ��Ƶ����MPEG1��ʽ */
    HDMI_AUDIO_CODING_MP3,                /**< ��Ƶ����MP3��ʽ */
    HDMI_AUDIO_CODING_MPEG2,              /**< ��Ƶ����MPEG2��ʽ */
    HDMI_AUDIO_CODING_AAC,                /**< ��Ƶ����AAC��ʽ */
    HDMI_AUDIO_CODING_DTS,                /**< ��Ƶ����DTS��ʽ */
    HDMI_AUDIO_CODING_DDPLUS,             /**< ��Ƶ����DDPLUS��ʽ */
    HDMI_AUDIO_CODING_MLP,                /**< ��Ƶ����MLP��ʽ */
    HDMI_AUDIO_CODING_WMA,                /**< ��Ƶ����WMA��ʽ */
    HDMI_AUDIO_CODING_MAX
}HI_UNF_HDMI_CODING_TYPE_E;

/** HDMIǣ�����ģʽ ö�� */
typedef enum hiUNF_HDMI_FORCE_ACTION_E
{
    HI_UNF_HDMI_FORCE_NULL,               /**< ��׼ģʽ */
    HI_UNF_HDMI_FORCE_HDMI,               /**< ǿ�ư�HDMI��ʽ��� */
    HI_UNF_HDMI_FORCE_DVI,                /**< ǿ�ư�DVI��ʽ��� */
    HI_UNF_HDMI_INIT_BOOT_CONFIG          /**< ʹ��boot��HDMI���õĲ�����ʼ��HDMI, Test Only */
}HI_UNF_HDMI_FORCE_ACTION_E;

/** �ӿ��Ȳ�λص����� */
typedef void (*HI_UNF_HDMI_CallBack)(HI_UNF_HDMI_EVENT_TYPE_E event, HI_VOID *pPrivateData);

/** HDMI�ӿڳ�ʼ������ */
typedef struct hiUNF_HDMI_INIT_PARA_S
{
    HI_UNF_HDMI_CallBack pfnHdmiEventCallback;    /**< �¼��ص� */
    HI_VOID             *pCallBackArgs;           /**< �ص���������˽������ */
    HI_UNF_HDMI_FORCE_ACTION_E enForceMode;       /**< 0:����׼Э��ģʽ HDMI ATC���Ա���ʹ��0,1:ǿ��HDMIģʽ,2:ǿ��ΪDVIģʽ */
}HI_UNF_HDMI_INIT_PARA_S;

/** HDMI sink �ӿ������� */
typedef struct hiUNF_HDMI_SINK_CAPABILITY_S
{
    HI_BOOL             bConnected;               /**< �豸�Ƿ����� */
    HI_BOOL             bSupportHdmi;             /**< �豸�Ƿ�֧��HDMI�������֧�֣���ΪDVI�豸.*/
    HI_BOOL             bIsSinkPowerOn;           /**< Sink�豸�Ƿ��ϵ� */
    HI_BOOL             bIsRealEDID;              /**< EDID�Ƿ���������sink�豸��ȡ��־��HI_TRUEΪ��ȷ��ȡ��HI_FASEΪǿ�����ý�� */

    HI_UNF_ENC_FMT_E    enNativeVideoFormat;      /**< ��ʾ�豸����ֱ��� */
    HI_BOOL             bVideoFmtSupported[HI_UNF_ENC_FMT_BUTT]; /**< ��Ƶ������,HI_TRUE��ʾ֧��������ʾ��ʽ��HI_FALSE��ʾ��֧�� */
    HI_BOOL             bSupportYCbCr;            /**< �Ƿ�֧��YCBCR��ʾ�� ���ΪHI_FALSE,��ʾֻ֧��RGB��ʾ */
    
    HI_BOOL             bSupportxvYCC601;         /**< �Ƿ�֧��xvYCC601��ɫ��ʽ */
    HI_BOOL             bSupportxvYCC709;         /**< �Ƿ�֧��xvYCC709��ɫ��ʽ */
    HI_U8               u8MDBit;                  /**< xvYCC601֧�ֵĴ���profile:1:P0,2:P1,4:P2 */
    
    HI_BOOL             bAudioFmtSupported[HI_UNF_HDMI_MAX_AUDIO_CAP_COUNT]; /**< ��Ƶ������, ��ο�EIA-CEA-861-D ��37;HI_TRUE��ʾ֧��������ʾ��ʽ��HI_FALSE��ʾ��֧�� */
    HI_U32              u32AudioSampleRateSupported[HI_UNF_HDMI_MAX_AUDIO_SMPRATE_COUNT]; /**< PCM��Ƶ��������������0Ϊ�Ƿ�ֵ������Ϊ֧�ֵ���Ƶ������ */
    HI_U32              u32MaxPcmChannels;        /**< ��Ƶ����PCMͨ���� */
    HI_U8               u8Speaker;                /**< ������λ�ã���ο�EIA-CEA-861-D��SpeakerDATABlock�Ķ��� */
    
    HI_U8               u8IDManufactureName[4];   /**< �豸���̱�ʶ */
    HI_U32              u32IDProductCode;         /**< �豸ID */
    HI_U32              u32IDSerialNumber;        /**< �豸���к� */
    HI_U32              u32WeekOfManufacture;     /**< �豸��������(��) */
    HI_U32              u32YearOfManufacture;     /**< �豸��������(��) */
    HI_U8               u8Version;                /**< �豸�汾�� */
    HI_U8               u8Revision;               /**< �豸�Ӱ汾�� */
    HI_U8               u8EDIDExternBlockNum;     /**< EDID��չ����Ŀ */

    HI_U8               u8IEERegId[3];            /**< 24-bit IEEE Registration Identifier (0x000C03) */
    HI_BOOL             bIsPhyAddrValid;          /**< CEC�����ַ�Ƿ���Ч��־ */   
    HI_U8               u8PhyAddr_A;              /**< CEC�����ַA */
    HI_U8               u8PhyAddr_B;              /**< CEC�����ַB */  
    HI_U8               u8PhyAddr_C;              /**< CEC�����ַC */  
    HI_U8               u8PhyAddr_D;              /**< CEC�����ַD */  
    HI_BOOL             bSupportDVIDual;          /**< �Ƿ�֧�� DVI dual-link ���� */
    HI_BOOL             bSupportDeepColorYCBCR444;/**< �Ƿ�֧�� YCBCR 4:4:4  Deep Color ģʽ */
    HI_BOOL             bSupportDeepColor30Bit;   /**< �Ƿ�֧��Deep Color 30bit ģʽ */
    HI_BOOL             bSupportDeepColor36Bit;   /**< �Ƿ�֧��Deep Color 36bit ģʽ */
    HI_BOOL             bSupportDeepColor48Bit;   /**< �Ƿ�֧��Deep Color 48bit ģʽ */
    HI_BOOL             bSupportAI;               /**< �Ƿ�֧�� Supports_AI ģʽ */
    HI_U32              u8MaxTMDSClock;           /**< ���TMDSʱ�� */
    HI_BOOL             bI_Latency_Fields_Present;/**< ��ʱ��־λ */
    HI_BOOL             bLatency_Fields_Present;  /**< whether Video_Latency and Audio_Latency fields are present */
    HI_BOOL             bHDMI_Video_Present;      /**< �������Ƶ��ʽ */
    HI_U8               u8Video_Latency;          /**< ��Ƶ��ʱ */
    HI_U8               u8Audio_Latency;          /**< ��Ƶ��ʱ */
    HI_U8               u8Interlaced_Video_Latency;/**< ������Ƶģʽ�µ���Ƶ��ʱ */
    HI_U8               u8Interlaced_Audio_Latency;/**< ������Ƶģʽ�µ���Ƶ��ʱ */
} HI_UNF_HDMI_SINK_CAPABILITY_S;

/**HDMI �ӿڲ������� */
typedef struct hiUNF_HDMI_ATTR_S
{
	HI_BOOL                 bEnableHdmi;         /**< �Ƿ�ǿ��HDMI,����ΪDVI.��ֵ������ HI_UNF_HDMI_Start֮ǰ����HI_UNF_HDMI_Stop֮������  */

    HI_BOOL                 bEnableVideo;        /**< ������HI_TRUE, �����HI_FALSE:HDMI������ǿ������ΪHI_TRUE */
    HI_UNF_ENC_FMT_E        enVideoFmt;          /**< ��Ƶ��ʽ,�˲�����Ҫ��Display���õ���ʽ����һ�� */
    
    HI_UNF_HDMI_VIDEO_MODE_E enVidOutMode;       /**< HDMI�����Ƶģʽ��VIDEO_MODE_YCBCR444��VIDEO_MODE_YCBCR422��VIDEO_MODE_RGB444 */
    HI_UNF_HDMI_DEEP_COLOR_E enDeepColorMode;    /**< DeepColor���ģʽ, Ĭ��ΪHI_UNF_HDMI_DEEP_COLOR_24BIT */
    HI_BOOL                 bxvYCCMode;          /**< xvYCC���ģʽ��Ĭ��ΪHI_FALSE */

    HI_BOOL                 bEnableAudio;        /**< �Ƿ�Enable��Ƶ */
    HI_UNF_SND_INTERFACE_E  enSoundIntf;         /**< HDMI��Ƶ��Դ, ����HI_UNF_SND_INTERFACE_I2S,�˲�����Ҫ��AO���뱣��һ�� */
    HI_BOOL                 bIsMultiChannel;     /**< ������������������0:��������1:�������̶�Ϊ8���� */
    HI_UNF_SAMPLE_RATE_E    enSampleRate;        /**< PCM��Ƶ������,�˲�����Ҫ��AO�����ñ���һ�� */
    HI_U8                   u8DownSampleParm;    /**< PCM��Ƶ����downsample�����ʵĲ�����Ĭ��Ϊ0 */
    
    HI_UNF_BIT_DEPTH_E      enBitDepth;          /**< ��Ƶλ��Ĭ��Ϊ16,�˲�����Ҫ��AO�����ñ���һ�� */
    HI_U8                   u8I2SCtlVbit;        /**< ������������Ϊ0, I2S control (0x7A:0x1D) */

    HI_BOOL                 bEnableAviInfoFrame; /**< �Ƿ�ʹ�� AVI InfoFrame������ʹ�� */
    HI_BOOL                 bEnableAudInfoFrame; /**< �Ƿ�ʹ�� AUDIO InfoFrame������ʹ�� */
    HI_BOOL                 bEnableSpdInfoFrame; /**< �Ƿ�ʹ�� SPD InfoFrame�� ����ر� */
    HI_BOOL                 bEnableMpegInfoFrame;/**< �Ƿ�ʹ�� MPEG InfoFrame�� ����ر� */

    HI_U32                  bDebugFlag;          /**< �Ƿ�ʹ�� ��hdmi�ڲ�debug��Ϣ�� ����ر� */
    HI_BOOL                 bHDCPEnable;         /**< 0:HDCP�����1:HDCPģʽ�� */
    
    HI_BOOL                 b3DEnable;           /**< 0:3D�����1:3Dģʽ�� */
    HI_U32                  u83DParam;           /**< 3D Parameter, Ĭ��ΪHI_FALSE */
} HI_UNF_HDMI_ATTR_S;


/** HDMI InfoFrame ���Ͷ��� */
typedef enum tagHI_UNF_HDMI_INFOFRAME_TYPE_E
{
    HI_INFOFRAME_TYPE_AVI,          /**< HDMI AVI InfoFrame ���Ͷ��� */
    HI_INFOFRAME_TYPE_SPD,          /**< HDMI SPD InfoFrame ���Ͷ��� */
    HI_INFOFRAME_TYPE_AUDIO,        /**< HDMI AUDIO InfoFrame ���Ͷ��� */    
    HI_INFOFRAME_TYPE_MPEG,         /**< HDMI MPEG InfoFrame ���Ͷ��� */
    HI_INFOFRAME_TYPE_VENDORSPEC,   /**< HDMI Vendor Specific InfoFrame ���Ͷ��� */  
    HI_INFOFRAME_TYPE_BUTT 
}HI_UNF_HDMI_INFOFRAME_TYPE_E;

/** HDMI AVI InfoFrame �����ṹ, ��ο�EIA-CEA-861-D */
typedef struct hiUNF_HDMI_AVI_INFOFRAME_VER2_S
{
    HI_UNF_ENC_FMT_E               enTimingMode;            /**< AVI��Ƶtiming��ʽ */
    HI_UNF_HDMI_VIDEO_MODE_E       enOutputType;            /**< AVI��Ƶ�����ɫ��ʽ */   
    HI_BOOL                        bActive_Infor_Present;   /**< AVI��ƵActive_Infor_Present��־λ */
    HI_UNF_HDMI_BARINFO_E          enBarInfo;               /**< AVI��ƵBarInfo���� */
    HI_UNF_HDMI_SCANINFO_E         enScanInfo;              /**< AVI��ƵScanInfo���� */
    HI_UNF_HDMI_COLORSPACE_E       enColorimetry;           /**< AVI��ƵColorimetry���� */
    HI_UNF_ASPECT_RATIO_E          enAspectRatio;           /**< AVI��Ƶ��߱ȸ�ʽ */
    HI_UNF_ASPECT_RATIO_E          enActiveAspectRatio;     /**< AVI��Ƶ��Ч��߱ȸ�ʽ */
    HI_UNF_HDMI_PICTURE_SCALING_E  enPictureScaling;        /**< AVI��Ƶscaling��ʽ */
    HI_UNF_HDMI_RGB_QUAN_RAGE_E    enRGBQuantization;       /**< AVI��ƵRGBɫ�ȷ�Χ */
    HI_BOOL                        bIsITContent;            /**< AVI��ƵITcontent */
    HI_U32                         u32PixelRepetition;      /**< AVI��Ƶ�����ش���־λ */

    HI_UNF_HDMI_CONTENT_TYPE_E     enContentType;           /**< AVI��Ƶ���ݵ����� */
    HI_UNF_HDMI_YCC_QUAN_RAGE_E    enYCCQuantization;       /**< AVI��ƵYCCɫ�ȷ�Χ */
    
    HI_U32                         u32LineNEndofTopBar;     /**< AVI��ƵEndofTopBar���꣬ȱʡΪ0 */
    HI_U32                         u32LineNStartofBotBar;   /**< AVI��ƵStartofBotBar���꣬ȱʡΪ0 */
    HI_U32                         u32PixelNEndofLeftBar;   /**< AVI��ƵEndofLeft���꣬ȱʡΪ0 */
    HI_U32                         u32PixelNStartofRightBar;/**< AVI��ƵStartofRightBar���꣬ȱʡΪ0 */ 
}HI_UNF_HDMI_AVI_INFOFRAME_VER2_S;

/** HDMI AUDIO InfoFrame �����ṹ, ��ο�EIA-CEA-861-D */
typedef struct hiUNF_HDMI_AUD_INFOFRAME_VER1_S
{
    HI_U32                         u32ChannelCount;          /**< ��Ƶ ������ */
    HI_UNF_HDMI_CODING_TYPE_E      enCodingType;             /**< ��Ƶ �������ͣ�ȱʡΪ0��Refer to Stream Header */
    HI_U32                         u32SampleSize;            /**< ��Ƶ ������С��ȱʡΪ0��Refer to Stream Header */
    HI_U32                         u32SamplingFrequency;     /**< ��Ƶ ����Ƶ�ʣ�ȱʡΪ0��Refer to Stream Header */
    HI_U32                         u32ChannelAlloc;          /**< ��Ƶ �������䣬ȱʡΪ0��Refer to Stream Header */
    HI_U32                         u32LevelShift;            /**< ��Ƶ Levelshift��ȱʡΪ0��Refer to Stream Header */
    HI_BOOL                        u32DownmixInhibit;        /**< ��Ƶ DownmixInhibit��ȱʡΪ0��Refer to Stream Header */
}HI_UNF_HDMI_AUD_INFOFRAME_VER1_S;

/** HDMI Source Product Description InfoFrame �����ṹ , ��ο�EIA-CEA-861-D */
typedef struct hiUNF_HDMI_SPD_INFOFRAME_S
{
    HI_U8                          u8VendorName[8];          /**< �������� */
    HI_U8                          u8ProductDescription[16]; /**< ��Ʒ������ */  
}HI_UNF_HDMI_SPD_INFOFRAME_S;

/** HDMI MEPG SOURCE Description InfoFrame �����ṹ , ��ο�EIA-CEA-861-D */
typedef struct hiUNF_HDMI_MPEGSOURCE_INFOFRAME_S
{
    HI_U32                         u32MPEGBitRate;           /**< MPEGλ�� */
    HI_BOOL                        bIsFieldRepeated;         /**< FieldRepeater��־λ */
}HI_UNF_HDMI_MPEGSOURCE_INFOFRAME_S;

/** HDMI Vendor Specific InfoFrame �����ṹ , ��ο�EIA-CEA-861-D */
typedef struct hiUNF_HDMI_VENDORSPEC_INFOFRAME_S
{
    HI_U32                         u32RegistrationId;       /**< ע��ID�� */
}HI_UNF_HDMI_VENDORSPEC_INFOFRAME_S;

/** HDMI InfoFrame ���϶����� */
typedef union hiUNF_HDMI_INFOFRAME_UNIT_U
{
    HI_UNF_HDMI_AVI_INFOFRAME_VER2_S   stAVIInfoFrame;      /**< AVI��Ϣ֡ */
    HI_UNF_HDMI_AUD_INFOFRAME_VER1_S   stAUDInfoFrame;      /**< AUD��Ϣ֡ */
    HI_UNF_HDMI_SPD_INFOFRAME_S        stSPDInfoFrame;      /**< SPD��Ϣ֡ */
    HI_UNF_HDMI_MPEGSOURCE_INFOFRAME_S stMPEGSourceInfoFrame;/**< MPEGSource��Ϣ֡ */
    HI_UNF_HDMI_VENDORSPEC_INFOFRAME_S stVendorSpecInfoFrame;/**< VS��Ϣ֡ */
}HI_UNF_HMDI_INFORFRAME_UNIT_U;

/** HDMI InfoFrame ���ݽṹ */
typedef struct hiUNF_HDMI_INFOFRAME_S
{
    HI_UNF_HDMI_INFOFRAME_TYPE_E    enInfoFrameType;  /**<InfoFrame���� */
    HI_UNF_HMDI_INFORFRAME_UNIT_U   unInforUnit;      /**<InfoFrame���� */  
}HI_UNF_HDMI_INFOFRAME_S;

typedef enum hiUNF_HDMI_CEC_CMDTYPE_E
{
    HI_UNF_HDMI_CEC_AUTOPING,                         /**< CEC AutoPing���� */
    HI_UNF_HDMI_CEC_RAWCOMMND,                        /**< CEC ԭʼ���� */
    HI_UNF_HDMI_CEC_BUTT
}HI_UNF_HDMI_CEC_CMDTYPE_E;

/** HDMI CEC �����ṹ */
typedef struct hiUNF_HDMI_CEC_CMD_S
{
    HI_U32    u32Reserved;                           /**< �ݲ�֧�ִ˹��� */
    HI_UNF_HDMI_CEC_CMDTYPE_E  enCMD;                /**< CEC �������� */
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
/** @{ */  /** <!-- ��HDMI�� */
/** 
\brief HDMI�ӿ����������ʼ��
\attention ������DISP����Setup֮���VO����Setup֮ǰ��
\param[in] pstHdmiPara ��ʼ������.
\�Ӳ���:pfnHdmiEventCallback ��hdmi�ص��¼��ڶ��߳���ֻ�е�һ�����ý�����Ч���������̲��ܻ�ûص��¼���
\retval HI_SUCCESS �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_Init(HI_UNF_HDMI_INIT_PARA_S *pstHdmiPara);


/** 
\brief HDMI�ӿ�ȥ��ʼ��
\attention ������VO����Exit֮���DISP����Exit֮ǰ��
\param ��
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_DeInit(void);


/** 
\brief ����HDMI�豸
\attention \n
\param[in] enHdmi  Ҫ�򿪵�HDMI�豸 
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_E enHdmi);


/** 
\brief ������HI_UNF_HDMI_Open�����ľ��
\attention \n
\param[in] enHdmi   HDMI�豸ID
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_E enHdmi);


/** 
\brief ��ѯ��ȡHDMI Sink�豸��������
\attention \n
\param[in] enHdmi   HDMI�豸ID
\param[out] pCapability  SINK������
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see ::HI_UNF_HDMI_SINK_CAPABILITY_S\n
��
*/
HI_S32 HI_UNF_HDMI_GetSinkCapability(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_SINK_CAPABILITY_S *pCapability);


/** 
\brief ����HDMI�ӿ����ԡ�
\attention \n
\param[in] enHdmi   HDMI�豸ID
\param[in] pstAttr      HDMI�ӿ�����
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see ::HI_UNF_HDMI_ATTR_S\n
��
*/
HI_S32 HI_UNF_HDMI_SetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr);


/** 
\brief ��ѯHDMI�ӿڵ�ǰ����
\attention \n
\param[in] enHdmi   HDMI�豸ID
\param[out] pstAttr     HDMI�ӿ�����
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see HI_UNF_HDMI_ATTR_S\n
��
*/
HI_S32 HI_UNF_HDMI_GetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr);


/** 
\brief ����CEC ����
\attention ��ʱ��֧������ӿ�\n
\param[in] enHdmi   HDMI�豸ID
\param[in] pCECCmd      Cec Command ����
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see ::HI_UNF_HDMI_CEC_CMD_S\n
��
*/
HI_S32 HI_UNF_HDMI_SetCECCommand(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_CEC_CMD_S  *pCECCmd);


/** 
\brief ���յ�CEC ����
\attention ��ʱ��֧������ӿ�\n
\param[in] enHdmi   HDMI�豸ID
\param[in] pCECCmd      Cec Command ����
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see ::HI_UNF_HDMI_CEC_CMD_S\n
��
*/
HI_S32 HI_UNF_HDMI_GetCECCommand(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_CEC_CMD_S  *pCECCmd);


/** 
\brief ���ò�����InfoFrame
\attention \n
\param[in] enHdmi       HDMI�豸ID
\param[in] pstInfoFrame InfoFrame����
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_SetInfoFrame(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_INFOFRAME_S *pstInfoFrame);

/** 
\brief ��ȡ���ڷ��͵�InfoFrame����Ϣ
\attention \n
\param[in] enHdmi       HDMI�豸ID
\param[in] pstInfoFrame InfoFrame����
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_GetInfoFrame(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_INFOFRAME_TYPE_E enInfoFrameType, HI_UNF_HDMI_INFOFRAME_S *pstInfoFrame);



/** 
\brief ����HDMI�ӿڡ�һ����HI_UNF_HDMI_SetAttr֮�����
\attention \n
\param[in] enHdmi   HDMI�豸ID
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_Start(HI_UNF_HDMI_ID_E enHdmi);

/** 
\brief ֹͣHDMI�ӿڣ��µ�,��HDMI�߱��γ���HDMI�ص�����Ӧ�õ��øú�����
\attention \n
\param[in] enHdmi   HDMI�豸ID
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_Stop(HI_UNF_HDMI_ID_E enHdmi);

/** 
\brief ����HDMI DeepColorģʽ
\attention \n
\param[in] enHdmi   HDMI�豸ID
\param[in] enDeepColor   DeepColorģʽ����ο�::HI_UNF_HDMI_DEEP_COLOR_E  
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_SetDeepColor(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_DEEP_COLOR_E enDeepColor);

/** 
\brief ����HDMI xvYCC ģʽ
\attention \n
\param[in] enHdmi   HDMI�豸ID
\param[in] bEnalbe   �Ƿ�ʹ��xvYCCģʽ
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_SetxvYCCMode(HI_UNF_HDMI_ID_E enHdmi, HI_BOOL bEnalbe);

/** 
\brief ����HDMI AV mute ģʽ
\attention \n
\param[in] enHdmi   HDMI�豸ID
\param[in] bAvMute   �Ƿ�mute AV
\retval HI_SUCCESS      �ɹ�
\retval ��ο�MPI������
\see \n
��
*/
HI_S32 HI_UNF_HDMI_SetAVMute(HI_UNF_HDMI_ID_E enHdmi, HI_BOOL bAvMute);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
}
#endif
#endif /* __HI_UNF_HDMI_H__ */

