testFile1="ev-100-15-10-1-2-0.5-0.1"
testFile2="ev-100-15-50-1-2-0.5-0.1-100"
testFile3="ev-100-15-100-1-2-0.5-0.1-100"

rm results/peuco_best/$testFile1
rm results/peuco_best/$testFile2
rm results/peuco_best/$testFile3

for i in {1..40}; do 
	bash time.sh instances/peuco/peuco1.txt 200 15 10 1 2 0.5 0.5 0.1 >> results/peuco_best/$testFile1; 
done


for i in {1..40}; do 
	bash time.sh instances/peuco/peuco1.txt 40 15 50 1 2 0.5 0.5 0.1 >> results/peuco_best/$testFile2; 
done

for i in {1..40}; do 
	bash time.sh instances/peuco/peuco1.txt 20 15 100 1 2 0.5 0.5 0.1 >> results/peuco_best/$testFile3; 
done

for i in {1..40}; do 
	bash time.sh instances/peuco/peuco1.txt 10 15 200 1 2 0.5 0.5 0.1 >> results/peuco_best/$testFile3; 
done
