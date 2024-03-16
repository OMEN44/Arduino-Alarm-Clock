#include <Arduino.h>
#include "drivers.hpp"
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
  display.useShiftRegister(true);
  // digit select must be high to select and segment pin must be low to enable
  pinMode(13, OUTPUT);
}

int hour = 16, min = 11;
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
    }
  }

  display.displayNumber(min + (hour * 100));
}