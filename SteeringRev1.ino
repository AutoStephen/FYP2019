// TWO POTENTIOMETER INPUTS AND TWO PWM OUTPUTS

 int PotValue0;
 int PotValue5;
 int LeftMotor = 9; //motor on pin 9
 int RightMotor = 6; //motor on pin 6
 int Throttle; //value from one potentiometer times conversion factor
 int Steering; //value from the other potentiometer times conversion factor
 int SteeringVariable;
 int LeftSignal;
 int RightSignal;

 
void setup() {

  Serial.begin(9600); //start communication to read signal
}

void loop() {

  PotValue0 = analogRead(A0); // signal from pot that represents the throttle
  PotValue5 = analogRead(A5); // signal from pot that represents the steering

  Throttle = PotValue0 * (255.0/1023.0); //Conversion Factor or simply divide by 4.
  Steering = PotValue5 * (255.0/1023.0);



  SteeringVariable = 127.5 - Steering; //17.5 is the neutral value. subtracting the pot's position will give the amount of change from the neutral position. 

  if (SteeringVariable <0) { //car is turning right
     LeftSignal = Throttle + SteeringVariable;
     RightSignal = Throttle - SteeringVariable;
  }

  if (SteeringVariable >0) { //car is turning left
     LeftSignal = Throttle + SteeringVariable;
     RightSignal = Throttle - SteeringVariable;
  }

  
  
  analogWrite(LeftMotor, LeftSignal); //signal going to motors
  analogWrite(RightMotor, RightSignal);

  
  Serial.print("Throttle "); //print value from the potentiometers
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

