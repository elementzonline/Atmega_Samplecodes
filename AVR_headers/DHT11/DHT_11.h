
#ifndef _DHT_11___
#define _DHT_11___

#define DHT_PORT_DIR        DDRA
#define DHT_PORT            PORTA
#define DHT_PORT_PIN        BIT3
#define DHT_PORT_STATUS     PINA


unsigned char read_dht(unsigned char *data);

#endif /* _DHT_11_H___ */
