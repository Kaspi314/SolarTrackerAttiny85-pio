#include "watchdog_t.h"
#include "Arduino.h"
#include <avr/sleep.h>
ISR(WDT_vect) {} // NB. MUST be present, otherwise ATTiny reboots instead of returning from Sleep!

byte boot;
/*
    Setup watchdog timer.
*/
void wd_setup()
{
  boot = MCUSR;
  MCUSR = 0x00; // NB. MCUSR must be zeroed or watchdog will keep rebooting
  wd_disable();
  wd_enable();
  wdt_reset();
  return;
}

/*
    Enable the watchdog timer
*/
void wd_enable()
{
  WDTCR = (1 << WDP3) | (0 << WDP2) | (0 << WDP1) | (0 << WDP0); // set watchdog-timing to 4secs
  WDTCR |= (1 << WDE);                                           // Set watchdog timer to re-boot if triggered to begin with (only add WDIE just before we start sleep)
}
/*
    Disable the watchdog timer
*/
void wd_disable()
{
  WDTCR |= (1 << WDCE) | (1 << WDE);
  WDTCR = 0x00; // disable watchdog
}

byte boot_reason()
{
  return boot;
}
