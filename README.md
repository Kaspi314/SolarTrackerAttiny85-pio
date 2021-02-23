This project is a solar tracker for tha attiny85. It uses picoCore and picoUART as the attiny85 does not have an integrated serial peripheral.

It is stilll rather crude at this point and I'm just trying to get it working.

TODO:

* Use a PID in deciding how far to drive the linear actuators.
* Figure out why Channel C5 is not working for analog input on the multiplexer. (Possibly this is an issue with this board, or the circuitry I am using to switch the RS485 DE/RE for TTL.)
* Figure out why a byte must be discarded with the PicoUART RX ISR when using PicoCore.
