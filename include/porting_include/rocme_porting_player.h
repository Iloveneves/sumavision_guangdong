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
/*����playerģ�������*/
typedef enum
{
	ROC_PORTING_PLAYER_SUCCESS = 0,
	ROC_PORTING_PLAYER_FAILURE,       
	ROC_PORTING_PLAYER_INVALID_PARAM,
	ROC_PORTING_PLAYER_NOT_SUPPORT,        /*��֧�ֵĸ�ʽ*/
	ROC_PORTING_PLAYER_UNKOWN
}Roc_Player_ErrCode_e;


/** �������򿪲��� */
typedef struct
{
	UINT32_T x, y, w, h;   /*��Ƶ������ڵ����꼰���*/
	UINT32_T reserved[2];
} Roc_Player_Param_t;


/*�����ļ�����*/
typedef struct
{
    char aszSrcUrl[ROC_PLAYER_MAX_PATH_LEN];          /*ý���ļ�·��*/
} Roc_Player_Source_t;



/*�ļ��Ĳ�������*/
typedef enum{
	ROC_PACE_1X_FORWARD,        /*ǰ����Ĭ��ֵ*/
	ROC_PACE_1X_BACKWARD,       /*����*/
	ROC_PACE_2X_FORWARD,       /*2�����ʿ��*/
	ROC_PACE_4X_FORWARD,       /*4�����ʿ��*/
	ROC_PACE_8X_FORWARD,       /*8�����ʿ��*/
	ROC_PACE_16X_FORWARD,       /*16�����ʿ��*/
	ROC_PACE_32X_FORWARD,       /*32�����ʿ��*/
	ROC_PACE_2X_BACKWARD,       /*2�����ʿ���*/
	ROC_PACE_4X_BACKWARD,       /*4�����ʿ���*/
	ROC_PACE_8X_BACKWARD,       /*4�����ʿ���*/
	ROC_PACE_16X_BACKWARD,       /*16�����ʿ���*/
	ROC_PACE_32X_BACKWARD,       /*32�����ʿ���*/
	ROC_PACE_2_SLOW_FORWARD,       /*1/2��������*/
	ROC_PACE_4_SLOW_FORWARD,       /*1/4��������*/
	ROC_PACE_8_SLOW_FORWARD,       /*1/8��������*/
	ROC_PACE_16_SLOW_FORWARD,       /*1/16��������*/
	ROC_PACE_2_SLOW_BACKWARD,       /*1/2��������*/
	ROC_PACE_4_SLOW_BACKWARD,       /*1/4��������*/
	ROC_PACE_8_SLOW_BACKWARD,       /*1/8��������*/
	ROC_PACE_16_SLOW_BACKWARD,       /*1/16��������*/
	ROC_PACE_MAX
}Roc_Player_Pace_e;


/*�����ļ���Ϣ*/
typedef struct {
	UINT32_T u32FileSize;  /*�ļ���С�����ֽ�Ϊ��λ*/
	UINT32_T u32Duration;   /*�ļ�������ʱ������λΪ��*/
	UINT32_T u32Bit_rate;   /*�ļ��������ʣ���λΪkb/s*/
	UINT32_T reserved[4];   /*�����ֽ�*/
} Roc_Player_Media_Info_t;


/**������Ϣ*/
typedef struct Roc_Player_Info
{
    UINT32_T  unProgress;                 /**< ���Űٷֱȣ�0-100 */
    UINT32_T  unPlayeTime;               /**< �Ѳ���ʱ�䣬��λΪ��*/
} Roc_Player_Info_t;


/************************************************************************************
 * ��ʼ��������ģ��
 * 
 * ����:	
 *		None
 *		
 * ˵��: 
 *		��ʼ��������ģ�飬���м������ʱ���ã����:
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_init(void);


/************************************************************************************
 * ȥ��ʼ��������ģ��
 * 
 * ����:	
 *		None
 *		
 * ˵��:
 *		�ͷų�ʼ��ʱ��������Դ
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_deinit(void);


/************************************************************************************
 * ����һ��������ʵ��
 * 
 * ����:	
 *		@pPlayerParam	����������ʵ���Ĳ���
 *		@phPlayer	�û��ṩָ�룬�ӿڵ��óɹ����ز�����ʵ����������򷵻�NULL
 *		
 * ˵��:
 *		1) 
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS	    �ɹ�
 *		ROC_PORTING_PLAYER_FAILURE	    ʧ��  
 *      ROC_PORTING_PLAYER_INVALID_PARAM   ��������
 ************************************************************************************/
 Roc_Player_ErrCode_e rocme_porting_player_create(Roc_Player_Param_t *pPlayerParam, INT32_T *phPlayer);




/************************************************************************************
 * ����Ҫ����ý���ļ�url��ַ
 * 
 * ����:	
 *		@hPlayer	����Roc_Player_Create���صľ��
 *		@pPlayerSrcInfo	ý���ļ���Ϣ�����Roc_Player_Source_t����
 * ˵��:
 *		1) 
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS	    �ɹ�
 *		ROC_PORTING_PLAYER_FAILURE	    ʧ��  
 *      ROC_PORTING_PLAYER_INVALID_PARAM   ��������
 ************************************************************************************/
 Roc_Player_ErrCode_e rocme_porting_player_setsource(INT32_T hPlayer, Roc_Player_Source_t *pPlayerSrcInfo);



/************************************************************************************
 * ��������
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		��ʼ����ý�壬ֻ�е�������������Ч��ý����Դʱ������ִ��
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_play(INT32_T hPlayer);



/************************************************************************************
 * ��ͣ����
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		��ͣý�岥�ţ������������ڲ���״̬ʱ�����˽ӿڽ�����ͣ״̬������������������״̬ʱ�����˽ӿڳ���
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_pause(INT32_T hPlayer);


/************************************************************************************
 * ����
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		�ָ�ý�岥�ţ���������������ͣ�����ˡ����״̬ʱ�����˽ӿڻָ����ţ�
 *      ����������������״̬ʱ�����˽ӿڳ���
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_resume(INT32_T hPlayer);




/************************************************************************************
 * ֹͣ����
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		ֹͣý�岥�ţ������������ڲ���״̬ʱ�����ô˽ӿڿ���ֹͣ����
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_stop(INT32_T hPlayer);




/************************************************************************************
 * ����ָ��λ�ò���,�ڲ���״̬�£�����ָ��λ�ò���
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 		@unTime     Seek��ʱ�䣬��λΪ��
 *		
 * ˵��:
 *		
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_seek(INT32_T hPlayer, UINT32_T unTime);


/************************************************************************************
 * ���ÿ��˿��
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 		@ePace      ��������
 *		
 * ˵��:
 *		
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_setpace(INT32_T hPlayer, Roc_Player_Pace_e ePace);



/************************************************************************************
 * ��ȡý���ļ���Ϣ
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		@pMediaInfo	ý���ļ���Ϣָ��
 *		
 * ˵��:
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_get_media_info(INT32_T hPlayer, Roc_Player_Media_Info_t *pMediaInfo);



/************************************************************************************
 * ��ȡ��������Ϣ
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		@pMediaInfo	��������Ϣָ�룬���Roc_Player_Info_t����
 *		
 * ˵��:
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_get_info(INT32_T hPlayer, Roc_Player_Info_t *pPlayerInfo);



/************************************************************************************
 * ���ٲ�����ʵ��
 * 
 * ����:	
 *		@hPlayer	������ʵ�����
 *		
 * ˵��:
 *		���ٲ�����ʵ��
 *
 * ����ֵ: 
 *		ROC_PORTING_PLAYER_SUCCESS		�ɹ�
 *		ROC_PORTING_PLAYER_FAILURE		ʧ��
 *		ROC_PORTING_PLAYER_INVALID_PARAM     ��������
 ************************************************************************************/
Roc_Player_ErrCode_e rocme_porting_player_destory(INT32_T hPlayer);


#endif

