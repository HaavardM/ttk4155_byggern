#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"

#define BAUD (F_CPU/16/9600-1)

void handle_new_messages();

int main(){
       USART_init(BAUD);
       spi_init(); 
       MCP2515_init(); 
       printf("Begin\n\r");
       can_message_t msg;
       msg.id = 0;
       while(1) { 
           msg.id++;
           msg.data[0] = 'H';
           msg.data[1] = 'E';
           msg.data[2] = 'S';
           msg.length = 3;
           can_msg_send(&msg);
       }
       return 0;
}
