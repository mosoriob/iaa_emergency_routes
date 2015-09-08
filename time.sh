g++ -std=c++11 -c -o functions.o functions.cpp
g++ -std=c++11 -c -o solve-time.o solve-time.cpp 
g++ -std=c++11 -o solve-time solve-time.o functions.o
for i in {1..20}; do ./solve-time $1; done  
