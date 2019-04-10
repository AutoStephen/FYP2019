#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.

float ThrottleInput;  // Variable to store raw input from Potentiometer.
float ThrottlePercent;  //Variable to store throttle %.
String ThrottleString; //Variable to store the string to control motor speed. 
////////////////////////////////////////////////////////////////////////////////////////
void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
mySerial.begin(115200); //Baud rate between Arduino and Controller.
mySerial.println("s"); //Initialise the controller to accept serial command strings.
Serial.println("s"); //Show in monitor for diagnostics.

}
////////////////////////////////////////////////////////////////////////////////////////
void loop() {

ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Throttle value converted to %.

//These two lines are only sent to the controller when the switch on the shield
//is set to hardware serial. ***MAKE PRINTLN???***
Serial.println("s"); //Ensure controller is in Serial Mode
mySerial.println("s");

if (ThrottlePercent < 5.00) {
  //Serial.println("s");
  Serial.println("0"); //Turn the motor off when switched to software pins.
  mySerial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 20.00 && ThrottlePercent <= 50.00) {
  //Serial.println("s");
  Serial.println("1f"); //Turn the motor at 20% when switched to software pins.
  mySerial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 60.00 && ThrottlePercent <= 100.00) {
  //Serial.println("s");
  Serial.println("3f"); //Turn the motor at 40% when switched to software pins.
  mySerial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}


//Print values to the serial monitor for diagnostics.
//Serial.println(" Throttle Input = ");
//Serial.println(ThrottleInput);
//Serial.println(" Throttle Percentage = ");
//Serial.println(ThrottlePercent);
//Serial.println(" % ");
//delay(50);  //Delay for stability.

}
