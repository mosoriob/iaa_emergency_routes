all:
	g++ -std=c++11 -O3 -c -o functions.o functions.cpp
	g++ -std=c++11 -O3 -c -o solve.o solve.cpp 
	g++ -std=c++11 -O3 -o solve solve.o functions.o

time:
	g++ -std=c++11 -O3 -c -o functions.o functions.cpp
	g++ -std=c++11 -O3 -c -o solve-time.o solve-time.cpp 
	g++ -std=c++11 -O3 -o solve-time solve-time.o functions.o

size:
	g++ -std=c++11 -O3 -c -o functions.o functions.cpp
	g++ -std=c++11 -O3 -c -o solve-size.o solve-size.cpp 
	g++ -std=c++11 -O3 -o solve-size solve-size.o functions.o
