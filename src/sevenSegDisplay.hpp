#pragma once
#include <vector>
#include <Arduino.h>

class SevenSegDisplay
{
public:
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

private:
};