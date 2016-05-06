
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
LDLIBS  =  -lncurses

executables =  chess
objects = chess_engine.o graphics.o util.o #legal_move.o

.PHONY: default
default: $(executables)

$(executables): $(objects)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o chess $(objects)

$(objects):

unit_tests: util.o

.PHONY: clean
clean:
	rm -f *~ a.out core $(objects) $(executables) unit_tests 

.PHONY: all
all: clean default

