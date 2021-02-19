#include "../util.h"
#include "table_calculator/result.h"

#ifdef UNIT_TEST
    #include <stdint.h>
    const int16_t vals[] = TEMP_VALUES; 
    #define ADC_TABLE_READ(i) vals[i]
#else // UNIT_TEST
    #include <Arduino.h>
    #include <avr/pgmspace.h>
    const uint16_t vals[] PROGMEM = TEMP_VALUES; 
    #define ADC_TABLE_READ(i) pgm_read_word(&vals[i])
#endif // HW_MODE

int8_t calc_address(uint16_t adc_value){
    if (adc_value < ADC_TABLE_READ(0)){
        return 0;
    }
    for (unsigned int i=0; i < ARRAY_SIZE(vals); i++){
        if (adc_value <= ADC_TABLE_READ(i)){
            return i;
        }
    }
    return ARRAY_SIZE(vals) - 1;
}

int16_t calc_temperature(uint16_t adcsum){
    return ADC_MAX_TEMP - calc_address(adcsum) * ADC_TEMP_STEP;
}