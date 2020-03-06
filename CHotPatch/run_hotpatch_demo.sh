#!/bin/bash 

make clean > /dev/null && make > /dev/null 

# run process in background
./dl_demo &
pid=$!
sleep 1
echo "Bash script: Copying my_dl2.so to my_dl.so"
cp my_dl2.so my_dl.so

wait $pid
