#include "functions.h"
#include <stdio.h>
#include "can.h"
#include "can_msg_defines.h"

#define LENGTH 5
int highscores[LENGTH] = {0,1,2,3,4};
can_message_t last_joystick_msg;

void game_on_can_msg(can_message_t* msg_p) {
	if(msg_p->id == MSG_JOYSTICK_POS) {
		last_joystick_msg = *msg_p;
	}
}




void send_score(int score){
	can_message_t msg;
	msg->id = MSG_SCORE;
	msg->data = score;
	msg->length = 1;
	can_msg_send(&msg);
}
