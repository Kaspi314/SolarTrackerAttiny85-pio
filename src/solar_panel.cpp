#include "Arduino.h"
#include <stdlib.h>
#include <avr/sleep.h>
#include "delay_msus.h"
#include "multiplex_hc4076.h"
#include "solar_panel.h"

/// INSTANTIATE
Motor motors[] =
    {
        {&panels[0], C14, C15}};

Sensor sensors[] =
    {
        {&panels[0], C5, C6}}; // These have the same power consumption on Signal pins.

SolarPanel panels[] =
    {
        {&motors[0], &sensors[0], 0x00}};

SP_Util sputil =
    {0.0f, 0.0f, 0.0f, 0x00, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

void read_sensor(Sensor *sensor, uint8_t dir)
{
  pinMode(A2, INPUT);
  if (dir == ROT_CW)
  {
    mp_channel(sensor->CW);
    sputil.fl_aa = analogRead(A2);
    return;
  }
  else
  {
    mp_channel(sensor->CCW);
    sputil.fl_ab = analogRead(A2);
    return;
  }
  return;
}

void turn_motor(Motor *motor, uint8_t rotation, double duration)
{
  pinMode(SIG0, OUTPUT);
  digitalWrite(SIG0, LOW);
  if (rotation == ROT_CW)
  {
    mp_channel(motor->CW);
  }
  else
  {
    //mp_channel(motor->CCW);
    mp_channel(motor->CCW);
  }
  digitalWrite(SIG0, HIGH);
  delay_ms((double)duration);
  digitalWrite(SIG0, LOW);
  rotation = 0x00;
}

uint8_t get_motor_channel(Motor *motor, uint8_t rotation)
{
  if (rotation == ROT_CW)
  {
    return motor->CW;
  }
  return motor->CCW;
}

float percent_change(float fl_A, float fl_B)
{
  return (fl_B - fl_A) / fl_A;
}
