//stores % steering wheel has turned left or right.
//stores what the steering angle is based on that value.

float AnalogInput;
float AnalogPercent;
float TurningRightPercent;
float TurningLeftPercent;
float RightWheelSteeringAngle; //Alpha
float LeftWheelSteeringAngle; //Beta
float InnerTurningRadius;
float OuterTurningRadius;
float WheelBase = 1.54; //Distance from rear to front wheels is 1.54 metres.


void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
}

void loop() {

AnalogInput = analogRead(A1); //Value from potentiometer placed into "ThrottleInput".
AnalogPercent = ((AnalogInput / 1023.00) * 100.00); //Analog Input value converted to %.

TurningRightPercent = (AnalogPercent - 50) * 2;

TurningLeftPercent = (50 - AnalogPercent) * 2;

if (AnalogPercent > 50) //If turning right
{
  WheelSteeringAngle = ((TurningRightPercent / 100) * 28);
  //add difference to right motor
}
  else if (AnalogPercent < 50) //If turning left
  {
    WheelSteeringAngle = ((TurningLeftPercent / 100) * 28);
    //add difference to left motor
  }

InnerTurningRadius = (WheelBase / ((tan(WheelSteeringAngle))/(180.00/3.14159)); //Turn radius = (w/tan(Alpha))
//Convert radians into degrees.
    
Serial.print(" Wheel Steering Angle = ");
Serial.print(WheelSteeringAngle);
Serial.print(" Turning Right = ");
Serial.print(TurningRightPercent);
Serial.print(" % ");
Serial.print(" Turning Left = ");
Serial.print(TurningLeftPercent);
Serial.print(" % ");
Serial.print(" Analog Input = ");
Serial.print(AnalogPercent);
Serial.println(" % ");
delay(50);  //Delay for stability.

}
