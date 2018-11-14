#include "dac.h"
#include <avr/io.h>
#include <util/delay.h>


void motor_controller_init() {
    DDRH |= (1 << PH4) | (1 << PH1) | (1<<PINH5) | (1<<PINH3) | (1<<PINH6);
    DDRK = 0x0;
    motor_controller_enable();
    set_direction_right();
    reset_encoder();
}

void reset_encoder() {
    PORTH &=~(1<<PINH6);
    _delay_us(200);
    PORTH |=(1<<PINH6);
}


void motor_controller_enable() {
    PORTH |= (1<<PINH4);
}

void motor_controller_disable() {
    PORTH &=~(1<<PINH4);
}

void set_direction_right() {
    PORTH |=(1<<PINH1);
}

void set_direction_left() {
    PORTH &=~(1<<PINH1);
}

void motor_controller_set_speed(int speed) {
    if(speed < -255 || speed > 255) {
        return;
    }

    if(speed < 0) {
        set_direction_left();
        dac_set_value(-speed);
    } else {
        set_direction_right();
        dac_set_value(speed);
    }
}

int16_t read_encoder() {
    PORTH &=~(1<<PINH5);
    PORTH |= (1<<PINH3);
    _delay_us(60);
    uint8_t low = PINK;
    PORTH &=~(1<<PINH3);
    _delay_us(60);
    uint8_t high = PINK;
    PORTH |=(1<<PINH5);
    return -1 * (int16_t)(high << 8 | low);
}
