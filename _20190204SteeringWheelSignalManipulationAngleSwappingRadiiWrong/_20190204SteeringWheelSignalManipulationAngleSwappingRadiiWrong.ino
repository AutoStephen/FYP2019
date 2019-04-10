//stores % steering wheel has turned left or right.
//stores what the steering angle is based on that value.
//Turning radii are not different by the correct %

float AnalogInput;
float AnalogPercent;
float TurningPercent;
float RightTurningPercent;
float LeftTurningPercent;
float WheelSteeringAngle;
float RightWheelSteeringAngle;
float LeftWheelSteeringAngle; 
float WheelTurningRadius;
float LeftWheelTurningRadius;
float RightWheelTurningRadius;
float WheelBase = 1.54; //Distance from rear to front wheels is 1.54 metres.


void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
}

void loop() {

AnalogInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
AnalogPercent = ((AnalogInput / 1023.00) * 100.00); //Analog Input value converted to %.

TurningPercent = (AnalogPercent - 50) * 2; //Convert the 50-100 and 0 -50 range to 0-100% of turning either direction


if (AnalogPercent > 50) //If turning right
{
  WheelTurningRadius = 
 // WheelSteeringAngle = ((TurningPercent / 100) * 28); //Steering angle of right wheel is between 0-28 degrees
 // LeftWheelSteeringAngle = ((TurningPercent / 100) * 24); //Steering angle of left wheel is between 0-28 degrees
 // LeftWheelTurningRadius = (WheelBase / (tan(LeftWheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Alpha)) and convert rads to degrees.
 // RightWheelTurningRadius = (WheelBase / (tan(RightWheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Beta)) and convert rads to degrees.
}
  else if (AnalogPercent < 50) //If turning left
  {
   // RightWheelSteeringAngle = (((TurningPercent / 100) * 24)*(-1));
   // LeftWheelSteeringAngle = (((TurningPercent / 100) * 28)*(-1));
   // LeftWheelTurningRadius = (WheelBase / (tan(LeftWheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Beta)) and convert rads to degrees.
   // RightWheelTurningRadius = (WheelBase / (tan(RightWheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Alpha)) and convert rads to degrees.
  }


    
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
Serial.println(RightWheelTurningRadius);
delay(50);  //Delay for stability.

}
