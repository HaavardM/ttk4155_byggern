#ifndef F_CPU
#define F_CPU 1000000
#endif

#include <util/delay.h>
#include "uart.h"

int main(){
       USART_init(9600);
       while(1 == 1) {
           USART_putchar('H');
           USART_putchar('E');
           USART_putchar('S');
           _delay_ms(1000);
       }

	return 0;
}
