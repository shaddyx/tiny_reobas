#include <unity.h>
#include "thermoresistor_calc.h"

void test_thermoresistor_calc(void){
    TEST_ASSERT_EQUAL_INT16(80, calc_temperature(10));
    TEST_ASSERT_EQUAL_INT16(48, calc_temperature(300));
    TEST_ASSERT_EQUAL_INT16(18, calc_temperature(600));
    TEST_ASSERT_EQUAL_INT16(12, calc_temperature(1600));
    TEST_ASSERT_EQUAL_INT16(80, calc_temperature(0));
}
