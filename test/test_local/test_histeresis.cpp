#include <unity.h>
#include "histeresis.h"
histeresis histeresis(10, 0, 0, 100);

void test_histeresis_after_init(void){
    TEST_ASSERT_EQUAL(0, histeresis.current_min);
    TEST_ASSERT_EQUAL(10, histeresis.current_max);
}

void test_histeresis_0_boundary(void){
    TEST_ASSERT_EQUAL(0, histeresis.process(0));
    TEST_ASSERT_EQUAL(0, histeresis.process(3));
    TEST_ASSERT_EQUAL(0, histeresis.process(5));
    TEST_ASSERT_EQUAL(0, histeresis.process(7));
    TEST_ASSERT_EQUAL(0, histeresis.process(9));
        // should remain the same
    TEST_ASSERT_EQUAL(0, histeresis.current_min);
    TEST_ASSERT_EQUAL(10, histeresis.current_max);
}

void test_histeresis_5_0_10(void){
    TEST_ASSERT_EQUAL(0, histeresis.process(5));
    // should remain the same
    TEST_ASSERT_EQUAL(0, histeresis.current_min);
    TEST_ASSERT_EQUAL(10, histeresis.current_max);
}

void test_histeresis_11_0_10_should_move(void){
    TEST_ASSERT_EQUAL(11, histeresis.process(11));
    // should remain the same
    TEST_ASSERT_EQUAL(6, histeresis.current_min);
    TEST_ASSERT_EQUAL(16, histeresis.current_max);
}

void test_histeresis_50_0_10_should_move(void){
    histeresis.current_val = 1;
    histeresis.current_min = 0;
    histeresis.current_max = 10;
    TEST_ASSERT_EQUAL(50, histeresis.process(50));
    // should remain the same
    TEST_ASSERT_EQUAL(45, histeresis.current_min);
    TEST_ASSERT_EQUAL(55, histeresis.current_max);
}

void test_histeresis_100_0_10_upper_boundary(void){
    histeresis.current_val = 1;
    histeresis.current_min = 0;
    histeresis.current_max = 10;
    TEST_ASSERT_EQUAL(100, histeresis.process(100));
    // should remain the same
    TEST_ASSERT_EQUAL(90, histeresis.current_min);
    TEST_ASSERT_EQUAL(100, histeresis.current_max);
}

void test_histeresis(void){
    
    RUN_TEST(test_histeresis_after_init);
    RUN_TEST(test_histeresis_0_boundary);
    RUN_TEST(test_histeresis_5_0_10);
    RUN_TEST(test_histeresis_11_0_10_should_move);
    RUN_TEST(test_histeresis_50_0_10_should_move);
    RUN_TEST(test_histeresis_100_0_10_upper_boundary);
}

