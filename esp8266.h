#define CARRIAR_RETURN  0x0D  //\r
#define LINE_FEED       0x0A  //\n

void init_esp8266(void);
void parser_esp8266(void);


void __esp8266_Send_Test_AT_cmd(void);
void __esp8266_Send_AT_RST_cmd(void);
void __esp8266_Send_AT_GMR_cmd(void);
void __esp8266_Send_AT_GSLP_cmd(uint16_t time);
void __esp8266_Send_ATE_cmd(bool echo);
void __esp8266_Send_AT_RESTORE_cmd(void);

void __esp8266_Send_AT_UART_CUR_cmd(uint16_t baudrate, uint8_t  databits, uint8_t  stopbits, uint8_t  parity, uint8_t  flow_control);
void __esp8266_Send_AT_UART_DEF_cmd(uint16_t baudrate, uint8_t  databits, uint8_t  stopbits, uint8_t  parity, uint8_t  flow_control);

void __esp8266_Send_AT_SLEEP_req_cmd(void);
void __esp8266_Send_AT_SLEEP_set_cmd(uint8_t sleep_mode);

void __esp8266_Send_AT_RFPOWER_set_cmd(uint8_t tx_power);

void __esp8266_Send_AT_RFVDD_get_cmd(void);
void __esp8266_Send_AT_RFVDD_set_cmd(uint16_t VDD33);
void __esp8266_Send_AT_RFVDD_req_cmd(void);