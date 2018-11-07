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
        printf("X: %d\n\r", msg.data[0]);
        uint8_t setpoint = 0xFF - msg.data[0];
        pwm_set_duty(setpoint);
    }
}

void servo_init() {
    can_set_on_received(0, on_new_joystick);
}
