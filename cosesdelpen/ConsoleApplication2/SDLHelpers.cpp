#include "SDLHelpers.h"

/**
Define the most used colors
*/
SDL_Color WHITE = { 255, 255, 255, 0 };
SDL_Color BLACK = { 0, 0, 0, 0 };
SDL_Color RED = { 255, 0, 0, 0 };
SDL_Color BLUE = { 0, 0, 255, 0 };
SDL_Color GREEN = { 0, 255, 0, 0 };
SDL_Color YELLOW = { 255, 255, 0, 0 };
SDL_Color CYAN = { 0, 255, 255, 0 };
SDL_Color PINK = { 255, 0, 127, 0 };
SDL_Color ORANGE = { 255, 127, 0, 0 };
SDL_Color DCYAN = { 0, 127, 127, 0 };
SDL_Color GREY = { 63, 63, 63, 0 };
SDL_Color LTGREY = { 191, 191, 191, 0 };
SDL_Color DKBLUE = { 0, 0, 127, 0 };
SDL_Color DKRED = { 127, 0, 0, 0 };
SDL_Color DKGREEN = { 0, 127, 0, 0 };

SDLHelper::SDLHelper() {
	numberOfSurfaces = 0;
}

/*
Destructor, it frees memory and other sources
*/
SDLHelper::~SDLHelper() {
	for (int i = 0; i < numberOfSurfaces; i++) {
		SDL_FreeSurface(gSurfaces[i]);
	}
	delete[] gSurfaces;
	gSurfaces = 0;
}

/**
Initialize the video system
@param caption is the windows title
@param width is the windows width
@param height is the windows height
*/
void SDLHelper::InitializeVideo(char caption[100], int width, int height) {

	//Initialize the video system and the timer. Timer allows us to detect the number of milliseconds that have passed	since the program was started with the SDL_GetTicks
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_WM_SetCaption(caption, 0);

	//Set our at exit function
	atexit(SDL_Quit);

	//Set the video mode. O means default depth
	g_window = SDL_SetVideoMode(width, height, 0, SDL_ANYFORMAT);
}

//Set how many surfaces will be used in the game
void SDLHelper::setNumSurfaces(int numSurfaces) {
	numberOfSurfaces = numSurfaces;
	gSurfaces = new SDL_Surface *[numberOfSurfaces];
	if (gSurfaces == 0) {
		throw exception("System was not able to allocate memory for the surfaces");
	}
}

/**
Load the image and store into a surface object
*/
void SDLHelper::LoadImageintoSurface(int idSurface, char pathImage[200])	{
	gSurfaces[idSurface] = SDL_LoadBMP(pathImage);
	SDL_SetColorKey(gSurfaces[idSurface], SDL_SRCCOLORKEY, SDL_MapRGB(gSurfaces[idSurface]->format, 255, 0, 255));
}

/**
Draw a monster
@param x is the x-coordinate
@param y is the y-coordinate
*/
void SDLHelper::DrawSurface(int idSurface, int x, int y) {
	SDLBlit(gSurfaces[idSurface], g_window, x, y);
}

/**
Push the exit event into the system
*/
void SDLHelper::PushExitGameEvent() {
	SDL_Event quit;
	quit.type = SDL_QUIT;
	SDL_PushEvent(&quit);
}

/** Clear the screen to white
*/
void SDLHelper::ClearWindow() {
	SDL_FillRect(g_window, NULL, SDL_MapRGB(g_window->format, 255, 255, 255));
}

/**
Update the entire window.
*/
void SDLHelper::UpdateWindow() {
	SDL_UpdateRect(g_window, 0, 0, 0, 0);
}

/**
Draws a point on a surface
@param p_surface: surface to draw on
@param x, y: coordinates
@param p_color: the color of the point
@return None
*/
void SDLHelper::SDLPoint(SDL_Surface* p_surface, int x, int y, SDL_Color p_color) {
	Uint32 col = SDL_MapRGB(p_surface->format, p_color.r, p_color.g, p_color.b);
	static SDL_Rect rec;
	rec.w = 1;
	rec.h = 1;
	rec.x = x;
	rec.y = y;
	SDL_FillRect(p_surface, &rec, col);
}

/**
Draws a line on a surface
@param p_surface: surface to draw on
@param x1, y1: first point
@param x2, y2: second point
@param  p_color: color of the line
@return none
*/
void SDLHelper::SDLLine(SDL_Surface* p_surface, int x1, int y1, int x2, int y2, SDL_Color p_color)  {
	// lock the surface
	SDL_LockSurface(p_surface);

	// find distances of the line
	int x;
	float y;
	int dx = x2 - x1;
	int dy = y2 - y1;
	float m;

	// if the line is more wide than tall...
	if (abs(dx) > abs(dy))
	{
		// check to see if dx is negative. If so, 
		// then swap the coordinates.
		if (dx < 0)
		{
			dx = -dx;
			dy = -dy;
			x = x1;
			x1 = x2;
			x2 = x;
			x = y1;
			y1 = y2;
			y2 = x;
		}

		// find the slope and the beginning y coordinate
		m = (float)dy / (float)dx;
		y = (float)y1;

		// draw a point for each x
		for (x = x1; x <= x2; x++)
		{
			SDLPoint(p_surface, x, (int)y, p_color);
			y += m;
		}
	}
	else
	{
		// check to see if dy is negative. If so, 
		// then swap the coordinates.
		if (dy < 0)
		{
			dx = -dx;
			dy = -dy;
			x = x1;
			x1 = x2;
			x2 = x;
			x = y1;
			y1 = y2;
			y2 = x;
		}


		// find the slope and the beginning x coordinate
		m = (float)dx / (float)dy;
		y = (float)x1;


		// draw a point for each y
		for (x = y1; x <= y2; x++)
		{
			SDLPoint(p_surface, (int)y, x, p_color);
			y += m;
		}
	}

	// unlock the surface
	SDL_UnlockSurface(p_surface);
}

/**
Draws a line, with optional arrowheads
@param p_surface: surface to draw on
@param x1, y1: first point
@param x2, y2: second point
@param r1, r2: the radius of the points
@param arrow1, arrow2: determines if an arrow is drawn
@param p_color: color of the line
@return none
*/
void SDLHelper::SDLArrowLine(SDL_Surface* p_surface, int x1, int y1, int x2, int y2, int r1, int r2, bool arrow1, bool arrow2, SDL_Color p_color) {
	int tx1, ty1, tx2, ty2;

	// calculate distance from each point
	float dx = (float)(x2 - x1);
	float dy = (float)(y2 - y1);
	float d = (float)sqrt(dx * dx + dy * dy);

	// calculate the normal vector (dx, dy), and
	// the angle of that vector, a.
	float a;
	dx /= d;
	dy /= d;
	a = (float)acos(dx);

	// if dy is less than 0, then subtract the angle from 2PI
	if (dy < 0)
		a = 6.2832f - a;

	// calculate new coordinates (tx1,ty1) and (tx2,ty2) that are
	// r1 and r2 units away from the original points, along the
	// same line.
	tx1 = x1 + (int)((float)cos(a) * (float)r1);
	ty1 = y1 + (int)((float)sin(a) * (float)r1);
	tx2 = x2 + (int)((float)cos(a + 3.1416f) * (float)r2);
	ty2 = y2 + (int)((float)sin(a + 3.1416f) * (float)r2);

	// draw the line with the new coordinates
	SDLLine(p_surface, tx1, ty1, tx2, ty2, p_color);

	if (arrow1 == true)     {
		// calculate two lines that are 0.3 degrees away
		// from the real line, 15 pixels long, and draw them.
		// these two lines are the arrowhead.
		tx2 = tx1 + (int)((float)cos(a + 0.3f) * 15.0f);
		ty2 = ty1 + (int)((float)sin(a + 0.3f) * 15.0f);
		SDLLine(p_surface, tx1, ty1, tx2, ty2, p_color);
		tx2 = tx1 + (int)((float)cos(a - 0.3f) * 15.0f);
		ty2 = ty1 + (int)((float)sin(a - 0.3f) * 15.0f);
		SDLLine(p_surface, tx1, ty1, tx2, ty2, p_color);
	}
	if (arrow2 == true)     {
		// calculate two lines that are 0.3 degrees away
		// from the real line, 15 pixels long, and draw them.
		// these two lines are the arrowhead.
		a += 3.1416f;
		tx1 = x2 + (int)((float)cos(a) * (float)r2);
		ty1 = y2 + (int)((float)sin(a) * (float)r2);
		tx2 = tx1 + (int)((float)cos(a + 0.3f) * 15.0f);
		ty2 = ty1 + (int)((float)sin(a + 0.3f) * 15.0f);
		SDLLine(p_surface, tx1, ty1, tx2, ty2, p_color);
		tx2 = tx1 + (int)((float)cos(a - 0.3f) * 15.0f);
		ty2 = ty1 + (int)((float)sin(a - 0.3f) * 15.0f);
		SDLLine(p_surface, tx1, ty1, tx2, ty2, p_color);
	}
}

/**
Draws a surface on another surface
@param p_source: surface to draw from
@param p_dest: surface to draw on
@param x, y: coordinates
@return none
*/
void SDLHelper::SDLBlit(SDL_Surface* p_source, SDL_Surface* p_dest, int x, int y) {
	// make the rects static for speed.
	static SDL_Rect sourcerect;
	static SDL_Rect destrect;

	sourcerect.w = p_source->w;
	sourcerect.h = p_source->h;
	sourcerect.x = 0;
	sourcerect.y = 0;
	destrect.w = p_source->w;
	destrect.h = p_source->h;
	destrect.x = x;
	destrect.y = y;
	SDL_BlitSurface(p_source, &sourcerect, p_dest, &destrect);
}

/**
Draws a solid box on a surface
@param p_surface: surface to draw on
@param x, y: coordinates
@param width, height: width and height of the box
@param p_color: color of the box
@return none
*/
void SDLHelper::SDLBox(SDL_Surface* p_surface, int x, int y, int w, int h, SDL_Color p_color) {
	static SDL_Rect rect;
	Uint32 col = SDL_MapRGB(p_surface->format, p_color.r, p_color.g, p_color.b);

	rect.w = w;
	rect.h = h;
	rect.x = x;
	rect.y = y;
	SDL_FillRect(p_surface, &rect, col);
}