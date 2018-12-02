// *** BASIC PROGRAMME TO READ INPUT FROM 2 THROTTLE POTS, 1 STEERING POT AND 1 BRAKE POT ***
// LAST UPDATED: 30-NOVEMBER-2018
// DEVELOPER: STEPHEN MURPHY

#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.

float ThrottleInput1; //Variable to store raw input from throttle potentiometer 1.
float ThrottleInput2; //Variable to store raw input from throttle potentiometer 2.
float SteeringInput; //Variable to store raw input from steering potentiometer.
float BrakeInput; //Variable to store raw input from brake potentiometer.
float ThrottlePercent1; //Variable to store % value of throttle potentiometer 1.
float ThrottlePercent2; //Variable to store % value of throttle potentiometer 2.
float SteeringPercent; //Variable to store % value of steering potentiometer.
float BrakePercent; //Variable to store % value of brake potentiometer.

////////////////////////////////////////////////////////////////////////////////////////////
void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
mySerial.begin(115200); //Baud rate between Arduino and Controller.
mySerial.println("s"); //Initialise the controller to accept serial command strings.
Serial.println("s"); //Show in monitor for diagnostics.

}

///////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  
// Read inputs from potentiometers and convert to 0 - 100 range. 
//First throttle potentiometer:
ThrottleInput1 = analogRead(A0);  //Read the data from the analog input pin and store in "ThrottleInput1" variable.
ThrottlePercent1 = ((ThrottleInput1 / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 

//Second throttle potentiometer:
ThrottleInput2 = analogRead(A1);  //Read the data from the analog input pin and store in "ThrottleInput2" variable.
ThrottlePercent2 = ((ThrottleInput2 / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 

//Steering potentiometer:
SteeringInput = analogRead(A2);  //Read the data from the analog input pin and store in "SteeringInput" variable.
SteeringPercent = ((SteeringInput / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 

//Brake potentiometer:
BrakeInput = analogRead(A3);  //Read the data from the analog input pin and store in "BrakeInput" variable.
BrakePercent = ((BrakeInput / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 


// ******************** Print values to the serial monitor for diagnostics. *************************
/*
Serial.print(" Throttle 1 = ");
Serial.print(ThrottleInput1);
Serial.print(" Throttle Percentage 1 = ");
Serial.print(ThrottlePercent1);
Serial.print(" % ");
*/
//Serial.print(" Throttle 2 = ");
//Serial.print(ThrottleInput2);
//Serial.print(" Throttle Percentage 2 = ");
//Serial.print(ThrottlePercent2);
//Serial.println(" % ");
/*
Serial.print(" Steering = ");
Serial.print(SteeringInput);
Serial.print(" Steering Percentage = ");
Serial.print(SteeringPercent);
Serial.print(" % ");

Serial.print(" Brake = ");
Serial.print(BrakeInput);
Serial.print(" Brake Percentage = ");
Serial.print(BrakePercent);
Serial.println(" % ");
*/
delay(300);  //Delay for stability.

}
