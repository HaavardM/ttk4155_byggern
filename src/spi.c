#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define BUFFER_SIZE 50

void spi_init() {
    DDRB = (1 << DDB5) | (1 << DDB7) | (1 << DDB4);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t spi_trancieve(uint8_t data) {
    SPDR = data;
    while(!(SPSR & (1 << SPIF)));
    return SPDR;
}

