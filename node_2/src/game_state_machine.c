#include "game_state_machine.h"
#include "game_timer.h"
#include "ir.h"
#include "functions.h"
#include <stdio.h>

fsm_state_e state_game_over();
fsm_state_e state_running();
fsm_state_e state_wait();
fsm_state_e state_start_game();

fsm_state_func state_vector[FSM_NUM_STATES] = 
{
	state_start_game, state_wait, state_running, state_game_over
};
int score = 0;
fsm_state_e state = STATE_START_GAME;

void timer_elapsed() {
	score += 1;
}

void game_init(){
	state = STATE_START_GAME;
	game_timer_set_on_elapsed(timer_elapsed);
}

fsm_state_e state_start_game() {
	printf("State start game\n\r");
	ir_start();
	score = 0;
	return STATE_WAIT;
}

fsm_state_e state_wait() {
	printf("State wait\n\r");
	if (button_is_pressed()) { 		// funksjonen eksisterer ikke enda
		game_timer_start();
		return STATE_RUNNING;
	}return STATE_WAIT;
}

fsm_state_e state_running() {
	printf("State running\n\r");
	if (ball_break_led()) {			// funksjonen eksisterer ikke enda
		game_timer_stop();
		return STATE_GAME_OVER;		
	}return STATE_RUNNING; 
}

fsm_state_e state_game_over() {
	printf("Todo: create update_highscore()");
	update_highscore(score);
	ir_stop();		
	quit();							// funksjonen eksisterer overraskende nok ikke enda
}



 void game_loop_once() {
 	///Get next state function
    fsm_state_func func = state_vector[state];
    if(func != NULL) {
        ///Run current state
        state = func();
    }
 }