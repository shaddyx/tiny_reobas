#include <Arduino.h>
#include "debug.h"
#include "config.h"
#include "pwm/pwm_control.h"
#include "state.h"
#include "adc/adc.h"
#include <adc_dac_temp_map.h>
#include "tiny_delay.h"

void stop(){
    debug_info("fan off");
    setPwm(0);
}

void setup(){
    OSCCAL = 82;    // calculated value for softwareSerial
    pinMode(THERMORESISTOR_PIN, INPUT);
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, 0);
}


State<bool> on(false);
bool cold_started = false;

void cold_start(){
    cold_started = true;
    setPwm(COLD_START_PWM);
    tiny_delay(COLD_START_DELAY);
}

void loop(){
    auto dac_value = adc_to_dac(getAdcValue());
    if (!cold_started && on.value && on.changeOlderThan(COLD_START_DELAY_AFTER_ON)){
        cold_start();
    }
    on.updateValue(dac_value > 0);
    if (!on.value){
        cold_started = false;
    }
    setPwm(dac_value);
}