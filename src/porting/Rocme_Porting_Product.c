/*************************************************************************
* Copyright (c) 2004, TIARTOP
* All rights reserved.
* 
* �ļ����ƣ�rocme_porting_product.cpp
* 
* ժ    Ҫ��
* 
* ��ǰ�汾��1.0
*
* ��    �ߣ�
*
* ������ڣ�2011��05��
*************************************************************************/
#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/route.h>
#include <linux/sockios.h>
#include <linux/ethtool.h> 
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if_arp.h> 
#include <netinet/ether.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <asm/types.h>
#include <sys/signal.h>
#include <unistd.h>
#include <resolv.h>

#include <sys/stat.h>




#include "hi_type.h"

#include "porter_rocme.h"


#define swap32(x) ((((x)&0xFF)<<24)  \
    |(((x)>>24)&0xFF)       \
    |(((x)&0x0000FF00)<<8)  \
    |(((x)&0x00FF0000)>>8)  )

/* format"010.000.010.001" to "10.0.10.1"*/
#define FormatIpAddr(src,dst) do{\
        INT32_T i = 0;\
        UINT32_T d[4] = {0,0,0,0};\
        CHAR_T *pstart = src;\
        if(!dst || !src){\
            return;\
        }\
        while(*pstart == ' '){\
            pstart++;\
        }\
        d[0] = atoi(pstart);\
        if(d[0]<=0){\
            break;\
        }\
        while(i < 3){\
            while(*pstart != '.'){\
                pstart++;\
            }\
            d[i+1] = atoi(++pstart);\
            ++i;\
        }\
        memset(dst,0,sizeof(ROCME_IP_LEN));\
        sprintf(dst,"%d.%d.%d.%d",d[0],d[1],d[2],d[3]);\
    }while(0)


#define SET_SA_FAMILY(addr, family)                        \
         memset ((HI_CHAR *) &(addr), '\0', sizeof(addr));        \
         addr.sa_family = (family);
#define SIN_ADDR(x)   (((struct sockaddr_in *) (&(x)))->sin_addr.s_addr)
#define BUFSIZE             8192

struct route_info{
    struct in_addr dstAddr;
    struct in_addr srcAddr;
    struct in_addr gateWay;
    char ifName[250];
};

typedef struct{        		//NETWORK_GET_PING_RESPONSE	
  	UINT32_T      recv;   	//�������ݣ���λbytes	
  	UINT32_T      ttl;  	//��������	
  	UINT32_T      address; 	//�ṩ���ݵ�IP��ַ 	
  	UINT32_T      time; 	//ping�������õ�ʱ�䣬��λms
} ROC_NETWORK_PING_RESPONSE; 

static LOADER_DB_INFO_S* g_pLoaderInfo = NULL;

static ROC_NETWORK_PING_RESPONSE ping_state_s = {64,0,0,0};

#define ETH_NAME "eth1"
#define PPP_NAME "ppp0"


#define ROCME_IP_LEN 16
static char rocme_ip_address[ROCME_IP_LEN+1]={'0','0','0','.','0','0','0','.','0','0','0','.','0','0','0','\0'};
static char rocme_ip_mask[ROCME_IP_LEN+1]={'0','0','0','.','0','0','0','.','0','0','0','.','0','0','0','\0'};
static char rocme_gateway[ROCME_IP_LEN+1]={'0','0','0','.','0','0','0','.','0','0','0','.','0','0','0','\0'};


static ROC_BOOL CheckIPAddr(char *pSrc) 
{
	int nSrcLen = strlen(pSrc);
	int nIndex = 0;
	int nDotCount = 0;
	int nIPVaildIndex = 0;
	ROC_BOOL bError = ROC_FALSE;

	printf("the ipaddr = %s,the len =%d\n",pSrc,nSrcLen);
	
	if (pSrc == NULL)
	{
		return ROC_FALSE;
	}

	while (nIndex < nSrcLen)
	{
		if (pSrc[nIndex] == '.')
		{
			nIPVaildIndex = 0;
			nDotCount++;
		}
		else if ((pSrc[nIndex] < '0') || (pSrc[nIndex] > '9'))
		{
			bError = ROC_TRUE;
			break;
		}
		else
		{
		}

		nIndex++;
	}

	if ((nDotCount != 3) || (bError))
	{
		return ROC_FALSE;
	}

	return ROC_TRUE;

}

static ROC_BOOL CheckAndFormatIpAddr(char *pSrc, char *pDst)
{
	if (!CheckIPAddr(pSrc))
	{
		return ROC_FALSE;
	}

	FormatIpAddr(pSrc, pDst);

	return ROC_TRUE;
}

/**************************************************************************
��������: 
            rocme_porting_net_init
����˵��: 
            �����豸��ʼ�����м����������ʱ���ô˺��������������м��֮ǰ
        �������Ѿ������������豸�ĳ�ʼ�����˺�������ʵ��Ϊ�������趨IP��mask
        ��gateway��
            Ҫ��:�ַ�����ʽΪ"192.125.001.090"����"192.125.1.90"��������ȷʶ��
����˵����
    ���������
            [ *deviceName]:�豸����
            [ *ip       ] : IP�ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
            [ *mask     ] : ���������ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
            [ *gateway  ] : �����ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ��ʼ���ɹ� )
    ʧ�� : -1 �� ������ ( ��ʼ��ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_net_device_init(const CHAR_T* deviceName)
{
ROCME_TEST_PRINT
	return ROC_OK;
}

INT32_T rocme_porting_net_init(const CHAR_T* deviceName, const CHAR_T *ip,const CHAR_T *mask,const CHAR_T *gateway)
{
ROCME_TEST_PRINT

	DOFUNC_RETURN(rocme_porting_set_IP(deviceName, ip));
	DOFUNC_RETURN(rocme_porting_set_mask(deviceName, mask));
	DOFUNC_RETURN(rocme_porting_set_gateway(deviceName, gateway));
#if 0	
	HI_S32 s = 0;
	struct ifreq ifr;
	

	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_IP ,creat socket err\n");
		return ROC_ERR;
	}
	ROCME_PRINTF(ROCME_LOG_INFO," interface_name = %s, ip = %s, mask = %s, gateway = %s\n", deviceName,ip,mask,gateway);
	struct rtentry rt;
	memset( (char*)&rt, 0, sizeof(rt) );

	u_int32_t dstaddr, gwaddr;

	dstaddr = inet_addr("0.0.0.0");
	gwaddr = inet_addr(gateway);
	
	ROCME_PRINTF(ROCME_LOG_INFO," dstaddr = 0x%x,gwadder = 0x%x\n", dstaddr,gwaddr);

	
	struct sockaddr_in* sin = NULL;
	
	// �����·��
	sin = (struct sockaddr_in*) &(rt.rt_dst);
	sin->sin_family			= AF_INET;
	sin->sin_port			= 0;
	sin->sin_addr.s_addr	= INADDR_ANY;
	
	sin = (struct sockaddr_in*)&(rt.rt_gateway);
	sin->sin_family			= AF_INET;
	sin->sin_port			= 0;
	sin->sin_addr.s_addr	= gwaddr;

	
	rt.rt_flags	= RTF_UP;
	rt.rt_flags	|= RTF_GATEWAY;
	
	rt.rt_dev = deviceName;

	int ret;
	ret = ioctl(s, SIOCADDRT, &rt);
	if(ret < 0)
	{
		close(s);
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_set_gateway fail  ret = %d\r\n ",ret);
		return ROC_ERR;
	}
	
	struct sockaddr_in Ipaddr;
	bzero((HI_CHAR *)&ifr, sizeof(ifr));
	strcpy(ifr.ifr_name,deviceName);

	bzero(&Ipaddr,sizeof(struct sockaddr_in));
	Ipaddr.sin_family = AF_INET;
	inet_aton(ip,&Ipaddr.sin_addr);

	memcpy((HI_CHAR*)&ifr.ifr_ifru.ifru_addr,(HI_CHAR*)&Ipaddr,sizeof(struct sockaddr_in));

	if (ioctl(s,SIOCSIFADDR,&ifr) < 0)
	{
		close(s); 
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_net_init ,setip err\n");
		return ROC_ERR;
	}

	struct sockaddr_in netmask_addr;
	bzero((HI_CHAR *)&ifr, sizeof(ifr));
	strcpy(ifr.ifr_name,deviceName);
	
	bzero(&netmask_addr,sizeof(struct sockaddr_in));
	netmask_addr.sin_family = AF_INET;
	inet_aton(mask,&netmask_addr.sin_addr);

	memcpy((HI_CHAR*)&ifr.ifr_ifru.ifru_netmask,(HI_CHAR*)&netmask_addr,sizeof(struct sockaddr_in));

	if(ioctl(s,SIOCSIFNETMASK,&ifr) < 0)
	{
		close(s); 
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_net_init ,setmask  err\n");
		return ROC_ERR;
	}

	close(s);
	

	
	return ROC_OK;
#endif
}

/**************************************************************************
��������: 
            rocme_porting_net_reset
����˵��: 
    ���趨��IP mask �� gateway �����仯�󣬵��ô˺���ʹ����Ч��
����˵����
    ���������
            ��
    ���������
            ��
��    �أ� 
			     ��
�޸ļ�¼��
**************************************************************************/
void rocme_porting_net_reset(void)
{
ROCME_TEST_PRINT
	return;
}

/**************************************************************************
��������: 
            rocme_porting_check_netcon_status
����˵��: 
            �ж�������������״̬��
����˵����
    ���������
            [ *deviceName]:�豸����
    ���������
            ��
��    �أ� 
    ROC_TRUE  ��������������
    ROC_FALSE �����������Ѿ��Ͽ� / ��ѯʧ��
�޸ļ�¼��
**************************************************************************/
ROC_BOOL rocme_porting_check_netcon_status(const CHAR_T* deviceName)
{
	ROCME_TEST_PRINT
	INT32_T skfd = 0;
	struct ifreq ifr;
	ROC_BOOL retErr = ROC_FALSE;
	SysNetworkEvent_t stEvent;

	struct ethtool_value
	{
		UINT32_T cmd;
		UINT32_T data;
	} edata;

	if(NULL == deviceName)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"deviceName is NULL err\n");
		goto NETCON_EXIT;
	}
	
	edata.cmd = 0x0a;//ETHTOOL_GLINK;
	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, deviceName);
	ifr.ifr_data = (caddr_t *)(&edata);

	skfd = socket(AF_INET, SOCK_STREAM, 0);

	if (skfd == 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_IP ,creat socket err\n");
		goto NETCON_EXIT;
	}

	if (ioctl(skfd, SIOCETHTOOL, &ifr) == -1)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"ETHTOOL_GLINK failed: %s\n", strerror(errno));
		close(skfd);
		goto NETCON_EXIT;
	}

	close(skfd);
	if (edata.data == 0)
	{
		goto NETCON_EXIT;
	}

	retErr = ROC_TRUE;

NETCON_EXIT:        
    if(ROC_FALSE == retErr)
    {
        //10502 �����ѶϿ���
        stEvent.msg = ROC_SYSEVENT_NETWORK_DISCONNECTED;
    }
    else
    {
        //10501 ���������ӡ�
        stEvent.msg = ROC_SYSEVENT_NETWORK_CONNECTED;
    }
    
    stEvent.msgType = ROC_SYSEVENT_TYPE;
    stEvent.modifiers[0] = 0;
    
    
    network_event_cbk(0, &stEvent, sizeof(stEvent));  //��ʱ�رոù��ܣ����ܺ͹㶫�ַ�������һ�¡�

    return retErr;
}

/**************************************************************************
��������: 
            rocme_porting_set_IP
����˵��: 
            ���õ�ǰ�����ն��豸��IP��ַ�ַ��������ϵ���"." ��ַ��׼����
        192.168.123.125�ȡ�
        Ҫ��:�ַ�����ʽΪ"192.125.001.090"����"192.125.1.90"��������ȷʶ��
����˵����
    ���������
			[ *deviceName]:�豸����
            [ *addr     ] : IP�ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ���������ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ���������ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_set_IP(const CHAR_T* deviceName, const CHAR_T *addr)
{
	ROCME_TEST_PRINT
	HI_S32 s = 0;
	struct ifreq ifr;
	struct sockaddr_in Ipaddr;

	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_IP ,creat socket err\n");
		return ROC_ERR;
	}
	ROCME_PRINTF(ROCME_LOG_INFO," interface_name = %s, ip = %s\n", deviceName,addr);

	bzero((HI_CHAR *)&ifr, sizeof(ifr));
	strcpy(ifr.ifr_name,deviceName);

	bzero(&Ipaddr,sizeof(struct sockaddr_in));
	Ipaddr.sin_family = AF_INET;
	inet_aton(addr,&Ipaddr.sin_addr);

	memcpy((HI_CHAR*)&ifr.ifr_ifru.ifru_addr,(HI_CHAR*)&Ipaddr,sizeof(struct sockaddr_in));

	if (ioctl(s,SIOCSIFADDR,&ifr) < 0)
	{
		close(s); 
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_IP ,setip err\n");
		return ROC_ERR;
	}

	close(s);

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_IP
����˵��: 
            ��ȡ��ǰ�����ն��豸��IP��ַ�ַ��������ϵ���"." ��ַ��׼����
        192.168.123.125�ȡ�
����˵����
    ���������
            [ *deviceName]:�豸����
    ���������
            [ *addr     ] : IP�ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
��    �أ� 
    �ɹ� : 0            ( ��ȡIP�����ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡIP�����ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_IP(const CHAR_T* deviceName, CHAR_T *addr)
{
	ROCME_TEST_PRINT
	HI_S32 s = 0;

	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_IP ,creat socket err\n");
		return ROC_ERR;
	}

	struct ifreq ifr;
	bzero((HI_CHAR *)&ifr, sizeof(ifr));
	strcpy(ifr.ifr_name,deviceName);

	if (ioctl(s,SIOCGIFADDR,&ifr) < 0)
	{
		close(s);
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_IP ,getip  err\n");
		return ROC_ERR;
	}

	struct sockaddr_in * ptr;

	ptr = (struct sockaddr_in *)&ifr.ifr_ifru.ifru_addr;
	memcpy((HI_CHAR*)addr, (HI_CHAR*)&ptr->sin_addr, sizeof(HI_U32));
	*addr = swap32(*addr);

	close(s);

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_set_mask
����˵��: 
            ���õ�ǰ�����ն��豸�����������ַ�ַ��������ϵ���"." ��ַ��׼
        ����192.168.123.125�ȡ�
        Ҫ��:�ַ�����ʽΪ"192.125.001.090"����"192.125.1.90"��������ȷʶ��
����˵����
    ���������
			[ *deviceName]:�豸����
            [ *addr     ] : ���������ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����mask�����ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ����mask�����ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_set_mask(const CHAR_T* deviceName, const CHAR_T *mask)
{
	ROCME_TEST_PRINT
	 HI_S32 s = 0;

	if((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"Netmask ,creat socket err\n");
		return ROC_ERR;
	}
	printf("[%s] interface_name = %s, netmask = %s\n", __FUNCTION__,deviceName,mask);
	struct ifreq ifr;
	bzero((HI_CHAR *)&ifr, sizeof(ifr));
	strcpy(ifr.ifr_name,deviceName);

	struct sockaddr_in netmask_addr;
	bzero(&netmask_addr,sizeof(struct sockaddr_in));
	netmask_addr.sin_family = AF_INET;
	inet_aton(mask,&netmask_addr.sin_addr);

	memcpy((HI_CHAR*)&ifr.ifr_ifru.ifru_netmask,(HI_CHAR*)&netmask_addr,sizeof(struct sockaddr_in));

	if(ioctl(s,SIOCSIFNETMASK,&ifr) < 0)
	{
		close(s); 
		ROCME_PRINTF(ROCME_LOG_ERROR,"Netmask ,setmask  err\n");
		return ROC_ERR;
	}

	close(s);

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_mask
����˵��: 
            ��ȡ��ǰ�����ն��豸�����������ַ�ַ��������ϵ���"." ��ַ��׼
        ����192.168.123.125�ȡ�
����˵����
    ���������
            [ *deviceName]:�豸����
    ���������
            [ *addr     ] : ���������ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
��    �أ� 
    �ɹ� : 0            ( ��ȡmask�����ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡmask�����ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_mask(const CHAR_T* deviceName, CHAR_T *mask)
{
ROCME_TEST_PRINT
	HI_S32 s = 0;
	if((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"Netmask ,creat socket err\n");
		return ROC_ERR;
	}

	struct ifreq ifr;

	bzero((HI_CHAR *)&ifr, sizeof(ifr));
	strcpy(ifr.ifr_name,deviceName);

	if(ioctl(s,SIOCGIFNETMASK,&ifr) < 0)
	{
		close(s); 
		ROCME_PRINTF(ROCME_LOG_ERROR,"Netmask ,get mask  err\n");
		return ROC_ERR;
	}

	struct sockaddr_in *ptr;

	ptr = (struct sockaddr_in *)&ifr.ifr_ifru.ifru_netmask;

	memcpy((HI_CHAR*)mask, (HI_CHAR*)&ptr->sin_addr, sizeof(HI_U32));
	*mask = swap32(*mask);

	ROCME_PRINTF(ROCME_LOG_INFO,"Netmask:%s\n",inet_ntoa(ptr->sin_addr));
	close(s);

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_set_gateway
����˵��: 
            ���õ�ǰ�����ն��豸�����ص�ַ�ַ��������ϵ���"." ��ַ��׼��
        ��192.168.123.125�ȡ�
        Ҫ��:�ַ�����ʽΪ"192.125.001.090"����"192.125.1.90"��������ȷʶ��
����˵����
    ���������
			[ *deviceName]:�豸����
            [ *addr     ] : �����ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
    ���������
            ��
��    �أ� 
    �ɹ� : 0            ( ����gateway�����ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ����gateway�����ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_set_gateway(const CHAR_T* deviceName, const CHAR_T *gateway)
{
	ROCME_TEST_PRINT

	#if 0
	static int sock_fd = -1;        /* socket for doing interface ioctls */
	struct rtentry rt;

	u_int32_t dstaddr, gwaddr;
	printf("[%s] interface_name = %s gateway = %s\n", __FUNCTION__,deviceName,gateway);

	dstaddr = inet_addr("0.0.0.0");
	gwaddr = inet_addr(gateway);

	/* Get an internet socket for doing socket ioctls. */
	if(sock_fd = socket(AF_INET, SOCK_DGRAM, 0)<0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_set_gateway ,creat socket err\n");
		return ROC_ERR;
	}
	memset (&rt, 0, sizeof (rt));
	/*set Destination addr*/
	SET_SA_FAMILY (rt.rt_dst, AF_INET);
	SIN_ADDR(rt.rt_dst) = dstaddr;

	/*set gw addr*/
	SET_SA_FAMILY (rt.rt_gateway, AF_INET);
	SIN_ADDR(rt.rt_gateway) = gwaddr;

	/*set genmask addr*/
	SET_SA_FAMILY (rt.rt_genmask, AF_INET);
	SIN_ADDR(rt.rt_genmask) = 0L;

	rt.rt_dev = deviceName;

	rt.rt_flags = RTF_GATEWAY;

	if (ioctl(sock_fd, SIOCADDRT, &rt) < 0)
	{
		close(sock_fd);
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_set_gateway fail\r\n ");
		return ROC_ERR;
	}
#endif

#if 1
	char temp[100];
	memset(temp,0,100);
	sprintf(temp,"route add default gw %s",gateway);
	system(temp);
#endif	
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_gateway
����˵��: 
            ��ȡ��ǰ�����ն��豸�����ص�ַ�ַ��������ϵ���"." ��ַ��׼
        ����192.168.123.125�ȡ�
����˵����
    ���������
           [ *deviceName]:�豸����
    ���������
            [ *addr     ] : �����ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
��    �أ� 
    �ɹ� : 0            ( ��ȡgateway�����ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡgateway�����ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_gateway(const CHAR_T* deviceName, CHAR_T *gateway)
{
	ROCME_TEST_PRINT

	FILE * fd = NULL;
    char line[256];
    char * token = NULL;

    fd = fopen("/proc/net/route", "r");
    
    if(fd == NULL)
    {
        return -1;
    }

#define DELIM "\t "


    while(fgets(line, sizeof(line), fd) != NULL)
    {
        
        token = strtok(line, DELIM);
        if(!strcmp(token,deviceName))
        {//�жϵ�ǰʹ�õ������豸�Ƿ���"eth0"��"ppp0"
            token = strtok(NULL, DELIM);
            if(!strcmp(token, "00000000"))
            {
                token = strtok(NULL, DELIM);
                break;
            }
        }

        token = NULL;
    }

    if(token == NULL)
    {
        memcpy(gateway, rocme_gateway, ROCME_IP_LEN);
    }
    else
    {
        struct in_addr addr;
        sscanf(token, "%x", &addr.s_addr);
        strcpy(gateway, inet_ntoa(addr));
    }

    if( NULL != fd )
    {
        fclose(fd);
    }

    rocme_porting_dprintf("rocme_porting_get_gateway = %s \n",gateway);
    
    return 0;
#if 0
	struct nlmsghdr *nlMsg;
	struct rtmsg *rtMsg;
	struct route_info *rtInfo;
	HI_CHAR msgBuf[BUFSIZE];

	HI_S32 sock = 0, len = 0, msgSeq = 0;

	*gateway = 0;

	/* Create Socket */
	if ((sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE)) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_gateway ,creat socket err\n");
		return ROC_ERR;
	}

	/* Initialize the buffer */
	memset(msgBuf, 0, BUFSIZE);

	/* point the header and the msg structure pointers into the buffer */
	nlMsg = (struct nlmsghdr *)msgBuf;
	rtMsg = (struct rtmsg *)NLMSG_DATA(nlMsg);

	/* Fill in the nlmsg header*/
	nlMsg->nlmsg_len  = NLMSG_LENGTH(sizeof(struct rtmsg)); // Length of message.
	nlMsg->nlmsg_type = RTM_GETROUTE; // Get the routes from kernel routing table .

	nlMsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST; // The message is a request for dump.
	nlMsg->nlmsg_seq   = msgSeq++; // Sequence of the message packet.
	nlMsg->nlmsg_pid   = getpid(); // PID of process sending the request.

	/* Send the request */
	if (send(sock, nlMsg, nlMsg->nlmsg_len, 0) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"Write To Socket Failed...\n");
		close(sock);
		return ROC_ERR;
	}

	/* Read the response */
	if ((len = readNlSock(sock, msgBuf, msgSeq, getpid())) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"Read From Socket Failed...\n");
		close(sock);
		return ROC_ERR;
	}

	/* Parse and print the response */
	rtInfo = (struct route_info *)malloc(sizeof(struct route_info));

	if (rtInfo == NULL)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"malloc err...\n");
		close(sock);
		return ROC_ERR;
	}

	// ADDED BY BOB
	/* THIS IS THE NETTSTAT -RL code I commented out the printing here and in parse routes */

	for(; NLMSG_OK(nlMsg,len); nlMsg = NLMSG_NEXT(nlMsg,len))
	{
		memset(rtInfo, 0, sizeof(struct route_info));
		parseRoutes(nlMsg, rtInfo, gateway, deviceName);
	}

	free(rtInfo);
	close(sock);

	return ROC_OK;
#endif
}
#if 0
/*******************************************************************************
��ȡsocket���ϵ�����
***********************************************************************************/
HI_S32 readNlSock(HI_S32 sockFd, HI_CHAR *bufPtr, HI_S32 seqNum, HI_S32 pId)
{
	ROCME_TEST_PRINT
	struct nlmsghdr *nlHdr;
	HI_S32 readLen = 0, msgLen = 0;

	do
	{
		/* Recieve response from the kernel */
		if ((readLen = recv(sockFd, bufPtr, BUFSIZE - msgLen, 0)) < 0)
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"SOCK READ: ");
			return HI_FAILURE;
		}

		nlHdr = (struct nlmsghdr *)bufPtr;

		/* Check if the header is valid */
		if ((NLMSG_OK(nlHdr, readLen) == 0) || (nlHdr->nlmsg_type == NLMSG_ERROR))
		{
			ROCME_PRINTF(ROCME_LOG_ERROR,"Error in recieved packet");
			return HI_FAILURE;
		}

		/* Check if the its the last message */
		if (nlHdr->nlmsg_type == NLMSG_DONE)
		{
			break;
		}
		else
		{
		/* Else move the pointer to buffer appropriately */
			bufPtr += readLen;
			msgLen += readLen;
		}

		/* Check if its a multi part message */
		if((nlHdr->nlmsg_flags & NLM_F_MULTI) == 0)
		{
			/* return if its not */
			break;
		}
	} while ((nlHdr->nlmsg_seq != seqNum) || (nlHdr->nlmsg_pid != pId));

	return msgLen;
}

/* For parsing the route info returned */
HI_VOID parseRoutes(struct nlmsghdr *nlHdr, struct route_info *rtInfo, HI_U32 *gateway, HI_CHAR *ifName)
{
ROCME_TEST_PRINT
    struct rtmsg *rtMsg;
    struct rtattr *rtAttr;
    HI_S32 rtLen = 0;

    rtMsg = (struct rtmsg *)NLMSG_DATA(nlHdr);

    /* If the route is not for AF_INET or does not belong to main routing table
    then return. */

    if ((rtMsg->rtm_family != AF_INET) || (rtMsg->rtm_table != RT_TABLE_MAIN))
        return;

    /* get the rtattr field */
    rtAttr = (struct rtattr *)RTM_RTA(rtMsg);
    rtLen = RTM_PAYLOAD(nlHdr);

    for (; RTA_OK(rtAttr,rtLen); rtAttr = RTA_NEXT(rtAttr,rtLen))
    {
        switch (rtAttr->rta_type)
        {
        case RTA_OIF:
            if_indextoname(*(int *)RTA_DATA(rtAttr), rtInfo->ifName);
            break;
        case RTA_GATEWAY:
            rtInfo->gateWay.s_addr = *(u_int *)RTA_DATA(rtAttr);
            break;
        case RTA_PREFSRC:
            rtInfo->srcAddr.s_addr = *(u_int *)RTA_DATA(rtAttr);
            break;
        case RTA_DST:
            rtInfo->dstAddr.s_addr = *(u_int *)RTA_DATA(rtAttr);
            break;
        }
    }

    if (strstr((HI_CHAR *)inet_ntoa(rtInfo->dstAddr), "0.0.0.0"))
    {
        if(strcmp(rtInfo->ifName, ifName) == 0)
        {
            memcpy((HI_CHAR*)gateway, (HI_CHAR*)&rtInfo->gateWay, sizeof(HI_U32));
            *gateway = swap32(*gateway);
            printf("gateway = [%s]\n", (HI_CHAR *)inet_ntoa(rtInfo->gateWay));
        }
    }

    return;
}
#endif

/**************************************************************************
��������: 
            rocme_porting_set_dnsserver
����˵��: 
            ����Э��ջ��dns server IP��ַ
����˵����
    ���������
            nIndex   : dns server ��ţ�Ŀǰ֧��0��1
    ���������
            addr     : IP ��ַ�ַ��������ϵ���"." ��ַ��׼����192.168.003.005�ȡ�
��    �أ� 
    �ɹ� : 0            ( ����DNS��������ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ����DNS��������ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_set_dnsserver(INT32_T nIndex,CHAR_T *addr)
{
ROCME_TEST_PRINT
	struct in_addr server_in_addr;
	FILE* fp = NULL;
	CHAR_T add[3][16];
	INT32_T i = 0;
	CHAR_T DnsServer[ROCME_IP_LEN] = {0};

	if (!CheckAndFormatIpAddr(addr,DnsServer))
	{
		return -1;
	}

	if(nIndex < 3)
	{
		while(i < 3)
		{
			memset(&add[i][0],0,16);
			rocme_porting_get_dnsserver(i,&add[i][0]);
			i++;
		}
		
		strcpy(&add[nIndex][0],DnsServer);
		
		fp = fopen("/etc/resolv.conf", "w");
		if (fp)
		{
			i = 0;
			while(i < 3)
			{
				fseek(fp,0,SEEK_END);
				fprintf(fp, "nameserver %s\n", &add[i][0]);
				rocme_porting_dprintf("[%s]%s\n", __FUNCTION__, &add[i][0]);
				i++;
			}	

			fclose(fp);
		}
		else
		{
			rocme_porting_dprintf("[%s]%s error\n", __FUNCTION__, &add[i][0]);
		}

		res_init();
		
		if (inet_pton(AF_INET, DnsServer, &server_in_addr) > 0) 
		{
			_res.nscount = nIndex + 1;
			_res.nsaddr_list[nIndex].sin_addr = server_in_addr;
		}
	}
	else
	{
		rocme_porting_dprintf("rocme_porting_set_dnsserver error! nIndex[%d] >\n",nIndex);
		return -1;
	}
	
	return 0;
}



/**************************************************************************
��������: 
            rocme_porting_get_dnsserver
����˵��: 
            ���Э��ջ��dns server IP��ַ
����˵����
    ���������
            count   : DNS  ��������ţ�Ŀǰ֧��0��1
    ���������
            addr     : IP ��ַ�ַ��������ϵ���"." ��ַ��׼������ж��
                          DNS�����������м��������/ ��
                          ��"192.168.003.005" 
��    �أ� 
    �ɹ� : 0            ( ����DNS��������ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ����DNS��������ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_dnsserver(INT32_T nIndex,CHAR_T *addr)
{
ROCME_TEST_PRINT
#if 0
	void *buff;
	FILE* fp = NULL;
 	char line[256];
	fp = fopen("/etc/resolv.conf", "r");
	if(fp)
	{
		  if(fgets(line, sizeof(line), fp) != NULL)
		  {
		  	buff = strstr(line,"nameserver");
			if(buff)
			{
				strcpy(addr,buff+11);/*nameserver +�ո�ĳ�����11*/
				fclose(fp);
				return 0;
			}
		  }
		  fclose(fp);
		  return -1;
	}
	else
	{
		return -1;
	}
#endif
	strcpy(addr, inet_ntoa(_res.nsaddr_list[nIndex].sin_addr));
	return 0;
}

/**************************************************************************
��������: 
            rocme_porting_get_DHCP_server
����˵��: 
            ��ȡ��ǰ�������ṩ DHCP ����ķ����� IP ��ַ�ַ��������ϵ���"." 
        ��ַ��׼����192.168.123.125�ȡ�
����˵����
    ���������
            ��
    ���������
            [ *addr     ] : DHCP��������ַ�ַ���ͷָ�룬�ַ�������Ϊ16*sizeof(CHAR_T)
��    �أ� 
    �ɹ� : 0            ( ��ȡDHCP�����������ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡDHCP�����������ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_DHCP_server(CHAR_T *addr)
{
ROCME_TEST_PRINT
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_DHCP_port
����˵��: 
            ��ȡ��ǰ�������ṩ DHCP ����ķ������˿ںš�
����˵����
    ���������
            ��
    ���������
            [ port     ] : DHCP ����ķ������˿ں�
��    �أ� 
    �ɹ� : 0            ( ��ȡDHCP�������˿ںųɹ� )
    ʧ�� : -1 �� ������ ( ��ȡDHCP�������˿ں�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_DHCP_port(UINT16_T *port)
{
ROCME_TEST_PRINT
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_mac_address
����˵��: 
            ��ȡ��ǰ����������MAC��ַ���ַ���������ʽ�����ǣ�
        "xx:xx:xx:xx:xx:xx" ����x ��[0 -9 a-f]16���ַ�֮һ��
����˵����
    ���������
            [ *deviceName]:�豸����
    ���������
            [ *mac     ] : MAC��ַ�ַ���ͷָ�룬�ַ�������18*sizeof(CHAR_T)
��    �أ� 
    �ɹ� : 0            ( ��ȡMAC��ַ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡMAC��ַʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_mac_address(const CHAR_T* deviceName, CHAR_T *mac)
{
	ROCME_TEST_PRINT
	HI_S32 s = 0;

	if ((s = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_mac_address ,creat socket err\n");
		return ROC_ERR;
	}

	struct ifreq ifr;
	bzero((HI_CHAR *)&ifr, sizeof(ifr));
	strcpy(ifr.ifr_name, deviceName);

	if (ioctl(s,SIOCGIFHWADDR,&ifr) != 0)
	{
		ROCME_PRINTF(ROCME_LOG_ERROR,"rocme_porting_get_mac_address ,get mac err\n");
		close(s); 
		return ROC_ERR;
	}

	HI_U8 * ptr;
	ptr =(HI_U8 *)&ifr.ifr_ifru.ifru_hwaddr.sa_data[0]; 
	sprintf(mac, "%02x-%02x-%02x-%02x-%02x-%02x",*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5));

	close(s);

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_rom_size
����˵��: 
            ��ȡ��ǰ��Ʒ�Ĵ洢��flash��С�� �ֽ���bytes��
����˵����
    ���������
            ��
    ���������
            [ *rom_size ] : ��ǰ��Ʒ�Ĵ洢��flash�ֽ���
��    �أ� 
    �ɹ� : 0            ( ��ȡflash��С�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡflash��Сʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_rom_size(UINT32_T *rom_size)
{
ROCME_TEST_PRINT
	*rom_size = 128*1024*1024;

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_ram_size
����˵��: 
            ��ȡ��ǰ��Ʒ���ڴ�������С�� �ֽ���bytes��
����˵����
    ���������
            ��
    ���������
            [ *rom_size ] : ��ǰ��Ʒ���ڴ�������С
��    �أ� 
    �ɹ� : 0            ( ��ȡ�ڴ��С�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ�ڴ��Сʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_ram_size(UINT32_T *ram_size)
{
ROCME_TEST_PRINT
	*ram_size = 256*1024*1024;

	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_product_serial
����˵��: 
           ��ȡ��ǰ��Ʒ���кţ��������Ϊ32�ֽڡ�
����˵����
    ���������
            ��
    ���������
            [ *product_serial ] : ��ǰ��Ʒ���кţ���󳤶�32*sizeof(CHAR_T)
��    �أ� 
    �ɹ� : 0            ( ��ȡ��Ʒ���кųɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ��Ʒ���к�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_product_serial(CHAR_T *product_serial)
{
	ROCME_TEST_PRINT
	#if 0
	int len = 0;
	char str[17] = {0};
	char str0[8] = "00000000";
	int i = 0;
	return ROC_OK;
	#endif
	int fd = -1;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if( fd < 0 )
	{
		return -1;
	}

	struct ifreq ifr;
	memset(&ifr, 0, sizeof(ifr));
	strcpy(ifr.ifr_name, "eth0");

	if( ioctl(fd, SIOCGIFHWADDR, &ifr, sizeof(ifr)) < 0 )
	{
		close(fd);
		return -1;
	}

	memcpy(product_serial, ifr.ifr_hwaddr.sa_data, 6);
	close(fd);

	return 0;
}

/**************************************************************************
��������: 
            rocme_porting_get_platform_info
����˵��: 
            ��ȡ��ǰϵͳ��Ӳ��ƽ̨��Ϣ���������Ϊ32�ֽڡ�
����˵����
    ���������
            ��
    ���������
            [ *info     ] : ��ǰϵͳ��Ӳ��ƽ̨��Ϣ����󳤶�32*sizeof(CHAR_T)
��    �أ� 
    �ɹ� : 0            ( ��ȡӲ��ƽ̨��Ϣ�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡӲ��ƽ̨��Ϣʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_platform_info(CHAR_T *info)
{
ROCME_TEST_PRINT
	memcpy(info,"Hi3716m",8);
    return 0;
}

/**************************************************************************
��������: 
            rocme_porting_get_software_version
����˵��: 
            ��ȡ����������汾��
����˵����
    ���������
            ��
    ���������
            [ *version  ] : �汾�� 
��    �أ� 
    �ɹ� : 0            ( ��ȡ����汾�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ����汾ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_software_version(UINT32_T *version)
{
ROCME_TEST_PRINT
	#if 0
	LOADER_DB_INFO_S stLoaderInfo;

	if(NULL == g_pLoaderInfo)
	{
		g_pLoaderInfo = (LOADER_DB_INFO_S*)malloc(sizeof(LOADER_DB_INFO_S));
		if(g_pLoaderInfo)
		{
			memset(g_pLoaderInfo, 0, sizeof(LOADER_DB_INFO_S));
			HI_LOADER_ReadLoaderInfo(g_pLoaderInfo);
		}
	}
	
	sprintf(version, "V%d.%d",g_pLoaderInfo->nSoftwareVersion / 100 , g_pLoaderInfo->nSoftwareVersion % 100);
	#endif
	*version = 0x12;
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_hardware_version
����˵��: 
            ��ȡ������Ӳ���汾��
����˵����
    ���������
            ��
    ���������
            [ *version  ] : �汾�� 
��    �أ� 
    �ɹ� : 0            ( ��ȡӲ���汾�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡӲ���汾ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_hardware_version(UINT32_T *version)
{
ROCME_TEST_PRINT
    if(NULL != version)
    {
        *version = 0x14040200;
         return 0;
    }
    
    return -1;

}

/**************************************************************************
��������: 
            rocme_porting_get_loader_version
����˵��: 
            ��ȡ������loader�汾��
����˵����
    ���������
            ��
    ���������
            [ *version  ] : �汾�� 
��    �أ� 
    �ɹ� : 0            ( ��ȡloader�汾�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡloader�汾ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_loader_version(UINT32_T *version)
{
    if(NULL != version)
    {
        *version = 0x100;
        return 0;
    }

    return -1;

}

/**************************************************************************
��������: 
            rocme_porting_get_browser_version
����˵��: 
            ��ȡ������汾��
����˵����
    ���������
            ��
    ���������
            [ *version ] : �汾�� 
��    �أ� 
    �ɹ� : 0            ( ��ȡ������汾�ɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ������汾ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_browser_version(UINT32_T *version)
{
ROCME_TEST_PRINT
	*version = 0x22;
	return ROC_OK;
}


/**************************************************************************
��������: 
            rocme_porting_get_stb_manufacturer
����˵��: 
            ��ȡ�������ṩ������,���40���ֽ�
����˵����
    ���������
            ��
    ���������
            [ *manufacturer ] : ��Ӧ������
            [ *pbyManuID   ]: ��������̱�ʶ(һ��byte��16������)
            �������������ĳ��û���򷵻�NULL
��    �أ� 
    �ɹ� : 0            ( ��ȡ�����й�Ӧ�����Ƴɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ�����й�Ӧ������ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_stb_manufacturer(CHAR_T *manufacturer, UINT8_T *pbyManuID)
{
ROCME_TEST_PRINT
	strcpy(manufacturer, "JiaCai");
#if 0
	if(NULL == g_pLoaderInfo)
	{
		return ROC_ERR;
	}
	else
	{
		sprintf(pbyManuID, "%d",g_pLoaderInfo->sManufacturer);
	}
#endif
	*pbyManuID = 0x1;
	return ROC_OK;
}

/**************************************************************************
��������: 
            rocme_porting_get_stb_model
����˵��: 
            ��ȡ�������ͺ�,���40���ֽ�
����˵����
    ���������
            ��
    ���������
            [ *model ] : �������ͺ�
��    �أ� 
    �ɹ� : 0            ( ��ȡ�����л������ͺųɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ�����л������ͺ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_stb_model(CHAR_T *model)
{
ROCME_TEST_PRINT
    if(NULL == model)
    {
        return -1;
    }
    memcpy(model, "DC3550", 7);
    return 0;

}

/**************************************************************************
��������: 
            rocme_porting_get_chip_id
����˵��: 
            ��ȡ������оƬ��ID���,���128�ֽ�
����˵����
    ���������
            ��
    ���������
            [ *chip_id ] : ������оƬ��ID�������ͷָ��,���128�ֽ�

��    �أ� 
    �ɹ� : 0            ( ��ȡ������chip�ͺųɹ� )
    ʧ�� : -1 �� ������ ( ��ȡ������chip�ͺ�ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_get_chip_id(UINT8_T *chip_id)
{
ROCME_TEST_PRINT
	unsigned char ChipId[] = {0x34,0x74,0xb0,0x12,0xad,0x37,0xf7,0x5c,0x91,0x0f,
		                       0xd6,0xf3,0x71,0x5c,0x5c,0x4b,0x17,0x94,0x06,0x95};

	if(chip_id==NULL)
		return -1;

	memcpy(chip_id,ChipId,sizeof(ChipId));
}

/**********************************
����˵����
    ADSL����
    
����˵����
    ��������� pppoe_config��PPPoE�����ṹ��
    ��������� 
    
��    �أ�0 - �ɹ� -1 - ʧ��
**********************************/
INT32_T rocme_porting_adsl_setup( Roc_PPPoE_Config_t *pppoe_config )
{
ROCME_TEST_PRINT
	INT8_T setup_tmp[512];

    memset(setup_tmp,0x00,sizeof(INT8_T)*512);

    /*�����Ŀ�н�ʹ�õ��û��������� 2�����*/
    rocme_porting_dprintf(">> rocme_porting_adsl_setup : usr_name       = %s \n",pppoe_config->usr_name);
    rocme_porting_dprintf(">> rocme_porting_adsl_setup : password       = %s \n",pppoe_config->password);

    /* ���²����������Ŀ�в���Ҫ�ϲ����ã�
       �ڴ˴�дΪ�̶�ֵ����ֹ���ô�����
       �����Ӳ������� 2010.09.02 by dsm */
       
    //��ʹ�÷���ǽ������Ҫ�趨�����ѯrp-pppoe��ʹ��˵��
    pppoe_config->firewall = ROC_FIREWALL_NONE;
    
    //demand_valueʹ��Ĭ��ֵ-1�����������ɲ�ѯ״̬��׼ȷ
    pppoe_config->demand_value = -1;
    
    //ʹ��Ĭ�������豸eth0
    //memcpy(pppoe_config->dev_name,"eth0",4);
    memcpy(pppoe_config->dev_name,ETH_NAME,4);
    
    //���Ҫ��dnsΪ�Զ���ȡ
    memcpy(pppoe_config->dns_ser1,"server",6);
    memcpy(pppoe_config->dns_ser2,"server",6);
    
    //�û����趨
    if( 0 == strlen(pppoe_config->usr_name) )
    {//��û��������Ч�û�����ʹ��Ĭ��ֵ123456
        memcpy(pppoe_config->usr_name,"123456",6);
    }

    //�����趨
    if(0 == strlen(pppoe_config->password))
    {//��û��������Ч���룬ʹ��Ĭ��ֵ123456
        memcpy(pppoe_config->password,"123456",6);
    }
    
    /*pppoe-setup�ű��� $1��ʾusr_name,
                        $2��ʾdevice_name,
                        $3��ʾdemand_value,
                        $4��ʾdns1��ַ,
                        $5��ʾdns2��ַ,
                        $6��ʾpassword,
                        $7��ʾfirewall���� */
    sprintf(setup_tmp,"pppoe-setup %s %s %d %s %s %s %d",
            pppoe_config->usr_name,
            pppoe_config->dev_name,
            pppoe_config->demand_value,
            pppoe_config->dns_ser1,
            pppoe_config->dns_ser2,
            pppoe_config->password,
            pppoe_config->firewall );

    /*ִ��rp-pppoeģ���shell����"pppoe-setup"
      ���úõĲ�����洢��/etc/ppp/pppoe.conf
      �ļ���*/
    system(setup_tmp);

    return 0;
}

/**********************************
����˵����
    ADSL��������
    
����˵����
    ��������� 
    ��������� 
    
��    �أ�0 - �ɹ� -1 - ʧ��
**********************************/
INT32_T rocme_porting_adsl_start(void)
{
ROCME_TEST_PRINT
	int i	= 0;
	int ret = 0;
	ROC_BOOL netlinkState = ROC_FALSE;

	netlinkState = rocme_porting_check_netcon_status(ETH_NAME);
	if(ROC_FALSE == netlinkState)
	{
		rocme_porting_dprintf("[rocme_porting_adsl_start]: check_netcon_status = %d!\n",netlinkState); 
		return -1;
	}
	
#if !defined(NFS_DEBUG)    
			system("ifconfig eth1 down");
#endif 

	/*1 ����pppoeǰȷ��pppoe���Ӵ����ж�״̬*/
	while(	0 == access( "/var/run/pppoe.conf-pppoe.pid"		, F_OK )
		 || 0 == access( "/var/run/pppoe.conf-pppoe.pid.pppd"	, F_OK )
		 || 0 == access( "/var/run/pppoe.conf-pppoe.pid.pppoe"	, F_OK ))
	{
		system("pppoe-stop");
		if( i >= 20 )
		{
			system("rm /etc/ppp/pppoe.conf-pppoe.*");
			rocme_porting_dprintf("\n		  >> WARNING : CAN NOT STOP THE PPPOE LINK !!!!!!!!!!!!!! \n\n");
			break;
		}
		rocme_porting_task_sleep(2);
		i ++;
	}

	/*2 ��ʼpppoe����*/
	system("pppoe-connect &");		
	rocme_porting_task_sleep(10);

	/*3 ��ѯpppoe������״̬,�ܹ���ʱ12s��ѯ*/
	for(i=0;i<25;i++)
	{
		rocme_porting_task_sleep(500);
		ret = rocme_porting_adsl_state();
		if( 0 == ret )
		{
			rocme_porting_dprintf("rocme_porting_adsl_start : PPP0 link OK \n");
			return ret;
		}
	}

	/*4 �����Ӳ��ɹ�����Ҫǿ�ƹر�����,��ֹpppoe-connectδ�˳����ڵײ㲻��������*/
	if( 0 != ret )
	{
		rocme_porting_dprintf("rocme_porting_adsl_start : PPP0 link false \n");
		rocme_porting_adsl_stop();
	}

	return ret;

}

/**********************************
����˵����
    ADSL���ӶϿ�
    
����˵����
    ��������� 
    ��������� 
    
��    �أ�0 - �ɹ� -1 - ʧ��
**********************************/
INT32_T rocme_porting_adsl_stop(void)
{
ROCME_TEST_PRINT
    int i = 0;
    
    system("pppoe-stop");
    rocme_porting_task_sleep(10);

    /*
    /var/run/pppoe.conf-pppoe.pid       �ļ��м�¼���ǵ�ǰpppoe-connect���̵�pid
    /var/run/pppoe.conf-pppoe.pid.pppd  �ļ��м�¼���ǵ�ǰpppd���̵�pid
    /var/run/pppoe.conf-pppoe.pid.pppoe �ļ��м�¼���ǵ�ǰpppoe���̵�pid
    ֹͣpppoe����ʱ��һ��Ҫȷ������������ȫ����kill�����������´�����pppoe
    ����ʱ��������ɽ������ppp�豸(ppp0,ppp1,...)��������ӻ��� 2010.09.02 by dsm
    */
    while(  0 == access( "/var/run/pppoe.conf-pppoe.pid"        , F_OK )
         || 0 == access( "/var/run/pppoe.conf-pppoe.pid.pppd"   , F_OK )
         || 0 == access( "/var/run/pppoe.conf-pppoe.pid.pppoe"  , F_OK ))
    {
        //��whileѭ��ȷ��pppd��pppoe-connect��pppoe�������̿��Ա�����kill�� 2010.09.02 by dsm
        system("pppoe-stop");
        if( i >= 20 )
        {
            system("rm /etc/ppp/pppoe.conf-pppoe.*");
            rocme_porting_dprintf("\n         >> WARNING : CAN NOT STOP THE PPPOE LINK !!!!!!!!!!!!!! \n\n");
            break;
        }
        rocme_porting_task_sleep(2);
        i ++;
    }

    //ȷ��ppp0�豸��down��
    system("ifconfig ppp0 down &");
    rocme_porting_task_sleep(5);

    //����eth1�豸
    system("ifconfig eth1 up &");

    return 0;

}

/**********************************
����˵����
    ADSL����״̬��ѯ
    
����˵����
    ��������� 
    ��������� 
    
��    �أ�0 - ��������״̬  -1 - δ��������״̬
**********************************/
INT32_T rocme_porting_adsl_state(void)
{
ROCME_TEST_PRINT
	FILE *fd = NULL;
	char line[256];
	int num = 0;
	char *token = NULL;
	int found = -1;

	/*���������豸���Ƿ����ppp0�ڵ����ж�pppoe�Ƿ����ӳɹ�*/
	
	fd = fopen("/proc/net/dev", "r");
	if( NULL == fd )
	{
		rocme_porting_dprintf("rocme_porting_adsl_state : NOT FOUND /proc/net/dev \n");
		return found;
	}

#define DELIM "\t "

	while(fgets(line, sizeof(line), fd) != NULL)
	{
		if(num ++ < 2)
		{
			continue;
		}

		if(strstr(line, PPP_NAME))
		{
			token = strtok(line, DELIM);
			token = strtok(NULL, DELIM);
			if(strcmp(token, "0"))
			{
				found = 0;
			}
			break;
		}
	}

	if( NULL != fd )
	{
		fclose(fd);
	}

	//rocme_porting_dprintf("rocme_porting_adsl_state ppp0 = %d \n",found);
	
	return found;

}

/**************************************************************************
��������: 
            rocme_porting_ping
����˵��: 
            ���Ի���������״̬
����˵����
    ���������
            [*ip_addr] : ����Ϊָ���ַ����ͱ�����ָ�룬ָ���ڴ����IP��ַ���ڴ��׵�ַ
            [*result] : ����Ϊָ���ַ����ͱ�����ָ�룬ָ���Ų��Խ���ַ������ڴ��׵�ַ���ڴ�ռ��ɴ˺������������룬��С��256���ֽ�

    ���������
            [*result] : ������ִ�гɹ���Ӧ�����ԵĽ�����ַ�����ʽ����result��ָ����ڴ���
            ���Գɹ�Ӧ��ӡ:
                        Recv xx byte From xxx.xxx.xxx.xxx ttl=xxx tm=xxx
            ����ʧ��Ӧ��ӡ:
                        Ping xxx.xxx.xxx.xxx time out

��    �أ� 
    �ɹ� : 0                             ( ���Ի���������״̬�ɹ� )
    ʧ�� : -1 �� ������ ( ���Ի���������״̬ʧ�� )
�޸ļ�¼��
**************************************************************************/
INT32_T rocme_porting_ping(CHAR_T *ip_addr, CHAR_T *result)
{
ROCME_TEST_PRINT
	int ok = 1; FILE * f = 0; int i=0; int ret=0;
	char cmd[512]=""; 
	unsigned char *matched=NULL;
	HI_U8 _ttl[4]={0};
	HI_U8 _time[3]="";
	HI_U8 *matched_temp=matched;

	struct stat file_atr;

	sprintf(result, "ping %s -c 2  > /tmp/ping.txt", ip_addr);
	printf("ping creat...%s\n",result);
	system(result);
	
	ret = stat("/tmp/ping.txt",&file_atr);
	if(ret)
		return ROC_ERR;
	
	if (!(file_atr.st_size))
	{
		return ROC_ERR;
	}
	f = fopen("/tmp/ping.txt", "r");

	if(!f) 
		return ROC_ERR;

	ret = fread(result,256,2,f);//????
	if (ret <0)
    		return ROC_OK;

	
	matched = strstr(result,"bytes from");  
	printf(">>>%s\n",result);
	if(!matched) 
		return ROC_ERR;
	
	matched +=11;
	ip_addr_parse(matched,&ping_state_s.address);
	printf("pint_state_s.address is 0x%08x\n",ping_state_s.address);
	matched = strstr(result,"ttl");
	if(!matched) 
		return ROC_ERR;
	
	matched +=4;
	memcpy(_ttl,matched,4);
	ping_state_s.ttl =(UINT32_T) atoi(_ttl);
	printf("pint_state_s.ttl is %d\n",ping_state_s.ttl);
	matched = strstr(result,"time");
	if(!matched) 
		return ROC_ERR;

	matched +=5;
	for(i=0;*matched != '.'; matched++,i++)
	_time[i] = *matched;
	ping_state_s.time =(UINT32_T) atoi(_time);
	printf("pint_state_s.time is %d\n",ping_state_s.time);
	
	fclose(f);
	system("rm /tmp/ping.txt");
	return ROC_OK;
}

void ip_addr_parse(HI_U8 * ip_char_start, UINT32_T * p_addr)
{
ROCME_TEST_PRINT
	if(ip_char_start == NULL ||NULL== p_addr )
		return ;
	
	HI_U8 add_0[3]={0},add_1[3]={0},add_2[3]={0},add_3[3]={0};
	HI_U8 *add[4]={add_0,add_1,add_2,add_3};
	HI_U8 *ip_char_temp = ip_char_start;
	int ip_char_length = strlen(ip_char_start);
	int add_int[4]={0};
	int test_sum=0;
	int i; 

	for( i = 0; i<4 && ':' != *ip_char_start && ip_char_start < ip_char_temp + ip_char_length;)
		{
		 	if('.' == *ip_char_start)
			{
				i++; ip_char_start++; continue;
			}
		*(add[i]) = *ip_char_start; 
		(add[i])++;  ip_char_start++;
	}

	add[0]=add_0;	add[1]=add_1;	
	add[2]=add_2;	add[3]=add_3;
	for (i=0 ; i<4 ; i++)
		{
		add_int[i] = atoi(add[i]);
		printf("add_int[%d] is %d\n",i,add_int[i]);
		
	}
	*p_addr =  add_int[0]<<24 |add_int[1]<<16 |add_int[2]<<8 |add_int[3];
//	test_sum=add_int[0]+add_int[2];

	return ;

}

/**********************************
����˵����
    ��û�����оƬ����
    
����˵����
    ��������� ��
    ��������� ��
    
��    �أ�������оƬ���ͣ�����μ�ö�٣�
						typedef enum Roc_CHIP_TYPE
						{
						    ROC_CHIP_ST_5105    = 0x00, 
						    ROC_CHIP_ST_5197    = 0x01, 
						    ROC_CHIP_ST_7105    = 0x02, 
						    ROC_CHIP_ST_7162    = 0x03, 
						    ROC_CHIP_ST_7167    = 0x04, 
						    ROC_CHIP_ST_7141    = 0x05, 
						    ROC_CHIP_ST_7108    = 0x06,
						
						    ROC_CHIP_BCM_7403   = 0x100,
						    ROC_CHIP_BCM_7405   = 0x101,
						    ROC_CHIP_BCM_7413   = 0x102,
						    ROC_CHIP_BCM_7019   = 0x103,
						
						    ROC_CHIP_HISI_3110E = 0x200,
						
						    ROC_CHIP_NEC_61325  = 0x300
						}Roc_CHIP_TYPE_e;

**********************************/
UINT32_T rocme_porting_get_chip_type(void)
{
ROCME_TEST_PRINT
	return (ROC_CHIP_ST_7105);
}


/**************************************************************************
��������: 
            rocme_porting_get_portal_url

����˵��: 
            ��ȡ������ͨ��DHCP�õ��ķ�����������Ϣ

����˵����
    ���������
            [ *purl ] : �����ļ�,���256���ֽڣ���"\0"������

��    �أ� 
    �ɹ� : 0
    ʧ�� : -1 �� ������

��ע:
    �㶫ʡ��ͨ��DHCP�е�Option�ֶ���ʵ�ֻ�ȡportal��������Ϣ��
    �������ڿ�����������������DHCP,����ȡ���е�cscfg���ݣ������档
    �м����ͨ���˽ӿ�����ȡcscfg��
    �����ļ�ʾ��:
    cscfg :URL=http://10.10.20.123/stb/configs/netwok.cfg&cfgmd5=E781FD
**************************************************************************/
INT32_T rocme_porting_get_portal_url(CHAR_T *purl)
{
ROCME_TEST_PRINT
#define OPT_DATA_ENREACH_FILE  "/resolv/dhcp_option.txt"

	FILE *fp = NULL;
	CHAR_T buf[256] = {0}; // 256 for option
	if(NULL == purl)
	{
		return -1;
	}

	fp = fopen(OPT_DATA_ENREACH_FILE, "r");

	if (fp == NULL)
	{
		return -1;
	}
	
	
	memset(buf, 0xff, 256);
	
	fgets(buf,	256, fp);

	if(*buf)
	{
		memcpy(purl, buf , 256);
	}

	fclose(fp);   
	return 0;

}
