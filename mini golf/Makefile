CC=g++
FLAGS=-O1 -Wall -Wno-missing-braces -Iinclude/ -Llib/ -lraylib -lopengl32 -lgdi32 -lwinmm

all: game
	game

nog: game

game: main.o hole.o player.o
	$(CC) $^ -o $@ $(FLAGS)

main.o: main.cpp
	$(CC) -c main.cpp

hole.o: hole.cpp include/hole.h
	$(CC) -c hole.cpp

player.o: player.cpp include/player.h 
	$(CC) -c player.cpp

clean:
	del game.exe .\*.o

clean_obj:
	del .\*.o
