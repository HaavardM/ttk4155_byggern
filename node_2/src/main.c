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
#include "game_timer.h"
#include "ir.h"
#include "game_controller.h"
#include "game_state_machine.h"

#define BAUD (F_CPU/16/9600-1)

int main(){
       USART_init(BAUD);
       spi_init(); 
       ir_init();
       pwm_init();
       can_init();
       game_timer_init();
       //game_init();
       sei();
       printf("Begin\n\r");
       ir_start();
       while(1) { 
           _delay_ms(1);
           game_controller_update();
           game_loop_once();
          
       }
       return 0;
}
