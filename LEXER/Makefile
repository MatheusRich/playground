BINFOLDER := bin/
INCFOLDER := include/
SRCFOLDER := src/
OBJFOLDER := obj/

CC := g++
CFLAGS := -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self

SRCFILES := $(wildcard src/*.cpp)

all: $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) $(CFLAGS) obj/*.o -o bin/compiler

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I./$(INCFOLDER)

.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*

run:
		bin/binario
