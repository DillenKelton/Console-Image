#include "consoleColor.h"

const struct CONSOLE_COLOR ConsoleColors[] = {
    { 197, 15, 31, BACKGROUND_RED },
    { 19, 161, 14, BACKGROUND_GREEN },
    { 0, 55, 218, BACKGROUND_BLUE },
    { 136, 23, 152, BACKGROUND_PURPLE },
    { 58, 150, 221, BACKGROUND_CYAN },
    { 193, 156, 0, BACKGROUND_YELLOW },
    { 204, 204, 204, BACKGROUND_WHITE },
    { 12, 12, 12, BACKGROUND_BLACK },
    { 231, 72, 86, BACKGROUND_PINK },
    { 22, 198, 12, BACKGROUND_LIGHTGREEN },
    { 59, 120, 255, BACKGROUND_LIGHTBLUE },
    { 180, 0, 158, BACKGROUND_LIGHTPURPLE },
    { 97, 214, 214, BACKGROUND_LIGHTCYAN },
    { 249, 241, 165, BACKGROUND_LIGHTYELLOW },
    { 242, 242, 242, BACKGROUND_LIGHTWHITE },
//    { 118, 118, 118, BACKGROUND_GREY }
};

int colorDifference(unsigned char red, unsigned char green, unsigned char blue, struct CONSOLE_COLOR cc)
{
    int redDiff = abs(red - cc.red);
    int greenDiff = abs(green - cc.green);
    int blueDiff = abs(blue - cc.blue);

    return redDiff + greenDiff + blueDiff;
}

WORD closestColor(unsigned char red, unsigned char green, unsigned char blue)
{
    int closest = 0;
    int difference = colorDifference(red, green, blue, ConsoleColors[0]);

    for(int i = 1; i < (sizeof(ConsoleColors) / sizeof(struct CONSOLE_COLOR)); i++)
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