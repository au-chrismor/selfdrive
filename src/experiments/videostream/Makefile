CC=gcc
INCDIR=/usr/local/include
LIBDIR=/usr/local/lib
LIBS=-lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lwiringPi
DEFS=-D_HAS_SERIAL
GLOBALS=Makefile

all:	videostream

videostream:	videostream.cpp $(GLOBALS)
	$(CC) -I $(INCDIR) -L $(LIBDIR) -ggdb -o videostream videostream.cpp $(LIBS)

