/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_errno.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/

#include <string.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/mman.h>

//#include <asm/io.h>
#include <linux/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>



#include "hi_unf_ecs.h"
#include "hi_unf_demux.h"

#include "porter_rocme.h"

//�Ƿ��ʼ��
ROC_BOOL				g_bTunerInited = ROC_FALSE;

INT32_T g_nDemodSemaphoreId = 0;

#define TUNER_ID_0		(0)
#define TUNER_ID_1		(1)
#define TUNER_ID		(TUNER_ID_0)


/******************************************************************************************
func
*******************************************************************************************/
ROC_BOOL TDemodulate(INT32_T nFrequency,
					INT32_T nSymbolRate,
					INT32_T nModulation,
					INT32_T nInversion)
{
ROCME_TEST_PRINT
	if( !g_bTunerInited )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"tuner have not init\r\n");
		return ROC_ERR;
	}
	
	//Set_Demodulate_Status( TRUE );

	if( 0 == nFrequency || 0 == nSymbolRate )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"tuner param err\r\n");
		return ROC_ERR;
	}

	HI_UNF_TUNER_CONNECT_PARA_S stTunerParam;
	memset(&stTunerParam, 0, sizeof(HI_UNF_TUNER_CONNECT_PARA_S));
	stTunerParam.enSigType = HI_UNF_TUNER_SIG_TYPE_CAB;
	stTunerParam.unConnectPara.stCab.u32Freq = nFrequency;
	stTunerParam.unConnectPara.stCab.u32SymbolRate = nSymbolRate * 1000;
	switch( nModulation )
	{
	case 1:
		stTunerParam.unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_16;
		break;

	case 2:
		stTunerParam.unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_32;
		break;

	case 3:
		stTunerParam.unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_64;
		break;
		
	case 4:
		stTunerParam.unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_128;
		break;
		
	case 5:
		stTunerParam.unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_256;
		break;

	default:
		stTunerParam.unConnectPara.stCab.enModType = HI_UNF_MOD_TYPE_QAM_64;
		break;
	}

	if( nInversion )
	{
		stTunerParam.unConnectPara.stCab.bReverse = HI_TRUE;
	}
	else
	{
		stTunerParam.unConnectPara.stCab.bReverse = HI_FALSE;
	}
	
	if( HI_SUCCESS != HI_UNF_TUNER_Connect(TUNER_ID, &stTunerParam, 1000) )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"tuner connect err\r\n");
		return ROC_ERR;
	}

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_tuner_init
����˵��: 
            ��Ƶͷ�豸��ʼ�����м����������ʱ���ô˺��������������м��֮ǰ
        �������Ѿ������˸�Ƶͷ�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
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
INT32_T rocme_porting_tuner_init( void )
{
ROCME_TEST_PRINT
	HI_S32 ret;
	
	if( !g_bTunerInited )
	{
		if( 0 == g_nDemodSemaphoreId )
		{
			g_nDemodSemaphoreId = rocme_porting_sem_create( "Demod", 1, ROC_TASK_WAIT_FIFO);
		}

		if( HI_SUCCESS != HI_UNF_TUNER_Init() )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[TDRV_TunerInit] HI_UNF_TUNER_Init failed!\r\n");
			return ROC_ERR;
		}

		HI_UNF_TUNER_Open(TUNER_ID_0);

		HI_UNF_TUNER_ATTR_S enTunerAttr;
		HI_UNF_TUNER_GetDeftAttr(TUNER_ID_0, &enTunerAttr);
		enTunerAttr.enDemodDevType	= HI_UNF_DEMOD_DEV_TYPE_3130I;
		enTunerAttr.enI2cChannel	= HI_UNF_I2C_CHANNEL_QAM;
		enTunerAttr.enTunerDevType	= HI_UNF_TUNER_DEV_TYPE_TMX7070X;
		ret = HI_UNF_TUNER_SetAttr(TUNER_ID_0, &enTunerAttr);
		if( HI_SUCCESS != ret )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"[TDRV_TunerInit] HI_UNF_TUNER_SetAttr( TUNER_ID_0 ) failed! ret is %08x\r\n", ret);
			return ROC_ERR;
		}


		g_bTunerInited = ROC_TRUE;
	}
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_tuner_scanning
����˵��: 
            ��Ƶͷ�������ú���������ָ���Ĳ���������ָ��������ͨ���ϵĸ�Ƶͷ����
        ��ָ����Ƶ�㣬��Ҫ��ͬ����Ƶ��Ҫ����ȷ���ò����󣬺����������ء�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���ĸ�ƵͷID)
            [ tnr_param     ] : ��Ƶͷ����,��������:
                                type  -  ��Ƶͷ����
                                cab_param  -  typeΪ���߸�Ƶͷʱ���˲�����Ч
                                sat_param  -  typeΪ���Ǹ�Ƶͷʱ���˲�����Ч
                                ter_param  -  typeΪ�����Ƶͷʱ���˲�����Ч
    ���������
            [ tnr_state     ] : ��Ƶ������ĸ�Ƶͷ�Ĺ���״̬ 
��    �أ� 
    �ɹ� : 0            ( ��Ƶ���ò����ɹ� )
    ʧ�� : -1 �� ������ ( ��Ƶ���ò���ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_tuner_scanning( const INT32_T channel_index,const Roc_Tuner_Param_t tnr_param )
{
ROCME_TEST_PRINT
	INT32_T	bResult;
	
	if( !g_bTunerInited )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"tuner have not init\r\n");
		return ROC_ERR;
	}

	INT32_T nFrequency;
	INT32_T	nSymbolRate;
	INT32_T	nQAMSize;

	nFrequency = tnr_param.param.cab_param.frequency;
	nSymbolRate = tnr_param.param.cab_param.symbol_rate;
	nQAMSize = tnr_param.param.cab_param.modulation;
	
	
	bResult = TDemodulate(nFrequency, nSymbolRate, nQAMSize, 0);	
	if( !bResult )
	{
		bResult = TDemodulate(nFrequency, nSymbolRate, nQAMSize, 1);	
	}
	
	return bResult;
}
/**************************************************************************
��������: 
            rocme_porting_tuner_get_state
����˵��: 
           ��ѯָ������ͨ���ϵĸ�Ƶͷ�ĵ�ǰ״̬��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���ĸ�ƵͷID)
    ���������
            [ tnr_state     ] : ��Ƶͷ�ĵ�ǰ����״̬ 
��    �أ� 
    �ɹ� : 0            ( ��ѯ��Ƶͷ״̬�ɹ� )
    ʧ�� : -1 �� ������ ( ��ѯ��Ƶͷ״̬ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_tuner_get_state( const INT32_T channel_index,Roc_Tuner_State_e *tnr_state )
{
ROCME_TEST_PRINT
	HI_UNF_TUNER_STATUS_S stTunerStatus;
	
	if( HI_SUCCESS == HI_UNF_TUNER_GetStatus(TUNER_ID, &stTunerStatus) )
	{
		switch(stTunerStatus.enLockStatus)
		{
			case HI_UNF_TUNER_SIGNAL_DROPPED:
				*tnr_state = ROC_TUNER_STATE_UNLOCK;
				break;
			case HI_UNF_TUNER_SIGNAL_LOCKED:
				*tnr_state = ROC_TUNER_STATE_LOCKED;
				break;
			case HI_UNF_TUNER_SIGNAL_BUTT:
				*tnr_state = ROC_TUNER_STATE_UNKNOWN;
				break;
			default:
				*tnr_state = ROC_TUNER_STATE_IDLE;
				break;	
		}
		return ROC_OK;
	}
	else
	{
		
		ROCME_PRINTF(ROCME_LOG_ERROR, "get tuner status err\r\n");
		return ROC_ERR;
	}
}

/**************************************************************************
��������: 
            rocme_porting_tuner_get_signal_info
����˵��: 
           ��ȡָ������ͨ���ϵĸ�Ƶͷ�ĵ�ǰ�ź���Ϣ�������ź�ǿ�ȡ�����Ⱥ�
       �����ʡ�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ(�Ǿ���ĸ�ƵͷID)
    ���������
            [ signal_info   ] : ��Ƶͷ�ĵ�ǰ�ź���Ϣ������:
                                signal_strength  -  �ź�ǿ��
                                signal_snr       -  �ź������/�ź�����
                                signal_ber       -  �ź�������
��    �أ� 
    �ɹ� : 0            ( ��ѯ��Ƶͷ��Ϣ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ѯ��Ƶͷ��Ϣʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_tuner_get_signal_info( const INT32_T channel_index,Roc_Signal_Info_t *signal_info )
{
ROCME_TEST_PRINT
	if( !g_bTunerInited )
	{
		return ROC_ERR;
	}

	HI_U32 nSnr = 0;
	HI_U32 nSignalIntensity = 0;
	
	if( HI_SUCCESS != HI_UNF_TUNER_GetSNR(TUNER_ID, &nSnr) )
	{
		nSnr = 0;
	}


	if( HI_SUCCESS != HI_UNF_TUNER_GetSignalStrength(TUNER_ID, &nSignalIntensity) )
	{
		nSignalIntensity = 0;
	}

	HI_U32 szBuf[3];

	if( HI_SUCCESS != HI_UNF_TUNER_GetBER(TUNER_ID, szBuf) )
	{
		szBuf[0] = 0xff;
		szBuf[1] = 0xff;
		szBuf[2] = 0xff;
	}

	signal_info->signal_ber.total_counter 	= 50000;//��ʱ����һ������
	signal_info->signal_ber.error_counter	= szBuf[0];
	signal_info->signal_snr = nSnr;
	signal_info->signal_strength = nSignalIntensity;
	signal_info->signal_RFLevle = 50;

	return ROC_OK;
}




