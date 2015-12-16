/*
 * ADCTest.c
 *
 * Created: 12/9/2015 6:50:34 AM
 *  Author: Dhanish
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "LCD.h"
#include "com_def.h"

char array[5];
char i;

int main(void)
{
	InitADC();
	lcd_init();
	LCD_write_string_line1("ADC Value");
    while(1)
    {
		i++;
		int adc_value = ReadADC(0);
		integer_to_char(adc_value,array,4);
		LCD_write_string_line2(array);
		integer_to_char(i,array,3);
		LCD_write_string(LINE2,10,array);
		_delay_ms(250);
        //TODO:: Please write your application code 
    }
}