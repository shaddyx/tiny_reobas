#pragma once
#include <Arduino.h>

#define FORCE_DEBUG 0
#ifdef ARDUINO_AVR_UNO
    #define DEBUG_ALLOWED
#endif

#if !defined(ARDUINO_AVR_UNO) and FORCE_DEBUG == 1
    #define EMULATION
    #define DEBUG_ALLOWED
#endif

void debug_init();
void debug_info(char * str);
void debug_info(char * str, int16_t val);
void debug_info(char * str, int16_t val, char * str1, int16_t val1 );