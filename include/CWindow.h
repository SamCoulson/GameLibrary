#ifndef INC_CWINDOW_H
#define INC_CWINDOW_H

#include "IWindow.h"
#include "ICanvas.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class __declspec(dllexport) CWindow : public IWindow
{
public:
	// Setup SDL after object creation
	bool create(const char* windowTitle, UINT screenWidth, UINT screenHeight, Uint32 surfaceType);

	// Handle to render interface
	ICanvas* getCanvas();

	// Shutdown and cleanup after SDL
	void shutdown();

private:

	SDL_Window* window;

	ICanvas* canvas = NULL;

	// Create the window
	bool createWindow(const char* windowTitle, UINT screenWidth, UINT screenHeight, Uint32 surfaceType);

	// Get the version of SDL compiled against and currently linked against
	void logCompiledAndLinkedVersionInfo();

	// Output information about possible video modes
	void getVideoModes(void);
};

#endif INC_CWINDOW_H