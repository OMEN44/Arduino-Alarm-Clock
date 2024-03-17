#include <Arduino.h>
#include "drivers.hpp"
#include <StandardCplusplus.h>
#include <vector>

// sudo chmod a+rw /dev/ttyACM0

void checkButtons();

SevenSegDisplay display;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    // wait for serial conn
  }
  display.useShiftRegister(true);

  pinMode(9, INPUT);   // button
  pinMode(10, INPUT);  // button
  pinMode(11, OUTPUT); // buzzer
}

int hour = 12, min = 0;
unsigned long currentMillis, previousMillis = 0;
const long interval = 60000;
bool hourBtnPress = false, minBtnPress = false;

void loop()
{

  if (digitalRead(9) == HIGH && !hourBtnPress)
  {
    hourBtnPress = true;
    if (hour >= 23)
      hour = 0;
    else
      hour++;
  }
  if (digitalRead(10) == HIGH && !minBtnPress)
  {
    minBtnPress = true;
    if (min >= 59)
      min = 0;
    else
      min++;
  }
  if (digitalRead(9) == LOW)
    hourBtnPress = false;
  if (digitalRead(10) == LOW)
    minBtnPress = false;
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