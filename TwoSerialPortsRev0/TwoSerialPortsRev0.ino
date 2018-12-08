// *** BASIC PROGRAMME TO TEST TWO SOFTWARE SERIAL PORTS ***
// LAST UPDATED: 7-DECEMBER-2018
// DEVELOPER: STEPHEN MURPHY

#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.
SoftwareSerial mySerial2(4, 5); // RX, TX, Create a softwareSerial port on pins 4 and 5.

////////////////////////////////////////////////////////////////////////////////////////
void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
mySerial1.begin(115200); //Baud rate between Arduino and Controller.
mySerial1.println("s"); //Initialise the controller to accept serial command strings.
mySerial2.begin(115200); //Baud rate between Arduino and Controller.
mySerial2.println("s"); //Initialise the controller to accept serial command strings.

}
////////////////////////////////////////////////////////////////////////////////////////
void loop() {

mySerial1.println("0"); //Turn the motor off when the shield is looking at these software serial pins.
delay(500); //Delay for stability.

mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.
delay(500); //Delay for stability.

mySerial2.println("4f"); //Turn the motor off when the shield is looking at these software serial pins.
delay(500); //Delay for stability.

mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up.
delay(500); //Delay for stability.
}
