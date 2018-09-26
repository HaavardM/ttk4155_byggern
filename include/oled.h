#ifndef OLED_H
#define OLED_H
#include<stdint.h>
void oled_init();
void oled_write_string(char* s, uint8_t page, uint8_t column);
void oled_write_string_inverse(char* s, uint8_t page, uint8_t column);
void oled_clear();

#endif
