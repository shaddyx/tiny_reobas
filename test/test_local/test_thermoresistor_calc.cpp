#include <unity.h>
#include "table_calculator/result.h"
#include "thermoresistor_calc.h"

#if SERIESRESISTOR==90000
    void test_thermoresistor_calc(void){
        TEST_ASSERT_EQUAL_INT16(80, calc_temperature(10));
        TEST_ASSERT_EQUAL_INT16(48, calc_temperature(300));
        TEST_ASSERT_EQUAL_INT16(18, calc_temperature(600));
        TEST_ASSERT_EQUAL_INT16(12, calc_temperature(1600));
        TEST_ASSERT_EQUAL_INT16(12, calc_temperature(2600));
        TEST_ASSERT_EQUAL_INT16(80, calc_temperature(0));
    }
#endif

#if SERIESRESISTOR==100000
    void test_thermoresistor_calc(void){
        TEST_ASSERT_EQUAL_INT16(80, calc_temperature(10));
        TEST_ASSERT_EQUAL_INT16(46, calc_temperature(300));
        TEST_ASSERT_EQUAL_INT16(16, calc_temperature(600));
        TEST_ASSERT_EQUAL_INT16(12, calc_temperature(1600));
        TEST_ASSERT_EQUAL_INT16(12, calc_temperature(2600));
        TEST_ASSERT_EQUAL_INT16(80, calc_temperature(0));
    }
#endif


