#include <avr/io.h>

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA_ADDRESS 0x1200

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define BYTES_IN_LINE (OLED_WIDTH / 8)

uint8_t* pixel_buffer_p = (uint8_t*) 0x1BFF;


uint8_t get_buffer_value(uint8_t x, uint8_t y) {
    volatile uint8_t* p = pixel_buffer_p + BYTES_IN_LINE * y;
    p += x / 8;
    return *p & ((uint8_t) 1 << x % 8);
}

void write_buffer_value(uint8_t x, uint8_t y, uint8_t val) {
    volatile uint8_t* p = pixel_buffer_p + BYTES_IN_LINE * y;
    p += x / 8;
    if(val) {
        *p |= ((uint8_t) 1 << x % 8);
    } else {
        *p &= ~((uint8_t) 1 << x % 8);
    }
}



void write_c(uint8_t data) {
    volatile uint8_t* p = (uint8_t*) OLED_COMMAND_ADDRESS;
    *p = data; 
}

void write_d(uint8_t data) {
    volatile uint8_t* p = (uint8_t*) OLED_DATA_ADDRESS;
    *p = data;
}

void oled_init() {
    write_c(0xae); // display off
    write_c(0xa1); //segment remap
    write_c(0xda); //common pads hardware: alternative
    write_c(0x12);
    write_c(0xc8); //common output scan direction:com63~com0
    write_c(0xa8); //multiplex ration mode:63
    write_c(0x3f);
    write_c(0xd5); //display divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81); //contrast control
    write_c(0x50);
    write_c(0xd9); //set pre-charge period
    write_c(0x21);
    write_c(0x20); //Set Memory Addressing Mode
    write_c(0x00);
    write_c(0xdb); //VCOM deselect level mode
    write_c(0x30);
    write_c(0xad); //master configuration
    write_c(0x00);
    write_c(0xa4); //out follows RAM content
    write_c(0xa6); //set normal display
    write_c(0xaf); // display on
    write_c(0xa4);
    
}


void oled_home() {
    write_c(0x40);

}

void oled_reset() {
    write_c(0xae);
    write_c(0xaf);
}
