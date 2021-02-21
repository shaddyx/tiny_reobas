#pragma once

#define DEBUG_TX PB2
#define DEBUG_RX PB1

#ifdef ARDUINO_AVR_UNO
    #define THERMORESISTOR_PIN A0
    #define LED_PIN 13
    #define FAN_PIN 9
    // fuses default
# else
    #define ADC2 2
    #define THERMORESISTOR_PIN ADC2
    #define LED_PIN PB3
    #define FAN_PIN PB0
#endif

#define MIN_TEMP 32
#define MIN_TEMP_START 37
#define MAX_TEMP 60


#define COLD_START_PWM 50
#define MIN_PWM 10

#define TEST_MODE 0

#ifdef __AVR_ATtiny13__
    #define PWM_FREQ 800000
#else
    #define PWM_FREQ 50000
#endif

