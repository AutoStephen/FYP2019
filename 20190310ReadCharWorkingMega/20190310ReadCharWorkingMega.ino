#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(10, 11); // RX, TX, Create a softwareSerial port on pins 10 and 11.

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
  mySerial1.println("qwertyuasdfghjkzxcvbnmqwertyuiasdfghjcvbn");
  Serial.println("Mega Value = ");
}
