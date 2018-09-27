/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// Includes
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TM1638.h>

// Defines
#define throttleIn         A5  // Analog input pin, used for potentiometer throttle
#define steeringIn         A1  // Analog input pin, used for potentiometer steering
#define leftThrottlePin    9
#define throttleOutputPin 10   // Digital (PWM) output pin, used for Arduino analog throttle
#define rightThrottlePin  11

//#define LEFT 0                 // Define constants for left and right so we can easily choose 
//#define RIGHT 1                // which side of the display to show our number
#define RS232Speed 115200      // speed of RS232 communications with the controller
              
// define a module on data pin 7, clock pin 8 and strobe pin 9
//TM1638 module(5, 6, 7);
SoftwareSerial mySerial(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3


// displayDigits[0] = 63 which displays a 0 (being the sum of the six segments making up a 9) 1+2+4+8+16+32
// displayDigits[1] = 6 which displays a 1 (being the sum of the two segments making up a 1) (2 + 4)
// displayDigits[2] = 91 which displays a 2...etc (being the sum of the five segments making up a 2) (1+2+8+16+64) etc...
// Add 128 to value to display the same number with a dp following it.
// e.g. display a 2(91), display a 2. (91+128=219)
//byte displayDigits[] = {63,6,91,79,102,109,124,7,127,103 };

// An array for the values to be displayed - all zeroes means show nothing.
//byte values[] = { 0,0,0,0,0,0,0,0 };

// The digits which will make up a number to be displayed
// e.g. 25.63 will fill theDigits array with values of 2, 5, 6, and 3
//int theDigits[] = { 0,0,0,0 };

// Initial variable values
int     sensorValue=      0;    // used to read the potentiometer value (sensed in the range 0 -2013)
int     throttleValue=    0;    // used to send PWM signal to output (output in the range 0-255) corresponding to the throttle setting above
double  voltage=          0.0f; // ussed to report voltage read from potentiometer (and output being generated on the PWM pin)
double  throttlePercent=  0.0f; // used to report throttle percent to driver and for diagnstics

String  throttleString=   "";   // initialise the throttleString (digital control) to empty
                                // this will be the control string sent to the RS232 device, which is connected to the Pletttenbeg controller
                                
String  serialInitString= "p";  // used to initialise the controller to accept analog input, limp-home mode
                                // to do a real limp-home mode, we would add a resistor in series wiht the potentiometer
                                // to limit the max throttle in limp-home mode
                                
// String  serialInitString= "s";  // used to initialise the controller to accept serial command strings, by default we are using "p", not "s"

//////////////////////////////////////////////////////////////////////////////
// getDifferential
float getDifferential()
{
  int steeringSensor = analogRead(steeringIn);        // Read the steering setting, range 0-1023
  float differential = (512.0 - steeringSensor)/32.0; // crude calculation of the differential
                                                      // (512 - steeringSetting) gives a value in the range (512 to -511)
                                                      // (512 to -511)/32 gives a value in the range (16 to -16)
  return differential;
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// setThrottleString
// Used to set the throttle string to be sent to the RS232 port on the motor controller
// Not perfect (yet)
void setThrottleString(double tPercent)
{
  // refer to the Pletterberg manual for the protocol here
  // tens = digit 1-9
  // units = +
  // tenths (0.1) = g
  // 73.1 = 7+++gf (f being for forward)
  
  throttleString="";            // clear the throttleString
  if (tPercent == 100)          // if we are on full-throttle,
    throttleString="m";         // set the string to "m"
    
  else                          // if we are not on full-throttle
  {                             // set the initial digit, 0..9
    
      int digit1 = tPercent/10;   // gives us the tens multiplier
      tPercent -= digit1*10;      // this leaves us with the digits (and decimal fraction part)
      if (digit1 >= 1) throttleString+=String(digit1);

    ///////////////// 1s
    while(tPercent>=1)          // set the number of '+' characters for the second digit
                                // this loop decrements the tPercent value by one each time
                                // and adds a "+" to the string for each unit
          {
            tPercent -=1;
            throttleString+="+";
          }
    ///////////////// 0.1s
    while(tPercent>=0.1)        // set the number of 'g' characters for the third digit
                                // same again her for the 0.1s as for the 1s above
          {
            tPercent -=0.1;
            throttleString+="g";
          } // end while loop for third digit
          //////////////////

    } // end while loop for second digit and else loop for throttle <> 100%
  throttleString+="f";          // append 'f' character to end of every throttle string
} // end setThrottleString function
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// setup
// the setup routine runs once when you press reset:
void setup() {
  
  // Use the 5v supplied by the controller as Analog reference
  // analogReference (EXTERNAL) ;
  // analogRead (0) ;
  
  // initialize serial communication at 9600 bits per second:

  pinMode(throttleIn, INPUT);                 // set pin mode for input pin
  pinMode(throttleOutputPin, OUTPUT);         // set pin mode for throttle output pin

  Serial.begin(9600);                         // start serial communications for diagnostics
  mySerial.begin(RS232Speed);                 // start serial communications for digital control of motor

  mySerial.println("p");                      // send the command to switch on serial control of the motor to the RS232 port

}
// end setup
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// loop
// the loop routine runs over and over again forever:
void loop() {

  // 1: read some values
  // 2: do some cacullations
  // 3: print them out
  // 4: send something to the mySerial (RS232 Shield)
  // 5: send something to the PWM pin (one of the digital pins, possibly 10)
   
  sensorValue = analogRead(throttleIn);              // read the input on analog pin 0:
  voltage = (sensorValue * 5.0f)/1023.0;            // calculate the voltage for reporting, range 0-5.0volts
  throttlePercent = (sensorValue *100.0f)/1023.0f;  // calculate throttle percent for reporting and speedometer
  throttleValue = sensorValue / 4;                  // calculate the throttle value for output via PWM pin

  float differential = getDifferential();
  float lspeed = throttlePercent-differential;
  float rspeed = throttlePercent+differential;
  
  // display diagnostics
  Serial.print("SpeedSensor: ");                         // print the sensor value read on the analog input pin (0..1023)
  Serial.print(sensorValue);                        // print to the Serial Monitor

  //Serial.print(" SteeringSensor: ");                         // print the sensor value read on the analog input pin (0..1023)
  //Serial.print(analogRead(steeringIn));                        // print to the Serial Monitor
  
  Serial.print(" Voltage: ");                       // print the voltage seen at the analog input pin (0-5v)
  Serial.print(voltage);                            // print to the Serial Monitor
  Serial.print("v ");

  Serial.print(" Throttle: ");                      // print the throttle percentage (0..100%)
  Serial.print(throttlePercent);                    // print to the Serial Monitor
  Serial.print("% ");

  //Serial.print(" DIFF ");
  //Serial.print(differential);
    
  //Serial.print(" LEFTSpeed: ");                      // print the throttle percentage (0..100%)
  //Serial.print(throttlePercent-getDifferential());   // print to the Serial Monitor
  //Serial.print("% ");

  //analogWrite(leftThrottlePin, throttlePercent-getDifferential());
   
  //Serial.print(" RIGHTSpeed: ");                      // print the throttle percentage (0..100%)
  //Serial.print(throttlePercent+getDifferential());    // print to the Serial Monitor
  //Serial.print("% ");

  //analogWrite(rightThrottlePin, throttlePercent+getDifferential());

  Serial.print(" ThrottleValue: ");                 // print the throttle value to send to PWM pin (0..255)
  Serial.print(throttleValue);                      // print to the Serial Monitor

  Serial.print(" digitalString ");
  setThrottleString(throttlePercent);               // set the throttle string
  Serial.println(throttleString);                   // print the throttle string to the Serial Monitor
  
  mySerial.println(throttleString);                 // print the throttle string to the RS232 port

 
  //analogWrite(throttleOutputPin, throttleValue);    // send the throttle value to the PWM pin
} // end loop
//////////////////////////////////////////////////////////////////////////////
