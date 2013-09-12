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
����˵��: 
    socket�׽��ֵĳ�ʼ��

����˵��:
    ��
    
����:
    ʧ��: -1              
    �ɹ�:  0
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
����˵��:
    �ر��׽ӿڣ�����ֹ����

����˵��:
    �������:
        [s] Ҫ�رյ� socket��� 
    
��    ��:
    ʧ��: -1              
    �ɹ�: 0
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
INT32_T rocme_porting_socket_getsockopt(INT32_T s,INT32_T level,INT32_T optname,void *optval,INT32_T *optlen)
{
	ROCME_TEST_PRINT

	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}


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
����˵��:
    �õ�ϵͳ��ͬʱ�����socket��������
    
����˵��:
        ��
    
��    ��:
    ʧ��: -1
    �ɹ�: ϵͳ��ͬʱ�����socket��������
*****************************************************************************/
INT32_T rocme_porting_get_max_sockets( void )
{
	ROCME_TEST_PRINT
	return MAX_SOCKETS;
}


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
struct roc_hostent* rocme_porting_socket_gethostbyname(const CHAR_T *name)
{
	ROCME_TEST_PRINT

	return (struct roc_hostent*)gethostbyname(name);
	
}


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
struct roc_hostent *rocme_porting_socket_gethostbyaddr(const CHAR_T * addr, INT32_T len, INT32_T type)
{
	ROCME_TEST_PRINT
	return (struct roc_hostent *)gethostbyaddr(addr,len,type);
}


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
INT32_T rocme_porting_socket_getpeername (INT32_T s, struct roc_sockaddr *name, INT32_T *namelen)
{
	ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}



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
INT32_T rocme_porting_socket_gethostname(CHAR_T* hostname,INT32_T namelen)
{
	ROCME_TEST_PRINT
	return gethostname(gethostname,namelen);
}


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
INT32_T rocme_porting_socket_inet_aton (const CHAR_T *strptr, struct roc_in_addr *addrptr)
{
	ROCME_TEST_PRINT
	return inet_aton(strptr,(struct in_addr *)addrptr);
}


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
����˵��:
    32λ��������ֵתΪ�ַ���(x.x.x.x)
    
����˵��:
    �������: 
        [inaddr] 32λ��������ֵ

��    ��:
    ʧ��: -1
    �ɹ�: �ַ���(x.x.x.x)
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
����˵��:
    ���һ���ļ���������
    
����˵��:
    �������:
        [set] �ļ���������

��   ��: 
    ʧ��: -1
	�ɹ�: 0
*******************************************************************************/
INT32_T rocme_porting_socket_fd_zero(roc_fd_set *set)
{
	ROCME_TEST_PRINT
	FD_ZERO((fd_set *)set);
	return ROC_OK;
}


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
INT32_T rocme_porting_socket_fd_set(INT32_T fd, roc_fd_set *set)
{
	ROCME_TEST_PRINT
	FD_SET(fd,(fd_set *)set);
	return ROC_OK;
}

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
INT32_T rocme_porting_socket_fd_clr(INT32_T fd, roc_fd_set *set)
{
	ROCME_TEST_PRINT
	FD_CLR(fd,(fd_set *)set);
	return ROC_OK;
}


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
INT32_T rocme_porting_socket_fd_isset(INT32_T fd, roc_fd_set *set)
{
	ROCME_TEST_PRINT
	return FD_ISSET(fd,(fd_set *)set);
}


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
����˵��:
    ��32λ�����ַ�˳��ת���������ַ�˳��
    
����˵��:
    �������:
        [hostlong] 32λ�����ַ�
    
��    ��: 
    ��Ӧ�������ַ�˳��

*****************************************************************************/
UINT32_T rocme_porting_socket_htonl(UINT32_T hostlong)
{
	ROCME_TEST_PRINT
	return htonl(hostlong);
	
}


/*****************************************************************************
����˵��:
    ��16λ�����ַ�˳��ת���������ַ�˳��
    
����˵��:
    �������:
        [hostshort] 16λ�����ַ�
    
��    ��: 
    ��Ӧ�������ַ�˳��
*****************************************************************************/
UINT16_T rocme_porting_socket_htons(UINT16_T hostshort)
{
	ROCME_TEST_PRINT
	return htons(hostshort);
}

/*****************************************************************************
����˵��:
    ��32λ�����ַ�˳��ת���������ַ�˳��
    
����˵��:
    �������:
        [netlong] 32λ�����ַ�
    
��    ��: 
    ��Ӧ�������ַ�˳��
*****************************************************************************/
UINT32_T rocme_porting_socket_ntohl(UINT32_T netlong)
{
	ROCME_TEST_PRINT
	return ntohl(netlong);
}

/*****************************************************************************
����˵��:
    ��16λ�����ַ�˳��ת���������ַ�˳��
    
����˵��:
    �������:
        [netshort] 16λ�����ַ�
    
��   ��: 
    ��Ӧ�������ַ�˳��
*****************************************************************************/
UINT16_T rocme_porting_socket_ntohs(UINT16_T netshort)
{
	ROCME_TEST_PRINT
	return ntohs(netshort);
}

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
INT32_T rocme_porting_socket_get_last_errno(void)
{
	ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}

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
void rocme_porting_socket_set_errno(INT32_T nErr)
{
	ROCME_TEST_PRINT
	ROCME_PRINTF(ROCME_LOG_ERROR, "not support\r\n");
	return ROC_ERR;
}

#endif
