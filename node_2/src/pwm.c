#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define PRESCALE 8
#define PWM_FREQUENCY (F_CPU / PRESCALE)
#define PWM_PERIOD 20 / 1000
#define PWM_TIMER_STEPS (PWM_FREQUENCY * PWM_PERIOD - 1)
#define PWM_MIN (PWM_FREQUENCY * 9)  / 10000 
#define PWM_MAX (PWM_FREQUENCY * 21) / 10000

#include "pwm.h"
#include "avr/io.h"

void pwm_set_prescale() {
    TCCR1B |= (1 << CS11);
    TCCR1B &= ~((1 << CS12) | (1 << CS10));
}

void pwm_init() {
    //Enable PWM on PB5
    TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    TCCR1B |= (1 << CS10);
    ICR1 = PWM_TIMER_STEPS;
    DDRB |= (1 << PB5);
    pwm_set_prescale();
    
    pwm_set_duty(127);
}

void pwm_set_duty(uint8_t duty) {
    uint16_t value = ((float) duty / 255.0) * (PWM_MAX - PWM_MIN) + PWM_MIN;
    if(value < PWM_MIN) {
        value = PWM_MIN;
    } else if(value > PWM_MAX) {
        value = PWM_MAX;
    }
    //Invert
    value = PWM_TIMER_STEPS - value;
    OCR1A = value;
    OCR1A = value;
}
