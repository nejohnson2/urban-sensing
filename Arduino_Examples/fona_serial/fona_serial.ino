/*
  This is a basic example to connect to the Adafruit
  FONA GSM module through software serial.  Once connected
  you can send AT commands.  This is just for playing.
  
  You will need an antenna and a battery connected for this
  to work.
  
  Wiring:
  FONA RX  - Arduino Pin 2
  FONA TX  - Arduino Pin 3
  FONA Vin - Arduino 5v
  FONA Gnd - Arduino Gnd
  
*/
#include <SoftwareSerial.h>
SoftwareSerial fona = SoftwareSerial(3,2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  fona.begin(9600);
  Serial.println("GSM Started");
}

void loop() {
  if (fona.available())
    Serial.write(fona.read());
  if (Serial.available())
    fona.write(Serial.read());
}
