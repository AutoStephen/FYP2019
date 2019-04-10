// 8-March-2019 - Programme runs motor at 10% depending on toggle switch.
// Developer: Stephen Murphy
// Now attempting to read the data from the controller.


#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.
SoftwareSerial mySerial2(4, 5); // RX, TX, Create a softwareSerial port on pins 4 and 5.

String IncomingData;

int ToggleSwitch = 13;
int ToggleSwitchValue =0;

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
 Serial.setTimeout(10);
  
  pinMode(ToggleSwitch, INPUT);
  Serial.begin(115200); //Serial communication speed

    mySerial1.begin(115200); //Baud rate between Arduino and Controller.
    mySerial1.println("s"); //Initialise the controller to accept serial command strings.

    mySerial1.setTimeout(100); //Used with Serial.readString()

    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}


//////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  /*
  ToggleSwitchValue = digitalRead(ToggleSwitch);
if (ToggleSwitchValue == 1)
 { 
mySerial1.println("1----f"); //Run motor at 5%
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

IncomingData = mySerial1.readString();
 }
if (ToggleSwitchValue == 0)
{ 
mySerial1.println("0"); //Turn motor off
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.


}
*/

// if (mySerial1.available()>0)
// IncomingData = mySerial1.read(); //Store value from controller (hopefully)

   if (mySerial1.available())
   {
    Serial.write(mySerial1.read());
   }
//Print the following values to the serial monitor:
//Serial.print("Incoming Data = ");
//Serial.println(IncomingData);

}
