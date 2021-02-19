#define wdt_reset() __asm__ __volatile__("wdr") // this re-starts the watchdog clock/timer (ie. leaves current settings as is)

#include "Arduino.h"
#include <avr/sleep.h>

void wd_setup();
void wd_enable();
void wd_disable();
byte boot_reason();
