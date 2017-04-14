CC=g++

CFLAGS=-Wall -std=c99 

LDFLAGS=

TARGET=-o testCSDLSound 

SDIR=src

ODIR=obj
	  
testCSDLSound : testCSDLSound.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} testCSDLSound.o -lmingw32 -lSDLmain -L.. -lgamelib -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer  
clean:
	-del *.o
	-del testCSDLSound.exe
