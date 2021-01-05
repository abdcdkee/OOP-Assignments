#include "Shape.h"


void Shape::SetStartPoint(Point temp)
{
    startPoint.x = temp.x;
    startPoint.y = temp.y;
}

void Shape::SetEndPoint(Point temp)
{
    endPoint.x = temp.x;
    endPoint.y = temp.y;
}

Point Shape::GetStartPoint()
{
    return startPoint;
}

Point Shape::GetEndPoint()
{
    return endPoint;
}

int Shape::GetRed()
{
    return color.red;
}

int Shape::GetGreen()
{
    return color.green;
}

int Shape::GetBlue()
{
    return color.blue;
}

void Shape::SetDimensions()
{}

void Shape::Draw(SDL_Renderer* gRenderer)
{}
