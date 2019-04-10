
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

  Pot = analogRead(A0);
  
 //for (a=10000; a<11000; a++)
// {
// module.setDisplayToDecNumber(a,4,false);
// delay(1);
// }
// for (a=10000; a<11000; a++)
// {
 module.setDisplayToDecNumber(Pot,0,true);
// delay(1);
// }

 Serial.println (Pot);
 delay(50);
 // module.setupDisplay(true, 3); // where 7 is intensity (from 0~7)

 // module.setDisplayToDecNumber(Display,1,true);
  
  /*
// NOTE: seeting an LED to "green" turns it off because this display only has red LEDs. 
for(LED = 0; LED < 7; LED ++){
  module.setLED(TM1638_COLOR_RED, LED); //set LED ON
  delay(2000); //wait a set amount of time
  module.setLED(TM1638_COLOR_GREEN, LED); //set LED OFF
}
*/


}
