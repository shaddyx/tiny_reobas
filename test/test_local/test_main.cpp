#include <unity.h>
#include "test_thermoresistor_calc.h"
#include "test_state.h"
#include "test_hysteresis.h"
#include <Emulation.h>

int main(){
    UNITY_BEGIN(); // start unit testing
    RUN_TEST(test_thermoresistor_calc);
    RUN_TEST(test_state);
    test_hysteresis();
    UNITY_END(); // stop unit testing
}