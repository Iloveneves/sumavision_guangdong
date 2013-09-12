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
定义socket错误码
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
roc_sockaddr_in 成员sin_addr使用
*/
#define ROC_INADDR_ANY       0          /* 本机地址 */
#define ROC_INADDR_BROADCAST 0xffffffff /* 广播地址 */

/*
rocme_porting_socket 参数domain使用
用于选择用于通信的协议族，仅支持tcp/ip协议即可
*/
#define ROC_AF_INET 2 /* Internet IP Protocol*/


/*
rocme_porting_socket 参数type使用
套接字类型(TCP/UDP/RAW)
*/
#define ROC_SOCK_STREAM 1
#define ROC_SOCK_DGRAM  2
#define ROC_SOCK_RAW    3


/*
rocme_porting_socket_send/sendto rocme_porting_socket_recv/recvfrom 参数flags使用
flags: 是以下零个或者多个标志的组合体，可通过or操作连在一起
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
rocme_porting_socket_setsockopt/getsockopt 参数level使用
*/
#define ROC_IPPROTO_IP  0 /* IP选项         */
#define ROC_SOL_SOCKET  1 /* 通用套接字选项 */
#define ROC_IPPROTO_TCP 6 /* TCP选项        */

/*
rocme_porting_socket_setsockopt/getsockopt 参数optname使用
当level=ROC_SOL_SOCKET时，optname选用下面的值
*/
#define ROC_SO_DEBUG       1  /* 打开或关闭排错模式                       */
#define ROC_SO_REUSEADDR   2  /* 允许在bind过程中本地地址可重复使用       */ 
#define ROC_SO_TYPE        3  /* 返回socket形态                           */ 
#define ROC_SO_ERROR       4  /* 打开或关闭排错模式                       */ 
#define ROC_SO_DONTROUTE   5  /* 送出的数据包不要利用路由设备来传输       */ 
#define ROC_SO_BROADCAST   6  /* 使用广播方式传送                         */ 
#define ROC_SO_SNDBUF      7  /* 设置送出的暂存区大小                     */ 
#define ROC_SO_RCVBUF      8  /* 设置接收的暂存区大小                     */ 
#define ROC_SO_KEEPALIVE   9  /* 定期确定连线是否已终止                   */ 
#define ROC_SO_OOBINLINE   10 /* 当接收到OOB 数据时会马上送至标准输入设备 */ 
#define ROC_SO_NO_CHECK    11 /* 打开或关闭校验和                         */ 
#define ROC_SO_PRIORITY    12 /* 设置在套接字发送的所有包的协议定义优先权 */ 
#define ROC_SO_LINGER      13 /* 确保数据安全且可靠的传送出去             */ 
#define ROC_SO_RCVTIMEO    20 /* 设置接收超时时间                         */
#define ROC_SO_SNDTIMEO    21 /* 设置发送超时时间                         */


/*
rocme_porting_socket_setsockopt/getsockopt 参数optname使用
当level=ROC_IPPROTO_IP时，optname选用下面的值
*/     
#define ROC_IP_TOS     1 /* 服务类型             */
#define ROC_IP_TTL     2 /* 生存时间             */ 
#define ROC_IP_HDRINCL 3 /* 在数据包中包含IP首部 */
#define ROC_IP_OPTIONS 4 /* IP首部选项           */

/*
rocme_porting_socket_setsockopt/getsockopt 参数optname使用
当level=ROC_IPPROTO_TCP时，optname选用下面的值
*/
#define ROC_TCP_NODELAY 1 /* 不使用Nagle算法     */
#define ROC_TCP_MAXSEG  2 /* TCP最大数据段的大小 */

/*
rocme_porting_socket_shutdown 参数how使用
*/
enum
{
    ROC_SHUT_RD = 0, /* No more receptions.                  */
    ROC_SHUT_WR,     /* No more transmissions.               */
    ROC_SHUT_RDWR    /* No more receptions or transmissions. */
};

/*
rocme_porting_socket_ioctl 参数cmd使用
*/
#define ROC_FIONBIO  0 /* 清除或设置本套接口的非阻塞标志 */
#define ROC_FIONREAD 1 /* 获取接收缓存区中的字节数       */


#define ROC_IP_MULTICAST_IF    32 /* 指定外出多播数据报的外出接口 */
#define ROC_IP_MULTICAST_TTL   33 /* TTL数                        */
#define ROC_IP_MULTICAST_LOOP  34 /* 是否禁止回馈                 */
#define ROC_IP_ADD_MEMBERSHIP  35 /* 加入一个多播组               */
#define ROC_IP_DROP_MEMBERSHIP 36 /* 离开一个多播组               */


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
参数optname是ROC_SO_LINGER选项时,参数optval使用该结构
控制当调用close函数时套接口如何关闭
*/
struct roc_linger {
    INT32_T l_onoff;  /* 是否关心l_linger的设置       */
    INT32_T l_linger; /* 关闭套接口的超时时限，单位秒 */
};


typedef struct roc_ip_mreq {
    struct roc_in_addr imr_multiaddr;     /*组播组的IP地址*/
    struct roc_in_addr imr_interface; /*本地某一网络设备接口的IP地址*/
}roc_ip_mreq;


/*****************************************************************************
功能说明: 
    socket套接字的初始化

参数说明:
    无
    
返回:
    失败: -1              
    成功:  0
*****************************************************************************/
INT32_T rocme_porting_socket_init(void);


/*****************************************************************************
功能说明:
    socket套接字创建 

参数说明:
    输入参数:
        [domain  ] 指明所使用的协议族 ROC_AF_INNET
        [type    ] 连接类型:ROC_SOCK_STREAM
                            ROC_SOCK_DGRAM
                            ROC_SOCK_RAW
        [protocol] 设置为0
    
返回:
    失败: -1
    成功: socket句柄
*****************************************************************************/
INT32_T rocme_porting_socket(INT32_T domain, INT32_T type, INT32_T protocol);


/*****************************************************************************
功能说明:
    TCP客户端与TCP服务器建立连接
    
参数说明:
    输入参数:
        [s      ] socket句柄
        [name   ] 绑定的本地协议地址，对于网际协议，即IP地址和端口
                  如果IP地址赋值为ROC_INADDR_ANY，则系统会自动填入本机IP地址
                  如果端口赋值为0，则系统自动选择一个可用的端口
        [namelen] 地址结构体的大小，sizeof(roc_sockaddr)

返回:
    失败: -1              
    成功:  0

*****************************************************************************/
INT32_T rocme_porting_socket_connect(INT32_T s, const struct roc_sockaddr *name, INT32_T namelen);


/*****************************************************************************
功能说明: 
    socket套接字绑定端口
参数说明:
    输入参数:
        [s      ] socket句柄
        [name   ] 绑定的本地协议地址，对于网际协议，即IP地址和端口
                  如果IP地址赋值为ROC_INADDR_ANY，则系统会自动填入本机IP地址
                  如果端口赋值为0，则系统自动选择一个可用的端口
        [namelen] 地址结构体的大小，sizeof(roc_sockaddr)
    
返回:
    失败: -1              
    成功:  0
*****************************************************************************/
INT32_T rocme_porting_socket_bind(INT32_T s, struct roc_sockaddr *name, INT32_T namelen);



/*****************************************************************************
功能说明:
    接受一个未连接的套接口上的连接请求
    
参数说明:
    输入参数:
        [s      ] socket的句柄
        [backlog] 最大同时连接数
    
返回:
    失败: -1              
    成功:  0
*****************************************************************************/
INT32_T rocme_porting_socket_listen(INT32_T s, INT32_T backlog);


/*****************************************************************************
功能说明:
    返回一个已完成的连接, 在执行rocme_porting_socket_listen之后的立即执行
    
参数说明:
    输入参数:
        [s      ] socket句柄
    输出参数:
        [name   ] 返回已连接的客户端的协议地址，为NULL，则不返回
        [namelen] 返回套接口地址结构体的大小，为NULL，则不返回
    
返    回:
    失败: -1              
    成功: 已连接的套接口描述字
*****************************************************************************/
INT32_T rocme_porting_socket_accept(INT32_T s, struct roc_sockaddr *name, INT32_T *namelen);


/*****************************************************************************
功能说明:
    关闭套接口，并终止连接

参数说明:
    输入参数:
        [s] 要关闭的 socket句柄 
    
返    回:
    失败: -1              
    成功: 0
*****************************************************************************/
INT32_T rocme_porting_socket_close(INT32_T s);


/*****************************************************************************
功能说明:
    关闭连接
    
参数说明:
    输入参数:
        [s  ] 要关闭的 socket句柄 
        [how] 关闭连接方式
    
返    回:
    失败: -1              
    成功: 0
*****************************************************************************/
INT32_T rocme_porting_socket_shutdown(INT32_T s, INT32_T how);


/*****************************************************************************
功能说明:
    发送请求数据
    
参数说明:
    输入参数:
        [s:     ] socket句柄
        [dataptr] 发送数据的缓存区；
        [size:  ] 缓存区的最大长度
        [flags: ] 0                阻塞方式
        	      ROC_MSG_DONTWAIT 非阻塞方式,用于连接较多的情况
        	      ROC_MSG_OOB      带外接收数据
    
返    回:
    失败: -1              
    成功: 发送数据的字节数
*****************************************************************************/
INT32_T rocme_porting_socket_send(INT32_T s, const void *dataptr, INT32_T size, UINT32_T flags);


/*****************************************************************************
功能说明:
    发送请求数据
    
参数说明:
    输入参数:
        [s      ] socket句柄
        [dataptr] 存储接收数据的缓存区；
        [size   ] 缓存区的最大长度
        [flags  ] 0                阻塞方式
        	      ROC_MSG_DONTWAIT 非阻塞方式,用于连接较多的情况
        	      ROC_MSG_OOB      带外接收数据
        [to     ] 数据接收者的套接口地址
        [tolen  ] to套接口地址的大小
    
返    回:
    失败: -1              
    成功: 发送数据的字节数
*****************************************************************************/
INT32_T rocme_porting_socket_sendto( INT32_T s, const void *dataptr, INT32_T size, UINT32_T flags, struct roc_sockaddr *to, INT32_T tolen);


/*****************************************************************************
功能说明:
    接收返回的数据

参数说明:
    输入参数:
        [s    ] socket句柄
        [len  ] 缓存区的最大长度
        [flags] 0                阻塞方式
        	    ROC_MSG_DONTWAIT 非阻塞方式,用于连接较多的情况
        	    ROC_MSG_OOB      带外发送数据(与紧急包有关,有单独的缓冲区)
    输出参数：
        [mem ]  存放接收数据的缓冲区
    
返   回: 
    失败: -1
	成功: 接收到的数据长度

*****************************************************************************/
INT32_T rocme_porting_socket_recv(INT32_T s, void *mem, INT32_T len, UINT32_T flags);


/*****************************************************************************
功能说明:
    接收返回的数据
    
参数说明:
    输入参数：
        [s    ] socket句柄
        [mem  ] 存储接收数据的缓存区；
        [len  ] 缓存区的最大长度
        [flags] 0                阻塞方式
        	    ROC_MSG_DONTWAIT 非阻塞方式,用于连接较多的情况
        	    ROC_MSG_OOB      带外发送数据(与紧急包有关,有单独的缓冲区)    
    输出参数：
        [mem    ] 存放接收数据的缓冲区
        [from   ] 返回发送者的套接口地址
        [fromlen] 套接口地址的长度

返   回: 
    失败: -1
	成功: 接收到的数据长度
*******************************************************************************/
INT32_T rocme_porting_socket_recvfrom(INT32_T s, void *mem, INT32_T len, UINT32_T flags, struct roc_sockaddr *from, INT32_T *fromlen);


/*****************************************************************************
功能说明:
    设置套接字选项
    
参数说明:
    输入参数:
        [s      ] 要设置的socket句柄
        [level  ] 指定控制套接字的层次
        [optname] 指定控制的方式
        [optval ] 设置套接字选项.根据选项名称的数据类型进行转换
                  当optname是ROC_SO_LINGER选项时候,optval传递进来的是一个指向roc_linger数据结构的指针
        [optlen ] optval的长度
    
返    回:
    失败: -1
	成功: 0
*****************************************************************************/
INT32_T rocme_porting_socket_setsockopt (INT32_T s, INT32_T level, INT32_T optname, const void *optval, INT32_T optlen);


/*****************************************************************************
功能说明:
    获取套接字选项
    
参数说明:
    输入参数:
        [s      ] 要设置的socket句柄
        [level  ] 指定控制套接字的层次
        [optname] 指定控制的方式
    输出参数:
        [optval ] 获取套接字选项.根据选项名称的数据类型进行转换
                  当optname是ROC_SO_LINGER选项时候,optval传递进来的是一个指向roc_linger数据结构的指针
                  当level是ROC_IPPROTO_IP, optname是IP_MULTICAST_IF时候, optval传递进来的是一个指向roc_ip_mreq数据结构的指针
        [optlen ] optval的长度
    
返    回:
    失败: -1
	成功: 0
*****************************************************************************/
INT32_T rocme_porting_socket_getsockopt(INT32_T s,INT32_T level,INT32_T optname,void *optval,INT32_T *optlen);


/*****************************************************************************
功能说明:
    检查是否收到关心的套接字事件   
    
参数说明:
    输入参数:  
	    [maxfdp1  ] 关心的最大套接字 + 1
        [readset  ] 关心是否可读的套接字的集合; NULL代表不关心
        [writeset ] 关心是否可写的套接字的集合; NULL代表不关心
        [exceptset] 关心是否有异常的套接字的集合; NULL代表不关心
        [timeout  ] 秒数和毫秒数都为0 - 不等待；指定值 - 等待一段时间; NULL - 永远等下去
    
返    回:
    成功: 就绪套接字的数目
    失败: -1
    超时:  0
*****************************************************************************/
INT32_T rocme_porting_socket_select(INT32_T maxfdp1, roc_fd_set *readset, roc_fd_set *writeset, roc_fd_set *exceptset,struct roc_timeval *timeout);


/*****************************************************************************
功能说明:
    得到系统能同时处理的socket的最大个数
    
参数说明:
        无
    
返    回:
    失败: -1
    成功: 系统能同时处理的socket的最大个数
*****************************************************************************/
INT32_T rocme_porting_get_max_sockets( void );


/*****************************************************************************
功能说明:
    通过主机名获取主机地址信息
    
参数说明:
    输入参数: 
        [name] 主机名
    
返    回:
    失败: NULL
    成功: 返回结构roc_hostent
*****************************************************************************/
struct roc_hostent* rocme_porting_socket_gethostbyname(const CHAR_T *name);


/*****************************************************************************
功能说明:
    通过IP地址(xxx.xxx.xxx.xxx)获取主机地址信息
    
参数说明:
    输入参数: 
        [addr] IP地址(xxx.xxx.xxx.xxx)
        [len ]  addr的长度
        [type] ROC_AF_INET
    
返    回:
    失败: NULL
    成功: 返回结构roc_hostent
*****************************************************************************/
struct roc_hostent *rocme_porting_socket_gethostbyaddr(const CHAR_T * addr, INT32_T len, INT32_T type);


/*****************************************************************************
功能说明:
    获得与套接口关联的本地协议地址
    
参数说明:
    输入参数: 
        [s      ] socket句柄
    输出参数: 
        [name   ] 返回与套接口关联的本地协议地址
        [namelen] 返回套接字地址结构体的大小

返    回:
    失败: -1
    成功: 0
*****************************************************************************/
INT32_T rocme_porting_socket_getsockname (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen);


/*****************************************************************************
功能说明:
    获得与套接口关联的远端协议地址
    
参数说明:
    输入参数: 
        [s      ] socket句柄
    输出参数: 
        [name   ] 返回与套接口关联的远端协议地址
        [namelen] 返回套接字地址结构体的大小

返    回:
    失败: -1
    成功: 0
*****************************************************************************/
INT32_T rocme_porting_socket_getpeername (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen);



/*****************************************************************************
功能说明:
    获得主机名
    
参数说明:
    输入参数: 
        [namelen ] hostname 的大小
    输出参数: 
        [hostname] 返回主机名

返    回:
    失败: -1
    成功: 0
*****************************************************************************/
INT32_T rocme_porting_socket_gethostname(CHAR_T* hostname,INT32_T namelen);


/*****************************************************************************
功能说明:
    字符串(x.x.x.x)转为32位网络序数值
    
参数说明:
    输入参数: 
        [strptr ] 字符串(x.x.x.x)
    输出参数: 
        [addrptr] 返回32位网络序数值

返    回:
    失败: -1
    成功: 0
*****************************************************************************/
INT32_T rocme_porting_socket_inet_aton (const CHAR_T *strptr, struct roc_in_addr *addrptr);


/*****************************************************************************
功能说明:
    字符串(x.x.x.x)转为32位网络序数值
    
参数说明:
    输入参数: 
        [strptr] 字符串(x.x.x.x)

返    回:
    失败: -1
    成功: 32位网络序数值
*****************************************************************************/
UINT32_T rocme_porting_socket_inet_addr (const CHAR_T *strptr);


/*****************************************************************************
功能说明:
    32位网络序数值转为字符串(x.x.x.x)
    
参数说明:
    输入参数: 
        [inaddr] 32位网络序数值

返    回:
    失败: -1
    成功: 字符串(x.x.x.x)
*****************************************************************************/
CHAR_T* rocme_porting_socket_inet_ntoa (struct roc_in_addr inaddr);


/*****************************************************************************
功能说明:
    清除一个文件描述符集
    
参数说明:
    输入参数:
        [set] 文件描述符集

返   回: 
    失败: -1
	成功: 0
*******************************************************************************/
INT32_T rocme_porting_socket_fd_zero(roc_fd_set *set);


/*****************************************************************************
功能说明:
    将一个文件描述符加入文件描述符集中
    
参数说明:
    输入参数:
        [fd ] 文件描述符
        [set] 文件描述符集

返   回: 
    失败: -1
	成功: 0
*******************************************************************************/
INT32_T rocme_porting_socket_fd_set(INT32_T fd, roc_fd_set *set);

/*****************************************************************************
功能说明:
    将一个文件描述符从文件描述符集中清除
    
参数说明:
    输入参数:
        [fd ] 文件描述符
        [set] 文件描述符集

返   回: 
    失败: -1
	成功: 0
*******************************************************************************/
INT32_T rocme_porting_socket_fd_clr(INT32_T fd, roc_fd_set *set);


/*****************************************************************************
功能说明:
    试判断是否文件描述符被置位
    
参数说明:
    输入参数:
        [fd ] 文件描述符
        [set] 文件描述符集

返   回: 
     1 被置位 
     0 未置位
*******************************************************************************/
INT32_T rocme_porting_socket_fd_isset(INT32_T fd, roc_fd_set *set);


/*****************************************************************************
功能说明:
    套接字控制操作
    
参数说明:
    输入参数:
        [s  ] socket句柄
        [cmd] 命令
        	ROC_FIONBIO:  清除或设置本套接口的非阻塞标志
        	ROC_FIONREAD: 获取接收缓存区中的字节数
        [arg] 参数
        	在cmd=ROC_FIONBIO  arg=1 设置为非阻塞模式 arg=0 设置为阻塞模式
        	在cmd=ROC_FIONREAD arg返回获取的字节数
    
返    回:
    失败: -1
	成功:  0
*****************************************************************************/
INT32_T rocme_porting_socket_ioctl(INT32_T s, UINT32_T cmd, void *argp);



/*****************************************************************************
功能说明:
    将32位主机字符顺序转换成网络字符顺序
    
参数说明:
    输入参数:
        [hostlong] 32位主机字符
    
返    回: 
    对应的网络字符顺序

*****************************************************************************/
UINT32_T rocme_porting_socket_htonl(UINT32_T hostlong);


/*****************************************************************************
功能说明:
    将16位主机字符顺序转换成网络字符顺序
    
参数说明:
    输入参数:
        [hostshort] 16位主机字符
    
返    回: 
    对应的网络字符顺序
*****************************************************************************/
UINT16_T rocme_porting_socket_htons(UINT16_T hostshort); 

/*****************************************************************************
功能说明:
    将32位网络字符顺序转换成主机字符顺序
    
参数说明:
    输入参数:
        [netlong] 32位网络字符
    
返    回: 
    对应的主机字符顺序
*****************************************************************************/
UINT32_T rocme_porting_socket_ntohl(UINT32_T netlong); 

/*****************************************************************************
功能说明:
    将16位网络字符顺序转换成主机字符顺序
    
参数说明:
    输入参数:
        [netshort] 16位网络字符
    
返   回: 
    对应的主机字符顺序
*****************************************************************************/
UINT16_T rocme_porting_socket_ntohs(UINT16_T netshort);

/*****************************************************************************
功能说明:
获取最后socket操作的错误码，该接口必须在socket操作后，
判断操作返回值错误后再调用该接口获取错误码，否则获取的值无意义
该错误码可能被其他操作改写，需在需要获取的错误码的接口后立即调用

参数说明:
输入参数:
无

返   回: 
最后一次socket操作的错误码
*****************************************************************************/
INT32_T rocme_porting_socket_get_last_errno(void);

/*****************************************************************************
功能说明:
设置最后socket操作的错误码，该接口必须在socket操作后，
判断操作返回值错误后再调用该接口获取错误码，否则获取的值无意义
该错误码可能被其他操作改写，需在需要获取的错误码的接口后立即调用

参数说明:
输入参数:
无

返   回: 
最后一次socket操作的错误码
*****************************************************************************/
void rocme_porting_socket_set_errno(INT32_T nErr);


#ifdef __cplusplus
}
#endif

#endif


