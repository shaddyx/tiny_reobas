#include <Arduino.h>
#include <thermoresistor_calc.h>
#include "debug.h"
#include <FastPwmPin.h>
#define length(array) (sizeof((array)) / sizeof((array)[0]))
#ifdef ARDUINO_AVR_UNO
    #define THERMORESISTOR_PIN A0
    #define LED_PIN 13
# else
    #define ADC1 1
    #define ADC2 2
    #define ADC3 3
    #define ADC4 4
    #define THERMORESISTOR_PIN ADC2
    #define LED_PIN PB3
    #define FAN_PIN PB1
#endif

#define MIN_TEMP 40
#define MAX_TEMP 80

void setup(){
    debug_init();
    pinMode(LED_PIN, OUTPUT);
    pinMode(THERMORESISTOR_PIN, INPUT);
    digitalWrite(LED_PIN, 1);
    #ifdef DEBUG_ALLOWED
        debug_info("init complete");
    #endif
    delay(1000);
}

void checkAndBlinkError(int adcValue){
    if (adcValue == 1023){
        digitalWrite(LED_PIN, 1);
        delay(100);
        digitalWrite(LED_PIN, 0);
        delay(100);
    }
}

int16_t read_temp(){
    auto adcValue = analogRead(THERMORESISTOR_PIN);
    checkAndBlinkError(adcValue);
    auto temp = calc_temperature(adcValue);
    #ifdef DEBUG_ALLOWED
        //debug_info("a:" , adcValue, " t:" , temp);
    #endif
    return temp;
}
void stop(){
    FastPwmPin::enablePwmPin(FAN_PIN, 35000 , 1);
    #ifdef DEBUG_ALLOWED
        debug_info("fan off");
    #endif
    digitalWrite(FAN_PIN, 0);
}

bool checkDiff(unsigned long value, unsigned long * last){
    auto m = millis();
    if (*last > m){
        *last = m;
        return false;
    }
    return m - value > *last;
}

void initialDelay(){
    #ifdef __AVR_ATtiny13__
        delay(100);
    #else
        delay(500); 
    #endif 
}

unsigned long last_on = 0;
void loop(){
    auto temp = read_temp();
    digitalWrite(LED_PIN, temp > 40);
    int percentage;
    if (temp > MIN_TEMP){
        if (checkDiff(1000, &last_on)){
            FastPwmPin::enablePwmPin(FAN_PIN, 35000 , 99);
            initialDelay();
        } else {
            if (temp >= MAX_TEMP){
                percentage = 99;
            } else {
                percentage = ((temp - MIN_TEMP) * 100) * (100 / (MAX_TEMP - MIN_TEMP)) / 100;
                percentage += 10;
            }
            if (percentage >= 100){
                percentage = 99;
            }
            #ifdef DEBUG_ALLOWED
                debug_info("t:" , temp, " p:" , percentage);
            #endif
            FastPwmPin::enablePwmPin(FAN_PIN, 35000 , percentage);
        }
        last_on = millis();
    } else {
        stop();
    }   
}


