#include <Wire.h>  // to communicate with the presure sensor
#include <Adafruit_BMP085.h>  // include Pressure sensor library

Adafruit_BMP085 bmp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  // Make sure the pressure sensor is running
  if (!bmp.begin()) {
    Serial.println("Could not find BMP085");
    while (1) {}
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  String dataString = "";
  
  dataString += bmp.readTemperature(); // in celcius
  dataString += ",";
  
  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  dataString += bmp.readPressure();  
  dataString += ",";
  
  // This is assumed a 'standard' pressure of 1013.25
  dataString += bmp.readAltitude(); //meters  
  
  Serial.println(dataString);
  
  delay(1000);
}
