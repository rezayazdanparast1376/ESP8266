#include <stdint.h>
#include <stdbool.h>
#include "esp8266.h"


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
