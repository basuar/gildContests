all:
	g++ -O3 -march=native -o bowling bowling.cpp
	strip bowling
