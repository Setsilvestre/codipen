#pragma once
using namespace std;
#include "SDL.h"
#include "SDL_ttf.h"
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <exception>

/*
// ============================================================================
// SDL structures
// ============================================================================
SDL_Surface: It is really just a bitmap. These structures can hold bitmaps in any format, and the SDL drawing routines will draw them correctly.
SDL_Rects: It is a rectangles. These are often used in the drawing functions to define the source and destination areas. They have four variables: an x and a y coordinate and a width and a height.
SDL_PixelFormat: It defines the exact format that a surface is in, in case you ever need to do any image editing or converting.
SDL_Color: It is a simple structure that stores a single color value
*/

/*
// ============================================================================
// SDL constants
// ============================================================================
SDL_ANYFORMAT flag means that SDL should use the best format it can find.
*/

class SDLHelper {
	//SDL structures
	SDL_Surface* g_window = 0;		// this is the main window for the framework	
	SDL_Surface * * gSurfaces = 0;	// the monster bitmaps
	int numberOfSurfaces;

	//SDL event
	SDL_Event event;

public:
	//Initialize all the elements related to the SDL_Helper class
	SDLHelper();
	//Destructor, it frees memory and other sources
	~SDLHelper();
	//Prepare the video mode
	void InitializeVideo(char caption[100], int width, int height);
	//Set how many surfaces will be used in the game
	void setNumSurfaces(int numSurfaces);
	//Load the image and store into a surface object
	void LoadImageintoSurface(int idSurface, char path[200]);
	//Draw the specified surface in a specific position
	void DrawSurface(int idSurface, int x, int y);
	//Get the width of the monster bitmap
	inline int GetSurfaceWitdh(int idSurface) { return gSurfaces[idSurface]->w; };
	//Get the height of the monster bitmap
	inline int GetSurfaceHeight(int idSurface) { return gSurfaces[idSurface]->h; };
	//Detect if some event has occurred
	inline int AnyEvent() { return SDL_PollEvent(&event); };
	//Get the event type
	inline int GetEventType() { return (int)event.type; };
	//Get the key that originated the event. Check the "sdl_keysym.h" at SDL source code to know the different key values
	inline int GetKeyType() { return (int)event.key.keysym.sym; };
	//Activate the exit event
	void PushExitGameEvent();
	//Clear all the window information
	void ClearWindow();
	//Update the window information with the changes do
	void UpdateWindow();
	//Draws a point on a surface
	void SDLPoint(SDL_Surface* p_surface, int x, int y, SDL_Color p_color);
	//Draws a line on a surface
	void SDLLine(SDL_Surface* p_surface, int x1, int y1, int x2, int y2, SDL_Color p_color);
	//Draws a line, with optional arrowheads
	void SDLArrowLine(SDL_Surface* p_surface, int x1, int y1, int x2, int y2, int r1, int r2, bool arrow1, bool arrow2, SDL_Color p_color);
	//Draws a surface on another surface
	void SDLBlit(SDL_Surface* p_source, SDL_Surface* p_dest, int x, int y);
	//Draws a solid box on a surface
	void SDLBox(SDL_Surface* p_surface, int x, int y, int width, int height, SDL_Color p_color);
};
