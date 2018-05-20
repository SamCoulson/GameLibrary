#ifndef INC_IWINDOW_H
#define INC_IWINDOW_H

#include "SDL.h"
#include "Globals.h"
#include "CCanvas.h"

// Initialises SDL graphical components and creates a window.
class __declspec(dllexport) IWindow
{
public:
	IWindow() {};
	virtual ~IWindow() {};

	// Setup SDL after object creation
	virtual bool create(const char* windowTitle, UINT screenWidth, UINT screenHeight, Uint32 surfaceType) = 0;

	// Shutdown and cleanup after SDL
	virtual void shutdown() = 0;

	virtual ICanvas* getCanvas() = 0;
};

#endif INC_IWINDOW_H