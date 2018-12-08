// *** BASIC PROGRAMME TO TEST INDIVIDUAL POTS and convert a less than ideal range e.g: 0-50% into 0-100% ***
// LAST UPDATED: 7-DECEMBER-2018
// DEVELOPER: STEPHEN MURPHY



float ThrottleInput1; //Variable to store raw input from throttle potentiometer 1.
float ThrottleInput2; //Variable to store raw input from throttle potentiometer 2.
float SteeringInput; //Variable to store raw input from steering potentiometer.
float BrakeInput; //Variable to store raw input from brake potentiometer.
float ThrottlePercent1; //Variable to store % value of throttle potentiometer 1.
float ThrottlePercent2; //Variable to store % value of throttle potentiometer 2.
float SteeringPercent; //Variable to store % value of steering potentiometer.
float BrakePercent; //Variable to store % value of brake potentiometer.
float FinalPercent; //Variable to store Final % value of throttle potentiometer 1.

////////////////////////////////////////////////////////////////////////////////////////////
void setup() {


Serial.begin(9600); //Baud rate between Arduino and Controller.


}

///////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  
// Read inputs from potentiometers and convert to 0 - 100 range. 
//First throttle potentiometer:
ThrottleInput1 = analogRead(A0);  //Read the data from the analog input pin and store in "ThrottleInput1" variable.
ThrottlePercent1 = ((ThrottleInput1 / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 

//FinalPercent = ThrottlePercent1 * 2;

if (ThrottlePercent1 > 50.00) 
  {
  FinalPercent = 100.00;
  }
  else 
  {
    FinalPercent = (ThrottlePercent1 * 2);
  }
 

Serial.print(" Throttle 1 = ");
Serial.print(ThrottleInput1);
Serial.print(" Throttle Percentage 1 = ");
Serial.print(ThrottlePercent1);
Serial.print(" Final Percentage = ");
Serial.print(FinalPercent);
Serial.println(" % ");

delay(200);  //Delay for stability.

}
