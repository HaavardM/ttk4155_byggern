#ifndef JOYSTICK_H
#define JOYSTICK_H


void init_joystick();

//read the horizontal position of the joystick
int read_joystick_x();

//read the vertical position of the joystick
int read_joystick_y();

//read whether the joystick has been pushed down or not 
int read_joystick_select();

//read the position of the left slider
int read_left_slider();

//read the position of the right slider
int read_right_slider();

int read_left_button_select();

int read_right_button_select();

//Activates the joystick
void joystick_remote_enable();

//Deactives the joystick
void joystick_remote_disable();

//Updates the status of all components on the USB multifunction board
void joystick_update();


#endif
