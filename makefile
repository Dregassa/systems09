all: main.c
	gcc -o ls_test main.c

run: all
	./ls_test
