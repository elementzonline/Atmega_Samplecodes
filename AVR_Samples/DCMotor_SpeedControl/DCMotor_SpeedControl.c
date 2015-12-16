/*
 * ButtonLED.c
 *
 * Created: 12/9/2015 3:04:19 AM
 *  Author: Dhanish
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"

int main(void)
{
	init_hardware_pwm1();
	DDRB |= 0x01;
	DDRB &= ~(0x02);
	
	DDRD |= (0x04|0x08);
	/*
	Explain the concept of pull up	 
	*/
	
    while(1) 
    {
		if ((PINB & 0x02) == 0x02){
			PORTB |= 0x01;
			PORTD |= 0x04;
			PORTD &= ~0x08;
			change_speed_pwm1(500);
			
		}
		else{
			PORTB &= ~(0x01);
			PORTD &= ~(0x04);
			PORTD |= 0x08;
			change_speed_pwm1(2499);
		}
		
        //TODO:: Please write your application code 
    }
}