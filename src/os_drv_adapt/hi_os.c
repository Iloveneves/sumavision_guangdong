/*****************************************************************************
 *
 * Description: 
 *    
 *
 * Revision History:
 *    Date          Author         Modification
 * ---------------------------------------------------------------------
 * 1. 2006-10-16    
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <semaphore.h>
#include <stdarg.h>
#include <math.h>
#include <sys/time.h>

//#include "tx_adpt_types.h"

#include "hi_os.h"

static HI_S32 semaphore_create(sem_t *pSem, HI_U32 u32StartCount)
{
    HI_S32 s32Ret = 0;

    s32Ret = sem_init(pSem, 0, u32StartCount);
    if (s32Ret == 0)
    {
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

static HI_VOID semaphore_delete(sem_t *pSem)
{    
    sem_destroy((sem_t *)pSem);
    //free(pSem);
}

static HI_U32 semaphore_signal(sem_t *pSem)
{
    HI_S32 s32Ret;
        
    s32Ret = sem_post(pSem);
    if ( s32Ret == 0 )
    {
        return HI_TRUE;
    }
    return HI_FALSE;
}

static HI_U32 semaphore_wait(sem_t *pSem)
{
    HI_S32 s32Ret;
    s32Ret = sem_wait(pSem);
    if ( s32Ret == 0 )
    {
        return HI_TRUE;
    }
    return HI_FALSE;
}

static HI_U32 semaphore_nowait(sem_t *pSem)
{
    HI_S32 s32Ret;
    s32Ret = sem_trywait(pSem);
    if ( s32Ret == 0 )
    {
        return HI_TRUE;
    }
    return HI_FALSE;
}

static HI_VOID message_half_add(message_half_t* MessageHalf, HI_VOID* UsrMessage)
{
    int status;
    message_hdr_t* Message = (message_hdr_t*)UsrMessage - 1;

    if (!MessageHalf) {
        printf("FATAL! message_half_add: NULL MessageHalf\n");
        return;
    }

    if (!UsrMessage) {
        printf("FATAL! message_half_add: NULL UsrMessage\n");
        return;
    }

    status = pthread_mutex_lock(&MessageHalf->message_half_mutex);
    if (status != 0) {
        printf("FATAL! message_half_add: pthread_mutex_lock failure\n");
        return;
    }

    Message->message_hdr_next = NULL;
    if (NULL == MessageHalf->message_half_head  )
        MessageHalf->message_half_head = Message;
    else
        MessageHalf->message_half_tail->message_hdr_next = Message;
    MessageHalf->message_half_tail = Message;

    status = pthread_mutex_unlock(&MessageHalf->message_half_mutex);
    if (status != 0) {
        printf("FATAL! message_half_add: pthread_mutex_unlock failure\n");
        return;
    }

    sem_post(&MessageHalf->message_half_sem);

    return;
}

static HI_VOID* message_half_remove(message_half_t* MessageHalf)
{
    int status;
    message_hdr_t* Message;

    if (!MessageHalf) {
        printf("FATAL! message_half_remove: NULL MessageHalf\n");
        return NULL;
    }

    sem_wait(&MessageHalf->message_half_sem);

    status = pthread_mutex_lock(&MessageHalf->message_half_mutex);
    if (status != 0) {
        printf("FATAL! message_half_remove: pthread_mutex_lock failure\n");
        return NULL;
    }

    Message                        = MessageHalf->message_half_head;
    MessageHalf->message_half_head = Message->message_hdr_next;

    status = pthread_mutex_unlock(&MessageHalf->message_half_mutex);
    if (status != 0) {
        printf("FATAL! message_half_remove: pthread_mutex_unlock failure\n");
        return NULL;
    }

    return Message + 1;
}

static HI_VOID message_send (message_queue_t*  MessageQueue, HI_VOID* Message)
{
    if (!MessageQueue) {
        printf("FATAL! message_send: NULL MessageQueue\n");
        return;
    }

    /* other assertions defered to message_half_add */
    message_half_add(&MessageQueue->message_queue_queue, Message);
}

static HI_VOID* message_receive (message_queue_t* MessageQueue)
{
    if (!MessageQueue) {
        printf("FATAL! message_receive: NULL MessageQueue\n");
        return NULL;
    }

    /* other assertions defered to message_half_remove */
    return message_half_remove(&MessageQueue->message_queue_queue);
}

static HI_VOID* message_claim (message_queue_t* MessageQueue)
{
    if (!MessageQueue) {
        printf("FATAL! message_claim: NULL MessageQueue\n");
        return NULL;
    }

    /* other assertions defered to message_half_remove */
    return message_half_remove(&MessageQueue->message_queue_free);
}


static HI_VOID message_release (message_queue_t* MessageQueue, HI_VOID* Message)
{
    if (!MessageQueue) {
        printf("FATAL! message_release: NULL MessageQueue\n");
        return;
    }

    /* other assertions defered to message_half_add */
    message_half_add(&MessageQueue->message_queue_free, Message);
}

static HI_VOID message_uninit_queue(message_queue_t* MessageQueue)
{
    int status;

    if (!MessageQueue) {
        printf("FATAL! message_uninit_queue: NULL MessageQueue\n");
        return;
    }

    status = sem_destroy(&MessageQueue->message_queue_free.message_half_sem);
    if (-1 ==  status ) {
        printf("FATAL! message_uninit_queue: sem_destroy failure, message_queue_free\n");
        return;
    }

    status = sem_destroy(&MessageQueue->message_queue_queue.message_half_sem);
    if (-1 ==  status ) {
        printf("FATAL! message_uninit_queue: sem_destroy failure, message_queue_queue\n");
        return;
    }

    status = pthread_mutex_destroy(&MessageQueue->message_queue_free.message_half_mutex);
    if (status != 0) {
        printf("FATAL! message_uninit_queue: pthread_mutex_destroy failure, message_queue_free\n");
        return;
    }

    status = pthread_mutex_destroy(&MessageQueue->message_queue_queue.message_half_mutex);
    if (status != 0) {
        printf("FATAL! message_uninit_queue: pthread_mutex_destroy failure, message_queue_queue\n");
        return;
    }
    return;
}

static int message_init_generic(message_queue_t* MessageQueue, HI_VOID* memory,
        size_t ElementSize, unsigned int NoElements)
{
    message_hdr_t**   PrevMsgP;
    message_hdr_t*    CurrMsg;
    int               i;
    size_t            Needed;

    if (!MessageQueue) {
        printf("FATAL! message_init_generic: NULL MessageQueue\n");
        return FALSE;
    }

    if (!memory) {
        printf("FATAL! message_init_generic: NULL memory\n");
        return FALSE;
    }

    ElementSize = (ElementSize + 3) & ~3;
    Needed = ElementSize + sizeof(message_hdr_t);

    CurrMsg = (message_hdr_t*)memory;  
    PrevMsgP = &MessageQueue->message_queue_free.message_half_head;

    for (i = 1; i < NoElements; i++) {
        *PrevMsgP = CurrMsg;
        PrevMsgP = &CurrMsg->message_hdr_next;
        CurrMsg = (message_hdr_t*)((char*)CurrMsg + Needed);
    }
    *PrevMsgP = CurrMsg;
    MessageQueue->message_queue_free.message_half_tail = CurrMsg;
    CurrMsg->message_hdr_next = NULL;

    MessageQueue->message_queue_queue.message_half_head = NULL;
    MessageQueue->message_queue_queue.message_half_tail = NULL;

    sem_init(&MessageQueue->message_queue_free.message_half_sem, 0, NoElements);
    sem_init(&MessageQueue->message_queue_queue.message_half_sem, 0, 0);

    /* the following is the same as setting PTHREAD_MUTEX_INITIALIZER*/

    pthread_mutex_init(&MessageQueue->message_queue_free.message_half_mutex, NULL);
    pthread_mutex_init(&MessageQueue->message_queue_queue.message_half_mutex, NULL);

    MessageQueue->message_queue_memory = memory;

    return TRUE;
}

int message_init_queue(message_queue_t* MessageQueue, HI_VOID* memory,
        size_t ElementSize, unsigned int NoElements)
{
    /* assertions defered to message_init_queue */
    return message_init_generic(MessageQueue, memory, ElementSize, NoElements);
}

/*
 * Message queue creation functions
 */

static message_queue_t *message_create_generic(size_t ElementSize,
        unsigned int NoElements)
{
    message_queue_t* MessageQueue;
    HI_VOID* messages;
    size_t Needed;

    /* This calculation needs to be the same as the one performed in
     * message_queue_init() */
    ElementSize = (ElementSize + 3) & ~3;
    Needed = ElementSize + sizeof(message_hdr_t);

    messages = malloc(Needed * NoElements);
    if (NULL == messages  )
        return NULL;

    MessageQueue = malloc(sizeof(message_queue_t));
    if (NULL == MessageQueue  ) {
        free(messages);
    } else {
        message_init_generic(MessageQueue, messages, ElementSize, NoElements);
    }

    return MessageQueue;
}

static message_queue_t* message_create_queue(size_t ElementSize,
        unsigned int NoElements)
{
    /* assertions defered to message_create_generic */
    return message_create_generic(ElementSize, NoElements);
}

/*
 * Message queue with timeout functions
 */

static int semaphore_wait_timeout(sem_t *sem, unsigned int time_out_ms)
{
    int status, time_out = 0;

    while (time_out <= time_out_ms) {
        /*
         * sem_trywait immediately returns 0 if it is avaialble,
         * otherwise it immediately returns -1 with EAGAIN error code
         */
        status = sem_trywait(sem);
        if (!status)
            break;

        if (time_out == time_out_ms) {
            //printf("1 semaphore_wait_timeout: timed out\n");
            return -1;
        }
        /* sleep for 10ms */
        usleep(10*1000);
        time_out+=10;
    }

    if (time_out <= time_out_ms) {
        return 0;
    } else {
        printf("2 semaphore_wait_timeout: timed out\n");
        return -1;
    }
}

static HI_VOID* message_half_remove_timeout(message_half_t* MessageHalf, unsigned int time_out)
{
    message_hdr_t* Message;
    int result;

    if (!MessageHalf) {
        printf("FATAL! message_half_remove_timeout: NULL MessageHalf\n");
        return NULL;
    }

    result = semaphore_wait_timeout(&MessageHalf->message_half_sem, time_out);
    if (-1 == result  ) {
        //printf("FATAL! message_half_remove_timeout: semaphore_wait_timeout failure\n");
        return NULL;
    }


    result = pthread_mutex_lock(&MessageHalf->message_half_mutex);
    if (result != 0) {
        printf("FATAL! message_half_remove_timeout: pthread_mutex_lock failure\n");
        return NULL;
    }

    Message                        = MessageHalf->message_half_head;
    MessageHalf->message_half_head = Message->message_hdr_next;

    result = pthread_mutex_unlock(&MessageHalf->message_half_mutex);
    if (result != 0) {
        printf("FATAL! message_half_remove_timeout: pthread_mutex_unlock failure\n");
        return NULL;
    }

    return Message + 1;
}

static HI_VOID* message_receive_timeout (message_queue_t* MessageQueue, unsigned int time_out)
{
    if (!MessageQueue) {
        printf("FATAL! message_receive_timeout: NULL MessageQueue\n");
        return NULL;
    }
    /* other assertions defered to message_half_remove_timeout */
    return message_half_remove_timeout(&MessageQueue->message_queue_queue, time_out);
}

static HI_VOID* message_claim_timeout (message_queue_t* MessageQueue, unsigned int time_out)
{
    if (!MessageQueue) {
        printf("FATAL! message_claim_timeout: NULL MessageQueue\n");
        return NULL;
    }

    /* other assertions defered to message_half_remove_timeout */
    return message_half_remove_timeout(&MessageQueue->message_queue_free, time_out);
}

/*
 * Message queue vector functions
 */

static HI_VOID message_delete_queue (message_queue_t* MessageQueue)
{
    if (!MessageQueue) {
        printf("FATAL! message_delete_queue: NULL MessageQueue\n");
        return;
    }

    message_uninit_queue(MessageQueue);
    free(MessageQueue->message_queue_memory);
    free(MessageQueue);
}

HI_MsgQueue_p HI_OSMsgQueueCreate(size_t           MessageSize,
        unsigned int     Messages)
{
    return message_create_queue(MessageSize, Messages);
}

HI_VOID HI_OSMsgQueueDel(HI_MsgQueue_p Queue)
{
    message_delete_queue(Queue);
}

HI_VOID* HI_OSMsgClaim(HI_MsgQueue_p Queue, unsigned int Timeout_MS)
{
    if (!Timeout_MS) {
        return message_claim(Queue);
    } else {    
        return message_claim_timeout(Queue, Timeout_MS);
    }
}

HI_VOID HI_OSMsgSend(HI_MsgQueue_p Queue, HI_VOID *Message)
{
    message_send(Queue, Message);
}

HI_VOID *HI_OSMsgReceive(HI_MsgQueue_p Queue, unsigned int Timeout_MS)
{
    if (!Timeout_MS) {
        return message_receive(Queue);
    } else {    
        return message_receive_timeout(Queue, Timeout_MS);
    }
}

HI_VOID HI_OSMsgRelease(HI_MsgQueue_p Queue, HI_VOID *Message)
{
    message_release(Queue, Message);
}

HI_S32 HI_OSSemCreate(sem_t *pSem, HI_U32 u32StartCount)
{
    return semaphore_create(pSem, u32StartCount);
}

HI_VOID HI_OSSemDelete(sem_t *pSem)
{
    semaphore_delete(pSem);
}

HI_S32 HI_OSSemWait(sem_t *pSem)
{
    return semaphore_wait(pSem);
}

HI_S32 HI_OSSemWaitTimeout(sem_t *pSem, HI_U32 u32Timeout)
{
    return semaphore_wait_timeout(pSem, u32Timeout);
}

HI_S32 HI_OSSemNoWait(sem_t *pSem)
{
    return semaphore_nowait(pSem);
}


HI_S32 HI_OSSemSignal(sem_t *pSem)
{
    return semaphore_signal(pSem);
}




