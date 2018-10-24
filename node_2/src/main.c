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
#include "can.h"

#define BAUD (F_CPU/16/9600-1)

void handle_new_messages();

int main(){
       int state = 0;
       USART_init(BAUD);
       spi_init(); 
       MCP2515_init(); 
       printf("Begin\n\r");
       while(1) { 
           can_message_t msg;
           if(can_msg_read(0, &msg) != -1) {
               printf("New message:\n\r");
               printf("  ID: %d\n\r", msg.id);
               printf("  Data: [ ");
               for(int i = 0; i < msg.length; ++i) {
                   printf("%d ", msg.data[i]);
               }
               printf("]\n\r");
               state = 0;
           } else {
               if(state != 1) {
                    printf("No new message\n\r");
               }
               state = 1;
           }
       }
       return 0;
}
