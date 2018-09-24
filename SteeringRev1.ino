// TWO POTENTIOMETER INPUTS AND TWO PWM OUTPUTS

 int PotValue0; //Variable for storing the value from the throttle potentiometer.
 int PotValue5; //Variable for storing the value from the steering potentiometer.
 int LeftMotor = 3; //Motor on pin 3
 int RightMotor = 5; //Motor on pin 5
 int Throttle; //Value from one potentiometer times conversion factor
 int Steering; //Value from the other potentiometer times conversion factor
 int SteeringVariable; //Variable stored purely for calculations.
 int LeftSignal; //Variable that is ultimately sent to the left motor.
 int RightSignal; //Variable that is ultimately sent to the right motor.

 
void setup() {

  Serial.begin(9600); //Start communication to read signal.
}

void loop() {

  PotValue0 = analogRead(A0); // Extract information from throttle pot.
  PotValue5 = analogRead(A5); // Extract information from steering pot.

  Throttle = PotValue0 / 4; //Dividing by 4 brings the signal into the required 0-255 range.
  Steering = PotValue5 / 4;



  SteeringVariable = Steering;

  if (SteeringVariable <128) { //Car is turning left. Therefor the signal will be from 0 to 128. 
     LeftSignal = Throttle + (128 - SteeringVariable); // Left motor is increased by the difference from the mid point. 
     RightSignal = Throttle - (128 -SteeringVariable); // Right motor is decreased by the difference from the mid point.
  } // This will produce a signal proportional to the amount turned.

 if (SteeringVariable >128) { //Car is turning right. Therefor the signal will be from 128 to 255. 
   LeftSignal = Throttle - (SteeringVariable - 128); //Left motor is decreased by how far past the mid point the steering is.
   RightSignal = Throttle + (SteeringVariable - 128); //Right motor is increased by how far past the mid point the steering is.
 } // This will produce a signal proportional to the amount turned.

  
  
  analogWrite(LeftMotor, LeftSignal); //signal going to motors
  analogWrite(RightMotor, RightSignal);


  //Print values on the Serial Monitor.
  Serial.print("Throttle "); 
  Serial.print(Throttle); 
  Serial.print("  ");
  Serial.print("Steering ");
  Serial.print(Steering);
  Serial.print("  ");
  Serial.print("SteeringVariable ");
  Serial.print(SteeringVariable);
  Serial.print("  ");
  Serial.print("RightSignal ");
  Serial.print(RightSignal);
  Serial.print("  ");
  Serial.print("LeftSignal ");
  Serial.println(LeftSignal);
  
  delay(100); //delay for stability 
}

