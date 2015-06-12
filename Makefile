all:
	g++ -std=c++11 -c -o functions.o functions.cpp
	g++ -std=c++11 -c -o solve.o solve.cpp 
	g++ -std=c++11 -o solve solve.o functions.o

run:
	./solve set_test.txt
