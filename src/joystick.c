#include "joystick.h"
#include "adc.h"


int read_joystick_x(){
	pos_x = read_adc(1);
	if (pos_x < 10 && pos_x > -10){
		pos_x = 0;
	}
	return pos_x;
}
int read_joystick_y() {
	pos_y = read_adc(2);
	if (pos_y < 10 && pos_y > -10){
		pos_y = 0;
	}
	return pos_y;
}

