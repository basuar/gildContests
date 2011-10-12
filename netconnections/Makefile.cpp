all:
	g++ -O3 -march=native -std=c++0x -s -static -o netconnections netconnections.cpp
debug:
	g++ -ggdb3 -march=native -std=c++0x -static -o netconnections netconnections.cpp
