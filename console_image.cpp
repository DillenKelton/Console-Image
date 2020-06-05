#include <iostream>
#include <cstdlib>
#include "windows.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define BACKGROUND_PURPLE BACKGROUND_BLUE | BACKGROUND_RED
#define BACKGROUND_CYAN BACKGROUND_BLUE | BACKGROUND_GREEN
#define BACKGROUND_YELLOW BACKGROUND_RED | BACKGROUND_GREEN
#define BACKGROUND_WHITE BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN
#define BACKGROUND_BLACK 0

struct CONSOLE_COLOR
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    WORD flags;
} const ConsoleColors[] = {
    { 255, 0, 0, BACKGROUND_RED },
    { 0, 255, 0, BACKGROUND_GREEN },
    { 0, 0, 255, BACKGROUND_BLUE },
    { 255, 0, 255, BACKGROUND_PURPLE },
    { 0, 255, 255, BACKGROUND_CYAN },
    { 255, 255, 0, BACKGROUND_YELLOW },
    { 255, 255, 255, BACKGROUND_WHITE },
    { 0, 0, 0, BACKGROUND_BLACK }
};

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

int main(int argc, char** argv)
{
    int width, height, channels;
    unsigned char* data;
    char* imagePath;

    if(argc > 1)
    {
        imagePath = argv[1];
        data = stbi_load(imagePath, &width, &height, &channels, 3);

        if(data != NULL)
        {
            int count = 0;

            for(int h = 0; h < height; h += 3)
            {
                for(int w = 0; w < width; w += 3)
                {
                    unsigned char red, green, blue;

                    red = data[count++];
                    green = data[count++];
                    blue = data[count++];

                    count += 6;

                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), closestColor(red, green, blue));
                    std::cout << " ";
                }

                count += (width * 3) * 2;

                std::cout << std::endl;
            }
        }
        else
        {
            std::cout << "ERROR: File could not be read" << std::endl;
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); //set console to default state
    return 0;
}