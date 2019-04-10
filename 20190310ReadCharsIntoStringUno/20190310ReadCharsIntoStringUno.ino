#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200); //Serial communication speed

  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
}

//////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  if (mySerial1.available())
  {
    char myChar = mySerial1.read();
    Serial.print(myChar);
  }
  mySerial1.println("12345678912345789123456789");
  
  Serial.println("Uno Value = ");
}
