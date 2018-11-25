#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);  //creat Rx and Tx pins on pin 2 and 3


void setup() {

Serial.begin(9600); //baud rate for arduino to PC
mySerial.begin(115200); //baud rate for arduino to controller
mySerial.println("h");  //Tell controller to go to serial input mode

}

void loop() {

// mySerial.println("2f");  //tell controller to go forward at 20%

//Serial.println(mySerial.read());  //Print in the serial monitor, what is in the shield buffer.

if (mySerial.available() > 0) //if there are any bits in the serial buffer
{
  String Feedback = mySerial.readString(); // place what is in the buffer in "Feedback"
  Serial.println(Feedback); //Print what we get from controller
  // -1 no longer showing up. therefore, we are receiving something.
  // cannot see it because of data types??

 delay(1000); //delay for stability
}
}
