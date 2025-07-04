#include "esp8266.h"
#include "../Common_C/defs.h"


Void parser_esp8266(UInt8 received_byte) {

    request_parser(received_byte); // use timer for receive data timeout ...

    plus_parser(received_byte);
}



