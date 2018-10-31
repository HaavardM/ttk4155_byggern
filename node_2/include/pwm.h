#ifndef PWM_H
#define PWM_H
#include <avr/io.h>

void pwm_init();

//Set duty cycle, 0-255
void pwm_set_duty(uint8_t duty);

#endif
