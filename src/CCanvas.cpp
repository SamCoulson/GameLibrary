//////////////////////////////////////////////////////////////////////////////////////////////
//
// CSDLGraphics - SDL Graphics object for setting up window, shutdown and displaying graphics
//
//////////////////////////////////////////////////////////////////////////////////////////////
#include "../include/CCanvas.h"
#include <iostream>
#include <string.h>

using namespace std;

CCanvas::CCanvas(SDL_Renderer *renderer)
{
	// Save ref to renderer
	sdlRenderer = renderer;

	// Set some defaults
	SetRenderColour(0, 0, 0);
}

CCanvas::~CCanvas()
{
}

// Returns a Uint32 color value from a given surface and positions. *Need wrap this function in surface locker (possible macro), as according
// to the docs the surface should be locked before these methods are applied*.
Uint32 CCanvas::getColor(SDL_Surface * surface, int x, int y)
{
	// Find pixel format 8,16,24,32 bits-per-pxel
	int bpp = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	// bpp can be 1 byte = 8 bits, 2 bytes = 16 bits, 3 bytes = 24, 4 bytes = 32
	switch( bpp )
	{
	case 1:
		return *p;  // Return address of an Uint8 type location  
	case 2:
		return *(Uint16 *)p; // Cast p to a Uint16 pointer type
	case 3:
		// Bit shift p[0] 16 bits to the left, p[1] 8 bits to the left for SDL_LITTLE_ENDIAN
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
	case 4:
		return *(Uint32 *)p; // Cast p to a Uint32 pointer type
	default:
		return 0;
	}
}

void CCanvas::drawSolidRect(UINT x, UINT y, UINT width, UINT height, UINT r, UINT g, UINT b)
{
	// Convert rect to native SDL_Rect
	SDL_Rect destRect;

	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SetRenderColour(r, g, b);

	if( SDL_RenderFillRect( sdlRenderer, &destRect) != 0 )
	{
		std::cout << "Could not FillRect" << endl;
	}
}

// UpdateScreen swaps the back buffer to the screen
void CCanvas::update()
{
	SDL_RenderPresent(sdlRenderer);
}

// Fills the back buffer with the colour of the given RGB values. 
void CCanvas::clear(UINT r, UINT g, UINT b){

	SetRenderColour(r, g, b);

	if (SDL_RenderClear(sdlRenderer) < 0) 
	{
		SDL_Log("(SDL_RenderClear() failed : %s", SDL_GetError());
	}
}

void CCanvas::drawImage(int x, int y, SDL_Texture* srcImage)
{
	return drawImage(x, y, srcImage, NULL);
}

// Draw or puts or copies the source image to a destination surface
void CCanvas::drawImage(int x, int y, SDL_Texture* srcImage, SDL_Rect* srcClipRect)
{
	// destination rect, used to specify where on the destination surface the image will be blitted too
	SDL_Rect destXY;

	int w, h;

	// Use full width and height if no src clip rect set
	if (srcClipRect == NULL)
	{
		SDL_QueryTexture(srcImage, NULL, NULL, &w, &h);
	}
	else
	{
		w = srcClipRect->w;
		h = srcClipRect->h;
	}

	// Take XY input and make them useable for Blit.
	destXY.x = x;
	destXY.y = y;
	destXY.w = w;
	destXY.h = h; 

	if (SDL_RenderCopy(sdlRenderer, srcImage, srcClipRect, &destXY) < 0)
	{
		SDL_Log("SDL_RenderCopy() failed: %s", SDL_GetError());
	}
}

void CCanvas::drawText( std::string text, int pos_x, int pos_y, std::string fontName, int fontSize, Uint8 r, Uint8 g, Uint8 b)
{
	// Pointer to font object
	TTF_Font* m_pFont;

	// Surface for text to be drawn in to
	SDL_Surface *text_surface;

	//Set up m_pFont for text output *make settable* also ensure TTF_Init has been run
	m_pFont = TTF_OpenFont( fontName.c_str(), fontSize );

	// Was m_pFont not loaded OK
	if(!m_pFont)
	{
		SDL_Log("TTF_OpenFont() failed: %s", SDL_GetError());
		return;
	}

	// Set the colour according to the arguments
	SDL_Color color = {r, g, b};

	// There are also other ways to render the text see the headerfile for fonts
	text_surface = TTF_RenderText_Blended(m_pFont, text.c_str(), color);

	if(text_surface == NULL)
	{
		SDL_Log("TTF_RenderText_Blended() failed: %s", SDL_GetError());
		return;
	}

	SDL_Texture *textureSurface = SDL_CreateTextureFromSurface(sdlRenderer, text_surface);
	if (textureSurface == NULL)
	{
		SDL_FreeSurface(text_surface);
		SDL_Log("SDL_CreateTextureFromSurface() failed: %s", SDL_GetError());
		return;
	}

	SDL_FreeSurface(text_surface);
	
	drawImage(pos_x, pos_y, textureSurface);
	
	// Release the Font
	if( m_pFont != NULL ){
		TTF_CloseFont(m_pFont);
	}

	SDL_DestroyTexture(textureSurface);
}

void CCanvas::drawPoint(UINT x, UINT y, UINT r, UINT g, UINT b)
{
	SetRenderColour(r, g, b);

	if (SDL_RenderDrawPoint(sdlRenderer, x, y) < 0)
	{
		SDL_Log("SDL_RenderDrawPoint() failed: %s", SDL_GetError());
	}
}

void CCanvas::drawLine(UINT startX, UINT startY, UINT endX, UINT endY, UINT r, UINT g, UINT b)
{
	// TODO: Add checks for exceeding canvas limits and check for positive integers only
	SetRenderColour(r, g, b);

	if(SDL_RenderDrawLine(sdlRenderer, startX, startY, endX, endY) < 0)
	{
		SDL_Log("SDL_RenderDrawLine() failed: %s", SDL_GetError());
	}
}

void CCanvas::SetRenderColour(UINT r, UINT g, UINT b)
{
	if (SDL_SetRenderDrawColor(sdlRenderer, r, g, b, 0) < 0)
	{
		SDL_Log("SDL_SetRenderDrawColor() failed: %s", SDL_GetError());
	}
}

SDL_Texture* CCanvas::loadImage(std::string filename)
{
	return loadImage(filename, 0, 0, 0);
}

SDL_Texture* CCanvas::loadImage(std::string filename, Uint8 r, Uint8 g, Uint8 b)
{
	// Surfaces for loaded file and converted file 
	SDL_Surface *loadedImageFile = NULL;

	// Load the image in from the file
	// NOTE: IMG_Load automatically handles color key on .PNG files.
	SDL_Log("Trying to load %s", filename.c_str());
	loadedImageFile = IMG_Load(filename.c_str());

	if (loadedImageFile == NULL)
	{
		SDL_Log("LoadImage failed, ensure correct filename and path, error: %s", IMG_GetError());
		return NULL;
	}
	else
	{
		if (SDL_SetColorKey(loadedImageFile, SDL_TRUE, SDL_MapRGB(loadedImageFile->format, 0xFF, 0, 0xFF)) < 0)
		{
			SDL_Log("SDL_SetColorKey() failed: %s", SDL_GetError());
		}

		SDL_Texture *textureSurface = SDL_CreateTextureFromSurface(sdlRenderer, loadedImageFile);

		SDL_FreeSurface(loadedImageFile);

		if (textureSurface == NULL)
		{
			SDL_Log("SDL_CreateTextureFromSurface() failed: %s", SDL_GetError());
			return NULL;
		}

		// Free up original surface
		SDL_Log("Image Loaded successfully");

		return textureSurface;
	}
}

