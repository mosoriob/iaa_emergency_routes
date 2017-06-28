#!/bin/bash

bench=$1
outfile=outparamils
rm -rf ${outfile} ${outfile}.tmp ${outfile}.tmp2
seed=$5

#input_file = ARGV[0]
#instance_specifics = ARGV[1]
#timeout = ARGV[2].to_i
#cutoff_length = ARGV[3].to_i
#seed = ARGV[4].to_i

shift 5

while [ $# != 0 ]; do
    flag="$1"
    case "$flag" in
        -algorithm) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              temp=$arg
              case "$temp" in
                  1) algorithm=as;;
                  2) algorithm=mmas;;
                  3) algorithm=eas;;
                  4) algorithm=ras;;
                  5) algorithm=acs;;
              esac
            fi
            ;;
        -localsearch) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              localsearch=$arg
            fi
            ;;
        -alpha) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              alpha=$arg
            fi
            ;;
        -tau) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              tau=$arg
            fi
            ;;
        -beta) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              beta=$arg
            fi
            ;;
        -rho) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              rho=$arg
            fi
            ;;
        -ants) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              ants=$arg
            fi
            ;;
        -nnls) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              nnls=$arg
            fi
            ;;           
        -q0) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              q0=$arg
            fi
            ;;
        -dlb) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              dlb=$arg
            fi
            ;;            
        -rasrank) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              rasrank=$arg
            fi
            ;;             
        -elitistants) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              elitistants=$arg
            fi
            ;;
        *) echo "Unrecognized flag or argument: $flag"
            ;;
        esac
    shift
done


tries=1
#tours=100 -s ${tours}
#nnants=10 -g ${nnants}
ttime=5

echo " ./solve-time ${bench} 100 15 ${ants} ${alpha} ${beta} ${q0} ${rho} ${tau} ${seed} 1"
./solve-time ${bench} 100 15 ${ants} ${alpha} ${beta} ${q0} ${rho} ${tau} ${seed} 1 > $outfile.tmp
#tail -3 ${outfile}.tmp | head -1 | awk '{print $4}' > ${outfile}.tmp2
#fitness=`head -1 ${outfile}.tmp2 | sed -e 's/,/ /g'`
fitness=$(head -n 1 $outfile.tmp)
#buscar optimo en archivo

exec<"optimos.txt"
nproblem=`echo ${bench} | awk -F"/" '{print $NF}'`

while read line
do
    #echo "@line" 
    set -- $line
    name=$1
    if [[ $name == $nproblem ]]; 
    then
        optimo=$2
        echo "nombre: ${name}, optimo: ${optimo}" 
    fi
done
echo $fitness
diff=$(awk "BEGIN {printf \"%.2f\",${fitness}-${optimo}}")
gap=$(awk "BEGIN {printf \"%.2f\",100.00*${diff}/${optimo}}")
runlength=${gap}
rm ${outfile}.tmp

solved="SAT"
runtime=0
best_sol=0

#echo "variable1 (from data-file) = $runlength"
#echo "variable3 (from data-file) = $runtime"

echo "Result for ParamILS: ${solved}, ${runtime}, ${runlength}, ${best_sol}, ${seed}"
