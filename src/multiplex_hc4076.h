#include "Arduino.h"
#include <stdlib.h>

// MUX Pins //
// Select
#define S0 0
#define S1 1
#define S2 2
#define S3 3

// Signal switch registers ATTiny85 - CD74HC4067
#define SIGD 4
#define SIGA A2

// Channels
#define C0 0 //   RX
#define C1 1 //   TX
#define C2 2 //   NC
#define C3 3 //   NC
#define C4 4 //   ST0
#define C5 5 //   S0A
#define C6 6 //   S0B
#define C7 7 //   NC
#define C8 8 //   ST1
#define C9 9 //   S1A
#define C10 10 // S1B
#define C11 11 // NC
#define C12 12 // M0A
#define C13 13 // M0B
#define C14 14 // M1A
#define C15 15 // M1B

void mp_setup();
void mp_channel(uint8_t channel);
