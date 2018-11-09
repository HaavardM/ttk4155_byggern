#ifndef JOYSTICK_H
#define JOYSTICK_H

int read_joystick_x();
int read_joystick_y();
int read_joystick_select();
void init_joystick();
void joystick_update();
int read_left_slider();
int read_right_slider();

#endif
