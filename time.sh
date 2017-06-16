#bash time.sh instances/yuan-wang/grade4.txt 100 15 10 1 2 0.5 0.5 0.1
#g++ -std=c++11 -c -o functions.o functions.cpp
#g++ -std=c++11 -c -o solve-time.o solve-time.cpp 
#g++ -std=c++11 -o solve-time solve-time.o functions.o
instance=$1
loops=$2
cl=$3
M=$4
alpha_ant=$5
beta_ant=$6
q_0=$7
ro=$9
tau_0=$9
./solve-time $instance $loops $cl $M $alpha_ant $beta_ant $q_0 $ro $tau_0
