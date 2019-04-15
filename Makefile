
CFLAGS ?= -Wall -Werror -pedantic -ansi

.PHONY: all clean

all: test.out readme.out

test.out: examples/test_example.c lightunit.h
	$(CC) -o $@ $< -I. $(CFLAGS)

readme.out: examples/readme_example.c lightunit.h
	$(CC) -o $@ $< -I. $(CFLAGS)

clean:
	rm -f test.out readme.out