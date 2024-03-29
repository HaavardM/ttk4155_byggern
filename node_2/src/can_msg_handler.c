#include "can_msg_handler.h"
#include "can_msg_defines.h"
#include "can.h"
#include "game_controller.h"
#include "game_state_machine.h"
#include <util/atomic.h>


/*---Exposed functions---------------------------*/
void can_msg_handle(uint8_t buf) {
    can_message_t msg;
    if(can_msg_read(buf, &msg) != -1) {
        switch(msg.id) {
            case MSG_JOYSTICK_POS:
            case MSG_BUTTON_CLICK:
            case MSG_SLIDER_POS:
                game_controller_on_new_input(&msg);
                break;
            case MSG_START_GAME:
                game_init();
                break;
            }
        
    }
}
