#include "joystick.h"
#include "adc.h"
#include <avr/io.h>

int read_joystick_x(){
	int pos_x = adc_read(1);
	if (pos_x < 10 && pos_x > -10){
		pos_x = 0;
	}
	return pos_x;
}
int read_joystick_y() {
	int pos_y = adc_read(0);
	if (pos_y < 10 && pos_y > -10){
		pos_y = 0;
	}
	return pos_y;
}

void init_joystick() {
	DDRB &= ~(1 << PB0);	
	PORTB |= (1 << PB0);	
}

int read_joystick_select() {	
	return !(PINB & (1 << PB0));
}
