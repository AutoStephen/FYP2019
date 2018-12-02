//*** 28-11-2018 - PROGRAMME WORKING - MOTOR SPEED DEPENDS ON POTENTIOMETER INPUT. ***
// UPDATED TO WORK ON SOFT SERIAL PINS SO I CAN STILL USE SERIAL MONITOR FOR DIAGNOSTICS
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

//Convert the throttle input to a range 0-100.
ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Throttle value converted to %.

//These two lines are only sent to the controller when the switch on the shield
//is set to hardware serial. ***MAKE PRINTLN???***
Serial.println("s"); //Ensure controller is in Serial Mode
mySerial.println("s");

if (ThrottlePercent < 2.00) {
  //Serial.println("s");
  mySerial.println("0"); //Turn the motor off when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 5.00 && ThrottlePercent <= 10.00) {
  //Serial.println("s");
  mySerial.println("1f"); //Turn the motor at 10% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 12.00 && ThrottlePercent <= 20.00) {
  //Serial.println("s");
  mySerial.println("2f"); //Turn the motor at 20% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 22.00 && ThrottlePercent <= 30.00) {
  //Serial.println("s");
  mySerial.println("3f"); //Turn the motor at 30% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 32.00 && ThrottlePercent <= 40.00) {
  //Serial.println("s");
  mySerial.println("4f"); //Turn the motor at 40% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 42.00 && ThrottlePercent <= 50.00) {
  //Serial.println("s");
  mySerial.println("5f"); //Turn the motor at 50% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 52.00 && ThrottlePercent <= 60.00) {
  //Serial.println("s");
  mySerial.println("6f"); //Turn the motor at 60% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 62.00 && ThrottlePercent <= 70.00) {
  //Serial.println("s");
  mySerial.println("7f"); //Turn the motor at 70% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 72.00 && ThrottlePercent <= 80.00) {
  //Serial.println("s");
  mySerial.println("8f"); //Turn the motor at 80% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 82.00 && ThrottlePercent <= 90.00) {
  //Serial.println("s");
  mySerial.println("9f"); //Turn the motor at 90% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
if (ThrottlePercent > 92.00 && ThrottlePercent <= 100.00) {
  //Serial.println("s");
  mySerial.println("mf"); //Turn the motor at 100% when switched to software pins.
  Serial.println("0"); //Turn the motor off when the shield is looking at hardware pins.
}
//Print values to the serial monitor for diagnostics.
Serial.println(" Throttle Input = ");
Serial.println(ThrottleInput);
Serial.println(" Throttle Percentage = ");
Serial.println(ThrottlePercent);
Serial.println(" % ");
delay(50);  //Delay for stability.

}
