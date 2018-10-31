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
#include "pwm.h"

#define BAUD (F_CPU/16/9600-1)

void handle_new_messages();

void on_message_1() {
    can_message_t msg;
    can_msg_read(0, &msg);
    printf("ID: %d, Data: [", msg.id);
    for(int i = 0; i < msg.length; ++i) {
        printf(" %d", msg.data[i]);
    }
    printf(" ]\n\r");
}

int main(){
       int state = 0;
       USART_init(BAUD);
       spi_init(); 
       pwm_init();
       can_init();
       can_set_on_received(0, on_message_1);
       sei();
       printf("Begin\n\r");
       while(1) { 
           static uint8_t duty = 0; 
           pwm_set_duty(255);
           _delay_ms(10);
       }
           return 0;
}
