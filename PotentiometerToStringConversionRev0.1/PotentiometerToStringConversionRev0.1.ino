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
Serial.print("0"); //Turn the motor off when the shield is looking at hardware serial pins.
Serial.print("s"); //Ensure controller is in Serial Mode


if (ThrottlePercent < 5.00) {
  mySerial.print("0"); //Turn the motor off when switched to hardware pins.
  mySerial.print("s"); //Ensure controller is in Serial Mode
}
if (ThrottlePercent > 0.00 && ThrottlePercent <= 30.00) {
  mySerial.print("1f"); //Turn the motor at 10% when switched to hardware pins.
  mySerial.print("s"); //Ensure controller is in Serial Mode
}
if (ThrottlePercent > 30.00 && ThrottlePercent <= 60.00) {
  mySerial.print("4f"); //Turn the motor at 20% when switched to hardware pins.
  mySerial.print("s"); //Ensure controller is in Serial Mode
}
if (ThrottlePercent > 60.00 && ThrottlePercent <= 90.00) {
  mySerial.print("7f"); //Turn the motor at 30% when switched to hardware pins.
  mySerial.print("s"); //Ensure controller is in Serial Mode
}
if (ThrottlePercent > 90.00 && ThrottlePercent <= 100.00) {
  mySerial.print("mf"); //Turn the motor at 1000% when switched to hardware pins.
  mySerial.print("s"); //Ensure controller is in Serial Mode
}

//Print values to the serial monitor for diagnostics.
Serial.print(" Throttle Input = ");
Serial.print(ThrottleInput);
Serial.print(" Throttle Percentage = ");
Serial.print(ThrottlePercent);
Serial.println(" % ");
delay(50);  //Delay for stability.

}
