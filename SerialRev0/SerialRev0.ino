void setup() {

serial.begin(9600); //Set the communication speed and establish serial comm. 
}

void loop() {
// Wait until we receive something from the computer.
while(serial.available()==0) //Program will stay on this line until it receives something from the computer.
}
