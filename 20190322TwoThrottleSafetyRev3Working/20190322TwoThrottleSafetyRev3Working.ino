// PROGRAMME TO READ INPUT FROM 2 THROTTLE POTS
// IF THE % DIFFERENCE BETWEEN THEM IS >10%, MOTORS SWITCH OFF (and stay off until reset). 
// LAST UPDATED: 16-MARCH-2019
// DEVELOPER: STEPHEN MURPHY

#include <Arduino.h> //Include additional Arduino Libraries.

float ThrottleInput1; //Variable to store raw input from throttle potentiometer 1.
float ThrottleInput2; //Variable to store raw input from throttle potentiometer 2.
float ThrottlePercent1; //Variable to store % value of throttle potentiometer 1.
float ThrottlePercent2; //Variable to store % value of throttle potentiometer 2.
float OutputPercent; //Variable to store % value of being sent to motor.
bool Implausible; //Variable to turn on or off if there is a difference of more than 10%. 
int ImplausibleMillis;
int intervalMillis = 1000;
int currentMillis;
int differenceMillis;
int MotorInterlock = 0;

////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200); //Baud rate between computer and Arduino.
}

///////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{  
  // Read inputs from potentiometers and convert to 0 - 100 range. 
  //First throttle potentiometer:
  ThrottleInput1 = analogRead(A0);  //Read the data from the analog input pin and store in "ThrottleInput1" variable.
  ThrottlePercent1 = ((ThrottleInput1 / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 
  
  //Second throttle potentiometer:
  ThrottleInput2 = analogRead(A1);  //Read the data from the analog input pin and store in "ThrottleInput2" variable.
  ThrottlePercent2 = ((ThrottleInput2 / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 

  //if the difference between the two sensors is greater than 10%
  if ((ThrottlePercent1 - ThrottlePercent2) > 10.00 || (ThrottlePercent2 - ThrottlePercent1) > 10.00 )
  {
    Implausible = 1; //Turn on the flag on to say the sensor signal is inplausible.
  }
  else if (MotorInterlock = 0) //If the sensors have never been out of range for longer than 1 second
  {
    OutputPercent = ((ThrottlePercent1 + ThrottlePercent2)/2); //Output is as normal
    Implausible = 0; //Turn on the flag off to say the sensor signal is plausible.
  }

  if (Implausible == 1) //If the signal is inplausible
  {
    ImplausibleMillis = millis();
    differenceMillis = (ImplausibleMillis - currentMillis); //Count for how long.
    
    if (differenceMillis >= 1000) //If signals have been different for 1 second or more
    {
      OutputPercent = 0; //Turn off the motor
      MotorInterlock =1; //Turn on the interlock so the motor does no come on until reset.
    }
  }
  else if (Implausible == 0) //If the sensors are good
  {
    currentMillis = millis();
    OutputPercent = ((ThrottlePercent1 + ThrottlePercent2)/2); //Output is as normal
  }

  // ******************** Print values to the serial monitor for diagnostics. *************************
  
  Serial.print(" current Millis = ");
  Serial.print(currentMillis);

  Serial.print(" Implausible Millis = ");
  Serial.print(ImplausibleMillis);

  Serial.print(" Difference Millis = ");
  Serial.print(differenceMillis);

  Serial.print(" Implausible = ");
  Serial.print(Implausible);
  
  Serial.print(" Throttle 1 = ");
  Serial.print(ThrottlePercent1);
  Serial.print(" % ");
  
  Serial.print(" Throttle 2 = ");
  Serial.print(ThrottlePercent2);
  Serial.print(" % ");

  Serial.print(" Output = ");
  Serial.print(OutputPercent);
  Serial.println(" % ");

  delay(100);  //Delay for stability.
}
