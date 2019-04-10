
#include <InvertedTM1638.h>
#include <TM1638.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>

TM1638 module(8, 9, 7);

int LED;

void setup() {


}

void loop() {

for(LED = 0; LED < 7; LED ++){
  module.setLED(TM1638_COLOR_RED, LED); //set LED number x to red
  delay(2000);
  module.setLED(TM1638_COLOR_GREEN, LED); //set LED number x to red
}



}
