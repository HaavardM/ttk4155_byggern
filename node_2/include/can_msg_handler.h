#ifndef CAN_MSG_HANDLER_H
#define CAN_MSG_HANDLER_H
#include <stdint.h>

void can_msg_handle(uint8_t buf);
void can_msg_update();

#endif