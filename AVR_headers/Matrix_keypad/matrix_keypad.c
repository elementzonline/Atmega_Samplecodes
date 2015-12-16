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
#include "matrix_keypad.h"



void init_4x4_keypad(void)
{
  
  /* Colour Code
    Coloumns:
    Port Pin        Colour
      P0 --         orange
      P1 --         red
      P2 --         brown
      P3 --         black
  
    Rows:
    Port Pin        Colour
      P4 --         violet
      P5 --         blue
      P6 --         green
      P7 --         yellow
  */
  
  
  KEYPAD_PORT_DIR |= (BIT0|BIT1|BIT2|BIT3);  /*Keypad coloumns direction set as out*/
  KEYPAD_PORT_DIR &= ~(BIT4|BIT5|BIT6|BIT7);  /*Keypad rows direction set as in*/
  KEYPAD_PORT |= (BIT4|BIT5|BIT6|BIT7);       /*Enable pullup for rows*/
}

void init_3x3_keypad(void)
{
  KEYPAD_PORT_DIR |= (BIT0|BIT1|BIT2);    /*Keypad coloumns direction set as out*/
  KEYPAD_PORT_DIR &= ~(BIT3|BIT4|BIT5);   /*Keypad rows direction set as in*/
  KEYPAD_PORT |= (BIT3|BIT4|BIT5);        /*Enable pullup for rows*/
}


char read_key_3x3(void)
{
  char keycheck=0,i,key=0;
  for (i=0;i<3;i++)
  {
    KEYPAD_PORT |= (BIT0|BIT1|BIT2);
    KEYPAD_PORT &= ~(1<<i);              /*Set output low in order '110' - '101' - '011'*/
    _delay_us(1);  // delay of 1 microsecond
    
    keycheck = ~(KEYPAD_PORT_IN | 0xC7);   /*Check input*/
    switch (keycheck)
    {
    case 0x08:
      key = 1+i;
      return key;
    case 0x10:
      key = 4+i;
      return key;
    case 0x20:
      key = 7+i;
      return key;
    }
  }
  
  return 0;    /* return 0 if no key pressed */
}

char read_key_4x4(void)
{
  char keycheck=0,i,key=0;
  for (i=0;i<4;i++)
  {
    KEYPAD_PORT |= (BIT0|BIT1|BIT2|BIT3);
    KEYPAD_PORT &= ~(1<<i);              /*Set output low in order '1110' - '1101' - '1011' - '0111'*/
    _delay_us(1);  // delay of 1 microsecond
    
    keycheck = ~(KEYPAD_PORT_IN | 0x0F);   /*Check input*/
    switch (keycheck)
    {
    case 0x10:
      key = 1+i;
      return key;
    case 0x20:
      key = 5+i;
      return key;
    case 0x40:
      key = 9+i;
      return key;
    case 0x80:
      key = 13+i;
      return key;
    }
  }
  return 0xFF;
}
