CC=gcc

CFLAGS=-Wall -Wextra -Ofast
LFLAGS=-s

OBJS=main.o vector.o xml.o tokenizer.o
DEPS=vector.h xml.h tokenizer.h

BIN=xml_test

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)
