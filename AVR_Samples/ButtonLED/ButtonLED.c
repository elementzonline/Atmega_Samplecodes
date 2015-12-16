/*
 * ButtonLED.c
 *
 * Created: 12/9/2015 3:04:19 AM
 *  Author: Dhanish
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 0x01;
	DDRB &= ~(0x02);
	/*
	Explain the concept of pull up	 
	*/
	
    while(1) 
    {
		if ((PINB & 0x02) == 0x02){
			PORTB |= 0x01;
		}
		else{
			PORTB &= ~(0x01);
		}
		
        //TODO:: Please write your application code 
    }
}