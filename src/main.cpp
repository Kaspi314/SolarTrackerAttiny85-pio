#include "watchdog_t.h"
#include "delay_msus.h"
#include "main.h"
#include "Arduino.h"

#include "picoUART.h"
#include "pu_print.h"
#include "pu_config.h"
#include <stdlib.h>

#include "multiplex_hc4076.h"
#include "solar_panel.h"

#define DEBUG 1
#define RX_WAIT 0

bool rx_wdr_flag;

float percent_diff = 0.10f;

const int buflen = 20;
char linebuf[buflen];

int readline()
{
  int count = 0;
  char c;
  c = pu_read(); // waste
  do
  {
    while (!purx_dataready())
      ; // wait for data
    c = pu_read();
    linebuf[count++] = c;
  } while ((c != '\n') && (count < buflen - 1));
  linebuf[count] = '\0';
  return count;
}

void setup()
{
  // Setup pins for multiplexer CD74HC4067
  mp_setup();
  rx_wdr_flag = false;

  // Switch multiplexer to TX output 0001b
  mp_channel(1);
  prints("\nrxISR.\n");
  mp_channel(0); // back to rx
  wd_setup();
}

void loop()
{
  if (RX_WAIT || rx_wdr_flag)
  {
    if (purx_dataready())
    {
      readline();
      // Switch multiplexer to TX output 0001b
      mp_channel(1);

      prints("got: ");
      prints(linebuf);

      mp_channel(0);
    }
  }
  rx_wdr_flag = true;
  // Switch multiplexer to analog in - 0010b
  mp_channel(panels[0].SUNSENSOR->CW);
  delay_ms(5l);
  read_sensor_dir(panels[0].SUNSENSOR, ROT_CW);

  putx_dtostrf(&(sputil.fl_aa));

  /*  // Switch to TX out from 0010b to 0001b
  mp_channel(1);
  dtostrf(sputil.fl_aa, 6, 2, sputil.dtostrf_i);
  for (sputil.int_i = 0; sputil.int_i < 7; sputil.int_i++)
  {
    if (sputil.dtostrf_i[sputil.int_i])
    {

      putx(sputil.dtostrf_i[sputil.int_i]);
    }
    sputil.dtostrf_i[sputil.int_i] = false;
  }
  */
  putx(',');
  mp_channel(panels[0].SUNSENSOR->CCW);
  delay_ms(5l);

  read_sensor_dir(panels[0].SUNSENSOR, ROT_CCW);
  putx_dtostrf(&(sputil.fl_ab));

  prints("\r\n");
  if (DEBUG)
  {
    prints("fl cw: ");
    sputil.fl_i = ToFloatAtCompileTime(panels[0].SUNSENSOR->CW);
    dtostrf(sputil.fl_i, 6, 2, sputil.dtostrf_i);
    for (sputil.int_i = 0; sputil.int_i < 7; sputil.int_i++)
    {
      if (sputil.dtostrf_i[sputil.int_i])
      {
        putx(sputil.dtostrf_i[sputil.int_i]);
      }
      sputil.dtostrf_i[sputil.int_i] = false;
    }

    prints("\r\nfl ccw: ");
    sputil.fl_i = ToFloatAtCompileTime(panels[0].SUNSENSOR->CCW);
    dtostrf(sputil.fl_i, 6, 2, sputil.dtostrf_i);
    for (sputil.int_i = 0; sputil.int_i < 7; sputil.int_i++)
    {
      if (sputil.dtostrf_i[sputil.int_i])
      {
        putx(sputil.dtostrf_i[sputil.int_i]);
      }
      sputil.dtostrf_i[sputil.int_i] = false;
    }
  }
  prints("\r\n");
  mp_channel(0); // back to rx - 0000b

  if (percent_change(sputil.fl_aa, sputil.fl_ab) > percent_diff)
  {
    turn_motor(panels[0].MOTOR, ROT_CW, (double)1000);

    mp_channel(1);
    prints("mot: cw\r\n");
  }
  else if (percent_change(sputil.fl_aa, sputil.fl_ab) < -percent_diff)
  {
    turn_motor(panels[0].MOTOR, ROT_CCW, (double)1000);

    mp_channel(1);
    prints("mot: ccw\r\n");
  }
  else
  {
    mp_channel(1);
    prints("mot: xx\r\n");
  }
  mp_channel(0); // back to rx - 0000b
  sputil.fl_aa = 0;
  sputil.fl_ab = 0;
  wdt_reset();
}

void putx_dtostrf(float *fla)
{
  mp_channel(1);
  char dtostrf_i[8];
  dtostrf((*fla), 6, 2, dtostrf_i);
  for (uint8_t int_i = 0; int_i < 7; int_i++)
  {
    if (dtostrf_i[int_i])
    {

      putx(dtostrf_i[int_i]);
    }
  }
}


