#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "spi.h"
#include "mcp2515.h"

#define MCP2515_READ 0x3
#define MCP2515_WRITE 0x2
#define MCP2515_RESET 0xC0
#define MCP2515_RTS 0x81
#define MCP2515_READ_STATUS 0xA0
#define MCP2515_BIT_MODIFY 0x5
#define MCP2515_LOAD_TX_BUFFER_BASE 0x40
#define MCP2515_READ_RX_BUFFER_BASE 0x90

#define TXB0CTRL 0x30
#define TXB0SIDH 0x31
#define TXB0SIDL 0x32
#define TXB0EID8 0x33
#define TXB0EID0 0x34
#define TXB0DLC 0x35
#define TXB0D0 0x36

#define RXB0SIDH 0x61
#define RXB0SIDL 0x62
#define RXB0EID8 0x63
#define RXB0EID0 0x64
#define RXB0DLC 0x65
#define RXB0D0 0x66

#define CANINTE 0x2B
#define CANINTF 0x2C

#define TXP0 0x0
#define TXP1 0x2
#define TXREQ 0x8
#define RX0IF 0x0
#define RX1IF 0x1

volatile can_message_t messages[2];

void handle_new_messages() {
    uint8_t int_flag = MCP2515_read(CANINTF);
    can_message_t msg;
    if(int_flag & 0x1) {
        can_msg_read(0, &msg);
        printf("ID Buffer 1: %d\n\r", msg.id);
        messages[0] = msg;
    }
    if(int_flag & 0x2) {
        can_msg_read(1, &msg);
        messages[1] = msg;
        printf("ID Buffer 2: %d\n\r", msg.id);
    }
    //MCP2515_bit_modify(CANINTF, 0, 3);
}


ISR(INT0_vect) 
{
    handle_new_messages();
    printf("IDs %d, %d\n\r", messages[0].id, messages[1].id);
}

void MCP2515_init() {
    DDRB |= (1 << PINB7);
    PORTB |= (1 << PB7);
    MCP2515_reset();
    printf("%d\n\r", MCP2515_read(0xE));
    MCP2515_bit_modify(0x0F, 0, (7 << 5));
    MCP2515_bit_modify(CANINTE, 0x3, 0x3);
    printf("%d\n\r", MCP2515_read(0xE));
    //GICR |=(1 << INT0); 
    //MCUCR |= (1 << ISC01);
    //MCUCR &=~(1 << ISC00);
}

void MCP2515_set_SS() {
    PORTB &=~(1 << PB7);
}

void MCP2515_clear_SS() {
    PORTB |=(1 << PB7);
}

void MCP2515_read_multiple(uint8_t address, uint8_t* data, int length) {
    MCP2515_set_SS();
    spi_trancieve(MCP2515_READ);
    spi_trancieve(address);
    for(int i = 0; i < length; ++i) {
        data[i] = spi_trancieve(0x0);
    }
    MCP2515_clear_SS();
}


uint8_t MCP2515_read(uint8_t address) {
    uint8_t data;
    MCP2515_read_multiple(address, &data, 1);
    return data;

}


void MCP2515_write(uint8_t address, uint8_t* data_p, int length) {
    MCP2515_set_SS();
    spi_trancieve(MCP2515_WRITE);
    spi_trancieve(address);
    for(int i=0; i < length; ++i){
        spi_trancieve(data_p[i]);
    } 
    MCP2515_clear_SS();
}

void MCP2515_rts(uint8_t tx_buffer) {
    uint8_t ID = MCP2515_RTS;
    MCP2515_set_SS();
    spi_trancieve(ID + tx_buffer);
    MCP2515_clear_SS();
}

void MCP2515_reset() {
    MCP2515_set_SS();
    spi_trancieve(MCP2515_RESET);
    MCP2515_clear_SS();
    _delay_ms(10);
}

uint8_t MCP2515_read_status() {
    MCP2515_set_SS();
    spi_trancieve(MCP2515_READ_STATUS);
    uint8_t data = spi_trancieve(MCP2515_READ_STATUS);
    MCP2515_clear_SS();
    return data;
}


void MCP2515_bit_modify(uint8_t address, uint8_t data, uint8_t mask) {
    MCP2515_set_SS();
    spi_trancieve(MCP2515_BIT_MODIFY);
    spi_trancieve(address);
    spi_trancieve(mask);
    spi_trancieve(data);
    MCP2515_clear_SS();
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
    
    return 0;
}


int can_msg_read(uint8_t buffer_id, can_message_t* msg_p) {
    
    if(msg_p == NULL) {
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
