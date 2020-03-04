CC=gcc
CFLAGS=-c -Wall
SOURCES=main1.c game_init.c game_logic.c
OBJ=main1.o game_init.o game_logic.o
HFILES=game_init.h game_logic.h
EXEC=main

all: main

main: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o main
