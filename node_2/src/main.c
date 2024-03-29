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
#include "motor_controller.h"
#include "can_msg_handler.h"
#include "pi.h"

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
       pi_init();
       game_init();
       while(1) { 
           pi_update();
           game_loop_once();
       }
       return 0;
}
