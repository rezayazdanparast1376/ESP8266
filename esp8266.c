#include <stdint.h>
#include <stdbool.h>
#include "esp8266.h"
#define _In_
#define _Out_
#define _InOut_

#define ESP8266_PORT &huart2
void esp8266_uart_send(uint8_t* send_buf, size_t len) {
    HAL_UART_Transmit(ESP8266_PORT, send_buf, len, 1000);
}




void init_esp8266(void) {

}




void parser_esp8266(void) {
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
void __esp8266_Send_Test_AT_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * @addtogroup Basic_at_commands
 * 
*/
void __esp8266_Send_AT_RST_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+RST%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));   
}



/**
 * @addtogroup Basic_at_commands
 * 
*/
void __esp8266_Send_AT_GMR_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+GMR%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf)); 
}




// AT+GSLP
/**
 * @addtogroup Basic_at_commands
 * 
*/
void __esp8266_Send_AT_GSLP_cmd(uint16_t time) {
    uint8_t send_buf[15] = {0};
    sprintf((char*)send_buf, "AT+GSLP=%d%c", time, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf)); 
}




// ATE
/**
 * @addtogroup Basic_at_commands
 * 
*/
void __esp8266_Send_ATE_cmd(
    bool echo
) {
    uint8_t send_buf[15] = {0};
    
    if (echo == true) {
        sprintf((char*)send_buf, "ATE1%c", CARRIAR_RETURN);
    }
    else if (echo == false) {
        sprintf((char*)send_buf, "ATE0%c", CARRIAR_RETURN);
    }
    
    esp8266_uart_send(send_buf, strlen(send_buf)); 
}




// AT+RESTORE
/**
 * @addtogroup Basic_at_commands
 * 
*/
void __esp8266_Send_AT_RESTORE_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+RESTORE%c", CARRIAR_RETURN);

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
void __esp8266_Send_AT_UART_CUR_cmd(
    uint16_t baudrate, 
    uint8_t  databits, 
    uint8_t  stopbits, 
    uint8_t  parity, 
    uint8_t  flow_control
) {

    uint8_t send_buf[35] = {0};

    sprintf((char*)send_buf, "AT+UART_CUR=%d, %d, %d, %d, %d%c", baudrate, databits, stopbits, parity, flow_control, CARRIAR_RETURN);

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
void __esp8266_Send_AT_UART_DEF_cmd(
    uint16_t baudrate, 
    uint8_t  databits, 
    uint8_t  stopbits, 
    uint8_t  parity, 
    uint8_t  flow_control
) {
    uint8_t send_buf[35] = {0};

    sprintf((char*)send_buf, "AT+UART_DEF=%d, %d, %d, %d, %d%c", baudrate, databits, stopbits, parity, flow_control, CARRIAR_RETURN);

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
void __esp8266_Send_AT_SLEEP_req_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+SLEEP?%c", CARRIAR_RETURN);

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
void __esp8266_Send_AT_SLEEP_set_cmd(
    uint8_t sleep_mode
) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+SLEEP=%d%c", sleep_mode, CARRIAR_RETURN);

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
void __esp8266_Send_AT_RFPOWER_set_cmd(
    uint8_t tx_power
) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+RFPOWER=%d%c", tx_power, CARRIAR_RETURN);

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
void __esp8266_Send_AT_RFVDD_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+RFVDD?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}


/**
 * @addtogroup Basic_at_commands
 * 
 * @brief  AT+RFVDD=<VDD33>
 * @param VDD33 <VDD33> power voltage of ESP8266 VDD33, range [1900, 3300]
*/
void __esp8266_Send_AT_RFVDD_set_cmd(
    uint16_t VDD33
) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+RFVDD=%d%c", VDD33, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// AT+RFVDD
/**
 * @addtogroup Basic_at_commands
 * @brief AT+RFVDD
 * @note  "AT+RFVDD" will automatically set RF TX power according to VDD33. TOUT pin has to be suspended. 
*/
void __esp8266_Send_AT_RFVDD_req_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+RFVDD%c", CARRIAR_RETURN);

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
void __esp8266_Send_AT_CWMODE_CUR_req_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWMODE_CUR=?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}


/**
 * Command AT+CWMODE_CUR?
 * Response
 * +CWMODE_CUR:<mode> 
 * OK
*/
void __esp8266_Send_AT_CWMODE_CUR_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWMODE_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



 

/**
 * Command AT+CWMODE_CUR=<mode>
 * Response OK
*/
void __esp8266_Send_AT_CWMODE_CUR_set_cmd(uint8_t mode) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWMODE_CUR=%d%c", mode, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * Command AT+CWMODE_DEF=?
 * Response
 * +CWMODE_DEF:( value scope of <mode>) 
 * OK
*/
void __esp8266_Send_AT_CWMODE_DEF_req_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWMODE_DEF=?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




/**
 * Command AT+CWMODE_DEF?
 * Response
 * +CWMODE_DEF:<mode> 
 * OK
*/
void __esp8266_Send_AT_CWMODE_DEF_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWMODE_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



/**
 * Command AT+CWMODE_DEF=<mode>
 * Response OK
*/
void __esp8266_Send_AT_CWMODE_DEF_set_cmd(uint8_t mode) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWMODE_DEF?%d%c", mode, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



/**
 * Command AT+CWJAP_CUR?
 * Response
 * +CWJAP_CUR:<ssid>, <bssid>, <channel>, <rssi> 
 * OK
*/
void __esp8266_Send_AT_CWJAP_CUR_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWJAP_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWJAP_CUR=<ssid>, <pwd>[, <bssid>]
// Response
// OK 
// or 
// +CWJAP:<error code> 
// FAIL
void __esp8266_Send_AT_CWJAP_CUR_get_cmd(
    char* ssid, 
    char* pwd, 
    char* bssid
) {
    uint8_t send_buf[35] = {0};

    if (bssid == NULL) {
        sprintf((char*)send_buf, "AT+CWJAP_CUR=%s, %s%c", ssid, pwd, CARRIAR_RETURN);
    }
    else {
        sprintf((char*)send_buf, "AT+CWJAP_CUR=%s, %s, %s%c", ssid, pwd, bssid, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWJAP_DEF?
// Response
// +CWJAP_DEF:<ssid>, <bssid>, <channel>, <rssi> 
// OK
void __esp8266_Send_AT_CWJAP_DEF_get_cmd() {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWJAP_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWJAP_DEF=<ssid>, <pwd>[, <bssid>]
// Response
// OK 
// or 
// +CWJAP:<error code> 
// FAIL
void __esp8266_Send_AT_CWJAP_DEF_set_cmd(
    char* ssid, 
    char* pwd, 
    char* bssid
) {
    uint8_t send_buf[15] = {0};

    if (bssid == NULL) {
        sprintf((char*)send_buf, "AT+CWJAP_DEF=%s, %s%c", CARRIAR_RETURN);
    }
    else {
        sprintf((char*)send_buf, "AT+CWJAP_DEF=%s, %s, %s%c", CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}






//  Command AT+CWLAPOPT=<sort_enable>, <mask>
//  Response OK or ERROR
void __esp8266_Send_AT_CWLAPOPT_set_cmd(bool sort_enable, uint8_t mask) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWLAPOPT=%d, %d%c", sort_enable, mask, CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWLAP=<ssid>[, <mac>, <ch>]
// Response
// +CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration> 
// OK 
// ERROR
void __esp8266_Send_AT_CWLAP_set_cmd(char* ssid, char* mac, char* ch) {
    uint8_t send_buf[35] = {0};

    if (mac == NULL && ch == NULL) {
        sprintf((char*)send_buf, "AT+CWLAP=%s%c", ssid, CARRIAR_RETURN);
    }
    else if (mac != NULL && ch == NULL) {
        sprintf((char*)send_buf, "AT+CWLAP=%s, %s%c", ssid, mac, CARRIAR_RETURN);
    }
    else {
        sprintf((char*)send_buf, "AT+CWLAP=%s, %s, %d%c", ssid, mac, ch, CARRIAR_RETURN);
    } 

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWLAP
// Response
// +CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration> 
// OK 
// ERROR
void __esp8266_Send_AT_CWLAP_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWLAP%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWQAP
void __esp8266_Send_AT_CWQAP_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWQAP%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



//  Command AT+CWSAP_CUR?
//  Response +CWSAP_CUR:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>
void __esp8266_Send_AT_CWSAP_CUR_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWSAP_CUR?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWSAP_CUR=<ssid>, <pwd>, <chl>, <ecn>[, <max conn>][, <ssid hidden>]
// Response OK 
// ERROR
void __esp8266_Send_AT_CWSAP_CUR_set_cmd(
    _In_ char*    ssid, 
    _In_ char*    pwd, 
    _In_ uint8_t  chl, 
    _In_ uint8_t  ecn, 
    _In_ uint8_t* max_conn, 
    _In_ uint8_t* ssid_hidden
) {
    uint8_t send_buf[15] = {0};

    if (max_conn == NULL || ssid_hidden == NULL) {
        sprintf((char*)send_buf, "AT+CWSAP_CUR=%s, %s, %d, %d%c", ssid, pwd, chl, ecn, CARRIAR_RETURN);
    }
    else {
        sprintf((char*)send_buf, "AT+CWSAP_CUR=%s, %s, %d, %d, %d, %d%c", ssid, pwd, chl, ecn, max_conn, ssid_hidden, CARRIAR_RETURN);
    }

    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWSAP_DEF?
// Response +CWSAP_DEF:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>
void __esp8266_Send_AT_CWSAP_DEF_get_cmd() {
    uint8_t send_buf[15] = {0};
    
    sprintf((char*)send_buf, "AT+CWSAP_DEF?%c", CARRIAR_RETURN);

    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWSAP_DEF=<ssid>, <pwd>, <chl>, <ecn>[, <max conn>][, <ssid hidden>]
// Response OK 
// ERROR
void __esp8266_Send_AT_CWSAP_DEF_set_cmd(
    _In_ char*   ssid, 
    _In_ char*   pwd, 
    _In_ uint8_t chl, 
    _In_ uint8_t ecn, 
    _In_ char*   max_conn, 
    _In_ char*   ssid_hidden
) {
    uint8_t send_buf[15] = {0};
    
    if (max_conn != NULL && ssid_hidden != NULL) {
        sprintf((char*)send_buf, "AT+CWSAP_DEF=%s, %s, %d, %d, %s, %s%c", ssid, pwd, chl, ecn, max_conn, ssid_hidden, CARRIAR_RETURN);
    }
    else {
        sprintf((char*)send_buf, "AT+CWSAP_DEF=%s, %s, %d, %d%c", ssid, pwd, chl, ecn, CARRIAR_RETURN);
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
 *  Response
 *  <IP addr>, <mac>
 *  OK
*/
void __esp8266_Send_AT_CWLIF_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWLIF%c", CARRIAR_RETURN);
    
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
void __esp8266_Send_AT_CWDHCP_CUR_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWDHCP_CUR?%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
} 
 

// Command AT+CWDHCP_CUR=<mode>, <en>
// Response OK
void __esp8266_Send_AT_CWDHCP_CUR_set_cmd(uint8_t mode, bool en) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWDHCP_CUR=%d, %d%c",mode, en, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}




// Command AT+CWDHCP_DEF?
// Response DHCP disabled or enabled now?
void __esp8266_Send_AT_CWDHCP_DEF_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWDHCP_DEF?%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}



// Command AT+CWDHCP_DEF=<mode>, <en>
// Response OK
void __esp8266_Send_AT_CWDHCP_DEF_set_cmd(uint8_t mode, bool en) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWDHCP_DEF=%d, %d%c",mode, en, CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWDHCPS_CUR?
// Response +CWDHCPS_CUR=<lease time>, <start IP>, <end IP>
void __esp8266_Send_AT_CWDHCPS_CUR_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWDHCPS_CUR?%c", CARRIAR_RETURN);
    
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
void __esp8266_Send_AT_CWDHCPS_CUR_set_cmd(bool enable, uint16_t lease_time, char* startIP, char* endIP) {
    uint8_t send_buf[15] = {0};

    if (enable == true) {
        sprintf((char*)send_buf, "AT+CWDHCPS_CUR=%d, %d, %s, %s%c", CARRIAR_RETURN);
    }
    else {
        sprintf((char*)send_buf, "AT+CWDHCPS_CUR=0%c", CARRIAR_RETURN);
    }
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}





// Command AT+CWDHCPS_DEF?
// Response +CWDHCPS_DEF=<lease time>, <start IP>, <end IP>
void __esp8266_Send_AT_CWDHCPS_CUR_get_cmd(void) {
    uint8_t send_buf[15] = {0};

    sprintf((char*)send_buf, "AT+CWDHCPS_DEF?%c", CARRIAR_RETURN);
    
    esp8266_uart_send(send_buf, strlen(send_buf));
}


// Command AT+CWDHCPS_DEF=<enable>, <lease time>, <start IP>, <end IP>
// Response OK
void __esp8266_Send_AT_CWDHCPS_CUR_set_cmd(bool enable, uint16_t lease_time, char* startIP, char* endIP) {
    uint8_t send_buf[15] = {0};

    if (enable == true) {
        sprintf((char*)send_buf, "AT+CWDHCPS_DEF=%d, %d, %s, %s%c", CARRIAR_RETURN);
    }
    else {
        sprintf((char*)send_buf, "AT+CWDHCPS_DEF=0%c", CARRIAR_RETURN);
    }
    
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