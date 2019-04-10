#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(10, 11); // RX, TX, Create a softwareSerial port on pins 10 and 11.

int ToggleSwitch = 13;
int ToggleSwitchValue =0;

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  pinMode(ToggleSwitch, INPUT);
  
  Serial.begin(115200); //Serial communication speed

  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
  mySerial1.println("s"); //Initialise the controller to accept serial command strings.
}

//////////////////////////////////////////////////////////////////////////////////
void loop() 
{
 // mySerial1.println("s"); //Initialise the controller to accept serial command strings.
  /*
  if (Serial.available())
  {
    mySerial1.print(Serial.read());
    Serial.print(".");
  }
  */
  if (mySerial1.available())
  {
    Serial.println(mySerial1.read());
    //Serial.print("!");
  }
}
