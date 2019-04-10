//stores % steering wheel has turned left or right.
//stores what the steering angle is based on that value.

float AnalogInput;
float AnalogPercent;
float TurningPercent;
float RightTurningPercent;
float LeftTurningPercent;
float RightWheelSteeringAngle; //Alpha
float LeftWheelSteeringAngle; //Beta
float LeftWheelTurningRadius;
float RightWheelTurningRadius;
float WheelBase = 1.54; //Distance from rear to front wheels is 1.54 metres.
float WheelSteeringAngle;

void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
}

void loop() {

AnalogInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
AnalogPercent = ((AnalogInput / 1023.00) * 100.00); //Analog Input value converted to %.

TurningPercent = (AnalogPercent - 50) * 2; //Convert the 50-100 and 0 -50 range to 0-100% of turning either direction


if (AnalogPercent > 50) //If turning right
{
  RightWheelSteeringAngle = ((TurningPercent / 100) * 28); //Steering angle of right wheel is between 0-28 degrees
  LeftWheelSteeringAngle = ((TurningPercent / 100) * 24); //Steering angle of left wheel is between 0-28 degrees
}
  else if (AnalogPercent < 50) //If turning left
  {
    RightWheelSteeringAngle = (((TurningPercent / 100) * 24)*(-1));
    LeftWheelSteeringAngle = (((TurningPercent / 100) * 28)*(-1));
  }

//InnerTurningRadius = (WheelBase / (tan(WheelSteeringAngle*(3.14159/180)))); //Turn radius = (w/tan(Alpha)) and convert rads to degrees.
//Convert radians into degrees.

//Serial.print(" Inner Turning Radius = ");
//Serial.print(InnerTurningRadius);    
Serial.print(" Left Wheel Steering Angle = ");
Serial.print(LeftWheelSteeringAngle);
Serial.print(" Right Wheel Steering Angle = ");
Serial.print(RightWheelSteeringAngle);
Serial.print(" Turning = ");
Serial.print(TurningPercent);
Serial.print(" % ");
//Serial.print(" Turning Left = ");
//Serial.print(LeftTurningPercent);
//Serial.print(" % ");
Serial.print(" Analog Input = ");
Serial.print(AnalogPercent);
Serial.println(" % ");
delay(50);  //Delay for stability.

}
