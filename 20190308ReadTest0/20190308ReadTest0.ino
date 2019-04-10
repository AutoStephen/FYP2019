#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(10, 11); // RX, TX, Create a softwareSerial port on pins 2 and 3.

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200); //Serial communication speed

  Serial.setTimeout(10);

  mySerial1.begin(115200); //Baud rate between Arduino and Controller.

  mySerial1.setTimeout(10); //Used with Serial.readString(
}


//////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  if (mySerial1.available())
  {
    String myChar = mySerial1.readString();
    Serial.print(myChar);
  }
  mySerial1.println("s");
Serial.println("Mega Value = ");
}
