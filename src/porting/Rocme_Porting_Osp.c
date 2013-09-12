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

#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <memory.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/reboot.h>
#include <sys/time.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>

#include "hi_type.h"
#include "hi_os.h"

#include "porter_rocme.h"



static int key_valid = 0;
static int mem_pagesize;

pthread_key_t	thread_key;


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
INT32_T  rocme_porting_task_init_static_state(void)	
{
	if( key_valid == 0 )
	{
		if( ROC_OK != pthread_key_create(&thread_key, NULL) )
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"###[rocme_porting_taskInitStaticState] pthread_key_create failed !\n" );
			return ROC_ERR;
		}

		key_valid = 1;
	}
    mem_pagesize = getpagesize();

	return ROC_OK;
}


/***************************************************************************
����˵����
       ��ò���ϵͳ�汾�š�
����˵����
    ���������
    		��
    ���������
    		��
��    �أ� 
    �ɹ� : ���غ��а汾��Ϣ���ַ���ָ��
    ʧ�� : ���ؿ��ַ���
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
const CHAR_T* rocme_porting_operating_version(void)
{
//ROCME_TEST_PRINT
	return "Linux 2.6.35";
}


/***************************************************************************
����˵����
    �����߳�
����˵����
    ���������
      [      name ] �̵߳�����
      [      Func ] ������ڵ�ַ:typedef void(*Roc_Task_Proc)(void *)
      [     Param ] �����б�(һ����ΪNULL)
      [stack_size ] �߳�ջ��С(>0��Ч)
      [  priority ] �̵߳����ȼ������嶨���ö��Roc_Task_Prio_e��
                    ���ȼ���0��15,15���,0���

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : �����߳̾��           
    ʧ�� : 0
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
UINT32_T rocme_porting_task_create(const CHAR_T *name, Roc_Task_Proc func, void *param,Roc_Task_Prio_e priority, UINT32_T stack_size)
{
//ROCME_TEST_PRINT
    pthread_t tid;
    if( 0 != pthread_create( &tid, NULL, (void*)func, param ) )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR," pthread_create failed !\n" );
        return 0;
    }
    
    return tid;

}


/***************************************************************************
����˵����

����˵����
    ���������
    ���������
    [base]:����ջ����ַ
��    �أ� 
    �ɹ� : 0            ( )
    ʧ�� : -1 �� ������ ( )
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T  rocme_porting_task_stack_dump(INT8_T **base)
{
//ROCME_TEST_PRINT

	*base = (char*)(base+3 * 1024 - 128*1024);
	return ROC_OK;

}

/***************************************************************************
����˵����

����˵����
    ���������
    ���������
    [base]:����ջ����ַ
��    �أ� 
    �ɹ� : 1            ( )
    ʧ�� : 0 �� ������ ( )
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/



INT32_T  rocme_porting_task_stack_top(CHAR_T **base)
{
//ROCME_TEST_PRINT
#if 1
	int ret;
    size_t     size;
    void *stackaddr;
    pthread_attr_t attr;
    pthread_attr_t attr2;
    
    if( 0 == mem_pagesize )
        mem_pagesize = getpagesize();
        
    if( 0 != pthread_attr_init(&attr) )
    {
        return 0;    
    }
    

    pthread_getattr_np(pthread_self(), &attr);
    pthread_attr_getstack(&attr,(void*)&stackaddr,&size);

    (void)pthread_attr_destroy(&attr);
    //    rocme_porting_dprintf("stack addr is 0x%08x, stack size is 0x%08x\n",(U32)stackaddr,size);
    *base = ((void*)stackaddr)+size;
    return 1;

#endif
}

/***************************************************************************
����˵����

����˵����
    ���������
    [task ]:��Ҫ�����ݵ�task
    [data ]:��Ҫ���̰߳󶨵����ݵ�ָ��
    ���������
��    �أ� 
    �ɹ� : 0            ( )
    ʧ�� : -1 �� ������ ( )
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_task_data_set(UINT32_T task,void* data)
{
//ROCME_TEST_PRINT


    if( key_valid == 0 )
    {
        if( 0 != pthread_key_create(&thread_key, NULL) )
        {
            ROCME_PRINTF(ROCME_LOG_ERROR,"[OSLINUX]rocme_porting_task_init_static_state **error--> pthread_key_create failed !\n" );
            return ROC_ERR;
        }
        key_valid = 1;
    }
    if( 0 != pthread_setspecific( thread_key, data ) )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR,"[OSLINUX]rocme_porting_task_data_set pthread_setspecific failed !\n" );
        return ROC_ERR;
    }
	
    return ROC_OK;


}

/***************************************************************************
����˵����

����˵����
    ���������
    [task ]: ��Ҫ��ȡ�����ݵ��̵߳ľ��
    ���������
��    �أ� 
    �ɹ� : �����̵߳İ�����ָ��
    ʧ�� : ���ؿ�ָ��
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
void* rocme_porting_task_data(UINT32_T task)
{
//ROCME_TEST_PRINT
    if( key_valid == 0 )
    {
        if( 0 != pthread_key_create(&thread_key, NULL) )
        {
            ROCME_PRINTF(ROCME_LOG_ERROR,"[OSLINUX]rocme_porting_task_init_static_state **error--> pthread_key_create failed !\n" );
            return NULL;
        }
        key_valid = 1;
    } 
   void* test=pthread_getspecific( thread_key );
   return test;

}

/***************************************************************************
����˵����
    �����߳����ȼ�
    
����˵����
    ���������
      [      task ] �̵߳ľ��
      [  priority ] �̵߳����ȼ������嶨���ö��Roc_Task_Prio_e��
                    ���ȼ���0��15,15���,0���

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0           
    ʧ�� : -1 �� ������
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
void rocme_porting_task_priority_set(UINT32_T task,Roc_Task_Prio_e priority)
{
//ROCME_TEST_PRINT

	return 0;
#if 0
	INT32_T ret;
	
	if(0 == g_pOsMgr->ThreadMgr[task-1].nUsed)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_task_priority_set,task is not used\n" );
		return ROC_ERR;
	}

	struct sched_param param;
	int policy;

	param.sched_priority =  priority + 85>100?99:priority + 85;
	policy = SCHED_RR;
		
	ret = pthread_setschedparam( g_pOsMgr->ThreadMgr[task-1].hThread, policy, &param );
	if(ret != 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_task_priority_set,pthread_setschedparam err\n" );
		
	}

	return ;

#endif

}


/***************************************************************************
����˵����
    ��ȡ��ǰ�̵߳����ȼ�
����˵����
    ���������
    		[    task ]:��Ҫ��ȡ�߳����ȼ����߳̾��
    ���������
    		��
��    �أ� 
    �ɹ� : 
    	�����̵߳����ȼ�
    	����ֵӦ�÷���Roc_Task_Prio_eö�ٵĶ��塣
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
Roc_Task_Prio_e rocme_porting_task_priority(UINT32_T task)
{
//ROCME_TEST_PRINT
	return ROC_TASK_PRIO_LEVEL_0;

#if 0
	INT32_T ret;
	
	if(0 == g_pOsMgr->ThreadMgr[task-1].nUsed)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_task_priority_set,task is not used\n" );
		return ROC_ERR;
	}

	struct sched_param param;
	int policy;

		
	ret = pthread_getschedparam( g_pOsMgr->ThreadMgr[task-1].hThread, policy, &param );
	if(ret != 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_task_priority_set,pthread_setschedparam err\n" );
		return ROC_ERR;
	}
	
	return (Roc_Task_Prio_e)param.sched_priority-85;
#endif
}


/***************************************************************************
����˵����
    ��ȡ��ǰ�̵߳ľ��
����˵����
    ���������
	    	��
    ���������
    		��
��    �أ� 
    �ɹ� : �����̵߳ľ��������ֵӦ�÷���Roc_Task_Prio_eö�ٵĶ��塣
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
UINT32_T rocme_porting_task_ID(void)
{
//ROCME_TEST_PRINT

	return pthread_self();
#if 0
	UINT32_T pthread_id = pthread_self();
	UINT32_T index;

	for( index =0; index < PORT_MAX_TASK_NUM; index++ )
	{
		if( g_pOsMgr->ThreadMgr[index].nUsed &&
			g_pOsMgr->ThreadMgr[index].hThread == pthread_id )
		{
			return index + 1;
		}
	}

	return -1;
#endif
}


/***************************************************************************
����˵����
    ��ȡָ���̵߳�ջָ��
����˵����
    ���������
        [task ]:�̵߳�ID
    ���������
    		��
��    �أ� 
    �ɹ� : �߳�ջָ��
    ʧ�� : NULL
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
void* rocme_porting_task_get_stack(UINT32_T task)
{
//ROCME_TEST_PRINT
	return NULL;
}


/***************************************************************************
����˵����
    ����ָ�����߳�
����˵����
    ���������
        [  handle ]:�̵߳ľ��
    ���������
    		��
��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_task_destroy(UINT32_T handle)
{
//ROCME_TEST_PRINT

	pthread_t tid;

	tid = (pthread_t)handle;

	pthread_cancel(tid);

	return 0;
#if 0
	int pthread_kill_err;

	ROCME_PRINTF(ROCME_LOG_INFO, "handle: %d\r\n", handle);
	
	if( handle <= 0 || handle > PORT_MAX_TASK_NUM )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "param error. handle: %d, [1 - %d]\r\n", handle, PORT_MAX_TASK_NUM);
		return ROC_ERR;
	}
	
	if( 0 == g_pOsMgr->ThreadMgr[handle - 1].nUsed )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR, "handle not exist. handle = %d\r\n", handle);
		return ROC_ERR;
	}

	pthread_kill_err = pthread_kill(g_pOsMgr->ThreadMgr[handle-1].hThread, 0);
	if( ESRCH == pthread_kill_err )
	{
		ROCME_PRINTF(ROCME_LOG_WARN, "already exit\r\n");
		memset(&(g_pOsMgr->ThreadMgr[handle-1]), 0, sizeof(OS_THREAD_T));
		return ROC_OK;
	}
	else if( EINVAL == pthread_kill_err )
	{
		ROCME_PRINTF(ROCME_LOG_WARN, "wrong signal\r\n");
	}
	else
	{
		pthread_t hThread = g_pOsMgr->ThreadMgr[handle-1].hThread;
		memset(&(g_pOsMgr->ThreadMgr[handle-1]), 0, sizeof(OS_THREAD_T));		
		pthread_cancel(hThread);

		return ROC_OK;
	}

	ROCME_PRINTF(ROCME_LOG_WARN, "task destroy failed.\r\n");
	return ROC_ERR;
#endif
}


/***************************************************************************
����˵����
     �����߳�����һ��ʱ�䡣
����˵����
    ���������
        [  ms ]:����ʱ�䣬��λ����
    ���������
        ��
��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
void rocme_porting_task_sleep(INT32_T ms)
{
//ROCME_TEST_PRINT
	if( ms <= 0 || ms > 4294967 )
	{
		return;
	}

	usleep( ms * 1000 );
}


/***************************************************************************
����˵����
    �����̣߳����ǵ�����rocme_porting_task_resume����������̲߳Ż�ָ����С�
����˵����
    ���������
        [  handle ]: Ҫ������߳̾��    
    ���������
    		��
��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_task_suspend(UINT32_T handle)
{
//ROCME_TEST_PRINT
	
	pthread_t tid;

	tid = (pthread_t)handle;
	if( 0 != pthread_kill( tid, SIGSTOP ) )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"pthread_kill failed !\n" );
		return -1;
	}
	return ROC_OK;

}


/***************************************************************************
����˵����
    �ָ���������߳�
����˵����
    ���������
        [  handle ]: �ѱ�������߳̾��    
    ���������
    		��
��    �أ� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������ 
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_task_resume(UINT32_T handle)
{
//ROCME_TEST_PRINT
	
    pthread_t tid;
    
    tid = (pthread_t)handle;
    if( 0 != pthread_kill( tid, SIGCONT ) )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR," pthread_kill failed !\n" );
        return -1;
    }
    return 0;

}


/***************************************************************************
����˵����
    ǿ�Ƶ�ǰ�߳����µȴ�������
����˵����
    ���������
            �� 
    ���������
    		��
��    �أ� 
            �� 
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
void rocme_porting_task_yield(void)
{
//ROCME_TEST_PRINT
	sched_yield();
}


//�����ź��� porting �ӿ�
/***************************************************************************
����˵����
    �����ź���
����˵����
    ���������
      [         name ] �ź���������
      [ initial_count] ����ʼ������(���ڵ���0��Ч)
      [     wait_mode] �ź����ȴ�ʱ�䣬��λΪ����
      							��������μ�Roc_Task_Wait_Mode_e�еĶ���
      							ROC_TASK_WAIT_FIFO - �Ƚ���ȴ����е������Ȼ���ź���
										ROC_TASK_WAIT_PRIO - ���ȼ��ߵ������Ȼ���ź���

    ���������
    			��
�� �� ֵ�� 
    �ɹ����� �������ź�����Handle
		ʧ�ܷ��� 0
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
UINT32_T rocme_porting_sem_create(const CHAR_T *name, INT32_T initial_count,
                                   UINT32_T wait_mode)
{
//ROCME_TEST_PRINT
    sem_t *psem = NULL;

    psem = (sem_t *)malloc( sizeof(sem_t) );
    if( NULL == psem )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR, " malloc failed !" );
        return 0;
    }

    if( initial_count > SEM_VALUE_MAX )
    {
        initial_count = SEM_VALUE_MAX;
    }
    if( initial_count <= 0 )
    {
        initial_count = 0;
    }

    if ( -1 == sem_init( psem, 0, initial_count ) )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR,"sem_init failed !\n" );
        return 0;
    }

	return (unsigned int)psem;

}


/***************************************************************************
����˵����
    ����ָ�����ź���
����˵����
    ���������
      [      handle ] �ź������

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_sem_destroy(UINT32_T handle)
{
//ROCME_TEST_PRINT
    sem_t *psem = NULL;
    int ret = 0;


    if( handle == 0 )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR," handle error !\n" );
        return -1;
    }
    
    psem = (sem_t *)handle; 
    ret = sem_destroy( psem );
    if( ret == -1 )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR," sem_destroy failed ! ret=%d\n", ret );
    }
    
    free(psem);

    return 0;

}


/***************************************************************************
����˵����
    �ȴ��ź������˺���һ�������̵߳Ŀ�ʼλ�ã����������̵߳�ִ�С�
����˵����
    ���������
      [      handle ] �ź������
      [   wait_time ] �ź����ȴ�ģʽ���μ�Roc_Timeout_Mode_e������
											ROC_TIMEOUT_INFINITY  ��ʾ��Զ�ȴ���Ҳ��������
											ROC_TIMEOUT_IMMEDIATE ��ʾ��������
    ���������
    			��
�� �� ֵ�� 
    �ú����ķ����м����������Ӧ��ͬ�ķ���ֵ���μ�Roc_Queue_Sem_Status_e���������£�
    ROC_OS_QUEUE_SEM_TIMEOUT - �ź�����ʱ���أ�
    				������ wait_time����ROC_TIMEOUT_INFINITY��ROC_TIMEOUT_IMMEDIATE�����
    ROC_OS_QUEUE_SEM_FAILURE - ���󷵻�
    ROC_OS_QUEUE_SEM_SUCCESS - ��������
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_sem_wait(UINT32_T handle, INT32_T wait_time)
{
//ROCME_TEST_PRINT
    sem_t *psem = NULL;
    struct timespec ts;
    int ret = 0;

    if( 0 == handle )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR,"handle error !\n" );
        return ROC_OS_QUEUE_SEM_FAILURE;
    }    
    psem = (sem_t*)handle;

    if( 0 > wait_time )
    {
        if( 0 != sem_wait(psem) )
        {
            ROCME_PRINTF(ROCME_LOG_ERROR," sem_wait failed !\n" );
            return ROC_OS_QUEUE_SEM_FAILURE;
        }        
        return ROC_OS_QUEUE_SEM_SUCCESS;
    }

    ts.tv_sec = time(NULL)+(wait_time/1000);
    ts.tv_nsec = (wait_time%1000)*1000;
    ret = sem_timedwait( psem, &ts );
    if( 0 == ret )
    {
        return ROC_OS_QUEUE_SEM_SUCCESS;
    }
    else 
    {
        if( ETIMEDOUT == errno )
        {
	     usleep(1);
            return ROC_OS_QUEUE_SEM_TIMEOUT;
        }
        else
        {
            ROCME_PRINTF(ROCME_LOG_ERROR," sem_timedwait failed ! errno=%d\n", errno );
            return ROC_OS_QUEUE_SEM_FAILURE;
        }
    }
    return ROC_OS_QUEUE_SEM_FAILURE;

}	


/***************************************************************************
����˵����
    �ͷ�ָ�����ź���
����˵����
    ���������
      [      handle ] �ź������

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_sem_release(UINT32_T handle)
{
//ROCME_TEST_PRINT
    sem_t *psem = NULL;

    if( 0 == handle )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR,"handle error !\n" );
        return -1;
    } 
    
    psem = (sem_t*)handle;
    if( 0 != sem_post( psem ) )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR,"sem_post failed !\n" );
		return -1;
    }

    return 0;

}


/***************************************************************************
����˵����
    ���ָ�����ź������ź�ֵ
����˵����
    ���������
      [      handle ] �ź������

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : �ź�����ֵ            
    ʧ�� : -1
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_sem_get_value(UINT32_T handle)
{
//ROCME_TEST_PRINT
    int val = 0;
    sem_t *psem = NULL;

    if( 0 == handle )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR,"handle error !\n" );
        return -1;
    }
    
    psem = (sem_t*)handle;
    if( 0 != sem_getvalue( psem, &val ) )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR,"sem_getvalue failed !\n" );
		return -1;
    }

    return val;

}


//����queue potring�ӿ�
/***************************************************************************
����˵����
    �����ź���
����˵����
    ���������
      [         name ] ��Ϣ���е�����
      [          len ] ��Ϣ�����������Ϣ����
      [     wait_mode] ��Ϣ���еȴ�ʱ�䣬��λΪ����
      							��������μ�Roc_Task_Wait_Mode_e�еĶ���
      							ROC_TASK_WAIT_FIFO - �Ƚ���ȴ����е������Ȼ���ź���
										ROC_TASK_WAIT_PRIO - ���ȼ��ߵ������Ȼ���ź���
    ���������
    			��
�� �� ֵ�� 
    �ɹ��� ��������Ϣ���еľ��
		ʧ�ܣ� 0
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
UINT32_T rocme_porting_queue_create(const CHAR_T *name, UINT32_T len,UINT32_T wait_mode)
{
//ROCME_TEST_PRINT
    HI_MsgQueue_p pMsgQueue = HI_OSMsgQueueCreate(sizeof(Roc_Queue_Message_t), len);
    if(NULL == pMsgQueue)
    {
        ROCME_PRINTF(ROCME_LOG_ERROR, "creat failed !\n");
    }
    return pMsgQueue;
}


/***************************************************************************
����˵����
    ����ָ������Ϣ����
����˵����
    ���������
      [      handle ] ��Ϣ���о��

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_queue_destroy(UINT32_T handle)
{
//ROCME_TEST_PRINT
    HI_OSMsgQueueDel((HI_MsgQueue_p)handle);
    return 0;
}


/***************************************************************************
����˵����
    ��ָ������Ϣ���з�����Ϣ
����˵����
    ���������
      [      handle ] Ŀ����Ϣ���еľ��
      [         msg ] ��Ϣ����ָ��

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0            
    ʧ�� : -1 �� ������
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_queue_send(UINT32_T handle, Roc_Queue_Message_t *msg)
{
//ROCME_TEST_PRINT
    HI_VOID* pMsg = HI_OSMsgClaim((HI_MsgQueue_p)handle, 10);
    if(NULL == pMsg)
    {		
        ROCME_PRINTF(ROCME_LOG_ERROR, "HI_OSMsgClaim failed !\n");
        return -1;
    }
    memcpy(pMsg, msg, sizeof(Roc_Queue_Message_t));
    HI_OSMsgSend((HI_MsgQueue_p)handle, pMsg);
    return 0;

}


/***************************************************************************
����˵����
    �ȴ���Ϣ���˺���һ�������̵߳Ŀ�ʼλ�ã����������̵߳�ִ�С�
����˵����
    ���������
      [      handle ] ��Ϣ���еľ��
      [   wait_time ] ��Ϣ�ȴ�ģʽ���μ�Roc_Timeout_Mode_e������
											ROC_TIMEOUT_INFINITY  ��ʾ��Զ�ȴ���Ҳ��������
											ROC_TIMEOUT_IMMEDIATE ��ʾ��������
    ���������
    			��
�� �� ֵ�� 
    �ú����ķ����м����������Ӧ��ͬ�ķ���ֵ���μ�Roc_Queue_Sem_Status_e���������£�
    ROC_OS_QUEUE_SEM_TIMEOUT - ��ʱ���أ�
    				������ wait_time����ROC_TIMEOUT_INFINITY��ROC_TIMEOUT_IMMEDIATE�����
    ROC_OS_QUEUE_SEM_FAILURE - ���󷵻�
    ROC_OS_QUEUE_SEM_SUCCESS - ��������
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_queue_recv(UINT32_T handle, Roc_Queue_Message_t *msg,INT32_T wait_time)
{
//ROCME_TEST_PRINT
    HI_VOID* pMsg = HI_OSMsgReceive((HI_MsgQueue_p)handle, wait_time);

    if(NULL != pMsg)
    {
        memcpy(msg, pMsg, sizeof(Roc_Queue_Message_t));
        HI_OSMsgRelease((HI_MsgQueue_p)handle, pMsg);
        return ROC_OS_QUEUE_SEM_SUCCESS;
    }
    
    if((0 >= wait_time) || (ROC_TIMEOUT_INFINITY == wait_time))
    {
        return ROC_OS_QUEUE_SEM_FAILURE;
    }
    else
	{
        return ROC_OS_QUEUE_SEM_TIMEOUT;
    }

}


/***************************************************************************
����˵����
    ����������
    
����˵����
    ���������
      [      attr ] ��Ҫ�����Ļ����������ԣ��μ�Roc_Mutex_Attr_e

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : ���ػ������ľ��           
    ʧ�� : 0 ����ЧHANDLE��
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
UINT32_T rocme_porting_mutex_create(Roc_Mutex_Attr_e  attr)
{
//ROCME_TEST_PRINT

	pthread_mutex_t *pmutex = NULL;
	pthread_mutexattr_t ma;
	
	if( 0 != pthread_mutexattr_init(&ma) )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"pthread_mutexattr_init failed !\n" );
		return 0;
	}


	switch( attr )
	{
	case ROC_MUTEX_RECURSIVE_NP:
		pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_RECURSIVE_NP);
		break;
		
	case ROC_MUTEX_ERRORCHECK_NP:
		pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_ERRORCHECK_NP);
		break;
		
	case ROC_MUTEX_ADAPTIVE_NP:
		pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_ADAPTIVE_NP);
		break;

	case ROC_MUTEX_TIMED_NP:
	default:
		pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_TIMED_NP);
		break;
	}


    pmutex = (pthread_mutex_t*)malloc( sizeof(pthread_mutex_t) );
	if( NULL == pmutex )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"pthread_mutex_t malloc failed !\n" );
		return 0;
	}
	
	if( 0!= pthread_mutex_init(pmutex,&ma) )  /*��ʼ��������*/
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"pthread_mutex_init failed !\n" );
		free(pmutex);
		pthread_mutexattr_destroy(&ma);
		return 0;
	}
	
	pthread_mutexattr_destroy(&ma);
	
	return (unsigned int)pmutex;

}


/***************************************************************************
����˵����
    ����ָ���Ļ�����
    
����˵����
    ���������
      [      handle ] ��Ҫ���ٵĻ������ľ��

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0           
    ʧ�� : -1
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_mutex_destroy(UINT32_T handle)
{
//ROCME_TEST_PRINT
    pthread_mutex_t *pmutex;
    int ret = 0;
    
    pmutex = (pthread_mutex_t *)handle;
    if( NULL == pmutex )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR," handle error! \n" ); 
        return -1;       
    }
    
    ret = pthread_mutex_destroy( pmutex );
    if( ret != 0 )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR," pthread_mutex_destroy failed! ret=%d \n", ret );
		return -1;
    }
    free(pmutex);
    
    return 0;

}


/***************************************************************************
����˵����
    ����������
    
����˵����
    ���������
      [      handle ] ��Ҫ�����Ļ������ľ��

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0           
    ʧ�� : -1
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_mutex_lock(UINT32_T handle)
{
//ROCME_TEST_PRINT

	pthread_mutex_t *pmutex;
	int ret = 0;

	if(handle==0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"Error handle \n");
		return -1;
	}
  
	pmutex = (pthread_mutex_t *)handle;

	ret = pthread_mutex_lock( pmutex );
	if( ret != 0 )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"pthread_mutex_lock failed! handle = 0x%x, ret=%d \n", pmutex, ret );
		return -1;
	}
	
	return 0;

}


/***************************************************************************
����˵����
    ����������
    
����˵����
    ���������
      [      handle ] ��Ҫ�����Ļ������ľ��

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0           
    ʧ�� : -1
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_mutex_unlock(UINT32_T handle)
{
//ROCME_TEST_PRINT
	pthread_mutex_t *pmutex;
	int ret = 0;
	
	if(handle==0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"Error handle \n");
		return -1;
	}
	pmutex = (pthread_mutex_t *)handle;

	ret = pthread_mutex_unlock( pmutex );
	if( ret != 0 )
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"pthread_mutex_unlock failed! handle = 0x%x, ret=%d \n", pmutex, ret );
		perror(pmutex);
		return -1;
	}
	return 0;

}

/***************************************************************************
����˵����
    ���ԶԻ��������м������������rocme_porting_mutex_trylockʱ����������δ��ס״̬��     
��ôrocme_porting_mutex_trylock����ס������������ͻ�ʧ�ܣ�������ס�����������̷��ء�
    
����˵����
    ���������
      [      handle ] �������ľ��

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : 0           
    ʧ�� : -1
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_mutex_trylock(UINT32_T handle)
{
//ROCME_TEST_PRINT
    pthread_mutex_t *pmutex;
    int ret = 0;
	
	if(handle==0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"Error handle \n");
		return -1;
	}

    pmutex = (pthread_mutex_t *)handle;  
    ret = pthread_mutex_trylock( pmutex );
    if( ret == 0 )
    {
        return 0;
    }
    else if( ret == EBUSY )
    {
        ROCME_PRINTF(ROCME_LOG_ERROR, "pthread_mutex_unlock busy! handle=0x%x \n", handle );
    }
    else
    {
        ROCME_PRINTF(ROCME_LOG_ERROR, "pthread_mutex_unlock failed!  tid= %d , ret=%d \n",handle, ret );
    }

    return -1;

}


/***************************************************************************
����˵����
    ������ڴ����
    
����˵����
    ���������
      [      nSize  ] ������ڴ��С
      [      nAlignSize  ] ������ֽ���

    ���������
    			��
�� �� ֵ�� 
    �ɹ� : �ڴ�ָ��           
    ʧ�� : NULL
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
void* rocme_porting_aligned_malloc(int nSize,int nAlignSize)
{
//ROCME_TEST_PRINT

	int extra = 0;
	if (nSize > mem_pagesize)
		extra = nSize - mem_pagesize;

	void* mmapResult = mmap(NULL, nSize + extra, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	UINT32_T address = (UINT32_T)(mmapResult);

	size_t adjust = 0;
	if ((address & (nAlignSize-1)) != 0)
		adjust = nSize - (address & (nAlignSize-1));//��Ҫ����

	if (adjust > 0)
		munmap((char*)(address), adjust);//�ͷ�ǰ����

	if (adjust < extra)
		munmap((char*)(address + adjust + nSize), extra - adjust);//�ͷź󲿷�

	address += adjust;
	
	return (void*)address;
	
	
}


/***************************************************************************
����˵����
    ������ڴ��ͷ�
    
����˵����
    ���������
      [      addr  ] �ڴ�ָ��
      [      nAlignSize  ] ������ֽ���

    ���������
    			��
�� �� ֵ�� 
    ��
		
�ο�ʵ�֣�
    rocme_operating.c
***************************************************************************/
void rocme_porting_aligned_free(void* addr,int nAlignSize)
{
//ROCME_TEST_PRINT
	 munmap((char*)(addr), nAlignSize);
}

#if 0
INT32_T rocme_porting_cond_create(void)
{
ROCME_TEST_PRINT
	UINT32_T index;
	pthread_cond_t cond;

	os_init();

	for( index = 0; index < PORT_MAX_COND_NUM; index++ )
	{
		if( 0 == g_pOsMgr->CondMgr[index].nUsed )
		{
			if( 0 == pthread_cond_init(&cond, NULL) )
			{
				g_pOsMgr->CondMgr[index].nUsed = 1;
				g_pOsMgr->CondMgr[index].hCond = cond;

				return index + 1;
			}

			return 0;
		}
	}
	
	return 0;
}


INT32_T rocme_porting_cond_destroy(INT32_T handle)
{
	if( handle > 0 && handle <= PORT_MAX_COND_NUM )
	{
		if( g_pOsMgr->CondMgr[handle-1].nUsed )
		{
			if( 0 == pthread_cond_destroy(&(g_pOsMgr->CondMgr[handle-1].hCond)) )
			{
				memset(&(g_pOsMgr->CondMgr[handle-1]), 0, sizeof(OS_COND_T));
				return ROC_OK;
			}
		}
	}

	return ROC_ERR;
}


INT32_T rocme_porting_cond_wait(INT32_T condHandle, INT32_T mtxHandle, INT32_T wait_time)
{
	if( !( condHandle > 0 && condHandle <= PORT_MAX_COND_NUM ) ||
		g_pOsMgr->CondMgr[condHandle-1].nUsed == 0 )
	{
		return ROC_ERR;
	}

	if( wait_time <= 0 )
	{
		if( 0 == pthread_cond_wait(&g_pOsMgr->CondMgr[condHandle-1].hCond, &(g_pOsMgr->MutexMgr[mtxHandle-1].hMutex)) )
		{
			return ROC_OK;
		}
	}
	else
	{
		struct timeval ttime;
		struct timespec ttspec;
		
		gettimeofday(&ttime, NULL);
		ttspec.tv_nsec = (ttime.tv_usec + (wait_time % 1000) * 1000) * 1000;
		ttspec.tv_sec = ttime.tv_sec + wait_time / 1000;
		ttspec.tv_sec += ttspec.tv_nsec / 1000000000;
	
		if( 0 == pthread_cond_timedwait(&g_pOsMgr->CondMgr[condHandle-1].hCond, &(g_pOsMgr->MutexMgr[mtxHandle-1].hMutex), &ttspec) )
		{
			return ROC_OK;
		}
	}

	return ROC_ERR;
}


INT32_T rocme_porting_cond_signal(INT32_T handle)
{
	if( !( handle > 0 && handle <= PORT_MAX_COND_NUM ) ||
		g_pOsMgr->CondMgr[handle-1].nUsed == 0 )
	{
		return ROC_ERR;
	}

	if( 0 == pthread_cond_signal(&g_pOsMgr->CondMgr[handle-1].hCond) )
	{
		return ROC_OK;
	}
	
	return ROC_ERR;
}
#endif
