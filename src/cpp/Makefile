CC=gcc
INCDIR=/usr/local/include
LIBDIR=/usr/local/lib
#LIBS=-lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lwiringPi
LIBS=-lstdc++ -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lmosquitto -lserialport
DEFS+=-D_HAS_SERIAL
#DEFS+=-D_HAS_GUI
#DEFS+=-D_HAS_MQTT
GLOBALS=Makefile

all:videostream stop serialtest

videostream:videostream.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o videostream videostream.cpp $(LIBS)

serialtest:serialtest.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o serialtest serialtest.cpp -lstdc++ -lserialport

stop:stop.cpp $(GLOBALS)
	$(CC) $(DEFS) -I $(INCDIR) -L $(LIBDIR) -ggdb -o stop stop.cpp $(LIBS)
