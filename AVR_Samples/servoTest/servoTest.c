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
	/*
	Explain the concept of pull up	 
	*/
	
    while(1) 
    {
		for (int i = 100 ; i< 250; i++){
			change_speed_pwm1(i);
			_delay_ms(100);	
		}		
        //TODO:: Please write your application code 
    }
}