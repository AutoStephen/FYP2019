// 8-March-2019 - Programme runs motor at 10% depending on toggle switch.
// Developer: Stephen Murphy
// Now attempting to read the data from the controller.
// Serial monitor was scrolling down but showing nothing. 
// so something is coming in but the controller cannot make sense of it?
 

#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(10, 11); // RX, TX, Create a softwareSerial port on pins 10 and 11.

char inData[50]; // Allocate some space for the string
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

  while(mySerial1.available() > 0) // Don't read unless you know there is data 
  {
      if(index < 49) // One less than the size of the array
      {
        inChar = mySerial1.read(); // Read a character
        inData[index] = inChar; // Store it
        index++; // Increment where to write next
        inData[index] = '\0'; // Null terminate the string
      }
  }
  Serial.println(inData);
}
