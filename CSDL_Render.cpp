#include "CSDL_Render.h"
#include <iostream>

using namespace std;

CSDL_Render::CSDL_Render( CSDL ** sdlobj ) 
{

	// Set imageID to 1. 0 indicates no allocation possible
	imageID = 1;
	
}

CSDL_Render::~CSDL_Render()
{
};



/*
// Takes a name of a file and attempt to load it in to memory, allocate it an ID and store a pointer to it in the internal image list
// for later reference by the renderer. If the function is succesful an index in the form of an imageID to the image in the internal list is returned.
// If not then the imageID is 0.
unsigned int CSDL_Render::RegisterImage(string filename)
{

	UINT img_ref = 0; // Used to determine if image has already been loaded.

	// Allocate memory for a image_data strucuture
	image_data *img_data = new image_data;
	if( img_data == NULL)
	{
		cout << "Could not allocate memory for image_data" << endl;
		return 0;
	}

	// Is the filename valid
	if( filename.length() == 0)
	{
		cout << "Invalid filename passed to CSDL_Render::RegisterImage" << endl;
		return 0;
	}

	// Is image already in list if so return the existing imageID, implemented to save space
	if( FindImageByFilename(filename, img_ref) )
	{
		return img_ref;
	}

	// Try to load the image
	img_data->image = LoadImageFromFile(&filename, true);

	// If succesfull, add to the internal list of images
	if( img_data->image != NULL)
	{
		// Store filename
		img_data->filename = filename;
		// Add image ref to internal list
		image_list.push_back( img_data );
		// Allcate a resource ID.
		img_data->imageID = imageID;
		// Increment ID counter for next image *Not necessarily safe for deleting images from the list*
		imageID++;
		// Return ID.
		return img_data->imageID;
	}
	else
	{
		cout << "Could not register image" << endl;
		return 0;
	}
}
*/
UINT CSDL_Render::GetImageWidth( UINT imageID ) const
{
	unsigned int img_ref = 0;

	if(!FindImageByID( imageID, img_ref ))
	{
		cout << "GetImageWidth failed" << endl;	
		return 0;
	}

	return image_list[img_ref]->image->w;
}

UINT CSDL_Render::GetImageHeight( UINT imageID ) const
{
	unsigned int img_ref = 0;

	if(!FindImageByID( imageID, img_ref ))
		{
	cout << "GetImageHeight failed" << endl;	
	return 0;
	}

	return image_list[img_ref]->image->h;
}


// Find index of ID, fills in imageID, or returns false if failed
bool CSDL_Render::FindImageByID( unsigned int imageIDtoFind, unsigned int &image_indexID  ) const
{
	// Would like to have a better way of searching through the list but the alternatives seem more complex 
	// see vectors, structs and std:find on stackoverflow for more details.  Other suggestions are use stl map or have a separate array that maps to the 
	// image list array element. Maps still require the use of find to work out if the element has already been added. but this doesnt matter if the check is none
	// real time. It s the lookup at render time that matters.
	for(std::vector< image_data* >::size_type currentIndex = 0; currentIndex != image_list.size(); currentIndex++)
	{
		if(image_list[currentIndex]->imageID == imageIDtoFind)
		{
			// Found image store location for DrawImage
			image_indexID = currentIndex;
			// Set success flag
			return true;
		}
	}

	return false;
}

bool CSDL_Render::FindImageByFilename( string& filenameToFind, unsigned int& image_indexID )
{
	for(std::vector< image_data* >::size_type currentIndex = 0; currentIndex != image_list.size(); currentIndex++)
	{
		if(image_list[currentIndex]->filename == filenameToFind)
		{
			// Found image store location for DrawImage
			image_indexID = image_list[currentIndex]->imageID;
			// Set success flag
			return true;
		}
	}

	return false;
}


