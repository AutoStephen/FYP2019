// 8-March-2019 - Programme runs motor at 10% depending on toggle switch.
// Developer: Stephen Murphy
// Now attempting to read the data from the controller.


#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial portOne(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.

String IncomingData;

int ToggleSwitch = 13;
int ToggleSwitchValue =0;

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
 //Serial.setTimeout(10);
  
  pinMode(ToggleSwitch, INPUT);
  Serial.begin(115200); //Serial communication speed

    portOne.begin(115200); //Baud rate between Arduino and Controller.
    portOne.println("s"); //Initialise the controller to accept serial command strings.

    //portOne.setTimeout(100); //Used with Serial.readString()
}


//////////////////////////////////////////////////////////////////////////////////
void loop() 
{  
 
  ToggleSwitchValue = digitalRead(ToggleSwitch);
if (ToggleSwitchValue == 1)
 { 
portOne.println("1----f"); //Run motor at 5%
portOne.println("s"); //Send "s" so that the controller does not miss it upon start up.

portOne.listen();
  Serial.println("Data from port one:");
  
  while (portOne.available() > 0)
  {
    char inByte = portOne.read();
    Serial.write(inByte);

  Serial.println(); // blank line to separate data from the two ports:

//IncomingData = mySerial1.readString();
 }
 }
if (ToggleSwitchValue == 0)
{ 
portOne.println("0"); //Turn motor off
portOne.println("s"); //Send "s" so that the controller does not miss it upon start up.



//IncomingData = portOne.readString(); //Store value from controller (hopefully)
}

/*
//Below is two different attempts to read strings
if (portOne.available()) //If the controller is sending something, print it.
{
    Serial.println(portOne.read());
}
//Print the following values to the serial monitor:
Serial.print("Incoming Data = ");
Serial.println(IncomingData);
*/
 }
