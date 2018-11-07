#include "pwm.h"
#include "can.h"
#include "avr/io.h"

void servo_on_new_joystick() {
    can_message_t msg;
    if(can_msg_read(0, &msg) != -1) {
        printf("Message ID: %d\n\r", msg.id);
        if(msg.length != 3) {
            return;
        }
        printf("X: %d\n\r", msg.data[0]);
        printf("Y: %d\n\r", msg.data[1]);
        printf("Z: %d\n\r", msg.data[2]);
        uint8_t setpoint = 0xFF - msg.data[0];
        pwm_set_duty(setpoint);
    }
}
