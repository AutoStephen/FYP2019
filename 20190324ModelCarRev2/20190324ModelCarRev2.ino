int AnalogInput;
int AnalogPercent;
int ThrottleOutput;
int Motor1 = 3;
int Motor2 = 5;

void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
}

void loop() {

pinMode(Motor1, OUTPUT);
pinMode(Motor2, OUTPUT);

AnalogInput = analogRead(A1); //Value from potentiometer placed into "ThrottleInput".
AnalogPercent = ((AnalogInput / 1023.00) * 100.00); //Analog Input value converted to %.
ThrottleOutput = ((AnalogPercent / 100.00) * 255.00); 

analogWrite(Motor1, ThrottleOutput);
analogWrite(Motor2, ThrottleOutput);

Serial.print(" Throttle Output = ");
Serial.print(ThrottleOutput);
Serial.print(" Analog Input = ");
Serial.print(AnalogPercent);
Serial.println(" % ");
delay(50);  //Delay for stability.

}
