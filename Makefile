all: 
	g++ -std=c++11 src/main.cpp -Ofast -Wall -c -g
	g++ -std=c++11 main.o -lglpk -lm -o main.exe

clean:
	rm -rf *.o *.exe