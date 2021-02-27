#include <avr/io.h>
#include "config.h"
#include "attiny13.h"
#ifdef __AVR_ATtiny13__
    void pwm_init(void){
        DDRB |= _BV(FAN_PIN); // set PWM pin as OUTPUT
        TCCR0A |= _BV(WGM01)|_BV(WGM00); // set timer mode to FAST PWM
        //  COM0A1 -> pb0
        //  COM0B1 -> pb1
        TCCR0A |= _BV(FAN_PIN == PB0 ? COM0A1: COM0B1); // connect PWM signal to pin (AC0A => PB0)
    }

    void pwm_set_frequency(uint32_t N){
        TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | N; // set prescaler
    }

    void pwm_set_duty(uint8_t duty){
        OCR0A = duty; // set the OCRnx
    }
    void pwm_stop(){
        TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
        TCCR0A = 0;    //   disconnect register from pin
    }
#endif