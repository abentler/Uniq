CC = gcc
CFLAGS = -ansi -Wall -pedantic

all: uniq

uniq: uniq.c
	$(CC) $(CFLAGS) -o uniq uniq.c

test: uniq
	./uniq test

clean:
	rm -f uniq.o

