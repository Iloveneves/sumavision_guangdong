/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_pvr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/xx/xx
  Description   : hi_unf_mce.h header file
  History       :
  1.Date        : 2011/xx/xx
    Author      : 
    Modification: Created file

******************************************************************************/
/**
 * \file
 * \brief provide logo /play content and relevant configure information
 */
#ifndef __HI_UNF_MCE_H__
#define __HI_UNF_MCE_H__

#include "hi_unf_common.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_pic.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif  /* End of #ifdef __cplusplus */

/********************************Macro Definition********************************/
/** \addtogroup      H_2_2_xx */
/** @{ */  /** <!-- ¡¾MCE CONFIG¡¿ */

/**<the name of fastplay area,must be the same as the name in flash */
#define MTD_FASTPLAY_NAME  "fastplay"
#define MTD_LOGO_NAME "logo"
#define MTD_BASEPARAM_NAME "baseparam"
/**<fastplay area is divided into 5 parts:
 	1, base param part, 8KB
 	2, logo param part,  8KB
 	3, logo data part,      XKB
 	4, play param part,   8KB
 	5, play data part,	fastplay total size - 24KB - XKB
 */
#define PART_DEFT_PARA_SIZE		0x2000


/********************************Struct Definition********************************/
/** \addtogroup      H_2_2_xx */
/** @{ */  /** <!-- ¡¾MCE CONFIG¡¿ */

/** Video config  information*/
typedef struct hiUNF_MCE_BASE_PARAM_S
{
	HI_UNF_ENC_FMT_E hdFmt;				/**<hd video format */
	HI_UNF_ENC_FMT_E sdFmt;				/**<sd video format  */
	HI_UNF_DISP_INTF_TYPE_E hdIntf;		/**<hd channel type*/
  	HI_UNF_DISP_INTF_TYPE_E sdIntf;		/**<sd channel type*/
	HI_UNF_DISP_INTERFACE_S DacMode;	/**<DAC Mode */
	unsigned int layerformat;				/**layer pixel format*/
	unsigned int inrectwidth;				/**width of the input */
	unsigned int inrectheight;				/**height of the input*/
}HI_UNF_MCE_BASE_PARAM_S;


/** parameter of logo configure */
typedef struct hiUNF_MCE_LOGO_PARAM_S
{
	HI_U32 contentLen;					/**<size of the logo data */
	//HI_U32 dispTime;					/**<display time */
}HI_UNF_MCE_LOGO_PARAM_S;

/*fastplay support the decode mode of  AO */
typedef enum hiUNF_MCE_ADEC_TYPE_E
{
	HI_UNF_MCE_ADEC_TYPE_MP2 = 0,		/**<MP2 format */
	HI_UNF_MCE_ADEC_TYPE_MP3 = 1,		/**<MP3 format */
	HI_UNF_MCE_ADEC_TYPE_BUTT			/**<invalid format */
}HI_UNF_MCE_ADEC_TYPE_E;

/*fastplay support the decode mode of  VO */
typedef enum hiUNF_MCE_VDEC_TYPE_E
{
	HI_UNF_MCE_VDEC_TYPE_MPEG2 = 0,		/**<MPEG2  format */
	HI_UNF_MCE_VDEC_TYPE_MPEG4 = 1,		/**<MPEG4  format */
	HI_UNF_MCE_VDEC_TYPE_H264  = 2,		/**<H264  format */
	HI_UNF_MCE_VDEC_TYPE_AVS   = 3,		/**<AVS   format */
	HI_UNF_MCE_VDEC_TYPE_BUTT			/**<invalid format */
}HI_UNF_MCE_VDEC_TYPE_E;



/** parameters of dvb play configure  */
typedef struct hiUNF_MCE_DVB_PARAM_S
{
	HI_U32 PcrPid;						/**<pcr pid*/
	HI_U32 u32PlayTime;				       /*<play time */
	HI_U32 VElementPid;					/**<video pid*/
	HI_U32 AElementPid;					/**<audio pid*/
	HI_UNF_MCE_VDEC_TYPE_E VideoType;	/**<video type*/
	HI_UNF_MCE_ADEC_TYPE_E AudioType;	/**<audio type*/
	HI_U32 tunerId;						/**<tuner Id default value is 0*/
	HI_U32 tunerFreq;					/**<tuner frequence*/
	HI_U32 tunerSrate;					/**<tuner symbol rate*/
	HI_U32 tunerQam;					/**<tuner QAM */
	HI_U32 volume;						/**<volume of output*/
	HI_UNF_TRACK_MODE_E trackMode;		/**<mode of track only support HI_UNF_TRACK_MODE_STEREO*/
	HI_UNF_VO_DEV_MODE_E devMode;		/**vo mode of dev  */
}HI_UNF_MCE_DVB_PARAM_S;

/*the play parameter configure of ts file */
typedef struct hiUNF_MCE_TSFILE_PARAM_S
{
	HI_U32 contentLen;					/** file length */
	HI_BOOL IsCycle;					      /*default cycle*/
	HI_U32   u32PlayTime;				       /**<play time */
	HI_U32 PcrPid;						/**<pcr pid*/
	HI_U32 VElementPid;					/**<video pid*/	
	HI_U32 AElementPid;					/**<audio pid*/
	HI_UNF_MCE_VDEC_TYPE_E VideoType;	/**<video type*/
	HI_UNF_MCE_ADEC_TYPE_E AudioType;	/**<audio type*/
	HI_U32 volume;						/**volume of output */
	HI_UNF_TRACK_MODE_E trackMode;		/**<mode of track only support HI_UNF_TRACK_MODE_STEREO*/
	HI_UNF_VO_DEV_MODE_E devMode;		/**vo mode of dev  */
}HI_UNF_MCE_TSFILE_PARAM_S;


/** parameter configure of animation */
typedef struct hiUNF_MCE_GPHFILE_PARAM_S
{
	
	HI_BOOL IsCycle;					/**<whether is play by loop,current only support play by loop*/
	HI_U32   u32PlayTime;					/**<play time */
	HI_UNF_PIC_COMMINFO comInfo;	/**< animation common information*/
	HI_UNF_PIC_PICTURE	   *ppicInfo;	/**< animation picture show  information*/
}HI_UNF_MCE_GPHFILE_PARAM_S;


/** type of play  */
typedef enum hiUNF_MCE_PLAY_TYPE_E
{
	HI_UNF_MCE_TYPE_PLAY_DVB	 = 0, 	/**<DVB type */ 
	HI_UNF_MCE_TYPE_PLAY_TSFILE  = 1,        /**<ts file type */ 
	HI_UNF_MCE_TYPE_PLAY_GPHFILE = 2,  	/**<image animation file type */ 
	HI_UNF_MCE_TYPE_PLAY_BUTT  			/**<invalid type */
}HI_UNF_MCE_PLAY_TYPE_E;


/** the part of fastplay that will be operated */
typedef enum hiUNF_PARTION_TYPE_E
{
	HI_UNF_PARTION_TYPE_BASE  = 0,  	       /**<video display relevant configuration */ 
	HI_UNF_PARTION_TYPE_LOGO  = 1,  	       /**<logo configuration and logo data */
	HI_UNF_PARTION_TYPE_PLAY  = 2, 	 	/**<play configuation and play data*/
	HI_UNF_PARTION_TYPE_BUTT  = 3		/**<invalid operation */
}HI_UNF_PARTION_TYPE_E;


/** configuration of play */
typedef struct hiUNF_MCE_PLAY_PARAM_S
{
	HI_UNF_MCE_PLAY_TYPE_E playType;				/**<play type*/
	unsigned int fastplayflag;                                          /*the fastplay is play or not ;0 :not play, 1:play*/
	union 
	{
		HI_UNF_MCE_DVB_PARAM_S     dvbParam;		/**<DVB configuration */
		HI_UNF_MCE_TSFILE_PARAM_S  tsFileParam;	       /**<ts configuration */
		HI_UNF_MCE_GPHFILE_PARAM_S gphFileParam;	/**<animation configuration */
 	}param;
}HI_UNF_MCE_PLAY_PARAM_S;



/** @} */  /** <!-- ==== Struct Definition end ==== */

/********************************API declaration********************************/
/** \addtogroup      H_2_2_xx */
/** @{ */  /** <!-- ¡¾MCE CONFIG¡¿ */

/** 
\brief  init mce
\attention \n
initialize the mce ,prepare for other operation
\param[in]  PartType . the part that you want to operate
\retval ::HI_SUCCESS success
\retval ::HI_ERR_MCE_OPEN_ALREADY   already open
\retval ::HI_ERR_MCE_PARAM_INVALID    invalid parameter
\retval ::HI_ERR_MCE_MTD_NOFIND        no this part
\retval ::HI_ERR_MCE_MTD_INFO              size is no enough for data loaded
\see \n
no
*/
HI_S32  HI_UNF_MCE_Init(HI_UNF_PARTION_TYPE_E  PartType);

/** 
\brief  deinit mce
\attention \n
destroy all the mce resource
\param[in] no
\retval :: no
\see \n
no
*/
HI_VOID HI_UNF_MCE_deInit(HI_VOID);

/** 
\brief get the base configuration information
\attention \n
no
\param[in]  baseParam .pointer of the base param
\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_GetBaseParam(HI_UNF_MCE_BASE_PARAM_S *baseParam);


/** 
\brief modify the base configuration information
\attention \n
no
\param[in]  baseParam.pointer of the base param
\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_UpdateBaseParam(HI_UNF_MCE_BASE_PARAM_S *baseParam);

/** 
\brief get the base configuration information from  flash memory
\attention \n
no
\param[in]  logoParam  pointer of the logo param

\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_GetLogoParam(HI_UNF_MCE_LOGO_PARAM_S *logoParam);

/** 
\brief modify configuration information of logo param
\attention \n
no

\param[in]  logoParam  pointer of the logo param
\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_UpdateLogoParam(HI_UNF_MCE_LOGO_PARAM_S *logoParam);


/** 
\brief get the logo data from flash memory
\attention \n
no

\param[in]  content  . pointer of the logo data that would be written from flash
\param[in]  size  . size of the logo data that would be written

\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_GetLogoContent(HI_U8 *content, HI_U32 size);


/** 
\brief  modify the logo data 
\attention \n
no

\param[in]  content  . pointer of the logo data that would be read from flash
\param[in]  size  . size of the logo data that would be read

\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_UpdateLogoContent(HI_U8 *content, HI_U32 size);

/** 
\brief get the configuration information of the play
\attention \n
no
\param[in]  playParam  configuration information of the play 

\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_GetPlayParam(HI_UNF_MCE_PLAY_PARAM_S *playParam);

/** 
\brief modify the configuration information of the play
\attention \n
no
\param[in]  playParam  configuration information of the play 

\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_UpdatePlayParam(HI_UNF_MCE_PLAY_PARAM_S *playParam);

/** 
\brief get the play data from flash memory
\attention \n
no
\param[in]  content  . pointer of the data that would be read from flash
\param[in]  size  . size of the play data that would be read

\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_GetPlayContent(HI_U8 *content, HI_U32 size);


/** 
\brief update play data part
\attention \n
no
\param[in]  content  . pointer of the data that would be written into flash
\param[in]  size  . size of the play data 

\retval ::HI_SUCCESS  success
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_UpdatePlayContent(HI_U8 *content, HI_U32 size);

/** 
\brief open or close logo 
\attention \n
no
\param[in]  bLogoOpen£¬setting the logo  is open or close

\retval ::HI_SUCCESS 
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_SetLogoFlag(HI_BOOL bLogoOpen);

/** 
\brief open or close logo 
\attention \n
no
\param[in]  bPlayOpen£¬setting the play  is open or close

\retval ::HI_SUCCESS 
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_SetFastplayFlag(HI_BOOL bPlayOpen);

/** 
\brief open or close logo 
\attention \n
no
\param[out]  pbLogoOpen£¬get the logo whether is open

\retval ::HI_SUCCESS 
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_GetLogoFlag(HI_BOOL *pbLogoOpen);

/** 
\brief open or close logo 
\attention \n
no

\param[out]  pbPlayOpen£¬get the play whether is open

\retval ::HI_SUCCESS 
\retval ::HI_ERR_MCE_PTR_NULL      pointer is NULL
\retval ::HI_ERR_MCE_MTD_NOFIND    no this part
\retval ::HI_ERR_MCE_PARAM_INVALID  invalid parameter
\retval ::HI_ERR_MCE_MTD_OPEN       open failed
\retval ::HI_ERR_MCE_MTD_WRITE     write failed
\retval ::HI_ERR_MCE_MTD_CLOSE     close failed
\see \n
no
*/
HI_S32  HI_UNF_MCE_GetFastplayFlag(HI_BOOL *pbPlayOpen);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


