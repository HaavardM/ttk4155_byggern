#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "motor_controller.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include "avr/iom2560.h"

#define PRESCALE 8
#define FREQUENCY (F_CPU / PRESCALE)
#define PERIOD 1 / 60
#define TIMER_STEPS (FREQUENCY * PERIOD - 1)


int motor_speed = 0;


#define K_P 1
#define K_I 1

#define MAX_ERROR MAX_INT / (K_P + 1)

int16_t setpoint = 0;
int16_t sum_error = 0;
int16_t last_value = 0;

//TODO Update frequently
int16_t current_value = 0;

ISR(TIMER5_COMPA_vect) {
    int16_t error = setpoint - current_value;

    int16_t p_term, i_term;

    if(error > MAX_ERROR) {
        p_term = MAX_ERROR;
    }



}

void PI_init() {
    TIMSK5 |= (1 << OCIE5A);
    TCCR5B |= (1 << CS51) | (1 << WGM52);
    OCR5A = TIMER_STEPS;
}




