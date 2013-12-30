CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=

TARGET=-o testCGrid 

SDIR=src

ODIR=obj
	  
testCGrid : ../CSDLGraphics.o ../CGrid.o testCGrid.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} ../CSDLGraphics.o ../CGrid.o testCGrid.o -lmingw32 -lSDLmain -lSDL -lSDL_ttf -lSDL_image   
clean:
	-del *.o
	-del testCGrid.exe
