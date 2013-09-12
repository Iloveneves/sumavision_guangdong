/*******************************************************************************
File name   : rocme_porting_osp.h

Author		: XXX			

Description : The poriting interface & macro definition for OS Package module.
	          
Copyright (C) BeiJing SUMAVision, Inc., 2009 .All rights reserved.

History		:
				2009.12.20  		Created 					
*******************************************************************************/
#ifndef _ROCME_PORTING_OSP_H_
#define _ROCME_PORTING_OSP_H_



#include "rocme_porting_typedef.h"

/*++++++++++++++++++++++++++++     DEFINES     ++++++++++++++++++++++++++++*/
typedef UINT32_T pmutex;
typedef UINT32_T psem;
typedef UINT32_T pthread;

/*******************************************************************************
** Queue Message Structure used by the OSP.
** Note that it was decided to use a structure for the message type so as to
** provide bounds checking on the message being placed in the queue. An array 
** was the obvious alternative to such a structure, but it was felt that the
** array would not clearly indicate to the user the the limitations on the
** message size to use.
*******************************************************************************/
typedef struct Roc_Queue_Message
{
	UINT32_T q1stWordOfMsg;                /* First word of a queue message.  */
	UINT32_T q2ndWordOfMsg;                /* Second word of a queue message. */
	UINT32_T q3rdWordOfMsg;                /* Third word of a queue message.  */
	UINT32_T q4thWordOfMsg;                /* Fourth word of a queue message. */
} Roc_Queue_Message_t;

/* rocme_porting_sem_wait()/rocme_porting_queue_recv()函数中的等待模式 */
typedef enum Roc_Timeout_Mode
{
	ROC_TIMEOUT_INFINITY    = -1,	/* 永久等待 */
	ROC_TIMEOUT_IMMEDIATE   = 0		/* 立即返回 */
}Roc_Timeout_Mode_e;

/* 等待信号量及消息队列的返回值 ，用于rocme_porting_sem_wait()及rocme_porting_queue_recv()*/
typedef enum Roc_Queue_Sem_Status
{
    ROC_OS_QUEUE_SEM_TIMEOUT     = 0x00,		/* 消息队列或信号量超时返回 */
    ROC_OS_QUEUE_SEM_FAILURE     = 0x01, 		/* 消息队列或信号量错误返回 */
    ROC_OS_QUEUE_SEM_SUCCESS     = 0x02   /* 消息队列或信号量正常返回 */
}Roc_Queue_Sem_Status_e;

/*rocme_porting_sem_create()/rocme_porting_queue_create()的处理模式*/
typedef enum Roc_Task_Wait_Mode
{
    ROC_TASK_WAIT_FIFO      = 0x00,		/* 先进入等待队列的任务先获得信号量或消息 */
    ROC_TASK_WAIT_PRIO      = 0x01		/* 优先级高的任务先获得信号量或消息 */
}Roc_Task_Wait_Mode_e;

/*
中间件线程的优先级，总共分为16级，0为最低，15最高。
移植层根据操作系统的不同，可调整优先级的具体底层对应值。
*/
typedef enum _Roc_Task_Prio_
{
	ROC_TASK_PRIO_LEVEL_0 = 0,
	ROC_TASK_PRIO_LEVEL_1,
	ROC_TASK_PRIO_LEVEL_2,
	ROC_TASK_PRIO_LEVEL_3,
	ROC_TASK_PRIO_LEVEL_4,
	ROC_TASK_PRIO_LEVEL_5,
	ROC_TASK_PRIO_LEVEL_6,
	ROC_TASK_PRIO_LEVEL_7,
	ROC_TASK_PRIO_LEVEL_8,
	ROC_TASK_PRIO_LEVEL_9,
	ROC_TASK_PRIO_LEVEL_10,
	ROC_TASK_PRIO_LEVEL_11,
	ROC_TASK_PRIO_LEVEL_12,
	ROC_TASK_PRIO_LEVEL_13,
	ROC_TASK_PRIO_LEVEL_14,
	ROC_TASK_PRIO_LEVEL_15	
}Roc_Task_Prio_e;

typedef void (*Roc_Task_Proc)(void *param);/*定义线程回调函数的类型*/

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
const CHAR_T* rocme_porting_operating_version(void);

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
UINT32_T rocme_porting_task_create(const CHAR_T *name, Roc_Task_Proc func, void *param,Roc_Task_Prio_e priority, UINT32_T stack_size);

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
INT32_T  rocme_porting_task_stack_dump(INT8_T **base);

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
INT32_T  rocme_porting_task_stack_top(CHAR_T **base);

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
INT32_T rocme_porting_task_data_set(UINT32_T task,void* data);

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
void* rocme_porting_task_data(UINT32_T task);

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
void rocme_porting_task_priority_set(UINT32_T task,Roc_Task_Prio_e priority);

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
Roc_Task_Prio_e rocme_porting_task_priority(UINT32_T task);

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
UINT32_T rocme_porting_task_ID(void);

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
void* rocme_porting_task_get_stack(UINT32_T task);

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
INT32_T rocme_porting_task_destroy(UINT32_T handle);

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
void rocme_porting_task_sleep(INT32_T ms);

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
INT32_T rocme_porting_task_suspend(UINT32_T handle);

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
INT32_T rocme_porting_task_resume(UINT32_T handle);

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
void rocme_porting_task_yield(void);

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
                                   UINT32_T wait_mode);

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
INT32_T rocme_porting_sem_destroy(UINT32_T handle);

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
INT32_T rocme_porting_sem_wait(UINT32_T handle, INT32_T wait_time);

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
INT32_T rocme_porting_sem_release(UINT32_T handle); 

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
INT32_T rocme_porting_sem_get_value(UINT32_T handle);

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
UINT32_T rocme_porting_queue_create(const CHAR_T *name, UINT32_T len,UINT32_T wait_mode);

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
INT32_T rocme_porting_queue_destroy(UINT32_T handle);

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
INT32_T rocme_porting_queue_send(UINT32_T handle, Roc_Queue_Message_t *msg);

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
INT32_T rocme_porting_queue_recv(UINT32_T handle, Roc_Queue_Message_t *msg,INT32_T wait_time);


//四、互斥锁poting接口

/*******************************************************************************
*******************************************************************************/
typedef enum Roc_Mutex_Attr
{
    ROC_MUTEX_TIMED_NP      = 0x00, /*这是缺省值，也就是普通锁。当一个线程加锁以后，
    																其余请求锁的线程将形成一个等待队列，并在解锁后按
    																优先级获得锁。这种锁策略保证了资源分配的公平性*/
    ROC_MUTEX_RECURSIVE_NP  = 0x01, /*嵌套锁，允许同一个线程对同一个锁成功获得多次，
                                    并通过多次unlock解锁。如果是不同线程请求，则在
                                    加锁线程解锁时重新竞争。*/
    ROC_MUTEX_ERRORCHECK_NP = 0x02, /*检错锁，如果同一个线程请求同一个锁，则返回-1，
                                    否则与ROCME_MUTEX_TIMED_NP类型动作相同。这样就保
                                    证当不允许多次加锁时不会出现最简单情况下的死锁*/
    ROC_MUTEX_ADAPTIVE_NP   = 0x03  /*适应锁，动作最简单的锁类型，仅等待解锁后重新竞争*/
}Roc_Mutex_Attr_e;

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
UINT32_T rocme_porting_mutex_create(Roc_Mutex_Attr_e  attr);

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
INT32_T rocme_porting_mutex_destroy(UINT32_T handle);

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
INT32_T rocme_porting_mutex_lock(UINT32_T handle);


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
INT32_T rocme_porting_mutex_unlock(UINT32_T handle);

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
INT32_T rocme_porting_mutex_trylock(UINT32_T handle);


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
void* rocme_porting_aligned_malloc(int nSize,int nAlignSize);

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
void rocme_porting_aligned_free(void* addr,int nAlignSize);

INT32_T rocme_porting_cond_create(void);

INT32_T rocme_porting_cond_destroy(INT32_T handle);

INT32_T rocme_porting_cond_wait(INT32_T condHandle, INT32_T mtxHandle, INT32_T wait_time);

INT32_T rocme_porting_cond_signal(INT32_T handle);

INT32_T  rocme_porting_task_init_static_state(void);	



#endif
