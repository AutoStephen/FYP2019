
// program prints what i type in the serial monitor.

void setup() 
{
  Serial.begin(9600); //Set the communication speed and establish serial comm.
}
void loop() 
{ 
  String msg = "";

  if (Serial.available()>0)
  {
    while(Serial.available()>0) // stay in this loop while there are bytes to be read in the serial buffer.
    {
      msg += char(Serial.read()); // adding characters to the string.
      delay(25); // to ensure bits to not get lost.
    }

    Serial.println(msg);
    
  }
}
