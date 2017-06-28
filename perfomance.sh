rm results/best/*
for i in $(ls instances/yuan-wang/); do
	echo $i
	for s in $(head -n 200 seeds.txt ); do 
		bash run.sh instances/yuan-wang/$i $s >> results/best/yuan-$i ;
	done
done

for i in $(ls instances/peuco/); do
	echo $i
	for s in $(head -n 200 seeds.txt ); do 
		bash run.sh instances/peuco/$i $s >> results/best/peuco-$i ;
	done
done

