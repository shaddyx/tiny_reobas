#include <unity.h>
#include "state.h"
#include <ArduinoFake.h>

using namespace fakeit;
void test_state(void){
    When(Method(ArduinoFake(), millis)).AlwaysReturn(0);
    State<bool> on(false);
    on.updateValue(true);
    TEST_ASSERT(on.value);
    TEST_ASSERT(on.isChanged(false));
    on.updateValue(false);
    TEST_ASSERT(!on.value);
    TEST_ASSERT(on.isChanged(true));
}
