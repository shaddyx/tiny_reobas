#include <Arduino.h>
#include "../config.h"
#include "../tiny_delay.h"
int getAdcValue() {
    uint16_t result = 0;
    for (int i = 0; i < TEMP_NUM_READS; i++){
       result += analogRead(THERMORESISTOR_PIN) * 10;
       tiny_delay(10);
    }
    return (result / TEMP_NUM_READS) / 10;
}