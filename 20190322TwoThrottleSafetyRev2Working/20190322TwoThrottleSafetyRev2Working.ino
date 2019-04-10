// PROGRAMME TO READ INPUT FROM 2 THROTTLE POTS
// IF THE % DIFFERENCE BETWEEN THEM IS >10%, MOTORS SWITCH OFF. 
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
int intervalMillis = 3000;
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

  
  
  if ((ThrottlePercent1 - ThrottlePercent2) > 10.00 || (ThrottlePercent2 - ThrottlePercent1) > 10.00 )
  {
    Implausible = 1;
  }
  else if (MotorInterlock = 0)
  {
    OutputPercent = ((ThrottlePercent1 + ThrottlePercent2)/2);
    Implausible = 0;
  }



  if (Implausible == 1)
  {
    ImplausibleMillis = millis();
    differenceMillis = (ImplausibleMillis - currentMillis);
    
    if (differenceMillis >= 3000)
    {
      OutputPercent = 0;
      MotorInterlock =1;
    }
  }
  else if (Implausible == 0)
  {
    currentMillis = millis();
    OutputPercent = ((ThrottlePercent1 + ThrottlePercent2)/2);
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
