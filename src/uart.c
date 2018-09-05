#include<avr/io.h>
#include "uart.h"

void USART_init(unsigned int baud_rate) {
    //Set baud rate
    UBRR0H = (unsigned char) (baud_rate>>8);
    UBRR0L = (unsigned char) baud_rate;
    //enable rx and tx
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    //Set frame format
    UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
}

void USART_putchar(char c) {
    //Wait for transmit
    while(!(UCSR0A & (1 << UDRE0)));
    //Set data
    UDR0 = c;
}

unsigned char USART_recvchar() {
    //Wait for character
    while(!(UCSR0A & (1<<RXC0)));
    
    //Return
    return UDR0;
}


void USART_flush(void) {
    unsigned char dummy;
    while (UCSR0A & (1 << RXC0)) dummy = UDR0;
}
