#include "consoleColor.h"

int colorDifference(unsigned char red, unsigned char green, unsigned char blue, CONSOLE_COLOR cc)
{
    int redDiff = std::abs(red - cc.red);
    int greenDiff = std::abs(green - cc.green);
    int blueDiff = std::abs(blue - cc.blue);

    return redDiff + greenDiff + blueDiff;
}

WORD closestColor(unsigned char red, unsigned char green, unsigned char blue)
{
    int closest = 0;
    int difference = colorDifference(red, green, blue, ConsoleColors[0]);

    for(int i = 1; i < (sizeof(ConsoleColors) / sizeof(CONSOLE_COLOR)); i++)
    {
        int newDiff = colorDifference(red, green, blue, ConsoleColors[i]);
        if(newDiff < difference)
        {
            closest = i;
            difference = newDiff;
        }
    }

    return ConsoleColors[closest].flags;
}