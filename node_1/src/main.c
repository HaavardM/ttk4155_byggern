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
#include "joystick.h"

#define BAUD (F_CPU/16/9600-1)

void mcp_print();

int main(){
       USART_init(BAUD);
       init_external_memory(); 
       oled_init(); 
       ui_init();
       spi_init();
       MCP2515_init();
       init_joystick();
       printf("Begin\n\r");
       sei();
       while(1) { 
           //joystick_update();
           ui_update();
           read_right_slider();
           printf("Button: %d\n\r", read_right_button_select());
       }

	return 0;
}
