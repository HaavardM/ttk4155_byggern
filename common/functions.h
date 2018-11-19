#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "can.h"

void game_on_can_msg(can_message_t* msg_p);
int get_highscore(int i);
#endif