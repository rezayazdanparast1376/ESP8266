#include <stdint.h>
#include <stdbool.h>
#include "esp8266.h"
#include "../Common_C/defs.h"


#define ESP8266_PORT &huart2
Void esp8266_uart_send(UInt8* send_buf, size_t len) {
    HAL_UART_Transmit(ESP8266_PORT, send_buf, len, 1000);
}




Void init_esp8266(Void) {

}




Void parser_esp8266(Void) {
    //Respond basic command...
    /* [1] */
    // OK

    /* [2] */
    // <AT version info> 
    // <SDK version info> 
    // <compile time> 
    // OK


    /* [3] */
    // <time> 
    // OK


    /* [4] */
    // +SLEEP : <sleep mode> 
    // OK


    /* [5] */
    // +RFVDD:<VDD33> 
    // OK




    //Respond wifi command...
    /* [6] */
    // +CWMODE_CUR:( value scope of <mode>) 
    // OK

    /* [7] */
    // +CWMODE_CUR:<mode> 
    // OK

    /* [8] */
    // +CWMODE_DEF:( value scope of <mode>) 
    // OK

    /* [9] */
    // +CWMODE_DEF:<mode> 
    // OK

    /* [10] */
    // +CWJAP_CUR:<ssid>, <bssid>, <channel>, <rssi> 
    // OK

    /* [11] */
    // +CWJAP:<error code> 
    // FAIL

    /* [12] */
    // +CWJAP_DEF:<ssid>, <bssid>, <channel>, <rssi> 
    // OK

    /* [13] */
    // OK or ERROR

    /* [14] */
    // +CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration> 
    // OK 
    // ERROR

    /* [15] */
    // +CWSAP_CUR:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>

    /* [16] */
    // +CWSAP_DEF:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>

    /* [17] */
    // <IP addr>, <mac> 
    // OK

    /* [18] */
    // DHCP disabled or enabled now? [????]

    /* [19] */
    // +CWDHCPS_CUR=<lease time>, <start IP>, <end IP>

    /* [20] */
    // +CWDHCPS_DEF=<lease time>, <start IP>, <end IP>

    /* [21] */
    // +CIPSTAMAC_CUR:<mac> 
    // OK

    /* [22] */
    // +CIPSTAMAC_DEF:<mac> 
    // OK

    /* [23] */
    // +CIPAPMAC_CUR:<mac> 
    // OK

    /* [24] */
    // +CIPAPMAC_DEF:<mac> 
    // OK

    /* [25] */
    // +CIPSTA_CUR:<IP> 
    // OK

    /* [26] */
    // +CIPSTA:<IP> 
    // OK

    /* [27] */
    // +CIPAP_CUR:<IP> 
    // OK

    /* [28] */
    // +CIPAP_DEF:<IP> 
    // OK
}




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
    bool echo
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
Void __esp8266_Send_AT_CWJAP_CUR_get_cmd(
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
Void __esp8266_Send_AT_CWLAPOPT_set_cmd(bool sort_enable, UInt8 mask) {
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
Void __esp8266_Send_AT_CWDHCP_CUR_set_cmd(UInt8 mode, bool en) {
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
Void __esp8266_Send_AT_CWDHCP_DEF_set_cmd(UInt8 mode, bool en) {
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
Void __esp8266_Send_AT_CWDHCPS_CUR_set_cmd(bool enable, UInt16 lease_time, Char* startIP, Char* endIP) {
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
Void __esp8266_Send_AT_CWDHCPS_DEF_set_cmd(bool enable, UInt16 lease_time, Char* startIP, Char* endIP) {
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
Void __esp8266_Send_AT_CWAUTOCONN_set_cmd(bool enable) {
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
Void __esp8266_Send_AT_WPS_cmd(bool enable) {
    UInt8 send_buf[15] = {0};

    sprintf((Char*)send_buf, "AT+WPS=%d%c", enable, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+MDNS=<enable>, <hostname>, <server_name>, <server_port>
// Response OK or ERROR
Void __esp8266_Send_AT_MDNS_cmd(
    _In_ bool     enable, 
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

}




// Command AT+CIPDOMAIN=<domain name>
// Response +CIPDOMAIN:<IP address>
Void __esp8266_Send_AT_CIPDOMAIN_cmd(Char* domain_name) {

}




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










// Command
// AT+CIPSSLSIZE=<size>
// Response
// OK or ERROR





// Single connection (+CIPMUX=0) 
// AT+CIPSEND=<length>




// Multiple connection (+CIPMUX=1) 
// AT+CIPSEND=<link ID>, <length>



// UDP Transmission AT+CIPSEND=[<link ID>, ]<length>[, <remote IP>, <remote port>]




// Command AT+CIPSEND




// Single connection (+CIPMUX=0) 
// AT+CIPSENDEX=<length>



// Multiple connection (+CIPMUX=1) 
// AT+CIPSENDEX=<link ID>, <length>




// UDP Transmission AT+CIPSENDEX=[<link ID>, ]<length>[, <remote IP>, <remote port>]





// Single connection (+CIPMUX=0) 
// AT+CIPSENDBUF=<length>



// Multiple connection (+CIPMUX=1) 
// AT+CIPSENDBUF=<link ID>, <length>




// Single connection (+CIPMUX=0) 
// AT+CIPBUFSTATUS


// Multiple connection (+CIPMUX=1) 
// AT+CIPBUFSTATUS=<link ID>



// Single connection (+CIPMUX=0) 
// AT+CIPCHECKSEQ=<segment ID> 



// Multiple connection (+CIPMUX=1) 
// AT+CIPCHECKSEQ=<link ID>, <segment ID>



// Single connection (+CIPMUX=0) 
// AT+CIPBUFRESET




// Multiple connection (+CIPMUX=1) 
// AT+CIPBUFRESET=<link ID>


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






// Command AT+ CIFSR
// Response
// + CIFSR:<IP address> 
// OK 
// ERROR




// Command AT+CIPMUX?
// Response
// + CIPMUX:<mode> 
// OK




// Command AT+CIPMUX=<mode>
// Response
// OK 
// If already connected, returns 
// Link is builded





// Command AT+CIPSERVER=<mode>[, <port>]




// Command AT+CIPMODE?
// + CIPMODE:<mode> 
// Response
// OK




// Command AT+CIPMODE=<mode>
// Response
// OK 
// If already connected, returns 
// Link is builded





// For TCP connection: 
// AT+SAVETRANSLINK =<mode>, <remote IP or domain name>, <remote port>[, <type>][, <TCP keep alive>] 
// For UDP transmission: 
// AT+SAVETRANSLINK =<mode>, <remote IP>, <remote port>[, <type>][, <UDP local port>]





// Command AT+CIPSTO?




// Command AT+CIPSTO=<time>





// Command AT+PING=<IP>



// Command AT+CIUPDATE




// Command AT+CIPDINFO=<mode>





// Single connection
// (+CIPMUX=0) 
// +IPD, <len>[, <remote IP>, <remote port>]:<data>
// Multiple connection (+CIPMUX=1) 
// +IPD, <ID>, <len>[, <remote IP>, <remote port>]:<data>

