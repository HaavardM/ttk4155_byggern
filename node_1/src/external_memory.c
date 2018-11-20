#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "external_memory.h"

/*---Exposed functions---------------------------*/
void init_external_memory() {
    SFIOR |= (1 << XMM2);
    MCUCR |= (1 << SRE);
}
