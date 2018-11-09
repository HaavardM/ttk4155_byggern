#include "can_msg_handler.h"
#include "can_msg_defines.h"

#include "game_controller.h"
#include "game_state_machine.h"
#include "functions.h"

void can_msg_handle(uint8_t buf) {
    if(buf == 0) {
        game_controller_on_new_input();
    } else if(buf == 1) {
        //TODO
        can_message_t msg;
        can_msg_read(buf, &msg);
        game_on_can_msg(&msg);
    }
}