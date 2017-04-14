CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=

TARGET=-o testCGrid 

SDIR=src

ODIR=obj
	  
testCGrid : testCGrid.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} testCGrid.o -lmingw32 -L.. -lgamelib -lSDLmain -lSDL -lSDL_ttf -lSDL_image   
clean:
	-del *.o
	-del testCGrid.exe
