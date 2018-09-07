#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "uart.h"
#define RX_BUFFER_SIZE 100
#define TX_BUFFER_SIZE 200


unsigned int rx_buffer_start_index = 0;
unsigned int rx_buffer_end_index = 0;
char rx_buffer[RX_BUFFER_SIZE];

int USART_recvchar();
int USART_putchar(char c);
void USART_init(unsigned int baud_rate);

    
int USART_putchar(char c) {
    //Wait for TX ready
    while(!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
    return 0;
} 
    

int IO_USART_put(char c, FILE* f) {
    USART_putchar(c);
    return 0;
}

int IO_USART_get(FILE* f) {
    return USART_recvchar();
}

int USART_recvchar() {
    unsigned int end_index = rx_buffer_end_index % RX_BUFFER_SIZE;
    unsigned int start_index = rx_buffer_start_index % RX_BUFFER_SIZE;
    
    
    if (end_index == start_index) {
        return -1;
    } else {
        int c = rx_buffer[start_index];
        ++rx_buffer_start_index;
        return c;
    }
    
}

void USART_flush(void) {
    unsigned char dummy;
    while (UCSR0A & (1 << RXC0)) dummy = UDR0;
}

void USART_init(unsigned int baud_rate) {
    //Set baud rate
    UBRR0H = (unsigned char) (baud_rate>>8);
    UBRR0L = (unsigned char) baud_rate;
    //enable rx and tx
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    //Enable interrupts
    UCSR0B |= (1 << RXCIE0);
    UCSR0B |= (1 << TXCIE0);
    //Set frame format
    UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
    
    fdevopen(IO_USART_put, IO_USART_get);
}
