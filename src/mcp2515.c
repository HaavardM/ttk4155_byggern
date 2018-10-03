#include <avr/io.h>
#include "spi.h"
#include "mcp2515.h"

#define MCP2515_READ 0x3
#define MCP2515_WRITE 0x2
#define MCP2515_RESET 0xC0
#define MCP2515_RTS 0x80
#define MCP2515_READ_STATUS 0xA0
#define MCP2515_BIT_MODIFY 0x5


void MCP2515_init() {
    DDRB |= (1 << PINB4);
    PORTB |= (1 << PB4);
    MCP2515_bit_modify(0x0F, (1 << 6), (7 << 5));
    MCP2515_reset();
}

void MCP2515_set_SS() {
    PORTB &=~(1 << PB4);
}

void MCP2515_clear_SS() {
    PORTB |=(1 << PB4);
}

uint8_t MCP2515_read(uint8_t address) {
    MCP2515_set_SS();
    spi_trancieve(MCP2515_READ);
    spi_trancieve(address);
    uint8_t data = spi_trancieve(0x6);
    MCP2515_clear_SS();
    return data;
}


void MCP2515_write(uint8_t address, uint8_t data) {
    MCP2515_set_SS();
    spi_trancieve(MCP2515_WRITE);
    spi_trancieve(address);
    spi_trancieve(data);
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



