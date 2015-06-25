/*
  This is a basic example to get the Adafruit GPS modeule
  working.
  
  Please note: Sometimes the GPS module takes several minutes 
  to get a fix, especially the first time.  
  
  Wiring with Software Serial (not hardware):
  GPS Tx  > Arduino Pin 3   // defined in software serial 
  GPS Rx  > Arduino Pin 2   // defined in software serial
  GPS Vin > Arduino 3.3v
  GPS Gnd > Arduino Gnd
  
*/

#include <Adafruit_GPS.h>    //Install the adafruit GPS library
#include <SoftwareSerial.h> //Load the Software Serial library

SoftwareSerial mySerial(3, 2); //Initialize the Software Serial port
Adafruit_GPS GPS(&mySerial); //Create the GPS Object

uint32_t timer = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //Turn on serial monitor
  GPS.begin(9600); //Turn on GPS at 9600 baud
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Request RMC and GGA Sentences only
  //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Set update rate to 1 hz
  Serial.println("GPS Started");
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  char c = GPS.read();
  String dataString = "";

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
  
  if (timer > millis())  timer = millis();
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    if (GPS.fix) {
      dataString += GPS.latitude;  // this is more accurate
      dataString += ",";
      dataString += GPS.longitude;  // this is more accurate 
      dataString += " - ";
      dataString += GPS.latitudeDegrees;  // rounded in degrees
      dataString += ",";
      dataString += GPS.longitudeDegrees; //rounded in degrees
      Serial.println(dataString);     
      
    } else {
      Serial.println("Failed to get a fix");
    }
  }      
}
