
#include "esp8266.h"


Void __esp8266_Send_Test_AT_cmd(Void);
Void __esp8266_Send_AT_RST_cmd(Void);
Void __esp8266_Send_AT_GMR_cmd(Void);
Void __esp8266_Send_AT_GSLP_cmd(UInt16 time);
Void __esp8266_Send_ATE_cmd(Bool echo); 
Void __esp8266_Send_AT_RESTORE_cmd(Void);

Void __esp8266_Send_AT_UART_CUR_cmd(UInt16 baudrate, UInt8  databits, UInt8  stopbits, UInt8  parity, UInt8  flow_control);
Void __esp8266_Send_AT_UART_DEF_cmd(UInt16 baudrate, UInt8  databits, UInt8  stopbits, UInt8  parity, UInt8  flow_control); 

Void __esp8266_Send_AT_SLEEP_req_cmd(Void);
Void __esp8266_Send_AT_SLEEP_set_cmd(UInt8 sleep_mode);

Void __esp8266_Send_AT_RFPOWER_set_cmd(UInt8 tx_power);

Void __esp8266_Send_AT_RFVDD_get_cmd(Void);
Void __esp8266_Send_AT_RFVDD_set_cmd(UInt16 VDD33);
Void __esp8266_Send_AT_RFVDD_req_cmd(Void);

Void __esp8266_Send_AT_CWMODE_CUR_req_cmd(Void);
Void __esp8266_Send_AT_CWMODE_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CWMODE_CUR_set_cmd(UInt8 mode); 
Void __esp8266_Send_AT_CWMODE_DEF_req_cmd(Void);
Void __esp8266_Send_AT_CWMODE_DEF_get_cmd(Void);
Void __esp8266_Send_AT_CWMODE_DEF_set_cmd(UInt8 mode); 

Void __esp8266_Send_AT_CWJAP_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CWJAP_DEF_get_cmd(Void);
Void __esp8266_Send_AT_CWJAP_CUR_set_cmd(Char* ssid, Char* pwd, Char* bssid);
Void __esp8266_Send_AT_CWJAP_DEF_set_cmd(Char* ssid, Char* pwd, Char* bssid);

Void __esp8266_Send_AT_CWLAPOPT_set_cmd(Bool sort_enable, UInt8 mask);
Void __esp8266_Send_AT_CWLAP_get_cmd(Void);
Void __esp8266_Send_AT_CWLAP_set_cmd(Char* ssid, Char* mac, Char* ch);

Void __esp8266_Send_AT_CWQAP_cmd(Void);

Void __esp8266_Send_AT_CWSAP_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CWSAP_DEF_get_cmd(Void);
Void __esp8266_Send_AT_CWSAP_CUR_set_cmd(_In_ Char*    ssid, _In_ Char*    pwd, _In_ UInt8  chl, _In_ UInt8  ecn, _In_ UInt8* max_conn, _In_ UInt8* ssid_hidden);
Void __esp8266_Send_AT_CWSAP_DEF_set_cmd(_In_ Char*   ssid, _In_ Char*   pwd, _In_ UInt8 chl, _In_ UInt8 ecn, _In_ Char*   max_conn, _In_ Char*   ssid_hidden);

Void __esp8266_Send_AT_CWLIF_cmd(Void);

Void __esp8266_Send_AT_CWDHCP_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CWDHCP_DEF_get_cmd(Void);
Void __esp8266_Send_AT_CWDHCP_CUR_set_cmd(UInt8 mode, Bool en) ;
Void __esp8266_Send_AT_CWDHCP_DEF_set_cmd(UInt8 mode, Bool en) ;

Void __esp8266_Send_AT_CWDHCPS_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CWDHCPS_DEF_get_cmd(Void);
Void __esp8266_Send_AT_CWDHCPS_CUR_set_cmd(Bool enable, UInt16 lease_time, Char* startIP, Char* endIP) ;
Void __esp8266_Send_AT_CWDHCPS_DEF_set_cmd(Bool enable, UInt16 lease_time, Char* startIP, Char* endIP) ;

Void __esp8266_Send_AT_CWAUTOCONN_set_cmd(Bool enable) ;

Void __esp8266_Send_AT_CIPSTAMAC_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CIPSTAMAC_DEF_get_cmd(Void);
Void __esp8266_Send_AT_CIPAPMAC_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CIPAPMAC_DEF_get_cmd(Void); 
Void __esp8266_Send_AT_CIPSTAMAC_CUR_set_cmd(Char* mac); 
Void __esp8266_Send_AT_CIPSTAMAC_DEF_set_cmd(Char* mac); 
Void __esp8266_Send_AT_CIPAPMAC_CUR_set_cmd(Char* mac);
Void __esp8266_Send_AT_CIPAPMAC_DEF_set_cmd(Char* mac); 

Void __esp8266_Send_AT_CIPSTA_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CIPSTA_DEF_get_cmd(Void);
Void __esp8266_Send_AT_CIPAP_CUR_get_cmd(Void);
Void __esp8266_Send_AT_CIPAP_DEF_get_cmd(Void);
Void __esp8266_Send_AT_CIPSTA_CUR_set_cmd(_In_ Char* IP, _In_ Char* gateway, _In_ Char* netmask);
Void __esp8266_Send_AT_CIPSTA_DEF_set_cmd(_In_ Char* IP, _In_ Char* gateway, _In_ Char* netmask);
Void __esp8266_Send_AT_CIPAP_CUR_set_cmd(_In_ Char* IP, _In_ Char* gateway, _In_ Char* netmask);
Void __esp8266_Send_AT_CIPAP_CUR_set_cmd(_In_ Char* IP, _In_ Char* gateway, _In_ Char* netmask);

Void __esp8266_Send_AT_CWSTARTSMART_cmd(Void);
Void __esp8266_Send_AT_CWSTARTSMART_set_cmd(UInt8 type); 

Void __esp8266_Send_AT_CWSTOPSMART_cmd(Void);
Void __esp8266_Send_AT_CWSTOPSMART_set_cmd(_In_ Char*    WeChat_number, _In_ Char*    dev_type, _In_ UInt32 time);

Void __esp8266_Send_AT_CWSTOPDISCOVER_cmd(Void);

Void __esp8266_Send_AT_WPS_cmd(Bool enable);

Void __esp8266_Send_AT_MDNS_cmd(_In_ Bool     enable, _In_ Char*    hostname, _In_ Char*    server_name, _In_ UInt16 server_port);

Void __esp8266_Send_AT_CIPSTATUS_cmd(Void);

Void __esp8266_Send_AT_CIPDOMAIN_cmd(Char* domain_name);

Bool single_connection = true;
Bool Multiple_connection = true;

Void __esp8266_Send_AT_CIPSTART_TCP_cmd(linkID, type, remoteIP, remote_port, TCP_keep_alive);
Void __esp8266_Send_AT_CIPSTART_UDP_cmd(linkID, type, remoteIP, remote_port, UDPlocal_port, UDP_mode);
Void __esp8266_Send_AT_CIPSTART_SSL_cmd(linkID, type, remoteIP, remote_port, TCP_keep_alive);

Void __esp8266_Send_AT_CIPSSLSIZE_cmd(_In_ UInt16 size);
Void __esp8266_Send_AT_CIPSSLSIZE_cmd(_In_ UInt8  linkID, _In_ UInt16 length);

Void __esp8266_Send_AT_CIPSSLSIZE_UDP_cmd(_In_ UInt8  linkID, _In_ UInt16 length,_In_ Char*  remoteIP, _In_ UInt16 remote_port);
Void __esp8266_Send_AT_CIPSSLSIZE_TT_MODE_cmd(Void);

Void __esp8266_Send_AT_CIPSENDEX_cmd(_In_ UInt8  linkID, _In_ UInt16 length);
Void __esp8266_Send_AT_CIPSENDEX_UDP_cmd(_In_ UInt8  linkID, _In_ UInt16 length,_In_ Char*  remoteIP, _In_ UInt16 remote_port);
Void __esp8266_Send_AT_CIPSENDBUF_cmd(_In_ UInt8  linkID, _In_ UInt16 length);

Void __esp8266_Send_AT_CIPBUFSTATUS_cmd(_In_ UInt16 linkID);
Void __esp8266_Send_AT_CIPBUFSTATUS_cmd(_In_ UInt16 linkID,_In_ UInt16 segmentID);
Void __esp8266_Send_AT_CIPBUFSTATUS_cmd(_In_ UInt16 linkID);

Void __esp8266_Send_AT_CIPCLOSE_cmd(_In_ UInt16 linkID);

Void __esp8266_Send_AT_CIFSR_cmd(Void);
Void __esp8266_Send_AT_CIFSR_get_cmd(Void);
Void __esp8266_Send_AT_CIFSR_set_cmd(Bool mode);

Void __esp8266_Send_AT_CIPSERVER_cmd(Bool mode, UInt16 port);
Void __esp8266_Send_AT_CIPMODE_get_cmd(Void);
Void __esp8266_Send_AT_CIPMODE_set_cmd(Bool mode);

Void __esp8266_Send_AT_SAVETRANSLINK_TCP_cmd(Bool mode, Char* remoteIP, UInt16 remote_port, UInt16 TCP_keep_alive); 
Void __esp8266_Send_AT_SAVETRANSLINK_TCP_cmd(Bool mode, Char* remoteIP, UInt16 remote_port, UInt16 UDP_local_port); 



Void __esp8266_Send_AT_CIPSTO_get_cmd(Void); 
Void __esp8266_Send_AT_CIPSTO_set_cmd(UInt16 time);

Void __esp8266_Send_AT_PING_cmd(Char* IP);

Void __esp8266_Send_AT_CIUPDATE_cmd(Void);

Void __esp8266_Send_AT_CIPDINFO_cmd(Bool mode);
