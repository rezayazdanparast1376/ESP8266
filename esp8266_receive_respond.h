#ifndef _ESP8266_RECEIVE_RESPOND_H_
#define _ESP8266_RECEIVE_RESPOND_H_






typedef enum ESP8266_ERR_OK_MSG_t {
    WAIT_FOR_FRAME,
    O_RECEIVED,
    WAIT_FOR_R,
} ESP8266_ERR_OK_MSG;


typedef enum ESP8266_VERSION_MSG_t {
	WATIE_FOR_VERSION_FRAME,    /* version frame */
	WATIE_FOR_AT_VERSION,       /* AT version */
	WATIE_FOR_SDK_VERSION,      /* SDK version*/
	WATIE_FOR_COMPILE_TIME,     /* compile time */
    SAVE_AT_VERSION,
    SAVE_SKD_VERSON,
    SAVE_COMPILE_TIME
}ESP8266_VERSION_MSG;

//+CW
//+CIP
//+CIUPDATE:<n> 
//+ CIFSR
//+SLEEP
//+RFVDD
// +<time> 
// +IPD
typedef enum ESP8266_PLUS_MSG_t {
    WAIT_FOR_PLUS,
    PLUS_RECEIVED,
    C_RECEIVED,
    CW_RECEIVED,
    CI_RECEIVED
} ESP8266_PLUS_MSG;


typedef enum ESP8266_CW_MSG_t{
    WAIT_FOR_CW_MSG_FRAME
}ESP8266_CW_MSG;


extern ESP8266_WIFI_MODE __wifi_mode_cur;
extern ESP8266_WIFI_MODE __wifi_mode_def;


Void request_parser(UInt8 receive_byte);
Void plus_parser(UInt8 receive_byte);





#endif //_ESP8266_RECEIVE_RESPOND_H_

