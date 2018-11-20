#ifndef GAME_STATE_MAHINE_H
#define GAME_STATE_MAHINE_H

///FSM states enum
typedef enum {STATE_START_GAME, STATE_WAIT, STATE_RUNNING, STATE_GAME_OVER, FSM_NUM_STATES} fsm_state_e;

///FSM state function pointer type
typedef fsm_state_e (* const fsm_state_func)(void);

//A button has been pushed 
void game_fsm_set_button_flag();
void game_init();
//A loop that runs the function corresponing to the state
void game_loop_once();

#endif