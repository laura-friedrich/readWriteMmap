CFLAGS= -Wall -pedantic -g -fPIC

.PHONY: all
all: test-myio

test-myio: test-myio.o mymmapio.o
	gcc -shared -Wl,-soname,libmyio.so -o libmyio.so mymmapio.o
	gcc -L. -lmyio -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -f test-myio.o mymmapio.o test-myio test test2
