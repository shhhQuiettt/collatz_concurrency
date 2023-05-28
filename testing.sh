#!/bin/bash

# display usage

#this script runs in parrarel $n number of instances of the program
#
# get the number of instances
n=$1
# max_steps=$2
echo "Running $n instances of the program"

# remove shared memory
rm ./.data/*

# run $n instances of the program
for ((i=0; i<$n; i++))
do
    echo "Running instance $i"
    ./collatz 400 &
done

wait
