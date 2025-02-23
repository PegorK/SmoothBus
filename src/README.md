# SmoothBus Src

This folder contains the code that gets slapped onto the ATTiny85 chip using the Arduino IDE.


### Dependencies

* [Konde's ATTinyCore library](https://github.com/SpenceKonde/ATTinyCore) - add to your Arduino IDE.

### Flashing

* I used an Arduino Mega2560 as an ISP to flash the ATTiny85. [Here](https://www.instructables.com/How-to-Burn-ATTiny85-Using-Arduino-Mega/) is a decent write up.
    * Flashed the ATTiny85 with the clock set to 16 Mhz, anything less will introduce more servo jitter.