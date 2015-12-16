/*
 * RTCTest.c
 *
 * Created: 12/9/2015 11:25:34 AM
 *  Author: Dhanish
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "main.h"
#include "rtc.h"
#include "uart.h"
#include "com_def.h"

/*
  Configuration done for RTC IC 1307
*/

 unsigned char data;
 extern unsigned char config_time[8]; 
 extern unsigned char config_date[8]; 
 extern unsigned char day;

unsigned char character_array[3];




void main()
{
  init_usart(BAUD_9600);
  InitI2C();  // Initialise I2C port
  rtc_set_time(config_time,config_date,day,HOUR_MODE_24);     //Function to set RTC time.
                                                              //Comment the function after setting the time
                                                              //otherwise each time the code is resetted, RTC starts from the 
                                                              //set time in the program.  
      _delay_ms(1000);
      print_uart("This program is developed by Elementz ");
  
  while(1)
  {
    send2uart("TIME:  ");
    data = rtc_read(HOURS_ADDR);            //reading hour from DS1307
    hex_to_char(data,character_array);
    send2uart(character_array);
    send2uart(":");
    

     data = rtc_read(MINUTES_ADDR);            // reading minute from Ds1307
    hex_to_char(data,character_array);
    send2uart(character_array);
    send2uart(":");
    
    data = rtc_read(SECONDS_ADDR);            // reading seconds from Ds1307
    hex_to_char(data,character_array);
    send2uart(character_array);
    send2uart("   ");   
    
    
    send2uart("DATE:  ");
    data = rtc_read(DATE_ADDR);            // reading date from Ds1307
    hex_to_char(data,character_array);
    send2uart(character_array);
    send2uart("/");
    
    data = rtc_read(MONTH_ADDR);             // reading Month from Ds1307
    hex_to_char(data,character_array);
    send2uart(character_array);
      send2uart("/");
    
     data = rtc_read(YEAR_ADDR);             // reading Year from Ds1307
    hex_to_char(data,character_array);
    send2uart(character_array);
    
    usart_putchar(0x0D);
    usart_putchar(0x0A);
    _delay_ms(1000);
    
    
  }
}

