#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.


SoftwareSerial mySerial(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.
////////////////////////////////////////////////////////////////////////////////////////
void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
mySerial.begin(115200); //Baud rate between Arduino and Controller.
mySerial.println("s"); //Initialise the controller to accept serial command strings.
Serial.println("s"); //Show in monitor for diagnostics.

}
////////////////////////////////////////////////////////////////////////////////////////
void loop() {

mySerial.println("0"); //Turn the motor off when the shield is looking at software serial pins.
Serial.println("2f");  //Turn the motor at 20% when switched to hardware pins.
delay(500); //Delay for stability.

mySerial.println("s"); //Send "s" so that the controller does not miss it upon start up.
Serial.println("s"); //Print "s" on serial Monitor for diagnostics.
delay(500); //Delay for stability.

}
