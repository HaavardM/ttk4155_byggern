#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void ir_init();

//Returns 1 if blocked
uint8_t ir_is_blocked();


#endif
