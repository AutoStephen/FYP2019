//Timer Interrupt
//Change the throttle depending on how much time has passed. 
//Constantly runs the void loop and then executes the 
// interrupt service routine TimerISR every 5 seconds
//Next step could be to use switch to start timer?

#include <TimerOne.h>
#include <Arduino.h> //Include additional Arduino Libraries.
#include <SoftwareSerial.h> //Include software serial library for shield.

SoftwareSerial mySerial1(2, 3); // RX, TX, Create a softwareSerial port on pins 2 and 3.
SoftwareSerial mySerial2(4, 5); // RX, TX, Create a softwareSerial port on pins 4 and 5.

int TensCharacter; // Number 1 to 10 at the start of the throttle string

//Variables used to calculate the "TensCharacter"
int FirstTensVariable;
int SecondTensVariable;
int ThirdTensVariable;
int FourthTensVariable;
int FifthTensVariable;

//Variables used to calculate the "DecimalCharacters"
float DecimalValue;
float FirstDecimalVariable;
int SecondDecimalVariable;
float ThirdDecimalVariable;
float ThirdTensVariableDuplicate;
int FourthDecimalVariable;

String OnesCharacters = ""; //String storing the "+" characters for the ones multiplier
String DecimalCharacters = ""; //String storing the "g" characters for the decimal multiplier
String LessThanTenCharacters = ""; //String storing the "-" characters for the ones multiplier when <10%
String LessThanTenDecimalCharacters = ""; //String storing the "l" (as in L for lion) characters for the decimal multiplier when <10%
String FullThrottleString = "m"; //String to store "m" for full throttle, as per the controller manual
String ThrottleString = ""; //String that stores the final concated string to be sent to the motor

float ThrottleInput;  // Variable to store raw input from Potentiometer.
float ThrottlePercent = 0;  //Variable to store throttle %.

int ToggleSwitch = 13;
int ToggleSwitchValue =0;

volatile unsigned long TimerCounter = 0; // count how many times the timer TimerISR is called


//////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{  
  pinMode(ToggleSwitch, INPUT);
  
  Serial.begin(115200); //Serial communication speed
  
  mySerial1.begin(115200); //Baud rate between Arduino and Controller.
  mySerial1.println("s"); //Initialise the controller to accept serial command strings.
  
  mySerial2.begin(115200); //Baud rate between Arduino and Controller.
  mySerial2.println("s"); //Initialise the controller to accept serial command strings.
  
  Timer1.initialize(5000000); // 10 million microseconds is 10 seconds
  //Timer runs every x seconds and does the following TimerISR
  Timer1.attachInterrupt(TimerISR);

}


void loop() 
{
 noInterrupts();
 interrupts();

ToggleSwitchValue = digitalRead(ToggleSwitch); // Toggle switch to turn on/off motor. 

if (ThrottlePercent == 0 && ToggleSwitchValue == 1 && TimerCounter == 0 ) 
{ 
  for (ThrottlePercent = 0; ThrottlePercent <50; ThrottlePercent++)
    {
    Timer1.detachInterrupt(); 
    FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 OnesCharacters = ""; //Clear the string
  while (ThirdTensVariable >= 1) //While the units value is >= 1
  { 
  ThirdTensVariable-= 1; //Decrease the units value by 1
  OnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

 DecimalCharacters = ""; //Clear the string
  while (FourthDecimalVariable >= 1) //While the decimal units value is >= 1
  { 
  FourthDecimalVariable-= 1; //Decrease the units value by 1
  DecimalCharacters+="g"; //Increase the DecimalCharacters string by "+"
  }

 LessThanTenCharacters = ""; //Clear the string
  while (ThirdTensVariableDuplicate < 10) //While the units value is >= 1
  { 
  ThirdTensVariableDuplicate+= 1; //increase the units value by 1
  LessThanTenCharacters+="-"; //Increase the DecimalCharacters string by "+"
  }

if (ThrottlePercent >= 100.00 && ToggleSwitchValue == 1) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent == 0.00 || ToggleSwitchValue == 0) 
  ThrottleString = ("0"); //0% = 0
  else if (ThrottlePercent < 10.00 && ThrottlePercent > 0.00 && ToggleSwitchValue == 1)
  ThrottleString = (1 + LessThanTenCharacters + "f"); //e.g. 3.42% = "1-------f"
  else if (ToggleSwitchValue == 1)
  {
  ThrottleString = (TensCharacter + OnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

mySerial1.println(ThrottleString); //Send throttle value to motor
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

mySerial2.println("0"); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up. 

      
    Serial.print("Throttle Percent = ");
    Serial.print(ThrottlePercent);
    Serial.print("%   ");
    Serial.print("Throttle String = ");
    Serial.print(ThrottleString);
    Serial.println(" In For Loop ");
    delay(500);
    }
  interrupts();
 // Timer1.attachInterrupt(TimerISR); 
}
else if (TimerCounter == 1 && ThrottlePercent == 50)
{
  for (ThrottlePercent = 50; ThrottlePercent <70; ThrottlePercent++)
  {
    delay(100); //change by 20% in 2 seconds
        FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 OnesCharacters = ""; //Clear the string
  while (ThirdTensVariable >= 1) //While the units value is >= 1
  { 
  ThirdTensVariable-= 1; //Decrease the units value by 1
  OnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

if (ThrottlePercent >= 100.00 && ToggleSwitchValue == 1) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent == 0.00 || ToggleSwitchValue == 0) 
  ThrottleString = ("0"); //0% = 0
  else if (ThrottlePercent < 10.00 && ThrottlePercent > 0.00 && ToggleSwitchValue == 1)
  ThrottleString = (1 + LessThanTenCharacters + "f"); //e.g. 3.42% = "1-------f"
  else if (ToggleSwitchValue == 1)
  {
  ThrottleString = (TensCharacter + OnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

mySerial1.println(ThrottleString); //Send throttle value to motor
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

mySerial2.println("0"); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up. 

      
    Serial.print("Throttle Percent = ");
    Serial.print(ThrottlePercent);
    Serial.print("%   ");
    Serial.print("Throttle String = ");
    Serial.print(ThrottleString);
    Serial.println(" In For Loop ");
  }
}

else if (TimerCounter == 2 && ThrottlePercent == 70)
{
  for (ThrottlePercent = 70; ThrottlePercent >30; ThrottlePercent--)
  {
    delay(50); //change by 40% in 2 seconds
        FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 OnesCharacters = ""; //Clear the string
  while (ThirdTensVariable >= 1) //While the units value is >= 1
  { 
  ThirdTensVariable-= 1; //Decrease the units value by 1
  OnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

if (ThrottlePercent >= 100.00 && ToggleSwitchValue == 1) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent == 0.00 || ToggleSwitchValue == 0) 
  ThrottleString = ("0"); //0% = 0
  else if (ThrottlePercent < 10.00 && ThrottlePercent > 0.00 && ToggleSwitchValue == 1)
  ThrottleString = (1 + LessThanTenCharacters + "f"); //e.g. 3.42% = "1-------f"
  else if (ToggleSwitchValue == 1)
  {
  ThrottleString = (TensCharacter + OnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

mySerial1.println(ThrottleString); //Send throttle value to motor
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

mySerial2.println("0"); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up. 

      
    Serial.print("Throttle Percent = ");
    Serial.print(ThrottlePercent);
    Serial.print("%   ");
    Serial.print("Throttle String = ");
    Serial.print(ThrottleString);
    Serial.println(" In For Loop ");
  }
}

else if (TimerCounter == 3 && ThrottlePercent == 30)
{
  for (ThrottlePercent = 30; ThrottlePercent > 0; ThrottlePercent--)
  {
    delay(67); //change by 30% in 2 seconds
        FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 OnesCharacters = ""; //Clear the string
  while (ThirdTensVariable >= 1) //While the units value is >= 1
  { 
  ThirdTensVariable-= 1; //Decrease the units value by 1
  OnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

if (ThrottlePercent >= 100.00 && ToggleSwitchValue == 1) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent == 0.00 || ToggleSwitchValue == 0) 
  ThrottleString = ("0"); //0% = 0
  else if (ThrottlePercent < 10.00 && ThrottlePercent > 0.00 && ToggleSwitchValue == 1)
  ThrottleString = (1 + LessThanTenCharacters + "f"); //e.g. 3.42% = "1-------f"
  else if (ToggleSwitchValue == 1)
  {
  ThrottleString = (TensCharacter + OnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

mySerial1.println(ThrottleString); //Send throttle value to motor
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

mySerial2.println("0"); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up. 

      
    Serial.print("Throttle Percent = ");
    Serial.print(ThrottlePercent);
    Serial.print("%   ");
    Serial.print("Throttle String = ");
    Serial.print(ThrottleString);
    Serial.println(" In For Loop ");
  }
}

FirstTensVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
TensCharacter = (FirstTensVariable/10); //Stroe the tens multiplier e.g. 5

SecondTensVariable = (TensCharacter*10); //Store the previous value times ten e.g. 50
ThirdTensVariable = (FirstTensVariable - SecondTensVariable); //store the remaining units e.g 58-50 = 8

ThirdTensVariableDuplicate = ThirdTensVariable; // Store the same value in a second variable for seperate calculations simultaneously.

//DecimalValue:
FirstDecimalVariable = ThrottlePercent; //Store the 0-100 value read from the potentiometer e.g. 58.67%
SecondDecimalVariable = ThrottlePercent; //Store the throttle value in an INT data type e.g. 58
ThirdDecimalVariable = (ThrottlePercent - SecondDecimalVariable); //Store just the decimal value e.g. 58.67 - 58 = .67
FourthDecimalVariable = (ThirdDecimalVariable * 10); //Store the decimal multiplier e.g. .67 * 10 = 6

 OnesCharacters = ""; //Clear the string
  while (ThirdTensVariable >= 1) //While the units value is >= 1
  { 
  ThirdTensVariable-= 1; //Decrease the units value by 1
  OnesCharacters+="+"; //Increase the OnesCharacters string by "+"
  }

 DecimalCharacters = ""; //Clear the string
  while (FourthDecimalVariable >= 1) //While the decimal units value is >= 1
  { 
  FourthDecimalVariable-= 1; //Decrease the units value by 1
  DecimalCharacters+="g"; //Increase the DecimalCharacters string by "+"
  }

 LessThanTenCharacters = ""; //Clear the string
  while (ThirdTensVariableDuplicate < 10) //While the units value is >= 1
  { 
  ThirdTensVariableDuplicate+= 1; //increase the units value by 1
  LessThanTenCharacters+="-"; //Increase the DecimalCharacters string by "+"
  }

if (ThrottlePercent >= 100.00 && ToggleSwitchValue == 1) 
  ThrottleString = (FullThrottleString + "f"); //"mf" will be sent, i.e. forward at 100%
  else if (ThrottlePercent == 0.00 || ToggleSwitchValue == 0) 
  ThrottleString = ("0"); //0% = 0
  else if (ThrottlePercent < 10.00 && ThrottlePercent > 0.00 && ToggleSwitchValue == 1)
  ThrottleString = (1 + LessThanTenCharacters + "f"); //e.g. 3.42% = "1-------f"
  else if (ToggleSwitchValue == 1)
  {
  ThrottleString = (TensCharacter + OnesCharacters + "f"); //e.g. 23.42% = "2+++ggggf"
  }

mySerial1.println(ThrottleString); //Send throttle value to motor
mySerial1.println("s"); //Send "s" so that the controller does not miss it upon start up.

mySerial2.println("0"); //Turn the motor off when the shield is looking at these software serial pins.
mySerial2.println("s"); //Send "s" so that the controller does not miss it upon start up. 

//Print the following values:
Serial.print("Throttle Percent = ");
Serial.print(ThrottlePercent);
Serial.print("%   ");
Serial.print("Throttle String = ");
Serial.println(ThrottleString);


delay(100); // Delay for stability

}


//interrupt service routine TimerISR
void TimerISR() //does this every 4 seconds
{ 
  TimerCounter ++; // count how many times this routine has been executed. 
}
