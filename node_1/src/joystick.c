#include "joystick.h"
#include "mcp2515.h"
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


void joystick_update() {
    static int last_x = 0;
    static int last_y = 0;
    
    int x = read_joystick_x();
    int y = read_joystick_y();
    
    if(x != last_x || y != last_y) {
        can_message_t msg;
        msg.id = 1;
        msg.length = 2;
        msg.data[0] = x + 127;
        msg.data[1] = y + 127;
        can_msg_send(&msg);
    }
    last_x = x;
    last_y = y;
}
