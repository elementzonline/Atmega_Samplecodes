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
#include "DHT_11.h"


unsigned char read_dht(unsigned char *data)
{
	unsigned char count_thresh  = 30;
    unsigned char humidity_integer=0,humidity_decimal=0,temperature_integer=0,temperature_decimal=0,checksum=0;
    unsigned char sensor_state=0,counter =0,i=0;
    DHT_PORT_DIR |= DHT_PORT_PIN;
    DHT_PORT |= DHT_PORT_PIN;
    _delay_ms(200);
    
    /* Microcontroller request starts  */
    DHT_PORT &= ~DHT_PORT_PIN;   // pin low
    _delay_ms(25);
    
    DHT_PORT |= DHT_PORT_PIN;   // pin high
    _delay_us(35);   /* Microcontroller request ends  */
    
    
    /* Sensor response starts  */
    DHT_PORT_DIR &= ~DHT_PORT_PIN;  // configure as input and pullup enabled
    _delay_us(5);  // gave sensor time to respond
    sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);
     
    while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)   
    {
      _delay_us(1); 
      counter++;   // for debug
    }
    
    //PORTB = counter;
    _delay_us(5);
    sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);
    counter = 0;        // for dewbug
    while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
    {
      _delay_us(1); 
      counter++;
    }    // end of DHT acknowledgement for uC request
    
    //PORTB = counter;
    // start of sensor response read humidity decimal
    for (i=0;i<8;i++)
    {
    	_delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        
        _delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);  
        //PORTA |= counter;
        counter = 0;
        
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        //PORTB = counter;
        if (counter > count_thresh)
        {
          //PORTA |= counter;
          humidity_integer |= (0x01 << (7-i)); 
        }
        else
        {
          humidity_integer &= ~(0x01 << (7-i)); 
        }
    }
    
    // start of sensor response read humidity integer
    for (i=0;i<8;i++)
    {
    	_delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        
        _delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        if (counter > count_thresh)
        {
          humidity_decimal |= (0x01 << (7-i)); 
        }
        else
        {
          humidity_decimal &= ~(0x01 << (7-i)); 
        }
    }
    
    // start of sensor response read temperature integer
    for (i=0;i<8;i++)
    {
    	_delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        
        _delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        if (counter > count_thresh)
        {
          //PORTA |= counter;
          temperature_integer |= (0x01 << (7-i)); 
        }
        else
        {
          temperature_integer &= ~(0x01 << (7-i)); 
        }
    }
    
     // start of sensor response read temperature decimal
    for (i=0;i<8;i++)
    {
    	_delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        
        _delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        if (counter > count_thresh)
        {
          temperature_decimal |= (0x01 << (7-i)); 
        }
        else
        {
          temperature_decimal &= ~(0x01 << (7-i)); 
        }
    }
    
    
    for (i=0;i<8;i++)
    {
    	_delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        
        _delay_us(5);
        sensor_state = (DHT_PORT_STATUS & DHT_PORT_PIN);    
        counter = 0;
        
        while((DHT_PORT_STATUS&DHT_PORT_PIN) ==  sensor_state)
        {
          _delay_us(1); 
          counter++;
        }    // end of low level in 0 or 1
        if (counter > count_thresh)
        {
          checksum |= (0x01 << (7-i)); 
        }
        else
        {
          checksum &= ~(0x01 << (7-i)); 
        }
    }

    DHT_PORT_DIR |= DHT_PORT_PIN;
    DHT_PORT |= DHT_PORT_PIN;
        
   data[0] = humidity_integer;
   data[1] = humidity_decimal;
   data[2] = temperature_integer;
   data[3] = temperature_decimal;
   data[4] = checksum;
    
    if (checksum == (humidity_integer+humidity_decimal+temperature_integer+temperature_decimal))
    {
      return 1;
    }
    else
      return 0;

}
