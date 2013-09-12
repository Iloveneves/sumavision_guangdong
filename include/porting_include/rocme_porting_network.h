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



/*�������ͨ�ŷ�ʽ*/
#define ROC_SPEED_10    10
#define ROC_SPEED_100   100
#define ROC_SPEED_1000  1000
#define ROC_HALF_DUPLEX 0
#define ROC_FULL_DUPLEX 1

#define    ROC_SYSEVENT_TYPE                                   1001
#define    ROC_SYSEVENT_NETWORK_CONNECTED                      10501     // �����Ѳ���
#define    ROC_SYSEVENT_NETWORK_DISCONNECTED                   10502     // �����ѶϿ�
#define    ROC_SYSEVENT_LAN_NETWORK_CONNECTED                  10503     // LANģʽ����������.
#define    ROC_SYSEVENT_LAN_NETWORK_DISCONNECTED               10504     // LANģʽ�����ѶϿ�.
                                                                         /* Ԥ�� 10505-10520 ��LANģʽ�����Ϣʹ�� */

#define    ROC_SYSEVENT_NTPTIME_SYNC_SUCC                      10521     // ����NTPʱ��ͬ���ɹ�.
#define    ROC_SYSEVENT_NTPTIME_SYNC_TIMEOUT                   10522     // ���� NTPʱ��ͬ����ʱ.
#define    ROC_SYSEVENT_PING_RESPONSE                          10523     // PING������Ӧ.
                                                                         // #modifiers ȡֵ:-1����ʱ,����������Ӧ;>=0����ʾ��Ӧ��ʱ��,��λΪms.
                                                                         /* Ԥ�� 10524-10530 ���������������Ϣʹ�� */
#define    ROC_SYSEVENT_WRITE_FLASH_SUCC                       10601     // Flashд��ɹ�
                                                                         /* Ԥ�� 10602-10700 ������Ӳ�������Ϣʹ�� */


/*proxyģʽ*/
typedef enum Roc_Proxy_Mode
{
    ROC_PROXY_HTTP     = 0x00,   /*ʹ��http proxy*/
    ROC_PROXY_HTTPS    = 0x01,   /*ʹ��https proxy*/
    ROC_PROXY_FTP      = 0x02,   /*ʹ��ftp proxy*/
    ROC_PROXY_NUM      = 0x03    /*ʹ��ftp proxy*/
}Roc_Proxy_Mode_e;

//������Ϣ��webapp,type=1001Ϊϵͳ��Ϣ��type=1002Ϊ���̣�type=1003Ϊ��꣬type=1004Ϊͨ��ң������type=1005Ϊ ������ң������type=1006Ϊ��ͯ��ң������typeֵ����1006Ԥ������չ����ʹ�á�
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
    CHAR_T   leaseObtained[32];    //��ȡ��DHCPģʽ������IP��ַ��ʼʱ��,yyyy-mm-dd hh:mm:ss
    CHAR_T   leaseExpires[32];     //��ȡ��DHCPģʽ��IP��ַ�Ĺ���ʱ��,yyyy-mm-dd hh:mm:ss
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
    UINT32_T sentPackages;         //��ȡ�������͵����ݰ�����
    UINT32_T receivedPackages;     //��ȡ�������յ������ݰ�����
}Roc_Net_Package_Info_t;


/* proxy ���������뷽ʽ��Ϣ */
typedef struct Roc_Proxy_Config
{
    CHAR_T           deviceName[16];
    UINT8_T          proxyEnable;                //�Ƿ����ô���,��ֵ�ͣ�ȡֵ���£�1��ʾ��ǰ����������Ч��0��ʾ��ǰ������Ч���ɶ�д
    Roc_Proxy_Mode_e proxyMode;                  //proxy����
    CHAR_T           usrName[32];                //��ǰ proxy ���������뷽ʽ���û���,ȡֵΪ��0-30���ַ����������ǿո�
    CHAR_T           password[32];               //��ǰ proxy ���������뷽ʽ������,ȡֵΪ��0-30���ַ��������ǿո�
    CHAR_T           server[256];                //http����������� IP��ַ����������ַ,���ܳ��� 255 �ֽ�
    CHAR_T           unusedProxyURLs[5][256];    //���ò�ʹ�ô���� URLs,���ܳ��� 255 �ֽ�
    INT32_T          port;                       //http�������ķ������˿ں�,ȡֵΪ��0-5 �������ַ�
}Roc_Proxy_Config_t;





/*******************************************************************
���ܣ�����ģ��ʹ�õĻص�����������Ϣ���͸�webapp��
���������
    type:��ȡ��Ϣ����Դ��type=1001Ϊϵͳ��Ϣ��type=1002Ϊ���̣�type=1003Ϊ��꣬type=1004Ϊͨ��ң������
        type=1005Ϊ ������ң������type=1006Ϊ��ͯ��ң������typeֵ����1006Ԥ������չ����ʹ��
    data:void*���ͣ����ݾ�����Ϣ���ͣ�Ӧ�÷�װΪ����Ϣ�����ݽṹ��
    data_len:���ݳ���
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ޡ�
*/
INT32_T network_event_cbk(INT32_T type, void *data, INT32_T data_len);


/*******************************************************************
���ܣ���ȡ/���õ�ǰ�������ṩ����ʱ��������������� IP ��ַ,Ҳ������������NTPServer ����������������ʱ�䡣
���������
    NTPServer:�ַ����������� 255 �ֽ�
    NTPPort:��ֵ��
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ڵ��� Network.save()��д Flash
*/
INT32_T rocme_porting_network_set_ntp_server(CHAR_T* NTPServer);
INT32_T rocme_porting_network_get_ntp_server(CHAR_T* NTPServer, UINT8_T* BuffLen);

/*******************************************************************
���ܣ�ͬ�� NTP ʱ�䡣 ���ҳ���ȡ����Ϣ IP_network_NTP_READY��ʾ���� NTP ʱ��ͬ���ɹ���
    ҳ���ȡ����Ϣ"10506������ NTPʱ��ͬ����ʱ"
�����������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע������ֵֻ�Ǳ�ʾ�����Ƿ�ʼִ�� NTP ʱ��ͬ����������ʾʵ�ʵ�ͬ�������ʵ�ʵ�ͬ�����������Ϣ֪ͨ����
    �緵�� 0����������Ϊû������NTPServer��
*/
INT32_T rocme_porting_network_ntp_update();

/*******************************************************************
���ܣ���ȡ������������ն��豸��һ��ʶ���ַ�������������
���������
    hostName:�ַ����������� 255 �ֽڣ��ɶ�д
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע���ڵ��� Network.save()��д Flash���ھ�������Ҳ��ͨ��������ʶ����ն��豸
*/
INT32_T rocme_porting_network_set_host(CHAR_T* hostName);
INT32_T rocme_porting_network_get_host(CHAR_T* hostName, UINT8_T* BuffLen);

/*******************************************************************
���ܣ���ȡEthernet���������
���������
    deviceNameArray�������������飻
    deviceNumber:ethernet����
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_get_ethernets_num(CHAR_T deviceNameArray[][16], CHAR_T* deviceNumber);




/*******************************************************************
���ܣ���ȡ��ǰ���������ͣ�ȡֵ��Χ��"ethernet"��"ppp"��"pppoe"
���������
    currConnectionType:�ַ�����
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_get_connection_type(CHAR_T* deviceName, CHAR_T* currConnectionType);

/*******************************************************************
���ܣ�������������,��������Ϣд�� flash��
�����������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��
    ҳ���ͨ����ȡ "10601��Flashд��ɹ�"��Ϣ����֪д flash���. 
*/
INT32_T rocme_porting_network_save();

/*******************************************************************
���ܣ�ʵ����ͨ������ ping �Ĺ��ܡ�ͨ����Ϣ "10507��PING������Ӧ"������Ӧ������ͨ������Ϣֵ�� P2 ֵ�����ж��Ƿ� ping�ɹ���
���������
    address���ַ�����ping �������ַ,IP ����������ַ�� 
    Parameter���ַ�����ping�Ĳ�����Ŀǰ��ֻʵ��"-t"ѡ��,����ֵ���޲����� -t�������� ping һ����ַ��ֱ���ֶ�ֹͣ.
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��ÿ������Ӧ��ʱ��������Ϣ������������ͳ����Ϣ��
*/
INT32_T rocme_porting_network_ping(CHAR_T* address, CHAR_T* parameter);

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
INT32_T rocme_porting_network_get_ping_response(CHAR_T* pingResponseBuffer, UINT8_T* BuffLen);

/*******************************************************************
���ܣ�ȡ�����ڽ��е� ping ������
�����������
����ֵ����ֵ�ͣ�1����ֹͣ������ִ�е� ping ������0����ǰ ping �����Ѿ�������ǰ�� ping����.
��ע����
*/
INT32_T rocme_porting_network_cancel_ping();


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
INT32_T rocme_porting_network_get_device_state(CHAR_T* deviceName, INT32_T* deviceState);


/*******************************************************************
���ܣ�����/��ȡ�����еĴ����������Ϣ
���������
    configInfo����ο�Roc_Proxy_Config_t���嶨�塣
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��Network.save()��дFlash
*/
INT32_T rocme_porting_network_get_proxy(CHAR_T* deviceName, Roc_Proxy_Mode_e proxyMode, Roc_Proxy_Config_t* configInfo);
INT32_T rocme_porting_network_set_proxy(CHAR_T* deviceName, Roc_Proxy_Mode_e proxyMode, Roc_Proxy_Config_t* configInfo);

/*******************************************************************
���ܣ�����/��ȡ��ǰ�����ն��豸��IP���󣬰���IP��ַ���������롢���ء�
���������
    configInfo����ο�Roc_Proxy_Config_t���嶨�塣
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע��Network.save()��дFlash
*/
INT32_T rocme_porting_network_get_IP(CHAR_T* deviceName, Roc_IP_Config_t* IPInfo);
INT32_T rocme_porting_network_set_IP(CHAR_T* deviceName, Roc_IP_Config_t* IPInfo);



/*******************************************************************
���ܣ���ȡ�������պͷ��Ͱ�����Ϣ
���������
    deviceName���豸���ƣ���eth0
�������:
	pstNetPackage: �������ͺͽ��հ�����Ϣ�����Roc_Net_Package_Info_t����
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T rocme_porting_network_get_packeages(CHAR_T* deviceName, Roc_Net_Package_Info_t *pstNetPackage);


/*******************************************************************
���ܣ�����/��ȡ������ͨ�ŷ�ʽ
���������
    deviceName���豸���ƣ���eth0
    communicateWay: ������ͨ�ŷ�ʽ������������ֵ"adapting"��"10M_fullDuplex"��"10M_halfDuplex"��"100M_fullDuplex"��"100M_halfDuplex"
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T rocme_porting_network_set_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay);
INT32_T rocme_porting_network_get_commute_way(CHAR_T* deviceName, CHAR_T* communicateWay);


/*******************************************************************
���ܣ�����/��ȡDHCPģʽ�Ƿ��Զ���ȡDNS
���������
    deviceName: �������ƣ���eth0
    bDHCP: 1��ʾ�Զ���ȡDNS��0��ʾ�ֶ���ȡ
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T rocme_porting_set_dns_auto(CHAR_T* deviceName, ROC_BOOL bAutoGetDns);
INT32_T rocme_porting_get_dns_auto(CHAR_T* deviceName, ROC_BOOL *pbAutoGetDns);


/*******************************************************************
���ܣ�����/��ȡDNS��������Ϣ
���������
    deviceName���豸���ƣ���eth0
    nIndex: DNS������������������������DNS������
    pDNSServer: DNS��������ַ
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T rocme_porting_network_set_dnsserver(CHAR_T* deviceName, int nIndex, CHAR_T *pDNSServer);
INT32_T rocme_porting_network_get_dnsserver(CHAR_T* deviceName, int nIndex, CHAR_T *pDNSServer);




/**********************************************************************************
���ܣ�
    ����/��ȡ�ײ������ DHCP ������ʽ��dhcp Ϊ����� DHCP ������ʽ��0: ��ʾ������ DHCP��1: ��ʾ���� DHCP�� ����ֵ��Ч��ֱ�ӷ���-1��
    
����˵����
    ���������dhcp_mode ����� DHCP ������ʽ����
    �����������
    
��    �أ�0 - ���óɹ���-1 - ʧ��
*/
INT32_T rocme_porting_network_set_dhcp(const CHAR_T *pDeviceName, const Roc_DHCP_Mode_e dhcp_mode);
INT32_T rocme_porting_network_get_dhcp_status(CHAR_T *pDeviceName, Roc_DHCP_Mode_e *dhcp_mode);



/**********************************
����˵����
    ��ȡDHCP��̬�����DHCP�����Ϣ
    
����˵����
    ���������deviceName ��������
    ���������dhcp����Ϣ�����Roc_DHCP_Info_t�ṹ��
    
��    �أ�1��ʾ�ɹ���0��ʾʧ��

�ο�ʵ�֣�
**********************************/
INT32_T rocme_porting_get_dhcp_Info(CHAR_T* deviceName, Roc_DHCP_Info_t *pdhcpIP);



/*******************************************************************
���ܣ� ��ȡethernetģʽ������״̬
���������
    deviceName���豸���ƣ���eth0
�������:
    pbStatus: 1��ʾ�Ѿ������ϣ�0��ʾû��������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T romce_porting_network_get_lan_status(const CHAR_T *pDeviceName, ROC_BOOL *pbStatus);


/*******************************************************************
���ܣ� ����/��ȡ�����Ƿ����
���������
    deviceName���豸���ƣ���eth0
�������:
    pbEthStatus: 1��ʾ���ã�0��ʾ������
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
*/
INT32_T rocme_porting_network_set_eth_status(const CHAR_T *pDeviceName, ROC_BOOL bEthStatus);
INT32_T rocme_porting_network_get_eth_status(const CHAR_T *pDeviceName, ROC_BOOL *pbEthStatus);


/*******************************************************************
���ܣ����������õ���������һ�������ø��ײ㣬�������԰��� ethernet�����µ�����������Զ����Խ������á�
    �书������ PC���������õ�ȷ�ϰ�ť�Ĺ��ܡ�
���������
    deviceName���������ƣ�
����ֵ����ֵ�ͣ�1Ϊ�ɹ� 0Ϊʧ��
��ע����
*/
INT32_T rocme_porting_network_submit_parameters(CHAR_T* deviceName);


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
INT32_T rocme_porting_network_get_APs(CHAR_T* deviceName, CHAR_T* apInfo);


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
INT32_T rocme_porting_network_connect_AP(CHAR_T* deviceName, CHAR_T* essId, INT32_T keyType, CHAR_T* key);


/*******************************************************************
���ܣ��Ͽ���AP������
���������
    deviceName���������ƣ�
����ֵ����ֵ�ͣ��ɹ�����0��ʧ�ܷ��ش�����
��ע����
*/
INT32_T rocme_porting_network_disconnect_AP(CHAR_T* deviceName);


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
INT32_T rocme_porting_network_get_connected_AP(CHAR_T* deviceName, CHAR_T* apInfo);




/**********************************
����˵����
   ��ȡ����������Ϣ
    
����˵����
    ���������deviceName �豸����
    ���������pDescription����������Ϣ
    
��    �أ�1��ʾ�ɹ���0��ʾʧ��

�ο�ʵ�֣�
**********************************/
INT32_T rocme_porting_network_get_description(CHAR_T *deviceName, CHAR_T *pDescription);



/**********************************
����˵����
   �ָ���������MiddleWare ���е�������Դ�������Դ��
    
����˵����
    �����������
    �����������
    
��    �أ�1��ʾ�ɹ���0��ʾʧ��

�ο�ʵ�֣�
**********************************/
INT32_T rocme_porting_network_restore(void);

#ifdef __cplusplus
}
#endif

#endif

