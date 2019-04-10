
// LAST EDITED 27 DECEMBER 2018
// DEVELOPER: STEPHEN MURPHY


// include the TM1638 library.
#include <TM1638.h>


// Define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638 module(8, 9, 7);

// Define constants for left and right so we can easily choose 
// which side of the display to show our number
#define LEFT 0
#define RIGHT 1

// array of the numbers from 0 to 9. 
byte displayDigits[] = {63,6,91,79,102,109,124,7,127,103 };

// An array for the values to be displayed - all zeroes means show nothing.
byte values[] = { 0,0,0,0,0,0,0,0 };

// The digits which will make up a number to be displayed
int theDigits[] = { 0,0,0,0 };

/////////////////////////////////////////////////////////////////////////////////
float SteeringInput;
float SteeringPercent;
float ThrottleInput;
float ThrottlePercent;
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
 // Start with the digital display blank.
 module.setDisplay(values);

 // Set the display intensity. (1 to 7)
 module.setupDisplay(true, 7); 
}

/////////////////////////////////////////////////////////////////////////////////

void loop(){


ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Analog Input value converted to %.

SteeringInput = analogRead(A5); //Value from potentiometer placed into "ThrottleInput".
SteeringPercent = ((SteeringInput / 1023.00) * 100.00); //Analog Input value converted to %.

TurningPercent = (SteeringPercent - 50) * 2; //Convert the 50-100 and 0 -50 range to 0-100% of turning either direction


/////////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////////////

  
 // This is an example number from 0 to 99.9999 to display
 float theNumberToDisplay = LeftMotorPercent;

 // Display Number on left or right
  int positionToDisplayIt = LEFT;

 // How many decimal places to show - must be 1 or 2 in this example code
 int numberOfDecimalPlacesToShow = 2;

 // Call the function to display the number. This is where the programme jumps to the subroutine for the first display. 
 // This is "creating" the sub routine
 displayNumber(theNumberToDisplay, positionToDisplayIt, numberOfDecimalPlacesToShow);
 

// FOR THE SECOND DISPLAY:
 // This is an example number from 0 to 99.9999 to display
 float theNumberToDisplay2 = RightMotorPercent;

 // Display Number on left or right
  int positionToDisplayIt2 = RIGHT;

 // How many decimal places to show - must be 1 or 2 in this example code
 int numberOfDecimalPlacesToShow2 = 2;

 // Call the function to display the number
 displayNumber2(theNumberToDisplay2, positionToDisplayIt2, numberOfDecimalPlacesToShow2);


Serial.print(" Throttle = ");
Serial.print(ThrottlePercent);
Serial.print(" % "); 
Serial.print(" Right Motor = ");
Serial.print(RightMotorPercent);
Serial.print(" % "); 
Serial.print(" Left Motor = ");
Serial.print(LeftMotorPercent);
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

void displayNumber(float numberToSplit, int whichSide, int numOfDPs){
 // These three variables get their data from the previous three variables.
 // The number to be split should be a float from 0 to 99.9999
 // If is below zero or equal to or over 100, then just display ----.
 // numOfDPs is the number of digits after the point, only 1 or 2 are acceptable values
 if(numOfDPs > 2 or numOfDPs < 1)numOfDPs = 1;

 // Extract the digits from this number.
 numberToSplit = (int)(100 * numberToSplit);
 // If the value is 100 then the array will be larger than four digits
 // so just override any errors and display 100
 if(numberToSplit > 9999) numberToSplit = 100; 
 else
 // Multiply by 100 so the number is four digits long. 
 theDigits[0] = (int)(numberToSplit/1000);
 // Divide by 1000 so the this is only the first digit
 theDigits[1] = (int)((numberToSplit - (1000*theDigits[0])) / 100);
 // Second digit is the entire number minus the first digit in thousands 
 // and then divided by 100
 theDigits[2] = (int)((numberToSplit - (1000*theDigits[0]) - (100*theDigits[1]))/10);
 // third digit is the entire number minus the first digit in thousands, 
 // minus the second digit in hundreds and then divided by 10
 theDigits[3] = (int)(numberToSplit - (1000*theDigits[0]) - (100*theDigits[1]) - (10*theDigits[2]));
 // forth digit is the entire number minus the first digit in thousands, 
 // minus the second digit in hundreds, minus the third digit in tens
 
 // Find and store the byte variables required to show these digits
 int dispDig[4]; // Declaring an array with 4 elements
 if(theDigits[0] == 0) dispDig[0] = 0; // Hide a leading zero if there is one
 else dispDig[0] = displayDigits[theDigits[0]];
 dispDig[1] = displayDigits[theDigits[1]] + 128; // Apend the dp onto the second digit
 dispDig[2] = displayDigits[theDigits[2]];
 dispDig[3] = displayDigits[theDigits[3]]; //WHAT IS DISPLAY DIGITS DOING????????

 // If we are only showing one DP, then leave last character blank to make things more legible on the display
 if(numOfDPs == 1) dispDig[3] = 0;

 // Make sure that the number passed to the function was >= 0 or =<100, 
 // otherwise show an error with ----.
 if(numberToSplit/100 < 0 or numberToSplit/100 > 100){
   for(int i = 0; i < 4; i++) 
   dispDig[i] = 64;
 }
 
 if(numberToSplit == 100){
   dispDig[0] = 6;
   dispDig[1] = 63;
   dispDig[2] = 63;
   dispDig[3] = 0;
 }
 
 
 // Find if number to be shown on the left or the right side of the display
 int offset = 0; // LEFT by default
 if(whichSide == RIGHT) offset = 4;
 // WHERE DOES THIS COME FROM?????????????????

 // Update the values in the values array used by the display.
 values[0+offset] = dispDig[0];
 values[1+offset] = dispDig[1];
 values[2+offset] = dispDig[2];
 values[3+offset] = dispDig[3];

 // Update the display itself with the new values.
 module.setDisplay(values);
  delay(100);
}

/////////////////////////////////////////////////////////////////////////////////

void displayNumber2(float numberToSplit2, int whichSide2, int numOfDPs2){
 // These three variables get their data from the previous three variables.
 // The number to be split should be a float from 0 to 99.9999
 // If is below zero or equal to or over 100, then just display ----.
 // numOfDPs is the number of digits after the point, only 1 or 2 are acceptable values
 if(numOfDPs2 > 2 or numOfDPs2 < 1)numOfDPs2 = 1;

 // Extract the digits from this number.
 numberToSplit2 = (int)(100 * numberToSplit2);
 // If the value is 100 then the array will be larger than four digits
 // so just override any errors and display 100
 if(numberToSplit2 > 9999) numberToSplit2 = 100; 
 else
 // Multiply by 100 so the number is four digits long. 
 theDigits[0] = (int)(numberToSplit2/1000);
 // Divide by 1000 so the this is only the first digit
 theDigits[1] = (int)((numberToSplit2 - (1000*theDigits[0])) / 100);
 // Second digit is the entire number minus the first digit in thousands 
 // and then divided by 100
 theDigits[2] = (int)((numberToSplit2 - (1000*theDigits[0]) - (100*theDigits[1]))/10);
 // third digit is the entire number minus the first digit in thousands, 
 // minus the second digit in hundreds and then divided by 10
 theDigits[3] = (int)(numberToSplit2 - (1000*theDigits[0]) - (100*theDigits[1]) - (10*theDigits[2]));
 // forth digit is the entire number minus the first digit in thousands, 
 // minus the second digit in hundreds, minus the third digit in tens
 
 // Find and store the byte variables required to show these digits
 int dispDig[4]; // Declaring an array with 4 elements
 if(theDigits[0] == 0) dispDig[0] = 0; // Hide a leading zero if there is one
 else dispDig[0] = displayDigits[theDigits[0]];
 dispDig[1] = displayDigits[theDigits[1]] + 128; // Apend the dp onto the second digit
 dispDig[2] = displayDigits[theDigits[2]];
 dispDig[3] = displayDigits[theDigits[3]]; //WHAT IS DISPLAY DIGITS DOING????????

 // If we are only showing one DP, then leave last character blank to make things more legible on the display
 if(numOfDPs2 == 1) dispDig[3] = 0;

 // Make sure that the number passed to the function was >= 0 or =<100, 
 // otherwise show an error with ----.
 if(numberToSplit2/100 < 0 or numberToSplit2/100 >= 100){
   for(int i = 0; i < 4; i++) 
   dispDig[i] = 64;
 }
 
 if(numberToSplit2 == 100){
   dispDig[0] = 6;
   dispDig[1] = 63;
   dispDig[2] = 63;
   dispDig[3] = 0;
 }
 
 
 // Find if number to be shown on the left or the right side of the display
 int offset = 0; // LEFT by default
 if(whichSide2 == RIGHT) offset = 4;
 // WHERE DOES THIS COME FROM?????????????????

 // Update the values in the values array used by the display.
 values[0+offset] = dispDig[0];
 values[1+offset] = dispDig[1];
 values[2+offset] = dispDig[2];
 values[3+offset] = dispDig[3];

 // Update the display itself with the new values.
 module.setDisplay(values);
 delay(100);
}
