#include <unity.h>
#include "adc_dac_temp_map.h"

void test_thermoresistor_calc(void){
    TEST_ASSERT_EQUAL_INT16(0, adc_to_dac(450));
    TEST_ASSERT_EQUAL_INT16(255, adc_to_dac(200));

    TEST_ASSERT_EQUAL_INT16(0, adc_to_dac(450));
    TEST_ASSERT_EQUAL_INT16(25, adc_to_dac(400));
    TEST_ASSERT_EQUAL_INT16(204, adc_to_dac(292));
}
