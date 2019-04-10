//code write by Moz for YouTube changel LogMaker360 https://www.youtube.com/watch?v=U6FLgeLV3j8
//10-05-2016 


#include <TimerOne.h>

int motherLoopLedBlue = 7;
int timerInterruptLed = 8;

volatile boolean onOrOff = LOW;        // set led on or off inside the ISR
volatile unsigned long functionCounter = 0; // count how many times the function is called

unsigned int motherLoopCounter = 0; // to pick up the value of the function loop

void setup() 
{  
  pinMode(timerInterruptLed, OUTPUT);
  pinMode(motherLoopLedBlue, OUTPUT);
  Timer1.initialize(4000000); // 4 million microseconds is 4 seconds
  //Timer runs every two seconds and does the following function
  Timer1.attachInterrupt(function);
  Serial.begin(115200);
}

void loop() 
{
  noInterrupts();
  motherLoopCounter =  functionCounter;
  interrupts();
  Serial.print("Mother Loop LED = ");
  Serial.print(motherLoopLedBlue);
  Serial.print("  LED value = ");
  Serial.println(onOrOff);

 if(motherLoopCounter == 12)
  {
  functionCounter = 0; 
  }

  //digitalWrite(motherLoopLedBlue, HIGH);
  //delay(500);
  digitalWrite(motherLoopLedBlue, LOW);
  delay(100);
}

//interrupt service routine function
void function() //does this every 4 seconds
{  
  //digitalWrite(timerInterruptLed, onOrOff);
  //onOrOff =! onOrOff;
  //functionCounter  ++;
  Serial.println("  In the timer loop ");
}
