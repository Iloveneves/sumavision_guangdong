/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_demux.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/


#include "hi_unf_demux.h"

#include "porter_rocme.h"



#if 0
#define ROCME_DMX_FILTER_DEPTH          	(16)
#define ROCME_DMX_FILTER_NUM			(48)
#define ROCME_DMX_CHANNEL_NUM		(48)
#define ROCME_DMX_SEC_NUM			(32)
#define ROCME_DMX_SEC_MAXLEN			(4096)	

/* ͨ����һ�������� */
typedef struct 
{
	HI_BOOL 	bUsed; 				/* �Ƿ�ռ�� */
	HI_BOOL		bRun;				/* �Ƿ��ϱ�����*/

	HI_U32  		u32Pid;	 			/* ͨ��PID */
	HI_S32  		hChanHandle;		/* ͨ���� */
	HI_S32		poolsize;
	
	HI_U32  		u32DemuxId;		/* PORT�� */

	Roc_Slot_Type_e eType;  /* ͨ������ */

	HI_UNF_DMX_DATA_S stDataBuf;
} ROCME_DMX_CHANNEL_ATTR_S;

/* ���������� */
typedef struct 
{
   
	HI_BOOL 	bUsed;  				/* �Ƿ�ռ�� */
	HI_BOOL 	bRun;				/* �Ƿ��ϱ�����*/
	
	HI_HANDLE 	hFilterHandle;		/* ��������� */
	HI_HANDLE	hChanIndex;		/* ͨ����INDEX */

	HI_S32 s32Wide;
	Roc_Filter_Type_e	eType;//����������
	
	HI_U8 au8Coef[ROCME_DMX_FILTER_DEPTH];
	HI_U8 au8Mask[ROCME_DMX_FILTER_DEPTH];
	HI_U8 au8Excl[ROCME_DMX_FILTER_DEPTH];
	
} ROCME_DMX_FILTER_ATTR_S;

static HI_BOOL 	rocme_dmx_init = HI_FALSE;
static UINT32_T g_hDemuxMutex = 0;



static HI_U8	u8chanenable[ROCME_DMX_CHANNEL_NUM];
static HI_U8	u8filterenable[ROCME_DMX_FILTER_NUM];


static ROCME_DMX_CHANNEL_ATTR_S 	rocme_channel[ROCME_DMX_CHANNEL_NUM];
static ROCME_DMX_FILTER_ATTR_S		Rocme_filter[ROCME_DMX_FILTER_NUM];



/***************************************************************************************

!!!!!!!!���ļ��кܶ�ӿڲ���ͨ�������м�����ʵ�֣����ҿ�����������Ĺ���ʵ���г�ͻ
*****************************************************************************************/

static HI_UNF_DMX_CHAN_TYPE_E DemuxGetChannelType(const Roc_Slot_Type_e slot_type)
{
	HI_UNF_DMX_CHAN_TYPE_E eChannelType = HI_UNF_DMX_CHAN_TYPE_BUTT;
	
	switch (slot_type)
	{
		case ROC_SLOT_TYPE_SECTION:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_SEC;
			break;

		case ROC_SLOT_TYPE_PES:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_PES;
			break;
			
		case ROC_SLOT_TYPE_RAW:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_POST;
			break;

		default:
			break;	
	}

	return eChannelType;
}

/**************************************************************************
��������: 
            rocme_porting_demux_init
����˵��: 
            DEMUX���ܳ�ʼ�����м����������ʱ���ô˺��������������м��֮ǰ
        �������Ѿ�������DEMUX�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
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
INT32_T rocme_porting_demux_init(void)
{
ROCME_TEST_PRINT
	HI_S32 i;
	
	//�򿪽⸴���豸��
	CHK_RETURN( (HI_FALSE ==  rocme_dmx_init)  , HI_SUCCESS );

	/* �ȳ�ʼ��DVB TS ͨ· */
	DOFUNC_RETURN( HI_UNF_DMX_Init() );
	DOFUNC_RETURN( HI_UNF_DMX_AttachTSPort(HI_UNF_DMX_ID_0_PLAY , HI_UNF_DMX_PORT_0_TUNER ) );
printf("1111111111111111111111111111\r\n");
	if (g_hDemuxMutex == 0)
	{
		g_hDemuxMutex  = rocme_porting_mutex_create(ROC_MUTEX_RECURSIVE_NP);
		if (g_hDemuxMutex == 0)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"mutex create failed\n");
			return ROC_ERR;
		}
	}


	for (i = 0; i< ROCME_DMX_CHANNEL_NUM; i++)
	{
		memset(&rocme_channel[i], 0x0, sizeof(ROCME_DMX_CHANNEL_ATTR_S));
		
		rocme_channel[i].bUsed = HI_FALSE;
		rocme_channel[i].bRun = HI_FALSE;
		rocme_channel[i].hChanHandle= 0xffffffff;
		rocme_channel[i].u32Pid = 0xffffffff;

		u8chanenable[i] = 0;
		
	}

	for (i = 0; i< ROCME_DMX_FILTER_NUM; i++)
	{
		memset(&Rocme_filter[i], 0x0, sizeof(ROCME_DMX_FILTER_ATTR_S));

		Rocme_filter[i].bUsed = HI_FALSE;
		Rocme_filter[i].bRun = HI_FALSE;
		Rocme_filter[i].hChanIndex = 0xffffffff;
		Rocme_filter[i].hFilterHandle = 0xffffffff;

		u8filterenable[i] = 0;
	}



	rocme_dmx_init = HI_TRUE;

	rocme_porting_task_sleep(10);
	
	return ROC_OK;


}

/**************************************************************************
��������: 
            rocme_porting_demux_term
����˵��: 
            ж��DEMUX���ܡ�Ŀǰ�˺�������ʵ��Ϊ�ա�
����˵����
    ���������
            void
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ж�سɹ� )
    ʧ�� : -1 �� ������ ( ж��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_demux_term(void)
{

	ROCME_TEST_PRINT
	CHK_RETURN( (HI_TRUE ==  rocme_dmx_init)  , HI_SUCCESS );
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

	DOFUNC_RETURN( HI_UNF_DMX_DetachTSPort( HI_UNF_DMX_ID_0_PLAY) );
	HI_UNF_DMX_DeInit() ;

	rocme_porting_mutex_unlock(g_hDemuxMutex);


	rocme_porting_mutex_destroy(g_hDemuxMutex);
	g_hDemuxMutex = 0;

	rocme_dmx_init = HI_FALSE;

	return ROC_OK;
}


/**************************************************************************
��������: 
            rocme_porting_slot_query_PID
����˵��: 
            ָ������ͨ���ϣ���ѯһ��PID�Ƿ��Ѿ���ĳ��slot(�����м��ʹ�õ�
        slot���м��֮���slot)ռ�ã���ƽ̨��֧��slot��PID�趨�����ظ�����
        ���ܱ���ʵ�֡�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ pid           ] : ��Ҫ��ѯ��PIDֵ
    ���������
            
��    �أ� 
    ��PIDδ��ռ�� :  0
    ��PID�ѱ�ռ�� : -1
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_query_PID(const INT32_T channel_index,const UINT16_T pid)
{
ROCME_TEST_PRINT
	UINT32_T i;
	for(i=0;i<ROCME_DMX_CHANNEL_NUM;i++)
	{
		if((rocme_channel[i].bUsed == HI_TRUE)&&(rocme_channel[i].u32Pid == pid))
		{
			break;
		}
	}
	if(i>= ROCME_DMX_CHANNEL_NUM)
	{
		return ROC_OK;
	}
	else
	{
		return ROC_ERR;
	}
}


/**************************************************************************
��������: 
            rocme_porting_slot_alloc
����˵��: 
            ��ָ��������ͨ�����������һ��slot(ָ��slot�����͡�buff�Ĵ�С)��
        ���ɹ����뵽slot������һ��slot�Ŀ���ID���м����öԴ�slot�Ŀ���Ȩ��
        ��ͨ����ID�Դ�slot�豸�����޸ġ��������ͷŵȾ��������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ slot_type     ] : slot�����ͣ���������:
                                ROC_SLOT_TYPE_NULL     -  used with inject carousel 
                            packet only flag
                                ROC_SLOT_TYPE_SECTION  -  for section data - Signal 
                            every section
                                ROC_SLOT_TYPE_PES      -  signal every complete PES
                            packet except when signal_on_every_transport_packet is 
                            supplied as a flag
                                ROC_SLOT_TYPE_RAW      -  Raw transport packets, si-
                            -gnalled every packet
                                ROC_SLOT_TYPE_PCR      -  specifies that the data c-
                            -ollected on this slot is collected for PCR gathering purposes
                                ROC_SLOT_TYPE_RESERVE  -  ��չ����
             [ buff_size    ] : ��Ҫ���ٵ�slotʹ�õ�buff�Ĵ�С���м������������⣬
                            ������64KB��
    ���������
            ��
��    �أ� 
    �ɹ� : ���뵽��slot����ID ( ����ɹ� )
    ʧ�� : -1 �� ������       ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_alloc(const INT32_T channel_index,const Roc_Slot_Type_e slot_type,const INT32_T buff_size)
{
ROCME_TEST_PRINT
	UINT32_T ret = 0;
	INT32_T i;
	HI_UNF_DMX_CHAN_ATTR_S stChAttr;
			
	for (i = 0; i<	ROCME_DMX_CHANNEL_NUM; i++)
	{
		if (rocme_channel[i].bUsed == HI_FALSE)
		{


			rocme_channel[i].poolsize = buff_size;
			rocme_channel[i].eType = slot_type;
			rocme_channel[i].u32DemuxId = HI_UNF_DMX_ID_0_PLAY;

			break;
		}
	}

	if (i>= ROCME_DMX_CHANNEL_NUM) //IPANEL_DMX_CHANNEL_NUM
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "rocme_porting_slot_alloc failed. no slot %x\n");
		return ROC_ERR;
	}

	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[i];

	rocme_porting_mutex_lock(g_hDemuxMutex);

	ret = HI_UNF_DMX_GetChannelDefaultAttr(&stChAttr);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_GetChannelDefaultAttr failed. ret = %x\n", ret);
		return ROC_ERR;
	}
	
	stChAttr.enChannelType = DemuxGetChannelType(slot_type);
	if (stChAttr.enChannelType == HI_UNF_DMX_CHAN_TYPE_SEC)
	{
		stChAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_DISCARD; 
	}
	else
	{
		stChAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_FORBID; 
	}
	stChAttr.enOutputMode = HI_UNF_DMX_CHAN_OUTPUT_MODE_PLAY;
	stChAttr.u32BufSize = buff_size;

	
	ret = HI_UNF_DMX_CreateChannel((HI_U32)pChannel->u32DemuxId, &stChAttr, (HI_HANDLE*)(&pChannel->hChanHandle));
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CreateChannel failed. ret = %x\n", ret);
		return ROC_ERR;
	}
		
	rocme_channel[i].bUsed = HI_TRUE;
	rocme_porting_mutex_unlock(g_hDemuxMutex);
	return( i);
}

/**************************************************************************
��������: 
            rocme_porting_slot_modify
����˵��: 
            ����slot_ID���޸���Ӧ��slot�豸��һ����������(������PIDֵ)��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ pid        ] : ��Ҫ���õ�һ����������ֵ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �޸�slotһ�����������ɹ� )
    ʧ�� : -1 �� ������ ( �޸�slotһ����������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_modify(const INT32_T slot_ID,const UINT16_T pid)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
	HI_S8  i, j;
	HI_UNF_DMX_CHAN_ATTR_S stChAttr;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];

	if(pid == pChannel->u32Pid)
	{
		ROCME_PRINTF(ROCME_LOG_INFO, "same pid , %d to %d .\n", pid , pChannel->u32Pid);
		return ROC_OK;
	}
	if(rocme_porting_slot_query_PID(slot_ID,pid)==ROC_ERR)
	{
		
		ROCME_PRINTF(ROCME_LOG_ERROR, "the pid is used\n");
		return ROC_ERR;
	}

	if(pChannel->hChanHandle != 0xffffffff)
	{
		rocme_porting_mutex_lock(g_hDemuxMutex);
		//�ȹر�ͨ��
		HI_UNF_DMX_CHAN_STATUS_S status;
		ret = HI_UNF_DMX_GetChannelStatus(pChannel->hChanHandle, &status);
		if( ret != HI_SUCCESS)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CloseChannel failed. channel %x (%x) , ret = %x\n", 
				slot_ID, pChannel->hChanHandle, ret);
			
			status.enChanStatus = HI_UNF_DMX_CHAN_PLAY_EN;
		}
		
		if(status.enChanStatus != HI_UNF_DMX_CHAN_CLOSE)
		{
			ret = HI_UNF_DMX_CloseChannel(pChannel->hChanHandle);
			if( HI_SUCCESS != ret )
			{
				ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CloseChannel failed. channel %x (%x) , ret = %x\n", 
					slot_ID, pChannel->hChanHandle, ret);
			}
		}
		
		//����pid
		ret = HI_UNF_DMX_SetChannelPID(pChannel->hChanHandle, pid);
		if( HI_SUCCESS != ret )
		{
			rocme_porting_mutex_unlock(g_hDemuxMutex);
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_SetChannelPID failed. channel %x (%x), pid %d , ret = %x\n", 
				slot_ID, pChannel->hChanHandle, pid, ret);
			return ROC_ERR;
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_INFO, "HI_UNF_DMX_SetChannelPID succes, channel %x (%x) , pid %d  .\n", 
				slot_ID, pChannel->hChanHandle, pid);
		}
		
		pChannel->u32Pid= pid;	
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		return ROC_OK;

	}
	else
	{
		
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel handle err\r\n");
		return ROC_ERR;
	}
		

}
/**************************************************************************
��������: 
            rocme_porting_slot_clear
����˵��: 
            ����slot_ID����������õ�һ����������(�������PIDֵ)��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���slot���������ɹ� )
    ʧ�� : -1 �� ������ ( ���slot��������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_clear(const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
	HI_S8  i, j;
	HI_UNF_DMX_CHAN_ATTR_S stChAttr;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];


	rocme_porting_mutex_lock(g_hDemuxMutex);

	pChannel->u32Pid= 0x1fff;
	HI_UNF_DMX_CloseChannel(pChannel->hChanHandle);
	ret = HI_UNF_DMX_SetChannelPID(pChannel->hChanHandle, pChannel->u32Pid);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_SetChannelPID failed. channel %x (%x), pid %d , ret = %x\n", 
			slot_ID, pChannel->hChanHandle, pChannel->u32Pid, ret);
		return ROC_ERR;
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_INFO, "HI_UNF_DMX_SetChannelPID succes, channel %x (%x) , pid %d  .\n", 
			slot_ID, pChannel->hChanHandle, pChannel->u32Pid);
	}

	rocme_porting_mutex_unlock(g_hDemuxMutex);	
	return ROC_OK;


}


/**************************************************************************
��������: 
            rocme_porting_slot_start
����˵��: 
            ����һ��slot�豸��ʼ�������ݣ�����ײ�ƽ̨��slot�豸�޴����õ�ʵ�֣�
        ��˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����slot�豸�ɹ� )
    ʧ�� : -1 �� ������ ( ����slot�豸ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_start(const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
	HI_UNF_DMX_CHAN_STATUS_S status;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];

	ret = HI_UNF_DMX_GetChannelStatus(pChannel->hChanHandle, &status);
	if( ret != HI_SUCCESS)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CloseChannel failed. channel %x (%x) , ret = %x\n", 
			slot_ID, pChannel->hChanHandle, ret);
	
		status.enChanStatus = HI_UNF_DMX_CHAN_CLOSE;
	}
	
	if(status.enChanStatus == HI_UNF_DMX_CHAN_CLOSE)
	{
		ret = HI_UNF_DMX_OpenChannel((HI_U32)pChannel->hChanHandle);
		if( HI_SUCCESS != ret )
		{
			rocme_porting_mutex_unlock(g_hDemuxMutex);
			ROCME_PRINTF(ROCME_LOG_ERROR,"HI_UNF_DMX_OpenChannel failed. channel %x (%x), ret = %x\n", 
				slot_ID, pChannel->hChanHandle, ret);
			return ROC_ERR;
		}
		else
		{
			ROCME_PRINTF(ROCME_LOG_INFO, "HI_UNF_DMX_OpenChannel success. channel %x (%x) \n", 
				slot_ID, pChannel->hChanHandle);
		}
	}
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
}


/**************************************************************************
��������: 
            rocme_porting_slot_stop
����˵��: 
            ֹͣһ��slot�豸�������ݣ�����ײ�ƽ̨��slot�豸�޴����õ�ʵ�֣�
        ��˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣslot�豸�ɹ� )
    ʧ�� : -1 �� ������ ( ֹͣslot�豸ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_stop(const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];
	
	ret = HI_UNF_DMX_CloseChannel((HI_U32)pChannel->hChanHandle);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CloseChannel failed. channel %x (%x) , ret = %x\n", 
			slot_ID, pChannel->hChanHandle, ret);
		return ROC_ERR;
	}
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
}


/**************************************************************************
��������: 
            rocme_porting_slot_free
����˵��: 
            �ͷŵ���һ��ָ��slot�Ŀ���Ȩ��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �ͷųɹ� )
    ʧ�� : -1 �� ������ ( �ͷ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_free(const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
#if 1
	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];

	rocme_porting_mutex_lock(g_hDemuxMutex);

	ret = HI_UNF_DMX_DestroyChannel( (HI_U32)pChannel->hChanHandle ) ;
	if( HI_SUCCESS != ret )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_DestroyChannel failed. ch is 0x%x , ret = %x\n", 
						pChannel->hChanHandle, ret);
	}
	else
	{
		ROCME_PRINTF(ROCME_LOG_INFO, "HI_UNF_DMX_DestroyChannel %x success .\n", pChannel->hChanHandle);
	}
#endif
	rocme_channel[slot_ID].bUsed = HI_FALSE;
	rocme_channel[slot_ID].poolsize = 0;
	rocme_channel[slot_ID].eType = 0;
	rocme_channel[slot_ID].u32DemuxId = HI_UNF_DMX_ID_0_PLAY;
	rocme_channel[slot_ID].bRun = HI_FALSE;
	rocme_channel[slot_ID].u32Pid = 0xffffffff;
	rocme_channel[slot_ID].hChanHandle= 0xffffffff;
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
}


/**************************************************************************
��������: 
            rocme_porting_slot_buff_wait
����˵��: 
            ָ������ͨ���������м��ͨ���˷���������ѯ�Ƿ���slot���˵����ݣ�
        ���ҿ������õȴ���ʱʱ�ޣ���������ͨ���Ϲ��˵������ݣ��򷵻ع��˵�
        �����ݵ�slot����ID��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ time_out_ms   ] : ��ʱʱ�䣬��λΪ����(ms)
    ���������
            
��    �أ� 
    �ɹ� : slot����ID   ( �ɹ���ѯ����slot���˵����� )
    ʧ�� : -1 �� ������ ( ��ѯʧ��/slot��time_out_msʱ����δ���˵����� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait(const INT32_T channel_index,const INT32_T time_out_ms)
{
ROCME_TEST_PRINT

	INT32_T i,j;
	HI_U32 ret = 0;
	HI_U32 u32ChnNum ;
	HI_UNF_DMX_DATA_S stBuf;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	for(i=0;i<ROCME_DMX_CHANNEL_NUM;i++)
	{	
		if(rocme_channel[i].hChanHandle == 0xffffffff)
			continue;
		
		if(HI_UNF_DMX_AcquireBuf(rocme_channel[i].hChanHandle,1,&u32ChnNum,&stBuf,0) == HI_SUCCESS)
		{
			memcpy(&(rocme_channel[i].stDataBuf),&stBuf,sizeof(HI_UNF_DMX_DATA_S));
			rocme_porting_mutex_unlock(g_hDemuxMutex);
			return i;
		}
		
	}
	rocme_porting_mutex_unlock(g_hDemuxMutex);
	ROCME_PRINTF(ROCME_LOG_ERROR, "no channel get data err\r\n");
	return ROC_ERR;

}

/**************************************************************************
��������: 
            rocme_porting_slot_buff_wait_multi
����˵��: 
            ָ������ͨ���������м��ͨ���˷���������ѯ�Ƿ���slot���˵����ݣ�
        ���ҿ������õȴ���ʱʱ�ޣ���������ͨ���Ϲ��˵������ݣ��򽫻�ȡ����
        �ݵ�slot����slot_ID_ar�����Ա,���޸�*countΪ�Ѿ���ȡ�����ݵ�slot������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ time_out_ms   ] : ��ʱʱ�䣬��λΪ����(ms)
            [ *count        ] : slot_ID_ar�����Ա������
    ���������
            [ slot_ID_ar    ] : ��ȡ�����ݵ�slot
            [ *count        ] : �Ѿ���ȡ�����ݵ�slot�ĸ���
��    �أ� 
    �ɹ� : 0
    ʧ�� : -1 �� ������ ( ��ѯʧ��/slot��time_out_msʱ����δ���˵����� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait_multi(const INT32_T channel_index, INT32_T *slot_ID_ar, INT32_T *count , const INT32_T time_out_ms)
{
	ROCME_TEST_PRINT

		INT32_T i,j;
		HI_U32 ret = 0;
		HI_U32 u32ChnNum ;
		HI_UNF_DMX_DATA_S stBuf;
		HI_HANDLE ChannelHandle[ROCME_DMX_CHANNEL_NUM];
		memset(ChannelHandle,0xffffffff,ROCME_DMX_CHANNEL_NUM);
	
		u32ChnNum = ROCME_DMX_CHANNEL_NUM;
//		rocme_porting_mutex_lock(g_hDemuxMutex);
		ret = HI_UNF_DMX_GetDataHandle(ChannelHandle, &u32ChnNum, 100);
		if( HI_SUCCESS != ret )
		{	
//			rocme_porting_mutex_unlock(g_hDemuxMutex);
			//ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_GetDataHandle err\r\n");
			return ROC_ERR;
		}
		*count = u32ChnNum;
		j = 0;
		for(i=0;i<ROCME_DMX_CHANNEL_NUM;i++)
		{
			if(rocme_channel[i].hChanHandle == 0xffffffff)
				continue;
			
			if(HI_UNF_DMX_AcquireBuf(rocme_channel[i].hChanHandle,1,&u32ChnNum,&stBuf,100) == HI_SUCCESS)
			{
				slot_ID_ar[j] = i;
				memcpy(&(rocme_channel[i].stDataBuf),&stBuf,sizeof(HI_UNF_DMX_DATA_S));
				j++;
			}
		}
//		rocme_porting_mutex_unlock(g_hDemuxMutex);		
		return ROC_OK;

}


/**************************************************************************
��������: 
            rocme_porting_slot_buff_get
����˵��: 
            ��ָ��slot��buff�еĸ���(��ȡ)��ָ�����ȵ����ݣ��м��ֻ���ڵ���
        ��rocme_porting_slot_buff_wait�󣬲Ż�ʹ�ô˺����жϹ��˵����ݵĹ�����
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ *buff_ptr  ] : �洢��ȡ�������ݵ�buff��ͷָ��
            [ buff_size  ] : ��Ҫ��ȡ�����ݵĳ��ȣ����洢buff�ĳ���
    ���������
            [ *data_size ] : ʵ����ȡ�������ݵĳ���
��    �أ� 
    �ɹ� : 0            ( ��ȡ���ݳɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_get(const INT32_T slot_ID, UINT8_T *buff_ptr, const UINT32_T buff_size, UINT32_T *data_size)
{
ROCME_TEST_PRINT

	HI_S32 ret=0;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	*data_size = rocme_channel[slot_ID].stDataBuf.u32Size> buff_size ? buff_size : rocme_channel[slot_ID].stDataBuf.u32Size;
	memcpy(buff_ptr, rocme_channel[slot_ID].stDataBuf.pu8Data, *data_size);
	rocme_porting_mutex_unlock(g_hDemuxMutex);
	 return ROC_OK;
}


/**************************************************************************
��������: 
            rocme_porting_slot_buff_read
����˵��: 
            ��ָ����slot��buff�ж�ȡ���ݣ���ȡ���ݺ�Ҫ�����buff���м����
        Ҫ��slot��buff�е����ݶ���2��buff�У��ֱ���data0��data1����ȡ����ʱ
        ���Ƚ����ݶ���data0�У���data0�������ٽ����ݶ�ȡ��data1�У����ռ䲻
        ��ʱ�����ض�ȡʧ�ܡ�
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ *p_data0   ] : �洢������0��ͷָ��
            [ size0      ] : �洢������0�ĳ���
            [ *p_data1   ] : �洢������1��ͷָ��
            [ size1      ] : �洢������1�ĳ���
    ���������
            [ *datasize  ] : ʵ�ʶ�ȡ�������ݳ���
��    �أ� 
    �ɹ� : 0            ( ��ȡ���ݳɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_read(const INT32_T slot_ID, UINT8_T *p_data0, UINT32_T size0, UINT8_T *p_data1, UINT32_T size1, UINT32_T *datasize)
{
ROCME_TEST_PRINT

	HI_S32 ret=0;
	ROCME_PRINTF(ROCME_LOG_INFO, "size =%d,data_ptr = 0x%x\n",rocme_channel[slot_ID].stDataBuf.u32Size,rocme_channel[slot_ID].stDataBuf.pu8Data);

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(rocme_channel[slot_ID].stDataBuf.u32Size>size0+size1)
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "size too small\n");
		return ROC_ERR;
	}
	else if(rocme_channel[slot_ID].stDataBuf.u32Size>size0)
	{
		memcpy(p_data0,rocme_channel[slot_ID].stDataBuf.pu8Data,size0);
		memcpy(p_data1,rocme_channel[slot_ID].stDataBuf.pu8Data+size0,rocme_channel[slot_ID].stDataBuf.u32Size - size0);
	}
	else
	{
		memcpy(p_data0,rocme_channel[slot_ID].stDataBuf.pu8Data,size0);
	}
	*datasize =rocme_channel[slot_ID].stDataBuf.u32Size;
	rocme_porting_mutex_unlock(g_hDemuxMutex);
	return ROC_OK;

	
}


/**************************************************************************
��������: 
            rocme_porting_slot_buff_flush
����˵��: 
            ���ָ����slot��buff��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���ָ��slot��buff�ɹ� )
    ʧ�� : -1 �� ������ ( ���ָ��slot��buffʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_flush(const INT32_T slot_ID)
{
	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(HI_UNF_DMX_ReleaseBuf(rocme_channel[slot_ID].hChanHandle,1,&(rocme_channel[slot_ID].stDataBuf)) == HI_SUCCESS)
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		return ROC_OK;
	}
	else
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "release err \n");
		return ROC_ERR;
	}
}


/**************************************************************************
��������: 
            rocme_porting_filter_alloc
����˵��: 
            ��ָ��������ͨ�����������һ��filter(ָ��filter������)�����ɹ���
        �뵽filter������һ��filter�Ŀ���ID���м����öԴ�filter�Ŀ���Ȩ����
        ͨ����ID�Դ�filter�豸�����޸ġ��������ͷŵȾ��������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ filter_type   ] : filter�����ͣ���������:
                                ROC_FILTER_TYPE_SECTION       -  Provides 8 byte filter/mask
                                ROC_FILTER_TYPE_PES           -  Filter PES
                                ROC_FILTER_TYPE_TSHEADER      -  Filter TSHeader
                                ROC_FILTER_TYPE_PES_STREAMID  -  Filter PES stream ID
                                ROC_FILTER_TYPE_NEG_MATCH     -  Negative Match Mode filtering
                                ROC_FILTER_TYPE_RESERVE       -  ��չ����
    ���������
            ��
��    �أ� 
    �ɹ� : ���뵽��filter����ID ( ����ɹ� )
    ʧ�� : -1 �� ������         ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_alloc(const INT32_T channel_index,const Roc_Filter_Type_e filter_type)
{
ROCME_TEST_PRINT
	INT32_T i = 0;
	HI_S32 ret=0;

	HI_UNF_DMX_FILTER_ATTR_S	stFilterAttr;


	//Ѱ�ҿ���λ��
	for( i = 0; i < ROCME_DMX_FILTER_NUM; i ++ )
	{
		if( !Rocme_filter[i].bUsed)
		{
			break;
		}
	}
	
	if( i >= ROCME_DMX_FILTER_NUM )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "no more free filter, failed. \n");
		return ROC_ERR;
	}
	else
	{
		rocme_porting_mutex_lock(g_hDemuxMutex);
		
		memset(&stFilterAttr, 0, sizeof(HI_UNF_DMX_FILTER_ATTR_S));//�������κ����ݣ�������set�Ժ��ٹ��ˡ�

		ret = HI_UNF_DMX_CreateFilter(HI_UNF_DMX_ID_0_PLAY, &stFilterAttr, (HI_HANDLE*)&Rocme_filter[i].hFilterHandle);
		if( HI_SUCCESS != ret)
		{
			rocme_porting_mutex_unlock(g_hDemuxMutex);
			ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CreateFilter failed . ret %x . \n", ret);
			return ROC_ERR;
		}
		Rocme_filter[i].bUsed = ROC_TRUE;
		Rocme_filter[i].eType = filter_type;
		rocme_porting_mutex_unlock(g_hDemuxMutex);

		return i;
	}



}


/**************************************************************************
��������: 
            rocme_porting_filter_associate
����˵��: 
            ��ָ����slot��filter����������
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����ɹ� )
    ʧ�� : -1 �� ������ ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_associate(const INT32_T filter_ID,const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_UNF_DMX_FILTER_ATTR_S	stFilterAttr;
	int i = 0;
	HI_S32 ret=0;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}

	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", slot_ID);
		return ROC_ERR;
	}

	rocme_porting_mutex_lock(g_hDemuxMutex);

	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];
	ROCME_DMX_FILTER_ATTR_S	*pFitler = &Rocme_filter[filter_ID];
		
	ret = HI_UNF_DMX_AttachFilter( pFitler->hFilterHandle, pChannel->hChanHandle); 
	if( HI_SUCCESS != ret)
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CreateFilter failed . ret %x . \n", ret);
		return ROC_ERR;
	}
	Rocme_filter[filter_ID].hChanIndex = slot_ID;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
	
}


/**************************************************************************
��������: 
            rocme_porting_filter_disassociate
����˵��: 
            ��ָ����slot��filter�Ͽ���
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��        
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �Ͽ��ɹ� )
    ʧ�� : -1 �� ������ ( �Ͽ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_disassociate(const INT32_T filter_ID,const INT32_T slot_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;

	if(slot_ID < 0 || slot_ID >= ROCME_DMX_CHANNEL_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid channel %x .\n", slot_ID);
		return ROC_ERR;
	}

	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", slot_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	ROCME_DMX_CHANNEL_ATTR_S *pChannel = &rocme_channel[slot_ID];
	ROCME_DMX_FILTER_ATTR_S	*pFitler = &Rocme_filter[filter_ID];

	
	ret = HI_UNF_DMX_DetachFilter( pFitler->hFilterHandle, pChannel->hChanHandle);
	if( HI_SUCCESS != ret)
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_CreateFilter failed . ret %x . \n", ret);
		return ROC_ERR;
	}
	
	Rocme_filter[filter_ID].hChanIndex = 0xffffffff;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
}


/**************************************************************************
��������: 
            rocme_porting_filter_modify
����˵��: 
            ����filter_ID���޸���Ӧ��filter�豸�Ķ�����������(������cofe��maskֵ)��
        ���磬����TDT������������Ϊ:
        cafe[8]��ֵΪ{0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        mask[8]��ֵΪ{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00}.
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ *cofe      ] : ������������ͷָ��
            [ c_size     ] : ����������������
            [ *mask      ] : ����������������ֵͷָ��
            [ m_size     ] : ����������������ֵ����
    ���������
            
��    �أ� 
    �ɹ� : 0            ( �޸Ķ������������ɹ� )
    ʧ�� : -1 �� ������ ( �޸Ķ�����������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_modify(const INT32_T filter_ID,
                                    const UINT8_T*cofe,const UINT8_T c_size,
                                    const UINT8_T*mask,const UINT8_T m_size,
                                    const UINT8_T*nega,const UINT8_T m_nega)
{
ROCME_TEST_PRINT
	
	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", filter_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	memcpy(Rocme_filter[filter_ID].au8Coef,cofe,c_size);
	memcpy(Rocme_filter[filter_ID].au8Mask,mask,m_size);
	
	Rocme_filter[filter_ID].s32Wide = ROCME_DMX_FILTER_DEPTH;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;



}


/**************************************************************************
��������: 
            rocme_porting_filter_start
����˵��: 
            ����filter_ID������һ��filter�豸��ʼ������
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( filter�豸�����ɹ� )
    ʧ�� : -1 �� ������ ( filter�豸����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_start(const INT32_T filter_ID)
{
ROCME_TEST_PRINT
	HI_S32 i;
	HI_S32 ret=0;

	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;
	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", filter_ID);
		return ROC_ERR;
	}
		/* FILTER ����*/

	rocme_porting_mutex_lock(g_hDemuxMutex);
	memset(stFilterAttr.au8Match, 0x00, ROCME_DMX_FILTER_DEPTH);
	memset(stFilterAttr.au8Mask, 0xff, ROCME_DMX_FILTER_DEPTH);
	memset(stFilterAttr.au8Negate, 0x00, ROCME_DMX_FILTER_DEPTH);

	for ( i=0; i<Rocme_filter[filter_ID].s32Wide; i++ )
	{
		stFilterAttr.au8Match[i] = Rocme_filter[filter_ID].au8Coef[i];
		stFilterAttr.au8Mask[i] = ~Rocme_filter[filter_ID].au8Mask[i];
		stFilterAttr.au8Negate[i] = Rocme_filter[filter_ID].au8Excl[i];

	}

	stFilterAttr.u32FilterDepth = Rocme_filter[filter_ID].s32Wide;

	ret = HI_UNF_DMX_SetFilterAttr(Rocme_filter[filter_ID].hFilterHandle, &stFilterAttr);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_SetFilterAttr failed, filter  %x(%x) , ret %x . \n", 
						filter_ID, Rocme_filter[filter_ID].hFilterHandle, ret);
		return ROC_ERR;
	}
	else
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		return ROC_OK;
	}

}


/**************************************************************************
��������: 
            rocme_porting_filter_stop
����˵��: 
            ����filter_ID��ֹͣһ��filter�豸�Ĺ�����
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( filter�豸ֹͣ�ɹ� )
    ʧ�� : -1 �� ������ ( filter�豸ֹͣʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_stop(const INT32_T filter_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	memset(&stFilterAttr,0,sizeof(HI_UNF_DMX_FILTER_ATTR_S));
	ret = HI_UNF_DMX_SetFilterAttr(Rocme_filter[filter_ID].hFilterHandle, &stFilterAttr);
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_SetFilterAttr failed, filter  %x(%x) , ret %x . \n", 
						filter_ID, Rocme_filter[filter_ID].hFilterHandle, ret);
		return ROC_ERR;
	}
	else
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		return ROC_OK;
	}

}


/**************************************************************************
��������: 
            rocme_porting_filter_free
����˵��: 
            �ͷŵ���һ��fitler�豸�Ŀ���Ȩ��
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �ͷųɹ� )
    ʧ�� : -1 �� ������ ( �ͷ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_free(const INT32_T filter_ID)
{
ROCME_TEST_PRINT
	HI_S32 ret=0;

	if(filter_ID < 0 || filter_ID >= ROCME_DMX_FILTER_NUM)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "invalid filter %x .\n", filter_ID);
		return ROC_ERR;
	}
	rocme_porting_mutex_lock(g_hDemuxMutex);
	ret = HI_UNF_DMX_DestroyFilter( (HI_U32)Rocme_filter[filter_ID].hFilterHandle );
	if( HI_SUCCESS != ret )
	{
		rocme_porting_mutex_unlock(g_hDemuxMutex);
		ROCME_PRINTF(ROCME_LOG_ERROR, "HI_UNF_DMX_DestroyFilter failed .  , filter %x , ret %x. \n", 
			filter_ID, ret);
		return ROC_ERR;
	}

	Rocme_filter[filter_ID].bUsed = ROC_FALSE;
	Rocme_filter[filter_ID].hFilterHandle = 0xffffffff;
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return ROC_OK;
	
}

#endif

#include "rocme_porting_osp.h"
#include "rocme_porting_demux.h"
#include "hi_unf_demux.h"



#define ROCME_DEMUX_SUCCESS (0)
#define ROCME_DEMUX_FAILURE (-1)
#define ROCME_DEMUX_PRINT rocme_porting_dprintf
#define ROCME_DEMUX_DEFAULT_ID (0)

#define DEFAULT_DVB_PORT 0


struct stListDemuxHandle
{
	HI_HANDLE hDemuxChannelHandle;
	struct stListDemuxHandle *pNext;
};


struct stListDemuxBufInfo
{
	HI_HANDLE hChannel;
	HI_UNF_DMX_DATA_S stDataBuf;
	struct stListDemuxBufInfo *pNext;
};

typedef struct FilterInfo
{
	HI_HANDLE hFilter;
	HI_U8 au8Match[DMX_FILTER_MAX_DEPTH];
	HI_U8 au8Mask[DMX_FILTER_MAX_DEPTH];
	struct FilterInfo* pstNext;
}FilterInfo_t;

static UINT32_T g_hDemuxMutex = 0;
static ROC_BOOL g_hDemuxInit = ROC_FALSE;
static struct stListDemuxHandle *g_pstDemuxHandleList = NULL;
static struct stListDemuxBufInfo *g_pstDemuxBufInfoList = NULL; 
static FilterInfo_t* g_pstFilterInfo = NULL;

//static HI_HANDLE g_DemuxChannelHandle[DMX_TOTALCHAN_CNT];

#define FindNodeFromLinkList(name,member,thisNode,linkList)\
{\
	name##Info_t* pstHeadNode= linkList;\
	name##Info_t* pstCurNode = pstHeadNode;\
	name##Info_t* pstPreNode = pstCurNode;\
	while(pstCurNode!=NULL)\
	{\
		if(pstCurNode->h##name == member) break;\
		pstPreNode = pstCurNode;\
		pstCurNode = pstCurNode->pstNext;\
	}\
	if(pstCurNode!=NULL) {thisNode = pstCurNode;}\
	else {thisNode = NULL;ROCME_DEMUX_PRINT("fun=%s.line=%d.%s not found.this may be an err.\n",__FUNCTION__,__LINE__,#name);}\
}

#define AddNode2LinkList(name,node,linkList)\
{\
	name##Info_t* pstThisNode=(name##Info_t*)node;\
	if(linkList == NULL) {linkList = pstThisNode;}\
	else {pstThisNode->pstNext=linkList->pstNext; linkList->pstNext=pstThisNode;}\
}

#define DelNodeFromLinkList(name,node,linkList)\
{\
	name##Info_t* pstThisNode=(name##Info_t*)node;\
	name##Info_t* pstCurNode = linkList;\
	name##Info_t* pstPreNode = pstCurNode;\
	while(pstCurNode!=NULL)\
	{\
		if(pstCurNode == pstThisNode) break;\
		pstPreNode = pstCurNode;\
		pstCurNode = pstCurNode->pstNext;\
	}\
	if(pstCurNode != pstThisNode) {ROCME_DEMUX_PRINT("Error happens.in fun=%s.line=%d.\n",__FUNCTION__,__LINE__);}\
	else\
	{\
		if(pstCurNode==linkList) {linkList = pstCurNode->pstNext;}\
		else {pstPreNode->pstNext = pstCurNode->pstNext;}\
		free(pstCurNode);\
	}\
}


/**************************************************************************
��������: 
            rocme_porting_demux_init
����˵��: 
            DEMUX���ܳ�ʼ�����м����������ʱ���ô˺��������������м��֮ǰ
        �������Ѿ�������DEMUX�ĳ�ʼ�����˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
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
INT32_T rocme_porting_demux_init(void)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	do
	{
		if (g_hDemuxInit)
		{
			ROCME_DEMUX_PRINT("[%s]demux has inited\n", __FUNCTION__);
			nRet = ROCME_DEMUX_SUCCESS;
			break;
		}
		
		if (g_hDemuxMutex == 0)
		{
			g_hDemuxMutex  = rocme_porting_mutex_create(ROC_MUTEX_RECURSIVE_NP);
			if (g_hDemuxMutex == 0)
			{
				ROCME_DEMUX_PRINT("[%s]mutex create failed\n", __FUNCTION__);
				nRet = ROCME_DEMUX_FAILURE;
				break;
			}
		}
		
		nRet = HI_UNF_DMX_Init();
		if (nRet != HI_SUCCESS)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_Init errorcode = %d\n", __FUNCTION__, nRet);
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}
		
		nRet = HI_UNF_DMX_AttachTSPort(0,DEFAULT_DVB_PORT);
		if (HI_SUCCESS != nRet)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_Init errorcode = %d\n", __FUNCTION__, nRet);
			nRet = ROCME_DEMUX_FAILURE;
			break;

		}


		g_hDemuxInit = ROC_TRUE;

		ROCME_DEMUX_PRINT("[%s]demux init success\n", __FUNCTION__);
		nRet = ROCME_DEMUX_SUCCESS;
	}while (0);

	return nRet;
}



/**************************************************************************
��������: 
            rocme_porting_demux_term
����˵��: 
            ж��DEMUX���ܡ�Ŀǰ�˺�������ʵ��Ϊ�ա�
����˵����
    ���������
            void
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ж�سɹ� )
    ʧ�� : -1 �� ������ ( ж��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_demux_term(void)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		if (HI_UNF_DMX_DeInit() != HI_SUCCESS)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_DeInit errorcode = %d\n", __FUNCTION__, nRet);
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}
		
		//memset(g_DemuxChannelHandle, 0, sizeof(g_DemuxChannelHandle));
		nRet = ROCME_DEMUX_SUCCESS;
	}while (0);
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	if (nRet == ROCME_DEMUX_SUCCESS)
	{
		rocme_porting_mutex_destroy(g_hDemuxMutex);
		g_hDemuxMutex = 0;
		g_hDemuxInit = ROC_FALSE;
	}

	return nRet;
}



/**************************************************************************
��������: 
            rocme_porting_slot_query_PID
����˵��: 
            ָ������ͨ���ϣ���ѯһ��PID�Ƿ��Ѿ���ĳ��slot(�����м��ʹ�õ�
        slot���м��֮���slot)ռ�ã���ƽ̨��֧��slot��PID�趨�����ظ�����
        ���ܱ���ʵ�֡�
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ pid           ] : ��Ҫ��ѯ��PIDֵ
    ���������
            
��    �أ� 
    ��PIDδ��ռ�� :  0
    ��PID�ѱ�ռ�� : -1
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_query_PID(const INT32_T channel_index,const UINT16_T pid)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	HI_HANDLE hChannel;

	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		if (channel_index != ROCME_DEMUX_DEFAULT_ID)
		{
			ROCME_DEMUX_PRINT("[%s]channel_index=%d is invaild\n",__FUNCTION__, channel_index);
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}
		
		nRet = HI_UNF_DMX_GetChannelHandle(channel_index, (unsigned int)pid, &hChannel);

		if ((nRet == HI_SUCCESS) && (hChannel != NULL))
		{
			ROCME_DEMUX_PRINT("[%s]pid =0x%xis not free\n",__FUNCTION__, pid);
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}	

		nRet = ROCME_DEMUX_SUCCESS;
		ROCME_DEMUX_PRINT("[%s]pid=0x%x is free\n",__FUNCTION__, pid);
	}while (0);

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}



static HI_UNF_DMX_CHAN_TYPE_E DemuxGetChannelType(const Roc_Slot_Type_e slot_type)
{
	HI_UNF_DMX_CHAN_TYPE_E eChannelType = HI_UNF_DMX_CHAN_TYPE_BUTT;
	
	switch (slot_type)
	{
		case ROC_SLOT_TYPE_SECTION:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_SEC;
			break;

		case ROC_SLOT_TYPE_PES:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_PES;
			break;
			
		case ROC_SLOT_TYPE_RAW:
			eChannelType = HI_UNF_DMX_CHAN_TYPE_POST;
			break;

		default:
			break;	
	}

	return eChannelType;
}


static void addBufInfoList(struct stListDemuxBufInfo **pListHead, HI_HANDLE hChannel, HI_UNF_DMX_DATA_S stDataBuf)
{
	struct stListDemuxBufInfo *head = *pListHead;
	struct stListDemuxBufInfo *current = NULL;

	current = (struct stListDemuxBufInfo *)rocme_porting_malloc(sizeof(struct stListDemuxBufInfo));
	current->hChannel = hChannel;
	memcpy(&current->stDataBuf, &stDataBuf, sizeof(HI_UNF_DMX_DATA_S));
	current->pNext = NULL;

	/*�������Ϊ������*/
	if (head == NULL)
	{
		*pListHead = current;
	}
	else
	{
		while(head->pNext != NULL)
		{
			head = head->pNext;
		}
		head->pNext = current;
	}

	return;
}


static void delBufInfoList(struct stListDemuxBufInfo **pListHead, HI_HANDLE hChannel, HI_U8 * pu8Buf)
{
	struct stListDemuxBufInfo *head = *pListHead;
	struct stListDemuxBufInfo *pLast, *pNext;

	pLast = head;
	pNext = NULL;

	while (head != NULL)
	{
		if ((head->hChannel == hChannel) && ((head->stDataBuf.pu8Data == pu8Buf ) || (pu8Buf == NULL)))
		{
			pNext = head->pNext;
			
			/*���Ҫɾ���Ľڵ�Ϊͷ���*/
			if (head == *pListHead)
			{
				*pListHead = pNext;
			}
			else
			{
				pLast->pNext = pNext;
			}
			//rocme_porting_dprintf("[%s]head->hChannel=%d, head->stDataBuf->pu8Buf=0x%x\n",__FUNCTION__, head->hChannel, head->stDataBuf.pu8Buf);
			rocme_porting_free(head);
			
			if (pu8Buf == NULL)
			{
				head = *pListHead;
				continue;
			}
			else
			{
				break;
			}
		}

		pLast = head;
		head = head->pNext;
	}

	return;
}



static void addChannelList(struct stListDemuxHandle **pListHead, HI_HANDLE hChannelID)
{
	struct stListDemuxHandle *current = NULL;
	struct stListDemuxHandle *head = NULL;
	
	/*���ӽڵ�*/
	current = (struct stListDemuxHandle *)rocme_porting_malloc(sizeof(struct stListDemuxHandle));
	current->hDemuxChannelHandle = hChannelID;
	current->pNext = NULL;
	head = *pListHead;
	
	/*�������Ϊ������*/
	if (head == NULL)
	{
		*pListHead = current;
	}
	else
	{
		while (head->pNext != NULL)
		{
			head = head->pNext;
		}
		/*�ҵ�һ������β*/
		head->pNext = current;
	}

	return;
}



static void delChannelList(struct stListDemuxHandle **pListHead, HI_HANDLE hChannelID)
{
	struct stListDemuxHandle *head = *pListHead;
	struct stListDemuxHandle *pLast, *pNext;

	pLast = head;
	pNext = NULL;
	while (head != NULL)
	{
		/*�ҵ�Ҫɾ���Ľڵ�*/
		if (head->hDemuxChannelHandle == hChannelID)
		{
			pNext = head->pNext;
			rocme_porting_free(head);
			/*ɾ���Ľڵ�Ϊͷ���*/
			if (head == *pListHead)
			{
				*pListHead = pNext;
			}
			else
			{
				pLast->pNext = pNext;
			}
			
			break;
		}

		pLast = head;
		head = head->pNext;
	}

	return;
}


/**************************************************************************
��������: 
            rocme_porting_slot_alloc
����˵��: 
            ��ָ��������ͨ�����������һ��slot(ָ��slot�����͡�buff�Ĵ�С)��
        ���ɹ����뵽slot������һ��slot�Ŀ���ID���м����öԴ�slot�Ŀ���Ȩ��
        ��ͨ����ID�Դ�slot�豸�����޸ġ��������ͷŵȾ��������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ slot_type     ] : slot�����ͣ���������:
                                ROC_SLOT_TYPE_NULL     -  used with inject carousel 
                            packet only flag
                                ROC_SLOT_TYPE_SECTION  -  for section data - Signal 
                            every section
                                ROC_SLOT_TYPE_PES      -  signal every complete PES
                            packet except when signal_on_every_transport_packet is 
                            supplied as a flag
                                ROC_SLOT_TYPE_RAW      -  Raw transport packets, si-
                            -gnalled every packet
                                ROC_SLOT_TYPE_PCR      -  specifies that the data c-
                            -ollected on this slot is collected for PCR gathering purposes
                                ROC_SLOT_TYPE_RESERVE  -  ��չ����
             [ buff_size    ] : ��Ҫ���ٵ�slotʹ�õ�buff�Ĵ�С���м������������⣬
                            ������64KB��
    ���������
            ��
��    �أ� 
    �ɹ� : ���뵽��slot����ID ( ����ɹ� )
    ʧ�� : -1 �� ������       ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_alloc(const INT32_T channel_index,const Roc_Slot_Type_e slot_type,const INT32_T buff_size)
{
	INT32_T nRet = 0;
	HI_UNF_DMX_CHAN_ATTR_S stChanAttr;
	INT32_T nSlotID = ROCME_DEMUX_FAILURE;
	HI_HANDLE hChannelID;
	struct stListDemuxHandle *head, *current;
	

	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		nRet = HI_UNF_DMX_GetChannelDefaultAttr(&stChanAttr);
		if (nRet != HI_SUCCESS)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_GetChannelDefaultAttr failed errorcode =%d\n", __FUNCTION__, nRet);
			nSlotID = ROCME_DEMUX_FAILURE;
			break;
		}
		
		stChanAttr.enChannelType = DemuxGetChannelType(slot_type);
		if (stChanAttr.enChannelType == HI_UNF_DMX_CHAN_TYPE_SEC)
		{
			stChanAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_DISCARD; 
		}
		else
		{
			stChanAttr.enCRCMode = HI_UNF_DMX_CHAN_CRC_MODE_FORBID; 
		}

		stChanAttr.u32BufSize = buff_size;

		nRet = HI_UNF_DMX_CreateChannel(ROCME_DEMUX_DEFAULT_ID, &stChanAttr,&hChannelID);
		if (nRet != HI_SUCCESS)
		{
			ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_CreateChannel failed errorcode=%d\n", __FUNCTION__, nRet);
			nSlotID = ROCME_DEMUX_FAILURE;
			break;
		}

		nSlotID = hChannelID;

		addChannelList(&g_pstDemuxHandleList, nSlotID);
    }while(0);

    rocme_porting_mutex_unlock(g_hDemuxMutex);

    return nSlotID;
}




/**************************************************************************
��������: 
            rocme_porting_slot_modify
����˵��: 
            ����slot_ID���޸���Ӧ��slot�豸��һ����������(������PIDֵ)��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ pid        ] : ��Ҫ���õ�һ����������ֵ
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �޸�slotһ�����������ɹ� )
    ʧ�� : -1 �� ������ ( �޸�slotһ����������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_modify(const INT32_T slot_ID,const UINT16_T pid)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

    if(HI_UNF_DMX_CloseChannel(slot_ID) == HI_SUCCESS)
    {
        nRet = ROCME_DEMUX_SUCCESS;
    }
    if (HI_UNF_DMX_SetChannelPID(slot_ID, pid) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    }
    else
    {
        nRet = ROCME_DEMUX_FAILURE;
        ROCME_DEMUX_PRINT("[%s] failed \n", __FUNCTION__);
    }
    
    rocme_porting_mutex_unlock(g_hDemuxMutex);

    return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_slot_clear
����˵��: 
            ����slot_ID����������õ�һ����������(�������PIDֵ)��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���slot���������ɹ� )
    ʧ�� : -1 �� ������ ( ���slot��������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_clear(const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

    HI_UNF_DMX_CloseChannel(slot_ID);
    if(HI_UNF_DMX_SetChannelPID(slot_ID, 0x1fff) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    }

    rocme_porting_mutex_unlock(g_hDemuxMutex);
    return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_slot_start
����˵��: 
            ����һ��slot�豸��ʼ�������ݣ�����ײ�ƽ̨��slot�豸�޴����õ�ʵ�֣�
        ��˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����slot�豸�ɹ� )
    ʧ�� : -1 �� ������ ( ����slot�豸ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_start(const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(HI_UNF_DMX_OpenChannel(slot_ID) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    }
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_slot_stop
����˵��: 
            ֹͣһ��slot�豸�������ݣ�����ײ�ƽ̨��slot�豸�޴����õ�ʵ�֣�
        ��˺�������ʵ��Ϊ�գ�ֱ�ӷ���0��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ֹͣslot�豸�ɹ� )
    ʧ�� : -1 �� ������ ( ֹͣslot�豸ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_stop(const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(HI_UNF_DMX_CloseChannel(slot_ID) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    }
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}
/**************************************************************************
��������: 
            rocme_porting_slot_free
����˵��: 
            �ͷŵ���һ��ָ��slot�Ŀ���Ȩ��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �ͷųɹ� )
    ʧ�� : -1 �� ������ ( �ͷ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_free(const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	if(HI_UNF_DMX_DestroyChannel(slot_ID) == HI_SUCCESS)
    {
    	nRet = ROCME_DEMUX_SUCCESS;
    	delBufInfoList(&g_pstDemuxBufInfoList, slot_ID, NULL);
    	delChannelList(&g_pstDemuxHandleList, slot_ID);
    }
    
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_slot_buff_wait
����˵��: 
            ָ������ͨ���������м��ͨ���˷���������ѯ�Ƿ���slot���˵����ݣ�
        ���ҿ������õȴ���ʱʱ�ޣ���������ͨ���Ϲ��˵������ݣ��򷵻ع��˵�
        �����ݵ�slot����ID��
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ time_out_ms   ] : ��ʱʱ�䣬��λΪ����(ms)
    ���������
            
��    �أ� 
    �ɹ� : slot����ID   ( �ɹ���ѯ����slot���˵����� )
    ʧ�� : -1 �� ������ ( ��ѯʧ��/slot��time_out_msʱ����δ���˵����� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_wait(const INT32_T channel_index,const INT32_T time_out_ms)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	HI_HANDLE hChannel = 0;
	HI_U32 u32AcquireNum = 1;
	HI_U32 u32ReadNum;
	struct stListDemuxHandle *head = g_pstDemuxHandleList;
	HI_UNF_DMX_DATA_S stBuf;

	rocme_porting_mutex_lock(g_hDemuxMutex);
	while (head != NULL)
	{
		hChannel = head->hDemuxChannelHandle;
		
		if(HI_UNF_DMX_AcquireBuf(hChannel, u32AcquireNum,&u32ReadNum, &stBuf,0)== HI_SUCCESS)
		{
			nRet = hChannel;
			addBufInfoList(&g_pstDemuxBufInfoList, hChannel, stBuf);
			break;
		}

		head = head->pNext;
	}
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}


static ROC_BOOL CheckHandleValid(HI_HANDLE hChannel, HI_HANDLE *phGetChannel, int nNum)
{
	int ii;
	ROC_BOOL bRet = ROC_FALSE;

	for (ii=0; ii<nNum; ii++)
	{
		if (phGetChannel[ii] == hChannel)
		{
			bRet = ROC_TRUE;
			break;
		}
	}

	return bRet;
}


INT32_T rocme_porting_slot_buff_wait_multi(const INT32_T channel_index, INT32_T *slot_ID_ar, INT32_T *count , const INT32_T time_out_ms)
{
#if 0
	*slot_ID_ar = rocme_porting_slot_buff_wait(channel_index,time_out_ms);
	if(ROCME_DEMUX_FAILURE!=*slot_ID_ar)
	{
		*count = 1;
		return ROC_OK;
	}
    Sleep(20);
	return ROC_ERR;
#else
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	HI_HANDLE hChannel = 0;
	HI_U32 u32AcquireNum = 1;
	HI_U32 u32ReadNum;
	HI_HANDLE hGetChannel[32];
	UINT32_T u32ChNum = 0;
	struct stListDemuxHandle *head = NULL;
	HI_UNF_DMX_DATA_S stBuf;
	int nSlotIndex = 0;


	if ((slot_ID_ar == NULL) || (count == NULL) || (*count <= 0))
	{
		return ROCME_DEMUX_FAILURE;
	}


	u32ChNum = sizeof(hGetChannel)/sizeof(HI_HANDLE);
    nRet = HI_UNF_DMX_GetDataHandle(hGetChannel, &u32ChNum, 100);
	if (nRet != HI_SUCCESS)
	{
		//rocme_porting_dprintf("[%s]exit, nRet=[0x%x]\n", __FUNCTION__, nRet);
		return ROCME_DEMUX_FAILURE;
	}

	rocme_porting_mutex_lock(g_hDemuxMutex);
	head = g_pstDemuxHandleList;
	//rocme_porting_mutex_unlock(g_hDemuxMutex);
	
	while (head != NULL)
	{
		hChannel = head->hDemuxChannelHandle;
		if (!CheckHandleValid(hChannel, hGetChannel, u32ChNum))
		{
			head = head->pNext;
			continue;
		}

        nRet = HI_UNF_DMX_AcquireBuf(hChannel, u32AcquireNum,&u32ReadNum, &stBuf,100);
		
		if(nRet == HI_SUCCESS)
		{
            rocme_porting_dprintf("rocme_porting_slot_buff_wait_multi: addBufInfoList [0x%x] \n", u32ReadNum);
			if (nSlotIndex < *count)
			{
				slot_ID_ar[nSlotIndex] = hChannel;
				nSlotIndex++;
			}
			else
			{
				break;
			}
		//	rocme_porting_mutex_lock(g_hDemuxMutex);
			addBufInfoList(&g_pstDemuxBufInfoList, hChannel, stBuf);
		//	rocme_porting_mutex_unlock(g_hDemuxMutex);
		}
        else
        {
            rocme_porting_dprintf("HI_UNF_DMX_AcquireBuf Fail. nRet=[0x%x]!\n", nRet);
        }

		head = head->pNext;
	}

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	if (nSlotIndex > 0)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}
	*count = nSlotIndex;

	//rocme_porting_dprintf("[%s]exit\n", __FUNCTION__);
	return nRet;
#endif
}

/**************************************************************************
��������: 
            rocme_porting_slot_buff_get
����˵��: 
            ��ָ��slot��buff�еĸ���(��ȡ)��ָ�����ȵ����ݣ��м��ֻ���ڵ���
        ��rocme_porting_slot_buff_wait�󣬲Ż�ʹ�ô˺����жϹ��˵����ݵĹ�����
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ *buff_ptr  ] : �洢��ȡ�������ݵ�buff��ͷָ��
            [ buff_size  ] : ��Ҫ��ȡ�����ݵĳ��ȣ����洢buff�ĳ���
    ���������
            [ *data_size ] : ʵ����ȡ�������ݵĳ���
��    �أ� 
    �ɹ� : 0            ( ��ȡ���ݳɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_get(const INT32_T slot_ID, UINT8_T *buff_ptr, const UINT32_T buff_size, UINT32_T *data_size)
{
	struct stListDemuxBufInfo *head = g_pstDemuxBufInfoList;
	INT32_T nRet = ROCME_DEMUX_FAILURE;

	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		if ((buff_ptr == NULL) || (buff_size == 0) ||(data_size == NULL))
		{
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}

		while (head != NULL)
		{
			if (head->hChannel == slot_ID)
			{
				*data_size = head->stDataBuf.u32Size > buff_size ? buff_size : head->stDataBuf.u32Size;
				memcpy(buff_ptr, head->stDataBuf.pu8Data, *data_size);
				nRet = ROCME_DEMUX_SUCCESS;
				break;
			}
			
			head = head->pNext;
		}
	}while (0);
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}



/**************************************************************************
��������: 
            rocme_porting_slot_buff_read
����˵��: 
            ��ָ����slot��buff�ж�ȡ���ݣ���ȡ���ݺ�Ҫ�����buff���м����
        Ҫ��slot��buff�е����ݶ���2��buff�У��ֱ���data0��data1����ȡ����ʱ
        ���Ƚ����ݶ���data0�У���data0�������ٽ����ݶ�ȡ��data1�У����ռ䲻
        ��ʱ�����ض�ȡʧ�ܡ�
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
            [ *p_data0   ] : �洢������0��ͷָ��
            [ size0      ] : �洢������0�ĳ���
            [ *p_data1   ] : �洢������1��ͷָ��
            [ size1      ] : �洢������1�ĳ���
    ���������
            [ *datasize  ] : ʵ�ʶ�ȡ�������ݳ���
��    �أ� 
    �ɹ� : 0            ( ��ȡ���ݳɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_read(const INT32_T slot_ID, UINT8_T *p_data0, UINT32_T size0, UINT8_T *p_data1, UINT32_T size1, UINT32_T *datasize)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	struct stListDemuxBufInfo *head = g_pstDemuxBufInfoList;
	UINT32_T unData0ReadSize = 0;
	UINT32_T unReadSize = 0;
	UINT32_T unLeftSize = 0;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

	do
	{
		if ((p_data0 == NULL) || (datasize == NULL))
		{	
			nRet = ROCME_DEMUX_FAILURE;
			break;
		}

		while (head != NULL)
		{
			if (head->hChannel == slot_ID)
			{
				*datasize = 0;
				if (head->stDataBuf.u32Size > (size0+size1))
				{
					ROCME_DEMUX_PRINT("[%s]head->stDataBuf.u32Size=%d, (size0+size1)=%d\n", 
					__FUNCTION__, head->stDataBuf.u32Size, (size0+size1));
					nRet = ROCME_DEMUX_FAILURE;
					break;
				}
				unReadSize = head->stDataBuf.u32Size > size0 ? size0 : head->stDataBuf.u32Size;
				unData0ReadSize = unReadSize;
				memcpy(p_data0, head->stDataBuf.pu8Data, unReadSize);
				*datasize += unReadSize;
				unLeftSize = head->stDataBuf.u32Size - unReadSize;
				unReadSize = unLeftSize > size1? size1:unLeftSize;
				if ((unReadSize > 0) && (p_data1 != NULL))
				{
					memcpy(p_data1, head->stDataBuf.pu8Data+unData0ReadSize, unReadSize);
					*datasize += unReadSize;
				}

				if (*datasize != head->stDataBuf.u32Size)
				{
					nRet = ROCME_DEMUX_FAILURE;
					break;
				}
				/*�ͷ�buf, ɾ���ڵ�*/
				HI_UNF_DMX_ReleaseBuf(slot_ID, 1,&head->stDataBuf);
				delBufInfoList(&g_pstDemuxBufInfoList, slot_ID, head->stDataBuf.pu8Data);
				
				nRet = ROCME_DEMUX_SUCCESS;
				break;
			}
			
			head = head->pNext;
		}
		
	}while (0);

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
	
}

/**************************************************************************
��������: 
            rocme_porting_slot_buff_flush
����˵��: 
            ���ָ����slot��buff��
����˵����
    ���������
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���ָ��slot��buff�ɹ� )
    ʧ�� : -1 �� ������ ( ���ָ��slot��buffʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_slot_buff_flush(const INT32_T slot_ID)
{
    //ROCME_DEMUX_PRINT("[%s]not supported yet\n", __FUNCTION__);
    return 0;
}

/**************************************************************************
��������: 
            rocme_porting_filter_alloc
����˵��: 
            ��ָ��������ͨ�����������һ��filter(ָ��filter������)�����ɹ���
        �뵽filter������һ��filter�Ŀ���ID���м����öԴ�filter�Ŀ���Ȩ����
        ͨ����ID�Դ�filter�豸�����޸ġ��������ͷŵȾ��������
����˵����
    ���������
            [ channel_index ] : ����ͨ������ֵ
            [ filter_type   ] : filter�����ͣ���������:
                                ROC_FILTER_TYPE_SECTION       -  Provides 8 byte filter/mask
                                ROC_FILTER_TYPE_PES           -  Filter PES
                                ROC_FILTER_TYPE_TSHEADER      -  Filter TSHeader
                                ROC_FILTER_TYPE_PES_STREAMID  -  Filter PES stream ID
                                ROC_FILTER_TYPE_NEG_MATCH     -  Negative Match Mode filtering
                                ROC_FILTER_TYPE_RESERVE       -  ��չ����
    ���������
            ��
��    �أ� 
    �ɹ� : ���뵽��filter����ID ( ����ɹ� )
    ʧ�� : -1 �� ������         ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_alloc(const INT32_T channel_index,const Roc_Filter_Type_e filter_type)
{
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;
	HI_HANDLE hFilter;
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	FilterInfo_t* pstNewFilter = NULL;
	
	//rocme_porting_mutex_lock(g_hDemuxMutex);

	//memset(&stFilterAttr,0,sizeof(HI_UNF_DMX_FILTER_ATTR_S));
	stFilterAttr.u32FilterDepth = 0;
	memset(&stFilterAttr.au8Match,0,sizeof(stFilterAttr.au8Match));
	memset(&stFilterAttr.au8Mask,0,sizeof(stFilterAttr.au8Mask));
	memset(&stFilterAttr.au8Negate,0,sizeof(stFilterAttr.au8Negate));

	nRet = HI_UNF_DMX_CreateFilter(ROCME_DEMUX_DEFAULT_ID, &stFilterAttr, &hFilter);
	if (nRet != HI_SUCCESS)
	{
		ROCME_DEMUX_PRINT("[%s]HI_UNF_DMX_CreateFilter failed.err=%#x.\n", __FUNCTION__,nRet);
		nRet = ROCME_DEMUX_FAILURE;
	}
	else
	{
		nRet = hFilter;
	}

	pstNewFilter = malloc(sizeof(FilterInfo_t));
	if(pstNewFilter == NULL)
	{
		ROCME_DEMUX_PRINT("Error happens.in fun=%s.line=%d.\n",__FUNCTION__,__LINE__);
		nRet = ROCME_DEMUX_FAILURE;
	}
	else
	{
		memset(pstNewFilter,0,sizeof(FilterInfo_t));
		pstNewFilter->hFilter = hFilter;
		AddNode2LinkList(Filter,pstNewFilter,g_pstFilterInfo);
		ROCME_DEMUX_PRINT("fun=%s.line=%d.g_pstFilterInfo=%#x.\n",__FUNCTION__,__LINE__,g_pstFilterInfo);
	}

	//rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_filter_associate
����˵��: 
            ��ָ����slot��filter����������
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �����ɹ� )
    ʧ�� : -1 �� ������ ( ����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_associate(const INT32_T filter_ID,const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if (HI_UNF_DMX_AttachFilter(filter_ID, slot_ID) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}	

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_filter_disassociate
����˵��: 
            ��ָ����slot��filter�Ͽ���
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ slot_ID    ] : slot�豸�Ŀ���ID����rocme_porting_slot_alloc��ȡ��        
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �Ͽ��ɹ� )
    ʧ�� : -1 �� ������ ( �Ͽ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_disassociate(const INT32_T filter_ID,const INT32_T slot_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if (HI_UNF_DMX_DetachFilter(filter_ID, slot_ID) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_filter_modify
����˵��: 
            ����filter_ID���޸���Ӧ��filter�豸�Ķ�����������(������cofe��maskֵ)��
        ���磬����TDT������������Ϊ:
        cafe[8]��ֵΪ{0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        mask[8]��ֵΪ{0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00}.
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
            [ *cofe      ] : ������������ͷָ��
            [ c_size     ] : ����������������
            [ *mask      ] : ����������������ֵͷָ��
            [ m_size     ] : ����������������ֵ����
    ���������
            
��    �أ� 
    �ɹ� : 0            ( �޸Ķ������������ɹ� )
    ʧ�� : -1 �� ������ ( �޸Ķ�����������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_modify(const INT32_T filter_ID,
                                    const UINT8_T*cofe,const UINT8_T c_size,
                                    const UINT8_T*mask,const UINT8_T m_size,
                                    const UINT8_T*nega,const UINT8_T m_nega)
{
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr ;
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	UINT8_T tmpmask[DMX_FILTER_MAX_DEPTH];
	UINT8_T tmpnega[DMX_FILTER_MAX_DEPTH];
	int ii;
	FilterInfo_t* pstFilter;

	//ROCME_DEMUX_PRINT("fun=%s.line=%d.\n",__FUNCTION__,__LINE__);

	if ((cofe==NULL) || (mask == NULL) || (c_size == 0) ||(m_size == NULL))
	{
		return ROCME_DEMUX_FAILURE;
	}

	if ((c_size > DMX_FILTER_MAX_DEPTH) || (m_size > DMX_FILTER_MAX_DEPTH))
	{
		ROCME_DEMUX_PRINT("[%s]max size is %d \n", __FUNCTION__, DMX_FILTER_MAX_DEPTH);
		return ROCME_DEMUX_FAILURE;
	}
	
	rocme_porting_mutex_lock(g_hDemuxMutex);

	for (ii=0; ii<m_size; ii++)
	{
		tmpmask[ii] = ~mask[ii];
	}

	for (ii=0; ii<m_nega; ii++)
	{
		tmpnega[ii] = nega[ii];
	}

	
#if 0	
	memset(&stFilterAttr, 0, sizeof(HI_UNF_DMX_FILTER_ATTR_S));
	stFilterAttr.u32FilterDepth = c_size > m_size ? c_size : m_size;
	memcpy(stFilterAttr.au8Match, cofe, c_size);
	memcpy(stFilterAttr.au8Mask, tmpmask, m_size);
	/*print filter attr.
		int i=0; 
		ROCME_DEMUX_PRINT("fun=%s.line=%d.stFilterAttr.u32FilterDepth=%d.\n", __FUNCTION__,__LINE__,stFilterAttr.u32FilterDepth);
		ROCME_DEMUX_PRINT("math  :");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Match[i]);
		ROCME_DEMUX_PRINT("\nmask  :");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Mask[i]);
		ROCME_DEMUX_PRINT("\nnegate:");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Negate[i]);        
		ROCME_DEMUX_PRINT("\n");*/
	if (HI_UNF_DMX_SetFilterAttr(filter_ID, &stFilterAttr) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}
#else
	FindNodeFromLinkList(Filter,filter_ID,pstFilter,g_pstFilterInfo);
	if(pstFilter!=NULL)
	{
		memcpy(pstFilter->au8Match, cofe, c_size);
		memcpy(pstFilter->au8Mask, tmpmask, m_size);
		nRet = ROCME_DEMUX_SUCCESS;
	}
#endif
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	//ROCME_DEMUX_PRINT("fun=%s.line=%d.\n",__FUNCTION__,__LINE__);

	return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_filter_start
����˵��: 
            ����filter_ID������һ��filter�豸��ʼ������
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( filter�豸�����ɹ� )
    ʧ�� : -1 �� ������ ( filter�豸����ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_start(const INT32_T filter_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	FilterInfo_t* pstFilter;
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr ;

	//ROCME_DEMUX_PRINT("[%s]not supported\n", __FUNCTION__);
	
	FindNodeFromLinkList(Filter,filter_ID,pstFilter,g_pstFilterInfo);
	if(pstFilter != NULL)
	{
		memset(&stFilterAttr, 0, sizeof(HI_UNF_DMX_FILTER_ATTR_S));
		stFilterAttr.u32FilterDepth = 8;//?
		memcpy(stFilterAttr.au8Match, pstFilter->au8Match, 8);
		memcpy(stFilterAttr.au8Mask, pstFilter->au8Mask, 8);

		/*print filter attr.
		int i=0; 
		ROCME_DEMUX_PRINT("fun=%s.line=%d.stFilterAttr.u32FilterDepth=%d.\n", __FUNCTION__,__LINE__,stFilterAttr.u32FilterDepth);
		ROCME_DEMUX_PRINT("math  :");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Match[i]);
		ROCME_DEMUX_PRINT("\nmask  :");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Mask[i]);
		ROCME_DEMUX_PRINT("\nnegate:");
		for(i=0;i<8;i++) ROCME_DEMUX_PRINT("%02x.",stFilterAttr.au8Negate[i]);        
		ROCME_DEMUX_PRINT("\n");*/
		
		if (HI_UNF_DMX_SetFilterAttr(filter_ID, &stFilterAttr) == HI_SUCCESS)
		{
			nRet = ROCME_DEMUX_SUCCESS;
		}
	}
	
	return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_filter_stop
����˵��: 
            ����filter_ID��ֹͣһ��filter�豸�Ĺ�����
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( filter�豸ֹͣ�ɹ� )
    ʧ�� : -1 �� ������ ( filter�豸ֹͣʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_stop(const INT32_T filter_ID)
{
	HI_UNF_DMX_FILTER_ATTR_S stFilterAttr ;
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);
	memset(&stFilterAttr, 0, sizeof(HI_UNF_DMX_FILTER_ATTR_S));
	if (HI_UNF_DMX_SetFilterAttr(filter_ID, &stFilterAttr) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
	}

	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}

/**************************************************************************
��������: 
            rocme_porting_filter_free
����˵��: 
            �ͷŵ���һ��fitler�豸�Ŀ���Ȩ��
����˵����
    ���������
            [ filter_ID  ] : filter�豸�Ŀ���ID����rocme_porting_filter_alloc��ȡ��
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( �ͷųɹ� )
    ʧ�� : -1 �� ������ ( �ͷ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_filter_free(const INT32_T filter_ID)
{
	INT32_T nRet = ROCME_DEMUX_FAILURE;
	FilterInfo_t* pstFilter;
	
	rocme_porting_mutex_lock(g_hDemuxMutex);
	if (HI_UNF_DMX_DestroyFilter(filter_ID) == HI_SUCCESS)
	{
		nRet = ROCME_DEMUX_SUCCESS;
		FindNodeFromLinkList(Filter, filter_ID, pstFilter, g_pstFilterInfo);
		DelNodeFromLinkList(Filter,pstFilter,g_pstFilterInfo)
	}
	
	rocme_porting_mutex_unlock(g_hDemuxMutex);

	return nRet;
}


#if 0/*test code*/

#define TEST_PRINT printf
#define DO_FAIL_PRINT(fun)\
{\
    if(ROC_OK != (fun)) TEST_PRINT("Error happens,in fun=%s.line=%d.\n",__FUNCTION__,__LINE__);\
}

INT32_T testDmxEnter(void)
{
    INT32_T nSlotID;
    INT32_T nFilterID1;
    INT32_T nFilterID2;
    UINT8_T cofe1[8]={0x50, 0x00, 0x00, 0x00, 0x00, 0x00,0x00,0x00};
    UINT8_T mask1[8]={0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    UINT8_T cofe2[8]={0x4e, 0x00, 0x00, 0x00, 0x00, 0x00,0x00,0x00};
    UINT8_T mask2[8]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    char *pData0 = NULL;
    char* pData1 = NULL;
    UINT32_T nDatasize;
    INT32_T nDataSlot;
    
    DO_FAIL_PRINT(testLockTuner(259,2000));

    DO_FAIL_PRINT(rocme_porting_demux_init());

    nSlotID = rocme_porting_slot_alloc(0,ROC_SLOT_TYPE_SECTION,64*1024);
    DO_FAIL_PRINT(nSlotID>0?ROC_OK:ROC_ERR);
    TEST_PRINT("fun=%s.line=%d.nSlotID=%#x.\n",__FUNCTION__,__LINE__,nSlotID);
    
    DO_FAIL_PRINT(rocme_porting_slot_modify(nSlotID, 0x12));    
    
    nFilterID1 = rocme_porting_filter_alloc(0,ROC_FILTER_TYPE_SECTION);
    DO_FAIL_PRINT(nFilterID1>0?ROC_OK:ROC_ERR);
    TEST_PRINT("fun=%s.line=%d.nFilterID1=%#x.\n",__FUNCTION__,__LINE__,nFilterID1);
    nFilterID2 = rocme_porting_filter_alloc(0,ROC_FILTER_TYPE_SECTION);
    DO_FAIL_PRINT(nFilterID2>0?ROC_OK:ROC_ERR);
    TEST_PRINT("fun=%s.line=%d.nFilterID2=%#x.\n",__FUNCTION__,__LINE__,nFilterID2);

    DO_FAIL_PRINT(rocme_porting_filter_associate(nFilterID1,nSlotID));                
    DO_FAIL_PRINT(rocme_porting_filter_associate(nFilterID2,nSlotID));
    TEST_PRINT("fun=%s.line=%d.filter associate ok.\n",__FUNCTION__,__LINE__);	

    DO_FAIL_PRINT(rocme_porting_filter_modify(nFilterID1,cofe1,8,mask1,8));
    TEST_PRINT("fun=%s.line=%d.filter modify ok.\n",__FUNCTION__,__LINE__);
    DO_FAIL_PRINT(rocme_porting_filter_modify(nFilterID2,cofe2,8,mask2,8));
    TEST_PRINT("fun=%s.line=%d.filter modify ok.\n",__FUNCTION__,__LINE__);

    DO_FAIL_PRINT(rocme_porting_slot_start(nSlotID));
    TEST_PRINT("fun=%s.line=%d.slot start ok.\n",__FUNCTION__,__LINE__);
    
    DO_FAIL_PRINT(rocme_porting_filter_start(nFilterID1));
    DO_FAIL_PRINT(rocme_porting_filter_start(nFilterID2));
    TEST_PRINT("fun=%s.line=%d.filter start ok.\n",__FUNCTION__,__LINE__);

	

    pData0 = malloc(512*1024);
    DO_FAIL_PRINT(pData0!=NULL?ROC_OK:ROC_ERR);
    memset(pData0,0,512*1024);

    while(1)
    {
        nDataSlot = rocme_porting_slot_buff_wait(0,0x7fffffff);
        TEST_PRINT("fun=%s.line=%d.wait nDataSlot=%#x.\n",__FUNCTION__,__LINE__,nDataSlot);
    
        DO_FAIL_PRINT(rocme_porting_slot_buff_get(nDataSlot, pData0, 10, &nDatasize));
        TEST_PRINT("fun=%s.line=%d.get tableid=%#x.\n",__FUNCTION__,__LINE__,pData0[0]);
        
        DO_FAIL_PRINT(rocme_porting_slot_buff_read(nDataSlot,pData0,512*1024,pData1,0,&nDatasize));
        TEST_PRINT("fun=%s.line=%d.read tableid=%#x.nDatasize=%d.\n",__FUNCTION__,__LINE__,pData0[0],nDatasize);
    }

    while(1)
    {
        rocme_porting_task_sleep(3000);
        TEST_PRINT("fun into sleep while.\n",__FUNCTION__);
    }
}

#endif

