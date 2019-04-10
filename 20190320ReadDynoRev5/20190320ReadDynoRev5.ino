// 8-March-2019 - Programme runs motor at 10% depending on toggle switch.
// Developer: Stephen Murphy
// Now attempting to read the data from the controller.
//Unsuccessful.


#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(10, 11); // RX, TX, Create a softwareSerial port on pins 10 and 11.

String IncomingData;

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

//Below is two different attempts to read strings
if (mySerial1.available()) //If the controller is sending something
  {
    char myChar = mySerial1.read();
    Serial.println(myChar);
  }
}
