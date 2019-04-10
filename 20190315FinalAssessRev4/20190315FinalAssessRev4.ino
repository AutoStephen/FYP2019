


#include <Arduino.h> //Include additional Arduino Libraries.

#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.
SoftwareSerial mySerial2(4, 5); // RX, TX, Create a softwareSerial port on pins 4 and 5.


////////////////////////////////////////////

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
float LeftThirdTensVariableDuplicate;
int LeftFourthDecimalVariable;

String LeftOnesCharacters = ""; //String storing the "+" characters for the ones multiplier
String LeftDecimalCharacters = ""; //String storing the "g" characters for the decimal multiplier
String LeftLessThanTenCharacters = ""; //String storing the "-" characters for the ones multiplier when <10%
String LeftFullThrottleString = "m"; //String to store "m" for full throttle, as per the controller manual
String LeftThrottleString = ""; //String that stores the final concated string to be sent to the motor
float LeftThrottlePercent;  //Variable to store throttle %.
////////////////////////////////////////////////////////////////////////////////

float ThrottleInput;  // Variable to store raw input from Potentiometer.
float ThrottlePercent;  //Variable to store throttle %.

/////////////////////////////////////////////////////////////////////////////////

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
float RightThirdTensVariableDuplicate;
int RightFourthDecimalVariable;

String RightOnesCharacters = ""; //String storing the "+" characters for the ones multiplier
String RightDecimalCharacters = ""; //String storing the "g" characters for the decimal multiplier
String RightLessThanTenCharacters = ""; //String storing the "-" characters for the ones multiplier when <10%
String RightFullThrottleString = "m"; //String to store "m" for full throttle, as per the controller manual
String RightThrottleString = ""; //String that stores the final concated string to be sent to the motor
float RightThrottlePercent;  //Variable to store throttle %.

/////////////////////////////////////////////////////////////////////////////////

float SteeringInput;
float SteeringPercent;
float RightMotorPercent;
float LeftMotorPercent;
float ExcessPercent;
float TurningPercent;
float RightTurningPercent;
float LeftTurningPercent;
float WheelSteeringAngle;
float RightWheelSteeringAngle;
float LeftWheelSteeringAngle;
float AverageWheelSteeringAngle;
float WheelTurningRadius;
float LeftWheelTurningRadius;
float RightWheelTurningRadius;
float AverageWheelTurningRadius;
float WheelBase = 1.54; //Distance from rear to front wheels is 1.54 metres.
float TrackWidth = 1.15; //Distance from left to right wheels is 1 metre.
float RadiusDifferencePercent;
float NegativePercent;
float OverHundredVariable;
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////

void setup(){

  Serial.begin(115200);
  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
  mySerial1.println("s"); //Initialise the controller to accept serial command strings.
  mySerial2.begin(115200); //Baud rate between Arduino and Controller.
  mySerial2.println("s"); //Initialise the controller to accept serial command strings.
}

/////////////////////////////////////////////////////////////////////////////////

void loop(){

//EXTRACT USER INPUT:

ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Analog Input value converted to %.

SteeringInput = analogRead(A3); //Value from potentiometer placed into "ThrottleInput".
SteeringPercent = ((SteeringInput / 1023.00) * 100.00); //Analog Input value converted to %.



/////////////////////////////////////////////////////////////////////////////////

//DEVELOP DIFFERENTIAL BASED ON STEERING:

TurningPercent = (SteeringPercent - 50) * 2; //Convert the 50-100 and 0 -50 range to 0-100% of turning either direction

 if (ThrottlePercent == 0)
{
  RightMotorPercent = 0;
  LeftMotorPercent = 0;
}

else if (SteeringPercent > 50) //If turning right
{ 
  RightWheelSteeringAngle = ((TurningPercent / 100) * 28); //Steering angle of right wheel is between 0-28 degrees
  LeftWheelSteeringAngle = ((TurningPercent / 100) * 23); //Steering angle of left wheel is between 0-28 degrees
  AverageWheelSteeringAngle = ((LeftWheelSteeringAngle + RightWheelSteeringAngle) / 2);
  AverageWheelTurningRadius = (WheelBase / (tan(AverageWheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Beta)) and convert rads to degrees.
  LeftWheelTurningRadius = (AverageWheelTurningRadius + (TrackWidth/2)) ; //Outer radius = average radius + half the width of the car.
  RightWheelTurningRadius = (AverageWheelTurningRadius - (TrackWidth/2)) ; //Inner radius = average radius - half the width of the car.
  RadiusDifferencePercent = (((LeftWheelTurningRadius - RightWheelTurningRadius) / LeftWheelTurningRadius) * 100); //Outer - inner / outer
  ExcessPercent = (ThrottlePercent + (RadiusDifferencePercent / 2) - 100);
  NegativePercent = ((ThrottlePercent - (RadiusDifferencePercent / 2)) * (-1));
  OverHundredVariable = (ThrottlePercent + ExcessPercent);
    
    if (OverHundredVariable > 100)//If the % to one of the motors is larger than 100%
      {
        LeftMotorPercent = 100.00; //Make the outer motor 100%
        RightMotorPercent = (ThrottlePercent - ExcessPercent - (RadiusDifferencePercent / 2)); //Subtract the excess differential % from the inner wheel
      }
      else if ((ThrottlePercent - (RadiusDifferencePercent / 2)) < 0)
      {
        RightMotorPercent = 0;
        LeftMotorPercent = (ThrottlePercent + NegativePercent + (RadiusDifferencePercent / 2));
      }
      else
  {
  LeftMotorPercent = (ThrottlePercent + (RadiusDifferencePercent / 2)); //Outer speed = throttle + differential
  RightMotorPercent = (ThrottlePercent - (RadiusDifferencePercent / 2)); //Inner speed = throttle - differential
  }
}
  else if (SteeringPercent < 50) //If turning left
  {
    RightWheelSteeringAngle = (((TurningPercent / 100) * 23)*(-1));
    LeftWheelSteeringAngle = (((TurningPercent / 100) * 28)*(-1));
    AverageWheelSteeringAngle = ((LeftWheelSteeringAngle + RightWheelSteeringAngle) / 2);
    AverageWheelTurningRadius = (WheelBase / (tan(AverageWheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Beta)) and convert rads to degrees.
    LeftWheelTurningRadius = (AverageWheelTurningRadius - (TrackWidth/2)) ; //Inner radius = average radius + half the width of the car.
    RightWheelTurningRadius = (AverageWheelTurningRadius + (TrackWidth/2)) ; //Outer radius = average radius - half the width of the car.
    RadiusDifferencePercent = (((RightWheelTurningRadius - LeftWheelTurningRadius) / RightWheelTurningRadius) * 100); //Outer - inner / outer
    ExcessPercent = (ThrottlePercent + (RadiusDifferencePercent / 2) - 100);
    NegativePercent = ((ThrottlePercent - (RadiusDifferencePercent / 2)) * (-1));
    OverHundredVariable = (ThrottlePercent + ExcessPercent);
      
      if (OverHundredVariable > 100) //If the % to one of the motors is larger than 100%
      {
        RightMotorPercent = 100.00; //Make the outer motor 100%
        LeftMotorPercent = ((ThrottlePercent - ExcessPercent) - (RadiusDifferencePercent / 2)); //Subtract the excess differential % from the inner wheel
      }
      else if ((ThrottlePercent - (RadiusDifferencePercent / 2)) < 0)
      {
        LeftMotorPercent = 0;
        RightMotorPercent = (ThrottlePercent + NegativePercent + (RadiusDifferencePercent / 2));
      }
      else 
    {
    LeftMotorPercent = (ThrottlePercent - (RadiusDifferencePercent / 2)); //Inner speed = throttle - differential
    RightMotorPercent = (ThrottlePercent + (RadiusDifferencePercent / 2)); //Outer speed = throttle + differential
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONVERT LEFT THROTTLE VALUE INTO STRING


LeftFirstTensVariable = LeftMotorPercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
LeftTensCharacter = (LeftFirstTensVariable/10); //Stroe the tens multiplier e.g. 5

LeftSecondTensVariable = (LeftTensCharacter*10); //Store the previous value times ten e.g. 50
LeftThirdTensVariable = (LeftFirstTensVariable - LeftSecondTensVariable); //store the remaining units e.g 58-50 = 8

LeftThirdTensVariableDuplicate = LeftThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
LeftFirstDecimalVariable = LeftMotorPercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
LeftSecondDecimalVariable = LeftMotorPercent; //Store the throttle value in an INT data type e.g. 58
LeftThirdDecimalVariable = (LeftMotorPercent - LeftSecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
LeftFourthDecimalVariable = (LeftThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 LeftOnesCharacters = ""; //Clear the string
  while (LeftThirdTensVariable >= 1) //While the units value is >= 1
  { 
  LeftThirdTensVariable-= 1; //Decrease the units value by 1
  LeftOnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

 LeftDecimalCharacters = ""; //Clear the string
  while (LeftFourthDecimalVariable >= 1) //While the decimal units value is >= 1
  { 
  LeftFourthDecimalVariable-= 1; //Decrease the units value by 1
  LeftDecimalCharacters+="g"; //Increase the DecimalCharacters string by "+"
  }

 LeftLessThanTenCharacters = ""; //Clear the string
  while (LeftThirdTensVariableDuplicate < 10) //While the units value is >= 1
  { 
  LeftThirdTensVariableDuplicate+= 1; //increase the units value by 1
  LeftLessThanTenCharacters+="-"; //Increase the DecimalCharacters string by "+"
  }

if (LeftMotorPercent == 100.00) 
  LeftThrottleString = (LeftFullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (LeftMotorPercent < 10.00 && 0 < LeftMotorPercent) 
  LeftThrottleString = (1 + LeftLessThanTenCharacters + "f"); //e.g. 3.42% = "1-------ggggf"
  else if (LeftMotorPercent == 0.00) 
  LeftThrottleString = "0"; //Turn motor off
  else{
  LeftThrottleString = (LeftTensCharacter + LeftOnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

//Print the following values to the motor:
mySerial1.println(LeftThrottleString); //Turn the motor off when the shield is looking at these software serial pins.
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

//Print the following values to the motor (Required to switch serial port cable by hand):
//mySerial2.println(0); //Turn the motor off when the shield is looking at these software serial pins.
//mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up.


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONVERT RIGHT THROTTLE VALUE INTO STRING


RightFirstTensVariable = RightMotorPercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
RightTensCharacter = (RightFirstTensVariable/10); //Stroe the tens multiplier e.g. 5

RightSecondTensVariable = (RightTensCharacter*10); //Store the previous value times ten e.g. 50
RightThirdTensVariable = (RightFirstTensVariable - RightSecondTensVariable); //store the remaining units e.g 58-50 = 8

RightThirdTensVariableDuplicate = RightThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
RightFirstDecimalVariable = RightMotorPercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
RightSecondDecimalVariable = RightMotorPercent; //Store the throttle value in an INT data type e.g. 58
RightThirdDecimalVariable = (RightMotorPercent - RightSecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
RightFourthDecimalVariable = (RightThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 RightOnesCharacters = ""; //Clear the string
  while (RightThirdTensVariable >= 1) //While the units value is >= 1
  { 
  RightThirdTensVariable-= 1; //Decrease the units value by 1
  RightOnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

 RightDecimalCharacters = ""; //Clear the string
  while (RightFourthDecimalVariable >= 1) //While the decimal units value is >= 1
  { 
  RightFourthDecimalVariable-= 1; //Decrease the units value by 1
  RightDecimalCharacters+="g"; //Increase the DecimalCharacters string by "+"
  }

 RightLessThanTenCharacters = ""; //Clear the string
  while (RightThirdTensVariableDuplicate < 10) //While the units value is >= 1
  { 
  RightThirdTensVariableDuplicate+= 1; //increase the units value by 1
  RightLessThanTenCharacters+="-"; //Increase the DecimalCharacters string by "+"
  }

if (RightMotorPercent == 100.00) 
  RightThrottleString = (RightFullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (RightMotorPercent < 10.00 && 0 < RightMotorPercent) 
  RightThrottleString = (1 + RightLessThanTenCharacters + "f"); //e.g. 3.42% = "1-------ggggf"
  else if (RightMotorPercent == 0.00) 
  RightThrottleString = "0"; //Turn motor off
  else{
  RightThrottleString = (RightTensCharacter + RightOnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

//Print the following values to the motor:
//mySerial1.println(LeftThrottleString); //Turn the motor off when the shield is looking at these software serial pins.
//mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

//Print the following values to the motor
mySerial2.println(RightThrottleString); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up.


 

Serial.print(" Throttle = ");
Serial.print(ThrottlePercent);
Serial.print(" % "); 
Serial.print(" Right Motor = ");
Serial.print(RightThrottleString);
Serial.print(" % "); 
Serial.print(" Left Motor = ");
Serial.print(LeftThrottleString);
Serial.print(" % "); 
Serial.print(" Left Wheel Steering Angle = ");
Serial.print(LeftWheelSteeringAngle);
Serial.print(" Right Wheel Steering Angle = ");
Serial.print(RightWheelSteeringAngle);
Serial.print(" Turning = ");
Serial.print(TurningPercent);
Serial.print(" % ");
Serial.print(" Left Wheel Turning Radius = ");
Serial.print(LeftWheelTurningRadius);
Serial.print(" Right Wheel Turning Radius = ");
Serial.print(RightWheelTurningRadius);
Serial.print(" Difference = ");
Serial.print(RadiusDifferencePercent);
Serial.println(" % ");

  delay(100);
}

/////////////////////////////////////////////////////////////////////////////////

