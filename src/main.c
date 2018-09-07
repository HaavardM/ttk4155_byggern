#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "external_memory.h"
#include "uart.h"

#define BAUD (F_CPU/16/9600-1)


int main(){
       USART_init(BAUD);
       init_external_memory(); 
       while(1 == 1) { 
           SRAM_test();
           _delay_ms(1000);
       }

	return 0;
}
