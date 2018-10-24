#ifndef MCP2515_H
#define MCP2515_H
#include <stdint.h>

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
#define TXREQ 0x3
#define RX0IF 0x0
#define RX1IF 0x1

void MCP2515_init();
uint8_t MCP2515_read(uint8_t address);
void MCP2515_read_multiple(uint8_t address, uint8_t* data, int length);
void MCP2515_write(uint8_t address, uint8_t* data, int length);
void MCP2515_rts(uint8_t tx_buffer);
void MCP2515_reset();
uint8_t MCP2515_read_status();
void MCP2515_bit_modify(uint8_t address, uint8_t data, uint8_t mask);
void MCP2515_load_tx_buffer(uint8_t address, uint8_t data);
uint8_t MCP2515_read_rx_buffer(uint8_t address);
#endif
