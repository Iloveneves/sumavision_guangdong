/*******************************************************************************
File name   : rocme_porting_network.h

Author		: XXX			

Description : .
	          
Copyright (C) BeiJing SUMAVision, Inc., 2011 .All rights reserved.

History		:
				2011.01.12		Created 						
*******************************************************************************/
#ifndef __ROCME_PORTING_WORK_H_
#define __ROCME_PORTING_WORK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rocme_porting_typedef.h"
#include "rocme_porting_product.h"



/*网络带宽及通信方式*/
#define ROC_SPEED_10    10
#define ROC_SPEED_100   100
#define ROC_SPEED_1000  1000
#define ROC_HALF_DUPLEX 0
#define ROC_FULL_DUPLEX 1

#define    ROC_SYSEVENT_TYPE                                   1001
#define    ROC_SYSEVENT_NETWORK_CONNECTED                      10501     // 网线已插上
#define    ROC_SYSEVENT_NETWORK_DISCONNECTED                   10502     // 网线已断开
#define    ROC_SYSEVENT_LAN_NETWORK_CONNECTED                  10503     // LAN模式网络已连接.
#define    ROC_SYSEVENT_LAN_NETWORK_DISCONNECTED               10504     // LAN模式网络已断开.
                                                                         /* 预留 10505-10520 给LAN模式相关消息使用 */

#define    ROC_SYSEVENT_NTPTIME_SYNC_SUCC                      10521     // 网络NTP时间同步成功.
#define    ROC_SYSEVENT_NTPTIME_SYNC_TIMEOUT                   10522     // 网络 NTP时间同步超时.
#define    ROC_SYSEVENT_PING_RESPONSE                          10523     // PING命令响应.
                                                                         // #modifiers 取值:-1：超时,服务器无响应;>=0：表示响应的时间,单位为ms.
                                                                         /* 预留 10524-10530 给其他网络相关消息使用 */
#define    ROC_SYSEVENT_WRITE_FLASH_SUCC                       10601     // Flash写入成功
                                                                         /* 预留 10602-10700 给其它硬件相关消息使用 */


/*proxy模式*/
typedef enum Roc_Proxy_Mode
{
    ROC_PROXY_HTTP     = 0x00,   /*使用http proxy*/
    ROC_PROXY_HTTPS    = 0x01,   /*使用https proxy*/
    ROC_PROXY_FTP      = 0x02,   /*使用ftp proxy*/
    ROC_PROXY_NUM      = 0x03    /*使用ftp proxy*/
}Roc_Proxy_Mode_e;

//发送消息给webapp,type=1001为系统消息，type=1002为键盘，type=1003为鼠标，type=1004为通用遥控器，type=1005为 老人型遥控器，type=1006为儿童型遥控器，type值大于1006预留给扩展外设使用。
typedef struct SysNetworkEvent
{
	INT32_T msgType;
	INT32_T msg;
	CHAR_T  modifiers[32];
}SysNetworkEvent_t;

#define MAX_IP_PER_INTERFACE 3

typedef struct Roc_IP_Config
{
    INT32_T index;
    CHAR_T deviceName[16];
    CHAR_T ipAddress[16];
    CHAR_T mask[16];
    CHAR_T gateway[16];
}Roc_IP_Config_t;


typedef struct Roc_DHCPLeaseTime
{
    CHAR_T   leaseObtained[32];    //获取在DHCP模式下租用IP地址开始时间,yyyy-mm-dd hh:mm:ss
    CHAR_T   leaseExpires[32];     //获取在DHCP模式下IP地址的过期时间,yyyy-mm-dd hh:mm:ss
}Roc_DHCPLeaseTime_t;


typedef struct Roc_DHCP_Info
{
    CHAR_T ipAddress[16];
    CHAR_T mask[16];
    CHAR_T gateway[16];
    CHAR_T   dhcpServer[16];    
    INT16_T  dhcpPort;  
    Roc_DHCPLeaseTime_t stLeaseTime;
}Roc_DHCP_Info_t;


typedef struct Roc_Net_Package_Info
{
    UINT32_T sentPackages;         //获取网卡发送的数据包数量
    UINT32_T receivedPackages;     //获取网卡接收到的数据包数量
}Roc_Net_Package_Info_t;


/* proxy 服务器接入方式信息 */
typedef struct Roc_Proxy_Config
{
    CHAR_T           deviceName[16];
    UINT8_T          proxyEnable;                //是否启用代理,数值型，取值如下：1表示当前代理立即生效，0表示当前代理无效，可读写
    Roc_Proxy_Mode_e proxyMode;                  //proxy类型
    CHAR_T           usrName[32];                //当前 proxy 服务器接入方式的用户名,取值为：0-30个字符，不可以是空格
    CHAR_T           password[32];               //当前 proxy 服务器接入方式的密码,取值为：0-30个字符，可以是空格
    CHAR_T           server[256];                //http代理服务器的 IP地址或者域名地址,不能超过 255 字节
    CHAR_T           unusedProxyURLs[5][256];    //设置不使用代理的 URLs,不能超过 255 字节
    INT32_T          port;                       //http代理服务的服务器端口号,取值为：0-5 个数字字符
}Roc_Proxy_Config_t;





/*******************************************************************
功能：网络模块使用的回调函数，将消息发送给webapp。
输入参数：
    type:获取消息的来源，type=1001为系统消息，type=1002为键盘，type=1003为鼠标，type=1004为通用遥控器，
        type=1005为 老人型遥控器，type=1006为儿童型遥控器，type值大于1006预留给扩展外设使用
    data:void*类型，根据具体消息类型，应该封装为该消息的数据结构。
    data_len:数据长度
返回值：数值型，1为成功 0为失败
备注：无。
*/
INT32_T network_event_cbk(INT32_T type, void *data, INT32_T data_len);


/*******************************************************************
功能：获取/设置当前网络上提供网络时间服务器。可以是 IP 地址,也可以是域名。NTPServer 的作用是用来更新时间。
输入参数：
    NTPServer:字符串，不超过 255 字节
    NTPPort:数值型
返回值：数值型，1为成功 0为失败
备注：在调用 Network.save()后写 Flash
*/
INT32_T rocme_porting_network_set_ntp_server(CHAR_T* NTPServer);
INT32_T rocme_porting_network_get_ntp_server(CHAR_T* NTPServer, UINT8_T* BuffLen);

/*******************************************************************
功能：同步 NTP 时间。 如果页面获取到消息 IP_network_NTP_READY表示网络 NTP 时间同步成功；
    页面获取到消息"10506：网络 NTP时间同步超时"
输入参数：无
返回值：数值型，1为成功 0为失败
备注：返回值只是表示程序是否开始执行 NTP 时间同步，并不表示实际的同步结果（实际的同步结果是由消息通知）。
    如返回 0，可能是因为没有设置NTPServer等
*/
INT32_T rocme_porting_network_ntp_update();

/*******************************************************************
功能：获取和设置网络对终端设备的一种识别字符串，即主机名
输入参数：
    hostName:字符串，不超过 255 字节，可读写
返回值：数值型，1为成功 0为失败
备注：在调用 Network.save()后写 Flash，在局域网中也可通过此名称识别此终端设备
*/
INT32_T rocme_porting_network_set_host(CHAR_T* hostName);
INT32_T rocme_porting_network_get_host(CHAR_T* hostName, UINT8_T* BuffLen);

/*******************************************************************
功能：获取Ethernet对象个数。
输入参数：
    deviceNameArray：网卡名称数组；
    deviceNumber:ethernet个数
返回值：数值型，1为成功 0为失败
备注：无
*/
INT32_T rocme_porting_network_get_ethernets_num(CHAR_T deviceNameArray[][16], CHAR_T* deviceNumber);




/*******************************************************************
功能：获取当前的连接类型，取值范围："ethernet"、"ppp"或"pppoe"
输入参数：
    currConnectionType:字符串，
返回值：数值型，1为成功 0为失败
备注：无
*/
INT32_T rocme_porting_network_get_connection_type(CHAR_T* deviceName, CHAR_T* currConnectionType);

/*******************************************************************
功能：保存网络设置,将网络信息写入 flash。
输入参数：无
返回值：数值型，1为成功 0为失败
备注：
    页面可通过获取 "10601：Flash写入成功"消息来得知写 flash完毕. 
*/
INT32_T rocme_porting_network_save();

/*******************************************************************
功能：实现普通电脑上 ping 的功能。通过消息 "10507：PING命令响应"进行响应，并可通过该消息值的 P2 值进行判断是否 ping成功。
输入参数：
    address：字符串，ping 的网络地址,IP 或者域名地址。 
    Parameter：字符串，ping的参数，目前可只实现"-t"选项,其他值按无参数。 -t：连续地 ping 一个地址，直到手动停止.
返回值：数值型，1为成功 0为失败
备注：每个包响应或超时都返回消息，但不发最后的统计消息。
*/
INT32_T rocme_porting_network_ping(CHAR_T* address, CHAR_T* parameter);

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
INT32_T rocme_porting_network_get_ping_response(CHAR_T* pingResponseBuffer, UINT8_T* BuffLen);

/*******************************************************************
功能：取消正在进行的 ping 操作。
输入参数：无
返回值：数值型，1代表停止了正在执行的 ping 操作，0代表当前 ping 操作已经结束或当前无 ping操作.
备注：无
*/
INT32_T rocme_porting_network_cancel_ping();


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
INT32_T rocme_porting_network_get_device_state(CHAR_T* deviceName, INT32_T* deviceState);


/*******************************************************************
功能：设置/获取网络中的代理服务器信息
输入参数：
    configInfo：请参考Roc_Proxy_Config_t具体定义。
返回值：数值型，1为成功 0为失败
备注：Network.save()后写Flash
*/
INT32_T rocme_porting_network_get_proxy(CHAR_T* deviceName, Roc_Proxy_Mode_e proxyMode, Roc_Proxy_Config_t* configInfo);
INT32_T rocme_porting_network_set_proxy(CHAR_T* deviceName, Roc_Proxy_Mode_e proxyMode, Roc_Proxy_Config_t* configInfo);

/*******************************************************************
功能：设置/获取当前网络终端设备的IP对象，包括IP地址、子网掩码、网关。
输入参数：
    configInfo：请参考Roc_Proxy_Config_t具体定义。
返回值：数值型，1为成功 0为失败
备注：Network.save()后写Flash
*/
INT32_T rocme_porting_network_get_IP(CHAR_T* deviceName, Roc_IP_Config_t* IPInfo);
INT32_T rocme_porting_network_set_IP(CHAR_T* deviceName, Roc_IP_Config_t* IPInfo);



/*******************************************************************
功能：获取网卡接收和发送包的信息
输入参数：
    deviceName：设备名称，如eth0
输出参数:
	pstNetPackage: 网卡发送和接收包的信息，详见Roc_Net_Package_Info_t定义
返回值：数值型，1为成功 0为失败
*/
INT32_T rocme_porting_network_get_packeages(CHAR_T* deviceName, Roc_Net_Package_Info_t *pstNetPackage);


/*******************************************************************
功能：设置/获取网卡的通信方式
输入参数：
    deviceName：设备名称，如eth0
    communicateWay: 网卡的通信方式，可以是如下值"adapting"、"10M_fullDuplex"、"10M_halfDuplex"、"100M_fullDuplex"、"100M_halfDuplex"
返回值：数值型，1为成功 0为失败
*/
INT32_T rocme_porting_network_set_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay);
INT32_T rocme_porting_network_get_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay);


/*******************************************************************
功能：设置/获取DHCP模式是否自动获取DNS
输入参数：
    deviceName: 网卡名称，如eth0
    bDHCP: 1表示自动获取DNS，0表示手动获取
返回值：数值型，1为成功 0为失败
*/
INT32_T rocme_porting_set_dns_auto(CHAR_T* deviceName, ROC_BOOL bAutoGetDns);
INT32_T rocme_porting_get_dns_auto(CHAR_T* deviceName, ROC_BOOL *pbAutoGetDns);


/*******************************************************************
功能：设置/获取DNS服务器信息
输入参数：
    deviceName：设备名称，如eth0
    nIndex: DNS服务器索引，最多可设置三个DNS服务器
    pDNSServer: DNS服务器地址
返回值：数值型，1为成功 0为失败
*/
INT32_T rocme_porting_network_set_dnsserver(CHAR_T* deviceName, int nIndex, CHAR_T *pDNSServer);
INT32_T rocme_porting_network_get_dnsserver(CHAR_T* deviceName, int nIndex, CHAR_T *pDNSServer);




/**********************************************************************************
功能：
    设置/获取底层网络的 DHCP 工作方式，dhcp 为网络的 DHCP 工作方式，0: 表示不采用 DHCP，1: 表示采用 DHCP， 其他值无效，直接返回-1。
    
参数说明：
    输入参数：dhcp_mode 网络的 DHCP 工作方式代码
    输出参数：无
    
返    回：0 - 设置成功，-1 - 失败
*/
INT32_T rocme_porting_network_set_dhcp(const CHAR_T *pDeviceName, const Roc_DHCP_Mode_e dhcp_mode);
INT32_T rocme_porting_network_get_dhcp_status(CHAR_T *pDeviceName, Roc_DHCP_Mode_e *dhcp_mode);



/**********************************
功能说明：
    获取DHCP动态分配的DHCP相关信息
    
参数说明：
    输入参数：deviceName 网卡名称
    输出参数：dhcp的信息，详见Roc_DHCP_Info_t结构体
    
返    回：1表示成功，0表示失败

参考实现：
**********************************/
INT32_T rocme_porting_get_dhcp_Info(CHAR_T* deviceName, Roc_DHCP_Info_t *pdhcpIP);



/*******************************************************************
功能： 获取ethernet模式的连接状态
输入参数：
    deviceName：设备名称，如eth0
输出参数:
    pbStatus: 1表示已经连接上，0表示没有连接上
返回值：数值型，1为成功 0为失败
*/
INT32_T romce_porting_network_get_lan_status(const CHAR_T *pDeviceName, ROC_BOOL *pbStatus);


/*******************************************************************
功能： 设置/获取网卡是否禁用
输入参数：
    deviceName：设备名称，如eth0
输出参数:
    pbEthStatus: 1表示可用，0表示不可用
返回值：数值型，1为成功 0为失败
*/
INT32_T rocme_porting_network_set_eth_status(const CHAR_T *pDeviceName, ROC_BOOL bEthStatus);
INT32_T rocme_porting_network_get_eth_status(const CHAR_T *pDeviceName, ROC_BOOL *pbEthStatus);


/*******************************************************************
功能：将网卡设置的所有属性一次性设置给底层，所有属性包括 ethernet对象下的所有相关属性都可以进行设置。
    其功能类似 PC上网络设置的确认按钮的功能。
输入参数：
    deviceName：网卡名称；
返回值：数值型，1为成功 0为失败
备注：无
*/
INT32_T rocme_porting_network_submit_parameters(CHAR_T* deviceName);


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
INT32_T rocme_porting_network_get_APs(CHAR_T* deviceName, CHAR_T* apInfo);


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
INT32_T rocme_porting_network_connect_AP(CHAR_T* deviceName, CHAR_T* essId, INT32_T keyType, CHAR_T* key);


/*******************************************************************
功能：断开与AP的连接
输入参数：
    deviceName：网卡名称；
返回值：数值型，成功返回0，失败返回错误码
备注：无
*/
INT32_T rocme_porting_network_disconnect_AP(CHAR_T* deviceName);


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
INT32_T rocme_porting_network_get_connected_AP(CHAR_T* deviceName, CHAR_T* apInfo);




/**********************************
功能说明：
   获取网络描述信息
    
参数说明：
    输入参数：deviceName 设备名称
    输出参数：pDescription网络描述信息
    
返    回：1表示成功，0表示失败

参考实现：
**********************************/
INT32_T rocme_porting_network_get_description(CHAR_T *deviceName, CHAR_T *pDescription);



/**********************************
功能说明：
   恢复出厂设置MiddleWare 所有的网络资源和相关资源；
    
参数说明：
    输入参数：无
    输出参数：无
    
返    回：1表示成功，0表示失败

参考实现：
**********************************/
INT32_T rocme_porting_network_restore(void);

#ifdef __cplusplus
}
#endif

#endif

