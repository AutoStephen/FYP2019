int ThrottleInput;
int ThrottleOutput;
int FrontLeftMotor = 3;

void setup() {

Serial.begin(115200); //Baud rate between computer and Arduino.
}

void loop() {
pinMode (FrontLeftMotor, OUTPUT);
\
ThrottleInput = analogRead(A1); //Value from potentiometer placed into "ThrottleInput".
ThrottleOutput = ((ThrottleInput / 1023.00) * 255.00); //Analog Input value converted to %.

analogWrite(ThrottleOutput, FrontLeftMotor);

Serial.print(" Motor Signal = ");
Serial.println(ThrottleOutput);
delay(50);  //Delay for stability.

}
