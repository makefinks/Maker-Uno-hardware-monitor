# Maker Uno hardware monitor

## Inspiration

After receiving a Maker Uno from one of my Professors I wanted to experiment and try to make something that I would actually use. I recently built a new PC and wanted the project to have something to do with it. My Idea: Extending the Maker Uno with a shield display and make it able to display useful information about my hardware components (Temperature, fan speeds, etc.)

## What I used
#### Hardware:
- Maker UNO
- [ELEGOO UNO R3 2,8" TFT Touchscreen](https://www.amazon.de/gp/product/B01EUVJYME/ref=ppx_yo_dt_b_search_asin_image?ie=UTF8&psc=1)
#### Software:
- [OpenHardwareMonitor](https://openhardwaremonitor.org/)
#### Languages:
- Python
- Arduino (C++)

## How it works

### Gathering Information:
I wrote a Python script using WMI ([Windows Management Instrumentation](http://openhardwaremonitor.org/wordpress/wp-content/uploads/2011/04/OpenHardwareMonitor-WMI.pdf)) to get information from OpenHardwareMonitor an open-source software that monitors information about hardware components.

To send information to the microcontroller, via the serial ports of my computer, I used [pySerial](https://pyserial.readthedocs.io/en/latest/pyserial.html).

### Displaying Information:
To display information on the Screen I first had to learn about the Elegoo GFX Library (based on [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library))
Using the provided Library and the information sent to the serial ports of the Maker UNO I was able to come up with a design and display the gathered data accordingly.



## The Result
![Bild3](https://user-images.githubusercontent.com/62705365/154338222-11f12e88-9cd5-4de0-ad9b-cb2318c2ada6.jpg)

Depending on the usage of CPU, GPU, and RAM the color used to fill the boxes will change from blue (0-30%) to orange (30-70%) and eventually to red (70-100%).
The thin bars next to CPU and GPU show the current fan speed of the component and coloring is used as mentioned above.
Currently, the power draw is calculated only by how much the CPU and GPU draw other components are *not* included.

## TODO
- All arguments regarding the position of elements are absolute and not relative to the size of the display. This has to be changed.
- Currently there is no way to see the exact usage of the components other than how much the boxes are filled. A solution would be to display the usage in percent within the boxes.

