#ifndef INC_CSDLSOUND_H
#define INC_CSDLSOUND_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <string>

class CSDLSound{

	public:
		CSDLSound(){};
		~CSDLSound(){};

		bool initialise();

		void shutdown();

		Mix_Chunk* loadSoundFromFile( std::string );

		Mix_Music* loadMusicFromFile( std::string );

	private:

};

#endif // INC_CSDLSOUND_H
