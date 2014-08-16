CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=

TARGET=-o testCCollision 

SDIR=src

ODIR=obj
	  
testCCollision : testCCollision.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} testCCollision.o -lmingw32 -L.. -lgamelib -lSDLmain -lSDL -lSDL_ttf -lSDL_image   
clean:
	-del *.o
	-del testCCollision.exe
