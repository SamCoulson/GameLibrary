#ifndef INC_CWINDOW_H
#define INC_CWINDOW_H

#include "IWindow.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
// Font library used for graphical text output
#include "SDL/SDL_ttf.h"

class __declspec(dllexport) CWindow : public IWindow
{
public:
	// Setup SDL after object creation
	bool initialise(const char* windowTitle, UINT screenWidth, UINT screenHeight, UINT screenBPP, Uint32 surfaceType);

	// Shutdown and cleanup after SDL
	void shutdown();

private:

	SDL_Window* window;

	// Screen back buffer
	SDL_Surface *screenSurface;

	// Create the window
	bool createWindow(const char* windowTitle, UINT screenWidth, UINT screenHeight, UINT screenBPP, Uint32 surfaceType);

	// Get the version of SDL compiled against and currently linked against
	void getCompiledAndLinkedVersionInfo();

	// Output information about potential or set videos modes 
	void outputVideoModeInfo(void);

	// Output information about possible video modes
	void outputVideoModes(void);
};

#endif INC_CWINDOW_H