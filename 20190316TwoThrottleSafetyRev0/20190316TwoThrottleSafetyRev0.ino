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
  ThrottleInput1 = analogRead(A0);  //Store data from analog input.
  ThrottlePercent1 = ((ThrottleInput1 / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 
  
  //Second throttle potentiometer:
  ThrottleInput2 = analogRead(A3);  //Store data from analog input.
  ThrottlePercent2 = ((ThrottleInput2 / 1023.00) * 100.00); //Convert the 0-1023 value to a 0-100 value. 

  OutputPercent = ((ThrottlePercent1 + ThrottlePercent2)/2); //Output signal = average of the two.

  //If the difference is greater than 10%
  if ((ThrottlePercent1 - ThrottlePercent2) > 10.00 || (ThrottlePercent2 - ThrottlePercent1) > 10.00)
  {
    OutputPercent = 0; //Motor signalled to turn off.
  }

  // ******************** Print values to the serial monitor for diagnostics. *************************
  
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
