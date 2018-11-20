#include <avr/io.h>
#include "oled.h"
#include "fonts.h"

#define OLED_COMMAND_ADDRESS 0x1000
#define OLED_DATA_ADDRESS 0x1200

#define NUM_PAGES 8
#define NUM_COLUMNS 128

void write_c(uint8_t data) {
    volatile uint8_t* p = (uint8_t*) OLED_COMMAND_ADDRESS;
    *p = data; 
}

void write_d(uint8_t data) {
    volatile uint8_t* p = (uint8_t*) OLED_DATA_ADDRESS;
    *p = data;
}


void oled_set_page_range(unsigned char page_start, unsigned char page_end) {
    write_c(0x22);
    write_c(page_start);
    write_c(page_end);
}

void oled_set_column_range(unsigned char column_start, unsigned char column_end) {
    write_c(0x21);
    write_c(column_start);
    write_c(column_end);
}


void oled_write_char(char c) {
    int font_char = c - ' ';
    for (int i = 0; i < 8; ++i) {
        write_d(pgm_read_byte(&font8[font_char][i]));
    }
}

void oled_write_char_inverse(char c) {
    int font_char = c - ' ';
    for (int i = 0; i < 8; ++i) {
        write_d(~pgm_read_byte(&font8[font_char][i]));
    }
}

void write_string(char* s, uint8_t page, uint8_t column, void (*write_func)(char)) {
    oled_set_page_range(page, page);
    oled_set_column_range(column, NUM_COLUMNS - 1);
    char c;
    for (uint8_t i = 0; i < NUM_COLUMNS / 8 && (c = *(s+i)) != '\0'; ++i) {
        write_func(c);
    }
}

/*---Exposed functions---------------------------*/
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
    write_c(0x10);
    write_c(0xdb); //VCOM deselect level mode
    write_c(0x30);
    write_c(0xad); //master configuration
    write_c(0x00);
    write_c(0xa4); //out follows RAM content
    write_c(0xa6); //set normal display
    write_c(0xaf); // display on
    oled_clear();
}

void oled_clear() {
    oled_set_page_range(0, NUM_PAGES - 1);
    oled_set_column_range(0, NUM_COLUMNS - 1);
    for(unsigned char i = 0; i < NUM_PAGES; ++i) {
        oled_set_page_range(i, i);
        oled_set_column_range(0, NUM_COLUMNS - 1);
        for(unsigned char j = 0; j < NUM_COLUMNS; ++j) {
            write_d(0x0);
        }
    }
}

void oled_write_string(char* s, uint8_t page, uint8_t column) {
    write_string(s, page, column, oled_write_char);
}

void oled_write_string_inverse(char* s, uint8_t page, uint8_t column) {
    write_string(s, page, column, oled_write_char_inverse);
}
