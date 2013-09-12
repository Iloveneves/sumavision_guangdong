#ifndef TX_HI_OS_H
#define TX_HI_OS_H

#include <pthread.h>
#include <semaphore.h>

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#ifndef	FALSE
#define	FALSE	0
#endif

#ifndef	TRUE
#define	TRUE	1
#endif

#define DOFUNCERRPRINT(func)\
do{\
    HI_S32 s32Ret = func;\
    if(s32Ret != HI_SUCCESS)\
        HI_DBG("%s failed !!in %s at %d line ret = 0x%x\n""\033[0m", #func, __FUNCTION__, __LINE__, s32Ret);\
}while(0)


/* message */

typedef struct message_hdr_s
{
    struct message_hdr_s* message_hdr_next;
} message_hdr_t;

typedef struct message_half_s
{
    message_hdr_t*       message_half_head;
    message_hdr_t*       message_half_tail;
    sem_t        message_half_sem;    /* used for sync purpose */
    pthread_mutex_t    message_half_mutex;    /* guard queue ops */
} message_half_t;

typedef struct message_queue_s
{
    message_half_t                      message_queue_free;
    message_half_t                      message_queue_queue;
    HI_VOID*                               message_queue_memory;
} message_queue_t;

typedef message_queue_t HI_MsgQueue_t;  /* for init function */
typedef message_queue_t * HI_MsgQueue_p;  /* message queue handle */

HI_MsgQueue_p HI_OSMsgQueueCreate(size_t MessageSize, unsigned int Messages);

HI_VOID HI_OSMsgQueueDel(HI_MsgQueue_p Queue);

HI_VOID* HI_OSMsgClaim(HI_MsgQueue_p Queue, unsigned int Timeout_MS);

HI_VOID HI_OSMsgSend(HI_MsgQueue_p Queue, HI_VOID *Message);

HI_VOID *HI_OSMsgReceive(HI_MsgQueue_p Queue, unsigned int Timeout_MS);

HI_VOID HI_OSMsgRelease(HI_MsgQueue_p Queue, HI_VOID *Message);

HI_S32 HI_OSSemCreate(sem_t *pSem, HI_U32 u32StartCount);

HI_VOID HI_OSSemDelete(sem_t *pSem);

HI_S32 HI_OSSemWait(sem_t *pSem);

HI_S32 HI_OSSemWaitTimeout(sem_t *pSem, HI_U32 u32Timeout);

HI_S32 HI_OSSemNoWait(sem_t *pSem);

HI_S32 HI_OSSemSignal(sem_t *pSem);

HI_VOID HI_DBG(const char *fmt, ...);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif/*__MSG_Q_H*/

