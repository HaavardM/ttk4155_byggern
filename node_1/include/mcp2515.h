#ifndef MCP2515_H
#define MCP2515_H
#include <stdint.h>

void MCP2515_init();
uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t address, uint8_t* data, int length);
void MCP2515_rts(uint8_t tx_buffer);
void MCP2515_reset();
uint8_t MCP2515_read_status();
void MCP2515_bit_modify(uint8_t address, uint8_t data, uint8_t mask);
void MCP2515_read_multiple(uint8_t address, uint8_t* data, int length);
void MCP2515_load_tx_buffer(uint8_t address, uint8_t data);
uint8_t MCP2515_read_rx_buffer(uint8_t address);
#endif
