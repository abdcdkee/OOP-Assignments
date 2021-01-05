#pragma once
#include"SDL.h"
#include"Point.h"
#include"Shape.h"
#include"Color.h"


class Rect: public Shape
{
private:
    SDL_Rect* fillRect;

public:
    void SetDimensions();
    void Draw(SDL_Renderer* gRenderer);
};

