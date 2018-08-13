##############################################################################
# Student Name    : Federick Kwok
# RMIT Student ID : s3666874
# COURSE CODE     : CPT220
# 
# Startup code provided by Paul Miller for use in "Programming in C", 
# study period 2, 2018.
#############################################################################

SOURCES=board.c game.c gomoku.c io.c player.c rules.c
HEADERS=board.h game.h gomoku.h  io.h player.h rules.h shared.h 
OBJECTS=board.o game.o gomoku.o io.o player.o rules.o 
CC=gcc
LDFLAGS=
CFLAGS=-Wall -ansi -pedantic

all:gomoku

gomoku: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

debug:CFLAGS+=-DDEBUG -g
debug:clean all

sanitize:CFLAGS+=-DDEBUG -g -fsanitize=address
sanitize:LDFLAGS+=-fsanitize=address
sanitize:clean all

.PHONY:clean
clean:
	rm -f $(OBJECTS) gomoku


