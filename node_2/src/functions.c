#include "functions.h"
#include "joystick.h"
#include <std.io>
int length = 5;
int highscores[length] = {0,0,0,0,0};


int button_is_pressed(){
	if (read_joystick_select() > 0){
		return 1;
	}
	return 0;
}

int ball_break_led(){
	//if (ball has broken led)
	//	return 1;
	return 0;
}


void update_highscore(int score){

	for (i = 0 ; i < length ; i++){
		if score > highscores[i]{
			for (j = i+1 ; j <= length-i ; j++){
				highscores[j] = highscores[j-1];
			}
			highscores[i] = score;	
		}
	}
}


void quit(){
	
}

 can_message_t msg;
        msg.id = 1;
        msg.length = 2;
        msg.data[0] = x + 127;
        msg.data[1] = y + 127;
		msg.data[2] = z;
        can_msg_send(&msg);