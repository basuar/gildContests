all:
	gcc -O3 -march=native -std=gnu99 -s -static -o netconnections netconnections.c
debug:
	gcc -ggdb3 -march=native -std=gnu99 -static -o netconnections netconnections.cpp
