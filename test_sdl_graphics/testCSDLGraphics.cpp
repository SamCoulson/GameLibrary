#include "../include/CSDLGraphics.h"
#include <stdio.h>
#include <assert.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

CSDLGraphics *graphics = NULL;

void setup(){
	graphics = new CSDLGraphics();	
}

void cleanup(){

	if( graphics != NULL ){
		graphics->shutdown();
	}
	delete graphics;
}

int main( int argc, char* argv[] ){

	// Re-direct output to console as SDL will disable it	
	freopen( "CON" ,"w", stderr); /* Note: this must output to stderr not stdout to work */	
		
	setup();
	assert( graphics !=NULL && "test CSDL() - Create CSDl object" );
	cleanup();
	
	setup();
	assert( true == graphics->initialise( SCREEN_WIDTH, 
						SCREEN_HEIGHT, 
						SCREEN_BPP, 
						SDL_SWSURFACE, 
						"testCSDL" ) && "test CSDL() - initialise()" );	
	cleanup();
	
	setup();
	assert( true == graphics->initialise( SCREEN_WIDTH, 
						SCREEN_HEIGHT, 
						SCREEN_BPP, 
						SDL_SWSURFACE, 
						"testCSDL" ) && "test CSDL() - initialise() with SDL_SWSURFACE" );	
	cleanup();
	
	setup();
	assert( true == graphics->initialise( SCREEN_WIDTH, 
						SCREEN_HEIGHT, 
						SCREEN_BPP, 
						SDL_FULLSCREEN, 
						"testCSDL" ) && "test CSDL() - initialise() with SDL_FULLSCREEN" );	
	cleanup();
	
	setup();
	assert( true == graphics->initialise( SCREEN_WIDTH, 
						SCREEN_HEIGHT, 
						SCREEN_BPP, 
						SDL_FULLSCREEN | SDL_HWSURFACE, 
						"testCSDL" ) && "test CSDL() - initialise() with SDL_FULLSCREEN | SDL_HWSURFACE" );	
	cleanup();	
	
	setup();
	assert( false == graphics->initialise( NULL, 
						SCREEN_HEIGHT, 
						SCREEN_BPP, 
						SDL_SWSURFACE, 
						"testCSDL" ) && "test CSDL() - initialise() - NULL screen width" );	
	cleanup();
	
	setup();
	assert( false == graphics->initialise( SCREEN_WIDTH, 
						NULL, 
						SCREEN_BPP, 
						SDL_SWSURFACE, 
						"testCSDL" ) && "test CSDL() - initialise() - NULL screen height" );	
	cleanup();

	setup();
	assert( false == graphics->initialise( SCREEN_WIDTH, 
						SCREEN_HEIGHT, 
						NULL, 
						SDL_SWSURFACE, 
						"testCSDL" ) && "test CSDL() - initialise() - NULL screen bpp" );	
	cleanup();

	setup();
	assert( true == graphics->initialise( SCREEN_WIDTH, 
						SCREEN_HEIGHT, 
						SCREEN_BPP, 
						NULL, 
						"testCSDL" ) && "test CSDL() - initialise() - NULL front buffer surface" );	
	cleanup();
	
	setup();
	assert( true == graphics->initialise( SCREEN_WIDTH, 
						SCREEN_HEIGHT, 
						SCREEN_BPP, 
						SDL_SWSURFACE, 
						NULL ) && "test CSDL() - initialise() - NULL title" );	
	cleanup();
	
	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	 
	graphics->clearScreen( 255, 255, 255 );
	graphics->update();
	SDL_Delay( 2000 );	
	cleanup();	
	
	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	
	std::string missingfile = "missingfile.png"; 
	SDL_Surface* surface00 = graphics->loadImageFromFile( missingfile, 0, 0, 0 );
	assert( surface00 == NULL && "loadImageFromFile() - Incorrect filename" );
	SDL_FreeSurface( surface00 );	
	cleanup();
	
	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	
	std::string filename = "./images/test2.bmp"; 
	SDL_Surface* surface01 = graphics->loadImageFromFile( filename, 255, 0, 255 );
	assert( surface01 != NULL && "loadImageFromFile() - Correct filename" );		
	cleanup();

	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	 
	graphics->fillRect( 0, 0, 100, 100, 255,255,255 );
	graphics->update();
	SDL_Delay( 2000 );	
	cleanup();

	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	 
	graphics->fillRect( 0, 0, 100, 100, 255,255,255 );
	graphics->fillRect( 200, 200, 100, 100, 255, 0, 0 );

	graphics->update();
	SDL_Delay( 2000 );	
	cleanup();

	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	
	std::string sprite_filename_jpg = "./images/MarioStand.jpg"; 
	SDL_Surface* sprite_jpg = graphics->loadImageFromFile( sprite_filename_jpg, 255, 0, 255 );
	graphics->draw( 0, 0, sprite_jpg, SDL_GetVideoSurface(), NULL );
	graphics->update();
	SDL_Delay( 2000 );
	cleanup();

	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	
	std::string sprite_filename_trans = "./images/MarioStand.bmp"; 
	SDL_Surface* sprite_bmp_trans = graphics->loadImageFromFile( sprite_filename_trans, 255, 0, 255  );
	graphics->draw( 0, 0, sprite_bmp_trans, SDL_GetVideoSurface(), NULL );
	graphics->update();
	SDL_Delay( 2000 );
	cleanup();


	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	
	std::string sprite_filename_png = "./images/happy.png"; 
	SDL_Surface* sprite_png = graphics->loadImageFromFile( sprite_filename_png, 255, 255, 255 );
	graphics->draw( 0, 0, sprite_png, SDL_GetVideoSurface(), NULL );
	graphics->update();
	SDL_Delay( 2000 );
	cleanup();

	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );	
	graphics->drawText( std::string("Hello World!"), 0, 0, std::string("./fonts/tunga.ttf"), 45, 255, 0, 0 );
	graphics->update();
	SDL_Delay( 2000 );
	cleanup();

	setup();
	graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE, "testCSDLGraphics" );

	graphics->drawLine( 100, 100, 200, 100, 255, 50, 50); // Left to Right
	graphics->drawLine( 200, 100, 200, 200, 255, 50, 50); // Up to down
	
	graphics->drawLine( 200, 200, 100, 200, 255, 50, 50); // Right to Left

	graphics->drawLine( 100, 200, 100, 100, 255, 50, 50); // Down to Up 
	graphics->update();
	SDL_Delay( 2000 );
	cleanup();


	return 0;
}
