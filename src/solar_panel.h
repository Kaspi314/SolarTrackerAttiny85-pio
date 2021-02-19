#include "Arduino.h"
#include <stdlib.h>
#include <avr/sleep.h>
#include "multiplex_hc4076.h"

// Solar Panel CW and CCW
#define ROT_CW 0
#define ROT_CCW 1

class SP_Util;
class SolarPanel;
class Sensor;
class Motor;

class Motor
{
public:
  SolarPanel *PANEL;
  uint8_t CW;
  uint8_t CCW;
};
class Sensor
{
public:
  SolarPanel *PANEL;
  uint8_t CW;
  uint8_t CCW;
};
class SolarPanel
{
public:
  Motor *MOTOR;
  Sensor *SENSOR;
  uint8_t POSITION;
};

class SP_Util
{
public:
  float fl_i;
  float fl_aa;
  float fl_ab;
  uint8_t int_i;
  char dtostrf_i[8];
};

extern SolarPanel panels[];
extern SP_Util sputil;

void read_sensor(Sensor *sensor, uint8_t dir);
void turn_motor(Motor *motor, uint8_t rotation, double duration);
uint8_t get_motor_channel(Motor *motor, uint8_t rotation);
float percent_change(float fl_A, float fl_B);
constexpr float ToFloatAtCompileTime(uint8_t u8)
{
  return u8; // implicit conversion to return type
}
