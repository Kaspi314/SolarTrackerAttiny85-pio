#define wdt_reset() __asm__ __volatile__("wdr") // this re-starts the watchdog clock/timer (ie. leaves current settings as is)

#include "Arduino.h"
#include <avr/sleep.h>

#define WDRT8 1 // 4 or 8 secs.

#ifndef WDRT8
#define WDRT4
#endif

void wd_setup();
void wd_enable();
void wd_disable();
byte boot_reason();
