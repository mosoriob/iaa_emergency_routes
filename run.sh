instance=$1
loops=100
candidateList=15
ants=20
alpha_ant=2.92
beta_ant=9.83
q_0=0.55
ro=0.97
tau=1
seed=$2
s=$3



./solve-time $instance $loops $candidateList $ants $alpha_ant $beta_ant $q_0 $ro $tau $seed $s
