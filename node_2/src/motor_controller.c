#include "dac.h"
#include <avr/io.h>
#include <util/delay.h>

#define MAX_SPEED 180

#define MAX_ENCODER 10000

void motor_controller_init() {
    DDRH |= (1 << PH4) | (1 << PH1) | (1<<PINH5) | (1<<PINH3) | (1<<PINH6);
    DDRK &=~((1 << PINK0) | 
              (1 << PINK1) | 
              (1 << PINK2) | 
              (1 << PINK3) | 
              (1 << PINK4) | 
              (1 << PINK5) | 
              (1 << PINK6) | 
              ( 1<< PINK7));
    motor_controller_enable();
    motor_controller_calibrate_encoder();
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

void motor_controller_set_speed(int16_t speed) {
    if(speed < -MAX_SPEED) {
        speed = -MAX_SPEED;
    } else if(speed > MAX_SPEED) {
        speed = MAX_SPEED;
    }

    if(speed < 0) {
        set_direction_left();
        dac_set_value(-speed);
    } else {
        set_direction_right();
        dac_set_value(speed);
    }
}

int16_t motor_controller_read_encoder() {
    static int16_t lst = 0;
    PORTH &=~(1<<PINH5);
    PORTH |= (1<<PINH3);
    _delay_us(250);
    uint8_t low = PINK;
    PORTH &=~(1<<PINH3);
    _delay_us(250);
    uint8_t high = PINK;
    PORTH |=(1<<PINH5);


    int16_t value = -1 * (int16_t)(high << 8 | low);
    if(value < -MAX_ENCODER || value > MAX_ENCODER) {
        return lst;
    }
    lst = value;
    return lst;
}

void motor_controller_calibrate_encoder() {
    reset_encoder();
    int16_t val;
    for(int i = 0; i < 10; i++) { 
        val = motor_controller_read_encoder();
    }
    motor_controller_set_speed(-150);
    int16_t prev_val = val + 200;
    //Move until
    while(prev_val != val) {
        prev_val = val;
        _delay_ms(2000);
        val = motor_controller_read_encoder();
    }
    reset_encoder();
    motor_controller_set_speed(0);

}
