#include "pwm.h"
#include "can.h"
#include <avr/io.h>
#include "can_msg_defines.h"
#include "solenoid.h"
#include "game_controller.h"
#include "game_state_machine.h"

void game_controller_on_new_input(can_message_t* msg_p) {
    switch(msg_p->id) {
        case MSG_JOYSTICK_POS:
            handle_new_joystick_pos(msg_p);
            break;
        case MSG_BUTTON_CLICK:
            solenoid_fire();
            handle_new_button_click(msg_p);
            break;
        case MSG_SLIDER_POS:
            //handle_new_slider_pos(&msg);
            break;
        default:
            break;

    }
}

void handle_new_joystick_pos(can_message_t* msg_p) {
    uint8_t setpoint = 0xFF - msg_p->data[0];
    pwm_set_duty(setpoint);
}
/*
void handle_new_slider_pos(can_message_t* msg_p) {
    if (msg_p->data[0] < get_slider_position()){
        //move to left
    else if (msg_p->data[0] > get_slider_position())
        //move to right
    }
}
*/
void handle_new_button_click(can_message_t* msg_p) {
    
    if (msg_p->data[1] == 1) {  // right button
        //Shoot ball
        set_button_flag();
        state_running();
    }

}

