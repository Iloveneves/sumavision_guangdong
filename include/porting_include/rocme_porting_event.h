/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_event.h

Author      : DSM

Description : The poriting interface & macro definition for EVENT module.
              ���ļ����¼�ֵ��������˵�������Ǹ��� << ���ֵ����м�������淶
          �������豸��3���� Ӧ�ñ�̽ӿ� >> ��¼Q ���淶�Ը�¼�� �¼�����API 
          �е����������塣����˽�ж��壬��μ��¼�����ֵ�����ϸע��˵����

History     :
              2009.12.20          Created         Jason
              2010.01.08          Modified        DSM
              2010.01.24          Modified        JP
*******************************************************************************/
#ifndef _ROCME_PORTING_EVENT_H_
#define _ROCME_PORTING_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"


/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/


/*�����¼���������*/
typedef enum Roc_Evt_KeyAct
{
    ROC_KEY_SHIFT       = 0x0001,  /*�������¼�������ͬʱ��Shift��������*/
    ROC_KEY_CTRL        = 0x0002,  /*�������¼�������ͬʱ��Ctrl ��������*/
    ROC_KEY_ALT         = 0x0004,  /*�������¼�������ͬʱ��Alt  ��������*/
    ROC_KEY_PRESS       = 0x0100,  /*�������¼�                         */
    ROC_KEY_DOWN      = 0x0101,   
    ROC_KEY_RELEASE     = 0x0102,  /*���ͷ��¼�                         */
    ROC_KEY_UNKNOWN     = 0x0400   /*δ֪�İ���������SMSX�Զ���         */
}Roc_Evt_KeyAct_e;


/*�����¼������������*/
typedef enum Roc_Evt_Input
{
	ROC_INPUT_SYSEVT                 = 1001,  //ϵͳ��Ϣ
	ROC_INPUT_KEYBOARD            = 1002,  //������Ϣ  
	ROC_INPUT_MOUSE			  =	1003,  //�����Ϣ
	ROC_INPUT_REMOTECTRL         = 1004,  /*��ң���������������¼�*/
	ROC_INPUT_REMOTE_GAFFER	   =	1005,  //������ң������Ϣ
	ROC_INPUT_REMOTE_CHILD	   =	1006,  //��ͯ��ң������Ϣ
	ROC_INPUT_FRONTBOARD          = 1007,  /*��ǰ�������������¼�*/
	ROC_INPUT_RESERVE     = 0xffff
} Roc_Evt_Input_e;

/*�����¼�ֵ����*/
typedef enum Roc_Event
{
    ROC_IRKEY_NUM0          = 48,  /*���ּ�0*/
    ROC_IRKEY_NUM1          = 49,  /*���ּ�1*/
    ROC_IRKEY_NUM2          = 50,  /*���ּ�2*/
    ROC_IRKEY_NUM3          = 51,  /*���ּ�3*/
    ROC_IRKEY_NUM4          = 52,  /*���ּ�4*/
    ROC_IRKEY_NUM5          = 53,  /*���ּ�5*/
    ROC_IRKEY_NUM6          = 54,  /*���ּ�6*/
    ROC_IRKEY_NUM7          = 55,  /*���ּ�7*/
    ROC_IRKEY_NUM8          = 56,  /*���ּ�8*/
    ROC_IRKEY_NUM9          = 57,  /*���ּ�9*/
    ROC_IRKEY_EXIT          = 27,  /*ȡ��/�˳���,��CANCEL*/ 
    ROC_IRKEY_CHANNEL_DOWN  = 91,  /*ң�����ϵ�Ƶ�����ټ�*/
    ROC_IRKEY_CHANNEL_UP    = 93,  /*ң�����ϵ�Ƶ�����Ӽ�*/
    ROC_IRKEY_RED           = 320,  /*ң�����ϵĹ��ܼ�COLORED_KEY_0,RocME�д����ɫ����*/
    ROC_IRKEY_YELLOW        = 322,  /*ң�����ϵĹ��ܼ�COLORED_KEY_1,RocME�д����ɫ����*/
    ROC_IRKEY_BLUE          = 323,  /*ң�����ϵĹ��ܼ�COLORED_KEY_2,RocME�д�����ɫ����*/
    ROC_IRKEY_GREEN         = 321,  /*ң�����ϵĹ��ܼ�COLORED_KEY_3,RocME�д�����ɫ����*/
    ROC_IRKEY_EPG           = 69,  /*ң�����ϵĽ�Ŀָ�ϼ�,Ԥ���,��GUIDE*/
    ROC_IRKEY_INFO          = 73,  /*ң�����ϵ���Ϣ��*/
    ROC_IRKEY_MENU          = 72,  /*ң�����ϵĲ˵���*/
    ROC_IRKEY_VOLUME_MUTE   = 67,  /*ң�����ϵľ�����*/
    ROC_IRKEY_SELECT        = 13,  /*ң�����ϵ�ȷ����,��OK*/
    ROC_IRKEY_VOLUME_DOWN   = 45,  /*ң������������С��*/
    ROC_IRKEY_VOLUME_UP     = 61,  /*ң�����ϵ����������*/
    ROC_IRKEY_DOWN          = 83,  /*ң�����ϵ����¼�*/
    ROC_IRKEY_UP            = 87,  /*ң�����ϵ����ϼ�*/
    ROC_IRKEY_LEFT          = 65,  /*ң�����ϵ������*/
    ROC_IRKEY_RIGHT         = 68,  /*ң�����ϵ����Ҽ�*/
    ROC_IRKEY_POWER         = 19,  /*ң�����ϵ�ָʾ�ػ��뿪����*/
    ROC_IRKEY_PAGE_UP       = 306,  /*ң�����ϵ����Ϸ�ҳ��*/
    ROC_IRKEY_PAGE_DOWN     = 307,  /*ң�����ϵ����·�ҳ��*/
    ROC_IRKEY_TRACK         = 86,  /*ң�����ϵ�������,��AUDIO*/
    ROC_IRKEY_LIKE          = 76,  /*ң�����ϵ���Ļ��/Ƶ��ϲ����,��TELETEXT*/
    ROC_IRKEY_BACK          = 8,  /*ң�����ϵķ��ؼ�,��TOGGLE*/ 
    ROC_IRKEY_PROGRAM_LIST  = 0x0281,  /*ң�����ϵ�Ƶ���б������ѯ��,��PROG_LIST*/
    ROC_IRKEY_TV_RADIO      = 0x0282,  /*ң�����ϵ�ָʾ"����/��Ƶ�㲥"��*/
    ROC_IRKEY_NVOD          = 315,  /*ң�����ϵĿ���Ϣ��㲥��,������, ��CARD_INFO*/ 
    ROC_IRKEY_MAIL          = 77,  /*ң�����ϵ��ʼ���*/
/*����ΪSMSX�Զ��岿��*/

    ROC_IRKEY_STATE         = 0x0202,  /*ң�����ϵ�״̬����SMSX�Զ���*/
    ROC_IRKEY_DC            = 0x0203,  /*ң�����ϵ����ݹ㲥����SMSX�Զ���*/
    ROC_IRKEY_SORT          = 0x0204,  /*ң�����ϵĽ�Ŀ�������SMSX�Զ���*/
    ROC_IRKEY_GAME          = 0x0205,  /*ң�����ϵ���Ϸ����SMSX�Զ���*/
    ROC_IRKEY_LAST_CHANNEL  = 314,  /*ң�����ϵĵ��ӻؿ�����SMSX�Զ���*/
    ROC_IRKEY_PAUSE         = 59,  /*ң�����ϵ���ͣ������SMSX�Զ���*/
    ROC_IRKEY_HOMEPAGE      = 0x0213,  /*ң�����ϵ���ҳ�����SMSX�Զ���*/
    ROC_IRKEY_MOSAIC        = 0x0214,  /*ң�����ϵ������˼���SMSX�Զ���*/
    ROC_IRKEY_STOCK         = 0x0215,  /*ң�����ϵĹ�Ʊ����SMSX�Զ���*/
    ROC_IRKEY_VIDEO         = 313,  /*ң�����ϵĵ��Ӽ���SMSX�Զ���*/
    ROC_IRKEY_AUDIO         = 0x0217,  /*ң�����ϵĹ㲥����SMSX�Զ���*/

/*�û��Զ��尴��*/
    ROC_IRKEY_FUN1          = 0x0206,  /*�����Ŀ�д��� :  [��Ѷ] �� */
    ROC_IRKEY_FUN2          = 0x0207,  /*�����Ŀ�д��� :  [�㲥] �� */
    ROC_IRKEY_FUN3          = 0x0301,  /*�����Ŀ�д��� :  [��Ʊ] �� */
    ROC_IRKEY_FUN4          = 0x0302,  /*�����Ŀ�д��� :  [����] �� */
    ROC_IRKEY_FUN5          = 0x0303,  /*�����Ŀ�д��� :  [����] �� */
    ROC_IRKEY_FUN6          = 0x0304,  /*�����Ŀ�д��� :  [��һ��Ԫ] �� */
    ROC_IRKEY_FUN7          = 0x0305,  /*�����Ŀ�д��� :  [��һ��Ԫ] �� */
    ROC_IRKEY_FUN8          = 47,  /*�����Ŀ�д��� :  [ֹͣ] �� */
    ROC_IRKEY_FUN9          = 44,  /*�����Ŀ�д��� :  [����] �� */
    ROC_IRKEY_FUN10         = 46,  /*�����Ŀ�д��� :  [���] �� */
    ROC_IRKEY_FUN11         = 39,  /*�����Ŀ�д��� :  [����] �� */
    ROC_IRKEY_FUN12         = 59,  /*�����Ŀ�д��� :  [��ͣ/ʱ��] �� */
    ROC_IRKEY_FUN13         = 82,  /*�����Ŀ�д��� :  [¼��] �� */
    ROC_IRKEY_FUN14         = 0x030C,  /*�����Ŀ�д��� :  [ V+/PIP�ƶ� ] �� */
    ROC_IRKEY_FUN15         = 0x030D,  /*�����Ŀ�д��� :  [ V-/PIP���� ] �� */
    ROC_IRKEY_FUN16         = 0x030E,  /*�����Ŀ�д��� :  [PIP ] �� */
    ROC_IRKEY_FUN17         = 0x030F,  /*�����Ŀ�д��� :  [Ԥ��] �� */
    ROC_IRKEY_FUN18         = 0x0310,  /*�����Ŀ�д��� :  [ȫ��] �� */
    ROC_IRKEY_FUN19         = 0x0311,  /*�����Ŀ�д��� :  [] �� */
    ROC_IRKEY_FUN20         = 319,  /*�����Ŀ�д��� :  # �� */
    ROC_IRKEY_ASTERISK   = 318,   /*�Ǻż�*/
    ROC_IRKEY_INVALID       = 0xffff,  /*δ֪�����룬SMSX�Զ���*/
}Roc_Event_e;

#define KT_SYM      0   /*����ϵͳ������*/
#define KT_CN       1   /*���Ƽ�����*/
#define KT_SPE      2   /*�������������*/
#define KT_NM       3   /*���ְ�������*/
#define KT_CHAR     4   /*�ַ�������*/
#define KT_PAD      6   /*���ּ���*/
#define KT_FN       7   /*���ܼ�����*/
#define KT_LOCK     9   /*Lock����*/
#define KT_CONL     10  /*����Shift,����Ctrl,����Alt����*/
#define KT_SYMBOL   11  /*��������*/

#define LMD(t,v)    (((t)<<4)+(v))/*�����ֵ*/

#define KEYVALUE(base,val)  ((base) + (val))
#define KBD_BASE0     (48)
#define KBD_BASE1     (65)
#define KBD_BASE2     (32)
#define KBD_BASE3     (97)
#define KBD_BASE_SPC   (300)

/*���̰����¼�ֵ����*/
typedef enum Roc_Kbd_Event
{
    ROC_KBDKEY_0            = KEYVALUE(KBD_BASE0, 0),     /*�������ּ�0*/
    ROC_KBDKEY_1            = KEYVALUE(KBD_BASE0, 1),     /*�������ּ�1*/
    ROC_KBDKEY_2            = KEYVALUE(KBD_BASE0, 2),     /*�������ּ�2*/
    ROC_KBDKEY_3            = KEYVALUE(KBD_BASE0, 3),     /*�������ּ�3*/
    ROC_KBDKEY_4            = KEYVALUE(KBD_BASE0, 4),     /*�������ּ�4*/
    ROC_KBDKEY_5            = KEYVALUE(KBD_BASE0, 5),     /*�������ּ�5*/
    ROC_KBDKEY_6            = KEYVALUE(KBD_BASE0, 6),     /*�������ּ�6*/
    ROC_KBDKEY_7            = KEYVALUE(KBD_BASE0, 7),     /*�������ּ�7*/
    ROC_KBDKEY_8            = KEYVALUE(KBD_BASE0, 8),     /*�������ּ�8*/
    ROC_KBDKEY_9            = KEYVALUE(KBD_BASE0, 9),     /*�������ּ�9*/
    
    ROC_KBDKEY_A            = KEYVALUE(KBD_BASE1, 0),   /*�����ַ���'A'*/
    ROC_KBDKEY_B            = KEYVALUE(KBD_BASE1, 1),   /*�����ַ���'B'*/
    ROC_KBDKEY_C            = KEYVALUE(KBD_BASE1, 2),   /*�����ַ���'C'*/
    ROC_KBDKEY_D            = KEYVALUE(KBD_BASE1, 3),   /*�����ַ���'D'*/
    ROC_KBDKEY_E            = KEYVALUE(KBD_BASE1, 4),   /*�����ַ���'E'*/
    ROC_KBDKEY_F            = KEYVALUE(KBD_BASE1, 5),   /*�����ַ���'F'*/
    ROC_KBDKEY_G            = KEYVALUE(KBD_BASE1, 6),   /*�����ַ���'G'*/
    ROC_KBDKEY_H            = KEYVALUE(KBD_BASE1, 7),   /*�����ַ���'H'*/
    ROC_KBDKEY_I            = KEYVALUE(KBD_BASE1, 8),   /*�����ַ���'I'*/
    ROC_KBDKEY_J            = KEYVALUE(KBD_BASE1, 9),  /*�����ַ���'J'*/
    ROC_KBDKEY_K            = KEYVALUE(KBD_BASE1, 10),  /*�����ַ���'K'*/
    ROC_KBDKEY_L            = KEYVALUE(KBD_BASE1, 11),  /*�����ַ���'L'*/
    ROC_KBDKEY_M            = KEYVALUE(KBD_BASE1, 12),  /*�����ַ���'M'*/
    ROC_KBDKEY_N            = KEYVALUE(KBD_BASE1, 13),  /*�����ַ���'N'*/
    ROC_KBDKEY_O            = KEYVALUE(KBD_BASE1, 14),  /*�����ַ���'O'*/
    ROC_KBDKEY_P            = KEYVALUE(KBD_BASE1, 15),  /*�����ַ���'P'*/
    ROC_KBDKEY_Q            = KEYVALUE(KBD_BASE1, 16),  /*�����ַ���'Q'*/
    ROC_KBDKEY_R            = KEYVALUE(KBD_BASE1, 17),  /*�����ַ���'R'*/
    ROC_KBDKEY_S            = KEYVALUE(KBD_BASE1, 18),  /*�����ַ���'S'*/
    ROC_KBDKEY_T            = KEYVALUE(KBD_BASE1, 19),  /*�����ַ���'T'*/
    ROC_KBDKEY_U            = KEYVALUE(KBD_BASE1, 20),  /*�����ַ���'U'*/
    ROC_KBDKEY_V            = KEYVALUE(KBD_BASE1, 21),  /*�����ַ���'V'*/
    ROC_KBDKEY_W            = KEYVALUE(KBD_BASE1, 22),  /*�����ַ���'W'*/
    ROC_KBDKEY_X            = KEYVALUE(KBD_BASE1, 23),  /*�����ַ���'X'*/
    ROC_KBDKEY_Y            = KEYVALUE(KBD_BASE1, 24),  /*�����ַ���'Y'*/
    ROC_KBDKEY_Z            = KEYVALUE(KBD_BASE1, 25),  /*�����ַ���'Z'*/   

    ROC_KBDKEY_A_LC            = KEYVALUE(KBD_BASE3, 0),   /*�����ַ���'a'*/
    ROC_KBDKEY_B_LC            = KEYVALUE(KBD_BASE3, 1),   /*�����ַ���'b'*/
    ROC_KBDKEY_C_LC            = KEYVALUE(KBD_BASE3, 2),   /*�����ַ���'c'*/
    ROC_KBDKEY_D_LC            = KEYVALUE(KBD_BASE3, 3),   /*�����ַ���'d'*/
    ROC_KBDKEY_E_LC            = KEYVALUE(KBD_BASE3, 4),   /*�����ַ���'e'*/
    ROC_KBDKEY_F_LC            = KEYVALUE(KBD_BASE3, 5),   /*�����ַ���'f'*/
    ROC_KBDKEY_G_LC            = KEYVALUE(KBD_BASE3, 6),   /*�����ַ���'g'*/
    ROC_KBDKEY_H_LC            = KEYVALUE(KBD_BASE3, 7),   /*�����ַ���'h'*/
    ROC_KBDKEY_I_LC            = KEYVALUE(KBD_BASE3, 8),   /*�����ַ���'i'*/
    ROC_KBDKEY_J_LC            = KEYVALUE(KBD_BASE3, 9),  /*�����ַ���'j'*/
    ROC_KBDKEY_K_LC            = KEYVALUE(KBD_BASE3, 10),  /*�����ַ���'k'*/
    ROC_KBDKEY_L_LC            = KEYVALUE(KBD_BASE3, 11),  /*�����ַ���'l'*/
    ROC_KBDKEY_M_LC            = KEYVALUE(KBD_BASE3, 12),  /*�����ַ���'m'*/
    ROC_KBDKEY_N_LC            = KEYVALUE(KBD_BASE3, 13),  /*�����ַ���'n'*/
    ROC_KBDKEY_O_LC            = KEYVALUE(KBD_BASE3, 14),  /*�����ַ���'o'*/
    ROC_KBDKEY_P_LC            = KEYVALUE(KBD_BASE3, 15),  /*�����ַ���'p'*/
    ROC_KBDKEY_Q_LC            = KEYVALUE(KBD_BASE3, 16),  /*�����ַ���'q'*/
    ROC_KBDKEY_R_LC            = KEYVALUE(KBD_BASE3, 17),  /*�����ַ���'r'*/
    ROC_KBDKEY_S_LC            = KEYVALUE(KBD_BASE3, 18),  /*�����ַ���'s'*/
    ROC_KBDKEY_T_LC            = KEYVALUE(KBD_BASE3, 19),  /*�����ַ���'t'*/
    ROC_KBDKEY_U_LC            = KEYVALUE(KBD_BASE3, 20),  /*�����ַ���'u'*/
    ROC_KBDKEY_V_LC            = KEYVALUE(KBD_BASE3, 21),  /*�����ַ���'v'*/
    ROC_KBDKEY_W_LC            = KEYVALUE(KBD_BASE3, 22),  /*�����ַ���'w'*/
    ROC_KBDKEY_X_LC            = KEYVALUE(KBD_BASE3, 23),  /*�����ַ���'x'*/
    ROC_KBDKEY_Y_LC           = KEYVALUE(KBD_BASE3, 24),  /*�����ַ���'y'*/
    ROC_KBDKEY_Z_LC            = KEYVALUE(KBD_BASE3, 25),  /*�����ַ���'z'*/   
    
    ROC_KBDKEY_SPACE                       = KEYVALUE(KBD_BASE2, 0),    /*���̿ո��*/
    ROC_KBDKEY_EXCLAMATION           = KEYVALUE(KBD_BASE2, 1),    /*���̷��ż�'!'*/
    ROC_KBDKEY_DAPOSTROPHE          = KEYVALUE(KBD_BASE2, 2),  /*���̷��ż�'"'*/
    ROC_KBDKEY_WELL                         = KEYVALUE(KBD_BASE2, 3),               /* ���̷��ż�'# '*/
    ROC_KBDKEY_DOLLAR                     = KEYVALUE(KBD_BASE2, 4),      /* ���̷��ż�'$'*/
    ROC_KBDKEY_PERCENT                   = KEYVALUE(KBD_BASE2, 5),    /* ���̷��ż�'%'*/
    ROC_KBDKEY_AND                           = KEYVALUE(KBD_BASE2, 6),            /* ���̷��ż�'&'*/
    ROC_KBDKEY_APOSTROPHE             = KEYVALUE(KBD_BASE2, 7),  /*���̷��ż�'''*/
    ROC_KBDKEY_LEFT_PARENTHESIS    = KEYVALUE(KBD_BASE2, 8),    /* ���̷��ż�'('*/
    ROC_KBDKEY_RIGHT_PARENTHESIS  = KEYVALUE(KBD_BASE2, 9),          /* ���̷��ż�')'*/
    ROC_KBDKEY_ASTERISK                    = KEYVALUE(KBD_BASE2, 10),     /* ���̷��ż�'*'*/
    ROC_KBDKEY_PLUS                           = KEYVALUE(KBD_BASE2, 11), /*���̷��ż�'+'*/
    ROC_KBDKEY_COMMA                       = KEYVALUE(KBD_BASE2, 12),/*���̷��ż�','*/
    ROC_KBDKEY_MINUS                        = KEYVALUE(KBD_BASE2, 13),/*���̷��ż�'-'*/
    ROC_KBDKEY_DOT                            = KEYVALUE(KBD_BASE2, 14),/*���̷��ż�'.'*/
    ROC_KBDKEY_KPDOT                        = KEYVALUE(KBD_BASE2, 14),   /*���ּ���,'.',�����*/
    ROC_KBDKEY_SLASH                          = KEYVALUE(KBD_BASE2, 15),/*���̷��ż�'/'*/
 
    ROC_KBDKEY_BACKSPACE    = 8,    /*����Backspace��*/
    ROC_KBDKEY_TAB          = 9,    /*����Tab��*/
    ROC_KBDKEY_ENTER        = 13,   /*����Enter��*/
    ROC_KBDKEY_ESC          = 27,    /*����ESC��*/

    ROC_KBDKEY_SHIFT_L      = 16,   /*������Shift��*/
    ROC_KBDKEY_SHIFT_R      = 16,   /*������Shift��*/
    ROC_KBDKEY_CTRL_L       = 17,   /*������Ctrl��*/
    ROC_KBDKEY_CTRL_R       = 17,   /*������Ctrl��*/
    ROC_KBDKEY_ALT_L        = 18,   /*������Alt��*/
    ROC_KBDKEY_ALT_R        = 18,   /*������Alt��*/
    ROC_KBDKEY_PAUSE        = 19,     /*����Pause��*/
    ROC_KBDKEY_CAPSLOCK     = 20,     /*����Caps Lock��*/
    
    ROC_KBDKEY_LEFTBRACE    = 91,  /*���̷��ż�'['*/
    ROC_KBDKEY_BACKSLASH    = 92,  /*���̷��ż�'\'*/
    ROC_KBDKEY_RIGHTBRACE   = 93,  /*���̷��ż�']'*/
    ROC_KBDKEY_XOR           = 94,               /* ���̷��ż�'^'*/
    ROC_KBDKEY_UNDERLINE  = 95, /*���̷��ż�'_'*/
    ROC_KBDKEY_GRAVE        = 96,   /*���̷��ż�'`'*/
    
    ROC_KBDKEY_COLON        = 58,   /*���̷��ż�':'*/
    ROC_KBDKEY_SEMICOLON    = 59,/*���̷��ż�';'*/
    ROC_KBDKEY_LEFT_ANGLE_BRACKET = 60, /*���̷��ż�'<'*/
    ROC_KBDKEY_EQUAL        = 61,/*���̷��ż�'='*/
    ROC_KBDKEY_RIGHT_ANGLE_BRACKET = 62,   /*���̷��ż�'>'*/
    ROC_KBDKEY_QUESTION = 63,  /*���̷��ż�'?'*/
    ROC_KBDKEY_AT           = 64,      /*���̷��ż�'@'*/
    
    ROC_KBDKEY_LEFT_BRACE = 123,  /*���̷��ż�'{'*/
    ROC_KBDKEY_OR   = 124,             /*���̷��ż�'|'*/
    ROC_KBDKEY_RIGHT_BRACE = 125,  /*���̷��ż�'}'*/
    ROC_KBDKEY_INVERT = 126,    /*���̷��ż�'~'*/
    
    ROC_KBDKEY_NUMLOCK      = 144,   /*����Number Lock��*/
    ROC_KBDKEY_SCROLLLOCK   = 145,   /*����Scroll Lock��*/

    
    ROC_KBDKEY_PRINTSCREEN  = KEYVALUE(KBD_BASE_SPC, 1),   /*����Print Screen��*/
    ROC_KBDKEY_HOME         = KEYVALUE(KBD_BASE_SPC, 2),    /*����Home��*/
    ROC_KBDKEY_END          = KEYVALUE(KBD_BASE_SPC, 3),    /*����End��*/
    ROC_KBDKEY_INSERT       =  KEYVALUE(KBD_BASE_SPC, 4),   /*����Insert��*/
    ROC_KBDKEY_DELETE       = KEYVALUE(KBD_BASE_SPC, 5),   /*����Delete��*/
    ROC_KBDKEY_PAGEUP       = KEYVALUE(KBD_BASE_SPC, 6),    /*����Page Up��*/
    ROC_KBDKEY_PAGEDOWN     = KEYVALUE(KBD_BASE_SPC, 7),    /*����Page Down��*/
    ROC_KBDKEY_UP           = KEYVALUE(KBD_BASE_SPC, 8),    /*�����ϼ�*/
    ROC_KBDKEY_DOWN         = KEYVALUE(KBD_BASE_SPC, 9),    /*�����¼�*/
    ROC_KBDKEY_LEFT         = KEYVALUE(KBD_BASE_SPC, 10),    /*�������*/
    ROC_KBDKEY_RIGHT        = KEYVALUE(KBD_BASE_SPC, 11),    /*�����Ҽ�*/

    ROC_KBDKEY_F1           = KEYVALUE(KBD_BASE_SPC, 12),     /*���̹��ܼ�F1*/
    ROC_KBDKEY_F2           = KEYVALUE(KBD_BASE_SPC, 13),     /*���̹��ܼ�F2*/
    ROC_KBDKEY_F3           = KEYVALUE(KBD_BASE_SPC, 14),     /*���̹��ܼ�F3*/
    ROC_KBDKEY_F4           = KEYVALUE(KBD_BASE_SPC, 15),     /*���̹��ܼ�F4*/
    ROC_KBDKEY_F5           = KEYVALUE(KBD_BASE_SPC, 16),     /*���̹��ܼ�F5*/
    ROC_KBDKEY_F6           = KEYVALUE(KBD_BASE_SPC, 17),     /*���̹��ܼ�F6*/
    ROC_KBDKEY_F7           = KEYVALUE(KBD_BASE_SPC, 18),     /*���̹��ܼ�F7*/
    ROC_KBDKEY_F8           = KEYVALUE(KBD_BASE_SPC, 19),     /*���̹��ܼ�F8*/
    ROC_KBDKEY_F9           = KEYVALUE(KBD_BASE_SPC, 20),     /*���̹��ܼ�F9*/
    ROC_KBDKEY_F10          = KEYVALUE(KBD_BASE_SPC, 21),     /*���̹��ܼ�F10*/
    ROC_KBDKEY_F11          = KEYVALUE(KBD_BASE_SPC, 22),    /*���̹��ܼ�F11*/
    ROC_KBDKEY_F12          = KEYVALUE(KBD_BASE_SPC, 23),    /*���̹��ܼ�F12*/
    ROC_KBDKEY_F13          = KEYVALUE(KBD_BASE_SPC, 24),    /*���̹��ܼ�F13*/
    ROC_KBDKEY_F14          = KEYVALUE(KBD_BASE_SPC, 25),    /*���̹��ܼ�F14*/
    ROC_KBDKEY_F15          = KEYVALUE(KBD_BASE_SPC, 26),    /*���̹��ܼ�F15*/
    ROC_KBDKEY_F16          = 127,    /*���̹��ܼ�F16*/

    ROC_KBDKEY_KP0          = KEYVALUE(KBD_BASE_SPC, 27),    /*���ּ���,���ּ�0*/
    ROC_KBDKEY_KP1          = KEYVALUE(KBD_BASE_SPC, 28),    /*���ּ���,���ּ�1*/
    ROC_KBDKEY_KP2          = KEYVALUE(KBD_BASE_SPC, 29),    /*���ּ���,���ּ�2*/
    ROC_KBDKEY_KP3          = KEYVALUE(KBD_BASE_SPC, 30),    /*���ּ���,���ּ�3*/
    ROC_KBDKEY_KP4          = KEYVALUE(KBD_BASE_SPC, 31),    /*���ּ���,���ּ�4*/
    ROC_KBDKEY_KP5          = KEYVALUE(KBD_BASE_SPC, 32),    /*���ּ���,���ּ�5*/
    ROC_KBDKEY_KP6          = KEYVALUE(KBD_BASE_SPC, 33),    /*���ּ���,���ּ�6*/
    ROC_KBDKEY_KP7          = KEYVALUE(KBD_BASE_SPC, 34),    /*���ּ���,���ּ�7*/
    ROC_KBDKEY_KP8          = KEYVALUE(KBD_BASE_SPC, 35),    /*���ּ���,���ּ�8*/
    ROC_KBDKEY_KP9          = KEYVALUE(KBD_BASE_SPC, 36),    /*���ּ���,���ּ�9*/
    ROC_KBDKEY_KPDIVIDE     = KEYVALUE(KBD_BASE_SPC, 37),   /*���ּ���,'/',�������*/
    ROC_KBDKEY_KPMULTIPLY   = KEYVALUE(KBD_BASE_SPC, 38),   /*���ּ���,'*',�������*/
    ROC_KBDKEY_KPMINUS      = KEYVALUE(KBD_BASE_SPC, 39),   /*���ּ���,'-',�������*/
    ROC_KBDKEY_KPPLUS       = KEYVALUE(KBD_BASE_SPC, 40),   /*���ּ���,'+',�������*/
    
    ROC_KBDKEY_META_L       = KEYVALUE(KBD_BASE_SPC, 50),  /*������window��*/
    ROC_KBDKEY_META_R       = KEYVALUE(KBD_BASE_SPC, 51),  /*������window��*/
    ROC_KBDKEY_COMPOSE      = KEYVALUE(KBD_BASE_SPC, 52),  /*����������Ҽ����ܼ�*/
    ROC_KBDKEY_CLEAR        = KEYVALUE(KBD_BASE_SPC, 53),   /*����Clear��*/
    ROC_KBDKEY_PRINT        = KEYVALUE(KBD_BASE_SPC, 54),   /*����Print��*/
    ROC_KBDKEY_EXECUTE      = KEYVALUE(KBD_BASE_SPC, 55),   /*����Execute��*/
    ROC_KBDKEY_HELP         = KEYVALUE(KBD_BASE_SPC, 56),   /*����Help��*/
    ROC_KBDKEY_F17          = KEYVALUE(KBD_BASE_SPC, 57),    /*���̹��ܼ�F17*/
    ROC_KBDKEY_F18          = KEYVALUE(KBD_BASE_SPC, 58),    /*���̹��ܼ�F18*/
    ROC_KBDKEY_F19          = KEYVALUE(KBD_BASE_SPC, 59),    /*���̹��ܼ�F19*/
    ROC_KBDKEY_F20          = KEYVALUE(KBD_BASE_SPC, 60),    /*���̹��ܼ�F20*/
    ROC_KBDKEY_SYSRQ        = KEYVALUE(KBD_BASE_SPC, 61),   /*����SysRq��*/
    ROC_KBDKEY_MUTE         = KEYVALUE(KBD_BASE_SPC, 62),   /*���̾�����*/
    ROC_KBDKEY_VOLUMEDOWN   = KEYVALUE(KBD_BASE_SPC, 63),   /*��������-��*/
    ROC_KBDKEY_VOLUMEUP     = KEYVALUE(KBD_BASE_SPC, 64),   /*��������+��*/
    ROC_KBDKEY_POWER        = KEYVALUE(KBD_BASE_SPC, 65),   /*����Power��*/
}Roc_Kbd_Event_e;

/*�¼��ص���������*/
typedef INT32_T (*rocme_porting_event_callback) ( void *param, Roc_Evt_Input_e input, UINT32_T event, Roc_Evt_KeyAct_e act );

/*�¼�ע������ṹ����*/
typedef struct Roc_Evt_Param
{
    rocme_porting_event_callback    callback;   /*�¼��ص�����*/
    void                            *cb_param;  /*�ص�������˽�в���*/
}Roc_Evt_Param_t;

/*��궯������*/
typedef enum Roc_Mouse_Act
{
    ROC_MOUSE_DOWN = 0x0000,  /*��갴���¼�*/
    ROC_MOUSE_UP  = 0x0001,      /*��굯���¼�*/
    ROC_MOUSE_CLICK = 0x0002,    /*��굥���¼�*/
    ROC_MOUSE_DBCLICK = 0x0003,  /*���˫���¼�*/
    ROC_MOUSE_MOVED = 0x0004,    /*�����ƶ��¼�*/
    ROC_MOUSE_WHEEL     = 0x0005   /*�����ֹ���*/
}Roc_Mouse_Act_e;

typedef enum Roc_Mouse_Type
{
	ROC_MOUSE_LEFT				= 1,              /*������*/
	ROC_MOUSE_RIGHT 			= 2,              /*����Ҽ�*/
	ROC_MOUSE_MIDDLE			= 4,             /*����м�*/
	ROC_MOUSE_WHEEL_UP		= 8,              /*����������*/
	ROC_MOUSE_WHEEL_DOWN	= 16,              /*����������*/
	ROC_MOUSE_NULL				= 32,              /*������*/
}Roc_Mouse_Type_e;

/*����¼����Ͷ���*/
typedef struct Roc_Mouse_Event
{
    Roc_Mouse_Act_e act;  /*��궯������*/
    Roc_Mouse_Type_e eType;   /*��갴��ֵ*/
    INT32_T x;            /*��ǰ�������꣨�����Ļ��*/
    INT32_T y;            /*��ǰ��������꣨�����Ļ��*/
}Roc_Mouse_Event_t;


/*ң��������*/
typedef enum Roc_KeyBoard_Type
{
    ROC_KEYBOARD_TYPE_DEFAULT           = 0x0000,  /*Ĭ�ϰ汾    */
    ROC_KEYBOARD_TYPE_1                 = 0x0001,  /*��ά����汾*/
    ROC_KEYBOARD_TYPE_2                 = 0x0002,  /*TCB�汾*/
    ROC_KEYBOARD_TYPE_NUM               = 0x0003,  /*�汾number*/
}Roc_KeyBoard_Type_e;


/*����¼��ص���������*/
typedef INT32_T (*rocme_porting_mouse_evt_callback) ( void *param,Roc_Mouse_Event_t event );

/*����¼�ע������ṹ����*/
typedef struct Roc_Mouse_Param
{
    rocme_porting_mouse_evt_callback    callback;   /*����¼��ص�����*/
    void                                *cb_param;  /*�ص�������˽�в���*/
}Roc_Mouse_Param_t;


/*���弴���¼��ṹ����*/
typedef enum Roc_PlugPlay_Event
{
    ROC_KB_PLUGIN       = 0x0001, // ���̲���
    ROC_KB_PULLOUT      = 0x0002, // ���̰γ�
    ROC_MOUSE_PLUGIN    = 0x0003, // ������
    ROC_MOUSE_PULLOUT   = 0x0004,  // ���γ�
}Roc_PlugPlay_Event_t;

/*���弴���¼��ص���������*/
typedef INT32_T (*rocme_porting_plug_play_callback) ( void *param, Roc_PlugPlay_Event_t event);


/*���弴���¼�ע������ṹ����*/
typedef struct Roc_PlugPlay_Param
{
    rocme_porting_plug_play_callback    callback;   /*���弴���¼��ص�����*/
    void                                *cb_param;  /*�ص�������˽�в���*/
}Roc_PlugPlay_Param_t;
 


/*++++++++++++++++++++++++++++     ���뷨�궨��    ++++++++++++++++++++++++++++*/
//�л����뷨�İ���,�����ҿ����ж��塣
//���ɲ������ּ�,�����,ȷ����,�Ϸ�ҳ,�·�ҳ(���뷨��Ҫʹ��)
//���ɲ���ROC_IRKEY_BLUE ,ROC_IRKEY_YELLOW,(�������Ҫʹ��)
//#define ROC_IRKEY_IME ROC_IRKEY_RED
#define ROC_IRKEY_IME ROC_IRKEY_FUN20  //ʹ��ң������#�ż�


/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/

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
INT32_T rocme_porting_event_register(const Roc_Evt_Param_t evt_param,UINT32_T *handler);

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
INT32_T rocme_porting_event_unregister(const UINT32_T handler);

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
INT32_T rocme_porting_mouse_register( const Roc_Mouse_Param_t mouse_param,UINT32_T *handler );

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
INT32_T rocme_porting_mouse_unregister( const UINT32_T handler );


 
/**************************************************************************
��������: 
            rocme_porting_plug_play_register
����˵��: 
            �������ע��һ�����弴���¼��ļ���Ҫ��
����˵����
    ���������
            [ evt_param   ] : �¼����������������ص������Լ�˽�в���
    ���������
            [ handler     ] : ��ע������Ŀ��ƾ��
��    �أ� 
    �ɹ� : 0            ( ע��������弴���¼��ɹ� )
    ʧ�� : -1 �� ������ ( ע��������弴���¼�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_plug_play_register(const Roc_PlugPlay_Param_t evt_param,UINT32_T *handler);


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
INT32_T rocme_porting_mouse_set_coordinate( const UINT32_T x,const UINT32_T y );

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
INT32_T rocme_porting_keyboard_type_set(const Roc_KeyBoard_Type_e keyboard_type);

#undef KT_SYM
#undef KT_CN
#undef KT_SPE
#undef KT_NM
#undef KT_CHAR
#undef KT_PAD
#undef KT_FN
#undef KT_LOCK
#undef KT_CONL
#undef KT_SYMBOL
#undef LMD

#ifdef __cplusplus
}
#endif


#endif
