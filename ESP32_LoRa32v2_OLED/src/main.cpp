#include <Arduino.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`

// Initialize the OLED display using Wire library
SSD1306Wire  display(0x3c, 21, 22);

void setup() {
  Serial.begin(2000000); // 2Mbps serial
  Serial.println("setup()");
  Serial.println();

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
}

unsigned int t_start = 1;
unsigned int t_elapsed1[100];
unsigned long int t_elapsed1_avg = 1;
unsigned int t_elapsed2[100];
unsigned long int t_elapsed2_avg = 1;
unsigned int i = 0;
unsigned int j = 0;
unsigned int k = 0;


void oled_display_1() {
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
  display.drawString(0, 40, String(t_elapsed1_avg)+":"+String(t_elapsed2_avg));
  display.display();
}

void oled_display_2() {
  // clear the display
  display.clear();
  // create more fonts at http://oleddisplay.squix.ch/
  //display.setTextAlignment(TEXT_ALIGN_LEFT);
  //display.setFont(ArialMT_Plain_16);
  display.drawString(0,  0, "display: "+String(t_elapsed1_avg)+" us");
  display.drawString(0, 16, "display: "+String(t_elapsed1_avg)+" us");
  display.drawString(0, 32, "display: "+String(t_elapsed1_avg)+" us");
  display.drawString(0, 48, "display: "+String(t_elapsed1_avg)+" us");
  //display.setFont(ArialMT_Plain_16);
  //display.drawString(0, 16, "printf: "+String(t_elapsed2_avg)+" us");
  //display.setFont(ArialMT_Plain_24);
  //display.drawString(0, 40, String(micros()));

  //display.setTextAlignment(TEXT_ALIGN_RIGHT);
  //display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  //Serial.println("FPS = " + FPS);
  //display.setFont(ArialMT_Plain_24);
  //display.drawString(0, 40, +":"+String(t_elapsed2_avg));
  display.display();
}

void loop() {
  
  t_start = micros();
  oled_display_2();
  t_elapsed1[i++] = micros() - t_start;
  if (i > 99) i = 0;
  
  t_elapsed1_avg = 0;
  for(j=0 ; j<100 ; j++){
      t_elapsed1_avg += t_elapsed1[j];
  }
  t_elapsed1_avg = t_elapsed1_avg / 100;


  t_start = micros();
  Serial.printf("*");
  t_elapsed2[k++] = micros() - t_start;
  if (k > 99) k = 0;


  t_elapsed2_avg = 0;
  for(j=0 ; j<100 ; j++){
      t_elapsed2_avg += t_elapsed2[j];
  }
  t_elapsed2_avg = t_elapsed2_avg / 100;



  //Serial.printf("terminal: elapsed time in display function : %lu microsseconds, time in print function : %lu microsseconds.\n", t_elapsed1_avg, t_elapsed2_avg);
  Serial.printf("terminal: elapsed time in display function : %lu microsseconds, print function : %lu microsseconds.\n", t_elapsed1_avg, t_elapsed2_avg);
  

  delayMicroseconds(500000); // wait 500 miliseconds.
}


//*terminal: elapsed time in display function : 8658 microsseconds, time in print "*" function : 24 microsseconds. @ 2Mbps serail baudrate.