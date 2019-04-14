
.PHONY: all

all: test

test: basic_example.c
	gcc -o $@ $^ -Iclist/clistlib/include -I. -L clist/clistlib/bin -lclist
