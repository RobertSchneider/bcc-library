SRC = bcc.cpp
OBJS = $(SRC:.cpp=.o)
CLEAN = rm
INSTALLDIR = /usr/lib/
LIBNAME = libbcc.so
INCLUDES = -I. -I ./include/
CCFLAGS = -fPIC
CCLIBFLAG = -shared
CC = gcc

.SUFFIXES: .cpp
default: build clean

build:
	$(CC) $(INCLUDES) $(CCFLAGS) -c $(SRC)
	$(CC) $(CCLIBFLAG) -o $(LIBNAME) $(OBJS)

clean:
	$(CLEAN) $(OBJS)

install:
	mv $(LIBNAME) $(INSTALLDIR)
