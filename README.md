# macropad

## Device Driver Installation

The macropad is still useable without the drivers, the OLED display will not display any information however

1. install python from [python.org](https://python.org)
2. download `macropad.py`
3. open command line
4. run the following commands:
 - `pip install pyserial`
 - `pip install psutil`
5. plug in macropad
6. run `macropad.py`


## Parts
- SparkFun Pro Micro (Clone) (x1)
  - Processor: ATMega32U4
  - Flash Memory: 32kb
  - Clock Speed: 16Mhz
  - Voltage: 5v
- 12C 128x64 OLED Display (x1)
- 20 Step Rotary Encoder (x4)
- Tactile Buttons (x2)
- LED (x1)
- On/Off Switch (x1)

## Actions
- Rotary Encoder 1, Volume Down, Volume Up, Mute
- Rotary Encoder 2, Previous Track, Next Track, Play/Pause
- Rotary Encoder 3, [Ctrl Z], [Ctrl Y], [Ctrl S]
- Rotary Encoder 4, [Ctrl -], [Ctrl +], [Ctrl 0]
- OLED Display
  1. Date & Time
  2. CPU Usage, Frequency, Cores, & Threads
  3. RAM Usage & Total
- Button 1
- Button 2


## Pins
- 5v & gnd = 2
- rotary encoders: 12
- buttons: 2
- oled: 2
- oled buttons: 2

total required pins: 20