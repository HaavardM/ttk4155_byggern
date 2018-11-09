#include "pwm.h"
#include "can.h"
#include "avr/io.h"
#include "can_msg_defines.h"
#include "solenoid.h"

uint8_t new_can_msgs = 0;
void game_controller_on_new_input() {
    new_can_msgs = 1;
    printf("New message\n\r");
}

void handle_can_msgs() {
    can_message_t msg;
    if(can_msg_read(0, &msg) == -1) {
        return;
    }
    switch(msg.id) {
        case MSG_JOYSTICK_POS:
            handle_new_joystick_pos(&msg);
            printf("Joystick!\n\r");
            break;
        case MSG_BUTTON_CLICK:
            solenoid_fire();
            printf("Click!\n\r");
            break;
        default:
            break;
    }
}

void handle_new_joystick_pos(can_message_t* msg_p) {
    uint8_t setpoint = 0xFF - msg_p->data[0];
    pwm_set_duty(setpoint);
}


void game_controller_update() {
    if(new_can_msgs) {
        handle_can_msgs();
    }
}


