#include pwm.h

void pwm_init(){
	TCCR0 = ((1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << COM00)); // Fast pwm mode and set OC0 on Compare Match, clear OC0 at TOP
	
}
	

//Set duty cycle, 0-255
void pwm_set_duty(uint8_t duty);
