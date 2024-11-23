#include <unity.h>
#include "hysteresis.h"
Hysteresis hysteresis(10, 0, 0, 100);

void test_hysteresis_after_init(void){
    TEST_ASSERT_EQUAL(0, hysteresis.current_min);
    TEST_ASSERT_EQUAL(10, hysteresis.current_max);
}

void test_hysteresis_0_boundary(void){
    TEST_ASSERT_EQUAL(0, hysteresis.process(0));
    TEST_ASSERT_EQUAL(0, hysteresis.process(3));
    TEST_ASSERT_EQUAL(0, hysteresis.process(5));
    TEST_ASSERT_EQUAL(0, hysteresis.process(7));
    TEST_ASSERT_EQUAL(0, hysteresis.process(9));
        // should remain the same
    TEST_ASSERT_EQUAL(0, hysteresis.current_min);
    TEST_ASSERT_EQUAL(10, hysteresis.current_max);
}

void test_hysteresis_5_0_10(void){
    TEST_ASSERT_EQUAL(0, hysteresis.process(5));
    // should remain the same
    TEST_ASSERT_EQUAL(0, hysteresis.current_min);
    TEST_ASSERT_EQUAL(10, hysteresis.current_max);
}

void test_hysteresis_11_0_10_should_move(void){
    TEST_ASSERT_EQUAL(11, hysteresis.process(11));
    // should remain the same
    TEST_ASSERT_EQUAL(6, hysteresis.current_min);
    TEST_ASSERT_EQUAL(16, hysteresis.current_max);
}

void test_hysteresis_50_0_10_should_move(void){
    hysteresis.current_val = 1;
    hysteresis.current_min = 0;
    hysteresis.current_max = 10;
    TEST_ASSERT_EQUAL(50, hysteresis.process(50));
    // should remain the same
    TEST_ASSERT_EQUAL(45, hysteresis.current_min);
    TEST_ASSERT_EQUAL(55, hysteresis.current_max);
}

void test_hysteresis_100_0_10_upper_boundary(void){
    hysteresis.current_val = 1;
    hysteresis.current_min = 0;
    hysteresis.current_max = 10;
    TEST_ASSERT_EQUAL(100, hysteresis.process(100));
    // should remain the same
    TEST_ASSERT_EQUAL(90, hysteresis.current_min);
    TEST_ASSERT_EQUAL(100, hysteresis.current_max);
}

void test_hysteresis(void){
    
    RUN_TEST(test_hysteresis_after_init);
    RUN_TEST(test_hysteresis_0_boundary);
    RUN_TEST(test_hysteresis_5_0_10);
    RUN_TEST(test_hysteresis_11_0_10_should_move);
    RUN_TEST(test_hysteresis_50_0_10_should_move);
    RUN_TEST(test_hysteresis_100_0_10_upper_boundary);
}

