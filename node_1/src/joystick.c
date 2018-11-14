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
	static int last_slider_r = 0;
	static int last_button_r = 0;
	static int last_slider_l = 0;
	static int last_button_l = 0;

    
    int x = read_joystick_x();
    int y = read_joystick_y();
	int z = read_joystick_select();
	int slider_r = read_right_slider();
	int button_r = read_right_button_select();
    int slider_l = read_left_slider();
	int button_l = read_left_button_select();


    if(x != last_x || y != last_y) {
        can_message_t msg;
        msg.id = MSG_JOYSTICK_POS;
        msg.length = 2;
        msg.data[0] = x + 127;
        msg.data[1] = y + 127;
        can_msg_send(&msg);
        printf("X: %d, Y: %d\n\r", msg.data[0], msg.data[1]);
    }
	if((z && !last_z) || (button_r && !last_button_r) || (button_l && !last_button_l)) {
		can_message_t msg;
		msg.id = MSG_BUTTON_CLICK;
		msg.length = 3;
		msg.data[0] = z;
		msg.data[1] = button_r;
		msg.data[2] = button_l;
		printf("Click\n\r");
		can_msg_send(&msg);
	}

	/*if((slider_r >= last_slider_r + 2) || (slider_r <= last_slider_r -2)) {
		can_message_t msg;
        msg.id = MSG_SLIDER_POS;
        msg.length = 1;
        msg.data[0] = slider_r + 127;
        can_msg_send(&msg);
        last_slider_r = slider_r;
	}
	*/

    last_x = x;
    last_y = y;
	last_z = z;
	last_button_r = button_r;
    last_slider_l = slider_l;
	last_button_l = button_l;
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
	return (PINB & (1 << PB1));
}

int read_right_button_select(){
	return (PINB & (1 << PB2));
}

<<<<<<< HEAD
=======
/*int get_slider_position(){
	return last_slider_r; //kan vi gjøre denne global?
}
*/
>>>>>>> 227df9588f2aee14c37852968cf501059ec2b88b
