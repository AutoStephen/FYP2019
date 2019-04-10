#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(10, 11); // RX, TX, Create a softwareSerial port on pins 10 and 11.

char inData[1000]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200); //Serial communication speed

  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
}

//////////////////////////////////////////////////////////////////////////////////
void loop() 
{

  while(mySerial1.available() > 0) // Don't read unless you know there is data 
  {
      if(index < 999) // One less than the size of the array
      {
        inChar = mySerial1.read(); // Read a character
        inData[index] = inChar; // Store it
        index++; // Increment where to write next
        inData[index] = '\0'; // Null terminate the string
      }
  }

  Serial.println(inData);
delay(100);
  /*
  while (mySerial1.available())
  {
    char myChar = mySerial1.read();
    Serial.print(myChar);
  }
  mySerial1.println("s");
  Serial.println("Mega Value = ");
  */
}
