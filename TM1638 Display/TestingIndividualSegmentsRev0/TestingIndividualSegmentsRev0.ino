
#include <InvertedTM1638.h>
#include <TM1638.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>

TM1638 module(8, 9, 7);

int LED;
int Display = 782822;

unsigned long a;

unsigned long Pot;

void setup() {
Serial.begin(9600);
}

void loop() {

int theDigits[] = { 0,0,0,0 };  
byte values[] = { 109,63,119,119,102,0,0,0 };
//byte values[] = { 255, 2, 4, 8, 16, 32, 64, 128 };
module.setDisplay(values);


}
