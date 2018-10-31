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

int main(){
       int state = 0;
       USART_init(BAUD);
       spi_init(); 
       pwm_init();
       can_init();
       servo_init();
       sei();
       printf("Begin\n\r");
       while(1) { 
       }
       return 0;
}
