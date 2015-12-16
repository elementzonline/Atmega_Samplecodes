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
#include "com_def.h"
#include "main.h"
#include "ultrasonic_trigger_echo.h"

unsigned int echo_duration;

void init_Ultrasonic_sensor(void)
{
  Ultrasonic_Triger_Port_Direction |= (Ultrasonic_Trigger_pin);    // Ultrasonic Trigger pin
  Ultrasonic_Triger_Port &= ~(Ultrasonic_Trigger_pin);   // Ultrasonic pin set to low
  
  Ultrasonic_Echo_Port_Direction &= ~(Ultrasonic_Echo_pin);   // Ultrasonic Echo pin set to input
  Ultrasonic_Echo_Port |= Ultrasonic_Echo_pin;      // Enable pullup
}

void trigger_Ultrasonic_sensor(void)
{
    Ultrasonic_Triger_Port |= (Ultrasonic_Trigger_pin);
    _delay_us(10);
    Ultrasonic_Triger_Port &= ~(Ultrasonic_Trigger_pin);
}

unsigned int read_Ultrasonic_sensor(void)
{
    echo_duration = 0;   
    while((Ultrasonic_Echo_Input&Ultrasonic_Echo_pin) != Ultrasonic_Echo_pin);
    while(((Ultrasonic_Echo_Input&Ultrasonic_Echo_pin) == Ultrasonic_Echo_pin) && (echo_duration<20000))
    {
      _delay_us(1);
      echo_duration++;
    }
    return echo_duration;
}


unsigned int get_distance_Ultrasonic_sensor(void)
{
  trigger_Ultrasonic_sensor();
  return read_Ultrasonic_sensor()/SCALE_FACTOR;
}
