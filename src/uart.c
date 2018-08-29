


void USART_init(unsigned int baud_rate) {
    UBRRH = (unsigned char) (baud_rate>>8);
    UBRRL = (unsigned char) baud_rate;
    //enable rx and tx
    UCSRB = (1 << RXEN) | (1 << TXEN);
    //Set frame format
    UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}