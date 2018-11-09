#ifndef MCP2515_REGISTERS_H
#define MCP2515_REGISTERS_H

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

#define RXB0CTRL 0x60
#define RXB0SIDH 0x61
#define RXB0SIDL 0x62
#define RXB0EID8 0x63
#define RXB0EID0 0x64
#define RXB0DLC 0x65
#define RXB0D0 0x66

#define RXB1CTRL 0x70

#define CANCTRL 0xF
#define CANINTE 0x2B
#define CANINTF 0x2C

#define TXP0 0x0
#define TXP1 0x2
#define TXREQ 0x3
#define RX0IF 0x0
#define RX1IF 0x1

#define RXF0SIDH 0x0
#define RXF0SIDL 0x1
#define RXM0SIDH 0x20
#define RXM0SIDL 0x21
#define FILTERDIFF 0x4


#define SID0 5
#define SID1 6
#define SID2 7
#define SID3 0
#define SID4 1
#define SID5 2
#define SID6 3
#define SID7 4
#define SID8 5
#define SID9 6
#define SID10 7

#define FILHIT0 0
#define FILHIT1 1
#define RXM0 5
#define RXM1 6

#define BFPCTRL 0xC
#define B0BFM 0
#define B1BFM 1
#define B0BFE 2
#define B1BFE 3

#endif
