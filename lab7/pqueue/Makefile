CC=gcc
CFLAGS=-Wall -fPIC -I./include

all: libpqueue.a libpqueue.so

libpqueue.a: pqueue.o
	$(CC) -r -c $@ $^

libpqueue.so: pqueue.o
	$(CC) -shared -o $@ $^

pqueue.o: pqueue.c include/pqueue.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *.a *.so 