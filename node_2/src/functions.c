#include "functions.h"
#include <stdio.h>
#include "can.h"
#include "can_msg_defines.h"

#define LENGTH 5
int highscores[LENGTH] = {0,0,0,0,0};
can_message_t last_joystick_msg;

void game_on_can_msg(can_message_t* msg_p) {
	if(msg_p->id == joystick_pos) {
		last_joystick_msg = *msg_p;
	}
}

int button_is_pressed() {
	if (last_joystick_msg.id == 3){
		return last_joystick_msg.data[2] == 1;
	}
	return 0;
}

int ball_break_led(){
	//if (ball has broken led)
	//	return 1;
	return 0;
}


void update_highscore(int score){
	
	for (int i = 0 ; i < LENGTH; i++){
		if(score > highscores[i]){
			for (int j = i+1 ; j <= LENGTH-i ; j++){
				highscores[j] = highscores[j-1];
			}
			highscores[i] = score;	
		}
	}
}


void quit(){
	
}
