all:
	gcc -O3 -march=native -std=c99 -o bowling bowling.c
	strip bowling
