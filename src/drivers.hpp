#pragma once
#include <vector>
#include <Arduino.h>

class ShiftRegister
{
private:
    const int CLOCK;
    const int DIN;
    const int LAT;

public:
    ShiftRegister(int clockPin, int dataInPin, int latchPin);
    void shift8Bits(std::vector<bool> bits);
};

class SevenSegDisplay
{
public:
    SevenSegDisplay();
    void selectDigit(char number);
    void setDigit(std::vector<bool> digit, int index);
    void displayNumber(int value);
    void displayNumber(const char value[4]);

    static bool isSingleDigit(int value)
    {
        return (value < 10 && value > -1);
    }

    std::vector<std::vector<bool>> numbers = {
        {1, 1, 1, 1, 1, 1, 0},  // 0
        {0, 1, 1, 0, 0, 0, 0},  // 1
        {1, 1, 0, 1, 1, 0, 1},  // 2
        {1, 1, 1, 1, 0, 0, 1},  // 3
        {0, 1, 1, 0, 0, 1, 1},  // 4
        {1, 0, 1, 1, 0, 1, 1},  // 5
        {1, 0, 1, 1, 1, 1, 1},  // 6
        {1, 1, 1, 0, 0, 0, 0},  // 7
        {1, 1, 1, 1, 1, 1, 1},  // 8
        {1, 1, 1, 1, 0, 1, 1}}; // 9
};