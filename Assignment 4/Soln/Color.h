#pragma once
#include <time.h>
#include <stdlib.h>


struct Color
{
    int red;
    int green;
    int blue;

    //Randomizes color when object is created
    Color()
    {
        red = rand()%256;
        green = rand()%256;
        blue = rand()%256;
    }
};
