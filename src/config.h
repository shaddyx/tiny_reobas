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


// The number of times the temperature will be read sequentially to avoid the noise
#define TEMP_NUM_READS 5
// The value which will be set to the fan when the cold start is started and will remain for COLD_START_DELAY ms
#define COLD_START_PWM 150
// Histeresis trigger delay
// the logic is the next: if the ADC value is greater than histeresis_VALUE for this amount of time, the fan will be turned on
#define COLD_START_DELAY_AFTER_ON 100
// Cold start delay (the time it takes to turn the fan on with COLD_START_PWM value)
#define COLD_START_DELAY 300
// Smooth interval, the value in ms between the fan value increments or decrements by 1
#define SMOOTH_INTERVAL 10