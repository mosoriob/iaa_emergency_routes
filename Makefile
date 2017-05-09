all:
	g++ -std=c++11 -c -o functions.o functions.cpp
	g++ -std=c++11 -c -o solve.o solve.cpp 
	g++ -std=c++11 -o solve solve.o functions.o

time:
	g++ -std=c++11 -c -o functions.o functions.cpp
	g++ -std=c++11 -c -o solve-time.o solve-time.cpp 
	g++ -std=c++11 -o solve-time solve-time.o functions.o

size:
	g++ -std=c++11 -c -o functions.o functions.cpp
	g++ -std=c++11 -c -o solve-size.o solve-size.cpp 
	g++ -std=c++11 -o solve-size solve-size.o functions.o

clean:
	rm solve solve-size solve-time *.o
