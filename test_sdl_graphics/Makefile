CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=

TARGET=-o testCSDLGraphics 

SDIR=src

ODIR=obj
	  
testCSDLGraphics : ../CSDLGraphics.o testCSDLGraphics.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} ../CSDLGraphics.o testCSDLGraphics.o -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_image   
clean:
	-del $(SDIR)/*.o
	-del testCSDLGraphics.exe
