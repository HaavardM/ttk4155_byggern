#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include "callback_types.h"
#include <stdint.h>

//Initialize timer
void game_timer_init();

//Start timer
void game_timer_start();

//Stop timer
void game_timer_stop();

//Get value from timer
uint16_t game_timer_get();

#endif
