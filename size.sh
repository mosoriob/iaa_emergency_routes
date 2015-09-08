g++ -std=c++11 -c -o functions.o functions.cpp
g++ -std=c++11 -c -o solve-size.o solve-size.cpp 
g++ -std=c++11 -o solve-size solve-size.o functions.o
for i in {1..20}; do ./solve-size $1; done 

