
int AnalogInput;
int AnalogPercent;
int SquaredValue;
int SquaredPercent;

void setup() 
{

Serial.begin(115200); //Baud rate between computer and Arduino.
}

void loop() 
{

AnalogInput = analogRead(A0); //Value from potentiometer placed into "ThrottleInput".
AnalogPercent = ((AnalogInput / 1023.00) * 100.00); //Analog Input value converted to %.
SquaredValue = (AnalogPercent * AnalogPercent);
SquaredPercent = ((SquaredValue / 10000) * 100.00);


Serial.print(" Output Value = ");
Serial.print(AnalogPercent);
Serial.println(" % ");
delay(50);  //Delay for stability.

}
