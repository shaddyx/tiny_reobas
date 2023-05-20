#pragma once
#include <Arduino.h>

#define DEBUG_LED 0
#define FORCE_DEBUG 0
#ifdef ARDUINO_AVR_UNO
    #define DEBUG_ALLOWED
#endif

#if !defined(ARDUINO_AVR_UNO) && FORCE_DEBUG == 1
    #define EMULATION
    #define DEBUG_ALLOWED
#endif

#ifdef DEBUG_ALLOWED
    void debug_init();
    void debug_info(char * str);
    void debug_info(char * str, int16_t val);
    void debug_info(char * str, int16_t val, char * str1, int16_t val1 );
#else
    #define debug_init()
    #define debug_info(...)
#endif


#if DEBUG_LED == 1
    #define debugLed(v) digitalWrite(LED_PIN, v);
#else
    #define debugLed(v)
#endif