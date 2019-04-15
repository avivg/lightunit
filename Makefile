
CFLAGS ?= -Wall -Werror -pedantic -ansi

.PHONY: all

all: test

test: basic_example.c lightunit.h
	gcc -o $@ $< -I. $(CFLAGS)
