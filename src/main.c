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
       can_message_t msg;
       msg.id = 0;
       while(1) { 
           ui_update();
           msg.id++;
           msg.length = 3;
           msg.data[0] = 'H';
           msg.data[1] = 'E';
           msg.data[2] = 'S';
           printf("Before send\n\r");
           can_msg_send(&msg);
           printf("After sendt\n\r");
           _delay_ms(10);
       }

	return 0;
}
