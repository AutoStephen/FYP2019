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

String OnesCharacters = ""; //String storing the "+" characters for the ones multiplier
String DecimalCharacters = ""; //String storing the "g" characters for the decimal multiplier
String LessThanTenCharacters = ""; //String storing the "-" characters for the ones multiplier when <10%
String FullThrottleString = "m"; //String to store "m" for full throttle, as per the controller manual
String ThrottleString = ""; //String that stores the final concated string to be sent to the motor

float ThrottleInput;  // Variable to store raw input from Potentiometer.
float ThrottlePercent;  //Variable to store throttle %.

float BrakeInput;  // Variable to store raw input from Potentiometer.
float BrakePercent;  //Variable to store throttle %.

float MotorPercent;  //Variable to store throttle %.

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200); //Serial communication speed
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

//Convert the brake input to a range 0-100.
BrakeInput = analogRead(A5); //Value from potentiometer placed into "ThrottleInput".
BrakePercent = ((BrakeInput / 1023.00) * 100.00); //Throttle value converted to %.
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Signal to motor is made equal to the ThrottlePercent - The amount of braking.
MotorPercent = (ThrottlePercent - (ThrottlePercent * (BrakePercent / 100)));

////////////////////////////////////////////////////////////////////////////////////////////////////////////
FirstTensVariable = MotorPercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = MotorPercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = MotorPercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (MotorPercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 OnesCharacters = ""; //Clear the string
  while (ThirdTensVariable >= 1) //While the units value is >= 1
  { 
  ThirdTensVariable-= 1; //Decrease the units value by 1
  OnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

 DecimalCharacters = ""; //Clear the string
  while (FourthDecimalVariable >= 1) //While the decimal units value is >= 1
  { 
  FourthDecimalVariable-= 1; //Decrease the units value by 1
  DecimalCharacters+="g"; //Increase the DecimalCharacters string by "+"
  }

 LessThanTenCharacters = ""; //Clear the string
  while (ThirdTensVariableDuplicate < 10) //While the units value is >= 1
  { 
  ThirdTensVariableDuplicate+= 1; //increase the units value by 1
  LessThanTenCharacters+="-"; //Increase the DecimalCharacters string by "+"
  }

if (MotorPercent == 100.00) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (MotorPercent < 10.00 && 0 < MotorPercent) 
  ThrottleString = (1 + LessThanTenCharacters + "f"); //e.g. 3.42% = "1-------ggggf"
  else if (MotorPercent == 0.00) 
  ThrottleString = "0"; //Turn motor off
  else{
  ThrottleString = (TensCharacter + OnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

//Print the following values to the motor:
mySerial1.println(ThrottleString); //Turn the motor off when the shield is looking at these software serial pins.
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

//Print the following values to the motor (Required to switch serial port cable by hand):
mySerial2.println(0); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up.

//Print the following values:
Serial.print("Motor Percent = ");
Serial.print(MotorPercent);
Serial.print("%   ");
Serial.print("Throttle String = ");
Serial.println(ThrottleString);


delay(100); // Delay for stability

}
