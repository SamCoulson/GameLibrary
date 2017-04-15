#ifndef INC_ICANVAS_H
#define INC_ICANVAS_H

#include <string>
#include <list>
#include "Globals.h"

using namespace std;

class __declspec(dllexport) ICanvas
{
public:
	ICanvas(){};
	~ICanvas(){}; // Must use virtual deconstructors becasue when the interface is destroyed THIS gets called not the
	// Deconstrucotrs of the derived classes themselves.
		
	virtual void update() = 0;
	virtual void clear(UINT r, UINT g, UINT b) = 0;

	virtual void drawText( std::string text, int pos_x, int pos_y, std::string fontName, int fontSize, unsigned int r, unsigned int g, unsigned int b  ) = 0;
	virtual void drawImage(int x, int y, SDL_Texture* srcImage) = 0;
	virtual void drawImage(int x, int y, SDL_Texture* srcImage, SDL_Rect* srccliprect) = 0;

	virtual void drawSolidRect(UINT x, UINT y, UINT width, UINT height, UINT r, UINT g, UINT b) = 0;
	virtual void drawPoint(UINT x, UINT y, UINT r, UINT g, UINT b) = 0;
    virtual void drawLine(UINT startX, UINT startY, UINT endX, UINT endY, UINT r, UINT g, UINT b) = 0;

	virtual SDL_Texture* loadImage(std::string filename) = 0;
	virtual SDL_Texture* loadImage(std::string filename, Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;
};

#endif  INC_CANVAS_H
