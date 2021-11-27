#!/usr/bin/bash

# Write a shell script multiplication_table that will generate a multiplication table for a number
# given on the command line.

echo -n "Enter a Number: "; read n
echo -n "Enter Range: "; read r

echo "Multiplication Table for $n: "
i=0
while [ $i -le $r ]
do
    echo " $n x $i = `expr $n \* $i`"
    i=`expr $i + 1`
done
