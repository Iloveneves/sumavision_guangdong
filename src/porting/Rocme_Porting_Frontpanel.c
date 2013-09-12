/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_frontpanel.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/
#include "hi_type.h"
#include "hi_unf_ecs.h"


#include "porter_rocme.h"

static  HI_U8 DigDisCode[] = {0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09};
	
    //��д��ĸֻ�ܹ���ʾ'C'��'E'��'F'��'H'��'L'��'O'��'P'��'S'��'U'���������ҷֱ��Ӧ�������еķ�0xFFֵ

	#define BIT_A (1<<0)    /*          A           Q2��Ӧ7�� ���б�ʾQ2�������A*/
	#define BIT_B (1<<1)    /*       -------        Q3��Ӧ6�� ���б�ʾQ3�������B*/
	#define BIT_C (1<<2)    /*      |       |       Q4��Ӧ6�� ���б�ʾQ4�������C*/
	#define BIT_D (1<<3)    /*    F |       |  B    Q5��Ӧ4�� ���б�ʾQ5�������D*/
	#define BIT_E (1<<4)    /*       ---G---        Q6��Ӧ3�� ���б�ʾQ6�������E*/
	#define BIT_F (1<<5)    /*      |       |  C    Q7��Ӧ2�� ���б�ʾQ7�������F*/
	#define BIT_G (1<<6)    /*    E |       |	    Q8��Ӧ1�� ���б�ʾQ8�������G*/
	#define BIT_P (1<<7)    /*       ---D---   P    Q9��Ӧ0�� ���б�ʾQ9�������P*/

 static  HI_U8 UCharDisCode[]=
		{
			0x11, // A
			0x01, // B
			0x63, // C
			0x03, // D
			0x61, // E
			0x71, // F
			0x41, // G
			0x91, // H
			0x9f, // I
			0x8f, // J
			0xff, // K
			0xe3, // L
			0xff, // M
			0x13, // N
			0x03, // O
			0x31, // P
			0xff, // Q
			0x11, // R
			0x49, // S
			0x1f, // T
			0x83, // U
			0x83, // V
			0xff, // W
			0xff, // X
			0xff, // Y
			0xff, // Z
		};

static	HI_U8 LCharDisCode[]=
		{
			0x05, // a
			0xc1, // b
			0xe5, // c
			0x85, // d
			0x21, // e
			0x71, // f
			0x09, // g
			0xd1, // h
			0xf7, // i
			0x8f, // j
			0xf1, // k
			0x9f, // l
			0xff, // m
			0xd5, // n
			0xc5, // o
			0x31, // p
			0x19, // q
			0xf5, // r
			0x49, // s
			0xe1, // t
			0xc7, // u
			0xc7, // v
			0xff, // w
			0xff, // x
			0xb1, // y
			0xff, // z
		};
/**************************************************************************
��������: 
            rocme_porting_frontpanel_init
����˵��: 
            ǰ����豸��ʼ�����м����������ʱ���ô˺��������������м��
        ֮ǰ�������Ѿ�������ǰ�����صĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            void
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʼ���ɹ� )
    ʧ�� : -1 �� ������ ( ��ʼ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_frontpanel_init(void)
{
ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_INFO, "+++++++++++++++++++++++++++++++++++++=\r\n");
	HI_U32 display; 
	
	DOFUNC_RETURN(HI_UNF_KEYLED_Init());
	DOFUNC_RETURN(HI_UNF_KEYLED_SelectType(HI_UNF_KEYLED_TYPE_CT1642));
	
	DOFUNC_RETURN(HI_UNF_LED_Open());
	DOFUNC_RETURN(HI_UNF_LED_SetFlashPin(HI_UNF_KEYLED_LIGHT_NONE));
	DOFUNC_RETURN(HI_UNF_LED_SetFlashFreq(HI_UNF_KEYLED_LEVEL_1));
	
	DOFUNC_RETURN(HI_UNF_KEY_Open());
	DOFUNC_RETURN(HI_UNF_KEY_IsKeyUp(1));
	DOFUNC_RETURN(HI_UNF_KEY_IsRepKey(1));


	DOFUNC_RETURN( HI_UNF_IR_Open() );
	DOFUNC_RETURN( HI_UNF_IR_SetCodeType(HI_UNF_IR_CODE_NEC_SIMPLE) ) ;
	DOFUNC_RETURN( HI_UNF_IR_EnableKeyUp(HI_TRUE) ) ;
	DOFUNC_RETURN( HI_UNF_IR_SetRepKeyTimeoutAttr(108) ) ;
	DOFUNC_RETURN( HI_UNF_IR_EnableRepKey(HI_TRUE) ) ;
	DOFUNC_RETURN( HI_UNF_IR_Enable(HI_TRUE) ) ;
	display =  0xffffffff;

	if(HI_UNF_LED_Display(display) != 0)
	{
		return ROC_ERR;
	}

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_frontpanel_show_string
����˵��: 
            ǰ�����ʾ�ַ������ܣ�Ҫ�������ṩ��ʾ4���ַ�������֧�������ַ�:
       " 0 1 2 3 4 5 6 7 8 9 A E F L N O P S T U V a d g i l n o r t u v "��
����˵����
    ���������
            [ *pBuf   ] : �ַ���ͷָ��
            [ len     ] : �ַ������ȣ���󲻻ᳬ��4
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʾ�ַ����ɹ� )
    ʧ�� : -1 �� ������ ( ��ʾ�ַ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_string(CHAR_T *pBuf,UINT32_T len)
{
ROCME_TEST_PRINT	
	if (pBuf == NULL)
	return ROC_ERR;

    HI_S32 s32Index = 0, s32Ret = 0;
    HI_U8 u8Value[5] = {0};

    HI_U8 *u8Data = (HI_U8*)pBuf;
	
    printf("[%s] call, len = %d arg = %s\n", __FUNCTION__, len,pBuf);
    
	int bShowTime = 0;
	int i = 0;
	int nLength = strlen(u8Data);

    for (s32Index = 0; s32Index < nLength; s32Index++)
    {
        if(isupper(u8Data[s32Index]))
        {
            u8Value[i] = UCharDisCode[u8Data[s32Index]-'A'];
        }
        else if(islower(u8Data[s32Index]))
        {
            u8Value[i] = LCharDisCode[u8Data[s32Index]-'a'];
        }
        else if(isdigit(u8Data[s32Index]))
        {
            u8Value[i] = DigDisCode[u8Data[s32Index]-'0'];
        }
        else
        {
            u8Value[i] = DigDisCode[0];     
        }
		i ++;

		if(i >= 4 )
		{
			break;
		}
    } 

	HI_U32 n_display = 0;

	n_display = ~((u8Value[3]<<24)|(u8Value[2]<<16)|(u8Value[1]<<8)|(u8Value[0]));
	s32Ret = HI_UNF_LED_Display(n_display);
	if(s32Ret != HI_SUCCESS)
	{
		return ROC_ERR;
	}

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_frontpanel_show_2point
����˵��: 
            ǰ�������ʾʱ��ָ���( : )���ܡ�
����˵����
    ���������
            [ is_show   ] : �Ƿ���ʾʱ��ָ�����ʶ
                            ROC_TRUE   -  ��ʾ
                            ROC_FALSE  -  ����ʾ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʾʱ��ָ����ɹ� )
    ʧ�� : -1 �� ������ ( ��ʾʱ��ָ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_2point(ROC_BOOL is_show)
{
ROCME_TEST_PRINT
#if 0//�ײ㻹û�����
	if( HI_UNF_LED_DisplayColon(is_show)!= HI_SUCCESS)
	{
		return ROC_ERR;
	}
#endif
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_frontpanel_show_led
����˵��: 
            ǰ���LED�ƿ��ƹ��ܣ�����0����tuner����ָʾ�ƣ�1�����Դָʾ�ơ�
����˵����
    ���������
            [ len_index   ] : LED�������ţ�0����tuner����ָʾ�ƣ�1�����Դָʾ��
            [ on_off      ] : �Ƿ���ʾLED�Ʊ�ʶ
                              ROC_TRUE   -  ��ʾ
                              ROC_FALSE  -  ����ʾ                        
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʾʱ��ָ����ɹ� )
    ʧ�� : -1 �� ������ ( ��ʾʱ��ָ���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_led(UINT8_T len_index,ROC_BOOL on_off)
{
ROCME_TEST_PRINT
	if(len_index == 0)
	{
		if (HI_UNF_LED_LockSignal(on_off) != HI_SUCCESS)
		{
			return ROC_ERR;
		}
	}

	if(len_index == 1)
	{
		
	}

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_frontpanel_show_time
����˵��: 
            ǰ�����ʾʱ�书�ܣ�Ҫ����ݴ���Ŀ�ʼʱ�䣬ǰ��忪ʼ��ʾʱ�䣬
        ֱ���ٴε��ô˺����رգ���ʾʱ���ڼ�ǰ��岻����Ӧ�����ַ�������
        ������Ҫ��ʼ��ʾʱ��Ϊ18:20����on_off = ROC_TRUE,*time24h = "1820"��
        ����ʾʱ��ɹ���ʼ��ǰ���Ӧ��ʾ"18:20"�����Ұ���/���ӵ�Ƶ�ʽ���ˢ
        �£������ʾ"18:21"��"18:22"... ... ������Ҫ����ʱ����ʾʱ���������
        on_off = ROC_FALSE,*time24h = NULL�����⣬��ʱǰ�����Ҫ����ʾ��ա�
����˵����
    ���������
            [ on_off      ] : �Ƿ���ʾʱ���ʶ��ֻ�е�ROC_TRUEʱ������*time24h
                          �������á�
                              ROC_TRUE   -  ��ʾ
                              ROC_FALSE  -  ����ʾ                               
            [ *time24h    ] : ʱ���ַ���ͷָ�룬��on_off=ROC_TRUEʱ��Ч
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����/�ر�ʱ����ʾ�ɹ� )
    ʧ�� : -1 �� ������ ( ����/�ر�ʱ����ʾʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_time(ROC_BOOL on_off,CHAR_T *time24h)
{
ROCME_TEST_PRINT
	HI_UNF_KEYLED_TIME_S stLedTime;
	
	if( ROC_TRUE != on_off || time24h == NULL)
	{
		return ROC_FALSE;
	}

	stLedTime.u32Hour	= (time24h[0] - '0') * 10 + (time24h[1] - '0');
	stLedTime.u32Minute = (time24h[2] - '0') * 10 + (time24h[3] - '0');
	
	if(HI_UNF_LED_DisplayTime(stLedTime) != HI_SUCCESS)
	{
		return ROC_ERR;
	}

	return ROC_OK;
		
}

