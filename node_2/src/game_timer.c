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

void_cb_t timer_callback = NULL;

ISR(TIMER3_COMPA_vect) {
    if(timer_callback != NULL) {
        timer_callback();
    }
}

void enable_interrupt() {
    TIMSK3 |= (1 << OCIE3A);
}

void disable_interrupt() {
    TIMSK3 &= ~(1 << OCIE3A);
}

void game_timer_init() {
    cli();
    //Set prescale to 1024 and CTC mode
    TCCR3B = (1 << CS30) | (1 << CS32) | (1 << WGM32);
    //Set timer
    OCR3A = TIMER_STEPS;
    sei();
}

void game_timer_set_on_elapsed(void_cb_t cb) {
    timer_callback = cb;
}

void game_timer_start() {
    enable_interrupt();
}

void game_timer_stop() {
    disable_interrupt();
}