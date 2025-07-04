#include <stdint.h>
#include <stdbool.h>
#include "esp8266.h"
#include "../Common_C/defs.h"
#include "../Common_C/debug.h"

#include "main.h"

#define ESP8266_PORT &huart2

Void esp8266_uart_send(UInt8* send_buf, size_t len) {
    HAL_UART_Transmit(ESP8266_PORT, send_buf, len, 1000);
}




Void init_esp8266(Void) {

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

