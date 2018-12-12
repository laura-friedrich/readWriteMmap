CFLAGS= -Wall -pedantic -g -fPIC

.PHONY: all
all: test-myio

.PHONY: run
run: test-myio
	LD_LIBRARY_PATH=. ./test-myio

libmymmapio.so: mymmapio.c myio.h
	gcc -shared -Wl,-soname,$@ -o $@ $^

test-myio: test-myio.o libmymmapio.so
	gcc -L. -lmymmapio -o $@ $<

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -f *.o libmymmapio.so test test2 test-myio
