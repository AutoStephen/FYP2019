// 24-Jan-2019 - Programme reads potentiometer signal and converts to string to be sent to Plettenberg.
// Developer: Stephen Murphy
// Status: Working. Does not consider steering or two motors. 
//ramp upto 50. hold at 50.


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

/*
while (ThrottlePercent < 100.00) //While throttle is less than 100%
  { 
  ThrottlePercent+= 1.00; //Increase the throttle by 1
  delay(200); //from 0 ro 100% in 2 seconds. i.e. increase by 1% every 20ms
  }
*/

if (ThrottlePercent == 0 && ToggleSwitchValue == 1)
{
  for(ThrottlePercent = 0 ; ThrottlePercent < 50; ThrottlePercent +=1) //Ramp input from 0 to 50% in 2 seconds
  {
    FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6
FourthDecimalVariableDuplicate = FourthDecimalVariable; // Store the same value in a second variable for seperate calculations simultaneously.

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

 LessThanTenDecimalCharacters = ""; //Clear the string
  while (FourthDecimalVariableDuplicate < 10) //While the units value is >= 1
  { 
  FourthDecimalVariableDuplicate+= 1; //increase the units value by 1
  LessThanTenDecimalCharacters+="l"; //Increase the DecimalCharacters string by "l" (small letter L)
  }

if (ThrottlePercent == 100.00) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent == 0.00) 
  ThrottleString = ("0"); //0% = 0
  else if (ThrottlePercent < 10.00 && ThrottlePercent > 0.00) 
  ThrottleString = (1 + LessThanTenCharacters  + "f"); //e.g. 3.42% = "1-------llllllf"
  else{
  ThrottleString = (TensCharacter + OnesCharacters + DecimalCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

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
    delay(20);
  }
}

if (ThrottlePercent != 0 && ToggleSwitchValue == 0) //if motor is running and switch is off
{
  for(ThrottlePercent = 50 ; ThrottlePercent > 0; ThrottlePercent -=1) //Ramp input from 0 to 50% in 2 seconds
  {
    FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6
FourthDecimalVariableDuplicate = FourthDecimalVariable; // Store the same value in a second variable for seperate calculations simultaneously.

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

 LessThanTenDecimalCharacters = ""; //Clear the string
  while (FourthDecimalVariableDuplicate < 10) //While the units value is >= 1
  { 
  FourthDecimalVariableDuplicate+= 1; //increase the units value by 1
  LessThanTenDecimalCharacters+="l"; //Increase the DecimalCharacters string by "l" (small letter L)
  }

if (ThrottlePercent == 100.00) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent == 0.00) 
  ThrottleString = ("0"); //0% = 0
  else if (ThrottlePercent < 10.00 && ThrottlePercent > 0.00) 
  ThrottleString = (1 + LessThanTenCharacters  + "f"); //e.g. 3.42% = "1-------llllllf"
  else{
  ThrottleString = (TensCharacter + OnesCharacters + DecimalCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }


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
    delay(20);
  }
}
else 
{
FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6
FourthDecimalVariableDuplicate = FourthDecimalVariable; // Store the same value in a second variable for seperate calculations simultaneously.

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

 LessThanTenDecimalCharacters = ""; //Clear the string
  while (FourthDecimalVariableDuplicate < 10) //While the units value is >= 1
  { 
  FourthDecimalVariableDuplicate+= 1; //increase the units value by 1
  LessThanTenDecimalCharacters+="l"; //Increase the DecimalCharacters string by "+"
  }

if (ThrottlePercent == 100.00) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent == 0.00) 
  ThrottleString = ("0"); //0% = 0
  else if (ThrottlePercent < 10.00 && ThrottlePercent > 0.00)
  ThrottleString = (1 + LessThanTenCharacters + "f"); //e.g. 3.42% = "1-------llllllf"
  else{
  ThrottleString = (TensCharacter + OnesCharacters + DecimalCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }
}

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


//delay(100); // Delay for stability

}
