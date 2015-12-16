#ifndef _RTC_H___
#define _RTC_H___

#define HOURS_ADDR        0x02
#define MINUTES_ADDR      0x01
#define SECONDS_ADDR      0x00
#define DAY_ADDR          0x03
#define DATE_ADDR         0x04
#define MONTH_ADDR        0x05
#define YEAR_ADDR         0x06

#define HOUR_MODE_24    1
#define HOUR_MODE_12    0

void InitI2C(void);
void rtc_write(unsigned char addr,unsigned char data);
unsigned char rtc_read(unsigned char addr);

void rtc_set_time(unsigned char config_time[8],unsigned char config_date[8], unsigned char day, unsigned char HOUR_MODE);

#endif /* _MAIN_H___ */