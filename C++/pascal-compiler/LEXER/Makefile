BINFOLDER := bin
INCFOLDER := include
SRCFOLDER := src
OBJFOLDER := obj
BINFILE := compiler 

CC := g++
CFLAGS := -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self

SRCFILES := $(wildcard src/*.cpp)

all: $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) $(CFLAGS) $(OBJFOLDER)/*.o -o $(BINFOLDER)/$(BINFILE)

obj/%.o: $(SRCFOLDER)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I./$(INCFOLDER)

.PHONY: clean
clean:
	rm -rf $(OBJFOLDER)/*
	rm -rf $(BINFOLDER)/*

run:
		$(BINFOLDER)/$(BINFILE)
