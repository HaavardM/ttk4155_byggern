#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "spi.h"
#include "mcp2515.h"
#include "mcp2515_registers.h"

void MCP2515_init() {
    DDRB |= (1 << PB7) | (1 << PB0);
    PORTB |= (1 << PB7);
    MCP2515_reset();

    MCP2515_bit_modify(RXB0CTRL, (1 << RXM0), 1 | (1 << RXM0));
    MCP2515_bit_modify(RXB0CTRL, 0xFF, (1 << BUKT));
    

    MCP2515_bit_modify(BFPCTRL, 0xFF, (1<<B0BFM) | (1<<B1BFM));
    MCP2515_bit_modify(BFPCTRL, 0xFF, (1<<B0BFE) | (1<<B1BFE));

    //Request normal mode
    MCP2515_bit_modify(CANCTRL, 0x0, (7 << 5));
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

