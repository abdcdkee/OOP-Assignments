/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <iostream>

//Including header files
#include"Rect.h"
#include"Color.h"
#include"Stack.h"
#include"Shape.h"
#include"Line.h"

using namespace std;


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Draws shape as the mouse is pressed and being dragged across the screen
void DrawTempShape(SDL_Renderer* gRenderer, Shape* tempShape);

bool init()
{
	//Initialization mouseClicked
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success mouseClicked
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

int main( int argc, char* args[] )
{
    srand(time(0));
	Stack buildStack;
	Stack undoStack;

    //Start up SDL and create window

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )  //Load media
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;  //Main loop controlled
			SDL_Event e;        //Event handler that takes care of all events

			bool mouseClicked = false;      //True when mouse is clicked for the first time
            bool pressLeft = true;          //True for the duration when mouse button is pressed
            bool pressShift = false;
            bool shiftReleased = true;
            bool leftButtonMotion = true;   //True when mouse button is pressed and mouse is moving
            bool releaseLeft = true;        //True when mouse button is not being pressed

/*Default*/ bool makeRect = true;           //True when program is supposed to render rectangles
            bool makeLine = false;          //True when program is supposed to render lines
            bool tempDraw = false;          //True when mouse is pressed and being dragged across screen

            Shape* tempShape;               //Stores shape object as mouse is clicked and dragged across screen
                                            //Is appended to buildStack when mouse button is released
            //Components of topLeft
			int oldx = 0;
            int oldy = 0;
            Point topLeft;                  //Stores start point of object
            Point bottomRight;              //Stores end point of object

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

                    //Considers the situation when Shift is pressed and released without pressing plus
					if (e.type == SDL_KEYUP && !mouseClicked)
                    {
                        if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym==SDLK_RSHIFT)
                            shiftReleased = true;
                    }


                    //Considers Keyboard events
                    if (e.type == SDL_KEYDOWN && !mouseClicked)
                    {
                        //Calls MoveOut function if shift and plus keys are pressed simultaneously
                        if (pressShift && shiftReleased==false)
                        {
                            if (e.key.keysym.sym == SDLK_EQUALS && !buildStack.IsEmpty())
                                buildStack.MoveOut();
                            else
                                pressShift = false;
                        }

                        //Switches program to rendering rectangles
                        if (e.key.keysym.sym == SDLK_r)
                        {
                            makeRect = true;
                            makeLine = false;
                        }

                        //Switches program to rendering lines
                        else if (e.key.keysym.sym == SDLK_l)
                        {
                            makeRect = false;
                            makeLine = true;
                        }

                        //Calls MoveDeep function if '-' key is pressed
                        else if (e.key.keysym.sym == SDLK_MINUS && !buildStack.IsEmpty())
                        {
                            buildStack.MoveDeep();
                        }

                        //Considers when right or left shift has been pressed just before plus is pressed
                        else if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT)
                        {
                            pressShift = true;
                            shiftReleased = false;
                        }
                    }

                    //Considers Mouse button events
					if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                    {
                        //Right mouse button is clicked
                        if (e.button.button == SDL_BUTTON_RIGHT)
                        {
                            //Element is removed from buildStack and pushed to undoStack
                            if (e.type == SDL_MOUSEBUTTONDOWN && !buildStack.IsEmpty())
                            {
                                Shape* temp = buildStack.Pop();
                                if (temp!=NULL)
                                {
                                    undoStack.Append(temp);
                                }
                            }
                        }

                        //Mouse middle button is present
                        else if (e.button.button == SDL_BUTTON_MIDDLE)
                        {
                            //Pops element from the undoStack and pushes it to buildStack
                            if (e.type == SDL_MOUSEBUTTONDOWN && !undoStack.IsEmpty())
                            {
                                Shape* temp = undoStack.Pop();
                                if (temp!=NULL)
                                {
                                    buildStack.Append(temp);
                                    buildStack.SetPos(true);
                                }
                            }
                        }

                        //Left mouse button is pressed
                        else if (e.button.button == SDL_BUTTON_LEFT)
                        {
                            int x, y;
                            SDL_GetMouseState( &x, &y );

                            if(e.type == SDL_MOUSEMOTION)
                            {
                                //Mouse button is pressed and mouse is moving
                                if(oldx!=x && oldy!=y && mouseClicked && pressLeft && !releaseLeft)
                                {
                                    //undoStack deleted when new object being created
                                    if (!undoStack.IsEmpty())
                                    {
                                        undoStack.Delete();
                                    }

                                    tempDraw = true;
                                    leftButtonMotion = true;

                                    //Changes EndPoint of shape as the mouse moves
                                    bottomRight.SetPoint(x,y);
                                    tempShape->SetEndPoint(bottomRight);

                                    //Sets rectangle dimensions
                                    if (makeRect)
                                    {
                                        tempShape->SetDimensions();
                                    }
                                }
                            }
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                releaseLeft = false;
                                leftButtonMotion = false;

                                //Sets oldx//oldy values when mouse button is clicked for the first time
                                if(!mouseClicked)
                                {
                                    pressLeft = true;
                                    mouseClicked = true;
                                    oldx = x;
                                    oldy = y;
                                }

                                //Creates tempShape that can be rendered on screen as mouse is pressed and dragged
                                if ((oldx!=x && oldy!=y) || pressLeft)
                                {
                                    if (makeLine)
                                        tempShape = new Line;
                                    if (makeRect)
                                        tempShape = new Rect;

                                    topLeft.SetPoint(oldx,oldy);
                                    bottomRight.SetPoint(x,y);
                                    tempShape->SetStartPoint(topLeft);
                                    tempShape->SetEndPoint(bottomRight);

                                    if (makeRect)
                                        tempShape->SetDimensions();
                                }
                            }

                            if(e.type == SDL_MOUSEBUTTONUP)
                            {
                                releaseLeft = true;
                                mouseClicked = false;

                                //Appends tempShape to stack when mouse button has been pressed,dragged across
                                //the screen, and released
                                if (oldx!=x && oldy!=y && leftButtonMotion && pressLeft)
                                {
                                    buildStack.Append(tempShape);
                                    buildStack.SetPos(true);
                                    tempDraw = false;
                                    pressLeft = false;
                                    leftButtonMotion = false;
                                }
                            }
                        }
                    }
				}

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                //Draws shape as mouse is pressed and being dragged across the screen
                if (tempDraw)
                    DrawTempShape(gRenderer, tempShape);

                //Draws all elements in the stack if it's not empty
                if (!buildStack.IsEmpty())
                    buildStack.DrawAll(gRenderer);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
			//Frees dynamic memory
			if (tempShape!=NULL)
                delete tempShape;
		}
	}
	//Free resources and close SDL
    close();
	return 0;
}

//Draws shape as mouse is pressed and being dragged across the screen
void DrawTempShape(SDL_Renderer* gRenderer, Shape* tempShape)
{
    SDL_SetRenderDrawColor(gRenderer, tempShape->GetRed(), tempShape->GetGreen(), tempShape->GetBlue(), 0xFF);
    tempShape->Draw(gRenderer);
}
