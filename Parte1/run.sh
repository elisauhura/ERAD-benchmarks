# ===================
# ||    CLEANUP    ||
# ===================

rm results/*.out


# ===================
# ||   EXECUTION   ||
# ===================

SOURCE="binary-trees"
PARAM="15"


for i in $(seq 1 30)
do
	(time C/$SOURCE $PARAM) 2>> results/C.out
	(time python3 -OO Python/$SOURCE.py $PARAM) 2>> results/Python.out	
	(time Go/$SOURCE.go_run $PARAM) 2>> results/Go.out
done


