#ifndef INC_IWINDOW_H
#define INC_IWINDOW_H

#include "SDL/SDL.h"
#include "Globals.h"

// Initialises SDL graphical components and creates a window.
class __declspec(dllexport) IWindow
{
public:
	IWindow() {};
	virtual ~IWindow() {};

	// Setup SDL after object creation
	virtual bool initialise(const char* windowTitle, UINT screenWidth, UINT screenHeight, UINT screenBPP, Uint32 surfaceType) = 0;

	// Shutdown and cleanup after SDL
	virtual void shutdown() = 0;
};

#endif INC_IWINDOW_H