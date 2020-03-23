#!/bin/bash

perm_flag=0
dir_flag=0
dir_string=""
perm_string=""

if [ "$#" -ne 4 ]; then
    echo "Usage: "$0" -d <directory> -p <perm string> [-h]"
    exit 1
fi

while getopts ":d:p:h" option; do
    case "$option" in
       p) perm_flag=1
          perm_string=${OPTARG}
          ;;
       d) dir_flag=1
          dir_string=${OPTARG}
          ;;
       h) echo "Usage: "$0" -d <directory> -p <perm string> [-h]"
          exit 0
          ;;
       ?) printf "Error: Unknown option '-%s'.\n" $OPTARG >&2
          exit 1
          ;;
    esac
done


if [ $perm_flag -eq 0 ] || [ $dir_flag -eq 0 ]; then
   echo "One or more flags not specified: -d <directory> -p <permissions string>"
   exit 1
fi

touch masteroutput.txt
touch useroutput.txt
touch valgrind.txt

make clean > /dev/null && make > /dev/null #uncomment to remake project when run

#change to name of binary 
./pfind -d $dir_string -p $perm_string &> useroutput.txt
#change to name of given binary
./pfindmaster -d $dir_string -p $perm_string &> masteroutput.txt

valgrind ./pfind -d $dir_string -p $perm_string &> valgrind.txt 
diff -c masteroutput.txt useroutput.txt
echo "Master output is on the top, user output is on the bottom. No output if no difference."
echo "WC output: <<$(wc useroutput.txt)>>"
tail -n 8 valgrind.txt
exit 0