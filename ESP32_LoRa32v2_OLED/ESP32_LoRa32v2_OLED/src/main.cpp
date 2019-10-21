#include <Arduino.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`

// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, 21, 22);

void setup() {
  Serial.begin(500000);
  Serial.println("setup()");
  Serial.println();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

int t_start, t_elapsed = 1;

void loop() {
  
  t_start = micros();
  // clear the display
  display.clear();
  // create more fonts at http://oleddisplay.squix.ch/
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "NSEE");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 24, "Simucam");
  //display.setFont(ArialMT_Plain_24);
  //display.drawString(0, 40, String(micros()));

  //display.setTextAlignment(TEXT_ALIGN_RIGHT);
  //display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  //Serial.println("FPS = " + FPS);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 40, String(1000000/t_elapsed));
  display.display();
  
  t_elapsed = micros() - t_start;
}
