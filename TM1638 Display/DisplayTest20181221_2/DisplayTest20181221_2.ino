#include <InvertedTM1638.h>
#include <TM1638.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>


TM1638 module(8, 9, 7);



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
module.setLED(TM1638_COLOR_RED, 2);  // set LED number x to red
module.setLED(TM1638_COLOR_GREEN, 4); // set LED number x to green
module.setLED(TM1638_COLOR_RED+TM1638_COLOR_GREEN, 0); // set LED number x to red and green
}
