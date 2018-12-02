// ***** THIS PROGRAM WILL RUN THE MOTOR AT DIFFERENT SPEEDS AUTOMATICALLY, USING DELAYS. *****
// TESTED 28-NOVEMBER-2018 - WORKING AS PLANNED.

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
mySerial.println("s"); //Ensure the controller sees "s" so as to receive serial input. (SoftSerial)
Serial.println("s"); //Ensure the controller sees "s" so as to receive serial input. (HardSerial)
delay(50); //Delay between sending of signals for clarity in serial monitor.

mySerial.println("0"); //Turn the motor off when switched to SoftSerial.
Serial.println("2f"); //Turn the motor at 20% when switched to HardSerial.
delay(10000);  //Remain at 20% for 10 seconds


mySerial.println("0"); //Turn the motor off when switched to SoftSerial.
Serial.println("4f"); //Turn the motor at 40% when switched to HardSerial.
delay(10000);  //Remain at 40% for 10 seconds

mySerial.println("0"); //Turn the motor off when switched to SoftSerial.
Serial.println("6f"); //Turn the motor at 60% when switched to HardSerial.
delay(10000);  //Remain at 60% for 10 seconds

mySerial.println("0"); //Turn the motor off when switched to SoftSerial.
Serial.println("8f"); //Turn the motor at 80% when switched to HardSerial.
delay(10000);  //Remain at 80% for 10 seconds

mySerial.println("0"); //Turn the motor off when switched to SoftSerial.
Serial.println("m"); //Turn the motor at 100% when switched to HardSerial.
delay(5000);  //Remain at 1000% for 5 seconds

}
