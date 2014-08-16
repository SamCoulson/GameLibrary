CC=g++

CFLAGS=-c -Wall -std=c99 

LDFLAGS=

TARGET=-o gamelib.o

SDIR=src

ODIR=obj
	  
gamelib : src/csdlgraphics.o src/ccollision.o src/cgrid.o
	${CC} ${CFLAGS} ${LDFLAGS} ${TARGET} src/csdlgraphics.o src/ccollision.o src/cgrid.o
	ar rcs libgamelib.a src/csdlgraphics.o src/ccollision.o src/cgrid.o

clean:
	-del *.o
