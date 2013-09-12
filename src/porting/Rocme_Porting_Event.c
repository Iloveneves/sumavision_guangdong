/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_event.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <linux/input.h>

#include "hi_unf_ecs.h"

#include "porter_rocme.h"

#ifdef __cplusplus
extern "C"
{
#endif


static Roc_Evt_Param_t hisi_event_Param ;

static HI_BOOL	rocme_input_irrunflag = HI_FALSE;
static HI_BOOL	rocme_input_keyrunflag = HI_FALSE;

static pthread_t      rocme_input_irthread;
static pthread_t      rocme_input_keythread;

static HI_HANDLE	hEventHandle;

HI_S32 rocme_porting_input_mapkey(HI_U64 u32Key)
{
ROCME_TEST_PRINT

	HI_U32 i_t=0;

//=============================	test===============
	char loader_test[10];
	printf("**********************the key value = %lu\r\n",u32Key);
	switch(u32Key)
	{
		
		case 0x47e6414419:
			break;

		case 0x47504144af:
			return(ROC_IRKEY_POWER);			//开/关；
		case 0x47514144ae:
			return(ROC_IRKEY_VOLUME_MUTE);	//静音；
		case 0x47524144ad:
			return(ROC_IRKEY_TRACK);	//声道；
		case 0x4768414497:
			return(ROC_IRKEY_VOLUME_UP);		//音量++
		case 0x4769414496:
			return(ROC_IRKEY_VOLUME_DOWN);	//音量--
		case 0x4766414499:
			return(ROC_IRKEY_PAGE_UP);		//上页；
		case 0x4767414498:
			return(ROC_IRKEY_PAGE_DOWN);	//下页；
		case 0x47534144ac:
//			return(ROC_IRKEY_FAVORITE);		//喜爱；

		case 0x47544144ab:
			return(ROC_IRKEY_MENU);			//菜单键
		case 0x67344164cb:
			return(ROC_IRKEY_HOMEPAGE);		//主页；
			
//邮件；
		case 0x00415347:
			return(ROC_IRKEY_MAIL);			//
		case 0x47554144aa:
			return(ROC_IRKEY_TV_RADIO);	//节目；
		case 0x47574144a8:
			return(ROC_IRKEY_EPG);			//信息；
		case 0x476041449f:
			return(ROC_IRKEY_UP);				//上；
		case 0x476141449e:
			return(ROC_IRKEY_DOWN);			//下
		case 0x476241449d:
			return(ROC_IRKEY_LEFT);			//左
		case 0x476341449c:
			return(ROC_IRKEY_RIGHT);			//右
		case 0x476441449b:
			return(ROC_IRKEY_SELECT);			//确定；			

		

		case 0x477541448a:
		case 0x67494164b6:
			return(ROC_IRKEY_RED);		//红；
		case 0x4776414489:
		case 0x674a4164b5:
			return(ROC_IRKEY_GREEN);		//绿；
		case 0x4777414488:
		case 0x674b4164b4:
			return(ROC_IRKEY_YELLOW);	//黄
		case 0x4778414487:
		case 0x674c4164b3:
			return(ROC_IRKEY_BLUE);		//蓝
		case 0x47204144df:
		case 0x67104164ef:
			return(ROC_IRKEY_NUM0);		///0
		case 0x47214144de:
		case 0x67114164ee:
			return(ROC_IRKEY_NUM1);		///1
		case 0x47224144dd:
		case 0x67124164ed:
			return(ROC_IRKEY_NUM2);		///2
		case 0x47234144dc:
		case 0x67134164ec:	
			return(ROC_IRKEY_NUM3);		//3//3
		case 0x47244144db:
		case 0x67144164eb:
			return(ROC_IRKEY_NUM4);		//4//4
		case 0x47254144da:
		case 0x67154164ea:
			return(ROC_IRKEY_NUM5);		//5
		case 0x47264144d9:
		case 0x67164164e9:
			return(ROC_IRKEY_NUM6);		//6
		case 0x47274144d8:
		case 0x67174164e8:	
			return(ROC_IRKEY_NUM7);		//7
		case 0x47284144d7:
		case 0x67184164e7:	
			return(ROC_IRKEY_NUM8);		//8
		case 0x47294144d6:
		case 0x67194164e6:	
			return(ROC_IRKEY_NUM9);		//999
		case 0x47194144e6:
			return(ROC_IRKEY_ASTERISK);	//*****
		case 0x47594144a6:
			return(ROC_IRKEY_EXIT);		//退出；
		case 0x47584144a7:
		case 0x67384164c7:
			return(ROC_IRKEY_BACK);		//返回；
 	
 		default:
			return(ROC_IRKEY_INVALID);

		}
	
}


static HI_VOID rocme_porting_input_irthread(HI_VOID *pParam)
{
ROCME_TEST_PRINT

	HI_S32   	s32ret;
	HI_U32 	u32PressStatus;
	HI_U64	u32KeyId;
	static HI_U32 repeat_count = 0;
	HI_UNF_IR_PROTOCOL_E Protocol;

	while (rocme_input_irrunflag) 
	{
		
		s32ret = HI_UNF_IR_GetValue(&u32PressStatus, &u32KeyId, 100);
		
		if (HI_SUCCESS == s32ret)
		{
			
			printf("=====the status = %d\n",u32PressStatus);
			if(hisi_event_Param.callback != NULL)
			{

				if(HI_UNF_KEY_STATUS_DOWN == u32PressStatus)
				{
					(*(hisi_event_Param.callback))(0, ROC_INPUT_REMOTECTRL,rocme_porting_input_mapkey(u32KeyId),ROC_KEY_DOWN);
					
					(*(hisi_event_Param.callback))(0, ROC_INPUT_REMOTECTRL,rocme_porting_input_mapkey(u32KeyId),ROC_KEY_PRESS);
				}
				else
				{				
					(*(hisi_event_Param.callback))(0, ROC_INPUT_REMOTECTRL,rocme_porting_input_mapkey(u32KeyId),ROC_KEY_RELEASE);
				}
			}
		}
		else
		{
			usleep(100);			
		}
	}
}



static HI_VOID rocme_porting_input_keythread(HI_VOID *pParam)
{
ROCME_TEST_PRINT
    HI_U32 u32PressStatus,keyId;
    HI_S32 ret = -1;
    HI_BOOL bRepeatKey = HI_FALSE;

	while(rocme_input_keyrunflag)
	{
		ret = HI_UNF_KEY_GetValue(&u32PressStatus, &keyId);

		if (HI_SUCCESS == ret)
		{
			if (1 == u32PressStatus)
			{
					continue;
				/* 如果当前收到的是hold键，且当前为repeat状态，则发送该键值，否则不发送 */
				if (HI_FALSE == bRepeatKey)
				{
					bRepeatKey = HI_TRUE;
					continue;
				}
			}
			else
			{
				bRepeatKey = HI_FALSE;

				/* 屏蔽掉up键值 */
				if (2 == u32PressStatus)
				{
					continue;
				}
			}

			/*根据接收到的key值发送不同消息给ipanel中间件*/
			/*根据项目的实际需求进行调整*/

			printf("\n +++ KEY VALUE =0x%x u32PressStatus =0x%x +++\n", keyId,u32PressStatus);

			
			switch(keyId)
			{
			case 0xe:
				keyId	= ROC_IRKEY_RIGHT;
				break;
			case 0xb:
				keyId	= ROC_IRKEY_MENU;
				break;
			case 0xc:
				keyId	= ROC_IRKEY_SELECT;
				break;
			case 0xf:
				keyId	= ROC_IRKEY_UP;
				break;
			case 0xd:
				keyId	= ROC_IRKEY_LEFT;
				break;
			case 0x10:
				keyId	= ROC_IRKEY_DOWN;
				break;
			case 0x7:	
				keyId	= ROC_IRKEY_EXIT;
			default:
				break;
			}

			if(hisi_event_Param.callback)
			{
				(*(hisi_event_Param.callback))(0, ROC_INPUT_REMOTECTRL,keyId,ROC_KEY_DOWN);
					
				(*(hisi_event_Param.callback))(0, ROC_INPUT_REMOTECTRL,keyId,ROC_KEY_PRESS);
				(*(hisi_event_Param.callback))(0, ROC_INPUT_REMOTECTRL,keyId,ROC_KEY_RELEASE);
			}

		}
		else
		{
			usleep(500);
		}

	}

	return;
}
/**************************************************************************
函数名称: 
            rocme_porting_event_register
功能说明: 
            向机顶盒注册一个按键事件的监听要求
参数说明：
    输入参数：
            [ evt_param   ] : 事件监听参数，包括回调函数以及私有参数
    输出参数：
            [ handler     ] : 此注册监听的控制句柄
返    回： 
    成功 : 0            ( 注册监听按键事件成功 )
    失败 : -1 或 错误码 ( 注册监听按键事件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_event_register(const Roc_Evt_Param_t evt_param,UINT32_T *handler)
{
ROCME_TEST_PRINT
	
	hisi_event_Param.callback = evt_param.callback;
	hisi_event_Param.cb_param = evt_param.cb_param;


	rocme_input_irrunflag = HI_TRUE;
	if ( pthread_create( &rocme_input_irthread, NULL, (HI_VOID *)(rocme_porting_input_irthread), 0 ) != 0 )
	{
	
		return ROC_ERR;
	}

	rocme_input_keyrunflag = HI_FALSE;
	if ( pthread_create( &rocme_input_keythread, NULL, (HI_VOID *)(rocme_porting_input_keythread), 0 ) != 0 )
	{
		return ROC_ERR;
	}

	//随便赋的值，具体调试的时候修改
	hEventHandle = 0x001;
	
	return ROC_OK;
}

/**************************************************************************
函数名称: 
            rocme_porting_event_unregister
功能说明: 
            向机顶盒注销一个按键事件的监听要求
参数说明：
    输入参数：
            [ handler     ] : 需要注销的已注册监听的控制句柄
    输出参数：
            无
返    回： 
    成功 : 0            ( 注销监听按键事件成功 )
    失败 : -1 或 错误码 ( 注销监听按键事件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_event_unregister(const UINT32_T handler)
{
ROCME_TEST_PRINT
	if (rocme_input_irrunflag)
	{
		rocme_input_irrunflag = 0;
		pthread_join(rocme_input_irthread, NULL);
	}

	if (rocme_input_keyrunflag)
	{
		rocme_input_keyrunflag = 0;
		pthread_join(rocme_input_keythread, NULL);
	}

	hEventHandle = 0;

	return ROC_OK;
}

/**************************************************************************
函数名称: 
            romce_porting_mouse_register
功能说明: 
            向机顶盒注册一个鼠标事件的监听要求
参数说明：
    输入参数：
            [ evt_param   ] : 鼠标事件监听参数，包括回调函数以及私有参数
    输出参数：
            [ handler     ] : 此注册鼠标监听的控制句柄
返    回： 
    成功 : 0            ( 注册监听鼠标事件成功 )
    失败 : -1 或 错误码 ( 注册监听鼠标事件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_mouse_register( const Roc_Mouse_Param_t mouse_param,UINT32_T *handler )
{
ROCME_TEST_PRINT
	return ROC_OK;

}

/**************************************************************************
函数名称: 
            rocme_porting_mouse_unregister
功能说明: 
            向机顶盒注销一个鼠标事件的监听要求
参数说明：
    输入参数：
            [ handler     ] : 需要注销的已注册监听的控制句柄
    输出参数：
            无
返    回： 
    成功 : 0            ( 注销监听鼠标事件成功 )
    失败 : -1 或 错误码 ( 注销监听鼠标事件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_mouse_unregister( const UINT32_T handler )
{
ROCME_TEST_PRINT
	return ROC_OK;
}

/**************************************************************************
函数名称: 
            rocme_porting_mouse_set_coordinate
功能说明: 
            设置鼠标指针的当前坐标，左上为(0,0)坐标
参数说明：
    输入参数：
            [ x     ] : 鼠标的横坐标
            [ y     ] : 鼠标的纵坐标
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置鼠标坐标成功 )
    失败 : -1 或 错误码 ( 设置鼠标坐标失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_mouse_set_coordinate( const UINT32_T x,const UINT32_T y )
{
ROCME_TEST_PRINT
	return ROC_OK;

}

/**************************************************************************
函数名称: 
            rocme_porting_keyboard_type_set
功能说明: 
            选择遥控器类型
参数说明：
    输入参数：
            [ keyboard_type     ] : 遥控器类型
    输出参数：
            无
返    回： 
    成功 : 0            ( 设置遥控器类型成功 )
    失败 : -1 或 错误码 ( 设置遥控器类型失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_keyboard_type_set(const Roc_KeyBoard_Type_e keyboard_type)
{
ROCME_TEST_PRINT
	if(keyboard_type < ROC_KEYBOARD_TYPE_DEFAULT || keyboard_type > ROC_KEYBOARD_TYPE_NUM)
	{
		return ROC_ERR;
	}
	
	if(HI_UNF_IR_SetCodeType(keyboard_type)!= HI_SUCCESS)
	{
		return ROC_OK;
	}

	return ROC_ERR;
}


#ifdef __cplusplus
}
#endif
