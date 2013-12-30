#include "../CSDLGraphics.h"
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
	/* Note: Assert output to STDERR so must also be redirected*/		
	freopen( "CON" ,"w", stderr ); 
	freopen( "CON" ,"w", stdout );

	
	return 0;
}
