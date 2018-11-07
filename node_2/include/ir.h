#ifndef ADC_H
#define ADC_H

#include "callback_types.h"

void ir_init();
void ir_start();
void ir_stop();
void ir_set_on_blocked(void_cb_t cb);


#endif
