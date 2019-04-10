String IncomingData;

void setup() 
{

Serial.begin(115200);

}

void loop() 
{

//if (Serial.available() > 0)
//  {
  IncomingData = Serial.readString();
  
  Serial.println(IncomingData);
  //}
}
