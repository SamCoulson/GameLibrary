#ifndef H_SDLRENDER_INC
#define H_SDLRENDER_INC

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "CSDL.h"
#include "IRenderInterface.h"
#include <string>
#include <vector>
#include <algorithm>

// Define the amount of sprite that the internal sprite list may hold
//#define MAX_SPRITES 49

class CSDL_Render : public IRenderInterface
{
public:
	// Constructor
	CSDL_Render( CSDL ** );
	// Destructor
	~CSDL_Render();

	// Register image with renderer 
	UINT RegisterImage( string ); 

	// Return the image size for the given imageID
	UINT GetImageWidth( UINT imageID ) const;
	UINT GetImageHeight( UINT imageID ) const
	
private:
		
	typedef struct _IMAGEDATA
	{
		unsigned int imageID; // Unique image ID or index
		SDL_Surface* image; // Pointer to actual image data
		string filename; // Name of original image file 
		//imageData_s* imageData; // Clipping info used for sprite sheets
	}image_data;

	// Internal list of images
	vector< image_data* > image_list;

	// Find Image by given imageID, fills in second argument with reference
	bool FindImageByID( unsigned int imageIDtoFind, unsigned int& ) const;

	// Find Image by Filename
	bool FindImageByFilename( string&, unsigned int& );

	// Image ID counter
	unsigned int imageID;
	
};

#endif // H_SDLRENDER_INC
