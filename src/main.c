#ifndef F_CPU
#define F_CPU 4915200
#endif

#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "external_memory.h"
#include "uart.h"
#include "adc.h"
#include "oled.h"

#define BAUD (F_CPU/16/9600-1)

void ui_update();
void ui_move_up();
void ui_move_down();

int main(){
       USART_init(BAUD);
       init_external_memory(); 
       oled_init(); 
       ui_update();
       while(1 == 1) { 
           static int last_y = 0;
           int jy = adc_read(0);
           if (last_y < 50 && last_y > -50) {
               if (jy > 50) {
                   ui_move_up();
               } else if(jy < -50) {
                   ui_move_down();
               }
           }
           last_y = jy;
          // printf("Joystick X: %d, Joystick Y: %d, Slider 1: %d, Slider 2: %d\n\r", jx, jy, s1, s2);
           _delay_ms(100);
       }

	return 0;
}
