#ifndef _EEPROM_H__
#define _EEPROM_H__

void eeprom_putchar(int addr, char data) ;
char eeprom_getchar(int addr)   ;
void eeprom_putstring(int start_address ,char *buffer);
void eeprom_getstring(int start_address ,char *buffer,char len);

#endif