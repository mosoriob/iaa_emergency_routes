#!/bin/bash

for j in $(seq 0.8 0.05 1);
do  
best=$(for i in {1..30}; do ./solve grade1.txt $j 3.136548 4; done | sort | head -n 1)
echo $j $best

done

#best=$(for i in {1..20}; do ./solve grade1.txt $j 3.136548 4; done | sort | head -n 1)
#best=$(for i in {1..20}; do ./solve grade2.txt $j 3.480311 4; done | sort | head -n 1)
#best=$(for i in {1..20}; do ./solve grade3.txt $j 4.544814 4; done | sort | head -n 1)
#best=$(for i in {1..20}; do ./solve grade4.txt $j 6.36513 4; done | sort | head -n 1)
#best=$(for i in {1..20}; do ./solve grade5.txt $j 12.323639 4; done | sort | head -n 1)
