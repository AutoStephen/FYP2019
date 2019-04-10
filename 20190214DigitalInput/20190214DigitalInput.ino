int Switch = 13;
int SwitchValue;
void setup() 
{
  pinMode(Switch, INPUT);
  Serial.begin(115200); //Serial communication speed
}

void loop() 
{
  SwitchValue = digitalRead(Switch);
  Serial.println(SwitchValue);
}
