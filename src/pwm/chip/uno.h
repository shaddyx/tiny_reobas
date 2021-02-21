#pragma once
#include <Arduino.h>
#include "config.h"
#ifdef ARDUINO_AVR_UNO
    #define PWM_FREQ_N_1    (_BV(CS00))
    #define PWM_FREQ_N_8    (_BV(CS01))
    #define PWM_FREQ_N_64   (_BV(CS01)|_BV(CS00))
    #define PWM_FREQ_N_256  (_BV(CS02))
    #define PWM_FREQ_N_1024 (_BV(CS02)|_BV(CS00))
    void pwm_init(void);
    void pwm_set_frequency(uint32_t N);
    void pwm_set_duty(uint8_t duty);
    void pwm_stop();
#endif

