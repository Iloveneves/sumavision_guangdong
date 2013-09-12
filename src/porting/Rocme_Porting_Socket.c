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
#include <stdio.h>
#include <stdlib.h>
	
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/ioctl.h>
	
#include "rocme_porting_socket.h"
	
#define _M_SPRINT 
#ifdef  _M_SPRINT    
#define sprint(msg, args...) printf(msg, ##args) 
#else
#define sprint(msg, args...)
#endif
	
	
	INT32_T rocme_porting_socket_init(void)
	{
		return 0;
	}
	
	INT32_T rocme_porting_socket(INT32_T domain, INT32_T type, INT32_T protocol)
	{
		return socket( domain, type, protocol );
	}
	
	INT32_T rocme_porting_socket_connect(INT32_T s, const struct roc_sockaddr *name, INT32_T namelen)
	{
		//printf("port num = 0x%x\n", *(struct sockaddr *)name);
	
		return connect( s, (struct sockaddr *)name, namelen );
	}
	
	INT32_T rocme_porting_socket_bind(INT32_T s, struct roc_sockaddr *name, INT32_T namelen)
	{
		return bind( s, (struct sockaddr *)name, namelen );
	}
	
	INT32_T rocme_porting_socket_listen(INT32_T s, INT32_T backlog)
	{
		return listen( s, backlog );
	}
	
	INT32_T rocme_porting_socket_accept(INT32_T s, struct roc_sockaddr *name, INT32_T *namelen)
	{
		return accept( s, (struct sockaddr *)name, (socklen_t*)namelen );
	}
	
	INT32_T rocme_porting_socket_close(INT32_T s)
	{
		return close(s);
	}
	
	INT32_T rocme_porting_socket_shutdown(INT32_T s, INT32_T how)
	{
		return shutdown(s, how );
	}
	
	INT32_T rocme_porting_socket_send(INT32_T s, const void *dataptr, INT32_T size, UINT32_T flags)
	{
		return send( s, dataptr, size, flags );
	}
	
	INT32_T rocme_porting_socket_sendto( INT32_T s, const void *dataptr, INT32_T size, UINT32_T flags, struct roc_sockaddr *to, INT32_T tolen)
	{
		return sendto( s, dataptr, size, flags, (struct sockaddr *)to, tolen );
	}
	
	INT32_T rocme_porting_socket_recv(INT32_T s, void *mem, INT32_T len, UINT32_T flags)
	{
		return recv(s, mem, len, flags );
	}
	
	INT32_T rocme_porting_socket_recvfrom(INT32_T s, void *mem, INT32_T len, UINT32_T flags, struct roc_sockaddr *from, INT32_T *fromlen)
	{
		return recvfrom(s, mem, len, flags, (struct sockaddr *)from, (socklen_t*)fromlen );
	}
	
	INT32_T rocme_porting_socket_setsockopt (INT32_T s, INT32_T level, INT32_T optname, const void *optval, INT32_T optlen)
	{
		return setsockopt (s, level, optname, optval, optlen);
	}
	
	
	INT32_T rocme_porting_socket_getsockopt(INT32_T s,INT32_T level,INT32_T optname,void *optval,INT32_T *optlen)
	{
		return getsockopt( s, level, optname, optval, (socklen_t*)optlen);
	}
	
	INT32_T rocme_porting_socket_select(INT32_T maxfdp1, roc_fd_set *readset, roc_fd_set *writeset, roc_fd_set *exceptset,struct roc_timeval *timeout)
	{
		fd_set freadset, fwriteset, fexceptset;
		fd_set * pfreadset = NULL;
		fd_set * pfwriteset = NULL;
		fd_set * pfexceptset = NULL;
		
		INT32_T i32ErrCode;
		INT32_T i = 0;
	
		if(readset != NULL)
		{
			FD_ZERO(&freadset);
	
			for(i =0; i < ROC_FD_SETSIZE; i++)
			{
				if(1 == readset->words[i])
				{
					FD_SET(i, &freadset);
				}
			}
	
			pfreadset = &freadset;
		}
	
		if(writeset != NULL)
		{
			FD_ZERO(&fwriteset);
			
			for(i =0; i < ROC_FD_SETSIZE; i++)
			{
				if(1 == writeset->words[i])
				{
					FD_SET(i, &fwriteset);
				}
			}
	
			pfwriteset = &fwriteset;
		}
	
		if(exceptset != NULL)
		{
			FD_ZERO(&fexceptset);
			
			for(i =0; i < ROC_FD_SETSIZE; i++)
			{
				if(1 == exceptset->words[i])
				{
					FD_SET(i, &fexceptset);
				}
			}
	
			pfexceptset = &fexceptset;
		}
	
		i32ErrCode = select(maxfdp1, &freadset, &fwriteset, &fexceptset, (struct timeval *)timeout);
		
		if(0 != i32ErrCode)
		{
			return i32ErrCode;
		}
	
	
		if(readset != NULL)
		{
			for(i = 0; i < 32; i++)
			{
				if(FD_ISSET(i, &freadset))
				{
					readset->words[i] = 1;
				}
			}
		}
	
		 if(writeset != NULL)
		{
			for(i = 0; i < 32; i++)
			{
				if(FD_ISSET(i, &fwriteset))
				{
					writeset->words[i] = 1;
				}
			 }
		}
	
		 
		if(exceptset != NULL)
		{
			for(i = 0; i < 32; i++)
			{
				if(FD_ISSET(i, &fexceptset))
				{
					exceptset->words[i] = 1;
				}
			}
		}
	
		return i32ErrCode;
	}
	
	INT32_T rocme_porting_get_max_sockets( void )
	{
		return 1024;
	}
	
	struct roc_hostent* rocme_porting_socket_gethostbyname(const CHAR_T *name)
	{
		if (strncmp(name, "localhost", strlen("localhost")) == 0)
		{
			static struct hostent stlocal;
			static char LocalIp[4] = {0x7f, 0x00, 0x00, 0x01};
			static char LocalName[] = "localhost";
			char *p = LocalIp;
			
			memset(&stlocal, 0, sizeof(stlocal));
			stlocal.h_name = LocalName;
			stlocal.h_addrtype = 2;
			stlocal.h_length = 4;
			stlocal.h_addr_list = &p;
			return &stlocal;
		}
		return (struct roc_hostent*)gethostbyname(name);
	}
	
	struct roc_hostent *rocme_porting_socket_gethostbyaddr(const CHAR_T * addr, INT32_T len, INT32_T type)
	{
		return (struct roc_hostent *)gethostbyaddr(addr,  len,	type);
	}
	
	INT32_T rocme_porting_socket_getsockname (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen)
	{
		return getsockname (s, (struct sockaddr *)name, (socklen_t*)namelen);
	}
	
	INT32_T rocme_porting_socket_getpeername (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen)
	{
		return getpeername (s, (struct sockaddr *)name, (socklen_t*)namelen);
	}
	
	INT32_T rocme_porting_socket_gethostname(CHAR_T* hostname,INT32_T namelen)
	{
		return gethostname(hostname, namelen);
	}
	
	INT32_T rocme_porting_socket_inet_aton (const CHAR_T *strptr, struct roc_in_addr *addrptr)
	{
		return inet_aton(strptr, (struct in_addr *)addrptr);
	}
	
	//INT32_T rocme_porting_socket_inet_addr (const CHAR_T *strptr)
	UINT32_T rocme_porting_socket_inet_addr (const CHAR_T *strptr)	
	{
#if 0
		int a,b,c,d;
		printf("[%s.%d] param=%s\n",__FUNCTION__,__LINE__,strptr);
		sscanf(strptr,"%d.%d.%d.%d",&a,&b,&c,&d);
		return (a<<24)|(b<<16)|(c<<8)|d;
#endif
		return inet_addr( strptr);
	}
	
	CHAR_T* rocme_porting_socket_inet_ntoa(struct roc_in_addr inaddr )
	{
		struct in_addr in;
	
		in.s_addr = inaddr.addr;
		printf("[%s.%d] param=0x%x\n",__FUNCTION__,__LINE__,inaddr.addr);
		return inet_ntoa( in );
	}
	
	INT32_T rocme_porting_socket_fd_zero(roc_fd_set *set)
	{
		FD_ZERO((fd_set*)set);
		return 0;
	}
	
	INT32_T rocme_porting_socket_fd_set(INT32_T fd, roc_fd_set *set)
	{
		FD_SET(fd, (fd_set*)set);
		return 0;
	}
	
	INT32_T rocme_porting_socket_fd_clr(INT32_T fd, roc_fd_set *set)
	{
		FD_CLR(fd, (fd_set*)set);
		return 0;
	}
	
	INT32_T rocme_porting_socket_fd_isset(INT32_T fd, roc_fd_set *set)
	{
		return FD_ISSET(fd, (fd_set*)set);
	}
	
	INT32_T rocme_porting_socket_ioctl(INT32_T s, UINT32_T cmd, void *argp)
	{
		switch( cmd )
		{
		case ROC_FIONBIO:
			{
				cmd = FIONBIO;
			}
			break;
		case ROC_FIONREAD:
			{
				cmd = FIONREAD;
			}
			break;
		default:
			{
				sprint( "###[rocme_porting_socket_ioctl] unkown cmd %d !!!!\n", cmd );
			}
			break;
		}
		return ioctl( s, cmd, argp );
	}
	
	UINT32_T rocme_porting_socket_htonl(UINT32_T hostlong)
	{
		return htonl(hostlong);
	}
	
	UINT16_T rocme_porting_socket_htons(UINT16_T hostshort)
	{
		return htons(hostshort);
	}
	
	UINT32_T rocme_porting_socket_ntohl(UINT32_T netlong)
	{
		return ntohl(netlong);
	}
	
	UINT16_T rocme_porting_socket_ntohs(UINT16_T netshort)
	{
		return ntohs(netshort);
	}
	
	INT32_T rocme_porting_socket_get_last_errno(void){return 0;}
	void rocme_porting_socket_set_errno(INT32_T nErr){return 0;}

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "signal.h"
#include <stdarg.h>
#include <math.h>
#include <memory.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/mman.h>
//#include <asm/page.h> 
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <dirent.h>
#include <utime.h>
#include <ctype.h>


#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <net/if.h> 
#include <net/if_arp.h> 
#include <net/route.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h> 
#include <net/if_arp.h> 

#include "hi_type.h"


#include "porter_rocme.h"

#define MAX_SOCKETS             (16)
#define CONNECT_TIMEOUT         (8)
#define INVALID_SOCKET_ID       (-1)


#define ROCME_NFDBITS            (8 * sizeof(UINT32_T))
#define ROCME_FD_SET_SIZE        (16)


typedef struct tagSocketMgr
{
    INT32_T enable;
    INT32_T sockfd;
} socketMgr;

static socketMgr pSocketMgr[MAX_SOCKETS];

static INT32_T socketMgr_getidx(INT32_T sockfd)
{
    INT32_T index = 0;
    
    for (index = 0; index < MAX_SOCKETS; index++)
    {
        if (sockfd == pSocketMgr[index].sockfd)
        {
            break;
        }
    }

    if (MAX_SOCKETS <= index)
    {
        return HI_FAILURE;
    }

    return index;
}



static INT32_T socketMgr_set(INT32_T index, INT32_T sockfd)
{
	ROCME_TEST_PRINT
    if (MAX_SOCKETS < index || index < 0)
    {
        return HI_FAILURE;
    }

    pSocketMgr[index].enable = HI_TRUE;
    pSocketMgr[index].sockfd = sockfd;

    return HI_SUCCESS;
}


static HI_VOID socketMgr_close(INT32_T sockfd)
{
	ROCME_TEST_PRINT
    INT32_T index = 0;
    
    for (index = 0; index < MAX_SOCKETS; index++)
    {
        if (sockfd == pSocketMgr[index].sockfd)
        {
            pSocketMgr[index].enable = HI_FALSE;
            pSocketMgr[index].sockfd = INVALID_SOCKET_ID;
            break;
        }
    }    
}

/*****************************************************************************
功能说明: 
    socket套接字的初始化

参数说明:
    无
    
返回:
    失败: -1              
    成功:  0
*****************************************************************************/
INT32_T rocme_porting_socket_init(void)
{
	ROCME_TEST_PRINT

	INT32_T index = 0;
    
    for (index=0; index<MAX_SOCKETS; index++)
    {
        pSocketMgr[index].enable = HI_FALSE;
        pSocketMgr[index].sockfd = INVALID_SOCKET_ID;
    }

    return ROC_OK;
}


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
INT32_T rocme_porting_socket(INT32_T domain, INT32_T type, INT32_T protocol)
{
	ROCME_TEST_PRINT
	HI_S32 s = ROC_ERR;
    HI_S32 domain2 = 0, type2 = 0;
    HI_S32 s32idx = 0;



    s32idx = socketMgr_getidx(INVALID_SOCKET_ID);
    CHK_RETURN((s32idx != HI_FAILURE), ROC_ERR);

    domain2 =AF_INET;
    type2 = (ROC_SOCK_STREAM==type) ? SOCK_STREAM : SOCK_DGRAM;
    s = socket(domain2, type2, 0);
    CHK_RETURN((s >= 0), ROC_ERR);

    socketMgr_set(s32idx, s);
	
	
    return s;
}


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
INT32_T rocme_porting_socket_connect(INT32_T s, const struct roc_sockaddr *name, INT32_T namelen)
{
	ROCME_TEST_PRINT
	HI_S32 ret = ROC_ERR;
	struct sockaddr  serv_addr;


	if ((name == NULL) || (namelen == 0))
	{
		return ret;
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sa_family = name->sa_family;
	memcpy(serv_addr.sa_data,name->sa_data,14);
	
	ret = connect(s, &serv_addr, sizeof(serv_addr));

	if (ret != ROC_OK)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket connect err\r\n");
		ret = ROC_ERR;
	}

	return ret;
}


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
INT32_T rocme_porting_socket_bind(INT32_T s, struct roc_sockaddr *name, INT32_T namelen)
{
	ROCME_TEST_PRINT

	HI_S32 ret = ROC_ERR;
	struct sockaddr  serv_addr;
	
	
	if ((name == NULL) || (namelen == 0))
	{
		return ret;
	}
	
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sa_family = name->sa_family;
	memcpy(serv_addr.sa_data,name->sa_data,14);
	
	ret = bind(s, &serv_addr, sizeof(serv_addr));
	
	if (ret != ROC_OK)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket bind err\r\n");
		ret = ROC_ERR;
	}
	
	return ret;

}



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
INT32_T rocme_porting_socket_listen(INT32_T s, INT32_T backlog)
{
	ROCME_TEST_PRINT
	HI_S32 ret = ROC_ERR;


    ret = listen(s, backlog);

    if (ret != ROC_OK)
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket accept err\r\n");
        ret = ROC_ERR;
    }

    return ret;
}


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
INT32_T rocme_porting_socket_accept(INT32_T s, struct roc_sockaddr *name, INT32_T *namelen)
{
	ROCME_TEST_PRINT
    HI_S32 ret = ROC_ERR;
    struct sockaddr serv_addr = {0};
    INT32_T slen = sizeof(serv_addr);
    INT32_T s32idx = 0;
	


    s32idx = socketMgr_getidx(INVALID_SOCKET_ID);
    CHK_RETURN((s32idx != HI_FAILURE), ROC_ERR);

    bzero(&serv_addr,sizeof(serv_addr));
    ret = accept(s, (struct sockaddr*) &serv_addr, (socklen_t *)&slen);

    if (ret >= 0)
    {
       	name->sa_family = serv_addr.sa_family;
        memcpy(name->sa_data,serv_addr.sa_data,14);
        socketMgr_set(s32idx, ret);

        return ret;
    }
    else
    {		
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket accept err\r\n");
        ret = ROC_ERR;
    }

    return ret;
}


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
INT32_T rocme_porting_socket_close(INT32_T s)
{
	ROCME_TEST_PRINT
    HI_S32 ret = ROC_ERR;


    socketMgr_close(s);

    ret = close(s);

    if (ret != ROC_ERR)
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket close err\r\n");
        ret = ROC_ERR;
    }
    
    return ret;
}


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
INT32_T rocme_porting_socket_shutdown(INT32_T s, INT32_T how)
{
	ROCME_TEST_PRINT
    HI_S32 ret = ROC_ERR;


    //HISI_DBG("[ipanel_porting_socket_shutdown]s=%d, what=%d\n", sockfd, what);

    if (((how >= 0) && (how <= 2)))
    {
        ret = shutdown(s, how);
    }
    
    if (ret != ROC_OK)
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket shutdown err\r\n");
        ret = ROC_ERR;
    }
    
    return ret;
}


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
INT32_T rocme_porting_socket_send(INT32_T s, const void *dataptr, INT32_T size, UINT32_T flags)
{
	ROCME_TEST_PRINT

    HI_S32 ret = ROC_ERR;

    if ((!dataptr) || size<=0)
    {
        return ROC_ERR;
    }

    ret = send(s, dataptr, size, 0);


    if (ret < 0)
    {
	
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket send err\r\n");
        ret = ROC_ERR;
    }
    return ret;
}


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
INT32_T rocme_porting_socket_sendto( INT32_T s, const void *dataptr, INT32_T size, UINT32_T flags, struct roc_sockaddr *to, INT32_T tolen)
{
	ROCME_TEST_PRINT

	HI_S32 ret = ROC_ERR;
	struct sockaddr  serv_addr;
	HI_S32 slen = sizeof(serv_addr);
	
	if ((dataptr == NULL) || (size <= 0))
	{
		return ret;
	}
	
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sa_family = to->sa_family;
	memcpy(serv_addr.sa_data,to->sa_data,14);


    ret = sendto(s, dataptr, size, 0, &serv_addr, &slen);


    if (ret < 0)
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket sendto err\r\n");
        ret = ROC_ERR;
    }
	
    return ret;
}


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
INT32_T rocme_porting_socket_recv(INT32_T s, void *mem, INT32_T len, UINT32_T flags)
{
	ROCME_TEST_PRINT

    HI_S32 ret = ROC_ERR;

    if ((!mem) || len<=0)
    {
		return ROC_ERR;
    }

    ret = recv(s, mem, len, 0);

    if (ret < 0)
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket recv err\r\n");
        ret = ROC_ERR;
    }

    return ret;
}


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
INT32_T rocme_porting_socket_recvfrom(INT32_T s, void *mem, INT32_T len, UINT32_T flags, struct roc_sockaddr *from, INT32_T *fromlen)
{
	ROCME_TEST_PRINT

	HI_S32 ret = ROC_ERR;
	struct sockaddr  serv_addr;
	
	
    if ((!mem) || len<=0)
    {
		return ROC_ERR;
    }

	
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sa_family = from->sa_family;
	memcpy(serv_addr.sa_data,from->sa_data,14);


    ret = recvfrom(s, mem, len, 0, &serv_addr, sizeof(serv_addr));


    if (ret < 0)
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket recvfrom err\r\n");
        ret = ROC_ERR;
    }
	
    return ret;
}


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
INT32_T rocme_porting_socket_setsockopt (INT32_T s, INT32_T level, INT32_T optname, const void *optval, INT32_T optlen)
{
	ROCME_TEST_PRINT

	HI_S32 ret = ROC_ERR;
    
    if (level == SOL_SOCKET && optname == SO_LINGER)
    {

        ret = setsockopt(s, SOL_SOCKET, SO_LINGER, optval, sizeof(struct linger));
    }
	else
	{
		ret = ROC_ERR;
	}
    if (ret != ROC_OK)
    {
		ROCME_PRINTF(ROCME_LOG_ERROR,"socket setsockopt err\r\n");
        ret = ROC_ERR;
    }
    
    return ret;
}


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
INT32_T rocme_porting_socket_getsockopt(INT32_T s,INT32_T level,INT32_T optname,void *optval,INT32_T *optlen)
{
	ROCME_TEST_PRINT

	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}


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
INT32_T rocme_porting_socket_select(INT32_T maxfdp1, roc_fd_set *readset, roc_fd_set *writeset, roc_fd_set *exceptset,struct roc_timeval *timeout)
{
	ROCME_TEST_PRINT

		HI_S32 i = 0, j = 0, ret = ROC_ERR;
		struct timeval tm;
		fd_set fds_r ,fds_w ,fds_e;
		HI_S32 flag_r=0, flag_w=0, flag_e=0, maxfds = 0, sock = 0;
		UINT32_T fds_bits = 0;
	
		if ((maxfdp1 <= 0) || (maxfdp1 > ROCME_FD_SET_SIZE * ROCME_NFDBITS))
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"socket params err\r\n");
			return ROC_ERR;
		}
	
		if ((readset == NULL) && (writeset == NULL) && (exceptset == NULL))
		{
			
			ROCME_PRINTF(ROCME_LOG_ERROR,"socket params err\r\n");
			return ROC_ERR;
		}
	
		if (timeout == NULL) 
		{
			tm.tv_sec = 0xffffffff;
			tm.tv_usec = 0xffffffff;
		}
		else if ((timeout->tv_sec>= 0)||(timeout->tv_usec>=0)) 
		{
			tm.tv_sec = timeout->tv_sec;
			tm.tv_usec = timeout->tv_usec;
		}
		else 
		{
			return ret;
		}
	
		FD_ZERO(&fds_r);
		FD_ZERO(&fds_w);
		FD_ZERO(&fds_e);
	
		if (readset)
		{
			for (i = 0; i < ROCME_FD_SET_SIZE; i++)
			{
				if (0 == readset->words[i])
				{
					continue;
				}
	
				fds_bits = readset->words[i];
	
				if (!flag_r)
					flag_r = 1;
	
				for (j = 0; j < ROCME_NFDBITS; j++)
				{
					if (fds_bits&1)
					{
						sock = i * ROCME_NFDBITS + j;
						FD_SET(sock, &fds_r);
						maxfds = (sock > maxfds) ? sock : maxfds;
					}
	
					fds_bits >>= 1;
				}
			}
		}
	
		if (writeset)
		{
			for (i = 0; i < ROCME_FD_SET_SIZE; i++)
			{
				if (0 == writeset->words[i])
				{
					continue;
				}
	
				fds_bits = writeset->words[i];
	
				if (!flag_w)
					flag_w = 1;
	
				for (j = 0; j < ROCME_NFDBITS; j++)
				{
					if (fds_bits&1)
					{
						sock = i * ROCME_NFDBITS + j;
						FD_SET(sock, &fds_w);
						maxfds = (sock > maxfds) ? sock : maxfds;
					}
	
					fds_bits >>= 1;
				}
			}
		}
		
		if (exceptset)
		{
			for (i = 0; i < ROCME_FD_SET_SIZE; i++)
			{
				if (0 == exceptset->words[i])
				{
					continue;
				}
				
				fds_bits = exceptset->words[i];
	
				if (!flag_e)
					flag_e = 1;
				
				for (j = 0; j < ROCME_NFDBITS; j++)
				{
					if (fds_bits&1)
					{
						sock = i * ROCME_NFDBITS + j;
						FD_SET(sock, &fds_e);
						maxfds = (sock > maxfds) ? sock : maxfds;
					}
	
					fds_bits >>= 1;
				}
			}
		}
		
		if ((!flag_r) && (!flag_w) && (!flag_e))
			return ret;
		
		ret = select(maxfds + 1, &fds_r, &fds_w, &fds_e, &tm);
		
		if (ret < 0)
		{	
			ROCME_PRINTF(ROCME_LOG_ERROR,"socket select err\r\n");
			return ROC_ERR;
		}
		
		ret = ROC_OK;
		
		if (flag_r)
		{
			for (i = 0; i < ROCME_FD_SET_SIZE; i++)
			{
				if (0 == readset->words[i])
				{
					continue;
				}
	
				fds_bits = readset->words[i];
				readset->words[i] = 0;
				
				for (j = 0; j < ROCME_NFDBITS; j++)
				{
					sock = i * ROCME_NFDBITS + j;
					if ((fds_bits & 1) && FD_ISSET(sock, &fds_r))
					{
						readset->words[i] |= (1<<j);
					}
	
					fds_bits >>= 1;
				}
			}
		}
		
		if (flag_w)
		{
			for (i = 0; i < ROCME_FD_SET_SIZE; i++)
			{
				if (0 == writeset->words[i])
				{
					continue;
				}
				
				fds_bits = writeset->words[i];
				writeset->words[i] = 0;
				
				for (j = 0; j < ROCME_NFDBITS; j++)
				{
					sock = i * ROCME_NFDBITS + j;
					if ((fds_bits & 1) && FD_ISSET(sock, &fds_w))
					{
						writeset->words[i] |= (1<<j);
					}
	
					fds_bits >>= 1;
				}
			}
		}
		
		if (flag_e)
		{
			for (i = 0; i < ROCME_FD_SET_SIZE; i++)
			{
				if (0 == exceptset->words[i])
				{
					continue;
				}
				
				fds_bits = exceptset->words[i];
				exceptset->words[i] = 0;
				
				for (j = 0; j < ROCME_NFDBITS; j++)
				{
					sock = i * ROCME_NFDBITS + j;
					if ((fds_bits & 1) && FD_ISSET(sock, &fds_e))
					{
						exceptset->words[i] |= (1<<j);
					}
	
					fds_bits >>= 1;
				}
			}
		}
	
		return ret;
}


/*****************************************************************************
功能说明:
    得到系统能同时处理的socket的最大个数
    
参数说明:
        无
    
返    回:
    失败: -1
    成功: 系统能同时处理的socket的最大个数
*****************************************************************************/
INT32_T rocme_porting_get_max_sockets( void )
{
	ROCME_TEST_PRINT
	return MAX_SOCKETS;
}


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
struct roc_hostent* rocme_porting_socket_gethostbyname(const CHAR_T *name)
{
	ROCME_TEST_PRINT

	return (struct roc_hostent*)gethostbyname(name);
	
}


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
struct roc_hostent *rocme_porting_socket_gethostbyaddr(const CHAR_T * addr, INT32_T len, INT32_T type)
{
	ROCME_TEST_PRINT
	return (struct roc_hostent *)gethostbyaddr(addr,len,type);
}


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
INT32_T rocme_porting_socket_getsockname (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen)
{
	ROCME_TEST_PRINT

	HI_S32 ret = ROC_ERR;


    if((name != NULL) || (namelen != NULL))
    {
        struct sockaddr serv_addr;
        HI_S32 slen = sizeof(serv_addr);

        ret = getsockname(s, &serv_addr, (socklen_t *)&slen);

        if (ret >= 0)
        {
			name->sa_family = serv_addr.sa_family;
        	memcpy(name->sa_data,serv_addr.sa_data,14);
			*namelen = slen;
            ret = ROC_OK;
        }
    }

    if (ret != ROC_OK)
    {
		
		ROCME_PRINTF(ROCME_LOG_ERROR,"getsockname err\r\n");
        ret = ROC_ERR;
    }

    return ret;
}


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
INT32_T rocme_porting_socket_getpeername (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen)
{
	ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}



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
INT32_T rocme_porting_socket_gethostname(CHAR_T* hostname,INT32_T namelen)
{
	ROCME_TEST_PRINT
	return gethostname(gethostname,namelen);
}


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
INT32_T rocme_porting_socket_inet_aton (const CHAR_T *strptr, struct roc_in_addr *addrptr)
{
	ROCME_TEST_PRINT
	return inet_aton(strptr,(struct in_addr *)addrptr);
}


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
UINT32_T rocme_porting_socket_inet_addr (const CHAR_T *strptr)
{
	ROCME_TEST_PRINT
	HI_S32 ret = ROC_ERR;
	UINT32_T addr;
	ret=inet_aton(strptr,(struct in_addr *)&addr);
	if(ret == ROC_OK)
	{
		return addr;
	}
	else
	{
		
		ROCME_PRINTF(ROCME_LOG_ERROR,"inet_aton err\r\n");
		return ROC_ERR;
	}
}



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
CHAR_T* rocme_porting_socket_inet_ntoa (struct roc_in_addr inaddr)
{
	ROCME_TEST_PRINT
	HI_S32 ret = ROC_ERR;
	struct roc_in_addr tempinaddr;
	struct in_addr tempaddr;
	tempinaddr = inaddr;
	memcpy(&tempaddr,&tempinaddr,4);
	char *addr = NULL;
	addr = inet_ntoa(tempaddr);
	return addr;
}


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
INT32_T rocme_porting_socket_fd_zero(roc_fd_set *set)
{
	ROCME_TEST_PRINT
	FD_ZERO((fd_set *)set);
	return ROC_OK;
}


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
INT32_T rocme_porting_socket_fd_set(INT32_T fd, roc_fd_set *set)
{
	ROCME_TEST_PRINT
	FD_SET(fd,(fd_set *)set);
	return ROC_OK;
}

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
INT32_T rocme_porting_socket_fd_clr(INT32_T fd, roc_fd_set *set)
{
	ROCME_TEST_PRINT
	FD_CLR(fd,(fd_set *)set);
	return ROC_OK;
}


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
INT32_T rocme_porting_socket_fd_isset(INT32_T fd, roc_fd_set *set)
{
	ROCME_TEST_PRINT
	return FD_ISSET(fd,(fd_set *)set);
}


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
INT32_T rocme_porting_socket_ioctl(INT32_T s, UINT32_T cmd, void *argp)
{
	ROCME_TEST_PRINT
	UINT32_T flags;
	if(cmd == ROC_FIONBIO)
	{
		char *tempargp=NULL;
		tempargp = (char *)argp;
		if(*tempargp ==1)
		{
		
		flags = fcntl(s, F_GETFL, 0);  
		fcntl(s ,F_SETFL,flags|O_NONBLOCK);
		}
		else
		{
			flags = fcntl(s, F_GETFL, 0);  
			fcntl(s ,F_SETFL,flags|~O_NONBLOCK);
		}
	}
	else if(cmd == ROC_FIONREAD)
	{
		
	}
	return ROC_OK;
}



/*****************************************************************************
功能说明:
    将32位主机字符顺序转换成网络字符顺序
    
参数说明:
    输入参数:
        [hostlong] 32位主机字符
    
返    回: 
    对应的网络字符顺序

*****************************************************************************/
UINT32_T rocme_porting_socket_htonl(UINT32_T hostlong)
{
	ROCME_TEST_PRINT
	return htonl(hostlong);
	
}


/*****************************************************************************
功能说明:
    将16位主机字符顺序转换成网络字符顺序
    
参数说明:
    输入参数:
        [hostshort] 16位主机字符
    
返    回: 
    对应的网络字符顺序
*****************************************************************************/
UINT16_T rocme_porting_socket_htons(UINT16_T hostshort)
{
	ROCME_TEST_PRINT
	return htons(hostshort);
}

/*****************************************************************************
功能说明:
    将32位网络字符顺序转换成主机字符顺序
    
参数说明:
    输入参数:
        [netlong] 32位网络字符
    
返    回: 
    对应的主机字符顺序
*****************************************************************************/
UINT32_T rocme_porting_socket_ntohl(UINT32_T netlong)
{
	ROCME_TEST_PRINT
	return ntohl(netlong);
}

/*****************************************************************************
功能说明:
    将16位网络字符顺序转换成主机字符顺序
    
参数说明:
    输入参数:
        [netshort] 16位网络字符
    
返   回: 
    对应的主机字符顺序
*****************************************************************************/
UINT16_T rocme_porting_socket_ntohs(UINT16_T netshort)
{
	ROCME_TEST_PRINT
	return ntohs(netshort);
}

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
INT32_T rocme_porting_socket_get_last_errno(void)
{
	ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}

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
void rocme_porting_socket_set_errno(INT32_T nErr)
{
	ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}

#endif
