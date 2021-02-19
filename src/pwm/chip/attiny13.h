#pragma once

#ifdef __AVR_ATtiny13__
    #include <Arduino.h>
    #include "config.h"
    #define PWM_FREQ_N_1    (_BV(CS00))
    #define PWM_FREQ_N_8    (_BV(CS01))
    #define PWM_FREQ_N_64   (_BV(CS01)|_BV(CS00))
    #define PWM_FREQ_N_256  (_BV(CS02))
    #define PWM_FREQ_N_1024 (_BV(CS02)|_BV(CS00))


    #if FAN_PIN!=PB0
        #error "Attiny13 could use only PB0 because PB1 has a bug"
    #endif

    void pwm_init(void);
    void pwm_set_frequency(uint32_t N);
    void pwm_set_duty(uint8_t duty);
    void pwm_stop();
#endif

