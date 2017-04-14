// CSDLGraphics.h - Headers for CSDLGraphics.cpp
#ifndef INC_CSDLGRAPHICS_H
#define INC_CSDLGRAPHICS_H
// SDL library
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
// Font library used for graphical text output
#include "SDL/SDL_ttf.h"
#include <iostream>
#include "Globals.h"

// CSDL initialises SDL graphical component.
class __declspec(dllexport) CSDLGraphics
{
public:
	CSDLGraphics();
	~CSDLGraphics();

	// Load an image from a file with type *.png, *.jpg, *.bmp 
	SDL_Surface* loadImageFromFile( std::string filename, Uint8 r, Uint8 g, Uint8 b );
	
	// Returns a Uint32 pixel colour from a given surface and coord 
	Uint32 getColor(SDL_Surface * surface, int x, int y);

	// Sets a given pixel on a surface to a particular color
	void putColor(SDL_Surface *surface, int x, int y, Uint32 color);

	// Fil the given rectangle with the given colour
	void fillRect( unsigned int x, unsigned int y, unsigned int width, unsigned int height, 
			unsigned int r, unsigned int g, unsigned int b);
	
	// Clears the screen to one colour
	void clearScreen(UINT r, UINT g, UINT b);
	
	// Draws an image based on given data
	void draw(int x, int y , SDL_Surface* srcimage, SDL_Surface * destSurface, SDL_Rect* cliprect);	

	// Draw text with given font
	void drawText( std::string text, int pos_x, int pos_y, std::string fontName, int fontSize, 
			unsigned int r, unsigned int g, unsigned int b );

	void drawLine(int start_x, int start_y, int end_x, int end_y, UINT r, UINT g, UINT b );

	// Flushes the back buffer to the screen
	void update();
};

#endif // INC_CSDL_H
