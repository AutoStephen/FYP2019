
int TensCharacter;

int FirstTensVariable;
int SecondTensVariable;
int ThirdTensVariable;
int FourthTensVariable;
int FifthTensVariable;

String OnesCharacters = "";
String DecimalCharacters = "";
String FullThrottleString = "m";
String ThrottleString = "";

float DecimalValue;
float ThrottleInput;  // Variable to store raw input from Potentiometer.
float ThrottlePercent;  //Variable to store throttle %.
float FirstDecimalVariable;
int SecondDecimalVariable;
float ThirdDecimalVariable;
int FourthDecimalVariable;

//////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

//////////////////////////////////////////////////////////////////////////////////
/*void setThrottleString(){
  OnesCharacters = ""; //FUCKING FINALLY, I NEED TO CLEAR THE STRING EVERY TIME!!!!
  while (ThirdTensVariable >= 1) {
  ThirdTensVariable-= 1;
  OnesCharacters+="+";
  }
}
*/
//////////////////////////////////////////////////////////////////////////////////
void loop() {

//Convert the throttle input to a range 0-100.
ThrottleInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
ThrottlePercent = ((ThrottleInput / 1023.00) * 100.00); //Throttle value converted to %.

FirstTensVariable = ThrottlePercent;
TensCharacter = (FirstTensVariable/10);
SecondTensVariable = (TensCharacter*10);
ThirdTensVariable = (FirstTensVariable - SecondTensVariable);

//DecimalValue:
FirstDecimalVariable = ThrottlePercent;
SecondDecimalVariable = ThrottlePercent;
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable);
FourthDecimalVariable = (ThirdDecimalVariable * 10);

 OnesCharacters = ""; //FUCKING FINALLY, I NEED TO CLEAR THE STRING EVERY TIME!!!!
  while (ThirdTensVariable >= 1) {
  ThirdTensVariable-= 1;
  OnesCharacters+="+";
  }

 DecimalCharacters = ""; //FUCKING FINALLY, I NEED TO CLEAR THE STRING EVERY TIME!!!!
  while (FourthDecimalVariable >= 1) {
  FourthDecimalVariable-= 1;
  DecimalCharacters+="g";
  }

if (ThrottlePercent == 100.00) 
  ThrottleString = (FullThrottleString + "f");
  else if (ThrottlePercent < 10.00) 
  ThrottleString = ("" + OnesCharacters + DecimalCharacters + "f");
  else{
  ThrottleString = (TensCharacter + OnesCharacters + DecimalCharacters + "f");
  }
  
Serial.print("Throttle Percent = ");
Serial.print(ThrottlePercent);
Serial.print("%   ");
Serial.print("Throttle String = ");
Serial.println(ThrottleString);


delay(100);

}
