////////////////////////////////////////////////////////////////////////////////////
//  Generic 'main' source file for use with test bed projects.					  //
//  This file most only be copied and MUST NOT be modfied.	
////////////////////////////////////////////////////////////////////////////////////

#include "../include/CSDLGraphics.h"
#include "../include/CCollision.h"
//#include "CTimer.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 24

#define FPS 30

// Global objects
CSDLGraphics* graphics;
CCollision* collide;

SDL_Surface* ball;
SDL_Rect objB;
int ballVelX;
int ballVelY;

SDL_Surface* brick;
SDL_Rect objA;
int brickVelX;
int brickVelY;
//CTimer fps;

bool run_app = true;

SDL_Event event;

int ballspeed = 2;
int frame = 0;
bool cap = true;
bool isCollided = false;

void OnRender();
void OnUpdate();
void HandleEvents();

// Rects used for collidion detection

int main(int argc, char* argv[]){
	
	// Create SDL objects
	graphics = new CSDLGraphics(); 

	// Intialise SDL, setup subsystems
	if(!graphics->initialise( SCREEN_WIDTH, SCREEN_HEIGHT, 24, SDL_SWSURFACE, "Collision detection" ))
	{
		std::cout << "Could not initialise SDL object" << std::endl;
		SDL_Quit();
		return false;
	}

	collide = new CCollision();
	
	brick = graphics->loadImageFromFile( "./images/BBlockYellow.png", 255, 0, 255 );	
	ball = graphics->loadImageFromFile( "./images/GameBall.png", 255, 0, 255 );

	ballVelX = ballspeed;
	ballVelY = ballspeed;	
	
	objA.x = 300;
	objA.y = 200;	 
	objA.w = brick->w;
	objA.h = brick->h;

	objB.x = 10;
	objB.y = 10;	 
	objB.w = ball->w;
	objB.h = ball->h;

	while( run_app )
	{
		//fps.StartTimer();

		HandleEvents();
	
		OnUpdate();

		OnRender();
/*
		if( (cap == true) && fps.GetElapsedTime() < 1000 / FPS)
		{
		//	SDL_Delay( 1000 / FPS - fps.GetElapsedTime() );
		}
*/
	}

	SDL_Quit();

	return 0;
}

void OnRender(){

	graphics->clearScreen( 0, 0, 0 );

	graphics->draw( objA.x, objA.y, brick, SDL_GetVideoSurface(), NULL );	
	graphics->draw( objB.x, objB.y, ball, SDL_GetVideoSurface(), NULL );

	if( isCollided == true )
	{
		graphics->fillRect( objB.x, objB.y, objB.w, objB.h, 255, 0, 0 );
		isCollided = false;
	}

	graphics->update();
}

void OnUpdate(){
		
	// Ball edge of screen bounce logic
	if( objB.y < 0)
	{
		ballVelY += ballspeed;
	}
	
	if( objB.y + objB.h > 480 )
	{
		ballVelY += -ballspeed;
	}
	
	if( objB.x < 0)
	{
		ballVelX += ballspeed;
	}
	
	if( objB.x + objB.w >  640 )
	{
		ballVelX += -ballspeed;
	}

	// Object-to-object collision
	int EdgeOfCollision = 0;
	
	if( collide->CheckCollide(objA, objB) == true)
		{
			//EdgeOfCollision = g_pCollide->CollisionEdge(objB, objA);
			//EdgeOfCollision = collide->CheckCollideAABB(objB, objA );
	EdgeOfCollision = collide->CollisionEdge( objB, objA );

			switch( EdgeOfCollision )
			{
			case TOP_EDGE:
				{
					ballVelY += -ballspeed;
					isCollided = true;
					break;
				}
			case BOTTOM_EDGE:
				{
					ballVelY += ballspeed;
					isCollided = true;
					break;
				}
			case LEFT_EDGE:
				{
					ballVelX += -ballspeed;
					isCollided = true;
					break;
				}
			case RIGHT_EDGE:
				{
					ballVelX += ballspeed;
					isCollided = true;
					break;
				}
			default:
				break;
			}
			
	}
	
	objB.x += ballVelX;
	objB.y += ballVelY;

}

void HandleEvents()
{
	SDL_PollEvent( &event );

	if( event.key.state == SDL_PRESSED) 
	{
		switch( event.key.keysym.sym )
		{
		case SDLK_F11 :
			cap ? cap = false : cap = true;
			break;
		case SDLK_ESCAPE :
			run_app = false;
			break;
		default :
			break;
		}
	}
	event.key.state = SDL_KEYUP;
	if( event.type == SDL_QUIT )
	{
		run_app = false;
	}

}
