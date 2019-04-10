
#include <TM1638.h>
// define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638 module(8, 9, 7);
unsigned long a=1;
void setup(){}
void loop()
{
module.setLED(TM1638_COLOR_RED, 1);  // set LED number x to red
module.setLED(TM1638_COLOR_GREEN, 2); // set LED number x to green
module.setLED(TM1638_COLOR_RED+TM1638_COLOR_GREEN, 0); // set LED number x to red and green

}
