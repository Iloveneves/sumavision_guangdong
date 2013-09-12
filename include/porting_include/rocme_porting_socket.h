/*******************************************************************************
File name   : rocme_porting_socket.h

Author		: XXX			

Description : The poriting interface & macro definition for Socket module.
	          
Copyright (C) BeiJing SUMAVision, Inc., 2009 .All rights reserved.

History		:
				2009.12.20  		Created 					
*******************************************************************************/
#ifndef _ROCME_PORTING_SOCKET_H_
#define _ROCME_PORTING_SOCKET_H_

#include "rocme_porting_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
����socket������
*/
#define ROC_SOCKET_ERROR_BASE 10000
#define ROC_EUNKONWN          (ROC_SOCKET_ERROR_BASE+0)
#define ROC_EWOULDBLOCK       (ROC_SOCKET_ERROR_BASE+1)
#define ROC_EINPROGRESS       (ROC_SOCKET_ERROR_BASE+2)
#define ROC_EALREADY          (ROC_SOCKET_ERROR_BASE+3)
#define ROC_ENOTSOCK          (ROC_SOCKET_ERROR_BASE+4)
#define ROC_EDESTADDRREQ      (ROC_SOCKET_ERROR_BASE+5)
#define ROC_EMSGSIZE          (ROC_SOCKET_ERROR_BASE+6)
#define ROC_EPROTOTYPE        (ROC_SOCKET_ERROR_BASE+7)
#define ROC_ENOPROTOOPT       (ROC_SOCKET_ERROR_BASE+8)
#define ROC_EPROTONOSUPPORT   (ROC_SOCKET_ERROR_BASE+9)
#define ROC_ESOCKTNOSUPPORT   (ROC_SOCKET_ERROR_BASE+10)
#define ROC_EOPNOTSUPP        (ROC_SOCKET_ERROR_BASE+11)
#define ROC_EPFNOSUPPORT      (ROC_SOCKET_ERROR_BASE+12)
#define ROC_EAFNOSUPPORT      (ROC_SOCKET_ERROR_BASE+13)
#define ROC_EADDRINUSE        (ROC_SOCKET_ERROR_BASE+14)
#define ROC_EADDRNOTAVAIL     (ROC_SOCKET_ERROR_BASE+15)
#define ROC_ENETDOWN          (ROC_SOCKET_ERROR_BASE+16)
#define ROC_ENETUNREACH       (ROC_SOCKET_ERROR_BASE+17)
#define ROC_ENETRESET         (ROC_SOCKET_ERROR_BASE+18)
#define ROC_ECONNABORTED      (ROC_SOCKET_ERROR_BASE+19)
#define ROC_ECONNRESET        (ROC_SOCKET_ERROR_BASE+20)
#define ROC_ENOBUFS           (ROC_SOCKET_ERROR_BASE+21)
#define ROC_EISCONN           (ROC_SOCKET_ERROR_BASE+22)
#define ROC_ENOTCONN          (ROC_SOCKET_ERROR_BASE+23)
#define ROC_ESHUTDOWN         (ROC_SOCKET_ERROR_BASE+24)
#define ROC_ETOOMANYREFS      (ROC_SOCKET_ERROR_BASE+25)
#define ROC_ETIMEDOUT         (ROC_SOCKET_ERROR_BASE+26)
#define ROC_ECONNREFUSED      (ROC_SOCKET_ERROR_BASE+27)
#define ROC_ELOOP             (ROC_SOCKET_ERROR_BASE+28)
#define ROC_ENAMETOOLONG      (ROC_SOCKET_ERROR_BASE+29)
#define ROC_EHOSTDOWN         (ROC_SOCKET_ERROR_BASE+30)
#define ROC_EHOSTUNREACH      (ROC_SOCKET_ERROR_BASE+31)
#define ROC_ENOTEMPTY         (ROC_SOCKET_ERROR_BASE+32)
#define ROC_EPROCLIM          (ROC_SOCKET_ERROR_BASE+33)
#define ROC_EUSERS            (ROC_SOCKET_ERROR_BASE+34)
#define ROC_EDQUOT            (ROC_SOCKET_ERROR_BASE+35)
#define ROC_ESTALE            (ROC_SOCKET_ERROR_BASE+36)
#define ROC_EREMOTE           (ROC_SOCKET_ERROR_BASE+37)
#define ROC_EINVAL            (ROC_SOCKET_ERROR_BASE+38)
#define ROC_EINTR             (ROC_SOCKET_ERROR_BASE+39)

/*
roc_sockaddr_in ��Աsin_addrʹ��
*/
#define ROC_INADDR_ANY       0          /* ������ַ */
#define ROC_INADDR_BROADCAST 0xffffffff /* �㲥��ַ */

/*
rocme_porting_socket ����domainʹ��
����ѡ������ͨ�ŵ�Э���壬��֧��tcp/ipЭ�鼴��
*/
#define ROC_AF_INET 2 /* Internet IP Protocol*/


/*
rocme_porting_socket ����typeʹ��
�׽�������(TCP/UDP/RAW)
*/
#define ROC_SOCK_STREAM 1
#define ROC_SOCK_DGRAM  2
#define ROC_SOCK_RAW    3


/*
rocme_porting_socket_send/sendto rocme_porting_socket_recv/recvfrom ����flagsʹ��
flags: ������������߶����־������壬��ͨ��or��������һ��
*/
enum
{
    ROC_MSG_OOB       = 0x01,   /* Process out-of-band data.          */
    ROC_MSG_PEEK      = 0x02,   /* Peek at incoming messages.         */
    ROC_MSG_DONTROUTE = 0x04,   /* Don't use local routing.           */
    ROC_MSG_CTRUNC    = 0x08,   /* Control data lost before delivery. */
    ROC_MSG_PROXY     = 0x10,   /* Supply or ask second address.      */
    ROC_MSG_TRUNC     = 0x20,
    ROC_MSG_DONTWAIT  = 0x40,   /* Nonblocking IO.                    */
    ROC_MSG_EOR       = 0x80,   /* End of record.                     */
    ROC_MSG_WAITALL   = 0x100,  /* Wait for a full request.           */
    ROC_MSG_FIN       = 0x200,
    ROC_MSG_SYN       = 0x400,
    ROC_MSG_CONFIRM   = 0x800,  /* Confirm path validity.             */
    ROC_MSG_RST       = 0x1000,
    ROC_MSG_ERRQUEUE  = 0x2000, /* Fetch message from error queue.    */
    ROC_MSG_NOSIGNAL  = 0x4000, /* Do not generate SIGPIPE.           */
    ROC_MSG_MORE      = 0x8000  /* Sender will send more.             */
};


/*
rocme_porting_socket_setsockopt/getsockopt ����levelʹ��
*/
#define ROC_IPPROTO_IP  0 /* IPѡ��         */
#define ROC_SOL_SOCKET  1 /* ͨ���׽���ѡ�� */
#define ROC_IPPROTO_TCP 6 /* TCPѡ��        */

/*
rocme_porting_socket_setsockopt/getsockopt ����optnameʹ��
��level=ROC_SOL_SOCKETʱ��optnameѡ�������ֵ
*/
#define ROC_SO_DEBUG       1  /* �򿪻�ر��Ŵ�ģʽ                       */
#define ROC_SO_REUSEADDR   2  /* ������bind�����б��ص�ַ���ظ�ʹ��       */ 
#define ROC_SO_TYPE        3  /* ����socket��̬                           */ 
#define ROC_SO_ERROR       4  /* �򿪻�ر��Ŵ�ģʽ                       */ 
#define ROC_SO_DONTROUTE   5  /* �ͳ������ݰ���Ҫ����·���豸������       */ 
#define ROC_SO_BROADCAST   6  /* ʹ�ù㲥��ʽ����                         */ 
#define ROC_SO_SNDBUF      7  /* �����ͳ����ݴ�����С                     */ 
#define ROC_SO_RCVBUF      8  /* ���ý��յ��ݴ�����С                     */ 
#define ROC_SO_KEEPALIVE   9  /* ����ȷ�������Ƿ�����ֹ                   */ 
#define ROC_SO_OOBINLINE   10 /* �����յ�OOB ����ʱ������������׼�����豸 */ 
#define ROC_SO_NO_CHECK    11 /* �򿪻�ر�У���                         */ 
#define ROC_SO_PRIORITY    12 /* �������׽��ַ��͵����а���Э�鶨������Ȩ */ 
#define ROC_SO_LINGER      13 /* ȷ�����ݰ�ȫ�ҿɿ��Ĵ��ͳ�ȥ             */ 
#define ROC_SO_RCVTIMEO    20 /* ���ý��ճ�ʱʱ��                         */
#define ROC_SO_SNDTIMEO    21 /* ���÷��ͳ�ʱʱ��                         */


/*
rocme_porting_socket_setsockopt/getsockopt ����optnameʹ��
��level=ROC_IPPROTO_IPʱ��optnameѡ�������ֵ
*/     
#define ROC_IP_TOS     1 /* ��������             */
#define ROC_IP_TTL     2 /* ����ʱ��             */ 
#define ROC_IP_HDRINCL 3 /* �����ݰ��а���IP�ײ� */
#define ROC_IP_OPTIONS 4 /* IP�ײ�ѡ��           */

/*
rocme_porting_socket_setsockopt/getsockopt ����optnameʹ��
��level=ROC_IPPROTO_TCPʱ��optnameѡ�������ֵ
*/
#define ROC_TCP_NODELAY 1 /* ��ʹ��Nagle�㷨     */
#define ROC_TCP_MAXSEG  2 /* TCP������ݶεĴ�С */

/*
rocme_porting_socket_shutdown ����howʹ��
*/
enum
{
    ROC_SHUT_RD = 0, /* No more receptions.                  */
    ROC_SHUT_WR,     /* No more transmissions.               */
    ROC_SHUT_RDWR    /* No more receptions or transmissions. */
};

/*
rocme_porting_socket_ioctl ����cmdʹ��
*/
#define ROC_FIONBIO  0 /* ��������ñ��׽ӿڵķ�������־ */
#define ROC_FIONREAD 1 /* ��ȡ���ջ������е��ֽ���       */


#define ROC_IP_MULTICAST_IF    32 /* ָ������ಥ���ݱ�������ӿ� */
#define ROC_IP_MULTICAST_TTL   33 /* TTL��                        */
#define ROC_IP_MULTICAST_LOOP  34 /* �Ƿ��ֹ����                 */
#define ROC_IP_ADD_MEMBERSHIP  35 /* ����һ���ಥ��               */
#define ROC_IP_DROP_MEMBERSHIP 36 /* �뿪һ���ಥ��               */


#define ROC_INVALID_SOCKET      (-1) /*invalid socket */

#define ROC_FD_SETSIZE          32

/* Internet address (a structure for historical reasons) */
struct roc_in_addr {
    UINT32_T addr;
};

struct roc_sockaddr_in {
    UINT16_T sin_family;         /* Address family               */
    UINT16_T sin_port;           /* Port number                  */
    struct roc_in_addr sin_addr; /* Internet address             */
    UINT8_T  sin_zero[8];        /* Same size as struct sockaddr */
};

struct roc_sockaddr {
    UINT16_T sa_family; /* address family */
    CHAR_T sa_data[14]; /* up to 14 bytes of direct address */
};

struct roc_timeval {
    long tv_sec;  /* seconds          */
    long tv_usec; /* and microseconds */
};

/* Description of data base entry for a single host.  */
struct roc_hostent
{
    CHAR_T *h_name;           /* Official name of host.  */
    CHAR_T **h_aliases;       /* Alias list.  */
    INT32_T h_addrtype;       /* Host address type.  */
    INT32_T h_length;         /* Length of address.  */
    CHAR_T **h_addr_list;     /* List of addresses from name server.  */
#define h_addr h_addr_list[0] /* Address, for backward compatibility.  */
};

typedef struct
{
    INT32_T words[ROC_FD_SETSIZE];
}roc_fd_set;

/*
rocme_porting_socket_setsockopt/rocme_porting_socket_getsockopt
����optname��ROC_SO_LINGERѡ��ʱ,����optvalʹ�øýṹ
���Ƶ�����close����ʱ�׽ӿ���ιر�
*/
struct roc_linger {
    INT32_T l_onoff;  /* �Ƿ����l_linger������       */
    INT32_T l_linger; /* �ر��׽ӿڵĳ�ʱʱ�ޣ���λ�� */
};


typedef struct roc_ip_mreq {
    struct roc_in_addr imr_multiaddr;     /*�鲥���IP��ַ*/
    struct roc_in_addr imr_interface; /*����ĳһ�����豸�ӿڵ�IP��ַ*/
}roc_ip_mreq;


/*****************************************************************************
����˵��: 
    socket�׽��ֵĳ�ʼ��

����˵��:
    ��
    
����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_socket_init(void);


/*****************************************************************************
����˵��:
    socket�׽��ִ��� 

����˵��:
    �������:
        [domain  ] ָ����ʹ�õ�Э���� ROC_AF_INNET
        [type    ] ��������:ROC_SOCK_STREAM
                            ROC_SOCK_DGRAM
                            ROC_SOCK_RAW
        [protocol] ����Ϊ0
    
����:
    ʧ��: -1
    �ɹ�: socket���
*****************************************************************************/
INT32_T rocme_porting_socket(INT32_T domain, INT32_T type, INT32_T protocol);


/*****************************************************************************
����˵��:
    TCP�ͻ�����TCP��������������
    
����˵��:
    �������:
        [s      ] socket���
        [name   ] �󶨵ı���Э���ַ����������Э�飬��IP��ַ�Ͷ˿�
                  ���IP��ַ��ֵΪROC_INADDR_ANY����ϵͳ���Զ����뱾��IP��ַ
                  ����˿ڸ�ֵΪ0����ϵͳ�Զ�ѡ��һ�����õĶ˿�
        [namelen] ��ַ�ṹ��Ĵ�С��sizeof(roc_sockaddr)

����:
    ʧ��: -1              
    �ɹ�:  0

*****************************************************************************/
INT32_T rocme_porting_socket_connect(INT32_T s, const struct roc_sockaddr *name, INT32_T namelen);


/*****************************************************************************
����˵��: 
    socket�׽��ְ󶨶˿�
����˵��:
    �������:
        [s      ] socket���
        [name   ] �󶨵ı���Э���ַ����������Э�飬��IP��ַ�Ͷ˿�
                  ���IP��ַ��ֵΪROC_INADDR_ANY����ϵͳ���Զ����뱾��IP��ַ
                  ����˿ڸ�ֵΪ0����ϵͳ�Զ�ѡ��һ�����õĶ˿�
        [namelen] ��ַ�ṹ��Ĵ�С��sizeof(roc_sockaddr)
    
����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_socket_bind(INT32_T s, struct roc_sockaddr *name, INT32_T namelen);



/*****************************************************************************
����˵��:
    ����һ��δ���ӵ��׽ӿ��ϵ���������
    
����˵��:
    �������:
        [s      ] socket�ľ��
        [backlog] ���ͬʱ������
    
����:
    ʧ��: -1              
    �ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_socket_listen(INT32_T s, INT32_T backlog);


/*****************************************************************************
����˵��:
    ����һ������ɵ�����, ��ִ��rocme_porting_socket_listen֮�������ִ��
    
����˵��:
    �������:
        [s      ] socket���
    �������:
        [name   ] ���������ӵĿͻ��˵�Э���ַ��ΪNULL���򲻷���
        [namelen] �����׽ӿڵ�ַ�ṹ��Ĵ�С��ΪNULL���򲻷���
    
��    ��:
    ʧ��: -1              
    �ɹ�: �����ӵ��׽ӿ�������
*****************************************************************************/
INT32_T rocme_porting_socket_accept(INT32_T s, struct roc_sockaddr *name, INT32_T *namelen);


/*****************************************************************************
����˵��:
    �ر��׽ӿڣ�����ֹ����

����˵��:
    �������:
        [s] Ҫ�رյ� socket��� 
    
��    ��:
    ʧ��: -1              
    �ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_socket_close(INT32_T s);


/*****************************************************************************
����˵��:
    �ر�����
    
����˵��:
    �������:
        [s  ] Ҫ�رյ� socket��� 
        [how] �ر����ӷ�ʽ
    
��    ��:
    ʧ��: -1              
    �ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_socket_shutdown(INT32_T s, INT32_T how);


/*****************************************************************************
����˵��:
    ������������
    
����˵��:
    �������:
        [s:     ] socket���
        [dataptr] �������ݵĻ�������
        [size:  ] ����������󳤶�
        [flags: ] 0                ������ʽ
        	      ROC_MSG_DONTWAIT ��������ʽ,�������ӽ϶�����
        	      ROC_MSG_OOB      �����������
    
��    ��:
    ʧ��: -1              
    �ɹ�: �������ݵ��ֽ���
*****************************************************************************/
INT32_T rocme_porting_socket_send(INT32_T s, const void *dataptr, INT32_T size, UINT32_T flags);


/*****************************************************************************
����˵��:
    ������������
    
����˵��:
    �������:
        [s      ] socket���
        [dataptr] �洢�������ݵĻ�������
        [size   ] ����������󳤶�
        [flags  ] 0                ������ʽ
        	      ROC_MSG_DONTWAIT ��������ʽ,�������ӽ϶�����
        	      ROC_MSG_OOB      �����������
        [to     ] ���ݽ����ߵ��׽ӿڵ�ַ
        [tolen  ] to�׽ӿڵ�ַ�Ĵ�С
    
��    ��:
    ʧ��: -1              
    �ɹ�: �������ݵ��ֽ���
*****************************************************************************/
INT32_T rocme_porting_socket_sendto( INT32_T s, const void *dataptr, INT32_T size, UINT32_T flags, struct roc_sockaddr *to, INT32_T tolen);


/*****************************************************************************
����˵��:
    ���շ��ص�����

����˵��:
    �������:
        [s    ] socket���
        [len  ] ����������󳤶�
        [flags] 0                ������ʽ
        	    ROC_MSG_DONTWAIT ��������ʽ,�������ӽ϶�����
        	    ROC_MSG_OOB      ���ⷢ������(��������й�,�е����Ļ�����)
    ���������
        [mem ]  ��Ž������ݵĻ�����
    
��   ��: 
    ʧ��: -1
	�ɹ�: ���յ������ݳ���

*****************************************************************************/
INT32_T rocme_porting_socket_recv(INT32_T s, void *mem, INT32_T len, UINT32_T flags);


/*****************************************************************************
����˵��:
    ���շ��ص�����
    
����˵��:
    ���������
        [s    ] socket���
        [mem  ] �洢�������ݵĻ�������
        [len  ] ����������󳤶�
        [flags] 0                ������ʽ
        	    ROC_MSG_DONTWAIT ��������ʽ,�������ӽ϶�����
        	    ROC_MSG_OOB      ���ⷢ������(��������й�,�е����Ļ�����)    
    ���������
        [mem    ] ��Ž������ݵĻ�����
        [from   ] ���ط����ߵ��׽ӿڵ�ַ
        [fromlen] �׽ӿڵ�ַ�ĳ���

��   ��: 
    ʧ��: -1
	�ɹ�: ���յ������ݳ���
*******************************************************************************/
INT32_T rocme_porting_socket_recvfrom(INT32_T s, void *mem, INT32_T len, UINT32_T flags, struct roc_sockaddr *from, INT32_T *fromlen);


/*****************************************************************************
����˵��:
    �����׽���ѡ��
    
����˵��:
    �������:
        [s      ] Ҫ���õ�socket���
        [level  ] ָ�������׽��ֵĲ��
        [optname] ָ�����Ƶķ�ʽ
        [optval ] �����׽���ѡ��.����ѡ�����Ƶ��������ͽ���ת��
                  ��optname��ROC_SO_LINGERѡ��ʱ��,optval���ݽ�������һ��ָ��roc_linger���ݽṹ��ָ��
        [optlen ] optval�ĳ���
    
��    ��:
    ʧ��: -1
	�ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_socket_setsockopt (INT32_T s, INT32_T level, INT32_T optname, const void *optval, INT32_T optlen);


/*****************************************************************************
����˵��:
    ��ȡ�׽���ѡ��
    
����˵��:
    �������:
        [s      ] Ҫ���õ�socket���
        [level  ] ָ�������׽��ֵĲ��
        [optname] ָ�����Ƶķ�ʽ
    �������:
        [optval ] ��ȡ�׽���ѡ��.����ѡ�����Ƶ��������ͽ���ת��
                  ��optname��ROC_SO_LINGERѡ��ʱ��,optval���ݽ�������һ��ָ��roc_linger���ݽṹ��ָ��
                  ��level��ROC_IPPROTO_IP, optname��IP_MULTICAST_IFʱ��, optval���ݽ�������һ��ָ��roc_ip_mreq���ݽṹ��ָ��
        [optlen ] optval�ĳ���
    
��    ��:
    ʧ��: -1
	�ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_socket_getsockopt(INT32_T s,INT32_T level,INT32_T optname,void *optval,INT32_T *optlen);


/*****************************************************************************
����˵��:
    ����Ƿ��յ����ĵ��׽����¼�   
    
����˵��:
    �������:  
	    [maxfdp1  ] ���ĵ�����׽��� + 1
        [readset  ] �����Ƿ�ɶ����׽��ֵļ���; NULL��������
        [writeset ] �����Ƿ��д���׽��ֵļ���; NULL��������
        [exceptset] �����Ƿ����쳣���׽��ֵļ���; NULL��������
        [timeout  ] �����ͺ�������Ϊ0 - ���ȴ���ָ��ֵ - �ȴ�һ��ʱ��; NULL - ��Զ����ȥ
    
��    ��:
    �ɹ�: �����׽��ֵ���Ŀ
    ʧ��: -1
    ��ʱ:  0
*****************************************************************************/
INT32_T rocme_porting_socket_select(INT32_T maxfdp1, roc_fd_set *readset, roc_fd_set *writeset, roc_fd_set *exceptset,struct roc_timeval *timeout);


/*****************************************************************************
����˵��:
    �õ�ϵͳ��ͬʱ�����socket��������
    
����˵��:
        ��
    
��    ��:
    ʧ��: -1
    �ɹ�: ϵͳ��ͬʱ�����socket��������
*****************************************************************************/
INT32_T rocme_porting_get_max_sockets( void );


/*****************************************************************************
����˵��:
    ͨ����������ȡ������ַ��Ϣ
    
����˵��:
    �������: 
        [name] ������
    
��    ��:
    ʧ��: NULL
    �ɹ�: ���ؽṹroc_hostent
*****************************************************************************/
struct roc_hostent* rocme_porting_socket_gethostbyname(const CHAR_T *name);


/*****************************************************************************
����˵��:
    ͨ��IP��ַ(xxx.xxx.xxx.xxx)��ȡ������ַ��Ϣ
    
����˵��:
    �������: 
        [addr] IP��ַ(xxx.xxx.xxx.xxx)
        [len ]  addr�ĳ���
        [type] ROC_AF_INET
    
��    ��:
    ʧ��: NULL
    �ɹ�: ���ؽṹroc_hostent
*****************************************************************************/
struct roc_hostent *rocme_porting_socket_gethostbyaddr(const CHAR_T * addr, INT32_T len, INT32_T type);


/*****************************************************************************
����˵��:
    ������׽ӿڹ����ı���Э���ַ
    
����˵��:
    �������: 
        [s      ] socket���
    �������: 
        [name   ] �������׽ӿڹ����ı���Э���ַ
        [namelen] �����׽��ֵ�ַ�ṹ��Ĵ�С

��    ��:
    ʧ��: -1
    �ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_socket_getsockname (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen);


/*****************************************************************************
����˵��:
    ������׽ӿڹ�����Զ��Э���ַ
    
����˵��:
    �������: 
        [s      ] socket���
    �������: 
        [name   ] �������׽ӿڹ�����Զ��Э���ַ
        [namelen] �����׽��ֵ�ַ�ṹ��Ĵ�С

��    ��:
    ʧ��: -1
    �ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_socket_getpeername (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen);



/*****************************************************************************
����˵��:
    ���������
    
����˵��:
    �������: 
        [namelen ] hostname �Ĵ�С
    �������: 
        [hostname] ����������

��    ��:
    ʧ��: -1
    �ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_socket_gethostname(CHAR_T* hostname,INT32_T namelen);


/*****************************************************************************
����˵��:
    �ַ���(x.x.x.x)תΪ32λ��������ֵ
    
����˵��:
    �������: 
        [strptr ] �ַ���(x.x.x.x)
    �������: 
        [addrptr] ����32λ��������ֵ

��    ��:
    ʧ��: -1
    �ɹ�: 0
*****************************************************************************/
INT32_T rocme_porting_socket_inet_aton (const CHAR_T *strptr, struct roc_in_addr *addrptr);


/*****************************************************************************
����˵��:
    �ַ���(x.x.x.x)תΪ32λ��������ֵ
    
����˵��:
    �������: 
        [strptr] �ַ���(x.x.x.x)

��    ��:
    ʧ��: -1
    �ɹ�: 32λ��������ֵ
*****************************************************************************/
UINT32_T rocme_porting_socket_inet_addr (const CHAR_T *strptr);


/*****************************************************************************
����˵��:
    32λ��������ֵתΪ�ַ���(x.x.x.x)
    
����˵��:
    �������: 
        [inaddr] 32λ��������ֵ

��    ��:
    ʧ��: -1
    �ɹ�: �ַ���(x.x.x.x)
*****************************************************************************/
CHAR_T* rocme_porting_socket_inet_ntoa (struct roc_in_addr inaddr);


/*****************************************************************************
����˵��:
    ���һ���ļ���������
    
����˵��:
    �������:
        [set] �ļ���������

��   ��: 
    ʧ��: -1
	�ɹ�: 0
*******************************************************************************/
INT32_T rocme_porting_socket_fd_zero(roc_fd_set *set);


/*****************************************************************************
����˵��:
    ��һ���ļ������������ļ�����������
    
����˵��:
    �������:
        [fd ] �ļ�������
        [set] �ļ���������

��   ��: 
    ʧ��: -1
	�ɹ�: 0
*******************************************************************************/
INT32_T rocme_porting_socket_fd_set(INT32_T fd, roc_fd_set *set);

/*****************************************************************************
����˵��:
    ��һ���ļ����������ļ��������������
    
����˵��:
    �������:
        [fd ] �ļ�������
        [set] �ļ���������

��   ��: 
    ʧ��: -1
	�ɹ�: 0
*******************************************************************************/
INT32_T rocme_porting_socket_fd_clr(INT32_T fd, roc_fd_set *set);


/*****************************************************************************
����˵��:
    ���ж��Ƿ��ļ�����������λ
    
����˵��:
    �������:
        [fd ] �ļ�������
        [set] �ļ���������

��   ��: 
     1 ����λ 
     0 δ��λ
*******************************************************************************/
INT32_T rocme_porting_socket_fd_isset(INT32_T fd, roc_fd_set *set);


/*****************************************************************************
����˵��:
    �׽��ֿ��Ʋ���
    
����˵��:
    �������:
        [s  ] socket���
        [cmd] ����
        	ROC_FIONBIO:  ��������ñ��׽ӿڵķ�������־
        	ROC_FIONREAD: ��ȡ���ջ������е��ֽ���
        [arg] ����
        	��cmd=ROC_FIONBIO  arg=1 ����Ϊ������ģʽ arg=0 ����Ϊ����ģʽ
        	��cmd=ROC_FIONREAD arg���ػ�ȡ���ֽ���
    
��    ��:
    ʧ��: -1
	�ɹ�:  0
*****************************************************************************/
INT32_T rocme_porting_socket_ioctl(INT32_T s, UINT32_T cmd, void *argp);



/*****************************************************************************
����˵��:
    ��32λ�����ַ�˳��ת���������ַ�˳��
    
����˵��:
    �������:
        [hostlong] 32λ�����ַ�
    
��    ��: 
    ��Ӧ�������ַ�˳��

*****************************************************************************/
UINT32_T rocme_porting_socket_htonl(UINT32_T hostlong);


/*****************************************************************************
����˵��:
    ��16λ�����ַ�˳��ת���������ַ�˳��
    
����˵��:
    �������:
        [hostshort] 16λ�����ַ�
    
��    ��: 
    ��Ӧ�������ַ�˳��
*****************************************************************************/
UINT16_T rocme_porting_socket_htons(UINT16_T hostshort); 

/*****************************************************************************
����˵��:
    ��32λ�����ַ�˳��ת���������ַ�˳��
    
����˵��:
    �������:
        [netlong] 32λ�����ַ�
    
��    ��: 
    ��Ӧ�������ַ�˳��
*****************************************************************************/
UINT32_T rocme_porting_socket_ntohl(UINT32_T netlong); 

/*****************************************************************************
����˵��:
    ��16λ�����ַ�˳��ת���������ַ�˳��
    
����˵��:
    �������:
        [netshort] 16λ�����ַ�
    
��   ��: 
    ��Ӧ�������ַ�˳��
*****************************************************************************/
UINT16_T rocme_porting_socket_ntohs(UINT16_T netshort);

/*****************************************************************************
����˵��:
��ȡ���socket�����Ĵ����룬�ýӿڱ�����socket������
�жϲ�������ֵ������ٵ��øýӿڻ�ȡ�����룬�����ȡ��ֵ������
�ô�������ܱ�����������д��������Ҫ��ȡ�Ĵ�����Ľӿں���������

����˵��:
�������:
��

��   ��: 
���һ��socket�����Ĵ�����
*****************************************************************************/
INT32_T rocme_porting_socket_get_last_errno(void);

/*****************************************************************************
����˵��:
�������socket�����Ĵ����룬�ýӿڱ�����socket������
�жϲ�������ֵ������ٵ��øýӿڻ�ȡ�����룬�����ȡ��ֵ������
�ô�������ܱ�����������д��������Ҫ��ȡ�Ĵ�����Ľӿں���������

����˵��:
�������:
��

��   ��: 
���һ��socket�����Ĵ�����
*****************************************************************************/
void rocme_porting_socket_set_errno(INT32_T nErr);


#ifdef __cplusplus
}
#endif

#endif


