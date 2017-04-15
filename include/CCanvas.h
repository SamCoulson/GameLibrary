// CSDLGraphics.h - Headers for CSDLGraphics.cpp
#ifndef INC_CCANVAS_H
#define INC_CCANVAS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "ICanvas.h"
#include <iostream>
#include "Globals.h"

// Provides methods to draw things to the screen
class __declspec(dllexport) CCanvas : public ICanvas
{
public:
	CCanvas(SDL_Renderer *renderer);
	~CCanvas();

	// Flushes the back buffer to the screen
	void update();
	// Clears the screen to one colour
	void clear(UINT r, UINT g, UINT b);
	
	// Draws an image based on given data
	void drawImage(int x, int y, SDL_Texture* srcImage);
	void drawImage(int x, int y, SDL_Texture* srcImage, SDL_Rect* srccliprect);
	// Draw text with given font
	void drawText(std::string text, int pos_x, int pos_y, std::string fontName, int fontSize, unsigned int r, unsigned int g, unsigned int b);

	void drawSolidRect(UINT x, UINT y, UINT width, UINT height, UINT r, UINT g, UINT b);
	void drawPoint(UINT x, UINT y, UINT r, UINT g, UINT b);
	void drawLine(UINT startX, UINT startY, UINT endX, UINT endY, UINT r, UINT g, UINT b);

	SDL_Texture* loadImage(std::string filename);
	SDL_Texture* loadImage(std::string filename, Uint8 r, Uint8 g, Uint8 b, Uint8 a); // Really should move this to its own class but has SDL dependecies

	// Returns a Uint32 pixel colour from a given surface and coord 
	Uint32 getColor(SDL_Surface * surface, int x, int y);

private:

	SDL_Renderer *sdlRenderer = NULL;

	void SetRenderColour(UINT r, UINT g, UINT b);
};

#endif INC_CCANVAS_H
