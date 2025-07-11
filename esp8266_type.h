#ifndef _ESP8266_TYPE_H_
#define _ESP8266_TYPE_H_



typedef enum SLEEP_MODE_t {
    DISABLE_SLEEP_MODE = 0 , /* disable sleep mode */  
    LIGHT_SLEEP_MODE = 1 ,   /* light-sleep mode */
    MODEM_SLEEP_MODE = 2     /*modem-sleep mode*/ 
}SLEEP_MODE;

typedef struct ESP8266_t {
    SLEEP_MODE sleep_mode;
}ESP8266;



typedef enum ESP8266_UART_DATA_BIT_t {
    ESP8266_UART_DATABIT_5 = 5, /* 5: 5 bits data */
    ESP8266_UART_DATABIT_6 = 6, /* 6: 6 bits data */
    ESP8266_UART_DATABIT_7 = 7, /* 7: 7 bits data */
    ESP8266_UART_DATABIT_8 = 8  /* 8: 8 bits data */
}ESP8266_UART_DATA_BIT;

typedef enum ESP8266_UART_STOP_BIT_t {
    ESP8266_UART_STOP_BIT_1   = 1, // 1: 1 bit stop bit
    ESP8266_UART_STOP_BIT_1_5 = 2, // 2: 1.5 bit stop bit
    ESP8266_UART_STOP_BIT_2   = 3, // 3: 2 bit stop bit
}ESP8266_UART_STOP_BIT;


// <parity> 
typedef enum ESP8266_UART_PARITY_BIT_t {
    ESP8266_UART_PARITY_BIT_NONE = 0,  // 0: None
    ESP8266_UART_PARITY_BIT_ODD  = 1,  // 1: Odd
    ESP8266_UART_PARITY_BIT_EVEN  = 2, // 2: EVEN
}ESP8266_UART_PARITY_BIT;

// <flow control>
// 0: disable flow control
// 1: enable RTS
// 2: enable CTS
// 3: enable both RTS and CTS
typedef enum ESP8266_UART_FLOW_CONTROL_t {
    ESP8266_UART_DISABLE_FLOW_CONTROL = 0,  // 0: disable flow control
    ESP8266_UART_ENABLE_RTS           = 1,  // 1: enable RTS
    ESP8266_UART_ENABLE_CTS           = 2,  // 2: enable CTS
    ESP8266_UART_ENABLE_CTS_RTS       = 3,  // 3: enable both RTS and CTS
}ESP8266_UART_FLOW_CONTROL;


typedef enum ESP8266_CONFIG_STATE_t {
    ESP8266_CONFIG_STATE_CUR = 0,  // 0: current config
    ESP8266_CONFIG_STATE_DEF = 1,  // 1: default config
}ESP8266_CONFIG_STATE;

typedef struct ESP8266_UART_CONF_t {
    UInt16                    boud_rate;    // <baudrate> Baudrate range: 110 to 115200*40 (4.608 Mega)
    ESP8266_UART_DATA_BIT     data_bit;
    ESP8266_UART_STOP_BIT     stop_bit;
    ESP8266_UART_PARITY_BIT   parity_bit;
    ESP8266_UART_FLOW_CONTROL flow_control;
    ESP8266_CONFIG_STATE        config_state;
}ESP8266_UART_CONF;


typedef enum SLEEP_MODE_t {
    DISABLE_SLEEP_MODE = 0, /* 0 : disable sleep mode  */
    LIGHT_SLEEP_MODE   = 1, /* 1 : light-sleep mode  */
    MODEM_SLEEP_MODE   = 2  /* 2 : modem-sleep mode */
}SLEEP_MODE;


typedef enum ESP8266_WIFI_MODE_t {
    WIFI_MODE_STATION              = 1,
    WIFI_MODE_ACSESS_POINT         = 2,
    WIFI_MODE_STATION_ACSESS_POINT = 3,
}ESP8266_WIFI_MODE;

typedef struct ESP8266_WIFI_CONF_t {
    ESP8266_WIFI_MODE    wifi_mode;
    ESP8266_CONFIG_STATE config_state;
}ESP8266_WIFI_CONF;




typedef struct ESP8266_AP_CONF_t {
    Char                 ssid[32]; 
    Char                 pwd[64]; 
    UInt8                channel_id; 
    WPA                  wps; 
    UInt8                max_conn; 
    Bool                 ssid_headen;
    ESP8266_CONFIG_STATE state;
}ESP8266_AP_CONF;

typedef enum WIFI_PROTECTION_ACSESS_t{
    OPEN = 0,
    WPA_PSK = 2,
    WPA2_PSK = 3,
    WPA_WPA2_PSK = 4
}WPA;





typedef struct ESP8266_DHCP_CONF_t {
    ESP8266_WIFI_MODE    mode;
    ESP8266_CONFIG_STATE state;
    Bool                 en;
}ESP8266_DHCP_CONF;


typedef struct ESP8266_DHCP_IP_CONF_t {
    Bool     enable;
    UInt16   leas_time; 
    Char     start_ip[16]; 
    Char     end_ip[16];
    ESP8266_CONFIG_STATE state;
}ESP8266_DHCP_IP_CONF;




typedef struct ESP8266_STATION_MAC_t {
    Char                 mac_address[18];
    ESP8266_CONFIG_STATE state;
}ESP8266_STATION_MAC;




#endif  //_ESP8266_TYPE_H_
