//code write by Moz for YouTube changel LogMaker360 https://www.youtube.com/watch?v=U6FLgeLV3j8
//10-05-2016 


#include <TimerOne.h>

int motherLoopLedBlue = 7;
int timerInterruptLed = 8;

volatile boolean onOrOff = LOW;        // set led on or off inside the ISR
volatile unsigned long functionCounter = 0; // count how many times the function is called

volatile int Variable = 0;

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
  Serial.println(Variable);

  digitalWrite(motherLoopLedBlue, LOW);
  delay(100);
}

//interrupt service routine function
void function() //does this every 4 seconds
{ 
  for (Variable = 0; Variable < 10; Variable++)
  {
  Serial.print(Variable);
  Serial.println("  In the timer loop ");
  }
}
