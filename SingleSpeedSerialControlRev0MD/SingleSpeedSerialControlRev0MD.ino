#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup() {

Serial.begin(115200);
mySerial.begin(115200);
mySerial.println("s");
Serial.println("s");

}

void loop() {

mySerial.println("4f");
Serial.println("2f");
delay(500);

mySerial.println("s");
Serial.println("s");
delay(500);

}
