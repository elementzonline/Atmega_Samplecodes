#ifndef _MATRIX_KEYPAD_H__
#define _MATRIX_KEYPAD_H__

/* Defines common macro*/
#define CON_CAT(a,b)                a ## b
#define DDR_(name)        CON_CAT(DDR,name)
#define PORT_(name)       CON_CAT(PORT,name)
#define PIN_(name)        CON_CAT(PIN,name)
#define BIT_(name)        CON_CAT(BIT,name)

#define KEYPAD_PORT_IND        B               /*need to configure here */

#define KEYPAD_PORT_DIR  DDR_(KEYPAD_PORT_IND)
#define KEYPAD_PORT      PORT_(KEYPAD_PORT_IND)
#define KEYPAD_PORT_IN   PIN_(KEYPAD_PORT_IND)

void init_4x4_keypad(void);
void init_3x3_keypad(void);
char read_key_4x4(void);
char read_key_3x3(void);

#endif /* _MATRIX_KEYPAD_H__ */