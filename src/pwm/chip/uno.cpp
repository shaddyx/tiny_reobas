#ifdef ARDUINO_AVR_UNO
    #include <avr/io.h>
    #include <Arduino.h>
    #include "config.h"
    #include "uno.h"
    #include "debug.h"

    void pwm_init(void){
       pinMode(FAN_PIN, OUTPUT);
    }

    void pwm_set_frequency(uint32_t N){

    }
    void pwm_set_duty(uint8_t duty){
        analogWrite(FAN_PIN, duty);
    }

    void pwm_stop(){
        analogWrite(FAN_PIN, 0);
        digitalWrite(FAN_PIN, 0);
    }
#endif