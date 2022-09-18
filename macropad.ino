// keyboard
#include <HID-Project.h>

// oled
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// pin locations
// rotary encoder
const int pin_c = 5; // green (rotary encoder)
const int pin_d = 6; // blue (rotary encoder)
const int pin_s = 7; // orange (rotary encoder button)
// led
const int pin_l = 8; // brown (led)
// oled buttons
const int pin_ob1 = 9; // yellow (oled button 1)
const int pin_ob2 = 4; // purple (oled button 2)


int x = 0;

// pin values
int c = LOW; // green
int d = LOW; // blue
int s = LOW; // orange/yellow (button)
int ob1 = LOW; // oled button 1
int ob2 = LOW; // oled button 2
int last_c = LOW;
int last_d = LOW;
int last_s = LOW;
int last_ob1 = LOW;
int last_ob2 = LOW;


int count = 500;
String data = "None";
int screen = 0;
// 0: clock
// 1: cpu
// 2: memory
// ram, media, volume

// initialize oled
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
  // serial
  Serial.begin(9600);
  Serial.setTimeout(1);

  // start keyboard
  Consumer.begin();

  // rotary encoder
  pinMode(pin_c, INPUT_PULLUP);
  pinMode(pin_d, INPUT_PULLUP);
  pinMode(pin_s, INPUT_PULLUP);

  // led
  pinMode(pin_l, OUTPUT);


  // initialize oled
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{

  // serial
  if (Serial.available())
  {
    data = Serial.readString();
    draw();
  }

  // pin values
  c = digitalRead(pin_c);
  d = digitalRead(pin_d);
  s = digitalRead(pin_s);
  ob1 = digitalRead(pin_ob1);
  ob2 = digitalRead(pin_ob2);

  // rotary encoder
  if (last_c == LOW && last_d == LOW)
  {
    if (c == HIGH && d == LOW)
    {
      // rotary encoder right
      Consumer.write(MEDIA_VOLUME_UP);
    }
    else if (c == LOW && d == HIGH)
    {
      // rotary encoder left
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
  }

  if (last_s == HIGH && s == LOW)
  {
    // rotary encoder button button
    Consumer.write(MEDIA_VOLUME_MUTE);
  }

  if (last_ob1 == HIGH && ob1 == LOW)
  {
    // oled button 1
    data = "";
    screen += 1;
    if (screen == 3) {
      screen = 0;
    }
    draw();
    Serial.println(screen);
  }

  if (last_ob2 == HIGH && ob2 == LOW)
  {
    // oled button 2
    data = "";
    screen -= 1;
    if (screen == -1) {
      screen = 2;
    }
    draw();
    Serial.println(screen);
  }


  // set last values
  last_c = c;
  last_d = d;
  last_s = s;
  last_ob1 = ob1;
  last_ob2 = ob2;

  // led
  if (count >= 500)
  {
    digitalWrite(pin_l, HIGH);
    if (count >= 1000)
    {
      digitalWrite(pin_l, LOW);
      count = 0;
    }
  }

  count++;
  delay(1);
}

void draw(void)
{

  // font is 5x7
  // oled is 128x64
  // 21 characters wide
  // 10 characters wide
  // 1px gap between characters
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // handle data
  String arr[2];

  int j = 0;
  for (int i = 0; i <= data.length(); i++) {
    if (data.charAt(i) != '$') {
      // is not the break character
      arr[j] += data.charAt(i);
    } else {
      // is the break character
      j++;
    }
  }

  if (screen == 0) {
    // clock
    display.setTextSize(1);
    display.setCursor(4, 0);
    display.println(arr[0]);
    display.setCursor(16, 20);
    display.setTextSize(2);
    display.println(arr[1]);

  } else if (screen == 1 || screen == 2) {
    // cpu or ram
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println(arr[0]);
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.println(arr[1]);
  }
  display.display();
}
