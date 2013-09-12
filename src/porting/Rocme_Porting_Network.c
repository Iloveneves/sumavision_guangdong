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
功能：网络模块使用的回调函数，将消息发送给webapp。
输入参数：
    type:获取消息的来源，type=1001为系统消息，type=1002为键盘，type=1003为鼠标，type=1004为通用遥控器，
        type=1005为 老人型遥控器，type=1006为儿童型遥控器，type值大于1006预留给扩展外设使用
    data:void*类型，根据具体消息类型，应该封装为该消息的数据结构。
    data_len:数据长度
返回值：数值型，1为成功 0为失败
备注：无。
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
功能：获取/设置当前网络上提供网络时间服务器。可以是 IP 地址,也可以是域名。NTPServer 的作用是用来更新时间。
输入参数：
    NTPServer:字符串，不超过 255 字节
    NTPPort:数值型
返回值：数值型，1为成功 0为失败
备注：在调用 Network.save()后写 Flash
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
功能：同步 NTP 时间。 如果页面获取到消息 IP_network_NTP_READY表示网络 NTP 时间同步成功；
    页面获取到消息"10506：网络 NTP时间同步超时"
输入参数：无
返回值：数值型，1为成功 0为失败
备注：返回值只是表示程序是否开始执行 NTP 时间同步，并不表示实际的同步结果（实际的同步结果是由消息通知）。
    如返回 0，可能是因为没有设置NTPServer等
*/
INT32_T rocme_porting_network_ntp_update()
{
ROCME_TEST_PRINT

}

/*******************************************************************
功能：获取和设置网络对终端设备的一种识别字符串，即主机名
输入参数：
    hostName:字符串，不超过 255 字节，可读写
返回值：数值型，1为成功 0为失败
备注：在调用 Network.save()后写 Flash，在局域网中也可通过此名称识别此终端设备
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
功能：获取Ethernet对象个数。
输入参数：
    deviceNameArray：网卡名称数组；
    deviceNumber:ethernet个数
返回值：数值型，1为成功 0为失败
备注：无
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
功能：获取当前的连接类型，取值范围："ethernet"、"ppp"或"pppoe"
输入参数：
    currConnectionType:字符串，
返回值：数值型，1为成功 0为失败
备注：无
*/
INT32_T rocme_porting_network_get_connection_type(CHAR_T* deviceName, CHAR_T* currConnectionType)
{
ROCME_TEST_PRINT

}

/*******************************************************************
功能：保存网络设置,将网络信息写入 flash。
输入参数：无
返回值：数值型，1为成功 0为失败
备注：
    页面可通过获取 "10601：Flash写入成功"消息来得知写 flash完毕. 
*/
INT32_T rocme_porting_network_save()
{
ROCME_TEST_PRINT

}

/*******************************************************************
功能：实现普通电脑上 ping 的功能。通过消息 "10507：PING命令响应"进行响应，并可通过该消息值的 P2 值进行判断是否 ping成功。
输入参数：
    address：字符串，ping 的网络地址,IP 或者域名地址。 
    Parameter：字符串，ping的参数，目前可只实现"-t"选项,其他值按无参数。 -t：连续地 ping 一个地址，直到手动停止.
返回值：数值型，1为成功 0为失败
备注：每个包响应或超时都返回消息，但不发最后的统计消息。
*/
INT32_T rocme_porting_network_ping(CHAR_T* address, CHAR_T* parameter)
{
ROCME_TEST_PRINT

}

/*******************************************************************
功能：收到 IP_network_PING_RESPONSE 消息后获取 ping的响应字符串。
输入参数：
    pingResponseBuffer：字符串，用于获取ping的响应字符串 
    BuffLen：入参表示获取response分配内存长度，返回时表示实际长度；如果小于实际长度，webapp需要重新分配内存并获取该response。
返回值：数值型，1为成功 0为失败
备注：
    是否有响应根据消息 P2值判断. 
    如果需要其他信息需要从字符串中截取。 
    每一个响应消息发送后即可获取，下一次响应需要重新填充。
*/
INT32_T rocme_porting_network_get_ping_response(CHAR_T* pingResponseBuffer, UINT8_T* BuffLen)
{
ROCME_TEST_PRINT

}

/*******************************************************************
功能：取消正在进行的 ping 操作。
输入参数：无
返回值：数值型，1代表停止了正在执行的 ping 操作，0代表当前 ping 操作已经结束或当前无 ping操作.
备注：无
*/
INT32_T rocme_porting_network_cancel_ping()
{
ROCME_TEST_PRINT

}


/*******************************************************************
功能：获取设备状态
输入参数：
    deviceName：网卡名称；
    deviceState: 数值型，参考值如下:    
        0	设备不存在，不可访问
        1	设备存在，但无法获取状态
        101	网线连接
        102	网线脱落
        201	网络连接正常
        202	网络连接中断
        203	网络状态不改变，但是不良
        204	CableModem与STB通信中断
        205	CableModem与STB通信中断，重新上线
返回值：数值型，1为成功 0为失败
备注：无
*/
INT32_T rocme_porting_network_get_device_state(CHAR_T* deviceName, INT32_T* deviceState)
{
ROCME_TEST_PRINT

}


/*******************************************************************
功能：设置/获取网络中的代理服务器信息
输入参数：
    configInfo：请参考Roc_Proxy_Config_t具体定义。
返回值：数值型，1为成功 0为失败
备注：Network.save()后写Flash
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
功能：设置/获取当前网络终端设备的IP对象，包括IP地址、子网掩码、网关。
输入参数：
    configInfo：请参考Roc_Proxy_Config_t具体定义。
返回值：数值型，1为成功 0为失败
备注：Network.save()后写Flash
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
功能：获取网卡接收和发送包的信息
输入参数：
    deviceName：设备名称，如eth0
输出参数:
	pstNetPackage: 网卡发送和接收包的信息，详见Roc_Net_Package_Info_t定义
返回值：数值型，1为成功 0为失败
*/
INT32_T rocme_porting_network_get_packeages(CHAR_T* deviceName, Roc_Net_Package_Info_t *pstNetPackage)
{
ROCME_TEST_PRINT

}


/*******************************************************************
功能：设置/获取网卡的通信方式
输入参数：
    deviceName：设备名称，如eth0
    communicateWay: 网卡的通信方式，可以是如下值"adapting"、"10M_fullDuplex"、"10M_halfDuplex"、"100M_fullDuplex"、"100M_halfDuplex"
返回值：数值型，1为成功 0为失败
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
功能：设置/获取DHCP模式是否自动获取DNS
输入参数：
    deviceName: 网卡名称，如eth0
    bDHCP: 1表示自动获取DNS，0表示手动获取
返回值：数值型，1为成功 0为失败
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
功能：设置/获取DNS服务器信息
输入参数：
    deviceName：设备名称，如eth0
    nIndex: DNS服务器索引，最多可设置三个DNS服务器
    pDNSServer: DNS服务器地址
返回值：数值型，1为成功 0为失败
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
功能：
    设置/获取底层网络的 DHCP 工作方式，dhcp 为网络的 DHCP 工作方式，0: 表示不采用 DHCP，1: 表示采用 DHCP， 其他值无效，直接返回-1。
    
参数说明：
    输入参数：dhcp_mode 网络的 DHCP 工作方式代码
    输出参数：无
    
返    回：0 - 设置成功，-1 - 失败
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
功能说明：
    获取DHCP动态分配的DHCP相关信息
    
参数说明：
    输入参数：deviceName 网卡名称
    输出参数：dhcp的信息，详见Roc_DHCP_Info_t结构体
    
返    回：1表示成功，0表示失败

参考实现：
**********************************/
INT32_T rocme_porting_get_dhcp_Info(CHAR_T* deviceName, Roc_DHCP_Info_t *pdhcpIP)
{
ROCME_TEST_PRINT

}



/*******************************************************************
功能： 获取ethernet模式的连接状态
输入参数：
    deviceName：设备名称，如eth0
输出参数:
    pbStatus: 1表示已经连接上，0表示没有连接上
返回值：数值型，1为成功 0为失败
*/
INT32_T romce_porting_network_get_lan_status(const CHAR_T *pDeviceName, ROC_BOOL *pbStatus)
{
ROCME_TEST_PRINT

}


/*******************************************************************
功能： 设置/获取网卡是否禁用
输入参数：
    deviceName：设备名称，如eth0
输出参数:
    pbEthStatus: 1表示可用，0表示不可用
返回值：数值型，1为成功 0为失败
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
功能：将网卡设置的所有属性一次性设置给底层，所有属性包括 ethernet对象下的所有相关属性都可以进行设置。
    其功能类似 PC上网络设置的确认按钮的功能。
输入参数：
    deviceName：网卡名称；
返回值：数值型，1为成功 0为失败
备注：无
*/
INT32_T rocme_porting_network_submit_parameters(CHAR_T* deviceName)
{
ROCME_TEST_PRINT

}


/*******************************************************************
功能：获取所有的AP信息
输入参数：
    deviceName：网卡名称；
    apInfo: AP信息，使用json字符串表示。字符串格式为：
        [{essId: "ap1",signalStrength:"30%",linkQuality:"40%",encType:1 },
        { essId: "ap2",signalStrength:"10%",linkQuality:"20%",encType:1 },
        { essId: "ap3", signalStrength:"20%",linkQuality:"60%",encType:2 }]
返回值：数值型，1为成功 0为失败
备注：适用于无线网卡
encType	值	含义
    	0	设置无线网卡认证加密类型:无加密
    	1	设置无线网卡认证加密类型:WEPOpen加密
    	2	设置无线网卡认证加密类型:shared共享模式来加密WEP信息
    	3	设置无线网卡认证加密类型:Wi-Fi保护接入协议
    	4	设置无线网卡认证加密类型:Wi-Fi保护接入协议2
*/
INT32_T rocme_porting_network_get_APs(CHAR_T* deviceName, CHAR_T* apInfo)
{
ROCME_TEST_PRINT

}


/*******************************************************************
功能：连接AP
输入参数：
    deviceName：网卡名称；
    essId：字符串，传入essId，该值应该取searchAP的返回值中essId属性的值
    keyType：数值型，设置无线网卡密钥数据类型，keyType取值为下表中所描述的类型
    key：字符串，认证密钥
返回值：数值型，成功返回0，失败返回错误码。
备注：适用于无线网卡
    keyType	值	含义
            0	设置无线网卡密钥数据类型:16进制方式加密
        	1	设置无线网卡密钥数据类型:ansi编码方式加密
        	2	设置无线网卡密钥数据类型:string方式加密
*/
INT32_T rocme_porting_network_connect_AP(CHAR_T* deviceName, CHAR_T* essId, INT32_T keyType, CHAR_T* key)
{
ROCME_TEST_PRINT

}


/*******************************************************************
功能：断开与AP的连接
输入参数：
    deviceName：网卡名称；
返回值：数值型，成功返回0，失败返回错误码
备注：无
*/
INT32_T rocme_porting_network_disconnect_AP(CHAR_T* deviceName)
{
ROCME_TEST_PRINT

}


/*******************************************************************
功能：获取连接上的AP的信息
输入参数：
    deviceName：网卡名称；
    apInfo:成功返回AP信息，用json字符串表示，类型:
        {essId: "ap1",signalStrength:"30%",linkQuality:"40%",encType:1 }
        失败返回的AP信息中essId的值为空串
返回值：数值型，成功返回0，失败返回错误码
备注：适用于无线网卡
    WiFi错误码对照表如下：
    返回值（错误码）	值	含义	
                        0	成功
                    	1	参数错误
                    	2	无线网卡启动失败
                    	3	无线网卡关闭失败
                    	4	连接错误
                    	5	设置密钥错误
                    	6	清除认证信息错误
                    	7	未获取到AP名称
*/
INT32_T rocme_porting_network_get_connected_AP(CHAR_T* deviceName, CHAR_T* apInfo)
{
ROCME_TEST_PRINT

}




/**********************************
功能说明：
   获取网络描述信息
    
参数说明：
    输入参数：deviceName 设备名称
    输出参数：pDescription网络描述信息
    
返    回：1表示成功，0表示失败

参考实现：
**********************************/
INT32_T rocme_porting_network_get_description(CHAR_T *deviceName, CHAR_T *pDescription)
{
ROCME_TEST_PRINT

}



/**********************************
功能说明：
   恢复出厂设置MiddleWare 所有的网络资源和相关资源；
    
参数说明：
    输入参数：无
    输出参数：无
    
返    回：1表示成功，0表示失败

参考实现：
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

//#define NFS_DEBUG   //当测试使用nfs时打开此宏 add by lijing 2010.8.3


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

static long g_unDifferTime = 0;   //NTP同步前后的系统时间差

typedef struct t_Ping_Param
{
    CHAR_T address[256];
    CHAR_T parameter[8];
} Ping_Param;


/*Ethernet对象*/
typedef struct Roc_Ethernet_Config
{
    CHAR_T   deviceName[16];       //网卡设备名称
    CHAR_T   macAddr[32];          //物理网卡地址
    ROC_BOOL ethernetEnable;       //读取或设置网卡是否可用,数值型，1表示目前网卡可用，0表示网卡不可用
    ROC_BOOL dhcpEnable;           //获取和设置当前网络的是否启用DHCP工作方式,数值型，1表示使用DHCP，0表示静态IP模式
    ROC_BOOL lanStatus;            //获取ethernet模式的连接状态,1表示已连接上0表示没有连接上
    ROC_BOOL dhcpAutoGetDNS;       //读取或设置此ethernet在使用DHCP模式下是否自动获取DNSserver;1表示用动态获取的DNSserver，不用设置的DNSserver
    ROC_BOOL dhcpSuccess;
    //0表示不用动态获取的DNSserver，用设置的DNSserver;如果Ethernet.DHCPEnable=0;设置此属性无效
    CHAR_T   dhcpServer[16];       //返回当前网络上提供DHCP服务器IP地址,字符串，取值范围为1-255字节，只读
    INT16_T  dhcpPort;             //DHCP的端口号(注册的端口常见的有：53、161、162、67、68),数值型，只读,busybox用的68.
    CHAR_T   leaseObtained[32];    //获取在DHCP模式下租用IP地址开始时间,yyyy-mm-dd hh:mm:ss
    CHAR_T   leaseExpires[32];     //获取在DHCP模式下IP地址的过期时间,yyyy-mm-dd hh:mm:ss
    CHAR_T   description[256];     //获取当前本地连接所使用的网络设备的描述信息
    CHAR_T   communicateWay[16];   //设置或获取网络带宽及通信方式,一般可以是以下值："adapting"、"10M_fullDuplex"、
    //"10M_halfDuplex"、"100M_fullDuplex"、"100M_halfDuplex"
    UINT32_T sentPackages;         //获取网卡发送的数据包数量
    UINT32_T receivedPackages;     //获取网卡接收到的数据包数量
    Roc_IP_Config_t    dhcpIP;                     //获取DHCP动态分配的IP对象
    Roc_IP_Config_t    staticIP[3];                //获得网卡所设的IP对象数组,静态IP模式下数组元素最多限制为三个
    CHAR_T             dnsServers[3][16];          //获取和设置当前网络上提供DNS服务的服务器IP地址，DNSServers是一个数组，对当前网卡有效：
    //A、在DHCP模式下可选择自动获取DNSservers,若选择自动获取，则手动设置无效；
    //B、可选择手动设置DNSservers,若要使用手动设置的DNSServers那么必须取消掉自动获取DNSServer的设置；
    //C、非DHCP模式下只能手动设置DNSServers;
    //最多添加三个;设置后无需重新启动机顶盒即可生效; 每个元素的值为字符串，即IP地址
    Roc_Proxy_Config_t proxyArray[ROC_PROXY_NUM];  //Etherent所使用的代理对象,返回的是proxy对象
} Roc_Ethernet_Config_t;

#define NET_NAME_SIZE		16
#define	ETH_DEVICE_NUM		3
static char ROCME_ETH_NAME[3][NET_NAME_SIZE] =
{
	"eth0",
	"eth1",
	"rausb0",
};


static CHAR_T g_NTPServer[256];// = "133.100.11.8";    //保存ntp server
static CHAR_T g_hostName[256] = "localhost";     //保存hostname
static CHAR_T g_pingResponse[256]; //ping返回字符串记录，会不断覆盖前面的存储记录
static UINT32_T g_pingTaskHandle = 0;  //ping任务使用的句柄
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


//读取或设置此ethernet在使用DHCP模式下是否自动获取DNSserver;1表示用动态获取的DNSserver，
//不用设置的DNSserver;0表示不用动态获取的DNSserver，用设置的DNSserver;
//如果Ethernet.DHCPEnable=0;设置此属性无效
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
        //发送PING命令响应:10523
        //-1：超时，服务器无响应;
        //>=0：表示响应的时间，单位为ms
        stEvent.msgType = ROC_SYSEVENT_TYPE;
        stEvent.msg = ROC_SYSEVENT_PING_RESPONSE;

        memcpy(buffer, g_pingResponse, sizeof(buffer));
        printf("errRet:%d, %s\n", errRet, g_pingResponse);

        if(0 == errRet)
        {
            if(strstr(buffer, "time="))
            {
                //第一个=Recv 60bytes From 10.10.30.212: ttl
                token = strtok(buffer, delim);

                //第二个=64 tm
                token = strtok(NULL, delim);

                //第三个=具体的时间。比如：5.98 ms
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

        //需要提前设置全局量
        NetWorkSetEthByIndex(nIndex, &tmpCfg);


        if (tmpCfg.ethernetEnable)
        {
            rocme_porting_network_set_commute_way(pDeviceName, tmpCfg.communicateWay);

            //如果该网卡可用，并且dhcp确认开启，则直接调用dhcp初始化。
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
功能：获取/设置当前网络上提供网络时间服务器。可以是 IP 地址,也可以是域名。NTPServer 的作用是用来更新时间。
输入参数：
    NTPServer:字符串，不超过 255 字节，可读写
返回值：数值型，1为成功 0为失败
备注：在调用 Network.save()后写 Flash
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
功能：同步 NTP 时间。 如果页面获取到消息 IP_network_NTP_READY表示网络 NTP 时间同步成功；
    页面获取到消息"10506：网络 NTP时间同步超时"
输入参数：无
返回值：数值型，1为成功 0为失败
备注：返回值只是表示程序是否开始执行 NTP 时间同步，并不表示实际的同步结果（实际的同步结果是由消息通知）。
    如返回 0，可能是因为没有设置NTPServer等
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
        //不再使用默认ntp地址.
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

        //只记录一次差异时间

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

        //10521	网络NTP时间同步成功。
        stEvent.msgType = ROC_SYSEVENT_TYPE;
        stEvent.msg = ROC_SYSEVENT_NTPTIME_SYNC_SUCC;
        stEvent.modifiers[0] = 0;
        //memcpy(stEvent.modifiers, ntpTime, strlen(ntpTime)+1);
        network_event_cbk(0, &stEvent, sizeof(stEvent));

        return 1;
    }

ERR_EXIT:
    {
        //10522 网络 NTP时间同步超时。
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

    //避免从dhcp设置为静态IP时，丢失静态IP的问题。
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
        //发送flash写入成功的消息
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

    //如果ping任务没有停止，强制杀死该任务.
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
功能：获取和设置网络对终端设备的一种识别字符串，即主机名
输入参数：
    hostName:字符串，不超过 255 字节，可读写
返回值：数值型，1为成功 0为失败
备注：在调用 Network.save()后写 Flash，在局域网中也可通过此名称识别此终端设备
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

        //直接设置hostname到内核中
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

    //只考虑设置一个网关名称
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
        //只考虑设置一个网关名称
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




//linux中记录网卡数据的格式为  eth0:14285698   70072    0    0    0     0          0         0 15983632   59101    0    0    0     0       0          0
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

            //第10个字段为发送数据包的数值
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
功能：读取或设置网卡是否可用(即PC上的启用或禁用功能)
输入参数：
    enable:数值型，1表示目前网卡可用，0表示网卡不可用，可读写
返回值：数值型，1为成功 0为失败
备注：在调用 Network.save()后写 Flash
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
功能：设置DHCP模式是否自动获取DNS
输入参数：
    bDHCP: 1表示自动获取DNS，0表示手动获取
返回值：数值型，1为成功 0为失败
备注：需要调用
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
功能：获取DHCP模式是否自动获取DNS
输出参数
    bDHCP: 1表示自动获取DNS，0表示手动获取
返回值：数值型，1为成功 0为失败
备注：需要调用
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
            obtained_time = mktime(tmp_tm);   // 以前写入文件的时间

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
        //10508 网络 DHCP成功。
        stEvent.msg = 10508;
        bDHCPSuccess = ROC_TRUE;
        GetDHCPInfo(param, &g_stDHCPInfo[nIndex]);
    }
    else
    {
        //10509 网络 DHCP同步超时。
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

    //避免DNS为手动状态，但dhcp请求后被设置为0的问题。
    rocme_porting_network_set_dnsserver(param, 0, stEthCfg.dnsServers[0]);
    rocme_porting_network_set_dnsserver(param, 1, stEthCfg.dnsServers[1]);
    rocme_porting_network_set_dnsserver(param, 2, stEthCfg.dnsServers[2]);
}



/**********************************
功能说明：
    设置底层网络的 DHCP 工作方式，dhcp 为网络的 DHCP 工作方式，0: 表示不采用 DHCP，1: 表示采用 DHCP， 其他值无效，直接返回-1。

参数说明：
    输入参数：网络的 DHCP 工作方式代码
    输出参数：无

返    回：0 - 设置成功，-1 - 失败

参考实现：见rocme_product_demo.c
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
        system("udhcpc -q -t 1  -n > /mnt/dhcp_print.conf");  /*busybox 中的系统命令*/
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

        //10509 网络 DHCP同步超时。
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
功能说明：
    获取当前网络的 DHCP 工作方式代码，0: 表示不采用 DHCP，1: 表示采用 DHCP。

参数说明：
    输入参数：无
    输出参数：dhcp_mode 是否启用DHCP

返    回：1表示成功，0表示失败

参考实现：见rocme_product_demo.c
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

    //如果当前时间与文件时间比较接近，则认为文件时间可靠不需要转换
    //否则，需要转换为当前时间

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
功能说明：
    获取DHCP动态分配的DHCP相关信息

参数说明：
    输入参数：无
    输出参数：dhcp的信息，详见Roc_DHCP_Info_t结构体

返    回：1表示成功，0表示失败

参考实现：
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
    	//重新设置IP信息
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
设备（device）	返回值	含义
所有设备均适合
    0	设备不存在，不可访问
	1	设备存在，但无法获取状态

eth0, eth1等网卡设备

    101	网线连接
	102	网线脱落

cm
    201	网络连接正常
	202	网络连接中断
	203	网络状态不改变，但是不良
	204	CableModem与STB通信中断
	205	CableModem与STB通信中断，重新上线
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

    //获取网卡名称
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

    //rocme_get_ethernet_status返回-1时，获取网卡状态失败。
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
功能：将网卡设置的所有属性一次性设置给底层，所有属性包括 ethernet对象下的所有相关属性都可以进行设置。其功能类似 PC上网络设置的确认按钮的功能。
输入参数：无
返回值：数值型，1为成功 0为失败
备注：无
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

    //如果该网卡可用，并且dhcp确认开启，则直接调用dhcp初始化。
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
功能：将网卡的所有属性恢复为默认值
输入参数：无
返回值：数值型，1为成功 0为失败
备注：无
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

