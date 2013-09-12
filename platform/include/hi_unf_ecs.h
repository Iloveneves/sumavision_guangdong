/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
 File Name     : hi_unf_ecs_type.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2008/6/5
Last Modified :
Description   : ECS API�ӿ�
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

#define HI_I2C_MAX_NUM_USER      15 /**< ���I2Cͨ����*/

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_1 */
/** @{ */  /** <!-- ��QAM�� */

/**QAM���Ʒ�ʽ*/
typedef enum hiUNF_QAM_TYPE_E
{
    HI_UNF_MOD_TYPE_DEFAULT,                /**<Ĭ�ϵ�QAM����, ��ǰϵͳĬ��ΪHI_UNF_MOD_TYPE_QAM_64 */
    HI_UNF_MOD_TYPE_QAM_16 = 0x100,         /**<16QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_32,                 /**<32QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_64,                 /**<64QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_128,                /**<128QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_256,                /**<256QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_512,                /**<512QAM��Ӧ��ö��ֵ*/

    HI_UNF_MOD_TYPE_BPSK = 0x200,           /**<BPSK QAM��Ӧ��ö��ֵ���ݲ�֧��*/
    HI_UNF_MOD_TYPE_QPSK = 0x300,           /**<QPSK QAM��Ӧ��ö��ֵ���ݲ�֧��*/

    HI_UNF_MOD_TYPE_BUTT                    /**<�Ƿ���QAM����ö��ֵ*/
}HI_UNF_MODULATION_TYPE_E;

/**TUNER��Ƶ״̬*/
typedef enum  hiUNF_TUNER_LOCK_STATUS_E
{
    HI_UNF_TUNER_SIGNAL_DROPPED = 0,        /**<�ź�δ����*/
    HI_UNF_TUNER_SIGNAL_LOCKED,             /**<�ź�������*/
    HI_UNF_TUNER_SIGNAL_BUTT                /**<�Ƿ��߽�ֵ*/
}HI_UNF_TUNER_LOCK_STATUS_E;

/**TUNER���ģʽ */
typedef enum hiUNF_TUNER_OUTPUT_MODE_E
{
    HI_UNF_TUNER_OUTPUT_MODE_DEFAULT ,              /**<Ĭ��ģʽ*/
    HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A,       /**<����ģʽA*/
    HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_B,       /**<����ģʽB*/
    HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_C,       /**<����ģʽC*/
    HI_UNF_TUNER_OUTPUT_MODE_SERIAL,                /**<����ģʽ*/
    HI_UNF_TUNER_OUTPUT_MODE_BUTT                   /**<�Ƿ�ֵ*/
}HI_UNF_TUNER_OUPUT_MODE_E;

/**TUNER�ź�����*/
typedef enum    hiTUNER_SIG_TYPE_E
{
    HI_UNF_TUNER_SIG_TYPE_CAB = 0  ,     /**<CABLE�ź�*/
    HI_UNF_TUNER_SIG_TYPE_TER  ,         /**<�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_SAT ,          /**<�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_BUTT           /**<�Ƿ�ֵ*/
}HI_UNF_TUNER_SIG_TYPE_E;

/**TUNERʹ�õ�I2Cͨ��*/
typedef enum hiUNF_TUNER_I2cChannel
{
    HI_UNF_I2C_CHANNEL_0 = 0,           /**<I2Cͨ��0*/
    HI_UNF_I2C_CHANNEL_1,               /**<I2Cͨ��1*/
    HI_UNF_I2C_CHANNEL_2,               /**<I2Cͨ��2*/
    HI_UNF_I2C_CHANNEL_3,               /**<I2Cͨ��3*/
    HI_UNF_I2C_CHANNEL_QAM = 4,         /**<����QAMר��I2Cͨ�� */
    HI_UNF_I2C_CHANNEL_5,               /**GPIOģ��I2C*/
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
    HI_UNF_I2C_CHANNEL_MAX              /**<�Ƿ��߽�ֵ*/
}HI_UNF_TUNER_I2cChannel_E;

/**TUNER�豸����*/
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

    HI_UNF_TUNER_DEV_TYPE_BUTT,                 /**<�Ƿ��߽�ֵ*/
}HI_UNF_TUNER_DEV_TYPE_E ;

/**QAM�豸����*/
typedef enum    hiUNF_DEMOD_DEV_TYPE_E
{
    HI_UNF_DEMOD_DEV_TYPE_NONE,                 /**<��֧��*/  
    HI_UNF_DEMOD_DEV_TYPE_3130I= 0x100,         /**<�ڲ�QAM*/
    HI_UNF_DEMOD_DEV_TYPE_3130E,                /**<�ⲿHi3130оƬ*/

    HI_UNF_DEMOD_DEV_TYPE_PHILIP = 0x200,       /**<PHILIP*/
    HI_UNF_DEMOD_DEV_TYPE_ST,                   /**<ST*/
    HI_UNF_DEMOD_DEV_TYPE_GX,                   /**<GX*/

    HI_UNF_DEMOD_DEV_TYPE_BUTT,                 /**<�Ƿ��߽�ֵ*/
}HI_UNF_DEMOD_DEV_TYPE_E ;

/**����CABLE�����ź�*/
typedef struct  hiUNF_CAB_CONNECT_PARA_S
{
    HI_U32                      u32Freq;             /**<Ƶ�ʣ���λ��kHz*/
    HI_U32                      u32SymbolRate ;      /**<�����ʣ���λbps */
    HI_UNF_MODULATION_TYPE_E    enModType ;          /**<QAM���Ʒ�ʽ*/
    HI_BOOL                     bReverse ;           /**<Ƶ�׵��ô���ʽ*/
}HI_UNF_CAB_CONNECT_PARA_S ;

/*��δʹ��*/
typedef enum hiUNF_TUNER_FE_GUARD_INTV_E
{
    HI_UNF_TUNER_FE_GUARD_INTV_DEFALUT = 0 ,    /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_32       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_16       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_8        ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_4        ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_BUTT     ,       /**< */
}HI_UNF_TUNER_FE_GUARD_INTV_E;

/*��δʹ��*/
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

/*��δʹ��*/
typedef enum hiUNF_TUNER_FE_FFT_E
{
    HI_UNF_TUNER_FE_FFT_DEFAULT = 0,   /**< */
    HI_UNF_TUNER_FE_FFT_2K ,           /**< */
    HI_UNF_TUNER_FE_FFT_8K ,           /**< */
    HI_UNF_TUNER_FE_FFT_BUTT ,         /**< */
}HI_UNF_TUNER_FE_FFT_E;

/*��δʹ��*/
typedef enum hiUNF_TUNER_FE_HIERARCHY_E
{
    HI_UNF_TUNER_FE_HIERARCHY_DEFAULT = 0 ,   /**< */
    HI_UNF_TUNER_FE_HIERARCHY_NO,             /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA1,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA2,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA4,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_BUTT,           /**< */
}HI_UNF_TUNER_FE_HIERARCHY_E ;

/*��δʹ��*/
typedef struct  hiUNF_TER_CONNECT_PARA_S
{
    HI_U32          u32Freq     ;                    /**< */
    HI_U32          u32BandWidth    ;                /**< */
    HI_UNF_MODULATION_TYPE_E enModType  ;      /**< */
}HI_UNF_TER_CONNECT_PARA_S ;

/*��δʹ��*/
typedef struct  hiUNF_TUNER_TER_ATTR_S
{
    HI_UNF_TUNER_FE_DEPUNC_RATE_E   enHpCode ;      /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_E   enLpCode ;      /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_E    enGuardIntv ;   /**< */
    HI_UNF_TUNER_FE_FFT_E       enFftType ;           /**< */
    HI_UNF_TUNER_FE_HIERARCHY_E enHierType ;      /**< */

}HI_UNF_TUNER_TER_ATTR_S;


/**TUNER����*/
typedef struct  hiTUNER_ATTR_S
{
    HI_UNF_TUNER_SIG_TYPE_E     enSigType ;          /**<�ź�����*/
    HI_UNF_TUNER_DEV_TYPE_E     enTunerDevType ;     /**<TUNER����*/
    HI_UNF_DEMOD_DEV_TYPE_E     enDemodDevType ;     /**<QAM����*/
    HI_UNF_TUNER_OUPUT_MODE_E   enOutputMode ;       /**<TS�����ģʽ*/
    HI_UNF_TUNER_I2cChannel_E   enI2cChannel;        /**<TUNERʹ�õ�I2Cͨ��*/

    union{
        HI_UNF_TUNER_TER_ATTR_S stTer ;         /**<�����ź����ԣ��ݲ�֧��*/
    }unTunerAttr ;
}HI_UNF_TUNER_ATTR_S ;

/**TUNER��Ƶ����*/
typedef struct  hiUNF_TUNER_CONNECT_PARA_S
{
    HI_UNF_TUNER_SIG_TYPE_E enSigType ;         /**<�ź�����*/

    union
    {
        HI_UNF_CAB_CONNECT_PARA_S   stCab ;     /**<CABLE�����ź�*/
        HI_UNF_TER_CONNECT_PARA_S   stTer ;     /**<���洫���ź�*/
    }unConnectPara;
}HI_UNF_TUNER_CONNECT_PARA_S ;

/**TUNER��Ƶ״̬����Ƶ����*/
typedef struct  hiUNF_TUNER_STATUS_S
{
    HI_UNF_TUNER_LOCK_STATUS_E  enLockStatus ;      /**<��Ƶ״̬*/
    HI_UNF_TUNER_CONNECT_PARA_S stConnectPara;      /**<ʵ����Ƶ����*/
}HI_UNF_TUNER_STATUS_S ;

/** @} */  /** <!-- ==== Structure Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_3 */
/** @{ */  /** <!-- ��SCI�� */

/**SCICLK�����������*/
typedef enum  hiUNF_SCI_CLK_MODE_E
{
    HI_UNF_SCI_CLK_MODE_CMOS = 0,   /**<CMOS���*/
    HI_UNF_SCI_CLK_MODE_OD,         /**<OD���*/
    HI_UNF_SCI_CLK_MODE_BUTT
}HI_UNF_SCI_CLK_MODE_E;

/** SCI �˿� */
typedef enum hiUNF_SCI_PORT_E
{
    HI_UNF_SCI_PORT0,        /**< SCI�˿�0*/
    HI_UNF_SCI_PORT1,        /**< SCI�˿�1*/
    HI_UNF_SCI_PORT_BUTT     
}HI_UNF_SCI_PORT_E;

/** ���ܿ�״̬ */
typedef enum hiUNF_SCI_STATUS_E
{
    HI_UNF_SCI_STATUS_UNINIT     = 0,           /**< SCIδ��ʼ�� */
    HI_UNF_SCI_STATUS_FIRSTINIT,                /**< SCI��ʼ��������*/
    HI_UNF_SCI_STATUS_NOCARD,                   /**< �޿� */
    HI_UNF_SCI_STATUS_INACTIVECARD,             /**<��δ��ɼ������Ч�� */
 //   HI_UNF_SCI_STATUS_CARDFAULT,		     /*������*/
    HI_UNF_SCI_STATUS_WAITATR,                  /**<�ȴ�ATR*/
    HI_UNF_SCI_STATUS_READATR,                  /**<���ڽ���ATR*/
    HI_UNF_SCI_STATUS_READY,                    /**<������ʹ�ã������ */
    HI_UNF_SCI_STATUS_RX,                       /**<��æ�����������У� */
    HI_UNF_SCI_STATUS_TX                        /**<��æ�����������У� */
} HI_UNF_SCI_STATUS_E;

/** SCI Э�� */
typedef enum hiUNF_SCI_PROTOCOL_E
{
    HI_UNF_SCI_PROTOCOL_T0,     /**<7816 T0 Э�� */
    HI_UNF_SCI_PROTOCOL_T1,     /**<7816 T1 Э�� */
    HI_UNF_SCI_PROTOCOL_T14 ,   /**<7816 T14 Э�� */
    HI_UNF_SCI_PROTOCOL_BUTT
}HI_UNF_SCI_PROTOCOL_E;

/**SCI��Ч��ƽ*/
typedef enum hiUNF_SCI_LEVEL_E
{
    HI_UNF_SCI_LEVEL_LOW,      /**<�͵�ƽ��Ч */
    HI_UNF_SCI_LEVEL_HIGH,     /**<�ߵ�ƽ��Ч */
    HI_UNF_SCI_LEVEL_BUTT      
}HI_UNF_SCI_LEVEL_E ;

/**SCI ϵͳ���� */
typedef struct hiUNF_SCI_PARAMS_S
{
	HI_UNF_SCI_PORT_E enSciPort;			/**<SCI �˿ں� */
	HI_UNF_SCI_PROTOCOL_E enProtocolType;/**<ʹ�õ�Э������ */
	HI_U32 ActalClkRate;		/**<ʵ�ʵ�F ֵʱ��ת������ */
	HI_U32 ActalBitRate;		/**<ʵ�ʵ�D ֵ������ת������ */
	HI_U32 Fi;				/**<ATR ���ص�ʱ������ */
	HI_U32 Di;				/**<ATR ���صı��������� */
	HI_U32 GuardDelay;		/**<N ֵ�������ӵı���ʱ��*/
	HI_U32 CharTimeouts;		/**<T0 ��T1���ַ���ʱʱ��*/
	HI_U32 BlockTimeouts;	/**<T1�Ŀ鳬ʱʱ��*/
	HI_U32 TxRetries;			/**<�������Դ���*/
}HI_UNF_SCI_PARAMS_S,*HI_UNF_SCI_PARAMS_S_PTR;


/** @} */  /** <!-- ==== Structure Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_4 */
/** @{ */  /** <!-- ��E2PROM�� */

/**E2PROM�ͺŶ���*/
typedef enum hiUNF_E2PROM_CHIP_E
{
    HI_UNF_E2PROM_CHIP_AT24C01,    /**<E2PROM�ͺţ�AT24C01 */
    HI_UNF_E2PROM_CHIP_AT24C02,    /**<E2PROM�ͺţ�AT24C02 */
    HI_UNF_E2PROM_CHIP_AT24C04,    /**<E2PROM�ͺţ�AT24C04 */
    HI_UNF_E2PROM_CHIP_AT24C08,    /**<E2PROM�ͺţ�AT24C08 */
    HI_UNF_E2PROM_CHIP_AT24C16,    /**<E2PROM�ͺţ�AT24C16 */
    HI_UNF_E2PROM_CHIP_AT24C32,    /**<E2PROM�ͺţ�AT24C32 */
    HI_UNF_E2PROM_CHIP_AT24C64,    /**<E2PROM�ͺţ�AT24C64 */
    HI_UNF_E2PROM_CHIP_AT24C128,   /**<E2PROM�ͺţ�AT24C128 */
    HI_UNF_E2PROM_CHIP_AT24C256,   /**<E2PROM�ͺţ�AT24C256 */
    HI_UNF_E2PROM_CHIP_M24LC01,    /**<E2PROM�ͺţ�M24LC01 */
    HI_UNF_E2PROM_CHIP_M24LC02,    /**<E2PROM�ͺţ�M24LC02 */
    HI_UNF_E2PROM_CHIP_M24LC04,    /**<E2PROM�ͺţ�M24LC04 */
    HI_UNF_E2PROM_CHIP_M24LC08,    /**<E2PROM�ͺţ�M24LC08 */
    HI_UNF_E2PROM_CHIP_M24LC16,    /**<E2PROM�ͺţ�M24LC16 */
    HI_UNF_E2PROM_CHIP_M24LC32,    /**<E2PROM�ͺţ�M24LC32 */
    HI_UNF_E2PROM_CHIP_M24LC64,    /**<E2PROM�ͺţ�M24LC64 */
    HI_UNF_E2PROM_CHIP_M24LC128,   /**<E2PROM�ͺţ�M24LC128 */
    HI_UNF_E2PROM_CHIP_M24LC256,   /**<E2PROM�ͺţ�M24LC256 */

    HI_UNF_E2PROM_CHIP_BUTT
}HI_UNF_E2PROM_CHIP_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_5 */
/** @{ */  /** <!-- ��IR�� */

/**IR֧�ֵ�����*/
typedef enum hiUNF_IR_CODE_E
{
    HI_UNF_IR_CODE_NEC_SIMPLE = 0,  /**<NEC with simple repeat code����*/
    HI_UNF_IR_CODE_TC9012,          /**<TC9012����*/
    HI_UNF_IR_CODE_NEC_FULL,        /**<NEC with full repeat code����*/
    HI_UNF_IR_CODE_SONY_12BIT,      /**<SONY 12BIT����*/
    HI_UNF_IR_CODE_RAW,      		/**<raw ����*/
    HI_UNF_IR_CODE_BUTT
}HI_UNF_IR_CODE_E;


/**IR�����б�,HI_UNF_IR_STD���������HI_UNF_IR_CODE_E */
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
/** @{ */  /** <!-- ��KEYLED�� */

/**KEYLED���� */
typedef enum  hiUNF_KEYLED_TYPE_E
{
    HI_UNF_KEYLED_TYPE_STD = 0x0,  /**<��˼оƬ�Դ���KEYLED���� */
    HI_UNF_KEYLED_TYPE_PT6961,     /**<KEYLED�ͺţ�PT6961 */
    HI_UNF_KEYLED_TYPE_CT1642,     /**<KEYLED�ͺţ�CT1642 */
    HI_UNF_KEYLED_TYPE_PT6964,     /**<KEYLED�ͺţ�PT6964 */
    HI_UNF_KEYLED_TYPE_BUTT        /**< */
}HI_UNF_KEYLED_TYPE_E;

/**����״̬ */
typedef enum  hiUNF_KEY_STATUS_E
{
    HI_UNF_KEY_STATUS_DOWN = 0 ,    /**<���°��� */
    HI_UNF_KEY_STATUS_HOLD ,        /**<��ס���� */
    HI_UNF_KEY_STATUS_UP ,          /**<̧�𰴼� */

    HI_UNF_KEY_STATUS_BUTT
}HI_UNF_KEY_STATUS_E ;

/**LED��˸Ƶ�ʼ���*/
typedef enum hiUNF_KEYLED_LEVEL_E
{
    HI_UNF_KEYLED_LEVEL_1 = 0x01,     /**<����1,��˸Ƶ������*/
    HI_UNF_KEYLED_LEVEL_2,            /**<����2 */
    HI_UNF_KEYLED_LEVEL_3,            /**<����3 */
    HI_UNF_KEYLED_LEVEL_4,            /**<����4 */
    HI_UNF_KEYLED_LEVEL_5,            /**<����5 , ��˸Ƶ�����*/

    HI_UNF_KEYLED_LEVEL_BUTT
}HI_UNF_KEYLED_LEVEL_E;

/**��˸��LED���*/
typedef enum hiUNF_KEYLED_LIGHT_E
{
    HI_UNF_KEYLED_LIGHT_1 = 0x01,     /**<��1��LED��˸*/
    HI_UNF_KEYLED_LIGHT_2,            /**<��2��LED��˸*/
    HI_UNF_KEYLED_LIGHT_3,            /**<��3��LED��˸*/
    HI_UNF_KEYLED_LIGHT_4,            /**<��4��LED��˸*/
    HI_UNF_KEYLED_LIGHT_ALL,          /**<*����LED����˸*/
    HI_UNF_KEYLED_LIGHT_NONE,         /**<����LED������˸*/

    HI_UNF_KEYLED_LIGHT_BUTT
}HI_UNF_KEYLED_LIGHT_E;

/**LED��ʾʱ��*/
typedef struct hiUNF_KEYLED_Time_S
{
    HI_U32 u32Hour;             /**<ʱ*/
    HI_U32 u32Minute;           /**<��*/
}HI_UNF_KEYLED_TIME_S, *HI_UNF_KEYLED_TIME_S_PTR;

/** @} */  /** <!-- ==== Structure Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_7 */
/** @{ */  /** <!-- ��ARM MODE�� */

/**ARM������ģʽ*/
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
/** @{ */  /** <!-- ��PM�� */

/**���������ѵ����� */
typedef enum hiUNF_PMOC_ACTUAL_WKUP_E
{
     HI_UNF_PMOC_WKUP_IR  =0,      /**<��IR���� */
     HI_UNF_PMOC_WKUP_KEYLED,      /**<��ǰ���KEY���� */
     HI_UNF_PMOC_WKUP_TIMEOUT,     /**<����ʱ�жϻ��� */
     HI_UNF_PMOC_WKUP_BUTT        
}HI_UNF_PMOC_ACTUAL_WKUP_E;

typedef enum hiUNF_PMOC_SCENE_E
{
     HI_UNF_PMOC_SCENE_STANDARD  =0,  /**<��׼���� */
     HI_UNF_PMOC_SCENE_ETH,           /**<����ת������ */
     HI_UNF_PMOC_SCENE_PHONE,         /**<ͨ������ */
     HI_UNF_PMOC_SCENE_BUTT        
}HI_UNF_PMOC_SCENE_E;

#define PMOC_WKUP_IRKEY_MAXNUM    6
/**�������ѵ���������*/
typedef struct hiUNF_PMOC_WKUP_S
{
    HI_U32 u32IrPmocNum;					/**<�ܹ�֧��power��ֵ������raw �ͺ���ң��: ���ܳ�ԽPMOC_WKUP_IRKEY_MAXNUM(<=5)�궨������������ֵ����������ֻ��֧��һ����ֵ*/
    HI_U32 u32IrPowerKey0[PMOC_WKUP_IRKEY_MAXNUM];		/**<����ң�� power ��λ��ֵ */
    HI_U32 u32IrPowerKey1[PMOC_WKUP_IRKEY_MAXNUM];		/**<����ң�� power ��λ��ֵ */
    HI_U32 u32KeypadPowerKey;   				/**<���� power   ��ֵ */
    HI_U32 u32WakeUpTime ; 					/**<���Ѷ�ʱʱ�� ,��λΪ ��  */
}HI_UNF_PMOC_WKUP_S, *HI_UNF_PMOC_WKUP_S_PTR;

/**����ʱ��ǰ�����ʾ��ʱ������ */
typedef struct hiUNF_PMOC_TIME_S
{
    HI_U32  	u32Hour;        /**< ʱ */
    HI_U32  	u32Minute;      /**< �� */
    HI_U32  	u32Second;      /**< �� */
}HI_UNF_PMOC_TIME_S,*HI_UNF_PMOC_TIME_S_PTR;

/**����ʱ��ǰ�����ʾ���� */
typedef struct hiUNF_PMOC_STANDBY_MODE_S
{
    HI_U32		u32Mode;	        /**< 0 : ����ʾ 1 : ��ʾu32DispCode���������; 2 : ��ʾstTimeInfo�����ʱ��. */
    HI_U32		u32DispCode;	    /**< u32ModeΪ1ʱ��ǰ�����ʾ������  */
	HI_UNF_PMOC_TIME_S stTimeInfo;	/**< u32ModeΪ2ʱ��ǰ�����ʾ��ʱ�� */
}HI_UNF_PMOC_STANDBY_MODE_S, *HI_UNF_PMOC_STANDBY_MODE_S_PTR;


/**�������ѵ��豸���� */
typedef struct hiUNF_PMOC_DEV_TYPE_S
{
	HI_UNF_IR_CODE_E  irtype;		/**<����ң������ */
	HI_UNF_KEYLED_TYPE_E  kltype; 	/**<ǰ������� */
}HI_UNF_PMOC_DEV_TYPE_S, *HI_UNF_PMOC_DEV_TYPE_S_PTR;


/** @} */  /** <!-- ==== Structure Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_9 */
/** @{ */  /** <!-- ��WDG�� */
/**WDG��Ӧģʽ*/
typedef enum hiUNF_WDG_RESPOND_MODE_E
{
    HI_UNF_WDG_RESPOND_MODE_FIRSTRESET = 0, /**<WDG��һ�θ�λ*/
    HI_UNF_WDG_RESPOND_MODE_SECONDRESET,      /**<WDG��һ���жϣ��ڶ��θ�λ*/

    HI_UNF_WDG_RESPOND_MODE_BUTT
}HI_UNF_WDG_RESPOND_MODE_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_10 */
/** @{ */  /** <!-- ��I2C�� */

/**I2C���������� */
typedef enum hiUNF_I2C_RATE_E
{
    HI_UNF_I2C_RATE_50K = 0,    /**<��׼���ʣ�50kbit/s*/
    HI_UNF_I2C_RATE_100K ,      /**<��׼���ʣ�100kbit/s*/
    HI_UNF_I2C_RATE_200K ,      /**<��׼���ʣ�200kbit/s*/
    HI_UNF_I2C_RATE_300K ,      /**<��׼���ʣ�300kbit/s*/
    HI_UNF_I2C_RATE_400K,         /**<�������ʣ�400kbit/s*/

    HI_UNF_I2C_RATE_BUTT
}HI_UNF_I2C_RATE_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_11 */
/** @{ */  /** <!-- ��CIPHER�� */

/** CIPHER����ģʽ*/
typedef enum hiHI_UNF_CIPHER_WORK_MODE_E
{
    HI_UNF_CIPHER_WORK_MODE_ECB = 0x0,    /**< ECBģʽ��*/
    HI_UNF_CIPHER_WORK_MODE_CBC = 0x1,    /**< CBCģʽ��*/
    HI_UNF_CIPHER_WORK_MODE_CFB = 0x2,    /**< CFBģʽ��*/
    HI_UNF_CIPHER_WORK_MODE_OFB = 0x3,    /**< OFBģʽ��*/
    HI_UNF_CIPHER_WORK_MODE_CTR = 0x4,    /**< CTRģʽ��*/
    HI_UNF_CIPHER_WORK_MODE_BUTT = 0x5    

}HI_UNF_CIPHER_WORK_MODE_E;

/** CIPHER�����㷨*/
typedef enum hiHI_UNF_CIPHER_ALG_E
{
    HI_UNF_CIPHER_ALG_DES  = 0x0,   /**< DES�㷨*/
    HI_UNF_CIPHER_ALG_3DES = 0x1,   /**< 3DES�㷨*/
    HI_UNF_CIPHER_ALG_AES  = 0x2,   /**< AES�㷨*/
    HI_UNF_CIPHER_ALG_BUTT = 0x3   
}HI_UNF_CIPHER_ALG_E;

/** ��Կ����*/
typedef enum hiHI_UNF_CIPHER_KEY_LENGTH_E
{
    HI_UNF_CIPHER_KEY_AES_128BIT = 0x0,   /**< AES���㷽ʽ�²���128bit��Կ����*/
    HI_UNF_CIPHER_KEY_AES_192BIT = 0x1,   /**< AES���㷽ʽ�²���192bit��Կ����*/
    HI_UNF_CIPHER_KEY_AES_256BIT = 0x2,   /**< AES���㷽ʽ�²���256bit��Կ����*/
    HI_UNF_CIPHER_KEY_DES_3KEY = 0x2,     /**< DES���㷽ʽ�²���3��key */
    HI_UNF_CIPHER_KEY_DES_2KEY = 0x3,     /**< DES���㷽ʽ�²���2��key  */
}HI_UNF_CIPHER_KEY_LENGTH_E;

/** ����λ��*/
typedef enum hiHI_UNF_CIPHER_BIT_WIDTH_E
{
    HI_UNF_CIPHER_BIT_WIDTH_64BIT  = 0x0,   /**< 64bitλ��*/
    HI_UNF_CIPHER_BIT_WIDTH_8BIT   = 0x1,   /**< 8bitλ��*/
    HI_UNF_CIPHER_BIT_WIDTH_1BIT   = 0x2,   /**< 1bitλ��*/
    HI_UNF_CIPHER_BIT_WIDTH_128BIT = 0x3,   /**< 128bitλ��*/
}HI_UNF_CIPHER_BIT_WIDTH_E;

//////////////////////////////////////////////

/** ���ܿ�����Ϣ�ṹ*/
typedef struct hiHI_UNF_CIPHER_CTRL_S
{
    HI_U32                     u32Key[8];    /**< ��Կ*/
    HI_U32                     u32IV[4];     /**< ��ʼ����*/
    HI_BOOL                    bKeyByCA;     /**< �Ƿ�ʹ�ø߰�ȫCA���ܻ����KEY*/
    HI_UNF_CIPHER_ALG_E        enAlg;        /**< �����㷨*/
    HI_UNF_CIPHER_BIT_WIDTH_E  enBitWidth;   /**< ���ܻ���ܵ�λ��*/
    HI_UNF_CIPHER_WORK_MODE_E  enWorkMode;   /**< ����ģʽ*/
    HI_UNF_CIPHER_KEY_LENGTH_E enKeyLen;     /**< ��Կ����*/
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
/** @{ */  /** <!-- ��SCI�� */
/** 
\brief SCI��ʼ��
\attention \n
\param ��
\retval 0 �ɹ�

\see \n
��
*/
HI_S32 HI_UNF_SCI_Init(HI_VOID);

/** 
\brief SCIȥ��ʼ��
\attention \n
\param ��
\retval 0 �ɹ�

\see \n
��
*/
HI_S32 HI_UNF_SCI_DeInit(HI_VOID);

/** 
\brief ��SCI��Smart Card Interface���豸���������Ķ˿ں�Э�飬����SCI�ӿ��豸�ĳ�ʼ������������ڣ���ͬʱ�Կ����г�ʼ��
\attention \n
�ظ��򿪻�ʧ��\n
�򿪺�SCI�豸����Ĭ�����ö��豸���г�ʼ��\n
֮��������������ã���Ҫ����HI_UNF_SCI_ResetCard��ʹ������Ч\n
֮������Կ����аβ壬��Ҫ����HI_UNF_SCI_ResetCard�����и�λ��
���豸��ʱ����Ҫ����Ƶ�ʲ�������оƬʵ�ʸ�SCI ��ʱ�������ⲿ�����
ʱ��Ƶ�ʲ�������ķ�Ƶ���ӷ�Ƶ��������Ϊ���㹫ʽ����������ķ�Ƶ���ӵ�С�����֣�
����ͨ��ϵͳʱ�ӷ�Ƶ֮�������ʱ�ӻ����������ʵ�����ÿ�����������ӽ���ֵ��
���ú�Ȩ�⣬�����㷨:Fsci_clk = Frefclk/((clkicc+1)*2);����Frefclk��ϵͳ96Mʱ�ӣFFsci_clk ���ⲿ��Ҫ���õ�
sciʱ��,ʵ��Ҫ����Ĵ�����Ƶ����clkicc = Frefclk/(2*Fsci_clk) -1;clkicc ��ʱ���������Ǹ���������ֻȡ����
�������õ�Ƶ����ʵ��Ƶ����ƫ�

\param[in] enSciPort       SCI�˿ںţ�ȡֵ��ΧΪ0��1
\param[in] enSciProtocol  Э������
\param[in] u32Frequency    Ҫ���õ�SCI��Ƶ�ʡ�����T0��T1����֧��Ƶ��1MHz��5MHz������T14����ֻ֧��6MHz����λΪkhz
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_Open(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_PROTOCOL_E enSciProtocol, HI_U32 u32Frequency);

/** 
\brief �ر�SCI�豸��
\attention \n
�ظ��رջ�ʧ�ܡ�
\param[in] enSciPort       SCI�˿ںţ�ȡֵ��ΧΪ0��1
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\see \n
��
*/
HI_S32 HI_UNF_SCI_Close(HI_UNF_SCI_PORT_E enSciPort);


/** 
\brief �ȸ�λSCI����
\attention \n
û�в��뿨����λ��ʧ��\n
��������SCI�豸�����ú���Ҫ���øýӿ�ʹ������Ч\n
�ڵ��ô�SCI�豸�ӿں󣬶Կ����аβ壬Ҳ��Ҫ���øýӿڽ��и�λ��

\param[in] enSciPort    SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[in] bWarmResetValid  ��λ��ʽ��ȡֵ��ΧΪ0��1��0:warm reset,1:cold reset���Ƽ������ַ�ʽ����
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_ResetCard(HI_UNF_SCI_PORT_E enSciPort, HI_BOOL bWarmResetValid);


/** 
\brief ȥ����SCI����
\attention \n
ȥ������޷���д���ݡ�ֻ�����¸�λ���󣬲��ܼ�����д��
\param[in] enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_DeactiveCard(HI_UNF_SCI_PORT_E enSciPort);


/** 
\brief ��ȡSCI��ATR���ݡ�
\attention \n
��
\param[in]  enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[in]  pu8AtrBuf  ATR ���ݶ�ȡ buffer ���ȡ�
\param[in] u32AtrBufSize  ʵ�ʻ�ȡ��ATR���ݸ�����
\param[in]  pu8AtrRcvCount  ��ȡ��ATR���ݵĴ洢��ַ��
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\retval ::HI_ERR_SCI_FAILED_GETATR  ��ȡATR����ʧ��
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_FAILED_SEND  ���Ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_RECEIVE  ���ղ���ʧ��
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  ����������ʱʧ��
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  ��ȡδ���ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  ����VCCEN�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  ����DETECT�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  ������ʽ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_INVALID_PORT  ����Ķ˿ں�
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  �����Э������
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  �Ƿ���ʱ��Ƶ��
\retval ::HI_ERR_SCI_INVALID_LENTH  �Ƿ�����
\retval ::HI_ERR_SCI_NO_ATR  ��ATR����
\retval ::HI_ERR_SCI_CARD_STATUS  ��״̬����
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  ���ղ�����ʱ
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  �Ƿ���ʱʱ��ֵ
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  �Ƿ��ĵ�ƽ
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  ��ȡ��״̬��ʱ
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  ����CLK�ź��߹���ģʽʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_GetATR(HI_UNF_SCI_PORT_E enSciPort, HI_U8 *pu8AtrBuf, HI_U32 u32AtrBufSize, HI_U8 *pu8AtrRcvCount);


/** 
\brief ��ȡSCI��״̬��
\attention \n
�˽ӿ����������������ڿ���״̬ΪHI_UNF_SCI_STATUS_READYʱ���ſɵ���HI_UNF_SCI_Send��HI_UNF_SCI_Receive�ӿ��뿨�������ݽ���\n

\param[in] enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[Out] penSCIStatus  SCI��״̬��
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\retval ::HI_ERR_SCI_FAILED_GETATR  ��ȡATR����ʧ��
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_FAILED_SEND  ���Ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_RECEIVE  ���ղ���ʧ��
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  ����������ʱʧ��
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  ��ȡδ���ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  ����VCCEN�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  ����DETECT�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  ������ʽ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_INVALID_PORT  ����Ķ˿ں�
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  �����Э������
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  �Ƿ���ʱ��Ƶ��
\retval ::HI_ERR_SCI_INVALID_LENTH  �Ƿ�����
\retval ::HI_ERR_SCI_NO_ATR  ��ATR����
\retval ::HI_ERR_SCI_CARD_STATUS  ��״̬����
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  ���ղ�����ʱ
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  �Ƿ���ʱʱ��ֵ
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  �Ƿ��ĵ�ƽ
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  ��ȡ��״̬��ʱ
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  ����CLK�ź��߹���ģʽʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_GetCardStatus(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_STATUS_E *penSciStatus);


/** 
\brief ��SCI���������ݡ�
\attention \n
����������Ҫ����Ӧ��Э��������\n
�����������η��Ͷ��м䲻��������\n
���Ͷ�ȡ���������ģ���˷��ʹ���������ʱ���ܵ���ʱʱ������ƣ������ʱֵ�Ƚ϶̣��п��ܷ���ʧ�ܡ�
            
\param[in] enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[in]  pSciSendBuf  �������ݵĴ洢��ַ��
\param[in] u32SendLen  �������ݵĸ���,��λΪ BYTE��
\param[in]  pu32ActLen  ʵ�ʷ������ݸ���,��λΪ BYTE��
\param[in] u32TimeoutMs  �ȴ���ʱֵ, ��λ�Ǻ���, 0 - ������, 0xFFFFFFFF-����������
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\retval ::HI_ERR_SCI_FAILED_GETATR  ��ȡATR����ʧ��
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_FAILED_SEND  ���Ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_RECEIVE  ���ղ���ʧ��
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  ����������ʱʧ��
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  ��ȡδ���ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  ����VCCEN�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  ����DETECT�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  ������ʽ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_INVALID_PORT  ����Ķ˿ں�
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  �����Э������
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  �Ƿ���ʱ��Ƶ��
\retval ::HI_ERR_SCI_INVALID_LENTH  �Ƿ�����
\retval ::HI_ERR_SCI_NO_ATR  ��ATR����
\retval ::HI_ERR_SCI_CARD_STATUS  ��״̬����
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  ���ղ�����ʱ
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  �Ƿ���ʱʱ��ֵ
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  �Ƿ��ĵ�ƽ
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  ��ȡ��״̬��ʱ
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  ����CLK�ź��߹���ģʽʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_Send(HI_UNF_SCI_PORT_E enSciPort, HI_U8 *pSciSendBuf, HI_U32 u32SendLen, HI_U32 *pu32ActLen, HI_U32 u32TimeoutMs);


/** 
\brief ��SCI���������ݡ�
\attention \n
�ϲ�Ӧ�ó���������Э������������ȡ�ĳ��ȣ����ϣ����ȡ�ĳ��ȳ���ʵ���ܹ����صĳ��ȣ���ֻ�ܵȵ���ʱ���ڲ��ܷ��ء�

\param[in] enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[in]  pSciReceiveBuf  �������ݵĴ洢��ַ��
\param[in] u32ReceiveLen  �����������ݵĸ���,,��λΪ BYTE��
\param[in]  pu32ActLen  ʵ�ʽ������ݸ���,��λΪ BYTE��
\param[in] u32TimeOutMs  �ȴ���ʱֵ, ��λ�Ǻ���, 0 - ������, 0xFFFFFFFF-����������
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\retval ::HI_ERR_SCI_FAILED_GETATR  ��ȡATR����ʧ��
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_FAILED_SEND  ���Ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_RECEIVE  ���ղ���ʧ��
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  ����������ʱʧ��
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  ��ȡδ���ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  ����VCCEN�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  ����DETECT�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  ������ʽ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_INVALID_PORT  ����Ķ˿ں�
\retval ::HI_ERR_SCI_NO_ATR  ��ATR����
\retval ::HI_ERR_SCI_CARD_STATUS  ��״̬����
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  ���ղ�����ʱ
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  ��ȡ��״̬��ʱ
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  ����CLK�ź��߹���ģʽʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_Receive(HI_UNF_SCI_PORT_E enSciPort, HI_U8 *pSciReceiveBuf, HI_U32 u32ReceiveLen, HI_U32 *pu32ActLen, HI_U32 u32TimeOutMs);


/** 
\brief ����VCCEN�ź��ߵ���Ч��ƽ��
\attention \n
��Ҫ����Ӳ����·�������ã�Ĭ��Ϊ�͵�ƽ��Ч\n
���Ĵ������ú���Ҫ����HI_UNF_SCI_ResetCard����ʹ�µ�������Ч��
        
\param[in] enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[in] enSciVcc  �ź��ߵ���Ч��ƽ��HI_FALSE���͵�ƽ��Ч��HI_TRUE���ߵ�ƽ��Ч��
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\retval ::HI_ERR_SCI_FAILED_GETATR  ��ȡATR����ʧ��
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_FAILED_SEND  ���Ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_RECEIVE  ���ղ���ʧ��
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  ����������ʱʧ��
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  ��ȡδ���ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  ����VCCEN�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  ����DETECT�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  ������ʽ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_NO_ATR  ��ATR����
\retval ::HI_ERR_SCI_CARD_STATUS  ��״̬����
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  ���ղ�����ʱ
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  �Ƿ���ʱʱ��ֵ
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  �Ƿ��ĵ�ƽ
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  ��ȡ��״̬��ʱ
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  ����CLK�ź��߹���ģʽʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_ConfigVccEn(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_LEVEL_E enSciVcc);


/** 
\brief ����DETECT�ź��ߵ���Ч��ƽ��
\attention \n
��Ҫ����Ӳ����·�������ã�Ĭ��Ϊ�ߵ�ƽ��Ч\n
���Ĵ������ú���Ҫ����HI_UNF_SCI_ResetCard����ʹ�µ�������Ч��
        
\param[in] enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[in] enSciDetect �ź��ߵ���Ч��ƽ��HI_FALSE���͵�ƽ��Ч��HI_TRUE���ߵ�ƽ��Ч��
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\retval ::HI_ERR_SCI_FAILED_GETATR  ��ȡATR����ʧ��
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_FAILED_SEND  ���Ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_RECEIVE  ���ղ���ʧ��
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  ����������ʱʧ��
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  ��ȡδ���ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  ����VCCEN�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  ����DETECT�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  ������ʽ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_INVALID_PORT  ����Ķ˿ں�
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  �����Э������
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  �Ƿ���ʱ��Ƶ��
\retval ::HI_ERR_SCI_INVALID_LENTH  �Ƿ�����
\retval ::HI_ERR_SCI_NO_ATR  ��ATR����
\retval ::HI_ERR_SCI_CARD_STATUS  ��״̬����
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  ���ղ�����ʱ
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  �Ƿ���ʱʱ��ֵ
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  �Ƿ��ĵ�ƽ
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  ��ȡ��״̬��ʱ
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  ����CLK�ź��߹���ģʽʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_ConfigDetect(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_LEVEL_E enSciDetect);


/** 
\brief ����ʱ���ߵ�ģʽ��
\attention \n
��Ҫ����Ӳ����·�������ã�Ĭ��ΪODģʽ\n
���Ĵ������ú���Ҫ����HI_UNF_SCI_ResetCard����ʹ�µ�������Ч��

\param[in] enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[in] enClkMode  ʱ���ߵ�ģʽ��
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\retval ::HI_ERR_SCI_FAILED_GETATR  ��ȡATR����ʧ��
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_FAILED_SEND  ���Ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_RECEIVE  ���ղ���ʧ��
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  ����������ʱʧ��
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  ��ȡδ���ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  ����VCCEN�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  ����DETECT�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  ������ʽ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_INVALID_PORT  ����Ķ˿ں�
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  �����Э������
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  �Ƿ���ʱ��Ƶ��
\retval ::HI_ERR_SCI_INVALID_LENTH  �Ƿ�����
\retval ::HI_ERR_SCI_NO_ATR  ��ATR����
\retval ::HI_ERR_SCI_CARD_STATUS  ��״̬����
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  ���ղ�����ʱ
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  �Ƿ���ʱʱ��ֵ
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  �Ƿ��ĵ�ƽ
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  ��ȡ��״̬��ʱ
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  ����CLK�ź��߹���ģʽʧ��
\see \n
��
*/
HI_S32 HI_UNF_SCI_ConfigClkMode(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_CLK_MODE_E enClkMode);


/** 
\brief �л����ۡ�
\attention \n
����HI_UNF_SCI_Openʱ��Ĭ�ϴ򿪵�Ϊ���������˿�0\n
�л����µ�SCI�豸����������SCI�ӿڼ����µ�SCI�豸���в���\n
�л����µ�SCI�豸����Ĭ�����ö��豸���г�ʼ��\n
֮��������������ã���Ҫ����HI_UNF_SCI_ResetCard��ʹ������Ч\n
ϣ���л�����SCI�˿��뵱ǰ��Ч�˿���ͬʱ���᷵��ʧ�ܡ�

\param[in] enSciPort  SCI�˿ںţ�ȡֵ��ΧΪ0��1��
\param[in] enSciProtocol  Э�����͡�
\param[in] u32Frequency  Ҫ���õ�SCI��Ƶ�ʡ�����T0��T1����֧��Ƶ��1MHz~5MHz������T14����ֻ֧��6MHz����λΪkHz��
\retval 0 �ɹ�
\retval ::HI_ERR_SCI_NOT_INIT  SCI�豸δ��
\retval ::HI_ERR_SCI_REPEAT_INIT  SCI�豸�ظ���
\retval ::HI_ERR_SCI_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_SCI_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_SCI_FAILED_INIT  ��SCI�豸ʧ��
\retval ::HI_ERR_SCI_FAILED_RESET  �ȸ�λʧ��
\retval ::HI_ERR_SCI_FAILED_DEACTIVE  ȥ����ʧ��
\retval ::HI_ERR_SCI_FAILED_GETATR  ��ȡATR����ʧ��
\retval ::HI_ERR_SCI_FAILED_CARDSTATUS  ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_FAILED_SEND  ���Ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_RECEIVE  ���ղ���ʧ��
\retval ::HI_ERR_SCI_FAILED_TIMEOUT_VAL  ����������ʱʧ��
\retval ::HI_ERR_SCI_FAILED_GET_DATA_LEN  ��ȡδ���ͳ���ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGVCCEN  ����VCCEN�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_CONFIGDETECT  ����DETECT�ź�ʧ��
\retval ::HI_ERR_SCI_FAILED_BLK_CARDSTATUS  ������ʽ��ȡ��״̬ʧ��
\retval ::HI_ERR_SCI_INVALID_PORT  ����Ķ˿ں�
\retval ::HI_ERR_SCI_INVALID_PROTOCOL  �����Э������
\retval ::HI_ERR_SCI_INVALID_FREQUENCY  �Ƿ���ʱ��Ƶ��
\retval ::HI_ERR_SCI_INVALID_LENTH  �Ƿ�����
\retval ::HI_ERR_SCI_NO_ATR  ��ATR����
\retval ::HI_ERR_SCI_CARD_STATUS  ��״̬����
\retval ::HI_ERR_SCI_RECEIVE_TIMEOUT  ���ղ�����ʱ
\retval ::HI_ERR_SCI_INVALID_TIMEOUT_VAL  �Ƿ���ʱʱ��ֵ
\retval ::HI_ERR_SCI_INVALID_LEVEL_VAL  �Ƿ��ĵ�ƽ
\retval ::HI_ERR_SCI_FAILED_BLK_TIMEOUT  ��ȡ��״̬��ʱ
\retval ::HI_ERR_SCI_FAILED_CONFIGSCIMODE  ����CLK�ź��߹���ģʽʧ��

\see \n
��
*/
HI_S32 HI_UNF_SCI_SwitchCard(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_PROTOCOL_E enSciProtocol, HI_U32 u32Frequency);


/** 
\brief �����⿨��Ҫ����ָ��etu ʱ�������ӣ������ʵ�������
\attention \n
ֻ������Ҫ��Ŀ���Ҫ���ã���ͨ������Ҫ���ô˽ӿ����ã�
���õ�ֵҪ��Э���й涨��Fʱ��ת��ת�����ӡ�D�����ʵ������Ӽ��ݣ�
��������Ϊ���淶�й涨��ֵ��������������

\param [in] 	enSciPort	SCI�˿ںţ�ȡֵ��ΧΪ0��1 
\param [in] 	u32ClkFactor	ʱ��ת������372��2048 ���������òο�Э���F���ӺͿ�����
\param [in] 	u32BaudFactor	������У������1��2*n (n=1��16) ���������òο�Э��D���ӺͿ�����    
\retval ::  0 	�ɹ� 
\retval ::  HI_ERR_SCI_NOT_INIT   SCI�豸δ�� 
\retval ::  HI_ERR_SCI_INVALID_PARA �Ƿ����� 

\see \n
��
*/
HI_S32 HI_UNF_SCI_SetEtuFactor(HI_UNF_SCI_PORT_E enSciPort,HI_U32 u32ClkFactor,HI_U32 u32BaudFactor);


/** 
\brief �����ն���IC�����������������ֽ���ʼ�ض������ӵļ��ʱ��
\attention \n
ֻ������Ҫ��Ŀ�����Ҫ���������ַ�����ʱ��Ĳ��ܸ��ݿ�������������ã�
�����������á�һ��ʹ��ϵͳĬ��ֵ������ϵͳ����ATR�����Զ����á�

\param [in] 	enSciPort	SCI�˿ںţ�ȡֵ��ΧΪ0��1 
\param [in] 	u32GuardTime	�����������ķ�Χ0��254  etu
\retval ::  0 	�ɹ� 
\retval ::  HI_ERR_SCI_NOT_INIT   SCI�豸δ�� 
\retval ::  HI_ERR_SCI_INVALID_PARA �Ƿ����� 

\see \n
��
*/
HI_S32 HI_UNF_SCI_SetGuardTime(HI_UNF_SCI_PORT_E enSciPort,HI_U32 u32GuardTime);


/** 
\brief ͨ��PPS Э�̿������ÿ���֧�ֵĲ����ʻ�����ATR ���ص�F��D���ӽ���Э�̣�֧�ֶ�Э�鿨��Э���л�
\attention \n
Ҫ����PPS Э�����ȿ�����֧�ָù��ܣ�
ҪЭ�̵Ĳ��������ݱ����ǿ����涨��֧�ֵĲ����ʷ�Χ��
����Э�̵������������7816-3 ��9.2 PPS request and response ��

\param [in] 	enSciPort	SCI�˿ںţ�ȡֵ��ΧΪ0��1 
\param [in] 	pSciSendBuf ���ݿ��淶��ϵ�PPSЭ�������ʹ��ϵͳĬ�ϵ�Э�̷�ʽ�������ֵ����ݿ�Ϊ��
\param [in]	Sendlen	     ���������ֵĳ���(0��5),����Ϊ0��ʾʹ��ϵͳĬ�ϵ�Э�����ʽ��
\param [in]	RecTimeouts ����������֮�󣬽���PPS ��Ӧ�ĳ�ʱʱ��(1-10000),��λ�Ǻ���
\retval ::  0 	�ɹ� 
\retval ::  HI_ERR_SCI_NOT_INIT   SCI�豸δ�� 
\retval ::  HI_ERR_SCI_INVALID_PARA �Ƿ�����
\retval ::  HI_ERR_SCI_NULL_PTR		��ָ��
\retval ::  HI_ERR_SCI_INVALID_OPT	�����õ�ѡ��
\retval ::  HI_ERR_SCI_RECEIVE_ERR  ���մ���
\retval ::	 HI_ERR_SCI_PPS_PTYPE_ERR 	PPSЭ�̵�Э�����ʹ���
\retval ::	 HI_ERR_SCI_PPS_FACTOR_ERR 	PPSЭ�̵�F��D���Ӵ���
\retval ::  HI_ERR_SCI_PPS_NOTSUPPORT_ERR ��֧�ֵ�PPSЭ������

\see \n
��
*/
HI_S32 HI_UNF_SCI_NegotiatePPS(HI_UNF_SCI_PORT_E enSciPort, HI_U8 *pSciSendBuf,HI_U32 Sendlen, HI_U32 RecTimeouts);


/** 
\brief  PPS Э�̳ɹ�֮��,ͨ���ýӿڿɻ�ÿ���Ӧ��PPS ����
\attention \n
Ҫ��PPS Э�̳ɹ�֮��,ʹ�øýӿڲ���ʵ������

\param [in] 	enSciPort	SCI�˿ںţ�ȡֵ��ΧΪ0��1 
\param [out] 	pRecBuf   �����յ�����buffer ��ַ
\param [out]	pDataLen	   �����������ݵĳ��� 
\retval ::  0 	�ɹ� 
\retval ::  HI_ERR_SCI_INVALID_PARA �Ƿ�����
\retval ::  HI_ERR_SCI_NULL_PTR		��ָ��
\retval ::  HI_ERR_SCI_PPS_NOTSUPPORT_ERR ��֧�ֵ�PPSЭ������

\see \n
��
*/
HI_S32 HI_UNF_SCI_GetPPSResponData(HI_UNF_SCI_PORT_E enSciPort, HI_U8* pRecBuf, HI_U32* pDataLen);


/** 
\brief  ��ȡsci ��������Э�顢ATR ʱ�Ӻͱ��������ӡ�ʵ�����õ�ʱ�����Ӻͱ��������ӣ�
�������Դ�����GuardDelay ���ַ��ȴ���ʱ����ȴ���ʱ��
\attention \n
Ҫ�� ����ʼ����λ֮��,����ʹ�øýӿ�

\param [in] 	enSciPort	SCI�˿ںţ�ȡֵ��ΧΪ0��1 
\param [out] 	pParams   �����յĽṹ����������ָ��
\retval ::  0 	�ɹ� 
\retval ::  HI_ERR_SCI_INVALID_PARA �Ƿ�����
\retval ::  HI_ERR_SCI_NULL_PTR		��ָ��
\retval ::  HI_ERR_SCI_INVALID_OPT	�����õ�ѡ��
\retval ::  HI_ERR_SCI_NOT_INIT  	û��ɳ�ʼ��

\see \n
��
*/
HI_S32 HI_UNF_SCI_GetParams(HI_UNF_SCI_PORT_E enSciPort, HI_UNF_SCI_PARAMS_S_PTR pParams);


/** 
\brief  ���ݵ�ǰЭ�����ͷֱ������T0��T1���ַ���ʱʱ��
\attention \n
Ҫ�ȿ���λ�ɹ�֮��,���ܽ������ã�Э�����Ͳ��������뵱ǰ������һ�£�һ��������Ǹ���ATR������ֻ�����⿨�������Ҫ���á�

\param [in] 	enSciPort	SCI�˿ںţ�ȡֵ��ΧΪ0��1 
\param [in] 	enSciProtocol   Э������
\param [in]	MaxCharTime 	���������ַ���ʱʱ�䣬���÷�ΧT0(960��244800),T1(12��32779)
\retval ::  0 	�ɹ� 
\retval ::  HI_ERR_SCI_INVALID_PARA �Ƿ�����
\retval ::  HI_ERR_SCI_INVALID_OPT	�����õ�ѡ��
\retval ::  HI_ERR_SCI_NO_ATR  		û��λ�ɹ�

\see \n
��
*/
HI_S32 HI_UNF_SCI_SetCharTimeout(HI_UNF_SCI_PORT_E enSciPort,  HI_UNF_SCI_PROTOCOL_E  enSciProtocol, HI_U32 MaxCharTime);


/** 
\brief  ����T1�Ŀ鳬ʱʱ��
\attention \n
Ҫ�ȿ���λ�ɹ�֮��,���ܽ������ã�һ��������Ǹ���ATR������ֻ�����⿨�������Ҫ���á�

\param [in] 	enSciPort	SCI�˿ںţ�ȡֵ��ΧΪ0��1 
\param [in] 	MaxBlockTime   ���ÿ鳬ʱ�����ֵ����Χ(971��491531)
\retval ::  0 	�ɹ� 
\retval ::  HI_ERR_SCI_INVALID_PARA �Ƿ�����
\retval ::  HI_ERR_SCI_INVALID_OPT	�����õ�ѡ��
\retval ::  HI_ERR_SCI_NO_ATR  		û��λ�ɹ�

\see \n
��
*/
HI_S32 HI_UNF_SCI_SetBlockTimeout(HI_UNF_SCI_PORT_E enSciPort,HI_U32 MaxBlockTime);


/** 
\brief  ����У�������ط���������
\attention \n
Ҫ�ȿ���λ�ɹ�֮��,���ܽ�������

\param [in] 	enSciPort	SCI�˿ںţ�ȡֵ��ΧΪ0��1 
\param [in] 	TxRetryTimes   ������Χ(0��7)
\retval ::  0 	�ɹ� 
\retval ::  HI_ERR_SCI_INVALID_PARA �Ƿ�����
\retval ::  HI_ERR_SCI_INVALID_OPT	�����õ�ѡ��
\retval ::  HI_ERR_SCI_NO_ATR  		û��λ�ɹ�

\see \n
��
*/
HI_S32 HI_UNF_SCI_SetTxRetries(HI_UNF_SCI_PORT_E enSciPort,HI_U32 TxRetryTimes);


/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_2 */
/** @{ */  /** <!-- ��E2PROM�� */
/*---- e2prom ----*/
/** 
\brief ��E2PROM��Electrically-Erasable Programmable Read-Only Memory���豸��
\attention \n
�ظ��򿪻�ʧ�ܡ�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM�豸δ��ʼ��
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM�豸�ظ���ʼ��
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM��Чָ��
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM��Ч����
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM�豸��ʼ��ʧ��
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM���ݶ�ȡʧ��
\see \n
��
*/
HI_S32 HI_UNF_E2PROM_Open(HI_VOID);


/** 
\brief �ر�E2PROM�豸��
\attention \n
�ظ��رջ�ʧ�ܡ�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM�豸δ��ʼ��
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM�豸�ظ���ʼ��
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM��Чָ��
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM��Ч����
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM�豸��ʼ��ʧ��
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM���ݶ�ȡʧ��
\see \n
��
*/
HI_S32 HI_UNF_E2PROM_Close(HI_VOID);


/** 
\brief ��E2PROM�豸�����ݡ�
\attention \n
���ô˽ӿ�ǰӦȷ��I2Cģ�����\n
������ĵ�ַu32Addr����оƬ��ַ�ܳ��ȣ��򲻻��E2PROM���ж�����\n
�������ָ��pu8BufΪ�գ��򲻻��E2PROM���ж�����\n
�������ַu32Addr�Ϸ�����u32Addr��u32Length�ĺʹ���оƬ��ַ�ܳ��ȣ��򲻻��E2PROM���ж�������
\param[in] u32Addr  Ƭ��ƫ�Ƶ�ַ��
\param[out]  pu8Buf  ��Ŵ���ȡ�����ݡ�
\param[in] u32Length  ��ȡ���ݵĳ��ȡ�
\retval 0 �ɹ�
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM�豸δ��ʼ��
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM�豸�ظ���ʼ��
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM��Чָ��
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM��Ч����
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM�豸��ʼ��ʧ��
\see \n
��
*/
HI_S32 HI_UNF_E2PROM_Read (HI_U32 u32Addr, HI_U8 * pu8Buf, HI_U32 u32Length);


/** 
\brief ��E2PROM�豸д���ݡ�
\attention \n
���ô˽ӿ�ǰӦȷ��I2Cģ�����\n
������ĵ�ַu32Addr����оƬ��ַ�ܳ��ȣ��򲻻��E2PROM����д����\n
�������ָ��pu8BufΪ�գ��򲻻��E2PROM����д����\n
�������ַu32Addr�Ϸ�����u32Addr��u32Length�ĺʹ���оƬ��ַ�ܳ��ȣ��򲻻��E2PROM����д������
\param[in] u32Addr  Ƭ��ƫ�Ƶ�ַ��
\param[in]  pu8Buf  ��Ŵ�д������ݡ�
\param[in] u32Length  Ҫд������ݳ��ȡ�
\retval 0 �ɹ�
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM�豸δ��ʼ��
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM�豸�ظ���ʼ��
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM��Чָ��
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM��Ч����
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM�豸��ʼ��ʧ��
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM���ݶ�ȡʧ��
\see \n
��
*/
HI_S32 HI_UNF_E2PROM_Write (HI_U32 u32Addr, HI_U8 * pu8Buf, HI_U32 u32Length);


/** 
\brief ����E2PROMоƬ���͡�
\attention \n
���ô˽ӿ�ǰӦȷ��I2Cģ�����\n
�˽ӿڱ����ڵ���HI_UNF_E2PROM_Read��HI_UNF_E2PROM_Write֮ǰ����\n
Ŀǰ��ʵ����M24LC16оƬ���������͵�оƬδ���в��ԡ�
\param[in] enChip  E2PROMоƬ���͡�
                   HI_UNF_E2PROM_CHIP_AT24C01��оƬ����ΪAT24C01��
                   HI_UNF_E2PROM_CHIP_AT24C02��оƬ����ΪAT24C02��
                   HI_UNF_E2PROM_CHIP_AT24C04��оƬ����ΪAT24C04��
                   HI_UNF_E2PROM_CHIP_AT24C08��оƬ����ΪAT24C08��
                   HI_UNF_E2PROM_CHIP_AT24C16��оƬ����ΪAT24C16��
                   HI_UNF_E2PROM_CHIP_AT24C32��оƬ����ΪAT24C32��
                   HI_UNF_E2PROM_CHIP_AT24C64��оƬ����ΪAT24C64��
                   HI_UNF_E2PROM_CHIP_AT24C128��оƬ����ΪAT24C128��
                   HI_UNF_E2PROM_CHIP_AT24C256��оƬ����ΪAT24C256��
                   HI_UNF_E2PROM_CHIP_M24LC01��оƬ����ΪM24LC01��
                   HI_UNF_E2PROM_CHIP_M24LC02��оƬ����ΪM24LC02��
                   HI_UNF_E2PROM_CHIP_M24LC04��оƬ����ΪM24LC04��
                   HI_UNF_E2PROM_CHIP_M24LC08��оƬ����ΪM24LC08��
                   HI_UNF_E2PROM_CHIP_M24LC16��оƬ����ΪM24LC16��
                   HI_UNF_E2PROM_CHIP_M24LC32��оƬ����ΪM24LC32��
                   HI_UNF_E2PROM_CHIP_M24LC64��оƬ����ΪM24LC64��
                   HI_UNF_E2PROM_CHIP_M24LC128��оƬ����ΪM24LC128��
                   HI_UNF_E2PROM_CHIP_M24LC256��оƬ����ΪM24LC256��
\retval 0 �ɹ�
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM�豸δ��ʼ��
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM�豸�ظ���ʼ��
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM��Чָ��
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM��Ч����
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM�豸��ʼ��ʧ��
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM���ݶ�ȡʧ��
\retval ::HI_ERR_E2PROM_FAILED_WRITE  E2PROM����д��ʧ��
\retval ::HI_ERR_E2PROM_FAILED_SETCHIPTYPE  E2PROMѡ��оƬʧ��
\see \n
��
*/
HI_S32 HI_UNF_E2PROM_SetChipType(HI_UNF_E2PROM_CHIP_E enChip);


/** 
\brief ����E2PROM��I2C���ߵ�ַ��
\attention \n
��ַ��Ӳ�������йأ���ο�Ӳ����ơ�
\param[in] u32E2promAddr  E2PROM��I2C���ߵ�ַ��
\retval 0 �ɹ�
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM�豸δ��ʼ��
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM�豸�ظ���ʼ��
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM��Чָ��
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM��Ч����
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM�豸��ʼ��ʧ��
\retval ::HI_ERR_E2PROM_FAILED_READ  E2PROM���ݶ�ȡʧ��
\retval ::HI_ERR_E2PROM_FAILED_WRITE  E2PROM����д��ʧ��
\retval ::HI_ERR_E2PROM_FAILED_SETADDR  E2PROM���õ�ַʧ��
\see \n
��
*/
HI_S32 HI_UNF_E2PROM_SetAddr(HI_U32 u32E2promAddr);


/** 
\brief ����E2PROM��ʹ�õ�I2Cͨ���š�
\attention \n
��
\param[in] u32I2cNum  E2PROM���õ�I2Cͨ���ţ���Χ0��HI_I2C_MAX_NUM_USER
\retval 0 �ɹ�
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM�豸δ��ʼ��
\retval ::HI_ERR_E2PROM_REPEAT_INIT  E2PROM�豸�ظ���ʼ��
\retval ::HI_ERR_E2PROM_INVALID_POINT  E2PROM��Чָ��
\retval ::HI_ERR_E2PROM_INVALID_PARA  E2PROM��Ч����
\retval ::HI_ERR_E2PROM_FAILED_INIT  E2PROM�豸��ʼ��ʧ��
\retval ::HI_ERR_E2PROM_FAILED_SETI2CNUM  E2PROM����I2Cͨ��ʧ��
\retval ::HI_ERR_E2PROM_NOT_INIT  E2PROM�豸δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_E2PROM_SetI2cNum(HI_U32 u32I2cNum);

/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_3 */
/** @{ */  /** <!-- ��I2C�� */
/*---- i2c ----*/
/** 
\brief ��I2C��the Inter-Integrated Circuit���豸��
\attention \n
�ظ����ô˽ӿڻ�ʧ�ܡ�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_I2C_NOT_INIT  I2C�豸δ��ʼ��
\retval ::HI_ERR_I2C_REPEAT_INIT  I2C�豸�ظ���ʼ��
\retval ::HI_ERR_I2C_INVALID_POINT  I2C��Чָ��
\retval ::HI_ERR_I2C_INVALID_PARA  I2C��Ч����
\see \n
��
*/
HI_S32 HI_UNF_I2C_Open (HI_VOID);


/** 
\brief �ر�I2C�豸��
\attention \n
��I2C������������ô˽ӿ�\n
�ظ����ô˽ӿڻ�ʧ�ܡ�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_I2C_NOT_INIT  I2C�豸δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_I2C_Close(HI_VOID);

/** 
\brief ����һ·GpioI2c
\attention \n
���Gpio�ѱ�ռ�û�ʧ��\n
\param[in] u32I2cNum  �õ�I2C���ߺš�
\param[in] whichGpioClock  Clock�ܽ���ţ�ȡֵ��ΧΪ0��12
\param[in] whichGpioData   Data�ܽ���ţ� ȡֵ��ΧΪ0��12
\param[in] clockBit  Clock�ܽ�λ�ţ�ȡֵ��ΧΪ0��7
\param[in] dataBit   Data�ܽ�λ�ţ� ȡֵ��ΧΪ0��7
\retval 0 �ɹ�
\retval ::HI_ERR_GPIO_INVALID_PARA  �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_I2C_CreateGpioI2c(HI_U32 *u32I2cNum, HI_U32 whichGpioClock, HI_U32 whichGpioData, HI_U32 clockBit, HI_U32 dataBit);

/** 
\brief ����һ·GpioI2c
\attention \n
�����GpioI2cδʹ�ã�ֱ�ӷ��سɹ�\n
\param[in] u32I2cNum Ҫ���ٵ�I2C���ߺš�
\retval 0 �ɹ�
\retval ::HI_ERR_GPIO_INVALID_PARA  �����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_I2C_DestroyGpioI2c(HI_U32 u32I2cNum);
/** 
\brief ͨ��I2C�����ݡ�
\attention \n
��
\param[in] u32I2cNum  ����ȡ�豸ʹ�õ�I2C���ߡ�
\param[in] u8DevAddress  �豸��I2C�����ϵĵ�ַ��
\param[in] u32RegAddr  �豸��Ƭ��ƫ�Ƶ�ַ��
\param[in] u32RegAddrCount  Ƭ��ƫ�Ƶ�ַ�ĳ��ȵ�λ��
                            1����ʾ8bit�ӵ�ַ��
                            2����ʾ16bit�ӵ�ַ��
                            3����ʾ24bit�ӵ�ַ��
                            4����ʾ32bit�ӵ�ַ��

\param[out] pu8Buf  ��Buffer����Ŷ�ȡ���ݡ�
\param[in] u32Length  Ҫ��ȡ�����ݳ��ȡ�
\retval 0 �ɹ�
\retval ::HI_ERR_I2C_NOT_INIT  I2C�豸δ��ʼ��
\retval ::HI_ERR_I2C_INVALID_POINT  I2C��Чָ��
\retval ::HI_ERR_I2C_INVALID_PARA  I2C��Ч����
\retval ::HI_ERR_I2C_FAILED_INIT  I2C�豸��ʼ��ʧ��
\retval ::HI_ERR_I2C_FAILED_READ  I2C������ʧ��
\retval ::HI_ERR_I2C_FAILED_SETRATE  I2C��������ʧ��
\see \n
��
*/
HI_S32 HI_UNF_I2C_Read(HI_U32 u32I2cNum, HI_U8 u8DevAddress, HI_U32 u32RegAddr,
                       HI_U32 u32RegAddrCount, HI_U8 *pu8Buf, HI_U32 u32Length);
                       

/** 
\brief ͨ��I2Cд���ݡ�ͨ��I2Cͨ������I2C�����Ϲҽӵ��豸����д������
\attention \n
��
\param[in] u32I2cNum  ��д�豸ʹ�õ�I2C���ߡ�
\param[in] u8DevAddress  �豸��I2C�����ϵĵ�ַ��
\param[in] u32RegAddr  �豸��Ƭ��ƫ�Ƶ�ַ��
\param[in] u32RegAddrCount  Ƭ��ƫ�Ƶ�ַ�ĳ��ȵ�λ��
                            1����ʾ8bit�ӵ�ַ��
                            2����ʾ16bit�ӵ�ַ��
                            3����ʾ24bit�ӵ�ַ��
                            4����ʾ32bit�ӵ�ַ��
\param[in]  pu8Buf  дBuffer����Ŵ�д�����ݡ�
\param[in] u32Length  Ҫд������ݵĳ��ȡ�
\retval 0 �ɹ�
\retval ::HI_ERR_I2C_NOT_INIT  I2C�豸δ��ʼ��
\retval ::HI_ERR_I2C_REPEAT_INIT  I2C�豸�ظ���ʼ��
\retval ::HI_ERR_I2C_INVALID_POINT  I2C��Чָ��
\retval ::HI_ERR_I2C_INVALID_PARA  I2C��Ч����
\retval ::HI_ERR_I2C_FAILED_INIT  I2C�豸��ʼ��ʧ��
\retval ::HI_ERR_I2C_FAILED_WRITE  I2Cд����ʧ��
\retval ::HI_ERR_I2C_FAILED_SETRATE  I2C��������ʧ��
\see \n
��
*/                      
HI_S32 HI_UNF_I2C_Write(HI_U32 u32I2cNum, HI_U8 u8DevAddress, HI_U32 u32RegAddr,
                       HI_U32  u32RegAddrCount, HI_U8 * pu8Buf, HI_U32 u32Length);


/** 
\brief ����I2C�Ĵ������ʡ�
\attention \n
��������ô˽ӿڣ�ϵͳ����100Kbit/s��Ϊȱʡ���ʡ�
\param[in] u32I2cNum  ��д�豸��I2C�����ϵ�ͨ���š�
\param[in] enI2cRate  I2Cʱ�����ʡ�������ο�::HI_UNF_I2C_RATE_E
\retval 0 �ɹ�
\retval ::HI_ERR_I2C_NOT_INIT  I2C�豸δ��ʼ��
\retval ::HI_ERR_I2C_REPEAT_INIT  I2C�豸�ظ���ʼ��
\retval ::HI_ERR_I2C_INVALID_POINT  I2C��Чָ��
\retval ::HI_ERR_I2C_INVALID_PARA  I2C��Ч����
\retval ::HI_ERR_I2C_FAILED_INIT  I2C�豸��ʼ��ʧ��
\retval ::HI_ERR_I2C_FAILED_READ  I2C������ʧ��
\retval ::HI_ERR_I2C_FAILED_WRITE  I2Cд����ʧ��
\retval ::HI_ERR_I2C_FAILED_SETRATE  I2C��������ʧ��
\see \n
��
*/
HI_S32 HI_UNF_I2C_SetRate(HI_U32 u32I2cNum, HI_UNF_I2C_RATE_E enI2cRate);

/** @} */  /** <!-- ==== API declaration end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_4 */
/** @{ */  /** <!-- ��KEYLED�� */
/**---- keyled ----*/
/**
\brief ��ʼ��KEYLEDģ�顣
\attention \n
�ظ����ñ��ӿڣ��᷵�سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_KEYLED_Init(HI_VOID);


/**
\brief ȥ��ʼ��KEYLEDģ�顣
\attention \n
�ظ����ñ��ӿڣ��᷵�سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_KEYLED_DeInit(HI_VOID);

/**
\brief ѡ��KEYLED�������͡�
\attention \n
 �����ʼ����ֻѡ��һ�Σ���Ҫ�ظ����ã�Ĭ��Ϊ��׼KEYLEDģʽ��
\param[in] enKeyLedType  keyled���͡� 
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_KEYLED_SelectType(HI_UNF_KEYLED_TYPE_E enKeyLedType);

/**
\brief �򿪰������ܡ�
\attention \n
�򿪺�ʼ���հ���\n
�ظ����ñ��ӿڣ��᷵�سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_KEY_Open(HI_VOID);

/**
\brief �رհ������ܡ�
\attention \n
�رպ�ֹͣ���հ���\n
���ӿڵ�һ�ε���������,�ظ����÷��سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_KEY_Close(HI_VOID);

/**
\brief ��յ�ǰû�н��յİ�����
\attention \n
��հ���buffer���ص���ʱ״̬��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_KEY_Reset(HI_VOID);


/**
\brief ��ȡһ������ֵ��
\attention \n
��ȡbuffer�����絽��İ���ֵ�����ذ���ֵ����ֵ��״̬\n
״̬�������º͵���\n
�ӿ����::HI_UNF_KEY_SetBlockTime�ӿ�һ��ʹ��\n
û�а���ʱ�����еȴ�����ʱ���˳������س�ʱ������\n
��ʱֵΪ0ʱΪ�������ӿڣ�û�а���ֱ�ӷ���û�а���������\n
��ʱֵ����Ϊ0xffffffff��һֱ�ȴ���
\param[out] pu32PressStatus   ����״̬�ǰ��»��ǵ���
\param[out] pu32KeyId   ����ֵ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_KEYLED_NULL_PTR  ָ�����Ϊ��
\retval ::HI_ERR_KEYLED_NO_NEW_KEY  û�а���
\retval ::HI_ERR_KEYLED_TIMEOUT  �ȴ�������ʱ
\see \n
��
*/
HI_S32 HI_UNF_KEY_GetValue(HI_U32 * pu32PressStatus, HI_U32 * pu32KeyId);

/**
\brief ���ð�����ȡ�ĳ�ʱʱ�䡣
\attention \n
��ʱֵΪ0ʱ��������û�а���ֱ�ӷ���û�а���������\n
��ʱֵ����Ϊ0xffffffff��һֱ�ȴ���
\param[in] u32BlockTimeMs ��ʱʱ�䣬��λms��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\see \n
��
*/
HI_S32 HI_UNF_KEY_SetBlockTime(HI_U32 u32BlockTimeMs);


/**
\brief �����ظ�������ʱ�䡣
\attention \n
��ĳ�������ڰ���״̬���������õ�ʱ��ֵ�ж�Ϊ�ظ�����\n
�ظ����������÷�Χ��108ms��65536ms֮�䣬���������Χ���Զ�Լ�������޻�������\n
Ĭ�ϵ��ظ������ж�ʱ��Ϊ200ms��
\param[in] u32RepTimeMs �ж�Ϊ�ظ�������ʱ�䣬��λms��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\see \n
��
*/
HI_S32 HI_UNF_KEY_RepKeyTimeoutVal(HI_U32 u32RepTimeMs);

/**
\brief �����Ƿ�ʹ���ظ�������
\attention \n
ֻ��ʹ�ܺ�һֱ��סĳ���������������ϱ���ֵ��
\param[in] u32IsRepKey �Ƿ�ʹ���ظ�������1 ʹ�ܣ�0 ��ʹ�ܡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\see \n
��
*/
HI_S32 HI_UNF_KEY_IsRepKey(HI_U32 u32IsRepKey);

/**
\brief �����Ƿ��ϱ���������
\attention \n
ʹ�ܺ�Ż��ϱ����������¼�����Ȼֻ�ϱ������¼���
\param[in] u32IsKeyUp �Ƿ�ʹ���ظ�������1 ʹ�ܣ�0 ��ʹ�ܡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\see \n
��
*/
HI_S32 HI_UNF_KEY_IsKeyUp(HI_U32 u32IsKeyUp);

/**
\brief ���������ʾ���ܡ�
\attention \n
�򿪺�Ż�������ܵ���ʾ\n
�ظ����ñ��ӿڣ��᷵�سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_LED_Open(HI_VOID);

/**
\brief �ر��������ʾ���ܡ�
\attention \n
�رպ�ֹͣ�������ʾ\n
���ӿڵ�һ�ε���������,�ظ����÷��سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_LED_Close(HI_VOID);


/**
\brief ���ݴ��������ֵ������ʾ��
\attention \n
ÿ�������Ҫ��ʾ���ַ���Ӧһ���ֽڵ���ʾֵ��\n
��ʾʱ��Ҫ��4 ������ʾ�ַ���Ӧ����ʾֵ��ϳ�һ��unsiged int��32bit��������Ϊ�˽ӿڵĲ���ֵ��\n
�����ҵ�4 ��LED ������ʾ���ݵ�bit[7:0]��bit[15:8]��bit[23:16]��bit[31:24]��\n
���磺��LED ����ʾ��1234��������Ҫ����Щ�ַ���Ӧ����ʾֵ��ϳ�һ��Unsigned int �ı�����\n
  Unsigned int parameter = 0x03 + (0x9F <<8) + (0x25<<16) + (0x0D <<24)��\n
���У�0x03��0x9F��0x25��0x0D �ֱ��ǡ�1������2������3������4������ʾֵ��\n
�߶�����ܶ��������ݵ�bit��Ӧ��ϵ����:\n
       --7--       \n
      |     |      \n
     2|     |6     \n
      |--1--       \n
      |     |      \n
     3|     |5     \n
       --4-- .0    \n
��˼DEMO������ܳ�����ʾ�ַ������Ӧ����ʾֵ����(��Թ�������������Ҫȡ��)��\n
  . �ַ�0-9��0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09\n
  . ��д��ĸA-Z��������ʾ����0xFF ��ʾ����\n
     0xFF, 0xFF, 0x63, 0xFF, 0x61, 0x71, 0xFF, 0x91, 0xFF, 0xFF, 0xFF, 0xE3, 0xFF,\n
     0xFF, 0x03, 0x31, 0xFF, 0xFF, 0x49, 0xFF, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF\n
  . Сд��ĸa-z��������ʾ����0xFF ��ʾ����\n
    0xFF, 0xC1, 0xE5, 0x85, 0x21, 0xFF, 0x09, 0xD1, 0xDF, 0xFF, 0xFF, 0x9F, 0xFF,\n
    0xD5, 0xC5, 0x31, 0x19, 0xFF, 0x49, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
\param[in] u32CodeValue  ��Ҫ��ʾ��4λ��ֵ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\see \n
��
*/
HI_S32 HI_UNF_LED_Display(HI_U32 u32CodeValue);


/**
\brief �����������ʾʱ�䡣
\attention \n
Сʱ������ֻ�����ó���Ӧ��ʮ����ֵ�����ˡ�������ʾ22��45����hour=22��minute=45��\n
��Ҫ�ȵ���HI_UNF_LED_SetFlashPin ������ʾ�ܽ�ΪHI_UNF_KEYLED_LIGHT_ALL\n
����ʱ�����ݽṹ��Ȼ�������������ʾ����ʾʱ���ͬʱð�Ż���1HZ��Ƶ����˸\n
ʱ��ķ�Χע�ⰴ24Сʱ�ƣ����֧��СʱΪ23����Ϊ59��
\param[in] stLedTime ʱ�䡣
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_KEYLED_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_LED_DisplayTime(HI_UNF_KEYLED_TIME_S stLedTime);

/**
\brief ����Ҫ��˸��LED ��š�
\attention \n
�����ϵ�����ܵ���Ŵ���������Ϊ��1��2��3��4��
\param[in] enPin Ҫ��ʾ����š�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_KEYLED_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_LED_SetFlashPin(HI_UNF_KEYLED_LIGHT_E enPin);

/**
\brief ����LED ��˸����
\attention \n
����Խ����˸�ٶ�Խ�졣
\param[in] enLevel ��˸����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_KEYLED_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_LED_SetFlashFreq(HI_UNF_KEYLED_LEVEL_E enLevel);

/**
\brief ����LED �����źŵơ�
\attention \n
��������TRUE,������FALSE
\param[in] bEnable ������δ������
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_KEYLED_NOT_INIT  ģ��û�г�ʼ��
\retval ::HI_ERR_KEYLED_INVALID_PARA  ��������Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_LED_LockSignal(HI_BOOL uLockFlag);


/** @} */  /** <!-- ==== API declaration end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_5 */
/** @{ */  /** <!-- ��PM�� */
/*---- pm ----*/
/** 
\brief �򿪵͹���ģ���豸��
\attention \n
�ڴ򿪵͹���ģ���豸�󣬲����л�ARM�Ĺ���ģʽ���̶�����͹���״̬��
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_PMoC_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_PMoC_INVALID_MODE  �Ƿ���ϵͳ����ģʽ
\see \n
��
*/
HI_S32 HI_UNF_PMOC_Init(HI_VOID);

/** 
\brief �رյ͹����豸��
\attention \n
��
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_PMoC_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_PMoC_INVALID_MODE  �Ƿ���ϵͳ����ģʽ
\see \n
��
*/
HI_S32 HI_UNF_PMOC_DeInit(HI_VOID);

/** 
\brief ����ARMҪ�л�����ģʽ��ͬʱ��ȡARM���ѵķ�ʽ��
\attention \n
ARM����HI_UNF_PMOC_MODE_SLEEP�����ģʽ���������ֹͣ���У������ڻ��Ѻ���ܼ���ִ�к���Ĵ���\n
�������ģʽǰ�������IR��ң�������豸��ǰ���KEY�豸��RTC�豸�������Ӧģ����жϱ����Σ�����ʵ�ָ���ģʽ�Ļ���\n
���������ʱ������ȷ������DDR���з��ʡ����Ա���ر���ʾ�������Ƶ�����DEMUX���롢����Ƶ����ȡ�
\param[in] enSystemMode  �õ͹�����ARM����ģʽ��
                         ����HI_UNF_PMOC_MODE_SLOW��
                         HI_UNF_PMOC_MODE_DOZEֻ����ARM����Ƶ�ʣ����Ľ��Ͳ������ԣ��Ƽ�ʹ��HI_UNF_PMOC_MODE_SLEEP�����ģʽ��
                         ��ģʽ�³���ֹͣ���У����غ���Normalģʽ��
\param[in]  penWakeUpStatus  ��HI_UNF_PMOC_MODE_SLEEP״̬����ʱ�Ļ��ѷ�ʽ�����庬����ο�::HI_UNF_PMOC_ACTUAL_WKUP_E
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_PMoC_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_PMoC_INVALID_MODE  �Ƿ���ϵͳ����ģʽ
\see \n
��
*/
HI_S32 HI_UNF_PMOC_SwitchSystemMode(HI_UNF_PMOC_MODE_E enSystemMode, HI_UNF_PMOC_ACTUAL_WKUP_E * penWakeUpStatus);


/** 
\brief ����ARM���ѷ�ʽ��
\attention \n
IRԭʼ��ֵ����ͨ��ң������ʹ���ֲ�õ�\n
�������ֵ�Ķ�Ӧ��ϵ����ͨ��Ӳ����оƬ�����ӹ�ϵ�õ���
\param[in] pstAttr  ARM���ѷ�ʽ��
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_PMoC_INVALID_PARA  �Ƿ�����
\retval ::HI_ERR_PMoC_INVALID_MODE  �Ƿ���ϵͳ����ģʽ
\see \n
��
*/
HI_S32 HI_UNF_PMOC_SetWakeUpAttr(HI_UNF_PMOC_WKUP_S_PTR pstAttr);

/** 
\brief ���û�����ʾ���ݡ�
\attention \n
����ʱ�����ʾָ������\n
\param[in] pstStandbyMode  ��ʾ����:ʱ�� or Ƶ�� or ����ʾ��
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_PMoC_INVALID_PARA  �Ƿ�����
\see \n
��
*/
HI_S32 HI_UNF_PMOC_SetStandbyDispMode(HI_UNF_PMOC_STANDBY_MODE_S_PTR pstStandbyMode);

/** 
\brief ��ȡϵͳ��ǰģʽ��
\attention \n
��������״̬����Ч���ӿ�ǰ�����\n
\param[in] penSystemMode ��Ҫ��ȡ��ģʽ��
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\see \n
��
*/
HI_S32 HI_UNF_PMOC_ReadSystemMode(HI_UNF_PMOC_MODE_E * penSystemMode);

/** 
\brief ���ù���������
\attention \n
Ŀǰ��֧�ֱ�׼��������\n
\param[in] eScene  ����������
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_PMoC_INVALID_PARA  �Ƿ�����
\see \n
��
*/
HI_S32 HI_UNF_PMOC_SetScene(HI_UNF_PMOC_SCENE_E eScene);


/** 
\brief ����Ŀǰǰ���ͬ����ң�صȴ�������豸�����͡�
\attention \n
ң�ؽ�֧��  HI_UNF_IR_CODE_NEC_SIMPLE ����\n
ǰ���֧��	HI_UNF_KEYLED_TYPE_STD ͬ HI_UNF_KEYLED_TYPE_PT6961 ��������\n	
\param[in] pdevType  ��ҪMCU֧�ֵĴ����豸��
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_PMoC_INVALID_PARA   �Ƿ�����
\retval ::HI_ERR_PMOC_FAILED_SETDEV  ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_PMOC_SetDevType(HI_UNF_PMOC_DEV_TYPE_S_PTR pdevType);


/** 
\brief ���ڼ���MCU���롣
\attention \n
��������ʹ�ã�MCU���������ɺ󣬿���ʹ������ӿ����룬����ÿ�ζ�����hi_c51.ko\n	
\param[in] pMcuCode MCU�����ƴ�������
\param[in] CodeSize MCU�����ƴ��볤��
\retval 0 �ɹ�
\retval ::HI_ERR_PMoC_NOT_INIT  PMoC�豸δ��
\retval ::HI_ERR_PMoC_INVALID_POINT  �Ƿ�ָ��
\retval ::HI_ERR_PMoC_INVALID_PARA   �Ƿ�����
\see \n
��
*/
HI_S32 HI_UNF_PMOC_LoadMcuCode(HI_U8 *pMcuCode, HI_U32 CodeSize);



/** @} */  /** <!-- ==== API declaration end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_6 */
/** @{ */  /** <!-- ��IR�� */
/*---IR---*/
/** 
\brief ��IR�豸��
\attention \n
�ظ����û�ʧ�ܣ����豸������ٵ���HI_UNF_IR_Enable�����������ռ�ֵ��
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  �����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  �ظ����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_Open(HI_VOID);

/** 
\brief �ر�IR�豸��
\attention \n
�ظ����ùرջ�ʧ�ܡ�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  �����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  �ظ����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_Close(HI_VOID);


/** 
\brief ʹ��IR�豸��
\attention \n
��
\param[in] bEnable  IR ʹ�ܿ���, HI_TRUE ʹ��, HI_FALSE ���á�
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  �����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  �ظ����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_Enable ( HI_BOOL bEnable);

/** 
\brief ��ȡң������Э������ ��
\attention \n
�����Ҫ��ȡ����ң������Э�����ͣ����ڵ���HI_UNF_IR_GetValue֮���ٵ���HI_UNF_IR_GetProtocol��

���HI_UNF_IR_SelectUserCode�ӿڲ���u32UserCodeΪ0����pu32KeyId����������������ֵ���û���������룩������û��벻Ϊ0����pu32KeyIdֻ����������������
\param[out]  penProtocol  Э������ָ��  ���庬����ο�::HI_UNF_IR_PROTOCOL_E
\param[in]   penProtocol  Э������ָ��
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NULL_PTR  ָ��Ϊ��
\see \n
��
*/

HI_S32 HI_UNF_IR_GetProtocol(HI_UNF_IR_PROTOCOL_E *penProtocol);

/** 
\brief ��ȡң�����İ���ֵ�Ͱ���״̬ ��
\attention \n
������ʽ�£�����HI_UNF_IR_GetValue����ʱ������ʱ������HI_UNF_IR_SetBlockTime�������ó�ʱʱ��u32BlockTime��ʱ���ش�����Ϣ\n
���HI_UNF_IR_SelectUserCode�ӿڲ���u32UserCodeΪ0����pu32KeyId����������������ֵ���û���������룩������û��벻Ϊ0����pu32KeyIdֻ����������������
\param[out]  penPressStatus  ����״̬�����庬����ο�::HI_UNF_KEY_STATUS_E
\param[out]  pu64KeyId  ����ֵ
\param[in] u32TimeoutMs   ��ʱֵ, ��λ�Ǻ���, 0 - ������, 0xFFFFFFFF-��������
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  �����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  �ظ����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_GetValue(HI_UNF_KEY_STATUS_E * penPressStatus, HI_U64 * pu64KeyId , HI_U32 u32TimeoutMs);


/** 
\brief �����Ƿ��ϱ���������״̬��
\attention \n
�粻���ã�Ĭ��Ϊ�򿪡�
\param[in] bEnable       ����������Ч��
                         0���رգ�
                         1��ʹ�ܡ�
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  �����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  �ظ����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_EnableKeyUp(HI_BOOL bEnable );


/** 
\brief �����Ƿ��ϱ��ظ�������һֱ����ʱ�����ݻ�ԴԴ���ϵ����뵽���ջ����������Ӧ�ó�����Ը�����Ҫ�������Ƿ��ϱ��ظ�������
\attention \n
�粻���ã�Ĭ��Ϊ��\n
�˽ӿ���Ҫ��HI_UNF_IR_RepKeyTimeoutVal�������ʹ�ã���HI_UNF_IR_RepKeyTimeoutVal�����ϱ��ظ������ļ��\n
���ʹ�����ظ������ϱ���������һֱ���ڰ���״̬�������Ϊ300���룬��ÿ300������ϱ�һ������\n
�����ֹ���ظ������ϱ������۰��¶೤ʱ�䣬ֻ�ϱ�һ�����ݡ�
\param[in] bEnable        ���������ظ��������ܡ�
                          0���رգ�
                          1��ʹ�ܡ�
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  �����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  �ظ����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_EnableRepKey(HI_BOOL bEnable);


/** 
\brief �����ϱ��ظ�������ʱ��������λΪms ��
\attention \n
��HI_UNF_IR_IsRepKey����Ϊ���ϱ��ظ�����ʱ���˽ӿ�������Ч��
\param[in] u32TimeoutMs   �ϱ��ظ�������ʱ����������ֵ��108ms��65536ms ��
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  �����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  �ظ����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_SetRepKeyTimeoutAttr(HI_U32 u32TimeoutMs);


/** 
\brief ����ң�������͡�
\attention \n
�粻���ã�Ĭ��ΪHI_UNF_IR_CODE_NEC_SIMPLE���͡�
\param[in] enIRCode  Ĭ��֧��4�ֱ�׼ң�������ͣ�
                     HI_UNF_IR_CODE_NEC_SIMPLE��Nec With Simple���ͣ�
                     HI_UNF_IR_CODE_TC9012��TC9012���ͣ�
                     HI_UNF_IR_CODE_NEC_FULL��Nec With Full���ͣ�
                     HI_UNF_IR_CODE_SONY_12BIT��Sony12Bit���͡�
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_SetCodeType(HI_UNF_IR_CODE_E enIRCode);


/** 
\brief  ��λIR�豸��
\attention \n
ֻ�ǰ�buffer�еļ�ֵ��������֮����Ҫ���������û��롣
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_IR_NOT_INIT  IR�豸δ��ʼ��
\retval ::HI_ERR_IR_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_IR_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_IR_INVALID_ISKEYUP_ARG  �����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_ISREPKEY_ARG  �ظ����Ƿ��ϱ������Ƿ�
\retval ::HI_ERR_IR_INVALID_CODETYPE  ���Ͳ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_IR_Reset(HI_VOID);

/** @} */  /** <!-- ==== API declaration end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_7 */
/** @{ */  /** <!-- ��WDG�� */
/*---- wdg ----*/
/** 
\brief ��WDG��Watch Dog���豸��
\attention \n
��֮��WDGĬ���ǽ�ֹ�ģ���Ҫ��ʽ����HI_UNF_WDG_Enableʹ��WDG�豸\N
�ظ��򿪻�ʧ�ܡ�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG�豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT  WDG����ָ����Ч
\retval ::HI_ERR_WDG_INVALID_PARA  WDG���������Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_Open(HI_VOID);


/** 
\brief �ر�WDG�豸��
\attention \n
�ظ��رջ�ʧ�ܡ�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG�豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT  WDG����ָ����Ч
\retval ::HI_ERR_WDG_INVALID_PARA  WDG���������Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_Close(HI_VOID);


/** 
\brief ʹ��WDG�豸��
\attention \n
��WDG�豸�󣬱�����ʽ����ʹ�ܽӿڡ�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG�豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT  WDG����ָ����Ч
\retval ::HI_ERR_WDG_INVALID_PARA  WDG���������Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_Enable(HI_VOID);

/** 
\brief ��ֹWDG�豸��
\attention \n
���ô˺�����ι���͸�λ�����������á�
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG�豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT  WDG����ָ����Ч
\retval ::HI_ERR_WDG_INVALID_PARA  WDG���������Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_Disable(HI_VOID);


/** 
\brief ��ȡι��ʱ������
\attention \n
ʱ������ȷ��1000ms��
\param[in] pu32Value  ι��ʱ��������λΪms
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG �豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT WDG����ָ����Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_GetTimeout(HI_U32 *pu32Value);

/** 
\brief ����ι��ʱ������
\attention \n
��
\param[in] u32Value  ι��ʱ��������λΪms
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG�豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT  WDG����ָ����Ч
\retval ::HI_ERR_WDG_INVALID_PARA  WDG���������Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_SetTimeout(HI_U32 u32Value);


/** 
\brief ִ��ι��������
\attention \n
��
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG�豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT  WDG����ָ����Ч
\retval ::HI_ERR_WDG_INVALID_PARA  WDG���������Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_ClearWatchDog (HI_VOID);


/** 
\brief ����WDG����Ӧģʽ��
\attention \n
��
\param[in] enRespondMode  ��Ӧģʽ��
                          HI_UNF_WDG_RESPOND_MODE_FIRSTRESET����һ�θ�λ��
                          HI_UNF_WDG_RESPOND_MODE_SECONDRESET����һ���жϣ��ڶ��θ�λ��
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG�豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT  WDG����ָ����Ч
\retval ::HI_ERR_WDG_INVALID_PARA  WDG���������Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_RespondMode(HI_UNF_WDG_RESPOND_MODE_E enRespondMode);

/** 
\brief ���ڸ�λ����ϵͳ��
\attention \n
��
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_WDG_NOT_INIT  WDG�豸δ��ʼ��
\retval ::HI_ERR_WDG_INVALID_POINT  WDG����ָ����Ч
\retval ::HI_ERR_WDG_INVALID_PARA  WDG���������Ч
\see \n
��
*/
HI_S32 HI_UNF_WDG_Reset(HI_VOID);

/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_8 */
/** @{ */  /** <!-- ��GPIO�� */
/**---- GPIO----*/
/** 
\brief ��GPIO��General Purpose Input/Output���豸��
\attention \n
�ظ��򿪻�ɹ���
\param ��
\retval 0 �ɹ�
\retval ::HI_ERR_GPIO_NOT_INIT  GPIO�豸δ��ʼ��
\retval ::HI_ERR_GPIO_INVALID_POINT  ָ��Ϊ��
\retval ::HI_ERR_GPIO_INVALID_PARA  �����Ƿ�
\retval ::HI_ERR_GPIO_FAILED_SWITCH2LED  ���蹦���л���GPIO���ܲ���ʧ��
\retval ::HI_ERR_GPIO_FAILED_LED_DIRSET_BIT  TUNERָʾ�ƶ�ӦGPIO�ܽŷ�������ʧ��
\retval ::HI_ERR_GPIO_FAILED_LED_WRITE_BIT  дTUNERָʾ�ƶ�ӦGPIO�ܽŲ���ʧ��
\see \n
��
*/
HI_S32 HI_UNF_GPIO_Open(HI_VOID);


/** 
\brief �ر�GPIO�豸��
\attention \n
�ظ��رջ�ɹ���
\param ��
\retval ��ο������붨���½�
\see \n
��
*/
HI_S32 HI_UNF_GPIO_Close(HI_VOID);

/** 
\brief ��GPIO�������Ŷ�ȡ���ݡ�
\attention �ܽźż������: �ܽź� = GPIO���*8 + GPIO�ܽ������ڵı�š�\n
����GPIO1_2,�����1���2�ţ���ô�ܽź�=1*8+2=10��\n
GPIO����ź͹ܽźŵı�Ŷ���0��ʼ������оƬ�ṩ13��GPIO����104���ܽ�\n
��
\param[out] u32GpioNo  �ܽźţ�ȡֵ��ΧΪ0��103��
\param[out] pbHighVolt  ָ�����ͣ����عܽ������ƽ��
\retval ��ο������붨���½�
\see \n
��
*/
HI_S32 HI_UNF_GPIO_ReadBit(HI_U32  u32GpioNo , HI_BOOL  *pbHighVolt );


/** 
\brief ��GPIO��������������ݡ�
\attention \n
��
\param[in] u32GpioNo  �ܽźţ�ȡֵ��ΧΪ0��103��
\param[in] bHighVolt  �ܽ������ƽ��
                      0���͵�ƽ��
                      1���ߵ�ƽ��
                      �������ߵ�ƽ��
\retval ��ο������붨���½�
\see \n
��
*/
HI_S32 HI_UNF_GPIO_WriteBit(HI_U32  u32GpioNo , HI_BOOL     bHighVolt );


/** 
\brief ����GPIO�������������������
\attention \n
���ö�Ӧ�ܽŵĹ�����ʽʱ�����뱣֤�ùܽŽ�������GPIOģʽ��\n
GPIO�ܽ��п��ܱ����á�
\param[in] u32GpioNo  �ܽźţ�ȡֵ��ΧΪ0��103��
\param[in] bInput  ������������ʶ�ܽŷ���
                   HI_TRUE���ùܽ��������룻
                   HI_FALSE���ùܽ����������
\retval ��ο������붨���½�
\see \n
��
*/
HI_S32 HI_UNF_GPIO_SetDirBit(HI_U32  u32GpioNo , HI_BOOL    bInput);


/** 
\brief ��ȡGPIO�������������������
\attention \n
��
\param[in] u32GpioNo  �ܽźţ�ȡֵ��ΧΪ0��103��
\param[out] pbInput  ָ�����ͣ�ָ�򲼶��ͱ������������عܽŷ���
\retval ��ο������붨���½�
\see \n
��
*/
HI_S32 HI_UNF_GPIO_GetDirBit(HI_U32  u32GpioNo , HI_BOOL    *pbInput);

/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_9 */
/** @{ */  /** <!-- ��CIPHER�� */
/* ---CIPHER---*/
/** 
\brief ��CIPHER�豸��
\attention \n
���ô˽ӿڴ�CIPHER�豸���ظ��򿪷��سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CIPHER_FAILED_INIT  CIPHER�豸��ʼ��ʧ��
\see \n
��
*/
HI_S32 HI_UNF_CIPHER_Open(HI_VOID);

/** 
\brief  �ر�CIPHER�豸��
\attention \n
���ô˽ӿڹر�CIPHER�豸���ظ��رշ��سɹ�����һ�������á�
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER�豸δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_CIPHER_Close(HI_VOID);

/** 
\brief ����һ·CIPHER����ȡCIPHER�����
\attention \n
���ô˽ӿڻ�ȡ1��CIPHER��������ڼӽ��ܡ�
\param[out] phCipher CIPHER�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER�豸δ��ʼ��
\retval ::HI_ERR_CIPHER_INVALID_POINT  ָ�����Ϊ��
\retval ::HI_ERR_CIPHER_FAILED_GETHANDLE  ��ȡCIPHER���ʧ�ܣ�û�п��е�CIPHER���

\see \n
��
*/
HI_S32 HI_UNF_CIPHER_CreateHandle(HI_HANDLE* phCipher);

/** 
\brief ���ٴ�����CIPHER�����
\attention \n
���ô˽ӿ������Ѿ�������CIPHER�����
\param[in] hCipher CIPHER�����
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER�豸δ��ʼ��
\see \n
��
*/
HI_S32 HI_UNF_CIPHER_DestroyHandle(HI_HANDLE hCipher);

/** 
\brief ����CIPHER������Ϣ
\attention \n
���м��ܽ���ǰ������ʹ�ô˽ӿ�����CIPHER�Ŀ�����Ϣ��
\param[in] hCipher CIPHER�����
\param[in] pstCtrl CIPHER������Ϣ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER�豸δ��ʼ��
\retval ::HI_ERR_CIPHER_INVALID_POINT  ָ�����Ϊ��
\retval ::HI_ERR_CIPHER_INVALID_PARA  ��������
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl);

/** 
\brief ���м��� 
\attention \n
ʹ��CIPHER���м��ܲ�����
\param[in] hCipher CIPHER�����
\param[in] u32SrcPhyAddr Դ���������ַ��
\param[in] u32DestPhyAddr Ŀ�����������ַ��
\param[in] u32ByteLength �������ݳ��ȡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER�豸δ��ʼ��
\retval ::HI_ERR_CIPHER_INVALID_PARA  ��������
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);

/** 
\brief ���м���
\attention \n
ʹ��CIPHER���н��ܲ�����
\param[in] hCipher CIPHER�����
\param[in] u32SrcPhyAddr Դ���������ַ��
\param[in] u32DestPhyAddr Ŀ�����������ַ��
\param[in] u32ByteLength �������ݳ��ȡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\retval ::HI_ERR_CIPHER_NOT_INIT  CIPHER�豸δ��ʼ��
\retval ::HI_ERR_CIPHER_INVALID_PARA  ��������
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  ����Ƿ�
\see \n
��
*/
HI_S32 HI_UNF_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
/** @} */  /** <!-- ==== API declaration end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      H_1_4_10 */
/** @{ */  /** <!-- ��TUNER�� */
/*---TUNER---*/
/** 
\brief ��ʼ��TUNER�豸��
\attention \n
֧���ظ���ʼ��TUNER�豸����ʱֱ�ӷ��سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_Init(HI_VOID);


/** 
\brief ȥ��ʼ��TUNER�豸��
\attention \n
֧���ظ�ȥ��ʼ��TUNER�豸����ʱֱ�ӷ��سɹ���
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_DeInit(HI_VOID);


/** 
\brief  ��ȡTUNER��Ĭ�����ԡ�
\attention \n
�˽ӿ���TUNER�豸��ʼ�������ʹ�á�
\param[in] u32tunerId TUNER�˿ںţ�ȡֵΪ0��1��
\param[out] pstTunerAttr ���ص�ǰTUNER��Ĭ�����ԡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_GetDeftAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr );


/** 
\brief ����TUNER��ǰ���ԡ�
\attention \n
��
\param[in] u32tunerId TUNER�˿ںţ�ȡֵΪ0��1��
\param[in] pstTunerAttr TUNER�����ԡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_TUNER_SetAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr );


/** 
\brief ��ȡTUNER�����ԡ�
\attention \n
�˽ӿ���TUNER�豸��ʼ�������ʹ�á�
\param[in] u32tunerId  TUNER�˿ںţ�ȡֵΪ0��1��
\param[out] pstTunerAttr ���ص�ǰTUNER�����ԡ�
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_GetAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr );


/** 
\brief ��TUNER�豸��
\attention \n
֧���ظ���TUNER�豸����ʱ��ֱ�ӷ��سɹ���
\param[in] u32tunerId  TUNER�˿ںţ�ȡֵΪ0��1��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_Open (HI_U32    u32tunerId);


/** 
\brief �ر�TUNER�豸��
\attention \n
֧���ظ��ر�TUNER�豸����ʱ��ֱ�ӷ��سɹ���
\param[in] u32tunerId  TUNER�˿ںţ�ȡֵΪ0��1�� 
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_Close(HI_U32    u32tunerId);


/** 
\brief TUNER��Ƶ��
\attention \n
��
\param[in] u32tunerId  TUNER�˿ںţ�ȡֵΪ0��1��
\param[in] pstConnectPara  TUNER��Ƶ����Ϣ��
\param[in] u32TimeOut  TUNER�������ȴ���ʱʱ�䣬0Ϊ���ȴ�������Ϊ��ȴ�ʱ�䣬��λms��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_Connect(HI_U32  u32tunerId , HI_UNF_TUNER_CONNECT_PARA_S  *pstConnectPara,HI_U32 u32TimeOut);


/** 
\brief ��ȡTUNER��Ƶ״̬����Ƶ������
\attention \n
��
\param[in] u32tunerId TUNER�˿ںţ�ȡֵΪ0��1��
\param[out] pstTunerStatus: ���ص�ǰTUNER����Ƶ״̬����Ƶ������ ע�⣺�˲���ֻ�ں������سɹ�������²������塣
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_GetStatus(HI_U32    u32tunerId , HI_UNF_TUNER_STATUS_S  *pstTunerStatus);


/** 
\brief ��ȡ��ǰTUNER �������ʣ��ÿ�ѧ��������ʾ��
\attention \n
��
\param[in] u32tunerId TUNER�˿ںţ�ȡֵΪ0��1��
\param[out] pu32BER  ָ��ǰTUNER �����ʵ�ָ�롣��ָ��ָ��һ����������Ԫ�ص����飬����Ԫ�غ�������:
                    pu32BER[0]:�����ʵ�������������
                    pu32BER[1]:�����ʵ�����С�����ֳ���1000
                    pu32BER[2]:������ָ������ȡ����ֵ
                    ����:������Ϊ2.156E-7����ô����Ԫ�ص�ȡֵ�ֱ�Ϊ
                    2��156��7
                    ������Ԫ��ֻ�ں������سɹ�������²������壬
                    ����Ӧ�ò�ɸ���ʵ�������������һ���ϴ�ֵ(����0.5��������Ԫ�طֱ�Ϊ5��0��1)��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_GetBER(HI_U32   u32tunerId , HI_U32 *pu32BER);


/** 
\brief ��ȡ��ǰTUNER ������ȡ�
\attention \n
��
\param[in] u32tunerId  TUNER�˿ںţ�ȡֵΪ0��1��
\param[out] pu32SNR  ָ��ǰTUNER����ȵ�ָ�롣
                    *pu32SNRȡֵ��ΧΪ22 ~ 51
                    �˲���ֻ�ں������سɹ�������²������壬
                    ����Ӧ�ò�ɽ���ֵ����Ϊ��Сֵ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��

\see \n
��
*/
HI_S32 HI_UNF_TUNER_GetSNR(HI_U32   u32tunerId , HI_U32 *pu32SNR );             /* range : 0-255  */


/** 
\brief ��ȡ��ǰTUNER���ź�ǿ�ȡ�
\attention \n
��
\param[in] u32tunerId  TUNER�˿ںţ�ȡֵΪ0��1��
\param[out] pu32SignalStrength  ָ��ǰTUNER�ź�ǿ�ȵ�ָ�롣
                    *pu32SignalStrength��ȡֵ��ΧΪ20~60
                  �˲���ֻ�ں������سɹ�������²������壬
                  ����Ӧ�ò�ɽ���ֵ����Ϊ��Сֵ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_TUNER_GetSignalStrength(HI_U32   u32tunerId , HI_U32 *pu32SignalStrength );


/** 
\brief ��ȡ��ǰTUNER��ʵ��Ƶ�ʺͷ����ʡ�
\attention \n
��
\param[in] u32tunerId  TUNER�˿ںţ�ȡֵΪ0��1��
\param[out] pu32Freq  ָ��ǰTUNERƵ���ָ�롣
                    pu32Symbָ��ǰ������
               
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_TUNER_GetRealFreqSymb( HI_U32 u32TunerId, HI_U32 *pu32Freq, HI_U32 *pu32Symb );

/** 
\brief ��OTP�豸
\attention \n
��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_OTP_Open(HI_VOID);

/** 
\brief �ر�OTP�豸
\attention \n
��
\param ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_OTP_Close(HI_VOID);

/** 
\brief дOTP
\attention \n
��
\param[in] enType    OTP��������
\param[in] pKey      д��������׵�ַ
\param[in] u32KeyLen д������ݳ��� ��λ Byte
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_FAILURE  APIϵͳ����ʧ��
\see \n
��
*/
HI_S32 HI_UNF_OTP_Write(HI_UNF_OTP_AREATYPE_E enType,HI_U8 *pKey,HI_U32 u32KeyLen);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_ECS_TYPE_H__ */

