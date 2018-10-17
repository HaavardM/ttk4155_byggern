#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void spi_init() {
    DDRB = (1 << DDB2) | (1 << DDB1) | (1 << DDB0);
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t spi_trancieve(uint8_t data) {
    SPDR = data;
    while(!(SPSR & (1 << SPIF)));
    return SPDR;
}

