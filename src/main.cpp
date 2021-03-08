#include <Arduino.h>
#include <thermoresistor_calc.h>
#include "debug.h"
#include "config.h"
#include "temp_to_percentage.h"
#include "pwm/pwm_control.h"
#include "state.h"

void tinyDelay(int value){
    delay(value); 
}

void stop(){
    debug_info("fan off");
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
    debug_info("init complete");
    tinyDelay(1000);
    debug_info("Pin off");
    digitalWrite(LED_PIN, 0);
    tinyDelay(1000);
    debug_info("Starting");
}

void checkAndBlinkError(int adcValue){
    if (adcValue == 1023){
        debug_info("error!!!");
        digitalWrite(LED_PIN, 1);
        tinyDelay(100);
        digitalWrite(LED_PIN, 0);
        tinyDelay(100);
    }
}

int getTemp(){
    uint16_t result = 0;
    for (int i = 0; i < TEMP_NUM_READS; i++){
       result += analogRead(THERMORESISTOR_PIN) * 10;
       delay(10);
    }
    return (result / TEMP_NUM_READS) / 10;

}

int16_t read_temp(){
    auto adcValue = getTemp();
    checkAndBlinkError(adcValue);
    auto temp = calc_temperature(adcValue);
    //debug_info("a:" , adcValue, " t:" , temp);
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

#if TEST_MODE == 1
int step = 0;
int direction = 1;
void test_loop(){
    digitalWrite(LED_PIN, 1);
    delay(10);
    digitalWrite(LED_PIN, 0);
    //debug_info("percents:", step);
    setPwmPercents(step);
    if (step == 0 || step == 100){
        delay(2000);
    } else {
        delay(10);
    }
    
    step += direction * 1;
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

State<int16_t> temp(0);
State<bool> on(false);
int16_t prevTemp = 0;

void loop(){
    #if TEST_MODE == 1
        test_loop();
        return;
    #else
    delay(100);
    temp.updateValue(read_temp());
    int percentage;

    if (prevTemp == temp.value){
        return;
    }
    if (temp.value > MIN_TEMP){
        if (!on.value && temp.value < MIN_TEMP_START){
            return;
        }
        if (temp.value >= MAX_TEMP){
            percentage = 100;
        } else {
            percentage = calc_percentage(temp.value, MIN_TEMP, MAX_TEMP);
        }
        if (!on.value){
            debug_info("cold start");
            setPwmPercents(COLD_START_PWM);
            for (int i=0; i<10; i++){
                delay(100);
                digitalWrite(LED_PIN, i % 2);
            }
        }
        debug_info("t:" , temp.value, " p:" , percentage);
        if (percentage < MIN_PWM){
            percentage = MIN_PWM;
        }
        setPwmPercents(percentage);
        digitalWrite(LED_PIN, true);
        on.updateValue(true);
    } else {
        stop();
        on.updateValue(false);
        digitalWrite(LED_PIN, false);
    }   
    prevTemp = temp.value;
    #endif
}


