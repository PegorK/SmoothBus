# SmoothBus Hardware

This folder contains the 3D parts that were used and the PCB components including the schematic.

## 3D Parts

There are 4 total parts that were 3D printed:
* `case.stl`: The housing that the PCB and dial get mounted onto. Printed at standard 0.20mm layer height.
* `hand.stl`: The indicator hand that was then attached to a servo arm. Printed at 0.08mm layer height to preserve the chamfer detail.
* <s>`programming_jig.stl`: The jig that was used along with needle probes to sit on the case and be used to program the MCU. Printed at standard 0.20mm layer height, but the holes didn't come out with the print and I had to drill them by hand with some [REALLY tiny PCB drill bits](https://a.co/d/grPr89h). Resin printing might be better for this piece if possible.</s> No longer needed in V2.
* `spacer.stl`: Required spacer to make sure the connection screws on the back don't short against the metal backplate. Based on the original spacer, but shortened. Printed at standard 0.20mm layer height.

## PCB
* `board_layout_v2_gerber.zip`: Zip file that contains the necessary files to be sent to a PCB manufacturer. This can be directly uploaded to most online manufacturers and should be all you need.
* `smoothbus_v2.pdf`: Schematic that the PCB was based off. 


## Parts list
Most parts were ordered from DigiKey. You can find the link to every part below.
* [ATTiny85 MCU](https://www.digikey.com/short/wmvr7mbd)
* [Voltage Regulator (Automotive Version)](https://www.digikey.com/short/zhz2rd08)
* [Resistor (50Ω)](https://www.digikey.com/short/8h7b4hvm)
* [Resistor (300Ω)](https://www.digikey.com/short/w4hn2znd)
* [Resistor (10kΩ)](https://www.digikey.com/short/w4hn2znd)
* [Capacitor (100uF)](https://www.digikey.com/short/0v2nvz3h)
* [Capacitor (0.33uF)](https://www.digikey.com/short/m4wq48mh)
* [Capacitor (0.1uF)](https://www.digikey.com/short/tbf0djj4)
* [Green LED](https://www.digikey.com/short/ftfzptp3)
* [Red LED](https://a.co/d/7SslF5E)
* [Poly-Fuse](https://www.digikey.com/short/mqrrf4v7)
* [Watchdog Timer](https://www.digikey.com/short/7f4vbqbd)
* [TVS Diode](https://www.digikey.com/short/rtwmwz2c)
* [6 Pos Header](https://www.digikey.com/short/1v5wj33f)
* [SPDT Switch](https://www.digikey.com/short/7v9fw0z2m)
* [Servo](https://a.co/d/cdSHXeV)
* M5 Screws and Nuts (ACE/Home Depot)