#include <Arduino.h>
#include "drivers.hpp"
#include <StandardCplusplus.h>
#include <vector>

// sudo chmod a+rw /dev/ttyACM0

void checkButtons();
int calculateTime();

SevenSegDisplay display;

void setup()
{
  display.useShiftRegister(true);
  Serial.begin(9600);
  while (!Serial)
  {
  }

  pinMode(9, INPUT);   // Hour button
  pinMode(10, INPUT);  // Min button
  pinMode(12, INPUT);  // Function button
  pinMode(13, OUTPUT); // Buzzer
}

void loop()
{
  checkButtons();
  display.displayNumber(calculateTime());
}

// Time functions

int hour = 12, min = 0;
unsigned long currentMillis, previousMillis = 0;

int calculateTime()
{
  currentMillis = millis();

  if (currentMillis - previousMillis >= 60000)
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
  return min + (hour * 100);
}

// Buttons functions

bool hourBtnPress = false, minBtnPress = false;

void checkButtons()
{
  if (digitalRead(9) == HIGH && !hourBtnPress)
    hour = hour >= 23 ? 0 : 1 + hour;
  if (digitalRead(10) == HIGH && !minBtnPress)
    min = min >= 59 ? 0 : 1 + min;

  hourBtnPress = digitalRead(9) == LOW ? false : true;
  minBtnPress = digitalRead(10) == LOW ? false : true;
}