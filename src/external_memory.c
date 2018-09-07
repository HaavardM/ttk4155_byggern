#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "external_memory.h"

void init_external_memory() {
    MCUCR |= (1 << SRE);
    SFIOR |= (1 << XMM2);
}

void SRAM_test(void) {
    volatile char* ext_ram    = (char*) 0x1800;
    uint16_t ext_ram_size     = 0x800;
    uint16_t write_errors     = 0;
    uint16_t retrieval_errors = 0;
    
    printf("Starting SRAM test...\n\r");
    uint16_t seed = rand();
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; ++i) {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retrieved_value = ext_ram[i];
        if (retrieved_value != some_value) {
            printf("Write phase error: extram[%4d] = %02X (should be %02X)\n\r", i, retrieved_value, some_value);
            write_errors++;
        }
    }
    
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        uint8_t retrieved_value = ext_ram[i];
        if (retrieved_value != some_value) {
            printf("Read phase error: extram[%4d] = %02X (should be %02X)\n\r", i, retrieved_value, some_value);
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n\r%4d errors in write phase and \n\r%4d errors in retreival phase\n\r\n\r", write_errors, retrieval_errors);
}
