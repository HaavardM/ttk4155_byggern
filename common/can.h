#ifndef CAN_H
#define CAN_H
#include <avr/io.h>

typedef void (* can_callback_func)();

typedef struct { 
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
} can_message_t;


void can_init();
int can_msg_send(can_message_t* msg_p);
int can_msg_read(uint8_t buffer_id, can_message_t* msg_p);
void can_set_on_received(uint8_t id, can_callback_func cb);
void can_flush();
void can_update();

#endif
