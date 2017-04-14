//////////////////////////////////////////////////////////////////////////////////////////////
//
// CSDLGraphics - SDL Graphics object for setting up window, shutdown and displaying graphics
//
//////////////////////////////////////////////////////////////////////////////////////////////
#include "../include/CSDLGraphics.h"
#include <iostream>
#include <string.h>

using namespace std;

// Constructor 
CSDLGraphics::CSDLGraphics()
{
}

CSDLGraphics::~CSDLGraphics()
{
}

// Load and convert image to screen pixel format, as well as gets the upper left corner pixel for color key
SDL_Surface* CSDLGraphics::loadImageFromFile( std::string filename, Uint8 r, Uint8 g, Uint8 b )
{
	//// Surfaces for loaded file and converted file 
	//SDL_Surface *loadedImageFile = NULL;
	//SDL_Surface *convertedSurface = NULL;

	//// Load the image in from the file
	//// NOTE: IMG_Load automatically handles color key on .PNG files.
	//std::cout << "Trying to load " << filename.c_str() << endl;
	//loadedImageFile = IMG_Load( filename.c_str() );
	//
	//// Was an image loaded in to the surface
	//if(loadedImageFile == NULL)
	//{
	//	cout << "'CSDL_Render::LoadImageFromFile' failed to load image in to SDL_Surface, ensure correct filename and path" << endl;
	//	return convertedSurface = NULL;
	//}

	//// Convert the loaded image to ** This section of the code only work if the SDL object has been initialised before hand, else SDL_DisplayFormat is unknown **
	//convertedSurface = SDL_DisplayFormat( loadedImageFile );		
	//if( convertedSurface == NULL )
	//{
	//	cout << "Failed to convert SDL_Surface" << endl; 
	//	return convertedSurface = NULL;
	//}
	//else
	//{
	//	// NOTE: Some images do not display transparency correctly may need to recreate image and save with
	//	// pixels correctly set to the specified color key value ( 255, 0, 255 is a common one ) 
	//	if( SDL_SetColorKey( convertedSurface, SDL_SRCCOLORKEY,
	//				SDL_MapRGB( convertedSurface->format, r, g, b ) ) != 0 )  
	//	{
	//		// Free up original surface
	//		SDL_FreeSurface( loadedImageFile );

	//		cout << "Failed to set color key" << endl;
	//		return convertedSurface = NULL;
	//		
	//	}else{
	//		// Free up original surface
	//		SDL_FreeSurface( loadedImageFile );
	//		cout << "Image " << filename.c_str() << " loaded successfully" << endl;

	//		// Return the color keyed surface
	//		return convertedSurface;	 
	//	}
	//	
	//}

	//// Free surface from loaded original file image
	//SDL_FreeSurface( loadedImageFile );

	//// Return uncolor keyed new image
	//cout << "Image " << filename.c_str() << " loaded successfully" << endl;
	//return convertedSurface;

	return NULL;
}

// Returns a Uint32 color value from a given surface and positions. *Need wrap this function in surface locker (possible macro), as according
// to the docs the surface should be locked before these methods are applied*.
Uint32 CSDLGraphics::getColor(SDL_Surface * surface, int x, int y)
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

//  Set a given pixel in a surface to a specifed colour.  *Need wrap this function in surface locker (possible macro), as according
// to the docs the surface should be locked before these methods are applied*. Only true if SDL_MUSTLOCK evaluates to 1 it 0 then can be written to any time
// Also need to be able to specify RGB not have to create Uint32 before hand.
void CSDLGraphics::putColor(SDL_Surface *surface, int x, int y, Uint32 color)
{

	int bpp = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch( bpp ) 
	{
    case 1:
        *p = color;
        break;

    case 2:
        *(Uint16 *)p = color;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
		{
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
        } 
		else 
		{
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = color;
        break;
	}
}

// Wraps SDL_FillRrect
void CSDLGraphics::fillRect( unsigned int x, unsigned int y, unsigned int width, unsigned int height, 
		unsigned int r, unsigned int g, unsigned int b){

	// Convert rect to native SDL_Rect
	/*SDL_Rect destRect;

	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	if( SDL_FillRect( screenSurface, &destRect, SDL_MapRGB( screenSurface->format, r, g, b ) ) != 0 )
	{
		std::cout << "Could not FillRect" << endl;
	}*/

}

// UpdateScreen swaps the back buffer to the screen
void CSDLGraphics::update()
{
	//SDL_UpdateWindowSurface(window);
}

// Fills the back buffer with the colour of the given RGB values. 
void CSDLGraphics::clearScreen( unsigned int r, unsigned int g, unsigned int b ){
	
	//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, r, g, b ) );
}

// Draw or puts or copies the source image to a destination surface
void CSDLGraphics::draw(int x, int y, SDL_Surface* srcimage, SDL_Surface* destSurface, SDL_Rect* srccliprect)
{
	// destination rect, used to specify where on the destination surface the image will be blitted too
	SDL_Rect destXY;

	// Take XY input and make them useable for Blit.
	destXY.x = x;
	destXY.y = y;
	destXY.w = 0; // These are ignored
	destXY.h = 0; // Can use SDL_gfx for stretching

	// Put the image to the screen or back buffer
	// Can also be drawn or put to another surface might need to do src/dest xy chekcing here
	// Need to find out what error values this returns and how to handle when it goes wrong.
	SDL_BlitSurface(srcimage, srccliprect, destSurface, &destXY);

}

void CSDLGraphics::drawText( std::string text, int pos_x, int pos_y, std::string fontName, int fontSize, 
			unsigned int r, unsigned int g, unsigned int b  )
{
	// Pointer to font object
	//TTF_Font* m_pFont;

	//// Surface for text to be drawn in to
	//SDL_Surface *text_surface;

	////Set up m_pFont for text output *make settable* also ensure TTF_Init has been run
	//m_pFont = TTF_OpenFont( fontName.c_str(), fontSize );

	//// Was m_pFont not loaded OK
	//if(!m_pFont)
	//{
	//	cout << "Could not load font file" << endl;
	//}

	//// Set the colour according to the arguments
	//SDL_Color color = {r, g, b};

	//// There are also other ways to render the text see the headerfile for fonts
	//text_surface = TTF_RenderText_Blended(m_pFont, text.c_str(), color);

	//if(text_surface == NULL)
	//{
	//	cout << "Could not create render surface for m_pFont" << endl;
	//}

	//draw(pos_x, pos_y, text_surface, SDL_GetWindowSurface(window), NULL);
	//
	//// Release the Font
	//if( m_pFont != NULL ){
	//	TTF_CloseFont(m_pFont);
	//}

	//SDL_FreeSurface(text_surface);

}

// This works but is commented out because of the abs error warning whencompiling with GNU
void CSDLGraphics::drawLine(int start_x, int start_y, int end_x, int end_y, UINT r, UINT g, UINT b )
{
	// Add screen limit checks and check for positive integers only

	//int x0, x1, y0, y1 = 0;

	//int ystep = 0; // Determine which direction the line is drawn, up or down, on the y-axis

	//// Copy values for maninulation
	//x0 = start_x;
	//x1 = end_x;
	//y0 = start_y;
	//y1 = end_y;

	//Uint32 color = SDL_MapRGB(screenSurface->format, r, g, b);

	//bool steep = false; // Boolean for is line steeper than 45 degrees?

	//int tmp1, tmp2 = 0;

	//tmp1 = abs(y1 - y0);
	//tmp2 = abs(x1 - x0);

	//if( tmp1 > tmp2 )
	//{
	//	steep = true;
	//}
	//
	//// Is delta of y longer than delta of x, if so line extends past 45 degrees and values must be swapped 
	//if( steep ) 
	//{
	//	int steep_swap = 0; // Used for swapping routine

	//	steep = true;	  // Flag that line is steep used later during plotting

	//	steep_swap = y0;	  // Save state of start_y

	//	y0 = x0;		  // Make start_y == end_x
	//	x0 = steep_swap;	  // make end_x == start_y

	//	steep_swap = x1;    // Savew state of end_x

	//	x1 = y1;		  // Make end_x = end_y
	//	y1 = steep_swap;    // Make end_y = end_x

	//	
	//}
	//
	//if( x0 > x1) // Line goes backwards 
	//{
	//	int back_swap = 0;
	//	back_swap = x0;
	//	x0 = x1;
	//	x1 = back_swap;
	//	back_swap = y0;
	//	y0 = y1;
	//	y1 = back_swap;
	//}

	//float deltax = (float)x1 - (float)x0;       				// The difference in the x's
	//float deltay = abs((float)y1 - (float)y0);       			// The difference in the y's NOTE: must be the absolute value i.e. without and + or - sign
	//											// or must be positive

	//float error = 0.0;
	//float deltaerr = (deltay / deltax);			// Determine slope of line or how steep the line is
	//int y = y0;

	//if( y0 < y1 )			// If line goes down in the Y-axis 
	//{
	//	ystep = 1;
	//}
	//else					// If line goes up in the Y-axis
	//{
	//	ystep = -1;
	//}

	//for (int x = x0; x <= x1; x++)				// Iterate along line on the a-axis
	//{
	//  if( steep )
	//  {
	//	  putColor(SDL_GetWindowSurface(window), y, x, color);     // Draw the current pixel using swapped coordinates
	//  }
	//  else
	//  {
	//	  putColor(SDL_GetWindowSurface(window), x, y, color);		// Draw the current pixel using normal coordinates
	//  }

	//  error += deltaerr;       							// Add slope to error to determine whether to go one down
	//  if (error >= 0.5)   								// If error is over half way move down on the next square
	//  {
	//	y = y + ystep;                					// Increase the value of y to move down a square.
	//	error = error - 1.0f;     						// Reset error by one unit
	//  }
	//}
//	return 0;
}



