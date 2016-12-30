#include <string>
#include <math.h>
#include <application.h>

SYSTEM_MODE(MANUAL);

void timerTick();
Timer timer(100, timerTick);

#define PI 3.141592654
#define HALF_PI PI/2.0
#define PIX2 PI*2

double cycleCounter1 = HALF_PI;
double cycleCounter2 = HALF_PI;
double cycleCounter3 = 0.1;

void setup() 
{
  // Save power
  WiFi.off();

  // Establish serial connection
  Serial.begin(9600);

  randomSeed(micros());

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  timer.start();
}

void loop()
{
}

int enterDFU()
{
  System.dfu();
  return 0;
}

void timerTick()
{
  double step = 0.005 * random(1,20);
  cycleCounter1 += step;
  if (cycleCounter1 > PIX2)
    cycleCounter1 = 0.1;
  
  cycleCounter2 += step;
  if (cycleCounter2 > PIX2)
    cycleCounter2 = 0.1;
  
  cycleCounter3 += 0.05;
  if (cycleCounter3 > PIX2)
    cycleCounter3 = 0.1;

  double sinVal1 = sin(cycleCounter1) + 1.0;
  double sinVal2 = sin(cycleCounter2) + 1.0;
  double sinVal3 = sin(cycleCounter3) + 1.0;

  analogWrite(D0, int(sinVal1*80) + 50);
  analogWrite(D1, int(sinVal2*60) + 30);
  analogWrite(D2, random(1,100) == 1 ? 0 : random(150, 200));
}

void serialEvent()
{
  char c = Serial.read();
  if (c == 'D')
  {
    enterDFU();
    return;
  }
}

