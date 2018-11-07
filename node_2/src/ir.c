#include "ir.h"
#include <avr/io.h>

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define THRESHOLD 300

void default_cb() {
    printf("Blocked!\n\r");
}

void_cb_t on_blocked = default_cb;

ISR(ADC_vect) {
    static int blocked = 0;
    uint16_t value =  ADC;

    //Determine if value is of interest
    if(value < THRESHOLD) {
        if(!blocked) {
            blocked = 1;
            on_blocked();
        }
    } else {
        blocked = 0;
    }

    //Start ADC
    ADCSRA |= (1 << ADSC);
}

void ir_init() {
    DDRA &=~(1 << PA0);
    //Prescale 128, enable ADC and interrupt
    ADCSRA = (1 << ADEN) | (1 << ADIE) | 3;
    ADMUX |= (1 << REFS0);
}

void ir_start() {
    ADCSRA |= (1 << ADEN)| (1 << ADSC);
}

void ir_stop() {
    ADCSRA &= ~(1 << ADEN);
}


void ir_set_on_blocked(void_cb_t cb) {
    if(cb == NULL) {
        return;
    }
    on_blocked = cb;
}
