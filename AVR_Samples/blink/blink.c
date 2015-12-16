#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

void main(){

	DDRB |= 0x01;
	PORTB &= ~(0x01);

	while(1){
		_delay_ms(1000);
		PORTB |= (0x01);

		_delay_ms(1000);
		PORTB &= ~(0x01);

	}

}
