CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=

TARGET=-o testIScreen 

SDIR=src

ODIR=obj
	  
testIScreen : testIScreen.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} testIScreen.o -lmingw32 -L.. -lgamelib -lSDLmain -lSDL -lSDL_ttf -lSDL_image   
clean:
	-del *.o
	-del testIScreen.exe
