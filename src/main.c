#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "external_memory.h"
#include "uart.h"
#include "adc.h"

#define BAUD (F_CPU/16/9600-1)


int main(){
       USART_init(BAUD);
       init_external_memory(); 
       while(1 == 1) { 
           unsigned char y = adc_read(0);
           unsigned char x = adc_read(1);
           unsigned char z = adc_read(2);
           printf("X: %d, Y: %d, Z: %d\n\r", x, y, z);
           _delay_ms(100);
       }

	return 0;
}
