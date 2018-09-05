#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "uart.h"
#define RX_BUFFER_SIZE 100
#define TX_BUFFER_SIZE 200


unsigned int rx_buffer_start_index = 0;
unsigned int rx_buffer_end_index = 0;
unsigned int tx_buffer_start_index = 0;
unsigned int tx_buffer_end_index = 0;
char rx_buffer[RX_BUFFER_SIZE];
char tx_buffer[TX_BUFFER_SIZE];

int USART_recvchar();
int USART_putchar(char c);
void USART_init(unsigned int baud_rate);

    
ISR(USART0_RXC_vect) {
    
    unsigned int end_index = rx_buffer_end_index % RX_BUFFER_SIZE;
    unsigned int start_index = rx_buffer_start_index % RX_BUFFER_SIZE;

    rx_buffer[end_index] = UDR0;
    ++rx_buffer_end_index;
    
    if (end_index + 1 == start_index) {
        ++start_index;
    }
}

ISR(USART0_TXC_vect) {
    unsigned int start_index = tx_buffer_start_index % TX_BUFFER_SIZE;
    unsigned int end_index = tx_buffer_end_index % TX_BUFFER_SIZE;
    UDR0 = tx_buffer[start_index];
    ++tx_buffer_start_index;
}


int USART_putchar(char c) {
    /*cli();
    unsigned int start_index = tx_buffer_start_index % TX_BUFFER_SIZE;
    unsigned int end_index = tx_buffer_end_index % TX_BUFFER_SIZE;
    
    //Write if available
    if((UCSR0A & (1 << UDRE0))) {
        UDR0 = c;
        return 0; 
    }
    
    while(tx_buffer_end_index - tx_buffer_start_index > TX_BUFFER_SIZE) {}
    
    tx_buffer[end_index] = c;
    ++tx_buffer_end_index;
    sei();
    */
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
    cli();
    unsigned int end_index = rx_buffer_end_index % RX_BUFFER_SIZE;
    unsigned int start_index = rx_buffer_start_index % RX_BUFFER_SIZE;
    
    
    if (end_index == start_index) {
        sei();
        return -1;
    } else {
        int c = rx_buffer[start_index];
        ++rx_buffer_start_index;
        sei();
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
    
    //sei();

    fdevopen(IO_USART_put, IO_USART_get);
}
