/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_event.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
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
			return(ROC_IRKEY_POWER);			//��/�أ�
		case 0x47514144ae:
			return(ROC_IRKEY_VOLUME_MUTE);	//������
		case 0x47524144ad:
			return(ROC_IRKEY_TRACK);	//������
		case 0x4768414497:
			return(ROC_IRKEY_VOLUME_UP);		//����++
		case 0x4769414496:
			return(ROC_IRKEY_VOLUME_DOWN);	//����--
		case 0x4766414499:
			return(ROC_IRKEY_PAGE_UP);		//��ҳ��
		case 0x4767414498:
			return(ROC_IRKEY_PAGE_DOWN);	//��ҳ��
		case 0x47534144ac:
//			return(ROC_IRKEY_FAVORITE);		//ϲ����

		case 0x47544144ab:
			return(ROC_IRKEY_MENU);			//�˵���
		case 0x67344164cb:
			return(ROC_IRKEY_HOMEPAGE);		//��ҳ��
			
//�ʼ���
		case 0x00415347:
			return(ROC_IRKEY_MAIL);			//
		case 0x47554144aa:
			return(ROC_IRKEY_TV_RADIO);	//��Ŀ��
		case 0x47574144a8:
			return(ROC_IRKEY_EPG);			//��Ϣ��
		case 0x476041449f:
			return(ROC_IRKEY_UP);				//�ϣ�
		case 0x476141449e:
			return(ROC_IRKEY_DOWN);			//��
		case 0x476241449d:
			return(ROC_IRKEY_LEFT);			//��
		case 0x476341449c:
			return(ROC_IRKEY_RIGHT);			//��
		case 0x476441449b:
			return(ROC_IRKEY_SELECT);			//ȷ����			

		

		case 0x477541448a:
		case 0x67494164b6:
			return(ROC_IRKEY_RED);		//�죻
		case 0x4776414489:
		case 0x674a4164b5:
			return(ROC_IRKEY_GREEN);		//�̣�
		case 0x4777414488:
		case 0x674b4164b4:
			return(ROC_IRKEY_YELLOW);	//��
		case 0x4778414487:
		case 0x674c4164b3:
			return(ROC_IRKEY_BLUE);		//��
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
			return(ROC_IRKEY_EXIT);		//�˳���
		case 0x47584144a7:
		case 0x67384164c7:
			return(ROC_IRKEY_BACK);		//���أ�
 	
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
				/* �����ǰ�յ�����hold�����ҵ�ǰΪrepeat״̬�����͸ü�ֵ�����򲻷��� */
				if (HI_FALSE == bRepeatKey)
				{
					bRepeatKey = HI_TRUE;
					continue;
				}
			}
			else
			{
				bRepeatKey = HI_FALSE;

				/* ���ε�up��ֵ */
				if (2 == u32PressStatus)
				{
					continue;
				}
			}

			/*���ݽ��յ���keyֵ���Ͳ�ͬ��Ϣ��ipanel�м��*/
			/*������Ŀ��ʵ��������е���*/

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
��������: 
            rocme_porting_event_register
����˵��: 
            �������ע��һ�������¼��ļ���Ҫ��
����˵����
    ���������
            [ evt_param   ] : �¼����������������ص������Լ�˽�в���
    ���������
            [ handler     ] : ��ע������Ŀ��ƾ��
��    �أ� 
    �ɹ� : 0            ( ע����������¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע����������¼�ʧ�� )
�޸ļ�¼��
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

	//��㸳��ֵ��������Ե�ʱ���޸�
	hEventHandle = 0x001;
	
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_event_unregister
����˵��: 
            �������ע��һ�������¼��ļ���Ҫ��
����˵����
    ���������
            [ handler     ] : ��Ҫע������ע������Ŀ��ƾ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ע�����������¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע�����������¼�ʧ�� )
�޸ļ�¼��
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
��������: 
            romce_porting_mouse_register
����˵��: 
            �������ע��һ������¼��ļ���Ҫ��
����˵����
    ���������
            [ evt_param   ] : ����¼����������������ص������Լ�˽�в���
    ���������
            [ handler     ] : ��ע���������Ŀ��ƾ��
��    �أ� 
    �ɹ� : 0            ( ע���������¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע���������¼�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_mouse_register( const Roc_Mouse_Param_t mouse_param,UINT32_T *handler )
{
ROCME_TEST_PRINT
	return ROC_OK;

}

/**************************************************************************
��������: 
            rocme_porting_mouse_unregister
����˵��: 
            �������ע��һ������¼��ļ���Ҫ��
����˵����
    ���������
            [ handler     ] : ��Ҫע������ע������Ŀ��ƾ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ע����������¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע����������¼�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_mouse_unregister( const UINT32_T handler )
{
ROCME_TEST_PRINT
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_mouse_set_coordinate
����˵��: 
            �������ָ��ĵ�ǰ���꣬����Ϊ(0,0)����
����˵����
    ���������
            [ x     ] : ���ĺ�����
            [ y     ] : ����������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����������ɹ� )
    ʧ�� : -1 �� ������ ( �����������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_mouse_set_coordinate( const UINT32_T x,const UINT32_T y )
{
ROCME_TEST_PRINT
	return ROC_OK;

}

/**************************************************************************
��������: 
            rocme_porting_keyboard_type_set
����˵��: 
            ѡ��ң��������
����˵����
    ���������
            [ keyboard_type     ] : ң��������
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����ң�������ͳɹ� )
    ʧ�� : -1 �� ������ ( ����ң��������ʧ�� )
�޸ļ�¼��
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
