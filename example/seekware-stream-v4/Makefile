
INCFLAG		+= -I./include
DEBUGFLAG	= -g -O0 -Wall
CFLAGS		+= $(DEBUGFLAG) $(INCFLAG)
LDFLAGS	    	+= -lseekware -lSDL2 `pkg-config --libs libusb-1.0`
CXXFLAGS	+= $(CFLAGS)
CPPFLAGS	+= $(CFLAGS)

TARGET	= seekware-stream
OBJECTS	= objs/seekware-stream.o

TARGET2	= seekware-tcpip
OBJECTS2 = objs/seekware-tcpip.o

all: $(TARGET) $(TARGET2)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDPATH) $(LDFLAGS)

$(TARGET2): $(OBJECTS2)
	$(CXX) -o $@ $(OBJECTS2) $(LDPATH) $(LDFLAGS)

objs/%.o:	src/%.cpp
	@if test ! -e objs; then \
		mkdir objs  ;\
	fi;
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/%.o:	src/%.c
	@if test ! -e objs; then \
		mkdir objs  ;\
	fi;
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf core *~  $(TARGET) $(TARGET2) $(OBJECTS) $(LIB) $(LIBOBJ) src/*~ include/*~ 
