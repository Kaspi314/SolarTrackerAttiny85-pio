#include "Arduino.h"
#include <stdlib.h>
#include "multiplex_hc4076.h"

uint8_t current_channel;

void mp_setup()
{
  // Setup pins for multiplexer CD74HC4067
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  mp_channel(0);
}

void mp_channel(uint8_t channel)
{
  channel &= 0x0F; // bitmask limit to 16 channels.
  for (int pin = 0; pin < 4; pin++)
  {
    if (channel & (1 << pin))
    {
      switch (pin)
      {
      case 0:
      {
        digitalWrite(0, HIGH);
      }
      case 1:
      {
        digitalWrite(1, HIGH);
      }
      case 2:
      {
        digitalWrite(2, HIGH);
      }
      case 3:
      {
        digitalWrite(3, HIGH);
      }
      }
    }
    else
    {
      switch (pin)
      {
      case 0:
      {
        digitalWrite(0, LOW);
      }
      case 1:
      {
        digitalWrite(1, LOW);
      }
      case 2:
      {
        digitalWrite(2, LOW);
      }
      case 3:
      {
        digitalWrite(3, LOW);
      }
      }
    }
  }
  current_channel = channel;
  return;
}
