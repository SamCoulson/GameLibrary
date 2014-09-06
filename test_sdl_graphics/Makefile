CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=

TARGET=-o testCSDLGraphics 

SDIR=src

ODIR=obj
	  
testCSDLGraphics : testCSDLGraphics.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} testCSDLGraphics.o -lmingw32 -lSDLmain -L.. -lgamelib -lSDL -lSDL_ttf -lSDL_image   
clean:
	-del *.o
	-del testCSDLGraphics.exe
