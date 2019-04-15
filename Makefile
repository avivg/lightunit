
CFLAGS ?= -Wall -Werror -pedantic -ansi

.PHONY: all clean run_test

all: test.out readme.out

test.out: examples/test_example.c lightunit.h
	$(CC) -o $@ $< -I. $(CFLAGS)

readme.out: examples/readme_example.c lightunit.h
	$(CC) -o $@ $< -I. $(CFLAGS)

clean:
	rm -f test.out readme.out

run_test: test.out
	valgrind --leak-check=full --error-exitcode=2 ./test.out