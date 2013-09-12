/**
 \file
 \brief �ļ���������Э��ṹ��
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author 
 \date 2010-02-10
 */

#ifndef __HI_SVR_FORMAT_H__
#define __HI_SVR_FORMAT_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ******************************/
/** \addtogroup      H_3_1 */
/** @{ */  /** <!-- ���ļ������������롿 */

/** �����ļ�����λ�� */
#define HI_FORMAT_ERRO_ENDOFFILE            (HI_FAILURE - 1)

/** @} */  /*! <!-- Macro Definition end */  


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_1 */
/** @{ */  /** <!-- ���ļ����������ݽṹ�� */

/** ����Ŀ��������tsý���ļ�����Ŀ�����������5�����򲥷������ֻ�ܴ洢����ĳ5����Ŀ��Ϣ�����������е�ĳһ�� */
#define HI_FORMAT_MAX_PROGRAM_NUM           (5)
/** ·���ַ����� */
#define HI_FORMAT_MAX_URL_LEN               (512)
/** �ļ����Ƴ��� */
#define HI_FORMAT_MAX_FILE_NAME_LEN         (256)
/** �ļ����⡢���ߵ�����ַ��� */
#define HI_FORMAT_TITLE_MAX_LEN             (512)
/** �����ַ��� */
#define HI_FORMAT_LANG_LEN                  (4)
/** ��Ļ���ⳤ�� */
#define HI_FORMAT_SUB_TITLE_LEN             (8)
/** ����ֽ��� */
#define HI_FORMAT_TIME_LEN                  (8)
/** ������ */
#define HI_FORMAT_MAX_STREAM_NUM            (5)
/** ֧�ֵ��������������� */
#define HI_FORMAT_MAX_LANG_NUM              (5)
/** û��pts */
#define HI_FORMAT_NO_PTS                    (-1)
/** �Ƿ�streamid */
#define HI_FORMAT_INVALID_STREAM_ID         (-1)
/** ��ɫ���ֽ�����rgb+a */
#define HI_FORMAT_PALETTE_LEN               (4 * 256)

/*************************** Structure Definition ****************************/

/** �汾�Ŷ��� */
typedef struct hiFORMAT_LIB_VERSION_S
{
    HI_U8 u8VersionMajor;    /**< Major version accessor element */
    HI_U8 u8VersionMinor;    /**< Minor version accessor element */
    HI_U8 u8Revision;        /**< Revision version accessor element */
    HI_U8 u8Step;            /**< Step version accessor element */
} HI_FORMAT_LIB_VERSION_S;

/** �ļ��򿪷�ʽ */
typedef enum hiFORMAT_URL_OPENFLAG_E
{
    HI_FORMAT_URL_OPEN_RDONLY = 0x0,   /**< ֻ����ʽ */
    HI_FORMAT_URL_OPEN_RDWR,           /**< ��/д��ʽ */
    HI_FORMAT_URL_OPEN_BUTT
} HI_FORMAT_URL_OPENFLAG_E;

/** �ļ�SEEK��� */
typedef enum hiFORMAT_SEEK_FLAG_E
{   
    HI_FORMAT_AVSEEK_FLAG_NORMAL = 0x0,     /**< �ӵ�ǰ֡���ļ�βseek���ҵ��뵱ǰ֡����Ĺؼ�֡ */
    HI_FORMAT_AVSEEK_FLAG_BACKWARD,         /**< �ӵ�ǰ֡���ļ�ͷseek���ҵ��뵱ǰ֡����Ĺؼ�֡ */
    HI_FORMAT_AVSEEK_FLAG_BYTE,             /**< ���ֽ�seek */
    HI_FORMAT_AVSEEK_FLAG_ANY,              /**< ���������ļ�ͷ�����ļ�β���ҵ��뵱ǰ֡����Ĺؼ�֡ */
    HI_FORMAT_AVSEEK_FLAG_BUTT
} HI_FORMAT_SEEK_FLAG_E;

/** �����ͣ��ļ��������������������������� */
typedef enum hiFORMAT_DATA_TYPE_E
{
    HI_FORMAT_DATA_NULL = 0x0,
    HI_FORMAT_DATA_AUD,          /**< ��Ƶ�� */
    HI_FORMAT_DATA_VID,          /**< ��Ƶ�� */
    HI_FORMAT_DATA_SUB,          /**< ��Ļ�� */
    HI_FORMAT_DATA_RAW,          /**< �ֽ��� */
    HI_FORMAT_DATA_BUTT
} HI_FORMAT_DATA_TYPE_E;

/** �ļ������ͣ����ŵ��ļ����� */
typedef enum hiFORMAT_STREAM_TYPE_E
{
    HI_FORMAT_STREAM_ES = 0x0,    /**< es���ļ� */
    HI_FORMAT_STREAM_TS,          /**< ts���ļ� */
    HI_FORMAT_STREAM_NORMAL,      /**< ��ͨ�ļ� */
    HI_FPRMAT_STREAM_BUTT
} HI_FORMAT_STREAM_TYPE_E;

/** ��Ļ�������� */
typedef enum hiFORMAT_SUBTITLE_DATA_TYPE_E
{
    HI_FORMAT_SUBTITLE_DATA_TEXT = 0x0,    /**< �ַ��� */
    HI_FORMAT_SUBTITLE_DATA_BMP,           /**< bmpͼƬ */
    HI_FORMAT_SUBTITLE_DATA_ASS,           /**< ass��Ļ */
    HI_FORMAT_SUBTITLE_DATA_BUTT
} HI_FORMAT_SUBTITLE_DATA_TYPE_E;

/** ��Ƶ����Ϣ */
typedef struct hiFORMAT_AUD_INFO_S
{
    HI_S32 s32StreamIndex;                   /**< ������������ts������ֵΪ��pid���Ƿ�ֵΪ::HI_FORMAT_INVALID_STREAM_ID */
    HI_U32 u32Format;                        /**< ��Ƶ�����ʽ��ֵ����ο�HA_AUDIO_ID_AAC�ȶ��� */
    HI_U32 u32Version;                       /**< ��Ƶ����汾������wma���룬0x160(WMAV1), 0x161 (WMAV2) */
    HI_U32 u32SampleRate;                    /**< 8000,11025,441000,... */
    HI_U16 u16BitPerSample;                  /**< ��Ƶÿ����������ռ�ı�������8bit,16bit */
    HI_U16 u16Channels;                      /**< ������, 1 or 2 */
    HI_U32 u32BlockAlign;                    /**< packet�������ֽ��� */
    HI_U32 u32Bps;                           /**< ��Ƶ���ʣ�bits/s */
    HI_BOOL bBigEndian;                      /**< ��С�ˣ���pcm��ʽ��Ч */
    HI_CHAR aszAudLang[HI_FORMAT_LANG_LEN];  /**< ��Ƶ������ */
    HI_U32 u32ExtradataSize;                 /**< ��չ���ݳ��� */
    HI_U8  *pu8Extradata;                    /**< ��չ���� */
} HI_FORMAT_AUD_INFO_S;

/** ��Ƶ����Ϣ */
typedef struct hiFORMAT_VID_INFO_S
{
    HI_S32 s32StreamIndex;        /**< ������������ts������ֵΪ��pid���Ƿ�ֵΪ::HI_FORMAT_INVALID_STREAM_ID */
    HI_U32 u32Format;             /**< ��Ƶ�����ʽ��ֵ����ο�::HI_UNF_VCODEC_TYPE_E */
    HI_U16 u16Width;              /**< ��ȣ���λ���� */
    HI_U16 u16Height;             /**< �߶ȣ���λ���� */
    HI_U16 u16FpsInteger;         /**< ֡�ʣ��������� */
    HI_U16 u16FpsDecimal;         /**< ֡�ʣ�С������ */
    HI_U32 u32Bps;                /**< ��Ƶ���ʣ�bits/s */
    HI_U32 u32ExtradataSize;      /**< ��չ���ݳ��� */
    HI_U8  *pu8Extradata;         /**< ��չ���� */
} HI_FORMAT_VID_INFO_S;

/** ��Ļ��Ϣ */
typedef struct hiFORMAT_SUBTITLE_INFO_S
{
    HI_S32  s32StreamIndex;                            /**< ������������ts������ֵΪ��pid���Ƿ�ֵΪ::HI_FORMAT_INVALID_STREAM_ID */
    HI_BOOL bExtSubTitle;                              /**< �Ƿ�Ϊ�����Ļ */
    HI_FORMAT_SUBTITLE_DATA_TYPE_E eSubtitileType;     /**< ��Ļ��ʽ����bmp,string */
    HI_CHAR aszSubTitleName[HI_FORMAT_SUB_TITLE_LEN];  /**< ��Ļ���� */
    HI_U16  u16OriginalFrameWidth;                     /**< ԭʼͼ���� */
    HI_U16  u16OriginalFrameHeight;                    /**< ԭʼͼ��߶� */
    HI_U16  u16HorScale;                               /**< ˮƽ���űȣ�0-100 */
    HI_U16  u16VerScale;                               /**< ��ֱ���űȣ�0-100 */
    HI_U32  u32ExtradataSize;                          /**< ��չ���ݳ��� */
    HI_U8   *pu8Extradata;                             /**< ��չ���� */
} HI_FORMAT_SUBTITLE_INFO_S;

/** ��Ŀ��Ϣ������ļ��ȴ�������ĻҲ��������Ļ����������Ļ��Ϣ׷����������Ļ��
    ע: ���ý���ļ�������Ƶ�����轫videstreamindex����ΪHI_FORMAT_INVALID_STREAM_ID */
typedef struct hiFORMAT_PROGRAM_INFO_S
{
    HI_FORMAT_VID_INFO_S stVidStream;                                  /**< ��Ƶ����Ϣ */
    HI_U32 u32AudStreamNum;                                            /**< ��Ƶ������ */
    HI_FORMAT_AUD_INFO_S astAudStream[HI_FORMAT_MAX_STREAM_NUM];       /**< ��Ƶ����Ϣ */
    HI_U32 u32SubTitleNum;                                             /**< ��Ļ���� */
    HI_FORMAT_SUBTITLE_INFO_S astSubTitle[HI_FORMAT_MAX_LANG_NUM];     /**< ��Ļ��Ϣ */
} HI_FORMAT_PROGRAM_INFO_S;

/** ý���ļ���Ϣ */
typedef struct hiFORMAT_FILE_INFO_S
{
    HI_FORMAT_STREAM_TYPE_E eStreamType;                /**< �ļ������� */
    HI_U32  u32FileSize;                                /**< �ļ���С����λ�ֽ� */
    HI_S64  s64StartTime;                               /**< �ļ�������ʼʱ�䣬��λms */
    HI_S64  s64Duration;                                /**< �ļ���ʱ������λms */
    HI_U32  u32Bps;                                     /**< �ļ����ʣ�bits/s */
    HI_CHAR aszFileName[HI_FORMAT_MAX_FILE_NAME_LEN];   /**< �ļ����� */
    HI_CHAR aszAlbum[HI_FORMAT_TITLE_MAX_LEN];          /**< ר�� */
    HI_CHAR aszTitle[HI_FORMAT_TITLE_MAX_LEN];          /**< ���� */
    HI_CHAR aszArtist[HI_FORMAT_TITLE_MAX_LEN];         /**< �����ң����� */
    HI_CHAR aszGenre[HI_FORMAT_TITLE_MAX_LEN];          /**< ��� */
    HI_CHAR aszComments[HI_FORMAT_TITLE_MAX_LEN];       /**< ��ע */
    HI_CHAR aszTime[HI_FORMAT_TIME_LEN];                /**< ������� */
    HI_U32  u32ProgramNum;                              /**< ʵ�ʽ�Ŀ���� */
    HI_FORMAT_PROGRAM_INFO_S astProgramInfo[HI_FORMAT_MAX_PROGRAM_NUM];    /**< ��Ŀ��Ϣ */
} HI_FORMAT_FILE_INFO_S;

/** ֡���� */
typedef struct hiFORMAT_FRAME_S
{
    HI_FORMAT_DATA_TYPE_E eType;          /**< �������� */
    HI_S32  s32StreamIndex;               /**< ������ */
    HI_BOOL bKeyFrame;                    /**< �Ƿ�Ϊ�ؼ�֡ */
    HI_U32  u32Len;                       /**< ֡���ݳ��ȣ���λ�ֽڣ�����raw��ʽ���ò���Ϊ����/���������
                                               ����ΪҪ��ȡ���ֽ��������Ϊʵ�ʶ�ȡ���ֽ��� */
    HI_U8   *pu8Addr;                     /**< ֡���ݵ�ַ */
    HI_S64  s64Pts;                       /**< ʱ�������λms�����û��ʱ���������Ϊ::HI_FORMAT_NO_PTS */
    HI_U32  u32Duration;                  /**< ��ʾʱ������λms��û��duration������Ϊ0 */
    HI_U32  u32UserData;                  /**< ˽�����ݣ�����������ͨ���ò����ش�˽������ */
} HI_FORMAT_FRAME_S;


/** Э�飨�磺file��http��API */
typedef struct hiFORMAT_PROTOCOL_FUN_S
{
    /** 
    \brief ���������Э���Ƿ�֧��
    \attention \n
    ��
    \param[in] pszUrl �ļ�url����http://
    
    \retval ::HI_SUCCESS ֧�ָ�Э��
    \retval ::HI_FAILURE ��֧�ָ�Э��
    
    \see \n
    ��
    */
    HI_S32 (*url_find)(const HI_CHAR *pszUrl);

    /** 
    \brief ���ļ�
    \attention \n
    ��
    \param [in]  pszUrl url��ַ
    \param [in]  eFlag �򿪷�ʽ
    \param [out] pUrlHandle Э����
    
    \retval ::HI_SUCCESS �ļ��򿪳ɹ��������Ч
    \retval ::HI_FAILURE �ļ���ʧ��
    
    \see \n
    ��
    */
    HI_S32 (*url_open)(const HI_CHAR *pszUrl, HI_FORMAT_URL_OPENFLAG_E eFlag, HI_HANDLE *pUrlHandle);

    /** 
    \brief ��ȡָ����С����
    \attention \n
    ��
    \param [in] urlHandle �ļ����
    \param [in] s32Size ��ȡ�����ݴ�С���ֽ�Ϊ��λ
    \param [out] pu8Buf ���ݴ洢����
    
    \retval ::>0����ֵ����ȡ���ֽ���
    \retval ::HI_FAILURE �ļ�����
    
    \see \n
    ��
    */
    HI_S32 (*url_read)(HI_HANDLE urlHandle, HI_U8 *pu8Buf, HI_S32 s32Size);

    /** 
    \brief seek��ָ��λ�ã����ڲ�֧��seek���ļ�������HI_FAILURE��
    \attention \n
    ��
    \param [in] urlHandle �ļ����
    \param [in] s64Offsets seek�ֽ���
    \param [in] seek��ʾ��SEEK_CUR�ӵ�ǰλ��ƫ��s32Offsets,SEEK_SET����ʼλ��
    
    \retval ::��HI_FAILURE �ļ���ʼƫ���ֽ���
    \retval ::HI_FAILURE seekʧ��
    
    \see \n
    ��
    */
    HI_S64 (*url_seek)(HI_HANDLE urlHandle, HI_S64 s64Offsets, HI_S32 s32Whence);

    /** 
    \brief �����ļ����
    \attention \n
    ��
    \param [in] urlHandle �ļ����
    
    \retval ::HI_SUCCESS �ļ�������ٳɹ�
    \retval ::HI_FAILURE �����Ƿ�
    
    \see \n
    ��
    */
    HI_S32 (*url_close)(HI_HANDLE urlHandle);

    /** 
    \brief seekָ������
    \attention \n
    ��
    \param [in] urlHandle �ļ����
    \param [in] s32StreamIndex ������
    \param [in] s64Timestamp ʱ�������λms
    \param [in] eFlags seek���
    
    \retval ::HI_SUCCESS seek�ɹ�
    \retval ::HI_FAILURE seekʧ��
    
    \see \n
    ��
    */
    HI_S32 (*url_read_seek)(HI_HANDLE urlHandle, HI_S32 s32StreamIndex, HI_S64 s64Timestamp, HI_FORMAT_SEEK_FLAG_E eFlags);
} HI_FORMAT_PROTOCOL_FUN_S;


/** �ļ�������API */
typedef struct hiFORMAT_DEMUXER_FUN_S
{
    /** 
    \brief ����������ļ���ʽ�Ƿ�֧�֣�����0֧�֣�������֧��
    \attention \n
    ��
    \param [in] pszFileName �ļ����ƣ�·��+�ļ������ļ���
    
    \retval ::HI_SUCCESS ֧�ָ��ļ���ʽ
    \retval ::HI_FAILURE ��֧�ָ��ļ���ʽ
    
    \see \n
    ��
    */
    HI_S32 (*fmt_find)(const HI_CHAR *pszFileName);

    /** 
    \brief ��ָ���ļ�
    \attention \n
    ��
    \param [in] pszFileName �ļ�·��
    \param [in]  pstProtocol Э������ӿڣ�ע��Ķ�̬�����û��Э������ӿڿ���ͨ���÷�ʽָ��
    \param [out] pFmtHandle ����ļ����������

    \retval ::HI_SUCCESS �ļ��򿪳ɹ��������������Ч
    \retval ::HI_FAILURE �ļ���ʧ��
    
    \see \n
    ��
    */
    HI_S32 (*fmt_open)(const HI_CHAR *pszFileName, const HI_FORMAT_PROTOCOL_FUN_S *pstProtocol, HI_HANDLE *pFmtHandle);

    /** 
    \brief ��ȡ�ļ���Ϣ�����ý���ļ�������Ƶ�������轫��Ƶstreamindex����ΪHI_FORMAT_INVALID_STREAM_ID
    \attention \n
    ��
    \param [in] fmtHandle �ļ�·��
    \param [out] pstFmtInfo ����ļ���Ϣ

    \retval ::HI_SUCCESS �����ɹ�
    \retval ::HI_FAILURE �����Ƿ�
    
    \see \n
    ��
    */
    HI_S32 (*fmt_getinfo)(HI_HANDLE fmtHandle, HI_FORMAT_FILE_INFO_S *pstFmtInfo);

    /** 
    \brief ��ȡһ֡���ݣ���ȡ���ݱ������fmt_free�ͷ�
    \attention \n
    ��ȡ��֡�������û��ʱ�������ʱ���ֵ����ΪHI_FORMAT_NO_PTS
    \param [in] fmtHandle �ļ����������
    \param [in/out] pstFmtFrame ý��������Ϣ

    \retval ::HI_SUCCESS �����ɹ�
    \retval ::HI_FAILURE �����Ƿ�
    \retval ::HI_FORMAT_ERRO_ENDOFFILE �ļ�����

    \see \n
    ��
    */
    HI_S32 (*fmt_read)(HI_HANDLE fmtHandle, HI_FORMAT_FRAME_S *pstFmtFrame);

    /** 
    \brief �ͷ�֡����
    \attention \n
    ��
    \param [in] fmtHandle �ļ����������
    \param [in] pstFmtFrame fmt_read�ӿڶ�ȡ��ý��������Ϣ

    \retval ::HI_SUCCESS �����ɹ�
    \retval ::HI_FAILURE �����Ƿ�

    \see \n
    ��
    */
    HI_S32 (*fmt_free)(HI_HANDLE fmtHandle, HI_FORMAT_FRAME_S *pstFmtFrame);

    /** 
    \brief seek��ָ��pts��s64ptsΪ0��ʾseek���ļ�ͷ
    \attention \n
    ��
    \param [in] fmtHandle �ļ����������
    \param [in] s32StreamIndex ������
    \param [in] s64Pts ʱ�������λms
    \param [in] eFlag seek���

    \retval ::HI_SUCCESS �����ɹ�
    \retval ::HI_FAILURE ��֧��seek����

    \see \n
    ��
    */
    HI_S32 (*fmt_seek_pts)(HI_HANDLE fmtHandle, HI_S32 s32StreamIndex, HI_S64 s64Pts, HI_FORMAT_SEEK_FLAG_E eFlag);

    /** 
    \brief seek��ָ��λ�ֽ�����λ�ã������������ļ�������ͨ���ýӿ�ʵ����Ծ
    \attention \n
    ��
    \param [in] fmtHandle �ļ����������
    \param [in] s64Offsets seek�ֽ���
    \param [in] s32Whence ��ʾ����SEEK_CUR

    \retval ::��HI_FAILURE seek���ļ�ָ��ƫ���ֽ���
    \retval ::HI_FAILURE ��֧��seek����

    \see \n
    ��
    */
    HI_S64 (*fmt_seek_pos)(HI_HANDLE fmtHandle, HI_S64 s64Offsets, HI_S32 s32Whence);

    /** 
    \brief �ر��ļ�������
    \attention \n
    ��
    \param [in] fmtHandle �ļ����������

    \retval ::HI_SUCCESS �����ɹ�
    \retval ::HI_FAILURE �����Ƿ�

    \see \n
    ��
    */
    HI_S32 (*fmt_close)(HI_HANDLE fmtHandle);
} HI_FORMAT_DEMUXER_FUN_S;

/** �ļ����������Э������������ļ���������Э���������ʵ��
  * �ṹ���ж���ĺ�������ָ�����������ƣ�
  * ֧�ֵ��ļ���ʽ���汾�ŵ����ԣ�ͨ��dlsym
  * ϵͳ�����ܵ����ļ��������ж���ĸý�
  * ����ȫ�ַ��ţ��ⲿ�����޸ĸ÷��ŵ�����ֵ��
  * ����ʾ��: �������ж������±�����
  * HI_FORMAT_S g_stFormat_entry = {
  *     .pszDllName           = (const HI_PCHAR )"libavformat.so",
  *     .pszFormatName        = "asf,mp4,avi,smi,srt",
  *     .pszProtocolName      = "http,udp,file",
  *     .pszFmtDesc           = (const HI_PCHAR)"hisilicon avformat",
  *     .u32Merit             = 0;
  *     .stDemuxerFun.fmt_open             = ... ,
  *     .stDemuxerFun.fmt_getinfo          = ... ,
  *     .stDemuxerFun.fmt_read             = ... ,
  *     .stDemuxerFun.fmt_free             = ... ,
  *     .stDemuxerFun.fmt_close            = ... ,
  *     .stDemuxerFun.fmt_seek_pts         = ... ,
  *     .stDemuxerFun.fmt_seek_pos         = ... ,
  *
  *     .stProtocolFun.url_open            = ... ,
  *     .stProtocolFun.url_read            = ... ,
  *     .stProtocolFun.url_seek            = ... ,
  *     .stProtocolFun.url_close           = ... ,
  *     .stProtocolFun.url_read_seek       = ... ,
  * };
  *
  * APP���ط�ʽ����:
  *
  * HI_FORMAT_S *pstEntry = NULL;
  * pstEntry = dlsym(pDllModule, "g_stFormat_entry");
  *
  * ���÷�ʽ:
  * pstEntry->fmt_open();
  *  
  */
  
/** �ļ����������� */  
typedef struct hiFORMAT_S
{
    /**< ���������� */
    const HI_CHAR *pszDllName;

    /**< ������֧�ֵ��ļ���ʽ�������ļ���ʽ��","Ϊ��� */
    const HI_CHAR *pszFormatName;

    /**< ֧�ֵ�Э�飬����Э����","Ϊ��� */
    const HI_CHAR *pszProtocolName;

    /**< �������汾�� */
    const HI_FORMAT_LIB_VERSION_S stLibVersion;

    /**< ���������� */
    const HI_CHAR *pszFmtDesc;

    /**< ���ȼ�����0x0 - 0xFFFFFFFF��0xFFFFFFFF���ȼ���ߣ���������Ч */
    HI_U32 u32Merit;

    /**< �ļ����������ʽӿڣ��ļ�������ʵ�ֱ�����ѭ���¹���:
         1�������ļ��򿪡���ȡ���رյȲ���������ڱ����ļ���fopen/fclose�ȣ�
            �������ⲿָ�����ҿ������·���url�����ӿ����� */

    HI_FORMAT_DEMUXER_FUN_S stDemuxerFun;

    /**< Э����ʽӿڣ��ýӿ���ѭ���¹���:
         1������ļ�������û��ʵ�ָýӿڣ����뽫�ò�������ΪNULL;
         2���ò����������ⲿָ������: �ļ����������Բ�ʵ�ָýӿڣ�
            �ڽ������̶��ļ��Ĳ���ʹ���ⲿָ���ӿ�; */

    HI_FORMAT_PROTOCOL_FUN_S stProtocolFun;

    struct hiFORMAT_S *next;

    /**< ��������̬���� */
    HI_VOID  *pDllModule;

    /**< ˽������ */
    HI_U32 u32PrivateData;
} HI_FORMAT_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_SVR_FORMAT_H__ */

