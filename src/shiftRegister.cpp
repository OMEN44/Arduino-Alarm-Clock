#include "drivers.hpp"

ShiftRegister::ShiftRegister(int clockPin, int dataInPin, int latchPin)
{
    this->CLOCK = clockPin;
    this->DIN = dataInPin;
    this->LAT = latchPin;
    Serial.println("inside the shift init");
    for (int i = 0; i < 4; i++)
        pinMode(i + 2, OUTPUT);

    digitalWrite(DIN, LOW);
    digitalWrite(CLOCK, LOW);
    digitalWrite(LAT, LOW);

    for (int i = 0; i < 8; i++)
    {
        digitalWrite(CLOCK, HIGH);
        digitalWrite(CLOCK, LOW);
    }
    digitalWrite(LAT, HIGH);
    digitalWrite(LAT, LOW);
}

void ShiftRegister::shift8Bits(std::vector<bool> bits)
{

    for (int i = 0; i < 8; i++)
    {
        digitalWrite(DIN, bits[7 - i]);
        digitalWrite(CLOCK, HIGH);
        digitalWrite(CLOCK, LOW);
    }
    digitalWrite(LAT, HIGH);
    digitalWrite(LAT, LOW);
}