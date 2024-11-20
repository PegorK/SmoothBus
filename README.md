<div align="center">
  <img src="pictures/logo.png" alt="CoverImage" width="800px"/>
</div>
<p>
SmoothBus is a fuel gauge conversion for the classic VW Bus. More specifically a 1978 Bus. It's an all in one package with a small form factor that is slightly larger than the original gauge and can be installed with very minimal modifications to the dash. A majority of this project was done over a weekend, so don't expect perfection, but for my case it was a huge upgrade to a non working gauge.
</p>
<p>
The original gauges in the buses are pretty clever design in my opinion. I've included a picture of it below. You can see it's rather simple and if my understanding is correct the flow of current through it causes the wire to heat up and expand which causes the needle to move to different positions. The current is controlled by the fuel sender float which is located in the fuel tank and is essentially a rheostat. Utilizing this thermal property also smooths out bumps and turns since it takes a second or two for it expand & contract. These things don't normally break, it's the voltage regulator that they are connected to that often goes bad, but what's the fun in replacing that when you can make your own.
</p>

<div align="center">
    <img src="pictures/original_gauge.jpg" alt="Original fuel gauge" width="300"/>
    <br />Original fuel gauge guts.
</div>

The SmoothBus design ditches the old gauge components including the voltage regulator keeping only the fuel sender float which is used as the variable resistor in the voltage divider circuit. The overall process is still pretty simple, the ATTiny85 microcontroller reads the analog voltage on one of it's pins and outputs that value as a servo position that corresponds to the location on the original dial. The positions & values were determined by some very useful investigations that were done in this [samba forum post](https://www.thesamba.com/vw/forum/viewtopic.php?t=693930). The analog voltage that gets inputted is the voltage divider circuit that consists of a known resistor value (100ohms) and the unknown resistor value from the fuel sender which ranges from 10 ohms to 79ohms. There is also a moving average that is happening with each read. The configuration that I found works best has been a moving average window of 35 that has readings every 200ms. All of this can be easily changed in the code that can be found in `src` directory. It should be pretty easy to setup, it was all written in the Arduino IDE with the [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore) library that adds support to a bunch of tinyAVR devices (very cool project).

Programming the board wasn't the most intuitive. I decided to have probe points on the board (bottom left corner of PCB) that I thought would be a good idea to easily program the device, but it ended up being a bit finicky. It required making a jig and using tiny spring loaded probes that were then connected to an Arduino Mega that was used as an ISP (see below). [I thought I learned my lesson last time](https://gitlab.com/_Pegor/kepler_fw/-/tree/master/Hardware?ref_type=heads#programming-jig). I think the rest of design is rather straight forward. It contains a voltage regulator that can handle up to 35V and also has some red LEDs to indicate low fuel level. The schematic is included in `hardware/PCB` along with the gerber zip that you can send to a PCB manufacturer of your choice.

<div align="center">
    <table>
        <tr>
            <td>
                <div align="center">
                    <img src="pictures/pcb.jpg" alt="PCB" width="400"/>
                    <br />PCB
                </div>
            </td>
            <td>
                <div align="center">
                    <img src="pictures/programming_jig.jpg" alt="Programming jig" width="400"/>
                    <br /> Programming jig
                </div>
            </td>
        </tr>
    </table>
</div>

<div align="center">
    <img src="pictures/render_1.png" alt="Smooth bus render" width="300"/>
    <br />Render of all the parts.
</div>

I have included all the required 3D parts seen in the render above in the `hardware/3D Parts` directory. Everything was printed in GF-ASA so there is no warping due to warmer temperatures. Installation of the gauge required drilling one hole for the ground screw, other than that there was no other modification required to the dash. You can see it installed below. The red screw is the 12v line, the yellow is for the fuel sender, and the middle is ground, that whole backplate is grounded so no need to run additional wires.

<div align="center">
    <table>
        <tr>
            <td>
                <div align="center">
                    <img src="pictures/installed_1.jpg" alt="Installed Gauge" width="400"/>
                    <br />Installed fuel gauge
                </div>
            </td>
            <td>
                <div align="center">
                    <img src="pictures/installed_2.jpg" alt="Installed Gauge" width="400"/>
                    <br /> Terminals of the fuel gauge
                </div>
            </td>
        </tr>
    </table>
</div>

Lastly here is a picture of the finished product and a gif of it in action. Happy tinkering!

<div align="center">
    <table>
        <tr>
            <td>
                <div align="center">
                    <img src="pictures/complete_build.jpg" alt="SmoothBus Fuel Gauge" width="400"/>
                    <br />Complete build
                </div>
            </td>
            <td>
                <div align="center">
                    <img src="pictures/smoothbus.gif" alt="Installed Gauge" width="400"/>
                    <br /> GIF of it in action
                </div>
            </td>
        </tr>
    </table>
</div>
