#include "../Common_C/defs.h"

#include "esp8266_type.h"


#define ESP8266_GPIO0_PORT
#define ESP8266_GPIO0_PIN

// ESP8266 esp8266 = {0};


Void esp8266_set_deep_sleep_mode(UInt16 time);
Void esp8266_set_echo(Bool echo) ;
Void esp8266_set_uart_config(ESP8266_UART_CONF uart_config);

Void esp8266_set_sleep_mode(_In_ SLEEP_MODE sleep_mode);
Void esp8266_get_sleep_mode(_Out_ SLEEP_MODE* sleep_mode);
Void esp8266_set_rf_tx_power(UInt16 vdd);
Void esp8266_set_rf_tx_power_auto(Void);
Void esp8266_get_rf_tx_power(Void);
Void esp8266_set_wifi_mode(ESP8266_WIFI_CONF wifi_config);

Void esp8266_get_wifi_mode(_Out_ ESP8266_WIFI_MODE*   wifi_mode, _In_  ESP8266_CONFIG_STATE state);

Void esp8266_connect_to_acsess_point(
    Char*                ssid, 
    Char*                pwd, 
    Char*                bssid, 
    ESP8266_CONFIG_STATE state
);
Void esp8266_set_cwlap(
    Bool sort_enable, 
    Bool ecn,
    Bool ssid,
    Bool rssi,
    Bool mac,
    Bool ch,
    Bool freq_offset,
    Bool freq_calibration
);
Void esp8266_list_available_acess_point();
Void esp8266_find_acess_point(
    Char* ssid, 
    Char* mac, 
    Char* ch
);
Void esp8266_disconnect_acsses_point(Void);
Void esp8266_config_acsess_point(ESP8266_AP_CONF config);
Void esp8266_check_config_acsess_point(ESP8266_AP_CONF* config);
Void esp8266_get_ip_stations(Void);
Void esp8266_set_dhcp(ESP8266_DHCP_CONF config);
Void esp8266_get_dhcp(ESP8266_DHCP_CONF* config);
Void esp8266_set_dhcp_ip_address(ESP8266_DHCP_IP_CONF config);
Void esp8266_get_dhcp_ip_address(ESP8266_DHCP_IP_CONF* config);
Void esp8266_auto_connect_to_acsess_point(Bool enable);
Void esp8266_set_mac_address_station(ESP8266_STATION_MAC config);
Void esp8266_get_mac_address_station(ESP8266_STATION_MAC* config);
// =============================================================================================

Void init_esp8266(Void);
Void parser_esp8266(UInt8 received_byte);


