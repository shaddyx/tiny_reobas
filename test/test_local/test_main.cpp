#include <unity.h>
#include "test_calc.h"
#include "test_thermoresistor_calc.h"

int main(){
    UNITY_BEGIN(); // start unit testing
    RUN_TEST(test_percentage);
    RUN_TEST(test_thermoresistor_calc);
    UNITY_END(); // stop unit testing
}