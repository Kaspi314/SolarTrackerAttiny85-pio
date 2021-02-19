#include "Arduino.h"
#include <stdlib.h>

// MUX Pins //
// Select
#define S0 0
#define S1 1
#define S2 2
#define S3 3

// Signal switch registers ATTiny85 - CD74HC4067
#define SIG0 4

// Channels
#define C0 0
#define C1 1
#define C2 2
#define C3 3
#define C4 4
#define C5 5
#define C6 6
#define C7 7
#define C8 8
#define C9 9
#define C10 10
#define C11 11
#define C12 12
#define C13 13
#define C14 14
#define C15 15 // 16 channels.

void mp_setup();
void mp_channel(uint8_t channel);
