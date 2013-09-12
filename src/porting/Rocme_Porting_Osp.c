/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* 文件名称：rocme_porting_errno.cpp
* 
* 摘    要：
* 
* 当前版本：1.0
*
* 作    者：
*
* 完成日期：2011年05月
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
功能说明：
       获得操作系统版本号。
参数说明：
    输入参数：
    		无
    输出参数：
    		无
返    回： 
    成功 : 返回含有版本信息的字符串指针
    失败 : 返回空字符串
参考实现：
    rocme_operating.c
***************************************************************************/
const CHAR_T* rocme_porting_operating_version(void)
{
//ROCME_TEST_PRINT
	return "Linux 2.6.35";
}


/***************************************************************************
功能说明：
    创建线程
参数说明：
    输入参数：
      [      name ] 线程的名字
      [      Func ] 函数入口地址:typedef void(*Roc_Task_Proc)(void *)
      [     Param ] 参数列表(一般置为NULL)
      [stack_size ] 线程栈大小(>0有效)
      [  priority ] 线程的优先级，具体定义见枚举Roc_Task_Prio_e，
                    优先级从0到15,15最高,0最低

    输出参数：
    			无
返 回 值： 
    成功 : 返回线程句柄           
    失败 : 0
		
参考实现：
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
功能说明：

参数说明：
    输入参数：
    输出参数：
    [base]:返回栈顶地址
返    回： 
    成功 : 0            ( )
    失败 : -1 或 错误码 ( )
参考实现：
    rocme_operating.c
***************************************************************************/
INT32_T  rocme_porting_task_stack_dump(INT8_T **base)
{
//ROCME_TEST_PRINT

	*base = (char*)(base+3 * 1024 - 128*1024);
	return ROC_OK;

}

/***************************************************************************
功能说明：

参数说明：
    输入参数：
    输出参数：
    [base]:返回栈顶地址
返    回： 
    成功 : 1            ( )
    失败 : 0 或 错误码 ( )
参考实现：
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
功能说明：

参数说明：
    输入参数：
    [task ]:需要绑定数据的task
    [data ]:需要和线程绑定的数据的指针
    输出参数：
返    回： 
    成功 : 0            ( )
    失败 : -1 或 错误码 ( )
参考实现：
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
功能说明：

参数说明：
    输入参数：
    [task ]: 需要获取绑定数据的线程的句柄
    输出参数：
返    回： 
    成功 : 返回线程的绑定数据指针
    失败 : 返回空指针
参考实现：
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
功能说明：
    设置线程优先级
    
参数说明：
    输入参数：
      [      task ] 线程的句柄
      [  priority ] 线程的优先级，具体定义见枚举Roc_Task_Prio_e，
                    优先级从0到15,15最高,0最低

    输出参数：
    			无
返 回 值： 
    成功 : 0           
    失败 : -1 或 错误码
		
参考实现：
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
功能说明：
    获取当前线程的优先级
参数说明：
    输入参数：
    		[    task ]:需要获取线程优先级的线程句柄
    输出参数：
    		无
返    回： 
    成功 : 
    	返回线程的优先级
    	返回值应该符合Roc_Task_Prio_e枚举的定义。
    失败 : -1 或 错误码 
参考实现：
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
功能说明：
    获取当前线程的句柄
参数说明：
    输入参数：
	    	无
    输出参数：
    		无
返    回： 
    成功 : 返回线程的句柄，返回值应该符合Roc_Task_Prio_e枚举的定义。
    失败 : -1 或 错误码 
参考实现：
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
功能说明：
    获取指定线程的栈指针
参数说明：
    输入参数：
        [task ]:线程的ID
    输出参数：
    		无
返    回： 
    成功 : 线程栈指针
    失败 : NULL
参考实现：
    rocme_operating.c
***************************************************************************/
void* rocme_porting_task_get_stack(UINT32_T task)
{
//ROCME_TEST_PRINT
	return NULL;
}


/***************************************************************************
功能说明：
    销毁指定的线程
参数说明：
    输入参数：
        [  handle ]:线程的句柄
    输出参数：
    		无
返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：
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
功能说明：
     将本线程休眠一段时间。
参数说明：
    输入参数：
        [  ms ]:休眠时间，单位毫秒
    输出参数：
        无
返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：
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
功能说明：
    挂起线程，除非调用了rocme_porting_task_resume，被挂起的线程才会恢复运行。
参数说明：
    输入参数：
        [  handle ]: 要挂起的线程句柄    
    输出参数：
    		无
返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：
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
功能说明：
    恢复被挂起的线程
参数说明：
    输入参数：
        [  handle ]: 已被挂起的线程句柄    
    输出参数：
    		无
返    回： 
    成功 : 0            
    失败 : -1 或 错误码 
参考实现：
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
功能说明：
    强制当前线程重新等待被调度
参数说明：
    输入参数：
            无 
    输出参数：
    		无
返    回： 
            无 
参考实现：
    rocme_operating.c
***************************************************************************/
void rocme_porting_task_yield(void)
{
//ROCME_TEST_PRINT
	sched_yield();
}


//二、信号量 porting 接口
/***************************************************************************
功能说明：
    创建信号量
参数说明：
    输入参数：
      [         name ] 信号量的名字
      [ initial_count] 最大初始化计数(大于等于0有效)
      [     wait_mode] 信号量等待时间，单位为毫秒
      							特殊参数参见Roc_Task_Wait_Mode_e中的定义
      							ROC_TASK_WAIT_FIFO - 先进入等待队列的任务先获得信号量
										ROC_TASK_WAIT_PRIO - 优先级高的任务先获得信号量

    输出参数：
    			无
返 回 值： 
    成功返回 所创建信号量的Handle
		失败返回 0
		
参考实现：
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
功能说明：
    销毁指定的信号量
参数说明：
    输入参数：
      [      handle ] 信号量句柄

    输出参数：
    			无
返 回 值： 
    成功 : 0            
    失败 : -1 或 错误码
		
参考实现：
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
功能说明：
    等待信号量。此函数一般用在线程的开始位置，用于驱动线程的执行。
参数说明：
    输入参数：
      [      handle ] 信号量句柄
      [   wait_time ] 信号量等待模式，参见Roc_Timeout_Mode_e，其中
											ROC_TIMEOUT_INFINITY  表示永远等待，也就是死等
											ROC_TIMEOUT_IMMEDIATE 表示立即返回
    输出参数：
    			无
返 回 值： 
    该函数的返回有几种情况，对应不同的返回值，参见Roc_Queue_Sem_Status_e，具体如下：
    ROC_OS_QUEUE_SEM_TIMEOUT - 信号量超时返回，
    				仅用于 wait_time不是ROC_TIMEOUT_INFINITY和ROC_TIMEOUT_IMMEDIATE的情况
    ROC_OS_QUEUE_SEM_FAILURE - 错误返回
    ROC_OS_QUEUE_SEM_SUCCESS - 正常返回
		
参考实现：
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
功能说明：
    释放指定的信号量
参数说明：
    输入参数：
      [      handle ] 信号量句柄

    输出参数：
    			无
返 回 值： 
    成功 : 0            
    失败 : -1 或 错误码
		
参考实现：
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
功能说明：
    获得指定的信号量的信号值
参数说明：
    输入参数：
      [      handle ] 信号量句柄

    输出参数：
    			无
返 回 值： 
    成功 : 信号量的值            
    失败 : -1
		
参考实现：
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


//三、queue potring接口
/***************************************************************************
功能说明：
    创建信号量
参数说明：
    输入参数：
      [         name ] 消息队列的名字
      [          len ] 消息队列中最大消息数量
      [     wait_mode] 消息队列等待时间，单位为毫秒
      							特殊参数参见Roc_Task_Wait_Mode_e中的定义
      							ROC_TASK_WAIT_FIFO - 先进入等待队列的任务先获得信号量
										ROC_TASK_WAIT_PRIO - 优先级高的任务先获得信号量
    输出参数：
    			无
返 回 值： 
    成功： 所创建消息队列的句柄
		失败： 0
		
参考实现：
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
功能说明：
    销毁指定的消息队列
参数说明：
    输入参数：
      [      handle ] 消息队列句柄

    输出参数：
    			无
返 回 值： 
    成功 : 0            
    失败 : -1 或 错误码
		
参考实现：
    rocme_operating.c
***************************************************************************/
INT32_T rocme_porting_queue_destroy(UINT32_T handle)
{
//ROCME_TEST_PRINT
    HI_OSMsgQueueDel((HI_MsgQueue_p)handle);
    return 0;
}


/***************************************************************************
功能说明：
    向指定的消息队列发送消息
参数说明：
    输入参数：
      [      handle ] 目标消息队列的句柄
      [         msg ] 消息内容指针

    输出参数：
    			无
返 回 值： 
    成功 : 0            
    失败 : -1 或 错误码
		
参考实现：
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
功能说明：
    等待消息。此函数一般用在线程的开始位置，用于驱动线程的执行。
参数说明：
    输入参数：
      [      handle ] 消息队列的句柄
      [   wait_time ] 消息等待模式，参见Roc_Timeout_Mode_e，其中
											ROC_TIMEOUT_INFINITY  表示永远等待，也就是死等
											ROC_TIMEOUT_IMMEDIATE 表示立即返回
    输出参数：
    			无
返 回 值： 
    该函数的返回有几种情况，对应不同的返回值，参见Roc_Queue_Sem_Status_e，具体如下：
    ROC_OS_QUEUE_SEM_TIMEOUT - 超时返回，
    				仅用于 wait_time不是ROC_TIMEOUT_INFINITY和ROC_TIMEOUT_IMMEDIATE的情况
    ROC_OS_QUEUE_SEM_FAILURE - 错误返回
    ROC_OS_QUEUE_SEM_SUCCESS - 正常返回
		
参考实现：
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
功能说明：
    创建互斥锁
    
参数说明：
    输入参数：
      [      attr ] 需要创建的互斥锁的属性，参见Roc_Mutex_Attr_e

    输出参数：
    			无
返 回 值： 
    成功 : 返回互斥锁的句柄           
    失败 : 0 （无效HANDLE）
		
参考实现：
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
	
	if( 0!= pthread_mutex_init(pmutex,&ma) )  /*初始化互斥量*/
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
功能说明：
    销毁指定的互斥锁
    
参数说明：
    输入参数：
      [      handle ] 需要销毁的互斥锁的句柄

    输出参数：
    			无
返 回 值： 
    成功 : 0           
    失败 : -1
		
参考实现：
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
功能说明：
    互斥锁加锁
    
参数说明：
    输入参数：
      [      handle ] 需要加锁的互斥锁的句柄

    输出参数：
    			无
返 回 值： 
    成功 : 0           
    失败 : -1
		
参考实现：
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
功能说明：
    互斥锁解锁
    
参数说明：
    输入参数：
      [      handle ] 需要解锁的互斥锁的句柄

    输出参数：
    			无
返 回 值： 
    成功 : 0           
    失败 : -1
		
参考实现：
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
功能说明：
    尝试对互斥量进行加锁。如果调用rocme_porting_mutex_trylock时互斥量处于未锁住状态，     
那么rocme_porting_mutex_trylock将锁住互斥量，否则就会失败，不能锁住互斥量，立刻返回。
    
参数说明：
    输入参数：
      [      handle ] 互斥锁的句柄

    输出参数：
    			无
返 回 值： 
    成功 : 0           
    失败 : -1
		
参考实现：
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
功能说明：
    对齐的内存分配
    
参数说明：
    输入参数：
      [      nSize  ] 分配的内存大小
      [      nAlignSize  ] 对齐的字节数

    输出参数：
    			无
返 回 值： 
    成功 : 内存指针           
    失败 : NULL
		
参考实现：
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
		adjust = nSize - (address & (nAlignSize-1));//需要对齐

	if (adjust > 0)
		munmap((char*)(address), adjust);//释放前部分

	if (adjust < extra)
		munmap((char*)(address + adjust + nSize), extra - adjust);//释放后部分

	address += adjust;
	
	return (void*)address;
	
	
}


/***************************************************************************
功能说明：
    对齐的内存释放
    
参数说明：
    输入参数：
      [      addr  ] 内存指针
      [      nAlignSize  ] 对齐的字节数

    输出参数：
    			无
返 回 值： 
    无
		
参考实现：
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
