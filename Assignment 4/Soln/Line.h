#pragma once
#include"SDL.h"
#include"Shape.h"


class Line: public Shape
{
public:
    void Draw(SDL_Renderer* gRenderer);
};
