/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
 File Name     : hi_unf_ecs_type.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2008/6/5
Last Modified :
Description   : ECS API接口
Function List :
History       :
 ******************************************************************************/
#ifndef __HI_UNF_ECS_TYPE_H__
#define __HI_UNF_ECS_TYPE_H__

#include "hi_common.h"
#include "hi_error_ecs.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define HI_I2C_MAX_NUM_USER      15 /**< 最大I2C通道号*/

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_1 */
/** @{ */  /** <!-- 【QAM】 */

/**QAM调制方式*/
typedef enum hiUNF_QAM_TYPE_E
{
    HI_UNF_MOD_TYPE_DEFAULT,                /**<默认的QAM类型, 当前系统默认为HI_UNF_MOD_TYPE_QAM_64 */
    HI_UNF_MOD_TYPE_QAM_16 = 0x100,         /**<16QAM对应的枚举值*/
    HI_UNF_MOD_TYPE_QAM_32,                 /**<32QAM对应的枚举值*/
    HI_UNF_MOD_TYPE_QAM_64,                 /**<64QAM对应的枚举值*/
    HI_UNF_MOD_TYPE_QAM_128,                /**<128QAM对应的枚举值*/
    HI_UNF_MOD_TYPE_QAM_256,                /**<256QAM对应的枚举值*/
    HI_UNF_MOD_TYPE_QAM_512,                /**<512QAM对应的枚举值*/

    HI_UNF_MOD_TYPE_BPSK = 0x200,           /**<BPSK QAM对应的枚举值，暂不支持*/
    HI_UNF_MOD_TYPE_QPSK = 0x300,           /**<QPSK QAM对应的枚举值，暂不支持*/

    HI_UNF_MOD_TYPE_BUTT                    /**<非法的QAM类型枚举值*/
}HI_UNF_MODULATION_TYPE_E;

/**TUNER锁频状态*/
typedef enum  hiUNF_TUNER_LOCK_STATUS_E
{
    HI_UNF_TUNER_SIGNAL_DROPPED = 0,        /**<信号未锁定*/
    HI_UNF_TUNER_SIGNAL_LOCKED,             /**<信号已锁定*/
    HI_UNF_TUNER_SIGNAL_BUTT                /**<非法边界值*/
}HI_UNF_TUNER_LOCK_STATUS_E;

/**TUNER输出模式 */
typedef enum hiUNF_TUNER_OUTPUT_MODE_E
{
    HI_UNF_TUNER_OUTPUT_MODE_DEFAULT ,              /**<默认模式*/
    HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A,       /**<并行模式A*/
    HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_B,       /**<并行模式B*/
    HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_C,       /**<并行模式C*/
    HI_UNF_TUNER_OUTPUT_MODE_SERIAL,                /**<串行模式*/
    HI_UNF_TUNER_OUTPUT_MODE_BUTT                   /**<非法值*/
}HI_UNF_TUNER_OUPUT_MODE_E;

/**TUNER信号类型*/
typedef enum    hiTUNER_SIG_TYPE_E
{
    HI_UNF_TUNER_SIG_TYPE_CAB = 0  ,     /**<CABLE信号*/
    HI_UNF_TUNER_SIG_TYPE_TER  ,         /**<地面信号*/
    HI_UNF_TUNER_SIG_TYPE_SAT ,          /**<卫星信号*/
    HI_UNF_TUNER_SIG_TYPE_BUTT           /**<非法值*/
}HI_UNF_TUNER_SIG_TYPE_E;

/**TUNER使用的I2C通道*/
typedef enum hiUNF_TUNER_I2cChannel
{
    HI_UNF_I2C_CHANNEL_0 = 0,           /**<I2C通道0*/
    HI_UNF_I2C_CHANNEL_1,               /**<I2C通道1*/
    HI_UNF_I2C_CHANNEL_2,               /**<I2C通道2*/
    HI_UNF_I2C_CHANNEL_3,               /**<I2C通道3*/
    HI_UNF_I2C_CHANNEL_QAM = 4,         /**<内置QAM专用I2C通道 */
    HI_UNF_I2C_CHANNEL_5,               /**GPIO模拟I2C*/
    HI_UNF_I2C_CHANNEL_6,               
    HI_UNF_I2C_CHANNEL_7,
    HI_UNF_I2C_CHANNEL_8,               
    HI_UNF_I2C_CHANNEL_9,               
    HI_UNF_I2C_CHANNEL_10,
    HI_UNF_I2C_CHANNEL_11,               
    HI_UNF_I2C_CHANNEL_12,               
    HI_UNF_I2C_CHANNEL_13,
    HI_UNF_I2C_CHANNEL_14,               
    HI_UNF_I2C_CHANNEL_15,               
    HI_UNF_I2C_CHANNEL_MAX              /**<非法边界值*/
}HI_UNF_TUNER_I2cChannel_E;

/**TUNER设备类型*/
typedef enum    hiUNF_TUNER_DEV_TYPE_E
{
    HI_UNF_TUNER_DEV_TYPE_CU1216 = 0X100,       /**<CU1216*/
    HI_UNF_TUNER_DEV_TYPE_ALPS_TDE_3 ,          /**<ALPS_TDE_3*/
    HI_UNF_TUNER_DEV_TYPE_ALPS_TDE_5 ,          /**<ALPS_TDE_5*/
    HI_UNF_TUNER_DEV_TYPE_TMX70600,             /**<TMX70600*/
    HI_UNF_TUNER_DEV_TYPE_XG_3BL,               /**<XG_3BL*/
    HI_UNF_TUNER_DEV_TYPE_CD1616,               /**<CD1616*/
    HI_UNF_TUNER_DEV_TYPE_ALPS,                 /**<ALPS*/
    HI_UNF_TUNER_DEV_TYPE_ALPS_TDAE,            /**<ALPS_TDAE*/
    HI_UNF_TUNER_DEV_TYPE_1026,                 /**<1026*/
    HI_UNF_TUNER_DEV_TYPE_0297,                 /**<0297*/
    HI_UNF_TUNER_DEV_TYPE_TDCC,                 /**<TDCC*/
    HI_UNF_TUNER_DEV_TYPE_TDA18250,             /**<TDA18250*/
    HI_UNF_TUNER_DEV_TYPE_TDA18251,             /**<TDA18251*/
    HI_UNF_TUNER_DEV_TYPE_CD1616_LF_GIH_4,      /**<CD1616_LF_GIH_4*/
    HI_UNF_TUNER_DEV_TYPE_MXL203,               /**< MXL203 */
    HI_UNF_TUNER_DEV_TYPE_CD1616_DOUBLE,
    HI_UNF_TUNER_DEV_TYPE_RT810,
    HI_UNF_TUNER_DEV_TYPE_EN4020,
    HI_UNF_TUNER_DEV_TYPE_MT2066,
    HI_UNF_TUNER_DEV_TYPE_MT2081,
    HI_UNF_TUNER_DEV_TYPE_DTT5_E20 = 0x200 ,    /**<DTT5_E20*/
    HI_UNF_TUNER_DEV_TYPE_TMX7070X,             /**<THOMSON7070X*/

    HI_UNF_TUNER_DEV_TYPE_BUTT,                 /**<非法边界值*/
}HI_UNF_TUNER_DEV_TYPE_E ;

/**QAM设备类型*/
typedef enum    hiUNF_DEMOD_DEV_TYPE_E
{
    HI_UNF_DEMOD_DEV_TYPE_NONE,                 /**<不支持*/  
    HI_UNF_DEMOD_DEV_TYPE_3130I= 0x100,         /**<内部QAM*/
    HI_UNF_DEMOD_DEV_TYPE_3130E,                /**<外部Hi3130芯片*/

    HI_UNF_DEMOD_DEV_TYPE_PHILIP = 0x200,       /**<PHILIP*/
    HI_UNF_DEMOD_DEV_TYPE_ST,                   /**<ST*/
    HI_UNF_DEMOD_DEV_TYPE_GX,                   /**<GX*/

    HI_UNF_DEMOD_DEV_TYPE_BUTT,                 /**<非法边界值*/
}HI_UNF_DEMOD_DEV_TYPE_E ;

/**定义CABLE传输信号*/
typedef struct  hiUNF_CAB_CONNECT_PARA_S
{
    HI_U32                      u32Freq;             /**<频率，单位：kHz*/
    HI_U32                      u32SymbolRate ;      /**<符号率，单位bps */
    HI_UNF_MODULATION_TYPE_E    enModType ;          /**<QAM调制方式*/
    HI_BOOL                     bReverse ;           /**<频谱倒置处理方式*/
}HI_UNF_CAB_CONNECT_PARA_S ;

/*暂未使用*/
typedef enum hiUNF_TUNER_FE_GUARD_INTV_E
{
    HI_UNF_TUNER_FE_GUARD_INTV_DEFALUT = 0 ,    /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_32       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_16       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_8        ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_4        ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_BUTT     ,       /**< */
}HI_UNF_TUNER_FE_GUARD_INTV_E;

/*暂未使用*/
typedef enum hiUNF_TUNER_FE_DEPUNC_RATE_E
{
    HI_UNF_TUNER_FE_DEPUNC_RATE_DEFAULT = 0 ,    /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_12      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_23      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_34      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_45      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_56      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_67      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_78      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_89      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_BUTT    ,        /**< */
}HI_UNF_TUNER_FE_DEPUNC_RATE_E ;

/*暂未使用*/
typedef enum hiUNF_TUNER_FE_FFT_E
{
    HI_UNF_TUNER_FE_FFT_DEFAULT = 0,   /**< */
    HI_UNF_TUNER_FE_FFT_2K ,           /**< */
    HI_UNF_TUNER_FE_FFT_8K ,           /**< */
    HI_UNF_TUNER_FE_FFT_BUTT ,         /**< */
}HI_UNF_TUNER_FE_FFT_E;

/*暂未使用*/
typedef enum hiUNF_TUNER_FE_HIERARCHY_E
{
    HI_UNF_TUNER_FE_HIERARCHY_DEFAULT = 0 ,   /**< */
    HI_UNF_TUNER_FE_HIERARCHY_NO,             /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA1,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA2,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA4,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_BUTT,           /**< */
}HI_UNF_TUNER_FE_HIERARCHY_E ;

/*暂未使用*/
typedef struct  hiUNF_TER_CONNECT_PARA_S
{
    HI_U32          u32Freq     ;                    /**< */
    HI_U32          u32BandWidth    ;                /**< */
    HI_UNF_MODULATION_TYPE_E enModType  ;      /**< */
}HI_UNF_TER_CONNECT_PARA_S ;

/*暂未使用*/
typedef struct  hiUNF_TUNER_TER_ATTR_S
{
    HI_UNF_TUNER_FE_DEPUNC_RATE_E   enHpCode ;      /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_E   enLpCode ;      /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_E    enGuardIntv ;   /**< */
    HI_UNF_TUNER_FE_FFT_E       enFftType ;           /**< */
    HI_UNF_TUNER_FE_HIERARCHY_E enHierType ;      /**< */

}HI_UNF_TUNER_TER_ATTR_S;


/**TUNER属性*/
typedef struct  hiTUNER_ATTR_S
{
    HI_UNF_TUNER_SIG_TYPE_E     enSigType ;          /**<信号类型*/
    HI_UNF_TUNER_DEV_TYPE_E     enTunerDevType ;     /**<TUNER类型*/
    HI_UNF_DEMOD_DEV_TYPE_E     enDemodDevType ;     /**<QAM类型*/
    HI_UNF_TUNER_OUPUT_MODE_E   enOutputMode ;       /**<TS流输出模式*/
    HI_UNF_TUNER_I2cChannel_E   enI2cChannel;        /**<TUNER使用的I2C通道*/

    union{
        HI_UNF_TUNER_TER_ATTR_S stTer ;         /**<地面信号属性，暂不支持*/
    }unTunerAttr ;
}HI_UNF_TUNER_ATTR_S ;

/**TUNER锁频参数*/
typedef struct  hiUNF_TUNER_CONNECT_PARA_S
{
    HI_UNF_TUNER_SIG_TYPE_E enSigType ;         /**<信号类型*/

    union
    {
        HI_UNF_CAB_CONNECT_PARA_S   stCab ;     /**<CABLE传输信号*/
        HI_UNF_TER_CONNECT_PARA_S   stTer ;     /**<地面传输信号*/
    }unConnectPara;
}HI_UNF_TUNER_CONNECT_PARA_S ;

/**TUNER锁频状态和锁频参数*/
typedef struct  hiUNF_TUNER_STATUS_S
{
    HI_UNF_TUNER_LOCK_STATUS_E  enLockStatus ;      /**<锁频状态*/
    HI_UNF_TUNER_CONNECT_PARA_S stConnectPara;      /**<实际锁频参数*/
}HI_UNF_TUNER_STATUS_S ;

/** @} */  /** <!-- ==== Structure Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_3 */
/** @{ */  /** <!-- 【SCI】 */

/**SCICLK引脚输出配置*/
typedef enum  hiUNF_SCI_CLK_MODE_E
{
    HI_UNF_SCI_CLK_MODE_CMOS = 0,   /**<CMOS输出*/
    HI_UNF_SCI_CLK_MODE_OD,         /**<OD输出*/
    HI_UNF_SCI_CLK_MODE_BUTT
}HI_UNF_SCI_CLK_MODE_E;

/** SCI 端口 */
typedef enum hiUNF_SCI_PORT_E
{
    HI_UNF_SCI_PORT0,        /**< SCI端口0*/
    HI_UNF_SCI_PORT1,        /**< SCI端口1*/
    HI_UNF_SCI_PORT_BUTT     
}HI_UNF_SCI_PORT_E;

/** 智能卡状态 */
typedef enum hiUNF_SCI_STATUS_E
{
    HI_UNF_SCI_STATUS_UNINIT     = 0,           /**< SCI未初始化 */
    HI_UNF_SCI_STATUS_FIRSTINIT,                /**< SCI初始化过程中*/
    HI_UNF_SCI_STATUS_NOCARD,                   /**< 无卡 */
    HI_UNF_SCI_STATUS_INACTIVECARD,             /**<卡未完成激活（卡无效） */
 //   HI_UNF_SCI_STATUS_CARDFAULT,		     /*卡故障*/
    HI_UNF_SCI_STATUS_WAITATR,                  /**<等待ATR*/
    HI_UNF_SCI_STATUS_READATR,                  /**<正在接收ATR*/
    HI_UNF_SCI_STATUS_READY,                    /**<卡可以使用（卡激活） */
    HI_UNF_SCI_STATUS_RX,                       /**<卡忙（接收数据中） */
    HI_UNF_SCI_STATUS_TX                        /**<卡忙（发送数据中） */
} HI_UNF_SCI_STATUS_E;

/** SCI 协议 */
typedef enum hiUNF_SCI_PROTOCOL_E
{
    HI_UNF_SCI_PROTOCOL_T0,     /**<7816 T0 协议 */
    HI_UNF_SCI_PROTOCOL_T1,     /**<7816 T1 协议 */
    HI_UNF_SCI_PROTOCOL_T14 ,   /**<7816 T14 协议 */
    HI_UNF_SCI_PROTOCOL_BUTT
}HI_UNF_SCI_PROTOCOL_E;

/**SCI有效电平*/
typedef enum hiUNF_SCI_LEVEL_E
{
    HI_UNF_SCI_LEVEL_LOW,      /**<低电平有效 */
    HI_UNF_SCI_LEVEL_HIGH,     /**<高电平有效 */
    HI_UNF_SCI_LEVEL_BUTT      
}HI_UNF_SCI_LEVEL_E ;

/**SCI 系统参数 */
typedef struct hiUNF_SCI_PARAMS_S
{
	HI_UNF_SCI_PORT_E enSciPort;			/**<SCI 端口号 */
	HI_UNF_SCI_PROTOCOL_E enProtocolType;/**<使用的协议类型 */
	HI_U32 ActalClkRate;		/**<实际的F 值时钟转换因子 */
	HI_U32 ActalBitRate;		/**<实际的D 值比特率转换因子 */
	HI_U32 Fi;				/**<ATR 返回的时钟因子 */
	HI_U32 Di;				/**<ATR 返回的比特率因子 */
	HI_U32 GuardDelay;		/**<N 值额外增加的保护时间*/
	HI_U32 CharTimeouts;		/**<T0 或T1的字符超时时间*/
	HI_U32 BlockTimeouts;	/**<T1的块超时时间*/
	HI_U32 TxRetries;			/**<发送重试次数*/
}HI_UNF_SCI_PARAMS_S,*HI_UNF_SCI_PARAMS_S_PTR;


/** @} */  /** <!-- ==== Structure Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_4 */
/** @{ */  /** <!-- 【E2PROM】 */

/**E2PROM型号定义*/
typedef enum hiUNF_E2PROM_CHIP_E
{
    HI_UNF_E2PROM_CHIP_AT24C01,    /**<E2PROM型号：AT24C01 */
    HI_UNF_E2PROM_CHIP_AT24C02,    /**<E2PROM型号：AT24C02 */
    HI_UNF_E2PROM_CHIP_AT24C04,    /**<E2PROM型号：AT24C04 */
    HI_UNF_E2PROM_CHIP_AT24C08,    /**<E2PROM型号：AT24C08 */
    HI_UNF_E2PROM_CHIP_AT24C16,    /**<E2PROM型号：AT24C16 */
    HI_UNF_E2PROM_CHIP_AT24C32,    /**<E2PROM型号：AT24C32 */
    HI_UNF_E2PROM_CHIP_AT24C64,    /**<E2PROM型号：AT24C64 */
    HI_UNF_E2PROM_CHIP_AT24C128,   /**<E2PROM型号：AT24C128 */
    HI_UNF_E2PROM_CHIP_AT24C256,   /**<E2PROM型号：AT24C256 */
    HI_UNF_E2PROM_CHIP_M24LC01,    /**<E2PROM型号：M24LC01 */
    HI_UNF_E2PROM_CHIP_M24LC02,    /**<E2PROM型号：M24LC02 */
    HI_UNF_E2PROM_CHIP_M24LC04,    /**<E2PROM型号：M24LC04 */
    HI_UNF_E2PROM_CHIP_M24LC08,    /**<E2PROM型号：M24LC08 */
    HI_UNF_E2PROM_CHIP_M24LC16,    /**<E2PROM型号：M24LC16 */
    HI_UNF_E2PROM_CHIP_M24LC32,    /**<E2PROM型号：M24LC32 */
    HI_UNF_E2PROM_CHIP_M24LC64,    /**<E2PROM型号：M24LC64 */
    HI_UNF_E2PROM_CHIP_M24LC128,   /**<E2PROM型号：M24LC128 */
    HI_UNF_E2PROM_CHIP_M24LC256,   /**<E2PROM型号：M24LC256 */

    HI_UNF_E2PROM_CHIP_BUTT
}HI_UNF_E2PROM_CHIP_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_5 */
/** @{ */  /** <!-- 【IR】 */

/**IR支持的码型*/
typedef enum hiUNF_IR_CODE_E
{
    HI_UNF_IR_CODE_NEC_SIMPLE = 0,  /**<NEC with simple repeat code码型*/
    HI_UNF_IR_CODE_TC9012,          /**<TC9012码型*/
    HI_UNF_IR_CODE_NEC_FULL,        /**<NEC with full repeat code码型*/
    HI_UNF_IR_CODE_SONY_12BIT,      /**<SONY 12BIT码型*/
    HI_UNF_IR_CODE_RAW,      		/**<raw 码型*/
    HI_UNF_IR_CODE_BUTT
}HI_UNF_IR_CODE_E;


/**IR码型列表,HI_UNF_IR_STD部分请参照HI_UNF_IR_CODE_E */
typedef enum hiUNF_IR_PROTOCOL_E
{
    HI_UNF_IR_NEC,
	HI_UNF_IR_RC6A=10,
	HI_UNF_IR_RC5,	
    HI_UNF_IR_LOW_LATENCY_PROTOCOL,
    HI_UNF_IR_RC6_MODE0,         /*  for RC6 mode 0 */
    HI_UNF_IR_RCMM,              /*  for RCMM 24 /32 Protocol */
    HI_UNF_IR_RUWIDO,            /*  for Ruwido protocol */
    HI_UNF_IR_RCRF8,             /*  for RCRF8 protocol */
    HI_UNF_IR_MULTIPLE,         /*  for multiple protocol support*/
    HI_UNF_IR_RMAP,             /*  for RMAP protocol with Mancester coding*/
   	HI_UNF_IR_RSTEP,            /*  for RSTEP protocol */
    HI_UNF_IR_RMAP_DOUBLEBIT,    /*  for RMAP protocol with Double bit coding*/
    HI_UNF_IR_LOW_LATENCY_PRO_PROTOCOL,
    HI_UNF_IR_XMP,
    HI_UNF_IR_USER_DEFINED
} HI_UNF_IR_PROTOCOL_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_6 */
/** @{ */  /** <!-- 【KEYLED】 */

/**KEYLED类型 */
typedef enum  hiUNF_KEYLED_TYPE_E
{
    HI_UNF_KEYLED_TYPE_STD = 0x0,  /**<海思芯片自带的KEYLED类型 */
    HI_UNF_KEYLED_TYPE_PT6961,     /**<KEYLED型号：PT6961 */
    HI_UNF_KEYLED_TYPE_CT1642,     /**<KEYLED型号：CT1642 */
    HI_UNF_KEYLED_TYPE_PT6964,     /**<KEYLED型号：PT6964 */
    HI_UNF_KEYLED_TYPE_BUTT        /**< */
}HI_UNF_KEYLED_TYPE_E;

/**按键状态 */
typedef enum  hiUNF_KEY_STATUS_E
{
    HI_UNF_KEY_STATUS_DOWN = 0 ,    /**<按下按键 */
    HI_UNF_KEY_STATUS_HOLD ,        /**<按住不动 */
    HI_UNF_KEY_STATUS_UP ,          /**<抬起按键 */

    HI_UNF_KEY_STATUS_BUTT
}HI_UNF_KEY_STATUS_E ;

/**LED闪烁频率级别*/
typedef enum hiUNF_KEYLED_LEVEL_E
{
    HI_UNF_KEYLED_LEVEL_1 = 0x01,     /**<级别1,闪烁频率最慢*/
    HI_UNF_KEYLED_LEVEL_2,            /**<级别2 */
    HI_UNF_KEYLED_LEVEL_3,            /**<级别3 */
    HI_UNF_KEYLED_LEVEL_4,            /**<级别4 */
    HI_UNF_KEYLED_LEVEL_5,            /**<级别5 , 闪烁频率最快*/

    HI_UNF_KEYLED_LEVEL_BUTT
}HI_UNF_KEYLED_LEVEL_E;

/**闪烁的LED序号*/
typedef enum hiUNF_KEYLED_LIGHT_E
{
    HI_UNF_KEYLED_LIGHT_1 = 0x01,     /**<第1个LED闪烁*/
    HI_UNF_KEYLED_LIGHT_2,            /**<第2个LED闪烁*/
    HI_UNF_KEYLED_LIGHT_3,            /**<第3个LED闪烁*/
    HI_UNF_KEYLED_LIGHT_4,            /**<第4个LED闪烁*/
    HI_UNF_KEYLED_LIGHT_ALL,          /**<*所有LED均闪烁*/
    HI_UNF_KEYLED_LIGHT_NONE,         /**<所有LED均不闪烁*/

    HI_UNF_KEYLED_LIGHT_BUTT
}HI_UNF_KEYLED_LIGHT_E;

/**LED显示时间*/
typedef struct hiUNF_KEYLED_Time_S
{
    HI_U32 u32Hour;             /**<时*/
    HI_U32 u32Minute;           /**<分*/
}HI_UNF_KEYLED_TIME_S, *HI_UNF_KEYLED_TIME_S_PTR;

/** @} */  /** <!-- ==== Structure Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_7 */
/** @{ */  /** <!-- 【ARM MODE】 */

/**ARM所处的模式*/
typedef enum hiUNF_PMOC_MODE_E
{
    HI_UNF_PMOC_MODE_NORMAL = 0,    /**<NORMAL*/
    HI_UNF_PMOC_MODE_SLOW,          /**<SLOW*/
    HI_UNF_PMOC_MODE_DOZE,          /**<DOZE*/
    HI_UNF_PMOC_MODE_SLEEP,         /**<SLEEP*/

    HI_UNF_PMOC_MODE_BUTT
}HI_UNF_PMOC_MODE_E;
/** @} */  /** <!-- ==== Structure Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_8 */
/** @{ */  /** <!-- 【PM】 */

/**待机被唤醒的类型 */
typedef enum hiUNF_PMOC_ACTUAL_WKUP_E
{
     HI_UNF_PMOC_WKUP_IR  =0,      /**<被IR唤醒 */
     HI_UNF_PMOC_WKUP_KEYLED,      /**<被前面板KEY唤醒 */
     HI_UNF_PMOC_WKUP_TIMEOUT,     /**<被定时中断唤醒 */
     HI_UNF_PMOC_WKUP_BUTT        
}HI_UNF_PMOC_ACTUAL_WKUP_E;

typedef enum hiUNF_PMOC_SCENE_E
{
     HI_UNF_PMOC_SCENE_STANDARD  =0,  /**<标准场景 */
     HI_UNF_PMOC_SCENE_ETH,           /**<网口转发场景 */
     HI_UNF_PMOC_SCENE_PHONE,         /**<通话场景 */
     HI_UNF_PMOC_SCENE_BUTT        
}HI_UNF_PMOC_SCENE_E;

#define PMOC_WKUP_IRKEY_MAXNUM    6
/**待机唤醒的条件定义*/
typedef struct hiUNF_PMOC_WKUP_S
{
    HI_U32 u32IrPmocNum;					/**<能够支持power键值个数，raw 型红外遥控: 不能超越PMOC_WKUP_IRKEY_MAXNUM(<=5)宏定义所述个数键值，其余类型只能支持一个键值*/
    HI_U32 u32IrPowerKey0[PMOC_WKUP_IRKEY_MAXNUM];		/**<红外遥控 power 低位键值 */
    HI_U32 u32IrPowerKey1[PMOC_WKUP_IRKEY_MAXNUM];		/**<红外遥控 power 高位键值 */
    HI_U32 u32KeypadPowerKey;   				/**<按键 power   键值 */
    HI_U32 u32WakeUpTime ; 					/**<唤醒定时时间 ,单位为 秒  */
}HI_UNF_PMOC_WKUP_S, *HI_UNF_PMOC_WKUP_S_PTR;

/**待机时的前面板显示的时间配置 */
typedef struct hiUNF_PMOC_TIME_S
{
    HI_U32  	u32Hour;        /**< 时 */
    HI_U32  	u32Minute;      /**< 分 */
    HI_U32  	u32Second;      /**< 秒 */
}HI_UNF_PMOC_TIME_S,*HI_UNF_PMOC_TIME_S_PTR;

/**待机时的前面板显示配置 */
typedef struct hiUNF_PMOC_STANDBY_MODE_S
{
    HI_U32		u32Mode;	        /**< 0 : 无显示 1 : 显示u32DispCode代表的数字; 2 : 显示stTimeInfo代表的时间. */
    HI_U32		u32DispCode;	    /**< u32Mode为1时，前面板显示的数字  */
	HI_UNF_PMOC_TIME_S stTimeInfo;	/**< u32Mode为2时，前面板显示的时间 */
}HI_UNF_PMOC_STANDBY_MODE_S, *HI_UNF_PMOC_STANDBY_MODE_S_PTR;


/**待机唤醒的设备类型 */
typedef struct hiUNF_PMOC_DEV_TYPE_S
{
	HI_UNF_IR_CODE_E  irtype;		/**<红外遥控类型 */
	HI_UNF_KEYLED_TYPE_E  kltype; 	/**<前面板类型 */
}HI_UNF_PMOC_DEV_TYPE_S, *HI_UNF_PMOC_DEV_TYPE_S_PTR;


/** @} */  /** <!-- ==== Structure Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_9 */
/** @{ */  /** <!-- 【WDG】 */
/**WDG响应模式*/
typedef enum hiUNF_WDG_RESPOND_MODE_E
{
    HI_UNF_WDG_RESPOND_MODE_FIRSTRESET = 0, /**<WDG第一次复位*/
    HI_UNF_WDG_RESPOND_MODE_SECONDRESET,      /**<WDG第一次中断，第二次复位*/

    HI_UNF_WDG_RESPOND_MODE_BUTT
}HI_UNF_WDG_RESPOND_MODE_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_10 */
/** @{ */  /** <!-- 【I2C】 */

/**I2C的速率类型 */
typedef enum hiUNF_I2C_RATE_E
{
    HI_UNF_I2C_RATE_50K = 0,    /**<标准速率：50kbit/s*/
    HI_UNF_I2C_RATE_100K ,      /**<标准速率：100kbit/s*/
    HI_UNF_I2C_RATE_200K ,      /**<标准速率：200kbit/s*/
    HI_UNF_I2C_RATE_300K ,      /**<标准速率：300kbit/s*/
    HI_UNF_I2C_RATE_400K,         /**<快速速率：400kbit/s*/

    HI_UNF_I2C_RATE_BUTT
}HI_UNF_I2C_RATE_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_11 */
/** @{ */  /** <!-- 【CIPHER】 */

/** CIPHER工作模式*/
typedef enum hiHI_UNF_CIPHER_WORK_MODE_E
{
    HI_UNF_CIPHER_WORK_MODE_ECB = 0x0,    /**< ECB模式。*/
    HI_UNF_CIPHER_WORK_MODE_CBC = 0x1,    /**< CBC模式。*/
    HI_UNF_CIPHER_WORK_MODE_CFB = 0x2,    /**< CFB模式。*/
    HI_UNF_CIPHER_WORK_MODE_OFB = 0x3,    /**< OFB模式。*/
    HI_UNF_CIPHER_WORK_MODE_CTR = 0x4,    /**< CTR模式。*/
    HI_UNF_CIPHER_WORK_MODE_BUTT = 0x5    

}HI_UNF_CIPHER_WORK_MODE_E;

/** CIPHER加密算法*/
typedef enum hiHI_UNF_CIPHER_ALG_E
{
    HI_UNF_CIPHER_ALG_DES  = 0x0,   /**< DES算法*/
    HI_UNF_CIPHER_ALG_3DES = 0x1,   /**< 3DES算法*/
    HI_UNF_CIPHER_ALG_AES  = 0x2,   /**< AES算法*/
    HI_UNF_CIPHER_ALG_BUTT = 0x3   
}HI_UNF_CIPHER_ALG_E;

/** 密钥长度*/
typedef enum hiHI_UNF_CIPHER_KEY_LENGTH_E
{
    HI_UNF_CIPHER_KEY_AES_128BIT = 0x0,   /**< AES运算方式下采用128bit密钥长度*/
    HI_UNF_CIPHER_KEY_AES_192BIT = 0x1,   /**< AES运算方式下采用192bit密钥长度*/
    HI_UNF_CIPHER_KEY_AES_256BIT = 0x2,   /**< AES运算方式下采用256bit密钥长度*/
    HI_UNF_CIPHER_KEY_DES_3KEY = 0x2,     /**< DES运算方式下采用3个key */
    HI_UNF_CIPHER_KEY_DES_2KEY = 0x3,     /**< DES运算方式下采用2个key  */
}HI_UNF_CIPHER_KEY_LENGTH_E;

/** 加密位宽*/
typedef enum hiHI_UNF_CIPHER_BIT_WIDTH_E
{
    HI_UNF_CIPHER_BIT_WIDTH_64BIT  = 0x0,   /**< 64bit位宽*/
    HI_UNF_CIPHER_BIT_WIDTH_8BIT   = 0x1,   /**< 8bit位宽*/
    HI_UNF_CIPHER_BIT_WIDTH_1BIT   = 0x2,   /**< 1bit位宽*/
    HI_UNF_CIPHER_BIT_WIDTH_128BIT = 0x3,   /**< 128bit位宽*/
}HI_UNF_CIPHER_BIT_WIDTH_E;

//////////////////////////////////////////////

/** 加密控制信息结构*/
typedef struct hiHI_UNF_CIPHER_CTRL_S
{
    HI_U32                     u32Key[8];    /**< 密钥*/
    HI_U32                     u32IV[4];     /**< 初始向量*/
    HI_BOOL                    bKeyByCA;     /**< 是否使用高安全CA加密或解密KEY*/
    HI_UNF_CIPHER_ALG_E        enAlg;        /**< 加密算法*/
    HI_UNF_CIPHER_BIT_WIDTH_E  enBitWidth;   /**< 加密或解密的位宽*/
    HI_UNF_CIPHER_WORK_MODE_E  enWorkMode;   /**< 工作模式*/
    HI_UNF_CIPHER_KEY_LENGTH_E enKeyLen;     /**< 密钥长度*/
} HI_UNF_CIPHER_CTRL_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

#define OTP_HDCP_KEY_LEN   320

typedef enum hiHI_UNF_OTP_AREATYPE_E
{
    HI_UNF_OTP_AREATYPE_HDCPKEY,
    HI_UNF_OTP_AREATYPE_BUTT
}HI_UNF_OTP_AREATYPE_E;

//////////////////////////////////////////////
//////////////////////////////////////////////

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_1 */
/** @{ */  /** <!-- 【SCI】 */
/** 
\brief SCI初始化
\attention \n
\param 无
\retval 0 成功

\see \n
无
*/
HI_S32 HI_UNF_SCI_Init(HI_VOID);

/** 
\brief SCI去初始化
\attention \n
\param 无
\retval 0 成功

\see \n
无
*/
HI_S32 HI_UNF_SCI_DeInit(HI_VOID);

/** 
\brief 打开SCI（Smart Card Interface）设备，针对输入的端口和协议，进行SCI接口设备的初始化；如果卡存在，则同时对卡进行初始化
\attention \n
重复打开会失败\n
打开后SCI设备采用默认配置对设备进行初始化\n
之后如果更改了配置，需要调用HI_UNF_SCI_ResetCard来使配置生效\n
之后如果对卡进行拔插，需要调用HI_UNF_SCI_ResetCard来进行复位。
打开设备的时候需要设置频率参数，而芯片实际给SCI 的时钟是由外部传入的
时钟频率参数计算的分频因子分频得来，因为计算公式会舍弃计算的分频因子的小数部分，
所以通过系统时钟分频之后给卡的时钟会存在增量误差，实际配置考虑与需求最接近的值来
设置和权衡，具体算法:Fsci_clk = Frefclk/((clkicc+1)*2);其中Frefclk是系统96M时钟Fsci_clk 是外部需要设置的
sci时钟,实际要配入寄存器分频因子clkicc = Frefclk/(2*Fsci_clk) -1;clkicc 有时候计算出来是浮点数，但只取整，
所以设置的频率与实际频率有偏差。

\param[in] enSciPort       SCI端口号，取值范围为0和1
\param[in] enSciProtocol  协议类型
\param[in] u32Frequency    要设置的SCI卡频率。对于T0，T1卡，支持频率1MHz～5MHz；对于T14卡，只支持6MHz。单位为khz
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_Open(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_PROTOCOL_E enSciProtocol, HI_U32 u32Frequency);

/** 
\brief 关闭SCI设备。
\attention \n
重复关闭会失败。
\param[in] enSciPort       SCI端口号，取值范围为0和1
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\see \n
无
*/
HI_S32 HI_UNF_SCI_Close(HI_UNF_SCI_PORT_E enSciPort);


/** 
\brief 热复位SCI卡。
\attention \n
没有插入卡，复位会失败\n
当更改了SCI设备的配置后，需要调用该接口使配置生效\n
在调用打开SCI设备接口后，对卡进行拔插，也需要调用该接口进行复位。

\param[in] enSciPort    SCI端口号，取值范围为0和1。
\param[in] bWarmResetValid  复位方式，取值范围为0和1。0:warm reset,1:cold reset（推荐用这种方式）。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_ResetCard(HI_UNF_SCI_PORT_E enSciPort, HI_BOOL bWarmResetValid);


/** 
\brief 去激活SCI卡。
\attention \n
去激活卡后，无法读写数据。只有重新复位卡后，才能继续读写。
\param[in] enSciPort  SCI端口号，取值范围为0和1。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_DeactiveCard(HI_UNF_SCI_PORT_E enSciPort);


/** 
\brief 获取SCI卡ATR数据。
\attention \n
无
\param[in]  enSciPort  SCI端口号，取值范围为0和1。
\param[in]  pu8AtrBuf  ATR 数据读取 buffer 长度。
\param[in] u32AtrBufSize  实际获取的ATR数据个数。
\param[in]  pu8AtrRcvCount  获取的ATR数据的存储地址。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\retval ::HI_ERR_SCI_FAILED_GETATR  获取ATR数据失败
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  获取卡状态失败
\retval ::HI_ERR_SCI_FAILED_SEND  发送操作失败
\retval ::HI_ERR_SCI_FAILED_RECEIVE  接收操作失败
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  配置阻塞超时失败
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  获取未发送长度失败
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  配置VCCEN信号失败
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  配置DETECT信号失败
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  阻塞方式获取卡状态失败
\retval ::HI_ERR_SCI_INVALID_PORT  错误的端口号
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  错误的协议类型
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  非法的时钟频率
\retval ::HI_ERR_SCI_INVALID_LENTH  非法长度
\retval ::HI_ERR_SCI_NO_ATR  无ATR数据
\retval ::HI_ERR_SCI_CARD_STATUS  卡状态错误
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  接收操作超时
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  非法超时时间值
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  非法的电平
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  获取卡状态超时
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  配置CLK信号线工作模式失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_GetATR(HI_UNF_SCI_PORT_E enSciPort, HI_U8 *pu8AtrBuf, HI_U32 u32AtrBufSize, HI_U8 *pu8AtrRcvCount);


/** 
\brief 获取SCI卡状态。
\attention \n
此接口是无阻塞函数，在卡的状态为HI_UNF_SCI_STATUS_READY时，才可调用HI_UNF_SCI_Send或HI_UNF_SCI_Receive接口与卡进行数据交互\n

\param[in] enSciPort  SCI端口号，取值范围为0和1。
\param[Out] penSCIStatus  SCI卡状态。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\retval ::HI_ERR_SCI_FAILED_GETATR  获取ATR数据失败
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  获取卡状态失败
\retval ::HI_ERR_SCI_FAILED_SEND  发送操作失败
\retval ::HI_ERR_SCI_FAILED_RECEIVE  接收操作失败
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  配置阻塞超时失败
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  获取未发送长度失败
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  配置VCCEN信号失败
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  配置DETECT信号失败
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  阻塞方式获取卡状态失败
\retval ::HI_ERR_SCI_INVALID_PORT  错误的端口号
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  错误的协议类型
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  非法的时钟频率
\retval ::HI_ERR_SCI_INVALID_LENTH  非法长度
\retval ::HI_ERR_SCI_NO_ATR  无ATR数据
\retval ::HI_ERR_SCI_CARD_STATUS  卡状态错误
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  接收操作超时
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  非法超时时间值
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  非法的电平
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  获取卡状态超时
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  配置CLK信号线工作模式失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_GetCardStatus(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_STATUS_E *penSciStatus);


/** 
\brief 向SCI卡发送数据。
\attention \n
发送数据需要按照应用协议来发送\n
不能连续两次发送而中间不接收数据\n
发送读取都是阻塞的，因此发送大量的数据时，受到超时时间的限制，如果超时值比较短，有可能发送失败。
            
\param[in] enSciPort  SCI端口号，取值范围为0和1。
\param[in]  pSciSendBuf  发送数据的存储地址。
\param[in] u32SendLen  发送数据的个数,单位为 BYTE。
\param[in]  pu32ActLen  实际发送数据个数,单位为 BYTE。
\param[in] u32TimeoutMs  等待超时值, 单位是毫秒, 0 - 不阻塞, 0xFFFFFFFF-永久阻塞。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\retval ::HI_ERR_SCI_FAILED_GETATR  获取ATR数据失败
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  获取卡状态失败
\retval ::HI_ERR_SCI_FAILED_SEND  发送操作失败
\retval ::HI_ERR_SCI_FAILED_RECEIVE  接收操作失败
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  配置阻塞超时失败
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  获取未发送长度失败
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  配置VCCEN信号失败
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  配置DETECT信号失败
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  阻塞方式获取卡状态失败
\retval ::HI_ERR_SCI_INVALID_PORT  错误的端口号
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  错误的协议类型
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  非法的时钟频率
\retval ::HI_ERR_SCI_INVALID_LENTH  非法长度
\retval ::HI_ERR_SCI_NO_ATR  无ATR数据
\retval ::HI_ERR_SCI_CARD_STATUS  卡状态错误
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  接收操作超时
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  非法超时时间值
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  非法的电平
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  获取卡状态超时
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  配置CLK信号线工作模式失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_Send(HI_UNF_SCI_PORT_E enSciPort, HI_U8 *pSciSendBuf, HI_U32 u32SendLen, HI_U32 *pu32ActLen, HI_U32 u32TimeoutMs);


/** 
\brief 从SCI卡接收数据。
\attention \n
上层应用程序必须根据协议来配置所获取的长度，如果希望获取的长度超出实际能够返回的长度，则只能等到超时到期才能返回。

\param[in] enSciPort  SCI端口号，取值范围为0和1。
\param[in]  pSciReceiveBuf  接收数据的存储地址。
\param[in] u32ReceiveLen  期望接收数据的个数,,单位为 BYTE。
\param[in]  pu32ActLen  实际接收数据个数,单位为 BYTE。
\param[in] u32TimeOutMs  等待超时值, 单位是毫秒, 0 - 不阻塞, 0xFFFFFFFF-永久阻塞。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\retval ::HI_ERR_SCI_FAILED_GETATR  获取ATR数据失败
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  获取卡状态失败
\retval ::HI_ERR_SCI_FAILED_SEND  发送操作失败
\retval ::HI_ERR_SCI_FAILED_RECEIVE  接收操作失败
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  配置阻塞超时失败
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  获取未发送长度失败
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  配置VCCEN信号失败
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  配置DETECT信号失败
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  阻塞方式获取卡状态失败
\retval ::HI_ERR_SCI_INVALID_PORT  错误的端口号
\retval ::HI_ERR_SCI_NO_ATR  无ATR数据
\retval ::HI_ERR_SCI_CARD_STATUS  卡状态错误
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  接收操作超时
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  获取卡状态超时
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  配置CLK信号线工作模式失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_Receive(HI_UNF_SCI_PORT_E enSciPort, HI_U8 *pSciReceiveBuf, HI_U32 u32ReceiveLen, HI_U32 *pu32ActLen, HI_U32 u32TimeOutMs);


/** 
\brief 配置VCCEN信号线的有效电平。
\attention \n
需要根据硬件电路进行配置，默认为低电平有效\n
更改此项配置后需要调用HI_UNF_SCI_ResetCard才能使新的配置有效。
        
\param[in] enSciPort  SCI端口号，取值范围为0和1。
\param[in] enSciVcc  信号线的有效电平。HI_FALSE：低电平有效，HI_TRUE：高电平有效。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\retval ::HI_ERR_SCI_FAILED_GETATR  获取ATR数据失败
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  获取卡状态失败
\retval ::HI_ERR_SCI_FAILED_SEND  发送操作失败
\retval ::HI_ERR_SCI_FAILED_RECEIVE  接收操作失败
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  配置阻塞超时失败
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  获取未发送长度失败
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  配置VCCEN信号失败
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  配置DETECT信号失败
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  阻塞方式获取卡状态失败
\retval ::HI_ERR_SCI_NO_ATR  无ATR数据
\retval ::HI_ERR_SCI_CARD_STATUS  卡状态错误
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  接收操作超时
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  非法超时时间值
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  非法的电平
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  获取卡状态超时
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  配置CLK信号线工作模式失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_ConfigVccEn(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_LEVEL_E enSciVcc);


/** 
\brief 配置DETECT信号线的有效电平。
\attention \n
需要根据硬件电路进行设置，默认为高电平有效\n
更改此项配置后需要调用HI_UNF_SCI_ResetCard才能使新的配置有效。
        
\param[in] enSciPort  SCI端口号，取值范围为0和1。
\param[in] enSciDetect 信号线的有效电平。HI_FALSE：低电平有效，HI_TRUE：高电平有效。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\retval ::HI_ERR_SCI_FAILED_GETATR  获取ATR数据失败
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  获取卡状态失败
\retval ::HI_ERR_SCI_FAILED_SEND  发送操作失败
\retval ::HI_ERR_SCI_FAILED_RECEIVE  接收操作失败
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  配置阻塞超时失败
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  获取未发送长度失败
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  配置VCCEN信号失败
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  配置DETECT信号失败
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  阻塞方式获取卡状态失败
\retval ::HI_ERR_SCI_INVALID_PORT  错误的端口号
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  错误的协议类型
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  非法的时钟频率
\retval ::HI_ERR_SCI_INVALID_LENTH  非法长度
\retval ::HI_ERR_SCI_NO_ATR  无ATR数据
\retval ::HI_ERR_SCI_CARD_STATUS  卡状态错误
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  接收操作超时
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  非法超时时间值
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  非法的电平
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  获取卡状态超时
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  配置CLK信号线工作模式失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_ConfigDetect(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_LEVEL_E enSciDetect);


/** 
\brief 设置时钟线的模式。
\attention \n
需要根据硬件电路进行设置，默认为OD模式\n
更改此项配置后需要调用HI_UNF_SCI_ResetCard才能使新的配置有效。

\param[in] enSciPort  SCI端口号，取值范围为0和1。
\param[in] enClkMode  时钟线的模式。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\retval ::HI_ERR_SCI_FAILED_GETATR  获取ATR数据失败
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  获取卡状态失败
\retval ::HI_ERR_SCI_FAILED_SEND  发送操作失败
\retval ::HI_ERR_SCI_FAILED_RECEIVE  接收操作失败
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  配置阻塞超时失败
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  获取未发送长度失败
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  配置VCCEN信号失败
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  配置DETECT信号失败
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  阻塞方式获取卡状态失败
\retval ::HI_ERR_SCI_INVALID_PORT  错误的端口号
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  错误的协议类型
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  非法的时钟频率
\retval ::HI_ERR_SCI_INVALID_LENTH  非法长度
\retval ::HI_ERR_SCI_NO_ATR  无ATR数据
\retval ::HI_ERR_SCI_CARD_STATUS  卡状态错误
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  接收操作超时
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  非法超时时间值
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  非法的电平
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  获取卡状态超时
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  配置CLK信号线工作模式失败
\see \n
无
*/
HI_S32 HI_UNF_SCI_ConfigClkMode(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_CLK_MODE_E enClkMode);


/** 
\brief 切换卡槽。
\attention \n
调用HI_UNF_SCI_Open时，默认打开的为主卡，即端口0\n
切换到新的SCI设备后，上述所有SCI接口即对新的SCI设备进行操作\n
切换到新的SCI设备采用默认配置对设备进行初始化\n
之后如果更改了配置，需要调用HI_UNF_SCI_ResetCard来使配置生效\n
希望切换到的SCI端口与当前有效端口相同时，会返回失败。

\param[in] enSciPort  SCI端口号，取值范围为0和1。
\param[in] enSciProtocol  协议类型。
\param[in] u32Frequency  要设置的SCI卡频率。对于T0，T1卡，支持频率1MHz~5MHz；对于T14卡，只支持6MHz。单位为kHz。
\retval 0 成功
\retval ::HI_ERR_SCI_NOT_INIT  SCI设备未打开
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI设备重复打开
\retval ::HI_ERR_SCI_INVALID_POINT  非法指针
\retval ::HI_ERR_SCI_INVALID_PARA  非法参数
\retval ::HI_ERR_SCI_FAILED_INIT  打开SCI设备失败
\retval ::HI_ERR_SCI_FAILED_RESET  热复位失败
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  去激活失败
\retval ::HI_ERR_SCI_FAILED_GETATR  获取ATR数据失败
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  获取卡状态失败
\retval ::HI_ERR_SCI_FAILED_SEND  发送操作失败
\retval ::HI_ERR_SCI_FAILED_RECEIVE  接收操作失败
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  配置阻塞超时失败
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  获取未发送长度失败
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  配置VCCEN信号失败
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  配置DETECT信号失败
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  阻塞方式获取卡状态失败
\retval ::HI_ERR_SCI_INVALID_PORT  错误的端口号
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  错误的协议类型
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  非法的时钟频率
\retval ::HI_ERR_SCI_INVALID_LENTH  非法长度
\retval ::HI_ERR_SCI_NO_ATR  无ATR数据
\retval ::HI_ERR_SCI_CARD_STATUS  卡状态错误
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  接收操作超时
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  非法超时时间值
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  非法的电平
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  获取卡状态超时
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  配置CLK信号线工作模式失败

\see \n
无
*/
HI_S32 HI_UNF_SCI_SwitchCard(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_PROTOCOL_E enSciProtocol, HI_U32 u32Frequency);


/** 
\brief 对特殊卡需要设置指定etu 时钟率因子，波特率调节因子
\attention \n
只有特需要求的卡需要设置，普通卡不需要调用此接口设置，
设置的值要与协议中规定的F时钟转率转换因子、D比特率调节因子兼容，
或者设置为卡规范中规定的值，不可随意设置

\param [in] 	enSciPort	SCI端口号，取值范围为0和1 
\param [in] 	u32ClkFactor	时钟转率因子372～2048 ，具体设置参考协议的F因子和卡特性
\param [in] 	u32BaudFactor	波特率校正因子1、2*n (n=1～16) ，具体设置参考协议D因子和卡特性    
\retval ::  0 	成功 
\retval ::  HI_ERR_SCI_NOT_INIT   SCI设备未打开 
\retval ::  HI_ERR_SCI_INVALID_PARA 非法参数 

\see \n
无
*/
HI_S32 HI_UNF_SCI_SetEtuFactor(HI_UNF_SCI_PORT_E enSciPort,HI_U32 u32ClkFactor,HI_U32 u32BaudFactor);


/** 
\brief 设置终端向IC卡发送连续的两个字节起始沿额外增加的间隔时间
\attention \n
只有特需要求的卡，需要额外设置字符保护时间的才能根据卡的相关特性设置，
不可随意设置。一般使用系统默认值，或者系统根据ATR解析自动设置。

\param [in] 	enSciPort	SCI端口号，取值范围为0和1 
\param [in] 	u32GuardTime	额外间隔保护的范围0～254  etu
\retval ::  0 	成功 
\retval ::  HI_ERR_SCI_NOT_INIT   SCI设备未打开 
\retval ::  HI_ERR_SCI_INVALID_PARA 非法参数 

\see \n
无
*/
HI_S32 HI_UNF_SCI_SetGuardTime(HI_UNF_SCI_PORT_E enSciPort,HI_U32 u32GuardTime);


/** 
\brief 通过PPS 协商可以设置卡所支持的波特率或者用ATR 传回的F、D因子进行协商，支持多协议卡的协议切换
\attention \n
要进行PPS 协商首先卡必须支持该功能，
要协商的波特率内容必须是卡所规定的支持的波特率范围，
请求协商的命令字需符合7816-3 中9.2 PPS request and response 。

\param [in] 	enSciPort	SCI端口号，取值范围为0和1 
\param [in] 	pSciSendBuf 根据卡规范组合的PPS协商命令，若使用系统默认的协商方式，命令字的内容可为空
\param [in]	Sendlen	     发送命令字的长度(0～5),设置为0表示使用系统默认的协商命令方式。
\param [in]	RecTimeouts 发送完命令之后，接收PPS 响应的超时时间(1-10000),单位是毫秒
\retval ::  0 	成功 
\retval ::  HI_ERR_SCI_NOT_INIT   SCI设备未打开 
\retval ::  HI_ERR_SCI_INVALID_PARA 非法参数
\retval ::  HI_ERR_SCI_NULL_PTR		空指针
\retval ::  HI_ERR_SCI_INVALID_OPT	不可用的选项
\retval ::  HI_ERR_SCI_RECEIVE_ERR  接收错误
\retval ::	 HI_ERR_SCI_PPS_PTYPE_ERR 	PPS协商的协议类型错误
\retval ::	 HI_ERR_SCI_PPS_FACTOR_ERR 	PPS协商的F、D因子错误
\retval ::  HI_ERR_SCI_PPS_NOTSUPPORT_ERR 不支持的PPS协商类型

\see \n
无
*/
HI_S32 HI_UNF_SCI_NegotiatePPS(HI_UNF_SCI_PORT_E enSciPort, HI_U8 *pSciSendBuf,HI_U32 Sendlen, HI_U32 RecTimeouts);


/** 
\brief  PPS 协商成功之后,通过该接口可获得卡响应的PPS 数据
\attention \n
要等PPS 协商成功之后,使用该接口才有实际意义

\param [in] 	enSciPort	SCI端口号，取值范围为0和1 
\param [out] 	pRecBuf   待接收的数据buffer 地址
\param [out]	pDataLen	   期望接收数据的长度 
\retval ::  0 	成功 
\retval ::  HI_ERR_SCI_INVALID_PARA 非法参数
\retval ::  HI_ERR_SCI_NULL_PTR		空指针
\retval ::  HI_ERR_SCI_PPS_NOTSUPPORT_ERR 不支持的PPS协商类型

\see \n
无
*/
HI_S32 HI_UNF_SCI_GetPPSResponData(HI_UNF_SCI_PORT_E enSciPort, HI_U8* pRecBuf, HI_U32* pDataLen);


/** 
\brief  获取sci 参数包括协议、ATR 时钟和比特率因子、实际设置的时钟因子和比特率因子，
发送重试次数、GuardDelay 、字符等待超时、块等待超时。
\attention \n
要等 到初始化复位之后,才能使用该接口

\param [in] 	enSciPort	SCI端口号，取值范围为0和1 
\param [out] 	pParams   待接收的结构体数据类型指针
\retval ::  0 	成功 
\retval ::  HI_ERR_SCI_INVALID_PARA 非法参数
\retval ::  HI_ERR_SCI_NULL_PTR		空指针
\retval ::  HI_ERR_SCI_INVALID_OPT	不可用的选项
\retval ::  HI_ERR_SCI_NOT_INIT  	没完成初始化

\see \n
无
*/
HI_S32 HI_UNF_SCI_GetParams(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_PARAMS_S_PTR pParams);


/** 
\brief  根据当前协议类型分别可设置T0、T1的字符超时时间
\attention \n
要等卡复位成功之后,才能进行设置，协议类型参数必须与当前卡类型一致，一般情况都是根据ATR解析，只有特殊卡情况才需要设置。

\param [in] 	enSciPort	SCI端口号，取值范围为0和1 
\param [in] 	enSciProtocol   协议类型
\param [in]	MaxCharTime 	设置最大的字符超时时间，设置范围T0(960～244800),T1(12～32779)
\retval ::  0 	成功 
\retval ::  HI_ERR_SCI_INVALID_PARA 非法参数
\retval ::  HI_ERR_SCI_INVALID_OPT	不可用的选项
\retval ::  HI_ERR_SCI_NO_ATR  		没复位成功

\see \n
无
*/
HI_S32 HI_UNF_SCI_SetCharTimeout(HI_UNF_SCI_PORT_E enSciPort,  HI_UNF_SCI_PROTOCOL_E  enSciProtocol, HI_U32 MaxCharTime);


/** 
\brief  设置T1的块超时时间
\attention \n
要等卡复位成功之后,才能进行设置，一般情况都是根据ATR解析，只有特殊卡情况才需要设置。

\param [in] 	enSciPort	SCI端口号，取值范围为0和1 
\param [in] 	MaxBlockTime   设置块超时的最大值，范围(971～491531)
\retval ::  0 	成功 
\retval ::  HI_ERR_SCI_INVALID_PARA 非法参数
\retval ::  HI_ERR_SCI_INVALID_OPT	不可用的选项
\retval ::  HI_ERR_SCI_NO_ATR  		没复位成功

\see \n
无
*/
HI_S32 HI_UNF_SCI_SetBlockTimeout(HI_UNF_SCI_PORT_E enSciPort,HI_U32 MaxBlockTime);


/** 
\brief  设置校验错误后重发送最大次数
\attention \n
要等卡复位成功之后,才能进行设置

\param [in] 	enSciPort	SCI端口号，取值范围为0和1 
\param [in] 	TxRetryTimes   次数范围(0～7)
\retval ::  0 	成功 
\retval ::  HI_ERR_SCI_INVALID_PARA 非法参数
\retval ::  HI_ERR_SCI_INVALID_OPT	不可用的选项
\retval ::  HI_ERR_SCI_NO_ATR  		没复位成功

\see \n
无
*/
HI_S32 HI_UNF_SCI_SetTxRetries(HI_UNF_SCI_PORT_E enSciPort,HI_U32 TxRetryTimes);


/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_2 */
/** @{ */  /** <!-- 【E2PROM】 */
/*---- e2prom ----*/
/** 
\brief 打开E2PROM（Electrically-Erasable Programmable Read-Only Memory）设备。
\attention \n
重复打开会失败。
\param 无
\retval 0 成功
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM设备未初始化
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM设备重复初始化
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM无效指针
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM无效参数
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM设备初始化失败
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM数据读取失败
\see \n
无
*/
HI_S32 HI_UNF_E2PROM_Open(HI_VOID);


/** 
\brief 关闭E2PROM设备。
\attention \n
重复关闭会失败。
\param 无
\retval 0 成功
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM设备未初始化
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM设备重复初始化
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM无效指针
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM无效参数
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM设备初始化失败
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM数据读取失败
\see \n
无
*/
HI_S32 HI_UNF_E2PROM_Close(HI_VOID);


/** 
\brief 从E2PROM设备读数据。
\attention \n
调用此接口前应确保I2C模块可用\n
若传入的地址u32Addr大于芯片地址总长度，则不会对E2PROM进行读操作\n
若传入的指针pu8Buf为空，则不会对E2PROM进行读操作\n
若传入地址u32Addr合法，但u32Addr与u32Length的和大于芯片地址总长度，则不会对E2PROM进行读操作。
\param[in] u32Addr  片内偏移地址。
\param[out]  pu8Buf  存放待读取的数据。
\param[in] u32Length  读取数据的长度。
\retval 0 成功
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM设备未初始化
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM设备重复初始化
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM无效指针
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM无效参数
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM设备初始化失败
\see \n
无
*/
HI_S32 HI_UNF_E2PROM_Read (HI_U32 u32Addr, HI_U8 * pu8Buf, HI_U32 u32Length);


/** 
\brief 向E2PROM设备写数据。
\attention \n
调用此接口前应确保I2C模块可用\n
若传入的地址u32Addr大于芯片地址总长度，则不会对E2PROM进行写操作\n
若传入的指针pu8Buf为空，则不会对E2PROM进行写操作\n
若传入地址u32Addr合法，但u32Addr与u32Length的和大于芯片地址总长度，则不会对E2PROM进行写操作。
\param[in] u32Addr  片内偏移地址。
\param[in]  pu8Buf  存放待写入的数据。
\param[in] u32Length  要写入的数据长度。
\retval 0 成功
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM设备未初始化
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM设备重复初始化
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM无效指针
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM无效参数
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM设备初始化失败
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM数据读取失败
\see \n
无
*/
HI_S32 HI_UNF_E2PROM_Write (HI_U32 u32Addr, HI_U8 * pu8Buf, HI_U32 u32Length);


/** 
\brief 设置E2PROM芯片类型。
\attention \n
调用此接口前应确保I2C模块可用\n
此接口必须在调用HI_UNF_E2PROM_Read和HI_UNF_E2PROM_Write之前调用\n
目前仅实测了M24LC16芯片，其它类型的芯片未进行测试。
\param[in] enChip  E2PROM芯片类型。
                   HI_UNF_E2PROM_CHIP_AT24C01：芯片类型为AT24C01；
                   HI_UNF_E2PROM_CHIP_AT24C02：芯片类型为AT24C02；
                   HI_UNF_E2PROM_CHIP_AT24C04：芯片类型为AT24C04；
                   HI_UNF_E2PROM_CHIP_AT24C08：芯片类型为AT24C08；
                   HI_UNF_E2PROM_CHIP_AT24C16：芯片类型为AT24C16；
                   HI_UNF_E2PROM_CHIP_AT24C32：芯片类型为AT24C32；
                   HI_UNF_E2PROM_CHIP_AT24C64：芯片类型为AT24C64；
                   HI_UNF_E2PROM_CHIP_AT24C128：芯片类型为AT24C128；
                   HI_UNF_E2PROM_CHIP_AT24C256：芯片类型为AT24C256；
                   HI_UNF_E2PROM_CHIP_M24LC01：芯片类型为M24LC01；
                   HI_UNF_E2PROM_CHIP_M24LC02：芯片类型为M24LC02；
                   HI_UNF_E2PROM_CHIP_M24LC04：芯片类型为M24LC04；
                   HI_UNF_E2PROM_CHIP_M24LC08：芯片类型为M24LC08；
                   HI_UNF_E2PROM_CHIP_M24LC16：芯片类型为M24LC16；
                   HI_UNF_E2PROM_CHIP_M24LC32：芯片类型为M24LC32；
                   HI_UNF_E2PROM_CHIP_M24LC64：芯片类型为M24LC64；
                   HI_UNF_E2PROM_CHIP_M24LC128：芯片类型为M24LC128；
                   HI_UNF_E2PROM_CHIP_M24LC256：芯片类型为M24LC256。
\retval 0 成功
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM设备未初始化
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM设备重复初始化
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM无效指针
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM无效参数
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM设备初始化失败
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM数据读取失败
\retval ::HI_ERR_E2PROM_FAILED_WRITE  E2PROM数据写入失败
\retval ::HI_ERR_E2PROM_FAILED_SETCHIPTYPE  E2PROM选择芯片失败
\see \n
无
*/
HI_S32 HI_UNF_E2PROM_SetChipType(HI_UNF_E2PROM_CHIP_E enChip);


/** 
\brief 设置E2PROM的I2C总线地址。
\attention \n
地址跟硬件布局有关，请参考硬件设计。
\param[in] u32E2promAddr  E2PROM的I2C总线地址。
\retval 0 成功
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM设备未初始化
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM设备重复初始化
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM无效指针
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM无效参数
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM设备初始化失败
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM数据读取失败
\retval ::HI_ERR_E2PROM_FAILED_WRITE  E2PROM数据写入失败
\retval ::HI_ERR_E2PROM_FAILED_SETADDR  E2PROM设置地址失败
\see \n
无
*/
HI_S32 HI_UNF_E2PROM_SetAddr(HI_U32 u32E2promAddr);


/** 
\brief 设置E2PROM所使用的I2C通道号。
\attention \n
无
\param[in] u32I2cNum  E2PROM所用的I2C通道号，范围0～HI_I2C_MAX_NUM_USER
\retval 0 成功
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM设备未初始化
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM设备重复初始化
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM无效指针
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM无效参数
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM设备初始化失败
\retval ::HI_ERR_E2PROM_FAILED_SETI2CNUM  E2PROM设置I2C通道失败
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM设备未初始化
\see \n
无
*/
HI_S32 HI_UNF_E2PROM_SetI2cNum(HI_U32 u32I2cNum);

/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_3 */
/** @{ */  /** <!-- 【I2C】 */
/*---- i2c ----*/
/** 
\brief 打开I2C（the Inter-Integrated Circuit）设备。
\attention \n
重复调用此接口会失败。
\param 无
\retval 0 成功
\retval ::HI_ERR_I2C_NOT_INIT  I2C设备未初始化
\retval ::HI_ERR_I2C_REPEAT_INIT  I2C设备重复初始化
\retval ::HI_ERR_I2C_INVALID_POINT  I2C无效指针
\retval ::HI_ERR_I2C_INVALID_PARA  I2C无效参数
\see \n
无
*/
HI_S32 HI_UNF_I2C_Open (HI_VOID);


/** 
\brief 关闭I2C设备。
\attention \n
在I2C操作结束后调用此接口\n
重复调用此接口会失败。
\param 无
\retval 0 成功
\retval ::HI_ERR_I2C_NOT_INIT  I2C设备未初始化
\see \n
无
*/
HI_S32 HI_UNF_I2C_Close(HI_VOID);

/** 
\brief 创建一路GpioI2c
\attention \n
如果Gpio已被占用会失败\n
\param[in] u32I2cNum  得到I2C总线号。
\param[in] whichGpioClock  Clock管脚组号，取值范围为0～12
\param[in] whichGpioData   Data管脚组号， 取值范围为0～12
\param[in] clockBit  Clock管脚位号，取值范围为0～7
\param[in] dataBit   Data管脚位号， 取值范围为0～7
\retval 0 成功
\retval ::HI_ERR_GPIO_INVALID_PARA  参数非法
\see \n
无
*/
HI_S32 HI_UNF_I2C_CreateGpioI2c(HI_U32 *u32I2cNum, HI_U32 whichGpioClock, HI_U32 whichGpioData, HI_U32 clockBit, HI_U32 dataBit);

/** 
\brief 销毁一路GpioI2c
\attention \n
如果该GpioI2c未使用，直接返回成功\n
\param[in] u32I2cNum 要销毁的I2C总线号。
\retval 0 成功
\retval ::HI_ERR_GPIO_INVALID_PARA  参数非法
\see \n
无
*/
HI_S32 HI_UNF_I2C_DestroyGpioI2c(HI_U32 u32I2cNum);
/** 
\brief 通过I2C读数据。
\attention \n
无
\param[in] u32I2cNum  所读取设备使用的I2C总线。
\param[in] u8DevAddress  设备在I2C总线上的地址。
\param[in] u32RegAddr  设备的片内偏移地址。
\param[in] u32RegAddrCount  片内偏移地址的长度单位。
                            1：表示8bit子地址；
                            2：表示16bit子地址；
                            3：表示24bit子地址；
                            4：表示32bit子地址。

\param[out] pu8Buf  读Buffer，存放读取数据。
\param[in] u32Length  要读取的数据长度。
\retval 0 成功
\retval ::HI_ERR_I2C_NOT_INIT  I2C设备未初始化
\retval ::HI_ERR_I2C_INVALID_POINT  I2C无效指针
\retval ::HI_ERR_I2C_INVALID_PARA  I2C无效参数
\retval ::HI_ERR_I2C_FAILED_INIT  I2C设备初始化失败
\retval ::HI_ERR_I2C_FAILED_READ  I2C读数据失败
\retval ::HI_ERR_I2C_FAILED_SETRATE  I2C设置速率失败
\see \n
无
*/
HI_S32 HI_UNF_I2C_Read(HI_U32 u32I2cNum, HI_U8 u8DevAddress, HI_U32 u32RegAddr,
                       HI_U32 u32RegAddrCount, HI_U8 *pu8Buf, HI_U32 u32Length);
                       

/** 
\brief 通过I2C写数据。通过I2C通道，向I2C总线上挂接的设备进行写操作。
\attention \n
无
\param[in] u32I2cNum  待写设备使用的I2C总线。
\param[in] u8DevAddress  设备在I2C总线上的地址。
\param[in] u32RegAddr  设备的片内偏移地址。
\param[in] u32RegAddrCount  片内偏移地址的长度单位。
                            1：表示8bit子地址；
                            2：表示16bit子地址；
                            3：表示24bit子地址；
                            4：表示32bit子地址。
\param[in]  pu8Buf  写Buffer，存放待写入数据。
\param[in] u32Length  要写入的数据的长度。
\retval 0 成功
\retval ::HI_ERR_I2C_NOT_INIT  I2C设备未初始化
\retval ::HI_ERR_I2C_REPEAT_INIT  I2C设备重复初始化
\retval ::HI_ERR_I2C_INVALID_POINT  I2C无效指针
\retval ::HI_ERR_I2C_INVALID_PARA  I2C无效参数
\retval ::HI_ERR_I2C_FAILED_INIT  I2C设备初始化失败
\retval ::HI_ERR_I2C_FAILED_WRITE  I2C写数据失败
\retval ::HI_ERR_I2C_FAILED_SETRATE  I2C设置速率失败
\see \n
无
*/                      
HI_S32 HI_UNF_I2C_Write(HI_U32 u32I2cNum, HI_U8 u8DevAddress, HI_U32 u32RegAddr,
                       HI_U32  u32RegAddrCount, HI_U8 * pu8Buf, HI_U32 u32Length);


/** 
\brief 设置I2C的传输速率。
\attention \n
如果不调用此接口，系统采用100Kbit/s作为缺省速率。
\param[in] u32I2cNum  所写设备在I2C总线上的通道号。
\param[in] enI2cRate  I2C时钟速率。含义请参考::HI_UNF_I2C_RATE_E
\retval 0 成功
\retval ::HI_ERR_I2C_NOT_INIT  I2C设备未初始化
\retval ::HI_ERR_I2C_REPEAT_INIT  I2C设备重复初始化
\retval ::HI_ERR_I2C_INVALID_POINT  I2C无效指针
\retval ::HI_ERR_I2C_INVALID_PARA  I2C无效参数
\retval ::HI_ERR_I2C_FAILED_INIT  I2C设备初始化失败
\retval ::HI_ERR_I2C_FAILED_READ  I2C读数据失败
\retval ::HI_ERR_I2C_FAILED_WRITE  I2C写数据失败
\retval ::HI_ERR_I2C_FAILED_SETRATE  I2C设置速率失败
\see \n
无
*/
HI_S32 HI_UNF_I2C_SetRate(HI_U32 u32I2cNum, HI_UNF_I2C_RATE_E enI2cRate);

/** @} */  /** <!-- ==== API declaration end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_4 */
/** @{ */  /** <!-- 【KEYLED】 */
/**---- keyled ----*/
/**
\brief 初始化KEYLED模块。
\attention \n
重复调用本接口，会返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_KEYLED_Init(HI_VOID);


/**
\brief 去初始化KEYLED模块。
\attention \n
重复调用本接口，会返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_KEYLED_DeInit(HI_VOID);

/**
\brief 选择KEYLED器件类型。
\attention \n
 建议初始化后只选择一次，不要重复调用，默认为标准KEYLED模式。
\param[in] enKeyLedType  keyled类型。 
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_KEYLED_SelectType(HI_UNF_KEYLED_TYPE_E enKeyLedType);

/**
\brief 打开按键功能。
\attention \n
打开后开始接收按键\n
重复调用本接口，会返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_KEY_Open(HI_VOID);

/**
\brief 关闭按键功能。
\attention \n
关闭后停止接收按键\n
本接口第一次调用起作用,重复调用返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_KEY_Close(HI_VOID);

/**
\brief 清空当前没有接收的按键。
\attention \n
清空按键buffer，回到初时状态。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_KEY_Reset(HI_VOID);


/**
\brief 获取一个按键值。
\attention \n
获取buffer中最早到达的按键值，返回按键值的数值和状态\n
状态包含按下和弹起\n
接口配合::HI_UNF_KEY_SetBlockTime接口一起使用\n
没有按键时，进行等待，超时后退出并返回超时错误码\n
超时值为0时为非阻塞接口，没有按键直接返回没有按键错误码\n
超时值设置为0xffffffff，一直等待。
\param[out] pu32PressStatus   按键状态是按下还是弹起。
\param[out] pu32KeyId   按键值。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\retval ::HI_ERR_KEYLED_NULL_PTR  指针参数为空
\retval ::HI_ERR_KEYLED_NO_NEW_KEY  没有按键
\retval ::HI_ERR_KEYLED_TIMEOUT  等待按键超时
\see \n
无
*/
HI_S32 HI_UNF_KEY_GetValue(HI_U32 * pu32PressStatus, HI_U32 * pu32KeyId);

/**
\brief 设置按键读取的超时时间。
\attention \n
超时值为0时不阻塞，没有按键直接返回没有按键错误码\n
超时值设置为0xffffffff，一直等待。
\param[in] u32BlockTimeMs 超时时间，单位ms。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\see \n
无
*/
HI_S32 HI_UNF_KEY_SetBlockTime(HI_U32 u32BlockTimeMs);


/**
\brief 设置重复按键的时间。
\attention \n
当某个键处于按下状态，超过设置的时间值判断为重复按键\n
重复按键的设置范围在108ms到65536ms之间，超过这个范围会自动约束到上限或下限上\n
默认的重复按键判断时间为200ms。
\param[in] u32RepTimeMs 判断为重复按键的时间，单位ms。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\see \n
无
*/
HI_S32 HI_UNF_KEY_RepKeyTimeoutVal(HI_U32 u32RepTimeMs);

/**
\brief 设置是否使能重复按键。
\attention \n
只有使能后，一直按住某个键，才能连续上报键值。
\param[in] u32IsRepKey 是否使能重复按键，1 使能，0 不使能。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\see \n
无
*/
HI_S32 HI_UNF_KEY_IsRepKey(HI_U32 u32IsRepKey);

/**
\brief 设置是否上报按键弹起。
\attention \n
使能后才会上报按键弹起事件，不然只上报按下事件。
\param[in] u32IsKeyUp 是否使能重复按键，1 使能，0 不使能。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\see \n
无
*/
HI_S32 HI_UNF_KEY_IsKeyUp(HI_U32 u32IsKeyUp);

/**
\brief 打开数码管显示功能。
\attention \n
打开后才会有数码管的显示\n
重复调用本接口，会返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_LED_Open(HI_VOID);

/**
\brief 关闭数码管显示功能。
\attention \n
关闭后停止数码管显示\n
本接口第一次调用起作用,重复调用返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_LED_Close(HI_VOID);


/**
\brief 根据传入的码型值进行显示。
\attention \n
每个数码管要显示的字符对应一个字节的显示值。\n
显示时需要将4 个待显示字符对应的显示值组合成一个unsiged int（32bit）数据作为此接口的参数值。\n
从左到右的4 个LED 依次显示数据的bit[7:0]、bit[15:8]、bit[23:16]、bit[31:24]。\n
例如：在LED 上显示“1234”，则需要将这些字符对应的显示值组合成一个Unsigned int 的变量：\n
  Unsigned int parameter = 0x03 + (0x9F <<8) + (0x25<<16) + (0x0D <<24)；\n
其中：0x03、0x9F、0x25、0x0D 分别是‘1’、‘2’、‘3’、‘4’的显示值。\n
七段数码管段数与数据的bit对应关系如下:\n
       --7--       \n
      |     |      \n
     2|     |6     \n
      |--1--       \n
      |     |      \n
     3|     |5     \n
       --4-- .0    \n
海思DEMO板数码管常用显示字符及其对应的显示值如下(针对共阳极，共阴极要取反)：\n
  . 字符0-9：0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09\n
  . 大写字母A-Z（不能显示的用0xFF 表示）：\n
     0xFF, 0xFF, 0x63, 0xFF, 0x61, 0x71, 0xFF, 0x91, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF,\n
     0xFF, 0x03, 0x31, 0xFF, 0xFF, 0x49, 0xFF, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF\n
  . 小写字母a-z（不能显示的用0xFF 表示）：\n
    0xFF, 0xC1, 0xE5, 0x85, 0x21, 0xFF, 0x09, 0xD1, 0xDF, 0xFF, 0xFF, 0x9F, 0xFF,\n
    0xD5, 0xC5, 0x31, 0x19, 0xFF, 0x49, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
\param[in] u32CodeValue  需要显示的4位数值。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\see \n
无
*/
HI_S32 HI_UNF_LED_Display(HI_U32 u32CodeValue);


/**
\brief 在数码管上显示时间。
\attention \n
小时、分钟只需配置成相应的十进制值就行了。比如显示22：45，则hour=22，minute=45。\n
需要先调用HI_UNF_LED_SetFlashPin 配置显示管脚为HI_UNF_KEYLED_LIGHT_ALL\n
传入时间数据结构，然后在数码管上显示，显示时间的同时冒号会以1HZ的频率闪烁\n
时间的范围注意按24小时制，最大支持小时为23，分为59。
\param[in] stLedTime 时间。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\retval ::HI_ERR_KEYLED_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_LED_DisplayTime(HI_UNF_KEYLED_TIME_S stLedTime);

/**
\brief 设置要闪烁的LED 序号。
\attention \n
单板上的数码管的序号从左到右依次为：1、2、3、4。
\param[in] enPin 要显示的序号。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\retval ::HI_ERR_KEYLED_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_LED_SetFlashPin(HI_UNF_KEYLED_LIGHT_E enPin);

/**
\brief 设置LED 闪烁级别。
\attention \n
级别越高闪烁速度越快。
\param[in] enLevel 闪烁级别。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\retval ::HI_ERR_KEYLED_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_LED_SetFlashFreq(HI_UNF_KEYLED_LEVEL_E enLevel);

/**
\brief 设置LED 锁定信号灯。
\attention \n
锁定传入TRUE,否则传入FALSE
\param[in] bEnable 锁定或未锁定。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_KEYLED_NOT_INIT  模块没有初始化
\retval ::HI_ERR_KEYLED_INVALID_PARA  输入参数非法
\see \n
无
*/
HI_S32 HI_UNF_LED_LockSignal(HI_BOOL uLockFlag);


/** @} */  /** <!-- ==== API declaration end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_5 */
/** @{ */  /** <!-- 【PM】 */
/*---- pm ----*/
/** 
\brief 打开低功耗模块设备。
\attention \n
在打开低功耗模块设备后，才能切换ARM的工作模式，继而进入低功耗状态。
\param 无
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\retval ::HI_ERR_PMoC_INVALID_PARA  非法参数
\retval ::HI_ERR_PMoC_INVALID_MODE  非法的系统运行模式
\see \n
无
*/
HI_S32 HI_UNF_PMOC_Init(HI_VOID);

/** 
\brief 关闭低功耗设备。
\attention \n
无
\param 无
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\retval ::HI_ERR_PMoC_INVALID_PARA  非法参数
\retval ::HI_ERR_PMoC_INVALID_MODE  非法的系统运行模式
\see \n
无
*/
HI_S32 HI_UNF_PMOC_DeInit(HI_VOID);

/** 
\brief 设置ARM要切换到的模式，同时获取ARM唤醒的方式。
\attention \n
ARM进入HI_UNF_PMOC_MODE_SLEEP真待机模式后程序立即停止运行，必须在唤醒后才能继续执行后面的代码\n
进入待机模式前，必须打开IR（遥控器）设备、前面板KEY设备和RTC设备，否则对应模块的中断被屏蔽，不能实现该种模式的唤醒\n
进入真待机时，必须确保不对DDR进行访问。所以必须关闭显示输出、视频输出、DEMUX输入、音视频解码等。
\param[in] enSystemMode  置低功耗下ARM所处模式。
                         由于HI_UNF_PMOC_MODE_SLOW和
                         HI_UNF_PMOC_MODE_DOZE只降低ARM工作频率，功耗降低并不明显，推荐使用HI_UNF_PMOC_MODE_SLEEP真待机模式，
                         此模式下程序停止运行，返回后处于Normal模式。
\param[in]  penWakeUpStatus  从HI_UNF_PMOC_MODE_SLEEP状态返回时的唤醒方式。具体含义请参考::HI_UNF_PMOC_ACTUAL_WKUP_E
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\retval ::HI_ERR_PMoC_INVALID_PARA  非法参数
\retval ::HI_ERR_PMoC_INVALID_MODE  非法的系统运行模式
\see \n
无
*/
HI_S32 HI_UNF_PMOC_SwitchSystemMode(HI_UNF_PMOC_MODE_E enSystemMode, HI_UNF_PMOC_ACTUAL_WKUP_E * penWakeUpStatus);


/** 
\brief 设置ARM唤醒方式。
\attention \n
IR原始码值可以通过遥控器的使用手册得到\n
按键与键值的对应关系可以通过硬件和芯片的连接关系得到。
\param[in] pstAttr  ARM唤醒方式。
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\retval ::HI_ERR_PMoC_INVALID_PARA  非法参数
\retval ::HI_ERR_PMoC_INVALID_MODE  非法的系统运行模式
\see \n
无
*/
HI_S32 HI_UNF_PMOC_SetWakeUpAttr(HI_UNF_PMOC_WKUP_S_PTR pstAttr);

/** 
\brief 设置唤醒显示内容。
\attention \n
待机时面板显示指定内容\n
\param[in] pstStandbyMode  显示内容:时间 or 频道 or 无显示。
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\retval ::HI_ERR_PMoC_INVALID_PARA  非法参数
\see \n
无
*/
HI_S32 HI_UNF_PMOC_SetStandbyDispMode(HI_UNF_PMOC_STANDBY_MODE_S_PTR pstStandbyMode);

/** 
\brief 获取系统当前模式。
\attention \n
仅在正常状态下有效，接口前项兼容\n
\param[in] penSystemMode 需要获取的模式。
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\see \n
无
*/
HI_S32 HI_UNF_PMOC_ReadSystemMode(HI_UNF_PMOC_MODE_E * penSystemMode);

/** 
\brief 设置工作场景。
\attention \n
目前仅支持标准待机场景\n
\param[in] eScene  待机场景。
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\retval ::HI_ERR_PMoC_INVALID_PARA  非法参数
\see \n
无
*/
HI_S32 HI_UNF_PMOC_SetScene(HI_UNF_PMOC_SCENE_E eScene);


/** 
\brief 设置目前前面板同红外遥控等待机相关设备的类型。
\attention \n
遥控仅支持  HI_UNF_IR_CODE_NEC_SIMPLE 类型\n
前面板支持	HI_UNF_KEYLED_TYPE_STD 同 HI_UNF_KEYLED_TYPE_PT6961 两种类型\n	
\param[in] pdevType  需要MCU支持的待机设备。
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\retval ::HI_ERR_PMoC_INVALID_PARA   非法参数
\retval ::HI_ERR_PMOC_FAILED_SETDEV  设置失败
\see \n
无
*/
HI_S32 HI_UNF_PMOC_SetDevType(HI_UNF_PMOC_DEV_TYPE_S_PTR pdevType);


/** 
\brief 用于加载MCU代码。
\attention \n
仅供调试使用，MCU代码编译完成后，可以使用这个接口载入，避免每次都编译hi_c51.ko\n	
\param[in] pMcuCode MCU二进制代码内容
\param[in] CodeSize MCU二进制代码长度
\retval 0 成功
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC设备未打开
\retval ::HI_ERR_PMoC_INVALID_POINT  非法指针
\retval ::HI_ERR_PMoC_INVALID_PARA   非法参数
\see \n
无
*/
HI_S32 HI_UNF_PMOC_LoadMcuCode(HI_U8 *pMcuCode, HI_U32 CodeSize);



/** @} */  /** <!-- ==== API declaration end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_6 */
/** @{ */  /** <!-- 【IR】 */
/*---IR---*/
/** 
\brief 打开IR设备。
\attention \n
重复调用会失败，打开设备后必须再调用HI_UNF_IR_Enable才能正常接收键值。
\param 无
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  按键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  重复键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_Open(HI_VOID);

/** 
\brief 关闭IR设备。
\attention \n
重复调用关闭会失败。
\param 无
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  按键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  重复键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_Close(HI_VOID);


/** 
\brief 使能IR设备。
\attention \n
无
\param[in] bEnable  IR 使能开关, HI_TRUE 使能, HI_FALSE 禁用。
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  按键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  重复键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_Enable ( HI_BOOL bEnable);

/** 
\brief 获取遥控器的协议类型 。
\attention \n
如果需要获取红外遥控器的协议类型，请在调用HI_UNF_IR_GetValue之后再调用HI_UNF_IR_GetProtocol。

如果HI_UNF_IR_SelectUserCode接口参数u32UserCode为0，则pu32KeyId包含按键的完整码值（用户码和数据码）；如果用户码不为0，则pu32KeyId只包含按键的数据码
\param[out]  penProtocol  协议类型指针  具体含义请参考::HI_UNF_IR_PROTOCOL_E
\param[in]   penProtocol  协议类型指针
\retval 0 成功
\retval ::HI_ERR_IR_NULL_PTR  指针为空
\see \n
无
*/

HI_S32 HI_UNF_IR_GetProtocol(HI_UNF_IR_PROTOCOL_E *penProtocol);

/** 
\brief 获取遥控器的按键值和按键状态 。
\attention \n
阻塞方式下，调用HI_UNF_IR_GetValue函数时，当超时（调用HI_UNF_IR_SetBlockTime函数设置超时时间u32BlockTime）时返回错误信息\n
如果HI_UNF_IR_SelectUserCode接口参数u32UserCode为0，则pu32KeyId包含按键的完整码值（用户码和数据码）；如果用户码不为0，则pu32KeyId只包含按键的数据码
\param[out]  penPressStatus  按键状态。具体含义请参考::HI_UNF_KEY_STATUS_E
\param[out]  pu64KeyId  按键值
\param[in] u32TimeoutMs   超时值, 单位是毫秒, 0 - 不阻塞, 0xFFFFFFFF-永久阻塞
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  按键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  重复键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_GetValue(HI_UNF_KEY_STATUS_E * penPressStatus, HI_U64 * pu64KeyId , HI_U32 u32TimeoutMs);


/** 
\brief 设置是否上报按键弹起状态。
\attention \n
如不设置，默认为打开。
\param[in] bEnable       按键弹起有效。
                         0：关闭；
                         1：使能。
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  按键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  重复键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_EnableKeyUp(HI_BOOL bEnable );


/** 
\brief 设置是否上报重复按键。一直按键时，数据会源源不断的送入到接收缓冲区，因此应用程序可以根据需要来设置是否上报重复按键。
\attention \n
如不设置，默认为打开\n
此接口需要和HI_UNF_IR_RepKeyTimeoutVal函数结合使用，由HI_UNF_IR_RepKeyTimeoutVal设置上报重复按键的间隔\n
如果使能了重复按键上报，当按键一直处于按下状态，间隔设为300毫秒，则每300毫秒会上报一次数据\n
如果禁止了重复按键上报，则不论按下多长时间，只上报一次数据。
\param[in] bEnable        按键产生重复按键功能。
                          0：关闭；
                          1：使能。
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  按键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  重复键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_EnableRepKey(HI_BOOL bEnable);


/** 
\brief 设置上报重复按键的时间间隔，单位为ms 。
\attention \n
当HI_UNF_IR_IsRepKey配置为不上报重复按键时，此接口设置无效。
\param[in] u32TimeoutMs   上报重复按键的时间间隔，建议值：108ms～65536ms 。
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  按键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  重复键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_SetRepKeyTimeoutAttr(HI_U32 u32TimeoutMs);


/** 
\brief 设置遥控器码型。
\attention \n
如不设置，默认为HI_UNF_IR_CODE_NEC_SIMPLE码型。
\param[in] enIRCode  默认支持4种标准遥控器码型：
                     HI_UNF_IR_CODE_NEC_SIMPLE：Nec With Simple码型；
                     HI_UNF_IR_CODE_TC9012：TC9012码型；
                     HI_UNF_IR_CODE_NEC_FULL：Nec With Full码型；
                     HI_UNF_IR_CODE_SONY_12BIT：Sony12Bit码型。
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_SetCodeType(HI_UNF_IR_CODE_E enIRCode);


/** 
\brief  复位IR设备。
\attention \n
只是把buffer中的键值清掉，清掉之后不需要重新设置用户码。
\param 无
\retval 0 成功
\retval ::HI_ERR_IR_NOT_INIT  IR设备未初始化
\retval ::HI_ERR_IR_INVALID_POINT  指针为空
\retval ::HI_ERR_IR_INVALID_PARA  参数非法
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  按键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  重复键是否上报参数非法
\retval ::HI_ERR_IR_INVALID_CODETYPE  码型参数非法
\see \n
无
*/
HI_S32 HI_UNF_IR_Reset(HI_VOID);

/** @} */  /** <!-- ==== API declaration end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_7 */
/** @{ */  /** <!-- 【WDG】 */
/*---- wdg ----*/
/** 
\brief 打开WDG（Watch Dog）设备。
\attention \n
打开之后，WDG默认是禁止的，需要显式调用HI_UNF_WDG_Enable使能WDG设备\N
重复打开会失败。
\param 无
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT  WDG输入指针无效
\retval ::HI_ERR_WDG_INVALID_PARA  WDG输入参数无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_Open(HI_VOID);


/** 
\brief 关闭WDG设备。
\attention \n
重复关闭会失败。
\param 无
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT  WDG输入指针无效
\retval ::HI_ERR_WDG_INVALID_PARA  WDG输入参数无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_Close(HI_VOID);


/** 
\brief 使能WDG设备。
\attention \n
打开WDG设备后，必须显式调用使能接口。
\param 无
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT  WDG输入指针无效
\retval ::HI_ERR_WDG_INVALID_PARA  WDG输入参数无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_Enable(HI_VOID);

/** 
\brief 禁止WDG设备。
\attention \n
调用此函数后，喂狗和复位操作不起作用。
\param 无
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT  WDG输入指针无效
\retval ::HI_ERR_WDG_INVALID_PARA  WDG输入参数无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_Disable(HI_VOID);


/** 
\brief 获取喂狗时间间隔。
\attention \n
时间间隔精确到1000ms。
\param[in] pu32Value  喂狗时间间隔，单位为ms
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG 设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT WDG输入指针无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_GetTimeout(HI_U32 *pu32Value);

/** 
\brief 设置喂狗时间间隔。
\attention \n
无
\param[in] u32Value  喂狗时间间隔，单位为ms
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT  WDG输入指针无效
\retval ::HI_ERR_WDG_INVALID_PARA  WDG输入参数无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_SetTimeout(HI_U32 u32Value);


/** 
\brief 执行喂狗操作。
\attention \n
无
\param 无
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT  WDG输入指针无效
\retval ::HI_ERR_WDG_INVALID_PARA  WDG输入参数无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_ClearWatchDog (HI_VOID);


/** 
\brief 设置WDG的响应模式。
\attention \n
无
\param[in] enRespondMode  响应模式。
                          HI_UNF_WDG_RESPOND_MODE_FIRSTRESET：第一次复位；
                          HI_UNF_WDG_RESPOND_MODE_SECONDRESET：第一次中断，第二次复位。
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT  WDG输入指针无效
\retval ::HI_ERR_WDG_INVALID_PARA  WDG输入参数无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_RespondMode(HI_UNF_WDG_RESPOND_MODE_E enRespondMode);

/** 
\brief 用于复位整个系统。
\attention \n
无
\param 无
\retval 0 成功
\retval ::HI_ERR_WDG_NOT_INIT  WDG设备未初始化
\retval ::HI_ERR_WDG_INVALID_POINT  WDG输入指针无效
\retval ::HI_ERR_WDG_INVALID_PARA  WDG输入参数无效
\see \n
无
*/
HI_S32 HI_UNF_WDG_Reset(HI_VOID);

/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_8 */
/** @{ */  /** <!-- 【GPIO】 */
/**---- GPIO----*/
/** 
\brief 打开GPIO（General Purpose Input/Output）设备。
\attention \n
重复打开会成功。
\param 无
\retval 0 成功
\retval ::HI_ERR_GPIO_NOT_INIT  GPIO设备未初始化
\retval ::HI_ERR_GPIO_INVALID_POINT  指针为空
\retval ::HI_ERR_GPIO_INVALID_PARA  参数非法
\retval ::HI_ERR_GPIO_FAILED_SWITCH2LED  外设功能切换到GPIO功能操作失败
\retval ::HI_ERR_GPIO_FAILED_LED_DIRSET_BIT  TUNER指示灯对应GPIO管脚方向设置失败
\retval ::HI_ERR_GPIO_FAILED_LED_WRITE_BIT  写TUNER指示灯对应GPIO管脚操作失败
\see \n
无
*/
HI_S32 HI_UNF_GPIO_Open(HI_VOID);


/** 
\brief 关闭GPIO设备。
\attention \n
重复关闭会成功。
\param 无
\retval 请参考错误码定义章节
\see \n
无
*/
HI_S32 HI_UNF_GPIO_Close(HI_VOID);

/** 
\brief 从GPIO单个引脚读取数据。
\attention 管脚号计算规则: 管脚号 = GPIO组号*8 + GPIO管脚在组内的遍号。\n
比如GPIO1_2,代表第1组第2脚，那么管脚号=1*8+2=10。\n
GPIO的组号和管脚号的编号都从0开始。高清芯片提供13组GPIO，共104个管脚\n
无
\param[out] u32GpioNo  管脚号，取值范围为0～103。
\param[out] pbHighVolt  指针类型，返回管脚输入电平。
\retval 请参考错误码定义章节
\see \n
无
*/
HI_S32 HI_UNF_GPIO_ReadBit(HI_U32  u32GpioNo , HI_BOOL  *pbHighVolt );


/** 
\brief 向GPIO单个引脚输出数据。
\attention \n
无
\param[in] u32GpioNo  管脚号，取值范围为0～103。
\param[in] bHighVolt  管脚输出电平。
                      0：低电平；
                      1：高电平；
                      其他：高电平。
\retval 请参考错误码定义章节
\see \n
无
*/
HI_S32 HI_UNF_GPIO_WriteBit(HI_U32  u32GpioNo , HI_BOOL     bHighVolt );


/** 
\brief 设置GPIO单个引脚输入输出方向。
\attention \n
设置对应管脚的工作方式时，必须保证该管脚仅工作在GPIO模式下\n
GPIO管脚有可能被复用。
\param[in] u32GpioNo  管脚号，取值范围为0～103。
\param[in] bInput  布尔变量，标识管脚方向。
                   HI_TRUE：该管脚用于输入；
                   HI_FALSE：该管脚用于输出。
\retval 请参考错误码定义章节
\see \n
无
*/
HI_S32 HI_UNF_GPIO_SetDirBit(HI_U32  u32GpioNo , HI_BOOL    bInput);


/** 
\brief 获取GPIO单个引脚输入输出方向。
\attention \n
无
\param[in] u32GpioNo  管脚号，取值范围为0～103。
\param[out] pbInput  指针类型，指向布尔型变量，用来返回管脚方向。
\retval 请参考错误码定义章节
\see \n
无
*/
HI_S32 HI_UNF_GPIO_GetDirBit(HI_U32  u32GpioNo , HI_BOOL    *pbInput);

/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_9 */
/** @{ */  /** <!-- 【CIPHER】 */
/* ---CIPHER---*/
/** 
\brief 打开CIPHER设备。
\attention \n
调用此接口打开CIPHER设备。重复打开返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CIPHER_FAILED_INIT  CIPHER设备初始化失败
\see \n
无
*/
HI_S32 HI_UNF_CIPHER_Open(HI_VOID);

/** 
\brief  关闭CIPHER设备。
\attention \n
调用此接口关闭CIPHER设备。重复关闭返回成功，第一次起作用。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER设备未初始化
\see \n
无
*/
HI_S32 HI_UNF_CIPHER_Close(HI_VOID);

/** 
\brief 创建一路CIPHER，获取CIPHER句柄。
\attention \n
调用此接口获取1个CIPHER句柄，用于加解密。
\param[out] phCipher CIPHER句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER设备未初始化
\retval ::HI_ERR_CIPHER_INVALID_POINT  指针参数为空
\retval ::HI_ERR_CIPHER_FAILED_GETHANDLE  获取CIPHER句柄失败，没有空闲的CIPHER句柄

\see \n
无
*/
HI_S32 HI_UNF_CIPHER_CreateHandle(HI_HANDLE* phCipher);

/** 
\brief 销毁创建的CIPHER句柄。
\attention \n
调用此接口销毁已经创建的CIPHER句柄。
\param[in] hCipher CIPHER句柄。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER设备未初始化
\see \n
无
*/
HI_S32 HI_UNF_CIPHER_DestroyHandle(HI_HANDLE hCipher);

/** 
\brief 配置CIPHER控制信息
\attention \n
进行加密解密前必须先使用此接口配置CIPHER的控制信息。
\param[in] hCipher CIPHER句柄。
\param[in] pstCtrl CIPHER控制信息。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER设备未初始化
\retval ::HI_ERR_CIPHER_INVALID_POINT  指针参数为空
\retval ::HI_ERR_CIPHER_INVALID_PARA  参数错误
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  句柄非法
\see \n
无
*/
HI_S32 HI_UNF_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl);

/** 
\brief 进行加密 
\attention \n
使用CIPHER进行加密操作。
\param[in] hCipher CIPHER句柄。
\param[in] u32SrcPhyAddr 源数据物理地址。
\param[in] u32DestPhyAddr 目的数据物理地址。
\param[in] u32ByteLength 加密数据长度。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER设备未初始化
\retval ::HI_ERR_CIPHER_INVALID_PARA  参数错误
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  句柄非法
\see \n
无
*/
HI_S32 HI_UNF_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);

/** 
\brief 进行加密
\attention \n
使用CIPHER进行解密操作。
\param[in] hCipher CIPHER句柄。
\param[in] u32SrcPhyAddr 源数据物理地址。
\param[in] u32DestPhyAddr 目的数据物理地址。
\param[in] u32ByteLength 解密数据长度。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER设备未初始化
\retval ::HI_ERR_CIPHER_INVALID_PARA  参数错误
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  句柄非法
\see \n
无
*/
HI_S32 HI_UNF_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_10 */
/** @{ */  /** <!-- 【TUNER】 */
/*---TUNER---*/
/** 
\brief 初始化TUNER设备。
\attention \n
支持重复初始化TUNER设备，此时直接返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_Init(HI_VOID);


/** 
\brief 去初始化TUNER设备。
\attention \n
支持重复去初始化TUNER设备，此时直接返回成功。
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_DeInit(HI_VOID);


/** 
\brief  获取TUNER的默认属性。
\attention \n
此接口在TUNER设备初始化后才能使用。
\param[in] u32tunerId TUNER端口号，取值为0或1。
\param[out] pstTunerAttr 返回当前TUNER的默认属性。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_GetDeftAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr );


/** 
\brief 设置TUNER当前属性。
\attention \n
无
\param[in] u32tunerId TUNER端口号，取值为0或1。
\param[in] pstTunerAttr TUNER的属性。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_TUNER_SetAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr );


/** 
\brief 获取TUNER的属性。
\attention \n
此接口在TUNER设备初始化后才能使用。
\param[in] u32tunerId  TUNER端口号，取值为0或1。
\param[out] pstTunerAttr 返回当前TUNER的属性。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_GetAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr );


/** 
\brief 打开TUNER设备。
\attention \n
支持重复打开TUNER设备。此时，直接返回成功。
\param[in] u32tunerId  TUNER端口号，取值为0或1。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_Open (HI_U32    u32tunerId);


/** 
\brief 关闭TUNER设备。
\attention \n
支持重复关闭TUNER设备。此时，直接返回成功。
\param[in] u32tunerId  TUNER端口号，取值为0或1。 
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_Close(HI_U32    u32tunerId);


/** 
\brief TUNER锁频。
\attention \n
无
\param[in] u32tunerId  TUNER端口号，取值为0或1。
\param[in] pstConnectPara  TUNER的频点信息。
\param[in] u32TimeOut  TUNER的锁定等待超时时间，0为不等待，其他为最长等待时间，单位ms。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_Connect(HI_U32  u32tunerId , HI_UNF_TUNER_CONNECT_PARA_S  *pstConnectPara,HI_U32 u32TimeOut);


/** 
\brief 获取TUNER锁频状态和锁频参数。
\attention \n
无
\param[in] u32tunerId TUNER端口号，取值为0或1。
\param[out] pstTunerStatus: 返回当前TUNER的锁频状态和锁频参数。 注意：此参数只在函数返回成功的情况下才有意义。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_GetStatus(HI_U32    u32tunerId , HI_UNF_TUNER_STATUS_S  *pstTunerStatus);


/** 
\brief 获取当前TUNER 的误码率，用科学计数法表示。
\attention \n
无
\param[in] u32tunerId TUNER端口号，取值为0或1。
\param[out] pu32BER  指向当前TUNER 误码率的指针。该指针指向一个包含三个元素的数组，三个元素含义如下:
                    pu32BER[0]:误码率底数的整数部分
                    pu32BER[1]:误码率底数的小数部分乘以1000
                    pu32BER[2]:误码率指数部分取绝对值
                    例如:误码率为2.156E-7，那么三个元素的取值分别为
                    2、156和7
                    这三个元素只在函数返回成功的情况下才有意义，
                    否则应用层可根据实际情况自行设置一个较大值(比如0.5，即三个元素分别为5、0、1)。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_GetBER(HI_U32   u32tunerId , HI_U32 *pu32BER);


/** 
\brief 获取当前TUNER 的信噪比。
\attention \n
无
\param[in] u32tunerId  TUNER端口号，取值为0或1。
\param[out] pu32SNR  指向当前TUNER信噪比的指针。
                    *pu32SNR取值范围为22 ~ 51
                    此参数只在函数返回成功的情况下才有意义，
                    否则，应用层可将此值设置为最小值。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败

\see \n
无
*/
HI_S32 HI_UNF_TUNER_GetSNR(HI_U32   u32tunerId , HI_U32 *pu32SNR );             /* range : 0-255  */


/** 
\brief 获取当前TUNER的信号强度。
\attention \n
无
\param[in] u32tunerId  TUNER端口号，取值为0或1。
\param[out] pu32SignalStrength  指向当前TUNER信号强度的指针。
                    *pu32SignalStrength的取值范围为20~60
                  此参数只在函数返回成功的情况下才有意义，
                  否则，应用层可将此值设置为最小值。
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_TUNER_GetSignalStrength(HI_U32   u32tunerId , HI_U32 *pu32SignalStrength );


/** 
\brief 获取当前TUNER的实际频率和符号率。
\attention \n
无
\param[in] u32tunerId  TUNER端口号，取值为0或1。
\param[out] pu32Freq  指向当前TUNER频点的指针。
                    pu32Symb指向当前符号率
               
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_TUNER_GetRealFreqSymb( HI_U32 u32TunerId, HI_U32 *pu32Freq, HI_U32 *pu32Symb );

/** 
\brief 打开OTP设备
\attention \n
无
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_OTP_Open(HI_VOID);

/** 
\brief 关闭OTP设备
\attention \n
无
\param 无
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_OTP_Close(HI_VOID);

/** 
\brief 写OTP
\attention \n
无
\param[in] enType    OTP区域类型
\param[in] pKey      写入的内容首地址
\param[in] u32KeyLen 写入的内容长度 单位 Byte
\retval ::HI_SUCCESS 成功
\retval ::HI_FAILURE  API系统调用失败
\see \n
无
*/
HI_S32 HI_UNF_OTP_Write(HI_UNF_OTP_AREATYPE_E enType,HI_U8 *pKey,HI_U32 u32KeyLen);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_ECS_TYPE_H__ */

