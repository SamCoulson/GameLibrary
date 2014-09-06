#include "../include/CSDLSound.h"
#include <iostream>

bool CSDLSound::initialise(){
		
	// Start SDL for audio
	std::cout << "Initialising SDLAudio system" << std::endl;		
	if(SDL_InitSubSystem( SDL_INIT_AUDIO ) < 0){
		// Send some errors to stderr
		std::cout << "Failed to initialiase SDL Audio subsystem" << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	if( SDL_WasInit( SDL_INIT_AUDIO )){
		std::cout << "Audio subsystem initialised"<< std::endl;
	}

	// Initialise SDL Audio Mixer
	Mix_Init( 0 );
	
	std::cout << "Initialising SDL_Mixer" << std::endl;		
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) ){
		// Send some errors to stderr
		std::cout << "Failed to initialiase SDL_Mixer" << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void CSDLSound::shutdown(){
	// Quit SDL Mixer
	std::cout << "Shutting down SDL_Mixer" << std::endl;			
	Mix_CloseAudio();	

	Mix_Quit();

	// Shutdown
	std::cout << "Shutting down SDL audio subsystem" << std::endl;	 
	SDL_QuitSubSystem( SDL_INIT_AUDIO );
}

Mix_Chunk* CSDLSound::loadSoundFromFile( std::string filename ){

	Mix_Chunk* effect = NULL; 

	//  Load the .wav effect file
	effect = Mix_LoadWAV( filename.c_str() );

	if( effect == NULL ){
		std::cout << "Failed to load " << filename << " effect file" << std::endl;
		std::cout << Mix_GetError() << std::endl;
	}else{
		std::cout << "Loaded "<< filename << " file successfully" << std::endl;
	}

	return effect;
}

Mix_Music* CSDLSound::loadMusicFromFile( std::string filename ){

	Mix_Music* music = NULL;

	//  Load the .wav music file
	music = Mix_LoadMUS( filename.c_str() );

	if( music == NULL ){
		std::cout << "Failed to load " << filename << " music file" << std::endl;
		std::cout << Mix_GetError() << std::endl;
	}else{
		std::cout << "Loaded "<< filename << " file successfully" << std::endl;
	}

	return music;
}

