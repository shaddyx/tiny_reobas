#include <unity.h>
#include "adc_dac_temp_map.h"

void test_thermoresistor_calc(void){
    TEST_ASSERT_EQUAL_INT16(0, adc_to_dac(522));
    TEST_ASSERT_EQUAL_INT16(255, adc_to_dac(1024));

    TEST_ASSERT_EQUAL_INT16(0, adc_to_dac(526));
    TEST_ASSERT_EQUAL_INT16(25, adc_to_dac(570));
    TEST_ASSERT_EQUAL_INT16(102, adc_to_dac(650));
}
