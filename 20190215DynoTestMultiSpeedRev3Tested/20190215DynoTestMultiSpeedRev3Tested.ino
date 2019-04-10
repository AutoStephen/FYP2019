// 24-Jan-2019 - Programme reads potentiometer signal and converts to string to be sent to Plettenberg.
// Developer: Stephen Murphy
// Status: Working. Does not consider steering or two motors. 

#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.
SoftwareSerial mySerial2(4, 5); // RX, TX, Create a softwareSerial port on pins 4 and 5.

int TensCharacter; // Number 1 to 10 at the start of the throttle string

//Variables used to calculate the "TensCharacter"
int FirstTensVariable;
int SecondTensVariable;
int ThirdTensVariable;
int FourthTensVariable;
int FifthTensVariable;

//Variables used to calculate the "DecimalCharacters"
float DecimalValue;
float FirstDecimalVariable;
int SecondDecimalVariable;
float ThirdDecimalVariable;
float ThirdTensVariableDuplicate;
int FourthDecimalVariable;
int FourthDecimalVariableDuplicate;

String OnesCharacters = ""; //String storing the "+" characters for the ones multiplier
String DecimalCharacters = ""; //String storing the "g" characters for the decimal multiplier
String LessThanTenCharacters = ""; //String storing the "-" characters for the ones multiplier when <10%
String LessThanTenDecimalCharacters = ""; //String storing the "l" (as in L for lion) characters for the decimal multiplier when <10%
String FullThrottleString = "m"; //String to store "m" for full throttle, as per the controller manual
String ThrottleString = ""; //String that stores the final concated string to be sent to the motor

float ThrottleInput;  // Variable to store raw input from Potentiometer.
float ThrottlePercent = 0.00;  //Variable to store throttle %.

int ToggleSwitch = 13;
int ToggleSwitchValue =0;

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  pinMode(ToggleSwitch, INPUT);
  Serial.begin(115200); //Serial communication speed
  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
  mySerial1.println("s"); //Initialise the controller to accept serial command strings.
  mySerial2.begin(115200); //Baud rate between Arduino and Controller.
  mySerial2.println("s"); //Initialise the controller to accept serial command strings.
}

//////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  ToggleSwitchValue = digitalRead(ToggleSwitch);
  
//Convert the throttle input to a range 0-100.
//ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
//ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Throttle value converted to %.

if (ToggleSwitchValue == 0)
{
ThrottleString = "0";  
}

else if (millis() < 10000 && ToggleSwitchValue == 1) //Start motor after 10 seconds if switch is on.
{
ThrottleString = "0";
}

else if (millis() > 10000 && millis() < 20000 && ToggleSwitchValue == 1) //jump to 5% after another 10 seconds
{
ThrottleString = "1-----f";
}

else if (millis() > 20000 && millis() < 30000 && ToggleSwitchValue == 1) 
{
ThrottleString = "1f";
}

else if (millis() > 30000 && millis() < 40000 && ToggleSwitchValue == 1) 
{
ThrottleString = "1+++++f";
}

else if (millis() > 40000 && millis() < 50000 && ToggleSwitchValue == 1) 
{
ThrottleString = "2f";
}

else if (millis() > 50000 && millis() < 60000 && ToggleSwitchValue == 1) 
{
ThrottleString = "2+++++f";
}

else if (millis() > 60000 && millis() < 70000 && ToggleSwitchValue == 1) 
{
ThrottleString = "3f";
}

else if (millis() > 70000 && millis() < 80000 && ToggleSwitchValue == 1) 
{
ThrottleString = "3+++++f";
}

else if (millis() > 80000 && millis() < 90000 && ToggleSwitchValue == 1) 
{
ThrottleString = "4f";
}

else if (millis() > 90000 && millis() < 100000 && ToggleSwitchValue == 1) 
{
ThrottleString = "4+++++f";
}

else if (millis() > 100000 && millis() < 110000 && ToggleSwitchValue == 1) 
{
ThrottleString = "5f";
}

else if (millis() > 110000 && millis() < 120000 && ToggleSwitchValue == 1) 
{
ThrottleString = "4f";
}

else if (millis() > 120000 && millis() < 130000 && ToggleSwitchValue == 1) 
{
ThrottleString = "3f";
}

else if (millis() > 130000 && millis() < 140000 && ToggleSwitchValue == 1) 
{
ThrottleString = "2f";
}

else if (millis() > 140000 && millis() < 150000 && ToggleSwitchValue == 1) 
{
ThrottleString = "1f";
}

else if (millis() > 150000 || ToggleSwitchValue == 1) 
{
ThrottleString = "0";
}

/*
else if (millis() > 110000) 
{
ThrottleString = "4f";
delay(1000);
ThrottleString = "3f";
delay(1000);
ThrottleString = "2f";
delay(1000);
ThrottleString = "1f";
delay(1000);
ThrottleString = "0";
delay(1000);
}
*/

mySerial1.println(ThrottleString); //Send throttle value to motor
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

mySerial2.println("0"); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up.

//Print the following values:
Serial.print("Throttle Percent = ");
Serial.print(ThrottlePercent);
Serial.print("%   ");
Serial.print("Throttle String = ");
Serial.println(ThrottleString);


}
