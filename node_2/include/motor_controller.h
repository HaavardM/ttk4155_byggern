#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <stdint.h>

void motor_controller_init();
void motor_controller_calibrate_encoder();
int16_t motor_controller_read_encoder();

#endif