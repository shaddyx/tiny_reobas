#include <Arduino.h>
#include "debug.h"
#include "config.h"

#ifdef EMULATION
    #include <SoftwareSerial.h>
    SoftwareSerial mySerial(DEBUG_RX, DEBUG_TX); // RX, TX
#endif // EMULATION

#ifdef DEBUG_ALLOWED

void debug_init(){
    #ifdef ARDUINO_AVR_UNO
        Serial.begin(9600);
    #elif defined(EMULATION)
        mySerial.begin(9600);
    #endif
}

void debug_info(char * str){
    #ifdef ARDUINO_AVR_UNO
        Serial.println(str);
    #elif defined(EMULATION)
        mySerial.println(str);
    #endif
}

void debug_info(char * str, int16_t val){
    #ifdef ARDUINO_AVR_UNO
        Serial.print(str);
        Serial.println(val);
    #elif defined(EMULATION)
        mySerial.print(str);
        mySerial.println(val);
    #endif
}

void debug_info(char * str, int16_t val, char * str1, int16_t val1 ){
    #ifdef ARDUINO_AVR_UNO
        Serial.print(str);
        Serial.print(val);
        Serial.print(str1);
        Serial.println(val1);
    #elif defined(EMULATION)
        mySerial.print(str);
        mySerial.print(val);
        mySerial.print(str1);
        mySerial.println(val1);
    #endif
}

#endif