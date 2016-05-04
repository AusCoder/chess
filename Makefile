
# 
# Makefile
#

CC  = g++
CXX = g++
CPP_DIR=

# header file includes
INCLUDES = 

CFLAGS   = -std=c++14 -g -Wall $(INCLUDES)
CXXFLAGS = -std=c++1y -g -Wall $(INCLUDES)

# linking options
LDFLAGS = -g
# linking libraries
LDLIBS  =

executables =  chess
objects = chess_engine.o

.PHONY: default
default: $(executables)

$(executables): $(objects)
	$(CXX) $(LDFLAGS) -o chess $(objects)

$(objects):

test:

.PHONY: clean
clean:
	rm -f *~ a.out core $(objects) $(executables)

.PHONY: all
all: clean default

