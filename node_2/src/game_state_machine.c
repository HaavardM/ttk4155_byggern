#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include "game_state_machine.h"
#include "game_timer.h"
#include "ir.h"
//#include "functions.h"
#include "can_msg_defines.h"
#include <stdio.h>
#include "can.h"

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

fsm_state_e state_start_game() {
	//Reset game timer
	game_timer_stop();
	return STATE_WAIT;
}

fsm_state_e state_wait() {
	if (button_flag) {
		game_timer_start();
		return STATE_RUNNING;
	}
	return STATE_WAIT;
}

fsm_state_e state_running() {
	button_flag = 0;
	if (ir_is_blocked()) {			
		game_timer_stop();
		return STATE_GAME_OVER;		
	}return STATE_RUNNING; 
}

fsm_state_e state_game_over() {
	uint16_t score = game_timer_get();
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

/*---Exposed functions---------------------------*/

 void game_loop_once() {
 	///Get next state function
    fsm_state_func func = state_vector[state];
    if(func != NULL) {
        ///Run current state
        state = func();
    }
 }

void game_fsm_set_button_flag(){
 	button_flag = 1;
}

void game_init(){
	state = STATE_START_GAME;
	button_flag = 0;
}
