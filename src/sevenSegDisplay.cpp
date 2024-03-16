#include <sevenSegDisplay.hpp>
#include <Arduino.h>

SevenSegDisplay::SevenSegDisplay()
{
    for (int i = 2; i < 13; i++)
    {
        pinMode(i, OUTPUT);
        if (i < 6)
            digitalWrite(i, LOW);
        else
            digitalWrite(i, HIGH);
    }
}

void SevenSegDisplay::selectDigit(char number)
{
    for (int i = 2; i < 6; i++)
    {
        if (number + 2 == i)
            digitalWrite(i, HIGH);
        else
            digitalWrite(i, LOW);
    }
}

void SevenSegDisplay::setDigit(std::vector<bool> digit, int index)
{
    selectDigit(index);
    for (int i = 0; i < digit.size(); i++)
    {
        digitalWrite(i + 6, digit[i] ? LOW : HIGH);
        digitalWrite(i + 6, HIGH);
    }
}

void SevenSegDisplay::displayNumber(int value)
{
    String valueString = String(value);
    char cString[4];
    for (int j = 0, i = 0; i < 4; i++)
    {
        if (i < 4 - valueString.length())
            cString[i] = ' ';
        else
        {
            cString[i] = valueString[j];
            j++;
        }
    }
    displayNumber(cString);
}

void SevenSegDisplay::displayNumber(const char value[4])
{

    bool sigFig = false;
    for (int i = 0; i < 4; i++)
    {
        int digit = (int)value[i] - 48;
        if (isSingleDigit(digit))
        {
            setDigit(numbers[digit], i);
            sigFig = false;
        }
    }
}