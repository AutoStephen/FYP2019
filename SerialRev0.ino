
int val;  // Variable to store data.

void setup() 
{


Serial.begin(9600); //Set the communication speed and establish serial comm. 
}

void loop() 
{
  // Wait until we receive something from the computer.
   while(Serial.available() == 0) /*Program will stay on this line until it receives 
                               something from the computer. */

  // When the Arduino does receive something, input that data into a variable.
  val = Serial.read() - '0';  // 0 is 48 in decimal from the Ascii table. 
                              // this ensures the returned value = input value.

  // Show this data in the serial monitor.
  Serial.println(val, DEC);
                  
}
