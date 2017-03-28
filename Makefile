all:
	g++ -std=c++11 main.cpp -c
	g++ -std=c++11 main.o -lglpk -lm -o main.exe