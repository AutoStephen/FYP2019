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
  ToggleSwitchValue = digitalRead(ToggleSwitch);
  
  if (ToggleSwitchValue == 1)
 { 
  mySerial1.println("1fs"); //Run motor at 10%
  //mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.
 }
  if (ToggleSwitchValue == 0)
 { 
  mySerial1.println("0"); //Turn motor off
  mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.
 }

//Below is two different attempts to read strings
if (mySerial1.available()) //If the controller is sending something
  {
    char myChar = mySerial1.read();
    Serial.print(myChar);
  }
  mySerial1.println("h");
  delay(1000);
}
