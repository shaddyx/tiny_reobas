#include <Arduino.h>
#include <avr/pgmspace.h>
#include "util.h"

const int16_t vals[] PROGMEM = {73, 84, 96, 110, 126, 145, 167, 192, 221, 254, 291, 333, 379, 429, 482, 538, 595, 652, 707, 759};
//const int16_t temp[] PROGMEM = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5};

#define TEMPERATURE_TABLE_READ(i) pgm_read_word(&temp[i])
#define ADC_TABLE_READ(i) pgm_read_word(&vals[i])

int8_t calc_address(int16_t adc_value){
    if (adc_value < ADC_TABLE_READ(0)){
        return 0;
    }
    for (int i=0; i < ARRAY_SIZE(vals); i++){
        if (adc_value <= ADC_TABLE_READ(i)){
            return i;
        }
    }
    return ARRAY_SIZE(vals) - 1;
}

int16_t calc_temperature(int16_t adcsum){
    return 100 - calc_address(adcsum) * 5;
    //return TEMPERATURE_TABLE_READ(calc_address(adcsum));
}