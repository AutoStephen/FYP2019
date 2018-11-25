#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup() {

Serial.begin(9600);
mySerial.begin(115200);
mySerial.println("s");

}

void loop() {

mySerial.println("2f");
delay(500);

Serial.println(mySerial.read());

}
