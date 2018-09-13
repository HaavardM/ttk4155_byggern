#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <avr/io.h>
#include <util/delay.h>

unsigned char adc_read(unsigned char channel) {
    volatile unsigned char* p = (unsigned char*) 0x1400;
    *p = 4 + channel;
    _delay_us(60);
    return *p; 
}
