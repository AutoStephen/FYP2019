/*
 * REUK.co.uk February 2016
 * Displaying two 1 or 2dp values less than 100 on a TM1638 module.
 * 
 * An excellent starter guide to the TM1638 modules is available here:
 * http://tronixstuff.com/2012/03/11/arduino-and-tm1638-led-display-modules/
*/

// include the TM1638 library (which you must first install to your Arduino IDE).
#include <TM1638.h>

// Define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638 module(8, 9, 7);

// Define constants for left and right so we can easily choose 
// which side of the display to show our number
#define LEFT 0
#define RIGHT 1

// displayDigits[0] = 63 which displays a 0
// displayDigits[1] = 6 which displays a 1
// displayDigits[2] = 91 which displays a 2...etc
// Add 128 to value to display the same number with a dp following it.
// e.g. display a 2 with 91, display a 2. with 91+128=219
byte displayDigits[] = {63,6,91,79,102,109,124,7,127,103 };

// An array for the values to be displayed - all zeroes means show nothing.
byte values[] = { 0,0,0,0,0,0,0,0 };

// The digits which will make up a number to be displayed
// e.g. 25.63 will fill theDigits array with values of 2, 5, 6, and 3
int theDigits[] = { 0,0,0,0 };

void setup(){
 // Start with the digital display blank.
 module.setDisplay(values);

 // Set the display to low intensity. High intensity is very bright and
 // uses more power.
 module.setupDisplay(true, 2); // where 7 is intensity (from 0 to 7)
}

void loop(){
 // This is an example number from 0 to 99.9999 you would like to display.
 float theNumberToDisplay = 12.5432334;

 // Where do you want to show the number, on the LEFT side, or the RIGHT of the display?
 int positionToDisplayIt = LEFT;

 // How many decimal places to show - must be 1 or 2 in this example code
 int numberOfDecimalPlacesToShow = 2;

 // Call the function to display the number
 displayNumber(theNumberToDisplay, positionToDisplayIt, numberOfDecimalPlacesToShow);
}

void displayNumber(float numberToSplit, int whichSide, int numOfDPs){
 // The number to be split should be a float from 0 to 99.9999
 // If is below zero or equal to or over 100, then just display ----.
 // numOfDPs is the number of digits after the point, only 1 or 2 are acceptable values
 if(numOfDPs > 2 or numOfDPs < 1)numOfDPs = 1;

 // Extract the digits from this number.
 numberToSplit = (int)(100 * numberToSplit);
 theDigits[0] = (int)(numberToSplit/1000);
 theDigits[1] = (int)((numberToSplit - (1000*theDigits[0])) / 100);
 theDigits[2] = (int)((numberToSplit - (1000*theDigits[0]) - (100*theDigits[1]))/10);
 theDigits[3] = (int)(numberToSplit - (1000*theDigits[0]) - (100*theDigits[1]) - (10*theDigits[2]));

 // Find and store the byte variables required to show these digits
 int dispDig[4];
 if(theDigits[0] == 0) dispDig[0] = 0; // Hide a leading zero if there is one
 else dispDig[0] = displayDigits[theDigits[0]];
 dispDig[1] = displayDigits[theDigits[1]] + 128; // Apend the dp onto the second digit
 dispDig[2] = displayDigits[theDigits[2]];
 dispDig[3] = displayDigits[theDigits[3]];

 // If we are only showing one DP, then leave last character blank to make things more legible on the display
 if(numOfDPs == 1) dispDig[3] = 0;

 // Make sure that the number passed to the function was >= 0 or <100, otherwise show an error with ----.
 if(numberToSplit/100 < 0 or numberToSplit/100 >= 100){
   for(int i = 0; i < 4; i++) dispDig[i] = 64;
 }

 // Find if number to be shown on the left or the right side of the display
 int offset = 0; // LEFT by default
 if(whichSide == RIGHT) offset = 4;

 // Update the values in the values array used by the display.
 values[0+offset] = dispDig[0];
 values[1+offset] = dispDig[1];
 values[2+offset] = dispDig[2];
 values[3+offset] = dispDig[3];

 // Update the display itself with the new values.
 module.setDisplay(values);
}
