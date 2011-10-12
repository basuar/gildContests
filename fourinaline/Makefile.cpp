all:
	g++ -O3 -march=native -std=c++0x -fno-rtti -fno-exceptions -fsched-spec-load-dangerous -funsafe-loop-optimizations -s -static -o fourinaline fourinaline.cpp
