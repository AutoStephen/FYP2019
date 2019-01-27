// 24-Jan-2019 - Programme reads throttle and steering and sends to different signal to two motors.
// Developer: Stephen Murphy
// Status: Working. Far from perfect. signals greater than 100% being sent to motors.


#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.
SoftwareSerial mySerial2(4, 5); // RX, TX, Create a softwareSerial port on pins 4 and 5.

//Variables for left motor:
int LeftTensCharacter; // Number 1 to 10 at the start of the throttle string

//Variables used to calculate the "TensCharacter"
int LeftFirstTensVariable;
int LeftSecondTensVariable;
int LeftThirdTensVariable;
int LeftFourthTensVariable;
int LeftFifthTensVariable;

//Variables used to calculate the "DecimalCharacters"
float LeftDecimalValue;
float LeftFirstDecimalVariable;
int LeftSecondDecimalVariable;
float LeftThirdDecimalVariable;
int LeftFourthDecimalVariable;

String LeftOnesCharacters = ""; //String storing the "+" characters for the ones multiplier
String LeftDecimalCharacters = ""; //String storing the "g" characters for the decimal multiplier
String LeftThrottleString = ""; //String that stores the final concated string to be sent to the motor

//Variables for right motor:
int RightTensCharacter; // Number 1 to 10 at the start of the throttle string

//Variables used to calculate the "TensCharacter"
int RightFirstTensVariable;
int RightSecondTensVariable;
int RightThirdTensVariable;
int RightFourthTensVariable;
int RightFifthTensVariable;

//Variables used to calculate the "DecimalCharacters"
float RightDecimalValue;
float RightFirstDecimalVariable;
int RightSecondDecimalVariable;
float RightThirdDecimalVariable;
int RightFourthDecimalVariable;

String RightOnesCharacters = ""; //String storing the "+" characters for the ones multiplier
String RightDecimalCharacters = ""; //String storing the "g" characters for the decimal multiplier
String RightThrottleString = ""; //String that stores the final concated string to be sent to the motor

//Variables for both motors:
String FullThrottleString = "m"; //String to store "m" for full throttle, as per the controller manual

float ThrottleInput;  // Variable to store raw input from Potentiometer.
float ThrottlePercent;  //Variable to store throttle %.
float SteeringInput;  // Variable to store raw input from Potentiometer.
float SteeringPercent;  //Variable to store steering %.

 int SteeringVariable; //Variable stored purely for calculations.
 int LeftSignal; //Variable that is ultimately sent to the left motor.
 int RightSignal; //Variable that is ultimately sent to the right motor.
 
//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200); //Baud rate between computer and Arduino.
  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
  mySerial1.println("s"); //Initialise the controller to accept serial command strings.
  mySerial2.begin(115200); //Baud rate between Arduino and Controller.
  mySerial2.println("s"); //Initialise the controller to accept serial command strings.
}

//////////////////////////////////////////////////////////////////////////////////
void loop() 
{
//Convert the throttle input to a range 0-100.
ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Throttle value converted to %.

//Convert the steering input to a range 0-100.
SteeringInput = analogRead(A5); //Value from potentiometer placed into "SteeringInput".
SteeringPercent = ((SteeringInput / 1023.00) * 100.00); //Steering value converted to %.




// Steering Differential Calculation

  SteeringVariable = SteeringPercent;

  if (SteeringVariable <50) 
  { 
    //Car is turning left. Therefor the signal will be from 0 to 128. 
     LeftSignal = ThrottlePercent + (50 - SteeringVariable); // Left motor is increased by the difference from the mid point. 
     RightSignal = ThrottlePercent - (50 -SteeringVariable); // Right motor is decreased by the difference from the mid point.
    // This will produce a signal proportional to the amount turned.
  }
  if (SteeringVariable >50) 
  { 
   //Car is turning right. Therefor the signal will be from 128 to 255. 
    LeftSignal = ThrottlePercent - (SteeringVariable - 50); //Left motor is decreased by how far past the mid point the steering is.
    RightSignal = ThrottlePercent + (SteeringVariable - 50); //Right motor is increased by how far past the mid point the steering is.
   // This will produce a signal proportional to the amount turned.
  }



 
//LEFT MOTOR:
LeftFirstTensVariable = LeftSignal; //Store the 0-100 value read from the potentiometer e.g. 58.67%
LeftTensCharacter = (LeftFirstTensVariable/10); //Stroe the tens multiplier e.g. 5

LeftSecondTensVariable = (LeftTensCharacter*10); //Store the previous value times ten e.g. 50
LeftThirdTensVariable = (LeftFirstTensVariable - LeftSecondTensVariable); //store the remaining units e.g 58-50 = 8

//DecimalValue:
LeftFirstDecimalVariable = LeftSignal; //Store the 0-100 value read from the potentiometer e.g. 58.67%
LeftSecondDecimalVariable = LeftSignal; //Store the throttle value in an INT data type e.g. 58
LeftThirdDecimalVariable = (LeftSignal - LeftSecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
LeftFourthDecimalVariable = (LeftThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 LeftOnesCharacters = ""; //Clear the string
  while (LeftThirdTensVariable >= 1) { //While the units value is >= 1
  LeftThirdTensVariable-= 1; //Decrease the units value by 1
  LeftOnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

 LeftDecimalCharacters = ""; //Clear the string
  while (LeftFourthDecimalVariable >= 1) { //While the decimal units value is >= 1
  LeftFourthDecimalVariable-= 1; //Decrease the units value by 1
  LeftDecimalCharacters+="g"; //Increase the DecimalCharacters string by "+"
  }

if (LeftSignal == 100.00) 
  LeftThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (LeftSignal < 10.00) 
  LeftThrottleString = ("" + LeftOnesCharacters + LeftDecimalCharacters + "f"); //e.g. 3.42% = "+++ggggf"
  else{
  LeftThrottleString = (LeftTensCharacter + LeftOnesCharacters + LeftDecimalCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }






//RIGHT MOTOR
RightFirstTensVariable = RightSignal; //Store the 0-100 value read from the potentiometer e.g. 58.67%
RightTensCharacter = (RightFirstTensVariable/10); //Stroe the tens multiplier e.g. 5

RightSecondTensVariable = (RightTensCharacter*10); //Store the previous value times ten e.g. 50
RightThirdTensVariable = (RightFirstTensVariable - RightSecondTensVariable); //store the remaining units e.g 58-50 = 8

//DecimalValue:
RightFirstDecimalVariable = RightSignal; //Store the 0-100 value read from the potentiometer e.g. 58.67%
RightSecondDecimalVariable = RightSignal; //Store the throttle value in an INT data type e.g. 58
RightThirdDecimalVariable = (RightSignal - RightSecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
RightFourthDecimalVariable = (RightThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 RightOnesCharacters = ""; //Clear the string
  while (RightThirdTensVariable >= 1) { //While the units value is >= 1
  RightThirdTensVariable-= 1; //Decrease the units value by 1
  RightOnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

 RightDecimalCharacters = ""; //Clear the string
  while (RightFourthDecimalVariable >= 1) { //While the decimal units value is >= 1
  RightFourthDecimalVariable-= 1; //Decrease the units value by 1
  RightDecimalCharacters+="g"; //Increase the DecimalCharacters string by "+"
  }

if (RightSignal == 100.00) 
  RightThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (RightSignal < 10.00) 
  RightThrottleString = ("" + RightOnesCharacters + RightDecimalCharacters + "f"); //e.g. 3.42% = "+++ggggf"
  else{
  RightThrottleString = (RightTensCharacter + RightOnesCharacters + RightDecimalCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }


//Print the following values to the left motor:
mySerial1.println(LeftThrottleString); //Turn the motor off when the shield is looking at these software serial pins.
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

//Print the following values to the right motor:
mySerial2.println(RightThrottleString); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up.



  

//Print the following values to the serial monitor for diagnostics:
Serial.print("Left Throttle Percent = ");
Serial.print(LeftSignal);
Serial.print("%   ");
Serial.print("Left Throttle String = ");
Serial.print(LeftThrottleString);
Serial.print("    ");
Serial.print("Right Throttle Percent = ");
Serial.print(RightSignal);
Serial.print("%   ");
Serial.print("Right Throttle String = ");
Serial.println(RightThrottleString);

delay(100); // Delay for stability

}
