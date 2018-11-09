#include "joystick.h"
#include "mcp2515.h"
#include "can.h"
#include "adc.h"
#include <avr/io.h>
#include "can_msg_defines.h"

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
	static int last_z = 0;
    
    int x = read_joystick_x();
    int y = read_joystick_y();
	int z = read_joystick_select();
    
    if(x != last_x || y != last_y) {
        can_message_t msg;
        msg.id = MSG_JOYSTICK_POS;
        msg.length = 2;
        msg.data[0] = x + 127;
        msg.data[1] = y + 127;
        can_msg_send(&msg);
        printf("X: %d, Y: %d\n\r", msg.data[0], msg.data[1]);
    }
	if(z != last_z) {
		can_message_t msg;
		msg.id = MSG_BUTTON_CLICK;
		msg.length = 1;
		msg.data[0] = z;
		can_msg_send(&msg);
	}
    last_x = x;
    last_y = y;
	last_z = z;
}

int read_left_slider() {
	int left_slider = adc_read(2);
	return left_slider;
}

int read_right_slider() {
	int right_slider = adc_read(3);
	return right_slider;
}

int read_left_button_select(){
	return !(PINB & (1 << PB1));
}

int read_right_button_select(){
	return !(PINB & (1 << PB2));
}
