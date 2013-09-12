/*****************************************************************************
File name   : rocme_porting_player.h

Author		: XXX			

Description : The poriting interface & macro definition for MEDIA module.
	          
Copyright (C) BeiJing SUMAVision, Inc., 2011 .All rights reserved.

History		:
				2011.04.08		Created 					
*****************************************************************************/
#ifndef _ROCME_PORTING_MP_H_
#define _ROCME_PORTING_MP_H_



#include "rocme_porting_typedef.h"

#define ROC_PLAYER_MAX_PATH_LEN     (512)
/*定义player模块错误码*/
typedef enum
{
	ROC_PORTING_PLAYER_SUCCESS = 0,
	ROC_PORTING_PLAYER_FAILURE,       
	ROC_PORTING_PLAYER_INVALID_PARAM,
	ROC_PORTING_PLAYER_NOT_SUPPORT,        /*不支持的格式*/
	ROC_PORTING_PLAYER_UNKOWN
}Roc_Player_ErrCode_e;


/** 播放器打开参数 */
typedef struct
{
	UINT32_T x, y, w, h;   /*视频输出窗口的坐标及宽高*/
	UINT32_T reserved[2];
} Roc_Player_Param_t;


/*播放文件属性*/
typedef struct
{
    char aszSrcUrl[ROC_PLAYER_MAX_PATH_LEN];          /*媒体文件路径*/
} Roc_Player_Source_t;



/*文件的播放速率*/
typedef enum{
	ROC_PACE_1X_FORWARD,        /*前进，默认值*/
	ROC_PACE_1X_BACKWARD,       /*后退*/
	ROC_PACE_2X_FORWARD,       /*2倍速率快进*/
	ROC_PACE_4X_FORWARD,       /*4倍速率快进*/
	ROC_PACE_8X_FORWARD,       /*8倍速率快进*/
	ROC_PACE_16X_FORWARD,       /*16倍速率快进*/
	ROC_PACE_32X_FORWARD,       /*32倍速率快进*/
	ROC_PACE_2X_BACKWARD,       /*2倍速率快退*/
	ROC_PACE_4X_BACKWARD,       /*4倍速率快退*/
	ROC_PACE_8X_BACKWARD,       /*4倍速率快退*/
	ROC_PACE_16X_BACKWARD,       /*16倍速率快退*/
	ROC_PACE_32X_BACKWARD,       /*32倍速率快退*/
	ROC_PACE_2_SLOW_FORWARD,       /*1/2速率慢进*/
	ROC_PACE_4_SLOW_FORWARD,       /*1/4速率慢进*/
	ROC_PACE_8_SLOW_FORWARD,       /*1/8速率慢进*/
	ROC_PACE_16_SLOW_FORWARD,       /*1/16速率慢进*/
	ROC_PACE_2_SLOW_BACKWARD,       /*1/2速率慢退*/
	ROC_PACE_4_SLOW_BACKWARD,       /*1/4速率慢退*/
	ROC_PACE_8_SLOW_BACKWARD,       /*1/8速率慢退*/
	ROC_PACE_16_SLOW_BACKWARD,       /*1/16速率慢退*/
	ROC_PACE_MAX
}Roc_Player_Pace_e;


/*播放文件信息*/
typedef struct {
	UINT32_T u32FileSize;  /*文件大小，以字节为单位*/
	UINT32_T u32Duration;   /*文件播放总时长，单位为秒*/
	UINT32_T u32Bit_rate;   /*文件播放码率，单位为kb/s*/
	UINT32_T reserved[4];   /*保留字节*/
} Roc_Player_Media_Info_t;


/**播放信息*/
typedef struct Roc_Player_Info
{
    UINT32_T  unProgress;                 /**< 播放百分比，0-100 */
    UINT32_T  unPlayeTime;               /**< 已播放时间，单位为秒*/
} Roc_Player_Info_t;


/************************************************************************************
 * 初始化解码器模块
 * 
 * 参数:	
 *		None
 *		
 * 说明: 
 *		初始化播放器模块，在中间件启动时调用，完成:
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_init(void);


/************************************************************************************
 * 去初始化解码器模块
 * 
 * 参数:	
 *		None
 *		
 * 说明:
 *		释放初始化时创建的资源
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_deinit(void);


/************************************************************************************
 * 创建一个播放器实例
 * 
 * 参数:	
 *		@pPlayerParam	创建播放器实例的参数
 *		@phPlayer	用户提供指针，接口调用成功返回播放器实例句柄，否则返回NULL
 *		
 * 说明:
 *		1) 
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS	    成功
 *		ROC_PORTING_PLAYER_FAILURE	    失败  
 *      ROC_PORTING_PLAYER_INVALID_PARAM   参数错误
 ************************************************************************************/
 Roc_Player_ErrCode_e rocme_porting_player_create(Roc_Player_Param_t *pPlayerParam, INT32_T *phPlayer);




/************************************************************************************
 * 设置要播放媒体文件url地址
 * 
 * 参数:	
 *		@hPlayer	调用Roc_Player_Create返回的句柄
 *		@pPlayerSrcInfo	媒体文件信息，详见Roc_Player_Source_t定义
 * 说明:
 *		1) 
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS	    成功
 *		ROC_PORTING_PLAYER_FAILURE	    失败  
 *      ROC_PORTING_PLAYER_INVALID_PARAM   参数错误
 ************************************************************************************/
 Roc_Player_ErrCode_e rocme_porting_player_setsource(INT32_T hPlayer, Roc_Player_Source_t *pPlayerSrcInfo);



/************************************************************************************
 * 启动播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		开始播放媒体，只有当播放器包含有效的媒体资源时，才能执行
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_play(INT32_T hPlayer);



/************************************************************************************
 * 暂停播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		暂停媒体播放，当播放器处于播放状态时，调此接口进入暂停状态；当播放器处于其他状态时，调此接口出错。
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_pause(INT32_T hPlayer);


/************************************************************************************
 * 播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		恢复媒体播放，当播放器处于暂停、快退、快进状态时，调此接口恢复播放；
 *      当播放器处于其他状态时，调此接口出错。
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_resume(INT32_T hPlayer);




/************************************************************************************
 * 停止播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		停止媒体播放，当播放器处于播放状态时，调用此接口可以停止播放
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_stop(INT32_T hPlayer);




/************************************************************************************
 * 跳到指定位置播放,在播放状态下，跳到指定位置播放
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 		@unTime     Seek的时间，单位为秒
 *		
 * 说明:
 *		
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_seek(INT32_T hPlayer, UINT32_T unTime);


/************************************************************************************
 * 设置快退快进
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 		@ePace      播放速率
 *		
 * 说明:
 *		
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_setpace(INT32_T hPlayer, Roc_Player_Pace_e ePace);



/************************************************************************************
 * 获取媒体文件信息
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		@pMediaInfo	媒体文件信息指针
 *		
 * 说明:
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_get_media_info(INT32_T hPlayer, Roc_Player_Media_Info_t *pMediaInfo);



/************************************************************************************
 * 获取播放器信息
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		@pMediaInfo	播放器信息指针，详见Roc_Player_Info_t定义
 *		
 * 说明:
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_get_info(INT32_T hPlayer, Roc_Player_Info_t *pPlayerInfo);



/************************************************************************************
 * 销毁播放器实例
 * 
 * 参数:	
 *		@hPlayer	播放器实例句柄
 *		
 * 说明:
 *		销毁播放器实例
 *
 * 返回值: 
 *		ROC_PORTING_PLAYER_SUCCESS		成功
 *		ROC_PORTING_PLAYER_FAILURE		失败
 *		ROC_PORTING_PLAYER_INVALID_PARAM     参数错误
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_destory(INT32_T hPlayer);


#endif

