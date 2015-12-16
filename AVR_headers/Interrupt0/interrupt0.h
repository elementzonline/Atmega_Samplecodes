
#ifndef _INTERRUPT0_H__
#define _INTERRUPT0_H__


#define RISING_EDGE   3
#define FALLING_EDGE  2
#define ANY_EDGE      1


void init_interrupt0(char edge);
void enable_int0(void);
void disable_int0(void);
void clear_interrupt0(void);



#endif /* _INTERRUPT0_H__ */