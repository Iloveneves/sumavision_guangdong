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
/** @{ */  /** <!-- ��ý��ͨ�á� */

/**������������ṹ�� */
typedef struct hiUNF_STREAM_BUF_S
{
    HI_U8   *pu8Data;        /**< ����ָ�� */
    HI_U32  u32Size;         /**< ���ݳ��� */
} HI_UNF_STREAM_BUF_S;

/**����ES��������ṹ�� */
typedef struct hiUNF_ES_BUF_S
{
    HI_U8 * pu8Buf;    /**< buffer���û�̬���ַ*/
    HI_U32 u32BufLen;  /**< buffer�ĳ���*/
    HI_U32 u32PtsMs;   /**< ������ʼ����Ӧ��PTSֵ����ЧΪ0xffffffff*/
}HI_UNF_ES_BUF_S;

/**������Ƶ������ö��*/
typedef enum hiUNF_SAMPLE_RATE_E
{
    HI_UNF_SAMPLE_RATE_UNKNOWN=0,       /**< δ֪����Ƶ��    */
    HI_UNF_SAMPLE_RATE_8K    = 8000,    /**< 8K����Ƶ��      */
    HI_UNF_SAMPLE_RATE_11K   = 11025,   /**< 11.025K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_12K   = 12000,   /**< 12K����Ƶ��     */
    HI_UNF_SAMPLE_RATE_16K   = 16000,   /**< 16K����Ƶ��     */
    HI_UNF_SAMPLE_RATE_22K   = 22050,   /**< 22.050K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_24K   = 24000,   /**< 24K����Ƶ��     */
    HI_UNF_SAMPLE_RATE_32K   = 32000,   /**< 32K����Ƶ��     */
    HI_UNF_SAMPLE_RATE_44K   = 44100,   /**< 44.1K����Ƶ��   */
    HI_UNF_SAMPLE_RATE_48K   = 48000,   /**< 48K����Ƶ��     */
    HI_UNF_SAMPLE_RATE_88K   = 88200,   /**< 88.2K����Ƶ��   */
    HI_UNF_SAMPLE_RATE_96K   = 96000,   /**< 96K����Ƶ��     */
	HI_UNF_SAMPLE_RATE_176K	 = 176400,	/**< 176K����Ƶ��	 */
    HI_UNF_SAMPLE_RATE_192K  = 192000,  /**< 192K����Ƶ��    */

    HI_UNF_SAMPLE_RATE_BUTT
}HI_UNF_SAMPLE_RATE_E;


/**������Ƶ����λ��ö��*/
typedef enum hiUNF_BIT_DEPTH_E
{
    HI_UNF_BIT_DEPTH_UNKNOWN =0,/**< δ֪����λ��  */
    HI_UNF_BIT_DEPTH_8  = 8,    /**< 8λ����λ��  */
    HI_UNF_BIT_DEPTH_16 = 16,   /**< 16λ����λ�� */
    HI_UNF_BIT_DEPTH_18 = 18,   /**< 18λ����λ�� */
    HI_UNF_BIT_DEPTH_20 = 20,   /**< 20λ����λ�� */
    HI_UNF_BIT_DEPTH_24 = 24,   /**< 24λ����λ�� */
    HI_UNF_BIT_DEPTH_32 = 32,   /**< 32λ����λ�� */

    HI_UNF_BIT_DEPTH_BUTT
}HI_UNF_BIT_DEPTH_E;


/**������Ƶ����ģʽö��*/
typedef enum hiUNF_TRACK_MODE_E
{
    HI_UNF_TRACK_MODE_STEREO = 0,          /**<������*/
    HI_UNF_TRACK_MODE_DOUBLE_MONO,         /**<����������Ϻ����*/
    HI_UNF_TRACK_MODE_DOUBLE_LEFT,         /**<���������������������*/
    HI_UNF_TRACK_MODE_DOUBLE_RIGHT,        /**<���������������������*/
    HI_UNF_TRACK_MODE_EXCHANGE,            /**<�����������ݽ������ */
    HI_UNF_TRACK_MODE_ONLY_RIGHT,          /**<ֻ�������������*/
    HI_UNF_TRACK_MODE_ONLY_LEFT,           /**<ֻ�������������*/
    HI_UNF_TRACK_MODE_MUTED,               /**<����*/

    HI_UNF_TRACK_MODE_BUTT
} HI_UNF_TRACK_MODE_E;

/**������Ƶ������ʽö��*/
typedef enum hiUNF_ADEC_STREAM_FMT_E
{
    HI_UNF_ADEC_STRAM_FMT_NONE = 0,     /**<����ģʽ*/
    HI_UNF_ADEC_STRAM_FMT_PACKET,       /**<packet ģʽ�� ��������������һ������packet ����, ���ܽ�����һ��packet
    										���롣Ϊ��֤packet �����ԣ�һ��packet �����Ӧһ���Ϸ�PTS
    										*/

    HI_UNF_ADEC_STRAM_FMT_BUTT
}UNF_ADEC_STREAM_FMT_E;


/**������Ƶ���������Խṹ*/
typedef struct hiUNF_ACODEC_ATTR_S{
    HI_U32        enType;                 /**< ��Ƶ��������*/
    HI_HADECODE_OPENPARAM_S   stDecodeParam;          /**< ��Ƶ�������*/
	UNF_ADEC_STREAM_FMT_E enFmt;          /**<��Ƶ������ʽ����*/

}HI_UNF_ACODEC_ATTR_S;


/**������Ƶ������Ϣ�ṹ*/
typedef struct hiUNF_ACODEC_STREAMINFO_S
{
    HI_U32   enACodecType;  /**<��Ƶ��������*/
    HI_U32               enSampleRate;  /**<��Ƶ������*/
    HI_UNF_BIT_DEPTH_E   enBitDepth;    /**<��Ƶ����λ��*/
}HI_UNF_ACODEC_STREAMINFO_S;


/**������Ƶ֡��Ϣ�ṹ*/
typedef struct hiUNF_AO_FRAMEINFO_S
{
    /** s32BitPerSample: (PCM) ����λ������. �����Ÿ�ʽ
          ����16bit:   ռ��16bit word�ڴ�
          ����16bit:   ռ��32bit word�ڴ�, ��������뷽ʽ���(��Ч�����ڸ�λ)
     */
    HI_S32  s32BitPerSample;       /**< ����λ��*/
    HI_BOOL bInterleaved;          /**< �����Ƿ�֯*/
    HI_U32  u32SampleRate;         /**< ������*/
    HI_U32  u32Channels;           /**< ͨ������*/
    HI_U32  u32PtsMs;              /**< ʱ���*/
    HI_S32 *ps32PcmBuffer;         /**< PCM���ݻ���ָ��*/
    HI_S32 *ps32BitsBuffer;        /**< �������ݻ���ָ��*/
    HI_U32  u32PcmSamplesPerFrame; /**< PCM���ݲ���������*/
    HI_U32  u32BitsBytesPerFrame;  /**< IEC61937���ݳ���*/
    HI_U32  u32FrameIndex;         /**< ֡��� */
} HI_UNF_AO_FRAMEINFO_S;


/**������Ƶ��ʽö��*/
typedef enum hiUNF_ENC_FMT_E
{
    HI_UNF_ENC_FMT_1080P_60 = 0,     /**<1080p60����*/
    HI_UNF_ENC_FMT_1080P_50,         /**<1080p50����*/
    HI_UNF_ENC_FMT_1080P_30,         /**<1080p30����*/
    HI_UNF_ENC_FMT_1080P_25,         /**<1080p25����*/
    HI_UNF_ENC_FMT_1080P_24,         /**<1080p24����*/

    HI_UNF_ENC_FMT_1080i_60,         /**<1080i60���� */
    HI_UNF_ENC_FMT_1080i_50,         /**<1080i60���� */

    HI_UNF_ENC_FMT_720P_60,          /**<720p60���� */
    HI_UNF_ENC_FMT_720P_50,          /**<720p50���� */

    HI_UNF_ENC_FMT_576P_50,          /**<576p50���� */
    HI_UNF_ENC_FMT_480P_60,          /**<480p60���� */

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

/**�����߱�ö��*/
typedef enum hiUNF_ASPECT_RATIO_E
{
    HI_UNF_ASPECT_RATIO_UNKNOWN,  /**< δ֪��߱�*/
    HI_UNF_ASPECT_RATIO_4TO3,     /**< 4��3*/
    HI_UNF_ASPECT_RATIO_16TO9,    /**< 16��9*/
    HI_UNF_ASPECT_RATIO_SQUARE,   /**< ������*/
    HI_UNF_ASPECT_RATIO_14TO9,    /**< 14��9*/
    HI_UNF_ASPECT_RATIO_221TO1,   /**< 221��100*/

    HI_UNF_ASPECT_RATIO_BUTT
}HI_UNF_ASPECT_RATIO_E;


/**�����߱�ת����ʽö��*/
typedef enum hiUNF_ASPECT_CVRS_E
{
    HI_UNF_ASPECT_CVRS_IGNORE = 0x0,   /**< ����*/
    HI_UNF_ASPECT_CVRS_LETTERBOX,      /**< �Ӻڱ�*/
    HI_UNF_ASPECT_CVRS_PANANDSCAN,     /**< �ü�*/
    HI_UNF_ASPECT_CVRS_COMBINED,       /**< �ӺڱߺͲü����*/
    HI_UNF_ASPECT_CVRS_BUTT
} HI_UNF_ASPECT_CVRS_E;


/**������Ƶ������ģʽö��*/
typedef enum hiUNF_VCODEC_MODE_E
{
    HI_UNF_VCODEC_MODE_NORMAL = 0,   /**< ������֡*/
    HI_UNF_VCODEC_MODE_IP,           /**< ֻ��IP֡*/
    HI_UNF_VCODEC_MODE_I,            /**< ֻ��I֡*/
    HI_UNF_VCODEC_MODE_BUTT
}HI_UNF_VCODEC_MODE_E;

/**�����������������(�ֱ���) */
typedef enum hiUNF_VCODEC_CAP_LEVEL_E
{
    HI_UNF_VCODEC_CAP_LEVEL_NULL = 0, /**< ����Ҫ���� */
    HI_UNF_VCODEC_CAP_LEVEL_QCIF = 0, /**< �����ͼ���С������176*144 */
    HI_UNF_VCODEC_CAP_LEVEL_CIF,      /**< �����ͼ���С������352*288 */
    HI_UNF_VCODEC_CAP_LEVEL_D1,       /**< �����ͼ���С������720*576 */  
    HI_UNF_VCODEC_CAP_LEVEL_720P,     /**< �����ͼ���С������1280*1024 */
    HI_UNF_VCODEC_CAP_LEVEL_FULLHD,   /**< �����ͼ���С������1920*1080 */ 
    HI_UNF_VCODEC_CAP_LEVEL_BUTT    
} HI_UNF_VCODEC_CAP_LEVEL_E;

/**���������֧�ֵ��������� */
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
    HI_UNF_VCODEC_TYPE_DIVX3,  /**< DIVX3����֧��*/
    
    HI_UNF_VCODEC_TYPE_JPEG,  /**< JPEG��add for Venc*/

    HI_UNF_VCODEC_TYPE_BUTT
}HI_UNF_VCODEC_TYPE_E;

typedef struct hiUNF_VCODEC_VC1_ATTR_S
{
	HI_BOOL  bAdvancedProfile;   /**<�Ƿ�Advanced Profile*/
	HI_U32   u32CodecVersion;    /**<�汾��*/
}HI_UNF_VCODEC_VC1_ATTR_S;

typedef struct hiUNF_VCODEC_VP6_ATTR_S
{
	HI_BOOL  bReversed;    /**<ͼ����Ҫ��תʱ��1��������0*/
}HI_UNF_VCODEC_VP6_ATTR_S;

typedef union hiUNF_VCODEC_EXTATTR_U
{
	HI_UNF_VCODEC_VC1_ATTR_S stVC1Attr;
	HI_UNF_VCODEC_VP6_ATTR_S stVP6Attr;
}HI_UNF_VCODEC_EXTATTR_U;

/**������Ƶ���������Խṹ*/
typedef struct hiUNF_VCODEC_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E     enType;       /**<��Ƶ��������*/
	HI_UNF_VCODEC_EXTATTR_U  unExtAttr;    /**<��Ƶ����������صĶ�������*/
    HI_UNF_VCODEC_MODE_E  	 enMode;       /**<��Ƶ������ģʽģʽ*/
    HI_U32                	 u32ErrCover;  /**<��Ƶ�����������֡�����������ޣ�0:���ִ��󼴲������100:���ܴ������ȫ�����*/
    HI_U32                	 u32Priority;  /**<��Ƶ���������ȼ�, ȡֵ��Χ: ���ڵ���1��С�ڵ���HI_UNF_VCODEC_MAX_PRIORITY, 0�Ǳ���ֵ������Ϊ0���ᱨ�����ǻ��Զ�ȡֵΪ1,��ֵԽС���ȼ�Խ�� */
    HI_BOOL                  bOrderOutput; /**<�Ƿ񰴽����������VPģʽ���Ƽ�����ΪHI_TRUE, һ��ģʽ������ΪHI_FALSE */	
}HI_UNF_VCODEC_ATTR_S;


/**������Ƶ��������ǿ���Խṹ*/
typedef struct hiUNF_VCODEC_ADV_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E  enType;           /**<��Ƶ��������*/
    HI_UNF_VCODEC_MODE_E  enMode;           /**<��Ƶ������ģʽģʽ*/
    HI_U32                u32ErrCover;      /**<��Ƶ�����������֡�����������ޣ�0:���ִ��󼴲������100:���ܴ������ȫ�����*/
    HI_U32                u32Priority;      /**<��Ƶ���������ȼ�, ȡֵ��Χ: ���ڵ���1��С�ڵ���HI_UNF_VCODEC_MAX_PRIORITY, 0�Ǳ���ֵ������Ϊ0���ᱨ�����ǻ��Զ�ȡֵΪ1,��ֵԽС���ȼ�Խ�� */
    HI_BOOL               bOrderOutput;     /**<�Ƿ񰴽����������VPģʽ���Ƽ�����ΪHI_TRUE, һ��ģʽ������ΪHI_FALSE */
}HI_UNF_VCODEC_ADV_ATTR_S;

/**����������Э���֧ö��*/
typedef enum hiUNF_VIDEO_SUB_STANDARD_E
{
    HI_UNF_VIDEO_SUB_STANDARD_UNKNOWN,       /**< δ֪Э���֧*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG2_MPEG1,   /**<MPEG2Э������Լ���MPEG1 */
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_SHV,     /**<MPEG4Э������Լ���SHV*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_XVID,    /**<MPEG4Э�����XVID��֧*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_DIVX,    /**<MPEG4Э�����DIVX��֧*/

    HI_UNF_VIDEO_SUB_STANDARD_BUTT
}HI_UNF_VIDEO_SUB_STANDARD_E;


/**������Ƶ��������ö��*/
typedef enum hiUNF_VIDEO_SAMPLE_TYPE_E
{
    HI_UNF_VIDEO_SAMPLE_TYPE_UNKNOWN,                  /**<δ֪������ʽ*/
    HI_UNF_VIDEO_SAMPLE_TYPE_PROGRESSIVE,              /**<������ʽΪ����*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INTERLACE,                /**<������ʽΪ����*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INFERED_PROGRESSIVE,      /**<������ʽΪ�Ʋ�����*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INFERED_INTERLACE,        /**<������ʽΪ�Ʋ����*/

    HI_UNF_VIDEO_SAMPLE_TYPE_BUTT
}HI_UNF_VIDEO_SAMPLE_TYPE_E;


/**������Ƶ����֡�ʽṹ*/
typedef struct hiUNF_VCODEC_FRMRATE_S
{
    HI_U32 u32fpsInteger;     /**< ������֡�ʵ���������, fps            */
    HI_U32 u32fpsDecimal;     /**< ������֡�ʵ�С�����֣�����3λ��, fps */
}HI_UNF_VCODEC_FRMRATE_S;


/**������Ƶ������Ϣ�ṹ*/
typedef struct hiUNF_VCODEC_STREAMINFO_S
{
    HI_UNF_VCODEC_TYPE_E        enVCodecType;   /**< ��������            */
    HI_UNF_VIDEO_SUB_STANDARD_E enSubStandard;  /**< ������Э���֧      */
    HI_U32                      u32SubVersion;  /**< ������Э��汾��    */
    HI_U32                      u32Profile;     /**< ������profile       */
    HI_U32                      u32Level;       /**< ������level         */
    HI_UNF_ENC_FMT_E            enDisplayNorm;  /**< ��ʾ��׼(P/N)       */
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;   /**< ������ʽ(����/����) */
    HI_UNF_ASPECT_RATIO_E       enAspectRatio;  /**< �����߱�          */

    HI_U32 u32bps;            /**< ����������, Kbps                     */
    HI_U32 u32fpsInteger;     /**< ������֡�ʵ���������, fps            */
    HI_U32 u32fpsDecimal;     /**< ������֡�ʵ�С�����֣�����3λ��, fps */
    HI_U32 u32Width;          /**< ����ͼ��� */
    HI_U32 u32Height;         /**< ����ͼ��� */
    HI_U32 u32DisplayWidth;   /**< ��ʾͼ��� */
    HI_U32 u32DisplayHeight;  /**< ��ʾͼ��� */
    HI_U32 u32DisplayCenterX; /**< ��ʾͼ�����ĺ����꣬��ԭʼͼ������Ͻ�Ϊ����ԭ�� */
    HI_U32 u32DisplayCenterY; /**< ��ʾͼ�����������꣬��ԭʼͼ������Ͻ�Ϊ����ԭ�� */
}HI_UNF_VCODEC_STREAMINFO_S;


/**������Ƶ����������Ϣ�ṹ*/
typedef struct hiUNF_VIDEO_SEQUENCE_INFO_S
{
    HI_U32                      u32Height;          /**<��Ƶ������ͼ��ĸ߶�*/
    HI_U32                      u32Width;           /**<��Ƶ������ͼ��Ŀ��*/
    HI_UNF_ASPECT_RATIO_E       enAspect;           /**<��Ƶ������ͼ��Ŀ�߱�*/
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;       /**<��Ƶ��������*/
    HI_U32                      u32FrameRate;       /**<��Ƶ����֡��*/
    HI_U32                      u32BitRate;         /**<��Ƶ���ŵı�����*/
    HI_UNF_VCODEC_TYPE_E        entype;             /**<��Ƶ�������ͣ�����MPEG2��MPEG4��H.264����*/
    HI_BOOL                     bIsLowDelay;        /**<�Ƿ���ӳ�*/
    HI_U32                      u32VBVBufferSize;   /**<��������С*/
    HI_U32                      u32StreamID;        /**<��Ƶ����ID*/
    HI_U32                      u32Profile;         /**<��Ƶ�����profile*/
    HI_U32                      u32Level;           /**<��Ƶ�����level*/
    HI_UNF_ENC_FMT_E            enVideoFormat;      /**<��Ƶ��ʽ��ֻ��VIDEO_MPEGSTANDARD_EΪVIDeo_MPEG_STANDARD_ISO_IEC_13818���ø�ʽ����Ч*/

    /* Valid only if VIDEO_MPEGSTANDARD_E is VIDeo_MPEG_STANDARD_ISO_IEC_13818 */
    HI_U32                      u32FrameRateExtensionN;    /**<������֡�ʵ��������֣���λΪfps*/
    HI_U32                      u32FrameRateExtensionD;    /**<������֡�ʵ�С�����֣�����3bit������λΪfps*/
}HI_UNF_VIDEO_SEQUENCE_INFO_S;


/**������Ƶ�㲥��profileö��*/
typedef enum hiUNF_VIDEO_BROADCAST_PROFILE_E
{
    HI_UNF_VIDEO_BROADCAST_DVB,        /**<������Ƶ�㲥DVB*/
    HI_UNF_VIDEO_BROADCAST_DIRECTV,    /**<����ֱ����Ӫ��DirecTV*/
    HI_UNF_VIDEO_BROADCAST_ATSC,       /**<�Ƚ�������ʽίԱ��ATSC��Advanced Television Systems Committee��*/
    HI_UNF_VIDEO_BROADCAST_DVD,        /**<������Ƶ����*/
    HI_UNF_VIDEO_BROADCAST_ARIB,       /**<���ߵ繤ҵ����ҵЭ����*/
    HI_UNF_VIDEO_BROADCAST_BUTT
}HI_UNF_VIDEO_BROADCAST_PROFILE_E;


/**������Ƶ��Ϣ���û����ݵ�λ��ö��*/
typedef enum hiUNF_VIDEO_USER_DATA_POSITION_E
{
    HI_UNF_VIDEO_USER_DATA_POSITION_UNKNOWN,       /**<δ֪λ��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_SEQ,     /**<MPEG2Э���£��������н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_GOP,     /**<MPEG2Э���£���GOP��Group Of Pictures���н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_FRAME,   /**<MPEG2Э���£���ͼ��֡�н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VSOS,    /**<MPEG4Э���£��ӿ��Ӷ��������н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VSO,     /**<MPEG4Э���£��ӿ��Ӷ����н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VOL,     /**<MPEG4Э���£�����Ƶ������н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_GOP,     /**<MPEG4Э���£���GOP�н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_H264_REG,      /**<��H.264Э���user_data_regestered_itu_t_t35()�﷨�н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_H264_UNREG,    /**<��H.264Э���user_data_unregestered()�﷨�н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_BUTT
}HI_UNF_VIDEO_USER_DATA_POSITION_E;


/**������Ƶ��Ϣ�е��û����ݽṹ*/
typedef struct hiUNF_VIDEO_USERDATA_S
{
    HI_UNF_VIDEO_BROADCAST_PROFILE_E   enBroadcastProfile;   /**<�û����ݵĹ㲥profile*/
    HI_UNF_VIDEO_USER_DATA_POSITION_E  enPositionInStream;   /**<�û���������Ƶ���е�λ��*/
    HI_U32                             u32Pts;               /**<�û����ݶ�Ӧ��ʱ���*/
    HI_U32                             u32SeqCnt;            /**<�û����ݵ�ǰһ������*/
    HI_U32                             u32SeqFrameCnt;       /**<�û����ݵ�ǰһ֡��*/
    HI_U8                              *pu8Buffer;           /**<�û������ڴ����ĳ�ʼ��ַ,�������*/
    HI_U32                             u32Length;            /**<�û����ݵĴ�С����1byteΪ��λ*/
    HI_BOOL                            bBufferOverflow;      /**<��־�û����ݵĳ����Ƿ񳬹���MAX_USER_DATA_LEN��������ֵ*/
}HI_UNF_VIDEO_USERDATA_S;


/**������Ƶ��ʽö��*/
typedef enum hiUNF_VIDEO_FORMAT_E
{
    HI_UNF_FORMAT_YUV_SEMIPLANAR_422 = 0X10,       /**<YUV�ռ������ʽΪ4:2:2*/
    HI_UNF_FORMAT_YUV_SEMIPLANAR_420 = 0X11,       /**<YUV�ռ������ʽΪ4:2:0*/
    HI_UNF_FORMAT_YUV_PACKAGE_UYVY,                /**<YUV�ռ������ʽΪpackage,�ڴ�����ΪUYVY*/
    HI_UNF_FORMAT_YUV_PACKAGE_YUYV,                /**<YUV�ռ������ʽΪpackage,�ڴ�����ΪYUYV*/
    HI_UNF_FORMAT_YUV_PACKAGE_YVYU,                /**<YUV�ռ������ʽΪpackage,�ڴ�����ΪYVYU*/
    HI_UNF_FORMAT_YUV_BUTT
}HI_UNF_VIDEO_FORMAT_E;


/**������Ƶ֡������ö��*/
typedef enum hiUNF_VIDEO_FRAME_TYPE_E
{
    HI_UNF_FRAME_TYPE_UNKNOWN,   /**<δ֪��֡����*/
    HI_UNF_FRAME_TYPE_I,         /**<I֡*/
    HI_UNF_FRAME_TYPE_P,         /**<P֡*/
    HI_UNF_FRAME_TYPE_B,         /**<B֡*/
    HI_UNF_FRAME_TYPE_BUTT
}HI_UNF_VIDEO_FRAME_TYPE_E;


/**������Ƶ֡��ģʽö��*/
typedef enum hiUNF_VIDEO_FIELD_MODE_E
{
    HI_UNF_VIDEO_FIELD_ALL,        /**<֡ģʽ*/
    HI_UNF_VIDEO_FIELD_TOP,        /**<����ģʽ*/
    HI_UNF_VIDEO_FIELD_BOTTOM,     /**<�׳�ģʽ*/
    HI_UNF_VIDEO_FIELD_BUTT
}HI_UNF_VIDEO_FIELD_MODE_E;


/**������Ƶ����ʱ��ṹ*/
typedef struct hiUNF_VIDEO_TIMECODE_S
{
    HI_U8   u8Hours;         /**<ʱ*/
    HI_U8   u8Minutes;       /**<��*/
    HI_U8   u8Seconds;       /**<��*/
    HI_U8   u8Frames;        /**<����֡��*/
    HI_BOOL bInterpolated;   /**<�Ƿ񾭹���ֵ*/
}HI_UNF_VIDEO_TIMECODE_S;


/**���岶��ͼ����Ϣ�ṹ*/
typedef struct hiUNF_CAPTURE_PICTURE_S
{
    HI_U32                u32TopYStartAddr;      /**< ��Ų���ͼ��Ķ���Y�ڴ��ַ */
    HI_U32                u32TopCStartAddr;      /**< ��Ų���ͼ��Ķ���C�ڴ��ַ */
    HI_U32                u32BottomYStartAddr;   /**< ��Ų���ͼ��ĵ׳�Y�ڴ��ַ */
    HI_U32                u32BottomCStartAddr;   /**< ��Ų���ͼ��ĵ׳�C�ڴ��ַ */
    HI_U32                u32Width;              /**< ����ͼ��Ŀ�� */
    HI_U32                u32Height;             /**< ����ͼ��ĸ߶� */
    HI_U32                u32Stride;             /**< ����ͼ����о� */
    HI_UNF_VIDEO_FORMAT_E    enVideoFormat;      /**< ���������ɫ��ʽ */
    HI_UNF_VIDEO_FIELD_MODE_E enFieldMode;       /**< ����ͼ���֡����Ϣ */
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;    /**< ����ͼ����������Ϣ */
} HI_UNF_CAPTURE_PICTURE_S;


/**������Ƶ֡�г���Դö�� */
typedef enum hiUNF_VIDEO_FRAME_COMBINE_E
{
    HI_UNF_VIDEO_FRAME_COMBINE_T0B0,     /**< ������������һ֡*/
    HI_UNF_VIDEO_FRAME_COMBINE_T0B1,     /**< ����������һ֡���׳����Ե�ǰ֡*/
    HI_UNF_VIDEO_FRAME_COMBINE_T1B0,     /**< �������Ե�ǰ֡���׳�������һ֡*/
    HI_UNF_VIDEO_FRAME_COMBINE_T1B1,     /**< ���������Ե�ǰ֡*/
    HI_UNF_VIDEO_FRAME_COMBINE_BUTT

}HI_UNF_VIDEO_FRAME_COMBINE_E;

/** max user data num of each frame*/
#define MAX_USER_DATA_NUM       4
/** max user data length*/
#define MAX_USER_DATA_LEN       256UL


/**������Ƶ֡��Ϣ�ṹ*/
typedef struct hiUNF_VO_FRAMEINFO_S
{
    HI_UNF_VIDEO_SEQUENCE_INFO_S     stSeqInfo;        /**<��Ƶ������Ϣ�������кŸı�ʱֻ�Ե�ǰ֡��Ч*/
    HI_U32                           u32FrameIndex;    /**<��Ƶ�����е�֡������*/
    HI_UNF_VIDEO_FORMAT_E            enVideoFormat;    /**<��Ƶ��ʽ*/
    HI_UNF_ENC_FMT_E                 enDisplayNorm;    /**<���ű�׼*/
    HI_UNF_VIDEO_FRAME_TYPE_E        enFrameType;      /**<֡����*/
    HI_UNF_VIDEO_SAMPLE_TYPE_E       enSampleType;     /**<��������*/
    HI_UNF_VIDEO_FIELD_MODE_E        enFieldMode;      /**<֡�򳡱���ģʽ*/
    HI_BOOL                          bTopFieldFirst;   /**<�������ȱ�־*/
    HI_UNF_ASPECT_RATIO_E            enAspectRatio;    /**<ͼ���߱�*/
    HI_UNF_VIDEO_FRAME_COMBINE_E     enVideoCombine;   /**<��Ƶ֡�г���Դ*/

    HI_U32                           u32Width;                 /**<ԭʼͼ���*/
    HI_U32                           u32Height;                /**<ԭʼͼ���*/
    HI_U32                           u32DisplayWidth;          /**<��ʾͼ���*/
    HI_U32                           u32DisplayHeight;         /**<��ʾͼ���*/
    HI_U32                           u32DisplayCenterX;        /**<��ʾ����x���꣬ԭʼͼ�����Ͻ�Ϊ����ԭ��*/
    HI_U32                           u32DisplayCenterY;        /**<��ʾ����y���꣬ԭʼͼ�����Ͻ�Ϊ����ԭ��*/
    HI_U32                           u32ErrorLevel;            /**<һ������ͼ���еĴ��������ȡֵΪ0��100*/
    HI_U32                           u32SeqCnt;                /**<��Ƶ���кţ���0��ʼ������һ֡ͼ����1�������ﵽ���ֵ���0���¼���*/
    HI_U32                           u32SeqFrameCnt;           /**<��Ƶ�����е�ͼ���ţ�ÿ�������е�һ֡���Ϊ0*/
    HI_U32                           u32SrcPts;                /**<��Ƶ֡��ԭʼʱ���*/
    HI_U32                           u32Pts;                   /**<��Ƶ֡��ʱ���*/
    HI_UNF_VIDEO_TIMECODE_S          stTimeCode;               /**<һ����Ƶ֡�Ĳ���ʱ��ֵ*/

    HI_U32                           u32YAddr;                 /**<��ǰ֡Y�������ݵĵ�ַ*/
    HI_U32                           u32CAddr;                 /**<��ǰ֡C�������ݵĵ�ַ*/

    HI_U32                           u32LstYAddr;              /**<��һ֡Y�������ݵĵ�ַ*/
    HI_U32                           u32LstYCddr;              /**<��һ֡C�������ݵĵ�ַ*/

    HI_U32                           u32YStride;               /**<Y�������ݵĿ��*/
    HI_U32                           u32CStride;               /**<C�������ݵĿ��*/
    HI_U32                           u32Repeat;                /**<��Ƶ֡���Ŵ���.*/
    HI_U32                           u32MgcNum;                /**<��Ƶ֡ħ����*/

    HI_U32                           u32VdecInfo[8];
}HI_UNF_VO_FRAMEINFO_S;

#pragma pack(4)
/** ��������ṹ�����־λ */
typedef struct
{
   HI_U32   bit1IPAddr:1;	/**<ip������, u32IpLen��u8IpAddr[16]�и���*/
   HI_U32   bit1IPPort:1;	/**<ip port������, u16Ipport�и���*/
   HI_U32   bit1IPTos:1;	/**<IP�������ͱ�����,u32IPTos��u32Mask�и���*/
   HI_U32   bit1Vlan:1;		/**<Vlan������,u32VlanEn,u32VlanPri,u32VlanPid��u32Mask�и��ģ�����*/
   HI_U32   bit1Protocol:1;	/**<Э�����ͱ����ǣ�Ŀǰֻ֧��IPV4,����*/
   HI_U32   bit25Resv:27;         
}HI_UNF_NET_CHANGE_S;

/** ������������ṹ */
typedef struct
{
    HI_U32 					  u32IpLen;      /**<source ip��ַ���ȣ�4(IPV4)��16(IPV6)������ֵ��Ч*/
    HI_U8 					  u8IpAddr[16];   /**<source ip��ַ��4�ֽ�(IPV4)��16�ֽ�(IPV6)�������ַ�������192.168.1.1Ϊ����4�ֽ�����Ϊ192,168,1,1*/
    HI_U16 					  u16Ipport;    	 /**<source RTP �˿ںţ�ӦΪż������ӦRTCP�˿ں�Ϊ����ֵ+1*/
    HI_U16 					  u16Reserve;    	 /**<�����ֶ�*/
    HI_U32 					  u32Protocol;       /**<Э������,0x0800--IPV4, 0x86dd--IPV6��Ŀǰֻ֧��IPV4������*/
	HI_U32					  u32PayLoadValue;   /**<�������� */   
	HI_UNF_NET_CHANGE_S       stNetChange;       /**<������������־λ  */ 

}HI_UNF_VP_NET_PARA_S;
#pragma pack()
/** @} */  /** <!-- ==== Structure Definition end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_VID_ H*/
