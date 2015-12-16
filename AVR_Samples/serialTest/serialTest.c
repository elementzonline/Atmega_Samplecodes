/*
 * serialTest.c
 *
 * Created: 12/9/2015 8:49:37 AM
 *  Author: Dhanish
 */ 
#define  F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "main.h"
#include "uart.h"

int main(void)
{
	init_usart(BAUD_9600);
    while(1)
    {
		_delay_ms(1000);
		print_uart("Hello World");
        //TODO:: Please write your application code 
    }
}