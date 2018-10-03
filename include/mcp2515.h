#ifndef MCP2515_H
#define MCP2515_H
#include <stdint.h>

void MCP2515_init();
uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t address, uint8_t data);
void MCP2515_rts(uint8_t tx_buffer);
void MCP2515_reset();
uint8_t MCP2515_read_status();
void MCP2515_bit_modify(uint8_t address, uint8_t data, uint8_t mask);

#endif
