/*
  An example ;to access the realtime clock from the
  Adafruit SD logger shield.
  
*/
// include libraries
#include <Wire.h>
#include "RTClib.h"

// initialize library
RTC_DS1307 RTC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Make sure the clock is running
  if (! RTC.isrunning()) {
    Serial.println("RTC NOT running");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  String dataString = "";
  DateTime now = RTC.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
}
