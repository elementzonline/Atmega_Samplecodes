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

#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

//void _delay_ms(long no_milliseconds)
//{  long i;    for (i = 0; i < no_milliseconds; i++)
//{     __delay_cycles(milliseconds);
//}
//}
//void _delay_us(long no_microseconds)
//{
//  long i;  for (i = 0; i < no_microseconds; i++)
//  {     __delay_cycles(microseconds);
//  }
//}

void integer_to_char(int integer_input, char* character_array, char type)
{
  int reminder,quotient;    
  if (type == 2)  
  {	  
    quotient = integer_input/10;	  
    reminder = integer_input%10;	  
    character_array[0] = quotient+0x30;	  
    character_array[1] = reminder+0x30;	  
    character_array[2] = '\0';  
  }    
  if (type == 3)  
  {	  
    quotient = integer_input/100;	  
    reminder = integer_input%100;	  
    character_array[0] = quotient+0x30;	  
    quotient = reminder/10;	  
    reminder = reminder%10;	  
    character_array[1] = quotient+0x30;	  
    character_array[2] = reminder+0x30;	  
    character_array[3] = '\0';  
  } 
  if (type == 4)  
  {	  
    quotient = integer_input/1000;	// 1234  -- 1  
    reminder = integer_input%1000;	// 234  
    character_array[0] = quotient+0x30;	    //'1'
    quotient = reminder/100;	       // 234  -- 2
    reminder = reminder%100;	       // 34
    character_array[1] = quotient+0x30;	  // '2'
    quotient = reminder/10;	        //  3  
    reminder = reminder%10;	
    character_array[2] = quotient+0x30;	  
    character_array[3] = reminder+0x30;	  
    character_array[4] = '\0';  
  } 
}

void hex_to_char(char hex,char character_array[3])
{  
  if (((hex & 0xF0) >> 4 )>9)  
  {    
    character_array[0] = (((hex & 0xF0) >> 4 ) + 0x37);  
  } 
  else  
  {    
    character_array[0] = (((hex & 0xF0) >> 4 ) + 0x30);  
  }    
  if((hex & 0x0F)>9)  
  {    character_array[1] = ((hex & 0x0F) + 0x37);  
  }  
  else  
  {    
    character_array[1] = ((hex & 0x0F) + 0x30);  
  }  
  character_array[2] = '\0'; 
}


char char2num(char character)
{
  char result = 0;
  if ((character >= 0x30) && (character <= 0x39))
    result =  (character-0x30);
  else 
    result = 0;
  
  return result;
}


long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int char_to_int(char character_array[3], char type)
{
  int integer = 0;
  if (type == 1)
  {
    integer += (character_array[0]-0x30);
  }
  else if (type == 2)
  {
    integer += ((character_array[0]-0x30)*10);
    integer += (character_array[1]-0x30);
  }
  else if (type == 3)
  {
    integer += ((character_array[0]-0x30)*100);
    integer += ((character_array[1]-0x30)*10);
    integer += (character_array[2]-0x30);    
  }
  else if (type == 4)
  {
    integer += ((character_array[0]-0x30)*1000);
    integer += ((character_array[1]-0x30)*100);
    integer += ((character_array[2]-0x30)*10);
    integer += (character_array[3]-0x30); 
  }
  return integer;
}
