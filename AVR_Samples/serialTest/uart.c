/* Copyright (c) 2015 Dhanish Vijayan
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
 */

#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

char rx_buffer[160];  //rx buffer chat length
char buff_index;

void init_usart(unsigned int baud)   
{   
    // USART initialization   
    // Communication Parameters: 8 Data, 1 Stop, No Parity   
    // USART Receiver: Off   
    // USART Transmitter: On   
    // USART Mode: Asynchronous   
    // USART Baud rate: baud   
    UCSRA=(0x00);   
    UCSRB=0x98;   
    UCSRC=0x86;   
    UBRRH=baud>>8;   
    UBRRL=baud;  
       
    //fdevopen(usart_putchar, NULL, 0);   
}
 
void usart_putchar(char data)   
{   
   while(!(UCSRA & BIT5));
   //Now write the data to USART buffer
   UDR=data;      
} 

void send2uart(char *buffer)
{
  int i;
//  for (i=0;i<strlen(buffer);i++)
  for (i=0;buffer[i] != '\0' ;i++)
  usart_putchar(buffer[i]);
}

void send_ATcommand(char *buffer)
{
  send2uart(buffer);
  usart_putchar(0x0D);
}

void print_uart(char *buffer)
{
  int i;
//  for (i=0;i<strlen(buffer);i++)
  for (i=0;buffer[i] != '\0' ;i++)
  usart_putchar(buffer[i]);
  usart_putchar(0x0D);
  usart_putchar(0x0A);
  }

char process_uart_data(char uart_buffer)
{
  if(uart_buffer != 0x0D && uart_buffer != 0x0A)
  {
    rx_buffer[buff_index] = uart_buffer;
    buff_index++;
    return 0;
  }
  else
  {
    rx_buffer[buff_index]='\0';
    buff_index = 0;
    return 1;
  }
}
