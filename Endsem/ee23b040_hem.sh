#!/bin/bash


gcc ee23b040_hem.c -o out -lm

OUTFILE="ee23b040_hem.txt"
rm -f "$OUTFILE"
touch "$OUTFILE"

for I in $(seq 2 1 25)
do
	VAL1=$(./out $I)
	VAL2=$(./out $((I+1)))
	RATIO=$(awk "BEGIN{print $VAL2/$VAL1}")
	echo "$I $VAL1 $RATIO" >> "$OUTFILE"
done

gnuplot -persist -e "load 'ee23b040_hemgp.txt'"