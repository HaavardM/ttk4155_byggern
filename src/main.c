#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include "external_memory.h"

#define BAUD (F_CPU/16/9600-1)


int main(){
       USART_init(BAUD);
       init_external_memory(); 
       unsigned char* p = (unsigned char*) 0x1807;
       unsigned char* p1 = (unsigned char*) 0x1808;
       unsigned char* p2 = (unsigned char*) 0x1850;
       while(1 == 1) { 
           SRAM_test();
           _delay_ms(1000);
       }

	return 0;
}
