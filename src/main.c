#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "external_memory.h"
#include "uart.h"
#include "adc.h"

#define BAUD (F_CPU/16/9600-1)


int main(){
       USART_init(BAUD);
       init_external_memory(); 
       while(1 == 1) { 
           int jy = adc_read(0);
           int jx = adc_read(1);
           int s1 = adc_read(2);
           int s2 = adc_read(3);
           
           printf("Joystick X: %d, Joystick Y: %d, Slider 1: %d, Slider 2: %d\n\r", jx, jy, s1, s2);
           _delay_ms(100);
       }

	return 0;
}
