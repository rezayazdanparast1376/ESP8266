#include "../Common_C/defs.h"

typedef enum SLEEP_MODE_t {
    DISABLE_SLEEP_MODE = 0 ,// disable sleep mode 
    LIGHT_SLEEP_MODE = 1 , //: light-sleep mode 
    MODEM_SLEEP_MODE = 2 //: modem-sleep mode
}SLEEP_MODE;

typedef struct ESP8266_t {
    SLEEP_MODE sleep_mode;
}ESP8266;

// ESP8266 esp8266 = {0};


Void init_esp8266(Void);
Void parser_esp8266(UInt8 received_byte);


