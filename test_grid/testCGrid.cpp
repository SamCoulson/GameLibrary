#include "../CSDLGraphics.h"
#include "../CGrid.h"
#include <stdio.h>
#include <assert.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

#define GRID_WIDTH  10
#define GRID_HEIGHT 15
#define GRID_TILE_SIZE_X 20 
#define GRID_TILE_SIZE_Y 20

CSDLGraphics *graphics = NULL;
CGrid *grid = NULL;

void setup(){
	graphics = new CSDLGraphics();
	grid = new CGrid( GRID_WIDTH, GRID_HEIGHT, GRID_TILE_SIZE_X, GRID_TILE_SIZE_Y, 0, 0 );	
}

void cleanup(){
	
	if( grid != NULL ){
		delete grid;
	}

	if( graphics != NULL ){
		graphics->shutdown();
	}
	delete graphics;
}

int main( int argc, char* argv[] ){
	
	// Re-direct output to console as SDL will disable it
	/* Note: Assert output to STDERR so must also be redirected*/		
	freopen( "CON" ,"w", stderr ); 
	freopen( "CON" ,"w", stdout );

	setup();
	assert( NULL != grid && "Create grid object" );
	cleanup();

	setup();
	coords* xy;
	xy = grid->getXY( 5, 6 );
	assert( ( xy->x != 0 ) || ( xy->y != 0 ) && "return valid x and y coorinates" );
	cleanup();
	
	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "CGrid Test"  );
	Uint32 color = SDL_MapRGB( SDL_GetVideoSurface()->format, 255, 255, 255 );
	coords* xy_coords;
	for( int x = 0; x < GRID_WIDTH; x++ ){
		for( int y = 0; y < GRID_HEIGHT; y++ ){
			xy_coords = grid->getXY( x, y );
			graphics->putColor( SDL_GetVideoSurface(), xy_coords->x, xy_coords->y, color );
		}
	}
	graphics->update();
	SDL_Delay( 3000 );
	//assert( ( xy->x != 0 ) || ( xy->y != 0 ) && "return valid x and y coorinates" );
	cleanup();

	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "CGrid Test"  );
	Uint32 tile_color = SDL_MapRGB( SDL_GetVideoSurface()->format, 255, 255, 255 );
	coords* tile_xy_coords;
	tile_xy_coords = grid->getXY( 5, 6 );
	graphics->fillRect( tile_xy_coords->x, tile_xy_coords->y, GRID_TILE_SIZE_X, GRID_TILE_SIZE_Y, 255, 0, 0 );
	tile_xy_coords = grid->getXY( 8, 7 );
	graphics->fillRect( tile_xy_coords->x, tile_xy_coords->y, GRID_TILE_SIZE_X, GRID_TILE_SIZE_Y, 0, 255, 0 );
	tile_xy_coords = grid->getXY( 3, 2 );
	graphics->fillRect( tile_xy_coords->x, tile_xy_coords->y, GRID_TILE_SIZE_X, GRID_TILE_SIZE_Y, 0, 0, 255 );
	graphics->update();
	SDL_Delay( 3000 );
	//assert( ( xy->x != 0 ) || ( xy->y != 0 ) && "return valid x and y coorinates" );
	cleanup();

	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "CGrid Test"  );
	SDL_Surface* tileImage;
	tileImage = graphics->loadImageFromFile( std::string("./images/GoldBlock24bit.bmp"), false  );
	coords* image_xy_coords;
	image_xy_coords = grid->getXY( 5, 6 );
	graphics->draw( image_xy_coords->x, image_xy_coords->y, tileImage, SDL_GetVideoSurface(), NULL );
	image_xy_coords = grid->getXY( 9, 8 );	
	graphics->draw( image_xy_coords->x, image_xy_coords->y, tileImage, SDL_GetVideoSurface(), NULL );	
	graphics->update();
	SDL_Delay( 5000 );
	//assert( ( xy->x != 0 ) || ( xy->y != 0 ) && "return valid x and y coorinates" );
	cleanup();
	return 0;
}
