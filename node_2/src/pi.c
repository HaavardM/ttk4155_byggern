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
#define ENCODER_MAX 10000
#define ENCODER_SAFEZONE 200
#define SETPOINT_MAX 255
#define K_P 1000
#define K_I 0
#define MAX_INT INT16_MAX
#define MAX_LONG INT32_MAX
#define MAX_I_TERM (MAX_LONG / 2)
#define MAX_ERROR MAX_LONG / (K_P + 1)
#define MAX_SUM_ERROR (MAX_I_TERM / (K_I + 1))
#define SCALING_FACTOR 8000

//Desired setpoint
int32_t setpoint = 0;
//Sum error - used for "integral"
int32_t sum_error = 0;
//Error value
int32_t error, ret;
//Measurement
int32_t current_value = 0;

ISR(TIMER5_COMPA_vect) {
    int32_t p_term;
    int32_t i_term, temp;
    
    //Calculate error
    error = setpoint - current_value;

    //Limit error and calculate pterm
    if(error > MAX_ERROR) {
        p_term = MAX_INT;
    } else if(error < -MAX_ERROR) {
        p_term = -MAX_INT;
    } else {
        p_term = K_P * error;
    }

    //Limit sum error and calculate Iterm 
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

    //Caluclate output by scaling the sum of the terms
    ret = (p_term + i_term) / SCALING_FACTOR;
    //Limit ret
    if(ret > MAX_INT) {
        ret = MAX_INT;
    } else if(ret < -MAX_INT) {
        ret = -MAX_INT;
    }
    //Set motor speed
    motor_controller_set_speed(ret);
}

void pi_init() {
    cli();
    //Set timer for PI update
    TIMSK5 |= (1 << OCIE5A);
    TCCR5B |= (1 << CS51) | (1 << WGM52);
    OCR5A = TIMER_STEPS;
    sei();
}

void pi_update() {
    //Read new measurement
    current_value = motor_controller_read_encoder();
    //printf("Error: %d, Speed: %d\n\r", error, ret);
    //printf("Encoder %d\n\r", current_value);
}

//Set new setpoint
void pi_set_setpoint(uint8_t pos) {
    static int16_t old = 0;
    if(pos < 10) {
        pos = 10;
    } else if(pos > 245) {
        pos = 245;
    }
    //Calculate setpoint in same range as encoder
    setpoint = (((int32_t) (ENCODER_MAX - 2 * ENCODER_SAFEZONE) * (int32_t)pos) / SETPOINT_MAX) + ENCODER_SAFEZONE;
}




