instance=$1
loops=200
candidateList=15
ants=10
alpha_ant=1
beta_ant=2
q_0=0.5
ro=0.5
tau=0.1
seed=$2
s=1

./solve-time $instance $loops $candidateList $ants $alpha_ant $beta_ant $q_0 $ro $tau $seed $s
