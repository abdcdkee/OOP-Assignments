#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <cstring>
#include <string>
#include <sstream>

#include "Box.h"


using namespace std;

Box::Box()
{
    length = rand()%26 + 5;     //Random value of length b/w 5 and 30 generated
    width = rand()%26 + 5;
    height = rand()%26 + 5;
}

int Box::Volume()
{
    return length*width*height;
}

string Box::GetDimensions() //Gives dimensions of the box in the form (A x B x C)
{
    string temp;
    stringstream temp1,temp2,temp3;
    temp1<<length;
    temp2<<width;
    temp3<<height;
    temp = "(" + temp1.str() + " x " + temp2.str() + " x " + temp3.str() + ")";
    return temp;
}

