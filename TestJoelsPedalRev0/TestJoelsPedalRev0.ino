//READ SIGNAL FROM JOEL'S PEDAL POTENTIOMETERS
//DEVELOPER: STEPHEN MURPHY
//LAST UPDATED: 14-DEC-2018

//BRAKE POTENTIOMETR WORKING.
//ACCELERATOR POTENTIOMETER NOT WORKING.
void setup() {
  
Serial.begin(9600); 

int SensorValue1;
int SensorValue2;

}

void loop() {
int SensorValue1 = analogRead(A0);
//int SensorValue2 = analogRead(A1);

Serial.print(" potentiometer 1 = ");
Serial.println(SensorValue1);
//Serial.print(" potentiometer 2 = ");
//Serial.println(SensorValue2);

delay(100);

}
