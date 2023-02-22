/*
  OLED Temperature and Humidity Meter
  oled-temp-humid-meter.ino
  Displays results on 128 x 64 OLED display
  Uses AM2320 I2C Temperature and Humidity sensor
  Uses Adafruit SSD1306 OLED Library
  Uses Adafruit AM2320 Library
  Uses Adafruit GFX Graphics Library
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Sous-Vide");
    display.setCursor(0,9);
    display.print("TEST! data here, this is a test to understand the limitations of this OLED display.");
    display.display();
}