CC=gcc
INCDIR=/usr/local/include
LIBDIR=/usr/local/lib
#LIBS=-lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lwiringPi
LIBS=-lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc
#DEFS=-D_HAS_SERIAL
#DEFS=-D_HAS_GUI
GLOBALS=Makefile

all:videostream

videostream:videostream.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o videostream videostream.cpp $(LIBS)


