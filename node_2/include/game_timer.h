#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include "callback_types.h"

//Initialize timer
void game_timer_init();

//Set method to run on each callback
void game_timer_set_on_elapsed(void_cb_t cb);

//Start timer
void game_timer_start();

//Stop timer
void game_timer_stop();

#endif
