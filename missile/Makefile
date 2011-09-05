all:
	g++ -O3 -march=native -fomit-frame-pointer -fexpensive-optimizations -funroll-loops -o missile missile.cpp
	strip missile

debug:
	g++ -ggdb3 -DDEBUG -o missile missile.cpp
