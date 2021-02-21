#ifdef __AVR_ATtiny45__
    #include <avr/io.h>
    #include <Arduino.h>
    #include "config.h"
    #include "attiny45.h"
    #include <FastPwmPin.h>
    void pwm_init(void){
       //TCCR0A = TCCR0A & 0b11111000 | 0b001;
    }

    void pwm_set_frequency(uint32_t N){
        
        // TCCR0A = 3<<COM0A0 | 3<<COM0B0 | 3<<WGM00;
        // TCCR0B = 0<<WGM02 | 3<<CS00; // Optional; already set


        TCCR1 = 1<<PWM1A | 1<<COM1A0 | 1<<CS10;
        GTCCR = 0<<PWM1B | 1<<COM1B0;
        
    }

    void pwm_set_duty(uint8_t duty){
        OCR0A = 255 - duty;
    }

    void pwm_stop(){
        //TCCR0B = 0<<WGM02;
    }
#endif