#include "ir.h"
#include <avr/io.h>

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define THRESHOLD 200

/*---Exposed functions---------------------------*/
void ir_init() {
    DDRA &=~(1 << PA0);
    //Prescale 128, enable ADC and interrupt
    ADCSRA = (1 << ADEN) | 3;
    ADMUX |= (1 << REFS0);
    ir_is_blocked();
}

uint8_t ir_is_blocked() {
    //Start conversion 
    ADCSRA |= (1 << ADSC);
    //Wait for conversion to complete
    while((ADCSRA & (1 << ADSC)));
    uint16_t value = ADC;
    if(value < THRESHOLD) {
        return 1;
    } else {
        return 0;
    }
}
