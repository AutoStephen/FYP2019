/*  
  Optical Sensor Two Motor Demonstration
  DualMotorSpeedDemo.ino
  Demonstrates use of Hardware Interrupts
  to measure speed from two motors
  
  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Edited for just 1 motor

// Include the TimerOne Library from Paul Stoffregen
#include "TimerOne.h"

// Constants for Interrupt Pins
// Change values if not using Arduino Uno

const byte MOTOR1 = 2;  // Motor 1 Interrupt Pin - INT 0


// Integers for pulse counters
unsigned int counter1 = 0;


// Float for number of slots in encoder disk
float diskslots = 96;  

// Interrupt Service Routines

// Motor 1 pulse count ISR
void ISR_count1()  
{
  counter1++;  // increment Motor 1 counter value
} 

 

// TimerOne ISR
void ISR_timerone()
{
  Timer1.detachInterrupt();  // Stop the timer
  Serial.print("Motor Speed 1: "); 
  float rotation1 = (counter1 / diskslots) * 60.00;  // calculate RPM for Motor 1
  Serial.print(rotation1);  
  Serial.println(" RPM - "); 
  counter1 = 0;  //  reset counter to zero
  
  Timer1.attachInterrupt( ISR_timerone );  // Enable the timer
}

void setup() 
{
  Serial.begin(9600);
  
  Timer1.initialize(100000); // set timer for 1sec
  attachInterrupt(digitalPinToInterrupt (MOTOR1), ISR_count1, RISING);  // Increase counter 1 when speed sensor pin goes High

  Timer1.attachInterrupt( ISR_timerone ); // Enable the timer
} 

void loop()
{
  // Nothing in the loop!
}
