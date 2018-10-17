#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "external_memory.h"
#include "uart.h"
#include "adc.h"
#include "oled.h"
#include "ui.h"
#include "spi.h"
#include "mcp2515.h"

#define BAUD (F_CPU/16/9600-1)

void mcp_print();

int main(){
       USART_init(BAUD);
       init_external_memory(); 
       oled_init(); 
       ui_init();
       spi_init();
       MCP2515_init();
       printf("Begin\n\r");
       sei();
       while(1) { 
           ui_update();
           _delay_ms(10);
       }

	return 0;
}
