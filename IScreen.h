#ifndef H_CSCREENBASE_INC
#define H_CSCREENBASE_INC

#include "SDL_Events.h"
#include "CSDLGraphics.h"
//class CScreenManager; // Forward delcare here for base class but include the header in the derived class to access the member functions.
					// All that happens here is that you say that a class exists called CScreenManager but nothing is know about it's members.
//extern IRenderInterface* g_pRender;
/*
enum KBInputKeys
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_SPACE,
	BUTTON_ENTER,
	BUTTON_F11,
	BUTTON_ESCAPE,
	BUTTON_S,
	BUTTON_A,
	BUTTON_M
};
*/
class IScreen
{
public:
	IScreen(){};
	virtual ~IScreen(){};

	// Hold screen entities
	//CEntityManager scrnEntityManager;

	// Pointer to parent screen manager
	//CScreenManager* scrnManager;

	//unsigned int screenID; 

	// Init is used to register all the required sprite objects the screen with entity manager,
	// set up any variables and data structures needed for the current screen.
	virtual bool init() = 0;

	virtual void cleanUp() = 0;

	// Called to update the (model) data, or screen objects, also does collisions.
	virtual void update() = 0;

	virtual void render() = 0;

	virtual void processEvents( SDL_Event* ) = 0;

	virtual bool requestQuit() = 0;

	// Used by screen manager to allocate screen ID's and retrieve them
	//void SetScreenID(unsigned int scrnID){ screenID = scrnID; }
	//unsigned int GetScreenID(){ return screenID; }

	//void SetScreenManager(CScreenManager& scrnMan){ scrnManager = &scrnMan; }

private:

};


#endif // H_CSCREENBASE_INC
