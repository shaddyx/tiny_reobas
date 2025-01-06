#include <Arduino.h>
#include "debug.h"
#include "config.h"
#include "pwm/pwm_control.h"
#include "state.h"
#include "adc/adc.h"
#include <adc_dac_temp_map.h>
#include "tiny_delay.h"
#include "result.h"
#include "histeresis.h"
#include "smoother.h"

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
Smoother<uint8_t> smoother(SMOOTH_INTERVAL, 0);
// histeresis<int> histeresis(6, 0, 0, ADC_MAX);
bool cold_started = false;

void cold_start(){
    cold_started = true;
    smoother.current = COLD_START_PWM;
    setPwm(COLD_START_PWM);
    tiny_delay(COLD_START_DELAY);
    debug_init();
}

void loop(){
    auto adc_value = getAdcValue();

    // adc_value = histeresis.process(adc_value);
    auto dac_value = adc_to_dac(adc_value);
    smoother.target = dac_value;
    dac_value = smoother.poll();
    debug_info("ADCValue:", adc_value);
    debug_info("DACValue:", dac_value);
    if (!cold_started && on.value && on.changeOlderThan(COLD_START_DELAY_AFTER_ON)){
        cold_start();
    }
    if (!on.value && dac_value >= HISTERESIS_VALUE){
        on.updateValue(true);
    } else if (dac_value <= 0){
        on.updateValue(false);
    }

    if (!on.value){
        cold_started = false;
    }
    setPwm(on.value ? dac_value : 0);
}