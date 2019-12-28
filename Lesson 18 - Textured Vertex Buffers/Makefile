OBJS=util.c main.c texture.c
CC=clang
CFLAGS=-Wall -ggdb
LDFLAGS=-lGL -lGLU -lglut -lIL -lILU
OUT=main

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(OUT)
