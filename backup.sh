#!/bin/bash

readonly JUNKPATH="~/.junk"

if [ ! -d $JUNKPATH ]; then
    echo "Create .junk"
    mkdir -p $JUNKPATH
fi


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
          exit 1
          ;;
    esac
done

print_help () {
    cat <<END_HELP_STRING
Usage: $(basename "$file") [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files.
END_HELP_STRING
}
shift "$((OPTIND-1))"
declare -a filenames
index=0
for f in $@; do
    filenames[$index]="$f"
    ((++index))
done

echo $index

if [ $index -gt 0 ]; then
    ((--no_flag))
fi

echo $no_flag


if [ $no_flag -lt 0 ]; then
    echo "Error: Too many options enabled."
    print_help
    exit 1
fi

if [ $help_flag -eq 1 ]; then
   print_help
   exit 0
fi

if [ $purge_flag -eq 1 ]; then
   echo "Yay, purge flag!"
fi

if [ $list_flag -eq 1 ]; then
   echo "Yay, list flag!"
fi

if [ $no_flag -eq 0 ]; then
   echo "Yay, no flag!"
fi


exit 0