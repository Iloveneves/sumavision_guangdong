/**
 \file
 \brief 文件解析器，协议结构体
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
/** @{ */  /** <!-- 【文件解析器错误码】 */

/** 到达文件结束位置 */
#define HI_FORMAT_ERRO_ENDOFFILE            (HI_FAILURE - 1)

/** @} */  /*! <!-- Macro Definition end */  


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_1 */
/** @{ */  /** <!-- 【文件解析器数据结构】 */

/** 最大节目个数，如ts媒体文件，节目个数如果超过5个，则播放器最多只能存储其中某5个节目信息，并播放其中的某一个 */
#define HI_FORMAT_MAX_PROGRAM_NUM           (5)
/** 路径字符长度 */
#define HI_FORMAT_MAX_URL_LEN               (512)
/** 文件名称长度 */
#define HI_FORMAT_MAX_FILE_NAME_LEN         (256)
/** 文件标题、作者等最大字符数 */
#define HI_FORMAT_TITLE_MAX_LEN             (512)
/** 语言字符数 */
#define HI_FORMAT_LANG_LEN                  (4)
/** 字幕标题长度 */
#define HI_FORMAT_SUB_TITLE_LEN             (8)
/** 年份字节数 */
#define HI_FORMAT_TIME_LEN                  (8)
/** 流个数 */
#define HI_FORMAT_MAX_STREAM_NUM            (5)
/** 支持的最多语言种类个数 */
#define HI_FORMAT_MAX_LANG_NUM              (5)
/** 没有pts */
#define HI_FORMAT_NO_PTS                    (-1)
/** 非法streamid */
#define HI_FORMAT_INVALID_STREAM_ID         (-1)
/** 调色板字节数，rgb+a */
#define HI_FORMAT_PALETTE_LEN               (4 * 256)

/*************************** Structure Definition ****************************/

/** 版本号定义 */
typedef struct hiFORMAT_LIB_VERSION_S
{
    HI_U8 u8VersionMajor;    /**< Major version accessor element */
    HI_U8 u8VersionMinor;    /**< Minor version accessor element */
    HI_U8 u8Revision;        /**< Revision version accessor element */
    HI_U8 u8Step;            /**< Step version accessor element */
} HI_FORMAT_LIB_VERSION_S;

/** 文件打开方式 */
typedef enum hiFORMAT_URL_OPENFLAG_E
{
    HI_FORMAT_URL_OPEN_RDONLY = 0x0,   /**< 只读方式 */
    HI_FORMAT_URL_OPEN_RDWR,           /**< 读/写方式 */
    HI_FORMAT_URL_OPEN_BUTT
} HI_FORMAT_URL_OPENFLAG_E;

/** 文件SEEK标记 */
typedef enum hiFORMAT_SEEK_FLAG_E
{   
    HI_FORMAT_AVSEEK_FLAG_NORMAL = 0x0,     /**< 从当前帧向文件尾seek，找到离当前帧最近的关键帧 */
    HI_FORMAT_AVSEEK_FLAG_BACKWARD,         /**< 从当前帧向文件头seek，找到离当前帧最近的关键帧 */
    HI_FORMAT_AVSEEK_FLAG_BYTE,             /**< 按字节seek */
    HI_FORMAT_AVSEEK_FLAG_ANY,              /**< 不管是向文件头还是文件尾，找到离当前帧最近的关键帧 */
    HI_FORMAT_AVSEEK_FLAG_BUTT
} HI_FORMAT_SEEK_FLAG_E;

/** 流类型，文件解析器解析出来的流数据类型 */
typedef enum hiFORMAT_DATA_TYPE_E
{
    HI_FORMAT_DATA_NULL = 0x0,
    HI_FORMAT_DATA_AUD,          /**< 音频流 */
    HI_FORMAT_DATA_VID,          /**< 视频流 */
    HI_FORMAT_DATA_SUB,          /**< 字幕流 */
    HI_FORMAT_DATA_RAW,          /**< 字节流 */
    HI_FORMAT_DATA_BUTT
} HI_FORMAT_DATA_TYPE_E;

/** 文件流类型，播放的文件类型 */
typedef enum hiFORMAT_STREAM_TYPE_E
{
    HI_FORMAT_STREAM_ES = 0x0,    /**< es流文件 */
    HI_FORMAT_STREAM_TS,          /**< ts流文件 */
    HI_FORMAT_STREAM_NORMAL,      /**< 普通文件 */
    HI_FPRMAT_STREAM_BUTT
} HI_FORMAT_STREAM_TYPE_E;

/** 字幕数据类型 */
typedef enum hiFORMAT_SUBTITLE_DATA_TYPE_E
{
    HI_FORMAT_SUBTITLE_DATA_TEXT = 0x0,    /**< 字符串 */
    HI_FORMAT_SUBTITLE_DATA_BMP,           /**< bmp图片 */
    HI_FORMAT_SUBTITLE_DATA_ASS,           /**< ass字幕 */
    HI_FORMAT_SUBTITLE_DATA_BUTT
} HI_FORMAT_SUBTITLE_DATA_TYPE_E;

/** 音频流信息 */
typedef struct hiFORMAT_AUD_INFO_S
{
    HI_S32 s32StreamIndex;                   /**< 流索引，对于ts流，该值为流pid，非法值为::HI_FORMAT_INVALID_STREAM_ID */
    HI_U32 u32Format;                        /**< 音频编码格式，值定义参考HA_AUDIO_ID_AAC等定义 */
    HI_U32 u32Version;                       /**< 音频编码版本，仅对wma编码，0x160(WMAV1), 0x161 (WMAV2) */
    HI_U32 u32SampleRate;                    /**< 8000,11025,441000,... */
    HI_U16 u16BitPerSample;                  /**< 音频每个采样点所占的比特数，8bit,16bit */
    HI_U16 u16Channels;                      /**< 声道数, 1 or 2 */
    HI_U32 u32BlockAlign;                    /**< packet包含的字节数 */
    HI_U32 u32Bps;                           /**< 音频码率，bits/s */
    HI_BOOL bBigEndian;                      /**< 大小端，仅pcm格式有效 */
    HI_CHAR aszAudLang[HI_FORMAT_LANG_LEN];  /**< 音频流语言 */
    HI_U32 u32ExtradataSize;                 /**< 扩展数据长度 */
    HI_U8  *pu8Extradata;                    /**< 扩展数据 */
} HI_FORMAT_AUD_INFO_S;

/** 视频流信息 */
typedef struct hiFORMAT_VID_INFO_S
{
    HI_S32 s32StreamIndex;        /**< 流索引，对于ts流，该值为流pid，非法值为::HI_FORMAT_INVALID_STREAM_ID */
    HI_U32 u32Format;             /**< 视频编码格式，值定义参考::HI_UNF_VCODEC_TYPE_E */
    HI_U16 u16Width;              /**< 宽度，单位像素 */
    HI_U16 u16Height;             /**< 高度，单位像素 */
    HI_U16 u16FpsInteger;         /**< 帧率，整数部分 */
    HI_U16 u16FpsDecimal;         /**< 帧率，小数部分 */
    HI_U32 u32Bps;                /**< 视频码率，bits/s */
    HI_U32 u32ExtradataSize;      /**< 扩展数据长度 */
    HI_U8  *pu8Extradata;         /**< 扩展数据 */
} HI_FORMAT_VID_INFO_S;

/** 字幕信息 */
typedef struct hiFORMAT_SUBTITLE_INFO_S
{
    HI_S32  s32StreamIndex;                            /**< 流索引，对于ts流，该值为流pid，非法值为::HI_FORMAT_INVALID_STREAM_ID */
    HI_BOOL bExtSubTitle;                              /**< 是否为外挂字幕 */
    HI_FORMAT_SUBTITLE_DATA_TYPE_E eSubtitileType;     /**< 字幕格式，如bmp,string */
    HI_CHAR aszSubTitleName[HI_FORMAT_SUB_TITLE_LEN];  /**< 字幕标题 */
    HI_U16  u16OriginalFrameWidth;                     /**< 原始图像宽度 */
    HI_U16  u16OriginalFrameHeight;                    /**< 原始图像高度 */
    HI_U16  u16HorScale;                               /**< 水平缩放比，0-100 */
    HI_U16  u16VerScale;                               /**< 垂直缩放比，0-100 */
    HI_U32  u32ExtradataSize;                          /**< 扩展数据长度 */
    HI_U8   *pu8Extradata;                             /**< 扩展数据 */
} HI_FORMAT_SUBTITLE_INFO_S;

/** 节目信息，如果文件既带内置字幕也带外置字幕，则外置字幕信息追加在内置字幕后，
    注: 如果媒体文件不带视频流，需将videstreamindex设置为HI_FORMAT_INVALID_STREAM_ID */
typedef struct hiFORMAT_PROGRAM_INFO_S
{
    HI_FORMAT_VID_INFO_S stVidStream;                                  /**< 视频流信息 */
    HI_U32 u32AudStreamNum;                                            /**< 音频流个数 */
    HI_FORMAT_AUD_INFO_S astAudStream[HI_FORMAT_MAX_STREAM_NUM];       /**< 音频流信息 */
    HI_U32 u32SubTitleNum;                                             /**< 字幕个数 */
    HI_FORMAT_SUBTITLE_INFO_S astSubTitle[HI_FORMAT_MAX_LANG_NUM];     /**< 字幕信息 */
} HI_FORMAT_PROGRAM_INFO_S;

/** 媒体文件信息 */
typedef struct hiFORMAT_FILE_INFO_S
{
    HI_FORMAT_STREAM_TYPE_E eStreamType;                /**< 文件流类型 */
    HI_U32  u32FileSize;                                /**< 文件大小，单位字节 */
    HI_S64  s64StartTime;                               /**< 文件播放起始时间，单位ms */
    HI_S64  s64Duration;                                /**< 文件总时长，单位ms */
    HI_U32  u32Bps;                                     /**< 文件码率，bits/s */
    HI_CHAR aszFileName[HI_FORMAT_MAX_FILE_NAME_LEN];   /**< 文件名称 */
    HI_CHAR aszAlbum[HI_FORMAT_TITLE_MAX_LEN];          /**< 专辑 */
    HI_CHAR aszTitle[HI_FORMAT_TITLE_MAX_LEN];          /**< 标题 */
    HI_CHAR aszArtist[HI_FORMAT_TITLE_MAX_LEN];         /**< 艺术家，作者 */
    HI_CHAR aszGenre[HI_FORMAT_TITLE_MAX_LEN];          /**< 风格 */
    HI_CHAR aszComments[HI_FORMAT_TITLE_MAX_LEN];       /**< 附注 */
    HI_CHAR aszTime[HI_FORMAT_TIME_LEN];                /**< 创建年份 */
    HI_U32  u32ProgramNum;                              /**< 实际节目个数 */
    HI_FORMAT_PROGRAM_INFO_S astProgramInfo[HI_FORMAT_MAX_PROGRAM_NUM];    /**< 节目信息 */
} HI_FORMAT_FILE_INFO_S;

/** 帧数据 */
typedef struct hiFORMAT_FRAME_S
{
    HI_FORMAT_DATA_TYPE_E eType;          /**< 数据类型 */
    HI_S32  s32StreamIndex;               /**< 流索引 */
    HI_BOOL bKeyFrame;                    /**< 是否为关键帧 */
    HI_U32  u32Len;                       /**< 帧数据长度，单位字节，对于raw方式，该参数为输入/输出参数，
                                               输入为要读取的字节数，输出为实际读取的字节数 */
    HI_U8   *pu8Addr;                     /**< 帧数据地址 */
    HI_S64  s64Pts;                       /**< 时间戳，单位ms，如果没有时间戳，设置为::HI_FORMAT_NO_PTS */
    HI_U32  u32Duration;                  /**< 显示时长，单位ms，没有duration，设置为0 */
    HI_U32  u32UserData;                  /**< 私有数据，解析器可以通过该参数回带私有数据 */
} HI_FORMAT_FRAME_S;


/** 协议（如：file，http）API */
typedef struct hiFORMAT_PROTOCOL_FUN_S
{
    /** 
    \brief 查找输入的协议是否支持
    \attention \n
    无
    \param[in] pszUrl 文件url，如http://
    
    \retval ::HI_SUCCESS 支持该协议
    \retval ::HI_FAILURE 不支持该协议
    
    \see \n
    无
    */
    HI_S32 (*url_find)(const HI_CHAR *pszUrl);

    /** 
    \brief 打开文件
    \attention \n
    无
    \param [in]  pszUrl url地址
    \param [in]  eFlag 打开方式
    \param [out] pUrlHandle 协议句柄
    
    \retval ::HI_SUCCESS 文件打开成功，句柄有效
    \retval ::HI_FAILURE 文件打开失败
    
    \see \n
    无
    */
    HI_S32 (*url_open)(const HI_CHAR *pszUrl, HI_FORMAT_URL_OPENFLAG_E eFlag, HI_HANDLE *pUrlHandle);

    /** 
    \brief 读取指定大小数据
    \attention \n
    无
    \param [in] urlHandle 文件句柄
    \param [in] s32Size 读取的数据大小，字节为单位
    \param [out] pu8Buf 数据存储缓冲
    
    \retval ::>0的数值，读取的字节数
    \retval ::HI_FAILURE 文件结束
    
    \see \n
    无
    */
    HI_S32 (*url_read)(HI_HANDLE urlHandle, HI_U8 *pu8Buf, HI_S32 s32Size);

    /** 
    \brief seek到指定位置，对于不支持seek的文件，返回HI_FAILURE，
    \attention \n
    无
    \param [in] urlHandle 文件句柄
    \param [in] s64Offsets seek字节数
    \param [in] seek标示，SEEK_CUR从当前位置偏移s32Offsets,SEEK_SET从起始位置
    
    \retval ::非HI_FAILURE 文件起始偏移字节数
    \retval ::HI_FAILURE seek失败
    
    \see \n
    无
    */
    HI_S64 (*url_seek)(HI_HANDLE urlHandle, HI_S64 s64Offsets, HI_S32 s32Whence);

    /** 
    \brief 销毁文件句柄
    \attention \n
    无
    \param [in] urlHandle 文件句柄
    
    \retval ::HI_SUCCESS 文件句柄销毁成功
    \retval ::HI_FAILURE 参数非法
    
    \see \n
    无
    */
    HI_S32 (*url_close)(HI_HANDLE urlHandle);

    /** 
    \brief seek指定的流
    \attention \n
    无
    \param [in] urlHandle 文件句柄
    \param [in] s32StreamIndex 流索引
    \param [in] s64Timestamp 时间戳，单位ms
    \param [in] eFlags seek标记
    
    \retval ::HI_SUCCESS seek成功
    \retval ::HI_FAILURE seek失败
    
    \see \n
    无
    */
    HI_S32 (*url_read_seek)(HI_HANDLE urlHandle, HI_S32 s32StreamIndex, HI_S64 s64Timestamp, HI_FORMAT_SEEK_FLAG_E eFlags);
} HI_FORMAT_PROTOCOL_FUN_S;


/** 文件解析器API */
typedef struct hiFORMAT_DEMUXER_FUN_S
{
    /** 
    \brief 查找输入的文件格式是否支持，返回0支持，其他不支持
    \attention \n
    无
    \param [in] pszFileName 文件名称，路径+文件名或文件名
    
    \retval ::HI_SUCCESS 支持该文件格式
    \retval ::HI_FAILURE 不支持该文件格式
    
    \see \n
    无
    */
    HI_S32 (*fmt_find)(const HI_CHAR *pszFileName);

    /** 
    \brief 打开指定文件
    \attention \n
    无
    \param [in] pszFileName 文件路径
    \param [in]  pstProtocol 协议操作接口，注册的动态库如果没有协议操作接口可以通过该方式指定
    \param [out] pFmtHandle 输出文件解析器句柄

    \retval ::HI_SUCCESS 文件打开成功，解析器句柄有效
    \retval ::HI_FAILURE 文件打开失败
    
    \see \n
    无
    */
    HI_S32 (*fmt_open)(const HI_CHAR *pszFileName, const HI_FORMAT_PROTOCOL_FUN_S *pstProtocol, HI_HANDLE *pFmtHandle);

    /** 
    \brief 获取文件信息，如果媒体文件不带视频流，则需将视频streamindex设置为HI_FORMAT_INVALID_STREAM_ID
    \attention \n
    无
    \param [in] fmtHandle 文件路径
    \param [out] pstFmtInfo 输出文件信息

    \retval ::HI_SUCCESS 操作成功
    \retval ::HI_FAILURE 参数非法
    
    \see \n
    无
    */
    HI_S32 (*fmt_getinfo)(HI_HANDLE fmtHandle, HI_FORMAT_FILE_INFO_S *pstFmtInfo);

    /** 
    \brief 读取一帧数据，读取数据必须调用fmt_free释放
    \attention \n
    读取的帧数据如果没有时间戳，将时间戳值设置为HI_FORMAT_NO_PTS
    \param [in] fmtHandle 文件解析器句柄
    \param [in/out] pstFmtFrame 媒体数据信息

    \retval ::HI_SUCCESS 操作成功
    \retval ::HI_FAILURE 参数非法
    \retval ::HI_FORMAT_ERRO_ENDOFFILE 文件结束

    \see \n
    无
    */
    HI_S32 (*fmt_read)(HI_HANDLE fmtHandle, HI_FORMAT_FRAME_S *pstFmtFrame);

    /** 
    \brief 释放帧数据
    \attention \n
    无
    \param [in] fmtHandle 文件解析器句柄
    \param [in] pstFmtFrame fmt_read接口读取的媒体数据信息

    \retval ::HI_SUCCESS 操作成功
    \retval ::HI_FAILURE 参数非法

    \see \n
    无
    */
    HI_S32 (*fmt_free)(HI_HANDLE fmtHandle, HI_FORMAT_FRAME_S *pstFmtFrame);

    /** 
    \brief seek到指定pts，s64pts为0表示seek到文件头
    \attention \n
    无
    \param [in] fmtHandle 文件解析器句柄
    \param [in] s32StreamIndex 流索引
    \param [in] s64Pts 时间戳，单位ms
    \param [in] eFlag seek标记

    \retval ::HI_SUCCESS 操作成功
    \retval ::HI_FAILURE 不支持seek操作

    \see \n
    无
    */
    HI_S32 (*fmt_seek_pts)(HI_HANDLE fmtHandle, HI_S32 s32StreamIndex, HI_S64 s64Pts, HI_FORMAT_SEEK_FLAG_E eFlag);

    /** 
    \brief seek到指定位字节数的位置，对于裸码流文件，可以通过该接口实现跳跃
    \attention \n
    无
    \param [in] fmtHandle 文件解析器句柄
    \param [in] s64Offsets seek字节数
    \param [in] s32Whence 标示，如SEEK_CUR

    \retval ::非HI_FAILURE seek后，文件指针偏移字节数
    \retval ::HI_FAILURE 不支持seek操作

    \see \n
    无
    */
    HI_S64 (*fmt_seek_pos)(HI_HANDLE fmtHandle, HI_S64 s64Offsets, HI_S32 s32Whence);

    /** 
    \brief 关闭文件解析器
    \attention \n
    无
    \param [in] fmtHandle 文件解析器句柄

    \retval ::HI_SUCCESS 操作成功
    \retval ::HI_FAILURE 参数非法

    \see \n
    无
    */
    HI_S32 (*fmt_close)(HI_HANDLE fmtHandle);
} HI_FORMAT_DEMUXER_FUN_S;

/** 文件解析组件、协议组件参数，文件解析器、协议组件必须实现
  * 结构体中定义的函数，并指定解析器名称，
  * 支持的文件格式，版本号等属性，通过dlsym
  * 系统函数能导出文件解析器中定义的该结
  * 构体全局符号，外部不能修改该符号的属性值，
  * 如下示例: 解析器中定义如下变量，
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
  * APP加载方式如下:
  *
  * HI_FORMAT_S *pstEntry = NULL;
  * pstEntry = dlsym(pDllModule, "g_stFormat_entry");
  *
  * 调用方式:
  * pstEntry->fmt_open();
  *  
  */
  
/** 文件解析器属性 */  
typedef struct hiFORMAT_S
{
    /**< 解析器名称 */
    const HI_CHAR *pszDllName;

    /**< 解析器支持的文件格式，多种文件格式以","为间隔 */
    const HI_CHAR *pszFormatName;

    /**< 支持的协议，多种协议以","为间隔 */
    const HI_CHAR *pszProtocolName;

    /**< 解析器版本号 */
    const HI_FORMAT_LIB_VERSION_S stLibVersion;

    /**< 解析器描述 */
    const HI_CHAR *pszFmtDesc;

    /**< 优先级，从0x0 - 0xFFFFFFFF，0xFFFFFFFF优先级最高，该属性无效 */
    HI_U32 u32Merit;

    /**< 文件解析器访问接口，文件解析器实现必须遵循如下规则:
         1、对于文件打开、读取、关闭等操作，如对于本地文件的fopen/fclose等，
            可以由外部指定，且可以由下方的url操作接口适配 */

    HI_FORMAT_DEMUXER_FUN_S stDemuxerFun;

    /**< 协议访问接口，该接口遵循以下规则:
         1、如果文件解析器没有实现该接口，必须将该参数设置为NULL;
         2、该参数可以在外部指定，即: 文件解析器可以不实现该接口，
            在解析过程对文件的操作使用外部指定接口; */

    HI_FORMAT_PROTOCOL_FUN_S stProtocolFun;

    struct hiFORMAT_S *next;

    /**< 解析器动态库句柄 */
    HI_VOID  *pDllModule;

    /**< 私有数据 */
    HI_U32 u32PrivateData;
} HI_FORMAT_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_SVR_FORMAT_H__ */

