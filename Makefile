SRC = bcc.cpp
OBJS = $(SRC:.cpp=.o)
CLEAN = rm
LIBNAME = libbcc.so
INCLUDES = -I. -I ./include/
CCFLAGS = -fPIC
CCLIBFLAG = -shared
CCC = gcc

.SUFFIXES: .cpp
default: build clean

build:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $(SRC)
	$(CCC) $(CCLIBFLAG) -o $(LIBNAME) $(OBJS)

clean:
	$(CLEAN) $(OBJS)
