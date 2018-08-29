#ifndef UART_H
#define UART_H
//Initialize USART
void USART_init(unsigned int baud_rate);
//Write char to TX
void USART_putchar(char c);
//Wait for char on RX
unsigned char USART_recvchar();
//Flush output
void USART_flush();
#endif
