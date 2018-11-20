#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define PRESCALE 1024
#define FREQUENCY (F_CPU / PRESCALE)
#define PERIOD 4 / 100
#define TIMER_STEPS (FREQUENCY * PERIOD - 1)

#include "pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include <avr/iom2560.h>

void stop_timer() {
    TCCR4B &=~((1<<CS42) | (1<<CS41) | (1<<CS40));
}

ISR(TIMER4_COMPA_vect) {
    //Clear pin after timeout
    TIMSK4 &=~(1<<OCIE4A);    
    PORTB |=(1 << PINB4);
    stop_timer();
}

void start_timer() {
    //Reset timer and start
    TCCR4B |= (1 << CS42) | (1 << CS40);
    TCCR4B &=~(1<<CS41);
    TCNT4 = 0;
}


void solenoid_init() {
    cli();
    //Set prescale to 1024 and CTC mode
    TCCR4B = (1 << WGM42);
    DDRB |= (1<<PB4);
    PORTB |= (1 << PINB4);
    //Set timer
    OCR4A = TIMER_STEPS;
    sei();
}

void solenoid_fire() {
    //Create a pulse
    PORTB &= ~(1 << PINB4);
    TIMSK4 |= (1 << OCIE4A);
    start_timer();
}