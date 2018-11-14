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
#include "solenoid.h"
#include "dac.h"

#define BAUD (F_CPU/16/9600-1)

int main(){
       USART_init(BAUD);
       spi_init(); 
       ir_init();
       pwm_init();
       can_init();
       game_timer_init();
       solenoid_init();
       dac_init();
       motor_controller_init();
       //game_init();
       sei();
       printf("Begin\n\r");
       ir_start();
       dac_set_value(20);
       while(1) { 
           can_msg_update();
           //game_loop_once();
          
       }
       return 0;
}
