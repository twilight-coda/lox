# -*- MakeFile -*-

CC=clang
INCDIRS=-I.
CFLAGS=-g -Wall -Wextra $(INCDIRS)
OBJECTS=main.o chunk.o memory.o debug.o value.o vm.o
BIN=lox

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) -g $(OBJECTS) -o $(BIN)

%.o: %.c common.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJECTS) lox
