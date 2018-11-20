#include <avr/io.h>
#include "led.h"

/*---Exposed functions---------------------------*/
void led_init(){
	DDRC |= (1 << PC1);
	PORTC |= (1 << PC1);
}

void led_turn_on(){
	PORTC &= ~(1 << PC1);
}

void led_turn_off(){
	PORTC |= (1 << PC1);
}
