#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <stdint.h>

//Initialize motor controller
void motor_controller_init();
//Calibrate encoder - go left until stopping and reset value
void motor_controller_calibrate_encoder();
//Read current value
int16_t motor_controller_read_encoder();
//Set motor speed. Values < 0 = left, values > 0 = right
void motor_controller_set_speed(int16_t);

#endif