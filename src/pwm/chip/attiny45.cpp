#include <avr/io.h>
#include <Arduino.h>
#include "config.h"
#include "attiny45.h"

#ifdef __AVR_ATtiny45__
    void pwm_init(void){
       //TCCR0A = TCCR0A & 0b11111000 | 0b001;
    }

    void pwm_set_frequency(uint32_t N){
        TCCR0B = TCCR0B & 0b11111000 | 0b001;
    }

    void pwm_set_duty(uint8_t duty){
        analogWrite(FAN_PIN, duty);
    }
    void pwm_stop(){
        analogWrite(FAN_PIN, 0);
    }
#endif