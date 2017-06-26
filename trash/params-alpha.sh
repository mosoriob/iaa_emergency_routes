testFile1="ev-100-15-100-0.01-2-0.5-0.1"
testFile2="ev-100-15-100-0.1-2-0.5-0.1"
testFile3="ev-100-15-100-0.5-2-0.5-0.1"
testFile4="ev-100-15-100-1-2-0.5-0.1"
testFile5="ev-100-15-100-2-2-0.5-0.1"


# rm results/peuco_best/$testFile1
# rm results/peuco_best/$testFile2
# rm results/peuco_best/$testFile3
rm results/peuco_best/$testFile4
rm results/peuco_best/$testFile5

# for i in {1..40}; do 
# 	bash time.sh instances/peuco/peuco1.txt 100 15 100 0.01 2 0.5 0.5 0.1 >> results/peuco_best/$testFile1; 
# done


# for i in {1..40}; do 
# 	bash time.sh instances/peuco/peuco1.txt 100 15 100 0.1 2 0.5 0.5 0.1 >> results/peuco_best/$testFile2; 
# done

# for i in {1..40}; do 
# 	bash time.sh instances/peuco/peuco1.txt 100 15 100 0.5 2 0.5 0.5 0.1 >> results/peuco_best/$testFile3; 
# done

for i in {1..40}; do 
	bash time.sh instances/peuco/peuco1.txt 100 15 100 1 2 0.5 0.5 0.1 >> results/peuco_best/$testFile4; 
done


for i in {1..40}; do 
	bash time.sh instances/peuco/peuco1.txt 100 15 100 2 2 0.5 0.5 0.1 >> results/peuco_best/$testFile5; 
done
