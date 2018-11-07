#ifndef GAME_STATE_MAHINE_H
#define GAME_STATE_MAHINE_H

///FSM states enum
typedef enum {STATE_START_GAME, STATE_WAIT, STATE_RUNNING, STATE_GAME_OVER, FSM_NUM_STATES} fsm_state_e;

///FSM state function pointer type
typedef fsm_state_e (* const fsm_state_func)(void);

void game_init();
void game_loop_once();

#endif