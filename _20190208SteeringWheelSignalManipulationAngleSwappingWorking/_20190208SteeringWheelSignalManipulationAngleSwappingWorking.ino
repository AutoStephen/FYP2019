//stores % steering wheel has turned left or right.
//stores what the steering angle is based on that value.
//Turning radii are not different by the correct % (16 to 14 to 16%)

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

void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
}

void loop() {

ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Analog Input value converted to %.

SteeringInput = analogRead(A5); //Value from potentiometer placed into "ThrottleInput".
SteeringPercent = ((SteeringInput / 1023.00) * 100.00); //Analog Input value converted to %.

TurningPercent = (SteeringPercent - 50) * 2; //Convert the 50-100 and 0 -50 range to 0-100% of turning either direction



if (SteeringPercent > 50) //If turning right
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
delay(50);  //Delay for stability.

}
