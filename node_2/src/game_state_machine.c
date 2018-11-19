#include "game_state_machine.h"
#include "game_timer.h"
#include "ir.h"
#include "functions.h"
#include "can_msg_defines.h"
#include <stdio.h>
#include <util/delay.h>

fsm_state_e state_game_over();
fsm_state_e state_running();
fsm_state_e state_wait();
fsm_state_e state_start_game();

fsm_state_func state_vector[FSM_NUM_STATES] = 
{
	state_start_game, state_wait, state_running, state_game_over
};

int button_flag = 0;
int ir_flag = 0;
uint16_t score = 0;
fsm_state_e state = STATE_START_GAME;

void timer_elapsed() {
	score += 1;
}
void set_button_flag(){
 	button_flag = 1;
}

void game_init(){
	state = STATE_START_GAME;
	button_flag = 0;
	game_timer_set_on_elapsed(timer_elapsed);
}

fsm_state_e state_start_game() {
	printf("State start game\n\r");
	score = 0;
	button_flag = 0;
	printf("State wait\n\r");
	return STATE_WAIT;
}

fsm_state_e state_wait() {
	if (button_flag) {
		printf("Nå er vi inne der det skal endre seg til running\n\r");
		game_timer_start();
		printf("State running\n\r");
		return STATE_RUNNING;
	}return STATE_WAIT;
}

fsm_state_e state_running() {
	button_flag = 0;
	if (ir_is_blocked()) {			
		game_timer_stop();
		printf("state game over\n\r");
		return STATE_GAME_OVER;		
	}return STATE_RUNNING; 
}

fsm_state_e state_game_over() {
	ir_flag = 0;	
	can_message_t msg;
	msg.id = MSG_GAME_OVER;
	msg.length = 2;
	//HIGH byte
	msg.data[0] = score / 256; 
	//LOW byte
	msg.data[1] = score % 256;
	can_msg_send(&msg);
	return STATE_START_GAME;							
}


 void game_loop_once() {
 	///Get next state function
    fsm_state_func func = state_vector[state];
    if(func != NULL) {
        ///Run current state
        state = func();
    }
 }

