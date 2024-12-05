# SmoothBus Src

This folder contains the code that gets slapped onto the ATTiny85 chip using the Arduino IDE.


### Dependencies

* [Konde's ATTinyCore library](https://github.com/SpenceKonde/ATTinyCore) - add to your Arduino IDE.

### Flashing

* I used an Arduino Mega2560 as an ISP to flash the ATTiny85 with the programming jig. [Here](https://www.instructables.com/How-to-Burn-ATTiny85-Using-Arduino-Mega/) is a decent write up.
    * Flashed the ATTiny85 with the clock set to 16 Mhz, anything less with introduce more servo jitter.

## Things to improve
* Discard readings that are dramatically different than previous reading. Could be based on percent difference.
* Low fuel warning indicator logic could be improved to not trigger on every time it has a reading in that range. Instead turn the warning lights on if there has been continuous readings in that range (maybe something along the lines of if 20 readings) same with turning them off. This could help reduce flashing warning lights when you take a turn.