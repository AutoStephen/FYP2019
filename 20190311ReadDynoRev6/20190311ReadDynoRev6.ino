#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(10, 11); // RX, TX, Create a softwareSerial port on pins 10 and 11.

char inData[1000]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

int ToggleSwitch = 13;
int ToggleSwitchValue =0;

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  pinMode(ToggleSwitch, INPUT);
  
  Serial.begin(115200); //Serial communication speed

  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
  mySerial1.println("s"); //Initialise the controller to accept serial command strings.
}

//////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  ToggleSwitchValue = digitalRead(ToggleSwitch);
  
  if (ToggleSwitchValue == 1)
 { 
  mySerial1.println("1f"); //Run motor at 10%
  mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.
 }
  if (ToggleSwitchValue == 0)
 { 
  mySerial1.println("0"); //Turn motor off
  mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.
 }


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
}
