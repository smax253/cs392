#!/bin/bash

size_flag=0

while getopts ":s" option; do
    case "$option" in
       s) size_flag=1
          ;;
       ?) printf "Error: Unknown option '-%s'.\n" $OPTARG >&2
          exit 1
          ;;
    esac
done

declare -a filenames

shift "$((OPTIND-1))"
index=0
for f in $@; do
   filenames[$index]="$f"
   (( ++index ))
done

if [ $size_flag -eq 1 ]; then
   echo "Yay, size flag!"
fi
echo ${filenames[*]}

exit 0