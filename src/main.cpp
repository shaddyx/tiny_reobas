#include <Arduino.h>
#include <thermoresistor_calc.h>
#include "debug.h"
#include "config.h"
#include "temp_to_percentage.h"
#include "pwm/pwm_control.h"

void tinyDelay(int value){
    delay(value); 
}



void stop(){
    #ifdef DEBUG_ALLOWED
        debug_info("fan off");
    #endif
    setPwm(0);
}

void setup(){
    OSCCAL = 82;    // calculated value for softwareSerial

    //OSCCAL = 93;    // calculated value for softwareSerial
    debug_init();
    pinMode(LED_PIN, OUTPUT);
    pinMode(THERMORESISTOR_PIN, INPUT);
    digitalWrite(LED_PIN, 1);
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, 0);
    #ifdef DEBUG_ALLOWED
        debug_info("init complete");
    #endif
    tinyDelay(1000);
    #ifdef DEBUG_ALLOWED
        debug_info("Pin off");
    #endif
    digitalWrite(LED_PIN, 0);
    tinyDelay(1000);
    #ifdef DEBUG_ALLOWED
        debug_info("Starting");
    #endif
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
unsigned long last_off = 0;

#if TEST_MODE == 1
int step = 0;
int direction = 1;
void test_loop(){
    digitalWrite(LED_PIN, 1);
    delay(1000);
    digitalWrite(LED_PIN, 0);
    setPwmPercents(step);
    delay(1000);
    step += direction * 10;
    if (step >= 100){
        direction = -1;
        step = 100;
    }
    if (step <= 0){
        direction = 1;
        step = 0;
    }
}
#endif

void loop(){
    #if TEST_MODE == 1
        test_loop();
    #else
    auto temp = read_temp();
    digitalWrite(LED_PIN, temp > MIN_TEMP);
    int percentage;
    if (temp > MIN_TEMP){
        if (checkDiff(1000, &last_off)){
            setPwm(99);
            initialDelay();
        } else {
            if (temp >= MAX_TEMP){
                percentage = 99;
            } else {
                percentage = calc_percentage(temp, MIN_TEMP, MAX_TEMP);
                percentage += MIN_PWM;
            }
            #ifdef DEBUG_ALLOWED
                debug_info("t:" , temp, " p:" , percentage);
            #endif
            setPwm(percentage);
            last_on = millis();
        }
    } else {
        stop();
        last_off = millis();
    }   
    #endif
}


