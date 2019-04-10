
#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.
SoftwareSerial mySerial2(4, 5); // RX, TX, Create a softwareSerial port on pins 4 and 5.

String IncomingData;

void setup() 
{
  mySerial1.setTimeout(10);
  mySerial2.setTimeout(10);
  Serial.setTimeout(10); 
   
  Serial.begin(115200);
  
  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
  mySerial1.println("s"); //Initialise the controller to accept serial command strings.
  
  mySerial2.begin(115200); //Baud rate between Arduino and Controller.
  mySerial2.println("s"); //Initialise the controller to accept serial command strings.
}

void loop() 
{

//if (Serial.available() > 0)
//  {
  IncomingData = Serial.readString();
  
  Serial.println(IncomingData);
  //}
}
