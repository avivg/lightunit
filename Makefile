
.PHONY: all

all: test

test: basic_example.c
	gcc -o $@ $^ -I.
