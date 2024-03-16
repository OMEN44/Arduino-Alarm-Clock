#include <drivers.hpp>

bool SevenSegDisplay::useShiftRegister()
{
    return this->usingShiftRegister;
}

bool SevenSegDisplay::useShiftRegister(bool toggle)
{
    if (toggle)
        this->shiftRegister = new ShiftRegister(3, 2, 4);
    else
        delete this->shiftRegister;
    this->usingShiftRegister = toggle;
    return this->usingShiftRegister;
}

SevenSegDisplay::SevenSegDisplay()
{
    if (this->usingShiftRegister)
    {
        for (int i = 5; i < 9; i++)
        {
            pinMode(i, OUTPUT);
            digitalWrite(i, LOW);
        }
    }
    else
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
}

void SevenSegDisplay::selectDigit(char number)
{
    for (int i = 5; i < 9; i++)
    {
        if (number + 5 == i)
            digitalWrite(i, HIGH);
        else
            digitalWrite(i, LOW);
    }
}

void SevenSegDisplay::setDigit(std::vector<bool> digit, int index)
{
    if (!usingShiftRegister)
    {
        selectDigit(index);
        for (int i = 0; i < (int)digit.size(); i++)
        {
            digitalWrite(i + 6, digit[i] ? LOW : HIGH);
            digitalWrite(i + 6, HIGH);
        }
    }
    else
    {
        std::vector<bool> data;
        selectDigit(index);
        for (int i = 0; i < 8; i++)
        {
            data.push_back(digit[i] ? false : true);
        }
        this->shiftRegister->shift8Bits(data);
        this->shiftRegister->shift8Bits({true, true, true, true, true, true, true});
    }
}

void SevenSegDisplay::displayNumber(int value)
{
    String valueString = String(value);
    char cString[4];
    for (int j = 0, i = 0; i < 4; i++)
    {
        if (i < (int)(4 - valueString.length()))
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
    for (int i = 0; i < 4; i++)
    {
        int digit = (int)value[i] - 48;
        if (isSingleDigit(digit))
        {
            setDigit(numbers[digit], i);
        }
    }
}