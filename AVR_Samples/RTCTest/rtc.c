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
#include "rtc.h"


unsigned char config_time[8] = "17:30:00";                 // time : minute : second
unsigned char config_date[8] = "09:12:15";                 // date : month :year
unsigned char day = 7;     // 1-sun, 2-mon, 3-tue , 4-wed, 5-thu, 6-fri, 7-sat 

void InitI2C(void)
{
  DDRC &= ~(BIT0|BIT1);
  PORTC |= (BIT0|BIT1);
}


void rtc_write(unsigned char addr,unsigned char data)
{
  
  TWBR = 0x0F;                                        //SCL hz value set (7.3 khz)
  TWSR = 0x00;                                        //prescalar value set(4)
  
  //TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWSTA)|(1<<TWEN);   //Send start condition of I2C
  TWCR = (BIT7|BIT6|BIT5|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill start condition send operation 
  while(!(TWCR & BIT7));                             
  
  TWDR = 0xD0;                                        //load the slave addr(RTC) to be written
  //TWCR = (1<<TWINT)|(1<<TWEN);                        //Trigger send operation
  TWCR = (BIT7|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill send operation to be finish      
  while(!(TWCR & BIT7)); 
  
  TWDR = addr;                                        //load the RTC_NV_RAM addr 
  //TWCR = (1<<TWINT)|(1<<TWEN);                        //Trigger send operation
  TWCR = (BIT7|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill send operation to be finish
  while(!(TWCR & BIT7));   
  
  TWDR = data;                                        //load the data
  //TWCR = (1<<TWINT)|(1<<TWEN);                        //Trigger send operation
  TWCR = (BIT7|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill send operation to be finish
  while(!(TWCR & BIT7));
  
  //TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWSTO)|(1<<TWEN);   //STOP the I2C,yet disabled 
  TWCR = (BIT7|BIT6|BIT4|BIT2);    
  //TWCR=0x00; //-- stop and disable I2C              //VERY IMPORTANT , NEED TO CHECK
  
  
  
}
unsigned char rtc_read(unsigned char addr)
{
  unsigned char data;
  //unsigned char register d=0;
  
  TWBR = 0x0F;                                        //SCL hz value set (7.3 khz)
  TWSR = 0x00;                                        //prescalar value set(4)
  
  //TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWSTA)|(1<<TWEN);   //Send start condition of I2C
  TWCR = (BIT7|BIT6|BIT5|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill start condition send operation 
  while(!(TWCR & BIT7)); 
  
  TWDR = 0xD0;                                        //load the slave addr(RTC) 
  //TWCR = (1<<TWINT)|(1<<TWEN);                        //Trigger send operation
  TWCR = (BIT7|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill send operation to be finish      
  while(!(TWCR & BIT7));
  
  TWDR = addr;                                        //load the RTC_NV_RAM addr 
  //TWCR = (1<<TWINT)|(1<<TWEN);                        //Trigger send operation
  TWCR = (BIT7|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill send operation to be finish
  while(!(TWCR & BIT7));
  
  //TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWSTA)|(1<<TWEN);   //Send start condition of I2C
  TWCR = (BIT7|BIT6|BIT5|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill start condition send operation
  while(!(TWCR & BIT7));
  
  TWDR = 0xD1;                                       //load the slave addr(RTC) to be READ
  //TWCR = (1<<TWINT)|(1<<TWEN);                        //Trigger send operation
  TWCR = (BIT7|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill send operation to be finish
  while(!(TWCR & BIT7));
  
  //TWCR = (1<<TWINT)|(1<<TWEN);                        //Trigger send operation
  TWCR = (BIT7|BIT2);
  //while(!(TWCR &(1<<TWINT)));                         //wait untill send operation to be finish
  while(!(TWCR & BIT7));
  
  data = TWDR;
  
  //TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWSTO)|(1<<TWEN);   //STOP the I2C,yet disabled
  TWCR = (BIT7|BIT6|BIT4|BIT2); 
  
  //TWCR = 0x00;                                      //VERY IMPORTNAT , NEED TO CHECK AGAIN
  
  return data;
  
  
}


void rtc_set_time(unsigned char config_time[8],unsigned char config_date[8], unsigned char day, unsigned char HOUR_MODE) 
{
  unsigned char temp = 0,temp1 = 0;
  
  if (HOUR_MODE == HOUR_MODE_24)
  {
   temp =  (config_time[0] - 0x30)<<4;
   temp +=  (config_time[1] - 0x30);
  }
  else
  {
   temp =  (config_time[0] - 0x30)*10;
   temp +=  (config_time[1] - 0x30); 
   if (temp >= 12)
   {
     temp -= 12;
     temp1 = temp/10 << 4;
     temp1 += temp%10;
     temp =  temp1|BIT5|BIT6;
   }
   else
   {
     temp1 = temp/10 << 4;
     temp1 += temp%10;
     temp = temp1|BIT6;
   }   
  }

   rtc_write(HOURS_ADDR,temp);
   
   temp =  (config_time[3] - 0x30)<<4;
   temp +=  (config_time[4] - 0x30);
   rtc_write(MINUTES_ADDR,temp);
   
   temp =  (config_time[6] - 0x30)<<4;
   temp +=  (config_time[7] - 0x30);
   rtc_write(SECONDS_ADDR,temp);
  
   temp =  (config_date[0] - 0x30)<<4;
   temp +=  (config_date[1] - 0x30);
   rtc_write(DATE_ADDR,temp);
   
   temp =  (config_date[3] - 0x30)<<4;
   temp +=  (config_date[4] - 0x30);
   rtc_write(MONTH_ADDR,temp);
   
   temp =  (config_date[6] - 0x30)<<4;
   temp +=  (config_date[7] - 0x30);
   rtc_write(YEAR_ADDR,temp);
   rtc_write(DAY_ADDR,day);
}
