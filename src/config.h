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

#ifdef __AVR_ATtiny13__
    #define PWM_FREQ 800000
#else
    #define PWM_FREQ 50000
#endif

#define TEMP_NUM_READS 5
#define COLD_START_PWM 150
#define COLD_START_DELAY_AFTER_ON 100
#define COLD_START_DELAY 300
