OBJS=util.c main.c texture.c
CC=clang
CFLAGS=-Wall
LDFLAGS=-lGL -lGLU -lglut -lIL -lILU
OUT=main

all: $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(OUT)
