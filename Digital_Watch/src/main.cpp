/*                          Digital_Watch                       *
 *                      =====================                   *
 *                                                              *
 * Digital watch using a 7-segment display for time,            *
 * oled display for date, with standalone microcontroller       *
 * ATmega328p configuration.                                    * 
 *                                                              *
 *                                                              *
 * Author: Giacomo Mancin                                       *
 *                                                              */

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include "TM1637.h"
#include <Adafruit_SSD1306.h>
#include "image.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS3231 rtc;

#define PIN_CLK 2
#define PIN_DIO 3
TM1637 tm1637(PIN_CLK, PIN_DIO);

unsigned long t1;
int bt4, bt5;
int pvbt4, pvbt5;

void setup() {
  pinMode(8, INPUT);
  pinMode(12, INPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  // Clear the buffer
  display.clearDisplay();  
  

  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("RTC Error");
    while(true);  
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
  }
  tm1637.init();
  tm1637.set(3); // 0 to 7
}

void loop() {
  static bool fpoint;

  bt4 = digitalRead(8);
  bt5 = digitalRead(13);
  
  if ((millis() - t1) >= 500) {
    fpoint = !fpoint;
    tm1637.point(fpoint);

    DateTime now = rtc.now();
    int hh = now.hour();
    int mm = now.minute();
    int s  = now.second();
    int Y  = now.year();
    int M  = now.month();
    int D  = now.day();
    Serial.print(Y); Serial.print("-"); Serial.print(M); Serial.print("-"); Serial.println(D); 
    Serial.print(hh); Serial.print(":"); Serial.print(mm); Serial.print(":"); Serial.println(s); 

    int d1 = hh%10;
    int d2 = (hh/10)%10;
    int d3 = mm%10;
    int d4 = (mm/10)%10;

    tm1637.display(0, d2);
    tm1637.display(1, d1);
    tm1637.display(2, d4);
    tm1637.display(3, d3);
    t1 = millis();

    // Oled
    display.clearDisplay();  
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(20,0);     // Start at x,y coord
    display.cp437(true);         // Use full 256 char 'Code Page 437' font
    display.print(D); display.print("-"); display.print(M); display.print("-"); display.println(Y); 
    
    display.setCursor(1,0);
    display.drawBitmap(40, 20, logo, 50, 44, WHITE);
    display.display();
    delay(200);

  }

  if (bt4 && !pvbt4) {
     DateTime now = rtc.now();
     int mm = now.minute() + 1;
     if (mm >= 60) mm = 0;
     rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), mm, now.second()));
  }
  if (bt5 && !pvbt5) {
     DateTime now = rtc.now();
     int hh = now.hour() + 1;
     if (hh >= 24) hh = 0;
     rtc.adjust(DateTime(now.year(), now.month(), now.day(), hh, now.minute(), now.second()));
  }

  pvbt4 = bt4;
  pvbt5 = bt5;
}