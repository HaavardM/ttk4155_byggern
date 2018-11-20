#ifndef JOYSTICK_H
#define JOYSTICK_H


void controller_init();

//read the horizontal position of the joystick
int controller_read_joystick_x();

//read the vertical position of the joystick
int controller_read_joystick_y();

//read whether the joystick has been pushed down or not 
int controller_read_joystick_select();

//read the position of the left slider
int controller_read_left_slider();

//read the position of the right slider
int controller_read_right_slider();

int controller_read_left_button_select();

int controller_read_right_button_select();

//Activates the joystick
void controller_remote_enable();

//Deactives the joystick
void controller_remote_disable();

//Updates the status of all components on the USB multifunction board
void controller_update();


#endif
