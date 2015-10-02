/*
 * Modified by Dhanish
 * Company : Elementz Engineers Guild Pvt Ltd
 *
 * Data field -- Upto 8 bytes maximum
 *
 * Tested on 15/02/2015
 *
 * Working status: Reception and transmission working perfectly
 *
 * Hardware used -- MCP2515+MCP2551(at 12 MHz crystal frequency) 
 * 
 * Code developed for ATMEGA16/32 with 8MHz external crystal oscillator

// ----------------------------------------------------------------------------
 * Copyright (c) 2015 Elementz Engineers Guild Pvt Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
// ----------------------------------------------------------------------------
 *
 * */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#include "main.h"
#include "mcp2515.h"
#include "uart.h"

extern char mcprxBuffer[9];
extern char rx_buffer[160];
// ----------------------------------------------------------------------------
// Main program

int main(void)
{
	// Initialize the UART interface - for 8MHz crystal Oscillator
	init_usart(BAUD_9600);
	
	// Activate Interrupts
	sei();
	
	
	if (!mcp2515_init()) {
		print_uart("Error: can not address the MCP2515 !\r\n");
		while(1);
	}
	else {
		print_uart("MCP2515 is active\r\n");
	}
	
	print_uart("working in the normal mode\r\n");
	mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
	
	while (1) {
		// wait until we receive a message
		if (mcp2515_check_message()) {
			print_uart("message received!\r\n");

			// Read the message from the buffers of the MCP2515
			if (mcp2515_get_message()) {
				print_uart(mcprxBuffer);
			}
			else {
				print_uart("Can not read the news\r\n");
			}
		}
	}
	
	return 0;
}

/*UART Interrupt routine- Only maximum of 8 bytes send in one CAN message */
ISR(USART_RXC_vect){
	char uart_buffer = UDR;
	char rx_complete = process_uart_data(uart_buffer);  // wait until an enter character is received.

	if (rx_complete == 1){
		if (mcp2515_send_message_part(rx_buffer)) {
			print_uart("This message was written to the buffer\r\n");
		}
		else {
			print_uart("Error: Could not send the message\r\n");
		}
	}

}
