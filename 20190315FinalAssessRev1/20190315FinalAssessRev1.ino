// 15-March-2019 - Programme for final presentation.
// Developer: Stephen Murphy
// Status: Working.
// The programme does the following:
// Coverts the % signal to strings for two motors.
// Creates an electronic differential based on the steering.
// Incorporates the brake pedal. 
// Displays the % signal to each motor on the digital display.


  #include <Arduino.h> //Include additional Arduino Libraries.
  #include <SoftwareSerial.h> //Include software serial library for shield.
  
  SoftwareSerial mySerial1(10, 11); // RX, TX, Create a softwareSerial port on pins 10 and 11.
  SoftwareSerial mySerial2(12, 13); // RX, TX, Create a softwareSerial port on pins 12 and 13.


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
  float WheelBase = 1.54; //Distance from rear to front wheels is 1.54 metres.
  float TrackWidth = 1.15; //Distance from left to right wheels is 1 metre.
  float RadiusDifferencePercent;
  float NegativePercent;
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

  pinMode(ToggleSwitch, INPUT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  ToggleSwitchValue = digitalRead(ToggleSwitch); //Store the 1 or 0 from the toggle switch

////////////////////////////////////////////////////////////////////////////////////////////
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
//Electronic Differential Algorithm:
 if (OutputPercent == 0) //If the throttle signal is 0%, both motors should be off. 
{
  RightMotorPercent = 0;
  LeftMotorPercent = 0;
}

else if (SteeringPercent > 50) //If turning right
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
    
    if (OverHundredVariable > 100)//If the % to one of the motors is larger than 100%
      {
        LeftMotorPercent = 100.00; //Make the outer motor 100%
        RightMotorPercent = (OutputPercent - ExcessPercent - (RadiusDifferencePercent / 2)); //Subtract the excess differential % from the inner wheel
      }
      else if ((OutputPercent - (RadiusDifferencePercent / 2)) < 0) //If signal to motor is less than 0%
      {
        RightMotorPercent = 0; //Inner motor set to 0%
        LeftMotorPercent = (OutputPercent + NegativePercent + (RadiusDifferencePercent / 2)); //Outer motor has the excess % added onto it.
      }
      else
  {
  LeftMotorPercent = (OutputPercent + (RadiusDifferencePercent / 2)); //Outer speed = throttle + differential
  RightMotorPercent = (OutputPercent - (RadiusDifferencePercent / 2)); //Inner speed = throttle - differential
  }
}
  else if (SteeringPercent < 50) //If turning left (repeat calculations but swap the motors).
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
      
      if (OverHundredVariable > 100) //If the % to one of the motors is larger than 100%
      {
        RightMotorPercent = 100.00; //Make the outer motor 100%
        LeftMotorPercent = ((OutputPercent - ExcessPercent) - (RadiusDifferencePercent / 2)); //Subtract the excess differential % from the inner wheel
      }
      else if ((OutputPercent - (RadiusDifferencePercent / 2)) < 0) //If signal to motor is less than 0%
      {
        LeftMotorPercent = 0; //Inner motor set to 0%
        RightMotorPercent = (OutputPercent + NegativePercent + (RadiusDifferencePercent / 2)); //Outer motor has the excess % added onto it.
      }
      else 
    {
    LeftMotorPercent = (OutputPercent - (RadiusDifferencePercent / 2)); //Inner speed = throttle - differential
    RightMotorPercent = (OutputPercent + (RadiusDifferencePercent / 2)); //Outer speed = throttle + differential
    }
  }
  
////////////////////////////////////////////////////////////////////////////////////////////

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
  delay(50);  //Delay for stability.

}
