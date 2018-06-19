#game of life makefile
CC = g++

#define flags for compiling
CFLAGS  = -g -Wall -std=c++11

CURSES = -lncurses

#directory for other files
DEPS = ./UI/mainUI.h ./program/backend.h

SRCS = main.cpp program/backend.cpp UI/mainUI.cpp
OBJS = $(SRCS:.cpp=.o)

EXE = life

all: $(SRCS) $(DEPS)
	$(CC) $(CFLAGS) -o $(EXE) $^ $(CURSES)

clean:
	rm -rf $(EXE)

.PHONY: clean
