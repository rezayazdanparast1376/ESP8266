#include "esp8266.h"



Void send_data_parser(Void) {
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

    
Void err_ok_parser(Void) {
    /* [1] */
    // OK

    /* [13] */
    // OK or ERROR
}

Void version_parser(Void) {
    /* [2] */
    // <AT version info> 
    // <SDK version info> 
    // <compile time> 
    // OK
}

Void time_parser(Void) {
    /* [3] */
    // <time> 
    // OK
}

Void ip_mac_parser(Void) {   
    /* [17] */
    // <IP addr>, <mac> 
    // OK
}

Void dhcp_parser(Void) {
    /* [18] */
    // DHCP disabled or enabled now? [????]
}

Void connection_parser(Void) {
    /* [31] */
    // ALREADY CONNECT
    // OK or ERROR
}    


Void tcp_send_buffer_status_parser(Void) {
    /* [35] */
    // <next segment ID>, < segment ID of which has sent >, < segment ID of which sent successfully>, <remain buffer size>, <queue number> 
    // OK 

    // ERROR
}

Void specific_tcp_segment_parser() {
    /* [36] */
    // [<link ID>, ]<segment ID> , <status> 
    // OK 
    // If connection is not established, returns 
    // ERROR
}



Bool send_data_flag              = 0;
Bool err_ok_flag                 = 0;
Bool version_flag                = 0;
Bool time_flag                   = 0;
Bool ip_mac_flag                 = 0;
Bool dhcp_flag                   = 0;
Bool connection_flag             = 0;
Bool tcp_send_buffer_status_flag = 0;
Bool specific_tcp_segment_flag   = 0;

Void request_parser(UInt8 receive_byte) {
    if (send_data_flag == 1) {
        send_data_parser();
        send_data_flag = 0;
    }
    if (err_ok_flag == 1) {
        err_ok_parser();
        err_ok_flag = 0;
    }
    if (version_flag == 1) {
        version_parser();
        version_flag = 0;
    }
    if (time_flag == 1) {
        time_parser();
        time_flag = 0;
    }
    if (ip_mac_flag == 1) {
        ip_mac_parser();
        ip_mac_flag = 0;
    }
    if (dhcp_flag == 1) {
        dhcp_parser();        
        dhcp_flag = 0;
    }
    if (connection_flag == 1) {
        connection_parser();
        connection_flag = 0;
    }
    if (tcp_send_buffer_status_flag == 1) {
        tcp_send_buffer_status_parser();
        tcp_send_buffer_status_flag = 0;
    }
    if (specific_tcp_segment_flag == 1) {   
        specific_tcp_segment_parser();
        specific_tcp_segment_flag = 0;
    }
}


//+CW
//+CIP
//+CIUPDATE:<n> 
//+ CIFSR
//+SLEEP
//+RFVDD
// +<time> 
typedef enum ESP8266_PLUS_MSG_t {
    WAIT_FOR_PLUS,
    PLUS_RECEIVED,
    C_RECEIVED,
    CI_RECEIVED
} ESP8266_PLUS_MSG;

ESP8266_PLUS_MSG esp8266_plus_msg = WAIT_FOR_PLUS;

UInt8 plus_frame[100] = {0};
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
            else if (receive_byte == 'S') {
                sleep_parser();         //+SLEEP
            }
            else if (receive_byte == 'R') {
                rf_voltage_parser();    //+RFVDD
            }
            else {
                ping_parser();          // +<time> 
            }
            break;
        case C_RECEIVED:
            if (receive_byte == 'W') {
                cw_purser();            //+CW
            }
            if (receive_byte == 'I') {
                esp8266_plus_msg = CI_RECEIVED;
            }
            break;
        case CI_RECEIVED:
            if (receive_byte == 'P') {
                cip_parser();           //+CIP
            }
            else if (receive_byte == 'U') {
                update_parser();        //+CIUPDATE:<n> 
            }
            else if (receive_byte == 'F') {
                ip_address_parser();    //+ CIFSR
            }
            break;
        default:
            break;
    }
}




Void rf_voltage_parser(Void) {
    /* [5] */
    // +RFVDD:<VDD33> 
    // OK
}

Void ip_address_parser(Void) {
    /* [37] */
    // + CIFSR:<IP address> 
    // OK 
    // ERROR
}

Void sleep_parser(Void) {
    /* [4] */
    // +SLEEP : <sleep mode> 
    // OK
}


Void update_parser(Void) {
    /* [43] */
    // +CIUPDATE:<n> 
    // OK
}

Void ping_parser(Void) {
    /* [42] */
    // +<time> 
    // OK 
    // Or 
    // ERROR // means ping fail
}



Void ipd_parser(Void) {
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
Void cwmode_parser(Void) {
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


Void cwjap_purser(Void) {
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

Void cwlap_purser(Void) {
    /* [14] */
    // +CWLAP:<ecn>, <ssid>, <rssi>, <mac>, <ch>, <freq offset>, <freq calibration> 
    // OK 
    // ERROR
}


Void cwsap_purser(Void) {
    /* [15] */
    // +CWSAP_CUR:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>

    /* [16] */
    // +CWSAP_DEF:<ssid>, <pwd>, <chl>, <ecn>, <max conn>, <ssid hidden>
}

Void cwdhcps_purser(Void) {
    /* [19] */
    // +CWDHCPS_CUR=<lease time>, <start IP>, <end IP>

    /* [20] */
    // +CWDHCPS_DEF=<lease time>, <start IP>, <end IP>
}



Void cw_purser(Void) {

    cwmode_parser();    // +CWMODE
    
    cwjap_purser();     // +CWJAP
    
    cwlap_purser();     // +CWLAP

    cwsap_purser();     // +CWSAP
    
    cwdhcps_purser();   // +CWDHCPS
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
Void cipsta_parser(Void) {
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

Void cipap_parser(Void) {
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


Void cip_status_parser(Void) {
    /* [29] */
    // STATUS:<stat> 
    // +CIPSTATUS:<link ID>, <type>, <remote_IP>, <remote_port>, <local_port>,  <tetype>
}


Void cipdomain_parser(Void) {
    /* [30] */
    // +CIPDOMAIN:<IP address>
}

Void cipmux_parser(Void) {
    /* [38] */
    // + CIPMUX:<mode> 
    // OK
}

Void cipmode_parser(Void) {
    /* [39] */
    // +CIPMODE:<mode> 
    // OK
}

Void cipsto_parser(Void) {
    /* [41] */
    // + CIPSTO:<time> 
    // OK
}

Void cip_parser(Void) {

    cipsta_parser();        //+CIPSTA

    cipap_parser();         //+CIPAP

    cip_status_parser();    //+CIPSTATUS

    cipdomain_parser();     // +CIPDOMAIN

    cipmode_parser();       //+CIPMODE

    cipsto_parser();        //+ CIPSTO
}


// ============================================================================================================================================
// ============================================================== END CIP PARSER ==============================================================
// ============================================================================================================================================

