#include <Arduino.h>
#include <thermoresistor_calc.h>
#include "debug.h"
#include <FastPwmPin.h>
#define length(array) (sizeof((array)) / sizeof((array)[0]))
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
    #define FAN_PIN PB1
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


void tinyDelay(int value){
    delay(value); 
}

void setPwm(uint8_t pwm){
    if (pwm < MIN_PWM){
        pwm = MIN_PWM;
    }
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
void test_loop(){
    digitalWrite(LED_PIN, 1);
    if (step > 5){
        step = 0;
    }
    FastPwmPin::enablePwmPin(FAN_PIN, PWM_FREQ , 20 * step);
    step ++;
    delay(500);
    digitalWrite(LED_PIN, 0);
    delay(3000);
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
                percentage = ((temp - MIN_TEMP) * 100) * (100 / (MAX_TEMP - MIN_TEMP)) / 100;
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


