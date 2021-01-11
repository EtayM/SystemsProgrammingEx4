CC=gcc
CFLAGS=-Wall -g
PHONY=all clean
PROGS=frequency

.PHONY: $(PHONY)

all: $(PROGS)

frequency: frequencyMain.o frequency.o
	$(CC) $(CFLAGS) frequencyMain.o frequency.o -o frequency

frequencyMain.o: frequency.h frequencyMain.c
	$(CC) $(CFLAGS) -c frequencyMain.c

frequency.o: frequency.h frequency.c
	$(CC) $(CFLAGS) -c frequency.c

clean:
	rm -f *.o $(PROGS)