#ifndef JOYSTICK_H
#define JOYSTICK_H

int read_joystick_x();
int read_joystick_y();
int read_joystick_select();
void init_joystick();
void joystick_update();
int read_left_slider();
int read_right_slider();
int read_left_button_select();
int read_right_button_select();
void joystick_remote_enable();
void joystick_remote_disable();

#endif
