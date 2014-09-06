#include "../include/CSDLGraphics.h"
#include "../include/CSDLSound.h"
#include <iostream>

// Tests for CSDLSound, this code is non-interactive.  If interaction is required the graphics subsystem will
// need to be initialised in order to be able to handle key press events.
CSDLSound *sound;

void setup(){
	// Initialise the SDL audio system
	sound = new CSDLSound();
	sound->initialise();
}

void shutdown(){
	// Shutdow the mixer and SDL audio subsystem	
	sound->shutdown();
}

int main( int argc, char* argv[] ){

	// Re-direct output to console as SDL will disable it	
	freopen( "CON" ,"w", stdout); /* Note: this must output to stderr not stdout to work */	

	// Test music playback
	setup();

	Mix_Music *music = NULL;
	const char* musicFilename = NULL; //"music/electric.wav";

	music = sound->loadMusicFromFile( musicFilename ); 	
	if( music == NULL ){
		return 0;	
	}else{
		
		// Play Music file
		Mix_PlayMusic( music, -1 );

		SDL_Delay(2000);  // Delay required to allow sound to run through before program tries to quit

		// Unload the .wav music file
		if( music != NULL ){
			Mix_FreeMusic( music );
		}
	}	

	shutdown();

	// Test channel playback
	setup();

	Mix_Chunk *effect = NULL;
	const char* effectFilename = NULL; //"music/electric.wav";

	//  Load the .wav music file
	effect = sound->loadSoundFromFile( effectFilename );

	if( effect == NULL ){
		return 0;		
	}else{
		
		// Play Music file
		Mix_PlayChannel( -1, effect, 1 );

		SDL_Delay(2000);  // Delay required to allow sound to run through before program tries to quit

		// Unload the .wav music file
		if( effect != NULL ){
			Mix_FreeChunk( effect );
		}
	}	

	shutdown();	
			
	return 0;
}


