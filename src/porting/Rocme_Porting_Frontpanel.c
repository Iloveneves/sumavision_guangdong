/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_frontpanel.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
*************************************************************************/
#include "hi_type.h"
#include "hi_unf_ecs.h"


#include "porter_rocme.h"

static  HI_U8 DigDisCode[] = {0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09};
	
    //大写字母只能够显示'C'、'E'、'F'、'H'、'L'、'O'、'P'、'S'、'U'，从左至右分别对应此数组中的非0xFF值

	#define BIT_A (1<<0)    /*          A           Q2对应7， 此行表示Q2接数码管A*/
	#define BIT_B (1<<1)    /*       -------        Q3对应6， 此行表示Q3接数码管B*/
	#define BIT_C (1<<2)    /*      |       |       Q4对应6， 此行表示Q4接数码管C*/
	#define BIT_D (1<<3)    /*    F |       |  B    Q5对应4， 此行表示Q5接数码管D*/
	#define BIT_E (1<<4)    /*       ---G---        Q6对应3， 此行表示Q6接数码管E*/
	#define BIT_F (1<<5)    /*      |       |  C    Q7对应2， 此行表示Q7接数码管F*/
	#define BIT_G (1<<6)    /*    E |       |	    Q8对应1， 此行表示Q8接数码管G*/
	#define BIT_P (1<<7)    /*       ---D---   P    Q9对应0， 此行表示Q9接数码管P*/

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
函数名称: 
            rocme_porting_frontpanel_init
功能说明: 
            前面板设备初始化，中间件会在启动时调用此函数，若在启动中间件
        之前机顶盒已经做好了前面板相关的初始化，此函数可以实现为空，直接返回0。
参数说明：
    输入参数：
            void
    输出参数：
            无
返    回： 
    成功 : 0            ( 初始化成功 )
    失败 : -1 或 错误码 ( 初始化失败 )
修改记录：
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
函数名称: 
            rocme_porting_frontpanel_show_string
功能说明: 
            前面板显示字符串功能，要求至少提供显示4个字符，至少支持如下字符:
       " 0 1 2 3 4 5 6 7 8 9 A E F L N O P S T U V a d g i l n o r t u v "。
参数说明：
    输入参数：
            [ *pBuf   ] : 字符串头指针
            [ len     ] : 字符串长度，最大不会超过4
    输出参数：
            无
返    回： 
    成功 : 0            ( 显示字符串成功 )
    失败 : -1 或 错误码 ( 显示字符串失败 )
修改记录：
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
函数名称: 
            rocme_porting_frontpanel_show_2point
功能说明: 
            前面板上显示时间分隔符( : )功能。
参数说明：
    输入参数：
            [ is_show   ] : 是否显示时间分隔符标识
                            ROC_TRUE   -  显示
                            ROC_FALSE  -  不显示
    输出参数：
            无
返    回： 
    成功 : 0            ( 显示时间分隔符成功 )
    失败 : -1 或 错误码 ( 显示时间分隔符失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_frontpanel_show_2point(ROC_BOOL is_show)
{
ROCME_TEST_PRINT
#if 0//底层还没有添加
	if( HI_UNF_LED_DisplayColon(is_show)!= HI_SUCCESS)
	{
		return ROC_ERR;
	}
#endif
	return ROC_OK;
}

/**************************************************************************
函数名称: 
            rocme_porting_frontpanel_show_led
功能说明: 
            前面板LED灯控制功能，索引0代表tuner锁定指示灯，1代表电源指示灯。
参数说明：
    输入参数：
            [ len_index   ] : LED灯索引号，0代表tuner锁定指示灯，1代表电源指示灯
            [ on_off      ] : 是否显示LED灯标识
                              ROC_TRUE   -  显示
                              ROC_FALSE  -  不显示                        
    输出参数：
            无
返    回： 
    成功 : 0            ( 显示时间分隔符成功 )
    失败 : -1 或 错误码 ( 显示时间分隔符失败 )
修改记录：
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
函数名称: 
            rocme_porting_frontpanel_show_time
功能说明: 
            前面板显示时间功能，要求根据传入的开始时间，前面板开始显示时间，
        直至再次调用此函数关闭，显示时间期间前面板不必响应其他字符串请求。
        例如若要求开始显示时间为18:20，则on_off = ROC_TRUE,*time24h = "1820"，
        当显示时间成功开始后，前面板应显示"18:20"，并且按照/分钟的频率进行刷
        新，逐次显示"18:21"、"18:22"... ... ，当需要结束时间显示时，传入参数
        on_off = ROC_FALSE,*time24h = NULL或任意，此时前面板需要将显示清空。
参数说明：
    输入参数：
            [ on_off      ] : 是否显示时间标识，只有当ROC_TRUE时，参数*time24h
                          才起作用。
                              ROC_TRUE   -  显示
                              ROC_FALSE  -  不显示                               
            [ *time24h    ] : 时间字符串头指针，当on_off=ROC_TRUE时有效
    输出参数：
            无
返    回： 
    成功 : 0            ( 开启/关闭时间显示成功 )
    失败 : -1 或 错误码 ( 开启/关闭时间显示失败 )
修改记录：
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

