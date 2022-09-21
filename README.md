# macropad


## Device Drivers

The macropad is still useable without the drivers, the OLED display will not display any information however

1. Install python from [python.org](https://python.org)
2. Download `macropad.pyw`
3. Open command line
4. Run the following commands:
    1. `pip install pyserial`
    2. `pip install psutil`
    3. `pip install speedtest-cli`
5. Plug in macropad
6. Run `macropad.pyw`


To exit the driver script run the follow command `TASKKILL /F /IM pythonw.exe`

## Arduino 

The macropad should already have code uploaded to it, however if you want to edit the code and reupload, do the following steps

1. Download Arduino IDE
2. Plug in board
3. Add Board
    1. `File > Preferences`
    2. `Additional Boards Manager URLs`
    3. Add `https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json` to the text box
    4. `Tools > Board: > Boards Manager...`
    5. Install `"SparkFun AVR Boards"`
    6. `Tools > Board: > SparkFun AVR Boards > SparkFun Pro Micro`
    7. `Tools > Processor > ATMega32U4 (5v, 16 Mhz)` 
4. Install HID-Project Library (Keyboard)
    1. Go to [https://github.com/NicoHood/HID](https://github.com/NicoHood/HID)
    2. Download the code as a ZIP
    3. `Sketch > Include Library > Add .ZIP Library...`
    4. Select `HID-master.zip` from your files
5. Install Adafruit SSD1306 Library (OLED)
    1. `Sketch > Include Library > Manage Libraries`
    2. Install `"Adafruit SSD1306"` along with it's dependencies
6. Upload Code
    1. `Tools > Port:`
    2. Select the correct port
    3. Upload the code


## Parts
- SparkFun Pro Micro (Clone) (x1) ($7.00)
  - Processor: ATMega32U4
  - Flash Memory: 32kb
  - Clock Speed: 16Mhz
  - Voltage: 5v
- 12C 128x64 OLED Display (x1) ($3.00)
- 20 Step Rotary Encoder (x4) ($2.00)
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
  4. *Network Information (ping, up, down, ip)
  5. *Computer Media Info
  6. *Weather
- Button 1
- Button 2

* wip, add graphs?


## Pins
- 5v & gnd = 2
- rotary encoders: 12 *
- buttons: 2 *
- oled: 2
- oled buttons: 2 *

total required pins: 20

* read and written to by the board
