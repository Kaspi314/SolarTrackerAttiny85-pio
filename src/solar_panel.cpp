#include "Arduino.h"
#include <stdlib.h>
#include <avr/sleep.h>
#include "delay_msus.h"
#include "multiplex_hc4076.h"
#include "solar_panel.h"

/// INSTANTIATE
Motor motors[] =
    {
        {&panels[0], C14, C15},
        {&panels[1], C12, C13}};

SunSensor sunsensors[] =
    {
        {&panels[0], C5, C6},
        {&panels[1], C9, C10}}; // These have the same power consumption on Signal pins.
RotSensor rotsensors[] =
    {
        {&panels[0], 0, 1023, C4},
        {&panels[1], 0, 1023, C8}};

SolarPanel panels[] =
    {
        {&motors[0], &sunsensors[0], 0x00},
        {&motors[1], &sunsensors[1], 0x00}};

SP_Util sputil =
    {0.0f, 0.0f, 0.0f, 0x00, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

void read_sensor_dir(SunSensor *sensor, uint8_t dir)
{
  pinMode(SIGA, INPUT);
  if (dir == ROT_CW)
  {
    mp_channel(sensor->CW);
    sputil.fl_aa = analogRead(SIGA);
    return;
  }
  else if (dir == ROT_CCW)
  {
    mp_channel(sensor->CCW);
    sputil.fl_ab = analogRead(SIGA);
    return;
  }
  return;
}

void read_sensor(SunSensor *sensor)
{
  read_sensor_dir(sensor, ROT_CW);
  read_sensor_dir(sensor, ROT_CCW);
}

void turn_motor(Motor *motor, uint8_t rotation, double duration)
{
  pinMode(SIGD, OUTPUT);
  digitalWrite(SIGD, LOW);
  if (rotation == ROT_CW)
  {
    mp_channel(motor->CW);
  }
  else
  {
    //mp_channel(motor->CCW);
    mp_channel(motor->CCW);
  }
  digitalWrite(SIGD, HIGH);
  delay_ms((double)duration);
  digitalWrite(SIGD, LOW);
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
