#include "esp8266.h"
#include <string.h>
#include "esp8266_receive_respond.h"
#include "debug.h"
#include "defs.h"


Void cipsta_parser(UInt8* str);
Void cipap_parser(UInt8* str);
Void cip_status_parser(UInt8* str);
Void cipdomain_parser(UInt8* str);
Void cipmux_parser(UInt8* str);
Void cipmode_parser(UInt8* str);
Void cipsto_parser(UInt8* str);
Void cip_parser(UInt8* str);



Void rf_voltage_parser(UInt8* str);
Void ip_address_parser(UInt8* str);
Void sleep_parser(UInt8* str);
Void update_parser(UInt8* str);
Void ping_parser(UInt8* str);

Void cw_parser(UInt8* str);

Void ipd_parser(_In_  UInt8*  str /* , _Out_ UInt16* len */);

ESP8266_RESPONCE esp8266_responce = ESP8266_NO_RESPONCE;


Bool send_data_flag              = False;
Bool err_ok_flag                 = False;
Bool version_flag                = False;
Bool time_flag                   = False;
Bool ip_mac_flag                 = False;
Bool dhcp_flag                   = False;
Bool connection_flag             = False;
Bool tcp_send_buffer_status_flag = False;
Bool specific_tcp_segment_flag   = False;


Void send_data_parser(UInt8 receive_byte) {
    /* [32] */
    // ">"
    // ERROR
    // SEND OK

    
    /* [33] */
    // ">"
    // +++

    /* [34] */
    // <current segment ID>, <segment ID of which sent successfully> 
    // OK 
    // > 

    // "busy" // ERROR  // <segment ID>, SEND OK    // <link ID>, <segment ID>, SEND OK
}



ESP8266_ERR_OK_MSG err_ok_state = WAIT_FOR_FRAME;

Void err_ok_parser(UInt8 receive_byte) {
    static UInt8 receiver_counter = 0;
    switch (err_ok_state) {
        case WAIT_FOR_FRAME:
            if (receive_byte == 'O' && receiver_counter == 0) {
                receiver_counter++;
                err_ok_state = O_RECEIVED;
            }
            else if (receive_byte == 'E' && receiver_counter == 0) {
                receiver_counter++;         //receiver counter: 1
                err_ok_state = WAIT_FOR_R;
            }
            else {
                receiver_counter = 0;
                err_ok_state     = WAIT_FOR_FRAME;
            }
            break;
        case O_RECEIVED:
            if (receive_byte == 'K' && receiver_counter == 1) {
                esp8266_responce = ESP8266_OK_RESPONCE;                // OK received ...
                err_ok_flag      = False;
                // debug_info(&DEBUG_PORT, "[esp8266 parser] receive OK from esp8266.");
            }
            err_ok_state     = WAIT_FOR_FRAME;
            receiver_counter = 0;
            break;
            case WAIT_FOR_R:
            if (receive_byte == 'R' && receiver_counter <= 2) {
                receiver_counter++;
            }
            else if (receive_byte == 'O' && receiver_counter == 3) {
                receiver_counter ++;
            }
            else if (receive_byte == 'R' && receiver_counter == 4) {
                esp8266_responce = ESP8266_ERROR_RESPONCE;          // ERROR received ...
                err_ok_flag      = False;
                debug_info(&DEBUG_PORT, "[esp8266 parser] receive ERROR from esp8266.");
            }
            else {
                err_ok_state     = WAIT_FOR_FRAME;
                receiver_counter = 0;
            }
            break;
        default:
            receiver_counter = 0;
            err_ok_state     = WAIT_FOR_FRAME;
            break;
    }
    /* [1] */
    // OK

    /* [13] */
    // OK or ERROR
}







Char __at_version[35]   = {0};
Char __sdk_version[35]  = {0};
Char __compile_time[35] = {0};
ESP8266_VERSION_MSG version_msg_state = WATIE_FOR_VERSION_FRAME;
Void version_parser(UInt8 receive_byte) {
    static UInt8 receiver_counter = 0;
    switch (version_msg_state) {
        case WATIE_FOR_VERSION_FRAME:
            if (receive_byte == 'A')        version_msg_state = WATIE_FOR_AT_VERSION;
            else if (receive_byte == 'S')   version_msg_state = WATIE_FOR_SDK_VERSION;
            else if (receive_byte == 'c')   version_msg_state = WATIE_FOR_COMPILE_TIME;
            break;
        case WATIE_FOR_AT_VERSION:
            if (receive_byte == ':')    version_msg_state = SAVE_AT_VERSION;
            break;
        case WATIE_FOR_SDK_VERSION:
            if (receive_byte == ':')    version_msg_state = SAVE_SKD_VERSON;           
            break;
        case WATIE_FOR_COMPILE_TIME:
            if (receive_byte == ':')    version_msg_state = SAVE_COMPILE_TIME;
            break;
        case SAVE_AT_VERSION:
            if (receive_byte == '\n' || receive_byte == '\r') {
                receiver_counter  = 0;
                version_msg_state = WATIE_FOR_VERSION_FRAME;
            }
            else {
                __at_version[receiver_counter] = receive_byte;      //save data ...
                receiver_counter++;
            }
            break;
        case SAVE_SKD_VERSON:
            if (receive_byte == '\n' || receive_byte == '\r') {
                receiver_counter  = 0;
                version_msg_state = WATIE_FOR_VERSION_FRAME;
            }
            else {
                __sdk_version[receiver_counter] = receive_byte;     //save data ...
                receiver_counter++;
            }
            break;
        case SAVE_COMPILE_TIME:
            if (receive_byte == '\n' || receive_byte == '\r') {
                receiver_counter  = 0;
                version_msg_state = WATIE_FOR_VERSION_FRAME;
            }
            else {
                __compile_time[receiver_counter] = receive_byte;    //save data ...
                receiver_counter++;
            }
            break;
        default:
            break;
    }


    // AT version:1.7.4.0(Jul  8 2020 15:53:04)
    // SDK version:3.0.5-dev(52383f9)
    // compile time:Aug 28 2020 14:37:33
    // OK


    /* [2] */
    // <AT version info> 
    // <SDK version info> 
    // <compile time> 
    // OK
}

Void time_parser(UInt8 receive_byte) {
    /* [3] */
    // <time> 
    // OK
}

Void ip_mac_parser(UInt8 receive_byte) {   
    /* [17] */
    // <IP addr>, <mac> 
    // OK
}

Void dhcp_parser(UInt8 receive_byte) {
    /* [18] */
    // DHCP disabled or enabled now? [????]
}

Void connection_parser(UInt8 receive_byte) {
    /* [31] */
    // ALREADY CONNECT
    // OK or ERROR
}    


Void tcp_send_buffer_status_parser(UInt8 receive_byte) {
    /* [35] */
    // <next segment ID>, < segment ID of which has sent >, < segment ID of which sent successfully>, <remain buffer size>, <queue number> 
    // OK 

    // ERROR
}

Void specific_tcp_segment_parser(UInt8 receive_byte) {
    /* [36] */
    // [<link ID>, ]<segment ID> , <status> 
    // OK 
    // If connection is not established, returns 
    // ERROR
}





Void request_parser(UInt8 receive_byte) {
    if (send_data_flag == True) {
        send_data_parser(receive_byte);
        send_data_flag = 0;
    }
    if (err_ok_flag == True) {
        err_ok_parser(receive_byte);
        // err_ok_flag = 0;
    }
    if (version_flag == True) {
        // debug_info(&DEBUG_PORT, "version parser ...");
        version_parser(receive_byte);
        // version_flag = 0;
    }
    if (time_flag == True) {
        time_parser(receive_byte);
        time_flag = 0;
    }
    if (ip_mac_flag == True) {
        ip_mac_parser(receive_byte);
        ip_mac_flag = 0;
    }
    if (dhcp_flag == True) {
        dhcp_parser(receive_byte);
        dhcp_flag = 0;
    }
    if (connection_flag == True) {
        connection_parser(receive_byte);
        connection_flag = 0;
    }
    if (tcp_send_buffer_status_flag == True) {
        tcp_send_buffer_status_parser(receive_byte);
        tcp_send_buffer_status_flag = 0;
    }
    if (specific_tcp_segment_flag == True) {   
        specific_tcp_segment_parser(receive_byte);
        specific_tcp_segment_flag = 0;
    }
}




ESP8266_PLUS_MSG esp8266_plus_msg = WAIT_FOR_PLUS;

UInt8 CW_frame[15]       = {0};
UInt8 CIP_frame[15]      = {0};
UInt8 CIUPDATE_frame[15] = {0}; 
UInt8 CIFSR_frame[15]    = {0};
UInt8 SLEEP_frame[15]    = {0};
UInt8 RFVDD_frame[15]    = {0};
UInt8 time_frame[15]     = {0}; 
UInt8 IPD_frame[15]      = {0};

UInt8 plus_frame[100] = {0};
UInt16 rx_byte_counter = 0;
Void plus_parser(UInt8 receive_byte) {
    switch (esp8266_plus_msg) {
        case WAIT_FOR_PLUS:
            if (receive_byte == '+') {
                esp8266_plus_msg = PLUS_RECEIVED;
            }
            break;
        case PLUS_RECEIVED:
            if (receive_byte == 'C') {
                esp8266_plus_msg = C_RECEIVED;
            }
            else if (receive_byte == 'S') {                 //+SLEEP
                SLEEP_frame[rx_byte_counter] = receive_byte;// save sleep frame
                rx_byte_counter++;
                if (receive_byte == CARRIAR_RETURN) {
                    rx_byte_counter = 0;
                    sleep_parser(SLEEP_frame);             // parse sleep frame
                    esp8266_plus_msg = WAIT_FOR_PLUS;
                }
            }
            else if (receive_byte == 'R') {
                RFVDD_frame[rx_byte_counter] = receive_byte;
                rx_byte_counter++;
                if (receive_byte == CARRIAR_RETURN) {
                    rx_byte_counter = 0;
                    rf_voltage_parser(RFVDD_frame);        //+RFVDD
                    esp8266_plus_msg = WAIT_FOR_PLUS;
                }
            }
            else if (receive_byte == 'I') {
                IPD_frame[rx_byte_counter] = receive_byte;
                rx_byte_counter++;
                if (receive_byte == CARRIAR_RETURN) {
                    rx_byte_counter = 0;
                    ipd_parser(IPD_frame);               // +IPD
                    esp8266_plus_msg = WAIT_FOR_PLUS;
                }
            }
            else {
                time_frame[rx_byte_counter] = receive_byte;
                rx_byte_counter++;
                if (receive_byte == CARRIAR_RETURN) {
                    rx_byte_counter = 0;
                    ping_parser(time_frame);              // +<time> 
                    esp8266_plus_msg = WAIT_FOR_PLUS;
                }
            }
            break;
        case C_RECEIVED:
            if (receive_byte == 'W') {
                esp8266_plus_msg = CW_RECEIVED;
            }
            if (receive_byte == 'I') {
                esp8266_plus_msg = CI_RECEIVED;
            }
            break;
        case CW_RECEIVED:
                CW_frame[rx_byte_counter] = receive_byte;
                rx_byte_counter++;
                if (receive_byte == CARRIAR_RETURN) {
                    rx_byte_counter = 0;
                    cw_parser(CW_frame);            //+CW
                    esp8266_plus_msg = WAIT_FOR_PLUS;
                }
            break;
        case CI_RECEIVED:
            if (receive_byte == 'P') {
                CIP_frame[rx_byte_counter] = receive_byte;
                rx_byte_counter++;
                if (receive_byte == CARRIAR_RETURN) {
                    rx_byte_counter = 0;
                    cip_parser(CIP_frame);           //+CIP
                    esp8266_plus_msg = WAIT_FOR_PLUS;
                }
            }
            else if (receive_byte == 'U') {
                CIUPDATE_frame[rx_byte_counter] = receive_byte;
                rx_byte_counter++;
                if (receive_byte == CARRIAR_RETURN) {
                    rx_byte_counter = 0;
                    update_parser(CIUPDATE_frame);        //+CIUPDATE:<n> 
                    esp8266_plus_msg = WAIT_FOR_PLUS;
                }
            }
            else if (receive_byte == 'F') {
                CIFSR_frame[rx_byte_counter] = receive_byte;
                rx_byte_counter++;
                if (receive_byte == CARRIAR_RETURN) {
                    rx_byte_counter = 0;
                    ip_address_parser(CIFSR_frame);    //+ CIFSR
                    esp8266_plus_msg = WAIT_FOR_PLUS;
                }
            }
            break;
        default:
            break;
    }
}




Void rf_voltage_parser(UInt8* str) {
    /* [5] */
    // +RFVDD:<VDD33> 
    // OK
}

Void ip_address_parser(UInt8* str) {
    /* [37] */
    // + CIFSR:<IP address> 
    // OK 
    // ERROR
}

Void sleep_parser(UInt8* str) {
    /* [4] */
    // +SLEEP : <sleep mode> 
    // OK
}


Void update_parser(UInt8* str) {
    /* [43] */
    // +CIUPDATE:<n> 
    // OK
}

Void ping_parser(UInt8* str) {
    /* [42] */
    // +<time> 
    // OK 
    // Or 
    // ERROR // means ping fail
}


typedef struct IPD_PACKET_t {
    UInt16  len;
    Char    remoteIP[16];
    UInt16  remote_port;
    Char    data[100];
}IPD_PACKET;


Void ipd_parser(_In_  UInt8*  str /* , _Out_ UInt16* len */) {
    
    /* [44] */
    // Single connection
    // (+CIPMUX=0) 
    // +IPD, <len>[, <remote IP>, <remote port>]:<data>

    // Multiple connection (+CIPMUX=1) 
    // +IPD, <ID>, <len>[, <remote IP>, <remote port>]:<data>
}


// =======================================================================================================================================
// ============================================================== CW PARSER ==============================================================
// =======================================================================================================================================
ESP8266_WIFI_MODE __wifi_mode_cur = WIFI_MODE_UNKNOWN;
ESP8266_WIFI_MODE __wifi_mode_def = WIFI_MODE_UNKNOWN;
Void cwmode_parser(UInt8* str) {
    if (strncmp((const Char*)str, "MODE_CUR:", strlen("MODE_CUR:")) == 0) {
        // debug_info(&DEBUG_PORT, "1_ CW MODE CUR parser ...");
        if (*(str + strlen("MODE_CUR:")) == '1') {
            __wifi_mode_cur = WIFI_MODE_STATION;
        }
        else if (*(str + strlen("MODE_CUR:")) == '2') {
            __wifi_mode_cur = WIFI_MODE_ACSESS_POINT;
        }
        else if (*(str + strlen("MODE_CUR:")) == '3') {
            __wifi_mode_cur = WIFI_MODE_STATION_ACSESS_POINT;
        }
        else {
            __wifi_mode_cur = WIFI_MODE_UNKNOWN;
        }
    }
    else if (strncmp((const Char*)str, "MODE_DEF:", strlen("MODE_DEF:")) == 0) {
        // debug_info(&DEBUG_PORT, "2_ CW MODE DEF parser ...");
        if (*(str + strlen("MODE_DEF:")) == '1') {
            __wifi_mode_def = WIFI_MODE_STATION;
        }
        else if (*(str + strlen("MODE_DEF:")) == '2') {
            __wifi_mode_def = WIFI_MODE_ACSESS_POINT;
        }
        else if (*(str + strlen("MODE_DEF:")) == '3') {
            __wifi_mode_def = WIFI_MODE_STATION_ACSESS_POINT;
        }
        else {
            __wifi_mode_def = WIFI_MODE_UNKNOWN;
        }
    }
    else if (strncmp((const Char*)str, "MODE_CUR:(", strlen("MODE_CUR:(")) == 0) {
        debug_info(&DEBUG_PORT, "3_ CW MODE CUR( parser ...");
    }
    else if (strncmp((const Char*)str, "MODE_DEF:(", strlen("MODE_DEF:(")) == 0) {
        debug_info(&DEBUG_PORT, "4_ CW MODE DEF( parser ...");
    }
    else {
        debug_info(&DEBUG_PORT, "error in cw mode parser!");
    }
    
    
    
    
    
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
}


Void cwjap_purser(UInt8* str) {
    /* [10] */
    // +CWJAP_CUR:<ssid>, <bssid>, <channel>, <rssi> 
    // OK

    /* [11] */
    // +CWJAP:<error code> 
    // FAIL

    /* [12] */
    // +CWJAP_DEF:<ssid>, <bssid>, <channel>, <rssi> 
    // OK
}

Void cwlap_purser(UInt8* str) {
    /* [14] */
    // +CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration> 
    // OK 
    // ERROR
}


Void cwsap_purser(UInt8* str) {
    /* [15] */
    // +CWSAP_CUR:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>

    /* [16] */
    // +CWSAP_DEF:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>
}

Void cwdhcps_purser(UInt8* str) {
    /* [19] */
    // +CWDHCPS_CUR=<lease time>, <start IP>, <end IP>

    /* [20] */
    // +CWDHCPS_DEF=<lease time>, <start IP>, <end IP>
}


ESP8266_CW_MSG cw_msg_state = WAIT_FOR_CW_MSG_FRAME;
Void cw_parser(UInt8* str) {
    // debug_info(&DEBUG_PORT, "cw parser ...");

    if (strncmp((const Char*)str, "MODE", strlen("MODE")) == 0) {
        // debug_info(&DEBUG_PORT, "CW MODE parser ...");
        cwmode_parser(str);    // +CWMODE
    }
    else if (strncmp((const Char*)str, "JAP", strlen("JAP")) == 0) {
        cwjap_purser(str);     // +CWJAP
    }
    else if (strncmp((const Char*)str, "LAP", strlen("LAP")) == 0) {
        cwlap_purser(str);     // +CWLAP
    }
    else if (strncmp((const Char*)str, "SAP", strlen("SAP")) == 0) {
        cwsap_purser(str);     // +CWSAP
    }
    else if (strncmp((const Char*)str, "DHCPS", strlen("DHCPS")) == 0) {
        cwdhcps_purser(str);   // +CWDHCPS
    }
}

// =========================================================================================================================================
// ============================================================== END CW PARSER ============================================================
// =========================================================================================================================================




// ***************************************************************************************************************************************************************************
// ***************************************************************************************************************************************************************************
// ***************************************************************************************************************************************************************************




// =======================================================================================================================================
// ============================================================== CIP PARSER ==============================================================
// =======================================================================================================================================




Void cipsta_parser(UInt8* str) {
    /* [21] */
    // +CIPSTAMAC_CUR:<mac> 
    // OK

    /* [22] */
    // +CIPSTAMAC_DEF:<mac> 
    // OK

    /* [25] */
    // +CIPSTA_CUR:<IP> 
    // OK

    /* [26] */
    // +CIPSTA:<IP> 
    // OK
}

Void cipap_parser(UInt8* str) {
    /* [23] */
    // +CIPAPMAC_CUR:<mac> 
    // OK

    /* [24] */
    // +CIPAPMAC_DEF:<mac> 
    // OK

    /* [27] */
    // +CIPAP_CUR:<IP> 
    // OK

    /* [28] */
    // +CIPAP_DEF:<IP> 
    // OK
}


Void cip_status_parser(UInt8* str) {
    /* [29] */
    // STATUS:<stat> 
    // +CIPSTATUS:<link ID>, <type>, <remote_IP>, <remote_port>, <local_port>,  <tetype>
}


Void cipdomain_parser(UInt8* str) {
    /* [30] */
    // +CIPDOMAIN:<IP address>
}

Void cipmux_parser(UInt8* str) {
    /* [38] */
    // + CIPMUX:<mode> 
    // OK
}

Void cipmode_parser(UInt8* str) {
    /* [39] */
    // +CIPMODE:<mode> 
    // OK
}

Void cipsto_parser(UInt8* str) {
    /* [41] */
    // + CIPSTO:<time> 
    // OK
}

Void cip_parser(UInt8* str) {

    
    if (strncmp((const char*)str, "PSTA", strlen("PSTA")) == 0) {
        cipsta_parser(str);        //+CIPSTA
    }
    else if (strncmp((const Char*)str, "PAP", strlen("PAP")) == 0) {
        cipap_parser(str);         //+CIPAP
    }
    else if (strncmp((const char*)str, "PSTATUS", strlen("PSTATUS")) == 0) {
        cip_status_parser(str);    //+CIPSTATUS
    }    
    else if (strncmp((const char*)str, "PDOMAIN", strlen("PDOMAIN")) == 0) {
        cipdomain_parser(str);     // +CIPDOMAIN   
    }    
    else if (strncmp((const char*)str, "PMODE", strlen("PMODE")) == 0) {
        cipmode_parser(str);       //+CIPMODE
    }
    else if (strncmp((const char*)str, "PSTO", strlen("PSTO")) == 0) {
        cipsto_parser(str);        //+ CIPSTO
    }
}


// ============================================================================================================================================
// ============================================================== END CIP PARSER ==============================================================
// ============================================================================================================================================

