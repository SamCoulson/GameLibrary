#include "../include/CWindow.h"
#include <iostream>
#include <string.h>

using namespace std;

// Initialises the SDL library with the given arguments in the parameter list
bool CWindow::initialise(const char* windowTitle, UINT screenWidth, UINT screenHeight, UINT screenBPP, Uint32 surfaceType)
{
	// Start SDL for VIDEO
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// Send some errors to stderr
		cout << "Failed to initialise SDL subsystem" << endl;
		cerr << SDL_GetError() << endl;
		return false;
	}

	if (SDL_WasInit(SDL_INIT_VIDEO)) {
		cout << "Video subsystem initialised" << endl;
	}

	// Load the font library 
	if (TTF_Init() == -1)
	{
		cout << "TTF_Init() Failed" << endl;
		return false;
	}

	// Set the video mode
	// surfaceType can be a set of OR'd flags not bitwise but logical OR *Need to fix the log output currently just puts 0. 
	if (!createWindow(windowTitle, screenWidth, screenHeight, screenBPP, surfaceType)) {
		cout << "CSDL Failed create window" << endl;
		return false;
	}

	// Output compiled and linked against SDL versions (useful for debug)
	getCompiledAndLinkedVersionInfo();

	// Everything set up successfully
	screenSurface = SDL_GetWindowSurface(window);

	return true;
}

void CWindow::getCompiledAndLinkedVersionInfo()
{
	// Get version that was compiled against 
	SDL_version compver;
	SDL_VERSION(&compver);

	// Get linker version information i.e. dll currently be used
	SDL_version runver;
	SDL_GetVersion(&runver);

	// Output version information to stdout
	cout << "SDL Compile-time version:" << (int)compver.major << "." << (int)compver.minor << "." << (int)compver.patch << endl;
	cout << "SDL Runtime version:" << (int)runver.major << "." << (int)runver.minor << "." << (int)runver.patch << endl;
}

// shutdown - closes any systems running and outputs to log
void CWindow::shutdown() {

	// Shutdown the font system.
	cout << "Shutting down font system" << endl;
	TTF_Quit();

	// SDL Quit
	cout << "Shutting down SDL" << endl;
	SDL_Quit();
}

// OutputVideoModeInfo() - Outputs video info to cout. Can be called before or after the video mode is set but will contain different info  
void CWindow::outputVideoModeInfo(void) {

	//char viddrvname[7];	// Buffer for name of video driver

	//cout << "**************Video mode info*******************\n" << endl;

	//// Get name of video driver **This can be found or included in the video info function**
	//if(SDL_VideoDriverName(viddrvname, 7) == NULL)
	//{
	//	cout << "Unable to determine video driver name\n" << endl; 
	//}else{
	//	cout << "Driver: " << viddrvname << endl;
	//}

	//const SDL_VideoInfo *vidinfo = NULL; // Video capabilites

	//// Get optimal video info see docs for all the settings
	//vidinfo = SDL_GetVideoInfo();

	//if( vidinfo != NULL){
	//	cout << "Available hardware video memory: " << vidinfo->video_mem <<
	//	"\nCurrent video resolution: " << vidinfo->current_w << " x " << vidinfo->current_h << 
	//	"\nHardware surfaces available: " << vidinfo->hw_available << 
	//	"\nCurrent video format (BitPerPixel): " << (int)vidinfo->vfmt->BitsPerPixel << 
	//	"\nCurrent video format (Colour Key): " << vidinfo->vfmt->colorkey << endl;
	//}else{
	//	cout << "" << endl;
	//}
}

// Returns video possible resolutions for a given video mode.  
void CWindow::outputVideoModes(void) {

	// NEED TO DO THE FOLLOWING IF YOU WANT TO DO THIS use SDL_GetDisplayMode()/SDL_GetNumDisplayModes() instead

	// Get available screen hardware modes, fullscreen will give a list of modes, other options many just return All resolutions possible
	// The reason for this is because any dimensions can be passed in during setup IF we want windows mode.  This will merely open a window the size of
	// the given dimensions with a front buffer of the matching size.  Fullscreen will still accept non-regular dimensions and initialise 
	// but it create a box in the middle with those dimensions. 
	// Resizing a window does not however resize the front buffer, it will just cut of the viewable area without resizing. Unless RESIZEABLE is set in which
	// case SetVideoMode is called and the new dimensions are set.
	// Changing bpp per pixel seems like a bad idea aswell, i think it may end up messing up the users desktop.
	// A better idea might be to the default as the users current settings.

	//SDL_Rect **modes;					 // List of video modes

	//cout << "**************Possible video modes*******************\n" << endl;

	//modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);
	//if( modes == (SDL_Rect**)0){
	//	cout << "No modes available" << endl;
	//	//return false;
	//}else if( modes == (SDL_Rect**)-1){
	//	cout << "All resolutions available "<< endl;		
	//}else{
	//	cout << "Available modes" << endl;
	//	for(int i=0; modes[i]; ++i){
	//		cout << modes[i]->w << " x " << modes[i]->h << endl;
	//	}
	//}

}

bool CWindow::createWindow(const char* windowTitle, UINT screenWidth, UINT screenHeight, UINT screenBPP, Uint32 surfaceType)
{
	//cout << "**************Current video mode*******************" << endl;

	//// Check that the requested video mode is available, if it isnt get the closest
	//cout << "Checking requested screen mode: "<< screenWidth << " x " << screenHeight << " at " << screenBPP << " BPP" <<  endl;

	//

	//bool SDL_GetClosetDisplayMode()

	//if(bpp == 0){
	//	cout << "Requested video mode not available" << endl;
	//	// Could just let it go and let SDL emulate the color depth but i want know what going on
	//	// Alternatively add a warning to the log to say what is going on.
	//	return false;
	//}else{
	//	
	//	// If video mode available, setup and create screen surface	
	//	// NOTE: screenSurface is actually a private member and so should
	//	// probably be named _m_screenSurface
	//	screenSurface = SDL_SetVideoMode( screenWidth, screenHeight, screenBPP, surfaceType );
	//	if(screenSurface == NULL){
	//		cout << "Could not set SDL video mode" << endl;
	//		return false;
	//	}

	//	// If HWSURFACE is not suported on the card then warn
	//	if( ( surfaceType & SDL_HWSURFACE ) && ( ( screenSurface->flags & SDL_HWSURFACE ) ==0 ) )
	//		std::cout << "**SDL_HWSURFACE requested but is not supported using SW_SURFACE**" << endl;

	//	// Out for startup log
	//	cout << "Video mode set to " << screenSurface->w << " x " << screenSurface->h << " at " << (int)screenSurface->format->BitsPerPixel << " Bpp" 
	//		<< " with flags ";
	//
	//	// Determine what flags are set
	//	if( ( screenSurface->flags & SDL_SWSURFACE ) == 0 )
	//		std::cout << "SDL_SWSURFACE ";
	//	if( screenSurface->flags & SDL_HWSURFACE )
	//		std::cout << "SDL_HWSURFACE ";	
	//	if( screenSurface->flags & SDL_FULLSCREEN )
	//		std::cout << "SDL_FULLSCREEN ";
	//	if( screenSurface->flags & SDL_ASYNCBLIT )
	//		std::cout << "SDL_ASYNCBLIT ";
	//	if( screenSurface->flags & SDL_HWPALETTE )
	//		std::cout << "SDL_HWPALETTE ";
	//	// NEEDS OTHER FLAGS ADDING
	//	std::cout << endl;
	//}

	// Create window 
	window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	SDL_Delay(2000);
	return true;
}