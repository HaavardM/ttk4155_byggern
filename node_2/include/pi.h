#ifndef PI_H
#define PI_H

#include <stdint.h>

//Initialize PI controller
void pi_init();

//Update PI controller - measurement values
void pi_update();

//Set a setpoint. 0 = left side, 255 = right side
void pi_set_setpoint(uint8_t setpoint);

#endif