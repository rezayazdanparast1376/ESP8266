#include <stdint.h>
#include <stdbool.h>
#include "esp8266.h"
#include "../Common_C/defs.h"
#include "debug.h"
#include "esp8266_send_command.h"
#include "main.h"

#define ESP8266_PORT &huart3


extern Bool send_data_flag;
extern Bool err_ok_flag;
extern Bool version_flag;
extern Bool time_flag;
extern Bool ip_mac_flag;
extern Bool dhcp_flag;
extern Bool connection_flag;
extern Bool tcp_send_buffer_status_flag;
extern Bool specific_tcp_segment_flag;

extern ESP8266_RESPONCE esp8266_responce;


Void esp8266_uart_send(const char* send_buf, size_t len) {
    HAL_UART_Transmit(ESP8266_PORT, send_buf, len, 1000);
}




Void esp8266_delay_ms(UInt16 _delay) {
    HAL_Delay(_delay);
}




/**
 * 
*/
Bool esp8266_Test(Void) {
    __esp8266_Send_Test_AT_cmd();
    
    err_ok_flag = True;
    
    esp8266_delay_ms(1000);
    
    receive_esp8266_data();
    
    if (esp8266_responce == ESP8266_OK_RESPONCE) {
        esp8266_responce = ESP8266_NO_RESPONCE;
        return True;
    }
    
    return False;
}



Bool esp8266_get_version(Void) {
    __esp8266_Send_AT_GMR_cmd();

    version_flag = True;

    esp8266_delay_ms(1000);

    receive_esp8266_data();
    
    if (esp8266_responce == ESP8266_OK_RESPONCE) {
        esp8266_responce = ESP8266_NO_RESPONCE;
        return True;
    }
    
    return False;
}



Void esp8266_set_deep_sleep_mode(UInt16 time) {
    __esp8266_Send_AT_GSLP_cmd(time);
}




Void esp8266_set_echo(Bool echo) {
    __esp8266_Send_ATE_cmd(echo);
}




Void esp8266_set_uart_config(
    ESP8266_UART_CONF uart_config
) {
    if (uart_config.config_state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_UART_CUR_cmd(uart_config.boud_rate, uart_config.data_bit, uart_config.stop_bit, uart_config.parity_bit, uart_config.flow_control);
    }
    else if(uart_config.config_state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_UART_DEF_cmd(uart_config.boud_rate, uart_config.data_bit, uart_config.stop_bit, uart_config.parity_bit, uart_config.flow_control);
    }
}




Void esp8266_set_sleep_mode(_In_ SLEEP_MODE sleep_mode) {
    __esp8266_Send_AT_SLEEP_set_cmd(sleep_mode);
}




Void esp8266_get_sleep_mode(_Out_ SLEEP_MODE* sleep_mode) {
    __esp8266_Send_AT_SLEEP_req_cmd();
    // delay_ms(100);
    //receive sleep mode from irq ...
}




Void esp8266_set_rf_tx_power(UInt16 vdd) {
    Soft_Assert_Void(vdd >= 1900 && vdd <= 3300, "Invalid parameter for power range! range[1900 ~ 3300]");

    __esp8266_Send_AT_RFVDD_set_cmd(vdd);
}




Void esp8266_set_rf_tx_power_auto(Void) {
    __esp8266_Send_AT_RFVDD_req_cmd();
}




Void esp8266_get_rf_tx_power(Void) {
    //TODO ...
    __esp8266_Send_AT_RFVDD_get_cmd();
    //delay 

    //receive response ...
}




Void esp8266_set_wifi_mode(ESP8266_WIFI_CONF wifi_config) {
    if (wifi_config.config_state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWMODE_CUR_set_cmd(wifi_config.wifi_mode);
    }
    else if (wifi_config.config_state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWMODE_DEF_set_cmd(wifi_config.wifi_mode);
    }
}




Void esp8266_get_wifi_mode(
    _Out_ ESP8266_WIFI_MODE*   wifi_mode, 
    _In_  ESP8266_CONFIG_STATE state
) {
    if (state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWMODE_CUR_get_cmd();
    }
    else if (state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWMODE_DEF_get_cmd();
    }
    // TODO: 
    // delay 
    
    // receive state ...
}




Void esp8266_connect_to_acsess_point(
    Char*                ssid, 
    Char*                pwd, 
    Char*                bssid, 
    ESP8266_CONFIG_STATE state
) {
    Soft_Assert_Void(ssid != NULL, "Invalid argument! ssid is NULL.");
    Soft_Assert_Void(pwd  != NULL, "Invalid argument! pwd is NULL.");

    if (state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWJAP_CUR_set_cmd(ssid, pwd, bssid);
    }
    else if (state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWJAP_DEF_set_cmd(ssid, pwd, bssid);
    }
    // TODO: check error code ...
    // delay
    // receive respond ...
}




Void esp8266_set_cwlap(
    Bool sort_enable, 
    Bool ecn,
    Bool ssid,
    Bool rssi,
    Bool mac,
    Bool ch,
    Bool freq_offset,
    Bool freq_calibration
) {
    UInt8 mask = (ecn << 0) | (ssid << 1) | (rssi << 2) | (mac << 3) | (ch << 4) | (freq_offset << 5) | (freq_calibration << 6);

    __esp8266_Send_AT_CWLAPOPT_set_cmd(sort_enable, mask);
}




Void esp8266_list_available_acess_point() {
    __esp8266_Send_AT_CWLAP_get_cmd();
    // TODO
    // delay
    // receive respond
}




Void esp8266_find_acess_point(
    Char* ssid, 
    Char* mac, 
    Char* ch
) {
    Soft_Assert_Void(ssid != NULL, "Invalid argument! ssid is NULL.");
    Soft_Assert_Void(mac != NULL, "Invalid argument! mac is NULL.");
    __esp8266_Send_AT_CWLAP_set_cmd(ssid, mac, ch);
    // TODO
    // delay
    // receive respond
}




Void esp8266_disconnect_acsses_point(Void) {
    __esp8266_Send_AT_CWQAP_cmd();
}




// <ssid> string, ESP8266 softAP’ SSID   
// <pwd> string, range: 8 ~ 64 bytes ASCII 
// <chl>  channel id 
// <ecn>   
// 0    OPEN 
// 2    WPA_PSK 
// 3    WPA2_PSK 
// 4    WPA_WPA2_PSK  
// <max conn>  maximum count of stations that allowed to connect to ESP8266 soft-AP  range: [1, 4] 
// <ssid hidden>  Broadcast SSID by default 
// 0   broadcast SSID of ESP8266 soft-AP 
// 1   do not broadcast SSID of ESP8266 soft-A
Void esp8266_config_acsess_point(ESP8266_AP_CONF config) {
    Soft_Assert_Void(config.ssid == NULL, "Invalid argument! ssid is NULL.");
    Soft_Assert_Void(config.pwd == NULL, "Invalid argument! pwd is NULL.");
//    Soft_Assert_Void(config.max_conn <= 4, "Inavlid argument! range of acssess point connnection: [1, 4] , request connection: %d", config.max_conn);
    if (config.wps == WPA_PSK) {
//        Soft_Assert_Void(strlen(config.pwd) <= 16, "Inavlid pasword len! - Maximum key length in WEP protection is 16 characters. len: %d", strlen(config.pwd));
    }
    else {
//        Soft_Assert_Void(strlen(config.pwd) <= 63, "Inavlid pasword len! - Maximum key length in WEP protection is 63 characters. len: %d", strlen(config.pwd));
    }
    
    
    if (config.state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWSAP_CUR_set_cmd(config.ssid, config.pwd, config.channel_id, config.wps, config.max_conn, NULL);//TODO: handel NULL
    }
    else if (config.state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWSAP_DEF_set_cmd(config.ssid, config.pwd, config.channel_id, config.wps, config.max_conn, NULL);// TODO: handel NULL
    }
}




Void esp8266_check_config_acsess_point(ESP8266_AP_CONF* config) {
    Soft_Assert_Void(config != NULL, "Invalid argument! config parameter is NULL.");

    if(config->state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWSAP_CUR_get_cmd();
    }
    else if (config->state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWSAP_DEF_get_cmd();
    }
}




Void esp8266_get_ip_stations(Void) {
    __esp8266_Send_AT_CWLIF_cmd();
}




Void esp8266_set_dhcp(ESP8266_DHCP_CONF config) {
    UInt8 mode = 0;
    if (config.mode == WIFI_MODE_STATION) {
        mode = 1;
    }
    else if (config.mode == WIFI_MODE_ACSESS_POINT) {
        mode = 0;
    }
    else if (config.mode == WIFI_MODE_STATION_ACSESS_POINT) {
        mode = 2;
    }
    
    if (config.state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWDHCP_CUR_set_cmd(mode, config.en);
    }
    else if (ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWDHCP_DEF_set_cmd(mode, config.en);
    }
}




Void esp8266_get_dhcp(ESP8266_DHCP_CONF* config) {
    Soft_Assert_Void(config != NULL, "Invalid argument! config parameter is NULL.");

    if (config->state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWDHCP_CUR_get_cmd();   
    }
    else if (config->state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWDHCP_DEF_get_cmd();   
    }
}




Void esp8266_set_dhcp_ip_address(ESP8266_DHCP_IP_CONF config) {
    Soft_Assert_Void((config.leas_time >= 1) && (config.leas_time <= 2880), "Invalid argument! leas time is out of range. range[1, 2880]");

    if (config.state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWDHCPS_CUR_set_cmd(config.enable, config.leas_time, config.start_ip, config.end_ip);
    }
    else if (config.state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWDHCPS_DEF_set_cmd(config.enable, config.leas_time, config.start_ip, config.end_ip);
    }
}




Void esp8266_get_dhcp_ip_address(ESP8266_DHCP_IP_CONF* config) {
    Soft_Assert_Void(config != NULL, "Invalid argument! config parameter is NULL");

    if (config->state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CWDHCPS_CUR_get_cmd();
    }
    else if (config->state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CWDHCPS_DEF_get_cmd();
    }
}




Void esp8266_auto_connect_to_acsess_point(Bool enable) {
    __esp8266_Send_AT_CWAUTOCONN_set_cmd(enable);
}




Void esp8266_set_mac_address_station(ESP8266_STATION_MAC config) {
    if (config.state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CIPSTAMAC_CUR_set_cmd(config.mac_address);
    }
    else if (config.state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CIPSTAMAC_DEF_set_cmd(config.mac_address);
    }
}




Void esp8266_get_mac_address_station(ESP8266_STATION_MAC* config) {
    Soft_Assert_Void(config != NULL, "Invalid argument! config parameter is NULL");

    if (config->state == ESP8266_CONFIG_STATE_CUR) {
        __esp8266_Send_AT_CIPSTAMAC_CUR_get_cmd();
    }
    else if (config->state == ESP8266_CONFIG_STATE_DEF) {
        __esp8266_Send_AT_CIPSTAMAC_DEF_get_cmd();
    }
}




/// ====================================================================================

Void init_esp8266(Void) {
    
    debug_info(&DEBUG_PORT, "Config echo massage ...");
    esp8266_set_echo(False);

    HAL_Delay(1000);

    Bool ret = esp8266_Test();
    Soft_Assert_Ignore(ret == True, "Communication test of esp8266 was fail!");

    debug_info(&DEBUG_PORT, "Comminucation test of esp8266 was sucsessful.");
    
    debug_info(&DEBUG_PORT, "Get verson of esp8266 ...");
    ret = esp8266_get_version();
    Soft_Assert_Ignore(ret == True, "Cannot get version information of esp8266!");

    debug_info(&DEBUG_PORT, "get F.W version of esp8266  was sucsessful.");
}



Void send_esp8266(Void) {

}


Void receive_esp8266(Void) {

}



// Single connection
// (+CIPMUX=0) 
// +IPD, <len>[, <remote IP>, <remote port>]:<data>
// Multiple connection (+CIPMUX=1) 
// +IPD, <ID>, <len>[, <remote IP>, <remote port>]:<data>

