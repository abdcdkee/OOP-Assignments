#include "Line.h"


//Draws the line
void Line::Draw(SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, GetRed(), GetGreen(), GetBlue(), 0xFF);
    SDL_RenderDrawLine( gRenderer, GetStartPoint().x, GetStartPoint().y, GetEndPoint().x, GetEndPoint().y );
}
