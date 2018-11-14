#include "can_msg_handler.h"
#include "can_msg_defines.h"
#include "can.h"
#include "game_controller.h"
#include "game_state_machine.h"
#include "functions.h"
#include <util/atomic.h>

uint8_t data_available[2] = {0, 0};
can_message_t data_buffer[2];

void can_msg_handle(uint8_t buf) {
    if(can_msg_read(buf, data_buffer + buf) != -1) {
        data_available[buf] = 1;
    }
}

void can_msg_update() {
    for(int i = 0; i < 2; ++i) {
        if(data_available[i]) {
            can_message_t* msg_p = &data_buffer[i];
            switch(msg_p->id) {
                case MSG_JOYSTICK_POS:
                case MSG_BUTTON_CLICK:
                case MSG_SLIDER_POS:
                    game_controller_on_new_input(msg_p);
                    break;
                case MSG_START_GAME:
                    set_button_flag();
                    break;
            }
            //Reset flag
            data_available[i] = 0;
        }
    }
}