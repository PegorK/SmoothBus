# SmoothBus Hardware

This folder contains the 3D parts that were used and the PCB components including the schematic.

## 3D Parts

There are 4 total parts that were 3D printed:
* `case.stl`: The housing that the PCB and dial get mounted onto. Printed at standard 0.20mm layer height.
* `hand.stl`: The indicator hand that was then attached to a servo arm. Printed at 0.08mm layer height to preserve the chamfer detail.
* `programming_jig.stl`: The jig that was used along with needle probes to sit on the case and be used to program the MCU. Printed at standard 0.20mm layer height, but the holes didn't come out with the print and I had to drill them by hand with some [REALLY tiny PCB drill bits](https://a.co/d/grPr89h). Resin printing might be better for this piece if possible.
* `spacer.stl`: Required spacer to make sure the connection screws on the back don't short against the metal backplate. Based on the original spacer, but shortened. Printed at standard 0.20mm layer height.

## PCB
* `board_layout_gerber.zip`: Zip file that contains the necessary files to be sent to a PCB manufacturer. This can be directly uploaded to most online manufacturers and should be all you need.
* `smoothbus_v1.pdf`: Schematic that the PCB was based off. 


## Parts list
Most parts were ordered from DigiKey. You can find the link to every part below.
* [ATTiny85 MCU](https://www.digikey.com/en/products/detail/microchip-technology/ATTINY85-20SU/735470?so=89524344&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGWmcaWXekrVHnhWS_QH42e2IfO4IPqG7whUqVekeKc50QXDYyLq4FDMk1B03GmXVukNkQf5vT7wma6IGS9dvrSbytcA07hW30_9-LSLiFI)
* [Voltage Regulator](https://www.digikey.com/en/products/detail/onsemi/MC7805BDTRKG/919331?so=89524344&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGWmcaWXQPZI5IpIA4jxuSj-j0oJsKcf3MiN5_SPBbcSTN6yNa732chOnHBOtDvxcu8hei2zJ8ulLiHPiOVp4p6lIHpy8KIhn2Zh2r5UxWp)
* [Resistor (100 ohm)](https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-3EKF1000V/196074?so=89524344&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGWmcaWXYRDXpi8Ml4N9Sp83X4YqKcldPyiTMATzQcQUZd8mh4gmYTtWWy6-fSJDjSYEJzsJjWVK19N6Dzl_O6S3iiEtepvPORJ8gQC9Rv4)
* [Resistor (300 ohm)](https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-3EKF3000V/1746363?so=89524344&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGWmcaWXdEbFEk2vnz8TdDCMYi2ZvBRvi0xZ3QWf4A1BBz3Y6H9VUHtYQ7Hx6Yc9U8TIDwPAMeCyvmbiHD4zOseAaEuE4b6-RVKmEEzlJ0n)
* [Capacitor](https://www.digikey.com/en/products/detail/panasonic-electronic-components/EEE-1AA101WAR/1717732?so=89524344&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGWmcaWXXrESR0Uub-6f2kRNF92ux7_UfMi5lWjfZ3HeSCeRQ4K-QIheCeCLtJbuBlB7UzqJeScWqTYXTorI1clshc5IrSi3ZXfU0YRYQy1)
* [Green LED](https://www.digikey.com/en/products/detail/w%C3%BCrth-elektronik/150060VS55040/8557182?so=89524344&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGWmcaWXSWnwSJVfg821OYlSVqJ8XjR337j5IsVlRd9hIlqfH-6m_PKL9PQZvykHguCCXttRMn7EU1WLZ2d0dGRmJl8GlbqXjSWTcFVhbzZ)
* [Red LED](https://a.co/d/7SslF5E)
* [Servo](https://a.co/d/cdSHXeV)
* [Test probe pins used on programming jig](https://a.co/d/gTRcbDf)
* M5 Screws and Nuts (ACE/Home Depot)

## Things to improve
* Ditch the probe points and programming jig. Add a connector instead.