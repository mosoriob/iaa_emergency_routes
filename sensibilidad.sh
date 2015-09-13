#!/bin/bash

for j in $(seq 0.8 0.05 1);
do  
best=$(for i in {1..30}; do ./solve grade1.txt $j 3.136548 4; done | sort | head -n 1)
echo $j $best

done