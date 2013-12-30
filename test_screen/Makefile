CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=

TARGET=-o testIScreen 

SDIR=src

ODIR=obj
	  
testCGrid : ../CSDLGraphics.o testIScreen.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} ../CSDLGraphics.o testIScreen.o -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_image   
clean:
	-del *.o
	-del testIScreen.exe
