CC=gcc
CFLAGS=-ggdb -std=c99 # -Wall -Wextra 
LDFLAGS=-lSDL2 -lSDL2_ttf

TARGET_NAME=sliding-game

all: src/main.c
	$(CC) $(CFLAGS) src/main.c -o $(TARGET_NAME) $(LDFLAGS)


run:
	./$(TARGET_NAME)
