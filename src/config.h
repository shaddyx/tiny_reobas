#pragma once

#define DEBUG_TX PB2
#define DEBUG_RX PB1

#ifdef ARDUINO_AVR_UNO
    #define THERMORESISTOR_PIN A0
    #define LED_PIN 13
    // fuses default
# else
    #define ADC1 1
    #define ADC2 2
    #define ADC3 3
    #define ADC4 4
    #define THERMORESISTOR_PIN ADC2
    #define LED_PIN PB3
    #define FAN_PIN PB0
#endif

#define MIN_TEMP 35
#define MAX_TEMP 60
#define MIN_PWM 1

#define TEST_MODE 1

#ifdef __AVR_ATtiny13__
    #define PWM_FREQ 800000
#else
    #define PWM_FREQ 50000
#endif

