#include <unity.h>
#include "temp_to_percentage.h"

void test_percentage(void){
    TEST_ASSERT_EQUAL_INT(0, calc_percentage(1, 1, 100));
    TEST_ASSERT_EQUAL_INT(9, calc_percentage(10, 1, 100));
    TEST_ASSERT_EQUAL_INT(19, calc_percentage(20, 1, 100));
    TEST_ASSERT_EQUAL_INT(29, calc_percentage(30, 1, 100));
    TEST_ASSERT_EQUAL_INT(39, calc_percentage(40, 1, 100));
    TEST_ASSERT_EQUAL_INT(49, calc_percentage(50, 1, 100));
    TEST_ASSERT_EQUAL_INT(59, calc_percentage(60, 1, 100));
    TEST_ASSERT_EQUAL_INT(69, calc_percentage(70, 1, 100));
    TEST_ASSERT_EQUAL_INT(79, calc_percentage(80, 1, 100));
    TEST_ASSERT_EQUAL_INT(89, calc_percentage(90, 1, 100));
    TEST_ASSERT_EQUAL_INT(100, calc_percentage(1000, 1, 100));
    TEST_ASSERT_EQUAL_INT(0, calc_percentage(0, 1, 100));
}