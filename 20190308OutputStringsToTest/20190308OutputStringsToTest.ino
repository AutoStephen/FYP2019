#include <Arduino.h>  //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.

int Value = 3;
////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
mySerial.begin(115200); //Baud rate between Arduino and Controller.
mySerial.println("s");  //Initialise the controller to accept serial command strings.


}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

mySerial.println("2");  //Turn the motor off when the shield is looking at software serial pins.

}
