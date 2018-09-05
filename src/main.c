#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include "uart.h"
#include <stdio.h>

#define BAUD (F_CPU/16/9600-1)

int main(){
       USART_init(BAUD);
       while(1 == 1) { 
           printf("HES\n");
           printf("er\n");
           printf("spektakulære\n");
           _delay_ms(1000);
       }

	return 0;
}
