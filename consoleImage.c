#include <stdio.h>
#include <math.h>
#include "windows.h"
#include "consoleColor.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char** argv)
{
    int desiredWidth = 200;
    int desiredHeight = 200;
    int width, height, channels;
    unsigned char* data;
    char* imagePath;
    const char* ERROR_MSG = "Use the following format: ConsoleImage.exe [image-name].[extension] [desired-width] [desired-height]\nExample: ConsoleImage.exe myImage.jpg 100 100\nIf width and height are not specified, a default value will be used.";

    switch(argc)
    {
        case 4:
            desiredWidth = atoi(argv[2]);
            desiredHeight = atoi(argv[3]);

            if(desiredWidth == 0 || desiredHeight == 0)
            {
                printf("Invalid desired width or desired height arguments.\n%s\n", ERROR_MSG);
                return 1;
            }
        case 2:
            imagePath = argv[1];
            break;

        default:
            printf("Invalid number of arguments.\n%s\n", ERROR_MSG);
            return 1;
    }

    data = stbi_load(imagePath, &width, &height, &channels, 3);

    if(data != NULL)
    {
        int count = 0;
        int widthSkip = ceil((double)(width - desiredWidth) / (double)desiredWidth);
        int heightSkip = ceil((double)(height - desiredHeight) / (double)desiredHeight);

        if(widthSkip < 0)
        {
            widthSkip = 0;
        }
        if(heightSkip < 0)
        {
            heightSkip = 0;
        }

        for(int h = 0; h < height; h++)
        {
            for(int w = 0; w < width; w++)
            {
                unsigned char red, green, blue;

                red = data[count++];
                green = data[count++];
                blue = data[count++];

                if((w + widthSkip) >= width)
                {
                    int remainingWidth = width - (w + 1);
                    w = width;
                    count += (3 * remainingWidth);
                }
                else
                {
                    w += widthSkip;
                    count += (3 * widthSkip);
                }

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), closestColor(red, green, blue));
                printf(" ");
            }

            h += heightSkip;
            count += (width * 3) * heightSkip;
            printf("\n");
        }
    }
    else
    {
        printf("ERROR: File could not be read\n");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); //set console to default state
    return 0;
}