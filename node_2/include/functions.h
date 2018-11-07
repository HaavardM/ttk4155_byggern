#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "can.h"

int button_is_pressed();
int ball_break_led();
void update_highscore();
void quit();
void game_on_can_msg(can_message_t* msg_p);
#endif