#include "CWindow.h"
#include <iostream>
#include <string.h>

using namespace std;

// Initialises the SDL library with the given arguments in the parameter list
bool CWindow::create(const char* windowTitle, UINT screenWidth, UINT screenHeight, Uint32 surfaceType)
{
	// Start SDL for VIDEO
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Failed to initialise SDL subsystem : %s", SDL_GetError());
		return false;
	}

	if (SDL_WasInit(SDL_INIT_VIDEO)) {
		SDL_Log("Video subsystem initialised");
	}

	// Load the font library 
	if (TTF_Init() == -1)
	{
		SDL_Log("TTF_Init() Failed : %s", SDL_GetError());
		return false;
	}

	// Initialise SDL_Image
	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initialisedFlags=IMG_Init(flags);
	if ((initialisedFlags) != flags)
	{
		SDL_Log("IMG_Init: Failed to init required jpg and png support!\n");
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
	}
    
	// Set the video mode
	// surfaceType can be a set of OR'd flags not bitwise but logical OR *Need to fix the log output currently just puts 0. 
	if (!createWindow(windowTitle, screenWidth, screenHeight, surfaceType)) {
		SDL_Log("CWindow->create failed create window : %s", SDL_GetError());
		return false;
	}

	// Output compiled and linked against SDL versions (useful for debug)
	logCompiledAndLinkedVersionInfo();

	getVideoModes();

	return true;
}

void CWindow::logCompiledAndLinkedVersionInfo()
{
	// Get version that was compiled against 
	SDL_version compver;
	SDL_VERSION(&compver);

	// Get linker version information i.e. dll currently be used
	SDL_version runver;
	SDL_GetVersion(&runver);

	// Output version information to stdout
	SDL_Log("SDL Compile-time version: %d.%d.%d", (int)compver.major, (int)compver.minor, (int)compver.patch);
	SDL_Log("SDL Runtime version: %d.%d.%d", (int)runver.major, (int)runver.minor, (int)runver.patch);
}

// shutdown - closes any systems running and outputs to log
void CWindow::shutdown() {

	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	// Unload SDL_Image libraries
	IMG_Quit();

	// Shutdown the font system.
	SDL_Log("Shutting down font system");
	TTF_Quit();

	// SDL Quit
	SDL_Log("Shutting down SDL");
	SDL_Quit();
}

// Returns video possible resolutions for a given video mode.  
void CWindow::getVideoModes(void) 
{	
	// Get available screen hardware modes, fullscreen will give a list of modes, other options many just return All resolutions possible
	// The reason for this is because any dimensions can be passed in during setup IF we want windows mode.  This will merely open a window the size of
	// the given dimensions with a front buffer of the matching size.  Fullscreen will still accept non-regular dimensions and initialise 
	// but it create a box in the middle with those dimensions. 
	// Resizing a window does not however resize the front buffer, it will just cut of the viewable area without resizing. Unless RESIZEABLE is set in which
	// case SetVideoMode is called and the new dimensions are set.
	// Changing bpp per pixel seems like a bad idea aswell, i think it may end up messing up the users desktop.
	// A better idea might be to the default as the users current settings.

	SDL_Log("**************Possible video modes*******************");

	int videoDisplayCount = SDL_GetNumVideoDisplays();
	if (videoDisplayCount < 1)
	{
		SDL_Log("SDL_GetNumVideoDisplays() returned: %s", videoDisplayCount);
		return;
	}

	int displayCount = SDL_GetNumDisplayModes(0);
	if (displayCount < 1)
	{
		SDL_Log("SDL_GetNumDisplayModes() returned: %s", displayCount);
		return;
	}

	SDL_DisplayMode current;
	for (int i = 0; i < displayCount; i++)
	{
		if (SDL_GetCurrentDisplayMode(i, &current) != 0)
		{
			SDL_Log("Could not get display mode for video display mode #%d: %s", i, SDL_GetError());
		}
		else
		{
			SDL_Log("Display #%d current display mode is %dx%dpx @ %dhz.", i, current.w, current.h, current.refresh_rate);
		}
	}
	
}

bool CWindow::createWindow(const char* windowTitle, UINT screenWidth, UINT screenHeight, Uint32 surfaceType)
{
	// Create window 
	window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);  // or SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL
	if (window == NULL)
	{
		SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, 0);
	if (sdlRenderer == NULL) {
		SDL_Log("Unable to create SDL renderer: %s\n", SDL_GetError());
		return false;
	}
	
	SDL_RenderSetLogicalSize(sdlRenderer, screenWidth, screenHeight);

	canvas = new CCanvas(sdlRenderer);

	return true;
}

ICanvas* CWindow::getCanvas()
{
	return canvas;
}