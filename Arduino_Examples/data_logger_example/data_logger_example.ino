/*
  SD Datalogger

  This was built from the DataLogger example and
  an example by Surya Mattu for Networked Sensors
  for Development class.

  The circuit
  * SD card attached to SPI bus as follows:
  ** MOSI / DI- pin 11
  ** MISO / DO - pin 12
  ** CLK - pin 13
  ** CS - pin 10

  Pressure sensor
  // Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
  // Connect GND to Ground
  // Connect SCL to i2c clock - (Analog 5)
  // Connect SDA to i2c data - (Analog 4)

*/

// include libraries for real time clock
#include <Wire.h>
#include "RTClib.h"

// include SD libraries
#include <SPI.h>
#include <SD.h>

// include Pressure sensor library
#include <Adafruit_BMP085.h>

// include GPS libraries
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

const int chipSelect = 10; // chip to communicate with SD module

File dataFile;
RTC_DS1307 RTC;
Adafruit_BMP085 bmp;
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);

uint32_t timer = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  RTC.begin();
  GPS.begin(9600);

  // Make sure the clock is running
  if (! RTC.isrunning()) {
    Serial.println("RTC NOT running");
  }
  // Make sure the pressure sensor is running
  if (!bmp.begin()) {
    Serial.println("Could not find BMP085");
    while (1) {}
  }

  // initialize the SD card
  if (initSD()) {
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    String dataString = "";

//    dataString += bmp.readTemperature(); // in celcius
//    dataString += ",";
//    
//    // Calculate altitude assuming 'standard' barometric
//    // pressure of 1013.25 millibar = 101325 Pascal
//    dataString += bmp.readPressure();
//    dataString += ",";
//    
//    // This is assumed a 'standard' pressure of 1013.25
//    dataString += bmp.readAltitude(); //meters
//    dataString += ",";
    
    /**************** Begin GPS *****************/
    char c = GPS.read();

    if (GPS.newNMEAreceived()) {
      if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
        return;  // we can fail to parse a sentence in which case we should just wait for another
    }

    if (GPS.fix) {
      dataString += GPS.latitudeDegrees;
      dataString += ",";
      dataString += GPS.longitudeDegrees;
    } else {
      Serial.println("No Fix"); 
    }

    /************** End GPS ****************/

    DateTime now = RTC.now();

    // building data to write to file
//    dataString += now.year();
//    dataString += ",";
//    dataString += now.month();
//    dataString += ",";
//    dataString += now.day();
//    dataString += ",";
//    dataString += now.hour();
//    dataString += ":";
//    dataString += now.minute();
//    dataString += ":";
//    dataString += now.second();

    Serial.println(dataString);

    dataFile.println(dataString);
    dataFile.flush();
  }
  delay(1000);
}

boolean initSD() {
  Serial.print("Initializing...");
  pinMode(SS, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1) ;
  }
  Serial.println("initialized.");

  // Open up the file we're going to log to!
  dataFile = SD.open("datafile.txt", FILE_WRITE);
  if (!dataFile) {
    Serial.println("error");
    // Wait forever since we cant write data
    while (1) ;
  }
  return true;
}
