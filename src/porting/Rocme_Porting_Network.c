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


#define NET_NAME_SIZE		16
#define	ETH_DEVICE_NUM		3
static char ROCME_ETH_NAME[3][NET_NAME_SIZE] =
{
	"eth0",
	"eth1",
	"rausb0",
};


typedef struct Rocme_Network_s
{
	CHAR_T				devicenme[NET_NAME_SIZE];
	INT32_T 			Rocme_Dns_Auto_Flag;
	Roc_DHCP_Mode_e 	dhcp_mode;
	UINT32_T 			g_nDns;

}Rocme_Network_t;

Rocme_Network_t g_RocmeNetwork[NET_NAME_SIZE];

#define SYSTEM_MESSAGE 1001
#define KEY_MESSAGE	1002
#define MOUSE_MESSAGE	1003
#define RCU_MESSAGE	1004
/*******************************************************************
���ܣ�����ģ��ʹ�õĻص�����������Ϣ���͸�webapp��
���������
    type:��ȡ��Ϣ����Դ��type=1001Ϊϵͳ��Ϣ��type=1002Ϊ���̣�type=1003Ϊ��꣬type=1004Ϊͨ��ң������
        type=1005Ϊ ������ң������type=1006Ϊ��ͯ��ң������typeֵ����1006Ԥ������չ����ʹ��
    data:void*���ͣ����ݾ�����Ϣ���ͣ�Ӧ�÷�װΪ����Ϣ�����ݽṹ��
    data_len:���ݳ���
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ޡ�
*****************************************************************/
#if 0
INT32_T network_event_cbk(INT32_T type, void *data, INT32_T data_len)
{
	switch(type)
	{
		case SYSTEM_MESSAGE:
		{
		}
		break;

		case KEY_MESSAGE:
		{
		}
		break;

		case MOUSE_MESSAGE:
		{
			
		}
		break;

		case RCU_MESSAGE:
		{
			
		}
		break;

		default:
		break;
	}
	return ROC_OK;
}

#endif
/*******************************************************************
���ܣ���ȡ/���õ�ǰ�������ṩ����ʱ��������������� IP ��ַ,Ҳ������������NTPServer ����������������ʱ�䡣
���������
    NTPServer:�ַ����������� 255 �ֽ�
    NTPPort:��ֵ��
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ڵ��� Network.save()��д Flash
*/
INT32_T rocme_porting_network_set_ntp_server(CHAR_T* NTPServer)
{
ROCME_TEST_PRINT
}
INT32_T rocme_porting_network_get_ntp_server(CHAR_T* NTPServer, UINT8_T* BuffLen)
{
ROCME_TEST_PRINT

}

/*******************************************************************
���ܣ�ͬ�� NTP ʱ�䡣 ���ҳ���ȡ����Ϣ IP_network_NTP_READY��ʾ���� NTP ʱ��ͬ���ɹ���
    ҳ���ȡ����Ϣ"10506������ NTPʱ��ͬ����ʱ"
�����������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע������ֵֻ�Ǳ�ʾ�����Ƿ�ʼִ�� NTP ʱ��ͬ����������ʾʵ�ʵ�ͬ�������ʵ�ʵ�ͬ�����������Ϣ֪ͨ����
    �緵�� 0����������Ϊû������NTPServer��
*/
INT32_T rocme_porting_network_ntp_update()
{
ROCME_TEST_PRINT

}

/*******************************************************************
���ܣ���ȡ������������ն��豸��һ��ʶ���ַ�������������
���������
    hostName:�ַ����������� 255 �ֽڣ��ɶ�д
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ڵ��� Network.save()��д Flash���ھ�������Ҳ��ͨ��������ʶ����ն��豸
*/
INT32_T rocme_porting_network_set_host(CHAR_T* hostName)
{
ROCME_TEST_PRINT

}
INT32_T rocme_porting_network_get_host(CHAR_T* hostName, UINT8_T* BuffLen)
{
ROCME_TEST_PRINT

}

/*******************************************************************
���ܣ���ȡEthernet���������
���������
    deviceNameArray�������������飻
    deviceNumber:ethernet����
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_get_ethernets_num(CHAR_T deviceNameArray[][16], CHAR_T* deviceNumber)
{
ROCME_TEST_PRINT

	INT32_T i = 0;
	*deviceNumber = ETH_DEVICE_NUM;
	for(i=0;i<ETH_DEVICE_NUM;i++)
	{
		memcpy(	deviceNameArray[i],ETH_NAME[i],sizeof(ETH_NAME[i]));
	}
	return 1;
}




/*******************************************************************
���ܣ���ȡ��ǰ���������ͣ�ȡֵ��Χ��"ethernet"��"ppp"��"pppoe"
���������
    currConnectionType:�ַ�����
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_get_connection_type(CHAR_T* deviceName, CHAR_T* currConnectionType)
{
ROCME_TEST_PRINT

}

/*******************************************************************
���ܣ�������������,��������Ϣд�� flash��
�����������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��
    ҳ���ͨ����ȡ "10601��Flashд��ɹ�"��Ϣ����֪д flash���. 
*/
INT32_T rocme_porting_network_save()
{
ROCME_TEST_PRINT

}

/*******************************************************************
���ܣ�ʵ����ͨ������ ping �Ĺ��ܡ�ͨ����Ϣ "10507��PING������Ӧ"������Ӧ������ͨ������Ϣֵ�� P2 ֵ�����ж��Ƿ� ping�ɹ���
���������
    address���ַ�����ping �������ַ,IP ����������ַ�� 
    Parameter���ַ�����ping�Ĳ�����Ŀǰ��ֻʵ��"-t"ѡ��,����ֵ���޲����� -t�������� ping һ����ַ��ֱ���ֶ�ֹͣ.
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��ÿ������Ӧ��ʱ��������Ϣ������������ͳ����Ϣ��
*/
INT32_T rocme_porting_network_ping(CHAR_T* address, CHAR_T* parameter)
{
ROCME_TEST_PRINT

}

/*******************************************************************
���ܣ��յ� IP_network_PING_RESPONSE ��Ϣ���ȡ ping����Ӧ�ַ�����
���������
    pingResponseBuffer���ַ��������ڻ�ȡping����Ӧ�ַ��� 
    BuffLen����α�ʾ��ȡresponse�����ڴ泤�ȣ�����ʱ��ʾʵ�ʳ��ȣ����С��ʵ�ʳ��ȣ�webapp��Ҫ���·����ڴ沢��ȡ��response��
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��
    �Ƿ�����Ӧ������Ϣ P2ֵ�ж�. 
    �����Ҫ������Ϣ��Ҫ���ַ����н�ȡ�� 
    ÿһ����Ӧ��Ϣ���ͺ󼴿ɻ�ȡ����һ����Ӧ��Ҫ������䡣
*/
INT32_T rocme_porting_network_get_ping_response(CHAR_T* pingResponseBuffer, UINT8_T* BuffLen)
{
ROCME_TEST_PRINT

}

/*******************************************************************
���ܣ�ȡ�����ڽ��е� ping ������
�����������
����ֵ����ֵ�ͣ�1����ֹͣ������ִ�е� ping ������0����ǰ ping �����Ѿ�������ǰ�� ping����.
��ע����
*/
INT32_T rocme_porting_network_cancel_ping()
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ���ȡ�豸״̬
���������
    deviceName���������ƣ�
    deviceState: ��ֵ�ͣ��ο�ֵ����:    
        0	�豸�����ڣ����ɷ���
        1	�豸���ڣ����޷���ȡ״̬
        101	��������
        102	��������
        201	������������
        202	���������ж�
        203	����״̬���ı䣬���ǲ���
        204	CableModem��STBͨ���ж�
        205	CableModem��STBͨ���жϣ���������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_get_device_state(CHAR_T* deviceName, INT32_T* deviceState)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ�����/��ȡ�����еĴ����������Ϣ
���������
    configInfo����ο�Roc_Proxy_Config_t���嶨�塣
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��Network.save()��дFlash
*/
INT32_T rocme_porting_network_get_proxy(CHAR_T* deviceName, Roc_Proxy_Mode_e proxyMode, Roc_Proxy_Config_t* configInfo)
{
ROCME_TEST_PRINT

}
INT32_T rocme_porting_network_set_proxy(CHAR_T* deviceName, Roc_Proxy_Mode_e proxyMode, Roc_Proxy_Config_t* configInfo)
{
ROCME_TEST_PRINT

}

/*******************************************************************
���ܣ�����/��ȡ��ǰ�����ն��豸��IP���󣬰���IP��ַ���������롢���ء�
���������
    configInfo����ο�Roc_Proxy_Config_t���嶨�塣
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��Network.save()��дFlash
*/
INT32_T rocme_porting_network_get_IP(CHAR_T* deviceName, Roc_IP_Config_t* IPInfo)
{
ROCME_TEST_PRINT

}
INT32_T rocme_porting_network_set_IP(CHAR_T* deviceName, Roc_IP_Config_t* IPInfo)
{
ROCME_TEST_PRINT


	int nSocketFd = -1;

	nSocketFd = socket( AF_INET, SOCK_DGRAM, 0 );
	if( nSocketFd < 0 )
	{
		return HI_FALSE;
	}
	if(IPInfo == NULL)
	{
		return HI_FALSE;
	}
	struct ifreq ifr;
	memset(&ifr, 0, sizeof(ifr));
	memcpy(ifr.ifr_name, deviceName, NET_NAME_SIZE);

	struct in_addr addrptr;
	struct in_addr addmask;
	inet_aton(IPInfo->ipAddress,&addrptr);
	inet_aton(IPInfo->mask,&addmask);
	
	struct sockaddr_in *sin = NULL;
	sin = (struct sockaddr_in*)&ifr.ifr_addr;
	sin->sin_family = AF_INET;
	sin->sin_addr= addrptr;

	if( ioctl(nSocketFd, SIOCSIFADDR, &ifr) < 0 )
	{
		close(nSocketFd);
		return HI_FALSE;
	}


	memset(&ifr, 0, sizeof(ifr));
	memcpy(ifr.ifr_name, deviceName, NET_NAME_SIZE);

	struct in_addr mastptr;
	inet_aton(IPInfo->mask,&mastptr);

	sin = (struct sockaddr_in*)&ifr.ifr_netmask;
	sin->sin_family = AF_INET;
	sin->sin_addr = mastptr;

	if( ioctl(nSocketFd, SIOCSIFNETMASK, &ifr) < 0 )
	{
		close(nSocketFd);
		return HI_FALSE;
	}


	close(nSocketFd);
	return HI_TRUE;
}



/*******************************************************************
���ܣ���ȡ�������պͷ��Ͱ�����Ϣ
���������
    deviceName���豸���ƣ���eth0
�������:
	pstNetPackage: �������ͺͽ��հ�����Ϣ�����Roc_Net_Package_Info_t����
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T rocme_porting_network_get_packeages(CHAR_T* deviceName, Roc_Net_Package_Info_t *pstNetPackage)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ�����/��ȡ������ͨ�ŷ�ʽ
���������
    deviceName���豸���ƣ���eth0
    communicateWay: ������ͨ�ŷ�ʽ������������ֵ"adapting"��"10M_fullDuplex"��"10M_halfDuplex"��"100M_fullDuplex"��"100M_halfDuplex"
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T rocme_porting_network_set_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay)
{
ROCME_TEST_PRINT

}
INT32_T rocme_porting_network_get_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ�����/��ȡDHCPģʽ�Ƿ��Զ���ȡDNS
���������
    deviceName: �������ƣ���eth0
    bDHCP: 1��ʾ�Զ���ȡDNS��0��ʾ�ֶ���ȡ
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/

static INT32_T Rocme_Dns_Auto_Flag = 0;
INT32_T rocme_porting_set_dns_auto(CHAR_T* deviceName, ROC_BOOL bAutoGetDns)
{
ROCME_TEST_PRINT
	HI_U32 i;
	for(i=0;i<ETH_DEVICE_NUM,i++)
	{
		if(strcmp(g_RocmeNetwork[i].devicenme,deviceName))
			break;
	}
	if(i>=ETH_DEVICE_NUM)
	{
	
		ROCME_PRINTF(ROCME_LOG_ERROR, "devicename error func %#x\r\n",	func);
		return 0;
	}
	g_RocmeNetwork[i].Rocme_Dns_Auto_Flag = bAutoGetDns;
	return 1;

}
INT32_T rocme_porting_get_dns_auto(CHAR_T* deviceName, ROC_BOOL *pbAutoGetDns)
{
ROCME_TEST_PRINT
	HI_U32 i;
	for(i=0;i<ETH_DEVICE_NUM,i++)
	{
		if(strcmp(g_RocmeNetwork[i].devicenme,deviceName))
			break;
	}
	if(i>=ETH_DEVICE_NUM)
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR, "devicename error func %#x\r\n",  func);
		return 0;
	}
	*bAutoGetDns = g_RocmeNetwork[i].Rocme_Dns_Auto_Flag;
	return 1;
}


/*******************************************************************
���ܣ�����/��ȡDNS��������Ϣ
���������
    deviceName���豸���ƣ���eth0
    nIndex: DNS������������������������DNS������
    pDNSServer: DNS��������ַ
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*************************************************************************/
INT32_T rocme_porting_network_set_dnsserver(CHAR_T* deviceName, int nIndex, CHAR_T *pDNSServer)
{
ROCME_TEST_PRINT
	HI_U32 i;
	for(i=0;i<ETH_DEVICE_NUM,i++)
	{
		if(strcmp(g_RocmeNetwork[i].devicenme,deviceName))
			break;
	}
	if(i>=ETH_DEVICE_NUM)
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR, "devicename error func %#x\r\n",  func);
		return 0;
	}

	struct in_addr addrptr;
	inet_aton(pDNSServer,&addrptr);
	
	struct sockaddr_in sin;
	sin.sin_addr	= addrptr;

	g_RocmeNetwork[i].g_nDns= (UINT32_T)sin.sin_addr.s_addr;

	char ch[128];
	memset(ch, 0, sizeof(ch));
	sprintf(ch, "nameserver %s\n", inet_ntoa(sin.sin_addr));


	int fd = -1;
	fd = open("/etc/resolv.conf", O_WRONLY | O_CREAT | O_TRUNC);
	if( fd < 0 )
	{
		return HI_FALSE;
	}

	if( write(fd, ch, strlen(ch)) < 0 )
	{
		close(fd);
		return HI_FALSE;
	}

	close(fd);
	return HI_TRUE;
}

INT32_T rocme_porting_network_get_dnsserver(CHAR_T* deviceName, int nIndex, CHAR_T *pDNSServer)
{
ROCME_TEST_PRINT
	HI_U32 i;
	for(i=0;i<ETH_DEVICE_NUM,i++)
	{
		if(strcmp(g_RocmeNetwork[i].devicenme,deviceName))
			break;
	}
	if(i>=ETH_DEVICE_NUM)
	{	
		ROCME_PRINTF(ROCME_LOG_ERROR, "devicename error func %#x\r\n",  func);
		return 0;
	}

	g_RocmeNetwork[i].g_nDns=ntohl(g_nDns);
	return 1;
}




/**********************************************************************************
���ܣ�
    ����/��ȡ�ײ������ DHCP ������ʽ��dhcp Ϊ����� DHCP ������ʽ��0: ��ʾ������ DHCP��1: ��ʾ���� DHCP�� ����ֵ��Ч��ֱ�ӷ���-1��
    
����˵����
    ���������dhcp_mode ����� DHCP ������ʽ����
    �����������
    
��    �أ�0 - ���óɹ���-1 - ʧ��
*/
INT32_T rocme_porting_network_set_dhcp(const CHAR_T *pDeviceName, const Roc_DHCP_Mode_e dhcp_mode)
{
ROCME_TEST_PRINT
	HI_U32 i;
	for(i=0;i<ETH_DEVICE_NUM,i++)
	{
		if(strcmp(g_RocmeNetwork[i].devicenme,deviceName))
			break;
	}
	if(i>=ETH_DEVICE_NUM)
	{		
		ROCME_PRINTF(ROCME_LOG_ERROR, "devicename error func %#x\r\n",  func);
		return -1;
	}
	g_RocmeNetwork[i].dhcp_mode = dhcp_mode;
	return 0;

}
INT32_T rocme_porting_network_get_dhcp_status(CHAR_T *pDeviceName, Roc_DHCP_Mode_e *dhcp_mode)
{
ROCME_TEST_PRINT
	HI_U32 i;
	for(i=0;i<ETH_DEVICE_NUM,i++)
	{
		if(strcmp(g_RocmeNetwork[i].devicenme,deviceName))
			break;
	}
	if(i>=ETH_DEVICE_NUM)
	{		
		ROCME_PRINTF(ROCME_LOG_ERROR, "devicename error func %#x\r\n",  func);
		return -1;
	}
	*dhcp_mode =g_RocmeNetwork[i].dhcp_mode;
	return 0;

}



/**********************************
����˵����
    ��ȡDHCP��̬�����DHCP�����Ϣ
    
����˵����
    ���������deviceName ��������
    ���������dhcp����Ϣ�����Roc_DHCP_Info_t�ṹ��
    
��    �أ�1��ʾ�ɹ���0��ʾʧ��

�ο�ʵ�֣�
**********************************/
INT32_T rocme_porting_get_dhcp_Info(CHAR_T* deviceName, Roc_DHCP_Info_t *pdhcpIP)
{
ROCME_TEST_PRINT

}



/*******************************************************************
���ܣ� ��ȡethernetģʽ������״̬
���������
    deviceName���豸���ƣ���eth0
�������:
    pbStatus: 1��ʾ�Ѿ������ϣ�0��ʾû��������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T romce_porting_network_get_lan_status(const CHAR_T *pDeviceName, ROC_BOOL *pbStatus)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ� ����/��ȡ�����Ƿ����
���������
    deviceName���豸���ƣ���eth0
�������:
    pbEthStatus: 1��ʾ���ã�0��ʾ������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T rocme_porting_network_set_eth_status(const CHAR_T *pDeviceName, ROC_BOOL bEthStatus)
{
ROCME_TEST_PRINT

}
INT32_T rocme_porting_network_get_eth_status(const CHAR_T *pDeviceName, ROC_BOOL *pbEthStatus)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ����������õ���������һ�������ø��ײ㣬�������԰��� ethernet�����µ�����������Զ����Խ������á�
    �书������ PC���������õ�ȷ�ϰ�ť�Ĺ��ܡ�
���������
    deviceName���������ƣ�
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_submit_parameters(CHAR_T* deviceName)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ���ȡ���е�AP��Ϣ
���������
    deviceName���������ƣ�
    apInfo: AP��Ϣ��ʹ��json�ַ�����ʾ���ַ�����ʽΪ��
        [{essId: "ap1",signalStrength:"30%",linkQuality:"40%",encType:1 },
        { essId: "ap2",signalStrength:"10%",linkQuality:"20%",encType:1 },
        { essId: "ap3", signalStrength:"20%",linkQuality:"60%",encType:2 }]
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����������������
encType	ֵ	����
    	0	��������������֤��������:�޼���
    	1	��������������֤��������:WEPOpen����
    	2	��������������֤��������:shared����ģʽ������WEP��Ϣ
    	3	��������������֤��������:Wi-Fi��������Э��
    	4	��������������֤��������:Wi-Fi��������Э��2
*/
INT32_T rocme_porting_network_get_APs(CHAR_T* deviceName, CHAR_T* apInfo)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ�����AP
���������
    deviceName���������ƣ�
    essId���ַ���������essId����ֵӦ��ȡsearchAP�ķ���ֵ��essId���Ե�ֵ
    keyType����ֵ�ͣ���������������Կ�������ͣ�keyTypeȡֵΪ�±���������������
    key���ַ�������֤��Կ
����ֵ����ֵ�ͣ��ɹ�����0��ʧ�ܷ��ش����롣
��ע����������������
    keyType	ֵ	����
            0	��������������Կ��������:16���Ʒ�ʽ����
        	1	��������������Կ��������:ansi���뷽ʽ����
        	2	��������������Կ��������:string��ʽ����
*/
INT32_T rocme_porting_network_connect_AP(CHAR_T* deviceName, CHAR_T* essId, INT32_T keyType, CHAR_T* key)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ��Ͽ���AP������
���������
    deviceName���������ƣ�
����ֵ����ֵ�ͣ��ɹ�����0��ʧ�ܷ��ش�����
��ע����
*/
INT32_T rocme_porting_network_disconnect_AP(CHAR_T* deviceName)
{
ROCME_TEST_PRINT

}


/*******************************************************************
���ܣ���ȡ�����ϵ�AP����Ϣ
���������
    deviceName���������ƣ�
    apInfo:�ɹ�����AP��Ϣ����json�ַ�����ʾ������:
        {essId: "ap1",signalStrength:"30%",linkQuality:"40%",encType:1 }
        ʧ�ܷ��ص�AP��Ϣ��essId��ֵΪ�մ�
����ֵ����ֵ�ͣ��ɹ�����0��ʧ�ܷ��ش�����
��ע����������������
    WiFi��������ձ����£�
    ����ֵ�������룩	ֵ	����	
                        0	�ɹ�
                    	1	��������
                    	2	������������ʧ��
                    	3	���������ر�ʧ��
                    	4	���Ӵ���
                    	5	������Կ����
                    	6	�����֤��Ϣ����
                    	7	δ��ȡ��AP����
*/
INT32_T rocme_porting_network_get_connected_AP(CHAR_T* deviceName, CHAR_T* apInfo)
{
ROCME_TEST_PRINT

}




/**********************************
����˵����
   ��ȡ����������Ϣ
    
����˵����
    ���������deviceName �豸����
    ���������pDescription����������Ϣ
    
��    �أ�1��ʾ�ɹ���0��ʾʧ��

�ο�ʵ�֣�
**********************************/
INT32_T rocme_porting_network_get_description(CHAR_T *deviceName, CHAR_T *pDescription)
{
ROCME_TEST_PRINT

}



/**********************************
����˵����
   �ָ���������MiddleWare ���е�������Դ�������Դ��
    
����˵����
    �����������
    �����������
    
��    �أ�1��ʾ�ɹ���0��ʾʧ��

�ο�ʵ�֣�
**********************************/
INT32_T rocme_porting_network_restore(void)
{
ROCME_TEST_PRINT

}


#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <time.h>



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
//#include <linux/ethtool.h>


#include "rocme_porting_base.h"
//#include "rocme_porting_util.h"
#include "rocme_porting_product.h"
#include "rocme_porting_network.h"
#include "rocme_porting_api.h" 
#include "porter_rocme.h"



/* TODO AAA 
INT32_T network_event_cbk(INT32_T type, void *data, INT32_T data_len)
{

}
*/

/*network module debug print ctrl*/
#define NETWORK_DEBUG
#ifdef NETWORK_DEBUG
#define NETWORK_PRINT rocme_porting_dprintf
#else
#define NETWORK_PRINT
#endif

#define DEFAULT_NTP_SERVER  ""//"172.30.56.201"
#define DEFAULT_HOSTNAME "localhost"
#define DEFAULT_DESCIRPTION "Micrel KSZ8041FTL"

//#define NFS_DEBUG   //������ʹ��nfsʱ�򿪴˺� add by lijing 2010.8.3


#define NETWORK_ERROR rocme_porting_dprintf

#define ETH_MAX_SUPPORT  (4)
#define DEFAULT_ETH_DEVICE_INDEX (0)
#define ROCME_PRODUCT_DHCP_PORT (68)
#define NETWORK_DEFAULT_DEVICE_NAME "eth0"

#define NETWORK_SUCCESS (1)
#define NETWORK_FAILED (0)

#define NETWORK_DEVICE_ENABLE (1)
#define NETWORK_COMMUNITY_WAY "100M_fullDuplex"
#define NETWORK_DEVICE_DISABLE (0)

static long g_unDifferTime = 0;   //NTPͬ��ǰ���ϵͳʱ���

typedef struct t_Ping_Param
{
    CHAR_T address[256];
    CHAR_T parameter[8];
} Ping_Param;


/*Ethernet����*/
typedef struct Roc_Ethernet_Config
{
    CHAR_T   deviceName[16];       //�����豸����
    CHAR_T   macAddr[32];          //����������ַ
    ROC_BOOL ethernetEnable;       //��ȡ�����������Ƿ����,��ֵ�ͣ�1��ʾĿǰ�������ã�0��ʾ����������
    ROC_BOOL dhcpEnable;           //��ȡ�����õ�ǰ������Ƿ�����DHCP������ʽ,��ֵ�ͣ�1��ʾʹ��DHCP��0��ʾ��̬IPģʽ
    ROC_BOOL lanStatus;            //��ȡethernetģʽ������״̬,1��ʾ��������0��ʾû��������
    ROC_BOOL dhcpAutoGetDNS;       //��ȡ�����ô�ethernet��ʹ��DHCPģʽ���Ƿ��Զ���ȡDNSserver;1��ʾ�ö�̬��ȡ��DNSserver���������õ�DNSserver
    ROC_BOOL dhcpSuccess;
    //0��ʾ���ö�̬��ȡ��DNSserver�������õ�DNSserver;���Ethernet.DHCPEnable=0;���ô�������Ч
    CHAR_T   dhcpServer[16];       //���ص�ǰ�������ṩDHCP������IP��ַ,�ַ�����ȡֵ��ΧΪ1-255�ֽڣ�ֻ��
    INT16_T  dhcpPort;             //DHCP�Ķ˿ں�(ע��Ķ˿ڳ������У�53��161��162��67��68),��ֵ�ͣ�ֻ��,busybox�õ�68.
    CHAR_T   leaseObtained[32];    //��ȡ��DHCPģʽ������IP��ַ��ʼʱ��,yyyy-mm-dd hh:mm:ss
    CHAR_T   leaseExpires[32];     //��ȡ��DHCPģʽ��IP��ַ�Ĺ���ʱ��,yyyy-mm-dd hh:mm:ss
    CHAR_T   description[256];     //��ȡ��ǰ����������ʹ�õ������豸��������Ϣ
    CHAR_T   communicateWay[16];   //���û��ȡ�������ͨ�ŷ�ʽ,һ�����������ֵ��"adapting"��"10M_fullDuplex"��
    //"10M_halfDuplex"��"100M_fullDuplex"��"100M_halfDuplex"
    UINT32_T sentPackages;         //��ȡ�������͵����ݰ�����
    UINT32_T receivedPackages;     //��ȡ�������յ������ݰ�����
    Roc_IP_Config_t    dhcpIP;                     //��ȡDHCP��̬�����IP����
    Roc_IP_Config_t    staticIP[3];                //������������IP��������,��̬IPģʽ������Ԫ���������Ϊ����
    CHAR_T             dnsServers[3][16];          //��ȡ�����õ�ǰ�������ṩDNS����ķ�����IP��ַ��DNSServers��һ�����飬�Ե�ǰ������Ч��
    //A����DHCPģʽ�¿�ѡ���Զ���ȡDNSservers,��ѡ���Զ���ȡ�����ֶ�������Ч��
    //B����ѡ���ֶ�����DNSservers,��Ҫʹ���ֶ����õ�DNSServers��ô����ȡ�����Զ���ȡDNSServer�����ã�
    //C����DHCPģʽ��ֻ���ֶ�����DNSServers;
    //����������;���ú������������������м�����Ч; ÿ��Ԫ�ص�ֵΪ�ַ�������IP��ַ
    Roc_Proxy_Config_t proxyArray[ROC_PROXY_NUM];  //Etherent��ʹ�õĴ������,���ص���proxy����
} Roc_Ethernet_Config_t;

#define NET_NAME_SIZE		16
#define	ETH_DEVICE_NUM		3
static char ROCME_ETH_NAME[3][NET_NAME_SIZE] =
{
	"eth0",
	"eth1",
	"rausb0",
};


static CHAR_T g_NTPServer[256];// = "133.100.11.8";    //����ntp server
static CHAR_T g_hostName[256] = "localhost";     //����hostname
static CHAR_T g_pingResponse[256]; //ping�����ַ�����¼���᲻�ϸ���ǰ��Ĵ洢��¼
static UINT32_T g_pingTaskHandle = 0;  //ping����ʹ�õľ��
static Ping_Param g_pingParam;

static Roc_Ethernet_Config_t  g_sEthernetConfig[ETH_MAX_SUPPORT];
static CHAR_T                 g_ucEthernetCount = 0;
static Roc_DHCP_Info_t g_stDHCPInfo[ETH_MAX_SUPPORT];
static int g_checkTaskHandle[ETH_MAX_SUPPORT]= {0};
static char g_sDeviceName[ETH_MAX_SUPPORT][16];
static int g_nDeviceNum = 0;
static struct tm g_stNTPUpdataTime;
static struct tm g_obtained_tm, g_expires_tm;
//static CHAR_T g_dhcpDnsServers[3][16];

#define PORT 123
#define MY_OFFSET 2208988800L
#define bzero(ptr,size) memset(ptr,0,size)

struct ntptime_pkt
{
    unsigned char livnmode, stratum, poll, prec;
    unsigned long delay, disp, refid;
    unsigned long reftime[2], origtime[2], rcvtime[2], txtime[2];
};


//��ȡ�����ô�ethernet��ʹ��DHCPģʽ���Ƿ��Զ���ȡDNSserver;1��ʾ�ö�̬��ȡ��DNSserver��
//�������õ�DNSserver;0��ʾ���ö�̬��ȡ��DNSserver�������õ�DNSserver;
//���Ethernet.DHCPEnable=0;���ô�������Ч
void rocme_write_dhcp_get_dns_method(CHAR_T* deviceName, ROC_BOOL dhcpAutoGetDNS)
{
ROCME_TEST_PRINT
    CHAR_T buffer[32];
    FILE* fp = NULL;
    int nIndex = DEFAULT_ETH_DEVICE_INDEX;

    fp = fopen("/mnt/dhcpAutoDns.dat", "wb");

    NETWORK_PRINT("%s: %s, %d\n", __FUNCTION__, deviceName, dhcpAutoGetDNS);

    fprintf(fp, "%s:%d\n", deviceName, dhcpAutoGetDNS);

    fclose(fp);

    NETWORK_PRINT("%s: exit\n", __FUNCTION__);
}


static INT32_T NetWorkGetDeviceIndex(const char *pDeviceName)
{
    int ii = 0;
    INT32_T  nIndex = -1;

    for (ii=0; ii<sizeof(g_sEthernetConfig)/sizeof(Roc_Ethernet_Config_t); ii++)
    {
        if (strcmp(pDeviceName, g_sEthernetConfig[ii].deviceName) == 0)
        {
            nIndex = ii;
            break;
        }
    }

    return nIndex;
}


static  void NetWorkGetEth(const char *pDeviceName, Roc_Ethernet_Config_t *pEthCfg)
{
    int nIndex = 0;

    nIndex = NetWorkGetDeviceIndex(pDeviceName);
    if (nIndex != -1)
    {
        memcpy(pEthCfg, &g_sEthernetConfig[nIndex], sizeof(Roc_Ethernet_Config_t));
    }
}

static void NetWorkSetEth(const char *pDeviceName, Roc_Ethernet_Config_t *pEthCfg)
{
    int nIndex = 0;

    nIndex = NetWorkGetDeviceIndex(pDeviceName);
    if (nIndex != -1)
    {
        memcpy(&g_sEthernetConfig[nIndex], pEthCfg, sizeof(Roc_Ethernet_Config_t));
    }
}


static void NetWorkSetEthByIndex(int nIndex, Roc_Ethernet_Config_t *pEthCfg)
{
    memcpy(&g_sEthernetConfig[nIndex], pEthCfg, sizeof(Roc_Ethernet_Config_t));
}


/* Sync the time */
ROC_BOOL rocme_request_time_from_ntpServer(char *hostip, unsigned long *myt)
{
ROCME_TEST_PRINT
    int fd = -1, len, n;
    struct sockaddr_in saddr;
    struct ntptime_pkt pkt;
    struct timeval tv;
    
    tv.tv_sec = 5;
    tv.tv_usec = 0;	
    /* Get server name */
    n = strlen(hostip);
    if (n <= 0)
    {
        return 0;
    }

    NETWORK_PRINT("%s: %s\n", __FUNCTION__, hostip);

    /* Resolve server name */
    bzero((char *)&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    if ((saddr.sin_addr.s_addr = inet_addr(hostip)) == 0)
    {
        return 0;
    }

    /* Get a socket */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        return 0;
    }
    
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(struct timeval));
	
    /* Fill in the request packet */
    bzero((char *)&pkt, sizeof(struct ntptime_pkt));
    /* version 1, mode 3 (client) */
    pkt.livnmode = 0x0b;

    /* Send packet to server */
    if ((n = sendto(fd, (char *)&pkt, sizeof(struct ntptime_pkt), 0,
                    (struct sockaddr *) &saddr,
                    sizeof(saddr))) != sizeof(struct ntptime_pkt))
    {
        close(fd);
        return 0;
    }

    /* Read reply packet from server */
    len = sizeof(struct ntptime_pkt);

    n = recvfrom(fd, (char *)&pkt, sizeof(struct ntptime_pkt), 0,
                 (struct sockaddr *) &saddr,
                 &len);

    /* Sanity checks */
#if 0
    if ((pkt.livnmode & 0xc0) == 0xc0 || !pkt.stratum || !pkt.txtime[0])
    {
        close(fd);
        return 0;
    }
#endif

    /*
    * NTP timestamps are represented as a 64-bit unsigned fixed-
    * point number, in seconds relative to 0h on 1 January 1900. The integer
    * part is in the first 32 bits and the fraction part in the last 32 bits.
    */
    if(n <= 0)
    {
        NETWORK_PRINT("%s:sock recvfrom fail!\n",__FUNCTION__);
        close(fd);
        return 0;
    }
    *myt = ntohl(pkt.txtime[0]) - MY_OFFSET;

    close(fd);

    return 1;
}

/*
 * This is the ping -t callback function. It is called when ping function with -t parameters.
 */

static void rocme_pingTask(void *param)
{
    INT32_T errRet = 0;
    CHAR_T* token;
    CHAR_T buffer[256];
    INT32_T loop = 0;
    INT32_T endless = -1;
    SysNetworkEvent_t stEvent;
    Ping_Param* pingParam = (Ping_Param*)param;

#define delim "="

    if(strlen(pingParam->parameter)==0)
    {
        loop = 4;
    }
    else if(!strcmp(pingParam->parameter,"-t"))
    {
        endless = 1;
    }
    else
    {
        rocme_porting_dprintf( "**ERROR**: frocme_pingTask param wrong!\n");
    }

    while(loop > 0 || endless == 1)
    {
        errRet = rocme_porting_ping(pingParam->address, g_pingResponse);
        //����PING������Ӧ:10523
        //-1����ʱ������������Ӧ;
        //>=0����ʾ��Ӧ��ʱ�䣬��λΪms
        stEvent.msgType = ROC_SYSEVENT_TYPE;
        stEvent.msg = ROC_SYSEVENT_PING_RESPONSE;

        memcpy(buffer, g_pingResponse, sizeof(buffer));
        printf("errRet:%d, %s\n", errRet, g_pingResponse);

        if(0 == errRet)
        {
            if(strstr(buffer, "time="))
            {
                //��һ��=Recv 60bytes From 10.10.30.212: ttl
                token = strtok(buffer, delim);

                //�ڶ���=64 tm
                token = strtok(NULL, delim);

                //������=�����ʱ�䡣���磺5.98 ms
                token = strtok(NULL, delim);
                printf("%s", token);

                sprintf(stEvent.modifiers, "%s", token);
            }
        }
        else
        {
            sprintf(stEvent.modifiers, "%d", -1);
        }

        network_event_cbk(0, &stEvent, sizeof(stEvent));

        rocme_porting_task_sleep(2000);

        loop--;
    }
}




static INT32_T network_device_init(int nIndex, CHAR_T *pDeviceName)
{
    INT32_T errCode;
    char szFileName[128];
    FILE *pCfgFile = NULL;
    UINT32_T len = 0;
    Roc_Ethernet_Config_t tmpCfg;
    CHAR_T szTmpHostName[256];
    INT32_T error;
    INT32_T nReadNum = 0;

    if (pDeviceName == NULL)
    {
        return NETWORK_FAILED;
    }

    memset(szFileName, 0, sizeof(szFileName));
    sprintf(szFileName, "%s%s%s", "/mnt/ipcfg_", pDeviceName, ".cfg");

    errCode = access(szFileName, F_OK);
    if (errCode != 0)
    {
        rocme_porting_dprintf("%s: [%s] file not exists.\n", __FUNCTION__, szFileName);
        pCfgFile = fopen(szFileName, "wb");
        if(pCfgFile == NULL)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s, %s file open failed!--+--\n", __FUNCTION__, szFileName );
            goto ERROR_EXIT;
        }

        len = sizeof(g_hostName);
        if( len != fwrite( (CHAR_T*)&g_hostName, 1, len, pCfgFile) )
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        error = fseek(pCfgFile,sizeof(g_hostName),SEEK_SET);
        if(error!=0)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        len = sizeof(g_NTPServer);
        if( len != fwrite( (CHAR_T*)&g_NTPServer, 1, len, pCfgFile) )
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        error = fseek(pCfgFile,sizeof(g_hostName)+ sizeof(g_NTPServer),SEEK_SET);
        if(error!=0)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }


        //NetWorkGetEth(pDeviceName, &tmpCfg);
        memset(&tmpCfg, 0, sizeof(Roc_Ethernet_Config_t));
        tmpCfg.ethernetEnable = NETWORK_DEVICE_ENABLE;
        tmpCfg.dhcpAutoGetDNS = NETWORK_DEVICE_ENABLE;
        tmpCfg.dhcpEnable = NETWORK_DEVICE_ENABLE;
        strcpy(tmpCfg.deviceName, pDeviceName);
        strcpy(tmpCfg.description, DEFAULT_DESCIRPTION);
        NetWorkSetEthByIndex(nIndex, &tmpCfg);

        len = sizeof(tmpCfg);
        if( len != fwrite( (CHAR_T*)&tmpCfg, 1, len, pCfgFile) )
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        rocme_write_dhcp_get_dns_method(tmpCfg.deviceName, tmpCfg.dhcpAutoGetDNS);
        rocme_porting_task_sleep(1000);
        rocme_porting_network_set_dhcp(tmpCfg.deviceName, ROC_USED_DHCP);
    }
    else
    {
        rocme_porting_dprintf("%s: [%s] file exists.\n", __FUNCTION__, szFileName);
        memset(&tmpCfg, 0, sizeof(Roc_Ethernet_Config_t));

        pCfgFile = fopen(szFileName, "rb");
        if(pCfgFile == NULL)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s, %s file open failed!--+--\n", __FUNCTION__, szFileName );
            goto ERROR_EXIT;
        }

        memset(szTmpHostName, 0, sizeof(szTmpHostName));
        nReadNum = fread((CHAR_T*)&szTmpHostName, sizeof(szTmpHostName), 1, pCfgFile);
        if(nReadNum == -1)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        if(strncmp(szTmpHostName, "", sizeof("")))
        {
            rocme_porting_network_set_host(szTmpHostName);
        }

        error = fseek(pCfgFile, sizeof(szTmpHostName), SEEK_SET);
        if(error!=0)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        nReadNum = fread((CHAR_T*)&g_NTPServer, sizeof(g_NTPServer), 1, pCfgFile);

        if(nReadNum == -1)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        error = fseek(pCfgFile, sizeof(g_hostName)+ sizeof(g_NTPServer),SEEK_SET);
        if(error!=0)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        nReadNum = fread((CHAR_T*)&tmpCfg, sizeof(tmpCfg), 1, pCfgFile);
        if (nReadNum == -1)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
            goto ERROR_EXIT;
        }

        strcpy(tmpCfg.deviceName, pDeviceName);
        rocme_porting_dprintf("[%s]tmpCfg.deviceName=%s, pDeviceName=%s\n", __FUNCTION__, tmpCfg.deviceName, pDeviceName);

        //��Ҫ��ǰ����ȫ����
        NetWorkSetEthByIndex(nIndex, &tmpCfg);


        if (tmpCfg.ethernetEnable)
        {
            rocme_porting_network_set_commute_way(pDeviceName, tmpCfg.communicateWay);

            //������������ã�����dhcpȷ�Ͽ�������ֱ�ӵ���dhcp��ʼ����
            if(tmpCfg.dhcpEnable)
            {
                rocme_write_dhcp_get_dns_method(tmpCfg.deviceName, tmpCfg.dhcpAutoGetDNS);
                rocme_porting_task_sleep(1000);       
                rocme_porting_dprintf("[%s]tmpCfg.deviceName=%s\n", __FUNCTION__, tmpCfg.deviceName);

                rocme_porting_network_set_dhcp(tmpCfg.deviceName, ROC_USED_DHCP);
            }
            else
            {
                Roc_IP_Config_t IPInfo;

                IPInfo.index = 0;
                strcpy(IPInfo.deviceName, tmpCfg.deviceName);
                strcpy(IPInfo.ipAddress, tmpCfg.staticIP[0].ipAddress);
                strcpy(IPInfo.mask, tmpCfg.staticIP[0].mask);
                strcpy(IPInfo.gateway, tmpCfg.staticIP[0].gateway);
                rocme_porting_network_set_IP(IPInfo.deviceName, &IPInfo);

                IPInfo.index = 1;
                strcpy(IPInfo.deviceName, tmpCfg.deviceName);
                strcpy(IPInfo.ipAddress, tmpCfg.staticIP[1].ipAddress);
                strcpy(IPInfo.mask, tmpCfg.staticIP[1].mask);
                strcpy(IPInfo.gateway, tmpCfg.staticIP[1].gateway);
                rocme_porting_network_set_IP(IPInfo.deviceName, &IPInfo);

                IPInfo.index = 2;
                strcpy(IPInfo.deviceName, tmpCfg.deviceName);
                strcpy(IPInfo.ipAddress, tmpCfg.staticIP[2].ipAddress);
                strcpy(IPInfo.mask, tmpCfg.staticIP[2].mask);
                strcpy(IPInfo.gateway, tmpCfg.staticIP[2].gateway);
                rocme_porting_network_set_IP(IPInfo.deviceName, &IPInfo);
                
                rocme_porting_network_set_dnsserver(IPInfo.deviceName, 0, tmpCfg.dnsServers[0]);
                rocme_porting_network_set_dnsserver(IPInfo.deviceName, 1, tmpCfg.dnsServers[1]);
                rocme_porting_network_set_dnsserver(IPInfo.deviceName, 2, tmpCfg.dnsServers[2]);
            }
        }
        else
        {
            rocme_set_ethernet_status(tmpCfg.deviceName, 0);
        }
    }

    if (pCfgFile != NULL)
    {
        fclose( pCfgFile );
        pCfgFile = NULL;
    }

    return NETWORK_SUCCESS;

ERROR_EXIT:
    if (pCfgFile != NULL)
    {
        fclose( pCfgFile );
        pCfgFile = NULL;
    }

    return NETWORK_FAILED;
}


void rocme_porting_network_init(void)
{
ROCME_TEST_PRINT
    INT32_T nRet = 0;
    CHAR_T deviceNameArray[ETH_MAX_SUPPORT][16];
    int ii, nInitCount;

    do
    {
        nInitCount = 0;

        nRet = rocme_porting_network_get_ethernets_num(deviceNameArray, &g_nDeviceNum);
        if (nRet != NETWORK_SUCCESS)
        {
            nRet = NETWORK_FAILED;
            break;
        }

        for (ii=0; ii<g_nDeviceNum; ii++)
        {
            nRet = network_device_init(ii, deviceNameArray[ii]);
            if (nRet == NETWORK_SUCCESS)
            {
                nInitCount++;
            }
            else
            {
                rocme_porting_dprintf( "device %s init failed\n", __FUNCTION__, deviceNameArray[ii] );
            }
        }
    }
    while (0);

    if (nInitCount == g_nDeviceNum)
    {
        return nRet;
    }

    return NETWORK_FAILED;
}




/*******************************************************************
���ܣ���ȡ/���õ�ǰ�������ṩ����ʱ��������������� IP ��ַ,Ҳ������������NTPServer ����������������ʱ�䡣
���������
    NTPServer:�ַ����������� 255 �ֽڣ��ɶ�д
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ڵ��� Network.save()��д Flash
*/
INT32_T rocme_porting_network_set_ntp_server(CHAR_T* NTPServer)
{
ROCME_TEST_PRINT
    INT32_T errRet = 0;

    NETWORK_PRINT("%s: %s\n", __FUNCTION__, NTPServer);

    if(NTPServer)
    {
        memset(g_NTPServer, 0, sizeof(g_NTPServer));
        memcpy(g_NTPServer, NTPServer, strlen(NTPServer));

        errRet = 1;
    }

    return errRet;
}

INT32_T rocme_porting_network_get_ntp_server(CHAR_T* NTPServer, UINT8_T* ntpServerBuffLen)
{
ROCME_TEST_PRINT
    INT32_T errRet = 0;
    NETWORK_PRINT("%s: bufferLen = %d\n", __FUNCTION__, *ntpServerBuffLen);

    if(*ntpServerBuffLen > strlen(g_NTPServer))
    {
        memcpy(NTPServer, g_NTPServer, strlen(g_NTPServer)+1);
        errRet = 1;
    }

    *ntpServerBuffLen = strlen(g_NTPServer)+1;

    return errRet;
}

/*******************************************************************
���ܣ�ͬ�� NTP ʱ�䡣 ���ҳ���ȡ����Ϣ IP_network_NTP_READY��ʾ���� NTP ʱ��ͬ���ɹ���
    ҳ���ȡ����Ϣ"10506������ NTPʱ��ͬ����ʱ"
�����������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע������ֵֻ�Ǳ�ʾ�����Ƿ�ʼִ�� NTP ʱ��ͬ����������ʾʵ�ʵ�ͬ�������ʵ�ʵ�ͬ�����������Ϣ֪ͨ����
    �緵�� 0����������Ϊû������NTPServer��
*/
INT32_T rocme_porting_network_ntp_update()
{
ROCME_TEST_PRINT
    unsigned long myt;
    struct tm *ptr;
    UINT32_T uTime = myt;
    INT32_T errRet = 0;
    CHAR_T  ntpTime[32] = {0};
    SysNetworkEvent_t stEvent;
    struct timeval stCurTime, stGetCurTime;

    NETWORK_PRINT("%s: %s\n", __FUNCTION__, g_NTPServer);

    if(strlen(g_NTPServer) != 0)
    {
        errRet = rocme_request_time_from_ntpServer(g_NTPServer,&myt);
    }
    else
    {
        //����ʹ��Ĭ��ntp��ַ.
        //errRet = rocme_request_time_from_ntpServer(DEFAULT_NTP_SERVER,&myt);
        goto ERR_EXIT; 
    }
    uTime = myt;

    if(0 != errRet)
    {
        rocme_porting_dprintf("[%s]uTime = %ld\n", __FUNCTION__, uTime);
        gettimeofday(&stGetCurTime, NULL);
        rocme_porting_dprintf("[%s]stGetCurTime.tv_sec=%ld, stGetCurTime.tv_usec=%ld\n",
                              __FUNCTION__, stGetCurTime.tv_sec, stGetCurTime.tv_usec);
        stCurTime.tv_sec = uTime + 8*60*60;
        stCurTime.tv_usec = 0;
        settimeofday(&stCurTime, NULL);
        ptr=localtime(&uTime);

        //ֻ��¼һ�β���ʱ��

        if (g_unDifferTime == 0)
        {
            if (stGetCurTime.tv_sec <= uTime)
            {
                g_unDifferTime = uTime - stGetCurTime.tv_sec;
            }
            else
            {
                g_unDifferTime = stGetCurTime.tv_sec - uTime;
            }
        }

        rocme_porting_dprintf("[%s]year = %d, month =%d, day=%d, hour=%d, min=%d, sec=%d\n",
                              __FUNCTION__, ptr->tm_year, ptr->tm_mon, ptr->tm_mday, ptr->tm_hour, ptr->tm_min, ptr->tm_sec);

        sprintf(ntpTime, "%d-%d-%d %d:%d:%d\n", ptr->tm_year+1900, ptr->tm_mon+1, ptr->tm_mday, ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
        NETWORK_PRINT("%s: %s\n", __FUNCTION__, ntpTime);

        //10521	����NTPʱ��ͬ���ɹ���
        stEvent.msgType = ROC_SYSEVENT_TYPE;
        stEvent.msg = ROC_SYSEVENT_NTPTIME_SYNC_SUCC;
        stEvent.modifiers[0] = 0;
        //memcpy(stEvent.modifiers, ntpTime, strlen(ntpTime)+1);
        network_event_cbk(0, &stEvent, sizeof(stEvent));

        return 1;
    }

ERR_EXIT:
    {
        //10522 ���� NTPʱ��ͬ����ʱ��
        stEvent.msgType = ROC_SYSEVENT_TYPE;
        stEvent.msg = ROC_SYSEVENT_NTPTIME_SYNC_TIMEOUT;
        stEvent.modifiers[0] = 0;
        network_event_cbk(0, &stEvent, sizeof(stEvent));
    }

    return 0;
}


static CHAR_T *NetWorkGetDeviceName(int nIndex)
{
    if (nIndex < g_nDeviceNum)
    {
        return g_sEthernetConfig[nIndex].deviceName;
    }
    else
    {
        return NULL;
    }


}


static INT32_T rocme_network_device_save(CHAR_T *pDeviceName)
{
ROCME_TEST_PRINT
    FILE *pCfgFile = NULL;
    char szFileName[128];
    INT32_T error;
    UINT32_T len = 0;
    Roc_Ethernet_Config_t tmpCfg;

    if (pDeviceName == NULL)
    {
        return NETWORK_FAILED;
    }

    memset(szFileName, 0, sizeof(szFileName));
    sprintf(szFileName, "%s%s%s", "/mnt/ipcfg_", pDeviceName, ".cfg");

    pCfgFile = fopen(szFileName, "r+b");
    if(pCfgFile == NULL)
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s, %s file open failed!--+--\n", __FUNCTION__, szFileName );
        goto ERROR_EXIT;
    }

    len = sizeof(g_hostName);
    if( len != fwrite( (CHAR_T*)&g_hostName, 1, len, pCfgFile))
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    error = fseek(pCfgFile,sizeof(g_hostName),SEEK_SET);
    if(error!=0)
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    len = sizeof(g_NTPServer);
    if( len != fwrite( (CHAR_T*)&g_NTPServer, 1, len, pCfgFile))
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    error = fseek(pCfgFile, sizeof(g_hostName)+ sizeof(g_NTPServer),SEEK_SET);
    if(error!=0)
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    NetWorkGetEth(pDeviceName, &tmpCfg);

    //�����dhcp����Ϊ��̬IPʱ����ʧ��̬IP�����⡣
    tmpCfg.staticIP[0].index = 0;
    rocme_porting_network_get_IP(pDeviceName, &tmpCfg.staticIP[0]);
    rocme_porting_get_dnsserver(0, &tmpCfg.dnsServers[0]);
    rocme_porting_get_dnsserver(1, &tmpCfg.dnsServers[1]);
    rocme_porting_get_dnsserver(2, &tmpCfg.dnsServers[2]);

    len = sizeof(tmpCfg);
    if( len != fwrite( (CHAR_T*)&tmpCfg, 1, len, pCfgFile))
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    if (pCfgFile != NULL)
    {
        fclose(pCfgFile);
        pCfgFile = NULL;
    }

    return NETWORK_SUCCESS;

ERROR_EXIT:
    if (pCfgFile != NULL)
    {
        fclose(pCfgFile);
        pCfgFile = NULL;
    }
    return NETWORK_FAILED;
}


INT32_T rocme_porting_network_save()
{
ROCME_TEST_PRINT
    SysNetworkEvent_t stEvent;
    int ii = 0;
    INT32_T nRet = 0;
    int nSuccessCount = 0;

    NETWORK_PRINT("%s\n", __FUNCTION__);

    for (ii=0; ii<g_nDeviceNum; ii++)
    {
        if (rocme_network_device_save(NetWorkGetDeviceName(ii)) == NETWORK_SUCCESS)
        {
            nSuccessCount++;
        }
    }

    if (nSuccessCount == g_nDeviceNum)
    {
        //����flashд��ɹ�����Ϣ
        stEvent.msgType = ROC_SYSEVENT_TYPE;
        stEvent.msg = ROC_SYSEVENT_WRITE_FLASH_SUCC;
        stEvent.modifiers[0] = 0;
        network_event_cbk(0, &stEvent, sizeof(stEvent));
        nRet = 1;

    }


    return nRet;
}


INT32_T rocme_porting_network_ping(CHAR_T* address, CHAR_T* parameter)
{
ROCME_TEST_PRINT
    INT32_T errRet = 0;
    CHAR_T  szParamterSupport[] = "-t";
    CHAR_T* token;
    const CHAR_T info[] = "Invalid parameters";
    SysNetworkEvent_t stEvent;

    if((address == NULL))
    {
        NETWORK_ERROR("%s: param is null\n", __FUNCTION__);
        stEvent.msgType = ROC_SYSEVENT_TYPE;
        stEvent.msg = ROC_SYSEVENT_PING_RESPONSE;

        memcpy(g_pingResponse, info, sizeof(info));

        sprintf(stEvent.modifiers, "%d", -1);

        network_event_cbk(0, &stEvent, sizeof(stEvent));
        return NETWORK_FAILED;
    }

    NETWORK_PRINT("%s: %s, %d\n", __FUNCTION__, address, parameter);

    memset(&g_pingParam,0,sizeof(g_pingParam));

    strcpy(g_pingParam.address, address);

    if(parameter)
    {
        strcpy(g_pingParam.parameter, parameter);
    }

    //���ping����û��ֹͣ��ǿ��ɱ��������.
    if(0 != g_pingTaskHandle)
    {
        rocme_porting_task_destroy(g_pingTaskHandle);
        g_pingTaskHandle = 0;
    }

    g_pingTaskHandle = rocme_porting_task_create("ping_task", rocme_pingTask, (void*)&g_pingParam, 1, 0x2000);

    return NETWORK_SUCCESS;
}


INT32_T rocme_porting_network_get_ping_response(CHAR_T* pingResponseBuffer, UINT8_T* BuffLen)
{
ROCME_TEST_PRINT
    INT32_T errRet = NETWORK_FAILED;
    INT32_T pingResponseBuffLen = strlen(g_pingResponse)+1;

    if ((pingResponseBuffer == NULL) || (BuffLen == NULL))
    {
        return NETWORK_FAILED;
    }

    NETWORK_PRINT("%s: %d, %d\n", __FUNCTION__, *BuffLen, pingResponseBuffLen);

    if(*BuffLen >= pingResponseBuffLen)
    {
        memcpy(pingResponseBuffer, g_pingResponse, pingResponseBuffLen);
        errRet = NETWORK_SUCCESS;
    }

    *BuffLen = pingResponseBuffLen;

    return errRet;
}




INT32_T rocme_porting_network_cancel_ping()
{
ROCME_TEST_PRINT
    INT32_T errRet = 0;

    if(0 != g_pingTaskHandle)
    {
        rocme_porting_task_destroy(g_pingTaskHandle);

        g_pingTaskHandle = 0;
        errRet = 1;
    }

    return errRet;
}

/*******************************************************************
���ܣ���ȡ������������ն��豸��һ��ʶ���ַ�������������
���������
    hostName:�ַ����������� 255 �ֽڣ��ɶ�д
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ڵ��� Network.save()��д Flash���ھ�������Ҳ��ͨ��������ʶ����ն��豸
*/
INT32_T rocme_porting_network_set_host(CHAR_T* hostName)
{
ROCME_TEST_PRINT
    INT32_T errRet = NETWORK_FAILED;
    CHAR_T buffer[32];

    if(hostName)
    {
        NETWORK_PRINT("%s: %s\n", __FUNCTION__, hostName);
        memset(g_hostName, 0, sizeof(g_hostName));
        strncpy(g_hostName, hostName, strlen(hostName));

        //ֱ������hostname���ں���
        sprintf(buffer, "hostname %s", g_hostName);
        system(buffer);

        errRet = NETWORK_SUCCESS;
    }

    return errRet;
}




INT32_T rocme_porting_network_get_host(CHAR_T* hostName, UINT8_T* BuffLen)
{
ROCME_TEST_PRINT
    INT32_T errRet = NETWORK_FAILED;

    if ((hostName == NULL) || (BuffLen == NULL))
    {
        return NETWORK_FAILED;
    }

    NETWORK_PRINT("%s: bufferLen = %d\n", __FUNCTION__, *BuffLen);

    if(*BuffLen > strlen(g_hostName))
    {
        memcpy(hostName, g_hostName, strlen(g_hostName)+1);
        errRet = NETWORK_SUCCESS;
    }

    *BuffLen = strlen(g_hostName)+1;

    return errRet;
}


INT32_T rocme_porting_network_get_connection_type(CHAR_T* deviceName, CHAR_T* currConnectionType)
{
ROCME_TEST_PRINT
    INT32_T errRet = 0;

    NETWORK_PRINT("%s\n", __FUNCTION__);

    if(currConnectionType)
    {
        if(rocme_porting_adsl_state() == 0)
        {
            strcpy(currConnectionType, "pppoe");
        }
        else
        {
            strcpy(currConnectionType, "ethernet");
        }

        errRet = 1;
    }

    return errRet;
}




INT32_T rocme_porting_network_get_proxy(CHAR_T* deviceName, Roc_Proxy_Mode_e proxyMode, Roc_Proxy_Config_t* configInfo)
{
ROCME_TEST_PRINT
    INT8_T i = 0;
    Roc_Ethernet_Config_t stTmpEthCfg;

    if((deviceName == NULL) || (configInfo == NULL))
    {
        NETWORK_ERROR("%s: %d\n", __FUNCTION__, __LINE__);
        return NETWORK_FAILED;
    }

    NETWORK_PRINT("%s: %s, proxyMode=%d\n", __FUNCTION__, deviceName, proxyMode);

    if(proxyMode >= ROC_PROXY_NUM)
    {
        NETWORK_ERROR("%s: %d\n", __FUNCTION__, __LINE__);
        return NETWORK_FAILED;
    }

    NetWorkGetEth(deviceName, &stTmpEthCfg);


    rocme_porting_dprintf("[%s]port = %d\n", __FUNCTION__, stTmpEthCfg.proxyArray[0].port);

    memcpy(configInfo->deviceName, deviceName, strlen(deviceName)+1);
    rocme_porting_dprintf("[%s]devicename = %s\n", __FUNCTION__, configInfo->deviceName);

    configInfo->proxyEnable = stTmpEthCfg.proxyArray[proxyMode].proxyEnable;
    rocme_porting_dprintf("[%s]proxyEnable = %d\n", __FUNCTION__, configInfo->proxyEnable);
    configInfo->port = stTmpEthCfg.proxyArray[proxyMode].port;
    rocme_porting_dprintf("[%s]port = %d\n", __FUNCTION__, configInfo->port);
    configInfo->proxyMode = proxyMode;
    rocme_porting_dprintf("[%s]proxyMode = %d\n", __FUNCTION__, configInfo->proxyMode);

    memcpy(configInfo->usrName, stTmpEthCfg.proxyArray[proxyMode].usrName, strlen(stTmpEthCfg.proxyArray[proxyMode].usrName)+1);
    rocme_porting_dprintf("[%s]usrName = %s\n", __FUNCTION__, configInfo->usrName);
    memcpy(configInfo->password, stTmpEthCfg.proxyArray[proxyMode].password, strlen(stTmpEthCfg.proxyArray[proxyMode].password)+1);
    rocme_porting_dprintf("[%s]password = %s\n", __FUNCTION__, configInfo->password);
    memcpy(configInfo->server, stTmpEthCfg.proxyArray[proxyMode].server, strlen(stTmpEthCfg.proxyArray[proxyMode].server)+1);
    rocme_porting_dprintf("[%s]server = %s\n", __FUNCTION__, configInfo->server);

    for(i = 0; i < 5; i++)
    {
        memcpy(configInfo->unusedProxyURLs[i], stTmpEthCfg.proxyArray[proxyMode].unusedProxyURLs[i], strlen(stTmpEthCfg.proxyArray[proxyMode].unusedProxyURLs[i])+1);
        rocme_porting_dprintf("[%s]%d URLS= %s\n", __FUNCTION__, i, configInfo->unusedProxyURLs[i]);
    }

    return NETWORK_SUCCESS;
}



INT32_T rocme_porting_network_set_proxy(CHAR_T* deviceName, Roc_Proxy_Mode_e proxyMode, Roc_Proxy_Config_t* configInfo)
{
ROCME_TEST_PRINT
    INT8_T i = 0;
    Roc_Ethernet_Config_t stTmpEthCfg;

    NETWORK_PRINT("%s: %s, proxyMode=%d\n", __FUNCTION__, deviceName, proxyMode);


    if((deviceName == NULL) || (configInfo == NULL))
    {
        NETWORK_ERROR("%s: %d\n", __FUNCTION__, __LINE__);
        return NETWORK_FAILED;
    }

    if(proxyMode >= ROC_PROXY_NUM)
    {
        NETWORK_ERROR("%s: %d\n", __FUNCTION__, __LINE__);
        return NETWORK_FAILED;
    }

    NetWorkGetEth(deviceName, &stTmpEthCfg);

    stTmpEthCfg.proxyArray[proxyMode].proxyEnable = configInfo->proxyEnable;
    rocme_porting_dprintf("[%s]proxyEnable=%d\n", __FUNCTION__, configInfo->proxyEnable);
    stTmpEthCfg.proxyArray[proxyMode].port = configInfo->port;
    rocme_porting_dprintf("[%s]port=%d\n", __FUNCTION__, configInfo->port);
    memcpy(stTmpEthCfg.proxyArray[proxyMode].usrName, configInfo->usrName, strlen(configInfo->usrName)+1);
    rocme_porting_dprintf("[%s]cusrName=%s\n", __FUNCTION__, configInfo->usrName);
    memcpy(stTmpEthCfg.proxyArray[proxyMode].password, configInfo->password, strlen(configInfo->password)+1);
    rocme_porting_dprintf("[%s]password=%s\n", __FUNCTION__, configInfo->password);
    memcpy(stTmpEthCfg.proxyArray[proxyMode].server, configInfo->server, strlen(configInfo->server)+1);
    rocme_porting_dprintf("[%s]server=%s\n", __FUNCTION__, configInfo->server);
    for(i = 0; i < 5; i++)
    {
        rocme_porting_dprintf("[%s]unusedProxyURLs[%d]=%s\n", __FUNCTION__, i, configInfo->unusedProxyURLs[i]);
        memcpy(stTmpEthCfg.proxyArray[proxyMode].unusedProxyURLs[i], configInfo->unusedProxyURLs[i], strlen(configInfo->unusedProxyURLs[i])+1);
    }

    NetWorkSetEth(deviceName, &stTmpEthCfg);

    return NETWORK_SUCCESS;
}



INT32_T rocme_porting_network_get_IP(CHAR_T* deviceName, Roc_IP_Config_t* IPInfo)
{
ROCME_TEST_PRINT
    CHAR_T nameBuffer[16] = {0};
    Roc_Ethernet_Config_t stEthCfgTmp;

    if((IPInfo == NULL) || (deviceName == NULL))
    {
        return NETWORK_FAILED;
    }

    NETWORK_PRINT("rocme_porting_network_get_IP,devicename:%s, index:%d len=%d\n",deviceName,IPInfo->index, sizeof(IPInfo->ipAddress));

    memcpy(IPInfo->deviceName, deviceName, strlen(deviceName)+1);

    if(IPInfo->index > 0)
    {
        sprintf(nameBuffer,"%s:%d",deviceName,IPInfo->index);
    }
    else
    {
        sprintf(nameBuffer,"%s",deviceName);
    }

    if(rocme_porting_get_IP(nameBuffer,IPInfo->ipAddress) != 0)
    {
        strcpy(stEthCfgTmp.staticIP[IPInfo->index].ipAddress, "0.0.0.0");
    }
    else
    {
        memcpy(stEthCfgTmp.staticIP[IPInfo->index].ipAddress, IPInfo->ipAddress, sizeof(IPInfo->ipAddress));
    }

    if(rocme_porting_get_mask(nameBuffer,IPInfo->mask) != 0)
    {
        strcpy(stEthCfgTmp.staticIP[IPInfo->index].mask, "255.255.255.0");
    }
    else
    {
        memcpy(stEthCfgTmp.staticIP[IPInfo->index].mask, IPInfo->mask, sizeof(IPInfo->mask));
    }

    //ֻ��������һ����������
    //if(rocme_porting_get_gateway(nameBuffer,IPInfo->gateway) != 0)
    if(rocme_porting_get_gateway(deviceName,IPInfo->gateway) != 0)
    {
        strcpy(stEthCfgTmp.staticIP[IPInfo->index].gateway, "192.168.1.1");
    }
    else
    {
        memcpy(stEthCfgTmp.staticIP[IPInfo->index].gateway, IPInfo->gateway, sizeof(IPInfo->gateway));
    }

    NetWorkGetEth(deviceName, &stEthCfgTmp);
    memcpy(stEthCfgTmp.staticIP[IPInfo->index].deviceName, IPInfo->deviceName, sizeof(IPInfo->deviceName));
    stEthCfgTmp.staticIP[IPInfo->index].index = IPInfo->index;
    NetWorkSetEth(deviceName, &stEthCfgTmp);
    
    rocme_porting_dprintf("[%s]deviceName=%s, index=%d, gateway=%s, ipaddress=%s, mask=%s\n",
                          __FUNCTION__, IPInfo->deviceName, IPInfo->index, IPInfo->gateway, IPInfo->ipAddress, IPInfo->mask);
    rocme_porting_dprintf("rocme_porting_get_gateway end \n");


    return NETWORK_SUCCESS;
}


INT32_T rocme_porting_network_set_IP(CHAR_T* deviceName, Roc_IP_Config_t* IPInfo)
{
ROCME_TEST_PRINT
    CHAR_T nameBuffer[16] = {0};
    Roc_Ethernet_Config_t stEthCfgTmp;
    INT32_T nRet = NETWORK_FAILED;

    NETWORK_PRINT("enter rocme_porting_network_set_IP!\n");

    if((IPInfo == NULL) || (deviceName == NULL))
    {
        return NETWORK_FAILED;
    }

    NETWORK_PRINT("%s: %s, %s, %s, %s,index %d\n", __FUNCTION__, deviceName, IPInfo->ipAddress, IPInfo->mask, IPInfo->gateway,IPInfo->index);

    if(IPInfo->index >= MAX_IP_PER_INTERFACE)
    {
        return NETWORK_FAILED;
    }

    if(IPInfo->index > 0)
    {
        sprintf(nameBuffer,"%s:%d",deviceName,IPInfo->index);
    }
    else
    {
        sprintf(nameBuffer,"%s",deviceName);
    }

    NetWorkGetEth(deviceName, &stEthCfgTmp);
/*
    if (!stEthCfgTmp.ethernetEnable)
    {
        rocme_porting_dprintf("[%s]network device %s has been disable \n", __FUNCTION__, stEthCfgTmp.deviceName);
        nRet = NETWORK_FAILED;
        goto EXIT;
    }
//*/
 //   if(0 != strncmp(stEthCfgTmp.staticIP[IPInfo->index].ipAddress, IPInfo->ipAddress, sizeof(stEthCfgTmp.staticIP[0].ipAddress)))
    {
        if (rocme_porting_set_IP(nameBuffer,IPInfo->ipAddress) != 0)
        {
            rocme_porting_dprintf("[%s]porting_set_IP set failed \n", __FUNCTION__);
            nRet = NETWORK_FAILED;
            goto EXIT;
        }
        memcpy(stEthCfgTmp.staticIP[IPInfo->index].ipAddress, IPInfo->ipAddress, sizeof(stEthCfgTmp.staticIP[0].ipAddress));
    }

  //  if(0 != strncmp(stEthCfgTmp.staticIP[IPInfo->index].mask, IPInfo->mask, sizeof(stEthCfgTmp.staticIP[0].mask)))
    {
        if (rocme_porting_set_mask(nameBuffer,IPInfo->mask) != 0)
        {
            rocme_porting_dprintf("[%s]porting_set_mask set failed \n", __FUNCTION__);
            nRet = NETWORK_FAILED;
            goto EXIT;
        }
        memcpy(stEthCfgTmp.staticIP[IPInfo->index].mask, IPInfo->mask, sizeof(stEthCfgTmp.staticIP[0].mask));
    }

  //  if(0 != strncmp(stEthCfgTmp.staticIP[IPInfo->index].gateway, IPInfo->gateway, sizeof(stEthCfgTmp.staticIP[0].gateway)))
    {
        //ֻ��������һ����������
        //if (rocme_porting_set_gateway(nameBuffer,IPInfo->gateway) != 0)
        if (rocme_porting_set_gateway(deviceName,IPInfo->gateway) != 0)
        {
            rocme_porting_dprintf("[%s]porting_set_gateway set failed \n", __FUNCTION__);
            nRet = NETWORK_FAILED;
            goto EXIT;
        }
        memcpy(stEthCfgTmp.staticIP[IPInfo->index].gateway, IPInfo->gateway, sizeof(stEthCfgTmp.staticIP[0].gateway));
    }

    nRet = NETWORK_SUCCESS;

EXIT:
    NetWorkSetEth(deviceName, &stEthCfgTmp);

    return nRet;
}




//linux�м�¼�������ݵĸ�ʽΪ  eth0:14285698   70072    0    0    0     0          0         0 15983632   59101    0    0    0     0       0          0
UINT32_T rocme_get_recv_packages(CHAR_T* deviceName)
{
ROCME_TEST_PRINT
    FILE *fd = NULL;
    CHAR_T* token = NULL;
    CHAR_T line[256];
    INT32_T num = 0;
    UINT32_T packetNumber=0;

    if (deviceName == NULL)
    {
        return 0;
    }

#define DELIM "\t "

    fd = fopen("/proc/net/dev", "r");
    if( NULL == fd )
    {
        NETWORK_ERROR("%s : NOT FOUND /proc/net/dev \n", __FUNCTION__);
        return packetNumber;
    }

    while(fgets(line, sizeof(line), fd) != NULL)
    {
        if(num ++ < 2)
        {
            continue;
        }

        if(strstr(line, deviceName))
        {
            token = strtok(line, DELIM);
            token = strtok(NULL, DELIM);

            packetNumber = atoi(token);
            break;
        }
    }

    if( NULL != fd )
    {
        fclose(fd);
    }

    NETWORK_PRINT("%s: %s, %d\n", __FUNCTION__, deviceName, packetNumber);

    return packetNumber;
}






UINT32_T rocme_get_send_packages(CHAR_T* deviceName)
{
ROCME_TEST_PRINT
    FILE *fd = NULL;
    CHAR_T* token = NULL;
    CHAR_T line[256];
    INT32_T num = 0;
    INT8_T i = 0;
    UINT32_T packetNumber=0;

#define DELIM "\t "

    if (deviceName == NULL)
    {
        return 0;
    }

    fd = fopen("/proc/net/dev", "r");
    if( NULL == fd )
    {
        NETWORK_ERROR("%s : NOT FOUND /proc/net/dev \n", __FUNCTION__);
        return packetNumber;
    }

    while(fgets(line, sizeof(line), fd) != NULL)
    {
        if(num ++ < 2)
        {
            continue;
        }

        if(strstr(line, deviceName))
        {
            token = strtok(line, DELIM);

            //��10���ֶ�Ϊ�������ݰ�����ֵ
            for(i = 0; i < 9; i++)
            {
                token = strtok(NULL, DELIM);
            }

            packetNumber = atoi(token);
            break;
        }
    }

    if( NULL != fd )
    {
        fclose(fd);
    }

    NETWORK_PRINT("%s: %s, %d\n", __FUNCTION__, deviceName, packetNumber);

    return packetNumber;
}


INT32_T rocme_porting_network_get_packeages(CHAR_T* deviceName, Roc_Net_Package_Info_t *pstNetPackage)
{
ROCME_TEST_PRINT
    if ((deviceName == NULL) || (pstNetPackage == NULL))
    {
        return NETWORK_FAILED;
    }

    pstNetPackage->receivedPackages =  rocme_get_recv_packages(deviceName);
    pstNetPackage->sentPackages = rocme_get_send_packages(deviceName);

    return NETWORK_SUCCESS;
}


INT32_T set_commute_way(CHAR_T* deviceName,INT32_T speed,INT32_T duplex)
{
ROCME_TEST_PRINT
#if 0
    struct ethtool_cmd ecmd;
    struct ifreq ifr;
    int fd;

    if((NULL == deviceName) || (speed < 0) || (duplex < 0))
    {
        return NETWORK_FAILED;
    }

    /* Setup our control structures. */
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, deviceName);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        return NETWORK_FAILED;
    }

    ecmd.speed =speed;
    ecmd.duplex=duplex;

    ecmd.cmd = ETHTOOL_SSET;
    ecmd.autoneg = 0;

    ifr.ifr_data = (caddr_t)&ecmd;
    if(ioctl(fd, SIOCETHTOOL, &ifr))
    {
        close(fd);
        perror("SIOCETHTOOL");
        return NETWORK_FAILED;
    }
    close(fd);
   #endif

    return NETWORK_SUCCESS;
}


INT32_T rocme_porting_network_set_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay)
{
ROCME_TEST_PRINT
    if ((deviceName == NULL) || (communicateWay == NULL))
    {
        return NETWORK_FAILED;
    }

    return rocme_set_commute_way(deviceName, communicateWay);
}



INT32_T rocme_porting_network_get_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay)
{
ROCME_TEST_PRINT
    INT32_T nRet = NETWORK_FAILED;
    Roc_Ethernet_Config_t EthCfg;

    if ((deviceName == NULL) || (communicateWay == NULL))
    {
        return NETWORK_FAILED;
    }

    nRet = rocme_get_commute_way(deviceName, communicateWay);

    if (nRet)
    {
        NetWorkGetEth(deviceName, &EthCfg);
        memcpy(EthCfg.communicateWay, communicateWay, strlen(communicateWay)+1);
        NetWorkSetEth(deviceName, &EthCfg);
    }

    return nRet;
}


//lease time
//date +'%y-%m-%d %H:%M:%S'  > /mnt/dhcp_lease.conf

INT32_T rocme_set_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay)
{
ROCME_TEST_PRINT
    INT32_T speed = -1;
    INT32_T duplex = -1;
    INT32_T ret = NETWORK_FAILED;
    INT32_T communicateTmp[16] = {0};
    Roc_Ethernet_Config_t EthCfg;

    if(NULL == deviceName)
    {
        return ret;
    }

    NETWORK_PRINT("%s: %s, %s\n", __FUNCTION__, deviceName, communicateWay);

    if(0 == strncmp(communicateWay, "adapting", sizeof("adapting")))
    {
        do
        {
            speed =ROC_SPEED_100;
            duplex=ROC_FULL_DUPLEX;
            if(NETWORK_SUCCESS == set_commute_way(deviceName,speed,duplex) && NETWORK_SUCCESS == rocme_get_ethernet_status(deviceName))
            {
                NETWORK_PRINT("%s,adapting success,result is 100M_fullDuplex\n",__FUNCTION__);
                strcpy(communicateTmp,"100M_fullDuplex");
                ret = NETWORK_SUCCESS;
                break;
            }

            speed =ROC_SPEED_100;
            duplex=ROC_HALF_DUPLEX;
            if(NETWORK_SUCCESS == set_commute_way(deviceName,speed,duplex) && NETWORK_SUCCESS == rocme_get_ethernet_status(deviceName))
            {
                NETWORK_PRINT("%s,adapting success,result is 100M_halfDuplex\n",__FUNCTION__);
                strcpy(communicateTmp,"100M_halfDuplex");
                ret = NETWORK_SUCCESS;
                break;
            }

            speed =ROC_SPEED_10;
            duplex=ROC_FULL_DUPLEX;
            if(NETWORK_SUCCESS == set_commute_way(deviceName,speed,duplex) && NETWORK_SUCCESS == rocme_get_ethernet_status(deviceName))
            {
                NETWORK_PRINT("%s,adapting success,result is 10M_fullDuplex\n",__FUNCTION__);
                strcpy(communicateTmp,"10M_fullDuplex");
                ret = NETWORK_SUCCESS;
                break;
            }

            speed =ROC_SPEED_10;
            duplex=ROC_HALF_DUPLEX;
            if(NETWORK_SUCCESS == set_commute_way(deviceName,speed,duplex) && NETWORK_SUCCESS == rocme_get_ethernet_status(deviceName))
            {
                NETWORK_PRINT("%s,adapting success,result is 10M_halfDuplex\n",__FUNCTION__);
                strcpy(communicateTmp,"10M_halfDuplex");
                ret = NETWORK_SUCCESS;
                break;
            }

            NETWORK_PRINT("%s,adapting fail!\n",__FUNCTION__);
        }
        while(0);

    }
    else
    {
        if(0 == strncmp(communicateWay, "10M_fullDuplex", sizeof("10M_fullDuplex")))
        {
            speed =ROC_SPEED_10;
            duplex=ROC_FULL_DUPLEX;
        }
        else if(0 == strncmp(communicateWay, "10M_halfDuplex", sizeof("10M_halfDuplex")))
        {
            speed =ROC_SPEED_10;
            duplex=ROC_HALF_DUPLEX;
        }
        else if(0 == strncmp(communicateWay, "100M_fullDuplex", sizeof("100M_fullDuplex")))
        {
            speed =ROC_SPEED_100;
            duplex=ROC_FULL_DUPLEX;
        }
        else if(0 == strncmp(communicateWay, "100M_halfDuplex", sizeof("100M_halfDuplex")))
        {
            speed =ROC_SPEED_100;
            duplex=ROC_HALF_DUPLEX;
        }

        strcpy(communicateTmp,communicateWay);
        ret = set_commute_way(deviceName,speed,duplex);
    }

    if(ret == NETWORK_SUCCESS)
    {
        NetWorkGetEth(deviceName, &EthCfg);
        memcpy(EthCfg.communicateWay, communicateTmp, strlen(communicateTmp)+1);
        NetWorkSetEth(deviceName, &EthCfg);
    }

    return ret;
}



//Settings for eth0:
//Supported link modes:   10baseT/Half 10baseT/Full
//                        100baseT/Half 100baseT/Full
//Speed: 100Mb/s
//Duplex: Full
INT32_T rocme_get_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay)
{
ROCME_TEST_PRINT
#if 0
    struct ifreq ifr;
    int fd;
    struct ethtool_cmd ecmd;
    int allfail = 1;

    NETWORK_PRINT("%s: %s\n", __FUNCTION__, deviceName);

    /* Setup our control structures. */
    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, deviceName);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        return NETWORK_FAILED;
    }

    ecmd.cmd = ETHTOOL_GSET;
    ifr.ifr_data = (caddr_t)&ecmd;
    if(ioctl(fd, SIOCETHTOOL, &ifr))
    {
        close(fd);
        perror("SIOCETHTOOL");
        return NETWORK_FAILED;
    }

    if(ecmd.speed == ROC_SPEED_10)
    {
        if(ecmd.duplex == ROC_FULL_DUPLEX)
        {
            memcpy(communicateWay, "10M_fullDuplex", sizeof("10M_fullDuplex"));
        }
        else
        {
            memcpy(communicateWay, "10M_halfDuplex", sizeof("10M_halfDuplex"));
        }
    }
    else if(ecmd.speed == ROC_SPEED_100)
    {
        if(ecmd.duplex == ROC_FULL_DUPLEX)
        {
            memcpy(communicateWay, "100M_fullDuplex", sizeof("100M_fullDuplex"));
        }
        else
        {
            memcpy(communicateWay, "100M_halfDuplex", sizeof("100M_halfDuplex"));
        }
    }
    else
    {
        memcpy(communicateWay, "adapting", sizeof("adapting"));
    }

    close(fd);
    #endif
    return NETWORK_SUCCESS;
}


/*******************************************************************
���ܣ���ȡ�����������Ƿ����(��PC�ϵ����û���ù���)
���������
    enable:��ֵ�ͣ�1��ʾĿǰ�������ã�0��ʾ���������ã��ɶ�д
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ڵ��� Network.save()��д Flash
*********************************************************************/
INT32_T rocme_set_ethernet_status(CHAR_T* deviceName, ROC_BOOL enable)
{
ROCME_TEST_PRINT
    struct ifreq ifr;
    int nSockfd;
    char pcIfName[30];
    Roc_Ethernet_Config_t stTmpCfg;

    if (deviceName == NULL)
    {
        NETWORK_PRINT("ERROR:[%s] invalid parameters\n", __FUNCTION__);
        return NETWORK_FAILED;
    }

    NETWORK_PRINT("%s: %s\n", __FUNCTION__, deviceName);

    sprintf(pcIfName,"%s",deviceName);

    memset(&ifr, 0, sizeof(ifr));
    memcpy(ifr.ifr_name, pcIfName, sizeof(ifr.ifr_name));

    nSockfd  =  socket(AF_INET, SOCK_DGRAM, 0);
    if (nSockfd == -1)
    {
        return NETWORK_FAILED;
    }

    if (ioctl(nSockfd, SIOCGIFFLAGS, &ifr) < 0)
    {
        close(nSockfd);
        return NETWORK_FAILED;
    }

    if(enable)
    {
        ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);
    }
    else
    {
        ifr.ifr_flags &= ~IFF_UP;
    }

    if (ioctl(nSockfd, SIOCSIFFLAGS, &ifr) < 0)
    {
        close(nSockfd);
        return NETWORK_FAILED;
    }

    NetWorkGetEth(deviceName, &stTmpCfg);
    stTmpCfg.ethernetEnable = enable;
    NetWorkSetEth(deviceName, &stTmpCfg);

    close(nSockfd);

    return NETWORK_SUCCESS;
}


INT32_T rocme_get_ethernet_status(CHAR_T* deviceName )
{
ROCME_TEST_PRINT
    int len = 0;
    int sockfd;
    struct ifreq ifr;
    struct sockaddr_in *sin;
    struct ifconf ifc;
    ROC_BOOL enable = 0;

    if (deviceName == NULL)
    {
        NETWORK_PRINT("ERROR:[%s] invalid parameters\n", __FUNCTION__);
        return -1;
    }

    NETWORK_PRINT("[%s] %s\n", __FUNCTION__, deviceName);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        NETWORK_ERROR("ERROR:[porting_set_IP] socket() failed\n");
        return -1;
    }

    /* interface request struct */
    memset(&ifr, 0, sizeof(struct ifreq));
    strcpy(ifr.ifr_name, deviceName);

    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0)
    {
        NETWORK_PRINT("ERROR:[%s]%d ioctl(SIOCGIFFLAGS) failed\n", __FUNCTION__, __LINE__);
        close(sockfd);
        return -1;
    }

    if (ifr.ifr_flags & IFF_UP)
    {
        enable = 1;
    }
    else
    {
        enable = 0;
    }

    close(sockfd);

    NETWORK_PRINT("interface card %s status: %d\n", deviceName, enable);

    return enable;
}




static char g_cFileRd[1024];
static ROC_BOOL rocme_parse_device_num(CHAR_T deviceNameArray[][16], CHAR_T* deviceNumber)
{
ROCME_TEST_PRINT
    FILE *pCfgFile = NULL;
    ROC_BOOL bRet = ROC_FALSE;
    CHAR_T* token;
    char cDeviceName[16];
#define findstr ":"
    int ii = 0;

    pCfgFile = fopen("/proc/net/dev", "rb");
    *deviceNumber = 0;

    if(pCfgFile == NULL)
    {
        rocme_porting_dprintf( "[%s]open file error\n", __FUNCTION__ );
        goto EXIT;
    }

    if(fread((CHAR_T*)g_cFileRd, sizeof(g_cFileRd), sizeof(char), pCfgFile) == -1)
    {
        rocme_porting_dprintf( "[%s]file read error\n", __FUNCTION__ );
        goto EXIT;
    }

    token = strtok(g_cFileRd, findstr);
    while (token != NULL)
    {
        memset(cDeviceName, 0, sizeof(cDeviceName));
        strncpy(cDeviceName, token-5, 5);
        rocme_porting_dprintf("token=%s, cDeviceName=%s\n", token-5, cDeviceName);
        if((strstr(cDeviceName, "lo") == NULL) && (strlen(cDeviceName) != 0))
        {
            strcpy(deviceNameArray[*deviceNumber], cDeviceName);
            *deviceNumber += 1;
        }

        token = strtok(NULL, findstr);
    }

    bRet = ROC_TRUE;

EXIT:
    if (pCfgFile != NULL)
    {
        fclose(pCfgFile);
    }
    return bRet;
}



INT32_T rocme_porting_network_get_ethernets_num(CHAR_T deviceNameArray[][16], CHAR_T* deviceNumber)
{
ROCME_TEST_PRINT
	INT32_T i = 0;
	*deviceNumber = ETH_DEVICE_NUM;
	for(i=0;i<ETH_DEVICE_NUM;i++)
	{
		memcpy(	deviceNameArray[i],ROCME_ETH_NAME[i],sizeof(ROCME_ETH_NAME[i]));
	}
	return 1;

   /// return rocme_parse_device_num(deviceNameArray, deviceNumber);
}




INT32_T rocme_porting_network_set_dnsserver(CHAR_T* deviceName, int nIndex, CHAR_T *pDNSServer)
{	
ROCME_TEST_PRINT
    INT32_T nRet = NETWORK_FAILED;

    Roc_Ethernet_Config_t stEthConfTmp;

    if ((deviceName == NULL) || (pDNSServer == NULL))
    {
        return NETWORK_FAILED;
    }

    rocme_porting_dprintf("[%s]deviceName=%s, nIndex=%d, pDNSServer=%s\n", __FUNCTION__, deviceName, nIndex, pDNSServer);

    NetWorkGetEth(deviceName, &stEthConfTmp);

    if (!stEthConfTmp.dhcpEnable || !stEthConfTmp.dhcpAutoGetDNS)
    {
        nRet = rocme_porting_set_dnsserver(nIndex, pDNSServer);
        if (nRet == 0)
        {
            NetWorkGetEth(deviceName, &stEthConfTmp);
            memcpy(stEthConfTmp.dnsServers[nIndex], pDNSServer, strlen(pDNSServer)+1);
            NetWorkSetEth(deviceName, &stEthConfTmp);
        }
    }

    rocme_porting_dprintf("[%s]nRet = %d\n", __FUNCTION__, nRet);

    return (nRet ? NETWORK_FAILED : NETWORK_SUCCESS); 
  
}


INT32_T rocme_porting_network_get_dnsserver(CHAR_T* deviceName, int nIndex, CHAR_T *pDNSServer)
{
ROCME_TEST_PRINT
    Roc_Ethernet_Config_t stEthConfTmp;
    INT32_T nRet = NETWORK_FAILED;

    if ((deviceName == NULL) || (pDNSServer == NULL))
    {
        return NETWORK_FAILED;
    }

    rocme_porting_get_dnsserver(nIndex, pDNSServer);
    NetWorkGetEth(deviceName, &stEthConfTmp);
    strcpy(stEthConfTmp.dnsServers[nIndex], pDNSServer);
    NetWorkSetEth(deviceName, &stEthConfTmp);

    return NETWORK_SUCCESS;
}



/*******************************************************************
���ܣ�����DHCPģʽ�Ƿ��Զ���ȡDNS
���������
    bDHCP: 1��ʾ�Զ���ȡDNS��0��ʾ�ֶ���ȡ
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����Ҫ����
*********************************************************************/
INT32_T rocme_porting_set_dns_auto(CHAR_T* deviceName, ROC_BOOL bAutoGetDns)
{
ROCME_TEST_PRINT
    Roc_Ethernet_Config_t stEthConfTmp;

    if (deviceName == NULL)
    {
        return NETWORK_FAILED;
    }

    NetWorkGetEth(deviceName, &stEthConfTmp);
    stEthConfTmp.dhcpAutoGetDNS = bAutoGetDns;
    NetWorkSetEth(deviceName, &stEthConfTmp);

    rocme_write_dhcp_get_dns_method(deviceName, bAutoGetDns);
    return NETWORK_SUCCESS;
}


/*******************************************************************
���ܣ���ȡDHCPģʽ�Ƿ��Զ���ȡDNS
�������
    bDHCP: 1��ʾ�Զ���ȡDNS��0��ʾ�ֶ���ȡ
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����Ҫ����
*********************************************************************/
INT32_T rocme_porting_get_dns_auto(CHAR_T* deviceName, ROC_BOOL *pbAutoGetDns)
{
ROCME_TEST_PRINT
    Roc_Ethernet_Config_t stEthConfTmp;

    if ((deviceName == NULL) || (pbAutoGetDns == NULL))
    {
        return NETWORK_FAILED;
    }

    NetWorkGetEth(deviceName, &stEthConfTmp);
    *pbAutoGetDns = stEthConfTmp.dhcpAutoGetDNS;

    return NETWORK_SUCCESS;
}


static ROC_BOOL rocme_parse_dhcp_info(CHAR_T* serverIp, CHAR_T* leaseObtainedTime, CHAR_T* leaseExpiresTime )
{
ROCME_TEST_PRINT
    FILE *fd = NULL;
    CHAR_T line[256];
    CHAR_T*ptr = NULL;
    ROC_BOOL ret = ROC_FALSE;

    struct tm *get_tm;
    struct tm obtained_tm, expires_tm;
    struct tm tmp_tm[1] = {0};
    rocme_time_t ts_roc_tm[1] = {0};
    INT32_T baseoff = 0,lease_offset = 0;
    time_t obtained_time,expires_time,current_time,ts_tim;

    NETWORK_PRINT("%s: enter\n", __FUNCTION__);

    fd = fopen("/mnt/dhcp_print.conf", "r");
    if( NULL == fd )
    {
        NETWORK_ERROR("/mnt/dhcp_print.conf opens failed \n");
        return ret;
    }

    if (g_unDifferTime == 0)
    {
        rocme_porting_network_ntp_update();
    }

    while(fgets(line, sizeof(line), fd) != NULL)
    {
        if((ptr = strstr(line, "lease_start_time")))
        {
        
			/*parse string like "lease_start_time:2000-1-1 0:0:12" */
			sscanf(ptr,"%*[a-zA-Z_ :]%d%*[- ]%d%*[- ]%d%*[- ]%d:%d:%d",
			&tmp_tm->tm_year, &tmp_tm->tm_mon, &tmp_tm->tm_mday, &tmp_tm->tm_hour,
			&tmp_tm->tm_min, &tmp_tm->tm_sec);

#if 0
            ptr += strlen("lease_start_time")+1;

            if(NULL == ptr)
            {
                NETWORK_ERROR("get lease_start_time failed \n");
            }
			
            tmp_tm->tm_year = atoi(ptr);

            while(*ptr != '-')
            {
                ++ptr;
            }
            tmp_tm->tm_mon = atoi(++ptr);

            while(*ptr != '-')
            {
                ++ptr;
            }
            tmp_tm->tm_mday = atoi(++ptr);

            while(*ptr != ' ')
            {
                ++ptr;
            }
            tmp_tm->tm_hour = atoi(++ptr);

            while(*ptr != ':')
            {
                ++ptr;
            }
            tmp_tm->tm_min = atoi(++ptr);

            while(*ptr != ':')
            {
                ++ptr;
            }
            tmp_tm->tm_sec = atoi(++ptr);
#endif
			
            rocme_porting_dprintf("[%s]tm_year=%d, tm_mon=%d, tm_mday=%d, tm_hour=%d, tm_min=%d, tm_sec=%d\n",
                                  __FUNCTION__, tmp_tm->tm_year, tmp_tm->tm_mon, tmp_tm->tm_mday, tmp_tm->tm_hour, tmp_tm->tm_min, tmp_tm->tm_sec );

            tmp_tm->tm_year -= 1900;
            tmp_tm->tm_mon -= 1;
            obtained_time = mktime(tmp_tm);   // ��ǰд���ļ���ʱ��

            current_time = obtained_time;

            //get_tm = localtime(&current_time);
            if (tmp_tm != NULL)
            {
                obtained_tm.tm_year = tmp_tm->tm_year;
                obtained_tm.tm_mon = tmp_tm->tm_mon;
                obtained_tm.tm_mday = tmp_tm->tm_mday;
                obtained_tm.tm_hour = tmp_tm->tm_hour;
                obtained_tm.tm_min = tmp_tm->tm_min;
                obtained_tm.tm_sec = tmp_tm->tm_sec;

            }
            memcpy(&g_obtained_tm, &obtained_tm, sizeof(struct tm));
            obtained_tm.tm_year += 1900;
            obtained_tm.tm_mon += 1;

            rocme_porting_dprintf("[%s]obtained_tm->tm_year=%ld, tm_mday=%ld, obtained_tm.tm_hour=%ld, obtained_tm->tm_min=%ld, obtained_tm->tm_sec=%ld\n",
                                  __FUNCTION__, obtained_tm.tm_year, obtained_tm.tm_mday, obtained_tm.tm_hour, obtained_tm.tm_min, obtained_tm.tm_sec);

            if(leaseObtainedTime)
            {
                sprintf(leaseObtainedTime,"%04d-%02d-%02d %02d:%02d:%02d",
                        obtained_tm.tm_year,obtained_tm.tm_mon,obtained_tm.tm_mday,
                        obtained_tm.tm_hour,obtained_tm.tm_min,obtained_tm.tm_sec);
            }

        }

        if((ptr = strstr(line, "lease_offset")))
        {
            ptr += strlen("lease_offset")+1;

            if(NULL == ptr)
            {
                NETWORK_ERROR("get lease_offset failed \n");
            }

            lease_offset = atoi(ptr);
            expires_time = lease_offset + current_time;
            get_tm = localtime(&expires_time);
            if (get_tm != NULL)
            {
                expires_tm.tm_year = get_tm->tm_year ;
                expires_tm.tm_mon = get_tm->tm_mon;
                expires_tm.tm_mday = get_tm->tm_mday;
                expires_tm.tm_hour = get_tm->tm_hour;
                expires_tm.tm_min = get_tm->tm_min;
                expires_tm.tm_sec = get_tm->tm_sec;
            }

            memcpy(&g_expires_tm, &expires_tm, sizeof(struct tm));
            expires_tm.tm_year += 1900;
            expires_tm.tm_mon += 1;

            rocme_porting_dprintf("[%s]expires_tm->tm_year=%ld, tm_mday=%ld, expires_tm.tm_hour=%ld, expires_tm->tm_min=%ld, expires_tm->tm_sec=%ld\n",
                                  __FUNCTION__, expires_tm.tm_year, expires_tm.tm_mday, expires_tm.tm_hour,expires_tm.tm_min, expires_tm.tm_sec);

            if(leaseExpiresTime)
            {
                sprintf(leaseExpiresTime,"%04d-%02d-%02d %02d:%02d:%02d",
                        expires_tm.tm_year,expires_tm.tm_mon,expires_tm.tm_mday,
                        expires_tm.tm_hour,expires_tm.tm_min,expires_tm.tm_sec);
            }
        }

        if((ptr = strstr(line, "dhcp_server_ip")))
        {
			sscanf(ptr,"%*[a-zA-Z_ :]%s",serverIp);
#if 0			
			ptr += strlen("dhcp_server_ip")+1;

            if(NULL == ptr)
            {
                NETWORK_ERROR("get dhcp_server_ip failed \n");
            }

            if(serverIp)
            {
                strcpy(serverIp,ptr);
            }
#endif
		}

    }

    fclose(fd);

    return ROC_TRUE;
}



static void GetDHCPInfo(char *pDeviceName, Roc_DHCP_Info_t *pDHCPInfo)
{
    if ((pDeviceName == NULL) ||(pDHCPInfo == NULL))
    {
        return;
    }

    pDHCPInfo->dhcpPort = ROCME_PRODUCT_DHCP_PORT;
    rocme_porting_get_IP(pDeviceName, pDHCPInfo->ipAddress);
    rocme_porting_get_mask(pDeviceName, pDHCPInfo->mask);
    rocme_porting_get_gateway(pDeviceName, pDHCPInfo->gateway);

    rocme_parse_dhcp_info(pDHCPInfo->dhcpServer, &pDHCPInfo->stLeaseTime.leaseObtained, &pDHCPInfo->stLeaseTime.leaseExpires);
}




void checkDhcpStatus(void* param)
{
    FILE *fd = NULL;
    CHAR_T line[256];
    CHAR_T*ptr = NULL;
    int errCode;
    int flag = ROC_FALSE;
    int i = 0;
    SysNetworkEvent_t stEvent;
    int nIndex = DEFAULT_ETH_DEVICE_INDEX;
    Roc_Ethernet_Config_t stEthCfg;
    ROC_BOOL bDHCPSuccess = ROC_FALSE;

    rocme_porting_dprintf("[%s]%d,param=%s, size=0x%x\n", __FUNCTION__, __LINE__,param,sizeof(Roc_Ethernet_Config_t));

    rocme_porting_task_sleep(2000);

    while((i++ < 30) && (ROC_FALSE == flag))
    {
        rocme_porting_task_sleep(500);

        errCode = access("/mnt/dhcp_print.conf", F_OK);
        if(errCode != 0)
        {
            continue;
        }
        rocme_porting_task_sleep(200);

        rocme_porting_dprintf("/mnt/dhcp_print.conf file exist. %d\n", i);

        fd = fopen("/mnt/dhcp_print.conf", "rb");
        if( fd )
        {
            while(fgets(line, sizeof(line), fd) != NULL)
            {
                if((ptr = strstr(line, "select for")))
                {
                    flag = ROC_TRUE;

                    break;
                }
            }
        }

        fclose(fd);
    }

        rocme_porting_dprintf("[%s]%d,param=%s\n", __FUNCTION__, __LINE__,param);


    if(flag)
    {
        //10508 ���� DHCP�ɹ���
        stEvent.msg = 10508;
        bDHCPSuccess = ROC_TRUE;
        GetDHCPInfo(param, &g_stDHCPInfo[nIndex]);
    }
    else
    {
        //10509 ���� DHCPͬ����ʱ��
        stEvent.msg = 10509;
        bDHCPSuccess = ROC_FALSE;
        system("killall udhcpc");
    }

    rocme_porting_dprintf("%s, param=%s, msgtype: %d\n", __FUNCTION__, param, stEvent.msg);

    stEvent.msgType = ROC_SYSEVENT_TYPE;
    stEvent.modifiers[0] = 0;

    network_event_cbk(0, &stEvent, sizeof(stEvent));

    NetWorkGetEth(param, &stEthCfg);
    stEthCfg.dhcpSuccess = bDHCPSuccess;
    NetWorkSetEth(param, &stEthCfg);

 	rocme_porting_dprintf("[%s]%d,param=%s\n", __FUNCTION__, __LINE__,param);

    //����DNSΪ�ֶ�״̬����dhcp���������Ϊ0�����⡣
    rocme_porting_network_set_dnsserver(param, 0, stEthCfg.dnsServers[0]);
    rocme_porting_network_set_dnsserver(param, 1, stEthCfg.dnsServers[1]);
    rocme_porting_network_set_dnsserver(param, 2, stEthCfg.dnsServers[2]);
}



/**********************************
����˵����
    ���õײ������ DHCP ������ʽ��dhcp Ϊ����� DHCP ������ʽ��0: ��ʾ������ DHCP��1: ��ʾ���� DHCP�� ����ֵ��Ч��ֱ�ӷ���-1��

����˵����
    �������������� DHCP ������ʽ����
    �����������

��    �أ�0 - ���óɹ���-1 - ʧ��

�ο�ʵ�֣���rocme_product_demo.c
**********************************/
INT32_T rocme_porting_network_set_dhcp(const CHAR_T *pDeviceName, const Roc_DHCP_Mode_e dhcp_mode)
{
ROCME_TEST_PRINT
    ROC_BOOL dhcpflag = ROC_FALSE;
    Roc_Ethernet_Config_t stEthConfTmp;
    char deviceNameArray[4][16];
    int nDeviceIndex = 0;

    rocme_porting_dprintf("###%s: %s: %d\n", __FUNCTION__, pDeviceName, dhcp_mode);

    if ((pDeviceName == NULL) || (dhcp_mode > ROC_USED_DHCP))
    {
        return -1;
    }
    
    nDeviceIndex = NetWorkGetDeviceIndex(pDeviceName);

#if !defined(NFS_DEBUG)
    if ( ROC_USED_DHCP == dhcp_mode )
    {
        FILE *fd = NULL;
        INT32_T i = 0;
        INT32_T errCode = 0;
        CHAR_T line[256];
        CHAR_T*ptr = NULL;

        dhcpflag = ROC_TRUE;
        
        system("killall udhcpc");
        rocme_porting_task_sleep(200);

        rocme_porting_dprintf("%s: %d\n", __FUNCTION__, __LINE__);

        system("rm -rf /mnt/dhcp_print.conf");
        
        if(0 != g_checkTaskHandle[nDeviceIndex])
        {
        	rocme_porting_dprintf("%s: %d\n", __FUNCTION__, __LINE__);
            rocme_porting_task_destroy(g_checkTaskHandle[nDeviceIndex]);
            g_checkTaskHandle[nDeviceIndex] = 0;
        }

        rocme_porting_dprintf("%s: %d\n", __FUNCTION__, __LINE__);
        strcpy(g_sDeviceName[nDeviceIndex], pDeviceName);

        g_checkTaskHandle[nDeviceIndex] = rocme_porting_task_create("dhcp_task", checkDhcpStatus, (void *)g_sDeviceName[nDeviceIndex], 1, 0x8000);
        system("udhcpc -q -t 1  -n > /mnt/dhcp_print.conf");  /*busybox �е�ϵͳ����*/
        rocme_porting_dprintf("%s: %d\n", __FUNCTION__, __LINE__);
    }
    else if ( ROC_NO_DHCP == dhcp_mode )
    {
        dhcpflag = ROC_FALSE;
        system("killall udhcpc");
        rocme_porting_task_sleep(200);
        
        if(0 != g_checkTaskHandle[nDeviceIndex])
        {
            rocme_porting_task_destroy(g_checkTaskHandle[nDeviceIndex]);
            g_checkTaskHandle[nDeviceIndex] = 0;
        }
    }
#endif


    NetWorkGetEth(pDeviceName, &stEthConfTmp);
    stEthConfTmp.dhcpEnable = dhcpflag;
    NetWorkSetEth(pDeviceName, &stEthConfTmp);

    if((0 == g_checkTaskHandle[nDeviceIndex]) && (ROC_USED_DHCP == dhcp_mode))
    {
        SysNetworkEvent_t stEvent;

        //10509 ���� DHCPͬ����ʱ��
        stEvent.msg = 10509;

        system("killall udhcpc");

        rocme_porting_dprintf("%s, msgtype: %d\n", __FUNCTION__, stEvent.msg);

        stEvent.msgType = ROC_SYSEVENT_TYPE;
        stEvent.modifiers[0] = 0;
        network_event_cbk(0, &stEvent, sizeof(stEvent));
    }

    return 0;
}


/**********************************
����˵����
    ��ȡ��ǰ����� DHCP ������ʽ���룬0: ��ʾ������ DHCP��1: ��ʾ���� DHCP��

����˵����
    �����������
    ���������dhcp_mode �Ƿ�����DHCP

��    �أ�1��ʾ�ɹ���0��ʾʧ��

�ο�ʵ�֣���rocme_product_demo.c
**********************************/
INT32_T rocme_porting_network_get_dhcp_status(CHAR_T *pDeviceName, Roc_DHCP_Mode_e *dhcp_mode)
{
ROCME_TEST_PRINT
    INT32_T nRet = NETWORK_FAILED;
    Roc_Ethernet_Config_t stEthConfTmp;

    rocme_porting_dprintf("[%s]pDeviceName=%s\n", __FUNCTION__, pDeviceName);

    if ((pDeviceName == NULL) || (dhcp_mode == NULL))
    {
        return NETWORK_FAILED;
    }

    NetWorkGetEth(pDeviceName, &stEthConfTmp);
    *dhcp_mode = stEthConfTmp.dhcpEnable;
    nRet = NETWORK_SUCCESS;

    rocme_porting_dprintf("[%s]nRet=%d\n", __FUNCTION__, nRet);

    return nRet;
}



static ROC_BOOL rocme_porting_trans_time(Roc_DHCPLeaseTime_t *srctime, Roc_DHCPLeaseTime_t *pdesttime)
{
ROCME_TEST_PRINT
    time_t current_time, wrifileTime, obtaintime, oexpirestime;
    struct tm *stcur_tm,*stobtaintm, *stexpirestm;
    struct tm srcObtaintm, srcExpirestm;

    if ((srctime == NULL) || (pdesttime == NULL))
    {
        return ROC_FALSE;
    }

    current_time = time(NULL);
    stcur_tm = localtime(&current_time);

    //�����ǰʱ�����ļ�ʱ��ȽϽӽ�������Ϊ�ļ�ʱ��ɿ�����Ҫת��
    //������Ҫת��Ϊ��ǰʱ��

    if ((stcur_tm->tm_year == g_obtained_tm.tm_year)
            && (stcur_tm->tm_mon == g_obtained_tm.tm_mon))
    {
        rocme_porting_dprintf("srctime->leaseExpires=%s, srctime->leaseObtained=%s\n", srctime->leaseExpires, srctime->leaseObtained);
    }
    else
    {
        wrifileTime = mktime(&g_obtained_tm);
        obtaintime = (wrifileTime + g_unDifferTime);
        stobtaintm = localtime(&obtaintime);
        stobtaintm->tm_year += 1900;
        stobtaintm->tm_mon += 1;

        sprintf(pdesttime->leaseObtained,"%04d-%02d-%02d %02d:%02d:%02d",
                stobtaintm->tm_year,stobtaintm->tm_mon,stobtaintm->tm_mday,
                stobtaintm->tm_hour,stobtaintm->tm_min,stobtaintm->tm_sec);

        wrifileTime = mktime(&g_expires_tm);
        oexpirestime = (wrifileTime + g_unDifferTime);
        stexpirestm = localtime(&oexpirestime);
        stexpirestm->tm_year += 1900;
        stexpirestm->tm_mon += 1;

        sprintf(pdesttime->leaseExpires,"%04d-%02d-%02d %02d:%02d:%02d",
                stexpirestm->tm_year,stexpirestm->tm_mon,stexpirestm->tm_mday,
                stexpirestm->tm_hour,stexpirestm->tm_min,stexpirestm->tm_sec);
    }
    /*
    printf("%04d-%02d-%02d %02d:%02d:%02d",
            stobtaintm->tm_year,stobtaintm->tm_mon,stobtaintm->tm_mday,
            stobtaintm->tm_hour,stobtaintm->tm_min,stobtaintm->tm_sec);
    printf("%04d-%02d-%02d %02d:%02d:%02d",
            stexpirestm->tm_year,stexpirestm->tm_mon,stexpirestm->tm_mday,
            stexpirestm->tm_hour,stexpirestm->tm_min,stexpirestm->tm_sec);
//*/
    return ROC_TRUE;
}


/**********************************
����˵����
    ��ȡDHCP��̬�����DHCP�����Ϣ

����˵����
    �����������
    ���������dhcp����Ϣ�����Roc_DHCP_Info_t�ṹ��

��    �أ�1��ʾ�ɹ���0��ʾʧ��

�ο�ʵ�֣�
**********************************/
INT32_T rocme_porting_get_dhcp_Info(CHAR_T* deviceName, Roc_DHCP_Info_t *pdhcpIP)
{
ROCME_TEST_PRINT
	int nIndex = DEFAULT_ETH_DEVICE_INDEX;
	INT32_T nRet = 0;
	Roc_Ethernet_Config_t stEthConfTmp;

	if ((deviceName == NULL) || (pdhcpIP == NULL))
	{
		return NETWORK_FAILED;
	}

	NetWorkGetEth(deviceName, &stEthConfTmp);

	if (stEthConfTmp.dhcpEnable && stEthConfTmp.dhcpSuccess)
	{
		memcpy(pdhcpIP, &g_stDHCPInfo[nIndex], sizeof(Roc_DHCP_Info_t));

		if (rocme_porting_trans_time(&g_stDHCPInfo[nIndex].stLeaseTime, &(pdhcpIP->stLeaseTime)))
		{
			nRet = NETWORK_SUCCESS;
		}
	}

	NETWORK_PRINT("%s,LeaseTime:%s-%s\n",__FUNCTION__,pdhcpIP->stLeaseTime.leaseObtained,pdhcpIP->stLeaseTime.leaseExpires);

	return nRet;
}


INT32_T romce_porting_network_get_lan_status(const CHAR_T *pDeviceName, ROC_BOOL *pbStatus)
{
ROCME_TEST_PRINT
    Roc_Ethernet_Config_t stEthConfTmp;

    if ((pDeviceName == NULL) || (pbStatus == NULL))
    {
        return NETWORK_FAILED;
    }

    *pbStatus = rocme_porting_check_netcon_status(pDeviceName);
    NetWorkGetEth(pDeviceName, &stEthConfTmp);
    stEthConfTmp.lanStatus = *pbStatus;
    NetWorkSetEth(pDeviceName, &stEthConfTmp);

    return NETWORK_SUCCESS;
}


INT32_T rocme_porting_network_set_eth_status(const CHAR_T *pDeviceName, ROC_BOOL bEthStatus)
{
ROCME_TEST_PRINT
	int nRet = NETWORK_FAILED;

	
    nRet = rocme_set_ethernet_status(pDeviceName, bEthStatus);
    if ((nRet == NETWORK_SUCCESS) && (bEthStatus))
    {
    	//��������IP��Ϣ
    	Roc_Ethernet_Config_t tmpCfg;
    	
    	NetWorkGetEth(pDeviceName, &tmpCfg);
    	
	    if(tmpCfg.dhcpEnable)
        {
            rocme_write_dhcp_get_dns_method(tmpCfg.deviceName, tmpCfg.dhcpAutoGetDNS);
            rocme_porting_network_set_dhcp(tmpCfg.deviceName, ROC_USED_DHCP);
        }
        else
        {
            Roc_IP_Config_t IPInfo;

            IPInfo.index = 0;
            strcpy(IPInfo.deviceName, tmpCfg.deviceName);
            strcpy(IPInfo.ipAddress, tmpCfg.staticIP[0].ipAddress);
            strcpy(IPInfo.mask, tmpCfg.staticIP[0].mask);
            strcpy(IPInfo.gateway, tmpCfg.staticIP[0].gateway);
            rocme_porting_network_set_IP(IPInfo.deviceName, &IPInfo);

            IPInfo.index = 1;
            strcpy(IPInfo.deviceName, tmpCfg.deviceName);
            strcpy(IPInfo.ipAddress, tmpCfg.staticIP[1].ipAddress);
            strcpy(IPInfo.mask, tmpCfg.staticIP[1].mask);
            strcpy(IPInfo.gateway, tmpCfg.staticIP[1].gateway);
            rocme_porting_network_set_IP(IPInfo.deviceName, &IPInfo);

            IPInfo.index = 2;
            strcpy(IPInfo.deviceName, tmpCfg.deviceName);
            strcpy(IPInfo.ipAddress, tmpCfg.staticIP[2].ipAddress);
            strcpy(IPInfo.mask, tmpCfg.staticIP[2].mask);
            strcpy(IPInfo.gateway, tmpCfg.staticIP[2].gateway);
            rocme_porting_network_set_IP(IPInfo.deviceName, &IPInfo);
            
            rocme_porting_set_dnsserver(0, tmpCfg.dnsServers[0]);
            rocme_porting_set_dnsserver(1, tmpCfg.dnsServers[1]);
            rocme_porting_set_dnsserver(2, tmpCfg.dnsServers[2]);
        }

        NetWorkSetEth(pDeviceName, &tmpCfg);

    }

    return nRet;
}



INT32_T rocme_porting_network_get_eth_status(const CHAR_T *pDeviceName, ROC_BOOL *pbEthStatus)
{
ROCME_TEST_PRINT
    Roc_Ethernet_Config_t stEthConfTmp;

    if ((pDeviceName == NULL) || (pbEthStatus == NULL))
    {
        return NETWORK_FAILED;
    }

    *pbEthStatus = rocme_get_ethernet_status(pDeviceName);
    NetWorkGetEth(pDeviceName, &stEthConfTmp);
    stEthConfTmp.ethernetEnable = *pbEthStatus;
    NetWorkSetEth(pDeviceName, &stEthConfTmp);

    return NETWORK_SUCCESS;
}




/***********************************************************************
�豸��device��	����ֵ	����
�����豸���ʺ�
    0	�豸�����ڣ����ɷ���
	1	�豸���ڣ����޷���ȡ״̬

eth0, eth1�������豸

    101	��������
	102	��������

cm
    201	������������
	202	���������ж�
	203	����״̬���ı䣬���ǲ���
	204	CableModem��STBͨ���ж�
	205	CableModem��STBͨ���жϣ���������
*/
INT32_T rocme_porting_network_get_device_state(CHAR_T* deviceName, INT32_T* deviceState)
{
ROCME_TEST_PRINT
    CHAR_T deviceNameArray[8][16];
    CHAR_T  deviceNumber;
    CHAR_T  gateway[16];
    CHAR_T  result[256];

    if ((deviceName == NULL) || (deviceState == NULL))
    {
        NETWORK_PRINT("ERROR:[%s] invalid parameters\n", __FUNCTION__);
        return NETWORK_FAILED;
    }

    NETWORK_PRINT("%s: enter\n", __FUNCTION__);

    //��ȡ��������
    if(ROC_TRUE != rocme_porting_network_get_ethernets_num(deviceNameArray, &deviceNumber))
    {
        *deviceState = 0;
        goto STATE_EXIT;
    }

    while(deviceNumber > 0)
    {
        if(!strcasecmp(deviceNameArray[deviceNumber-1],deviceName))
        {
            break;
        }

        deviceNumber--;
    }

    if(deviceNumber == 0)
    {
        *deviceState = 0;
        goto STATE_EXIT;
    }

    //rocme_get_ethernet_status����-1ʱ����ȡ����״̬ʧ�ܡ�
    if(-1 == rocme_get_ethernet_status(deviceName))
    {
        *deviceState = 1;
        goto STATE_EXIT;
    }

    if(NULL != strstr(deviceName,"eth"))
    {
        if(ROC_TRUE != rocme_porting_check_netcon_status(deviceName))
        {
            *deviceState = 102;
            goto STATE_EXIT;
        }
        else
        {
            *deviceState = 101;
            goto STATE_EXIT;
        }
    }
    else if(NULL != strstr(deviceName,"cm"))
    {
        rocme_porting_get_gateway(deviceName,gateway);

        if(0 == rocme_porting_ping(gateway, result))
        {
            *deviceState = 201;
            goto STATE_EXIT;
        }
        else
        {
            *deviceState = 202;
            goto STATE_EXIT;
        }
    }

STATE_EXIT:
    NETWORK_PRINT("%s: exit\n", __FUNCTION__);

    return NETWORK_SUCCESS;
}

/*******************************************************************
���ܣ����������õ���������һ�������ø��ײ㣬�������԰��� ethernet�����µ�����������Զ����Խ������á��书������ PC���������õ�ȷ�ϰ�ť�Ĺ��ܡ�
�����������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_submit_parameters(CHAR_T* deviceName)
{
    NETWORK_PRINT("%s: enter\n", __FUNCTION__);
    return 1;
}

static INT32_T network_device_restore(CHAR_T *pDeviceName)
{
    INT32_T errCode;
    char szFileName[128];
    FILE *pCfgFile = NULL;
    UINT32_T len = 0;
    Roc_Ethernet_Config_t tmpCfg;
    Roc_Ethernet_Config_t oldCfg;
    CHAR_T szTmpHostName[256];
    INT32_T error;
    INT32_T ii;

    if (pDeviceName == NULL)
    {
        return NETWORK_FAILED;
    }

    memset(szFileName, 0, sizeof(szFileName));
    sprintf(szFileName, "%s%s%s", "/mnt/ipcfg_", pDeviceName, ".cfg");

    errCode = access(szFileName, F_OK);
    if (errCode != 0)
    {
        rocme_porting_dprintf("%s: [%s] file not exists.\n", __FUNCTION__, szFileName);
        pCfgFile = fopen(szFileName, "wb");
        if(pCfgFile == NULL)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s, %s file open failed!--+--\n", __FUNCTION__, szFileName );
            goto ERROR_EXIT;
        }
    }
    else
    {
        rocme_porting_dprintf("%s: [%s] file exists.\n", __FUNCTION__, szFileName);
        pCfgFile = fopen(szFileName, "wb");
        if(pCfgFile == NULL)
        {
            rocme_porting_dprintf( "--+--**ERROR**: %s, %s file open failed!--+--\n", __FUNCTION__, szFileName );
            goto ERROR_EXIT;
        }
    }

    strcpy(g_hostName, DEFAULT_HOSTNAME);

    len = fwrite( (CHAR_T*)&g_hostName, 1, sizeof(g_hostName), pCfgFile);
    if( len != sizeof(g_hostName) )
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d, %d!--+--\n", __FUNCTION__, __LINE__, len );
        goto ERROR_EXIT;
    }

    error = fseek(pCfgFile,sizeof(g_hostName),SEEK_SET);
    if(error!=0)
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    strcpy(g_NTPServer, DEFAULT_NTP_SERVER);

    len = fwrite( (CHAR_T*)&g_NTPServer, 1, sizeof(g_NTPServer), pCfgFile);
    if( len !=  sizeof(g_NTPServer))
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    error = fseek(pCfgFile,sizeof(g_hostName)+ sizeof(g_NTPServer),SEEK_SET);
    if(error!=0)
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    memset(&tmpCfg, 0, sizeof(Roc_Ethernet_Config_t));
    memset(&oldCfg, 0, sizeof(Roc_Ethernet_Config_t));

    NetWorkGetEth(pDeviceName, &oldCfg);

    strcpy(tmpCfg.deviceName, pDeviceName);
    tmpCfg.ethernetEnable = NETWORK_DEVICE_ENABLE;
    tmpCfg.dhcpAutoGetDNS = NETWORK_DEVICE_ENABLE;
    tmpCfg.dhcpEnable = NETWORK_DEVICE_ENABLE;
    strcpy(tmpCfg.communicateWay, NETWORK_COMMUNITY_WAY);
    strcpy(tmpCfg.description, DEFAULT_DESCIRPTION);

    len = fwrite( (CHAR_T*)&tmpCfg, 1, sizeof(tmpCfg), pCfgFile);
    if( len !=  sizeof(tmpCfg))
    {
        rocme_porting_dprintf( "--+--**ERROR**: %s , %d!--+--\n", __FUNCTION__, __LINE__ );
        goto ERROR_EXIT;
    }

    for (ii=0; ii<3; ii++)
    {
        Roc_IP_Config_t IPInfo;

        strcpy(IPInfo.deviceName, pDeviceName);
        IPInfo.index = ii;
        strcpy(IPInfo.gateway, tmpCfg.staticIP[ii].gateway);
        strcpy(IPInfo.ipAddress, tmpCfg.staticIP[ii].ipAddress);
        strcpy(IPInfo.mask, tmpCfg.staticIP[ii].mask);
        rocme_porting_network_set_IP(tmpCfg.deviceName, &IPInfo);
    }

    for (ii=0; ii<3; ii++)
    {
        rocme_porting_network_set_dnsserver(pDeviceName, ii, tmpCfg.dnsServers[ii]);
    }

    if(0 != strncmp(oldCfg.communicateWay, tmpCfg.communicateWay, strlen(tmpCfg.communicateWay)))
    {
        rocme_porting_network_set_commute_way(pDeviceName, tmpCfg.communicateWay);
    }

    printf("#####%d, %d, %d\n", oldCfg.dhcpEnable, oldCfg.dhcpSuccess, oldCfg.dhcpAutoGetDNS);

    //������������ã�����dhcpȷ�Ͽ�������ֱ�ӵ���dhcp��ʼ����
    if(!(oldCfg.dhcpEnable && oldCfg.dhcpSuccess && oldCfg.dhcpAutoGetDNS))
    {
        if(tmpCfg.dhcpEnable && tmpCfg.ethernetEnable)
        {
            rocme_write_dhcp_get_dns_method(tmpCfg.deviceName, tmpCfg.dhcpAutoGetDNS);

            rocme_porting_task_sleep(1000);
            rocme_porting_network_set_dhcp(tmpCfg.deviceName, ROC_USED_DHCP);
        }
    }

    NetWorkSetEth(pDeviceName, &tmpCfg);


    if (pCfgFile != NULL)
    {
        fclose( pCfgFile );
        pCfgFile = NULL;
    }

    return NETWORK_SUCCESS;

ERROR_EXIT:
    if (pCfgFile != NULL)
    {
        fclose( pCfgFile );
        pCfgFile = NULL;
    }

    return NETWORK_FAILED;
}



/*******************************************************************
���ܣ����������������Իָ�ΪĬ��ֵ
�����������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_restore(void)
{
ROCME_TEST_PRINT
    INT32_T nRet = NETWORK_FAILED;
    CHAR_T deviceNameArray[ETH_MAX_SUPPORT][16];
    int ii, nSuccessCount;

    nSuccessCount = 0;

    do
    {
        nRet = rocme_porting_network_get_ethernets_num(deviceNameArray, &g_nDeviceNum);
        if (nRet != NETWORK_SUCCESS)
        {
            nRet = NETWORK_FAILED;
            break;
        }

        for (ii=0; ii<g_nDeviceNum; ii++)
        {
            if (network_device_restore(deviceNameArray[ii]) == NETWORK_SUCCESS)
            {
                nSuccessCount++;
            }
        }
    }
    while (0);

    if (nSuccessCount == g_nDeviceNum)
    {
        nRet = NETWORK_SUCCESS;
    }

    return nRet;
}



INT32_T rocme_porting_network_get_description(CHAR_T *deviceName, CHAR_T *pDescription)
{
ROCME_TEST_PRINT
    if ((deviceName == NULL) || (pDescription == NULL))
    {
        return NETWORK_FAILED;
    }

    strcpy(pDescription, DEFAULT_DESCIRPTION);

    return NETWORK_SUCCESS;
}

/* just for beijingsuma */
#if 0
INT32_T network_event_cbk(INT32_T type, void *data, INT32_T data_len)
{
    return NETWORK_SUCCESS;
}

INT32_T Roc_KeyEvt_Init()
{
    return ROC_OK;
}
#endif

