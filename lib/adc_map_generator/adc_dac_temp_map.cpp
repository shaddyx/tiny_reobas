#include "result.h"
#include "../util.h"

#if defined(UNIT_TEST) || defined(PIO_UNIT_TESTING)
    #include <stdint.h>
    const int16_t vals[] = TEMP_VALUES; 
    #define ADC_TABLE_READ(i) vals[i]
    #define abs(a) a < 0 ? -a : a
#else // UNIT_TEST
    #include <Arduino.h>
    #include <avr/pgmspace.h>
    const uint16_t vals[] PROGMEM = TEMP_VALUES; 
    #define ADC_TABLE_READ(i) pgm_read_word(&vals[i])
#endif // HW_MODE

inline int distance(int a, int b){
    return abs(a - b);
}

unsigned int calc_address(unsigned int adc_value){
    int closest = 0;
    for (unsigned int i=0; i < ARRAY_SIZE(vals); i += 2){
        int adc_table_val = ADC_TABLE_READ(i);
        int closest_val = ADC_TABLE_READ(closest);
        if (distance(adc_value, closest_val) >= distance(adc_table_val, adc_value)){
            closest = i;
        }
    }
    return closest + 1;
}

unsigned int adc_to_dac(unsigned int adc){
    return ADC_TABLE_READ(calc_address(adc));  
}