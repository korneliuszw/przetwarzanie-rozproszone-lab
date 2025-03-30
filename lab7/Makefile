SDIR=.
IDIR=pqueue/include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

ODIR=build
LIBS=-lpthread

_DEPS=pqueue.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o pqueue.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: main

clean:
	rm -rf $(ODIR) main

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/pqueue.o: pqueue/pqueue.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS) -I./pqueue

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

