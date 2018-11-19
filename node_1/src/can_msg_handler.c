#include "can_msg_handler.h"
#include "can_msg_defines.h"
#include "can.h"
#include "joystick.h"
#include "highscore.h"



void can_msg_handle(uint8_t buf) {
    can_message_t msg;
    if(can_msg_read(buf, &msg) != -1) {
        switch(msg.id) {
            case MSG_GAME_OVER:
                joystick_remote_disable();
                update_highscore(msg.data[0], msg.data[1]);
                break;
            }
        
    }
}

void can_msg_update() {
}
