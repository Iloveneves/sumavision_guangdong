/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_disp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/17
  Description   :
  History       :
  1.Date        : 2009/12/17
    Author      : w58735
    Modification: Created file

*******************************************************************************/

#ifndef __HI_UNF_COMMON_H__
#define __HI_UNF_COMMON_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_common.h"
#include "hi_audio_codec.h"

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_1 */
/** @{ */  /** <!-- 【媒体通用】 */

/**定义码流缓冲结构体 */
typedef struct hiUNF_STREAM_BUF_S
{
    HI_U8   *pu8Data;        /**< 数据指针 */
    HI_U32  u32Size;         /**< 数据长度 */
} HI_UNF_STREAM_BUF_S;

/**定义ES码流缓冲结构体 */
typedef struct hiUNF_ES_BUF_S
{
    HI_U8 * pu8Buf;    /**< buffer的用户态虚地址*/
    HI_U32 u32BufLen;  /**< buffer的长度*/
    HI_U32 u32PtsMs;   /**< 码流开始处对应的PTS值，无效为0xffffffff*/
}HI_UNF_ES_BUF_S;

/**定义音频采样率枚举*/
typedef enum hiUNF_SAMPLE_RATE_E
{
    HI_UNF_SAMPLE_RATE_UNKNOWN=0,       /**< 未知采样频率    */
    HI_UNF_SAMPLE_RATE_8K    = 8000,    /**< 8K采样频率      */
    HI_UNF_SAMPLE_RATE_11K   = 11025,   /**< 11.025K采样频率 */
    HI_UNF_SAMPLE_RATE_12K   = 12000,   /**< 12K采样频率     */
    HI_UNF_SAMPLE_RATE_16K   = 16000,   /**< 16K采样频率     */
    HI_UNF_SAMPLE_RATE_22K   = 22050,   /**< 22.050K采样频率 */
    HI_UNF_SAMPLE_RATE_24K   = 24000,   /**< 24K采样频率     */
    HI_UNF_SAMPLE_RATE_32K   = 32000,   /**< 32K采样频率     */
    HI_UNF_SAMPLE_RATE_44K   = 44100,   /**< 44.1K采样频率   */
    HI_UNF_SAMPLE_RATE_48K   = 48000,   /**< 48K采样频率     */
    HI_UNF_SAMPLE_RATE_88K   = 88200,   /**< 88.2K采样频率   */
    HI_UNF_SAMPLE_RATE_96K   = 96000,   /**< 96K采样频率     */
	HI_UNF_SAMPLE_RATE_176K	 = 176400,	/**< 176K采样频率	 */
    HI_UNF_SAMPLE_RATE_192K  = 192000,  /**< 192K采样频率    */

    HI_UNF_SAMPLE_RATE_BUTT
}HI_UNF_SAMPLE_RATE_E;


/**定义音频采样位宽枚举*/
typedef enum hiUNF_BIT_DEPTH_E
{
    HI_UNF_BIT_DEPTH_UNKNOWN =0,/**< 未知采样位宽  */
    HI_UNF_BIT_DEPTH_8  = 8,    /**< 8位采样位宽  */
    HI_UNF_BIT_DEPTH_16 = 16,   /**< 16位采样位宽 */
    HI_UNF_BIT_DEPTH_18 = 18,   /**< 18位采样位宽 */
    HI_UNF_BIT_DEPTH_20 = 20,   /**< 20位采样位宽 */
    HI_UNF_BIT_DEPTH_24 = 24,   /**< 24位采样位宽 */
    HI_UNF_BIT_DEPTH_32 = 32,   /**< 32位采样位宽 */

    HI_UNF_BIT_DEPTH_BUTT
}HI_UNF_BIT_DEPTH_E;


/**定义音频声道模式枚举*/
typedef enum hiUNF_TRACK_MODE_E
{
    HI_UNF_TRACK_MODE_STEREO = 0,          /**<立体声*/
    HI_UNF_TRACK_MODE_DOUBLE_MONO,         /**<左右声道混合后输出*/
    HI_UNF_TRACK_MODE_DOUBLE_LEFT,         /**<左右声道输出左声道数据*/
    HI_UNF_TRACK_MODE_DOUBLE_RIGHT,        /**<左右声道输出右声道数据*/
    HI_UNF_TRACK_MODE_EXCHANGE,            /**<左右声道数据交换输出 */
    HI_UNF_TRACK_MODE_ONLY_RIGHT,          /**<只输出右声道数据*/
    HI_UNF_TRACK_MODE_ONLY_LEFT,           /**<只输出左声道数据*/
    HI_UNF_TRACK_MODE_MUTED,               /**<静音*/

    HI_UNF_TRACK_MODE_BUTT
} HI_UNF_TRACK_MODE_E;

/**定义音频码流格式枚举*/
typedef enum hiUNF_ADEC_STREAM_FMT_E
{
    HI_UNF_ADEC_STRAM_FMT_NONE = 0,     /**<正常模式*/
    HI_UNF_ADEC_STRAM_FMT_PACKET,       /**<packet 模式。 解码器必须消耗一个完整packet 码流, 才能进行下一个packet
    										解码。为保证packet 完整性，一个packet 必须对应一个合法PTS
    										*/

    HI_UNF_ADEC_STRAM_FMT_BUTT
}UNF_ADEC_STREAM_FMT_E;


/**定义音频解码器属性结构*/
typedef struct hiUNF_ACODEC_ATTR_S{
    HI_U32        enType;                 /**< 音频编码类型*/
    HI_HADECODE_OPENPARAM_S   stDecodeParam;          /**< 音频解码参数*/
	UNF_ADEC_STREAM_FMT_E enFmt;          /**<音频码流格式参数*/

}HI_UNF_ACODEC_ATTR_S;


/**定义音频码流信息结构*/
typedef struct hiUNF_ACODEC_STREAMINFO_S
{
    HI_U32   enACodecType;  /**<音频编码类型*/
    HI_U32               enSampleRate;  /**<音频采样率*/
    HI_UNF_BIT_DEPTH_E   enBitDepth;    /**<音频采样位宽*/
}HI_UNF_ACODEC_STREAMINFO_S;


/**定义音频帧信息结构*/
typedef struct hiUNF_AO_FRAMEINFO_S
{
    /** s32BitPerSample: (PCM) 数据位宽设置. 输出存放格式
          等于16bit:   占用16bit word内存
          大于16bit:   占用32bit word内存, 数据左对齐方式存放(有效数据在高位)
     */
    HI_S32  s32BitPerSample;       /**< 数据位宽*/
    HI_BOOL bInterleaved;          /**< 数据是否交织*/
    HI_U32  u32SampleRate;         /**< 采样率*/
    HI_U32  u32Channels;           /**< 通道数量*/
    HI_U32  u32PtsMs;              /**< 时间戳*/
    HI_S32 *ps32PcmBuffer;         /**< PCM数据缓冲指针*/
    HI_S32 *ps32BitsBuffer;        /**< 码流数据缓冲指针*/
    HI_U32  u32PcmSamplesPerFrame; /**< PCM数据采样点数量*/
    HI_U32  u32BitsBytesPerFrame;  /**< IEC61937数据长度*/
    HI_U32  u32FrameIndex;         /**< 帧序号 */
} HI_UNF_AO_FRAMEINFO_S;


/**定义视频制式枚举*/
typedef enum hiUNF_ENC_FMT_E
{
    HI_UNF_ENC_FMT_1080P_60 = 0,     /**<1080p60赫兹*/
    HI_UNF_ENC_FMT_1080P_50,         /**<1080p50赫兹*/
    HI_UNF_ENC_FMT_1080P_30,         /**<1080p30赫兹*/
    HI_UNF_ENC_FMT_1080P_25,         /**<1080p25赫兹*/
    HI_UNF_ENC_FMT_1080P_24,         /**<1080p24赫兹*/

    HI_UNF_ENC_FMT_1080i_60,         /**<1080i60赫兹 */
    HI_UNF_ENC_FMT_1080i_50,         /**<1080i60赫兹 */

    HI_UNF_ENC_FMT_720P_60,          /**<720p60赫兹 */
    HI_UNF_ENC_FMT_720P_50,          /**<720p50赫兹 */

    HI_UNF_ENC_FMT_576P_50,          /**<576p50赫兹 */
    HI_UNF_ENC_FMT_480P_60,          /**<480p60赫兹 */

    HI_UNF_ENC_FMT_PAL,              /* B D G H I PAL */
    HI_UNF_ENC_FMT_PAL_N,            /* (N)PAL        */
    HI_UNF_ENC_FMT_PAL_Nc,           /* (Nc)PAL       */

    HI_UNF_ENC_FMT_NTSC,             /* (M)NTSC       */
    HI_UNF_ENC_FMT_NTSC_J,           /* NTSC-J        */
    HI_UNF_ENC_FMT_NTSC_PAL_M,       /* (M)PAL        */

    HI_UNF_ENC_FMT_SECAM_SIN,        /**< SECAM_SIN*/
    HI_UNF_ENC_FMT_SECAM_COS,        /**< SECAM_COS*/

    HI_UNF_ENC_FMT_861D_640X480_60,
    HI_UNF_ENC_FMT_VESA_800X600_60,
    HI_UNF_ENC_FMT_VESA_1024X768_60,
    HI_UNF_ENC_FMT_VESA_1280X1024_60,
    HI_UNF_ENC_FMT_VESA_1366X768_60,
    HI_UNF_ENC_FMT_VESA_1440X900_60,
    HI_UNF_ENC_FMT_VESA_1440X900_60_RB,
    HI_UNF_ENC_FMT_VESA_1600X1200_60,
    HI_UNF_ENC_FMT_VESA_1920X1200_60,
    HI_UNF_ENC_FMT_VESA_2048X1152_60,

    HI_UNF_ENC_FMT_BUTT
}HI_UNF_ENC_FMT_E;

/**定义宽高比枚举*/
typedef enum hiUNF_ASPECT_RATIO_E
{
    HI_UNF_ASPECT_RATIO_UNKNOWN,  /**< 未知宽高比*/
    HI_UNF_ASPECT_RATIO_4TO3,     /**< 4比3*/
    HI_UNF_ASPECT_RATIO_16TO9,    /**< 16比9*/
    HI_UNF_ASPECT_RATIO_SQUARE,   /**< 正方形*/
    HI_UNF_ASPECT_RATIO_14TO9,    /**< 14比9*/
    HI_UNF_ASPECT_RATIO_221TO1,   /**< 221比100*/

    HI_UNF_ASPECT_RATIO_BUTT
}HI_UNF_ASPECT_RATIO_E;


/**定义宽高比转换方式枚举*/
typedef enum hiUNF_ASPECT_CVRS_E
{
    HI_UNF_ASPECT_CVRS_IGNORE = 0x0,   /**< 忽略*/
    HI_UNF_ASPECT_CVRS_LETTERBOX,      /**< 加黑边*/
    HI_UNF_ASPECT_CVRS_PANANDSCAN,     /**< 裁减*/
    HI_UNF_ASPECT_CVRS_COMBINED,       /**< 加黑边和裁减混合*/
    HI_UNF_ASPECT_CVRS_BUTT
} HI_UNF_ASPECT_CVRS_E;


/**定义视频解码器模式枚举*/
typedef enum hiUNF_VCODEC_MODE_E
{
    HI_UNF_VCODEC_MODE_NORMAL = 0,   /**< 解所有帧*/
    HI_UNF_VCODEC_MODE_IP,           /**< 只解IP帧*/
    HI_UNF_VCODEC_MODE_I,            /**< 只解I帧*/
    HI_UNF_VCODEC_MODE_BUTT
}HI_UNF_VCODEC_MODE_E;

/**定义解码器解码能力(分辨率) */
typedef enum hiUNF_VCODEC_CAP_LEVEL_E
{
    HI_UNF_VCODEC_CAP_LEVEL_NULL = 0, /**< 不需要解码 */
    HI_UNF_VCODEC_CAP_LEVEL_QCIF = 0, /**< 解码的图像大小不超过176*144 */
    HI_UNF_VCODEC_CAP_LEVEL_CIF,      /**< 解码的图像大小不超过352*288 */
    HI_UNF_VCODEC_CAP_LEVEL_D1,       /**< 解码的图像大小不超过720*576 */  
    HI_UNF_VCODEC_CAP_LEVEL_720P,     /**< 解码的图像大小不超过1280*1024 */
    HI_UNF_VCODEC_CAP_LEVEL_FULLHD,   /**< 解码的图像大小不超过1920*1080 */ 
    HI_UNF_VCODEC_CAP_LEVEL_BUTT    
} HI_UNF_VCODEC_CAP_LEVEL_E;

/**定义解码器支持的码流类型 */
typedef enum hiUNF_VCODEC_TYPE_E
{
    HI_UNF_VCODEC_TYPE_MPEG2,  /**< MPEG2*/
    HI_UNF_VCODEC_TYPE_MPEG4,  /**< MPEG4 DIVX4 DIVX5*/
    HI_UNF_VCODEC_TYPE_AVS,    /**< AVS*/
    HI_UNF_VCODEC_TYPE_H263,   /**< H263*/
    HI_UNF_VCODEC_TYPE_H264,   /**< H264*/
    HI_UNF_VCODEC_TYPE_REAL8,  /**< REAL*/
    HI_UNF_VCODEC_TYPE_REAL9,  /**< REAL*/
    HI_UNF_VCODEC_TYPE_VC1,    /**< VC-1*/
    HI_UNF_VCODEC_TYPE_VP6,    /**< VP6*/
    HI_UNF_VCODEC_TYPE_VP6F,   /**< VP6F*/
    HI_UNF_VCODEC_TYPE_VP6A,   /**< VP6A*/
    HI_UNF_VCODEC_TYPE_SORENSON, /**< SORENSON SPARK*/
    HI_UNF_VCODEC_TYPE_DIVX3,  /**< DIVX3，不支持*/
    
    HI_UNF_VCODEC_TYPE_JPEG,  /**< JPEG，add for Venc*/

    HI_UNF_VCODEC_TYPE_BUTT
}HI_UNF_VCODEC_TYPE_E;

typedef struct hiUNF_VCODEC_VC1_ATTR_S
{
	HI_BOOL  bAdvancedProfile;   /**<是否Advanced Profile*/
	HI_U32   u32CodecVersion;    /**<版本号*/
}HI_UNF_VCODEC_VC1_ATTR_S;

typedef struct hiUNF_VCODEC_VP6_ATTR_S
{
	HI_BOOL  bReversed;    /**<图像需要倒转时置1，否则置0*/
}HI_UNF_VCODEC_VP6_ATTR_S;

typedef union hiUNF_VCODEC_EXTATTR_U
{
	HI_UNF_VCODEC_VC1_ATTR_S stVC1Attr;
	HI_UNF_VCODEC_VP6_ATTR_S stVP6Attr;
}HI_UNF_VCODEC_EXTATTR_U;

/**定义视频解码器属性结构*/
typedef struct hiUNF_VCODEC_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E     enType;       /**<视频编码类型*/
	HI_UNF_VCODEC_EXTATTR_U  unExtAttr;    /**<视频编码类型相关的额外属性*/
    HI_UNF_VCODEC_MODE_E  	 enMode;       /**<视频解码器模式模式*/
    HI_U32                	 u32ErrCover;  /**<视频解码器的输出帧错误隐藏门限，0:出现错误即不输出；100:不管错误比例全部输出*/
    HI_U32                	 u32Priority;  /**<视频解码器优先级, 取值范围: 大于等于1，小于等于HI_UNF_VCODEC_MAX_PRIORITY, 0是保留值，配置为0不会报错，但是会自动取值为1,数值越小优先级越低 */
    HI_BOOL                  bOrderOutput; /**<是否按解码序输出，VP模式下推荐配置为HI_TRUE, 一般模式下配置为HI_FALSE */	
}HI_UNF_VCODEC_ATTR_S;


/**定义视频解码器增强属性结构*/
typedef struct hiUNF_VCODEC_ADV_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E  enType;           /**<视频编码类型*/
    HI_UNF_VCODEC_MODE_E  enMode;           /**<视频解码器模式模式*/
    HI_U32                u32ErrCover;      /**<视频解码器的输出帧错误隐藏门限，0:出现错误即不输出；100:不管错误比例全部输出*/
    HI_U32                u32Priority;      /**<视频解码器优先级, 取值范围: 大于等于1，小于等于HI_UNF_VCODEC_MAX_PRIORITY, 0是保留值，配置为0不会报错，但是会自动取值为1,数值越小优先级越低 */
    HI_BOOL               bOrderOutput;     /**<是否按解码序输出，VP模式下推荐配置为HI_TRUE, 一般模式下配置为HI_FALSE */
}HI_UNF_VCODEC_ADV_ATTR_S;

/**定义码流的协议分支枚举*/
typedef enum hiUNF_VIDEO_SUB_STANDARD_E
{
    HI_UNF_VIDEO_SUB_STANDARD_UNKNOWN,       /**< 未知协议分支*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG2_MPEG1,   /**<MPEG2协议族可以兼容MPEG1 */
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_SHV,     /**<MPEG4协议族可以兼容SHV*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_XVID,    /**<MPEG4协议包含XVID分支*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_DIVX,    /**<MPEG4协议包含DIVX分支*/

    HI_UNF_VIDEO_SUB_STANDARD_BUTT
}HI_UNF_VIDEO_SUB_STANDARD_E;


/**定义视频采样类型枚举*/
typedef enum hiUNF_VIDEO_SAMPLE_TYPE_E
{
    HI_UNF_VIDEO_SAMPLE_TYPE_UNKNOWN,                  /**<未知采样方式*/
    HI_UNF_VIDEO_SAMPLE_TYPE_PROGRESSIVE,              /**<采样方式为逐行*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INTERLACE,                /**<采样方式为隔行*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INFERED_PROGRESSIVE,      /**<采样方式为推测逐行*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INFERED_INTERLACE,        /**<采样方式为推测隔行*/

    HI_UNF_VIDEO_SAMPLE_TYPE_BUTT
}HI_UNF_VIDEO_SAMPLE_TYPE_E;


/**定义视频码流帧率结构*/
typedef struct hiUNF_VCODEC_FRMRATE_S
{
    HI_U32 u32fpsInteger;     /**< 码流的帧率的整数部分, fps            */
    HI_U32 u32fpsDecimal;     /**< 码流的帧率的小数部分（保留3位）, fps */
}HI_UNF_VCODEC_FRMRATE_S;


/**定义视频码流信息结构*/
typedef struct hiUNF_VCODEC_STREAMINFO_S
{
    HI_UNF_VCODEC_TYPE_E        enVCodecType;   /**< 码流类型            */
    HI_UNF_VIDEO_SUB_STANDARD_E enSubStandard;  /**< 码流的协议分支      */
    HI_U32                      u32SubVersion;  /**< 码流子协议版本号    */
    HI_U32                      u32Profile;     /**< 码流的profile       */
    HI_U32                      u32Level;       /**< 码流的level         */
    HI_UNF_ENC_FMT_E            enDisplayNorm;  /**< 显示标准(P/N)       */
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;   /**< 采样方式(逐行/隔行) */
    HI_UNF_ASPECT_RATIO_E       enAspectRatio;  /**< 输出宽高比          */

    HI_U32 u32bps;            /**< 码流的码率, Kbps                     */
    HI_U32 u32fpsInteger;     /**< 码流的帧率的整数部分, fps            */
    HI_U32 u32fpsDecimal;     /**< 码流的帧率的小数部分（保留3位）, fps */
    HI_U32 u32Width;          /**< 解码图像宽 */
    HI_U32 u32Height;         /**< 解码图像高 */
    HI_U32 u32DisplayWidth;   /**< 显示图像宽 */
    HI_U32 u32DisplayHeight;  /**< 显示图像高 */
    HI_U32 u32DisplayCenterX; /**< 显示图像中心横坐标，以原始图像的左上角为坐标原点 */
    HI_U32 u32DisplayCenterY; /**< 显示图像中心纵坐标，以原始图像的左上角为坐标原点 */
}HI_UNF_VCODEC_STREAMINFO_S;


/**定义视频序列数据信息结构*/
typedef struct hiUNF_VIDEO_SEQUENCE_INFO_S
{
    HI_U32                      u32Height;          /**<视频序列中图像的高度*/
    HI_U32                      u32Width;           /**<视频序列中图像的宽度*/
    HI_UNF_ASPECT_RATIO_E       enAspect;           /**<视频序列中图像的宽高比*/
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;       /**<视频采样类型*/
    HI_U32                      u32FrameRate;       /**<视频播放帧率*/
    HI_U32                      u32BitRate;         /**<视频播放的比特率*/
    HI_UNF_VCODEC_TYPE_E        entype;             /**<视频解码类型，包括MPEG2、MPEG4、H.264三种*/
    HI_BOOL                     bIsLowDelay;        /**<是否低延迟*/
    HI_U32                      u32VBVBufferSize;   /**<缓冲区大小*/
    HI_U32                      u32StreamID;        /**<视频流的ID*/
    HI_U32                      u32Profile;         /**<视频解码的profile*/
    HI_U32                      u32Level;           /**<视频解码的level*/
    HI_UNF_ENC_FMT_E            enVideoFormat;      /**<视频格式，只有VIDEO_MPEGSTANDARD_E为VIDeo_MPEG_STANDARD_ISO_IEC_13818，该格式才有效*/

    /* Valid only if VIDEO_MPEGSTANDARD_E is VIDeo_MPEG_STANDARD_ISO_IEC_13818 */
    HI_U32                      u32FrameRateExtensionN;    /**<码流的帧率的整数部分，单位为fps*/
    HI_U32                      u32FrameRateExtensionD;    /**<码流的帧率的小数部分（保留3bit），单位为fps*/
}HI_UNF_VIDEO_SEQUENCE_INFO_S;


/**定义视频广播的profile枚举*/
typedef enum hiUNF_VIDEO_BROADCAST_PROFILE_E
{
    HI_UNF_VIDEO_BROADCAST_DVB,        /**<数字视频广播DVB*/
    HI_UNF_VIDEO_BROADCAST_DIRECTV,    /**<美国直播运营商DirecTV*/
    HI_UNF_VIDEO_BROADCAST_ATSC,       /**<先进电视制式委员会ATSC（Advanced Television Systems Committee）*/
    HI_UNF_VIDEO_BROADCAST_DVD,        /**<数字视频光盘*/
    HI_UNF_VIDEO_BROADCAST_ARIB,       /**<无线电工业及商业协会规格*/
    HI_UNF_VIDEO_BROADCAST_BUTT
}HI_UNF_VIDEO_BROADCAST_PROFILE_E;


/**定义视频信息中用户数据的位置枚举*/
typedef enum hiUNF_VIDEO_USER_DATA_POSITION_E
{
    HI_UNF_VIDEO_USER_DATA_POSITION_UNKNOWN,       /**<未知位置*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_SEQ,     /**<MPEG2协议下，从序列中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_GOP,     /**<MPEG2协议下，从GOP（Group Of Pictures）中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_FRAME,   /**<MPEG2协议下，从图像帧中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VSOS,    /**<MPEG4协议下，从可视对像序列中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VSO,     /**<MPEG4协议下，从可视对像中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VOL,     /**<MPEG4协议下，从视频对像层中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_GOP,     /**<MPEG4协议下，从GOP中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_H264_REG,      /**<从H.264协议的user_data_regestered_itu_t_t35()语法中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_H264_UNREG,    /**<从H.264协议的user_data_unregestered()语法中解出*/
    HI_UNF_VIDEO_USER_DATA_POSITION_BUTT
}HI_UNF_VIDEO_USER_DATA_POSITION_E;


/**定义视频信息中的用户数据结构*/
typedef struct hiUNF_VIDEO_USERDATA_S
{
    HI_UNF_VIDEO_BROADCAST_PROFILE_E   enBroadcastProfile;   /**<用户数据的广播profile*/
    HI_UNF_VIDEO_USER_DATA_POSITION_E  enPositionInStream;   /**<用户数据在视频流中的位置*/
    HI_U32                             u32Pts;               /**<用户数据对应的时间戳*/
    HI_U32                             u32SeqCnt;            /**<用户数据的前一序列数*/
    HI_U32                             u32SeqFrameCnt;       /**<用户数据的前一帧数*/
    HI_U8                              *pu8Buffer;           /**<用户数据内存区的初始地址,输出参数*/
    HI_U32                             u32Length;            /**<用户数据的大小，以1byte为单位*/
    HI_BOOL                            bBufferOverflow;      /**<标志用户数据的长度是否超过了MAX_USER_DATA_LEN定义的最大值*/
}HI_UNF_VIDEO_USERDATA_S;


/**定义视频格式枚举*/
typedef enum hiUNF_VIDEO_FORMAT_E
{
    HI_UNF_FORMAT_YUV_SEMIPLANAR_422 = 0X10,       /**<YUV空间采样格式为4:2:2*/
    HI_UNF_FORMAT_YUV_SEMIPLANAR_420 = 0X11,       /**<YUV空间采样格式为4:2:0*/
    HI_UNF_FORMAT_YUV_PACKAGE_UYVY,                /**<YUV空间采样格式为package,内存排列为UYVY*/
    HI_UNF_FORMAT_YUV_PACKAGE_YUYV,                /**<YUV空间采样格式为package,内存排列为YUYV*/
    HI_UNF_FORMAT_YUV_PACKAGE_YVYU,                /**<YUV空间采样格式为package,内存排列为YVYU*/
    HI_UNF_FORMAT_YUV_BUTT
}HI_UNF_VIDEO_FORMAT_E;


/**定义视频帧的类型枚举*/
typedef enum hiUNF_VIDEO_FRAME_TYPE_E
{
    HI_UNF_FRAME_TYPE_UNKNOWN,   /**<未知的帧类型*/
    HI_UNF_FRAME_TYPE_I,         /**<I帧*/
    HI_UNF_FRAME_TYPE_P,         /**<P帧*/
    HI_UNF_FRAME_TYPE_B,         /**<B帧*/
    HI_UNF_FRAME_TYPE_BUTT
}HI_UNF_VIDEO_FRAME_TYPE_E;


/**定义视频帧场模式枚举*/
typedef enum hiUNF_VIDEO_FIELD_MODE_E
{
    HI_UNF_VIDEO_FIELD_ALL,        /**<帧模式*/
    HI_UNF_VIDEO_FIELD_TOP,        /**<顶场模式*/
    HI_UNF_VIDEO_FIELD_BOTTOM,     /**<底场模式*/
    HI_UNF_VIDEO_FIELD_BUTT
}HI_UNF_VIDEO_FIELD_MODE_E;


/**定义视频播放时间结构*/
typedef struct hiUNF_VIDEO_TIMECODE_S
{
    HI_U8   u8Hours;         /**<时*/
    HI_U8   u8Minutes;       /**<分*/
    HI_U8   u8Seconds;       /**<秒*/
    HI_U8   u8Frames;        /**<播放帧数*/
    HI_BOOL bInterpolated;   /**<是否经过插值*/
}HI_UNF_VIDEO_TIMECODE_S;


/**定义捕获图象信息结构*/
typedef struct hiUNF_CAPTURE_PICTURE_S
{
    HI_U32                u32TopYStartAddr;      /**< 存放捕获图象的顶场Y内存地址 */
    HI_U32                u32TopCStartAddr;      /**< 存放捕获图象的顶场C内存地址 */
    HI_U32                u32BottomYStartAddr;   /**< 存放捕获图象的底场Y内存地址 */
    HI_U32                u32BottomCStartAddr;   /**< 存放捕获图象的底场C内存地址 */
    HI_U32                u32Width;              /**< 捕获图象的宽度 */
    HI_U32                u32Height;             /**< 捕获图象的高度 */
    HI_U32                u32Stride;             /**< 捕获图象的行距 */
    HI_UNF_VIDEO_FORMAT_E    enVideoFormat;      /**< 捕获截屏颜色格式 */
    HI_UNF_VIDEO_FIELD_MODE_E enFieldMode;       /**< 捕获图象的帧场信息 */
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;    /**< 捕获图象的逐隔行信息 */
} HI_UNF_CAPTURE_PICTURE_S;


/**定义视频帧中场来源枚举 */
typedef enum hiUNF_VIDEO_FRAME_COMBINE_E
{
    HI_UNF_VIDEO_FRAME_COMBINE_T0B0,     /**< 两场都来自上一帧*/
    HI_UNF_VIDEO_FRAME_COMBINE_T0B1,     /**< 顶场来自上一帧，底场来自当前帧*/
    HI_UNF_VIDEO_FRAME_COMBINE_T1B0,     /**< 顶场来自当前帧，底场来自上一帧*/
    HI_UNF_VIDEO_FRAME_COMBINE_T1B1,     /**< 两场都来自当前帧*/
    HI_UNF_VIDEO_FRAME_COMBINE_BUTT

}HI_UNF_VIDEO_FRAME_COMBINE_E;

/** max user data num of each frame*/
#define MAX_USER_DATA_NUM       4
/** max user data length*/
#define MAX_USER_DATA_LEN       256UL


/**定义视频帧信息结构*/
typedef struct hiUNF_VO_FRAMEINFO_S
{
    HI_UNF_VIDEO_SEQUENCE_INFO_S     stSeqInfo;        /**<视频序列信息，当序列号改变时只对当前帧有效*/
    HI_U32                           u32FrameIndex;    /**<视频序列中的帧索引号*/
    HI_UNF_VIDEO_FORMAT_E            enVideoFormat;    /**<视频格式*/
    HI_UNF_ENC_FMT_E                 enDisplayNorm;    /**<播放标准*/
    HI_UNF_VIDEO_FRAME_TYPE_E        enFrameType;      /**<帧类型*/
    HI_UNF_VIDEO_SAMPLE_TYPE_E       enSampleType;     /**<采样类型*/
    HI_UNF_VIDEO_FIELD_MODE_E        enFieldMode;      /**<帧或场编码模式*/
    HI_BOOL                          bTopFieldFirst;   /**<顶场优先标志*/
    HI_UNF_ASPECT_RATIO_E            enAspectRatio;    /**<图像宽高比*/
    HI_UNF_VIDEO_FRAME_COMBINE_E     enVideoCombine;   /**<视频帧中场来源*/

    HI_U32                           u32Width;                 /**<原始图像宽*/
    HI_U32                           u32Height;                /**<原始图像高*/
    HI_U32                           u32DisplayWidth;          /**<显示图像宽*/
    HI_U32                           u32DisplayHeight;         /**<显示图像高*/
    HI_U32                           u32DisplayCenterX;        /**<显示中心x坐标，原始图像左上角为坐标原点*/
    HI_U32                           u32DisplayCenterY;        /**<显示中心y坐标，原始图像左上角为坐标原点*/
    HI_U32                           u32ErrorLevel;            /**<一幅解码图像中的错误比例，取值为0～100*/
    HI_U32                           u32SeqCnt;                /**<视频序列号，从0开始计数第一帧图像，以1递增，达到最大值后归0重新计数*/
    HI_U32                           u32SeqFrameCnt;           /**<视频序列中的图像编号，每个序列中第一帧编号为0*/
    HI_U32                           u32SrcPts;                /**<视频帧的原始时间戳*/
    HI_U32                           u32Pts;                   /**<视频帧的时间戳*/
    HI_UNF_VIDEO_TIMECODE_S          stTimeCode;               /**<一个视频帧的播放时间值*/

    HI_U32                           u32YAddr;                 /**<当前帧Y分量数据的地址*/
    HI_U32                           u32CAddr;                 /**<当前帧C分量数据的地址*/

    HI_U32                           u32LstYAddr;              /**<上一帧Y分量数据的地址*/
    HI_U32                           u32LstYCddr;              /**<上一帧C分量数据的地址*/

    HI_U32                           u32YStride;               /**<Y分量数据的跨幅*/
    HI_U32                           u32CStride;               /**<C分量数据的跨幅*/
    HI_U32                           u32Repeat;                /**<视频帧播放次数.*/
    HI_U32                           u32MgcNum;                /**<视频帧魔术字*/

    HI_U32                           u32VdecInfo[8];
}HI_UNF_VO_FRAMEINFO_S;

#pragma pack(4)
/** 网络参数结构变更标志位 */
typedef struct
{
   HI_U32   bit1IPAddr:1;	/**<ip变更标记, u32IpLen和u8IpAddr[16]有更改*/
   HI_U32   bit1IPPort:1;	/**<ip port变更标记, u16Ipport有更改*/
   HI_U32   bit1IPTos:1;	/**<IP服务类型变更标记,u32IPTos和u32Mask有更改*/
   HI_U32   bit1Vlan:1;		/**<Vlan变更标记,u32VlanEn,u32VlanPri,u32VlanPid和u32Mask有更改，保留*/
   HI_U32   bit1Protocol:1;	/**<协议类型变更标记，目前只支持IPV4,保留*/
   HI_U32   bit25Resv:27;         
}HI_UNF_NET_CHANGE_S;

/** 配置网络参数结构 */
typedef struct
{
    HI_U32 					  u32IpLen;      /**<source ip地址长度，4(IPV4)或16(IPV6)，其它值无效*/
    HI_U8 					  u8IpAddr[16];   /**<source ip地址，4字节(IPV4)或16字节(IPV6)，不是字符串，以192.168.1.1为例，4字节依次为192,168,1,1*/
    HI_U16 					  u16Ipport;    	 /**<source RTP 端口号，应为偶数；对应RTCP端口号为该数值+1*/
    HI_U16 					  u16Reserve;    	 /**<保留字段*/
    HI_U32 					  u32Protocol;       /**<协议类型,0x0800--IPV4, 0x86dd--IPV6，目前只支持IPV4，保留*/
	HI_U32					  u32PayLoadValue;   /**<负载类型 */   
	HI_UNF_NET_CHANGE_S       stNetChange;       /**<网络参数变更标志位  */ 

}HI_UNF_VP_NET_PARA_S;
#pragma pack()
/** @} */  /** <!-- ==== Structure Definition end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_VID_ H*/
