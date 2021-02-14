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

#define MIN_TEMP 30
#define MAX_TEMP 80

#ifdef __AVR_ATtiny13__
    #define PWM_FREQ 800000
#else
    #define PWM_FREQ 35000
#endif


void tinyDelay(int value){
    #ifdef __AVR_ATtiny13__
        // fix default prescaler configuration
        delay(value / 8);
    #else
        delay(value); 
    #endif 
}

void setPwm(uint8_t pwm){
    #ifdef __AVR_ATtiny13__
        if (pwm < 10){
            pwm = 10;
        }
    #endif
     if (pwm >= 90){
        pwm = 90;
    }
    FastPwmPin::enablePwmPin(FAN_PIN, PWM_FREQ , pwm);
}

void stop(){
    #ifdef DEBUG_ALLOWED
        debug_info("fan off");
    #endif
    setPwm(0);
  
}

void setup(){
    debug_init();
    //stop();
    pinMode(LED_PIN, OUTPUT);
    pinMode(THERMORESISTOR_PIN, INPUT);
    digitalWrite(LED_PIN, 1);
    #ifdef DEBUG_ALLOWED
        debug_info("init complete");
    #endif
    tinyDelay(1000);
}

void checkAndBlinkError(int adcValue){
    if (adcValue == 1023){
        digitalWrite(LED_PIN, 1);
        tinyDelay(100);
        digitalWrite(LED_PIN, 0);
        tinyDelay(100);
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


bool checkDiff(unsigned long value, unsigned long * last){
    auto m = millis();
    if (*last > m){
        *last = m;
        return false;
    }
    return m - value > *last;
}

void initialDelay(){
    digitalWrite(LED_PIN, 0);
    tinyDelay(500);
    digitalWrite(LED_PIN, 1);
    tinyDelay(500);
}

unsigned long last_on = 0;
void loop(){
    auto temp = read_temp();
    digitalWrite(LED_PIN, temp > MIN_TEMP);
    int percentage;
    if (temp > MIN_TEMP){
        if (checkDiff(1000, &last_on)){
            setPwm(99);
            initialDelay();
        } else {
            if (temp >= MAX_TEMP){
                percentage = 99;
            } else {
                percentage = ((temp - MIN_TEMP) * 100) * (100 / (MAX_TEMP - MIN_TEMP)) / 100;
                percentage += 10;
            }
            #ifdef DEBUG_ALLOWED
                debug_info("t:" , temp, " p:" , percentage);
            #endif
            setPwm(percentage);
        }
        last_on = millis();
    } else {
        stop();
    }   
}


