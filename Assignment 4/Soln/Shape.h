#pragma once
#include"SDL.h"
#include"Point.h"
#include"Color.h"


class Shape
{
private:
    Point startPoint;
    Point endPoint;
    Color color;

public:
    int GetRed();
    int GetGreen();
    int GetBlue();
    virtual void SetStartPoint(Point);
    virtual void SetEndPoint(Point);
    virtual Point GetStartPoint();
    virtual Point GetEndPoint();

    //Functions below are declared but not defined since they are different for all child classes
    virtual void SetDimensions();
    virtual void Draw(SDL_Renderer*);
};
