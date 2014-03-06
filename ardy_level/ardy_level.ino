/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

// set pin numbers
const int xaxis = A1;
const int yaxis = A0;
const int zaxis = A2;

// variables
int xstate = 0;
int ystate = 0;
int xoutput = 0;
int youtput = 0;
int led_color = LED_GREEN;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  pinMode(xaxis, INPUT);
  pinMode(yaxis, INPUT);
  pinMode(zaxis, INPUT);
  
  matrix.begin(0x70);  // pass in the address
}

static const uint8_t PROGMEM
  custom[] = 
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00010000,
    B00000000,
    B00000000,
    B00000000 },
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };

void loop() {

  xstate = analogRead(xaxis);
  ystate = analogRead(yaxis);
  Serial.println("Accelerometer: ");
  Serial.println(xstate);
  Serial.println(ystate);
//  xoutput = xstate/10;
  // Range 260 - 330 - 400
  // 260-270 = 0
  // 270-280 = 1
  // 280-290 = 2
  // 290-300 = 3
  // 300-360 = 3&4
  // 360-370 = 4
  // 370-380 = 5
  // 380-390 = 6
  // 390-400 = 7
  xoutput = (xstate-260)/17.5;
  youtput = (ystate-260)/17.5;
  led_color = LED_GREEN;
  if (xoutput < 1 || xoutput > 6 || youtput < 1 || youtput > 6){
    led_color = LED_RED;
  }  
  
/*  
  matrix.clear();
  matrix.drawBitmap(0, 0, custom, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(2000);
  */
  
  matrix.clear();      // clear display
  matrix.drawPixel(xoutput, youtput, led_color);  
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1000);

  
/*
  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();      // clear display
  matrix.drawPixel(0, 0, LED_GREEN);  
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawLine(0,0, 7,7, LED_YELLOW);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawRect(0,0, 8,8, LED_RED);
  matrix.fillRect(2,2, 4,4, LED_GREEN);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawCircle(3,3, 3, LED_YELLOW);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);
  for (int8_t x=7; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Hello");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(3);
  matrix.setTextColor(LED_RED);
  for (int8_t x=7; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("World");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);
*/
}

