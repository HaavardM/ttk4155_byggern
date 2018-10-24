#ifndef CAN_H
#define CAN_H
#include <stdint.h>

typedef struct { 
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
} can_message_t;

int can_msg_send(can_message_t* msg_p);
int can_msg_read(uint8_t buffer_id, can_message_t* msg_p);
void can_init();
#endif
