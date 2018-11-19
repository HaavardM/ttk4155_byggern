#ifndef GAME_STATE_MAHINE_H
#define GAME_STATE_MAHINE_H

///FSM states enum
typedef enum {STATE_START_GAME, STATE_WAIT, STATE_RUNNING, STATE_GAME_OVER, FSM_NUM_STATES} fsm_state_e;

///FSM state function pointer type
typedef fsm_state_e (* const fsm_state_func)(void);

void timer_elapsed();
void game_fsm_set_button_flag();
void set_ir_flag();
void game_init();
fsm_state_e state_start_game();
fsm_state_e state_wait();
fsm_state_e state_running();
fsm_state_e state_game_over();
void game_loop_once();

#endif