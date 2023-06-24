#include <Arduino.h>
#include "debug.h"
#include "config.h"
#include "pwm/pwm_control.h"
#include "state.h"
#include "adc/adc.h"
#include <adc_dac_temp_map.h>
#include "tiny_delay.h"
#include "result.h"

void stop(){
    debug_info("fan off");
    setPwm(0);
}

void setup(){
    OSCCAL = 82;    // calculated value for softwareSerial
    pinMode(THERMORESISTOR_PIN, INPUT);
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, 0);
    debug_init();
    #if DEBUG_PWM == 1
        setPwm(128);
        while (true) {}
    #endif
}


State<bool> on(false);
bool cold_started = false;

void cold_start(){
    cold_started = true;
    setPwm(COLD_START_PWM);
    tiny_delay(COLD_START_DELAY);
    debug_init();
}

void loop(){
    auto adc_value = getAdcValue();
    auto dac_value = adc_to_dac(adc_value);
    debug_info("ADCValue:", adc_value);
    debug_info("DACValue:", dac_value);
    if (!cold_started && on.value && on.changeOlderThan(COLD_START_DELAY_AFTER_ON)){
        cold_start();
    }
    if (!on.value && dac_value >= HYSTERESIS_VALUE){
        on.updateValue(true);
    } else if (dac_value <= 0){
        on.updateValue(false);
    }

    if (!on.value){
        cold_started = false;
    }
    setPwm(on.value ? dac_value : 0);
}