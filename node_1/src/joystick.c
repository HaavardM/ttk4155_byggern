#include "joystick.h"
#include "mcp2515.h"
#include "can.h"
#include "adc.h"
#include <avr/io.h>
#include "can_msg_defines.h"

uint8_t remote_enabled = 0;


/*---Exposed functions---------------------------*/
void init_joystick() {
	DDRB &= ~(1 << PB0);	
	PORTB |= (1 << PB0);	
}

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

int read_joystick_select() {	
	return !(PINB & (1 << PB0));
}

int read_left_slider() {
	static int lst = 0;
	int new = adc_read(2);
	int ret = (5 * lst + new) / 6;
	lst = ret;
	return ret;
}

int read_right_slider() {
	static int lst = 0;
	int new = adc_read(3);
	int ret = (5 * lst + new) / 6;
	lst = ret;
	return ret;
}

int read_left_button_select(){
	return (PINB & (1 << PB1));
}

int read_right_button_select(){
	return (PINB & (1 << PB2));
}


void joystick_remote_enable() {
	remote_enabled = 1;
}

void joystick_remote_disable() {
	remote_enabled = 0;
}

void joystick_update() {
    static int last_x = 0;
    static int last_y = 0;
	static int last_z = 0;
	static int last_slider_r = 0;
	static int last_button_r = 0;
	static int last_slider_l = 0;
	static int last_button_l = 0;

	//dont send commands if not neccessary
	if(!remote_enabled) {
		return;
	}

    
    int x = read_joystick_x();
    int y = read_joystick_y();
	int z = read_joystick_select();
	int slider_r = read_right_slider();
	int button_r = read_right_button_select();
    int slider_l = read_left_slider();
	int button_l = read_left_button_select();

	//If the position of the joystick has changed since last update
    if(x != last_x || y != last_y) {
        can_message_t msg;
        msg.id = MSG_JOYSTICK_POS;
        msg.length = 2;
        msg.data[0] = x + 127;
        msg.data[1] = y + 127;
        can_msg_send(&msg);
    }
    //If any of the buttons have been activated since last update
	if((z && !last_z) || (button_r && !last_button_r) || (button_l && !last_button_l)) {
		can_message_t msg;
		msg.id = MSG_BUTTON_CLICK;
		msg.length = 3;
		msg.data[0] = z;
		msg.data[1] = button_r;
		msg.data[2] = button_l;
		can_msg_send(&msg);
	}
	//If the slider positions have changed since last update
	//Plus and minus 2 to make it less sensitive to noise
	if((slider_r >= last_slider_r + 2) || (slider_r <= last_slider_r -2)) {
		can_message_t msg;
        msg.id = MSG_SLIDER_POS;
        msg.length = 1;
        msg.data[0] = slider_r + 127;
        can_msg_send(&msg);
        last_slider_r = slider_r;
	}
	

    last_x = x;
    last_y = y;
	last_z = z;
	last_button_r = button_r;
    last_slider_l = slider_l;
	last_button_l = button_l;
}

