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
#include "servo_motor1.h"
#include "main.h"




void increase_speed_pwm1(int increment)
{
  if ( Motor_PWM1 + increment <= upper_bound)
    Motor_PWM1 = Motor_PWM1 + increment;
  else
    Motor_PWM1 = upper_bound;
}

void decrease_speed_pwm1(int decrement)
{
  if (Motor_PWM1 - decrement >= lower_bound)
    Motor_PWM1 = Motor_PWM1 - decrement;
  else
    Motor_PWM1 = lower_bound;  
}

void change_speed_pwm1(int speed)
{
  Motor_PWM1 = speed;
}

//void 

void init_hardware_pwm1(void)
{
  TCCR1A |= (BIT7|BIT5|BIT1);      // configuration for timer on compare mode for pwm configuration
  TCCR1B |= (BIT4|BIT3|BIT1|BIT0);
  
  
  
  ICR1=2499;                      // selecting pwm period to 20 ms 
  
  DDRD|=(BIT4|BIT5);              // Pwm out to output PORTD4 and PORTD5
  
}


