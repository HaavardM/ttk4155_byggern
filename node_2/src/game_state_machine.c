#include "game_state_machine.h"
#include <std.io>

fsm_state_func state_vector[FSM_NUM_STATES] = 
{
	state_start_game, state_wait, state_running, state_game_over
};
int score = 0;
fsm_state_func state = STATE_START_GAME;

fsm_state_e state_start_game() {
	printf("State start game\n\r");
	score = 0;
	return STATE_WAIT;
}

fsm_state_e state_wait() {
	printf("State wait\n\r");
	if (button_is_pressed()) { 		// funksjonen eksisterer ikke enda
		start_timer();				// funksjonen eksisterer ikke enda
		return STATE_RUNNING;
	}return STATE_WAIT;
}

fsm_state_e state_running() {
	printf("State running\n\r");
	if (ball_break_led()) {			// funksjonen eksisterer ikke enda
		stop_timer();
		return STATE_GAME_OVER;		// funksjonen eksisterer ikke enda
	}return STATE_RUNNING; 
}

fsm_state_e state_game_over() {
	printf("Todo: create update_highscore()")
	//update_highscore(score);		// eksisterer ikke!!!!!!!!!!
	quit();							// funksjonen eksisterer overraskende nok ikke enda
}

void timer_elapsed() {
	score += 1;
}
 void game_loop_once() {
 	///Get next state function
    fsm_state_func func = state_vector[state];
    if(func != NULL) {
        ///Run current state
        state = func();
    }
 }