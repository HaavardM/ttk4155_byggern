#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "game_timer.h"

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define PRESCALE 1024
#define FREQUENCY (F_CPU / PRESCALE)
#define PERIOD 1
#define TIMER_STEPS (FREQUENCY * PERIOD - 1)

#define SECONDS_PER_OVERFLOW (419 / 100)
#define TIMER_ENABLE_BITS ((1 << CS30) | (1 << CS32))

uint16_t ovf = 0;

ISR(TIMER3_OVF_vect)
{
    ++ovf; 
}

void game_timer_init() {
    sei();
}

void game_timer_start() {
    ovf = 0;
    TCNT3 = 0;
    TIMSK3 |= (1 << TOIE3);
    TCCR3B |= TIMER_ENABLE_BITS;
}

void game_timer_stop() {
    //Disable interrupt and timer
    TIMSK3 &=~(1 << TOIE3);
    TCCR3B &=~TIMER_ENABLE_BITS;
}

uint16_t game_timer_get() {
    return (TCNT3 / FREQUENCY) + ((uint32_t)ovf * SECONDS_PER_OVERFLOW);
}

