/*******************************************************************************
Copyright (C) BeiJing SUMAVision, Inc., 2009-2011 .All rights reserved.

File name   : rocme_porting_event.h

Author      : DSM

Description : The poriting interface & macro definition for EVENT module.
              本文件的事件值若无特殊说明，则是根据 << 数字电视中间件技术规范
          －接收设备第3部分 应用编程接口 >> 附录Q （规范性附录） 事件管理API 
          中的描述所定义。个别私有定义，请参见事件定义值后的详细注释说明。

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


/*按键事件动作定义*/
typedef enum Roc_Evt_KeyAct
{
    ROC_KEY_SHIFT       = 0x0001,  /*键按下事件发生的同时，Shift键被按下*/
    ROC_KEY_CTRL        = 0x0002,  /*键按下事件发生的同时，Ctrl 键被按下*/
    ROC_KEY_ALT         = 0x0004,  /*键按下事件发生的同时，Alt  键被按下*/
    ROC_KEY_PRESS       = 0x0100,  /*键按下事件                         */
    ROC_KEY_DOWN      = 0x0101,   
    ROC_KEY_RELEASE     = 0x0102,  /*键释放事件                         */
    ROC_KEY_UNKNOWN     = 0x0400   /*未知的按键动作，SMSX自定义         */
}Roc_Evt_KeyAct_e;


/*按键事件输入产生定义*/
typedef enum Roc_Evt_Input
{
	ROC_INPUT_SYSEVT                 = 1001,  //系统消息
	ROC_INPUT_KEYBOARD            = 1002,  //键盘消息  
	ROC_INPUT_MOUSE			  =	1003,  //鼠标消息
	ROC_INPUT_REMOTECTRL         = 1004,  /*由遥控器产生的输入事件*/
	ROC_INPUT_REMOTE_GAFFER	   =	1005,  //老人型遥控器消息
	ROC_INPUT_REMOTE_CHILD	   =	1006,  //儿童型遥控器消息
	ROC_INPUT_FRONTBOARD          = 1007,  /*由前面板产生的输入事件*/
	ROC_INPUT_RESERVE     = 0xffff
} Roc_Evt_Input_e;

/*按键事件值定义*/
typedef enum Roc_Event
{
    ROC_IRKEY_NUM0          = 48,  /*数字键0*/
    ROC_IRKEY_NUM1          = 49,  /*数字键1*/
    ROC_IRKEY_NUM2          = 50,  /*数字键2*/
    ROC_IRKEY_NUM3          = 51,  /*数字键3*/
    ROC_IRKEY_NUM4          = 52,  /*数字键4*/
    ROC_IRKEY_NUM5          = 53,  /*数字键5*/
    ROC_IRKEY_NUM6          = 54,  /*数字键6*/
    ROC_IRKEY_NUM7          = 55,  /*数字键7*/
    ROC_IRKEY_NUM8          = 56,  /*数字键8*/
    ROC_IRKEY_NUM9          = 57,  /*数字键9*/
    ROC_IRKEY_EXIT          = 27,  /*取消/退出键,即CANCEL*/ 
    ROC_IRKEY_CHANNEL_DOWN  = 91,  /*遥控器上的频道减少键*/
    ROC_IRKEY_CHANNEL_UP    = 93,  /*遥控器上的频道增加键*/
    ROC_IRKEY_RED           = 320,  /*遥控器上的功能键COLORED_KEY_0,RocME中代表红色按键*/
    ROC_IRKEY_YELLOW        = 322,  /*遥控器上的功能键COLORED_KEY_1,RocME中代表黄色按键*/
    ROC_IRKEY_BLUE          = 323,  /*遥控器上的功能键COLORED_KEY_2,RocME中代表蓝色按键*/
    ROC_IRKEY_GREEN         = 321,  /*遥控器上的功能键COLORED_KEY_3,RocME中代表绿色按键*/
    ROC_IRKEY_EPG           = 69,  /*遥控器上的节目指南键,预告键,即GUIDE*/
    ROC_IRKEY_INFO          = 73,  /*遥控器上的信息键*/
    ROC_IRKEY_MENU          = 72,  /*遥控器上的菜单键*/
    ROC_IRKEY_VOLUME_MUTE   = 67,  /*遥控器上的静音键*/
    ROC_IRKEY_SELECT        = 13,  /*遥控器上的确定键,即OK*/
    ROC_IRKEY_VOLUME_DOWN   = 45,  /*遥控器上音量减小键*/
    ROC_IRKEY_VOLUME_UP     = 61,  /*遥控器上的音量增大键*/
    ROC_IRKEY_DOWN          = 83,  /*遥控器上的向下键*/
    ROC_IRKEY_UP            = 87,  /*遥控器上的向上键*/
    ROC_IRKEY_LEFT          = 65,  /*遥控器上的向左键*/
    ROC_IRKEY_RIGHT         = 68,  /*遥控器上的向右键*/
    ROC_IRKEY_POWER         = 19,  /*遥控器上的指示关机与开机键*/
    ROC_IRKEY_PAGE_UP       = 306,  /*遥控器上的向上翻页键*/
    ROC_IRKEY_PAGE_DOWN     = 307,  /*遥控器上的向下翻页键*/
    ROC_IRKEY_TRACK         = 86,  /*遥控器上的声道键,即AUDIO*/
    ROC_IRKEY_LIKE          = 76,  /*遥控器上的字幕键/频道喜爱键,即TELETEXT*/
    ROC_IRKEY_BACK          = 8,  /*遥控器上的返回键,即TOGGLE*/ 
    ROC_IRKEY_PROGRAM_LIST  = 0x0281,  /*遥控器上的频道列表键或咨询键,即PROG_LIST*/
    ROC_IRKEY_TV_RADIO      = 0x0282,  /*遥控器上的指示"电视/音频广播"键*/
    ROC_IRKEY_NVOD          = 315,  /*遥控器上的卡信息或点播键,交互键, 即CARD_INFO*/ 
    ROC_IRKEY_MAIL          = 77,  /*遥控器上的邮件键*/
/*以下为SMSX自定义部分*/

    ROC_IRKEY_STATE         = 0x0202,  /*遥控器上的状态键，SMSX自定义*/
    ROC_IRKEY_DC            = 0x0203,  /*遥控器上的数据广播键，SMSX自定义*/
    ROC_IRKEY_SORT          = 0x0204,  /*遥控器上的节目分类键，SMSX自定义*/
    ROC_IRKEY_GAME          = 0x0205,  /*遥控器上的游戏键，SMSX自定义*/
    ROC_IRKEY_LAST_CHANNEL  = 314,  /*遥控器上的电视回看键，SMSX自定义*/
    ROC_IRKEY_PAUSE         = 59,  /*遥控器上的暂停按键，SMSX自定义*/
    ROC_IRKEY_HOMEPAGE      = 0x0213,  /*遥控器上的主页面键，SMSX自定义*/
    ROC_IRKEY_MOSAIC        = 0x0214,  /*遥控器上的马赛克键，SMSX自定义*/
    ROC_IRKEY_STOCK         = 0x0215,  /*遥控器上的股票键，SMSX自定义*/
    ROC_IRKEY_VIDEO         = 313,  /*遥控器上的电视键，SMSX自定义*/
    ROC_IRKEY_AUDIO         = 0x0217,  /*遥控器上的广播键，SMSX自定义*/

/*用户自定义按键*/
    ROC_IRKEY_FUN1          = 0x0206,  /*天津项目中代表 :  [视讯] 键 */
    ROC_IRKEY_FUN2          = 0x0207,  /*天津项目中代表 :  [点播] 键 */
    ROC_IRKEY_FUN3          = 0x0301,  /*天津项目中代表 :  [股票] 键 */
    ROC_IRKEY_FUN4          = 0x0302,  /*天津项目中代表 :  [信箱] 键 */
    ROC_IRKEY_FUN5          = 0x0303,  /*天津项目中代表 :  [步进] 键 */
    ROC_IRKEY_FUN6          = 0x0304,  /*天津项目中代表 :  [上一单元] 键 */
    ROC_IRKEY_FUN7          = 0x0305,  /*天津项目中代表 :  [下一单元] 键 */
    ROC_IRKEY_FUN8          = 47,  /*天津项目中代表 :  [停止] 键 */
    ROC_IRKEY_FUN9          = 44,  /*天津项目中代表 :  [快退] 键 */
    ROC_IRKEY_FUN10         = 46,  /*天津项目中代表 :  [快进] 键 */
    ROC_IRKEY_FUN11         = 39,  /*天津项目中代表 :  [播放] 键 */
    ROC_IRKEY_FUN12         = 59,  /*天津项目中代表 :  [暂停/时移] 键 */
    ROC_IRKEY_FUN13         = 82,  /*天津项目中代表 :  [录制] 键 */
    ROC_IRKEY_FUN14         = 0x030C,  /*天津项目中代表 :  [ V+/PIP移动 ] 键 */
    ROC_IRKEY_FUN15         = 0x030D,  /*天津项目中代表 :  [ V-/PIP互换 ] 键 */
    ROC_IRKEY_FUN16         = 0x030E,  /*天津项目中代表 :  [PIP ] 键 */
    ROC_IRKEY_FUN17         = 0x030F,  /*天津项目中代表 :  [预定] 键 */
    ROC_IRKEY_FUN18         = 0x0310,  /*天津项目中代表 :  [全部] 键 */
    ROC_IRKEY_FUN19         = 0x0311,  /*天津项目中代表 :  [] 键 */
    ROC_IRKEY_FUN20         = 319,  /*天津项目中代表 :  # 键 */
    ROC_IRKEY_ASTERISK   = 318,   /*星号键*/
    ROC_IRKEY_INVALID       = 0xffff,  /*未知按键码，SMSX自定义*/
}Roc_Event_e;

#define KT_SYM      0   /*常用系统键类型*/
#define KT_CN       1   /*控制键类型*/
#define KT_SPE      2   /*常用特殊键类型*/
#define KT_NM       3   /*数字按键类型*/
#define KT_CHAR     4   /*字符键类型*/
#define KT_PAD      6   /*数字键盘*/
#define KT_FN       7   /*功能键类型*/
#define KT_LOCK     9   /*Lock类型*/
#define KT_CONL     10  /*左右Shift,左右Ctrl,左右Alt按键*/
#define KT_SYMBOL   11  /*符号类型*/

#define LMD(t,v)    (((t)<<4)+(v))/*计算键值*/

#define KEYVALUE(base,val)  ((base) + (val))
#define KBD_BASE0     (48)
#define KBD_BASE1     (65)
#define KBD_BASE2     (32)
#define KBD_BASE3     (97)
#define KBD_BASE_SPC   (300)

/*键盘按键事件值定义*/
typedef enum Roc_Kbd_Event
{
    ROC_KBDKEY_0            = KEYVALUE(KBD_BASE0, 0),     /*键盘数字键0*/
    ROC_KBDKEY_1            = KEYVALUE(KBD_BASE0, 1),     /*键盘数字键1*/
    ROC_KBDKEY_2            = KEYVALUE(KBD_BASE0, 2),     /*键盘数字键2*/
    ROC_KBDKEY_3            = KEYVALUE(KBD_BASE0, 3),     /*键盘数字键3*/
    ROC_KBDKEY_4            = KEYVALUE(KBD_BASE0, 4),     /*键盘数字键4*/
    ROC_KBDKEY_5            = KEYVALUE(KBD_BASE0, 5),     /*键盘数字键5*/
    ROC_KBDKEY_6            = KEYVALUE(KBD_BASE0, 6),     /*键盘数字键6*/
    ROC_KBDKEY_7            = KEYVALUE(KBD_BASE0, 7),     /*键盘数字键7*/
    ROC_KBDKEY_8            = KEYVALUE(KBD_BASE0, 8),     /*键盘数字键8*/
    ROC_KBDKEY_9            = KEYVALUE(KBD_BASE0, 9),     /*键盘数字键9*/
    
    ROC_KBDKEY_A            = KEYVALUE(KBD_BASE1, 0),   /*键盘字符键'A'*/
    ROC_KBDKEY_B            = KEYVALUE(KBD_BASE1, 1),   /*键盘字符键'B'*/
    ROC_KBDKEY_C            = KEYVALUE(KBD_BASE1, 2),   /*键盘字符键'C'*/
    ROC_KBDKEY_D            = KEYVALUE(KBD_BASE1, 3),   /*键盘字符键'D'*/
    ROC_KBDKEY_E            = KEYVALUE(KBD_BASE1, 4),   /*键盘字符键'E'*/
    ROC_KBDKEY_F            = KEYVALUE(KBD_BASE1, 5),   /*键盘字符键'F'*/
    ROC_KBDKEY_G            = KEYVALUE(KBD_BASE1, 6),   /*键盘字符键'G'*/
    ROC_KBDKEY_H            = KEYVALUE(KBD_BASE1, 7),   /*键盘字符键'H'*/
    ROC_KBDKEY_I            = KEYVALUE(KBD_BASE1, 8),   /*键盘字符键'I'*/
    ROC_KBDKEY_J            = KEYVALUE(KBD_BASE1, 9),  /*键盘字符键'J'*/
    ROC_KBDKEY_K            = KEYVALUE(KBD_BASE1, 10),  /*键盘字符键'K'*/
    ROC_KBDKEY_L            = KEYVALUE(KBD_BASE1, 11),  /*键盘字符键'L'*/
    ROC_KBDKEY_M            = KEYVALUE(KBD_BASE1, 12),  /*键盘字符键'M'*/
    ROC_KBDKEY_N            = KEYVALUE(KBD_BASE1, 13),  /*键盘字符键'N'*/
    ROC_KBDKEY_O            = KEYVALUE(KBD_BASE1, 14),  /*键盘字符键'O'*/
    ROC_KBDKEY_P            = KEYVALUE(KBD_BASE1, 15),  /*键盘字符键'P'*/
    ROC_KBDKEY_Q            = KEYVALUE(KBD_BASE1, 16),  /*键盘字符键'Q'*/
    ROC_KBDKEY_R            = KEYVALUE(KBD_BASE1, 17),  /*键盘字符键'R'*/
    ROC_KBDKEY_S            = KEYVALUE(KBD_BASE1, 18),  /*键盘字符键'S'*/
    ROC_KBDKEY_T            = KEYVALUE(KBD_BASE1, 19),  /*键盘字符键'T'*/
    ROC_KBDKEY_U            = KEYVALUE(KBD_BASE1, 20),  /*键盘字符键'U'*/
    ROC_KBDKEY_V            = KEYVALUE(KBD_BASE1, 21),  /*键盘字符键'V'*/
    ROC_KBDKEY_W            = KEYVALUE(KBD_BASE1, 22),  /*键盘字符键'W'*/
    ROC_KBDKEY_X            = KEYVALUE(KBD_BASE1, 23),  /*键盘字符键'X'*/
    ROC_KBDKEY_Y            = KEYVALUE(KBD_BASE1, 24),  /*键盘字符键'Y'*/
    ROC_KBDKEY_Z            = KEYVALUE(KBD_BASE1, 25),  /*键盘字符键'Z'*/   

    ROC_KBDKEY_A_LC            = KEYVALUE(KBD_BASE3, 0),   /*键盘字符键'a'*/
    ROC_KBDKEY_B_LC            = KEYVALUE(KBD_BASE3, 1),   /*键盘字符键'b'*/
    ROC_KBDKEY_C_LC            = KEYVALUE(KBD_BASE3, 2),   /*键盘字符键'c'*/
    ROC_KBDKEY_D_LC            = KEYVALUE(KBD_BASE3, 3),   /*键盘字符键'd'*/
    ROC_KBDKEY_E_LC            = KEYVALUE(KBD_BASE3, 4),   /*键盘字符键'e'*/
    ROC_KBDKEY_F_LC            = KEYVALUE(KBD_BASE3, 5),   /*键盘字符键'f'*/
    ROC_KBDKEY_G_LC            = KEYVALUE(KBD_BASE3, 6),   /*键盘字符键'g'*/
    ROC_KBDKEY_H_LC            = KEYVALUE(KBD_BASE3, 7),   /*键盘字符键'h'*/
    ROC_KBDKEY_I_LC            = KEYVALUE(KBD_BASE3, 8),   /*键盘字符键'i'*/
    ROC_KBDKEY_J_LC            = KEYVALUE(KBD_BASE3, 9),  /*键盘字符键'j'*/
    ROC_KBDKEY_K_LC            = KEYVALUE(KBD_BASE3, 10),  /*键盘字符键'k'*/
    ROC_KBDKEY_L_LC            = KEYVALUE(KBD_BASE3, 11),  /*键盘字符键'l'*/
    ROC_KBDKEY_M_LC            = KEYVALUE(KBD_BASE3, 12),  /*键盘字符键'm'*/
    ROC_KBDKEY_N_LC            = KEYVALUE(KBD_BASE3, 13),  /*键盘字符键'n'*/
    ROC_KBDKEY_O_LC            = KEYVALUE(KBD_BASE3, 14),  /*键盘字符键'o'*/
    ROC_KBDKEY_P_LC            = KEYVALUE(KBD_BASE3, 15),  /*键盘字符键'p'*/
    ROC_KBDKEY_Q_LC            = KEYVALUE(KBD_BASE3, 16),  /*键盘字符键'q'*/
    ROC_KBDKEY_R_LC            = KEYVALUE(KBD_BASE3, 17),  /*键盘字符键'r'*/
    ROC_KBDKEY_S_LC            = KEYVALUE(KBD_BASE3, 18),  /*键盘字符键's'*/
    ROC_KBDKEY_T_LC            = KEYVALUE(KBD_BASE3, 19),  /*键盘字符键't'*/
    ROC_KBDKEY_U_LC            = KEYVALUE(KBD_BASE3, 20),  /*键盘字符键'u'*/
    ROC_KBDKEY_V_LC            = KEYVALUE(KBD_BASE3, 21),  /*键盘字符键'v'*/
    ROC_KBDKEY_W_LC            = KEYVALUE(KBD_BASE3, 22),  /*键盘字符键'w'*/
    ROC_KBDKEY_X_LC            = KEYVALUE(KBD_BASE3, 23),  /*键盘字符键'x'*/
    ROC_KBDKEY_Y_LC           = KEYVALUE(KBD_BASE3, 24),  /*键盘字符键'y'*/
    ROC_KBDKEY_Z_LC            = KEYVALUE(KBD_BASE3, 25),  /*键盘字符键'z'*/   
    
    ROC_KBDKEY_SPACE                       = KEYVALUE(KBD_BASE2, 0),    /*键盘空格键*/
    ROC_KBDKEY_EXCLAMATION           = KEYVALUE(KBD_BASE2, 1),    /*键盘符号键'!'*/
    ROC_KBDKEY_DAPOSTROPHE          = KEYVALUE(KBD_BASE2, 2),  /*键盘符号键'"'*/
    ROC_KBDKEY_WELL                         = KEYVALUE(KBD_BASE2, 3),               /* 键盘符号键'# '*/
    ROC_KBDKEY_DOLLAR                     = KEYVALUE(KBD_BASE2, 4),      /* 键盘符号键'$'*/
    ROC_KBDKEY_PERCENT                   = KEYVALUE(KBD_BASE2, 5),    /* 键盘符号键'%'*/
    ROC_KBDKEY_AND                           = KEYVALUE(KBD_BASE2, 6),            /* 键盘符号键'&'*/
    ROC_KBDKEY_APOSTROPHE             = KEYVALUE(KBD_BASE2, 7),  /*键盘符号键'''*/
    ROC_KBDKEY_LEFT_PARENTHESIS    = KEYVALUE(KBD_BASE2, 8),    /* 键盘符号键'('*/
    ROC_KBDKEY_RIGHT_PARENTHESIS  = KEYVALUE(KBD_BASE2, 9),          /* 键盘符号键')'*/
    ROC_KBDKEY_ASTERISK                    = KEYVALUE(KBD_BASE2, 10),     /* 键盘符号键'*'*/
    ROC_KBDKEY_PLUS                           = KEYVALUE(KBD_BASE2, 11), /*键盘符号键'+'*/
    ROC_KBDKEY_COMMA                       = KEYVALUE(KBD_BASE2, 12),/*键盘符号键','*/
    ROC_KBDKEY_MINUS                        = KEYVALUE(KBD_BASE2, 13),/*键盘符号键'-'*/
    ROC_KBDKEY_DOT                            = KEYVALUE(KBD_BASE2, 14),/*键盘符号键'.'*/
    ROC_KBDKEY_KPDOT                        = KEYVALUE(KBD_BASE2, 14),   /*数字键盘,'.',运算符*/
    ROC_KBDKEY_SLASH                          = KEYVALUE(KBD_BASE2, 15),/*键盘符号键'/'*/
 
    ROC_KBDKEY_BACKSPACE    = 8,    /*键盘Backspace键*/
    ROC_KBDKEY_TAB          = 9,    /*键盘Tab键*/
    ROC_KBDKEY_ENTER        = 13,   /*键盘Enter键*/
    ROC_KBDKEY_ESC          = 27,    /*键盘ESC键*/

    ROC_KBDKEY_SHIFT_L      = 16,   /*键盘左Shift键*/
    ROC_KBDKEY_SHIFT_R      = 16,   /*键盘右Shift键*/
    ROC_KBDKEY_CTRL_L       = 17,   /*键盘左Ctrl键*/
    ROC_KBDKEY_CTRL_R       = 17,   /*键盘右Ctrl键*/
    ROC_KBDKEY_ALT_L        = 18,   /*键盘左Alt键*/
    ROC_KBDKEY_ALT_R        = 18,   /*键盘右Alt键*/
    ROC_KBDKEY_PAUSE        = 19,     /*键盘Pause键*/
    ROC_KBDKEY_CAPSLOCK     = 20,     /*键盘Caps Lock键*/
    
    ROC_KBDKEY_LEFTBRACE    = 91,  /*键盘符号键'['*/
    ROC_KBDKEY_BACKSLASH    = 92,  /*键盘符号键'\'*/
    ROC_KBDKEY_RIGHTBRACE   = 93,  /*键盘符号键']'*/
    ROC_KBDKEY_XOR           = 94,               /* 键盘符号键'^'*/
    ROC_KBDKEY_UNDERLINE  = 95, /*键盘符号键'_'*/
    ROC_KBDKEY_GRAVE        = 96,   /*键盘符号键'`'*/
    
    ROC_KBDKEY_COLON        = 58,   /*键盘符号键':'*/
    ROC_KBDKEY_SEMICOLON    = 59,/*键盘符号键';'*/
    ROC_KBDKEY_LEFT_ANGLE_BRACKET = 60, /*键盘符号键'<'*/
    ROC_KBDKEY_EQUAL        = 61,/*键盘符号键'='*/
    ROC_KBDKEY_RIGHT_ANGLE_BRACKET = 62,   /*键盘符号键'>'*/
    ROC_KBDKEY_QUESTION = 63,  /*键盘符号键'?'*/
    ROC_KBDKEY_AT           = 64,      /*键盘符号键'@'*/
    
    ROC_KBDKEY_LEFT_BRACE = 123,  /*键盘符号键'{'*/
    ROC_KBDKEY_OR   = 124,             /*键盘符号键'|'*/
    ROC_KBDKEY_RIGHT_BRACE = 125,  /*键盘符号键'}'*/
    ROC_KBDKEY_INVERT = 126,    /*键盘符号键'~'*/
    
    ROC_KBDKEY_NUMLOCK      = 144,   /*键盘Number Lock键*/
    ROC_KBDKEY_SCROLLLOCK   = 145,   /*键盘Scroll Lock键*/

    
    ROC_KBDKEY_PRINTSCREEN  = KEYVALUE(KBD_BASE_SPC, 1),   /*键盘Print Screen键*/
    ROC_KBDKEY_HOME         = KEYVALUE(KBD_BASE_SPC, 2),    /*键盘Home键*/
    ROC_KBDKEY_END          = KEYVALUE(KBD_BASE_SPC, 3),    /*键盘End键*/
    ROC_KBDKEY_INSERT       =  KEYVALUE(KBD_BASE_SPC, 4),   /*键盘Insert键*/
    ROC_KBDKEY_DELETE       = KEYVALUE(KBD_BASE_SPC, 5),   /*键盘Delete键*/
    ROC_KBDKEY_PAGEUP       = KEYVALUE(KBD_BASE_SPC, 6),    /*键盘Page Up键*/
    ROC_KBDKEY_PAGEDOWN     = KEYVALUE(KBD_BASE_SPC, 7),    /*键盘Page Down键*/
    ROC_KBDKEY_UP           = KEYVALUE(KBD_BASE_SPC, 8),    /*键盘上键*/
    ROC_KBDKEY_DOWN         = KEYVALUE(KBD_BASE_SPC, 9),    /*键盘下键*/
    ROC_KBDKEY_LEFT         = KEYVALUE(KBD_BASE_SPC, 10),    /*键盘左键*/
    ROC_KBDKEY_RIGHT        = KEYVALUE(KBD_BASE_SPC, 11),    /*键盘右键*/

    ROC_KBDKEY_F1           = KEYVALUE(KBD_BASE_SPC, 12),     /*键盘功能键F1*/
    ROC_KBDKEY_F2           = KEYVALUE(KBD_BASE_SPC, 13),     /*键盘功能键F2*/
    ROC_KBDKEY_F3           = KEYVALUE(KBD_BASE_SPC, 14),     /*键盘功能键F3*/
    ROC_KBDKEY_F4           = KEYVALUE(KBD_BASE_SPC, 15),     /*键盘功能键F4*/
    ROC_KBDKEY_F5           = KEYVALUE(KBD_BASE_SPC, 16),     /*键盘功能键F5*/
    ROC_KBDKEY_F6           = KEYVALUE(KBD_BASE_SPC, 17),     /*键盘功能键F6*/
    ROC_KBDKEY_F7           = KEYVALUE(KBD_BASE_SPC, 18),     /*键盘功能键F7*/
    ROC_KBDKEY_F8           = KEYVALUE(KBD_BASE_SPC, 19),     /*键盘功能键F8*/
    ROC_KBDKEY_F9           = KEYVALUE(KBD_BASE_SPC, 20),     /*键盘功能键F9*/
    ROC_KBDKEY_F10          = KEYVALUE(KBD_BASE_SPC, 21),     /*键盘功能键F10*/
    ROC_KBDKEY_F11          = KEYVALUE(KBD_BASE_SPC, 22),    /*键盘功能键F11*/
    ROC_KBDKEY_F12          = KEYVALUE(KBD_BASE_SPC, 23),    /*键盘功能键F12*/
    ROC_KBDKEY_F13          = KEYVALUE(KBD_BASE_SPC, 24),    /*键盘功能键F13*/
    ROC_KBDKEY_F14          = KEYVALUE(KBD_BASE_SPC, 25),    /*键盘功能键F14*/
    ROC_KBDKEY_F15          = KEYVALUE(KBD_BASE_SPC, 26),    /*键盘功能键F15*/
    ROC_KBDKEY_F16          = 127,    /*键盘功能键F16*/

    ROC_KBDKEY_KP0          = KEYVALUE(KBD_BASE_SPC, 27),    /*数字键盘,数字键0*/
    ROC_KBDKEY_KP1          = KEYVALUE(KBD_BASE_SPC, 28),    /*数字键盘,数字键1*/
    ROC_KBDKEY_KP2          = KEYVALUE(KBD_BASE_SPC, 29),    /*数字键盘,数字键2*/
    ROC_KBDKEY_KP3          = KEYVALUE(KBD_BASE_SPC, 30),    /*数字键盘,数字键3*/
    ROC_KBDKEY_KP4          = KEYVALUE(KBD_BASE_SPC, 31),    /*数字键盘,数字键4*/
    ROC_KBDKEY_KP5          = KEYVALUE(KBD_BASE_SPC, 32),    /*数字键盘,数字键5*/
    ROC_KBDKEY_KP6          = KEYVALUE(KBD_BASE_SPC, 33),    /*数字键盘,数字键6*/
    ROC_KBDKEY_KP7          = KEYVALUE(KBD_BASE_SPC, 34),    /*数字键盘,数字键7*/
    ROC_KBDKEY_KP8          = KEYVALUE(KBD_BASE_SPC, 35),    /*数字键盘,数字键8*/
    ROC_KBDKEY_KP9          = KEYVALUE(KBD_BASE_SPC, 36),    /*数字键盘,数字键9*/
    ROC_KBDKEY_KPDIVIDE     = KEYVALUE(KBD_BASE_SPC, 37),   /*数字键盘,'/',运算键除*/
    ROC_KBDKEY_KPMULTIPLY   = KEYVALUE(KBD_BASE_SPC, 38),   /*数字键盘,'*',运算键乘*/
    ROC_KBDKEY_KPMINUS      = KEYVALUE(KBD_BASE_SPC, 39),   /*数字键盘,'-',运算键减*/
    ROC_KBDKEY_KPPLUS       = KEYVALUE(KBD_BASE_SPC, 40),   /*数字键盘,'+',运算键加*/
    
    ROC_KBDKEY_META_L       = KEYVALUE(KBD_BASE_SPC, 50),  /*键盘左window键*/
    ROC_KBDKEY_META_R       = KEYVALUE(KBD_BASE_SPC, 51),  /*键盘右window键*/
    ROC_KBDKEY_COMPOSE      = KEYVALUE(KBD_BASE_SPC, 52),  /*键盘上鼠标右键功能键*/
    ROC_KBDKEY_CLEAR        = KEYVALUE(KBD_BASE_SPC, 53),   /*键盘Clear键*/
    ROC_KBDKEY_PRINT        = KEYVALUE(KBD_BASE_SPC, 54),   /*键盘Print键*/
    ROC_KBDKEY_EXECUTE      = KEYVALUE(KBD_BASE_SPC, 55),   /*键盘Execute键*/
    ROC_KBDKEY_HELP         = KEYVALUE(KBD_BASE_SPC, 56),   /*键盘Help键*/
    ROC_KBDKEY_F17          = KEYVALUE(KBD_BASE_SPC, 57),    /*键盘功能键F17*/
    ROC_KBDKEY_F18          = KEYVALUE(KBD_BASE_SPC, 58),    /*键盘功能键F18*/
    ROC_KBDKEY_F19          = KEYVALUE(KBD_BASE_SPC, 59),    /*键盘功能键F19*/
    ROC_KBDKEY_F20          = KEYVALUE(KBD_BASE_SPC, 60),    /*键盘功能键F20*/
    ROC_KBDKEY_SYSRQ        = KEYVALUE(KBD_BASE_SPC, 61),   /*键盘SysRq键*/
    ROC_KBDKEY_MUTE         = KEYVALUE(KBD_BASE_SPC, 62),   /*键盘静音键*/
    ROC_KBDKEY_VOLUMEDOWN   = KEYVALUE(KBD_BASE_SPC, 63),   /*键盘音量-键*/
    ROC_KBDKEY_VOLUMEUP     = KEYVALUE(KBD_BASE_SPC, 64),   /*键盘音量+键*/
    ROC_KBDKEY_POWER        = KEYVALUE(KBD_BASE_SPC, 65),   /*键盘Power键*/
}Roc_Kbd_Event_e;

/*事件回调函数定义*/
typedef INT32_T (*rocme_porting_event_callback) ( void *param, Roc_Evt_Input_e input, UINT32_T event, Roc_Evt_KeyAct_e act );

/*事件注册参数结构定义*/
typedef struct Roc_Evt_Param
{
    rocme_porting_event_callback    callback;   /*事件回调函数*/
    void                            *cb_param;  /*回调函数的私有参数*/
}Roc_Evt_Param_t;

/*鼠标动作类型*/
typedef enum Roc_Mouse_Act
{
    ROC_MOUSE_DOWN = 0x0000,  /*鼠标按下事件*/
    ROC_MOUSE_UP  = 0x0001,      /*鼠标弹起事件*/
    ROC_MOUSE_CLICK = 0x0002,    /*鼠标单击事件*/
    ROC_MOUSE_DBCLICK = 0x0003,  /*鼠标双击事件*/
    ROC_MOUSE_MOVED = 0x0004,    /*鼠标的移动事件*/
    ROC_MOUSE_WHEEL     = 0x0005   /*鼠标滚轮滚动*/
}Roc_Mouse_Act_e;

typedef enum Roc_Mouse_Type
{
	ROC_MOUSE_LEFT				= 1,              /*鼠标左键*/
	ROC_MOUSE_RIGHT 			= 2,              /*鼠标右键*/
	ROC_MOUSE_MIDDLE			= 4,             /*鼠标中键*/
	ROC_MOUSE_WHEEL_UP		= 8,              /*鼠标滚轮向上*/
	ROC_MOUSE_WHEEL_DOWN	= 16,              /*鼠标滚轮向下*/
	ROC_MOUSE_NULL				= 32,              /*无类型*/
}Roc_Mouse_Type_e;

/*鼠标事件类型定义*/
typedef struct Roc_Mouse_Event
{
    Roc_Mouse_Act_e act;  /*鼠标动作类型*/
    Roc_Mouse_Type_e eType;   /*鼠标按键值*/
    INT32_T x;            /*当前鼠标横坐标（针对屏幕）*/
    INT32_T y;            /*当前鼠标纵坐标（针对屏幕）*/
}Roc_Mouse_Event_t;


/*遥控器类型*/
typedef enum Roc_KeyBoard_Type
{
    ROC_KEYBOARD_TYPE_DEFAULT           = 0x0000,  /*默认版本    */
    ROC_KEYBOARD_TYPE_1                 = 0x0001,  /*创维长虹版本*/
    ROC_KEYBOARD_TYPE_2                 = 0x0002,  /*TCB版本*/
    ROC_KEYBOARD_TYPE_NUM               = 0x0003,  /*版本number*/
}Roc_KeyBoard_Type_e;


/*鼠标事件回调函数定义*/
typedef INT32_T (*rocme_porting_mouse_evt_callback) ( void *param,Roc_Mouse_Event_t event );

/*鼠标事件注册参数结构定义*/
typedef struct Roc_Mouse_Param
{
    rocme_porting_mouse_evt_callback    callback;   /*鼠标事件回调函数*/
    void                                *cb_param;  /*回调函数的私有参数*/
}Roc_Mouse_Param_t;


/*即插即用事件结构定义*/
typedef enum Roc_PlugPlay_Event
{
    ROC_KB_PLUGIN       = 0x0001, // 键盘插入
    ROC_KB_PULLOUT      = 0x0002, // 键盘拔除
    ROC_MOUSE_PLUGIN    = 0x0003, // 鼠标插入
    ROC_MOUSE_PULLOUT   = 0x0004,  // 鼠标拔除
}Roc_PlugPlay_Event_t;

/*即插即用事件回调函数定义*/
typedef INT32_T (*rocme_porting_plug_play_callback) ( void *param, Roc_PlugPlay_Event_t event);


/*即插即用事件注册参数结构定义*/
typedef struct Roc_PlugPlay_Param
{
    rocme_porting_plug_play_callback    callback;   /*即插即用事件回调函数*/
    void                                *cb_param;  /*回调函数的私有参数*/
}Roc_PlugPlay_Param_t;
 


/*++++++++++++++++++++++++++++     输入法宏定义    ++++++++++++++++++++++++++++*/
//切换输入法的按键,各厂家可自行定义。
//不可采用数字键,方向键,确定键,上翻页,下翻页(输入法需要使用)
//不可采用ROC_IRKEY_BLUE ,ROC_IRKEY_YELLOW,(浏览器需要使用)
//#define ROC_IRKEY_IME ROC_IRKEY_RED
#define ROC_IRKEY_IME ROC_IRKEY_FUN20  //使用遥控器的#号键


/*++++++++++++++++++++++++++++    FUNCTIONS    ++++++++++++++++++++++++++++*/

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
INT32_T rocme_porting_event_register(const Roc_Evt_Param_t evt_param,UINT32_T *handler);

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
INT32_T rocme_porting_event_unregister(const UINT32_T handler);

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
INT32_T rocme_porting_mouse_register( const Roc_Mouse_Param_t mouse_param,UINT32_T *handler );

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
INT32_T rocme_porting_mouse_unregister( const UINT32_T handler );


 
/**************************************************************************
函数名称: 
            rocme_porting_plug_play_register
功能说明: 
            向机顶盒注册一个即插即用事件的监听要求
参数说明：
    输入参数：
            [ evt_param   ] : 事件监听参数，包括回调函数以及私有参数
    输出参数：
            [ handler     ] : 此注册监听的控制句柄
返    回： 
    成功 : 0            ( 注册监听即插即用事件成功 )
    失败 : -1 或 错误码 ( 注册监听即插即用事件失败 )
修改记录：
**************************************************************************/
INT32_T rocme_porting_plug_play_register(const Roc_PlugPlay_Param_t evt_param,UINT32_T *handler);


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
INT32_T rocme_porting_mouse_set_coordinate( const UINT32_T x,const UINT32_T y );

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
