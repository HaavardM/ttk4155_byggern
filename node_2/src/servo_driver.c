#include "pwm.h"
#include "can.h"
#include "avr/io.h"

void on_new_joystick() {
    can_message_t msg;
    if(can_msg_read(0, &msg) != -1) {
        printf("Message ID: %d\n\r", msg.id);
        if(msg.length != 2) {
            return;
        }
        pwm_set_duty(msg.data[0]);
    }
}

void servo_init() {
    can_set_on_received(0, on_new_joystick);
}
