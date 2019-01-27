// 24-Jan-2019 - Programme reads potentiometer signal and converts to string to be sent to Plettenberg.
// Developer: Stephen Murphy
// Status: Working. Does not consider steering or two motors. 

int TensCharacter; // Number 1 to 10 at the start of the throttle string

//Variables used to calculate the "TensCharacter"
int FirstTensVariable;
int SecondTensVariable;
int ThirdTensVariable;
int FourthTensVariable;
int FifthTensVariable;

//Variables used to calculate the "DecimalCharacters"
float DecimalValue;
float FirstDecimalVariable;
int SecondDecimalVariable;
float ThirdDecimalVariable;
int FourthDecimalVariable;

String OnesCharacters = ""; //String storing the "+" characters for the ones multiplier
String DecimalCharacters = ""; //String storing the "g" characters for the decimal multiplier
String FullThrottleString = "m"; //String to store "m" for full throttle, as per the controller manual
String ThrottleString = ""; //String that stores the final concated string to be sent to the motor

float ThrottleInput;  // Variable to store raw input from Potentiometer.
float ThrottlePercent;  //Variable to store throttle %.
float SteeringInput;  // Variable to store raw input from Potentiometer.
float SteeringPercent;  //Variable to store steering %.

 int SteeringVariable; //Variable stored purely for calculations.
 int LeftSignal; //Variable that is ultimately sent to the left motor.
 int RightSignal; //Variable that is ultimately sent to the right motor.
 
//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200); //Serial communication speed
}

//////////////////////////////////////////////////////////////////////////////////
void loop() 
{
//Convert the throttle input to a range 0-100.
ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Throttle value converted to %.

//Convert the steering input to a range 0-100.
SteeringInput = analogRead(A0); //Value from potentiometer placed into "SteeringInput".
SteeringPercent = ((SteeringInput / 1023.00) * 100.00); //Steering value converted to %.

// Steering Differential Calculation

  SteeringVariable = SteeringPercent;

  if (SteeringVariable <50) 
  { 
    //Car is turning left. Therefor the signal will be from 0 to 128. 
     LeftSignal = ThrottlePercent + (50 - SteeringVariable); // Left motor is increased by the difference from the mid point. 
     RightSignal = ThrottlePercent - (50 -SteeringVariable); // Right motor is decreased by the difference from the mid point.
    // This will produce a signal proportional to the amount turned.
  }
  if (SteeringVariable >50) 
  { 
   //Car is turning right. Therefor the signal will be from 128 to 255. 
    LeftSignal = ThrottlePercent - (SteeringVariable - 50); //Left motor is decreased by how far past the mid point the steering is.
    RightSignal = ThrottlePercent + (SteeringVariable - 50); //Right motor is increased by how far past the mid point the steering is.
   // This will produce a signal proportional to the amount turned.
  }
 

FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 OnesCharacters = ""; //Clear the string
  while (ThirdTensVariable >= 1) { //While the units value is >= 1
  ThirdTensVariable-= 1; //Decrease the units value by 1
  OnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

 DecimalCharacters = ""; //Clear the string
  while (FourthDecimalVariable >= 1) { //While the decimal units value is >= 1
  FourthDecimalVariable-= 1; //Decrease the units value by 1
  DecimalCharacters+="g"; //Increase the DecimalCharacters string by "+"
  }

if (ThrottlePercent == 100.00) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent < 10.00) 
  ThrottleString = ("" + OnesCharacters + DecimalCharacters + "f"); //e.g. 3.42% = "+++ggggf"
  else{
  ThrottleString = (TensCharacter + OnesCharacters + DecimalCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

//Print the following values:
Serial.print("Throttle Percent = ");
Serial.print(ThrottlePercent);
Serial.print("%   ");
Serial.print("Throttle String = ");
Serial.println(ThrottleString);


delay(100); // Delay for stability

}
