starts="25 44"

for i in $(ls instances/peuco/); do
	for start in $starts; do 
		for s in $(head -n 200 seeds.txt ); do 
			bash run.sh instances/peuco/$i $s $start >> results/starts/${start}-${i};
		done
	done
done