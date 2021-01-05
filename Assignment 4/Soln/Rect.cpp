#include"Rect.h"
#include"Shape.h"


//Sets the start and end point of the rectangle
void Rect::SetDimensions()
{
    fillRect = new SDL_Rect;
    fillRect->x = GetStartPoint().x;
    fillRect->y = GetStartPoint().y;
    fillRect->w = GetEndPoint().x-GetStartPoint().x;
    fillRect->h = GetEndPoint().y-GetStartPoint().y;
}

//Draws the rectangle and also defines its color
void Rect::Draw(SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, GetRed(), GetGreen(), GetBlue(), 0xFF);
    SDL_RenderFillRect( gRenderer, fillRect );
}

