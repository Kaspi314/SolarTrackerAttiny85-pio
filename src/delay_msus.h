// CPU freq for delay
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define __DELAY_BACKWARD_COMPATIBLE__

#include "Arduino.h"
void delay_ms(double __ms);
void delay_us(double __us);