#include <HID-Project.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// pin locations
const int pin_c = 5; // green
const int pin_d = 6; // blue
const int pin_s = 7; // orange (button)
const int pin_l = 8; // brown (led)
const int pin_b = 9; // yellow (button)

int x = 0;

// pin valuesxf
int c = LOW; // green
int d = LOW; // blue
int s = LOW; // orange/yellow (button)
int b = LOW;
int last_c = LOW;
int last_d = LOW;
int last_s = LOW;
int last_b = LOW;


int count = 500;
String data = "None";
int screen = 0;
// 0: clock
// 1: cpu
// 2: memory
// 3: off
// ram, media, volume

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
  // serial
  Serial.begin(9600);
  Serial.setTimeout(1);

  // start keyboard
  Consumer.begin();

  // initialize pins
  // rotary encoder
  pinMode(pin_c, INPUT_PULLUP);
  pinMode(pin_d, INPUT_PULLUP);
  pinMode(pin_s, INPUT_PULLUP);

  // led
  pinMode(pin_l, OUTPUT);

  // button
  pinMode(pin_l, INPUT_PULLUP);

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
  b = digitalRead(pin_b);

  // rotary encoder rotations
  if (last_c == LOW && last_d == LOW)
  {
    if (c == HIGH && d == LOW)
    {
      // right
      Consumer.write(MEDIA_VOLUME_UP);
    }
    else if (c == LOW && d == HIGH)
    {
      // left
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
  }

  if (last_s == HIGH && s == LOW)
  {
    // button
    Consumer.write(MEDIA_VOLUME_MUTE);
  }

  if (last_b == HIGH && b == LOW)
  {
    data = "";
    screen += 1;
    if (screen == 4) {
      screen = 0;
    }
    draw();
    Serial.println(screen);
  }

  // set last values
  last_c = c;
  last_d = d;
  last_s = s;
  last_b = b;

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
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  if (screen == 0) {
    // clock
    display.setTextSize(2);
    display.println(data);

  } else if (screen == 1 || screen == 2) {
    // cpu
    display.setTextSize(1);
    display.println(data);
  } else if (screen == 3) {
    // none, off
  }



  //  display.setTextSize(2);
  /// display.print("Text ");
  //display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);

  display.display();
}
