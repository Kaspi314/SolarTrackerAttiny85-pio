#include "Arduino.h"
#include "delay_msus.h"
#include "watchdog_t.h"
/*
    This delay uses the avr builtin _delay_ms() which offers a resolution of 1/10th of a ms
    when the delay is above 262.14 ms / F_CPU in MHz. Up to 6.5535 seconds (at which point we have
    the overhead of another loop.)
*/
void delay_ms(double __ms)
{
  uint16_t __ticks;
  double __tmp;
  __tmp = ((F_CPU) / 4e3) * __ms;
  if (__tmp < 1.0)
    __ticks = 1;
  else if (__tmp > 65535)
  {
    //  __ticks = requested delay in 1/10 ms
    __ticks = (uint16_t)(__ms * 10.0);
    while (__ticks)
    {
      // wait 1/10 ms
      _delay_loop_2(((F_CPU) / 4e3) / 10);
      __ticks--;
      wdt_reset();
    }
    return;
  }
  else
    __ticks = (uint16_t)__tmp;
  _delay_loop_2(__ticks);
  wdt_reset();
}

void delay_us(double __us)
{
  uint16_t __ticks;
  double __tmp;
  __tmp = ((F_CPU) / 3e6) * __us;
  if (__tmp < 1.0)
    __ticks = 1;
  else if (__tmp > 255)
  {
    _delay_ms(__us / 1000.0);
    wdt_reset();
    return;
  }
  else
    __ticks = (uint8_t)__tmp;
  _delay_loop_1(__ticks);
  wdt_reset();
}
