#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <avr/io.h>
#include <util/delay.h>

volatile int adc_read(unsigned char channel) {
    volatile uint8_t* p = (uint8_t*) 0x1400;
    *p = 4 + channel;
    _delay_us(60);
    int temp = *p;
    return temp - 127;
}
