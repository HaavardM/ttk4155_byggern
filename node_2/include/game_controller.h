#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

void game_controller_on_new_input();
void handle_can_msgs();
void handle_new_joystick_pos(can_message_t* msg_p);
void handle_new_slider_pos(can_message_t* msg_p);
void handle_new_button_click(can_message_t* msg_p);
void game_controller_update();

#endif
