#include <Arduino.h>
#include "sevenSegDisplay.hpp"
#include <StandardCplusplus.h>
#include <vector>

// sudo chmod a+rw /dev/ttyACM0

SevenSegDisplay display;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    // wait for serial conn
  }

  Serial.println();
  Serial.println();
  Serial.println();

  // put your setup code here, to run once:
  for (int i = 2; i < 13; i++)
  {
    pinMode(i, OUTPUT);
    if (i < 6)
      digitalWrite(i, LOW);
    else
      digitalWrite(i, HIGH);
  }

  // digit select must be high to select and segment pin must be low to enable
}

// bool setTime = false;
int hour = 10, min = 24;
unsigned long currentMillis, previousMillis = 0;
const long interval = 60000;

void loop()
{

  currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you updated the time
    previousMillis = currentMillis;

    // update the current time
    min++;
    if (min >= 60)
    {
      min = 0;
      hour = hour >= 23 ? 0 : 1 + hour;
      Serial.println(min + (hour * 100));
    }
  }

  display.displayNumber(min + (hour * 100));
}