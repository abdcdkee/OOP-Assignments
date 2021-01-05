#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma once
#include <string>

using namespace std;


class Box
{
    private:
        int length;
        int width;
        int height;

    public:
        Box();
        int Volume();
        string GetDimensions();
};


