CC=gcc
CFLAGS=-g -Wall
IFLAGS=-I ./include
SRC=src
LFLAGS=
BIN=bin
SORTO=mv *.o -t ./bin
SORTC=mv *.c -t ./src
SORTH=mv *.h -t ./include

COMPILE=$(CC) $(CFLAGS) $(IFLAGS) -c $(SRC)/*.c 

PARSEDIR=parser

all: parser game
	$(CC) $(CFLAGS) $(BIN)/*.o -o $(BIN)/main

generated-code:
	cd $(PARSEDIR); flex *.lex; bison -d *.y
	cd $(PARSEDIR); $(SORTC); $(SORTH)

parser: generated-code
	cd $(PARSEDIR); $(COMPILE); $(SORTO)

game:
	$(COMPILE)
	$(SORTO)
