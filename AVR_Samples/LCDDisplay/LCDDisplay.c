/*
 * ButtonLED.c
 *
 * Created: 12/9/2015 3:04:19 AM
 *  Author: Dhanish
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include "LCD.h"
#include <util/delay.h>

int main(void)
{
	//_delay_ms(1000);
	lcd_init();
	_delay_ms(1000);
	LCD_write_string_line1("Hello World!!");
    while(1) 
    {
		
        //TODO:: Please write your application code 
    }
}