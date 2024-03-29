#include "pwm.h"
#include "can.h"
#include <avr/io.h>
#include "can_msg_defines.h"
#include "solenoid.h"
#include "game_controller.h"
#include "game_state_machine.h"
#include "pi.h"

void handle_new_joystick_pos(can_message_t* msg_p) {
    uint8_t setpoint = msg_p->data[0];
    pwm_set_duty(setpoint);
}

void handle_new_slider_pos(can_message_t* msg_p) {
    pi_set_setpoint(msg_p->data[0]);
}
void handle_new_button_click(can_message_t* msg_p) {
    
    if (msg_p->data[1]) {  // right button
        //Shoot ball
        game_fsm_set_button_flag();
    }

}

/*---Exposed functions---------------------------*/

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
            handle_new_slider_pos(msg_p);
            break;
        default:
            break;

    }
}

