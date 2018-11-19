#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdint.h>

//Update highscore - 16 bit value
void update_highscore(uint8_t high, uint8_t low);
int get_highscore(int i);
char* get_name(int i);

#endif