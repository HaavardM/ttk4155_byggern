#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "motor_controller.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include "avr/iom2560.h"

#define PRESCALE 8
#define FREQUENCY (F_CPU / PRESCALE)
#define PERIOD 1 / 33
#define TIMER_STEPS (FREQUENCY * PERIOD - 1)


int motor_speed = 0;


#define ENCODER_MAX 9500
#define SETPOINT_MAX 255

#define K_P 10
#define K_I 1

#define MAX_INT INT16_MAX
#define MAX_LONG INT32_MAX
#define MAX_I_TERM (MAX_LONG / 2)


#define MAX_I_TERM MAX_LONG / 2
#define MAX_ERROR MAX_INT / (K_P + 1)
#define MAX_SUM_ERROR (MAX_I_TERM / (K_I + 1))

#define SCALING_FACTOR 500

int16_t setpoint = 0;
int32_t sum_error = 0;
int16_t last_value = 0;

//TODO Update frequently
int16_t current_value = 0;

ISR(TIMER5_COMPA_vect) {
    int16_t error, p_term;
    int32_t i_term, temp;
    
    error = setpoint - current_value;

    if(error > MAX_ERROR) {
        p_term = MAX_INT;
    } else if(error < -MAX_ERROR) {
        p_term = -MAX_INT;
    } else {
        p_term = K_P * error;
    }
    printf("Error: %d\n\r", error);

    temp = sum_error + error;
    if(temp > MAX_SUM_ERROR) {
        i_term = MAX_I_TERM;
        sum_error = MAX_SUM_ERROR;
    } else if(temp < -MAX_SUM_ERROR) {
        i_term = -MAX_I_TERM;
        sum_error = -MAX_SUM_ERROR;
    } else {
        sum_error = temp;
        i_term = K_I * sum_error;
    }

    int32_t ret = (p_term + i_term) / SCALING_FACTOR;
    if(ret > MAX_INT) {
        ret = MAX_INT;
    } else if(ret < -MAX_INT) {
        ret = -MAX_INT;
    }
    printf("Ret %d\n\r", ret);
    motor_controller_set_speed(ret);
}

void pi_init() {
    cli();
    TIMSK5 |= (1 << OCIE5A);
    TCCR5B |= (1 << CS51) | (1 << WGM52);
    OCR5A = TIMER_STEPS;
    motor_controller_init();
    motor_controller_calibrate_encoder();
    sei();
}

void pi_update() {
    current_value = motor_controller_read_encoder();
    //printf("Encoder %d\n\r", current_value);
}

void pi_set_setpoint(uint8_t pos) {
    uint32_t temp = ((uint32_t)ENCODER_MAX * (uint32_t)pos) / (uint32_t)SETPOINT_MAX;
    setpoint = temp;
}




