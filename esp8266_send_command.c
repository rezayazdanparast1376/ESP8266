#include "esp8266.h"


// ================================================== Basic Command ==================================================

// 1.  AT           – Test AT startup
// 2.  AT+RST       – Restart module
// 3.  AT+GMR       – View version info
// 4.  AT+GSLP      – Enter deep-sleep mode
// 5.  ATE          – AT commands echo
// 6.  AT+RESTORE   – Factory reset
// 7.  AT+UART      – UART configuration
// 8.  AT+UART_CUR  – current UART configuration
// 9.  AT+UART_DEF  – default UART configuration
// 10. AT+SLEEP     – sleep mode
// 11. AT+RFPOWER   – set maximum value of RF TX Power
// 12. AT+RFVDD     – set RF TX Power according to VDD33
// ===================================================================================================================




/**
 * @addtogroup Basic_at_commands
 * 
 * @typedef Type Execute
 * 
 * 
*/
Void __esp8266_Send_Test_AT_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @addtogroup Basic_at_commands
 * 
*/
Void __esp8266_Send_AT_RST_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+RST%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));   
}



/**
 * @addtogroup Basic_at_commands
 * 
*/
Void __esp8266_Send_AT_GMR_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+GMR%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf)); 
}




// AT+GSLP
/**
 * @addtogroup Basic_at_commands
 * 
*/
Void __esp8266_Send_AT_GSLP_cmd(UInt16 time) {
    UInt8 send_buf[15] = {0};
    sprintf((Char*)send_buf, "AT+GSLP=%d%c", time, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf)); 
}




// ATE
/**
 * @addtogroup Basic_at_commands
 * 
*/
Void __esp8266_Send_ATE_cmd(
    Bool echo
) {
    UInt8 send_buf[15] = {0};
    
    if (echo == true) {
        sprintf((Char*)send_buf, "ATE1%c", CARRIAR_RETURN);
    }
    else if (echo == false) {
        sprintf((Char*)send_buf, "ATE0%c", CARRIAR_RETURN);
    }
    
    esp8266_uart_send(send_buf, strlen(send_buf)); 
}




// AT+RESTORE
/**
 * @addtogroup Basic_at_commands
 * 
*/
Void __esp8266_Send_AT_RESTORE_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+RESTORE%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// AT+UART_CUR
// AT+UART_CUR=<baudrate>, <databits>, <stopbits>, <parity>, <flow control>
// Example AT+UART_CUR=115200, 8, 1, 0, 3
/**
 * @addtogroup Basic_at_commands
 * 
 * @brief This command sets the current UART configuration; it does not write to the flash. Hence there is no change in the default baudrate.
 * 
 * @param baudrate     Baudrate range: 110 to 115200*40 (4.608 Mega)
 * @param databits     [ 5: 5 bits data, 6: 6 bits data, 7: 7 bits data, 8: 8 bits data]
 * @param stopbits     [ 1: 1 bit stop bit, 2: 1.5 bit stop bit, 3: 2 bit stop bit ]
 * @param parity       [ 0: None, 1: Odd, 2: EVEN ]
 * @param flow_control [0: disable flow control, 1: enable RTS, 2: enable CTS, 3: enable both RTS and CTS]
 * 
*/
Void __esp8266_Send_AT_UART_CUR_cmd(
    UInt16 baudrate, 
    UInt8  databits, 
    UInt8  stopbits, 
    UInt8  parity, 
    UInt8  flow_control
) {

    UInt8 send_buf[35] = {0};

    sprintf((Char*)send_buf, "AT+UART_CUR=%d, %d, %d, %d, %d%c", baudrate, databits, stopbits, parity, flow_control, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// AT+UART_DEF – default UART configuration

/**
 * @addtogroup Basic_at_commands
 * 
 * @brief This command sets the UART configuration and save it to flash. It is stored as the default parameter and will also be used as the default baudrate henceforth.
 * @example AT+UART_DEF=115200, 8, 1, 0, 3
 * 
 * @param baudrate     Baudrate range: 110 to 115200*40 (4.608 Mega)
 * @param databits     [ 5: 5 bits data, 6: 6 bits data, 7: 7 bits data, 8: 8 bits data]
 * @param stopbits     [ 1: 1 bit stop bit, 2: 1.5 bit stop bit, 3: 2 bit stop bit ]
 * @param parity       [ 0: None, 1: Odd, 2: EVEN ]
 * @param flow_control [0: disable flow control, 1: enable RTS, 2: enable CTS, 3: enable both RTS and CTS]
 * 
*/ 
Void __esp8266_Send_AT_UART_DEF_cmd(
    UInt16 baudrate, 
    UInt8  databits, 
    UInt8  stopbits, 
    UInt8  parity, 
    UInt8  flow_control
) {
    UInt8 send_buf[35] = {0};

    sprintf((Char*)send_buf, "AT+UART_DEF=%d, %d, %d, %d, %d%c", baudrate, databits, stopbits, parity, flow_control, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}






// 10. AT+SLEEP – sleep mode 
/**
 * @addtogroup Basic_at_commands
 * 
 * @brief This command sets ESP8266 sleep mode. It can only be used in station mode, default to be modem sleep mode.
 * 
 * @example  
 *  Command 
 *  AT+SLEEP?
 *  
 *  Response
 *  +SLEEP : <sleep mode> 
 *  
 *  OK
*/
Void __esp8266_Send_AT_SLEEP_req_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+SLEEP?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// AT+SLEEP=<sleep mode>
/**
 * @addtogroup Basic_at_commands
 * 
 * @brief This command sets ESP8266 sleep mode. It can only be used in station mode, default to be modem sleep mode.
 * 
 * @param sleep_mode [0 : disable sleep mode, 1 : light-sleep mode, 2 : modem-sleep mode]
 * 
 * @example 
 * Command 
 * AT+SLEEP=<sleep mode>
 * Response 
 * OK
 */
Void __esp8266_Send_AT_SLEEP_set_cmd(
    UInt8 sleep_mode
) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+SLEEP=%d%c", sleep_mode, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// AT+RFPOWER
/**
 * @addtogroup Basic_at_commands
 * 
 * @brief This command sets the maximum value of ESP8266 RF TX power, it is not precise.
 * @example  Example AT+RFPOWER=50
 * 
 * @param tx_power
 * 
*/
Void __esp8266_Send_AT_RFPOWER_set_cmd(
    UInt8 tx_power
) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+RFPOWER=%d%c", tx_power, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// AT+RFVDD
/**
 * @addtogroup Basic_at_commands
 * 
 * @brief This command sets ESP8266 RF TX power according to VDD33. To get the power voltage of ESP8266 VDD3P3, TOUT pin has to be suspended. 
 * TOUT pin has to be suspended to measure VDD33.
 * 
 * @example
 * Command AT+RFVDD?
 * Response +RFVDD:<VDD33> 
 * OK
 * 
 * @param  <VDD33> power voltage of ESP8266 VDD33, unit: 1/1024 V TOUT pin has to be suspended to measure VDD33.
 * 
*/
Void __esp8266_Send_AT_RFVDD_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+RFVDD?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}


/**
 * @addtogroup Basic_at_commands
 * 
 * @brief  AT+RFVDD=<VDD33>
 * @param VDD33 <VDD33> power voltage of ESP8266 VDD33, range [1900, 3300]
*/
Void __esp8266_Send_AT_RFVDD_set_cmd(
    UInt16 VDD33
) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+RFVDD=%d%c", VDD33, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// AT+RFVDD
/**
 * @addtogroup Basic_at_commands
 * @brief AT+RFVDD
 * @note  "AT+RFVDD" will automatically set RF TX power according to VDD33. TOUT pin has to be suspended. 
*/
Void __esp8266_Send_AT_RFVDD_req_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+RFVDD%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// AT+CWMODE            Wi-Fi mode(sta/AP/sta+AP),                                  [@deprecated]
// AT+CWMODE_CUR        Wi-Fi mode(sta/AP/sta+AP) Won’t save to Flash
// AT+CWMODE_DEF        Wi-Fi default mode(sta/AP/sta+AP) Save to Flash
// AT+CWJAP             Connect to AP,                                              [@deprecated]
// AT+CWJAP_CUR         Connect to AP, won’t save to Flash
// AT+CWJAP_DEF         Connect to AP, save to Flash
// AT+CWLAPOPT          Set the configuration of command AT+CWLAP
// AT+CWLAP             Lists available APs
// AT+CWQAP             Disconnect from AP
// AT+CWSAP             Set configuration of ESP8266 soft-AP                        [@deprecated]
// AT+CWSAP_CUR         Set configuration of ESP8266 soft-AP Won’t save to Flash.
// AT+CWSAP_DEF         Set configuration of ESP8266 soft-AP Save to Flash.
// AT+CWLIF             Get station’s IP which is connected to ESP8266 soft-AP
// AT+CWDHCP            Enable/Disable DHCP,                                        [@deprecated]
// AT+CWDHCP_CUR        Enable/Disable DHCP, won’t save to Flash
// AT+CWDHCP_DEF        Enable/Disable DHCP, save to Flash
// AT+CWDHCPS_CUR       Set IP range of DHCP server, won’t save to Flash
// AT+CWDHCPS_DEF       Set IP range of DHCP server, save to Flash
// AT+CWAUTOCONN        Connect to AP automatically when power on
// AT+CIPSTAMAC         Set MAC address of ESP8266 station                          [@deprecated]
// AT+CIPSTAMAC_CUR     Set MAC address of ESP8266 station Won’t save to Flash.
// AT+CIPSTAMAC_DEF     Set MAC address of ESP8266 station Save to Flash.
// AT+CIPAPMAC          Set MAC address of ESP8266 soft-AP                          [@deprecated]
// AT+CIPAPMAC_CUR      Set MAC address of ESP8266 soft-AP Won’t save to Flash.
// AT+CIPAPMAC_DEF      Set MAC address of ESP8266 soft-AP Save to Flash.
// AT+CIPSTA            Set IP address of ESP8266 station,                          [@deprecated]
// AT+CIPSTA_CUR        Set IP address of ESP8266 station Won’t save to Flash.
// AT+CIPSTA_DEF        Set IP address of ESP8266 station Save to Flash.
// AT+CIPAP             Set IP address of ESP8266 soft-AP,                          [@deprecated]
// AT+CIPAP_CUR         Set IP address of ESP8266 soft-AP Won’t save to Flash.
// AT+CIPAP_DEF         Set IP address of ESP8266 soft-AP Save to Flash.
// AT+CWSTARTSMART      Start SmartConfig
// AT+CWSTOPSMART       Stop SmartConfig
// AT+CWSTARTDISCOVER   Start the mode that ESP8266 can be found by WeChat
// AT+CWSTOPDISCOVER    Stop the mode that ESP8266 can be found by WeChat
// AT+WPS               Set WPS function
// AT+MDNS              Set MDNS function



/**
 *  Command AT+CWMODE_CUR=?
 *  Response
 * +CWMODE_CUR:( value scope of <mode>) 
 * OK
*/
Void __esp8266_Send_AT_CWMODE_CUR_req_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWMODE_CUR=?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}


/**
 * Command AT+CWMODE_CUR?
 * Response
 * +CWMODE_CUR:<mode> 
 * OK
*/
Void __esp8266_Send_AT_CWMODE_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWMODE_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



 

/**
 * Command AT+CWMODE_CUR=<mode>
 * Response OK
*/
Void __esp8266_Send_AT_CWMODE_CUR_set_cmd(UInt8 mode) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWMODE_CUR=%d%c", mode, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * Command AT+CWMODE_DEF=?
 * Response
 * +CWMODE_DEF:( value scope of <mode>) 
 * OK
*/
Void __esp8266_Send_AT_CWMODE_DEF_req_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWMODE_DEF=?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * Command AT+CWMODE_DEF?
 * Response
 * +CWMODE_DEF:<mode> 
 * OK
*/
Void __esp8266_Send_AT_CWMODE_DEF_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWMODE_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



/**
 * Command AT+CWMODE_DEF=<mode>
 * Response OK
*/
Void __esp8266_Send_AT_CWMODE_DEF_set_cmd(UInt8 mode) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWMODE_DEF?%d%c", mode, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



/**
 * Command AT+CWJAP_CUR?
 * Response
 * +CWJAP_CUR:<ssid>, <bssid>, <channel>, <rssi> 
 * OK
*/
Void __esp8266_Send_AT_CWJAP_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWJAP_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWJAP_CUR=<ssid>, <pwd>[, <bssid>]
// Response
// OK 
// or 
// +CWJAP:<error code> 
// FAIL
Void __esp8266_Send_AT_CWJAP_CUR_set_cmd(
    Char* ssid, 
    Char* pwd, 
    Char* bssid
) {
    UInt8 send_buf[35] = {0};

    if (bssid == NULL) {
        sprintf((Char*)send_buf, "AT+CWJAP_CUR=%s, %s%c", ssid, pwd, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CWJAP_CUR=%s, %s, %s%c", ssid, pwd, bssid, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWJAP_DEF?
// Response
// +CWJAP_DEF:<ssid>, <bssid>, <channel>, <rssi> 
// OK
Void __esp8266_Send_AT_CWJAP_DEF_get_cmd() {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWJAP_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWJAP_DEF=<ssid>, <pwd>[, <bssid>]
// Response
// OK 
// or 
// +CWJAP:<error code> 
// FAIL
Void __esp8266_Send_AT_CWJAP_DEF_set_cmd(
    Char* ssid, 
    Char* pwd, 
    Char* bssid
) {
    UInt8 send_buf[15] = {0};

    if (bssid == NULL) {
        sprintf((Char*)send_buf, "AT+CWJAP_DEF=%s, %s%c", CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CWJAP_DEF=%s, %s, %s%c", CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}






//  Command AT+CWLAPOPT=<sort_enable>, <mask>
//  Response OK or ERROR
Void __esp8266_Send_AT_CWLAPOPT_set_cmd(Bool sort_enable, UInt8 mask) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWLAPOPT=%d, %d%c", sort_enable, mask, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWLAP=<ssid>[, <mac>, <ch>]
// Response
// +CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration> 
// OK 
// ERROR
Void __esp8266_Send_AT_CWLAP_set_cmd(Char* ssid, Char* mac, Char* ch) {
    UInt8 send_buf[35] = {0};

    if (mac == NULL && ch == NULL) {
        sprintf((Char*)send_buf, "AT+CWLAP=%s%c", ssid, CARRIAR_RETURN);
    }
    else if (mac != NULL && ch == NULL) {
        sprintf((Char*)send_buf, "AT+CWLAP=%s, %s%c", ssid, mac, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CWLAP=%s, %s, %d%c", ssid, mac, ch, CARRIAR_RETURN);
    } 

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWLAP
// Response
// +CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration> 
// OK 
// ERROR
Void __esp8266_Send_AT_CWLAP_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWLAP%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWQAP
Void __esp8266_Send_AT_CWQAP_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWQAP%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



//  Command AT+CWSAP_CUR?
//  Response +CWSAP_CUR:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>
Void __esp8266_Send_AT_CWSAP_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWSAP_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWSAP_CUR=<ssid>, <pwd>, <chl>, <ecn>[, <max conn>][, <ssid hidden>]
// Response OK 
// ERROR
Void __esp8266_Send_AT_CWSAP_CUR_set_cmd(
    _In_ Char*    ssid, 
    _In_ Char*    pwd, 
    _In_ UInt8  chl, 
    _In_ UInt8  ecn, 
    _In_ UInt8* max_conn, 
    _In_ UInt8* ssid_hidden
) {
    UInt8 send_buf[15] = {0};

    if (max_conn == NULL || ssid_hidden == NULL) {
        sprintf((Char*)send_buf, "AT+CWSAP_CUR=%s, %s, %d, %d%c", ssid, pwd, chl, ecn, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CWSAP_CUR=%s, %s, %d, %d, %d, %d%c", ssid, pwd, chl, ecn, max_conn, ssid_hidden, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWSAP_DEF?
// Response +CWSAP_DEF:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>
Void __esp8266_Send_AT_CWSAP_DEF_get_cmd() {
    UInt8 send_buf[15] = {0};
    
    sprintf((Char*)send_buf, "AT+CWSAP_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWSAP_DEF=<ssid>, <pwd>, <chl>, <ecn>[, <max conn>][, <ssid hidden>]
// Response OK 
// ERROR
Void __esp8266_Send_AT_CWSAP_DEF_set_cmd(
    _In_ Char*   ssid, 
    _In_ Char*   pwd, 
    _In_ UInt8 chl, 
    _In_ UInt8 ecn, 
    _In_ Char*   max_conn, 
    _In_ Char*   ssid_hidden
) {
    UInt8 send_buf[15] = {0};
    
    if (max_conn != NULL && ssid_hidden != NULL) {
        sprintf((Char*)send_buf, "AT+CWSAP_DEF=%s, %s, %d, %d, %s, %s%c", ssid, pwd, chl, ecn, max_conn, ssid_hidden, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CWSAP_DEF=%s, %s, %d, %d%c", ssid, pwd, chl, ecn, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}



/**
 * @brief This command is used to get the IP of stations that are connected to ESP8266 softAP.
 * AT+CWLIF– IP of stations which are connected to ESP8266 softAP
 * 
 * @param   IPaddr  IP address of stations which are connected to ESP8266 softAP  
 * @param   mac     MAC address of stations which are connected to ESP8266 softAP
 * 
 * @note This command can not get static IP, it is only available if DHCP is enabled.
 * 
 * @todo test ...
 * 
 *  Response
 *  <IP addr>, <mac>
 *  OK
*/
Void __esp8266_Send_AT_CWLIF_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWLIF%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}
 
 
 
/**
 * @brief
 * 
 * @note  
 * • This configuration will NOT store in Flash user parameter area. 
 * • This configuration interact with static IP related AT commands(AT+CIPSTA related and AT+CIPAP related): 
 *      ‣ If enable DHCP, static IP will be disabled; 
 *      ‣ If enable static IP, DHCP will be disabled; 
 *      ‣ This will depends on the last configuration.
 * 
 * 
*/  
Void __esp8266_Send_AT_CWDHCP_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWDHCP_CUR?%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
} 
 

// Command AT+CWDHCP_CUR=<mode>, <en>
// Response OK
Void __esp8266_Send_AT_CWDHCP_CUR_set_cmd(UInt8 mode, Bool en) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWDHCP_CUR=%d, %d%c",mode, en, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWDHCP_DEF?
// Response DHCP disabled or enabled now?
Void __esp8266_Send_AT_CWDHCP_DEF_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWDHCP_DEF?%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWDHCP_DEF=<mode>, <en>
// Response OK
Void __esp8266_Send_AT_CWDHCP_DEF_set_cmd(UInt8 mode, Bool en) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWDHCP_DEF=%d, %d%c",mode, en, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWDHCPS_CUR?
// Response +CWDHCPS_CUR=<lease time>, <start IP>, <end IP>
Void __esp8266_Send_AT_CWDHCPS_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWDHCPS_CUR?%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWDHCPS_CUR=<enable>, <lease time>, <start IP>, <end IP>
// Response OK
/**
 * @param[in] enable 
 *          0 : Disable the settings and use the default IP range. 
 *          1: Enable setting the IP range, parameters below have to be set.
 * @param[in] lease_time    the unit of lease time is minute, range [1, 2880] 
 * @param[in] startIP       start IP of the IP range that can be got from ESP8266 soft-AP DHCP server 
 * @param[in] endIP         end IP of the IP range that can be got from ESP8266 soft-AP DHCP server
*/
Void __esp8266_Send_AT_CWDHCPS_CUR_set_cmd(Bool enable, UInt16 lease_time, Char* startIP, Char* endIP) {
    UInt8 send_buf[15] = {0};

    if (enable == true) {
        sprintf((Char*)send_buf, "AT+CWDHCPS_CUR=%d, %d, %s, %s%c", enable, lease_time, startIP, endIP, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CWDHCPS_CUR=0%c", CARRIAR_RETURN);
    }
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWDHCPS_DEF?
// Response +CWDHCPS_DEF=<lease time>, <start IP>, <end IP>
Void __esp8266_Send_AT_CWDHCPS_DEF_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWDHCPS_DEF?%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWDHCPS_DEF=<enable>, <lease time>, <start IP>, <end IP>
// Response OK
Void __esp8266_Send_AT_CWDHCPS_DEF_set_cmd(Bool enable, UInt16 lease_time, Char* startIP, Char* endIP) {
    UInt8 send_buf[15] = {0};

    if (enable == true) {
        sprintf((Char*)send_buf, "AT+CWDHCPS_DEF=%d, %d, %s, %s%c", enable, lease_time, startIP, endIP, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CWDHCPS_DEF=0%c", CARRIAR_RETURN);
    }
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWAUTOCONN=<enable>
// Response OK
Void __esp8266_Send_AT_CWAUTOCONN_set_cmd(Bool enable) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWAUTOCONN=%d%c", enable, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTAMAC_CUR?
// Response
// +CIPSTAMAC_CUR:<mac> 
// OK
Void __esp8266_Send_AT_CIPSTAMAC_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPSTAMAC_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTAMAC_CUR=<mac>
// Response OK
Void __esp8266_Send_AT_CIPSTAMAC_CUR_set_cmd(Char* mac) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPSTAMAC_CUR=%s%c", mac, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTAMAC_DEF?
// Response
// +CIPSTAMAC_DEF:<mac> 
// OK
Void __esp8266_Send_AT_CIPSTAMAC_DEF_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPSTAMAC_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTAMAC_DEF=<mac>
// Response OK
Void __esp8266_Send_AT_CIPSTAMAC_DEF_set_cmd(Char* mac) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPSTAMAC_DEF=%s%c", mac, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPAPMAC_CUR?
// Response
// +CIPAPMAC_CUR:<mac> 
// OK
Void __esp8266_Send_AT_CIPAPMAC_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPAPMAC_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPAPMAC_CUR=<mac>
// Response OK
Void __esp8266_Send_AT_CIPAPMAC_CUR_set_cmd(Char* mac) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPAPMAC_CUR=%s%c", mac, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPAPMAC_DEF?
// Response
// +CIPAPMAC_DEF:<mac> 
// OK
Void __esp8266_Send_AT_CIPAPMAC_DEF_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPAPMAC_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPAPMAC_DEF=<mac>
// Response
// OK
Void __esp8266_Send_AT_CIPAPMAC_DEF_set_cmd(Char* mac) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPAPMAC_DEF=%s%c", mac, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTA_CUR?
// Response
// +CIPSTA_CUR:<IP> 
// OK
Void __esp8266_Send_AT_CIPSTA_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPSTA_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTA_CUR=<IP>[, <gateway>, <netmask>]
// Response OK
Void __esp8266_Send_AT_CIPSTA_CUR_set_cmd(
    _In_ Char* IP, 
    _In_ Char* gateway, 
    _In_ Char* netmask
) {
    UInt8 send_buf[15] = {0};

    if (gateway != NULL && netmask != NULL) {
        sprintf((Char*)send_buf, "AT+CIPSTA_CUR=%s, %s, %s%c", CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPSTA_CUR=%s%c", CARRIAR_RETURN);      
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTA_DEF?
// Response
// +CIPSTA:<IP> 
// OK
Void __esp8266_Send_AT_CIPSTA_DEF_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPSTA_DEF?%c", CARRIAR_RETURN);      

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTA_DEF=<IP>[, <gateway>, <netmask>]
// Response OK
Void __esp8266_Send_AT_CIPSTA_DEF_set_cmd(
    _In_ Char* IP, 
    _In_ Char* gateway, 
    _In_ Char* netmask
) {
    UInt8 send_buf[15] = {0};

    if (gateway != NULL && netmask != NULL) {
        sprintf((Char*)send_buf, "AT+CIPSTA_DEF=%s, %s, %s%c", IP, gateway, netmask, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPSTA_DEF=%s%c", IP, CARRIAR_RETURN);      
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPAP_CUR?
// Response
// +CIPAP_CUR:<IP> 
// OK
Void __esp8266_Send_AT_CIPAP_CUR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPAP_CUR?%c", CARRIAR_RETURN);      

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPAP_CUR=<IP>[, <gateway>, <netmask>]
// Response OK
Void __esp8266_Send_AT_CIPAP_CUR_set_cmd(
    _In_ Char* IP, 
    _In_ Char* gateway, 
    _In_ Char* netmask
) {
    UInt8 send_buf[15] = {0};

    if (gateway != NULL && netmask != NULL) {
        sprintf((Char*)send_buf, "AT+CIPAP_CUR=%s, %s, %s%c", CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPAP_CUR=%s%c", CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPAP_DEF?
// Response
// +CIPAP_DEF:<IP> 
// OK
Void __esp8266_Send_AT_CIPAP_DEF_get_cmd() {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPAP_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPAP_DEF=<IP>[, <gateway>, <netmask>]
// Response OK
Void __esp8266_Send_AT_CIPAP_CUR_set_cmd(
    _In_ Char* IP, 
    _In_ Char* gateway, 
    _In_ Char* netmask
) {
    UInt8 send_buf[15] = {0};
    
    if (gateway != NULL && netmask != NULL) {
        sprintf((Char*)send_buf, "AT+CIPAP_CUR=%s, %s, %s%c", CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPAP_CUR=%s%c", CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWSTARTSMART 
// Response OK or ERROR
Void __esp8266_Send_AT_CWSTARTSMART_cmd() {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWSTARTSMART%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWSTARTSMART=<type>
// Response OK or ERROR
Void __esp8266_Send_AT_CWSTARTSMART_set_cmd(UInt8 type) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWSTARTSMART=%d%c", type, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWSTOPSMART
//  Response OK or ERROR
Void __esp8266_Send_AT_CWSTOPSMART_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWSTOPSMART%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWSTARTDISCOVER=<WeChat number>, <dev_type>, <time>
// Response OK or ERROR
Void __esp8266_Send_AT_CWSTOPSMART_set_cmd(
    _In_ Char*    WeChat_number, 
    _In_ Char*    dev_type, 
    _In_ uint32_t time
) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWSTARTDISCOVER=%s, %s, %d%c", WeChat_number, dev_type, time, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWSTOPDISCOVER
// Response OK or ERROR
Void __esp8266_Send_AT_CWSTOPDISCOVER_cmd() {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CWSTOPDISCOVER%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+WPS=<enable>
// Response OK or ERROR
Void __esp8266_Send_AT_WPS_cmd(Bool enable) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+WPS=%d%c", enable, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+MDNS=<enable>, <hostname>, <server_name>, <server_port>
// Response OK or ERROR
Void __esp8266_Send_AT_MDNS_cmd(
    _In_ Bool     enable, 
    _In_ Char*    hostname, 
    _In_ Char*    server_name, 
    _In_ UInt16 server_port
) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+WPS=%d, %s, %s, %d%c", enable, hostname, server_name, server_port, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// =================================================== TCP/IP ====================================================
// AT+CIPSTATUS     Get connection status
// AT+CIPDOMAIN     DNS function
// AT+CIPSTART      Establish TCP connection, UDP transmission or SSL connection 
// AT+CIPSSLSIZE    Set the size of SSL buffer
// AT+CIPSEND       Send data
// AT+CIPSENDEX     Send data, if <length> or "\0" is met, data will be sent
// AT+CIPSENDBUF    Write data into TCP-send-buffer
// AT+CIPBUFRESET   Reset segment ID count
// AT+CIPBUFSTATUS  Check status of TCP-send-buffer
// AT+CIPCHECKSEQ   Check if a specific segment is sent or not
// AT+CIPCLOSE      Close TCP/UDP/SSL connection 
// AT+CIFSR         Get local IP address 
// AT+CIPMUX        Set multiple connections mode
// AT+CIPSERVER     Configure as server
// AT+CIPMODE       Set transmission mode
// AT+SAVETRANSLINK Save transparent transmission link to Flash
// AT+CIPSTO        Set timeout when ESP8266 runs as TCP server
// AT+CIUPDATE      Upgrade firmware through network
// AT+PING          Function PING 
// AT+CIPDINFO      Show remote IP and remote port with "+IPD"




// Command AT+CIPSTATUS
// Response
// STATUS:<stat> 
// +CIPSTATUS:<link ID>, <type>, <remote_IP>, <remote_port>, <local_port>, 
// <tetype>
Void __esp8266_Send_AT_CIPSTATUS_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPSTATUS%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPDOMAIN=<domain name>
// Response +CIPDOMAIN:<IP address>
Void __esp8266_Send_AT_CIPDOMAIN_cmd(Char* domain_name) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPDOMAIN=%s%c", domain_name, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



Bool single_connection = true;
Bool Multiple_connection = true;
// Single connection 
// (AT+CIPMUX=0)
// AT+CIPSTART=  <type>, <remote IP>, <remote port>[, <TCP keep alive>]
// Multiple connection 
// (AT+CIPMUX=1)
// AT+CIPSTART=<link ID>, <type>, <remote IP>, <remote port>[, <TCP keep alive>]

// Response
// OK or ERROR 
// If TCP is connected already, returns 
// ALREADY CONNECT
Void __esp8266_Send_AT_CIPSTART_TCP_cmd(linkID, type, remoteIP, remote_port, TCP_keep_alive) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSTART=%s%c", type, remoteIP, remote_port, TCP_keep_alive, CARRIAR_RETURN);
    }
    if (Multiple_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSTART=%s%c", linkID, type, remoteIP, remote_port, TCP_keep_alive, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Single connection 
// (AT+CIPMUX=0)
// AT+CIPSTART=<type>, <remote IP>, <remote port>[, <UDP local port>, <UDP mode>]
// Multiple connection 
// (AT+CIPMUX=1)
// AT+CIPSTART=<link ID>, <type>, <remote IP>, <remote port>[, <UDP local port>, <UDP mode>]

// Response
// OK or ERROR 
// If connection already exists, returns 
// ALREADY CONNECT
Void __esp8266_Send_AT_CIPSTART_UDP_cmd(linkID, type, remoteIP, remote_port, UDPlocal_port, UDP_mode) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSTART=%s%c", type, remoteIP, remote_port, UDPlocal_port, UDP_mode, CARRIAR_RETURN);
    }
    if (Multiple_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSTART=%c", linkID, type, remoteIP, remote_port, UDPlocal_port, UDP_mode, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Single connection 
// (AT+CIPMUX=0)
// AT+CIPSTART= <type>, <remote IP>, <remote port>[, <TCP keep alive>]
// Multiple connection 
// (AT+CIPMUX=1)
// AT+CIPSTART=<link ID>, <type>, <remote IP>, <remote port>[, <TCP keep alive>]

// Response
// OK or ERROR 
// If TCP is connected already, returns 
// ALREADY CONNECT
Void __esp8266_Send_AT_CIPSTART_SSL_cmd(linkID, type, remoteIP, remote_port, TCP_keep_alive) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSTART=%s%c", type, remoteIP, remote_port, TCP_keep_alive, CARRIAR_RETURN);
    }
    if (Multiple_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSTART=%c", linkID, type, remoteIP, remote_port, TCP_keep_alive, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command
// AT+CIPSSLSIZE=<size>
// Response
// OK or ERROR
/**
 * @brief Set the size of SSL buffer 
 * 
 * @param[in]  size   The size of SSL buffer, range: 2048 ~ 4096
*/
Void __esp8266_Send_AT_CIPSSLSIZE_cmd(
    _In_ UInt16 size
) {
    Soft_Assert_Void(size >= 2048 && size <= 4096, "Invalid parameter! size parameter must be in range: 2048 ~ 4096");

    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPSSLSIZE=%s%c", size, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Single connection (+CIPMUX=0) 
// AT+CIPSEND=<length>

// Multiple connection (+CIPMUX=1) 
// AT+CIPSEND=<link ID>, <length>
Void __esp8266_Send_AT_CIPSSLSIZE_cmd(
    _In_ UInt8  linkID, 
    _In_ UInt16 length
) {
    Soft_Assert_Void(linkID <= 4, "Invalid linkID!");
    Soft_Assert_Void(length <= 2048, "Invalind parameter!");

    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSEND=%d%c", length, CARRIAR_RETURN);
    }
    if (Multiple_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSTART=%d, %d%c", linkID, length, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// UDP Transmission AT+CIPSEND=[<link ID>, ]<length>[, <remote IP>, <remote port>]
/**
 * @brief Send data
 * 
 * @param[in] linkID      ID of the connection (0~4), for multi-connect 
 * @param[in] length      data length, MAX 2048 bytes  
 * @param[in] remoteIP    UDP transmission can set remote IP when send data 
 * @param[in] remote_port UDP transmission can set remote port when send data
*/
Void __esp8266_Send_AT_CIPSSLSIZE_UDP_cmd(
    _In_ UInt8  linkID, 
    _In_ UInt16 length,
    _In_ Char*  remoteIP, 
    _In_ UInt16 remote_port
) {
    Soft_Assert_Void(linkID <= 4, "Invalid linkID!");
    Soft_Assert_Void(length <= 2048, "Invalind parameter!");

    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        if (remoteIP != NULL) {
            sprintf((Char*)send_buf, "AT+CIPSEND=%d, %s, %d%c", length, remoteIP, remote_port, CARRIAR_RETURN);
        }
        else {
            sprintf((Char*)send_buf, "AT+CIPSEND=%d%c", length, CARRIAR_RETURN);
        }
    }
    if (Multiple_connection == 1) {
        if (remoteIP != NULL) {
            sprintf((Char*)send_buf, "AT+CIPSTART=%d, %d, %s, %d%c", linkID, length, remoteIP, remote_port, CARRIAR_RETURN);
        }
        else {
            sprintf((Char*)send_buf, "AT+CIPSTART=%d, %d%c", linkID, length, CARRIAR_RETURN);
        }
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CIPSEND
/**
 * @brief Send data
 * 
 * @attention  Wrap return ">" after execute command. Enters unvarnished transmission, 20ms interval between each packet, maximum 2048 bytes per packet. 
 * When single packet containing "+++" is received, it returns to normal command mode. Please wait at least 1 second before sending next AT command. 
 * @note
 * This command can only be used in transparent transmission mode which require to be single connection mode.  
 * For UDP transparent transmission, <UDP mode> has to be 0 in command "AT+CIPSTART"
*/
Void __esp8266_Send_AT_CIPSSLSIZE_TT_MODE_cmd(Void) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSEND%c", CARRIAR_RETURN);
    }    

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Single connection (+CIPMUX=0) 
// AT+CIPSENDEX=<length>

// Multiple connection (+CIPMUX=1) 
// AT+CIPSENDEX=<link ID>, <length>

/**
 * @param[in] linkID ID of the connection (0~4), for multi-connect 
 * @param[in] length data length, MAX 2048 bytes
*/
Void __esp8266_Send_AT_CIPSENDEX_cmd(
    _In_ UInt8  linkID, 
    _In_ UInt16 length
) {
    Soft_Assert_Void(linkID <= 4, "Invalid linkID!");
    Soft_Assert_Void(length <= 2048, "Invalind parameter!");

    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSEND=%d%c", length, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPSEND=%d, %d%c", linkID, length, CARRIAR_RETURN);
    }
    

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// UDP Transmission AT+CIPSENDEX=[<link ID>, ]<length>[, <remote IP>, <remote port>]
Void __esp8266_Send_AT_CIPSENDEX_UDP_cmd(
    _In_ UInt8  linkID, 
    _In_ UInt16 length,
    _In_ Char*  remoteIP, 
    _In_ UInt16 remote_port
) {
    Soft_Assert_Void(linkID <= 4, "Invalid linkID!");
    Soft_Assert_Void(length <= 2048, "Invalind parameter!");

    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        if (remoteIP != NULL) {
            sprintf((Char*)send_buf, "AT+CIPSEND=%d, %s, %d%c", length, remoteIP, remote_port, CARRIAR_RETURN);       
        }
        else {
            sprintf((Char*)send_buf, "AT+CIPSEND=%d%c", length, CARRIAR_RETURN);
        }
    }
    else {
        if (remoteIP != NULL) {
            sprintf((Char*)send_buf, "AT+CIPSEND=%d, %d, %s%d%c", linkID, length, remoteIP, remote_port, CARRIAR_RETURN);
        }
        else {
            sprintf((Char*)send_buf, "AT+CIPSEND=%d, %d%c", linkID, length, CARRIAR_RETURN);
        }
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief Write data into TCP-send-buffer
 * 
 * @attention This command only write data into TCP-send-buffer, so it can be called continually, needn’t wait for "SEND OK";  
 * if a TCP segment is sent successfully, it will return <segment ID>, SEND OK. 
 * Before data <length> is met, input "+++" can switch back from data mode to command mode, and discard the 
 * data received before, cancel the "AT+CIPSENDBUF". This command can NOT be used on SSL connection.
 * 
 * @param[in] linkID    ID of the connection (0~4), for multi-connect 
 * @param[in] length    data length, data more than <length> will be discarded, MAX 2048 bytes
 * 
 * @param[out] segmentID uint32, starts from 1, add 1 every time be called;
 * 
 * @note 
 * <current segment ID>, <segment ID of which sent successfully> 
 * OK 
 * > 
 * 
 * Wrap return ">" begins receiving of serial data, when data <length> is met, send it; data more than <length> will be discarded, and returns "busy" 
 * 
 * If connection cannot be established, or it’s not a TCP connection , or buffer full, or some other error occurred, returns ERROR 
 * 
 * If data is transmitted successfully,  
 * (1) for single connection, returns <segment ID>, SEND OK 
 * (2) for multiple connection, returns <link ID>, <segment ID>, SEND OK
*/
Void __esp8266_Send_AT_CIPSENDBUF_cmd(
    _In_ UInt8  linkID, 
    _In_ UInt16 length
) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPSENDBUF=%d%c", length, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPSENDBUF=%d, %d%c", linkID, length, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}





/**
 * @brief Check status of TCP-send-buffer
 * 
 * @attention Please do not user this command on SSL connection.
 * 
 * @note Response
 * <next segment ID>, < segment ID of which has sent >, < segment ID of which sent successfully>, <remain buffer size>, <queue number> 
 * OK 
 * 
 * If connection is not established, returns ERROR
*/
Void __esp8266_Send_AT_CIPBUFSTATUS_cmd(
    _In_ UInt16 linkID
) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPBUFSTATUS%c", linkID, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPBUFSTATUS=%d%c", linkID, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief Check if specific segment sent successfully or not
 * 
 * @param[in] segmentID SegmentID got by AT+CIPSENDBUF command 
 * @param[in] LinkID    ID of the connection (0~4), for multi-connect 
 * 
 * @note 
 * [<link ID>, ]<segment ID> , <status> 
 * 
 * OK 
 * 
 * If connection is not established, returns ERROR
 */
Void __esp8266_Send_AT_CIPBUFSTATUS_cmd(
    _In_ UInt16 linkID,
    _In_ UInt16 segmentID
) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPCHECKSEQ=%d%c", segmentID, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPCHECKSEQ=%d, %d%c", linkID, segmentID, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief  Reset segment ID count 
 * @param[in] linkID ID of the connection (0~4), for multi-connect
 * 
 * @note  This command can only be used if AT+CIPSENDBUF  is used
*/
Void __esp8266_Send_AT_CIPBUFSTATUS_cmd(
    _In_ UInt16 linkID
) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPCHECKSEQ%c", CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPBUFRESET=%d%c", linkID, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}


// Multiple connection AT+CIPCLOSE=<link ID>
// Response
// OK 
// or 
// ERROR

// Single connection AT+CIPCLOSE
// Response
// OK 
// or 
// If no such connection, returns 
// ERROR
Void __esp8266_Send_AT_CIPCLOSE_cmd(
    _In_ UInt16 linkID
) {
    UInt8 send_buf[15] = {0};

    if (single_connection == 1) {
        sprintf((Char*)send_buf, "AT+CIPCLOSE%c", CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPCLOSE=%d%c", linkID, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief  Get local IP address 
 * 
 * @note  Only after ESP8266 station connected to AP, station IP can be got and inquiried.
*/
Void __esp8266_Send_AT_CIFSR_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIFSR%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief multiple connections is enable or not
*/
Void __esp8266_Send_AT_CIFSR_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPMUX?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief Enable multiple connections 
 * 
 * @param[in] mode  
 * 0  single connection 
 * 1  multiple connection 
 * 
 * @note
 * 1. "AT+CIPMUX=1" can only be set when transparent transmission disabled ( "AT+CIPMODE=0") 
 * 2. This mode can only be changed after all connections are disconnected.  
 * 3. If TCP server is started, has to delete TCP server first, then change to single connection is allowed.
*/
Void __esp8266_Send_AT_CIFSR_set_cmd(Bool mode) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPMUX=%d%c", mode, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief  Configure as TCP server
 * 
 * @param[in] mode 
 * 0  Delete server  
 * 1  Create server 
 * @param[in] port port number, default is 333
 * 
 * @example  [AT+CIPMUX=1] [AT+CIPSERVER=1, 1001]
 * 
 * @note Server can only be created when AT+CIPMUX=1
*/
Void __esp8266_Send_AT_CIPSERVER_cmd(Bool mode, UInt16 port) {
    UInt8 send_buf[15] = {0};

    if (port == 333) {
        sprintf((Char*)send_buf, "AT+CIPMUX=%d, %d%c", mode, port, CARRIAR_RETURN);
    }
    else {
        sprintf((Char*)send_buf, "AT+CIPMUX=%d%c", mode, CARRIAR_RETURN);
    }
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief  get transfer mode
 * 
 * @note This configuration would NOT save into Flash.
*/
Void __esp8266_Send_AT_CIPMODE_get_cmd(Void) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPMODE?%c", CARRIAR_RETURN);   
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief  set transfer mode
 * 
 * @param[in] mode 
 * 0  normal mode  
 * 1  UART-WiFi passthrough mode
 * 
 * @attention 
 * UART-WiFi passthrough mode (transparent transmission) can only be enabled in TCP single connection mode or UDP of which remote IP and port won’t change (parameter <UDP mode> is 0 when using command "AT+CIPSTART" to create a UDP transmission).
 * During UART-WiFi passthrough transmission, if it is TCP connection and the TCP connection breaks, ESP8266 will keep trying to reconnect until "+++" is inputed to quit from transmission. 
 * After "+++", please wait at least 1 second before sending next AT command. If it is a normal TCP transmission and TCP connection breaks, ESP8266 will prompt " [<link ID>, ] 
 * CLOSED" , and won’t try to reconnect. Users can call "AT+CIPSTART" to create a connection again if it’s needed.
 * 
 * @note This configuration would NOT save into Flash.
*/
Void __esp8266_Send_AT_CIPMODE_set_cmd(Bool mode) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+CIPMODE=%d%c", mode, CARRIAR_RETURN);   
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}





// For TCP connection: 
// AT+SAVETRANSLINK =<mode>, <remote IP or domain name>, <remote port>[, <type>][, <TCP keep alive>] 
/**
 * @brief Save transparent transmission link to Flash
 * 
 * @param[in] mode 
 *              0 :  normal mode, cancel enter UART-WiFi passthrough mode when power on 
 *              1 :  save UART-WiFi passthrough mode 
 * 
 * @param[in] remote_IP      remote IP or domain name 
 * @param[in] remote_port    remote port 
 * 
 * @param[in] TCP_keep_alive TCP keep alive, default to be disabled 
 *              0: disable TCP keep alive 
 *              1 ~ 7200: keep-alive detect time interval, unit: second 
 * 
 * @example AT+SAVETRANSLINK=1, "192.168.6.110", 1002, "TCP"
 * 
 * @note 
 * This command will save the UART-WiFi passthrough mode and its link into Flash user parameter area, ESP8266 will enter UART-WiFi passthrough mode since next power on. 
 * As long as the IP (or domain name), port conformance to specification, we will save them to Flash
*/
Void __esp8266_Send_AT_SAVETRANSLINK_TCP_cmd(Bool mode, Char* remoteIP, UInt16 remote_port, UInt16 TCP_keep_alive) {
    UInt8 send_buf[15] = {0};
     
    sprintf((Char*)send_buf, "AT+CIPMODE=%d, \"%s\", %d, \"%s\", %d%c", mode, remoteIP, remote_port, "TCP",TCP_keep_alive, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




// For UDP transmission: 
// AT+SAVETRANSLINK =<mode>, <remote IP>, <remote port>[, <type>][, <UDP local port>]
/**
 * @brief Save transparent transmission link to Flash
 * 
 * @param[in] mode 
 *              0 :  normal mode, cancel enter UART-WiFi passthrough mode when power on 
 *              1 :  save UART-WiFi passthrough mode 
 * 
 * @param[in] remote_IP      remote IP or domain name 
 * @param[in] remote_port    remote port
 * 
 * @param[in] UDP_local_port local port if enter UDP transparent transmission when power on.
 * 
 * @note
 * This command will save the UART-WiFi passthrough mode and its link into Flash user parameter area, ESP8266 will enter UART-WiFi passthrough mode since next power on. 
 * As long as the IP (or domain name), port conformance to specification, we will save them to Flash
*/
Void __esp8266_Send_AT_SAVETRANSLINK_TCP_cmd(Bool mode, Char* remoteIP, UInt16 remote_port, UInt16 UDP_local_port) {
    UInt8 send_buf[15] = {0};
     
    sprintf((Char*)send_buf, "AT+CIPMODE=%d, \"%s\", %d, \"%s\", %d%c", mode, remoteIP, remote_port, "UDP", UDP_local_port, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CIPSTO?
Void __esp8266_Send_AT_CIPSTO_get_cmd(Void) {
    UInt8 send_buf[15] = {0};
     
    sprintf((Char*)send_buf, "AT+CIPSTO?%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CIPSTO=<time>
/**
 * @brief Set TCP server timeout
 * 
 * @param time TCP server timeout, range 0~7200 seconds 
 * 
 * @note  ESP8266 as TCP server, will disconnect to TCP client that didn’t communicate with it even if timeout. 
 * If AT+CIPSTO=0, it will never timeout. We don’t recommend that.
 * 
*/
Void __esp8266_Send_AT_CIPSTO_set_cmd(UInt16 time) {
    UInt8 send_buf[15] = {0};
     
    sprintf((Char*)send_buf, "AT+CIPSTO=%d%c", time, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief Function Ping 
 * 
 * @param[in] IP string, host IP or domain name 
*/
Void __esp8266_Send_AT_PING_cmd(Char* IP) {
    UInt8 send_buf[15] = {0};
     
    sprintf((Char*)send_buf, "AT+PING=\"%s\"%c", IP, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief Update through network
*/
Void __esp8266_Send_AT_CIUPDATE_cmd(Void) {
    UInt8 send_buf[15] = {0};
     
    sprintf((Char*)send_buf, "AT+CIUPDATE%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @brief Show remote IP and port with "+IPD"
 * Show remote IP and port with "+IPD" (received data from network)
 * 
 * @param mode 
 *          0: will not show remote IP and port with "+IPD" 
 *          1: show remote IP and port with "+IPD"
*/
Void __esp8266_Send_AT_CIPDINFO_cmd(Bool mode) {
    UInt8 send_buf[15] = {0};
     
    sprintf((Char*)send_buf, "AT+CIPDINFO=%d%c", mode, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}
