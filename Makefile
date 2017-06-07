all:
	g++ -std=c++11 -c -o functions.o functions.cpp
	g++ -std=c++11 -c -o solve-time.o solve-time.cpp 
	g++ -std=c++11 -o solve-time solve-time.o functions.o


clean:
	rm solve-time *.o
