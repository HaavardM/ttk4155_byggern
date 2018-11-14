#include "TWI_Master.h"
#include <stdint.h>


void dac_init() {
    TWI_Master_Initialise();
}

void dac_set_value(uint8_t val) {
    uint8_t address = 0b01010000;
    uint8_t command = 0b0;

    uint8_t message[3];
    message[0] = address;
    message[1] = command;
    message[2] = val;
    TWI_Start_Transceiver_With_Data(message, 3);
}