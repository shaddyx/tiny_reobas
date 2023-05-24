#include "result.h"
#include "../util.h"

#if defined(UNIT_TEST) || defined(PIO_UNIT_TESTING)
    #include <stdint.h>
    const int16_t vals[] = TEMP_VALUES; 
    #define ADC_TABLE_READ(i) vals[i]
#else // UNIT_TEST
    #include <Arduino.h>
    #include <avr/pgmspace.h>
    const uint16_t vals[] PROGMEM = TEMP_VALUES; 
    #define ADC_TABLE_READ(i) pgm_read_word(&vals[i])
#endif // HW_MODE

unsigned int calc_address(unsigned int adc_value){
    for (unsigned int i=0; i < ARRAY_SIZE(vals); i += 2){
        if (adc_value >= ADC_TABLE_READ(i)){
            return i + 1;
        }
    }
    return ARRAY_SIZE(vals) - 1;
}

unsigned int adc_to_dac(unsigned int adc){
    return ADC_TABLE_READ(calc_address(adc));  
}