#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include "can.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcp2515.h"
#include "mcp2515_registers.h"
#include "can_msg_handler.h"


void can_init() {
    //Initialize MCP
    MCP2515_init();
    cli();
    MCP2515_bit_modify(CANINTE, 0x3, 0x3);
    DDRD &=~((1 << PD2) | (1 << PD3));
    PORTD |= (1 << PIND2) | (1 << PIND3);
    EIMSK |=(1 << INT2); 
    EICRA |= (1 << ISC21);
    EICRA &=~(1 << ISC20);
    can_flush();
    sei();

}

void can_flush() {
    MCP2515_bit_modify(CANINTF, 0, 3);
}

ISR(INT2_vect)
{
    can_msg_handle(0);
}

void can_update() {
    uint8_t int_flag = MCP2515_read(CANINTF);
    if(int_flag & 1) {
        can_msg_handle(0);
    }
}



int ready_to_transmit(uint8_t buffer_id) {
    uint8_t tx_ctrl_status = MCP2515_read(TXB0CTRL + buffer_id * 0x10);
    return !(tx_ctrl_status & (1 << TXREQ));
}

int can_msg_send(can_message_t* msg_p) {
    
    static uint8_t buffer_id = 0;
    if(msg_p == NULL || msg_p->length > 8) {
        return -1;
    }
    
    //Only change buffer if neccessary
    while(!ready_to_transmit(buffer_id)) {
        ++buffer_id;
        if(buffer_id > 2) {
            buffer_id = 0;
        }
    }
    uint8_t high_id = msg_p->id / 8;
    uint8_t low_id = (msg_p->id % 8) * 0b100000;   
    MCP2515_write(TXB0SIDH + buffer_id * 0x10, &high_id, 1);
    MCP2515_write(TXB0SIDL + buffer_id * 0x10, &low_id, 1);
    MCP2515_write(TXB0DLC + buffer_id * 0x10, &msg_p->length, 1);
    MCP2515_write(TXB0D0 + buffer_id * 0x10, msg_p->data, msg_p->length);
    MCP2515_rts(buffer_id);
    uint8_t status = MCP2515_read(TXB0CTRL + buffer_id * 0x10);
    
    return status;
}


int can_msg_read(uint8_t buffer_id, can_message_t* msg_p) {
    
    if(msg_p == NULL) {
        return -1;
    }
    
    uint8_t int_flag = MCP2515_read(CANINTF);
    if(!(int_flag & (buffer_id + 1))) {
        return -1;
    }

    uint8_t high_id_raw = MCP2515_read(RXB0SIDH + buffer_id * 0x10);
    uint8_t low_id_raw = MCP2515_read(RXB0SIDL + buffer_id * 0x10);
    uint8_t dlc_raw = MCP2515_read(RXB0DLC + buffer_id * 0x10);

    uint8_t high_id = high_id_raw;
    uint8_t low_id = low_id_raw & 0b11100000;
    uint8_t length = dlc_raw & 0xF;
    
    msg_p->length = length;
    msg_p->id = 0b1000*high_id + low_id/0b100000;
    MCP2515_read_multiple(RXB0D0 + 0x10 * buffer_id, msg_p->data, length);
    MCP2515_bit_modify(CANINTF, 0, (1 << buffer_id));
    return 0;
}