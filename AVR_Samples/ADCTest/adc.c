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

void InitADC()
{
  ADMUX |= BIT6;               // For Aref=AVcc;
  
  ADCSRA |= (BIT7|BIT2|BIT1|BIT0);  //ADC Enable, ADC clock = Mainclock/128
                                    //ADC clock = 16MHz/128 = 125 KHz
  //ADCSRA |= (BIT7|BIT0);
}

unsigned int ReadADC(unsigned char ch)
{
   //Select ADC Channel ch must be 0-7
   //ch = ch & 0x07;
   //ADMUX |= ch;
   //ADMUX &= (0xf8|ch);
   
   ADMUX |= 0x00;


   //Start Single conversion
   ADCSRA |= BIT6;

   //Wait for conversion to complete
    while(!(ADCSRA & BIT4));

   //Clear ADIF by writing one to it
   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

    ADCSRA |= BIT4;

   return(ADC);
}
