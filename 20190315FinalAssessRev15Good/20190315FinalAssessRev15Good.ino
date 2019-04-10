// 15-March-2019 - Programme for final presentation.
// Developer: Stephen Murphy
// Status: Working.
// The programme does the following:
// Coverts the % signal to strings for two motors.
// Creates an electronic differential based on the steering.
// Incorporates the brake pedal. 
// Displays the % signal to each motor on the digital display.
// The speed differential is a function of the brake pedal

  #include <Arduino.h> //Include additional Arduino Libraries.
  #include <SoftwareSerial.h> //Include software serial library for shield.
  #include <TM1638.h> //Include the TM1638 library.
  
  SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 10 and 11.
  SoftwareSerial mySerial2(4, 5); // RX, TX, Create a softwareSerial port on pins 12 and 13.

  TM1638 module(8, 9, 7); // Define a module on data pin 8, clock pin 9 and strobe pin 7

  

////////////////////////////////////////////////////////////////////////////////
  //Digital Display Declarations:
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
  
////////////////////////////////////////////////////////////////////////////////
  //Variables for left motor calculation:
  
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
  
/////////////////////////////////////////////////////////////////////////////////
  //Variables for right motor calculation:
  
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
  float ThrottleInput;
  float ThrottlePercent;
  float ThrottleInput2;
  float ThrottlePercent2;
  float RightMotorPercent;
  float LeftMotorPercent;
  float BrakeInput;  // Variable to store raw input from Potentiometer.
  float BrakePercent;  //Variable to store throttle %.
  float OutputPercent;  //Variable to store % signal to be sent after braking is considered.
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
  float RadiusDifferencePercent;
  float ExcessRadiusDifferencePercent;
  
  float WheelBase = 1.54; //Distance from rear to front wheels is 1.54 metres.
  
  float TrackWidth = 1.15; //Distance from left to right wheels is 1 metre.
  
  float NegativePercent;
  float ExcessNegativePercent;
  float OverHundredVariable;

  int ToggleSwitch = 13;
  int ToggleSwitchValue =0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200); //Baud rate between computer and Arduino.
  
  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
  mySerial1.println("s"); //Initialise the controller to accept serial command strings.
  
  mySerial2.begin(115200); //Baud rate between Arduino and Controller.
  mySerial2.println("s"); //Initialise the controller to accept serial command strings.

  
  module.setDisplay(values); // Start with the digital display blank.
  module.setupDisplay(true, 7); // Set the display intensity. (1 to 7)

  pinMode(ToggleSwitch, INPUT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  ExcessRadiusDifferencePercent = (RadiusDifferencePercent - (RadiusDifferencePercent * (BrakePercent / 100)));
  ExcessNegativePercent = (NegativePercent - (NegativePercent * (BrakePercent / 100)));
  ToggleSwitchValue = digitalRead(ToggleSwitch); //Store the 1 or 0 from the toggle switch

////////////////////////////////////////////////////////////////////////////////////////////
  //READ USER INPUTS
  //Take inputs and convert to the 0 - 100% range:
  ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
  ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Analog Input value converted to %.

  //This is storing the value for the second potentiometer as required in the rulebook.
  //This is not being used currently. 
  ThrottleInput2 = analogRead(A1); //Value from potentiometer placed into "ThrottleInput2".
  ThrottlePercent2 = ((ThrottleInput2 / 1023.00) * 100.00); //Analog Input value converted to %.

  //Convert the brake input to a range 0-100.
  BrakeInput = analogRead(A2); //Value from potentiometer placed into "BrakeInput".
  BrakePercent = ((BrakeInput / 1023.00) * 100.00); //Throttle value converted to %.

  //Signal to motor is made equal to the ThrottlePercent - The amount of braking.
  //Braking will override throttle.
  OutputPercent = (ThrottlePercent - (ThrottlePercent * (BrakePercent / 100)));
  
  SteeringInput = analogRead(A3); //Value from potentiometer placed into "SteeringInput".
  SteeringPercent = ((SteeringInput / 1023.00) * 100.00); //Analog Input value converted to %.
  
  //Convert the 50-100 and 0 -50 range to 0-100% of turning either direction
  TurningPercent = (SteeringPercent - 50) * 2;

////////////////////////////////////////////////////////////////////////////////////////////
//ELECTRONIC DIFFERENTIAL ALGORITHM:
 if (OutputPercent == 0 || BrakePercent == 100) //If the throttle signal is 0%, both motors should be off. 
{
  RightMotorPercent = 0;
  LeftMotorPercent = 0;
}

//IF TURNING RIGHT
else if (SteeringPercent > 50) 
{ 
  RightWheelSteeringAngle = ((TurningPercent / 100) * 28); //Steering angle of right wheel is between 0-28 degrees
  LeftWheelSteeringAngle = ((TurningPercent / 100) * 23); //Steering angle of left wheel is between 0-23 degrees
  AverageWheelSteeringAngle = ((LeftWheelSteeringAngle + RightWheelSteeringAngle) / 2);
  AverageWheelTurningRadius = (WheelBase / (tan(AverageWheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Beta)) and convert rads to degrees.
  LeftWheelTurningRadius = (AverageWheelTurningRadius + (TrackWidth/2)) ; //Outer radius = average radius + half the width of the car.
  RightWheelTurningRadius = (AverageWheelTurningRadius - (TrackWidth/2)) ; //Inner radius = average radius - half the width of the car.
  RadiusDifferencePercent = (((LeftWheelTurningRadius - RightWheelTurningRadius) / LeftWheelTurningRadius) * 100); //Outer - inner / outer
  ExcessPercent = (OutputPercent + (RadiusDifferencePercent / 2) - 100); //Store the amount that goes past 100%
  NegativePercent = ((OutputPercent - (RadiusDifferencePercent / 2)) * (-1)); //Store the amount that goes below 0%
  OverHundredVariable = (OutputPercent + ExcessPercent); //Value past 100%. e.g. 112%

    if (BrakePercent > 98.00) 
      {
      LeftMotorPercent = 0; //Turn motor off
      RightMotorPercent = 0; //Turn motor off
      }
      else if (OverHundredVariable > 100)//If the % to one of the motors is larger than 100%
      {
        LeftMotorPercent = 100.00; //Make the outer motor 100%
        RightMotorPercent = (OutputPercent - ExcessPercent - (ExcessRadiusDifferencePercent / 2)); //Subtract the excess differential % from the inner wheel
      }
      else if ((OutputPercent - (ExcessRadiusDifferencePercent / 2)) < 0) //If signal to motor is less than 0%
      {
        RightMotorPercent = 0; //Inner motor set to 0%
        //LeftMotorPercent = (OutputPercent + (ExcessRadiusDifferencePercent / 2)); //Outer motor has the excess % added onto it.
        LeftMotorPercent = OutputPercent;
      }
      //**********************************
      //NOTE: ONCE THE INNER MOTOR SIGNAL IS > 0, THE PROGRAMME MOVES ON. THIS RESULTS IN A STEP OF 10% AT THIS POINT.
      //**********************************
      else if (OutputPercent < 30)
      {
        RightMotorPercent = 0; //Inner motor set to 0%
        LeftMotorPercent = (OutputPercent + (ExcessRadiusDifferencePercent / 2)); //Outer motor has the excess % added onto it.
      }
      else 
      {
      LeftMotorPercent = (OutputPercent + (ExcessRadiusDifferencePercent / 2)); //Outer speed = throttle + differential
      RightMotorPercent = (OutputPercent - (ExcessRadiusDifferencePercent / 2)); //Inner speed = throttle - differential
      }
}
  //IF TURNING LEFT (repeat calculations but swap the motors).
  else if (SteeringPercent < 50)
  {
    RightWheelSteeringAngle = (((TurningPercent / 100) * 23)*(-1)); //Steering angle of right wheel is between 0-23 degrees
    LeftWheelSteeringAngle = (((TurningPercent / 100) * 28)*(-1)); //Steering angle of left wheel is between 0-28 degrees
    AverageWheelSteeringAngle = ((LeftWheelSteeringAngle + RightWheelSteeringAngle) / 2); //Average of the two
    AverageWheelTurningRadius = (WheelBase / (tan(AverageWheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Beta)) and convert rads to degrees.
    LeftWheelTurningRadius = (AverageWheelTurningRadius - (TrackWidth/2)) ; //Inner radius = average radius + half the width of the car.
    RightWheelTurningRadius = (AverageWheelTurningRadius + (TrackWidth/2)) ; //Outer radius = average radius - half the width of the car.
    RadiusDifferencePercent = (((RightWheelTurningRadius - LeftWheelTurningRadius) / RightWheelTurningRadius) * 100); //Outer - inner / outer
    ExcessPercent = (OutputPercent + (RadiusDifferencePercent / 2) - 100); //Store the amount that goes past 100%
    NegativePercent = ((OutputPercent - (RadiusDifferencePercent / 2)) * (-1)); //Store the amount that goes below 0%
    OverHundredVariable = (OutputPercent + ExcessPercent); //Value past 100%. e.g. 112%

      if (BrakePercent >= 98.00) 
      {
      LeftMotorPercent = 0; //Turn motor off
      RightMotorPercent = 0; //Turn motor off
      }
      else if (OverHundredVariable > 100) //If the % to one of the motors is larger than 100%
      {
        RightMotorPercent = 100.00; //Make the outer motor 100%
        LeftMotorPercent = ((OutputPercent - ExcessPercent) - (ExcessRadiusDifferencePercent / 2)); //Subtract the excess differential % from the inner wheel
      }
      else if ((OutputPercent - (ExcessRadiusDifferencePercent / 2)) < 0) //If signal to motor is less than 0%
      {
        LeftMotorPercent = 0; //Inner motor set to 0%
        //ExcessRadiusDifferencePercent = (RadiusDifferencePercent - (RadiusDifferencePercent * (BrakePercent / 100)));
        //RightMotorPercent = OutputPercent;
        RightMotorPercent = (OutputPercent + (ExcessRadiusDifferencePercent / 2)); //Outer motor has the excess % added onto it.
      }
      //**********************************
      //NOTE: ONCE THE INNER MOTOR SIGNAL IS > 0, THE PROGRAMME MOVES ON. THIS RESULTS IN A STEP OF 10% AT THIS POINT.
      //**********************************
      else 
      {
      LeftMotorPercent = (OutputPercent - (ExcessRadiusDifferencePercent / 2)); //Inner speed = throttle - differential
      RightMotorPercent = (OutputPercent + (ExcessRadiusDifferencePercent / 2)); //Outer speed = throttle + differential
      }
  }
  
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //CONVERT LEFT THROTTLE VALUE INTO STRINGS

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

if (BrakePercent == 100.00) 
  LeftThrottleString = "0"; //Turn motor off
  else if (LeftMotorPercent == 0.00 || BrakePercent == 100.00) 
  LeftThrottleString = "0"; //Turn motor off
  else if(LeftMotorPercent == 100.00) 
  LeftThrottleString = (LeftFullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (LeftMotorPercent < 10.00 && 0 < LeftMotorPercent) 
  LeftThrottleString = (1 + LeftLessThanTenCharacters + "f"); //e.g. 3.42% = "1-------ggggf"
  else{
  LeftThrottleString = (LeftTensCharacter + LeftOnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CONVERT RIGHT THROTTLE VALUE INTO STRINGS


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

if (BrakePercent == 100.00)
  RightThrottleString = "0"; //Turn motor off
  else if (RightMotorPercent == 0.00 || BrakePercent == 100.00) 
  RightThrottleString = "0"; //Turn motor off
  else if(RightMotorPercent == 100.00) 
  RightThrottleString = (RightFullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (RightMotorPercent < 10.00 && 0 < RightMotorPercent) 
  RightThrottleString = (1 + RightLessThanTenCharacters + "f"); //e.g. 3.42% = "1-------ggggf"
  else{
  RightThrottleString = (RightTensCharacter + RightOnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

  
  //Print the following values to the motor:
  mySerial1.println(LeftThrottleString); //Send the left signal % as strings over this port.
  mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.
  
  //Print the following values to the motor
  mySerial2.println(RightThrottleString); //Send the right signal % as strings over this port.
  mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up.


/////////////////////////////////////////////////////////////////////////////////
 //Declare and Initialise variables for the digital display
 // FOR THE FIRST DISPLAY:
 // Display the % sent to the left motor
 float theNumberToDisplay = LeftMotorPercent;

 // Display Number on left or right
  int positionToDisplayIt = LEFT;

 // How many decimal places to show - must be 1 or 2.
 int numberOfDecimalPlacesToShow = 2;

 // Call the function to display the number. This is where the programme jumps to the subroutine for the first display. 
 // This is "creating" the sub routine
 displayNumber(theNumberToDisplay, positionToDisplayIt, numberOfDecimalPlacesToShow);
 

 // FOR THE SECOND DISPLAY:
 // Display the % sent to the right motor
 float theNumberToDisplay2 = RightMotorPercent;

 // Display Number on left or right
  int positionToDisplayIt2 = RIGHT;

 // How many decimal places to show - must be 1 or 2.
 int numberOfDecimalPlacesToShow2 = 2;

 // Call the function to display the number
 displayNumber2(theNumberToDisplay2, positionToDisplayIt2, numberOfDecimalPlacesToShow2);

  //Print values to the serial monitor for diagnostic purposes:
  Serial.print(" Output Signal = ");
  Serial.print(OutputPercent);
  Serial.print(" % "); 
  Serial.print(" Right Motor = ");
  Serial.print(RightMotorPercent);
  Serial.print(" % "); 
  Serial.print(" Left Motor = ");
  Serial.print(LeftMotorPercent);
  Serial.print(" % "); 
  Serial.print(" Difference = ");
  Serial.print(RadiusDifferencePercent);
  Serial.print(" % ");
  Serial.print(" Excess Difference = ");
  Serial.print(ExcessRadiusDifferencePercent);
  Serial.println(" % ");
  delay(50);  //Delay for stability.

}
/////////////////////////////////////////////////////////////////////////////////

// DISPLAY NUMBERS ON LEFT OF DIGITAL DISPLAY

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
 dispDig[3] = displayDigits[theDigits[3]]; 

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
 

 // Update the values in the values array used by the display.
 values[0+offset] = dispDig[0];
 values[1+offset] = dispDig[1];
 values[2+offset] = dispDig[2];
 values[3+offset] = dispDig[3];

 // Update the display itself with the new values.
 module.setDisplay(values);
}

/////////////////////////////////////////////////////////////////////////////////

// DISPLAY NUMBERS ON RIGHT OF DIGITAL DISPLAY

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
 dispDig[3] = displayDigits[theDigits[3]]; 

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
 

 // Update the values in the values array used by the display.
 values[0+offset] = dispDig[0];
 values[1+offset] = dispDig[1];
 values[2+offset] = dispDig[2];
 values[3+offset] = dispDig[3];

 // Update the display itself with the new values.
 module.setDisplay(values);


}
