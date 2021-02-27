#include "config.h"
#include "debug.h"
#ifdef __AVR_ATtiny13__
    #include "chip/attiny13.h"
#endif
#ifdef __AVR_ATtiny45__
    #include "chip/attiny45.h"
#endif

#ifdef ARDUINO_AVR_UNO
    #include "chip/uno.h"
#endif


bool initialized = false;

void stopPwm(){
    initialized = false;
    pwm_stop();
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, 0);
}

void setPwm(uint8_t pwm){
    if (pwm == 0){
        stopPwm();
        return;
    }
    if (pwm >= 255){
        stopPwm();
        digitalWrite(FAN_PIN, 1);
        return;
    } 

    if (!initialized){
        pwm_init();
        pwm_set_frequency(PWM_FREQ_N_1);
        initialized = true;
    }
    pwm_set_duty(pwm);
}
void setPwmPercents(uint8_t pwm){
    auto duty = pwm * 255 / 100;
    debug_info("duty:", duty, " pwm:", pwm);
    setPwm(duty);
}
