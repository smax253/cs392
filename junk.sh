###############################################################################
# Author: Max Shi
# Date: 2/7/2020
# Pledge: I pledge my honor that I have abided by the Stevens Honor System.
# Description: Implementation of the junk.sh script from Borowski's CS392 Assignment 1.
###############################################################################
#!/bin/bash

readonly JUNKPATH="$HOME/.junk"


if [ ! -d "$JUNKPATH" ]; then
    #echo "Create .junk"
    mkdir -p "$JUNKPATH"
fi

print_help () {
    cat <<END_HELP_STRING
Usage: $(basename "$0") [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files.
END_HELP_STRING
}

purge_files () {
    cd $JUNKPATH
    rm -rf .* 2> /dev/null 
    rm -rf *
}

list_files () {
    cd $JUNKPATH
    ls -lAF | cat
    #echo $(ls -lAF)
}

help_flag=0
purge_flag=0
list_flag=0
no_flag=1



while getopts ":hpl" option; do
    case "$option" in
       h) help_flag=1
          ((--no_flag))
          ;;
       p) purge_flag=1
          ((--no_flag))
          ;;
       l) list_flag=1
          ((--no_flag))
          ;;
       ?) printf "Error: Unknown option '-%s'.\n" $OPTARG >&2
          print_help
          exit 1
          ;;
    esac
done



shift "$((OPTIND-1))"
declare -a filenames
index=0
for f in $@; do
    filenames[$index]="$f"
    ((++index))
done

#echo $index

if [ $index -gt 0 ]; then
    ((--no_flag))
fi

#echo $no_flag


if [ $no_flag -lt 0 ]; then
    echo "Error: Too many options enabled."
    print_help
    exit 1
fi

if [ $help_flag -eq 1 ] || [ $no_flag -eq 1 ]; then
   print_help
   exit 0
fi

if [ $purge_flag -eq 1 ]; then
    purge_files
    #echo "Yay, purge flag!"
    exit 0
fi

if [ $list_flag -eq 1 ]; then
    list_files
   #echo "Yay, list flag!"
   exit 0
fi

for file in "${filenames[@]}"; do
    if [ ! -f "$file" ] && [ ! -d "$file" ]; then
        echo "Warning: '$file' not found."
    else 
        mv "$file" -t $JUNKPATH
    fi
    #echo $file
done
exit 0