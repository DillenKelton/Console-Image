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
#define BACKGROUND_PINK BACKGROUND_RED | BACKGROUND_INTENSITY
#define BACKGROUND_LIGHTGREEN BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define BACKGROUND_LIGHTBLUE BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUND_LIGHTPURPLE BACKGROUND_PURPLE | BACKGROUND_INTENSITY
#define BACKGROUND_LIGHTCYAN BACKGROUND_CYAN | BACKGROUND_INTENSITY
#define BACKGROUND_LIGHTYELLOW BACKGROUND_YELLOW | BACKGROUND_INTENSITY
#define BACKGROUND_LIGHTWHITE BACKGROUND_WHITE | BACKGROUND_INTENSITY
#define BACKGROUND_GREY BACKGROUND_BLACK | BACKGROUND_INTENSITY

struct CONSOLE_COLOR
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    WORD flags;
} const ConsoleColors[] = {
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
    { 118, 118, 118, BACKGROUND_GREY }
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