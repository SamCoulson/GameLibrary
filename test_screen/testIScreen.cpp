#include "../CSDLGraphics.h"
#include "../IScreen.h"
#include <stdio.h>
#include <assert.h>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

class CScreenOne : public IScreen{

public:
	CScreenOne( CSDLGraphics& graphics ) : IScreen( graphics ){};
	~CScreenOne(){};

	bool init(){ printf("initialising screen one..\n"); return true; }
	void cleanUp(){printf("cleaning up screen one...\n"); }
	void update(){ printf("updating screen one...\n"); }
	void render(){ printf("rendering screen one...\n"); }
	void processEvents( SDL_Event* event ){ printf("processing events for screen one...\n"); }
	bool isPaused(){ printf("pausing screen one...\n"); return true; }
	bool requestQuit(){ printf("requesting quit for screen one...\n");return true; }

private:	
	
};

class CScreenTwo : public IScreen{

	public:
	CScreenTwo( CSDLGraphics& graphics ) : IScreen( graphics ){};
	~CScreenTwo(){};

	bool init(){ printf("initialising screen two..\n"); return true; }
	void cleanUp(){printf("cleaing up screen two...\n"); }
	void update(){ printf("updating screen two...\n"); }
	void render(){ printf("rendering screen two...\n"); }
	void processEvents( SDL_Event* event ){ printf("processing events for screen two...\n"); }
	bool isPaused(){ printf("pausing screen two...\n"); return true; }
	bool requestQuit(){ printf("requesting quit for screen two...\n");return true; }	
	
};

class CScreenThree : public IScreen{

	public:
	CScreenThree( CSDLGraphics& graphics ) : IScreen( graphics ){};
	~CScreenThree(){};

	bool init(){ printf("initialising screen three..\n"); return true; }
	void cleanUp(){printf("cleaing up screen three...\n"); }
	void update(){ printf("updating screen three...\n"); }
	void render(){ printf("rendering screen three...\n"); }
	void processEvents( SDL_Event* event ){ printf("processing events for screen three...\n"); }
	bool isPaused(){ printf("pausing screen three...\n"); return true; }
	bool requestQuit(){ printf("requesting quit for screen three...\n");return true; }	
	
};
CSDLGraphics *graphics = NULL;
IScreen *screenOne = NULL;
IScreen *screenTwo = NULL;
IScreen *screenThree = NULL;
SDL_Event event;

void setup(){
	graphics = new CSDLGraphics();
	screenOne = new CScreenOne( *graphics );
	screenTwo = new CScreenTwo( *graphics );
	screenThree = new CScreenThree( *graphics );

}

void cleanup(){	

	if( graphics != NULL ){
		graphics->shutdown();
	}
	delete graphics;

	if( screenOne != NULL ){
		delete screenOne;
	}

	if( screenTwo != NULL ){
		delete screenTwo;
	}
	
	if( screenThree != NULL ){
		delete screenThree;
	}
}

int main( int argc, char* argv[] ){
	
	// Re-direct output to console as SDL will disable it
	/* Note: Assert output to STDERR so must also be redirected*/		
	freopen( "CON" ,"w", stderr ); 
	freopen( "CON" ,"w", stdout );
	
	// Test single class of Abstract Base Class type IScreen	
	setup();
	screenOne->init();
	screenOne->processEvents( &event );
	screenOne->update();
	screenOne->render();
	screenOne->isPaused();
	screenOne->requestQuit();
	cleanup();

	// Test multiple classes of type IScreen in vector
	setup();

	std::vector< IScreen* > screens;

	screens.push_back( screenOne );
	screens.push_back( screenTwo );
	screens.push_back( screenThree );

	for( std::vector< IScreen* >::iterator it = screens.begin(); it != screens.end(); ++it  ){
	
		(*it)->init();
		(*it)->processEvents( &event );
		(*it)->update();
		(*it)->render();
		(*it)->isPaused();
		(*it)->requestQuit();
	}	

	cleanup();

	return 0;
}
